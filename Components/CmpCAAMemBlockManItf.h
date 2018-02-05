 
	
	
#ifndef _CMPCAAMEMBLOCKMANITF_H_
#define _CMPCAAMEMBLOCKMANITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAAMemBlockMan.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Pool Functions */
CAA_HANDLE CDECL MBM_PoolCreateH(CAA_COUNT ctNumBlocks, CAA_SIZE szBlockSize, CAA_ENUM eEmpty, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_POOLCREATEH) (CAA_COUNT ctNumBlocks, CAA_SIZE szBlockSize, CAA_ENUM eEmpty, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLCREATEH_NOTIMPLEMENTED)
	#define USE_MBM_PoolCreateH
	#define EXT_MBM_PoolCreateH
	#define GET_MBM_PoolCreateH(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_PoolCreateH(p0,p1,p2,p3)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_PoolCreateH  FALSE
	#define EXP_MBM_PoolCreateH  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_PoolCreateH
	#define EXT_MBM_PoolCreateH
	#define GET_MBM_PoolCreateH(fl)  CAL_CMGETAPI( "MBM_PoolCreateH" ) 
	#define CAL_MBM_PoolCreateH  MBM_PoolCreateH
	#define CHK_MBM_PoolCreateH  TRUE
	#define EXP_MBM_PoolCreateH  CAL_CMEXPAPI( "MBM_PoolCreateH" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_PoolCreateH
	#define EXT_MBM_PoolCreateH
	#define GET_MBM_PoolCreateH(fl)  CAL_CMGETAPI( "MBM_PoolCreateH" ) 
	#define CAL_MBM_PoolCreateH  MBM_PoolCreateH
	#define CHK_MBM_PoolCreateH  TRUE
	#define EXP_MBM_PoolCreateH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolCreateH", (RTS_UINTPTR)MBM_PoolCreateH, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_PoolCreateH
	#define EXT_CmpCAAMemBlockManMBM_PoolCreateH
	#define GET_CmpCAAMemBlockManMBM_PoolCreateH  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_PoolCreateH pICmpCAAMemBlockMan->IMBM_PoolCreateH
	#define CHK_CmpCAAMemBlockManMBM_PoolCreateH (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_PoolCreateH  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_PoolCreateH
	#define EXT_MBM_PoolCreateH
	#define GET_MBM_PoolCreateH(fl)  CAL_CMGETAPI( "MBM_PoolCreateH" ) 
	#define CAL_MBM_PoolCreateH pICmpCAAMemBlockMan->IMBM_PoolCreateH
	#define CHK_MBM_PoolCreateH (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_PoolCreateH  CAL_CMEXPAPI( "MBM_PoolCreateH" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_PoolCreateH  PFMBM_POOLCREATEH pfMBM_PoolCreateH;
	#define EXT_MBM_PoolCreateH  extern PFMBM_POOLCREATEH pfMBM_PoolCreateH;
	#define GET_MBM_PoolCreateH(fl)  s_pfCMGetAPI2( "MBM_PoolCreateH", (RTS_VOID_FCTPTR *)&pfMBM_PoolCreateH, (fl), 0, 0)
	#define CAL_MBM_PoolCreateH  pfMBM_PoolCreateH
	#define CHK_MBM_PoolCreateH  (pfMBM_PoolCreateH != NULL)
	#define EXP_MBM_PoolCreateH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolCreateH", (RTS_UINTPTR)MBM_PoolCreateH, 0, 0) 
#endif



CAA_HANDLE CDECL MBM_PoolCreateP(CAA_SIZE szBlockSize, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ENUM eEmpty, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_POOLCREATEP) (CAA_SIZE szBlockSize, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ENUM eEmpty, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLCREATEP_NOTIMPLEMENTED)
	#define USE_MBM_PoolCreateP
	#define EXT_MBM_PoolCreateP
	#define GET_MBM_PoolCreateP(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_PoolCreateP(p0,p1,p2,p3,p4)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_PoolCreateP  FALSE
	#define EXP_MBM_PoolCreateP  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_PoolCreateP
	#define EXT_MBM_PoolCreateP
	#define GET_MBM_PoolCreateP(fl)  CAL_CMGETAPI( "MBM_PoolCreateP" ) 
	#define CAL_MBM_PoolCreateP  MBM_PoolCreateP
	#define CHK_MBM_PoolCreateP  TRUE
	#define EXP_MBM_PoolCreateP  CAL_CMEXPAPI( "MBM_PoolCreateP" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_PoolCreateP
	#define EXT_MBM_PoolCreateP
	#define GET_MBM_PoolCreateP(fl)  CAL_CMGETAPI( "MBM_PoolCreateP" ) 
	#define CAL_MBM_PoolCreateP  MBM_PoolCreateP
	#define CHK_MBM_PoolCreateP  TRUE
	#define EXP_MBM_PoolCreateP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolCreateP", (RTS_UINTPTR)MBM_PoolCreateP, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_PoolCreateP
	#define EXT_CmpCAAMemBlockManMBM_PoolCreateP
	#define GET_CmpCAAMemBlockManMBM_PoolCreateP  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_PoolCreateP pICmpCAAMemBlockMan->IMBM_PoolCreateP
	#define CHK_CmpCAAMemBlockManMBM_PoolCreateP (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_PoolCreateP  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_PoolCreateP
	#define EXT_MBM_PoolCreateP
	#define GET_MBM_PoolCreateP(fl)  CAL_CMGETAPI( "MBM_PoolCreateP" ) 
	#define CAL_MBM_PoolCreateP pICmpCAAMemBlockMan->IMBM_PoolCreateP
	#define CHK_MBM_PoolCreateP (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_PoolCreateP  CAL_CMEXPAPI( "MBM_PoolCreateP" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_PoolCreateP  PFMBM_POOLCREATEP pfMBM_PoolCreateP;
	#define EXT_MBM_PoolCreateP  extern PFMBM_POOLCREATEP pfMBM_PoolCreateP;
	#define GET_MBM_PoolCreateP(fl)  s_pfCMGetAPI2( "MBM_PoolCreateP", (RTS_VOID_FCTPTR *)&pfMBM_PoolCreateP, (fl), 0, 0)
	#define CAL_MBM_PoolCreateP  pfMBM_PoolCreateP
	#define CHK_MBM_PoolCreateP  (pfMBM_PoolCreateP != NULL)
	#define EXP_MBM_PoolCreateP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolCreateP", (RTS_UINTPTR)MBM_PoolCreateP, 0, 0) 
#endif



CAA_ERROR CDECL MBM_PoolExtendH(CAA_HANDLE hPool, CAA_COUNT ctNumBlocks);
typedef CAA_ERROR (CDECL * PFMBM_POOLEXTENDH) (CAA_HANDLE hPool, CAA_COUNT ctNumBlocks);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLEXTENDH_NOTIMPLEMENTED)
	#define USE_MBM_PoolExtendH
	#define EXT_MBM_PoolExtendH
	#define GET_MBM_PoolExtendH(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_PoolExtendH(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_PoolExtendH  FALSE
	#define EXP_MBM_PoolExtendH  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_PoolExtendH
	#define EXT_MBM_PoolExtendH
	#define GET_MBM_PoolExtendH(fl)  CAL_CMGETAPI( "MBM_PoolExtendH" ) 
	#define CAL_MBM_PoolExtendH  MBM_PoolExtendH
	#define CHK_MBM_PoolExtendH  TRUE
	#define EXP_MBM_PoolExtendH  CAL_CMEXPAPI( "MBM_PoolExtendH" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_PoolExtendH
	#define EXT_MBM_PoolExtendH
	#define GET_MBM_PoolExtendH(fl)  CAL_CMGETAPI( "MBM_PoolExtendH" ) 
	#define CAL_MBM_PoolExtendH  MBM_PoolExtendH
	#define CHK_MBM_PoolExtendH  TRUE
	#define EXP_MBM_PoolExtendH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolExtendH", (RTS_UINTPTR)MBM_PoolExtendH, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_PoolExtendH
	#define EXT_CmpCAAMemBlockManMBM_PoolExtendH
	#define GET_CmpCAAMemBlockManMBM_PoolExtendH  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_PoolExtendH pICmpCAAMemBlockMan->IMBM_PoolExtendH
	#define CHK_CmpCAAMemBlockManMBM_PoolExtendH (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_PoolExtendH  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_PoolExtendH
	#define EXT_MBM_PoolExtendH
	#define GET_MBM_PoolExtendH(fl)  CAL_CMGETAPI( "MBM_PoolExtendH" ) 
	#define CAL_MBM_PoolExtendH pICmpCAAMemBlockMan->IMBM_PoolExtendH
	#define CHK_MBM_PoolExtendH (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_PoolExtendH  CAL_CMEXPAPI( "MBM_PoolExtendH" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_PoolExtendH  PFMBM_POOLEXTENDH pfMBM_PoolExtendH;
	#define EXT_MBM_PoolExtendH  extern PFMBM_POOLEXTENDH pfMBM_PoolExtendH;
	#define GET_MBM_PoolExtendH(fl)  s_pfCMGetAPI2( "MBM_PoolExtendH", (RTS_VOID_FCTPTR *)&pfMBM_PoolExtendH, (fl), 0, 0)
	#define CAL_MBM_PoolExtendH  pfMBM_PoolExtendH
	#define CHK_MBM_PoolExtendH  (pfMBM_PoolExtendH != NULL)
	#define EXP_MBM_PoolExtendH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolExtendH", (RTS_UINTPTR)MBM_PoolExtendH, 0, 0) 
#endif



CAA_ERROR CDECL MBM_PoolDelete(CAA_HANDLE hPool);
typedef CAA_ERROR (CDECL * PFMBM_POOLDELETE) (CAA_HANDLE hPool);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLDELETE_NOTIMPLEMENTED)
	#define USE_MBM_PoolDelete
	#define EXT_MBM_PoolDelete
	#define GET_MBM_PoolDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_PoolDelete(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_PoolDelete  FALSE
	#define EXP_MBM_PoolDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_PoolDelete
	#define EXT_MBM_PoolDelete
	#define GET_MBM_PoolDelete(fl)  CAL_CMGETAPI( "MBM_PoolDelete" ) 
	#define CAL_MBM_PoolDelete  MBM_PoolDelete
	#define CHK_MBM_PoolDelete  TRUE
	#define EXP_MBM_PoolDelete  CAL_CMEXPAPI( "MBM_PoolDelete" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_PoolDelete
	#define EXT_MBM_PoolDelete
	#define GET_MBM_PoolDelete(fl)  CAL_CMGETAPI( "MBM_PoolDelete" ) 
	#define CAL_MBM_PoolDelete  MBM_PoolDelete
	#define CHK_MBM_PoolDelete  TRUE
	#define EXP_MBM_PoolDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolDelete", (RTS_UINTPTR)MBM_PoolDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_PoolDelete
	#define EXT_CmpCAAMemBlockManMBM_PoolDelete
	#define GET_CmpCAAMemBlockManMBM_PoolDelete  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_PoolDelete pICmpCAAMemBlockMan->IMBM_PoolDelete
	#define CHK_CmpCAAMemBlockManMBM_PoolDelete (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_PoolDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_PoolDelete
	#define EXT_MBM_PoolDelete
	#define GET_MBM_PoolDelete(fl)  CAL_CMGETAPI( "MBM_PoolDelete" ) 
	#define CAL_MBM_PoolDelete pICmpCAAMemBlockMan->IMBM_PoolDelete
	#define CHK_MBM_PoolDelete (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_PoolDelete  CAL_CMEXPAPI( "MBM_PoolDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_PoolDelete  PFMBM_POOLDELETE pfMBM_PoolDelete;
	#define EXT_MBM_PoolDelete  extern PFMBM_POOLDELETE pfMBM_PoolDelete;
	#define GET_MBM_PoolDelete(fl)  s_pfCMGetAPI2( "MBM_PoolDelete", (RTS_VOID_FCTPTR *)&pfMBM_PoolDelete, (fl), 0, 0)
	#define CAL_MBM_PoolDelete  pfMBM_PoolDelete
	#define CHK_MBM_PoolDelete  (pfMBM_PoolDelete != NULL)
	#define EXP_MBM_PoolDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolDelete", (RTS_UINTPTR)MBM_PoolDelete, 0, 0) 
#endif



CAA_HANDLE CDECL MBM_PoolGetBlock(CAA_HANDLE hPool, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_POOLGETBLOCK) (CAA_HANDLE hPool, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLGETBLOCK_NOTIMPLEMENTED)
	#define USE_MBM_PoolGetBlock
	#define EXT_MBM_PoolGetBlock
	#define GET_MBM_PoolGetBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_PoolGetBlock(p0,p1)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_PoolGetBlock  FALSE
	#define EXP_MBM_PoolGetBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_PoolGetBlock
	#define EXT_MBM_PoolGetBlock
	#define GET_MBM_PoolGetBlock(fl)  CAL_CMGETAPI( "MBM_PoolGetBlock" ) 
	#define CAL_MBM_PoolGetBlock  MBM_PoolGetBlock
	#define CHK_MBM_PoolGetBlock  TRUE
	#define EXP_MBM_PoolGetBlock  CAL_CMEXPAPI( "MBM_PoolGetBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_PoolGetBlock
	#define EXT_MBM_PoolGetBlock
	#define GET_MBM_PoolGetBlock(fl)  CAL_CMGETAPI( "MBM_PoolGetBlock" ) 
	#define CAL_MBM_PoolGetBlock  MBM_PoolGetBlock
	#define CHK_MBM_PoolGetBlock  TRUE
	#define EXP_MBM_PoolGetBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolGetBlock", (RTS_UINTPTR)MBM_PoolGetBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_PoolGetBlock
	#define EXT_CmpCAAMemBlockManMBM_PoolGetBlock
	#define GET_CmpCAAMemBlockManMBM_PoolGetBlock  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_PoolGetBlock pICmpCAAMemBlockMan->IMBM_PoolGetBlock
	#define CHK_CmpCAAMemBlockManMBM_PoolGetBlock (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_PoolGetBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_PoolGetBlock
	#define EXT_MBM_PoolGetBlock
	#define GET_MBM_PoolGetBlock(fl)  CAL_CMGETAPI( "MBM_PoolGetBlock" ) 
	#define CAL_MBM_PoolGetBlock pICmpCAAMemBlockMan->IMBM_PoolGetBlock
	#define CHK_MBM_PoolGetBlock (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_PoolGetBlock  CAL_CMEXPAPI( "MBM_PoolGetBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_PoolGetBlock  PFMBM_POOLGETBLOCK pfMBM_PoolGetBlock;
	#define EXT_MBM_PoolGetBlock  extern PFMBM_POOLGETBLOCK pfMBM_PoolGetBlock;
	#define GET_MBM_PoolGetBlock(fl)  s_pfCMGetAPI2( "MBM_PoolGetBlock", (RTS_VOID_FCTPTR *)&pfMBM_PoolGetBlock, (fl), 0, 0)
	#define CAL_MBM_PoolGetBlock  pfMBM_PoolGetBlock
	#define CHK_MBM_PoolGetBlock  (pfMBM_PoolGetBlock != NULL)
	#define EXP_MBM_PoolGetBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolGetBlock", (RTS_UINTPTR)MBM_PoolGetBlock, 0, 0) 
#endif



CAA_PVOID CDECL MBM_BlockGetData(CAA_HANDLE hBlock, CAA_ERROR* peError);
typedef CAA_PVOID (CDECL * PFMBM_BLOCKGETDATA) (CAA_HANDLE hBlock, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_BLOCKGETDATA_NOTIMPLEMENTED)
	#define USE_MBM_BlockGetData
	#define EXT_MBM_BlockGetData
	#define GET_MBM_BlockGetData(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_BlockGetData(p0,p1)  (CAA_PVOID)ERR_NOTIMPLEMENTED
	#define CHK_MBM_BlockGetData  FALSE
	#define EXP_MBM_BlockGetData  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_BlockGetData
	#define EXT_MBM_BlockGetData
	#define GET_MBM_BlockGetData(fl)  CAL_CMGETAPI( "MBM_BlockGetData" ) 
	#define CAL_MBM_BlockGetData  MBM_BlockGetData
	#define CHK_MBM_BlockGetData  TRUE
	#define EXP_MBM_BlockGetData  CAL_CMEXPAPI( "MBM_BlockGetData" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_BlockGetData
	#define EXT_MBM_BlockGetData
	#define GET_MBM_BlockGetData(fl)  CAL_CMGETAPI( "MBM_BlockGetData" ) 
	#define CAL_MBM_BlockGetData  MBM_BlockGetData
	#define CHK_MBM_BlockGetData  TRUE
	#define EXP_MBM_BlockGetData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_BlockGetData", (RTS_UINTPTR)MBM_BlockGetData, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_BlockGetData
	#define EXT_CmpCAAMemBlockManMBM_BlockGetData
	#define GET_CmpCAAMemBlockManMBM_BlockGetData  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_BlockGetData pICmpCAAMemBlockMan->IMBM_BlockGetData
	#define CHK_CmpCAAMemBlockManMBM_BlockGetData (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_BlockGetData  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_BlockGetData
	#define EXT_MBM_BlockGetData
	#define GET_MBM_BlockGetData(fl)  CAL_CMGETAPI( "MBM_BlockGetData" ) 
	#define CAL_MBM_BlockGetData pICmpCAAMemBlockMan->IMBM_BlockGetData
	#define CHK_MBM_BlockGetData (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_BlockGetData  CAL_CMEXPAPI( "MBM_BlockGetData" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_BlockGetData  PFMBM_BLOCKGETDATA pfMBM_BlockGetData;
	#define EXT_MBM_BlockGetData  extern PFMBM_BLOCKGETDATA pfMBM_BlockGetData;
	#define GET_MBM_BlockGetData(fl)  s_pfCMGetAPI2( "MBM_BlockGetData", (RTS_VOID_FCTPTR *)&pfMBM_BlockGetData, (fl), 0, 0)
	#define CAL_MBM_BlockGetData  pfMBM_BlockGetData
	#define CHK_MBM_BlockGetData  (pfMBM_BlockGetData != NULL)
	#define EXP_MBM_BlockGetData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_BlockGetData", (RTS_UINTPTR)MBM_BlockGetData, 0, 0) 
#endif



CAA_ERROR CDECL MBM_PoolPutBlock(CAA_HANDLE hBlock);
typedef CAA_ERROR (CDECL * PFMBM_POOLPUTBLOCK) (CAA_HANDLE hBlock);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLPUTBLOCK_NOTIMPLEMENTED)
	#define USE_MBM_PoolPutBlock
	#define EXT_MBM_PoolPutBlock
	#define GET_MBM_PoolPutBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_PoolPutBlock(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_PoolPutBlock  FALSE
	#define EXP_MBM_PoolPutBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_PoolPutBlock
	#define EXT_MBM_PoolPutBlock
	#define GET_MBM_PoolPutBlock(fl)  CAL_CMGETAPI( "MBM_PoolPutBlock" ) 
	#define CAL_MBM_PoolPutBlock  MBM_PoolPutBlock
	#define CHK_MBM_PoolPutBlock  TRUE
	#define EXP_MBM_PoolPutBlock  CAL_CMEXPAPI( "MBM_PoolPutBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_PoolPutBlock
	#define EXT_MBM_PoolPutBlock
	#define GET_MBM_PoolPutBlock(fl)  CAL_CMGETAPI( "MBM_PoolPutBlock" ) 
	#define CAL_MBM_PoolPutBlock  MBM_PoolPutBlock
	#define CHK_MBM_PoolPutBlock  TRUE
	#define EXP_MBM_PoolPutBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolPutBlock", (RTS_UINTPTR)MBM_PoolPutBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_PoolPutBlock
	#define EXT_CmpCAAMemBlockManMBM_PoolPutBlock
	#define GET_CmpCAAMemBlockManMBM_PoolPutBlock  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_PoolPutBlock pICmpCAAMemBlockMan->IMBM_PoolPutBlock
	#define CHK_CmpCAAMemBlockManMBM_PoolPutBlock (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_PoolPutBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_PoolPutBlock
	#define EXT_MBM_PoolPutBlock
	#define GET_MBM_PoolPutBlock(fl)  CAL_CMGETAPI( "MBM_PoolPutBlock" ) 
	#define CAL_MBM_PoolPutBlock pICmpCAAMemBlockMan->IMBM_PoolPutBlock
	#define CHK_MBM_PoolPutBlock (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_PoolPutBlock  CAL_CMEXPAPI( "MBM_PoolPutBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_PoolPutBlock  PFMBM_POOLPUTBLOCK pfMBM_PoolPutBlock;
	#define EXT_MBM_PoolPutBlock  extern PFMBM_POOLPUTBLOCK pfMBM_PoolPutBlock;
	#define GET_MBM_PoolPutBlock(fl)  s_pfCMGetAPI2( "MBM_PoolPutBlock", (RTS_VOID_FCTPTR *)&pfMBM_PoolPutBlock, (fl), 0, 0)
	#define CAL_MBM_PoolPutBlock  pfMBM_PoolPutBlock
	#define CHK_MBM_PoolPutBlock  (pfMBM_PoolPutBlock != NULL)
	#define EXP_MBM_PoolPutBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolPutBlock", (RTS_UINTPTR)MBM_PoolPutBlock, 0, 0) 
#endif



CAA_SIZE CDECL MBM_PoolGetSize(CAA_COUNT ctNumBlocks, CAA_SIZE szBlockSize);
typedef CAA_SIZE (CDECL * PFMBM_POOLGETSIZE) (CAA_COUNT ctNumBlocks, CAA_SIZE szBlockSize);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLGETSIZE_NOTIMPLEMENTED)
	#define USE_MBM_PoolGetSize
	#define EXT_MBM_PoolGetSize
	#define GET_MBM_PoolGetSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_PoolGetSize(p0,p1)  (CAA_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_PoolGetSize  FALSE
	#define EXP_MBM_PoolGetSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_PoolGetSize
	#define EXT_MBM_PoolGetSize
	#define GET_MBM_PoolGetSize(fl)  CAL_CMGETAPI( "MBM_PoolGetSize" ) 
	#define CAL_MBM_PoolGetSize  MBM_PoolGetSize
	#define CHK_MBM_PoolGetSize  TRUE
	#define EXP_MBM_PoolGetSize  CAL_CMEXPAPI( "MBM_PoolGetSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_PoolGetSize
	#define EXT_MBM_PoolGetSize
	#define GET_MBM_PoolGetSize(fl)  CAL_CMGETAPI( "MBM_PoolGetSize" ) 
	#define CAL_MBM_PoolGetSize  MBM_PoolGetSize
	#define CHK_MBM_PoolGetSize  TRUE
	#define EXP_MBM_PoolGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolGetSize", (RTS_UINTPTR)MBM_PoolGetSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_PoolGetSize
	#define EXT_CmpCAAMemBlockManMBM_PoolGetSize
	#define GET_CmpCAAMemBlockManMBM_PoolGetSize  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_PoolGetSize pICmpCAAMemBlockMan->IMBM_PoolGetSize
	#define CHK_CmpCAAMemBlockManMBM_PoolGetSize (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_PoolGetSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_PoolGetSize
	#define EXT_MBM_PoolGetSize
	#define GET_MBM_PoolGetSize(fl)  CAL_CMGETAPI( "MBM_PoolGetSize" ) 
	#define CAL_MBM_PoolGetSize pICmpCAAMemBlockMan->IMBM_PoolGetSize
	#define CHK_MBM_PoolGetSize (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_PoolGetSize  CAL_CMEXPAPI( "MBM_PoolGetSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_PoolGetSize  PFMBM_POOLGETSIZE pfMBM_PoolGetSize;
	#define EXT_MBM_PoolGetSize  extern PFMBM_POOLGETSIZE pfMBM_PoolGetSize;
	#define GET_MBM_PoolGetSize(fl)  s_pfCMGetAPI2( "MBM_PoolGetSize", (RTS_VOID_FCTPTR *)&pfMBM_PoolGetSize, (fl), 0, 0)
	#define CAL_MBM_PoolGetSize  pfMBM_PoolGetSize
	#define CHK_MBM_PoolGetSize  (pfMBM_PoolGetSize != NULL)
	#define EXP_MBM_PoolGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_PoolGetSize", (RTS_UINTPTR)MBM_PoolGetSize, 0, 0) 
#endif




/* Message Functions */
CAA_HANDLE CDECL MBM_MsgReceive(CAA_HANDLE hXChg, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_MSGRECEIVE) (CAA_HANDLE hXChg, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGRECEIVE_NOTIMPLEMENTED)
	#define USE_MBM_MsgReceive
	#define EXT_MBM_MsgReceive
	#define GET_MBM_MsgReceive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_MsgReceive(p0,p1,p2)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_MsgReceive  FALSE
	#define EXP_MBM_MsgReceive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_MsgReceive
	#define EXT_MBM_MsgReceive
	#define GET_MBM_MsgReceive(fl)  CAL_CMGETAPI( "MBM_MsgReceive" ) 
	#define CAL_MBM_MsgReceive  MBM_MsgReceive
	#define CHK_MBM_MsgReceive  TRUE
	#define EXP_MBM_MsgReceive  CAL_CMEXPAPI( "MBM_MsgReceive" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_MsgReceive
	#define EXT_MBM_MsgReceive
	#define GET_MBM_MsgReceive(fl)  CAL_CMGETAPI( "MBM_MsgReceive" ) 
	#define CAL_MBM_MsgReceive  MBM_MsgReceive
	#define CHK_MBM_MsgReceive  TRUE
	#define EXP_MBM_MsgReceive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgReceive", (RTS_UINTPTR)MBM_MsgReceive, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_MsgReceive
	#define EXT_CmpCAAMemBlockManMBM_MsgReceive
	#define GET_CmpCAAMemBlockManMBM_MsgReceive  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_MsgReceive pICmpCAAMemBlockMan->IMBM_MsgReceive
	#define CHK_CmpCAAMemBlockManMBM_MsgReceive (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_MsgReceive  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_MsgReceive
	#define EXT_MBM_MsgReceive
	#define GET_MBM_MsgReceive(fl)  CAL_CMGETAPI( "MBM_MsgReceive" ) 
	#define CAL_MBM_MsgReceive pICmpCAAMemBlockMan->IMBM_MsgReceive
	#define CHK_MBM_MsgReceive (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_MsgReceive  CAL_CMEXPAPI( "MBM_MsgReceive" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_MsgReceive  PFMBM_MSGRECEIVE pfMBM_MsgReceive;
	#define EXT_MBM_MsgReceive  extern PFMBM_MSGRECEIVE pfMBM_MsgReceive;
	#define GET_MBM_MsgReceive(fl)  s_pfCMGetAPI2( "MBM_MsgReceive", (RTS_VOID_FCTPTR *)&pfMBM_MsgReceive, (fl), 0, 0)
	#define CAL_MBM_MsgReceive  pfMBM_MsgReceive
	#define CHK_MBM_MsgReceive  (pfMBM_MsgReceive != NULL)
	#define EXP_MBM_MsgReceive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgReceive", (RTS_UINTPTR)MBM_MsgReceive, 0, 0) 
#endif



CAA_PVOID CDECL MBM_MsgGetData(CAA_HANDLE hMsg, CAA_ERROR* peError);
typedef CAA_PVOID (CDECL * PFMBM_MSGGETDATA) (CAA_HANDLE hMsg, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGGETDATA_NOTIMPLEMENTED)
	#define USE_MBM_MsgGetData
	#define EXT_MBM_MsgGetData
	#define GET_MBM_MsgGetData(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_MsgGetData(p0,p1)  (CAA_PVOID)ERR_NOTIMPLEMENTED
	#define CHK_MBM_MsgGetData  FALSE
	#define EXP_MBM_MsgGetData  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_MsgGetData
	#define EXT_MBM_MsgGetData
	#define GET_MBM_MsgGetData(fl)  CAL_CMGETAPI( "MBM_MsgGetData" ) 
	#define CAL_MBM_MsgGetData  MBM_MsgGetData
	#define CHK_MBM_MsgGetData  TRUE
	#define EXP_MBM_MsgGetData  CAL_CMEXPAPI( "MBM_MsgGetData" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_MsgGetData
	#define EXT_MBM_MsgGetData
	#define GET_MBM_MsgGetData(fl)  CAL_CMGETAPI( "MBM_MsgGetData" ) 
	#define CAL_MBM_MsgGetData  MBM_MsgGetData
	#define CHK_MBM_MsgGetData  TRUE
	#define EXP_MBM_MsgGetData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgGetData", (RTS_UINTPTR)MBM_MsgGetData, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_MsgGetData
	#define EXT_CmpCAAMemBlockManMBM_MsgGetData
	#define GET_CmpCAAMemBlockManMBM_MsgGetData  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_MsgGetData pICmpCAAMemBlockMan->IMBM_MsgGetData
	#define CHK_CmpCAAMemBlockManMBM_MsgGetData (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_MsgGetData  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_MsgGetData
	#define EXT_MBM_MsgGetData
	#define GET_MBM_MsgGetData(fl)  CAL_CMGETAPI( "MBM_MsgGetData" ) 
	#define CAL_MBM_MsgGetData pICmpCAAMemBlockMan->IMBM_MsgGetData
	#define CHK_MBM_MsgGetData (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_MsgGetData  CAL_CMEXPAPI( "MBM_MsgGetData" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_MsgGetData  PFMBM_MSGGETDATA pfMBM_MsgGetData;
	#define EXT_MBM_MsgGetData  extern PFMBM_MSGGETDATA pfMBM_MsgGetData;
	#define GET_MBM_MsgGetData(fl)  s_pfCMGetAPI2( "MBM_MsgGetData", (RTS_VOID_FCTPTR *)&pfMBM_MsgGetData, (fl), 0, 0)
	#define CAL_MBM_MsgGetData  pfMBM_MsgGetData
	#define CHK_MBM_MsgGetData  (pfMBM_MsgGetData != NULL)
	#define EXP_MBM_MsgGetData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgGetData", (RTS_UINTPTR)MBM_MsgGetData, 0, 0) 
#endif



CAA_ERROR CDECL MBM_MsgSend(CAA_HANDLE hMsg, unsigned char ucPrio, CAA_HANDLE hXChg);
typedef CAA_ERROR (CDECL * PFMBM_MSGSEND) (CAA_HANDLE hMsg, unsigned char ucPrio, CAA_HANDLE hXChg);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGSEND_NOTIMPLEMENTED)
	#define USE_MBM_MsgSend
	#define EXT_MBM_MsgSend
	#define GET_MBM_MsgSend(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_MsgSend(p0,p1,p2)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_MsgSend  FALSE
	#define EXP_MBM_MsgSend  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_MsgSend
	#define EXT_MBM_MsgSend
	#define GET_MBM_MsgSend(fl)  CAL_CMGETAPI( "MBM_MsgSend" ) 
	#define CAL_MBM_MsgSend  MBM_MsgSend
	#define CHK_MBM_MsgSend  TRUE
	#define EXP_MBM_MsgSend  CAL_CMEXPAPI( "MBM_MsgSend" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_MsgSend
	#define EXT_MBM_MsgSend
	#define GET_MBM_MsgSend(fl)  CAL_CMGETAPI( "MBM_MsgSend" ) 
	#define CAL_MBM_MsgSend  MBM_MsgSend
	#define CHK_MBM_MsgSend  TRUE
	#define EXP_MBM_MsgSend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgSend", (RTS_UINTPTR)MBM_MsgSend, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_MsgSend
	#define EXT_CmpCAAMemBlockManMBM_MsgSend
	#define GET_CmpCAAMemBlockManMBM_MsgSend  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_MsgSend pICmpCAAMemBlockMan->IMBM_MsgSend
	#define CHK_CmpCAAMemBlockManMBM_MsgSend (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_MsgSend  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_MsgSend
	#define EXT_MBM_MsgSend
	#define GET_MBM_MsgSend(fl)  CAL_CMGETAPI( "MBM_MsgSend" ) 
	#define CAL_MBM_MsgSend pICmpCAAMemBlockMan->IMBM_MsgSend
	#define CHK_MBM_MsgSend (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_MsgSend  CAL_CMEXPAPI( "MBM_MsgSend" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_MsgSend  PFMBM_MSGSEND pfMBM_MsgSend;
	#define EXT_MBM_MsgSend  extern PFMBM_MSGSEND pfMBM_MsgSend;
	#define GET_MBM_MsgSend(fl)  s_pfCMGetAPI2( "MBM_MsgSend", (RTS_VOID_FCTPTR *)&pfMBM_MsgSend, (fl), 0, 0)
	#define CAL_MBM_MsgSend  pfMBM_MsgSend
	#define CHK_MBM_MsgSend  (pfMBM_MsgSend != NULL)
	#define EXP_MBM_MsgSend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgSend", (RTS_UINTPTR)MBM_MsgSend, 0, 0) 
#endif



CAA_ERROR CDECL MBM_MsgAddRef(CAA_HANDLE hMsg);
typedef CAA_ERROR (CDECL * PFMBM_MSGADDREF) (CAA_HANDLE hMsg);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGADDREF_NOTIMPLEMENTED)
	#define USE_MBM_MsgAddRef
	#define EXT_MBM_MsgAddRef
	#define GET_MBM_MsgAddRef(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_MsgAddRef(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_MsgAddRef  FALSE
	#define EXP_MBM_MsgAddRef  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_MsgAddRef
	#define EXT_MBM_MsgAddRef
	#define GET_MBM_MsgAddRef(fl)  CAL_CMGETAPI( "MBM_MsgAddRef" ) 
	#define CAL_MBM_MsgAddRef  MBM_MsgAddRef
	#define CHK_MBM_MsgAddRef  TRUE
	#define EXP_MBM_MsgAddRef  CAL_CMEXPAPI( "MBM_MsgAddRef" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_MsgAddRef
	#define EXT_MBM_MsgAddRef
	#define GET_MBM_MsgAddRef(fl)  CAL_CMGETAPI( "MBM_MsgAddRef" ) 
	#define CAL_MBM_MsgAddRef  MBM_MsgAddRef
	#define CHK_MBM_MsgAddRef  TRUE
	#define EXP_MBM_MsgAddRef  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgAddRef", (RTS_UINTPTR)MBM_MsgAddRef, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_MsgAddRef
	#define EXT_CmpCAAMemBlockManMBM_MsgAddRef
	#define GET_CmpCAAMemBlockManMBM_MsgAddRef  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_MsgAddRef pICmpCAAMemBlockMan->IMBM_MsgAddRef
	#define CHK_CmpCAAMemBlockManMBM_MsgAddRef (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_MsgAddRef  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_MsgAddRef
	#define EXT_MBM_MsgAddRef
	#define GET_MBM_MsgAddRef(fl)  CAL_CMGETAPI( "MBM_MsgAddRef" ) 
	#define CAL_MBM_MsgAddRef pICmpCAAMemBlockMan->IMBM_MsgAddRef
	#define CHK_MBM_MsgAddRef (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_MsgAddRef  CAL_CMEXPAPI( "MBM_MsgAddRef" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_MsgAddRef  PFMBM_MSGADDREF pfMBM_MsgAddRef;
	#define EXT_MBM_MsgAddRef  extern PFMBM_MSGADDREF pfMBM_MsgAddRef;
	#define GET_MBM_MsgAddRef(fl)  s_pfCMGetAPI2( "MBM_MsgAddRef", (RTS_VOID_FCTPTR *)&pfMBM_MsgAddRef, (fl), 0, 0)
	#define CAL_MBM_MsgAddRef  pfMBM_MsgAddRef
	#define CHK_MBM_MsgAddRef  (pfMBM_MsgAddRef != NULL)
	#define EXP_MBM_MsgAddRef  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgAddRef", (RTS_UINTPTR)MBM_MsgAddRef, 0, 0) 
#endif



CAA_ERROR CDECL MBM_MsgRelease(CAA_HANDLE hMsg);
typedef CAA_ERROR (CDECL * PFMBM_MSGRELEASE) (CAA_HANDLE hMsg);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGRELEASE_NOTIMPLEMENTED)
	#define USE_MBM_MsgRelease
	#define EXT_MBM_MsgRelease
	#define GET_MBM_MsgRelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_MsgRelease(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_MsgRelease  FALSE
	#define EXP_MBM_MsgRelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_MsgRelease
	#define EXT_MBM_MsgRelease
	#define GET_MBM_MsgRelease(fl)  CAL_CMGETAPI( "MBM_MsgRelease" ) 
	#define CAL_MBM_MsgRelease  MBM_MsgRelease
	#define CHK_MBM_MsgRelease  TRUE
	#define EXP_MBM_MsgRelease  CAL_CMEXPAPI( "MBM_MsgRelease" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_MsgRelease
	#define EXT_MBM_MsgRelease
	#define GET_MBM_MsgRelease(fl)  CAL_CMGETAPI( "MBM_MsgRelease" ) 
	#define CAL_MBM_MsgRelease  MBM_MsgRelease
	#define CHK_MBM_MsgRelease  TRUE
	#define EXP_MBM_MsgRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgRelease", (RTS_UINTPTR)MBM_MsgRelease, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_MsgRelease
	#define EXT_CmpCAAMemBlockManMBM_MsgRelease
	#define GET_CmpCAAMemBlockManMBM_MsgRelease  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_MsgRelease pICmpCAAMemBlockMan->IMBM_MsgRelease
	#define CHK_CmpCAAMemBlockManMBM_MsgRelease (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_MsgRelease  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_MsgRelease
	#define EXT_MBM_MsgRelease
	#define GET_MBM_MsgRelease(fl)  CAL_CMGETAPI( "MBM_MsgRelease" ) 
	#define CAL_MBM_MsgRelease pICmpCAAMemBlockMan->IMBM_MsgRelease
	#define CHK_MBM_MsgRelease (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_MsgRelease  CAL_CMEXPAPI( "MBM_MsgRelease" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_MsgRelease  PFMBM_MSGRELEASE pfMBM_MsgRelease;
	#define EXT_MBM_MsgRelease  extern PFMBM_MSGRELEASE pfMBM_MsgRelease;
	#define GET_MBM_MsgRelease(fl)  s_pfCMGetAPI2( "MBM_MsgRelease", (RTS_VOID_FCTPTR *)&pfMBM_MsgRelease, (fl), 0, 0)
	#define CAL_MBM_MsgRelease  pfMBM_MsgRelease
	#define CHK_MBM_MsgRelease  (pfMBM_MsgRelease != NULL)
	#define EXP_MBM_MsgRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgRelease", (RTS_UINTPTR)MBM_MsgRelease, 0, 0) 
#endif



CAA_ERROR CDECL MBM_MsgReleaseEx(CAA_HANDLE hMsg, CAA_HANDLE hXChg);
typedef CAA_ERROR (CDECL * PFMBM_MSGRELEASEEX) (CAA_HANDLE hMsg, CAA_HANDLE hXChg);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGRELEASEEX_NOTIMPLEMENTED)
	#define USE_MBM_MsgReleaseEx
	#define EXT_MBM_MsgReleaseEx
	#define GET_MBM_MsgReleaseEx(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_MsgReleaseEx(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_MsgReleaseEx  FALSE
	#define EXP_MBM_MsgReleaseEx  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_MsgReleaseEx
	#define EXT_MBM_MsgReleaseEx
	#define GET_MBM_MsgReleaseEx(fl)  CAL_CMGETAPI( "MBM_MsgReleaseEx" ) 
	#define CAL_MBM_MsgReleaseEx  MBM_MsgReleaseEx
	#define CHK_MBM_MsgReleaseEx  TRUE
	#define EXP_MBM_MsgReleaseEx  CAL_CMEXPAPI( "MBM_MsgReleaseEx" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_MsgReleaseEx
	#define EXT_MBM_MsgReleaseEx
	#define GET_MBM_MsgReleaseEx(fl)  CAL_CMGETAPI( "MBM_MsgReleaseEx" ) 
	#define CAL_MBM_MsgReleaseEx  MBM_MsgReleaseEx
	#define CHK_MBM_MsgReleaseEx  TRUE
	#define EXP_MBM_MsgReleaseEx  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgReleaseEx", (RTS_UINTPTR)MBM_MsgReleaseEx, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_MsgReleaseEx
	#define EXT_CmpCAAMemBlockManMBM_MsgReleaseEx
	#define GET_CmpCAAMemBlockManMBM_MsgReleaseEx  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_MsgReleaseEx pICmpCAAMemBlockMan->IMBM_MsgReleaseEx
	#define CHK_CmpCAAMemBlockManMBM_MsgReleaseEx (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_MsgReleaseEx  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_MsgReleaseEx
	#define EXT_MBM_MsgReleaseEx
	#define GET_MBM_MsgReleaseEx(fl)  CAL_CMGETAPI( "MBM_MsgReleaseEx" ) 
	#define CAL_MBM_MsgReleaseEx pICmpCAAMemBlockMan->IMBM_MsgReleaseEx
	#define CHK_MBM_MsgReleaseEx (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_MsgReleaseEx  CAL_CMEXPAPI( "MBM_MsgReleaseEx" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_MsgReleaseEx  PFMBM_MSGRELEASEEX pfMBM_MsgReleaseEx;
	#define EXT_MBM_MsgReleaseEx  extern PFMBM_MSGRELEASEEX pfMBM_MsgReleaseEx;
	#define GET_MBM_MsgReleaseEx(fl)  s_pfCMGetAPI2( "MBM_MsgReleaseEx", (RTS_VOID_FCTPTR *)&pfMBM_MsgReleaseEx, (fl), 0, 0)
	#define CAL_MBM_MsgReleaseEx  pfMBM_MsgReleaseEx
	#define CHK_MBM_MsgReleaseEx  (pfMBM_MsgReleaseEx != NULL)
	#define EXP_MBM_MsgReleaseEx  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgReleaseEx", (RTS_UINTPTR)MBM_MsgReleaseEx, 0, 0) 
#endif



CAA_HANDLE CDECL MBM_MsgClone(CAA_HANDLE hMsg, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_MSGCLONE) (CAA_HANDLE hMsg, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGCLONE_NOTIMPLEMENTED)
	#define USE_MBM_MsgClone
	#define EXT_MBM_MsgClone
	#define GET_MBM_MsgClone(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_MsgClone(p0,p1)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_MsgClone  FALSE
	#define EXP_MBM_MsgClone  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_MsgClone
	#define EXT_MBM_MsgClone
	#define GET_MBM_MsgClone(fl)  CAL_CMGETAPI( "MBM_MsgClone" ) 
	#define CAL_MBM_MsgClone  MBM_MsgClone
	#define CHK_MBM_MsgClone  TRUE
	#define EXP_MBM_MsgClone  CAL_CMEXPAPI( "MBM_MsgClone" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_MsgClone
	#define EXT_MBM_MsgClone
	#define GET_MBM_MsgClone(fl)  CAL_CMGETAPI( "MBM_MsgClone" ) 
	#define CAL_MBM_MsgClone  MBM_MsgClone
	#define CHK_MBM_MsgClone  TRUE
	#define EXP_MBM_MsgClone  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgClone", (RTS_UINTPTR)MBM_MsgClone, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_MsgClone
	#define EXT_CmpCAAMemBlockManMBM_MsgClone
	#define GET_CmpCAAMemBlockManMBM_MsgClone  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_MsgClone pICmpCAAMemBlockMan->IMBM_MsgClone
	#define CHK_CmpCAAMemBlockManMBM_MsgClone (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_MsgClone  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_MsgClone
	#define EXT_MBM_MsgClone
	#define GET_MBM_MsgClone(fl)  CAL_CMGETAPI( "MBM_MsgClone" ) 
	#define CAL_MBM_MsgClone pICmpCAAMemBlockMan->IMBM_MsgClone
	#define CHK_MBM_MsgClone (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_MsgClone  CAL_CMEXPAPI( "MBM_MsgClone" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_MsgClone  PFMBM_MSGCLONE pfMBM_MsgClone;
	#define EXT_MBM_MsgClone  extern PFMBM_MSGCLONE pfMBM_MsgClone;
	#define GET_MBM_MsgClone(fl)  s_pfCMGetAPI2( "MBM_MsgClone", (RTS_VOID_FCTPTR *)&pfMBM_MsgClone, (fl), 0, 0)
	#define CAL_MBM_MsgClone  pfMBM_MsgClone
	#define CHK_MBM_MsgClone  (pfMBM_MsgClone != NULL)
	#define EXP_MBM_MsgClone  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_MsgClone", (RTS_UINTPTR)MBM_MsgClone, 0, 0) 
#endif




/* Exchange Functions */
CAA_HANDLE CDECL MBM_XChgCreateH(CAA_COUNT ctNumMsg, CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios, CAA_ENUM eSendMsg, CAA_ENUM eReceiveMsg, CAA_ENUM eXChgEmpty, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_XCHGCREATEH) (CAA_COUNT ctNumMsg, CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios, CAA_ENUM eSendMsg, CAA_ENUM eReceiveMsg, CAA_ENUM eXChgEmpty, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGCREATEH_NOTIMPLEMENTED)
	#define USE_MBM_XChgCreateH
	#define EXT_MBM_XChgCreateH
	#define GET_MBM_XChgCreateH(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_XChgCreateH(p0,p1,p2,p3,p4,p5,p6)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_XChgCreateH  FALSE
	#define EXP_MBM_XChgCreateH  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_XChgCreateH
	#define EXT_MBM_XChgCreateH
	#define GET_MBM_XChgCreateH(fl)  CAL_CMGETAPI( "MBM_XChgCreateH" ) 
	#define CAL_MBM_XChgCreateH  MBM_XChgCreateH
	#define CHK_MBM_XChgCreateH  TRUE
	#define EXP_MBM_XChgCreateH  CAL_CMEXPAPI( "MBM_XChgCreateH" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_XChgCreateH
	#define EXT_MBM_XChgCreateH
	#define GET_MBM_XChgCreateH(fl)  CAL_CMGETAPI( "MBM_XChgCreateH" ) 
	#define CAL_MBM_XChgCreateH  MBM_XChgCreateH
	#define CHK_MBM_XChgCreateH  TRUE
	#define EXP_MBM_XChgCreateH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgCreateH", (RTS_UINTPTR)MBM_XChgCreateH, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_XChgCreateH
	#define EXT_CmpCAAMemBlockManMBM_XChgCreateH
	#define GET_CmpCAAMemBlockManMBM_XChgCreateH  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_XChgCreateH pICmpCAAMemBlockMan->IMBM_XChgCreateH
	#define CHK_CmpCAAMemBlockManMBM_XChgCreateH (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_XChgCreateH  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_XChgCreateH
	#define EXT_MBM_XChgCreateH
	#define GET_MBM_XChgCreateH(fl)  CAL_CMGETAPI( "MBM_XChgCreateH" ) 
	#define CAL_MBM_XChgCreateH pICmpCAAMemBlockMan->IMBM_XChgCreateH
	#define CHK_MBM_XChgCreateH (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_XChgCreateH  CAL_CMEXPAPI( "MBM_XChgCreateH" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_XChgCreateH  PFMBM_XCHGCREATEH pfMBM_XChgCreateH;
	#define EXT_MBM_XChgCreateH  extern PFMBM_XCHGCREATEH pfMBM_XChgCreateH;
	#define GET_MBM_XChgCreateH(fl)  s_pfCMGetAPI2( "MBM_XChgCreateH", (RTS_VOID_FCTPTR *)&pfMBM_XChgCreateH, (fl), 0, 0)
	#define CAL_MBM_XChgCreateH  pfMBM_XChgCreateH
	#define CHK_MBM_XChgCreateH  (pfMBM_XChgCreateH != NULL)
	#define EXP_MBM_XChgCreateH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgCreateH", (RTS_UINTPTR)MBM_XChgCreateH, 0, 0) 
#endif



CAA_HANDLE CDECL MBM_XChgCreateP(CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ENUM eSendMsg, CAA_ENUM eReceiveMsg, CAA_ENUM eXChgEmpty, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_XCHGCREATEP) (CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ENUM eSendMsg, CAA_ENUM eReceiveMsg, CAA_ENUM eXChgEmpty, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGCREATEP_NOTIMPLEMENTED)
	#define USE_MBM_XChgCreateP
	#define EXT_MBM_XChgCreateP
	#define GET_MBM_XChgCreateP(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_XChgCreateP(p0,p1,p2,p3,p4,p5,p6,p7)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_XChgCreateP  FALSE
	#define EXP_MBM_XChgCreateP  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_XChgCreateP
	#define EXT_MBM_XChgCreateP
	#define GET_MBM_XChgCreateP(fl)  CAL_CMGETAPI( "MBM_XChgCreateP" ) 
	#define CAL_MBM_XChgCreateP  MBM_XChgCreateP
	#define CHK_MBM_XChgCreateP  TRUE
	#define EXP_MBM_XChgCreateP  CAL_CMEXPAPI( "MBM_XChgCreateP" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_XChgCreateP
	#define EXT_MBM_XChgCreateP
	#define GET_MBM_XChgCreateP(fl)  CAL_CMGETAPI( "MBM_XChgCreateP" ) 
	#define CAL_MBM_XChgCreateP  MBM_XChgCreateP
	#define CHK_MBM_XChgCreateP  TRUE
	#define EXP_MBM_XChgCreateP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgCreateP", (RTS_UINTPTR)MBM_XChgCreateP, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_XChgCreateP
	#define EXT_CmpCAAMemBlockManMBM_XChgCreateP
	#define GET_CmpCAAMemBlockManMBM_XChgCreateP  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_XChgCreateP pICmpCAAMemBlockMan->IMBM_XChgCreateP
	#define CHK_CmpCAAMemBlockManMBM_XChgCreateP (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_XChgCreateP  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_XChgCreateP
	#define EXT_MBM_XChgCreateP
	#define GET_MBM_XChgCreateP(fl)  CAL_CMGETAPI( "MBM_XChgCreateP" ) 
	#define CAL_MBM_XChgCreateP pICmpCAAMemBlockMan->IMBM_XChgCreateP
	#define CHK_MBM_XChgCreateP (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_XChgCreateP  CAL_CMEXPAPI( "MBM_XChgCreateP" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_XChgCreateP  PFMBM_XCHGCREATEP pfMBM_XChgCreateP;
	#define EXT_MBM_XChgCreateP  extern PFMBM_XCHGCREATEP pfMBM_XChgCreateP;
	#define GET_MBM_XChgCreateP(fl)  s_pfCMGetAPI2( "MBM_XChgCreateP", (RTS_VOID_FCTPTR *)&pfMBM_XChgCreateP, (fl), 0, 0)
	#define CAL_MBM_XChgCreateP  pfMBM_XChgCreateP
	#define CHK_MBM_XChgCreateP  (pfMBM_XChgCreateP != NULL)
	#define EXP_MBM_XChgCreateP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgCreateP", (RTS_UINTPTR)MBM_XChgCreateP, 0, 0) 
#endif



CAA_ERROR CDECL MBM_XChgExtendH(CAA_HANDLE hXChg, CAA_COUNT ctNumBlocks);
typedef CAA_ERROR (CDECL * PFMBM_XCHGEXTENDH) (CAA_HANDLE hXChg, CAA_COUNT ctNumBlocks);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGEXTENDH_NOTIMPLEMENTED)
	#define USE_MBM_XChgExtendH
	#define EXT_MBM_XChgExtendH
	#define GET_MBM_XChgExtendH(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_XChgExtendH(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_XChgExtendH  FALSE
	#define EXP_MBM_XChgExtendH  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_XChgExtendH
	#define EXT_MBM_XChgExtendH
	#define GET_MBM_XChgExtendH(fl)  CAL_CMGETAPI( "MBM_XChgExtendH" ) 
	#define CAL_MBM_XChgExtendH  MBM_XChgExtendH
	#define CHK_MBM_XChgExtendH  TRUE
	#define EXP_MBM_XChgExtendH  CAL_CMEXPAPI( "MBM_XChgExtendH" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_XChgExtendH
	#define EXT_MBM_XChgExtendH
	#define GET_MBM_XChgExtendH(fl)  CAL_CMGETAPI( "MBM_XChgExtendH" ) 
	#define CAL_MBM_XChgExtendH  MBM_XChgExtendH
	#define CHK_MBM_XChgExtendH  TRUE
	#define EXP_MBM_XChgExtendH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgExtendH", (RTS_UINTPTR)MBM_XChgExtendH, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_XChgExtendH
	#define EXT_CmpCAAMemBlockManMBM_XChgExtendH
	#define GET_CmpCAAMemBlockManMBM_XChgExtendH  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_XChgExtendH pICmpCAAMemBlockMan->IMBM_XChgExtendH
	#define CHK_CmpCAAMemBlockManMBM_XChgExtendH (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_XChgExtendH  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_XChgExtendH
	#define EXT_MBM_XChgExtendH
	#define GET_MBM_XChgExtendH(fl)  CAL_CMGETAPI( "MBM_XChgExtendH" ) 
	#define CAL_MBM_XChgExtendH pICmpCAAMemBlockMan->IMBM_XChgExtendH
	#define CHK_MBM_XChgExtendH (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_XChgExtendH  CAL_CMEXPAPI( "MBM_XChgExtendH" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_XChgExtendH  PFMBM_XCHGEXTENDH pfMBM_XChgExtendH;
	#define EXT_MBM_XChgExtendH  extern PFMBM_XCHGEXTENDH pfMBM_XChgExtendH;
	#define GET_MBM_XChgExtendH(fl)  s_pfCMGetAPI2( "MBM_XChgExtendH", (RTS_VOID_FCTPTR *)&pfMBM_XChgExtendH, (fl), 0, 0)
	#define CAL_MBM_XChgExtendH  pfMBM_XChgExtendH
	#define CHK_MBM_XChgExtendH  (pfMBM_XChgExtendH != NULL)
	#define EXP_MBM_XChgExtendH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgExtendH", (RTS_UINTPTR)MBM_XChgExtendH, 0, 0) 
#endif



CAA_ERROR CDECL MBM_XChgDelete(CAA_HANDLE hXChg);
typedef CAA_ERROR (CDECL * PFMBM_XCHGDELETE) (CAA_HANDLE hXChg);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGDELETE_NOTIMPLEMENTED)
	#define USE_MBM_XChgDelete
	#define EXT_MBM_XChgDelete
	#define GET_MBM_XChgDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_XChgDelete(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_XChgDelete  FALSE
	#define EXP_MBM_XChgDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_XChgDelete
	#define EXT_MBM_XChgDelete
	#define GET_MBM_XChgDelete(fl)  CAL_CMGETAPI( "MBM_XChgDelete" ) 
	#define CAL_MBM_XChgDelete  MBM_XChgDelete
	#define CHK_MBM_XChgDelete  TRUE
	#define EXP_MBM_XChgDelete  CAL_CMEXPAPI( "MBM_XChgDelete" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_XChgDelete
	#define EXT_MBM_XChgDelete
	#define GET_MBM_XChgDelete(fl)  CAL_CMGETAPI( "MBM_XChgDelete" ) 
	#define CAL_MBM_XChgDelete  MBM_XChgDelete
	#define CHK_MBM_XChgDelete  TRUE
	#define EXP_MBM_XChgDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgDelete", (RTS_UINTPTR)MBM_XChgDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_XChgDelete
	#define EXT_CmpCAAMemBlockManMBM_XChgDelete
	#define GET_CmpCAAMemBlockManMBM_XChgDelete  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_XChgDelete pICmpCAAMemBlockMan->IMBM_XChgDelete
	#define CHK_CmpCAAMemBlockManMBM_XChgDelete (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_XChgDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_XChgDelete
	#define EXT_MBM_XChgDelete
	#define GET_MBM_XChgDelete(fl)  CAL_CMGETAPI( "MBM_XChgDelete" ) 
	#define CAL_MBM_XChgDelete pICmpCAAMemBlockMan->IMBM_XChgDelete
	#define CHK_MBM_XChgDelete (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_XChgDelete  CAL_CMEXPAPI( "MBM_XChgDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_XChgDelete  PFMBM_XCHGDELETE pfMBM_XChgDelete;
	#define EXT_MBM_XChgDelete  extern PFMBM_XCHGDELETE pfMBM_XChgDelete;
	#define GET_MBM_XChgDelete(fl)  s_pfCMGetAPI2( "MBM_XChgDelete", (RTS_VOID_FCTPTR *)&pfMBM_XChgDelete, (fl), 0, 0)
	#define CAL_MBM_XChgDelete  pfMBM_XChgDelete
	#define CHK_MBM_XChgDelete  (pfMBM_XChgDelete != NULL)
	#define EXP_MBM_XChgDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgDelete", (RTS_UINTPTR)MBM_XChgDelete, 0, 0) 
#endif



CAA_ERROR CDECL MBM_XChgDelete2(CAA_HANDLE hXChg, CAA_BOOL xForce);
typedef CAA_ERROR (CDECL * PFMBM_XCHGDELETE2) (CAA_HANDLE hXChg, CAA_BOOL xForce);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGDELETE2_NOTIMPLEMENTED)
	#define USE_MBM_XChgDelete2
	#define EXT_MBM_XChgDelete2
	#define GET_MBM_XChgDelete2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_XChgDelete2(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_XChgDelete2  FALSE
	#define EXP_MBM_XChgDelete2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_XChgDelete2
	#define EXT_MBM_XChgDelete2
	#define GET_MBM_XChgDelete2(fl)  CAL_CMGETAPI( "MBM_XChgDelete2" ) 
	#define CAL_MBM_XChgDelete2  MBM_XChgDelete2
	#define CHK_MBM_XChgDelete2  TRUE
	#define EXP_MBM_XChgDelete2  CAL_CMEXPAPI( "MBM_XChgDelete2" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_XChgDelete2
	#define EXT_MBM_XChgDelete2
	#define GET_MBM_XChgDelete2(fl)  CAL_CMGETAPI( "MBM_XChgDelete2" ) 
	#define CAL_MBM_XChgDelete2  MBM_XChgDelete2
	#define CHK_MBM_XChgDelete2  TRUE
	#define EXP_MBM_XChgDelete2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgDelete2", (RTS_UINTPTR)MBM_XChgDelete2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_XChgDelete2
	#define EXT_CmpCAAMemBlockManMBM_XChgDelete2
	#define GET_CmpCAAMemBlockManMBM_XChgDelete2  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_XChgDelete2 pICmpCAAMemBlockMan->IMBM_XChgDelete2
	#define CHK_CmpCAAMemBlockManMBM_XChgDelete2 (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_XChgDelete2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_XChgDelete2
	#define EXT_MBM_XChgDelete2
	#define GET_MBM_XChgDelete2(fl)  CAL_CMGETAPI( "MBM_XChgDelete2" ) 
	#define CAL_MBM_XChgDelete2 pICmpCAAMemBlockMan->IMBM_XChgDelete2
	#define CHK_MBM_XChgDelete2 (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_XChgDelete2  CAL_CMEXPAPI( "MBM_XChgDelete2" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_XChgDelete2  PFMBM_XCHGDELETE2 pfMBM_XChgDelete2;
	#define EXT_MBM_XChgDelete2  extern PFMBM_XCHGDELETE2 pfMBM_XChgDelete2;
	#define GET_MBM_XChgDelete2(fl)  s_pfCMGetAPI2( "MBM_XChgDelete2", (RTS_VOID_FCTPTR *)&pfMBM_XChgDelete2, (fl), 0, 0)
	#define CAL_MBM_XChgDelete2  pfMBM_XChgDelete2
	#define CHK_MBM_XChgDelete2  (pfMBM_XChgDelete2 != NULL)
	#define EXP_MBM_XChgDelete2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgDelete2", (RTS_UINTPTR)MBM_XChgDelete2, 0, 0) 
#endif



CAA_SIZE CDECL MBM_XChgGetSize(CAA_COUNT ctNumMsg, CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios);
typedef CAA_SIZE (CDECL * PFMBM_XCHGGETSIZE) (CAA_COUNT ctNumMsg, CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGGETSIZE_NOTIMPLEMENTED)
	#define USE_MBM_XChgGetSize
	#define EXT_MBM_XChgGetSize
	#define GET_MBM_XChgGetSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_XChgGetSize(p0,p1,p2)  (CAA_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_XChgGetSize  FALSE
	#define EXP_MBM_XChgGetSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_XChgGetSize
	#define EXT_MBM_XChgGetSize
	#define GET_MBM_XChgGetSize(fl)  CAL_CMGETAPI( "MBM_XChgGetSize" ) 
	#define CAL_MBM_XChgGetSize  MBM_XChgGetSize
	#define CHK_MBM_XChgGetSize  TRUE
	#define EXP_MBM_XChgGetSize  CAL_CMEXPAPI( "MBM_XChgGetSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_XChgGetSize
	#define EXT_MBM_XChgGetSize
	#define GET_MBM_XChgGetSize(fl)  CAL_CMGETAPI( "MBM_XChgGetSize" ) 
	#define CAL_MBM_XChgGetSize  MBM_XChgGetSize
	#define CHK_MBM_XChgGetSize  TRUE
	#define EXP_MBM_XChgGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgGetSize", (RTS_UINTPTR)MBM_XChgGetSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_XChgGetSize
	#define EXT_CmpCAAMemBlockManMBM_XChgGetSize
	#define GET_CmpCAAMemBlockManMBM_XChgGetSize  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_XChgGetSize pICmpCAAMemBlockMan->IMBM_XChgGetSize
	#define CHK_CmpCAAMemBlockManMBM_XChgGetSize (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_XChgGetSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_XChgGetSize
	#define EXT_MBM_XChgGetSize
	#define GET_MBM_XChgGetSize(fl)  CAL_CMGETAPI( "MBM_XChgGetSize" ) 
	#define CAL_MBM_XChgGetSize pICmpCAAMemBlockMan->IMBM_XChgGetSize
	#define CHK_MBM_XChgGetSize (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_XChgGetSize  CAL_CMEXPAPI( "MBM_XChgGetSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_XChgGetSize  PFMBM_XCHGGETSIZE pfMBM_XChgGetSize;
	#define EXT_MBM_XChgGetSize  extern PFMBM_XCHGGETSIZE pfMBM_XChgGetSize;
	#define GET_MBM_XChgGetSize(fl)  s_pfCMGetAPI2( "MBM_XChgGetSize", (RTS_VOID_FCTPTR *)&pfMBM_XChgGetSize, (fl), 0, 0)
	#define CAL_MBM_XChgGetSize  pfMBM_XChgGetSize
	#define CHK_MBM_XChgGetSize  (pfMBM_XChgGetSize != NULL)
	#define EXP_MBM_XChgGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgGetSize", (RTS_UINTPTR)MBM_XChgGetSize, 0, 0) 
#endif



CAA_BOOL CDECL MBM_XChgIsEmpty(CAA_HANDLE hXChg, CAA_ERROR* peError);
typedef CAA_BOOL (CDECL * PFMBM_XCHGISEMPTY) (CAA_HANDLE hXChg, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGISEMPTY_NOTIMPLEMENTED)
	#define USE_MBM_XChgIsEmpty
	#define EXT_MBM_XChgIsEmpty
	#define GET_MBM_XChgIsEmpty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_XChgIsEmpty(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_MBM_XChgIsEmpty  FALSE
	#define EXP_MBM_XChgIsEmpty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_XChgIsEmpty
	#define EXT_MBM_XChgIsEmpty
	#define GET_MBM_XChgIsEmpty(fl)  CAL_CMGETAPI( "MBM_XChgIsEmpty" ) 
	#define CAL_MBM_XChgIsEmpty  MBM_XChgIsEmpty
	#define CHK_MBM_XChgIsEmpty  TRUE
	#define EXP_MBM_XChgIsEmpty  CAL_CMEXPAPI( "MBM_XChgIsEmpty" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_XChgIsEmpty
	#define EXT_MBM_XChgIsEmpty
	#define GET_MBM_XChgIsEmpty(fl)  CAL_CMGETAPI( "MBM_XChgIsEmpty" ) 
	#define CAL_MBM_XChgIsEmpty  MBM_XChgIsEmpty
	#define CHK_MBM_XChgIsEmpty  TRUE
	#define EXP_MBM_XChgIsEmpty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgIsEmpty", (RTS_UINTPTR)MBM_XChgIsEmpty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_XChgIsEmpty
	#define EXT_CmpCAAMemBlockManMBM_XChgIsEmpty
	#define GET_CmpCAAMemBlockManMBM_XChgIsEmpty  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_XChgIsEmpty pICmpCAAMemBlockMan->IMBM_XChgIsEmpty
	#define CHK_CmpCAAMemBlockManMBM_XChgIsEmpty (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_XChgIsEmpty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_XChgIsEmpty
	#define EXT_MBM_XChgIsEmpty
	#define GET_MBM_XChgIsEmpty(fl)  CAL_CMGETAPI( "MBM_XChgIsEmpty" ) 
	#define CAL_MBM_XChgIsEmpty pICmpCAAMemBlockMan->IMBM_XChgIsEmpty
	#define CHK_MBM_XChgIsEmpty (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_XChgIsEmpty  CAL_CMEXPAPI( "MBM_XChgIsEmpty" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_XChgIsEmpty  PFMBM_XCHGISEMPTY pfMBM_XChgIsEmpty;
	#define EXT_MBM_XChgIsEmpty  extern PFMBM_XCHGISEMPTY pfMBM_XChgIsEmpty;
	#define GET_MBM_XChgIsEmpty(fl)  s_pfCMGetAPI2( "MBM_XChgIsEmpty", (RTS_VOID_FCTPTR *)&pfMBM_XChgIsEmpty, (fl), 0, 0)
	#define CAL_MBM_XChgIsEmpty  pfMBM_XChgIsEmpty
	#define CHK_MBM_XChgIsEmpty  (pfMBM_XChgIsEmpty != NULL)
	#define EXP_MBM_XChgIsEmpty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgIsEmpty", (RTS_UINTPTR)MBM_XChgIsEmpty, 0, 0) 
#endif



CAA_COUNT CDECL MBM_XChgMsgLeft(CAA_HANDLE hXChg, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFMBM_XCHGMSGLEFT) (CAA_HANDLE hXChg, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGMSGLEFT_NOTIMPLEMENTED)
	#define USE_MBM_XChgMsgLeft
	#define EXT_MBM_XChgMsgLeft
	#define GET_MBM_XChgMsgLeft(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_XChgMsgLeft(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_MBM_XChgMsgLeft  FALSE
	#define EXP_MBM_XChgMsgLeft  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_XChgMsgLeft
	#define EXT_MBM_XChgMsgLeft
	#define GET_MBM_XChgMsgLeft(fl)  CAL_CMGETAPI( "MBM_XChgMsgLeft" ) 
	#define CAL_MBM_XChgMsgLeft  MBM_XChgMsgLeft
	#define CHK_MBM_XChgMsgLeft  TRUE
	#define EXP_MBM_XChgMsgLeft  CAL_CMEXPAPI( "MBM_XChgMsgLeft" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_XChgMsgLeft
	#define EXT_MBM_XChgMsgLeft
	#define GET_MBM_XChgMsgLeft(fl)  CAL_CMGETAPI( "MBM_XChgMsgLeft" ) 
	#define CAL_MBM_XChgMsgLeft  MBM_XChgMsgLeft
	#define CHK_MBM_XChgMsgLeft  TRUE
	#define EXP_MBM_XChgMsgLeft  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgMsgLeft", (RTS_UINTPTR)MBM_XChgMsgLeft, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_XChgMsgLeft
	#define EXT_CmpCAAMemBlockManMBM_XChgMsgLeft
	#define GET_CmpCAAMemBlockManMBM_XChgMsgLeft  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_XChgMsgLeft pICmpCAAMemBlockMan->IMBM_XChgMsgLeft
	#define CHK_CmpCAAMemBlockManMBM_XChgMsgLeft (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_XChgMsgLeft  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_XChgMsgLeft
	#define EXT_MBM_XChgMsgLeft
	#define GET_MBM_XChgMsgLeft(fl)  CAL_CMGETAPI( "MBM_XChgMsgLeft" ) 
	#define CAL_MBM_XChgMsgLeft pICmpCAAMemBlockMan->IMBM_XChgMsgLeft
	#define CHK_MBM_XChgMsgLeft (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_XChgMsgLeft  CAL_CMEXPAPI( "MBM_XChgMsgLeft" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_XChgMsgLeft  PFMBM_XCHGMSGLEFT pfMBM_XChgMsgLeft;
	#define EXT_MBM_XChgMsgLeft  extern PFMBM_XCHGMSGLEFT pfMBM_XChgMsgLeft;
	#define GET_MBM_XChgMsgLeft(fl)  s_pfCMGetAPI2( "MBM_XChgMsgLeft", (RTS_VOID_FCTPTR *)&pfMBM_XChgMsgLeft, (fl), 0, 0)
	#define CAL_MBM_XChgMsgLeft  pfMBM_XChgMsgLeft
	#define CHK_MBM_XChgMsgLeft  (pfMBM_XChgMsgLeft != NULL)
	#define EXP_MBM_XChgMsgLeft  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_XChgMsgLeft", (RTS_UINTPTR)MBM_XChgMsgLeft, 0, 0) 
#endif




/* Flat Functions */
CAA_HANDLE CDECL MBM_FlatCreateH(CAA_IDENT idMinKey, CAA_IDENT idMaxKey, CAA_COUNT ctNumKeys, CAA_ENUM eEnable, CAA_ENUM eDisable, CAA_ENUM eUpdate, CAA_ENUM eRead, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_FLATCREATEH) (CAA_IDENT idMinKey, CAA_IDENT idMaxKey, CAA_COUNT ctNumKeys, CAA_ENUM eEnable, CAA_ENUM eDisable, CAA_ENUM eUpdate, CAA_ENUM eRead, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATCREATEH_NOTIMPLEMENTED)
	#define USE_MBM_FlatCreateH
	#define EXT_MBM_FlatCreateH
	#define GET_MBM_FlatCreateH(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_FlatCreateH(p0,p1,p2,p3,p4,p5,p6,p7)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_FlatCreateH  FALSE
	#define EXP_MBM_FlatCreateH  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_FlatCreateH
	#define EXT_MBM_FlatCreateH
	#define GET_MBM_FlatCreateH(fl)  CAL_CMGETAPI( "MBM_FlatCreateH" ) 
	#define CAL_MBM_FlatCreateH  MBM_FlatCreateH
	#define CHK_MBM_FlatCreateH  TRUE
	#define EXP_MBM_FlatCreateH  CAL_CMEXPAPI( "MBM_FlatCreateH" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_FlatCreateH
	#define EXT_MBM_FlatCreateH
	#define GET_MBM_FlatCreateH(fl)  CAL_CMGETAPI( "MBM_FlatCreateH" ) 
	#define CAL_MBM_FlatCreateH  MBM_FlatCreateH
	#define CHK_MBM_FlatCreateH  TRUE
	#define EXP_MBM_FlatCreateH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatCreateH", (RTS_UINTPTR)MBM_FlatCreateH, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_FlatCreateH
	#define EXT_CmpCAAMemBlockManMBM_FlatCreateH
	#define GET_CmpCAAMemBlockManMBM_FlatCreateH  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_FlatCreateH pICmpCAAMemBlockMan->IMBM_FlatCreateH
	#define CHK_CmpCAAMemBlockManMBM_FlatCreateH (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_FlatCreateH  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_FlatCreateH
	#define EXT_MBM_FlatCreateH
	#define GET_MBM_FlatCreateH(fl)  CAL_CMGETAPI( "MBM_FlatCreateH" ) 
	#define CAL_MBM_FlatCreateH pICmpCAAMemBlockMan->IMBM_FlatCreateH
	#define CHK_MBM_FlatCreateH (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_FlatCreateH  CAL_CMEXPAPI( "MBM_FlatCreateH" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_FlatCreateH  PFMBM_FLATCREATEH pfMBM_FlatCreateH;
	#define EXT_MBM_FlatCreateH  extern PFMBM_FLATCREATEH pfMBM_FlatCreateH;
	#define GET_MBM_FlatCreateH(fl)  s_pfCMGetAPI2( "MBM_FlatCreateH", (RTS_VOID_FCTPTR *)&pfMBM_FlatCreateH, (fl), 0, 0)
	#define CAL_MBM_FlatCreateH  pfMBM_FlatCreateH
	#define CHK_MBM_FlatCreateH  (pfMBM_FlatCreateH != NULL)
	#define EXP_MBM_FlatCreateH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatCreateH", (RTS_UINTPTR)MBM_FlatCreateH, 0, 0) 
#endif



CAA_HANDLE CDECL MBM_FlatCreateP(CAA_IDENT idMinKey, CAA_IDENT idMaxKey, CAA_COUNT ctNumKeys, CAA_SIZE szMemory, CAA_PVOID pMemory, CAA_ENUM eEnable, CAA_ENUM eDisable, CAA_ENUM eUpdate, CAA_ENUM eRead, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_FLATCREATEP) (CAA_IDENT idMinKey, CAA_IDENT idMaxKey, CAA_COUNT ctNumKeys, CAA_SIZE szMemory, CAA_PVOID pMemory, CAA_ENUM eEnable, CAA_ENUM eDisable, CAA_ENUM eUpdate, CAA_ENUM eRead, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATCREATEP_NOTIMPLEMENTED)
	#define USE_MBM_FlatCreateP
	#define EXT_MBM_FlatCreateP
	#define GET_MBM_FlatCreateP(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_FlatCreateP(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_FlatCreateP  FALSE
	#define EXP_MBM_FlatCreateP  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_FlatCreateP
	#define EXT_MBM_FlatCreateP
	#define GET_MBM_FlatCreateP(fl)  CAL_CMGETAPI( "MBM_FlatCreateP" ) 
	#define CAL_MBM_FlatCreateP  MBM_FlatCreateP
	#define CHK_MBM_FlatCreateP  TRUE
	#define EXP_MBM_FlatCreateP  CAL_CMEXPAPI( "MBM_FlatCreateP" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_FlatCreateP
	#define EXT_MBM_FlatCreateP
	#define GET_MBM_FlatCreateP(fl)  CAL_CMGETAPI( "MBM_FlatCreateP" ) 
	#define CAL_MBM_FlatCreateP  MBM_FlatCreateP
	#define CHK_MBM_FlatCreateP  TRUE
	#define EXP_MBM_FlatCreateP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatCreateP", (RTS_UINTPTR)MBM_FlatCreateP, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_FlatCreateP
	#define EXT_CmpCAAMemBlockManMBM_FlatCreateP
	#define GET_CmpCAAMemBlockManMBM_FlatCreateP  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_FlatCreateP pICmpCAAMemBlockMan->IMBM_FlatCreateP
	#define CHK_CmpCAAMemBlockManMBM_FlatCreateP (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_FlatCreateP  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_FlatCreateP
	#define EXT_MBM_FlatCreateP
	#define GET_MBM_FlatCreateP(fl)  CAL_CMGETAPI( "MBM_FlatCreateP" ) 
	#define CAL_MBM_FlatCreateP pICmpCAAMemBlockMan->IMBM_FlatCreateP
	#define CHK_MBM_FlatCreateP (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_FlatCreateP  CAL_CMEXPAPI( "MBM_FlatCreateP" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_FlatCreateP  PFMBM_FLATCREATEP pfMBM_FlatCreateP;
	#define EXT_MBM_FlatCreateP  extern PFMBM_FLATCREATEP pfMBM_FlatCreateP;
	#define GET_MBM_FlatCreateP(fl)  s_pfCMGetAPI2( "MBM_FlatCreateP", (RTS_VOID_FCTPTR *)&pfMBM_FlatCreateP, (fl), 0, 0)
	#define CAL_MBM_FlatCreateP  pfMBM_FlatCreateP
	#define CHK_MBM_FlatCreateP  (pfMBM_FlatCreateP != NULL)
	#define EXP_MBM_FlatCreateP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatCreateP", (RTS_UINTPTR)MBM_FlatCreateP, 0, 0) 
#endif



CAA_ERROR CDECL MBM_FlatEnable(CAA_HANDLE hFlat, CAA_IDENT idKey);
typedef CAA_ERROR (CDECL * PFMBM_FLATENABLE) (CAA_HANDLE hFlat, CAA_IDENT idKey);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATENABLE_NOTIMPLEMENTED)
	#define USE_MBM_FlatEnable
	#define EXT_MBM_FlatEnable
	#define GET_MBM_FlatEnable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_FlatEnable(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_FlatEnable  FALSE
	#define EXP_MBM_FlatEnable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_FlatEnable
	#define EXT_MBM_FlatEnable
	#define GET_MBM_FlatEnable(fl)  CAL_CMGETAPI( "MBM_FlatEnable" ) 
	#define CAL_MBM_FlatEnable  MBM_FlatEnable
	#define CHK_MBM_FlatEnable  TRUE
	#define EXP_MBM_FlatEnable  CAL_CMEXPAPI( "MBM_FlatEnable" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_FlatEnable
	#define EXT_MBM_FlatEnable
	#define GET_MBM_FlatEnable(fl)  CAL_CMGETAPI( "MBM_FlatEnable" ) 
	#define CAL_MBM_FlatEnable  MBM_FlatEnable
	#define CHK_MBM_FlatEnable  TRUE
	#define EXP_MBM_FlatEnable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatEnable", (RTS_UINTPTR)MBM_FlatEnable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_FlatEnable
	#define EXT_CmpCAAMemBlockManMBM_FlatEnable
	#define GET_CmpCAAMemBlockManMBM_FlatEnable  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_FlatEnable pICmpCAAMemBlockMan->IMBM_FlatEnable
	#define CHK_CmpCAAMemBlockManMBM_FlatEnable (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_FlatEnable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_FlatEnable
	#define EXT_MBM_FlatEnable
	#define GET_MBM_FlatEnable(fl)  CAL_CMGETAPI( "MBM_FlatEnable" ) 
	#define CAL_MBM_FlatEnable pICmpCAAMemBlockMan->IMBM_FlatEnable
	#define CHK_MBM_FlatEnable (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_FlatEnable  CAL_CMEXPAPI( "MBM_FlatEnable" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_FlatEnable  PFMBM_FLATENABLE pfMBM_FlatEnable;
	#define EXT_MBM_FlatEnable  extern PFMBM_FLATENABLE pfMBM_FlatEnable;
	#define GET_MBM_FlatEnable(fl)  s_pfCMGetAPI2( "MBM_FlatEnable", (RTS_VOID_FCTPTR *)&pfMBM_FlatEnable, (fl), 0, 0)
	#define CAL_MBM_FlatEnable  pfMBM_FlatEnable
	#define CHK_MBM_FlatEnable  (pfMBM_FlatEnable != NULL)
	#define EXP_MBM_FlatEnable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatEnable", (RTS_UINTPTR)MBM_FlatEnable, 0, 0) 
#endif



CAA_HANDLE CDECL MBM_FlatDisable(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_FLATDISABLE) (CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATDISABLE_NOTIMPLEMENTED)
	#define USE_MBM_FlatDisable
	#define EXT_MBM_FlatDisable
	#define GET_MBM_FlatDisable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_FlatDisable(p0,p1,p2)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_FlatDisable  FALSE
	#define EXP_MBM_FlatDisable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_FlatDisable
	#define EXT_MBM_FlatDisable
	#define GET_MBM_FlatDisable(fl)  CAL_CMGETAPI( "MBM_FlatDisable" ) 
	#define CAL_MBM_FlatDisable  MBM_FlatDisable
	#define CHK_MBM_FlatDisable  TRUE
	#define EXP_MBM_FlatDisable  CAL_CMEXPAPI( "MBM_FlatDisable" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_FlatDisable
	#define EXT_MBM_FlatDisable
	#define GET_MBM_FlatDisable(fl)  CAL_CMGETAPI( "MBM_FlatDisable" ) 
	#define CAL_MBM_FlatDisable  MBM_FlatDisable
	#define CHK_MBM_FlatDisable  TRUE
	#define EXP_MBM_FlatDisable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatDisable", (RTS_UINTPTR)MBM_FlatDisable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_FlatDisable
	#define EXT_CmpCAAMemBlockManMBM_FlatDisable
	#define GET_CmpCAAMemBlockManMBM_FlatDisable  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_FlatDisable pICmpCAAMemBlockMan->IMBM_FlatDisable
	#define CHK_CmpCAAMemBlockManMBM_FlatDisable (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_FlatDisable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_FlatDisable
	#define EXT_MBM_FlatDisable
	#define GET_MBM_FlatDisable(fl)  CAL_CMGETAPI( "MBM_FlatDisable" ) 
	#define CAL_MBM_FlatDisable pICmpCAAMemBlockMan->IMBM_FlatDisable
	#define CHK_MBM_FlatDisable (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_FlatDisable  CAL_CMEXPAPI( "MBM_FlatDisable" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_FlatDisable  PFMBM_FLATDISABLE pfMBM_FlatDisable;
	#define EXT_MBM_FlatDisable  extern PFMBM_FLATDISABLE pfMBM_FlatDisable;
	#define GET_MBM_FlatDisable(fl)  s_pfCMGetAPI2( "MBM_FlatDisable", (RTS_VOID_FCTPTR *)&pfMBM_FlatDisable, (fl), 0, 0)
	#define CAL_MBM_FlatDisable  pfMBM_FlatDisable
	#define CHK_MBM_FlatDisable  (pfMBM_FlatDisable != NULL)
	#define EXP_MBM_FlatDisable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatDisable", (RTS_UINTPTR)MBM_FlatDisable, 0, 0) 
#endif



CAA_BOOL CDECL MBM_FlatTest(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError);
typedef CAA_BOOL (CDECL * PFMBM_FLATTEST) (CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATTEST_NOTIMPLEMENTED)
	#define USE_MBM_FlatTest
	#define EXT_MBM_FlatTest
	#define GET_MBM_FlatTest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_FlatTest(p0,p1,p2)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_MBM_FlatTest  FALSE
	#define EXP_MBM_FlatTest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_FlatTest
	#define EXT_MBM_FlatTest
	#define GET_MBM_FlatTest(fl)  CAL_CMGETAPI( "MBM_FlatTest" ) 
	#define CAL_MBM_FlatTest  MBM_FlatTest
	#define CHK_MBM_FlatTest  TRUE
	#define EXP_MBM_FlatTest  CAL_CMEXPAPI( "MBM_FlatTest" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_FlatTest
	#define EXT_MBM_FlatTest
	#define GET_MBM_FlatTest(fl)  CAL_CMGETAPI( "MBM_FlatTest" ) 
	#define CAL_MBM_FlatTest  MBM_FlatTest
	#define CHK_MBM_FlatTest  TRUE
	#define EXP_MBM_FlatTest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatTest", (RTS_UINTPTR)MBM_FlatTest, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_FlatTest
	#define EXT_CmpCAAMemBlockManMBM_FlatTest
	#define GET_CmpCAAMemBlockManMBM_FlatTest  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_FlatTest pICmpCAAMemBlockMan->IMBM_FlatTest
	#define CHK_CmpCAAMemBlockManMBM_FlatTest (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_FlatTest  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_FlatTest
	#define EXT_MBM_FlatTest
	#define GET_MBM_FlatTest(fl)  CAL_CMGETAPI( "MBM_FlatTest" ) 
	#define CAL_MBM_FlatTest pICmpCAAMemBlockMan->IMBM_FlatTest
	#define CHK_MBM_FlatTest (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_FlatTest  CAL_CMEXPAPI( "MBM_FlatTest" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_FlatTest  PFMBM_FLATTEST pfMBM_FlatTest;
	#define EXT_MBM_FlatTest  extern PFMBM_FLATTEST pfMBM_FlatTest;
	#define GET_MBM_FlatTest(fl)  s_pfCMGetAPI2( "MBM_FlatTest", (RTS_VOID_FCTPTR *)&pfMBM_FlatTest, (fl), 0, 0)
	#define CAL_MBM_FlatTest  pfMBM_FlatTest
	#define CHK_MBM_FlatTest  (pfMBM_FlatTest != NULL)
	#define EXP_MBM_FlatTest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatTest", (RTS_UINTPTR)MBM_FlatTest, 0, 0) 
#endif



CAA_HANDLE CDECL MBM_FlatUpdate(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_HANDLE hMsg, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_FLATUPDATE) (CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_HANDLE hMsg, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATUPDATE_NOTIMPLEMENTED)
	#define USE_MBM_FlatUpdate
	#define EXT_MBM_FlatUpdate
	#define GET_MBM_FlatUpdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_FlatUpdate(p0,p1,p2,p3)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_FlatUpdate  FALSE
	#define EXP_MBM_FlatUpdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_FlatUpdate
	#define EXT_MBM_FlatUpdate
	#define GET_MBM_FlatUpdate(fl)  CAL_CMGETAPI( "MBM_FlatUpdate" ) 
	#define CAL_MBM_FlatUpdate  MBM_FlatUpdate
	#define CHK_MBM_FlatUpdate  TRUE
	#define EXP_MBM_FlatUpdate  CAL_CMEXPAPI( "MBM_FlatUpdate" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_FlatUpdate
	#define EXT_MBM_FlatUpdate
	#define GET_MBM_FlatUpdate(fl)  CAL_CMGETAPI( "MBM_FlatUpdate" ) 
	#define CAL_MBM_FlatUpdate  MBM_FlatUpdate
	#define CHK_MBM_FlatUpdate  TRUE
	#define EXP_MBM_FlatUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatUpdate", (RTS_UINTPTR)MBM_FlatUpdate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_FlatUpdate
	#define EXT_CmpCAAMemBlockManMBM_FlatUpdate
	#define GET_CmpCAAMemBlockManMBM_FlatUpdate  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_FlatUpdate pICmpCAAMemBlockMan->IMBM_FlatUpdate
	#define CHK_CmpCAAMemBlockManMBM_FlatUpdate (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_FlatUpdate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_FlatUpdate
	#define EXT_MBM_FlatUpdate
	#define GET_MBM_FlatUpdate(fl)  CAL_CMGETAPI( "MBM_FlatUpdate" ) 
	#define CAL_MBM_FlatUpdate pICmpCAAMemBlockMan->IMBM_FlatUpdate
	#define CHK_MBM_FlatUpdate (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_FlatUpdate  CAL_CMEXPAPI( "MBM_FlatUpdate" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_FlatUpdate  PFMBM_FLATUPDATE pfMBM_FlatUpdate;
	#define EXT_MBM_FlatUpdate  extern PFMBM_FLATUPDATE pfMBM_FlatUpdate;
	#define GET_MBM_FlatUpdate(fl)  s_pfCMGetAPI2( "MBM_FlatUpdate", (RTS_VOID_FCTPTR *)&pfMBM_FlatUpdate, (fl), 0, 0)
	#define CAL_MBM_FlatUpdate  pfMBM_FlatUpdate
	#define CHK_MBM_FlatUpdate  (pfMBM_FlatUpdate != NULL)
	#define EXP_MBM_FlatUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatUpdate", (RTS_UINTPTR)MBM_FlatUpdate, 0, 0) 
#endif



CAA_HANDLE CDECL MBM_FlatRead(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_FLATREAD) (CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATREAD_NOTIMPLEMENTED)
	#define USE_MBM_FlatRead
	#define EXT_MBM_FlatRead
	#define GET_MBM_FlatRead(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_FlatRead(p0,p1,p2)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_FlatRead  FALSE
	#define EXP_MBM_FlatRead  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_FlatRead
	#define EXT_MBM_FlatRead
	#define GET_MBM_FlatRead(fl)  CAL_CMGETAPI( "MBM_FlatRead" ) 
	#define CAL_MBM_FlatRead  MBM_FlatRead
	#define CHK_MBM_FlatRead  TRUE
	#define EXP_MBM_FlatRead  CAL_CMEXPAPI( "MBM_FlatRead" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_FlatRead
	#define EXT_MBM_FlatRead
	#define GET_MBM_FlatRead(fl)  CAL_CMGETAPI( "MBM_FlatRead" ) 
	#define CAL_MBM_FlatRead  MBM_FlatRead
	#define CHK_MBM_FlatRead  TRUE
	#define EXP_MBM_FlatRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatRead", (RTS_UINTPTR)MBM_FlatRead, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_FlatRead
	#define EXT_CmpCAAMemBlockManMBM_FlatRead
	#define GET_CmpCAAMemBlockManMBM_FlatRead  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_FlatRead pICmpCAAMemBlockMan->IMBM_FlatRead
	#define CHK_CmpCAAMemBlockManMBM_FlatRead (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_FlatRead  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_FlatRead
	#define EXT_MBM_FlatRead
	#define GET_MBM_FlatRead(fl)  CAL_CMGETAPI( "MBM_FlatRead" ) 
	#define CAL_MBM_FlatRead pICmpCAAMemBlockMan->IMBM_FlatRead
	#define CHK_MBM_FlatRead (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_FlatRead  CAL_CMEXPAPI( "MBM_FlatRead" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_FlatRead  PFMBM_FLATREAD pfMBM_FlatRead;
	#define EXT_MBM_FlatRead  extern PFMBM_FLATREAD pfMBM_FlatRead;
	#define GET_MBM_FlatRead(fl)  s_pfCMGetAPI2( "MBM_FlatRead", (RTS_VOID_FCTPTR *)&pfMBM_FlatRead, (fl), 0, 0)
	#define CAL_MBM_FlatRead  pfMBM_FlatRead
	#define CHK_MBM_FlatRead  (pfMBM_FlatRead != NULL)
	#define EXP_MBM_FlatRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatRead", (RTS_UINTPTR)MBM_FlatRead, 0, 0) 
#endif



CAA_ERROR CDECL MBM_FlatDelete(CAA_HANDLE hFlat);
typedef CAA_ERROR (CDECL * PFMBM_FLATDELETE) (CAA_HANDLE hFlat);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATDELETE_NOTIMPLEMENTED)
	#define USE_MBM_FlatDelete
	#define EXT_MBM_FlatDelete
	#define GET_MBM_FlatDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_FlatDelete(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_FlatDelete  FALSE
	#define EXP_MBM_FlatDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_FlatDelete
	#define EXT_MBM_FlatDelete
	#define GET_MBM_FlatDelete(fl)  CAL_CMGETAPI( "MBM_FlatDelete" ) 
	#define CAL_MBM_FlatDelete  MBM_FlatDelete
	#define CHK_MBM_FlatDelete  TRUE
	#define EXP_MBM_FlatDelete  CAL_CMEXPAPI( "MBM_FlatDelete" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_FlatDelete
	#define EXT_MBM_FlatDelete
	#define GET_MBM_FlatDelete(fl)  CAL_CMGETAPI( "MBM_FlatDelete" ) 
	#define CAL_MBM_FlatDelete  MBM_FlatDelete
	#define CHK_MBM_FlatDelete  TRUE
	#define EXP_MBM_FlatDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatDelete", (RTS_UINTPTR)MBM_FlatDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_FlatDelete
	#define EXT_CmpCAAMemBlockManMBM_FlatDelete
	#define GET_CmpCAAMemBlockManMBM_FlatDelete  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_FlatDelete pICmpCAAMemBlockMan->IMBM_FlatDelete
	#define CHK_CmpCAAMemBlockManMBM_FlatDelete (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_FlatDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_FlatDelete
	#define EXT_MBM_FlatDelete
	#define GET_MBM_FlatDelete(fl)  CAL_CMGETAPI( "MBM_FlatDelete" ) 
	#define CAL_MBM_FlatDelete pICmpCAAMemBlockMan->IMBM_FlatDelete
	#define CHK_MBM_FlatDelete (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_FlatDelete  CAL_CMEXPAPI( "MBM_FlatDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_FlatDelete  PFMBM_FLATDELETE pfMBM_FlatDelete;
	#define EXT_MBM_FlatDelete  extern PFMBM_FLATDELETE pfMBM_FlatDelete;
	#define GET_MBM_FlatDelete(fl)  s_pfCMGetAPI2( "MBM_FlatDelete", (RTS_VOID_FCTPTR *)&pfMBM_FlatDelete, (fl), 0, 0)
	#define CAL_MBM_FlatDelete  pfMBM_FlatDelete
	#define CHK_MBM_FlatDelete  (pfMBM_FlatDelete != NULL)
	#define EXP_MBM_FlatDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatDelete", (RTS_UINTPTR)MBM_FlatDelete, 0, 0) 
#endif



CAA_SIZE CDECL MBM_FlatGetSize(CAA_COUNT ctNumKeys);
typedef CAA_SIZE (CDECL * PFMBM_FLATGETSIZE) (CAA_COUNT ctNumKeys);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATGETSIZE_NOTIMPLEMENTED)
	#define USE_MBM_FlatGetSize
	#define EXT_MBM_FlatGetSize
	#define GET_MBM_FlatGetSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_FlatGetSize(p0)  (CAA_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_FlatGetSize  FALSE
	#define EXP_MBM_FlatGetSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_FlatGetSize
	#define EXT_MBM_FlatGetSize
	#define GET_MBM_FlatGetSize(fl)  CAL_CMGETAPI( "MBM_FlatGetSize" ) 
	#define CAL_MBM_FlatGetSize  MBM_FlatGetSize
	#define CHK_MBM_FlatGetSize  TRUE
	#define EXP_MBM_FlatGetSize  CAL_CMEXPAPI( "MBM_FlatGetSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_FlatGetSize
	#define EXT_MBM_FlatGetSize
	#define GET_MBM_FlatGetSize(fl)  CAL_CMGETAPI( "MBM_FlatGetSize" ) 
	#define CAL_MBM_FlatGetSize  MBM_FlatGetSize
	#define CHK_MBM_FlatGetSize  TRUE
	#define EXP_MBM_FlatGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatGetSize", (RTS_UINTPTR)MBM_FlatGetSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_FlatGetSize
	#define EXT_CmpCAAMemBlockManMBM_FlatGetSize
	#define GET_CmpCAAMemBlockManMBM_FlatGetSize  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_FlatGetSize pICmpCAAMemBlockMan->IMBM_FlatGetSize
	#define CHK_CmpCAAMemBlockManMBM_FlatGetSize (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_FlatGetSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_FlatGetSize
	#define EXT_MBM_FlatGetSize
	#define GET_MBM_FlatGetSize(fl)  CAL_CMGETAPI( "MBM_FlatGetSize" ) 
	#define CAL_MBM_FlatGetSize pICmpCAAMemBlockMan->IMBM_FlatGetSize
	#define CHK_MBM_FlatGetSize (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_FlatGetSize  CAL_CMEXPAPI( "MBM_FlatGetSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_FlatGetSize  PFMBM_FLATGETSIZE pfMBM_FlatGetSize;
	#define EXT_MBM_FlatGetSize  extern PFMBM_FLATGETSIZE pfMBM_FlatGetSize;
	#define GET_MBM_FlatGetSize(fl)  s_pfCMGetAPI2( "MBM_FlatGetSize", (RTS_VOID_FCTPTR *)&pfMBM_FlatGetSize, (fl), 0, 0)
	#define CAL_MBM_FlatGetSize  pfMBM_FlatGetSize
	#define CHK_MBM_FlatGetSize  (pfMBM_FlatGetSize != NULL)
	#define EXP_MBM_FlatGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_FlatGetSize", (RTS_UINTPTR)MBM_FlatGetSize, 0, 0) 
#endif




/* Ready List Functions */
CAA_HANDLE CDECL MBM_RLstCreateH(CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_RLSTCREATEH) (CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTCREATEH_NOTIMPLEMENTED)
	#define USE_MBM_RLstCreateH
	#define EXT_MBM_RLstCreateH
	#define GET_MBM_RLstCreateH(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_RLstCreateH(p0)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_RLstCreateH  FALSE
	#define EXP_MBM_RLstCreateH  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_RLstCreateH
	#define EXT_MBM_RLstCreateH
	#define GET_MBM_RLstCreateH(fl)  CAL_CMGETAPI( "MBM_RLstCreateH" ) 
	#define CAL_MBM_RLstCreateH  MBM_RLstCreateH
	#define CHK_MBM_RLstCreateH  TRUE
	#define EXP_MBM_RLstCreateH  CAL_CMEXPAPI( "MBM_RLstCreateH" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_RLstCreateH
	#define EXT_MBM_RLstCreateH
	#define GET_MBM_RLstCreateH(fl)  CAL_CMGETAPI( "MBM_RLstCreateH" ) 
	#define CAL_MBM_RLstCreateH  MBM_RLstCreateH
	#define CHK_MBM_RLstCreateH  TRUE
	#define EXP_MBM_RLstCreateH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstCreateH", (RTS_UINTPTR)MBM_RLstCreateH, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_RLstCreateH
	#define EXT_CmpCAAMemBlockManMBM_RLstCreateH
	#define GET_CmpCAAMemBlockManMBM_RLstCreateH  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_RLstCreateH pICmpCAAMemBlockMan->IMBM_RLstCreateH
	#define CHK_CmpCAAMemBlockManMBM_RLstCreateH (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_RLstCreateH  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_RLstCreateH
	#define EXT_MBM_RLstCreateH
	#define GET_MBM_RLstCreateH(fl)  CAL_CMGETAPI( "MBM_RLstCreateH" ) 
	#define CAL_MBM_RLstCreateH pICmpCAAMemBlockMan->IMBM_RLstCreateH
	#define CHK_MBM_RLstCreateH (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_RLstCreateH  CAL_CMEXPAPI( "MBM_RLstCreateH" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_RLstCreateH  PFMBM_RLSTCREATEH pfMBM_RLstCreateH;
	#define EXT_MBM_RLstCreateH  extern PFMBM_RLSTCREATEH pfMBM_RLstCreateH;
	#define GET_MBM_RLstCreateH(fl)  s_pfCMGetAPI2( "MBM_RLstCreateH", (RTS_VOID_FCTPTR *)&pfMBM_RLstCreateH, (fl), 0, 0)
	#define CAL_MBM_RLstCreateH  pfMBM_RLstCreateH
	#define CHK_MBM_RLstCreateH  (pfMBM_RLstCreateH != NULL)
	#define EXP_MBM_RLstCreateH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstCreateH", (RTS_UINTPTR)MBM_RLstCreateH, 0, 0) 
#endif



CAA_HANDLE CDECL MBM_RLstCreateP(CAA_SIZE szMemory, CAA_PVOID pMemory, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFMBM_RLSTCREATEP) (CAA_SIZE szMemory, CAA_PVOID pMemory, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTCREATEP_NOTIMPLEMENTED)
	#define USE_MBM_RLstCreateP
	#define EXT_MBM_RLstCreateP
	#define GET_MBM_RLstCreateP(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_RLstCreateP(p0,p1,p2)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_RLstCreateP  FALSE
	#define EXP_MBM_RLstCreateP  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_RLstCreateP
	#define EXT_MBM_RLstCreateP
	#define GET_MBM_RLstCreateP(fl)  CAL_CMGETAPI( "MBM_RLstCreateP" ) 
	#define CAL_MBM_RLstCreateP  MBM_RLstCreateP
	#define CHK_MBM_RLstCreateP  TRUE
	#define EXP_MBM_RLstCreateP  CAL_CMEXPAPI( "MBM_RLstCreateP" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_RLstCreateP
	#define EXT_MBM_RLstCreateP
	#define GET_MBM_RLstCreateP(fl)  CAL_CMGETAPI( "MBM_RLstCreateP" ) 
	#define CAL_MBM_RLstCreateP  MBM_RLstCreateP
	#define CHK_MBM_RLstCreateP  TRUE
	#define EXP_MBM_RLstCreateP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstCreateP", (RTS_UINTPTR)MBM_RLstCreateP, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_RLstCreateP
	#define EXT_CmpCAAMemBlockManMBM_RLstCreateP
	#define GET_CmpCAAMemBlockManMBM_RLstCreateP  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_RLstCreateP pICmpCAAMemBlockMan->IMBM_RLstCreateP
	#define CHK_CmpCAAMemBlockManMBM_RLstCreateP (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_RLstCreateP  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_RLstCreateP
	#define EXT_MBM_RLstCreateP
	#define GET_MBM_RLstCreateP(fl)  CAL_CMGETAPI( "MBM_RLstCreateP" ) 
	#define CAL_MBM_RLstCreateP pICmpCAAMemBlockMan->IMBM_RLstCreateP
	#define CHK_MBM_RLstCreateP (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_RLstCreateP  CAL_CMEXPAPI( "MBM_RLstCreateP" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_RLstCreateP  PFMBM_RLSTCREATEP pfMBM_RLstCreateP;
	#define EXT_MBM_RLstCreateP  extern PFMBM_RLSTCREATEP pfMBM_RLstCreateP;
	#define GET_MBM_RLstCreateP(fl)  s_pfCMGetAPI2( "MBM_RLstCreateP", (RTS_VOID_FCTPTR *)&pfMBM_RLstCreateP, (fl), 0, 0)
	#define CAL_MBM_RLstCreateP  pfMBM_RLstCreateP
	#define CHK_MBM_RLstCreateP  (pfMBM_RLstCreateP != NULL)
	#define EXP_MBM_RLstCreateP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstCreateP", (RTS_UINTPTR)MBM_RLstCreateP, 0, 0) 
#endif



CAA_ERROR CDECL MBM_RLstAddPrio(CAA_HANDLE hRLst, unsigned char ucPrio);
typedef CAA_ERROR (CDECL * PFMBM_RLSTADDPRIO) (CAA_HANDLE hRLst, unsigned char ucPrio);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTADDPRIO_NOTIMPLEMENTED)
	#define USE_MBM_RLstAddPrio
	#define EXT_MBM_RLstAddPrio
	#define GET_MBM_RLstAddPrio(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_RLstAddPrio(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_RLstAddPrio  FALSE
	#define EXP_MBM_RLstAddPrio  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_RLstAddPrio
	#define EXT_MBM_RLstAddPrio
	#define GET_MBM_RLstAddPrio(fl)  CAL_CMGETAPI( "MBM_RLstAddPrio" ) 
	#define CAL_MBM_RLstAddPrio  MBM_RLstAddPrio
	#define CHK_MBM_RLstAddPrio  TRUE
	#define EXP_MBM_RLstAddPrio  CAL_CMEXPAPI( "MBM_RLstAddPrio" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_RLstAddPrio
	#define EXT_MBM_RLstAddPrio
	#define GET_MBM_RLstAddPrio(fl)  CAL_CMGETAPI( "MBM_RLstAddPrio" ) 
	#define CAL_MBM_RLstAddPrio  MBM_RLstAddPrio
	#define CHK_MBM_RLstAddPrio  TRUE
	#define EXP_MBM_RLstAddPrio  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstAddPrio", (RTS_UINTPTR)MBM_RLstAddPrio, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_RLstAddPrio
	#define EXT_CmpCAAMemBlockManMBM_RLstAddPrio
	#define GET_CmpCAAMemBlockManMBM_RLstAddPrio  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_RLstAddPrio pICmpCAAMemBlockMan->IMBM_RLstAddPrio
	#define CHK_CmpCAAMemBlockManMBM_RLstAddPrio (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_RLstAddPrio  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_RLstAddPrio
	#define EXT_MBM_RLstAddPrio
	#define GET_MBM_RLstAddPrio(fl)  CAL_CMGETAPI( "MBM_RLstAddPrio" ) 
	#define CAL_MBM_RLstAddPrio pICmpCAAMemBlockMan->IMBM_RLstAddPrio
	#define CHK_MBM_RLstAddPrio (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_RLstAddPrio  CAL_CMEXPAPI( "MBM_RLstAddPrio" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_RLstAddPrio  PFMBM_RLSTADDPRIO pfMBM_RLstAddPrio;
	#define EXT_MBM_RLstAddPrio  extern PFMBM_RLSTADDPRIO pfMBM_RLstAddPrio;
	#define GET_MBM_RLstAddPrio(fl)  s_pfCMGetAPI2( "MBM_RLstAddPrio", (RTS_VOID_FCTPTR *)&pfMBM_RLstAddPrio, (fl), 0, 0)
	#define CAL_MBM_RLstAddPrio  pfMBM_RLstAddPrio
	#define CHK_MBM_RLstAddPrio  (pfMBM_RLstAddPrio != NULL)
	#define EXP_MBM_RLstAddPrio  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstAddPrio", (RTS_UINTPTR)MBM_RLstAddPrio, 0, 0) 
#endif



CAA_ERROR CDECL MBM_RLstRemovePrio(CAA_HANDLE hRLst, unsigned char ucPrio);
typedef CAA_ERROR (CDECL * PFMBM_RLSTREMOVEPRIO) (CAA_HANDLE hRLst, unsigned char ucPrio);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTREMOVEPRIO_NOTIMPLEMENTED)
	#define USE_MBM_RLstRemovePrio
	#define EXT_MBM_RLstRemovePrio
	#define GET_MBM_RLstRemovePrio(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_RLstRemovePrio(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_RLstRemovePrio  FALSE
	#define EXP_MBM_RLstRemovePrio  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_RLstRemovePrio
	#define EXT_MBM_RLstRemovePrio
	#define GET_MBM_RLstRemovePrio(fl)  CAL_CMGETAPI( "MBM_RLstRemovePrio" ) 
	#define CAL_MBM_RLstRemovePrio  MBM_RLstRemovePrio
	#define CHK_MBM_RLstRemovePrio  TRUE
	#define EXP_MBM_RLstRemovePrio  CAL_CMEXPAPI( "MBM_RLstRemovePrio" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_RLstRemovePrio
	#define EXT_MBM_RLstRemovePrio
	#define GET_MBM_RLstRemovePrio(fl)  CAL_CMGETAPI( "MBM_RLstRemovePrio" ) 
	#define CAL_MBM_RLstRemovePrio  MBM_RLstRemovePrio
	#define CHK_MBM_RLstRemovePrio  TRUE
	#define EXP_MBM_RLstRemovePrio  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstRemovePrio", (RTS_UINTPTR)MBM_RLstRemovePrio, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_RLstRemovePrio
	#define EXT_CmpCAAMemBlockManMBM_RLstRemovePrio
	#define GET_CmpCAAMemBlockManMBM_RLstRemovePrio  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_RLstRemovePrio pICmpCAAMemBlockMan->IMBM_RLstRemovePrio
	#define CHK_CmpCAAMemBlockManMBM_RLstRemovePrio (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_RLstRemovePrio  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_RLstRemovePrio
	#define EXT_MBM_RLstRemovePrio
	#define GET_MBM_RLstRemovePrio(fl)  CAL_CMGETAPI( "MBM_RLstRemovePrio" ) 
	#define CAL_MBM_RLstRemovePrio pICmpCAAMemBlockMan->IMBM_RLstRemovePrio
	#define CHK_MBM_RLstRemovePrio (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_RLstRemovePrio  CAL_CMEXPAPI( "MBM_RLstRemovePrio" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_RLstRemovePrio  PFMBM_RLSTREMOVEPRIO pfMBM_RLstRemovePrio;
	#define EXT_MBM_RLstRemovePrio  extern PFMBM_RLSTREMOVEPRIO pfMBM_RLstRemovePrio;
	#define GET_MBM_RLstRemovePrio(fl)  s_pfCMGetAPI2( "MBM_RLstRemovePrio", (RTS_VOID_FCTPTR *)&pfMBM_RLstRemovePrio, (fl), 0, 0)
	#define CAL_MBM_RLstRemovePrio  pfMBM_RLstRemovePrio
	#define CHK_MBM_RLstRemovePrio  (pfMBM_RLstRemovePrio != NULL)
	#define EXP_MBM_RLstRemovePrio  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstRemovePrio", (RTS_UINTPTR)MBM_RLstRemovePrio, 0, 0) 
#endif



unsigned char CDECL MBM_RLstGetHighestPrio(CAA_HANDLE hRLst, CAA_ERROR* peError);
typedef unsigned char (CDECL * PFMBM_RLSTGETHIGHESTPRIO) (CAA_HANDLE hRLst, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTGETHIGHESTPRIO_NOTIMPLEMENTED)
	#define USE_MBM_RLstGetHighestPrio
	#define EXT_MBM_RLstGetHighestPrio
	#define GET_MBM_RLstGetHighestPrio(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_RLstGetHighestPrio(p0,p1)  (unsigned char)ERR_NOTIMPLEMENTED
	#define CHK_MBM_RLstGetHighestPrio  FALSE
	#define EXP_MBM_RLstGetHighestPrio  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_RLstGetHighestPrio
	#define EXT_MBM_RLstGetHighestPrio
	#define GET_MBM_RLstGetHighestPrio(fl)  CAL_CMGETAPI( "MBM_RLstGetHighestPrio" ) 
	#define CAL_MBM_RLstGetHighestPrio  MBM_RLstGetHighestPrio
	#define CHK_MBM_RLstGetHighestPrio  TRUE
	#define EXP_MBM_RLstGetHighestPrio  CAL_CMEXPAPI( "MBM_RLstGetHighestPrio" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_RLstGetHighestPrio
	#define EXT_MBM_RLstGetHighestPrio
	#define GET_MBM_RLstGetHighestPrio(fl)  CAL_CMGETAPI( "MBM_RLstGetHighestPrio" ) 
	#define CAL_MBM_RLstGetHighestPrio  MBM_RLstGetHighestPrio
	#define CHK_MBM_RLstGetHighestPrio  TRUE
	#define EXP_MBM_RLstGetHighestPrio  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstGetHighestPrio", (RTS_UINTPTR)MBM_RLstGetHighestPrio, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_RLstGetHighestPrio
	#define EXT_CmpCAAMemBlockManMBM_RLstGetHighestPrio
	#define GET_CmpCAAMemBlockManMBM_RLstGetHighestPrio  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_RLstGetHighestPrio pICmpCAAMemBlockMan->IMBM_RLstGetHighestPrio
	#define CHK_CmpCAAMemBlockManMBM_RLstGetHighestPrio (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_RLstGetHighestPrio  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_RLstGetHighestPrio
	#define EXT_MBM_RLstGetHighestPrio
	#define GET_MBM_RLstGetHighestPrio(fl)  CAL_CMGETAPI( "MBM_RLstGetHighestPrio" ) 
	#define CAL_MBM_RLstGetHighestPrio pICmpCAAMemBlockMan->IMBM_RLstGetHighestPrio
	#define CHK_MBM_RLstGetHighestPrio (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_RLstGetHighestPrio  CAL_CMEXPAPI( "MBM_RLstGetHighestPrio" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_RLstGetHighestPrio  PFMBM_RLSTGETHIGHESTPRIO pfMBM_RLstGetHighestPrio;
	#define EXT_MBM_RLstGetHighestPrio  extern PFMBM_RLSTGETHIGHESTPRIO pfMBM_RLstGetHighestPrio;
	#define GET_MBM_RLstGetHighestPrio(fl)  s_pfCMGetAPI2( "MBM_RLstGetHighestPrio", (RTS_VOID_FCTPTR *)&pfMBM_RLstGetHighestPrio, (fl), 0, 0)
	#define CAL_MBM_RLstGetHighestPrio  pfMBM_RLstGetHighestPrio
	#define CHK_MBM_RLstGetHighestPrio  (pfMBM_RLstGetHighestPrio != NULL)
	#define EXP_MBM_RLstGetHighestPrio  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstGetHighestPrio", (RTS_UINTPTR)MBM_RLstGetHighestPrio, 0, 0) 
#endif



CAA_BOOL CDECL MBM_RLstCheckPrio(CAA_HANDLE hRLst, unsigned char ucPrio, CAA_ERROR* peError);
typedef CAA_BOOL (CDECL * PFMBM_RLSTCHECKPRIO) (CAA_HANDLE hRLst, unsigned char ucPrio, CAA_ERROR* peError);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTCHECKPRIO_NOTIMPLEMENTED)
	#define USE_MBM_RLstCheckPrio
	#define EXT_MBM_RLstCheckPrio
	#define GET_MBM_RLstCheckPrio(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_RLstCheckPrio(p0,p1,p2)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_MBM_RLstCheckPrio  FALSE
	#define EXP_MBM_RLstCheckPrio  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_RLstCheckPrio
	#define EXT_MBM_RLstCheckPrio
	#define GET_MBM_RLstCheckPrio(fl)  CAL_CMGETAPI( "MBM_RLstCheckPrio" ) 
	#define CAL_MBM_RLstCheckPrio  MBM_RLstCheckPrio
	#define CHK_MBM_RLstCheckPrio  TRUE
	#define EXP_MBM_RLstCheckPrio  CAL_CMEXPAPI( "MBM_RLstCheckPrio" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_RLstCheckPrio
	#define EXT_MBM_RLstCheckPrio
	#define GET_MBM_RLstCheckPrio(fl)  CAL_CMGETAPI( "MBM_RLstCheckPrio" ) 
	#define CAL_MBM_RLstCheckPrio  MBM_RLstCheckPrio
	#define CHK_MBM_RLstCheckPrio  TRUE
	#define EXP_MBM_RLstCheckPrio  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstCheckPrio", (RTS_UINTPTR)MBM_RLstCheckPrio, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_RLstCheckPrio
	#define EXT_CmpCAAMemBlockManMBM_RLstCheckPrio
	#define GET_CmpCAAMemBlockManMBM_RLstCheckPrio  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_RLstCheckPrio pICmpCAAMemBlockMan->IMBM_RLstCheckPrio
	#define CHK_CmpCAAMemBlockManMBM_RLstCheckPrio (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_RLstCheckPrio  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_RLstCheckPrio
	#define EXT_MBM_RLstCheckPrio
	#define GET_MBM_RLstCheckPrio(fl)  CAL_CMGETAPI( "MBM_RLstCheckPrio" ) 
	#define CAL_MBM_RLstCheckPrio pICmpCAAMemBlockMan->IMBM_RLstCheckPrio
	#define CHK_MBM_RLstCheckPrio (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_RLstCheckPrio  CAL_CMEXPAPI( "MBM_RLstCheckPrio" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_RLstCheckPrio  PFMBM_RLSTCHECKPRIO pfMBM_RLstCheckPrio;
	#define EXT_MBM_RLstCheckPrio  extern PFMBM_RLSTCHECKPRIO pfMBM_RLstCheckPrio;
	#define GET_MBM_RLstCheckPrio(fl)  s_pfCMGetAPI2( "MBM_RLstCheckPrio", (RTS_VOID_FCTPTR *)&pfMBM_RLstCheckPrio, (fl), 0, 0)
	#define CAL_MBM_RLstCheckPrio  pfMBM_RLstCheckPrio
	#define CHK_MBM_RLstCheckPrio  (pfMBM_RLstCheckPrio != NULL)
	#define EXP_MBM_RLstCheckPrio  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstCheckPrio", (RTS_UINTPTR)MBM_RLstCheckPrio, 0, 0) 
#endif



CAA_ERROR CDECL MBM_RLstDelete(CAA_HANDLE hRLst);
typedef CAA_ERROR (CDECL * PFMBM_RLSTDELETE) (CAA_HANDLE hRLst);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTDELETE_NOTIMPLEMENTED)
	#define USE_MBM_RLstDelete
	#define EXT_MBM_RLstDelete
	#define GET_MBM_RLstDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_RLstDelete(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_MBM_RLstDelete  FALSE
	#define EXP_MBM_RLstDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_RLstDelete
	#define EXT_MBM_RLstDelete
	#define GET_MBM_RLstDelete(fl)  CAL_CMGETAPI( "MBM_RLstDelete" ) 
	#define CAL_MBM_RLstDelete  MBM_RLstDelete
	#define CHK_MBM_RLstDelete  TRUE
	#define EXP_MBM_RLstDelete  CAL_CMEXPAPI( "MBM_RLstDelete" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_RLstDelete
	#define EXT_MBM_RLstDelete
	#define GET_MBM_RLstDelete(fl)  CAL_CMGETAPI( "MBM_RLstDelete" ) 
	#define CAL_MBM_RLstDelete  MBM_RLstDelete
	#define CHK_MBM_RLstDelete  TRUE
	#define EXP_MBM_RLstDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstDelete", (RTS_UINTPTR)MBM_RLstDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_RLstDelete
	#define EXT_CmpCAAMemBlockManMBM_RLstDelete
	#define GET_CmpCAAMemBlockManMBM_RLstDelete  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_RLstDelete pICmpCAAMemBlockMan->IMBM_RLstDelete
	#define CHK_CmpCAAMemBlockManMBM_RLstDelete (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_RLstDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_RLstDelete
	#define EXT_MBM_RLstDelete
	#define GET_MBM_RLstDelete(fl)  CAL_CMGETAPI( "MBM_RLstDelete" ) 
	#define CAL_MBM_RLstDelete pICmpCAAMemBlockMan->IMBM_RLstDelete
	#define CHK_MBM_RLstDelete (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_RLstDelete  CAL_CMEXPAPI( "MBM_RLstDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_RLstDelete  PFMBM_RLSTDELETE pfMBM_RLstDelete;
	#define EXT_MBM_RLstDelete  extern PFMBM_RLSTDELETE pfMBM_RLstDelete;
	#define GET_MBM_RLstDelete(fl)  s_pfCMGetAPI2( "MBM_RLstDelete", (RTS_VOID_FCTPTR *)&pfMBM_RLstDelete, (fl), 0, 0)
	#define CAL_MBM_RLstDelete  pfMBM_RLstDelete
	#define CHK_MBM_RLstDelete  (pfMBM_RLstDelete != NULL)
	#define EXP_MBM_RLstDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstDelete", (RTS_UINTPTR)MBM_RLstDelete, 0, 0) 
#endif



CAA_SIZE CDECL MBM_RLstGetSize(CAA_BOOL xDummy);
typedef CAA_SIZE (CDECL * PFMBM_RLSTGETSIZE) (CAA_BOOL xDummy);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTGETSIZE_NOTIMPLEMENTED)
	#define USE_MBM_RLstGetSize
	#define EXT_MBM_RLstGetSize
	#define GET_MBM_RLstGetSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_RLstGetSize(p0)  (CAA_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_MBM_RLstGetSize  FALSE
	#define EXP_MBM_RLstGetSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_RLstGetSize
	#define EXT_MBM_RLstGetSize
	#define GET_MBM_RLstGetSize(fl)  CAL_CMGETAPI( "MBM_RLstGetSize" ) 
	#define CAL_MBM_RLstGetSize  MBM_RLstGetSize
	#define CHK_MBM_RLstGetSize  TRUE
	#define EXP_MBM_RLstGetSize  CAL_CMEXPAPI( "MBM_RLstGetSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_RLstGetSize
	#define EXT_MBM_RLstGetSize
	#define GET_MBM_RLstGetSize(fl)  CAL_CMGETAPI( "MBM_RLstGetSize" ) 
	#define CAL_MBM_RLstGetSize  MBM_RLstGetSize
	#define CHK_MBM_RLstGetSize  TRUE
	#define EXP_MBM_RLstGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstGetSize", (RTS_UINTPTR)MBM_RLstGetSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_RLstGetSize
	#define EXT_CmpCAAMemBlockManMBM_RLstGetSize
	#define GET_CmpCAAMemBlockManMBM_RLstGetSize  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_RLstGetSize pICmpCAAMemBlockMan->IMBM_RLstGetSize
	#define CHK_CmpCAAMemBlockManMBM_RLstGetSize (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_RLstGetSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_RLstGetSize
	#define EXT_MBM_RLstGetSize
	#define GET_MBM_RLstGetSize(fl)  CAL_CMGETAPI( "MBM_RLstGetSize" ) 
	#define CAL_MBM_RLstGetSize pICmpCAAMemBlockMan->IMBM_RLstGetSize
	#define CHK_MBM_RLstGetSize (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_RLstGetSize  CAL_CMEXPAPI( "MBM_RLstGetSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_RLstGetSize  PFMBM_RLSTGETSIZE pfMBM_RLstGetSize;
	#define EXT_MBM_RLstGetSize  extern PFMBM_RLSTGETSIZE pfMBM_RLstGetSize;
	#define GET_MBM_RLstGetSize(fl)  s_pfCMGetAPI2( "MBM_RLstGetSize", (RTS_VOID_FCTPTR *)&pfMBM_RLstGetSize, (fl), 0, 0)
	#define CAL_MBM_RLstGetSize  pfMBM_RLstGetSize
	#define CHK_MBM_RLstGetSize  (pfMBM_RLstGetSize != NULL)
	#define EXP_MBM_RLstGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_RLstGetSize", (RTS_UINTPTR)MBM_RLstGetSize, 0, 0) 
#endif




unsigned short CDECL MBM_GetSupplierVersion(CAA_BOOL xDummy);
typedef unsigned short (CDECL * PFMBM_GETSUPPLIERVERSION) (CAA_BOOL xDummy);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_MBM_GetSupplierVersion
	#define EXT_MBM_GetSupplierVersion
	#define GET_MBM_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MBM_GetSupplierVersion(p0)  (unsigned short)ERR_NOTIMPLEMENTED
	#define CHK_MBM_GetSupplierVersion  FALSE
	#define EXP_MBM_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MBM_GetSupplierVersion
	#define EXT_MBM_GetSupplierVersion
	#define GET_MBM_GetSupplierVersion(fl)  CAL_CMGETAPI( "MBM_GetSupplierVersion" ) 
	#define CAL_MBM_GetSupplierVersion  MBM_GetSupplierVersion
	#define CHK_MBM_GetSupplierVersion  TRUE
	#define EXP_MBM_GetSupplierVersion  CAL_CMEXPAPI( "MBM_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_MBM_GetSupplierVersion
	#define EXT_MBM_GetSupplierVersion
	#define GET_MBM_GetSupplierVersion(fl)  CAL_CMGETAPI( "MBM_GetSupplierVersion" ) 
	#define CAL_MBM_GetSupplierVersion  MBM_GetSupplierVersion
	#define CHK_MBM_GetSupplierVersion  TRUE
	#define EXP_MBM_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_GetSupplierVersion", (RTS_UINTPTR)MBM_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManMBM_GetSupplierVersion
	#define EXT_CmpCAAMemBlockManMBM_GetSupplierVersion
	#define GET_CmpCAAMemBlockManMBM_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAAMemBlockManMBM_GetSupplierVersion pICmpCAAMemBlockMan->IMBM_GetSupplierVersion
	#define CHK_CmpCAAMemBlockManMBM_GetSupplierVersion (pICmpCAAMemBlockMan != NULL)
	#define EXP_CmpCAAMemBlockManMBM_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MBM_GetSupplierVersion
	#define EXT_MBM_GetSupplierVersion
	#define GET_MBM_GetSupplierVersion(fl)  CAL_CMGETAPI( "MBM_GetSupplierVersion" ) 
	#define CAL_MBM_GetSupplierVersion pICmpCAAMemBlockMan->IMBM_GetSupplierVersion
	#define CHK_MBM_GetSupplierVersion (pICmpCAAMemBlockMan != NULL)
	#define EXP_MBM_GetSupplierVersion  CAL_CMEXPAPI( "MBM_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_MBM_GetSupplierVersion  PFMBM_GETSUPPLIERVERSION pfMBM_GetSupplierVersion;
	#define EXT_MBM_GetSupplierVersion  extern PFMBM_GETSUPPLIERVERSION pfMBM_GetSupplierVersion;
	#define GET_MBM_GetSupplierVersion(fl)  s_pfCMGetAPI2( "MBM_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfMBM_GetSupplierVersion, (fl), 0, 0)
	#define CAL_MBM_GetSupplierVersion  pfMBM_GetSupplierVersion
	#define CHK_MBM_GetSupplierVersion  (pfMBM_GetSupplierVersion != NULL)
	#define EXP_MBM_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MBM_GetSupplierVersion", (RTS_UINTPTR)MBM_GetSupplierVersion, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>mbm_blockgetdata</description>
 */
typedef struct tagmbm_blockgetdata_struct
{
	CAA_HANDLE hBlock;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_PVOID MBM_BlockGetData;			/* VAR_OUTPUT */	
} mbm_blockgetdata_struct;

void CDECL CDECL_EXT mbm_blockgetdata(mbm_blockgetdata_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_BLOCKGETDATA_IEC) (mbm_blockgetdata_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_BLOCKGETDATA_NOTIMPLEMENTED)
	#define USE_mbm_blockgetdata
	#define EXT_mbm_blockgetdata
	#define GET_mbm_blockgetdata(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_blockgetdata(p0) 
	#define CHK_mbm_blockgetdata  FALSE
	#define EXP_mbm_blockgetdata  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_blockgetdata
	#define EXT_mbm_blockgetdata
	#define GET_mbm_blockgetdata(fl)  CAL_CMGETAPI( "mbm_blockgetdata" ) 
	#define CAL_mbm_blockgetdata  mbm_blockgetdata
	#define CHK_mbm_blockgetdata  TRUE
	#define EXP_mbm_blockgetdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_blockgetdata", (RTS_UINTPTR)mbm_blockgetdata, 1, RTSITF_GET_SIGNATURE(0, 0x32F2CF4F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_blockgetdata
	#define EXT_mbm_blockgetdata
	#define GET_mbm_blockgetdata(fl)  CAL_CMGETAPI( "mbm_blockgetdata" ) 
	#define CAL_mbm_blockgetdata  mbm_blockgetdata
	#define CHK_mbm_blockgetdata  TRUE
	#define EXP_mbm_blockgetdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_blockgetdata", (RTS_UINTPTR)mbm_blockgetdata, 1, RTSITF_GET_SIGNATURE(0, 0x32F2CF4F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_blockgetdata
	#define EXT_CmpCAAMemBlockManmbm_blockgetdata
	#define GET_CmpCAAMemBlockManmbm_blockgetdata  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_blockgetdata  mbm_blockgetdata
	#define CHK_CmpCAAMemBlockManmbm_blockgetdata  TRUE
	#define EXP_CmpCAAMemBlockManmbm_blockgetdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_blockgetdata", (RTS_UINTPTR)mbm_blockgetdata, 1, RTSITF_GET_SIGNATURE(0, 0x32F2CF4F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_blockgetdata
	#define EXT_mbm_blockgetdata
	#define GET_mbm_blockgetdata(fl)  CAL_CMGETAPI( "mbm_blockgetdata" ) 
	#define CAL_mbm_blockgetdata  mbm_blockgetdata
	#define CHK_mbm_blockgetdata  TRUE
	#define EXP_mbm_blockgetdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_blockgetdata", (RTS_UINTPTR)mbm_blockgetdata, 1, RTSITF_GET_SIGNATURE(0, 0x32F2CF4F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_blockgetdata  PFMBM_BLOCKGETDATA_IEC pfmbm_blockgetdata;
	#define EXT_mbm_blockgetdata  extern PFMBM_BLOCKGETDATA_IEC pfmbm_blockgetdata;
	#define GET_mbm_blockgetdata(fl)  s_pfCMGetAPI2( "mbm_blockgetdata", (RTS_VOID_FCTPTR *)&pfmbm_blockgetdata, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x32F2CF4F), 0x03050500)
	#define CAL_mbm_blockgetdata  pfmbm_blockgetdata
	#define CHK_mbm_blockgetdata  (pfmbm_blockgetdata != NULL)
	#define EXP_mbm_blockgetdata   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_blockgetdata", (RTS_UINTPTR)mbm_blockgetdata, 1, RTSITF_GET_SIGNATURE(0, 0x32F2CF4F), 0x03050500) 
#endif


/**
 * <description>mbm_flatcreateh</description>
 */
typedef struct tagmbm_flatcreateh_struct
{
	CAA_IDENT idMinKey;					/* VAR_INPUT */	
	CAA_IDENT idMaxKey;					/* VAR_INPUT */	
	CAA_COUNT ctNumKeys;				/* VAR_INPUT */	
	CAA_ENUM eEnable;					/* VAR_INPUT */	
	CAA_ENUM eDisable;					/* VAR_INPUT */	
	CAA_ENUM eUpdate;					/* VAR_INPUT */	
	CAA_ENUM eRead;						/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_FlatCreateH;			/* VAR_OUTPUT */	/* hFlast */
} mbm_flatcreateh_struct;

void CDECL CDECL_EXT mbm_flatcreateh(mbm_flatcreateh_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_FLATCREATEH_IEC) (mbm_flatcreateh_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATCREATEH_NOTIMPLEMENTED)
	#define USE_mbm_flatcreateh
	#define EXT_mbm_flatcreateh
	#define GET_mbm_flatcreateh(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_flatcreateh(p0) 
	#define CHK_mbm_flatcreateh  FALSE
	#define EXP_mbm_flatcreateh  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_flatcreateh
	#define EXT_mbm_flatcreateh
	#define GET_mbm_flatcreateh(fl)  CAL_CMGETAPI( "mbm_flatcreateh" ) 
	#define CAL_mbm_flatcreateh  mbm_flatcreateh
	#define CHK_mbm_flatcreateh  TRUE
	#define EXP_mbm_flatcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatcreateh", (RTS_UINTPTR)mbm_flatcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x101D308E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_flatcreateh
	#define EXT_mbm_flatcreateh
	#define GET_mbm_flatcreateh(fl)  CAL_CMGETAPI( "mbm_flatcreateh" ) 
	#define CAL_mbm_flatcreateh  mbm_flatcreateh
	#define CHK_mbm_flatcreateh  TRUE
	#define EXP_mbm_flatcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatcreateh", (RTS_UINTPTR)mbm_flatcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x101D308E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_flatcreateh
	#define EXT_CmpCAAMemBlockManmbm_flatcreateh
	#define GET_CmpCAAMemBlockManmbm_flatcreateh  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_flatcreateh  mbm_flatcreateh
	#define CHK_CmpCAAMemBlockManmbm_flatcreateh  TRUE
	#define EXP_CmpCAAMemBlockManmbm_flatcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatcreateh", (RTS_UINTPTR)mbm_flatcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x101D308E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_flatcreateh
	#define EXT_mbm_flatcreateh
	#define GET_mbm_flatcreateh(fl)  CAL_CMGETAPI( "mbm_flatcreateh" ) 
	#define CAL_mbm_flatcreateh  mbm_flatcreateh
	#define CHK_mbm_flatcreateh  TRUE
	#define EXP_mbm_flatcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatcreateh", (RTS_UINTPTR)mbm_flatcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x101D308E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_flatcreateh  PFMBM_FLATCREATEH_IEC pfmbm_flatcreateh;
	#define EXT_mbm_flatcreateh  extern PFMBM_FLATCREATEH_IEC pfmbm_flatcreateh;
	#define GET_mbm_flatcreateh(fl)  s_pfCMGetAPI2( "mbm_flatcreateh", (RTS_VOID_FCTPTR *)&pfmbm_flatcreateh, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x101D308E), 0x03050500)
	#define CAL_mbm_flatcreateh  pfmbm_flatcreateh
	#define CHK_mbm_flatcreateh  (pfmbm_flatcreateh != NULL)
	#define EXP_mbm_flatcreateh   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatcreateh", (RTS_UINTPTR)mbm_flatcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x101D308E), 0x03050500) 
#endif


/**
 * <description>mbm_flatcreatep</description>
 */
typedef struct tagmbm_flatcreatep_struct
{
	CAA_IDENT idMinKey;					/* VAR_INPUT */	
	CAA_IDENT idMaxKey;					/* VAR_INPUT */	
	CAA_COUNT ctNumKey;					/* VAR_INPUT */	
	CAA_SIZE szMemSize;					/* VAR_INPUT */	
	CAA_PVOID pMemory;					/* VAR_INPUT */	
	CAA_ENUM eEnable;					/* VAR_INPUT */	
	CAA_ENUM eDisable;					/* VAR_INPUT */	
	CAA_ENUM eUpdate;					/* VAR_INPUT */	
	CAA_ENUM eRead;						/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_FlatCreateP;			/* VAR_OUTPUT */	/* hFlat */
} mbm_flatcreatep_struct;

void CDECL CDECL_EXT mbm_flatcreatep(mbm_flatcreatep_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_FLATCREATEP_IEC) (mbm_flatcreatep_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATCREATEP_NOTIMPLEMENTED)
	#define USE_mbm_flatcreatep
	#define EXT_mbm_flatcreatep
	#define GET_mbm_flatcreatep(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_flatcreatep(p0) 
	#define CHK_mbm_flatcreatep  FALSE
	#define EXP_mbm_flatcreatep  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_flatcreatep
	#define EXT_mbm_flatcreatep
	#define GET_mbm_flatcreatep(fl)  CAL_CMGETAPI( "mbm_flatcreatep" ) 
	#define CAL_mbm_flatcreatep  mbm_flatcreatep
	#define CHK_mbm_flatcreatep  TRUE
	#define EXP_mbm_flatcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatcreatep", (RTS_UINTPTR)mbm_flatcreatep, 1, RTSITF_GET_SIGNATURE(0, 0xFC1B413D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_flatcreatep
	#define EXT_mbm_flatcreatep
	#define GET_mbm_flatcreatep(fl)  CAL_CMGETAPI( "mbm_flatcreatep" ) 
	#define CAL_mbm_flatcreatep  mbm_flatcreatep
	#define CHK_mbm_flatcreatep  TRUE
	#define EXP_mbm_flatcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatcreatep", (RTS_UINTPTR)mbm_flatcreatep, 1, RTSITF_GET_SIGNATURE(0, 0xFC1B413D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_flatcreatep
	#define EXT_CmpCAAMemBlockManmbm_flatcreatep
	#define GET_CmpCAAMemBlockManmbm_flatcreatep  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_flatcreatep  mbm_flatcreatep
	#define CHK_CmpCAAMemBlockManmbm_flatcreatep  TRUE
	#define EXP_CmpCAAMemBlockManmbm_flatcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatcreatep", (RTS_UINTPTR)mbm_flatcreatep, 1, RTSITF_GET_SIGNATURE(0, 0xFC1B413D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_flatcreatep
	#define EXT_mbm_flatcreatep
	#define GET_mbm_flatcreatep(fl)  CAL_CMGETAPI( "mbm_flatcreatep" ) 
	#define CAL_mbm_flatcreatep  mbm_flatcreatep
	#define CHK_mbm_flatcreatep  TRUE
	#define EXP_mbm_flatcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatcreatep", (RTS_UINTPTR)mbm_flatcreatep, 1, RTSITF_GET_SIGNATURE(0, 0xFC1B413D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_flatcreatep  PFMBM_FLATCREATEP_IEC pfmbm_flatcreatep;
	#define EXT_mbm_flatcreatep  extern PFMBM_FLATCREATEP_IEC pfmbm_flatcreatep;
	#define GET_mbm_flatcreatep(fl)  s_pfCMGetAPI2( "mbm_flatcreatep", (RTS_VOID_FCTPTR *)&pfmbm_flatcreatep, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFC1B413D), 0x03050500)
	#define CAL_mbm_flatcreatep  pfmbm_flatcreatep
	#define CHK_mbm_flatcreatep  (pfmbm_flatcreatep != NULL)
	#define EXP_mbm_flatcreatep   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatcreatep", (RTS_UINTPTR)mbm_flatcreatep, 1, RTSITF_GET_SIGNATURE(0, 0xFC1B413D), 0x03050500) 
#endif


/**
 * <description>mbm_flatdelete</description>
 */
typedef struct tagmbm_flatdelete_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_ERROR MBM_FlatDelete;			/* VAR_OUTPUT */	/* eError */
} mbm_flatdelete_struct;

void CDECL CDECL_EXT mbm_flatdelete(mbm_flatdelete_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_FLATDELETE_IEC) (mbm_flatdelete_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATDELETE_NOTIMPLEMENTED)
	#define USE_mbm_flatdelete
	#define EXT_mbm_flatdelete
	#define GET_mbm_flatdelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_flatdelete(p0) 
	#define CHK_mbm_flatdelete  FALSE
	#define EXP_mbm_flatdelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_flatdelete
	#define EXT_mbm_flatdelete
	#define GET_mbm_flatdelete(fl)  CAL_CMGETAPI( "mbm_flatdelete" ) 
	#define CAL_mbm_flatdelete  mbm_flatdelete
	#define CHK_mbm_flatdelete  TRUE
	#define EXP_mbm_flatdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatdelete", (RTS_UINTPTR)mbm_flatdelete, 1, RTSITF_GET_SIGNATURE(0, 0x51070F21), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_flatdelete
	#define EXT_mbm_flatdelete
	#define GET_mbm_flatdelete(fl)  CAL_CMGETAPI( "mbm_flatdelete" ) 
	#define CAL_mbm_flatdelete  mbm_flatdelete
	#define CHK_mbm_flatdelete  TRUE
	#define EXP_mbm_flatdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatdelete", (RTS_UINTPTR)mbm_flatdelete, 1, RTSITF_GET_SIGNATURE(0, 0x51070F21), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_flatdelete
	#define EXT_CmpCAAMemBlockManmbm_flatdelete
	#define GET_CmpCAAMemBlockManmbm_flatdelete  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_flatdelete  mbm_flatdelete
	#define CHK_CmpCAAMemBlockManmbm_flatdelete  TRUE
	#define EXP_CmpCAAMemBlockManmbm_flatdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatdelete", (RTS_UINTPTR)mbm_flatdelete, 1, RTSITF_GET_SIGNATURE(0, 0x51070F21), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_flatdelete
	#define EXT_mbm_flatdelete
	#define GET_mbm_flatdelete(fl)  CAL_CMGETAPI( "mbm_flatdelete" ) 
	#define CAL_mbm_flatdelete  mbm_flatdelete
	#define CHK_mbm_flatdelete  TRUE
	#define EXP_mbm_flatdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatdelete", (RTS_UINTPTR)mbm_flatdelete, 1, RTSITF_GET_SIGNATURE(0, 0x51070F21), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_flatdelete  PFMBM_FLATDELETE_IEC pfmbm_flatdelete;
	#define EXT_mbm_flatdelete  extern PFMBM_FLATDELETE_IEC pfmbm_flatdelete;
	#define GET_mbm_flatdelete(fl)  s_pfCMGetAPI2( "mbm_flatdelete", (RTS_VOID_FCTPTR *)&pfmbm_flatdelete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x51070F21), 0x03050500)
	#define CAL_mbm_flatdelete  pfmbm_flatdelete
	#define CHK_mbm_flatdelete  (pfmbm_flatdelete != NULL)
	#define EXP_mbm_flatdelete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatdelete", (RTS_UINTPTR)mbm_flatdelete, 1, RTSITF_GET_SIGNATURE(0, 0x51070F21), 0x03050500) 
#endif


/**
 * <description>mbm_flatdisable</description>
 */
typedef struct tagmbm_flatdisable_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_IDENT idKey;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_FlatDisable;			/* VAR_OUTPUT */	/* hOldFlat */
} mbm_flatdisable_struct;

void CDECL CDECL_EXT mbm_flatdisable(mbm_flatdisable_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_FLATDISABLE_IEC) (mbm_flatdisable_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATDISABLE_NOTIMPLEMENTED)
	#define USE_mbm_flatdisable
	#define EXT_mbm_flatdisable
	#define GET_mbm_flatdisable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_flatdisable(p0) 
	#define CHK_mbm_flatdisable  FALSE
	#define EXP_mbm_flatdisable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_flatdisable
	#define EXT_mbm_flatdisable
	#define GET_mbm_flatdisable(fl)  CAL_CMGETAPI( "mbm_flatdisable" ) 
	#define CAL_mbm_flatdisable  mbm_flatdisable
	#define CHK_mbm_flatdisable  TRUE
	#define EXP_mbm_flatdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatdisable", (RTS_UINTPTR)mbm_flatdisable, 1, RTSITF_GET_SIGNATURE(0, 0x89676E45), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_flatdisable
	#define EXT_mbm_flatdisable
	#define GET_mbm_flatdisable(fl)  CAL_CMGETAPI( "mbm_flatdisable" ) 
	#define CAL_mbm_flatdisable  mbm_flatdisable
	#define CHK_mbm_flatdisable  TRUE
	#define EXP_mbm_flatdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatdisable", (RTS_UINTPTR)mbm_flatdisable, 1, RTSITF_GET_SIGNATURE(0, 0x89676E45), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_flatdisable
	#define EXT_CmpCAAMemBlockManmbm_flatdisable
	#define GET_CmpCAAMemBlockManmbm_flatdisable  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_flatdisable  mbm_flatdisable
	#define CHK_CmpCAAMemBlockManmbm_flatdisable  TRUE
	#define EXP_CmpCAAMemBlockManmbm_flatdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatdisable", (RTS_UINTPTR)mbm_flatdisable, 1, RTSITF_GET_SIGNATURE(0, 0x89676E45), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_flatdisable
	#define EXT_mbm_flatdisable
	#define GET_mbm_flatdisable(fl)  CAL_CMGETAPI( "mbm_flatdisable" ) 
	#define CAL_mbm_flatdisable  mbm_flatdisable
	#define CHK_mbm_flatdisable  TRUE
	#define EXP_mbm_flatdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatdisable", (RTS_UINTPTR)mbm_flatdisable, 1, RTSITF_GET_SIGNATURE(0, 0x89676E45), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_flatdisable  PFMBM_FLATDISABLE_IEC pfmbm_flatdisable;
	#define EXT_mbm_flatdisable  extern PFMBM_FLATDISABLE_IEC pfmbm_flatdisable;
	#define GET_mbm_flatdisable(fl)  s_pfCMGetAPI2( "mbm_flatdisable", (RTS_VOID_FCTPTR *)&pfmbm_flatdisable, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x89676E45), 0x03050500)
	#define CAL_mbm_flatdisable  pfmbm_flatdisable
	#define CHK_mbm_flatdisable  (pfmbm_flatdisable != NULL)
	#define EXP_mbm_flatdisable   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatdisable", (RTS_UINTPTR)mbm_flatdisable, 1, RTSITF_GET_SIGNATURE(0, 0x89676E45), 0x03050500) 
#endif


/**
 * <description>mbm_flatenable</description>
 */
typedef struct tagmbm_flatenable_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_IDENT idKey;					/* VAR_INPUT */	
	CAA_ERROR MBM_FlatEnable;			/* VAR_OUTPUT */	/* eError */
} mbm_flatenable_struct;

void CDECL CDECL_EXT mbm_flatenable(mbm_flatenable_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_FLATENABLE_IEC) (mbm_flatenable_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATENABLE_NOTIMPLEMENTED)
	#define USE_mbm_flatenable
	#define EXT_mbm_flatenable
	#define GET_mbm_flatenable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_flatenable(p0) 
	#define CHK_mbm_flatenable  FALSE
	#define EXP_mbm_flatenable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_flatenable
	#define EXT_mbm_flatenable
	#define GET_mbm_flatenable(fl)  CAL_CMGETAPI( "mbm_flatenable" ) 
	#define CAL_mbm_flatenable  mbm_flatenable
	#define CHK_mbm_flatenable  TRUE
	#define EXP_mbm_flatenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatenable", (RTS_UINTPTR)mbm_flatenable, 1, RTSITF_GET_SIGNATURE(0, 0x1923C169), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_flatenable
	#define EXT_mbm_flatenable
	#define GET_mbm_flatenable(fl)  CAL_CMGETAPI( "mbm_flatenable" ) 
	#define CAL_mbm_flatenable  mbm_flatenable
	#define CHK_mbm_flatenable  TRUE
	#define EXP_mbm_flatenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatenable", (RTS_UINTPTR)mbm_flatenable, 1, RTSITF_GET_SIGNATURE(0, 0x1923C169), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_flatenable
	#define EXT_CmpCAAMemBlockManmbm_flatenable
	#define GET_CmpCAAMemBlockManmbm_flatenable  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_flatenable  mbm_flatenable
	#define CHK_CmpCAAMemBlockManmbm_flatenable  TRUE
	#define EXP_CmpCAAMemBlockManmbm_flatenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatenable", (RTS_UINTPTR)mbm_flatenable, 1, RTSITF_GET_SIGNATURE(0, 0x1923C169), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_flatenable
	#define EXT_mbm_flatenable
	#define GET_mbm_flatenable(fl)  CAL_CMGETAPI( "mbm_flatenable" ) 
	#define CAL_mbm_flatenable  mbm_flatenable
	#define CHK_mbm_flatenable  TRUE
	#define EXP_mbm_flatenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatenable", (RTS_UINTPTR)mbm_flatenable, 1, RTSITF_GET_SIGNATURE(0, 0x1923C169), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_flatenable  PFMBM_FLATENABLE_IEC pfmbm_flatenable;
	#define EXT_mbm_flatenable  extern PFMBM_FLATENABLE_IEC pfmbm_flatenable;
	#define GET_mbm_flatenable(fl)  s_pfCMGetAPI2( "mbm_flatenable", (RTS_VOID_FCTPTR *)&pfmbm_flatenable, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1923C169), 0x03050500)
	#define CAL_mbm_flatenable  pfmbm_flatenable
	#define CHK_mbm_flatenable  (pfmbm_flatenable != NULL)
	#define EXP_mbm_flatenable   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatenable", (RTS_UINTPTR)mbm_flatenable, 1, RTSITF_GET_SIGNATURE(0, 0x1923C169), 0x03050500) 
#endif


/**
 * <description>mbm_flatgetsize</description>
 */
typedef struct tagmbm_flatgetsize_struct
{
	CAA_COUNT ctNumKeys;				/* VAR_INPUT */	
	CAA_SIZE MBM_FlatGetSize;			/* VAR_OUTPUT */	
} mbm_flatgetsize_struct;

void CDECL CDECL_EXT mbm_flatgetsize(mbm_flatgetsize_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_FLATGETSIZE_IEC) (mbm_flatgetsize_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATGETSIZE_NOTIMPLEMENTED)
	#define USE_mbm_flatgetsize
	#define EXT_mbm_flatgetsize
	#define GET_mbm_flatgetsize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_flatgetsize(p0) 
	#define CHK_mbm_flatgetsize  FALSE
	#define EXP_mbm_flatgetsize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_flatgetsize
	#define EXT_mbm_flatgetsize
	#define GET_mbm_flatgetsize(fl)  CAL_CMGETAPI( "mbm_flatgetsize" ) 
	#define CAL_mbm_flatgetsize  mbm_flatgetsize
	#define CHK_mbm_flatgetsize  TRUE
	#define EXP_mbm_flatgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatgetsize", (RTS_UINTPTR)mbm_flatgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x80F388B2), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_flatgetsize
	#define EXT_mbm_flatgetsize
	#define GET_mbm_flatgetsize(fl)  CAL_CMGETAPI( "mbm_flatgetsize" ) 
	#define CAL_mbm_flatgetsize  mbm_flatgetsize
	#define CHK_mbm_flatgetsize  TRUE
	#define EXP_mbm_flatgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatgetsize", (RTS_UINTPTR)mbm_flatgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x80F388B2), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_flatgetsize
	#define EXT_CmpCAAMemBlockManmbm_flatgetsize
	#define GET_CmpCAAMemBlockManmbm_flatgetsize  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_flatgetsize  mbm_flatgetsize
	#define CHK_CmpCAAMemBlockManmbm_flatgetsize  TRUE
	#define EXP_CmpCAAMemBlockManmbm_flatgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatgetsize", (RTS_UINTPTR)mbm_flatgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x80F388B2), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_flatgetsize
	#define EXT_mbm_flatgetsize
	#define GET_mbm_flatgetsize(fl)  CAL_CMGETAPI( "mbm_flatgetsize" ) 
	#define CAL_mbm_flatgetsize  mbm_flatgetsize
	#define CHK_mbm_flatgetsize  TRUE
	#define EXP_mbm_flatgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatgetsize", (RTS_UINTPTR)mbm_flatgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x80F388B2), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_flatgetsize  PFMBM_FLATGETSIZE_IEC pfmbm_flatgetsize;
	#define EXT_mbm_flatgetsize  extern PFMBM_FLATGETSIZE_IEC pfmbm_flatgetsize;
	#define GET_mbm_flatgetsize(fl)  s_pfCMGetAPI2( "mbm_flatgetsize", (RTS_VOID_FCTPTR *)&pfmbm_flatgetsize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x80F388B2), 0x03050500)
	#define CAL_mbm_flatgetsize  pfmbm_flatgetsize
	#define CHK_mbm_flatgetsize  (pfmbm_flatgetsize != NULL)
	#define EXP_mbm_flatgetsize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatgetsize", (RTS_UINTPTR)mbm_flatgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x80F388B2), 0x03050500) 
#endif


/**
 * <description>mbm_flatread</description>
 */
typedef struct tagmbm_flatread_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_IDENT idKey;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_FlatRead;			/* VAR_OUTPUT */	/* hMsg */
} mbm_flatread_struct;

void CDECL CDECL_EXT mbm_flatread(mbm_flatread_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_FLATREAD_IEC) (mbm_flatread_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATREAD_NOTIMPLEMENTED)
	#define USE_mbm_flatread
	#define EXT_mbm_flatread
	#define GET_mbm_flatread(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_flatread(p0) 
	#define CHK_mbm_flatread  FALSE
	#define EXP_mbm_flatread  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_flatread
	#define EXT_mbm_flatread
	#define GET_mbm_flatread(fl)  CAL_CMGETAPI( "mbm_flatread" ) 
	#define CAL_mbm_flatread  mbm_flatread
	#define CHK_mbm_flatread  TRUE
	#define EXP_mbm_flatread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatread", (RTS_UINTPTR)mbm_flatread, 1, RTSITF_GET_SIGNATURE(0, 0x6D388DC6), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_flatread
	#define EXT_mbm_flatread
	#define GET_mbm_flatread(fl)  CAL_CMGETAPI( "mbm_flatread" ) 
	#define CAL_mbm_flatread  mbm_flatread
	#define CHK_mbm_flatread  TRUE
	#define EXP_mbm_flatread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatread", (RTS_UINTPTR)mbm_flatread, 1, RTSITF_GET_SIGNATURE(0, 0x6D388DC6), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_flatread
	#define EXT_CmpCAAMemBlockManmbm_flatread
	#define GET_CmpCAAMemBlockManmbm_flatread  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_flatread  mbm_flatread
	#define CHK_CmpCAAMemBlockManmbm_flatread  TRUE
	#define EXP_CmpCAAMemBlockManmbm_flatread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatread", (RTS_UINTPTR)mbm_flatread, 1, RTSITF_GET_SIGNATURE(0, 0x6D388DC6), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_flatread
	#define EXT_mbm_flatread
	#define GET_mbm_flatread(fl)  CAL_CMGETAPI( "mbm_flatread" ) 
	#define CAL_mbm_flatread  mbm_flatread
	#define CHK_mbm_flatread  TRUE
	#define EXP_mbm_flatread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatread", (RTS_UINTPTR)mbm_flatread, 1, RTSITF_GET_SIGNATURE(0, 0x6D388DC6), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_flatread  PFMBM_FLATREAD_IEC pfmbm_flatread;
	#define EXT_mbm_flatread  extern PFMBM_FLATREAD_IEC pfmbm_flatread;
	#define GET_mbm_flatread(fl)  s_pfCMGetAPI2( "mbm_flatread", (RTS_VOID_FCTPTR *)&pfmbm_flatread, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6D388DC6), 0x03050500)
	#define CAL_mbm_flatread  pfmbm_flatread
	#define CHK_mbm_flatread  (pfmbm_flatread != NULL)
	#define EXP_mbm_flatread   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatread", (RTS_UINTPTR)mbm_flatread, 1, RTSITF_GET_SIGNATURE(0, 0x6D388DC6), 0x03050500) 
#endif


/**
 * <description>mbm_flattest</description>
 */
typedef struct tagmbm_flattest_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_IDENT idKey;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_BOOL MBM_FlatTest;				/* VAR_OUTPUT */	/* xEnabled */
} mbm_flattest_struct;

void CDECL CDECL_EXT mbm_flattest(mbm_flattest_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_FLATTEST_IEC) (mbm_flattest_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATTEST_NOTIMPLEMENTED)
	#define USE_mbm_flattest
	#define EXT_mbm_flattest
	#define GET_mbm_flattest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_flattest(p0) 
	#define CHK_mbm_flattest  FALSE
	#define EXP_mbm_flattest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_flattest
	#define EXT_mbm_flattest
	#define GET_mbm_flattest(fl)  CAL_CMGETAPI( "mbm_flattest" ) 
	#define CAL_mbm_flattest  mbm_flattest
	#define CHK_mbm_flattest  TRUE
	#define EXP_mbm_flattest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flattest", (RTS_UINTPTR)mbm_flattest, 1, RTSITF_GET_SIGNATURE(0, 0xFD1FEB32), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_flattest
	#define EXT_mbm_flattest
	#define GET_mbm_flattest(fl)  CAL_CMGETAPI( "mbm_flattest" ) 
	#define CAL_mbm_flattest  mbm_flattest
	#define CHK_mbm_flattest  TRUE
	#define EXP_mbm_flattest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flattest", (RTS_UINTPTR)mbm_flattest, 1, RTSITF_GET_SIGNATURE(0, 0xFD1FEB32), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_flattest
	#define EXT_CmpCAAMemBlockManmbm_flattest
	#define GET_CmpCAAMemBlockManmbm_flattest  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_flattest  mbm_flattest
	#define CHK_CmpCAAMemBlockManmbm_flattest  TRUE
	#define EXP_CmpCAAMemBlockManmbm_flattest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flattest", (RTS_UINTPTR)mbm_flattest, 1, RTSITF_GET_SIGNATURE(0, 0xFD1FEB32), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_flattest
	#define EXT_mbm_flattest
	#define GET_mbm_flattest(fl)  CAL_CMGETAPI( "mbm_flattest" ) 
	#define CAL_mbm_flattest  mbm_flattest
	#define CHK_mbm_flattest  TRUE
	#define EXP_mbm_flattest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flattest", (RTS_UINTPTR)mbm_flattest, 1, RTSITF_GET_SIGNATURE(0, 0xFD1FEB32), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_flattest  PFMBM_FLATTEST_IEC pfmbm_flattest;
	#define EXT_mbm_flattest  extern PFMBM_FLATTEST_IEC pfmbm_flattest;
	#define GET_mbm_flattest(fl)  s_pfCMGetAPI2( "mbm_flattest", (RTS_VOID_FCTPTR *)&pfmbm_flattest, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFD1FEB32), 0x03050500)
	#define CAL_mbm_flattest  pfmbm_flattest
	#define CHK_mbm_flattest  (pfmbm_flattest != NULL)
	#define EXP_mbm_flattest   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flattest", (RTS_UINTPTR)mbm_flattest, 1, RTSITF_GET_SIGNATURE(0, 0xFD1FEB32), 0x03050500) 
#endif


/**
 * <description>mbm_flatupdate</description>
 */
typedef struct tagmbm_flatupdate_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_IDENT idKey;					/* VAR_INPUT */	
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_FlatUpdate;			/* VAR_OUTPUT */	/* hOldMsg */
} mbm_flatupdate_struct;

void CDECL CDECL_EXT mbm_flatupdate(mbm_flatupdate_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_FLATUPDATE_IEC) (mbm_flatupdate_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_FLATUPDATE_NOTIMPLEMENTED)
	#define USE_mbm_flatupdate
	#define EXT_mbm_flatupdate
	#define GET_mbm_flatupdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_flatupdate(p0) 
	#define CHK_mbm_flatupdate  FALSE
	#define EXP_mbm_flatupdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_flatupdate
	#define EXT_mbm_flatupdate
	#define GET_mbm_flatupdate(fl)  CAL_CMGETAPI( "mbm_flatupdate" ) 
	#define CAL_mbm_flatupdate  mbm_flatupdate
	#define CHK_mbm_flatupdate  TRUE
	#define EXP_mbm_flatupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatupdate", (RTS_UINTPTR)mbm_flatupdate, 1, RTSITF_GET_SIGNATURE(0, 0xFDEEDB01), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_flatupdate
	#define EXT_mbm_flatupdate
	#define GET_mbm_flatupdate(fl)  CAL_CMGETAPI( "mbm_flatupdate" ) 
	#define CAL_mbm_flatupdate  mbm_flatupdate
	#define CHK_mbm_flatupdate  TRUE
	#define EXP_mbm_flatupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatupdate", (RTS_UINTPTR)mbm_flatupdate, 1, RTSITF_GET_SIGNATURE(0, 0xFDEEDB01), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_flatupdate
	#define EXT_CmpCAAMemBlockManmbm_flatupdate
	#define GET_CmpCAAMemBlockManmbm_flatupdate  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_flatupdate  mbm_flatupdate
	#define CHK_CmpCAAMemBlockManmbm_flatupdate  TRUE
	#define EXP_CmpCAAMemBlockManmbm_flatupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatupdate", (RTS_UINTPTR)mbm_flatupdate, 1, RTSITF_GET_SIGNATURE(0, 0xFDEEDB01), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_flatupdate
	#define EXT_mbm_flatupdate
	#define GET_mbm_flatupdate(fl)  CAL_CMGETAPI( "mbm_flatupdate" ) 
	#define CAL_mbm_flatupdate  mbm_flatupdate
	#define CHK_mbm_flatupdate  TRUE
	#define EXP_mbm_flatupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatupdate", (RTS_UINTPTR)mbm_flatupdate, 1, RTSITF_GET_SIGNATURE(0, 0xFDEEDB01), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_flatupdate  PFMBM_FLATUPDATE_IEC pfmbm_flatupdate;
	#define EXT_mbm_flatupdate  extern PFMBM_FLATUPDATE_IEC pfmbm_flatupdate;
	#define GET_mbm_flatupdate(fl)  s_pfCMGetAPI2( "mbm_flatupdate", (RTS_VOID_FCTPTR *)&pfmbm_flatupdate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFDEEDB01), 0x03050500)
	#define CAL_mbm_flatupdate  pfmbm_flatupdate
	#define CHK_mbm_flatupdate  (pfmbm_flatupdate != NULL)
	#define EXP_mbm_flatupdate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_flatupdate", (RTS_UINTPTR)mbm_flatupdate, 1, RTSITF_GET_SIGNATURE(0, 0xFDEEDB01), 0x03050500) 
#endif


/**
 * Add a reference, to this message 
 */
typedef struct tagmbm_msgaddref_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_ERROR MBM_MsgAddRef;			/* VAR_OUTPUT */	
} mbm_msgaddref_struct;

void CDECL CDECL_EXT mbm_msgaddref(mbm_msgaddref_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_MSGADDREF_IEC) (mbm_msgaddref_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGADDREF_NOTIMPLEMENTED)
	#define USE_mbm_msgaddref
	#define EXT_mbm_msgaddref
	#define GET_mbm_msgaddref(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_msgaddref(p0) 
	#define CHK_mbm_msgaddref  FALSE
	#define EXP_mbm_msgaddref  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_msgaddref
	#define EXT_mbm_msgaddref
	#define GET_mbm_msgaddref(fl)  CAL_CMGETAPI( "mbm_msgaddref" ) 
	#define CAL_mbm_msgaddref  mbm_msgaddref
	#define CHK_mbm_msgaddref  TRUE
	#define EXP_mbm_msgaddref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgaddref", (RTS_UINTPTR)mbm_msgaddref, 1, RTSITF_GET_SIGNATURE(0, 0x7BF62E5D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_msgaddref
	#define EXT_mbm_msgaddref
	#define GET_mbm_msgaddref(fl)  CAL_CMGETAPI( "mbm_msgaddref" ) 
	#define CAL_mbm_msgaddref  mbm_msgaddref
	#define CHK_mbm_msgaddref  TRUE
	#define EXP_mbm_msgaddref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgaddref", (RTS_UINTPTR)mbm_msgaddref, 1, RTSITF_GET_SIGNATURE(0, 0x7BF62E5D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_msgaddref
	#define EXT_CmpCAAMemBlockManmbm_msgaddref
	#define GET_CmpCAAMemBlockManmbm_msgaddref  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_msgaddref  mbm_msgaddref
	#define CHK_CmpCAAMemBlockManmbm_msgaddref  TRUE
	#define EXP_CmpCAAMemBlockManmbm_msgaddref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgaddref", (RTS_UINTPTR)mbm_msgaddref, 1, RTSITF_GET_SIGNATURE(0, 0x7BF62E5D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_msgaddref
	#define EXT_mbm_msgaddref
	#define GET_mbm_msgaddref(fl)  CAL_CMGETAPI( "mbm_msgaddref" ) 
	#define CAL_mbm_msgaddref  mbm_msgaddref
	#define CHK_mbm_msgaddref  TRUE
	#define EXP_mbm_msgaddref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgaddref", (RTS_UINTPTR)mbm_msgaddref, 1, RTSITF_GET_SIGNATURE(0, 0x7BF62E5D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_msgaddref  PFMBM_MSGADDREF_IEC pfmbm_msgaddref;
	#define EXT_mbm_msgaddref  extern PFMBM_MSGADDREF_IEC pfmbm_msgaddref;
	#define GET_mbm_msgaddref(fl)  s_pfCMGetAPI2( "mbm_msgaddref", (RTS_VOID_FCTPTR *)&pfmbm_msgaddref, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7BF62E5D), 0x03050500)
	#define CAL_mbm_msgaddref  pfmbm_msgaddref
	#define CHK_mbm_msgaddref  (pfmbm_msgaddref != NULL)
	#define EXP_mbm_msgaddref   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgaddref", (RTS_UINTPTR)mbm_msgaddref, 1, RTSITF_GET_SIGNATURE(0, 0x7BF62E5D), 0x03050500) 
#endif


/**
 * <description>mbm_msgclone</description>
 */
typedef struct tagmbm_msgclone_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_MsgClone;			/* VAR_OUTPUT */	
} mbm_msgclone_struct;

void CDECL CDECL_EXT mbm_msgclone(mbm_msgclone_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_MSGCLONE_IEC) (mbm_msgclone_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGCLONE_NOTIMPLEMENTED)
	#define USE_mbm_msgclone
	#define EXT_mbm_msgclone
	#define GET_mbm_msgclone(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_msgclone(p0) 
	#define CHK_mbm_msgclone  FALSE
	#define EXP_mbm_msgclone  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_msgclone
	#define EXT_mbm_msgclone
	#define GET_mbm_msgclone(fl)  CAL_CMGETAPI( "mbm_msgclone" ) 
	#define CAL_mbm_msgclone  mbm_msgclone
	#define CHK_mbm_msgclone  TRUE
	#define EXP_mbm_msgclone  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgclone", (RTS_UINTPTR)mbm_msgclone, 1, RTSITF_GET_SIGNATURE(0, 0x7F73045D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_msgclone
	#define EXT_mbm_msgclone
	#define GET_mbm_msgclone(fl)  CAL_CMGETAPI( "mbm_msgclone" ) 
	#define CAL_mbm_msgclone  mbm_msgclone
	#define CHK_mbm_msgclone  TRUE
	#define EXP_mbm_msgclone  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgclone", (RTS_UINTPTR)mbm_msgclone, 1, RTSITF_GET_SIGNATURE(0, 0x7F73045D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_msgclone
	#define EXT_CmpCAAMemBlockManmbm_msgclone
	#define GET_CmpCAAMemBlockManmbm_msgclone  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_msgclone  mbm_msgclone
	#define CHK_CmpCAAMemBlockManmbm_msgclone  TRUE
	#define EXP_CmpCAAMemBlockManmbm_msgclone  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgclone", (RTS_UINTPTR)mbm_msgclone, 1, RTSITF_GET_SIGNATURE(0, 0x7F73045D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_msgclone
	#define EXT_mbm_msgclone
	#define GET_mbm_msgclone(fl)  CAL_CMGETAPI( "mbm_msgclone" ) 
	#define CAL_mbm_msgclone  mbm_msgclone
	#define CHK_mbm_msgclone  TRUE
	#define EXP_mbm_msgclone  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgclone", (RTS_UINTPTR)mbm_msgclone, 1, RTSITF_GET_SIGNATURE(0, 0x7F73045D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_msgclone  PFMBM_MSGCLONE_IEC pfmbm_msgclone;
	#define EXT_mbm_msgclone  extern PFMBM_MSGCLONE_IEC pfmbm_msgclone;
	#define GET_mbm_msgclone(fl)  s_pfCMGetAPI2( "mbm_msgclone", (RTS_VOID_FCTPTR *)&pfmbm_msgclone, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7F73045D), 0x03050500)
	#define CAL_mbm_msgclone  pfmbm_msgclone
	#define CHK_mbm_msgclone  (pfmbm_msgclone != NULL)
	#define EXP_mbm_msgclone   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgclone", (RTS_UINTPTR)mbm_msgclone, 1, RTSITF_GET_SIGNATURE(0, 0x7F73045D), 0x03050500) 
#endif


/**
 * <description>mbm_msggetdata</description>
 */
typedef struct tagmbm_msggetdata_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_PVOID MBM_MsgGetData;			/* VAR_OUTPUT */	
} mbm_msggetdata_struct;

void CDECL CDECL_EXT mbm_msggetdata(mbm_msggetdata_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_MSGGETDATA_IEC) (mbm_msggetdata_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGGETDATA_NOTIMPLEMENTED)
	#define USE_mbm_msggetdata
	#define EXT_mbm_msggetdata
	#define GET_mbm_msggetdata(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_msggetdata(p0) 
	#define CHK_mbm_msggetdata  FALSE
	#define EXP_mbm_msggetdata  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_msggetdata
	#define EXT_mbm_msggetdata
	#define GET_mbm_msggetdata(fl)  CAL_CMGETAPI( "mbm_msggetdata" ) 
	#define CAL_mbm_msggetdata  mbm_msggetdata
	#define CHK_mbm_msggetdata  TRUE
	#define EXP_mbm_msggetdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msggetdata", (RTS_UINTPTR)mbm_msggetdata, 1, RTSITF_GET_SIGNATURE(0, 0x6B8C9A39), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_msggetdata
	#define EXT_mbm_msggetdata
	#define GET_mbm_msggetdata(fl)  CAL_CMGETAPI( "mbm_msggetdata" ) 
	#define CAL_mbm_msggetdata  mbm_msggetdata
	#define CHK_mbm_msggetdata  TRUE
	#define EXP_mbm_msggetdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msggetdata", (RTS_UINTPTR)mbm_msggetdata, 1, RTSITF_GET_SIGNATURE(0, 0x6B8C9A39), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_msggetdata
	#define EXT_CmpCAAMemBlockManmbm_msggetdata
	#define GET_CmpCAAMemBlockManmbm_msggetdata  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_msggetdata  mbm_msggetdata
	#define CHK_CmpCAAMemBlockManmbm_msggetdata  TRUE
	#define EXP_CmpCAAMemBlockManmbm_msggetdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msggetdata", (RTS_UINTPTR)mbm_msggetdata, 1, RTSITF_GET_SIGNATURE(0, 0x6B8C9A39), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_msggetdata
	#define EXT_mbm_msggetdata
	#define GET_mbm_msggetdata(fl)  CAL_CMGETAPI( "mbm_msggetdata" ) 
	#define CAL_mbm_msggetdata  mbm_msggetdata
	#define CHK_mbm_msggetdata  TRUE
	#define EXP_mbm_msggetdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msggetdata", (RTS_UINTPTR)mbm_msggetdata, 1, RTSITF_GET_SIGNATURE(0, 0x6B8C9A39), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_msggetdata  PFMBM_MSGGETDATA_IEC pfmbm_msggetdata;
	#define EXT_mbm_msggetdata  extern PFMBM_MSGGETDATA_IEC pfmbm_msggetdata;
	#define GET_mbm_msggetdata(fl)  s_pfCMGetAPI2( "mbm_msggetdata", (RTS_VOID_FCTPTR *)&pfmbm_msggetdata, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6B8C9A39), 0x03050500)
	#define CAL_mbm_msggetdata  pfmbm_msggetdata
	#define CHK_mbm_msggetdata  (pfmbm_msggetdata != NULL)
	#define EXP_mbm_msggetdata   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msggetdata", (RTS_UINTPTR)mbm_msggetdata, 1, RTSITF_GET_SIGNATURE(0, 0x6B8C9A39), 0x03050500) 
#endif


/**
 * Gets a message from hXChg 
 */
typedef struct tagmbm_msgreceive_struct
{
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_COUNT *pctMsgLeft;				/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_MsgReceive;			/* VAR_OUTPUT */	
} mbm_msgreceive_struct;

void CDECL CDECL_EXT mbm_msgreceive(mbm_msgreceive_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_MSGRECEIVE_IEC) (mbm_msgreceive_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGRECEIVE_NOTIMPLEMENTED)
	#define USE_mbm_msgreceive
	#define EXT_mbm_msgreceive
	#define GET_mbm_msgreceive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_msgreceive(p0) 
	#define CHK_mbm_msgreceive  FALSE
	#define EXP_mbm_msgreceive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_msgreceive
	#define EXT_mbm_msgreceive
	#define GET_mbm_msgreceive(fl)  CAL_CMGETAPI( "mbm_msgreceive" ) 
	#define CAL_mbm_msgreceive  mbm_msgreceive
	#define CHK_mbm_msgreceive  TRUE
	#define EXP_mbm_msgreceive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgreceive", (RTS_UINTPTR)mbm_msgreceive, 1, RTSITF_GET_SIGNATURE(0, 0x4387638B), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_msgreceive
	#define EXT_mbm_msgreceive
	#define GET_mbm_msgreceive(fl)  CAL_CMGETAPI( "mbm_msgreceive" ) 
	#define CAL_mbm_msgreceive  mbm_msgreceive
	#define CHK_mbm_msgreceive  TRUE
	#define EXP_mbm_msgreceive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgreceive", (RTS_UINTPTR)mbm_msgreceive, 1, RTSITF_GET_SIGNATURE(0, 0x4387638B), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_msgreceive
	#define EXT_CmpCAAMemBlockManmbm_msgreceive
	#define GET_CmpCAAMemBlockManmbm_msgreceive  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_msgreceive  mbm_msgreceive
	#define CHK_CmpCAAMemBlockManmbm_msgreceive  TRUE
	#define EXP_CmpCAAMemBlockManmbm_msgreceive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgreceive", (RTS_UINTPTR)mbm_msgreceive, 1, RTSITF_GET_SIGNATURE(0, 0x4387638B), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_msgreceive
	#define EXT_mbm_msgreceive
	#define GET_mbm_msgreceive(fl)  CAL_CMGETAPI( "mbm_msgreceive" ) 
	#define CAL_mbm_msgreceive  mbm_msgreceive
	#define CHK_mbm_msgreceive  TRUE
	#define EXP_mbm_msgreceive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgreceive", (RTS_UINTPTR)mbm_msgreceive, 1, RTSITF_GET_SIGNATURE(0, 0x4387638B), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_msgreceive  PFMBM_MSGRECEIVE_IEC pfmbm_msgreceive;
	#define EXT_mbm_msgreceive  extern PFMBM_MSGRECEIVE_IEC pfmbm_msgreceive;
	#define GET_mbm_msgreceive(fl)  s_pfCMGetAPI2( "mbm_msgreceive", (RTS_VOID_FCTPTR *)&pfmbm_msgreceive, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4387638B), 0x03050500)
	#define CAL_mbm_msgreceive  pfmbm_msgreceive
	#define CHK_mbm_msgreceive  (pfmbm_msgreceive != NULL)
	#define EXP_mbm_msgreceive   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgreceive", (RTS_UINTPTR)mbm_msgreceive, 1, RTSITF_GET_SIGNATURE(0, 0x4387638B), 0x03050500) 
#endif


/**
 * If this message has the last reference, then Send it back to its ResourceExchange 
 */
typedef struct tagmbm_msgrelease_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_ERROR MBM_MsgRelease;			/* VAR_OUTPUT */	
} mbm_msgrelease_struct;

void CDECL CDECL_EXT mbm_msgrelease(mbm_msgrelease_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_MSGRELEASE_IEC) (mbm_msgrelease_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGRELEASE_NOTIMPLEMENTED)
	#define USE_mbm_msgrelease
	#define EXT_mbm_msgrelease
	#define GET_mbm_msgrelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_msgrelease(p0) 
	#define CHK_mbm_msgrelease  FALSE
	#define EXP_mbm_msgrelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_msgrelease
	#define EXT_mbm_msgrelease
	#define GET_mbm_msgrelease(fl)  CAL_CMGETAPI( "mbm_msgrelease" ) 
	#define CAL_mbm_msgrelease  mbm_msgrelease
	#define CHK_mbm_msgrelease  TRUE
	#define EXP_mbm_msgrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgrelease", (RTS_UINTPTR)mbm_msgrelease, 1, RTSITF_GET_SIGNATURE(0, 0x6D55A0C0), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_msgrelease
	#define EXT_mbm_msgrelease
	#define GET_mbm_msgrelease(fl)  CAL_CMGETAPI( "mbm_msgrelease" ) 
	#define CAL_mbm_msgrelease  mbm_msgrelease
	#define CHK_mbm_msgrelease  TRUE
	#define EXP_mbm_msgrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgrelease", (RTS_UINTPTR)mbm_msgrelease, 1, RTSITF_GET_SIGNATURE(0, 0x6D55A0C0), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_msgrelease
	#define EXT_CmpCAAMemBlockManmbm_msgrelease
	#define GET_CmpCAAMemBlockManmbm_msgrelease  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_msgrelease  mbm_msgrelease
	#define CHK_CmpCAAMemBlockManmbm_msgrelease  TRUE
	#define EXP_CmpCAAMemBlockManmbm_msgrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgrelease", (RTS_UINTPTR)mbm_msgrelease, 1, RTSITF_GET_SIGNATURE(0, 0x6D55A0C0), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_msgrelease
	#define EXT_mbm_msgrelease
	#define GET_mbm_msgrelease(fl)  CAL_CMGETAPI( "mbm_msgrelease" ) 
	#define CAL_mbm_msgrelease  mbm_msgrelease
	#define CHK_mbm_msgrelease  TRUE
	#define EXP_mbm_msgrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgrelease", (RTS_UINTPTR)mbm_msgrelease, 1, RTSITF_GET_SIGNATURE(0, 0x6D55A0C0), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_msgrelease  PFMBM_MSGRELEASE_IEC pfmbm_msgrelease;
	#define EXT_mbm_msgrelease  extern PFMBM_MSGRELEASE_IEC pfmbm_msgrelease;
	#define GET_mbm_msgrelease(fl)  s_pfCMGetAPI2( "mbm_msgrelease", (RTS_VOID_FCTPTR *)&pfmbm_msgrelease, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6D55A0C0), 0x03050500)
	#define CAL_mbm_msgrelease  pfmbm_msgrelease
	#define CHK_mbm_msgrelease  (pfmbm_msgrelease != NULL)
	#define EXP_mbm_msgrelease   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgrelease", (RTS_UINTPTR)mbm_msgrelease, 1, RTSITF_GET_SIGNATURE(0, 0x6D55A0C0), 0x03050500) 
#endif


/**
 * If this message has the last reference, then Send it back to hXchg 
 */
typedef struct tagmbm_msgreleaseex_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_ERROR MBM_MsgReleaseEx;			/* VAR_OUTPUT */	
} mbm_msgreleaseex_struct;

void CDECL CDECL_EXT mbm_msgreleaseex(mbm_msgreleaseex_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_MSGRELEASEEX_IEC) (mbm_msgreleaseex_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGRELEASEEX_NOTIMPLEMENTED)
	#define USE_mbm_msgreleaseex
	#define EXT_mbm_msgreleaseex
	#define GET_mbm_msgreleaseex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_msgreleaseex(p0) 
	#define CHK_mbm_msgreleaseex  FALSE
	#define EXP_mbm_msgreleaseex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_msgreleaseex
	#define EXT_mbm_msgreleaseex
	#define GET_mbm_msgreleaseex(fl)  CAL_CMGETAPI( "mbm_msgreleaseex" ) 
	#define CAL_mbm_msgreleaseex  mbm_msgreleaseex
	#define CHK_mbm_msgreleaseex  TRUE
	#define EXP_mbm_msgreleaseex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgreleaseex", (RTS_UINTPTR)mbm_msgreleaseex, 1, RTSITF_GET_SIGNATURE(0, 0xD41DCC1F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_msgreleaseex
	#define EXT_mbm_msgreleaseex
	#define GET_mbm_msgreleaseex(fl)  CAL_CMGETAPI( "mbm_msgreleaseex" ) 
	#define CAL_mbm_msgreleaseex  mbm_msgreleaseex
	#define CHK_mbm_msgreleaseex  TRUE
	#define EXP_mbm_msgreleaseex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgreleaseex", (RTS_UINTPTR)mbm_msgreleaseex, 1, RTSITF_GET_SIGNATURE(0, 0xD41DCC1F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_msgreleaseex
	#define EXT_CmpCAAMemBlockManmbm_msgreleaseex
	#define GET_CmpCAAMemBlockManmbm_msgreleaseex  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_msgreleaseex  mbm_msgreleaseex
	#define CHK_CmpCAAMemBlockManmbm_msgreleaseex  TRUE
	#define EXP_CmpCAAMemBlockManmbm_msgreleaseex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgreleaseex", (RTS_UINTPTR)mbm_msgreleaseex, 1, RTSITF_GET_SIGNATURE(0, 0xD41DCC1F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_msgreleaseex
	#define EXT_mbm_msgreleaseex
	#define GET_mbm_msgreleaseex(fl)  CAL_CMGETAPI( "mbm_msgreleaseex" ) 
	#define CAL_mbm_msgreleaseex  mbm_msgreleaseex
	#define CHK_mbm_msgreleaseex  TRUE
	#define EXP_mbm_msgreleaseex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgreleaseex", (RTS_UINTPTR)mbm_msgreleaseex, 1, RTSITF_GET_SIGNATURE(0, 0xD41DCC1F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_msgreleaseex  PFMBM_MSGRELEASEEX_IEC pfmbm_msgreleaseex;
	#define EXT_mbm_msgreleaseex  extern PFMBM_MSGRELEASEEX_IEC pfmbm_msgreleaseex;
	#define GET_mbm_msgreleaseex(fl)  s_pfCMGetAPI2( "mbm_msgreleaseex", (RTS_VOID_FCTPTR *)&pfmbm_msgreleaseex, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD41DCC1F), 0x03050500)
	#define CAL_mbm_msgreleaseex  pfmbm_msgreleaseex
	#define CHK_mbm_msgreleaseex  (pfmbm_msgreleaseex != NULL)
	#define EXP_mbm_msgreleaseex   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgreleaseex", (RTS_UINTPTR)mbm_msgreleaseex, 1, RTSITF_GET_SIGNATURE(0, 0xD41DCC1F), 0x03050500) 
#endif


/**
 * <description>mbm_msgsend</description>
 */
typedef struct tagmbm_msgsend_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	RTS_IEC_USINT usiPrio;				/* VAR_INPUT */	
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_ERROR MBM_MsgSend;				/* VAR_OUTPUT */	
} mbm_msgsend_struct;

void CDECL CDECL_EXT mbm_msgsend(mbm_msgsend_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_MSGSEND_IEC) (mbm_msgsend_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_MSGSEND_NOTIMPLEMENTED)
	#define USE_mbm_msgsend
	#define EXT_mbm_msgsend
	#define GET_mbm_msgsend(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_msgsend(p0) 
	#define CHK_mbm_msgsend  FALSE
	#define EXP_mbm_msgsend  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_msgsend
	#define EXT_mbm_msgsend
	#define GET_mbm_msgsend(fl)  CAL_CMGETAPI( "mbm_msgsend" ) 
	#define CAL_mbm_msgsend  mbm_msgsend
	#define CHK_mbm_msgsend  TRUE
	#define EXP_mbm_msgsend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgsend", (RTS_UINTPTR)mbm_msgsend, 1, RTSITF_GET_SIGNATURE(0, 0xA4201973), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_msgsend
	#define EXT_mbm_msgsend
	#define GET_mbm_msgsend(fl)  CAL_CMGETAPI( "mbm_msgsend" ) 
	#define CAL_mbm_msgsend  mbm_msgsend
	#define CHK_mbm_msgsend  TRUE
	#define EXP_mbm_msgsend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgsend", (RTS_UINTPTR)mbm_msgsend, 1, RTSITF_GET_SIGNATURE(0, 0xA4201973), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_msgsend
	#define EXT_CmpCAAMemBlockManmbm_msgsend
	#define GET_CmpCAAMemBlockManmbm_msgsend  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_msgsend  mbm_msgsend
	#define CHK_CmpCAAMemBlockManmbm_msgsend  TRUE
	#define EXP_CmpCAAMemBlockManmbm_msgsend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgsend", (RTS_UINTPTR)mbm_msgsend, 1, RTSITF_GET_SIGNATURE(0, 0xA4201973), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_msgsend
	#define EXT_mbm_msgsend
	#define GET_mbm_msgsend(fl)  CAL_CMGETAPI( "mbm_msgsend" ) 
	#define CAL_mbm_msgsend  mbm_msgsend
	#define CHK_mbm_msgsend  TRUE
	#define EXP_mbm_msgsend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgsend", (RTS_UINTPTR)mbm_msgsend, 1, RTSITF_GET_SIGNATURE(0, 0xA4201973), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_msgsend  PFMBM_MSGSEND_IEC pfmbm_msgsend;
	#define EXT_mbm_msgsend  extern PFMBM_MSGSEND_IEC pfmbm_msgsend;
	#define GET_mbm_msgsend(fl)  s_pfCMGetAPI2( "mbm_msgsend", (RTS_VOID_FCTPTR *)&pfmbm_msgsend, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA4201973), 0x03050500)
	#define CAL_mbm_msgsend  pfmbm_msgsend
	#define CHK_mbm_msgsend  (pfmbm_msgsend != NULL)
	#define EXP_mbm_msgsend   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_msgsend", (RTS_UINTPTR)mbm_msgsend, 1, RTSITF_GET_SIGNATURE(0, 0xA4201973), 0x03050500) 
#endif


/**
 * Take a pool of ctNumBlocks * szBlockSize bytes from the Heap(OS) and build a block pool 
 */
typedef struct tagmbm_poolcreateh_struct
{
	CAA_COUNT ctNumBlocks;				/* VAR_INPUT */	
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_ENUM eEmpty;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_PoolCreateH;			/* VAR_OUTPUT */	/* hPool */
} mbm_poolcreateh_struct;

void CDECL CDECL_EXT mbm_poolcreateh(mbm_poolcreateh_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_POOLCREATEH_IEC) (mbm_poolcreateh_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLCREATEH_NOTIMPLEMENTED)
	#define USE_mbm_poolcreateh
	#define EXT_mbm_poolcreateh
	#define GET_mbm_poolcreateh(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_poolcreateh(p0) 
	#define CHK_mbm_poolcreateh  FALSE
	#define EXP_mbm_poolcreateh  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_poolcreateh
	#define EXT_mbm_poolcreateh
	#define GET_mbm_poolcreateh(fl)  CAL_CMGETAPI( "mbm_poolcreateh" ) 
	#define CAL_mbm_poolcreateh  mbm_poolcreateh
	#define CHK_mbm_poolcreateh  TRUE
	#define EXP_mbm_poolcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolcreateh", (RTS_UINTPTR)mbm_poolcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x5DCA1021), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_poolcreateh
	#define EXT_mbm_poolcreateh
	#define GET_mbm_poolcreateh(fl)  CAL_CMGETAPI( "mbm_poolcreateh" ) 
	#define CAL_mbm_poolcreateh  mbm_poolcreateh
	#define CHK_mbm_poolcreateh  TRUE
	#define EXP_mbm_poolcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolcreateh", (RTS_UINTPTR)mbm_poolcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x5DCA1021), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_poolcreateh
	#define EXT_CmpCAAMemBlockManmbm_poolcreateh
	#define GET_CmpCAAMemBlockManmbm_poolcreateh  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_poolcreateh  mbm_poolcreateh
	#define CHK_CmpCAAMemBlockManmbm_poolcreateh  TRUE
	#define EXP_CmpCAAMemBlockManmbm_poolcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolcreateh", (RTS_UINTPTR)mbm_poolcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x5DCA1021), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_poolcreateh
	#define EXT_mbm_poolcreateh
	#define GET_mbm_poolcreateh(fl)  CAL_CMGETAPI( "mbm_poolcreateh" ) 
	#define CAL_mbm_poolcreateh  mbm_poolcreateh
	#define CHK_mbm_poolcreateh  TRUE
	#define EXP_mbm_poolcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolcreateh", (RTS_UINTPTR)mbm_poolcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x5DCA1021), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_poolcreateh  PFMBM_POOLCREATEH_IEC pfmbm_poolcreateh;
	#define EXT_mbm_poolcreateh  extern PFMBM_POOLCREATEH_IEC pfmbm_poolcreateh;
	#define GET_mbm_poolcreateh(fl)  s_pfCMGetAPI2( "mbm_poolcreateh", (RTS_VOID_FCTPTR *)&pfmbm_poolcreateh, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5DCA1021), 0x03050500)
	#define CAL_mbm_poolcreateh  pfmbm_poolcreateh
	#define CHK_mbm_poolcreateh  (pfmbm_poolcreateh != NULL)
	#define EXP_mbm_poolcreateh   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolcreateh", (RTS_UINTPTR)mbm_poolcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x5DCA1021), 0x03050500) 
#endif


/**
 * Take as much as possible block of szBlockSize bytes from a PLC(IEC) provided memory and build a block pool 
 */
typedef struct tagmbm_poolcreatep_struct
{
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_SIZE szMemSize;					/* VAR_INPUT */	
	CAA_PVOID pMemory;					/* VAR_INPUT */	
	CAA_ENUM eEmpty;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_PoolCreateP;			/* VAR_OUTPUT */	
} mbm_poolcreatep_struct;

void CDECL CDECL_EXT mbm_poolcreatep(mbm_poolcreatep_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_POOLCREATEP_IEC) (mbm_poolcreatep_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLCREATEP_NOTIMPLEMENTED)
	#define USE_mbm_poolcreatep
	#define EXT_mbm_poolcreatep
	#define GET_mbm_poolcreatep(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_poolcreatep(p0) 
	#define CHK_mbm_poolcreatep  FALSE
	#define EXP_mbm_poolcreatep  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_poolcreatep
	#define EXT_mbm_poolcreatep
	#define GET_mbm_poolcreatep(fl)  CAL_CMGETAPI( "mbm_poolcreatep" ) 
	#define CAL_mbm_poolcreatep  mbm_poolcreatep
	#define CHK_mbm_poolcreatep  TRUE
	#define EXP_mbm_poolcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolcreatep", (RTS_UINTPTR)mbm_poolcreatep, 1, 0, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_poolcreatep
	#define EXT_mbm_poolcreatep
	#define GET_mbm_poolcreatep(fl)  CAL_CMGETAPI( "mbm_poolcreatep" ) 
	#define CAL_mbm_poolcreatep  mbm_poolcreatep
	#define CHK_mbm_poolcreatep  TRUE
	#define EXP_mbm_poolcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolcreatep", (RTS_UINTPTR)mbm_poolcreatep, 1, 0, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_poolcreatep
	#define EXT_CmpCAAMemBlockManmbm_poolcreatep
	#define GET_CmpCAAMemBlockManmbm_poolcreatep  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_poolcreatep  mbm_poolcreatep
	#define CHK_CmpCAAMemBlockManmbm_poolcreatep  TRUE
	#define EXP_CmpCAAMemBlockManmbm_poolcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolcreatep", (RTS_UINTPTR)mbm_poolcreatep, 1, 0, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_poolcreatep
	#define EXT_mbm_poolcreatep
	#define GET_mbm_poolcreatep(fl)  CAL_CMGETAPI( "mbm_poolcreatep" ) 
	#define CAL_mbm_poolcreatep  mbm_poolcreatep
	#define CHK_mbm_poolcreatep  TRUE
	#define EXP_mbm_poolcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolcreatep", (RTS_UINTPTR)mbm_poolcreatep, 1, 0, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_poolcreatep  PFMBM_POOLCREATEP_IEC pfmbm_poolcreatep;
	#define EXT_mbm_poolcreatep  extern PFMBM_POOLCREATEP_IEC pfmbm_poolcreatep;
	#define GET_mbm_poolcreatep(fl)  s_pfCMGetAPI2( "mbm_poolcreatep", (RTS_VOID_FCTPTR *)&pfmbm_poolcreatep, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050500)
	#define CAL_mbm_poolcreatep  pfmbm_poolcreatep
	#define CHK_mbm_poolcreatep  (pfmbm_poolcreatep != NULL)
	#define EXP_mbm_poolcreatep   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolcreatep", (RTS_UINTPTR)mbm_poolcreatep, 1, 0, 0x03050500) 
#endif


/**
 * Deletes a block pool created by PoolCreateX provided that all blocks are free 
 * If a block is in use, this call aborts 
 */
typedef struct tagmbm_pooldelete_struct
{
	CAA_HANDLE hPool;					/* VAR_INPUT */	
	CAA_ERROR MBM_PoolDelete;			/* VAR_OUTPUT */	
} mbm_pooldelete_struct;

void CDECL CDECL_EXT mbm_pooldelete(mbm_pooldelete_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_POOLDELETE_IEC) (mbm_pooldelete_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLDELETE_NOTIMPLEMENTED)
	#define USE_mbm_pooldelete
	#define EXT_mbm_pooldelete
	#define GET_mbm_pooldelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_pooldelete(p0) 
	#define CHK_mbm_pooldelete  FALSE
	#define EXP_mbm_pooldelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_pooldelete
	#define EXT_mbm_pooldelete
	#define GET_mbm_pooldelete(fl)  CAL_CMGETAPI( "mbm_pooldelete" ) 
	#define CAL_mbm_pooldelete  mbm_pooldelete
	#define CHK_mbm_pooldelete  TRUE
	#define EXP_mbm_pooldelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_pooldelete", (RTS_UINTPTR)mbm_pooldelete, 1, RTSITF_GET_SIGNATURE(0, 0x98572907), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_pooldelete
	#define EXT_mbm_pooldelete
	#define GET_mbm_pooldelete(fl)  CAL_CMGETAPI( "mbm_pooldelete" ) 
	#define CAL_mbm_pooldelete  mbm_pooldelete
	#define CHK_mbm_pooldelete  TRUE
	#define EXP_mbm_pooldelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_pooldelete", (RTS_UINTPTR)mbm_pooldelete, 1, RTSITF_GET_SIGNATURE(0, 0x98572907), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_pooldelete
	#define EXT_CmpCAAMemBlockManmbm_pooldelete
	#define GET_CmpCAAMemBlockManmbm_pooldelete  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_pooldelete  mbm_pooldelete
	#define CHK_CmpCAAMemBlockManmbm_pooldelete  TRUE
	#define EXP_CmpCAAMemBlockManmbm_pooldelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_pooldelete", (RTS_UINTPTR)mbm_pooldelete, 1, RTSITF_GET_SIGNATURE(0, 0x98572907), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_pooldelete
	#define EXT_mbm_pooldelete
	#define GET_mbm_pooldelete(fl)  CAL_CMGETAPI( "mbm_pooldelete" ) 
	#define CAL_mbm_pooldelete  mbm_pooldelete
	#define CHK_mbm_pooldelete  TRUE
	#define EXP_mbm_pooldelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_pooldelete", (RTS_UINTPTR)mbm_pooldelete, 1, RTSITF_GET_SIGNATURE(0, 0x98572907), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_pooldelete  PFMBM_POOLDELETE_IEC pfmbm_pooldelete;
	#define EXT_mbm_pooldelete  extern PFMBM_POOLDELETE_IEC pfmbm_pooldelete;
	#define GET_mbm_pooldelete(fl)  s_pfCMGetAPI2( "mbm_pooldelete", (RTS_VOID_FCTPTR *)&pfmbm_pooldelete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x98572907), 0x03050500)
	#define CAL_mbm_pooldelete  pfmbm_pooldelete
	#define CHK_mbm_pooldelete  (pfmbm_pooldelete != NULL)
	#define EXP_mbm_pooldelete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_pooldelete", (RTS_UINTPTR)mbm_pooldelete, 1, RTSITF_GET_SIGNATURE(0, 0x98572907), 0x03050500) 
#endif


/**
 * <description>mbm_poolextendh</description>
 */
typedef struct tagmbm_poolextendh_struct
{
	CAA_HANDLE hPool;					/* VAR_INPUT */	
	CAA_COUNT ctNumBlocks;				/* VAR_INPUT */	
	CAA_ERROR MBM_PoolExtendH;			/* VAR_OUTPUT */	
} mbm_poolextendh_struct;

void CDECL CDECL_EXT mbm_poolextendh(mbm_poolextendh_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_POOLEXTENDH_IEC) (mbm_poolextendh_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLEXTENDH_NOTIMPLEMENTED)
	#define USE_mbm_poolextendh
	#define EXT_mbm_poolextendh
	#define GET_mbm_poolextendh(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_poolextendh(p0) 
	#define CHK_mbm_poolextendh  FALSE
	#define EXP_mbm_poolextendh  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_poolextendh
	#define EXT_mbm_poolextendh
	#define GET_mbm_poolextendh(fl)  CAL_CMGETAPI( "mbm_poolextendh" ) 
	#define CAL_mbm_poolextendh  mbm_poolextendh
	#define CHK_mbm_poolextendh  TRUE
	#define EXP_mbm_poolextendh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolextendh", (RTS_UINTPTR)mbm_poolextendh, 1, RTSITF_GET_SIGNATURE(0, 0x9C00A6F0), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_poolextendh
	#define EXT_mbm_poolextendh
	#define GET_mbm_poolextendh(fl)  CAL_CMGETAPI( "mbm_poolextendh" ) 
	#define CAL_mbm_poolextendh  mbm_poolextendh
	#define CHK_mbm_poolextendh  TRUE
	#define EXP_mbm_poolextendh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolextendh", (RTS_UINTPTR)mbm_poolextendh, 1, RTSITF_GET_SIGNATURE(0, 0x9C00A6F0), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_poolextendh
	#define EXT_CmpCAAMemBlockManmbm_poolextendh
	#define GET_CmpCAAMemBlockManmbm_poolextendh  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_poolextendh  mbm_poolextendh
	#define CHK_CmpCAAMemBlockManmbm_poolextendh  TRUE
	#define EXP_CmpCAAMemBlockManmbm_poolextendh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolextendh", (RTS_UINTPTR)mbm_poolextendh, 1, RTSITF_GET_SIGNATURE(0, 0x9C00A6F0), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_poolextendh
	#define EXT_mbm_poolextendh
	#define GET_mbm_poolextendh(fl)  CAL_CMGETAPI( "mbm_poolextendh" ) 
	#define CAL_mbm_poolextendh  mbm_poolextendh
	#define CHK_mbm_poolextendh  TRUE
	#define EXP_mbm_poolextendh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolextendh", (RTS_UINTPTR)mbm_poolextendh, 1, RTSITF_GET_SIGNATURE(0, 0x9C00A6F0), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_poolextendh  PFMBM_POOLEXTENDH_IEC pfmbm_poolextendh;
	#define EXT_mbm_poolextendh  extern PFMBM_POOLEXTENDH_IEC pfmbm_poolextendh;
	#define GET_mbm_poolextendh(fl)  s_pfCMGetAPI2( "mbm_poolextendh", (RTS_VOID_FCTPTR *)&pfmbm_poolextendh, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9C00A6F0), 0x03050500)
	#define CAL_mbm_poolextendh  pfmbm_poolextendh
	#define CHK_mbm_poolextendh  (pfmbm_poolextendh != NULL)
	#define EXP_mbm_poolextendh   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolextendh", (RTS_UINTPTR)mbm_poolextendh, 1, RTSITF_GET_SIGNATURE(0, 0x9C00A6F0), 0x03050500) 
#endif


/**
 * Gets the next available block from hPool and returns ist handle 
 */
typedef struct tagmbm_poolgetblock_struct
{
	CAA_HANDLE hPool;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_PoolGetBlock;		/* VAR_OUTPUT */	
} mbm_poolgetblock_struct;

void CDECL CDECL_EXT mbm_poolgetblock(mbm_poolgetblock_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_POOLGETBLOCK_IEC) (mbm_poolgetblock_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLGETBLOCK_NOTIMPLEMENTED)
	#define USE_mbm_poolgetblock
	#define EXT_mbm_poolgetblock
	#define GET_mbm_poolgetblock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_poolgetblock(p0) 
	#define CHK_mbm_poolgetblock  FALSE
	#define EXP_mbm_poolgetblock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_poolgetblock
	#define EXT_mbm_poolgetblock
	#define GET_mbm_poolgetblock(fl)  CAL_CMGETAPI( "mbm_poolgetblock" ) 
	#define CAL_mbm_poolgetblock  mbm_poolgetblock
	#define CHK_mbm_poolgetblock  TRUE
	#define EXP_mbm_poolgetblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolgetblock", (RTS_UINTPTR)mbm_poolgetblock, 1, RTSITF_GET_SIGNATURE(0, 0x2B3E34EB), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_poolgetblock
	#define EXT_mbm_poolgetblock
	#define GET_mbm_poolgetblock(fl)  CAL_CMGETAPI( "mbm_poolgetblock" ) 
	#define CAL_mbm_poolgetblock  mbm_poolgetblock
	#define CHK_mbm_poolgetblock  TRUE
	#define EXP_mbm_poolgetblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolgetblock", (RTS_UINTPTR)mbm_poolgetblock, 1, RTSITF_GET_SIGNATURE(0, 0x2B3E34EB), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_poolgetblock
	#define EXT_CmpCAAMemBlockManmbm_poolgetblock
	#define GET_CmpCAAMemBlockManmbm_poolgetblock  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_poolgetblock  mbm_poolgetblock
	#define CHK_CmpCAAMemBlockManmbm_poolgetblock  TRUE
	#define EXP_CmpCAAMemBlockManmbm_poolgetblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolgetblock", (RTS_UINTPTR)mbm_poolgetblock, 1, RTSITF_GET_SIGNATURE(0, 0x2B3E34EB), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_poolgetblock
	#define EXT_mbm_poolgetblock
	#define GET_mbm_poolgetblock(fl)  CAL_CMGETAPI( "mbm_poolgetblock" ) 
	#define CAL_mbm_poolgetblock  mbm_poolgetblock
	#define CHK_mbm_poolgetblock  TRUE
	#define EXP_mbm_poolgetblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolgetblock", (RTS_UINTPTR)mbm_poolgetblock, 1, RTSITF_GET_SIGNATURE(0, 0x2B3E34EB), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_poolgetblock  PFMBM_POOLGETBLOCK_IEC pfmbm_poolgetblock;
	#define EXT_mbm_poolgetblock  extern PFMBM_POOLGETBLOCK_IEC pfmbm_poolgetblock;
	#define GET_mbm_poolgetblock(fl)  s_pfCMGetAPI2( "mbm_poolgetblock", (RTS_VOID_FCTPTR *)&pfmbm_poolgetblock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2B3E34EB), 0x03050500)
	#define CAL_mbm_poolgetblock  pfmbm_poolgetblock
	#define CHK_mbm_poolgetblock  (pfmbm_poolgetblock != NULL)
	#define EXP_mbm_poolgetblock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolgetblock", (RTS_UINTPTR)mbm_poolgetblock, 1, RTSITF_GET_SIGNATURE(0, 0x2B3E34EB), 0x03050500) 
#endif


/**
 * <description>mbm_poolgetsize</description>
 */
typedef struct tagmbm_poolgetsize_struct
{
	CAA_COUNT ctNumBlock;				/* VAR_INPUT */	
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_SIZE MBM_PoolGetSize;			/* VAR_OUTPUT */	
} mbm_poolgetsize_struct;

void CDECL CDECL_EXT mbm_poolgetsize(mbm_poolgetsize_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_POOLGETSIZE_IEC) (mbm_poolgetsize_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLGETSIZE_NOTIMPLEMENTED)
	#define USE_mbm_poolgetsize
	#define EXT_mbm_poolgetsize
	#define GET_mbm_poolgetsize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_poolgetsize(p0) 
	#define CHK_mbm_poolgetsize  FALSE
	#define EXP_mbm_poolgetsize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_poolgetsize
	#define EXT_mbm_poolgetsize
	#define GET_mbm_poolgetsize(fl)  CAL_CMGETAPI( "mbm_poolgetsize" ) 
	#define CAL_mbm_poolgetsize  mbm_poolgetsize
	#define CHK_mbm_poolgetsize  TRUE
	#define EXP_mbm_poolgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolgetsize", (RTS_UINTPTR)mbm_poolgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x47282742), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_poolgetsize
	#define EXT_mbm_poolgetsize
	#define GET_mbm_poolgetsize(fl)  CAL_CMGETAPI( "mbm_poolgetsize" ) 
	#define CAL_mbm_poolgetsize  mbm_poolgetsize
	#define CHK_mbm_poolgetsize  TRUE
	#define EXP_mbm_poolgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolgetsize", (RTS_UINTPTR)mbm_poolgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x47282742), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_poolgetsize
	#define EXT_CmpCAAMemBlockManmbm_poolgetsize
	#define GET_CmpCAAMemBlockManmbm_poolgetsize  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_poolgetsize  mbm_poolgetsize
	#define CHK_CmpCAAMemBlockManmbm_poolgetsize  TRUE
	#define EXP_CmpCAAMemBlockManmbm_poolgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolgetsize", (RTS_UINTPTR)mbm_poolgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x47282742), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_poolgetsize
	#define EXT_mbm_poolgetsize
	#define GET_mbm_poolgetsize(fl)  CAL_CMGETAPI( "mbm_poolgetsize" ) 
	#define CAL_mbm_poolgetsize  mbm_poolgetsize
	#define CHK_mbm_poolgetsize  TRUE
	#define EXP_mbm_poolgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolgetsize", (RTS_UINTPTR)mbm_poolgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x47282742), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_poolgetsize  PFMBM_POOLGETSIZE_IEC pfmbm_poolgetsize;
	#define EXT_mbm_poolgetsize  extern PFMBM_POOLGETSIZE_IEC pfmbm_poolgetsize;
	#define GET_mbm_poolgetsize(fl)  s_pfCMGetAPI2( "mbm_poolgetsize", (RTS_VOID_FCTPTR *)&pfmbm_poolgetsize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x47282742), 0x03050500)
	#define CAL_mbm_poolgetsize  pfmbm_poolgetsize
	#define CHK_mbm_poolgetsize  (pfmbm_poolgetsize != NULL)
	#define EXP_mbm_poolgetsize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolgetsize", (RTS_UINTPTR)mbm_poolgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x47282742), 0x03050500) 
#endif


/**
 * Clears the block owner and returns hBlock to its pool 
 */
typedef struct tagmbm_poolputblock_struct
{
	CAA_HANDLE hBlock;					/* VAR_INPUT */	
	CAA_ERROR MBM_PoolPutBlock;			/* VAR_OUTPUT */	
} mbm_poolputblock_struct;

void CDECL CDECL_EXT mbm_poolputblock(mbm_poolputblock_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_POOLPUTBLOCK_IEC) (mbm_poolputblock_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_POOLPUTBLOCK_NOTIMPLEMENTED)
	#define USE_mbm_poolputblock
	#define EXT_mbm_poolputblock
	#define GET_mbm_poolputblock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_poolputblock(p0) 
	#define CHK_mbm_poolputblock  FALSE
	#define EXP_mbm_poolputblock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_poolputblock
	#define EXT_mbm_poolputblock
	#define GET_mbm_poolputblock(fl)  CAL_CMGETAPI( "mbm_poolputblock" ) 
	#define CAL_mbm_poolputblock  mbm_poolputblock
	#define CHK_mbm_poolputblock  TRUE
	#define EXP_mbm_poolputblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolputblock", (RTS_UINTPTR)mbm_poolputblock, 1, RTSITF_GET_SIGNATURE(0, 0x80479C72), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_poolputblock
	#define EXT_mbm_poolputblock
	#define GET_mbm_poolputblock(fl)  CAL_CMGETAPI( "mbm_poolputblock" ) 
	#define CAL_mbm_poolputblock  mbm_poolputblock
	#define CHK_mbm_poolputblock  TRUE
	#define EXP_mbm_poolputblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolputblock", (RTS_UINTPTR)mbm_poolputblock, 1, RTSITF_GET_SIGNATURE(0, 0x80479C72), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_poolputblock
	#define EXT_CmpCAAMemBlockManmbm_poolputblock
	#define GET_CmpCAAMemBlockManmbm_poolputblock  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_poolputblock  mbm_poolputblock
	#define CHK_CmpCAAMemBlockManmbm_poolputblock  TRUE
	#define EXP_CmpCAAMemBlockManmbm_poolputblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolputblock", (RTS_UINTPTR)mbm_poolputblock, 1, RTSITF_GET_SIGNATURE(0, 0x80479C72), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_poolputblock
	#define EXT_mbm_poolputblock
	#define GET_mbm_poolputblock(fl)  CAL_CMGETAPI( "mbm_poolputblock" ) 
	#define CAL_mbm_poolputblock  mbm_poolputblock
	#define CHK_mbm_poolputblock  TRUE
	#define EXP_mbm_poolputblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolputblock", (RTS_UINTPTR)mbm_poolputblock, 1, RTSITF_GET_SIGNATURE(0, 0x80479C72), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_poolputblock  PFMBM_POOLPUTBLOCK_IEC pfmbm_poolputblock;
	#define EXT_mbm_poolputblock  extern PFMBM_POOLPUTBLOCK_IEC pfmbm_poolputblock;
	#define GET_mbm_poolputblock(fl)  s_pfCMGetAPI2( "mbm_poolputblock", (RTS_VOID_FCTPTR *)&pfmbm_poolputblock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x80479C72), 0x03050500)
	#define CAL_mbm_poolputblock  pfmbm_poolputblock
	#define CHK_mbm_poolputblock  (pfmbm_poolputblock != NULL)
	#define EXP_mbm_poolputblock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_poolputblock", (RTS_UINTPTR)mbm_poolputblock, 1, RTSITF_GET_SIGNATURE(0, 0x80479C72), 0x03050500) 
#endif


/**
 * Add the priroity level usiPrio to the ready list 
 */
typedef struct tagmbm_rlstaddprio_struct
{
	CAA_HANDLE hRLst;					/* VAR_INPUT */	
	RTS_IEC_USINT usiPrio;				/* VAR_INPUT */	/* [0..63] Priotity Level */
	CAA_ERROR MBM_RLstAddPrio;			/* VAR_OUTPUT */	
} mbm_rlstaddprio_struct;

void CDECL CDECL_EXT mbm_rlstaddprio(mbm_rlstaddprio_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_RLSTADDPRIO_IEC) (mbm_rlstaddprio_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTADDPRIO_NOTIMPLEMENTED)
	#define USE_mbm_rlstaddprio
	#define EXT_mbm_rlstaddprio
	#define GET_mbm_rlstaddprio(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_rlstaddprio(p0) 
	#define CHK_mbm_rlstaddprio  FALSE
	#define EXP_mbm_rlstaddprio  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_rlstaddprio
	#define EXT_mbm_rlstaddprio
	#define GET_mbm_rlstaddprio(fl)  CAL_CMGETAPI( "mbm_rlstaddprio" ) 
	#define CAL_mbm_rlstaddprio  mbm_rlstaddprio
	#define CHK_mbm_rlstaddprio  TRUE
	#define EXP_mbm_rlstaddprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstaddprio", (RTS_UINTPTR)mbm_rlstaddprio, 1, RTSITF_GET_SIGNATURE(0, 0x977D4860), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_rlstaddprio
	#define EXT_mbm_rlstaddprio
	#define GET_mbm_rlstaddprio(fl)  CAL_CMGETAPI( "mbm_rlstaddprio" ) 
	#define CAL_mbm_rlstaddprio  mbm_rlstaddprio
	#define CHK_mbm_rlstaddprio  TRUE
	#define EXP_mbm_rlstaddprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstaddprio", (RTS_UINTPTR)mbm_rlstaddprio, 1, RTSITF_GET_SIGNATURE(0, 0x977D4860), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_rlstaddprio
	#define EXT_CmpCAAMemBlockManmbm_rlstaddprio
	#define GET_CmpCAAMemBlockManmbm_rlstaddprio  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_rlstaddprio  mbm_rlstaddprio
	#define CHK_CmpCAAMemBlockManmbm_rlstaddprio  TRUE
	#define EXP_CmpCAAMemBlockManmbm_rlstaddprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstaddprio", (RTS_UINTPTR)mbm_rlstaddprio, 1, RTSITF_GET_SIGNATURE(0, 0x977D4860), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_rlstaddprio
	#define EXT_mbm_rlstaddprio
	#define GET_mbm_rlstaddprio(fl)  CAL_CMGETAPI( "mbm_rlstaddprio" ) 
	#define CAL_mbm_rlstaddprio  mbm_rlstaddprio
	#define CHK_mbm_rlstaddprio  TRUE
	#define EXP_mbm_rlstaddprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstaddprio", (RTS_UINTPTR)mbm_rlstaddprio, 1, RTSITF_GET_SIGNATURE(0, 0x977D4860), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_rlstaddprio  PFMBM_RLSTADDPRIO_IEC pfmbm_rlstaddprio;
	#define EXT_mbm_rlstaddprio  extern PFMBM_RLSTADDPRIO_IEC pfmbm_rlstaddprio;
	#define GET_mbm_rlstaddprio(fl)  s_pfCMGetAPI2( "mbm_rlstaddprio", (RTS_VOID_FCTPTR *)&pfmbm_rlstaddprio, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x977D4860), 0x03050500)
	#define CAL_mbm_rlstaddprio  pfmbm_rlstaddprio
	#define CHK_mbm_rlstaddprio  (pfmbm_rlstaddprio != NULL)
	#define EXP_mbm_rlstaddprio   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstaddprio", (RTS_UINTPTR)mbm_rlstaddprio, 1, RTSITF_GET_SIGNATURE(0, 0x977D4860), 0x03050500) 
#endif


/**
 * return TRUE if the priority level usiPrio is part of the ready list 
 */
typedef struct tagmbm_rlstcheckprio_struct
{
	CAA_HANDLE hRLst;					/* VAR_INPUT */	
	RTS_IEC_USINT usiPrio;				/* VAR_INPUT */	/* [0..63] priority level. */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_BOOL MBM_RLstCheckPrio;			/* VAR_OUTPUT */	/* xReady */
} mbm_rlstcheckprio_struct;

void CDECL CDECL_EXT mbm_rlstcheckprio(mbm_rlstcheckprio_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_RLSTCHECKPRIO_IEC) (mbm_rlstcheckprio_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTCHECKPRIO_NOTIMPLEMENTED)
	#define USE_mbm_rlstcheckprio
	#define EXT_mbm_rlstcheckprio
	#define GET_mbm_rlstcheckprio(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_rlstcheckprio(p0) 
	#define CHK_mbm_rlstcheckprio  FALSE
	#define EXP_mbm_rlstcheckprio  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_rlstcheckprio
	#define EXT_mbm_rlstcheckprio
	#define GET_mbm_rlstcheckprio(fl)  CAL_CMGETAPI( "mbm_rlstcheckprio" ) 
	#define CAL_mbm_rlstcheckprio  mbm_rlstcheckprio
	#define CHK_mbm_rlstcheckprio  TRUE
	#define EXP_mbm_rlstcheckprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcheckprio", (RTS_UINTPTR)mbm_rlstcheckprio, 1, RTSITF_GET_SIGNATURE(0, 0x9650B960), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_rlstcheckprio
	#define EXT_mbm_rlstcheckprio
	#define GET_mbm_rlstcheckprio(fl)  CAL_CMGETAPI( "mbm_rlstcheckprio" ) 
	#define CAL_mbm_rlstcheckprio  mbm_rlstcheckprio
	#define CHK_mbm_rlstcheckprio  TRUE
	#define EXP_mbm_rlstcheckprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcheckprio", (RTS_UINTPTR)mbm_rlstcheckprio, 1, RTSITF_GET_SIGNATURE(0, 0x9650B960), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_rlstcheckprio
	#define EXT_CmpCAAMemBlockManmbm_rlstcheckprio
	#define GET_CmpCAAMemBlockManmbm_rlstcheckprio  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_rlstcheckprio  mbm_rlstcheckprio
	#define CHK_CmpCAAMemBlockManmbm_rlstcheckprio  TRUE
	#define EXP_CmpCAAMemBlockManmbm_rlstcheckprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcheckprio", (RTS_UINTPTR)mbm_rlstcheckprio, 1, RTSITF_GET_SIGNATURE(0, 0x9650B960), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_rlstcheckprio
	#define EXT_mbm_rlstcheckprio
	#define GET_mbm_rlstcheckprio(fl)  CAL_CMGETAPI( "mbm_rlstcheckprio" ) 
	#define CAL_mbm_rlstcheckprio  mbm_rlstcheckprio
	#define CHK_mbm_rlstcheckprio  TRUE
	#define EXP_mbm_rlstcheckprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcheckprio", (RTS_UINTPTR)mbm_rlstcheckprio, 1, RTSITF_GET_SIGNATURE(0, 0x9650B960), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_rlstcheckprio  PFMBM_RLSTCHECKPRIO_IEC pfmbm_rlstcheckprio;
	#define EXT_mbm_rlstcheckprio  extern PFMBM_RLSTCHECKPRIO_IEC pfmbm_rlstcheckprio;
	#define GET_mbm_rlstcheckprio(fl)  s_pfCMGetAPI2( "mbm_rlstcheckprio", (RTS_VOID_FCTPTR *)&pfmbm_rlstcheckprio, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9650B960), 0x03050500)
	#define CAL_mbm_rlstcheckprio  pfmbm_rlstcheckprio
	#define CHK_mbm_rlstcheckprio  (pfmbm_rlstcheckprio != NULL)
	#define EXP_mbm_rlstcheckprio   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcheckprio", (RTS_UINTPTR)mbm_rlstcheckprio, 1, RTSITF_GET_SIGNATURE(0, 0x9650B960), 0x03050500) 
#endif


/**
 * Take a SIZEOF(RLST) bytes from the Heap(OS) and build a Reday List 
 */
typedef struct tagmbm_rlstcreateh_struct
{
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_RLstCreateH;			/* VAR_OUTPUT */	
} mbm_rlstcreateh_struct;

void CDECL CDECL_EXT mbm_rlstcreateh(mbm_rlstcreateh_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_RLSTCREATEH_IEC) (mbm_rlstcreateh_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTCREATEH_NOTIMPLEMENTED)
	#define USE_mbm_rlstcreateh
	#define EXT_mbm_rlstcreateh
	#define GET_mbm_rlstcreateh(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_rlstcreateh(p0) 
	#define CHK_mbm_rlstcreateh  FALSE
	#define EXP_mbm_rlstcreateh  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_rlstcreateh
	#define EXT_mbm_rlstcreateh
	#define GET_mbm_rlstcreateh(fl)  CAL_CMGETAPI( "mbm_rlstcreateh" ) 
	#define CAL_mbm_rlstcreateh  mbm_rlstcreateh
	#define CHK_mbm_rlstcreateh  TRUE
	#define EXP_mbm_rlstcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcreateh", (RTS_UINTPTR)mbm_rlstcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x2D79CB11), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_rlstcreateh
	#define EXT_mbm_rlstcreateh
	#define GET_mbm_rlstcreateh(fl)  CAL_CMGETAPI( "mbm_rlstcreateh" ) 
	#define CAL_mbm_rlstcreateh  mbm_rlstcreateh
	#define CHK_mbm_rlstcreateh  TRUE
	#define EXP_mbm_rlstcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcreateh", (RTS_UINTPTR)mbm_rlstcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x2D79CB11), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_rlstcreateh
	#define EXT_CmpCAAMemBlockManmbm_rlstcreateh
	#define GET_CmpCAAMemBlockManmbm_rlstcreateh  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_rlstcreateh  mbm_rlstcreateh
	#define CHK_CmpCAAMemBlockManmbm_rlstcreateh  TRUE
	#define EXP_CmpCAAMemBlockManmbm_rlstcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcreateh", (RTS_UINTPTR)mbm_rlstcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x2D79CB11), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_rlstcreateh
	#define EXT_mbm_rlstcreateh
	#define GET_mbm_rlstcreateh(fl)  CAL_CMGETAPI( "mbm_rlstcreateh" ) 
	#define CAL_mbm_rlstcreateh  mbm_rlstcreateh
	#define CHK_mbm_rlstcreateh  TRUE
	#define EXP_mbm_rlstcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcreateh", (RTS_UINTPTR)mbm_rlstcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x2D79CB11), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_rlstcreateh  PFMBM_RLSTCREATEH_IEC pfmbm_rlstcreateh;
	#define EXT_mbm_rlstcreateh  extern PFMBM_RLSTCREATEH_IEC pfmbm_rlstcreateh;
	#define GET_mbm_rlstcreateh(fl)  s_pfCMGetAPI2( "mbm_rlstcreateh", (RTS_VOID_FCTPTR *)&pfmbm_rlstcreateh, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2D79CB11), 0x03050500)
	#define CAL_mbm_rlstcreateh  pfmbm_rlstcreateh
	#define CHK_mbm_rlstcreateh  (pfmbm_rlstcreateh != NULL)
	#define EXP_mbm_rlstcreateh   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcreateh", (RTS_UINTPTR)mbm_rlstcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x2D79CB11), 0x03050500) 
#endif


/**
 * Take SIZEOF(RLST) bytes from a PLC(IEC) provided memory and build a Ready List 
 */
typedef struct tagmbm_rlstcreatep_struct
{
	CAA_SIZE szMemory;					/* VAR_INPUT */	
	CAA_PVOID pMemory;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_RLstCreateP;			/* VAR_OUTPUT */	
} mbm_rlstcreatep_struct;

void CDECL CDECL_EXT mbm_rlstcreatep(mbm_rlstcreatep_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_RLSTCREATEP_IEC) (mbm_rlstcreatep_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTCREATEP_NOTIMPLEMENTED)
	#define USE_mbm_rlstcreatep
	#define EXT_mbm_rlstcreatep
	#define GET_mbm_rlstcreatep(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_rlstcreatep(p0) 
	#define CHK_mbm_rlstcreatep  FALSE
	#define EXP_mbm_rlstcreatep  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_rlstcreatep
	#define EXT_mbm_rlstcreatep
	#define GET_mbm_rlstcreatep(fl)  CAL_CMGETAPI( "mbm_rlstcreatep" ) 
	#define CAL_mbm_rlstcreatep  mbm_rlstcreatep
	#define CHK_mbm_rlstcreatep  TRUE
	#define EXP_mbm_rlstcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcreatep", (RTS_UINTPTR)mbm_rlstcreatep, 1, RTSITF_GET_SIGNATURE(0, 0x24A5FF5A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_rlstcreatep
	#define EXT_mbm_rlstcreatep
	#define GET_mbm_rlstcreatep(fl)  CAL_CMGETAPI( "mbm_rlstcreatep" ) 
	#define CAL_mbm_rlstcreatep  mbm_rlstcreatep
	#define CHK_mbm_rlstcreatep  TRUE
	#define EXP_mbm_rlstcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcreatep", (RTS_UINTPTR)mbm_rlstcreatep, 1, RTSITF_GET_SIGNATURE(0, 0x24A5FF5A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_rlstcreatep
	#define EXT_CmpCAAMemBlockManmbm_rlstcreatep
	#define GET_CmpCAAMemBlockManmbm_rlstcreatep  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_rlstcreatep  mbm_rlstcreatep
	#define CHK_CmpCAAMemBlockManmbm_rlstcreatep  TRUE
	#define EXP_CmpCAAMemBlockManmbm_rlstcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcreatep", (RTS_UINTPTR)mbm_rlstcreatep, 1, RTSITF_GET_SIGNATURE(0, 0x24A5FF5A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_rlstcreatep
	#define EXT_mbm_rlstcreatep
	#define GET_mbm_rlstcreatep(fl)  CAL_CMGETAPI( "mbm_rlstcreatep" ) 
	#define CAL_mbm_rlstcreatep  mbm_rlstcreatep
	#define CHK_mbm_rlstcreatep  TRUE
	#define EXP_mbm_rlstcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcreatep", (RTS_UINTPTR)mbm_rlstcreatep, 1, RTSITF_GET_SIGNATURE(0, 0x24A5FF5A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_rlstcreatep  PFMBM_RLSTCREATEP_IEC pfmbm_rlstcreatep;
	#define EXT_mbm_rlstcreatep  extern PFMBM_RLSTCREATEP_IEC pfmbm_rlstcreatep;
	#define GET_mbm_rlstcreatep(fl)  s_pfCMGetAPI2( "mbm_rlstcreatep", (RTS_VOID_FCTPTR *)&pfmbm_rlstcreatep, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x24A5FF5A), 0x03050500)
	#define CAL_mbm_rlstcreatep  pfmbm_rlstcreatep
	#define CHK_mbm_rlstcreatep  (pfmbm_rlstcreatep != NULL)
	#define EXP_mbm_rlstcreatep   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstcreatep", (RTS_UINTPTR)mbm_rlstcreatep, 1, RTSITF_GET_SIGNATURE(0, 0x24A5FF5A), 0x03050500) 
#endif


/**
 * free all allocated resources of a ready list 
 */
typedef struct tagmbm_rlstdelete_struct
{
	CAA_HANDLE hRLst;					/* VAR_INPUT */	
	CAA_ERROR MBM_RLstDelete;			/* VAR_OUTPUT */	
} mbm_rlstdelete_struct;

void CDECL CDECL_EXT mbm_rlstdelete(mbm_rlstdelete_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_RLSTDELETE_IEC) (mbm_rlstdelete_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTDELETE_NOTIMPLEMENTED)
	#define USE_mbm_rlstdelete
	#define EXT_mbm_rlstdelete
	#define GET_mbm_rlstdelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_rlstdelete(p0) 
	#define CHK_mbm_rlstdelete  FALSE
	#define EXP_mbm_rlstdelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_rlstdelete
	#define EXT_mbm_rlstdelete
	#define GET_mbm_rlstdelete(fl)  CAL_CMGETAPI( "mbm_rlstdelete" ) 
	#define CAL_mbm_rlstdelete  mbm_rlstdelete
	#define CHK_mbm_rlstdelete  TRUE
	#define EXP_mbm_rlstdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstdelete", (RTS_UINTPTR)mbm_rlstdelete, 1, RTSITF_GET_SIGNATURE(0, 0xA1F0D540), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_rlstdelete
	#define EXT_mbm_rlstdelete
	#define GET_mbm_rlstdelete(fl)  CAL_CMGETAPI( "mbm_rlstdelete" ) 
	#define CAL_mbm_rlstdelete  mbm_rlstdelete
	#define CHK_mbm_rlstdelete  TRUE
	#define EXP_mbm_rlstdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstdelete", (RTS_UINTPTR)mbm_rlstdelete, 1, RTSITF_GET_SIGNATURE(0, 0xA1F0D540), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_rlstdelete
	#define EXT_CmpCAAMemBlockManmbm_rlstdelete
	#define GET_CmpCAAMemBlockManmbm_rlstdelete  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_rlstdelete  mbm_rlstdelete
	#define CHK_CmpCAAMemBlockManmbm_rlstdelete  TRUE
	#define EXP_CmpCAAMemBlockManmbm_rlstdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstdelete", (RTS_UINTPTR)mbm_rlstdelete, 1, RTSITF_GET_SIGNATURE(0, 0xA1F0D540), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_rlstdelete
	#define EXT_mbm_rlstdelete
	#define GET_mbm_rlstdelete(fl)  CAL_CMGETAPI( "mbm_rlstdelete" ) 
	#define CAL_mbm_rlstdelete  mbm_rlstdelete
	#define CHK_mbm_rlstdelete  TRUE
	#define EXP_mbm_rlstdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstdelete", (RTS_UINTPTR)mbm_rlstdelete, 1, RTSITF_GET_SIGNATURE(0, 0xA1F0D540), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_rlstdelete  PFMBM_RLSTDELETE_IEC pfmbm_rlstdelete;
	#define EXT_mbm_rlstdelete  extern PFMBM_RLSTDELETE_IEC pfmbm_rlstdelete;
	#define GET_mbm_rlstdelete(fl)  s_pfCMGetAPI2( "mbm_rlstdelete", (RTS_VOID_FCTPTR *)&pfmbm_rlstdelete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA1F0D540), 0x03050500)
	#define CAL_mbm_rlstdelete  pfmbm_rlstdelete
	#define CHK_mbm_rlstdelete  (pfmbm_rlstdelete != NULL)
	#define EXP_mbm_rlstdelete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstdelete", (RTS_UINTPTR)mbm_rlstdelete, 1, RTSITF_GET_SIGNATURE(0, 0xA1F0D540), 0x03050500) 
#endif


/**
 * find the higest priority level in the ready list 
 */
typedef struct tagmbm_rlstgethighestprio_struct
{
	CAA_HANDLE hRLst;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	RTS_IEC_USINT MBM_RLstGetHighestPrio;	/* VAR_OUTPUT */	
} mbm_rlstgethighestprio_struct;

void CDECL CDECL_EXT mbm_rlstgethighestprio(mbm_rlstgethighestprio_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_RLSTGETHIGHESTPRIO_IEC) (mbm_rlstgethighestprio_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTGETHIGHESTPRIO_NOTIMPLEMENTED)
	#define USE_mbm_rlstgethighestprio
	#define EXT_mbm_rlstgethighestprio
	#define GET_mbm_rlstgethighestprio(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_rlstgethighestprio(p0) 
	#define CHK_mbm_rlstgethighestprio  FALSE
	#define EXP_mbm_rlstgethighestprio  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_rlstgethighestprio
	#define EXT_mbm_rlstgethighestprio
	#define GET_mbm_rlstgethighestprio(fl)  CAL_CMGETAPI( "mbm_rlstgethighestprio" ) 
	#define CAL_mbm_rlstgethighestprio  mbm_rlstgethighestprio
	#define CHK_mbm_rlstgethighestprio  TRUE
	#define EXP_mbm_rlstgethighestprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstgethighestprio", (RTS_UINTPTR)mbm_rlstgethighestprio, 1, RTSITF_GET_SIGNATURE(0, 0x94D7A1CB), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_rlstgethighestprio
	#define EXT_mbm_rlstgethighestprio
	#define GET_mbm_rlstgethighestprio(fl)  CAL_CMGETAPI( "mbm_rlstgethighestprio" ) 
	#define CAL_mbm_rlstgethighestprio  mbm_rlstgethighestprio
	#define CHK_mbm_rlstgethighestprio  TRUE
	#define EXP_mbm_rlstgethighestprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstgethighestprio", (RTS_UINTPTR)mbm_rlstgethighestprio, 1, RTSITF_GET_SIGNATURE(0, 0x94D7A1CB), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_rlstgethighestprio
	#define EXT_CmpCAAMemBlockManmbm_rlstgethighestprio
	#define GET_CmpCAAMemBlockManmbm_rlstgethighestprio  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_rlstgethighestprio  mbm_rlstgethighestprio
	#define CHK_CmpCAAMemBlockManmbm_rlstgethighestprio  TRUE
	#define EXP_CmpCAAMemBlockManmbm_rlstgethighestprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstgethighestprio", (RTS_UINTPTR)mbm_rlstgethighestprio, 1, RTSITF_GET_SIGNATURE(0, 0x94D7A1CB), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_rlstgethighestprio
	#define EXT_mbm_rlstgethighestprio
	#define GET_mbm_rlstgethighestprio(fl)  CAL_CMGETAPI( "mbm_rlstgethighestprio" ) 
	#define CAL_mbm_rlstgethighestprio  mbm_rlstgethighestprio
	#define CHK_mbm_rlstgethighestprio  TRUE
	#define EXP_mbm_rlstgethighestprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstgethighestprio", (RTS_UINTPTR)mbm_rlstgethighestprio, 1, RTSITF_GET_SIGNATURE(0, 0x94D7A1CB), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_rlstgethighestprio  PFMBM_RLSTGETHIGHESTPRIO_IEC pfmbm_rlstgethighestprio;
	#define EXT_mbm_rlstgethighestprio  extern PFMBM_RLSTGETHIGHESTPRIO_IEC pfmbm_rlstgethighestprio;
	#define GET_mbm_rlstgethighestprio(fl)  s_pfCMGetAPI2( "mbm_rlstgethighestprio", (RTS_VOID_FCTPTR *)&pfmbm_rlstgethighestprio, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x94D7A1CB), 0x03050500)
	#define CAL_mbm_rlstgethighestprio  pfmbm_rlstgethighestprio
	#define CHK_mbm_rlstgethighestprio  (pfmbm_rlstgethighestprio != NULL)
	#define EXP_mbm_rlstgethighestprio   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstgethighestprio", (RTS_UINTPTR)mbm_rlstgethighestprio, 1, RTSITF_GET_SIGNATURE(0, 0x94D7A1CB), 0x03050500) 
#endif


/**
 * <description>mbm_rlstgetsize</description>
 */
typedef struct tagmbm_rlstgetsize_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	CAA_SIZE MBM_RLstGetSize;			/* VAR_OUTPUT */	
} mbm_rlstgetsize_struct;

void CDECL CDECL_EXT mbm_rlstgetsize(mbm_rlstgetsize_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_RLSTGETSIZE_IEC) (mbm_rlstgetsize_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTGETSIZE_NOTIMPLEMENTED)
	#define USE_mbm_rlstgetsize
	#define EXT_mbm_rlstgetsize
	#define GET_mbm_rlstgetsize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_rlstgetsize(p0) 
	#define CHK_mbm_rlstgetsize  FALSE
	#define EXP_mbm_rlstgetsize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_rlstgetsize
	#define EXT_mbm_rlstgetsize
	#define GET_mbm_rlstgetsize(fl)  CAL_CMGETAPI( "mbm_rlstgetsize" ) 
	#define CAL_mbm_rlstgetsize  mbm_rlstgetsize
	#define CHK_mbm_rlstgetsize  TRUE
	#define EXP_mbm_rlstgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstgetsize", (RTS_UINTPTR)mbm_rlstgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x3913C3B8), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_rlstgetsize
	#define EXT_mbm_rlstgetsize
	#define GET_mbm_rlstgetsize(fl)  CAL_CMGETAPI( "mbm_rlstgetsize" ) 
	#define CAL_mbm_rlstgetsize  mbm_rlstgetsize
	#define CHK_mbm_rlstgetsize  TRUE
	#define EXP_mbm_rlstgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstgetsize", (RTS_UINTPTR)mbm_rlstgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x3913C3B8), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_rlstgetsize
	#define EXT_CmpCAAMemBlockManmbm_rlstgetsize
	#define GET_CmpCAAMemBlockManmbm_rlstgetsize  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_rlstgetsize  mbm_rlstgetsize
	#define CHK_CmpCAAMemBlockManmbm_rlstgetsize  TRUE
	#define EXP_CmpCAAMemBlockManmbm_rlstgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstgetsize", (RTS_UINTPTR)mbm_rlstgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x3913C3B8), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_rlstgetsize
	#define EXT_mbm_rlstgetsize
	#define GET_mbm_rlstgetsize(fl)  CAL_CMGETAPI( "mbm_rlstgetsize" ) 
	#define CAL_mbm_rlstgetsize  mbm_rlstgetsize
	#define CHK_mbm_rlstgetsize  TRUE
	#define EXP_mbm_rlstgetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstgetsize", (RTS_UINTPTR)mbm_rlstgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x3913C3B8), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_rlstgetsize  PFMBM_RLSTGETSIZE_IEC pfmbm_rlstgetsize;
	#define EXT_mbm_rlstgetsize  extern PFMBM_RLSTGETSIZE_IEC pfmbm_rlstgetsize;
	#define GET_mbm_rlstgetsize(fl)  s_pfCMGetAPI2( "mbm_rlstgetsize", (RTS_VOID_FCTPTR *)&pfmbm_rlstgetsize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x3913C3B8), 0x03050500)
	#define CAL_mbm_rlstgetsize  pfmbm_rlstgetsize
	#define CHK_mbm_rlstgetsize  (pfmbm_rlstgetsize != NULL)
	#define EXP_mbm_rlstgetsize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstgetsize", (RTS_UINTPTR)mbm_rlstgetsize, 1, RTSITF_GET_SIGNATURE(0, 0x3913C3B8), 0x03050500) 
#endif


/**
 * remove the priority level usiPrio from the ready list 
 */
typedef struct tagmbm_rlstremoveprio_struct
{
	CAA_HANDLE hRLst;					/* VAR_INPUT */	
	RTS_IEC_USINT usiPrio;				/* VAR_INPUT */	/* [0..63] priority level. 255 :=> remove all levels from the list */
	CAA_ERROR MBM_RLstRemovePrio;		/* VAR_OUTPUT */	
} mbm_rlstremoveprio_struct;

void CDECL CDECL_EXT mbm_rlstremoveprio(mbm_rlstremoveprio_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_RLSTREMOVEPRIO_IEC) (mbm_rlstremoveprio_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_RLSTREMOVEPRIO_NOTIMPLEMENTED)
	#define USE_mbm_rlstremoveprio
	#define EXT_mbm_rlstremoveprio
	#define GET_mbm_rlstremoveprio(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_rlstremoveprio(p0) 
	#define CHK_mbm_rlstremoveprio  FALSE
	#define EXP_mbm_rlstremoveprio  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_rlstremoveprio
	#define EXT_mbm_rlstremoveprio
	#define GET_mbm_rlstremoveprio(fl)  CAL_CMGETAPI( "mbm_rlstremoveprio" ) 
	#define CAL_mbm_rlstremoveprio  mbm_rlstremoveprio
	#define CHK_mbm_rlstremoveprio  TRUE
	#define EXP_mbm_rlstremoveprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstremoveprio", (RTS_UINTPTR)mbm_rlstremoveprio, 1, RTSITF_GET_SIGNATURE(0, 0x15C75530), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_rlstremoveprio
	#define EXT_mbm_rlstremoveprio
	#define GET_mbm_rlstremoveprio(fl)  CAL_CMGETAPI( "mbm_rlstremoveprio" ) 
	#define CAL_mbm_rlstremoveprio  mbm_rlstremoveprio
	#define CHK_mbm_rlstremoveprio  TRUE
	#define EXP_mbm_rlstremoveprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstremoveprio", (RTS_UINTPTR)mbm_rlstremoveprio, 1, RTSITF_GET_SIGNATURE(0, 0x15C75530), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_rlstremoveprio
	#define EXT_CmpCAAMemBlockManmbm_rlstremoveprio
	#define GET_CmpCAAMemBlockManmbm_rlstremoveprio  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_rlstremoveprio  mbm_rlstremoveprio
	#define CHK_CmpCAAMemBlockManmbm_rlstremoveprio  TRUE
	#define EXP_CmpCAAMemBlockManmbm_rlstremoveprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstremoveprio", (RTS_UINTPTR)mbm_rlstremoveprio, 1, RTSITF_GET_SIGNATURE(0, 0x15C75530), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_rlstremoveprio
	#define EXT_mbm_rlstremoveprio
	#define GET_mbm_rlstremoveprio(fl)  CAL_CMGETAPI( "mbm_rlstremoveprio" ) 
	#define CAL_mbm_rlstremoveprio  mbm_rlstremoveprio
	#define CHK_mbm_rlstremoveprio  TRUE
	#define EXP_mbm_rlstremoveprio  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstremoveprio", (RTS_UINTPTR)mbm_rlstremoveprio, 1, RTSITF_GET_SIGNATURE(0, 0x15C75530), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_rlstremoveprio  PFMBM_RLSTREMOVEPRIO_IEC pfmbm_rlstremoveprio;
	#define EXT_mbm_rlstremoveprio  extern PFMBM_RLSTREMOVEPRIO_IEC pfmbm_rlstremoveprio;
	#define GET_mbm_rlstremoveprio(fl)  s_pfCMGetAPI2( "mbm_rlstremoveprio", (RTS_VOID_FCTPTR *)&pfmbm_rlstremoveprio, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x15C75530), 0x03050500)
	#define CAL_mbm_rlstremoveprio  pfmbm_rlstremoveprio
	#define CHK_mbm_rlstremoveprio  (pfmbm_rlstremoveprio != NULL)
	#define EXP_mbm_rlstremoveprio   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_rlstremoveprio", (RTS_UINTPTR)mbm_rlstremoveprio, 1, RTSITF_GET_SIGNATURE(0, 0x15C75530), 0x03050500) 
#endif


/**
 * Creates a message exchange of the specified type with Memory from Heap 
 * ctNumPrios = 0 AND ctNumMsg <> 0 => Resource Exchange 
 * ctNumPrios <> 0 AND ctNumMsg = 0 => NormalExchange    
 */
typedef struct tagmbm_xchgcreateh_struct
{
	CAA_COUNT ctNumMsg;					/* VAR_INPUT */	
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_COUNT ctNumPrios;				/* VAR_INPUT */	
	CAA_ENUM eSendMsg;					/* VAR_INPUT */	
	CAA_ENUM eReceiveMsg;				/* VAR_INPUT */	
	CAA_ENUM eXchgEmpty;				/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_XChgCreateH;			/* VAR_OUTPUT */	/* hXChg */
} mbm_xchgcreateh_struct;

void CDECL CDECL_EXT mbm_xchgcreateh(mbm_xchgcreateh_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_XCHGCREATEH_IEC) (mbm_xchgcreateh_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGCREATEH_NOTIMPLEMENTED)
	#define USE_mbm_xchgcreateh
	#define EXT_mbm_xchgcreateh
	#define GET_mbm_xchgcreateh(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_xchgcreateh(p0) 
	#define CHK_mbm_xchgcreateh  FALSE
	#define EXP_mbm_xchgcreateh  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_xchgcreateh
	#define EXT_mbm_xchgcreateh
	#define GET_mbm_xchgcreateh(fl)  CAL_CMGETAPI( "mbm_xchgcreateh" ) 
	#define CAL_mbm_xchgcreateh  mbm_xchgcreateh
	#define CHK_mbm_xchgcreateh  TRUE
	#define EXP_mbm_xchgcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgcreateh", (RTS_UINTPTR)mbm_xchgcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x36E091AE), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_xchgcreateh
	#define EXT_mbm_xchgcreateh
	#define GET_mbm_xchgcreateh(fl)  CAL_CMGETAPI( "mbm_xchgcreateh" ) 
	#define CAL_mbm_xchgcreateh  mbm_xchgcreateh
	#define CHK_mbm_xchgcreateh  TRUE
	#define EXP_mbm_xchgcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgcreateh", (RTS_UINTPTR)mbm_xchgcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x36E091AE), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_xchgcreateh
	#define EXT_CmpCAAMemBlockManmbm_xchgcreateh
	#define GET_CmpCAAMemBlockManmbm_xchgcreateh  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_xchgcreateh  mbm_xchgcreateh
	#define CHK_CmpCAAMemBlockManmbm_xchgcreateh  TRUE
	#define EXP_CmpCAAMemBlockManmbm_xchgcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgcreateh", (RTS_UINTPTR)mbm_xchgcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x36E091AE), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_xchgcreateh
	#define EXT_mbm_xchgcreateh
	#define GET_mbm_xchgcreateh(fl)  CAL_CMGETAPI( "mbm_xchgcreateh" ) 
	#define CAL_mbm_xchgcreateh  mbm_xchgcreateh
	#define CHK_mbm_xchgcreateh  TRUE
	#define EXP_mbm_xchgcreateh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgcreateh", (RTS_UINTPTR)mbm_xchgcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x36E091AE), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_xchgcreateh  PFMBM_XCHGCREATEH_IEC pfmbm_xchgcreateh;
	#define EXT_mbm_xchgcreateh  extern PFMBM_XCHGCREATEH_IEC pfmbm_xchgcreateh;
	#define GET_mbm_xchgcreateh(fl)  s_pfCMGetAPI2( "mbm_xchgcreateh", (RTS_VOID_FCTPTR *)&pfmbm_xchgcreateh, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x36E091AE), 0x03050500)
	#define CAL_mbm_xchgcreateh  pfmbm_xchgcreateh
	#define CHK_mbm_xchgcreateh  (pfmbm_xchgcreateh != NULL)
	#define EXP_mbm_xchgcreateh   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgcreateh", (RTS_UINTPTR)mbm_xchgcreateh, 1, RTSITF_GET_SIGNATURE(0, 0x36E091AE), 0x03050500) 
#endif


/**
 * Creates a message exchange of the specified type with Memory from PLC 
 * ctNumPrios = 0 AND ctNumMsg <> 0 => Resource Exchange 
 * ctNumPrios <> 0 AND ctNumMsg = 0 => NormalExchange    
 */
typedef struct tagmbm_xchgcreatep_struct
{
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_COUNT ctNumPrios;				/* VAR_INPUT */	
	CAA_SIZE szMemSize;					/* VAR_INPUT */	
	CAA_PVOID pMemory;					/* VAR_INPUT */	
	CAA_ENUM eSendMsg;					/* VAR_INPUT */	
	CAA_ENUM eReceiveMsg;				/* VAR_INPUT */	
	CAA_ENUM eXchgEmpty;				/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_XChgCreateP;			/* VAR_OUTPUT */	/* hXChg */
} mbm_xchgcreatep_struct;

void CDECL CDECL_EXT mbm_xchgcreatep(mbm_xchgcreatep_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_XCHGCREATEP_IEC) (mbm_xchgcreatep_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGCREATEP_NOTIMPLEMENTED)
	#define USE_mbm_xchgcreatep
	#define EXT_mbm_xchgcreatep
	#define GET_mbm_xchgcreatep(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_xchgcreatep(p0) 
	#define CHK_mbm_xchgcreatep  FALSE
	#define EXP_mbm_xchgcreatep  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_xchgcreatep
	#define EXT_mbm_xchgcreatep
	#define GET_mbm_xchgcreatep(fl)  CAL_CMGETAPI( "mbm_xchgcreatep" ) 
	#define CAL_mbm_xchgcreatep  mbm_xchgcreatep
	#define CHK_mbm_xchgcreatep  TRUE
	#define EXP_mbm_xchgcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgcreatep", (RTS_UINTPTR)mbm_xchgcreatep, 1, RTSITF_GET_SIGNATURE(0, 0x578CD111), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_xchgcreatep
	#define EXT_mbm_xchgcreatep
	#define GET_mbm_xchgcreatep(fl)  CAL_CMGETAPI( "mbm_xchgcreatep" ) 
	#define CAL_mbm_xchgcreatep  mbm_xchgcreatep
	#define CHK_mbm_xchgcreatep  TRUE
	#define EXP_mbm_xchgcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgcreatep", (RTS_UINTPTR)mbm_xchgcreatep, 1, RTSITF_GET_SIGNATURE(0, 0x578CD111), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_xchgcreatep
	#define EXT_CmpCAAMemBlockManmbm_xchgcreatep
	#define GET_CmpCAAMemBlockManmbm_xchgcreatep  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_xchgcreatep  mbm_xchgcreatep
	#define CHK_CmpCAAMemBlockManmbm_xchgcreatep  TRUE
	#define EXP_CmpCAAMemBlockManmbm_xchgcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgcreatep", (RTS_UINTPTR)mbm_xchgcreatep, 1, RTSITF_GET_SIGNATURE(0, 0x578CD111), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_xchgcreatep
	#define EXT_mbm_xchgcreatep
	#define GET_mbm_xchgcreatep(fl)  CAL_CMGETAPI( "mbm_xchgcreatep" ) 
	#define CAL_mbm_xchgcreatep  mbm_xchgcreatep
	#define CHK_mbm_xchgcreatep  TRUE
	#define EXP_mbm_xchgcreatep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgcreatep", (RTS_UINTPTR)mbm_xchgcreatep, 1, RTSITF_GET_SIGNATURE(0, 0x578CD111), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_xchgcreatep  PFMBM_XCHGCREATEP_IEC pfmbm_xchgcreatep;
	#define EXT_mbm_xchgcreatep  extern PFMBM_XCHGCREATEP_IEC pfmbm_xchgcreatep;
	#define GET_mbm_xchgcreatep(fl)  s_pfCMGetAPI2( "mbm_xchgcreatep", (RTS_VOID_FCTPTR *)&pfmbm_xchgcreatep, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x578CD111), 0x03050500)
	#define CAL_mbm_xchgcreatep  pfmbm_xchgcreatep
	#define CHK_mbm_xchgcreatep  (pfmbm_xchgcreatep != NULL)
	#define EXP_mbm_xchgcreatep   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgcreatep", (RTS_UINTPTR)mbm_xchgcreatep, 1, RTSITF_GET_SIGNATURE(0, 0x578CD111), 0x03050500) 
#endif


/**
 * Deletes an exchange created by XChgCreate 
 */
typedef struct tagmbm_xchgdelete_struct
{
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_ERROR MBM_XChgDelete;			/* VAR_OUTPUT */	
} mbm_xchgdelete_struct;

void CDECL CDECL_EXT mbm_xchgdelete(mbm_xchgdelete_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_XCHGDELETE_IEC) (mbm_xchgdelete_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGDELETE_NOTIMPLEMENTED)
	#define USE_mbm_xchgdelete
	#define EXT_mbm_xchgdelete
	#define GET_mbm_xchgdelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_xchgdelete(p0) 
	#define CHK_mbm_xchgdelete  FALSE
	#define EXP_mbm_xchgdelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_xchgdelete
	#define EXT_mbm_xchgdelete
	#define GET_mbm_xchgdelete(fl)  CAL_CMGETAPI( "mbm_xchgdelete" ) 
	#define CAL_mbm_xchgdelete  mbm_xchgdelete
	#define CHK_mbm_xchgdelete  TRUE
	#define EXP_mbm_xchgdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgdelete", (RTS_UINTPTR)mbm_xchgdelete, 1, RTSITF_GET_SIGNATURE(0, 0xB954F1E6), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_xchgdelete
	#define EXT_mbm_xchgdelete
	#define GET_mbm_xchgdelete(fl)  CAL_CMGETAPI( "mbm_xchgdelete" ) 
	#define CAL_mbm_xchgdelete  mbm_xchgdelete
	#define CHK_mbm_xchgdelete  TRUE
	#define EXP_mbm_xchgdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgdelete", (RTS_UINTPTR)mbm_xchgdelete, 1, RTSITF_GET_SIGNATURE(0, 0xB954F1E6), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_xchgdelete
	#define EXT_CmpCAAMemBlockManmbm_xchgdelete
	#define GET_CmpCAAMemBlockManmbm_xchgdelete  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_xchgdelete  mbm_xchgdelete
	#define CHK_CmpCAAMemBlockManmbm_xchgdelete  TRUE
	#define EXP_CmpCAAMemBlockManmbm_xchgdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgdelete", (RTS_UINTPTR)mbm_xchgdelete, 1, RTSITF_GET_SIGNATURE(0, 0xB954F1E6), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_xchgdelete
	#define EXT_mbm_xchgdelete
	#define GET_mbm_xchgdelete(fl)  CAL_CMGETAPI( "mbm_xchgdelete" ) 
	#define CAL_mbm_xchgdelete  mbm_xchgdelete
	#define CHK_mbm_xchgdelete  TRUE
	#define EXP_mbm_xchgdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgdelete", (RTS_UINTPTR)mbm_xchgdelete, 1, RTSITF_GET_SIGNATURE(0, 0xB954F1E6), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_xchgdelete  PFMBM_XCHGDELETE_IEC pfmbm_xchgdelete;
	#define EXT_mbm_xchgdelete  extern PFMBM_XCHGDELETE_IEC pfmbm_xchgdelete;
	#define GET_mbm_xchgdelete(fl)  s_pfCMGetAPI2( "mbm_xchgdelete", (RTS_VOID_FCTPTR *)&pfmbm_xchgdelete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB954F1E6), 0x03050500)
	#define CAL_mbm_xchgdelete  pfmbm_xchgdelete
	#define CHK_mbm_xchgdelete  (pfmbm_xchgdelete != NULL)
	#define EXP_mbm_xchgdelete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgdelete", (RTS_UINTPTR)mbm_xchgdelete, 1, RTSITF_GET_SIGNATURE(0, 0xB954F1E6), 0x03050500) 
#endif


/**
 * <description>mbm_xchgextendh</description>
 */
typedef struct tagmbm_xchgextendh_struct
{
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_COUNT ctNumMsg;					/* VAR_INPUT */	
	CAA_ERROR MBM_XChgExtendH;			/* VAR_OUTPUT */	
} mbm_xchgextendh_struct;

void CDECL CDECL_EXT mbm_xchgextendh(mbm_xchgextendh_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_XCHGEXTENDH_IEC) (mbm_xchgextendh_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGEXTENDH_NOTIMPLEMENTED)
	#define USE_mbm_xchgextendh
	#define EXT_mbm_xchgextendh
	#define GET_mbm_xchgextendh(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_xchgextendh(p0) 
	#define CHK_mbm_xchgextendh  FALSE
	#define EXP_mbm_xchgextendh  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_xchgextendh
	#define EXT_mbm_xchgextendh
	#define GET_mbm_xchgextendh(fl)  CAL_CMGETAPI( "mbm_xchgextendh" ) 
	#define CAL_mbm_xchgextendh  mbm_xchgextendh
	#define CHK_mbm_xchgextendh  TRUE
	#define EXP_mbm_xchgextendh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgextendh", (RTS_UINTPTR)mbm_xchgextendh, 1, RTSITF_GET_SIGNATURE(0, 0x9A53A368), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_xchgextendh
	#define EXT_mbm_xchgextendh
	#define GET_mbm_xchgextendh(fl)  CAL_CMGETAPI( "mbm_xchgextendh" ) 
	#define CAL_mbm_xchgextendh  mbm_xchgextendh
	#define CHK_mbm_xchgextendh  TRUE
	#define EXP_mbm_xchgextendh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgextendh", (RTS_UINTPTR)mbm_xchgextendh, 1, RTSITF_GET_SIGNATURE(0, 0x9A53A368), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_xchgextendh
	#define EXT_CmpCAAMemBlockManmbm_xchgextendh
	#define GET_CmpCAAMemBlockManmbm_xchgextendh  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_xchgextendh  mbm_xchgextendh
	#define CHK_CmpCAAMemBlockManmbm_xchgextendh  TRUE
	#define EXP_CmpCAAMemBlockManmbm_xchgextendh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgextendh", (RTS_UINTPTR)mbm_xchgextendh, 1, RTSITF_GET_SIGNATURE(0, 0x9A53A368), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_xchgextendh
	#define EXT_mbm_xchgextendh
	#define GET_mbm_xchgextendh(fl)  CAL_CMGETAPI( "mbm_xchgextendh" ) 
	#define CAL_mbm_xchgextendh  mbm_xchgextendh
	#define CHK_mbm_xchgextendh  TRUE
	#define EXP_mbm_xchgextendh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgextendh", (RTS_UINTPTR)mbm_xchgextendh, 1, RTSITF_GET_SIGNATURE(0, 0x9A53A368), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_xchgextendh  PFMBM_XCHGEXTENDH_IEC pfmbm_xchgextendh;
	#define EXT_mbm_xchgextendh  extern PFMBM_XCHGEXTENDH_IEC pfmbm_xchgextendh;
	#define GET_mbm_xchgextendh(fl)  s_pfCMGetAPI2( "mbm_xchgextendh", (RTS_VOID_FCTPTR *)&pfmbm_xchgextendh, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9A53A368), 0x03050500)
	#define CAL_mbm_xchgextendh  pfmbm_xchgextendh
	#define CHK_mbm_xchgextendh  (pfmbm_xchgextendh != NULL)
	#define EXP_mbm_xchgextendh   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgextendh", (RTS_UINTPTR)mbm_xchgextendh, 1, RTSITF_GET_SIGNATURE(0, 0x9A53A368), 0x03050500) 
#endif


/**
 * <description>mbm_xchggetsize</description>
 */
typedef struct tagmbm_xchggetsize_struct
{
	CAA_COUNT ctNumMsg;					/* VAR_INPUT */	
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_COUNT ctNumPrios;				/* VAR_INPUT */	
	CAA_SIZE MBM_XChgGetSize;			/* VAR_OUTPUT */	
} mbm_xchggetsize_struct;

void CDECL CDECL_EXT mbm_xchggetsize(mbm_xchggetsize_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_XCHGGETSIZE_IEC) (mbm_xchggetsize_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGGETSIZE_NOTIMPLEMENTED)
	#define USE_mbm_xchggetsize
	#define EXT_mbm_xchggetsize
	#define GET_mbm_xchggetsize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_xchggetsize(p0) 
	#define CHK_mbm_xchggetsize  FALSE
	#define EXP_mbm_xchggetsize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_xchggetsize
	#define EXT_mbm_xchggetsize
	#define GET_mbm_xchggetsize(fl)  CAL_CMGETAPI( "mbm_xchggetsize" ) 
	#define CAL_mbm_xchggetsize  mbm_xchggetsize
	#define CHK_mbm_xchggetsize  TRUE
	#define EXP_mbm_xchggetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchggetsize", (RTS_UINTPTR)mbm_xchggetsize, 1, RTSITF_GET_SIGNATURE(0, 0x58328040), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_xchggetsize
	#define EXT_mbm_xchggetsize
	#define GET_mbm_xchggetsize(fl)  CAL_CMGETAPI( "mbm_xchggetsize" ) 
	#define CAL_mbm_xchggetsize  mbm_xchggetsize
	#define CHK_mbm_xchggetsize  TRUE
	#define EXP_mbm_xchggetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchggetsize", (RTS_UINTPTR)mbm_xchggetsize, 1, RTSITF_GET_SIGNATURE(0, 0x58328040), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_xchggetsize
	#define EXT_CmpCAAMemBlockManmbm_xchggetsize
	#define GET_CmpCAAMemBlockManmbm_xchggetsize  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_xchggetsize  mbm_xchggetsize
	#define CHK_CmpCAAMemBlockManmbm_xchggetsize  TRUE
	#define EXP_CmpCAAMemBlockManmbm_xchggetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchggetsize", (RTS_UINTPTR)mbm_xchggetsize, 1, RTSITF_GET_SIGNATURE(0, 0x58328040), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_xchggetsize
	#define EXT_mbm_xchggetsize
	#define GET_mbm_xchggetsize(fl)  CAL_CMGETAPI( "mbm_xchggetsize" ) 
	#define CAL_mbm_xchggetsize  mbm_xchggetsize
	#define CHK_mbm_xchggetsize  TRUE
	#define EXP_mbm_xchggetsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchggetsize", (RTS_UINTPTR)mbm_xchggetsize, 1, RTSITF_GET_SIGNATURE(0, 0x58328040), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_xchggetsize  PFMBM_XCHGGETSIZE_IEC pfmbm_xchggetsize;
	#define EXT_mbm_xchggetsize  extern PFMBM_XCHGGETSIZE_IEC pfmbm_xchggetsize;
	#define GET_mbm_xchggetsize(fl)  s_pfCMGetAPI2( "mbm_xchggetsize", (RTS_VOID_FCTPTR *)&pfmbm_xchggetsize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x58328040), 0x03050500)
	#define CAL_mbm_xchggetsize  pfmbm_xchggetsize
	#define CHK_mbm_xchggetsize  (pfmbm_xchggetsize != NULL)
	#define EXP_mbm_xchggetsize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchggetsize", (RTS_UINTPTR)mbm_xchggetsize, 1, RTSITF_GET_SIGNATURE(0, 0x58328040), 0x03050500) 
#endif


/**
 * <description>mbm_xchgisempty</description>
 */
typedef struct tagmbm_xchgisempty_struct
{
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_BOOL MBM_XChgIsEmpty;			/* VAR_OUTPUT */	
} mbm_xchgisempty_struct;

void CDECL CDECL_EXT mbm_xchgisempty(mbm_xchgisempty_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_XCHGISEMPTY_IEC) (mbm_xchgisempty_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGISEMPTY_NOTIMPLEMENTED)
	#define USE_mbm_xchgisempty
	#define EXT_mbm_xchgisempty
	#define GET_mbm_xchgisempty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_xchgisempty(p0) 
	#define CHK_mbm_xchgisempty  FALSE
	#define EXP_mbm_xchgisempty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_xchgisempty
	#define EXT_mbm_xchgisempty
	#define GET_mbm_xchgisempty(fl)  CAL_CMGETAPI( "mbm_xchgisempty" ) 
	#define CAL_mbm_xchgisempty  mbm_xchgisempty
	#define CHK_mbm_xchgisempty  TRUE
	#define EXP_mbm_xchgisempty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgisempty", (RTS_UINTPTR)mbm_xchgisempty, 1, RTSITF_GET_SIGNATURE(0, 0xF693F781), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_xchgisempty
	#define EXT_mbm_xchgisempty
	#define GET_mbm_xchgisempty(fl)  CAL_CMGETAPI( "mbm_xchgisempty" ) 
	#define CAL_mbm_xchgisempty  mbm_xchgisempty
	#define CHK_mbm_xchgisempty  TRUE
	#define EXP_mbm_xchgisempty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgisempty", (RTS_UINTPTR)mbm_xchgisempty, 1, RTSITF_GET_SIGNATURE(0, 0xF693F781), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_xchgisempty
	#define EXT_CmpCAAMemBlockManmbm_xchgisempty
	#define GET_CmpCAAMemBlockManmbm_xchgisempty  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_xchgisempty  mbm_xchgisempty
	#define CHK_CmpCAAMemBlockManmbm_xchgisempty  TRUE
	#define EXP_CmpCAAMemBlockManmbm_xchgisempty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgisempty", (RTS_UINTPTR)mbm_xchgisempty, 1, RTSITF_GET_SIGNATURE(0, 0xF693F781), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_xchgisempty
	#define EXT_mbm_xchgisempty
	#define GET_mbm_xchgisempty(fl)  CAL_CMGETAPI( "mbm_xchgisempty" ) 
	#define CAL_mbm_xchgisempty  mbm_xchgisempty
	#define CHK_mbm_xchgisempty  TRUE
	#define EXP_mbm_xchgisempty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgisempty", (RTS_UINTPTR)mbm_xchgisempty, 1, RTSITF_GET_SIGNATURE(0, 0xF693F781), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_xchgisempty  PFMBM_XCHGISEMPTY_IEC pfmbm_xchgisempty;
	#define EXT_mbm_xchgisempty  extern PFMBM_XCHGISEMPTY_IEC pfmbm_xchgisempty;
	#define GET_mbm_xchgisempty(fl)  s_pfCMGetAPI2( "mbm_xchgisempty", (RTS_VOID_FCTPTR *)&pfmbm_xchgisempty, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF693F781), 0x03050500)
	#define CAL_mbm_xchgisempty  pfmbm_xchgisempty
	#define CHK_mbm_xchgisempty  (pfmbm_xchgisempty != NULL)
	#define EXP_mbm_xchgisempty   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgisempty", (RTS_UINTPTR)mbm_xchgisempty, 1, RTSITF_GET_SIGNATURE(0, 0xF693F781), 0x03050500) 
#endif


/**
 * <description>mbm_xchgmsgleft</description>
 */
typedef struct tagmbm_xchgmsgleft_struct
{
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_COUNT MBM_XChgMsgLeft;			/* VAR_OUTPUT */	
} mbm_xchgmsgleft_struct;

void CDECL CDECL_EXT mbm_xchgmsgleft(mbm_xchgmsgleft_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_XCHGMSGLEFT_IEC) (mbm_xchgmsgleft_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_XCHGMSGLEFT_NOTIMPLEMENTED)
	#define USE_mbm_xchgmsgleft
	#define EXT_mbm_xchgmsgleft
	#define GET_mbm_xchgmsgleft(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_xchgmsgleft(p0) 
	#define CHK_mbm_xchgmsgleft  FALSE
	#define EXP_mbm_xchgmsgleft  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_xchgmsgleft
	#define EXT_mbm_xchgmsgleft
	#define GET_mbm_xchgmsgleft(fl)  CAL_CMGETAPI( "mbm_xchgmsgleft" ) 
	#define CAL_mbm_xchgmsgleft  mbm_xchgmsgleft
	#define CHK_mbm_xchgmsgleft  TRUE
	#define EXP_mbm_xchgmsgleft  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgmsgleft", (RTS_UINTPTR)mbm_xchgmsgleft, 1, RTSITF_GET_SIGNATURE(0, 0xC98A455C), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_xchgmsgleft
	#define EXT_mbm_xchgmsgleft
	#define GET_mbm_xchgmsgleft(fl)  CAL_CMGETAPI( "mbm_xchgmsgleft" ) 
	#define CAL_mbm_xchgmsgleft  mbm_xchgmsgleft
	#define CHK_mbm_xchgmsgleft  TRUE
	#define EXP_mbm_xchgmsgleft  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgmsgleft", (RTS_UINTPTR)mbm_xchgmsgleft, 1, RTSITF_GET_SIGNATURE(0, 0xC98A455C), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_xchgmsgleft
	#define EXT_CmpCAAMemBlockManmbm_xchgmsgleft
	#define GET_CmpCAAMemBlockManmbm_xchgmsgleft  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_xchgmsgleft  mbm_xchgmsgleft
	#define CHK_CmpCAAMemBlockManmbm_xchgmsgleft  TRUE
	#define EXP_CmpCAAMemBlockManmbm_xchgmsgleft  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgmsgleft", (RTS_UINTPTR)mbm_xchgmsgleft, 1, RTSITF_GET_SIGNATURE(0, 0xC98A455C), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_xchgmsgleft
	#define EXT_mbm_xchgmsgleft
	#define GET_mbm_xchgmsgleft(fl)  CAL_CMGETAPI( "mbm_xchgmsgleft" ) 
	#define CAL_mbm_xchgmsgleft  mbm_xchgmsgleft
	#define CHK_mbm_xchgmsgleft  TRUE
	#define EXP_mbm_xchgmsgleft  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgmsgleft", (RTS_UINTPTR)mbm_xchgmsgleft, 1, RTSITF_GET_SIGNATURE(0, 0xC98A455C), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_xchgmsgleft  PFMBM_XCHGMSGLEFT_IEC pfmbm_xchgmsgleft;
	#define EXT_mbm_xchgmsgleft  extern PFMBM_XCHGMSGLEFT_IEC pfmbm_xchgmsgleft;
	#define GET_mbm_xchgmsgleft(fl)  s_pfCMGetAPI2( "mbm_xchgmsgleft", (RTS_VOID_FCTPTR *)&pfmbm_xchgmsgleft, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC98A455C), 0x03050500)
	#define CAL_mbm_xchgmsgleft  pfmbm_xchgmsgleft
	#define CHK_mbm_xchgmsgleft  (pfmbm_xchgmsgleft != NULL)
	#define EXP_mbm_xchgmsgleft   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_xchgmsgleft", (RTS_UINTPTR)mbm_xchgmsgleft, 1, RTSITF_GET_SIGNATURE(0, 0xC98A455C), 0x03050500) 
#endif


/**
 * <description>mbm_getsupplierversion</description>
 */
typedef struct tagmbm_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD MBM_GetSupplierVersion;	/* VAR_OUTPUT */	
} mbm_getsupplierversion_struct;

void CDECL CDECL_EXT mbm_getsupplierversion(mbm_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFMBM_GETSUPPLIERVERSION_IEC) (mbm_getsupplierversion_struct *p);
#if defined(CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED) || defined(MBM_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_mbm_getsupplierversion
	#define EXT_mbm_getsupplierversion
	#define GET_mbm_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_mbm_getsupplierversion(p0) 
	#define CHK_mbm_getsupplierversion  FALSE
	#define EXP_mbm_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_mbm_getsupplierversion
	#define EXT_mbm_getsupplierversion
	#define GET_mbm_getsupplierversion(fl)  CAL_CMGETAPI( "mbm_getsupplierversion" ) 
	#define CAL_mbm_getsupplierversion  mbm_getsupplierversion
	#define CHK_mbm_getsupplierversion  TRUE
	#define EXP_mbm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_getsupplierversion", (RTS_UINTPTR)mbm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x83993EFD), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAAMEMBLOCKMAN_EXTERNAL)
	#define USE_mbm_getsupplierversion
	#define EXT_mbm_getsupplierversion
	#define GET_mbm_getsupplierversion(fl)  CAL_CMGETAPI( "mbm_getsupplierversion" ) 
	#define CAL_mbm_getsupplierversion  mbm_getsupplierversion
	#define CHK_mbm_getsupplierversion  TRUE
	#define EXP_mbm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_getsupplierversion", (RTS_UINTPTR)mbm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x83993EFD), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAMemBlockManmbm_getsupplierversion
	#define EXT_CmpCAAMemBlockManmbm_getsupplierversion
	#define GET_CmpCAAMemBlockManmbm_getsupplierversion  ERR_OK
	#define CAL_CmpCAAMemBlockManmbm_getsupplierversion  mbm_getsupplierversion
	#define CHK_CmpCAAMemBlockManmbm_getsupplierversion  TRUE
	#define EXP_CmpCAAMemBlockManmbm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_getsupplierversion", (RTS_UINTPTR)mbm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x83993EFD), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_mbm_getsupplierversion
	#define EXT_mbm_getsupplierversion
	#define GET_mbm_getsupplierversion(fl)  CAL_CMGETAPI( "mbm_getsupplierversion" ) 
	#define CAL_mbm_getsupplierversion  mbm_getsupplierversion
	#define CHK_mbm_getsupplierversion  TRUE
	#define EXP_mbm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_getsupplierversion", (RTS_UINTPTR)mbm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x83993EFD), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_mbm_getsupplierversion  PFMBM_GETSUPPLIERVERSION_IEC pfmbm_getsupplierversion;
	#define EXT_mbm_getsupplierversion  extern PFMBM_GETSUPPLIERVERSION_IEC pfmbm_getsupplierversion;
	#define GET_mbm_getsupplierversion(fl)  s_pfCMGetAPI2( "mbm_getsupplierversion", (RTS_VOID_FCTPTR *)&pfmbm_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x83993EFD), 0x03050500)
	#define CAL_mbm_getsupplierversion  pfmbm_getsupplierversion
	#define CHK_mbm_getsupplierversion  (pfmbm_getsupplierversion != NULL)
	#define EXP_mbm_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"mbm_getsupplierversion", (RTS_UINTPTR)mbm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x83993EFD), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
	PFMBM_POOLCREATEH IMBM_PoolCreateH;
 	PFMBM_POOLCREATEP IMBM_PoolCreateP;
 	PFMBM_POOLEXTENDH IMBM_PoolExtendH;
 	PFMBM_POOLDELETE IMBM_PoolDelete;
 	PFMBM_POOLGETBLOCK IMBM_PoolGetBlock;
 	PFMBM_BLOCKGETDATA IMBM_BlockGetData;
 	PFMBM_POOLPUTBLOCK IMBM_PoolPutBlock;
 	PFMBM_POOLGETSIZE IMBM_PoolGetSize;
 	PFMBM_MSGRECEIVE IMBM_MsgReceive;
 	PFMBM_MSGGETDATA IMBM_MsgGetData;
 	PFMBM_MSGSEND IMBM_MsgSend;
 	PFMBM_MSGADDREF IMBM_MsgAddRef;
 	PFMBM_MSGRELEASE IMBM_MsgRelease;
 	PFMBM_MSGRELEASEEX IMBM_MsgReleaseEx;
 	PFMBM_MSGCLONE IMBM_MsgClone;
 	PFMBM_XCHGCREATEH IMBM_XChgCreateH;
 	PFMBM_XCHGCREATEP IMBM_XChgCreateP;
 	PFMBM_XCHGEXTENDH IMBM_XChgExtendH;
 	PFMBM_XCHGDELETE IMBM_XChgDelete;
 	PFMBM_XCHGDELETE2 IMBM_XChgDelete2;
 	PFMBM_XCHGGETSIZE IMBM_XChgGetSize;
 	PFMBM_XCHGISEMPTY IMBM_XChgIsEmpty;
 	PFMBM_XCHGMSGLEFT IMBM_XChgMsgLeft;
 	PFMBM_FLATCREATEH IMBM_FlatCreateH;
 	PFMBM_FLATCREATEP IMBM_FlatCreateP;
 	PFMBM_FLATENABLE IMBM_FlatEnable;
 	PFMBM_FLATDISABLE IMBM_FlatDisable;
 	PFMBM_FLATTEST IMBM_FlatTest;
 	PFMBM_FLATUPDATE IMBM_FlatUpdate;
 	PFMBM_FLATREAD IMBM_FlatRead;
 	PFMBM_FLATDELETE IMBM_FlatDelete;
 	PFMBM_FLATGETSIZE IMBM_FlatGetSize;
 	PFMBM_RLSTCREATEH IMBM_RLstCreateH;
 	PFMBM_RLSTCREATEP IMBM_RLstCreateP;
 	PFMBM_RLSTADDPRIO IMBM_RLstAddPrio;
 	PFMBM_RLSTREMOVEPRIO IMBM_RLstRemovePrio;
 	PFMBM_RLSTGETHIGHESTPRIO IMBM_RLstGetHighestPrio;
 	PFMBM_RLSTCHECKPRIO IMBM_RLstCheckPrio;
 	PFMBM_RLSTDELETE IMBM_RLstDelete;
 	PFMBM_RLSTGETSIZE IMBM_RLstGetSize;
 	PFMBM_GETSUPPLIERVERSION IMBM_GetSupplierVersion;
 } ICmpCAAMemBlockMan_C;

#ifdef CPLUSPLUS
class ICmpCAAMemBlockMan : public IBase
{
	public:
		virtual CAA_HANDLE CDECL IMBM_PoolCreateH(CAA_COUNT ctNumBlocks, CAA_SIZE szBlockSize, CAA_ENUM eEmpty, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL IMBM_PoolCreateP(CAA_SIZE szBlockSize, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ENUM eEmpty, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IMBM_PoolExtendH(CAA_HANDLE hPool, CAA_COUNT ctNumBlocks) =0;
		virtual CAA_ERROR CDECL IMBM_PoolDelete(CAA_HANDLE hPool) =0;
		virtual CAA_HANDLE CDECL IMBM_PoolGetBlock(CAA_HANDLE hPool, CAA_ERROR* peError) =0;
		virtual CAA_PVOID CDECL IMBM_BlockGetData(CAA_HANDLE hBlock, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IMBM_PoolPutBlock(CAA_HANDLE hBlock) =0;
		virtual CAA_SIZE CDECL IMBM_PoolGetSize(CAA_COUNT ctNumBlocks, CAA_SIZE szBlockSize) =0;
		virtual CAA_HANDLE CDECL IMBM_MsgReceive(CAA_HANDLE hXChg, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError) =0;
		virtual CAA_PVOID CDECL IMBM_MsgGetData(CAA_HANDLE hMsg, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IMBM_MsgSend(CAA_HANDLE hMsg, unsigned char ucPrio, CAA_HANDLE hXChg) =0;
		virtual CAA_ERROR CDECL IMBM_MsgAddRef(CAA_HANDLE hMsg) =0;
		virtual CAA_ERROR CDECL IMBM_MsgRelease(CAA_HANDLE hMsg) =0;
		virtual CAA_ERROR CDECL IMBM_MsgReleaseEx(CAA_HANDLE hMsg, CAA_HANDLE hXChg) =0;
		virtual CAA_HANDLE CDECL IMBM_MsgClone(CAA_HANDLE hMsg, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL IMBM_XChgCreateH(CAA_COUNT ctNumMsg, CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios, CAA_ENUM eSendMsg, CAA_ENUM eReceiveMsg, CAA_ENUM eXChgEmpty, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL IMBM_XChgCreateP(CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ENUM eSendMsg, CAA_ENUM eReceiveMsg, CAA_ENUM eXChgEmpty, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IMBM_XChgExtendH(CAA_HANDLE hXChg, CAA_COUNT ctNumBlocks) =0;
		virtual CAA_ERROR CDECL IMBM_XChgDelete(CAA_HANDLE hXChg) =0;
		virtual CAA_ERROR CDECL IMBM_XChgDelete2(CAA_HANDLE hXChg, CAA_BOOL xForce) =0;
		virtual CAA_SIZE CDECL IMBM_XChgGetSize(CAA_COUNT ctNumMsg, CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios) =0;
		virtual CAA_BOOL CDECL IMBM_XChgIsEmpty(CAA_HANDLE hXChg, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL IMBM_XChgMsgLeft(CAA_HANDLE hXChg, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL IMBM_FlatCreateH(CAA_IDENT idMinKey, CAA_IDENT idMaxKey, CAA_COUNT ctNumKeys, CAA_ENUM eEnable, CAA_ENUM eDisable, CAA_ENUM eUpdate, CAA_ENUM eRead, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL IMBM_FlatCreateP(CAA_IDENT idMinKey, CAA_IDENT idMaxKey, CAA_COUNT ctNumKeys, CAA_SIZE szMemory, CAA_PVOID pMemory, CAA_ENUM eEnable, CAA_ENUM eDisable, CAA_ENUM eUpdate, CAA_ENUM eRead, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IMBM_FlatEnable(CAA_HANDLE hFlat, CAA_IDENT idKey) =0;
		virtual CAA_HANDLE CDECL IMBM_FlatDisable(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError) =0;
		virtual CAA_BOOL CDECL IMBM_FlatTest(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL IMBM_FlatUpdate(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_HANDLE hMsg, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL IMBM_FlatRead(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IMBM_FlatDelete(CAA_HANDLE hFlat) =0;
		virtual CAA_SIZE CDECL IMBM_FlatGetSize(CAA_COUNT ctNumKeys) =0;
		virtual CAA_HANDLE CDECL IMBM_RLstCreateH(CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL IMBM_RLstCreateP(CAA_SIZE szMemory, CAA_PVOID pMemory, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IMBM_RLstAddPrio(CAA_HANDLE hRLst, unsigned char ucPrio) =0;
		virtual CAA_ERROR CDECL IMBM_RLstRemovePrio(CAA_HANDLE hRLst, unsigned char ucPrio) =0;
		virtual unsigned char CDECL IMBM_RLstGetHighestPrio(CAA_HANDLE hRLst, CAA_ERROR* peError) =0;
		virtual CAA_BOOL CDECL IMBM_RLstCheckPrio(CAA_HANDLE hRLst, unsigned char ucPrio, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IMBM_RLstDelete(CAA_HANDLE hRLst) =0;
		virtual CAA_SIZE CDECL IMBM_RLstGetSize(CAA_BOOL xDummy) =0;
		virtual unsigned short CDECL IMBM_GetSupplierVersion(CAA_BOOL xDummy) =0;
};
	#ifndef ITF_CmpCAAMemBlockMan
		#define ITF_CmpCAAMemBlockMan static ICmpCAAMemBlockMan *pICmpCAAMemBlockMan = NULL;
	#endif
	#define EXTITF_CmpCAAMemBlockMan
#else	/*CPLUSPLUS*/
	typedef ICmpCAAMemBlockMan_C		ICmpCAAMemBlockMan;
	#ifndef ITF_CmpCAAMemBlockMan
		#define ITF_CmpCAAMemBlockMan
	#endif
	#define EXTITF_CmpCAAMemBlockMan
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAAMEMBLOCKMANITF_H_*/
