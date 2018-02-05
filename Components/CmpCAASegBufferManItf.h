 
	
	
#ifndef _CMPCAASEGBUFFERMANITF_H_
#define _CMPCAASEGBUFFERMANITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAASegBufferMan.h"


#ifdef __cplusplus
extern "C" {
#endif

CAA_ERROR CDECL SBM_Init(void);
typedef CAA_ERROR (CDECL * PFSBM_INIT) (void);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_INIT_NOTIMPLEMENTED)
	#define USE_SBM_Init
	#define EXT_SBM_Init
	#define GET_SBM_Init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_Init()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SBM_Init  FALSE
	#define EXP_SBM_Init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_Init
	#define EXT_SBM_Init
	#define GET_SBM_Init(fl)  CAL_CMGETAPI( "SBM_Init" ) 
	#define CAL_SBM_Init  SBM_Init
	#define CHK_SBM_Init  TRUE
	#define EXP_SBM_Init  CAL_CMEXPAPI( "SBM_Init" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_Init
	#define EXT_SBM_Init
	#define GET_SBM_Init(fl)  CAL_CMGETAPI( "SBM_Init" ) 
	#define CAL_SBM_Init  SBM_Init
	#define CHK_SBM_Init  TRUE
	#define EXP_SBM_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_Init", (RTS_UINTPTR)SBM_Init, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_Init
	#define EXT_CmpCAASegBufferManSBM_Init
	#define GET_CmpCAASegBufferManSBM_Init  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_Init pICmpCAASegBufferMan->ISBM_Init
	#define CHK_CmpCAASegBufferManSBM_Init (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_Init  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_Init
	#define EXT_SBM_Init
	#define GET_SBM_Init(fl)  CAL_CMGETAPI( "SBM_Init" ) 
	#define CAL_SBM_Init pICmpCAASegBufferMan->ISBM_Init
	#define CHK_SBM_Init (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_Init  CAL_CMEXPAPI( "SBM_Init" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_Init  PFSBM_INIT pfSBM_Init;
	#define EXT_SBM_Init  extern PFSBM_INIT pfSBM_Init;
	#define GET_SBM_Init(fl)  s_pfCMGetAPI2( "SBM_Init", (RTS_VOID_FCTPTR *)&pfSBM_Init, (fl), 0, 0)
	#define CAL_SBM_Init  pfSBM_Init
	#define CHK_SBM_Init  (pfSBM_Init != NULL)
	#define EXP_SBM_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_Init", (RTS_UINTPTR)SBM_Init, 0, 0) 
#endif



CAA_ERROR CDECL SBM_Exit(void);
typedef CAA_ERROR (CDECL * PFSBM_EXIT) (void);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_EXIT_NOTIMPLEMENTED)
	#define USE_SBM_Exit
	#define EXT_SBM_Exit
	#define GET_SBM_Exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_Exit()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SBM_Exit  FALSE
	#define EXP_SBM_Exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_Exit
	#define EXT_SBM_Exit
	#define GET_SBM_Exit(fl)  CAL_CMGETAPI( "SBM_Exit" ) 
	#define CAL_SBM_Exit  SBM_Exit
	#define CHK_SBM_Exit  TRUE
	#define EXP_SBM_Exit  CAL_CMEXPAPI( "SBM_Exit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_Exit
	#define EXT_SBM_Exit
	#define GET_SBM_Exit(fl)  CAL_CMGETAPI( "SBM_Exit" ) 
	#define CAL_SBM_Exit  SBM_Exit
	#define CHK_SBM_Exit  TRUE
	#define EXP_SBM_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_Exit", (RTS_UINTPTR)SBM_Exit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_Exit
	#define EXT_CmpCAASegBufferManSBM_Exit
	#define GET_CmpCAASegBufferManSBM_Exit  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_Exit pICmpCAASegBufferMan->ISBM_Exit
	#define CHK_CmpCAASegBufferManSBM_Exit (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_Exit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_Exit
	#define EXT_SBM_Exit
	#define GET_SBM_Exit(fl)  CAL_CMGETAPI( "SBM_Exit" ) 
	#define CAL_SBM_Exit pICmpCAASegBufferMan->ISBM_Exit
	#define CHK_SBM_Exit (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_Exit  CAL_CMEXPAPI( "SBM_Exit" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_Exit  PFSBM_EXIT pfSBM_Exit;
	#define EXT_SBM_Exit  extern PFSBM_EXIT pfSBM_Exit;
	#define GET_SBM_Exit(fl)  s_pfCMGetAPI2( "SBM_Exit", (RTS_VOID_FCTPTR *)&pfSBM_Exit, (fl), 0, 0)
	#define CAL_SBM_Exit  pfSBM_Exit
	#define CHK_SBM_Exit  (pfSBM_Exit != NULL)
	#define EXP_SBM_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_Exit", (RTS_UINTPTR)SBM_Exit, 0, 0) 
#endif




SBM_PBUFFER CDECL SBM_ChainBuffer(SBM_PBUFFER pHead, SBM_PBUFFER pTail, CAA_ERROR* peError);
typedef SBM_PBUFFER (CDECL * PFSBM_CHAINBUFFER) (SBM_PBUFFER pHead, SBM_PBUFFER pTail, CAA_ERROR* peError);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_CHAINBUFFER_NOTIMPLEMENTED)
	#define USE_SBM_ChainBuffer
	#define EXT_SBM_ChainBuffer
	#define GET_SBM_ChainBuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_ChainBuffer(p0,p1,p2)  (SBM_PBUFFER)ERR_NOTIMPLEMENTED
	#define CHK_SBM_ChainBuffer  FALSE
	#define EXP_SBM_ChainBuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_ChainBuffer
	#define EXT_SBM_ChainBuffer
	#define GET_SBM_ChainBuffer(fl)  CAL_CMGETAPI( "SBM_ChainBuffer" ) 
	#define CAL_SBM_ChainBuffer  SBM_ChainBuffer
	#define CHK_SBM_ChainBuffer  TRUE
	#define EXP_SBM_ChainBuffer  CAL_CMEXPAPI( "SBM_ChainBuffer" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_ChainBuffer
	#define EXT_SBM_ChainBuffer
	#define GET_SBM_ChainBuffer(fl)  CAL_CMGETAPI( "SBM_ChainBuffer" ) 
	#define CAL_SBM_ChainBuffer  SBM_ChainBuffer
	#define CHK_SBM_ChainBuffer  TRUE
	#define EXP_SBM_ChainBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_ChainBuffer", (RTS_UINTPTR)SBM_ChainBuffer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_ChainBuffer
	#define EXT_CmpCAASegBufferManSBM_ChainBuffer
	#define GET_CmpCAASegBufferManSBM_ChainBuffer  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_ChainBuffer pICmpCAASegBufferMan->ISBM_ChainBuffer
	#define CHK_CmpCAASegBufferManSBM_ChainBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_ChainBuffer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_ChainBuffer
	#define EXT_SBM_ChainBuffer
	#define GET_SBM_ChainBuffer(fl)  CAL_CMGETAPI( "SBM_ChainBuffer" ) 
	#define CAL_SBM_ChainBuffer pICmpCAASegBufferMan->ISBM_ChainBuffer
	#define CHK_SBM_ChainBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_ChainBuffer  CAL_CMEXPAPI( "SBM_ChainBuffer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_ChainBuffer  PFSBM_CHAINBUFFER pfSBM_ChainBuffer;
	#define EXT_SBM_ChainBuffer  extern PFSBM_CHAINBUFFER pfSBM_ChainBuffer;
	#define GET_SBM_ChainBuffer(fl)  s_pfCMGetAPI2( "SBM_ChainBuffer", (RTS_VOID_FCTPTR *)&pfSBM_ChainBuffer, (fl), 0, 0)
	#define CAL_SBM_ChainBuffer  pfSBM_ChainBuffer
	#define CHK_SBM_ChainBuffer  (pfSBM_ChainBuffer != NULL)
	#define EXP_SBM_ChainBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_ChainBuffer", (RTS_UINTPTR)SBM_ChainBuffer, 0, 0) 
#endif



CAA_ERROR CDECL SBM_CopyBufferData(SBM_PBUFFER pBuffer, CAA_SIZE szOffset, CAA_SIZE szLength, CAA_PVOID pData, CAA_SIZE szSize);
typedef CAA_ERROR (CDECL * PFSBM_COPYBUFFERDATA) (SBM_PBUFFER pBuffer, CAA_SIZE szOffset, CAA_SIZE szLength, CAA_PVOID pData, CAA_SIZE szSize);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_COPYBUFFERDATA_NOTIMPLEMENTED)
	#define USE_SBM_CopyBufferData
	#define EXT_SBM_CopyBufferData
	#define GET_SBM_CopyBufferData(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_CopyBufferData(p0,p1,p2,p3,p4)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SBM_CopyBufferData  FALSE
	#define EXP_SBM_CopyBufferData  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_CopyBufferData
	#define EXT_SBM_CopyBufferData
	#define GET_SBM_CopyBufferData(fl)  CAL_CMGETAPI( "SBM_CopyBufferData" ) 
	#define CAL_SBM_CopyBufferData  SBM_CopyBufferData
	#define CHK_SBM_CopyBufferData  TRUE
	#define EXP_SBM_CopyBufferData  CAL_CMEXPAPI( "SBM_CopyBufferData" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_CopyBufferData
	#define EXT_SBM_CopyBufferData
	#define GET_SBM_CopyBufferData(fl)  CAL_CMGETAPI( "SBM_CopyBufferData" ) 
	#define CAL_SBM_CopyBufferData  SBM_CopyBufferData
	#define CHK_SBM_CopyBufferData  TRUE
	#define EXP_SBM_CopyBufferData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_CopyBufferData", (RTS_UINTPTR)SBM_CopyBufferData, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_CopyBufferData
	#define EXT_CmpCAASegBufferManSBM_CopyBufferData
	#define GET_CmpCAASegBufferManSBM_CopyBufferData  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_CopyBufferData pICmpCAASegBufferMan->ISBM_CopyBufferData
	#define CHK_CmpCAASegBufferManSBM_CopyBufferData (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_CopyBufferData  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_CopyBufferData
	#define EXT_SBM_CopyBufferData
	#define GET_SBM_CopyBufferData(fl)  CAL_CMGETAPI( "SBM_CopyBufferData" ) 
	#define CAL_SBM_CopyBufferData pICmpCAASegBufferMan->ISBM_CopyBufferData
	#define CHK_SBM_CopyBufferData (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_CopyBufferData  CAL_CMEXPAPI( "SBM_CopyBufferData" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_CopyBufferData  PFSBM_COPYBUFFERDATA pfSBM_CopyBufferData;
	#define EXT_SBM_CopyBufferData  extern PFSBM_COPYBUFFERDATA pfSBM_CopyBufferData;
	#define GET_SBM_CopyBufferData(fl)  s_pfCMGetAPI2( "SBM_CopyBufferData", (RTS_VOID_FCTPTR *)&pfSBM_CopyBufferData, (fl), 0, 0)
	#define CAL_SBM_CopyBufferData  pfSBM_CopyBufferData
	#define CHK_SBM_CopyBufferData  (pfSBM_CopyBufferData != NULL)
	#define EXP_SBM_CopyBufferData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_CopyBufferData", (RTS_UINTPTR)SBM_CopyBufferData, 0, 0) 
#endif



SBM_PBUFFER CDECL SBM_CreateBuffer(CAA_SIZE szSize, CAA_PVOID pData, CAA_BOOL xPermanent, CAA_ERROR* peError);
typedef SBM_PBUFFER (CDECL * PFSBM_CREATEBUFFER) (CAA_SIZE szSize, CAA_PVOID pData, CAA_BOOL xPermanent, CAA_ERROR* peError);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_CREATEBUFFER_NOTIMPLEMENTED)
	#define USE_SBM_CreateBuffer
	#define EXT_SBM_CreateBuffer
	#define GET_SBM_CreateBuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_CreateBuffer(p0,p1,p2,p3)  (SBM_PBUFFER)ERR_NOTIMPLEMENTED
	#define CHK_SBM_CreateBuffer  FALSE
	#define EXP_SBM_CreateBuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_CreateBuffer
	#define EXT_SBM_CreateBuffer
	#define GET_SBM_CreateBuffer(fl)  CAL_CMGETAPI( "SBM_CreateBuffer" ) 
	#define CAL_SBM_CreateBuffer  SBM_CreateBuffer
	#define CHK_SBM_CreateBuffer  TRUE
	#define EXP_SBM_CreateBuffer  CAL_CMEXPAPI( "SBM_CreateBuffer" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_CreateBuffer
	#define EXT_SBM_CreateBuffer
	#define GET_SBM_CreateBuffer(fl)  CAL_CMGETAPI( "SBM_CreateBuffer" ) 
	#define CAL_SBM_CreateBuffer  SBM_CreateBuffer
	#define CHK_SBM_CreateBuffer  TRUE
	#define EXP_SBM_CreateBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_CreateBuffer", (RTS_UINTPTR)SBM_CreateBuffer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_CreateBuffer
	#define EXT_CmpCAASegBufferManSBM_CreateBuffer
	#define GET_CmpCAASegBufferManSBM_CreateBuffer  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_CreateBuffer pICmpCAASegBufferMan->ISBM_CreateBuffer
	#define CHK_CmpCAASegBufferManSBM_CreateBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_CreateBuffer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_CreateBuffer
	#define EXT_SBM_CreateBuffer
	#define GET_SBM_CreateBuffer(fl)  CAL_CMGETAPI( "SBM_CreateBuffer" ) 
	#define CAL_SBM_CreateBuffer pICmpCAASegBufferMan->ISBM_CreateBuffer
	#define CHK_SBM_CreateBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_CreateBuffer  CAL_CMEXPAPI( "SBM_CreateBuffer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_CreateBuffer  PFSBM_CREATEBUFFER pfSBM_CreateBuffer;
	#define EXT_SBM_CreateBuffer  extern PFSBM_CREATEBUFFER pfSBM_CreateBuffer;
	#define GET_SBM_CreateBuffer(fl)  s_pfCMGetAPI2( "SBM_CreateBuffer", (RTS_VOID_FCTPTR *)&pfSBM_CreateBuffer, (fl), 0, 0)
	#define CAL_SBM_CreateBuffer  pfSBM_CreateBuffer
	#define CHK_SBM_CreateBuffer  (pfSBM_CreateBuffer != NULL)
	#define EXP_SBM_CreateBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_CreateBuffer", (RTS_UINTPTR)SBM_CreateBuffer, 0, 0) 
#endif



CAA_ERROR CDECL SBM_DeleteBuffer(SBM_PBUFFER pBuffer);
typedef CAA_ERROR (CDECL * PFSBM_DELETEBUFFER) (SBM_PBUFFER pBuffer);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_DELETEBUFFER_NOTIMPLEMENTED)
	#define USE_SBM_DeleteBuffer
	#define EXT_SBM_DeleteBuffer
	#define GET_SBM_DeleteBuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_DeleteBuffer(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SBM_DeleteBuffer  FALSE
	#define EXP_SBM_DeleteBuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_DeleteBuffer
	#define EXT_SBM_DeleteBuffer
	#define GET_SBM_DeleteBuffer(fl)  CAL_CMGETAPI( "SBM_DeleteBuffer" ) 
	#define CAL_SBM_DeleteBuffer  SBM_DeleteBuffer
	#define CHK_SBM_DeleteBuffer  TRUE
	#define EXP_SBM_DeleteBuffer  CAL_CMEXPAPI( "SBM_DeleteBuffer" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_DeleteBuffer
	#define EXT_SBM_DeleteBuffer
	#define GET_SBM_DeleteBuffer(fl)  CAL_CMGETAPI( "SBM_DeleteBuffer" ) 
	#define CAL_SBM_DeleteBuffer  SBM_DeleteBuffer
	#define CHK_SBM_DeleteBuffer  TRUE
	#define EXP_SBM_DeleteBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_DeleteBuffer", (RTS_UINTPTR)SBM_DeleteBuffer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_DeleteBuffer
	#define EXT_CmpCAASegBufferManSBM_DeleteBuffer
	#define GET_CmpCAASegBufferManSBM_DeleteBuffer  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_DeleteBuffer pICmpCAASegBufferMan->ISBM_DeleteBuffer
	#define CHK_CmpCAASegBufferManSBM_DeleteBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_DeleteBuffer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_DeleteBuffer
	#define EXT_SBM_DeleteBuffer
	#define GET_SBM_DeleteBuffer(fl)  CAL_CMGETAPI( "SBM_DeleteBuffer" ) 
	#define CAL_SBM_DeleteBuffer pICmpCAASegBufferMan->ISBM_DeleteBuffer
	#define CHK_SBM_DeleteBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_DeleteBuffer  CAL_CMEXPAPI( "SBM_DeleteBuffer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_DeleteBuffer  PFSBM_DELETEBUFFER pfSBM_DeleteBuffer;
	#define EXT_SBM_DeleteBuffer  extern PFSBM_DELETEBUFFER pfSBM_DeleteBuffer;
	#define GET_SBM_DeleteBuffer(fl)  s_pfCMGetAPI2( "SBM_DeleteBuffer", (RTS_VOID_FCTPTR *)&pfSBM_DeleteBuffer, (fl), 0, 0)
	#define CAL_SBM_DeleteBuffer  pfSBM_DeleteBuffer
	#define CHK_SBM_DeleteBuffer  (pfSBM_DeleteBuffer != NULL)
	#define EXP_SBM_DeleteBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_DeleteBuffer", (RTS_UINTPTR)SBM_DeleteBuffer, 0, 0) 
#endif



CAA_ERROR CDECL SBM_BufferAddRef(SBM_PBUFFER pBuffer);
typedef CAA_ERROR (CDECL * PFSBM_BUFFERADDREF) (SBM_PBUFFER pBuffer);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_BUFFERADDREF_NOTIMPLEMENTED)
	#define USE_SBM_BufferAddRef
	#define EXT_SBM_BufferAddRef
	#define GET_SBM_BufferAddRef(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_BufferAddRef(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SBM_BufferAddRef  FALSE
	#define EXP_SBM_BufferAddRef  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_BufferAddRef
	#define EXT_SBM_BufferAddRef
	#define GET_SBM_BufferAddRef(fl)  CAL_CMGETAPI( "SBM_BufferAddRef" ) 
	#define CAL_SBM_BufferAddRef  SBM_BufferAddRef
	#define CHK_SBM_BufferAddRef  TRUE
	#define EXP_SBM_BufferAddRef  CAL_CMEXPAPI( "SBM_BufferAddRef" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_BufferAddRef
	#define EXT_SBM_BufferAddRef
	#define GET_SBM_BufferAddRef(fl)  CAL_CMGETAPI( "SBM_BufferAddRef" ) 
	#define CAL_SBM_BufferAddRef  SBM_BufferAddRef
	#define CHK_SBM_BufferAddRef  TRUE
	#define EXP_SBM_BufferAddRef  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_BufferAddRef", (RTS_UINTPTR)SBM_BufferAddRef, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_BufferAddRef
	#define EXT_CmpCAASegBufferManSBM_BufferAddRef
	#define GET_CmpCAASegBufferManSBM_BufferAddRef  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_BufferAddRef pICmpCAASegBufferMan->ISBM_BufferAddRef
	#define CHK_CmpCAASegBufferManSBM_BufferAddRef (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_BufferAddRef  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_BufferAddRef
	#define EXT_SBM_BufferAddRef
	#define GET_SBM_BufferAddRef(fl)  CAL_CMGETAPI( "SBM_BufferAddRef" ) 
	#define CAL_SBM_BufferAddRef pICmpCAASegBufferMan->ISBM_BufferAddRef
	#define CHK_SBM_BufferAddRef (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_BufferAddRef  CAL_CMEXPAPI( "SBM_BufferAddRef" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_BufferAddRef  PFSBM_BUFFERADDREF pfSBM_BufferAddRef;
	#define EXT_SBM_BufferAddRef  extern PFSBM_BUFFERADDREF pfSBM_BufferAddRef;
	#define GET_SBM_BufferAddRef(fl)  s_pfCMGetAPI2( "SBM_BufferAddRef", (RTS_VOID_FCTPTR *)&pfSBM_BufferAddRef, (fl), 0, 0)
	#define CAL_SBM_BufferAddRef  pfSBM_BufferAddRef
	#define CHK_SBM_BufferAddRef  (pfSBM_BufferAddRef != NULL)
	#define EXP_SBM_BufferAddRef  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_BufferAddRef", (RTS_UINTPTR)SBM_BufferAddRef, 0, 0) 
#endif



CAA_SIZE CDECL SBM_GetBufferSize(SBM_PBUFFER pBuffer, CAA_ERROR* peError);
typedef CAA_SIZE (CDECL * PFSBM_GETBUFFERSIZE) (SBM_PBUFFER pBuffer, CAA_ERROR* peError);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_GETBUFFERSIZE_NOTIMPLEMENTED)
	#define USE_SBM_GetBufferSize
	#define EXT_SBM_GetBufferSize
	#define GET_SBM_GetBufferSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_GetBufferSize(p0,p1)  (CAA_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_SBM_GetBufferSize  FALSE
	#define EXP_SBM_GetBufferSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_GetBufferSize
	#define EXT_SBM_GetBufferSize
	#define GET_SBM_GetBufferSize(fl)  CAL_CMGETAPI( "SBM_GetBufferSize" ) 
	#define CAL_SBM_GetBufferSize  SBM_GetBufferSize
	#define CHK_SBM_GetBufferSize  TRUE
	#define EXP_SBM_GetBufferSize  CAL_CMEXPAPI( "SBM_GetBufferSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_GetBufferSize
	#define EXT_SBM_GetBufferSize
	#define GET_SBM_GetBufferSize(fl)  CAL_CMGETAPI( "SBM_GetBufferSize" ) 
	#define CAL_SBM_GetBufferSize  SBM_GetBufferSize
	#define CHK_SBM_GetBufferSize  TRUE
	#define EXP_SBM_GetBufferSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_GetBufferSize", (RTS_UINTPTR)SBM_GetBufferSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_GetBufferSize
	#define EXT_CmpCAASegBufferManSBM_GetBufferSize
	#define GET_CmpCAASegBufferManSBM_GetBufferSize  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_GetBufferSize pICmpCAASegBufferMan->ISBM_GetBufferSize
	#define CHK_CmpCAASegBufferManSBM_GetBufferSize (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_GetBufferSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_GetBufferSize
	#define EXT_SBM_GetBufferSize
	#define GET_SBM_GetBufferSize(fl)  CAL_CMGETAPI( "SBM_GetBufferSize" ) 
	#define CAL_SBM_GetBufferSize pICmpCAASegBufferMan->ISBM_GetBufferSize
	#define CHK_SBM_GetBufferSize (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_GetBufferSize  CAL_CMEXPAPI( "SBM_GetBufferSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_GetBufferSize  PFSBM_GETBUFFERSIZE pfSBM_GetBufferSize;
	#define EXT_SBM_GetBufferSize  extern PFSBM_GETBUFFERSIZE pfSBM_GetBufferSize;
	#define GET_SBM_GetBufferSize(fl)  s_pfCMGetAPI2( "SBM_GetBufferSize", (RTS_VOID_FCTPTR *)&pfSBM_GetBufferSize, (fl), 0, 0)
	#define CAL_SBM_GetBufferSize  pfSBM_GetBufferSize
	#define CHK_SBM_GetBufferSize  (pfSBM_GetBufferSize != NULL)
	#define EXP_SBM_GetBufferSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_GetBufferSize", (RTS_UINTPTR)SBM_GetBufferSize, 0, 0) 
#endif



CAA_PVOID CDECL SBM_GetSegmentDataPointer(SBM_PBUFFER pBuffer, CAA_SIZE* pszSize, CAA_BOOL* pxPermanent, CAA_ERROR* peError);
typedef CAA_PVOID (CDECL * PFSBM_GETSEGMENTDATAPOINTER) (SBM_PBUFFER pBuffer, CAA_SIZE* pszSize, CAA_BOOL* pxPermanent, CAA_ERROR* peError);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_GETSEGMENTDATAPOINTER_NOTIMPLEMENTED)
	#define USE_SBM_GetSegmentDataPointer
	#define EXT_SBM_GetSegmentDataPointer
	#define GET_SBM_GetSegmentDataPointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_GetSegmentDataPointer(p0,p1,p2,p3)  (CAA_PVOID)ERR_NOTIMPLEMENTED
	#define CHK_SBM_GetSegmentDataPointer  FALSE
	#define EXP_SBM_GetSegmentDataPointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_GetSegmentDataPointer
	#define EXT_SBM_GetSegmentDataPointer
	#define GET_SBM_GetSegmentDataPointer(fl)  CAL_CMGETAPI( "SBM_GetSegmentDataPointer" ) 
	#define CAL_SBM_GetSegmentDataPointer  SBM_GetSegmentDataPointer
	#define CHK_SBM_GetSegmentDataPointer  TRUE
	#define EXP_SBM_GetSegmentDataPointer  CAL_CMEXPAPI( "SBM_GetSegmentDataPointer" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_GetSegmentDataPointer
	#define EXT_SBM_GetSegmentDataPointer
	#define GET_SBM_GetSegmentDataPointer(fl)  CAL_CMGETAPI( "SBM_GetSegmentDataPointer" ) 
	#define CAL_SBM_GetSegmentDataPointer  SBM_GetSegmentDataPointer
	#define CHK_SBM_GetSegmentDataPointer  TRUE
	#define EXP_SBM_GetSegmentDataPointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_GetSegmentDataPointer", (RTS_UINTPTR)SBM_GetSegmentDataPointer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_GetSegmentDataPointer
	#define EXT_CmpCAASegBufferManSBM_GetSegmentDataPointer
	#define GET_CmpCAASegBufferManSBM_GetSegmentDataPointer  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_GetSegmentDataPointer pICmpCAASegBufferMan->ISBM_GetSegmentDataPointer
	#define CHK_CmpCAASegBufferManSBM_GetSegmentDataPointer (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_GetSegmentDataPointer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_GetSegmentDataPointer
	#define EXT_SBM_GetSegmentDataPointer
	#define GET_SBM_GetSegmentDataPointer(fl)  CAL_CMGETAPI( "SBM_GetSegmentDataPointer" ) 
	#define CAL_SBM_GetSegmentDataPointer pICmpCAASegBufferMan->ISBM_GetSegmentDataPointer
	#define CHK_SBM_GetSegmentDataPointer (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_GetSegmentDataPointer  CAL_CMEXPAPI( "SBM_GetSegmentDataPointer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_GetSegmentDataPointer  PFSBM_GETSEGMENTDATAPOINTER pfSBM_GetSegmentDataPointer;
	#define EXT_SBM_GetSegmentDataPointer  extern PFSBM_GETSEGMENTDATAPOINTER pfSBM_GetSegmentDataPointer;
	#define GET_SBM_GetSegmentDataPointer(fl)  s_pfCMGetAPI2( "SBM_GetSegmentDataPointer", (RTS_VOID_FCTPTR *)&pfSBM_GetSegmentDataPointer, (fl), 0, 0)
	#define CAL_SBM_GetSegmentDataPointer  pfSBM_GetSegmentDataPointer
	#define CHK_SBM_GetSegmentDataPointer  (pfSBM_GetSegmentDataPointer != NULL)
	#define EXP_SBM_GetSegmentDataPointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_GetSegmentDataPointer", (RTS_UINTPTR)SBM_GetSegmentDataPointer, 0, 0) 
#endif



CAA_ERROR CDECL SBM_MoveToBufferOffset(SBM_PBUFFER pBuffer, CAA_SIZE szOffset);
typedef CAA_ERROR (CDECL * PFSBM_MOVETOBUFFEROFFSET) (SBM_PBUFFER pBuffer, CAA_SIZE szOffset);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_MOVETOBUFFEROFFSET_NOTIMPLEMENTED)
	#define USE_SBM_MoveToBufferOffset
	#define EXT_SBM_MoveToBufferOffset
	#define GET_SBM_MoveToBufferOffset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_MoveToBufferOffset(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SBM_MoveToBufferOffset  FALSE
	#define EXP_SBM_MoveToBufferOffset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_MoveToBufferOffset
	#define EXT_SBM_MoveToBufferOffset
	#define GET_SBM_MoveToBufferOffset(fl)  CAL_CMGETAPI( "SBM_MoveToBufferOffset" ) 
	#define CAL_SBM_MoveToBufferOffset  SBM_MoveToBufferOffset
	#define CHK_SBM_MoveToBufferOffset  TRUE
	#define EXP_SBM_MoveToBufferOffset  CAL_CMEXPAPI( "SBM_MoveToBufferOffset" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_MoveToBufferOffset
	#define EXT_SBM_MoveToBufferOffset
	#define GET_SBM_MoveToBufferOffset(fl)  CAL_CMGETAPI( "SBM_MoveToBufferOffset" ) 
	#define CAL_SBM_MoveToBufferOffset  SBM_MoveToBufferOffset
	#define CHK_SBM_MoveToBufferOffset  TRUE
	#define EXP_SBM_MoveToBufferOffset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_MoveToBufferOffset", (RTS_UINTPTR)SBM_MoveToBufferOffset, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_MoveToBufferOffset
	#define EXT_CmpCAASegBufferManSBM_MoveToBufferOffset
	#define GET_CmpCAASegBufferManSBM_MoveToBufferOffset  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_MoveToBufferOffset pICmpCAASegBufferMan->ISBM_MoveToBufferOffset
	#define CHK_CmpCAASegBufferManSBM_MoveToBufferOffset (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_MoveToBufferOffset  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_MoveToBufferOffset
	#define EXT_SBM_MoveToBufferOffset
	#define GET_SBM_MoveToBufferOffset(fl)  CAL_CMGETAPI( "SBM_MoveToBufferOffset" ) 
	#define CAL_SBM_MoveToBufferOffset pICmpCAASegBufferMan->ISBM_MoveToBufferOffset
	#define CHK_SBM_MoveToBufferOffset (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_MoveToBufferOffset  CAL_CMEXPAPI( "SBM_MoveToBufferOffset" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_MoveToBufferOffset  PFSBM_MOVETOBUFFEROFFSET pfSBM_MoveToBufferOffset;
	#define EXT_SBM_MoveToBufferOffset  extern PFSBM_MOVETOBUFFEROFFSET pfSBM_MoveToBufferOffset;
	#define GET_SBM_MoveToBufferOffset(fl)  s_pfCMGetAPI2( "SBM_MoveToBufferOffset", (RTS_VOID_FCTPTR *)&pfSBM_MoveToBufferOffset, (fl), 0, 0)
	#define CAL_SBM_MoveToBufferOffset  pfSBM_MoveToBufferOffset
	#define CHK_SBM_MoveToBufferOffset  (pfSBM_MoveToBufferOffset != NULL)
	#define EXP_SBM_MoveToBufferOffset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_MoveToBufferOffset", (RTS_UINTPTR)SBM_MoveToBufferOffset, 0, 0) 
#endif



CAA_ERROR CDECL SBM_MoveToNextSegment(SBM_PBUFFER pBuffer);
typedef CAA_ERROR (CDECL * PFSBM_MOVETONEXTSEGMENT) (SBM_PBUFFER pBuffer);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_MOVETONEXTSEGMENT_NOTIMPLEMENTED)
	#define USE_SBM_MoveToNextSegment
	#define EXT_SBM_MoveToNextSegment
	#define GET_SBM_MoveToNextSegment(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_MoveToNextSegment(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SBM_MoveToNextSegment  FALSE
	#define EXP_SBM_MoveToNextSegment  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_MoveToNextSegment
	#define EXT_SBM_MoveToNextSegment
	#define GET_SBM_MoveToNextSegment(fl)  CAL_CMGETAPI( "SBM_MoveToNextSegment" ) 
	#define CAL_SBM_MoveToNextSegment  SBM_MoveToNextSegment
	#define CHK_SBM_MoveToNextSegment  TRUE
	#define EXP_SBM_MoveToNextSegment  CAL_CMEXPAPI( "SBM_MoveToNextSegment" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_MoveToNextSegment
	#define EXT_SBM_MoveToNextSegment
	#define GET_SBM_MoveToNextSegment(fl)  CAL_CMGETAPI( "SBM_MoveToNextSegment" ) 
	#define CAL_SBM_MoveToNextSegment  SBM_MoveToNextSegment
	#define CHK_SBM_MoveToNextSegment  TRUE
	#define EXP_SBM_MoveToNextSegment  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_MoveToNextSegment", (RTS_UINTPTR)SBM_MoveToNextSegment, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_MoveToNextSegment
	#define EXT_CmpCAASegBufferManSBM_MoveToNextSegment
	#define GET_CmpCAASegBufferManSBM_MoveToNextSegment  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_MoveToNextSegment pICmpCAASegBufferMan->ISBM_MoveToNextSegment
	#define CHK_CmpCAASegBufferManSBM_MoveToNextSegment (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_MoveToNextSegment  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_MoveToNextSegment
	#define EXT_SBM_MoveToNextSegment
	#define GET_SBM_MoveToNextSegment(fl)  CAL_CMGETAPI( "SBM_MoveToNextSegment" ) 
	#define CAL_SBM_MoveToNextSegment pICmpCAASegBufferMan->ISBM_MoveToNextSegment
	#define CHK_SBM_MoveToNextSegment (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_MoveToNextSegment  CAL_CMEXPAPI( "SBM_MoveToNextSegment" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_MoveToNextSegment  PFSBM_MOVETONEXTSEGMENT pfSBM_MoveToNextSegment;
	#define EXT_SBM_MoveToNextSegment  extern PFSBM_MOVETONEXTSEGMENT pfSBM_MoveToNextSegment;
	#define GET_SBM_MoveToNextSegment(fl)  s_pfCMGetAPI2( "SBM_MoveToNextSegment", (RTS_VOID_FCTPTR *)&pfSBM_MoveToNextSegment, (fl), 0, 0)
	#define CAL_SBM_MoveToNextSegment  pfSBM_MoveToNextSegment
	#define CHK_SBM_MoveToNextSegment  (pfSBM_MoveToNextSegment != NULL)
	#define EXP_SBM_MoveToNextSegment  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_MoveToNextSegment", (RTS_UINTPTR)SBM_MoveToNextSegment, 0, 0) 
#endif



SBM_PBUFFER CDECL SBM_SliceBuffer(SBM_PBUFFER pBuffer, CAA_SIZE szOffset, CAA_SIZE szLength, CAA_ERROR* peError);
typedef SBM_PBUFFER (CDECL * PFSBM_SLICEBUFFER) (SBM_PBUFFER pBuffer, CAA_SIZE szOffset, CAA_SIZE szLength, CAA_ERROR* peError);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_SLICEBUFFER_NOTIMPLEMENTED)
	#define USE_SBM_SliceBuffer
	#define EXT_SBM_SliceBuffer
	#define GET_SBM_SliceBuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_SliceBuffer(p0,p1,p2,p3)  (SBM_PBUFFER)ERR_NOTIMPLEMENTED
	#define CHK_SBM_SliceBuffer  FALSE
	#define EXP_SBM_SliceBuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_SliceBuffer
	#define EXT_SBM_SliceBuffer
	#define GET_SBM_SliceBuffer(fl)  CAL_CMGETAPI( "SBM_SliceBuffer" ) 
	#define CAL_SBM_SliceBuffer  SBM_SliceBuffer
	#define CHK_SBM_SliceBuffer  TRUE
	#define EXP_SBM_SliceBuffer  CAL_CMEXPAPI( "SBM_SliceBuffer" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_SliceBuffer
	#define EXT_SBM_SliceBuffer
	#define GET_SBM_SliceBuffer(fl)  CAL_CMGETAPI( "SBM_SliceBuffer" ) 
	#define CAL_SBM_SliceBuffer  SBM_SliceBuffer
	#define CHK_SBM_SliceBuffer  TRUE
	#define EXP_SBM_SliceBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_SliceBuffer", (RTS_UINTPTR)SBM_SliceBuffer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_SliceBuffer
	#define EXT_CmpCAASegBufferManSBM_SliceBuffer
	#define GET_CmpCAASegBufferManSBM_SliceBuffer  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_SliceBuffer pICmpCAASegBufferMan->ISBM_SliceBuffer
	#define CHK_CmpCAASegBufferManSBM_SliceBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_SliceBuffer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_SliceBuffer
	#define EXT_SBM_SliceBuffer
	#define GET_SBM_SliceBuffer(fl)  CAL_CMGETAPI( "SBM_SliceBuffer" ) 
	#define CAL_SBM_SliceBuffer pICmpCAASegBufferMan->ISBM_SliceBuffer
	#define CHK_SBM_SliceBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_SliceBuffer  CAL_CMEXPAPI( "SBM_SliceBuffer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_SliceBuffer  PFSBM_SLICEBUFFER pfSBM_SliceBuffer;
	#define EXT_SBM_SliceBuffer  extern PFSBM_SLICEBUFFER pfSBM_SliceBuffer;
	#define GET_SBM_SliceBuffer(fl)  s_pfCMGetAPI2( "SBM_SliceBuffer", (RTS_VOID_FCTPTR *)&pfSBM_SliceBuffer, (fl), 0, 0)
	#define CAL_SBM_SliceBuffer  pfSBM_SliceBuffer
	#define CHK_SBM_SliceBuffer  (pfSBM_SliceBuffer != NULL)
	#define EXP_SBM_SliceBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_SliceBuffer", (RTS_UINTPTR)SBM_SliceBuffer, 0, 0) 
#endif



SBM_PQUEUE CDECL SBM_CreateQueue(CAA_ERROR* peError);
typedef SBM_PQUEUE (CDECL * PFSBM_CREATEQUEUE) (CAA_ERROR* peError);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_CREATEQUEUE_NOTIMPLEMENTED)
	#define USE_SBM_CreateQueue
	#define EXT_SBM_CreateQueue
	#define GET_SBM_CreateQueue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_CreateQueue(p0)  (SBM_PQUEUE)ERR_NOTIMPLEMENTED
	#define CHK_SBM_CreateQueue  FALSE
	#define EXP_SBM_CreateQueue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_CreateQueue
	#define EXT_SBM_CreateQueue
	#define GET_SBM_CreateQueue(fl)  CAL_CMGETAPI( "SBM_CreateQueue" ) 
	#define CAL_SBM_CreateQueue  SBM_CreateQueue
	#define CHK_SBM_CreateQueue  TRUE
	#define EXP_SBM_CreateQueue  CAL_CMEXPAPI( "SBM_CreateQueue" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_CreateQueue
	#define EXT_SBM_CreateQueue
	#define GET_SBM_CreateQueue(fl)  CAL_CMGETAPI( "SBM_CreateQueue" ) 
	#define CAL_SBM_CreateQueue  SBM_CreateQueue
	#define CHK_SBM_CreateQueue  TRUE
	#define EXP_SBM_CreateQueue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_CreateQueue", (RTS_UINTPTR)SBM_CreateQueue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_CreateQueue
	#define EXT_CmpCAASegBufferManSBM_CreateQueue
	#define GET_CmpCAASegBufferManSBM_CreateQueue  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_CreateQueue pICmpCAASegBufferMan->ISBM_CreateQueue
	#define CHK_CmpCAASegBufferManSBM_CreateQueue (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_CreateQueue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_CreateQueue
	#define EXT_SBM_CreateQueue
	#define GET_SBM_CreateQueue(fl)  CAL_CMGETAPI( "SBM_CreateQueue" ) 
	#define CAL_SBM_CreateQueue pICmpCAASegBufferMan->ISBM_CreateQueue
	#define CHK_SBM_CreateQueue (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_CreateQueue  CAL_CMEXPAPI( "SBM_CreateQueue" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_CreateQueue  PFSBM_CREATEQUEUE pfSBM_CreateQueue;
	#define EXT_SBM_CreateQueue  extern PFSBM_CREATEQUEUE pfSBM_CreateQueue;
	#define GET_SBM_CreateQueue(fl)  s_pfCMGetAPI2( "SBM_CreateQueue", (RTS_VOID_FCTPTR *)&pfSBM_CreateQueue, (fl), 0, 0)
	#define CAL_SBM_CreateQueue  pfSBM_CreateQueue
	#define CHK_SBM_CreateQueue  (pfSBM_CreateQueue != NULL)
	#define EXP_SBM_CreateQueue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_CreateQueue", (RTS_UINTPTR)SBM_CreateQueue, 0, 0) 
#endif



CAA_ERROR CDECL SBM_DeleteQueue(SBM_PQUEUE pQueue);
typedef CAA_ERROR (CDECL * PFSBM_DELETEQUEUE) (SBM_PQUEUE pQueue);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_DELETEQUEUE_NOTIMPLEMENTED)
	#define USE_SBM_DeleteQueue
	#define EXT_SBM_DeleteQueue
	#define GET_SBM_DeleteQueue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_DeleteQueue(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SBM_DeleteQueue  FALSE
	#define EXP_SBM_DeleteQueue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_DeleteQueue
	#define EXT_SBM_DeleteQueue
	#define GET_SBM_DeleteQueue(fl)  CAL_CMGETAPI( "SBM_DeleteQueue" ) 
	#define CAL_SBM_DeleteQueue  SBM_DeleteQueue
	#define CHK_SBM_DeleteQueue  TRUE
	#define EXP_SBM_DeleteQueue  CAL_CMEXPAPI( "SBM_DeleteQueue" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_DeleteQueue
	#define EXT_SBM_DeleteQueue
	#define GET_SBM_DeleteQueue(fl)  CAL_CMGETAPI( "SBM_DeleteQueue" ) 
	#define CAL_SBM_DeleteQueue  SBM_DeleteQueue
	#define CHK_SBM_DeleteQueue  TRUE
	#define EXP_SBM_DeleteQueue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_DeleteQueue", (RTS_UINTPTR)SBM_DeleteQueue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_DeleteQueue
	#define EXT_CmpCAASegBufferManSBM_DeleteQueue
	#define GET_CmpCAASegBufferManSBM_DeleteQueue  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_DeleteQueue pICmpCAASegBufferMan->ISBM_DeleteQueue
	#define CHK_CmpCAASegBufferManSBM_DeleteQueue (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_DeleteQueue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_DeleteQueue
	#define EXT_SBM_DeleteQueue
	#define GET_SBM_DeleteQueue(fl)  CAL_CMGETAPI( "SBM_DeleteQueue" ) 
	#define CAL_SBM_DeleteQueue pICmpCAASegBufferMan->ISBM_DeleteQueue
	#define CHK_SBM_DeleteQueue (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_DeleteQueue  CAL_CMEXPAPI( "SBM_DeleteQueue" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_DeleteQueue  PFSBM_DELETEQUEUE pfSBM_DeleteQueue;
	#define EXT_SBM_DeleteQueue  extern PFSBM_DELETEQUEUE pfSBM_DeleteQueue;
	#define GET_SBM_DeleteQueue(fl)  s_pfCMGetAPI2( "SBM_DeleteQueue", (RTS_VOID_FCTPTR *)&pfSBM_DeleteQueue, (fl), 0, 0)
	#define CAL_SBM_DeleteQueue  pfSBM_DeleteQueue
	#define CHK_SBM_DeleteQueue  (pfSBM_DeleteQueue != NULL)
	#define EXP_SBM_DeleteQueue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_DeleteQueue", (RTS_UINTPTR)SBM_DeleteQueue, 0, 0) 
#endif



SBM_PBUFFER CDECL SBM_DequeueBuffer(SBM_PQUEUE pQueue, CAA_ERROR* peError);
typedef SBM_PBUFFER (CDECL * PFSBM_DEQUEUEBUFFER) (SBM_PQUEUE pQueue, CAA_ERROR* peError);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_DEQUEUEBUFFER_NOTIMPLEMENTED)
	#define USE_SBM_DequeueBuffer
	#define EXT_SBM_DequeueBuffer
	#define GET_SBM_DequeueBuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_DequeueBuffer(p0,p1)  (SBM_PBUFFER)ERR_NOTIMPLEMENTED
	#define CHK_SBM_DequeueBuffer  FALSE
	#define EXP_SBM_DequeueBuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_DequeueBuffer
	#define EXT_SBM_DequeueBuffer
	#define GET_SBM_DequeueBuffer(fl)  CAL_CMGETAPI( "SBM_DequeueBuffer" ) 
	#define CAL_SBM_DequeueBuffer  SBM_DequeueBuffer
	#define CHK_SBM_DequeueBuffer  TRUE
	#define EXP_SBM_DequeueBuffer  CAL_CMEXPAPI( "SBM_DequeueBuffer" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_DequeueBuffer
	#define EXT_SBM_DequeueBuffer
	#define GET_SBM_DequeueBuffer(fl)  CAL_CMGETAPI( "SBM_DequeueBuffer" ) 
	#define CAL_SBM_DequeueBuffer  SBM_DequeueBuffer
	#define CHK_SBM_DequeueBuffer  TRUE
	#define EXP_SBM_DequeueBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_DequeueBuffer", (RTS_UINTPTR)SBM_DequeueBuffer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_DequeueBuffer
	#define EXT_CmpCAASegBufferManSBM_DequeueBuffer
	#define GET_CmpCAASegBufferManSBM_DequeueBuffer  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_DequeueBuffer pICmpCAASegBufferMan->ISBM_DequeueBuffer
	#define CHK_CmpCAASegBufferManSBM_DequeueBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_DequeueBuffer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_DequeueBuffer
	#define EXT_SBM_DequeueBuffer
	#define GET_SBM_DequeueBuffer(fl)  CAL_CMGETAPI( "SBM_DequeueBuffer" ) 
	#define CAL_SBM_DequeueBuffer pICmpCAASegBufferMan->ISBM_DequeueBuffer
	#define CHK_SBM_DequeueBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_DequeueBuffer  CAL_CMEXPAPI( "SBM_DequeueBuffer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_DequeueBuffer  PFSBM_DEQUEUEBUFFER pfSBM_DequeueBuffer;
	#define EXT_SBM_DequeueBuffer  extern PFSBM_DEQUEUEBUFFER pfSBM_DequeueBuffer;
	#define GET_SBM_DequeueBuffer(fl)  s_pfCMGetAPI2( "SBM_DequeueBuffer", (RTS_VOID_FCTPTR *)&pfSBM_DequeueBuffer, (fl), 0, 0)
	#define CAL_SBM_DequeueBuffer  pfSBM_DequeueBuffer
	#define CHK_SBM_DequeueBuffer  (pfSBM_DequeueBuffer != NULL)
	#define EXP_SBM_DequeueBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_DequeueBuffer", (RTS_UINTPTR)SBM_DequeueBuffer, 0, 0) 
#endif



CAA_ERROR CDECL SBM_EnqueueBuffer(SBM_PQUEUE pQueue, SBM_PBUFFER hBuffer);
typedef CAA_ERROR (CDECL * PFSBM_ENQUEUEBUFFER) (SBM_PQUEUE pQueue, SBM_PBUFFER hBuffer);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_ENQUEUEBUFFER_NOTIMPLEMENTED)
	#define USE_SBM_EnqueueBuffer
	#define EXT_SBM_EnqueueBuffer
	#define GET_SBM_EnqueueBuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_EnqueueBuffer(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SBM_EnqueueBuffer  FALSE
	#define EXP_SBM_EnqueueBuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_EnqueueBuffer
	#define EXT_SBM_EnqueueBuffer
	#define GET_SBM_EnqueueBuffer(fl)  CAL_CMGETAPI( "SBM_EnqueueBuffer" ) 
	#define CAL_SBM_EnqueueBuffer  SBM_EnqueueBuffer
	#define CHK_SBM_EnqueueBuffer  TRUE
	#define EXP_SBM_EnqueueBuffer  CAL_CMEXPAPI( "SBM_EnqueueBuffer" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_EnqueueBuffer
	#define EXT_SBM_EnqueueBuffer
	#define GET_SBM_EnqueueBuffer(fl)  CAL_CMGETAPI( "SBM_EnqueueBuffer" ) 
	#define CAL_SBM_EnqueueBuffer  SBM_EnqueueBuffer
	#define CHK_SBM_EnqueueBuffer  TRUE
	#define EXP_SBM_EnqueueBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_EnqueueBuffer", (RTS_UINTPTR)SBM_EnqueueBuffer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_EnqueueBuffer
	#define EXT_CmpCAASegBufferManSBM_EnqueueBuffer
	#define GET_CmpCAASegBufferManSBM_EnqueueBuffer  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_EnqueueBuffer pICmpCAASegBufferMan->ISBM_EnqueueBuffer
	#define CHK_CmpCAASegBufferManSBM_EnqueueBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_EnqueueBuffer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_EnqueueBuffer
	#define EXT_SBM_EnqueueBuffer
	#define GET_SBM_EnqueueBuffer(fl)  CAL_CMGETAPI( "SBM_EnqueueBuffer" ) 
	#define CAL_SBM_EnqueueBuffer pICmpCAASegBufferMan->ISBM_EnqueueBuffer
	#define CHK_SBM_EnqueueBuffer (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_EnqueueBuffer  CAL_CMEXPAPI( "SBM_EnqueueBuffer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_EnqueueBuffer  PFSBM_ENQUEUEBUFFER pfSBM_EnqueueBuffer;
	#define EXT_SBM_EnqueueBuffer  extern PFSBM_ENQUEUEBUFFER pfSBM_EnqueueBuffer;
	#define GET_SBM_EnqueueBuffer(fl)  s_pfCMGetAPI2( "SBM_EnqueueBuffer", (RTS_VOID_FCTPTR *)&pfSBM_EnqueueBuffer, (fl), 0, 0)
	#define CAL_SBM_EnqueueBuffer  pfSBM_EnqueueBuffer
	#define CHK_SBM_EnqueueBuffer  (pfSBM_EnqueueBuffer != NULL)
	#define EXP_SBM_EnqueueBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_EnqueueBuffer", (RTS_UINTPTR)SBM_EnqueueBuffer, 0, 0) 
#endif



CAA_SIZE CDECL SBM_GetQueueLength(SBM_PQUEUE pQueue, CAA_ERROR* peError);
typedef CAA_SIZE (CDECL * PFSBM_GETQUEUELENGTH) (SBM_PQUEUE pQueue, CAA_ERROR* peError);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_GETQUEUELENGTH_NOTIMPLEMENTED)
	#define USE_SBM_GetQueueLength
	#define EXT_SBM_GetQueueLength
	#define GET_SBM_GetQueueLength(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_GetQueueLength(p0,p1)  (CAA_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_SBM_GetQueueLength  FALSE
	#define EXP_SBM_GetQueueLength  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_GetQueueLength
	#define EXT_SBM_GetQueueLength
	#define GET_SBM_GetQueueLength(fl)  CAL_CMGETAPI( "SBM_GetQueueLength" ) 
	#define CAL_SBM_GetQueueLength  SBM_GetQueueLength
	#define CHK_SBM_GetQueueLength  TRUE
	#define EXP_SBM_GetQueueLength  CAL_CMEXPAPI( "SBM_GetQueueLength" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_GetQueueLength
	#define EXT_SBM_GetQueueLength
	#define GET_SBM_GetQueueLength(fl)  CAL_CMGETAPI( "SBM_GetQueueLength" ) 
	#define CAL_SBM_GetQueueLength  SBM_GetQueueLength
	#define CHK_SBM_GetQueueLength  TRUE
	#define EXP_SBM_GetQueueLength  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_GetQueueLength", (RTS_UINTPTR)SBM_GetQueueLength, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_GetQueueLength
	#define EXT_CmpCAASegBufferManSBM_GetQueueLength
	#define GET_CmpCAASegBufferManSBM_GetQueueLength  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_GetQueueLength pICmpCAASegBufferMan->ISBM_GetQueueLength
	#define CHK_CmpCAASegBufferManSBM_GetQueueLength (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_GetQueueLength  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_GetQueueLength
	#define EXT_SBM_GetQueueLength
	#define GET_SBM_GetQueueLength(fl)  CAL_CMGETAPI( "SBM_GetQueueLength" ) 
	#define CAL_SBM_GetQueueLength pICmpCAASegBufferMan->ISBM_GetQueueLength
	#define CHK_SBM_GetQueueLength (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_GetQueueLength  CAL_CMEXPAPI( "SBM_GetQueueLength" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_GetQueueLength  PFSBM_GETQUEUELENGTH pfSBM_GetQueueLength;
	#define EXT_SBM_GetQueueLength  extern PFSBM_GETQUEUELENGTH pfSBM_GetQueueLength;
	#define GET_SBM_GetQueueLength(fl)  s_pfCMGetAPI2( "SBM_GetQueueLength", (RTS_VOID_FCTPTR *)&pfSBM_GetQueueLength, (fl), 0, 0)
	#define CAL_SBM_GetQueueLength  pfSBM_GetQueueLength
	#define CHK_SBM_GetQueueLength  (pfSBM_GetQueueLength != NULL)
	#define EXP_SBM_GetQueueLength  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_GetQueueLength", (RTS_UINTPTR)SBM_GetQueueLength, 0, 0) 
#endif



CAA_UINT CDECL SBM_GetSupplierVersion(CAA_BOOL xDummy);
typedef CAA_UINT (CDECL * PFSBM_GETSUPPLIERVERSION) (CAA_BOOL xDummy);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_SBM_GetSupplierVersion
	#define EXT_SBM_GetSupplierVersion
	#define GET_SBM_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SBM_GetSupplierVersion(p0)  (CAA_UINT)ERR_NOTIMPLEMENTED
	#define CHK_SBM_GetSupplierVersion  FALSE
	#define EXP_SBM_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SBM_GetSupplierVersion
	#define EXT_SBM_GetSupplierVersion
	#define GET_SBM_GetSupplierVersion(fl)  CAL_CMGETAPI( "SBM_GetSupplierVersion" ) 
	#define CAL_SBM_GetSupplierVersion  SBM_GetSupplierVersion
	#define CHK_SBM_GetSupplierVersion  TRUE
	#define EXP_SBM_GetSupplierVersion  CAL_CMEXPAPI( "SBM_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_SBM_GetSupplierVersion
	#define EXT_SBM_GetSupplierVersion
	#define GET_SBM_GetSupplierVersion(fl)  CAL_CMGETAPI( "SBM_GetSupplierVersion" ) 
	#define CAL_SBM_GetSupplierVersion  SBM_GetSupplierVersion
	#define CHK_SBM_GetSupplierVersion  TRUE
	#define EXP_SBM_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_GetSupplierVersion", (RTS_UINTPTR)SBM_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferManSBM_GetSupplierVersion
	#define EXT_CmpCAASegBufferManSBM_GetSupplierVersion
	#define GET_CmpCAASegBufferManSBM_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAASegBufferManSBM_GetSupplierVersion pICmpCAASegBufferMan->ISBM_GetSupplierVersion
	#define CHK_CmpCAASegBufferManSBM_GetSupplierVersion (pICmpCAASegBufferMan != NULL)
	#define EXP_CmpCAASegBufferManSBM_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SBM_GetSupplierVersion
	#define EXT_SBM_GetSupplierVersion
	#define GET_SBM_GetSupplierVersion(fl)  CAL_CMGETAPI( "SBM_GetSupplierVersion" ) 
	#define CAL_SBM_GetSupplierVersion pICmpCAASegBufferMan->ISBM_GetSupplierVersion
	#define CHK_SBM_GetSupplierVersion (pICmpCAASegBufferMan != NULL)
	#define EXP_SBM_GetSupplierVersion  CAL_CMEXPAPI( "SBM_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_SBM_GetSupplierVersion  PFSBM_GETSUPPLIERVERSION pfSBM_GetSupplierVersion;
	#define EXT_SBM_GetSupplierVersion  extern PFSBM_GETSUPPLIERVERSION pfSBM_GetSupplierVersion;
	#define GET_SBM_GetSupplierVersion(fl)  s_pfCMGetAPI2( "SBM_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfSBM_GetSupplierVersion, (fl), 0, 0)
	#define CAL_SBM_GetSupplierVersion  pfSBM_GetSupplierVersion
	#define CHK_SBM_GetSupplierVersion  (pfSBM_GetSupplierVersion != NULL)
	#define EXP_SBM_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SBM_GetSupplierVersion", (RTS_UINTPTR)SBM_GetSupplierVersion, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>sbm_bufferaddref</description>
 */
typedef struct tagsbm_bufferaddref_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_ERROR SBM_BufferAddRef;			/* VAR_OUTPUT */	
} sbm_bufferaddref_struct;

void CDECL CDECL_EXT sbm_bufferaddref(sbm_bufferaddref_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_BUFFERADDREF_IEC) (sbm_bufferaddref_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_BUFFERADDREF_NOTIMPLEMENTED)
	#define USE_sbm_bufferaddref
	#define EXT_sbm_bufferaddref
	#define GET_sbm_bufferaddref(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_bufferaddref(p0) 
	#define CHK_sbm_bufferaddref  FALSE
	#define EXP_sbm_bufferaddref  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_bufferaddref
	#define EXT_sbm_bufferaddref
	#define GET_sbm_bufferaddref(fl)  CAL_CMGETAPI( "sbm_bufferaddref" ) 
	#define CAL_sbm_bufferaddref  sbm_bufferaddref
	#define CHK_sbm_bufferaddref  TRUE
	#define EXP_sbm_bufferaddref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_bufferaddref", (RTS_UINTPTR)sbm_bufferaddref, 1, RTSITF_GET_SIGNATURE(0, 0x17A0E79E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_bufferaddref
	#define EXT_sbm_bufferaddref
	#define GET_sbm_bufferaddref(fl)  CAL_CMGETAPI( "sbm_bufferaddref" ) 
	#define CAL_sbm_bufferaddref  sbm_bufferaddref
	#define CHK_sbm_bufferaddref  TRUE
	#define EXP_sbm_bufferaddref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_bufferaddref", (RTS_UINTPTR)sbm_bufferaddref, 1, RTSITF_GET_SIGNATURE(0, 0x17A0E79E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_bufferaddref
	#define EXT_CmpCAASegBufferMansbm_bufferaddref
	#define GET_CmpCAASegBufferMansbm_bufferaddref  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_bufferaddref  sbm_bufferaddref
	#define CHK_CmpCAASegBufferMansbm_bufferaddref  TRUE
	#define EXP_CmpCAASegBufferMansbm_bufferaddref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_bufferaddref", (RTS_UINTPTR)sbm_bufferaddref, 1, RTSITF_GET_SIGNATURE(0, 0x17A0E79E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_bufferaddref
	#define EXT_sbm_bufferaddref
	#define GET_sbm_bufferaddref(fl)  CAL_CMGETAPI( "sbm_bufferaddref" ) 
	#define CAL_sbm_bufferaddref  sbm_bufferaddref
	#define CHK_sbm_bufferaddref  TRUE
	#define EXP_sbm_bufferaddref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_bufferaddref", (RTS_UINTPTR)sbm_bufferaddref, 1, RTSITF_GET_SIGNATURE(0, 0x17A0E79E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_bufferaddref  PFSBM_BUFFERADDREF_IEC pfsbm_bufferaddref;
	#define EXT_sbm_bufferaddref  extern PFSBM_BUFFERADDREF_IEC pfsbm_bufferaddref;
	#define GET_sbm_bufferaddref(fl)  s_pfCMGetAPI2( "sbm_bufferaddref", (RTS_VOID_FCTPTR *)&pfsbm_bufferaddref, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x17A0E79E), 0x03050500)
	#define CAL_sbm_bufferaddref  pfsbm_bufferaddref
	#define CHK_sbm_bufferaddref  (pfsbm_bufferaddref != NULL)
	#define EXP_sbm_bufferaddref   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_bufferaddref", (RTS_UINTPTR)sbm_bufferaddref, 1, RTSITF_GET_SIGNATURE(0, 0x17A0E79E), 0x03050500) 
#endif


/**
 * <description>sbm_chainbuffer</description>
 */
typedef struct tagsbm_chainbuffer_struct
{
	CAA_HANDLE hHead;					/* VAR_INPUT */	/* Head hBuffer */
	CAA_HANDLE hTail;					/* VAR_INPUT */	/* Tail hBuffer */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE SBM_ChainBuffer;			/* VAR_OUTPUT */	/* hBuffer */
} sbm_chainbuffer_struct;

void CDECL CDECL_EXT sbm_chainbuffer(sbm_chainbuffer_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_CHAINBUFFER_IEC) (sbm_chainbuffer_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_CHAINBUFFER_NOTIMPLEMENTED)
	#define USE_sbm_chainbuffer
	#define EXT_sbm_chainbuffer
	#define GET_sbm_chainbuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_chainbuffer(p0) 
	#define CHK_sbm_chainbuffer  FALSE
	#define EXP_sbm_chainbuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_chainbuffer
	#define EXT_sbm_chainbuffer
	#define GET_sbm_chainbuffer(fl)  CAL_CMGETAPI( "sbm_chainbuffer" ) 
	#define CAL_sbm_chainbuffer  sbm_chainbuffer
	#define CHK_sbm_chainbuffer  TRUE
	#define EXP_sbm_chainbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_chainbuffer", (RTS_UINTPTR)sbm_chainbuffer, 1, RTSITF_GET_SIGNATURE(0, 0x3A6B344E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_chainbuffer
	#define EXT_sbm_chainbuffer
	#define GET_sbm_chainbuffer(fl)  CAL_CMGETAPI( "sbm_chainbuffer" ) 
	#define CAL_sbm_chainbuffer  sbm_chainbuffer
	#define CHK_sbm_chainbuffer  TRUE
	#define EXP_sbm_chainbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_chainbuffer", (RTS_UINTPTR)sbm_chainbuffer, 1, RTSITF_GET_SIGNATURE(0, 0x3A6B344E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_chainbuffer
	#define EXT_CmpCAASegBufferMansbm_chainbuffer
	#define GET_CmpCAASegBufferMansbm_chainbuffer  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_chainbuffer  sbm_chainbuffer
	#define CHK_CmpCAASegBufferMansbm_chainbuffer  TRUE
	#define EXP_CmpCAASegBufferMansbm_chainbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_chainbuffer", (RTS_UINTPTR)sbm_chainbuffer, 1, RTSITF_GET_SIGNATURE(0, 0x3A6B344E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_chainbuffer
	#define EXT_sbm_chainbuffer
	#define GET_sbm_chainbuffer(fl)  CAL_CMGETAPI( "sbm_chainbuffer" ) 
	#define CAL_sbm_chainbuffer  sbm_chainbuffer
	#define CHK_sbm_chainbuffer  TRUE
	#define EXP_sbm_chainbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_chainbuffer", (RTS_UINTPTR)sbm_chainbuffer, 1, RTSITF_GET_SIGNATURE(0, 0x3A6B344E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_chainbuffer  PFSBM_CHAINBUFFER_IEC pfsbm_chainbuffer;
	#define EXT_sbm_chainbuffer  extern PFSBM_CHAINBUFFER_IEC pfsbm_chainbuffer;
	#define GET_sbm_chainbuffer(fl)  s_pfCMGetAPI2( "sbm_chainbuffer", (RTS_VOID_FCTPTR *)&pfsbm_chainbuffer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x3A6B344E), 0x03050500)
	#define CAL_sbm_chainbuffer  pfsbm_chainbuffer
	#define CHK_sbm_chainbuffer  (pfsbm_chainbuffer != NULL)
	#define EXP_sbm_chainbuffer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_chainbuffer", (RTS_UINTPTR)sbm_chainbuffer, 1, RTSITF_GET_SIGNATURE(0, 0x3A6B344E), 0x03050500) 
#endif


/**
 * <description>sbm_copybufferdata</description>
 */
typedef struct tagsbm_copybufferdata_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	/* Source */
	CAA_SIZE szOffset;					/* VAR_INPUT */	/* Offset in Buffer */
	CAA_SIZE szLength;					/* VAR_INPUT */	/* Length of Data to Copy */
	CAA_PVOID pData;					/* VAR_INPUT */	/* Destination */
	CAA_SIZE szSize;					/* VAR_INPUT */	/* Size of Destination */
	CAA_ERROR SBM_CopyBufferData;		/* VAR_OUTPUT */	/* eError */
} sbm_copybufferdata_struct;

void CDECL CDECL_EXT sbm_copybufferdata(sbm_copybufferdata_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_COPYBUFFERDATA_IEC) (sbm_copybufferdata_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_COPYBUFFERDATA_NOTIMPLEMENTED)
	#define USE_sbm_copybufferdata
	#define EXT_sbm_copybufferdata
	#define GET_sbm_copybufferdata(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_copybufferdata(p0) 
	#define CHK_sbm_copybufferdata  FALSE
	#define EXP_sbm_copybufferdata  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_copybufferdata
	#define EXT_sbm_copybufferdata
	#define GET_sbm_copybufferdata(fl)  CAL_CMGETAPI( "sbm_copybufferdata" ) 
	#define CAL_sbm_copybufferdata  sbm_copybufferdata
	#define CHK_sbm_copybufferdata  TRUE
	#define EXP_sbm_copybufferdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_copybufferdata", (RTS_UINTPTR)sbm_copybufferdata, 1, RTSITF_GET_SIGNATURE(0, 0xE0E8C059), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_copybufferdata
	#define EXT_sbm_copybufferdata
	#define GET_sbm_copybufferdata(fl)  CAL_CMGETAPI( "sbm_copybufferdata" ) 
	#define CAL_sbm_copybufferdata  sbm_copybufferdata
	#define CHK_sbm_copybufferdata  TRUE
	#define EXP_sbm_copybufferdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_copybufferdata", (RTS_UINTPTR)sbm_copybufferdata, 1, RTSITF_GET_SIGNATURE(0, 0xE0E8C059), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_copybufferdata
	#define EXT_CmpCAASegBufferMansbm_copybufferdata
	#define GET_CmpCAASegBufferMansbm_copybufferdata  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_copybufferdata  sbm_copybufferdata
	#define CHK_CmpCAASegBufferMansbm_copybufferdata  TRUE
	#define EXP_CmpCAASegBufferMansbm_copybufferdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_copybufferdata", (RTS_UINTPTR)sbm_copybufferdata, 1, RTSITF_GET_SIGNATURE(0, 0xE0E8C059), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_copybufferdata
	#define EXT_sbm_copybufferdata
	#define GET_sbm_copybufferdata(fl)  CAL_CMGETAPI( "sbm_copybufferdata" ) 
	#define CAL_sbm_copybufferdata  sbm_copybufferdata
	#define CHK_sbm_copybufferdata  TRUE
	#define EXP_sbm_copybufferdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_copybufferdata", (RTS_UINTPTR)sbm_copybufferdata, 1, RTSITF_GET_SIGNATURE(0, 0xE0E8C059), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_copybufferdata  PFSBM_COPYBUFFERDATA_IEC pfsbm_copybufferdata;
	#define EXT_sbm_copybufferdata  extern PFSBM_COPYBUFFERDATA_IEC pfsbm_copybufferdata;
	#define GET_sbm_copybufferdata(fl)  s_pfCMGetAPI2( "sbm_copybufferdata", (RTS_VOID_FCTPTR *)&pfsbm_copybufferdata, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE0E8C059), 0x03050500)
	#define CAL_sbm_copybufferdata  pfsbm_copybufferdata
	#define CHK_sbm_copybufferdata  (pfsbm_copybufferdata != NULL)
	#define EXP_sbm_copybufferdata   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_copybufferdata", (RTS_UINTPTR)sbm_copybufferdata, 1, RTSITF_GET_SIGNATURE(0, 0xE0E8C059), 0x03050500) 
#endif


/**
 * <description>sbm_createbuffer</description>
 */
typedef struct tagsbm_createbuffer_struct
{
	CAA_SIZE szSize;					/* VAR_INPUT */	/* size of the new Buffer */
	CAA_PVOID pData;					/* VAR_INPUT */	/* Pointer to initial data. CAA.gc_pNULL => Init with zero */
	CAA_BOOL xPermanent;				/* VAR_INPUT */	/* TRUE => Buffer is imutable */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE SBM_CreateBuffer;		/* VAR_OUTPUT */	/* hBuffer */
} sbm_createbuffer_struct;

void CDECL CDECL_EXT sbm_createbuffer(sbm_createbuffer_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_CREATEBUFFER_IEC) (sbm_createbuffer_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_CREATEBUFFER_NOTIMPLEMENTED)
	#define USE_sbm_createbuffer
	#define EXT_sbm_createbuffer
	#define GET_sbm_createbuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_createbuffer(p0) 
	#define CHK_sbm_createbuffer  FALSE
	#define EXP_sbm_createbuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_createbuffer
	#define EXT_sbm_createbuffer
	#define GET_sbm_createbuffer(fl)  CAL_CMGETAPI( "sbm_createbuffer" ) 
	#define CAL_sbm_createbuffer  sbm_createbuffer
	#define CHK_sbm_createbuffer  TRUE
	#define EXP_sbm_createbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_createbuffer", (RTS_UINTPTR)sbm_createbuffer, 1, RTSITF_GET_SIGNATURE(0, 0xEE6CBB0F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_createbuffer
	#define EXT_sbm_createbuffer
	#define GET_sbm_createbuffer(fl)  CAL_CMGETAPI( "sbm_createbuffer" ) 
	#define CAL_sbm_createbuffer  sbm_createbuffer
	#define CHK_sbm_createbuffer  TRUE
	#define EXP_sbm_createbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_createbuffer", (RTS_UINTPTR)sbm_createbuffer, 1, RTSITF_GET_SIGNATURE(0, 0xEE6CBB0F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_createbuffer
	#define EXT_CmpCAASegBufferMansbm_createbuffer
	#define GET_CmpCAASegBufferMansbm_createbuffer  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_createbuffer  sbm_createbuffer
	#define CHK_CmpCAASegBufferMansbm_createbuffer  TRUE
	#define EXP_CmpCAASegBufferMansbm_createbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_createbuffer", (RTS_UINTPTR)sbm_createbuffer, 1, RTSITF_GET_SIGNATURE(0, 0xEE6CBB0F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_createbuffer
	#define EXT_sbm_createbuffer
	#define GET_sbm_createbuffer(fl)  CAL_CMGETAPI( "sbm_createbuffer" ) 
	#define CAL_sbm_createbuffer  sbm_createbuffer
	#define CHK_sbm_createbuffer  TRUE
	#define EXP_sbm_createbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_createbuffer", (RTS_UINTPTR)sbm_createbuffer, 1, RTSITF_GET_SIGNATURE(0, 0xEE6CBB0F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_createbuffer  PFSBM_CREATEBUFFER_IEC pfsbm_createbuffer;
	#define EXT_sbm_createbuffer  extern PFSBM_CREATEBUFFER_IEC pfsbm_createbuffer;
	#define GET_sbm_createbuffer(fl)  s_pfCMGetAPI2( "sbm_createbuffer", (RTS_VOID_FCTPTR *)&pfsbm_createbuffer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xEE6CBB0F), 0x03050500)
	#define CAL_sbm_createbuffer  pfsbm_createbuffer
	#define CHK_sbm_createbuffer  (pfsbm_createbuffer != NULL)
	#define EXP_sbm_createbuffer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_createbuffer", (RTS_UINTPTR)sbm_createbuffer, 1, RTSITF_GET_SIGNATURE(0, 0xEE6CBB0F), 0x03050500) 
#endif


/**
 * <description>sbm_createqueue</description>
 */
typedef struct tagsbm_createqueue_struct
{
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE SBM_CreateQueue;			/* VAR_OUTPUT */	/* hQueue */
} sbm_createqueue_struct;

void CDECL CDECL_EXT sbm_createqueue(sbm_createqueue_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_CREATEQUEUE_IEC) (sbm_createqueue_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_CREATEQUEUE_NOTIMPLEMENTED)
	#define USE_sbm_createqueue
	#define EXT_sbm_createqueue
	#define GET_sbm_createqueue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_createqueue(p0) 
	#define CHK_sbm_createqueue  FALSE
	#define EXP_sbm_createqueue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_createqueue
	#define EXT_sbm_createqueue
	#define GET_sbm_createqueue(fl)  CAL_CMGETAPI( "sbm_createqueue" ) 
	#define CAL_sbm_createqueue  sbm_createqueue
	#define CHK_sbm_createqueue  TRUE
	#define EXP_sbm_createqueue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_createqueue", (RTS_UINTPTR)sbm_createqueue, 1, RTSITF_GET_SIGNATURE(0, 0xFEB5034F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_createqueue
	#define EXT_sbm_createqueue
	#define GET_sbm_createqueue(fl)  CAL_CMGETAPI( "sbm_createqueue" ) 
	#define CAL_sbm_createqueue  sbm_createqueue
	#define CHK_sbm_createqueue  TRUE
	#define EXP_sbm_createqueue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_createqueue", (RTS_UINTPTR)sbm_createqueue, 1, RTSITF_GET_SIGNATURE(0, 0xFEB5034F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_createqueue
	#define EXT_CmpCAASegBufferMansbm_createqueue
	#define GET_CmpCAASegBufferMansbm_createqueue  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_createqueue  sbm_createqueue
	#define CHK_CmpCAASegBufferMansbm_createqueue  TRUE
	#define EXP_CmpCAASegBufferMansbm_createqueue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_createqueue", (RTS_UINTPTR)sbm_createqueue, 1, RTSITF_GET_SIGNATURE(0, 0xFEB5034F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_createqueue
	#define EXT_sbm_createqueue
	#define GET_sbm_createqueue(fl)  CAL_CMGETAPI( "sbm_createqueue" ) 
	#define CAL_sbm_createqueue  sbm_createqueue
	#define CHK_sbm_createqueue  TRUE
	#define EXP_sbm_createqueue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_createqueue", (RTS_UINTPTR)sbm_createqueue, 1, RTSITF_GET_SIGNATURE(0, 0xFEB5034F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_createqueue  PFSBM_CREATEQUEUE_IEC pfsbm_createqueue;
	#define EXT_sbm_createqueue  extern PFSBM_CREATEQUEUE_IEC pfsbm_createqueue;
	#define GET_sbm_createqueue(fl)  s_pfCMGetAPI2( "sbm_createqueue", (RTS_VOID_FCTPTR *)&pfsbm_createqueue, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFEB5034F), 0x03050500)
	#define CAL_sbm_createqueue  pfsbm_createqueue
	#define CHK_sbm_createqueue  (pfsbm_createqueue != NULL)
	#define EXP_sbm_createqueue   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_createqueue", (RTS_UINTPTR)sbm_createqueue, 1, RTSITF_GET_SIGNATURE(0, 0xFEB5034F), 0x03050500) 
#endif


/**
 * <description>sbm_deletebuffer</description>
 */
typedef struct tagsbm_deletebuffer_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_ERROR SBM_DeleteBuffer;			/* VAR_OUTPUT */	/* eError */
} sbm_deletebuffer_struct;

void CDECL CDECL_EXT sbm_deletebuffer(sbm_deletebuffer_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_DELETEBUFFER_IEC) (sbm_deletebuffer_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_DELETEBUFFER_NOTIMPLEMENTED)
	#define USE_sbm_deletebuffer
	#define EXT_sbm_deletebuffer
	#define GET_sbm_deletebuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_deletebuffer(p0) 
	#define CHK_sbm_deletebuffer  FALSE
	#define EXP_sbm_deletebuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_deletebuffer
	#define EXT_sbm_deletebuffer
	#define GET_sbm_deletebuffer(fl)  CAL_CMGETAPI( "sbm_deletebuffer" ) 
	#define CAL_sbm_deletebuffer  sbm_deletebuffer
	#define CHK_sbm_deletebuffer  TRUE
	#define EXP_sbm_deletebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_deletebuffer", (RTS_UINTPTR)sbm_deletebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x42A2EADD), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_deletebuffer
	#define EXT_sbm_deletebuffer
	#define GET_sbm_deletebuffer(fl)  CAL_CMGETAPI( "sbm_deletebuffer" ) 
	#define CAL_sbm_deletebuffer  sbm_deletebuffer
	#define CHK_sbm_deletebuffer  TRUE
	#define EXP_sbm_deletebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_deletebuffer", (RTS_UINTPTR)sbm_deletebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x42A2EADD), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_deletebuffer
	#define EXT_CmpCAASegBufferMansbm_deletebuffer
	#define GET_CmpCAASegBufferMansbm_deletebuffer  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_deletebuffer  sbm_deletebuffer
	#define CHK_CmpCAASegBufferMansbm_deletebuffer  TRUE
	#define EXP_CmpCAASegBufferMansbm_deletebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_deletebuffer", (RTS_UINTPTR)sbm_deletebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x42A2EADD), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_deletebuffer
	#define EXT_sbm_deletebuffer
	#define GET_sbm_deletebuffer(fl)  CAL_CMGETAPI( "sbm_deletebuffer" ) 
	#define CAL_sbm_deletebuffer  sbm_deletebuffer
	#define CHK_sbm_deletebuffer  TRUE
	#define EXP_sbm_deletebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_deletebuffer", (RTS_UINTPTR)sbm_deletebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x42A2EADD), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_deletebuffer  PFSBM_DELETEBUFFER_IEC pfsbm_deletebuffer;
	#define EXT_sbm_deletebuffer  extern PFSBM_DELETEBUFFER_IEC pfsbm_deletebuffer;
	#define GET_sbm_deletebuffer(fl)  s_pfCMGetAPI2( "sbm_deletebuffer", (RTS_VOID_FCTPTR *)&pfsbm_deletebuffer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x42A2EADD), 0x03050500)
	#define CAL_sbm_deletebuffer  pfsbm_deletebuffer
	#define CHK_sbm_deletebuffer  (pfsbm_deletebuffer != NULL)
	#define EXP_sbm_deletebuffer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_deletebuffer", (RTS_UINTPTR)sbm_deletebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x42A2EADD), 0x03050500) 
#endif


/**
 * <description>sbm_deletequeue</description>
 */
typedef struct tagsbm_deletequeue_struct
{
	CAA_HANDLE hQueue;					/* VAR_INPUT */	
	CAA_ERROR SBM_DeleteQueue;			/* VAR_OUTPUT */	/* eError */
} sbm_deletequeue_struct;

void CDECL CDECL_EXT sbm_deletequeue(sbm_deletequeue_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_DELETEQUEUE_IEC) (sbm_deletequeue_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_DELETEQUEUE_NOTIMPLEMENTED)
	#define USE_sbm_deletequeue
	#define EXT_sbm_deletequeue
	#define GET_sbm_deletequeue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_deletequeue(p0) 
	#define CHK_sbm_deletequeue  FALSE
	#define EXP_sbm_deletequeue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_deletequeue
	#define EXT_sbm_deletequeue
	#define GET_sbm_deletequeue(fl)  CAL_CMGETAPI( "sbm_deletequeue" ) 
	#define CAL_sbm_deletequeue  sbm_deletequeue
	#define CHK_sbm_deletequeue  TRUE
	#define EXP_sbm_deletequeue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_deletequeue", (RTS_UINTPTR)sbm_deletequeue, 1, RTSITF_GET_SIGNATURE(0, 0x1637AFBF), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_deletequeue
	#define EXT_sbm_deletequeue
	#define GET_sbm_deletequeue(fl)  CAL_CMGETAPI( "sbm_deletequeue" ) 
	#define CAL_sbm_deletequeue  sbm_deletequeue
	#define CHK_sbm_deletequeue  TRUE
	#define EXP_sbm_deletequeue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_deletequeue", (RTS_UINTPTR)sbm_deletequeue, 1, RTSITF_GET_SIGNATURE(0, 0x1637AFBF), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_deletequeue
	#define EXT_CmpCAASegBufferMansbm_deletequeue
	#define GET_CmpCAASegBufferMansbm_deletequeue  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_deletequeue  sbm_deletequeue
	#define CHK_CmpCAASegBufferMansbm_deletequeue  TRUE
	#define EXP_CmpCAASegBufferMansbm_deletequeue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_deletequeue", (RTS_UINTPTR)sbm_deletequeue, 1, RTSITF_GET_SIGNATURE(0, 0x1637AFBF), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_deletequeue
	#define EXT_sbm_deletequeue
	#define GET_sbm_deletequeue(fl)  CAL_CMGETAPI( "sbm_deletequeue" ) 
	#define CAL_sbm_deletequeue  sbm_deletequeue
	#define CHK_sbm_deletequeue  TRUE
	#define EXP_sbm_deletequeue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_deletequeue", (RTS_UINTPTR)sbm_deletequeue, 1, RTSITF_GET_SIGNATURE(0, 0x1637AFBF), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_deletequeue  PFSBM_DELETEQUEUE_IEC pfsbm_deletequeue;
	#define EXT_sbm_deletequeue  extern PFSBM_DELETEQUEUE_IEC pfsbm_deletequeue;
	#define GET_sbm_deletequeue(fl)  s_pfCMGetAPI2( "sbm_deletequeue", (RTS_VOID_FCTPTR *)&pfsbm_deletequeue, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1637AFBF), 0x03050500)
	#define CAL_sbm_deletequeue  pfsbm_deletequeue
	#define CHK_sbm_deletequeue  (pfsbm_deletequeue != NULL)
	#define EXP_sbm_deletequeue   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_deletequeue", (RTS_UINTPTR)sbm_deletequeue, 1, RTSITF_GET_SIGNATURE(0, 0x1637AFBF), 0x03050500) 
#endif


/**
 * <description>sbm_dequeuebuffer</description>
 */
typedef struct tagsbm_dequeuebuffer_struct
{
	CAA_HANDLE hQueue;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE SBM_DequeueBuffer;		/* VAR_OUTPUT */	/* hBuffer */
} sbm_dequeuebuffer_struct;

void CDECL CDECL_EXT sbm_dequeuebuffer(sbm_dequeuebuffer_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_DEQUEUEBUFFER_IEC) (sbm_dequeuebuffer_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_DEQUEUEBUFFER_NOTIMPLEMENTED)
	#define USE_sbm_dequeuebuffer
	#define EXT_sbm_dequeuebuffer
	#define GET_sbm_dequeuebuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_dequeuebuffer(p0) 
	#define CHK_sbm_dequeuebuffer  FALSE
	#define EXP_sbm_dequeuebuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_dequeuebuffer
	#define EXT_sbm_dequeuebuffer
	#define GET_sbm_dequeuebuffer(fl)  CAL_CMGETAPI( "sbm_dequeuebuffer" ) 
	#define CAL_sbm_dequeuebuffer  sbm_dequeuebuffer
	#define CHK_sbm_dequeuebuffer  TRUE
	#define EXP_sbm_dequeuebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_dequeuebuffer", (RTS_UINTPTR)sbm_dequeuebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x94D91D25), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_dequeuebuffer
	#define EXT_sbm_dequeuebuffer
	#define GET_sbm_dequeuebuffer(fl)  CAL_CMGETAPI( "sbm_dequeuebuffer" ) 
	#define CAL_sbm_dequeuebuffer  sbm_dequeuebuffer
	#define CHK_sbm_dequeuebuffer  TRUE
	#define EXP_sbm_dequeuebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_dequeuebuffer", (RTS_UINTPTR)sbm_dequeuebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x94D91D25), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_dequeuebuffer
	#define EXT_CmpCAASegBufferMansbm_dequeuebuffer
	#define GET_CmpCAASegBufferMansbm_dequeuebuffer  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_dequeuebuffer  sbm_dequeuebuffer
	#define CHK_CmpCAASegBufferMansbm_dequeuebuffer  TRUE
	#define EXP_CmpCAASegBufferMansbm_dequeuebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_dequeuebuffer", (RTS_UINTPTR)sbm_dequeuebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x94D91D25), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_dequeuebuffer
	#define EXT_sbm_dequeuebuffer
	#define GET_sbm_dequeuebuffer(fl)  CAL_CMGETAPI( "sbm_dequeuebuffer" ) 
	#define CAL_sbm_dequeuebuffer  sbm_dequeuebuffer
	#define CHK_sbm_dequeuebuffer  TRUE
	#define EXP_sbm_dequeuebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_dequeuebuffer", (RTS_UINTPTR)sbm_dequeuebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x94D91D25), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_dequeuebuffer  PFSBM_DEQUEUEBUFFER_IEC pfsbm_dequeuebuffer;
	#define EXT_sbm_dequeuebuffer  extern PFSBM_DEQUEUEBUFFER_IEC pfsbm_dequeuebuffer;
	#define GET_sbm_dequeuebuffer(fl)  s_pfCMGetAPI2( "sbm_dequeuebuffer", (RTS_VOID_FCTPTR *)&pfsbm_dequeuebuffer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x94D91D25), 0x03050500)
	#define CAL_sbm_dequeuebuffer  pfsbm_dequeuebuffer
	#define CHK_sbm_dequeuebuffer  (pfsbm_dequeuebuffer != NULL)
	#define EXP_sbm_dequeuebuffer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_dequeuebuffer", (RTS_UINTPTR)sbm_dequeuebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x94D91D25), 0x03050500) 
#endif


/**
 * <description>sbm_enqueuebuffer</description>
 */
typedef struct tagsbm_enqueuebuffer_struct
{
	CAA_HANDLE hQueue;					/* VAR_INPUT */	
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_ERROR SBM_EnqueueBuffer;		/* VAR_OUTPUT */	
} sbm_enqueuebuffer_struct;

void CDECL CDECL_EXT sbm_enqueuebuffer(sbm_enqueuebuffer_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_ENQUEUEBUFFER_IEC) (sbm_enqueuebuffer_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_ENQUEUEBUFFER_NOTIMPLEMENTED)
	#define USE_sbm_enqueuebuffer
	#define EXT_sbm_enqueuebuffer
	#define GET_sbm_enqueuebuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_enqueuebuffer(p0) 
	#define CHK_sbm_enqueuebuffer  FALSE
	#define EXP_sbm_enqueuebuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_enqueuebuffer
	#define EXT_sbm_enqueuebuffer
	#define GET_sbm_enqueuebuffer(fl)  CAL_CMGETAPI( "sbm_enqueuebuffer" ) 
	#define CAL_sbm_enqueuebuffer  sbm_enqueuebuffer
	#define CHK_sbm_enqueuebuffer  TRUE
	#define EXP_sbm_enqueuebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_enqueuebuffer", (RTS_UINTPTR)sbm_enqueuebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x4216F02A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_enqueuebuffer
	#define EXT_sbm_enqueuebuffer
	#define GET_sbm_enqueuebuffer(fl)  CAL_CMGETAPI( "sbm_enqueuebuffer" ) 
	#define CAL_sbm_enqueuebuffer  sbm_enqueuebuffer
	#define CHK_sbm_enqueuebuffer  TRUE
	#define EXP_sbm_enqueuebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_enqueuebuffer", (RTS_UINTPTR)sbm_enqueuebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x4216F02A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_enqueuebuffer
	#define EXT_CmpCAASegBufferMansbm_enqueuebuffer
	#define GET_CmpCAASegBufferMansbm_enqueuebuffer  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_enqueuebuffer  sbm_enqueuebuffer
	#define CHK_CmpCAASegBufferMansbm_enqueuebuffer  TRUE
	#define EXP_CmpCAASegBufferMansbm_enqueuebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_enqueuebuffer", (RTS_UINTPTR)sbm_enqueuebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x4216F02A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_enqueuebuffer
	#define EXT_sbm_enqueuebuffer
	#define GET_sbm_enqueuebuffer(fl)  CAL_CMGETAPI( "sbm_enqueuebuffer" ) 
	#define CAL_sbm_enqueuebuffer  sbm_enqueuebuffer
	#define CHK_sbm_enqueuebuffer  TRUE
	#define EXP_sbm_enqueuebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_enqueuebuffer", (RTS_UINTPTR)sbm_enqueuebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x4216F02A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_enqueuebuffer  PFSBM_ENQUEUEBUFFER_IEC pfsbm_enqueuebuffer;
	#define EXT_sbm_enqueuebuffer  extern PFSBM_ENQUEUEBUFFER_IEC pfsbm_enqueuebuffer;
	#define GET_sbm_enqueuebuffer(fl)  s_pfCMGetAPI2( "sbm_enqueuebuffer", (RTS_VOID_FCTPTR *)&pfsbm_enqueuebuffer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4216F02A), 0x03050500)
	#define CAL_sbm_enqueuebuffer  pfsbm_enqueuebuffer
	#define CHK_sbm_enqueuebuffer  (pfsbm_enqueuebuffer != NULL)
	#define EXP_sbm_enqueuebuffer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_enqueuebuffer", (RTS_UINTPTR)sbm_enqueuebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x4216F02A), 0x03050500) 
#endif


/**
 * <description>sbm_getbuffersize</description>
 */
typedef struct tagsbm_getbuffersize_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_SIZE SBM_GetBufferSize;			/* VAR_OUTPUT */	/* szBufferSize */
} sbm_getbuffersize_struct;

void CDECL CDECL_EXT sbm_getbuffersize(sbm_getbuffersize_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_GETBUFFERSIZE_IEC) (sbm_getbuffersize_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_GETBUFFERSIZE_NOTIMPLEMENTED)
	#define USE_sbm_getbuffersize
	#define EXT_sbm_getbuffersize
	#define GET_sbm_getbuffersize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_getbuffersize(p0) 
	#define CHK_sbm_getbuffersize  FALSE
	#define EXP_sbm_getbuffersize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_getbuffersize
	#define EXT_sbm_getbuffersize
	#define GET_sbm_getbuffersize(fl)  CAL_CMGETAPI( "sbm_getbuffersize" ) 
	#define CAL_sbm_getbuffersize  sbm_getbuffersize
	#define CHK_sbm_getbuffersize  TRUE
	#define EXP_sbm_getbuffersize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getbuffersize", (RTS_UINTPTR)sbm_getbuffersize, 1, RTSITF_GET_SIGNATURE(0, 0x03A7FF21), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_getbuffersize
	#define EXT_sbm_getbuffersize
	#define GET_sbm_getbuffersize(fl)  CAL_CMGETAPI( "sbm_getbuffersize" ) 
	#define CAL_sbm_getbuffersize  sbm_getbuffersize
	#define CHK_sbm_getbuffersize  TRUE
	#define EXP_sbm_getbuffersize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getbuffersize", (RTS_UINTPTR)sbm_getbuffersize, 1, RTSITF_GET_SIGNATURE(0, 0x03A7FF21), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_getbuffersize
	#define EXT_CmpCAASegBufferMansbm_getbuffersize
	#define GET_CmpCAASegBufferMansbm_getbuffersize  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_getbuffersize  sbm_getbuffersize
	#define CHK_CmpCAASegBufferMansbm_getbuffersize  TRUE
	#define EXP_CmpCAASegBufferMansbm_getbuffersize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getbuffersize", (RTS_UINTPTR)sbm_getbuffersize, 1, RTSITF_GET_SIGNATURE(0, 0x03A7FF21), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_getbuffersize
	#define EXT_sbm_getbuffersize
	#define GET_sbm_getbuffersize(fl)  CAL_CMGETAPI( "sbm_getbuffersize" ) 
	#define CAL_sbm_getbuffersize  sbm_getbuffersize
	#define CHK_sbm_getbuffersize  TRUE
	#define EXP_sbm_getbuffersize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getbuffersize", (RTS_UINTPTR)sbm_getbuffersize, 1, RTSITF_GET_SIGNATURE(0, 0x03A7FF21), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_getbuffersize  PFSBM_GETBUFFERSIZE_IEC pfsbm_getbuffersize;
	#define EXT_sbm_getbuffersize  extern PFSBM_GETBUFFERSIZE_IEC pfsbm_getbuffersize;
	#define GET_sbm_getbuffersize(fl)  s_pfCMGetAPI2( "sbm_getbuffersize", (RTS_VOID_FCTPTR *)&pfsbm_getbuffersize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x03A7FF21), 0x03050500)
	#define CAL_sbm_getbuffersize  pfsbm_getbuffersize
	#define CHK_sbm_getbuffersize  (pfsbm_getbuffersize != NULL)
	#define EXP_sbm_getbuffersize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getbuffersize", (RTS_UINTPTR)sbm_getbuffersize, 1, RTSITF_GET_SIGNATURE(0, 0x03A7FF21), 0x03050500) 
#endif


/**
 * <description>sbm_getqueuelength</description>
 */
typedef struct tagsbm_getqueuelength_struct
{
	CAA_HANDLE hQueue;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_SIZE SBM_GetQueueLength;		/* VAR_OUTPUT */	/* szQueueLength */
} sbm_getqueuelength_struct;

void CDECL CDECL_EXT sbm_getqueuelength(sbm_getqueuelength_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_GETQUEUELENGTH_IEC) (sbm_getqueuelength_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_GETQUEUELENGTH_NOTIMPLEMENTED)
	#define USE_sbm_getqueuelength
	#define EXT_sbm_getqueuelength
	#define GET_sbm_getqueuelength(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_getqueuelength(p0) 
	#define CHK_sbm_getqueuelength  FALSE
	#define EXP_sbm_getqueuelength  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_getqueuelength
	#define EXT_sbm_getqueuelength
	#define GET_sbm_getqueuelength(fl)  CAL_CMGETAPI( "sbm_getqueuelength" ) 
	#define CAL_sbm_getqueuelength  sbm_getqueuelength
	#define CHK_sbm_getqueuelength  TRUE
	#define EXP_sbm_getqueuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getqueuelength", (RTS_UINTPTR)sbm_getqueuelength, 1, RTSITF_GET_SIGNATURE(0, 0xFE9B8C99), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_getqueuelength
	#define EXT_sbm_getqueuelength
	#define GET_sbm_getqueuelength(fl)  CAL_CMGETAPI( "sbm_getqueuelength" ) 
	#define CAL_sbm_getqueuelength  sbm_getqueuelength
	#define CHK_sbm_getqueuelength  TRUE
	#define EXP_sbm_getqueuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getqueuelength", (RTS_UINTPTR)sbm_getqueuelength, 1, RTSITF_GET_SIGNATURE(0, 0xFE9B8C99), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_getqueuelength
	#define EXT_CmpCAASegBufferMansbm_getqueuelength
	#define GET_CmpCAASegBufferMansbm_getqueuelength  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_getqueuelength  sbm_getqueuelength
	#define CHK_CmpCAASegBufferMansbm_getqueuelength  TRUE
	#define EXP_CmpCAASegBufferMansbm_getqueuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getqueuelength", (RTS_UINTPTR)sbm_getqueuelength, 1, RTSITF_GET_SIGNATURE(0, 0xFE9B8C99), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_getqueuelength
	#define EXT_sbm_getqueuelength
	#define GET_sbm_getqueuelength(fl)  CAL_CMGETAPI( "sbm_getqueuelength" ) 
	#define CAL_sbm_getqueuelength  sbm_getqueuelength
	#define CHK_sbm_getqueuelength  TRUE
	#define EXP_sbm_getqueuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getqueuelength", (RTS_UINTPTR)sbm_getqueuelength, 1, RTSITF_GET_SIGNATURE(0, 0xFE9B8C99), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_getqueuelength  PFSBM_GETQUEUELENGTH_IEC pfsbm_getqueuelength;
	#define EXT_sbm_getqueuelength  extern PFSBM_GETQUEUELENGTH_IEC pfsbm_getqueuelength;
	#define GET_sbm_getqueuelength(fl)  s_pfCMGetAPI2( "sbm_getqueuelength", (RTS_VOID_FCTPTR *)&pfsbm_getqueuelength, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFE9B8C99), 0x03050500)
	#define CAL_sbm_getqueuelength  pfsbm_getqueuelength
	#define CHK_sbm_getqueuelength  (pfsbm_getqueuelength != NULL)
	#define EXP_sbm_getqueuelength   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getqueuelength", (RTS_UINTPTR)sbm_getqueuelength, 1, RTSITF_GET_SIGNATURE(0, 0xFE9B8C99), 0x03050500) 
#endif


/**
 * <description>sbm_getsegmentdatapointer</description>
 */
typedef struct tagsbm_getsegmentdatapointer_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_SIZE *pszSize;					/* VAR_INPUT */	/* Size of Data */
	CAA_BOOL *pxPermanent;				/* VAR_INPUT */	/* TRUE => Segment is imutable */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_PVOID SBM_GetSegmentDataPointer;	/* VAR_OUTPUT */	/* pData */
} sbm_getsegmentdatapointer_struct;

void CDECL CDECL_EXT sbm_getsegmentdatapointer(sbm_getsegmentdatapointer_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_GETSEGMENTDATAPOINTER_IEC) (sbm_getsegmentdatapointer_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_GETSEGMENTDATAPOINTER_NOTIMPLEMENTED)
	#define USE_sbm_getsegmentdatapointer
	#define EXT_sbm_getsegmentdatapointer
	#define GET_sbm_getsegmentdatapointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_getsegmentdatapointer(p0) 
	#define CHK_sbm_getsegmentdatapointer  FALSE
	#define EXP_sbm_getsegmentdatapointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_getsegmentdatapointer
	#define EXT_sbm_getsegmentdatapointer
	#define GET_sbm_getsegmentdatapointer(fl)  CAL_CMGETAPI( "sbm_getsegmentdatapointer" ) 
	#define CAL_sbm_getsegmentdatapointer  sbm_getsegmentdatapointer
	#define CHK_sbm_getsegmentdatapointer  TRUE
	#define EXP_sbm_getsegmentdatapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getsegmentdatapointer", (RTS_UINTPTR)sbm_getsegmentdatapointer, 1, RTSITF_GET_SIGNATURE(0, 0x6E812FF2), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_getsegmentdatapointer
	#define EXT_sbm_getsegmentdatapointer
	#define GET_sbm_getsegmentdatapointer(fl)  CAL_CMGETAPI( "sbm_getsegmentdatapointer" ) 
	#define CAL_sbm_getsegmentdatapointer  sbm_getsegmentdatapointer
	#define CHK_sbm_getsegmentdatapointer  TRUE
	#define EXP_sbm_getsegmentdatapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getsegmentdatapointer", (RTS_UINTPTR)sbm_getsegmentdatapointer, 1, RTSITF_GET_SIGNATURE(0, 0x6E812FF2), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_getsegmentdatapointer
	#define EXT_CmpCAASegBufferMansbm_getsegmentdatapointer
	#define GET_CmpCAASegBufferMansbm_getsegmentdatapointer  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_getsegmentdatapointer  sbm_getsegmentdatapointer
	#define CHK_CmpCAASegBufferMansbm_getsegmentdatapointer  TRUE
	#define EXP_CmpCAASegBufferMansbm_getsegmentdatapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getsegmentdatapointer", (RTS_UINTPTR)sbm_getsegmentdatapointer, 1, RTSITF_GET_SIGNATURE(0, 0x6E812FF2), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_getsegmentdatapointer
	#define EXT_sbm_getsegmentdatapointer
	#define GET_sbm_getsegmentdatapointer(fl)  CAL_CMGETAPI( "sbm_getsegmentdatapointer" ) 
	#define CAL_sbm_getsegmentdatapointer  sbm_getsegmentdatapointer
	#define CHK_sbm_getsegmentdatapointer  TRUE
	#define EXP_sbm_getsegmentdatapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getsegmentdatapointer", (RTS_UINTPTR)sbm_getsegmentdatapointer, 1, RTSITF_GET_SIGNATURE(0, 0x6E812FF2), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_getsegmentdatapointer  PFSBM_GETSEGMENTDATAPOINTER_IEC pfsbm_getsegmentdatapointer;
	#define EXT_sbm_getsegmentdatapointer  extern PFSBM_GETSEGMENTDATAPOINTER_IEC pfsbm_getsegmentdatapointer;
	#define GET_sbm_getsegmentdatapointer(fl)  s_pfCMGetAPI2( "sbm_getsegmentdatapointer", (RTS_VOID_FCTPTR *)&pfsbm_getsegmentdatapointer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6E812FF2), 0x03050500)
	#define CAL_sbm_getsegmentdatapointer  pfsbm_getsegmentdatapointer
	#define CHK_sbm_getsegmentdatapointer  (pfsbm_getsegmentdatapointer != NULL)
	#define EXP_sbm_getsegmentdatapointer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getsegmentdatapointer", (RTS_UINTPTR)sbm_getsegmentdatapointer, 1, RTSITF_GET_SIGNATURE(0, 0x6E812FF2), 0x03050500) 
#endif


/**
 * <description>sbm_movetobufferoffset</description>
 */
typedef struct tagsbm_movetobufferoffset_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_SIZE szOffset;					/* VAR_INPUT */	
	CAA_ERROR SBM_MoveToBufferOffset;	/* VAR_OUTPUT */	/* eError */
} sbm_movetobufferoffset_struct;

void CDECL CDECL_EXT sbm_movetobufferoffset(sbm_movetobufferoffset_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_MOVETOBUFFEROFFSET_IEC) (sbm_movetobufferoffset_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_MOVETOBUFFEROFFSET_NOTIMPLEMENTED)
	#define USE_sbm_movetobufferoffset
	#define EXT_sbm_movetobufferoffset
	#define GET_sbm_movetobufferoffset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_movetobufferoffset(p0) 
	#define CHK_sbm_movetobufferoffset  FALSE
	#define EXP_sbm_movetobufferoffset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_movetobufferoffset
	#define EXT_sbm_movetobufferoffset
	#define GET_sbm_movetobufferoffset(fl)  CAL_CMGETAPI( "sbm_movetobufferoffset" ) 
	#define CAL_sbm_movetobufferoffset  sbm_movetobufferoffset
	#define CHK_sbm_movetobufferoffset  TRUE
	#define EXP_sbm_movetobufferoffset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_movetobufferoffset", (RTS_UINTPTR)sbm_movetobufferoffset, 1, RTSITF_GET_SIGNATURE(0, 0x2E7ADC1E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_movetobufferoffset
	#define EXT_sbm_movetobufferoffset
	#define GET_sbm_movetobufferoffset(fl)  CAL_CMGETAPI( "sbm_movetobufferoffset" ) 
	#define CAL_sbm_movetobufferoffset  sbm_movetobufferoffset
	#define CHK_sbm_movetobufferoffset  TRUE
	#define EXP_sbm_movetobufferoffset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_movetobufferoffset", (RTS_UINTPTR)sbm_movetobufferoffset, 1, RTSITF_GET_SIGNATURE(0, 0x2E7ADC1E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_movetobufferoffset
	#define EXT_CmpCAASegBufferMansbm_movetobufferoffset
	#define GET_CmpCAASegBufferMansbm_movetobufferoffset  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_movetobufferoffset  sbm_movetobufferoffset
	#define CHK_CmpCAASegBufferMansbm_movetobufferoffset  TRUE
	#define EXP_CmpCAASegBufferMansbm_movetobufferoffset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_movetobufferoffset", (RTS_UINTPTR)sbm_movetobufferoffset, 1, RTSITF_GET_SIGNATURE(0, 0x2E7ADC1E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_movetobufferoffset
	#define EXT_sbm_movetobufferoffset
	#define GET_sbm_movetobufferoffset(fl)  CAL_CMGETAPI( "sbm_movetobufferoffset" ) 
	#define CAL_sbm_movetobufferoffset  sbm_movetobufferoffset
	#define CHK_sbm_movetobufferoffset  TRUE
	#define EXP_sbm_movetobufferoffset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_movetobufferoffset", (RTS_UINTPTR)sbm_movetobufferoffset, 1, RTSITF_GET_SIGNATURE(0, 0x2E7ADC1E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_movetobufferoffset  PFSBM_MOVETOBUFFEROFFSET_IEC pfsbm_movetobufferoffset;
	#define EXT_sbm_movetobufferoffset  extern PFSBM_MOVETOBUFFEROFFSET_IEC pfsbm_movetobufferoffset;
	#define GET_sbm_movetobufferoffset(fl)  s_pfCMGetAPI2( "sbm_movetobufferoffset", (RTS_VOID_FCTPTR *)&pfsbm_movetobufferoffset, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2E7ADC1E), 0x03050500)
	#define CAL_sbm_movetobufferoffset  pfsbm_movetobufferoffset
	#define CHK_sbm_movetobufferoffset  (pfsbm_movetobufferoffset != NULL)
	#define EXP_sbm_movetobufferoffset   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_movetobufferoffset", (RTS_UINTPTR)sbm_movetobufferoffset, 1, RTSITF_GET_SIGNATURE(0, 0x2E7ADC1E), 0x03050500) 
#endif


/**
 * <description>sbm_movetonextsegment</description>
 */
typedef struct tagsbm_movetonextsegment_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_ERROR SBM_MoveToNextSegment;	/* VAR_OUTPUT */	/* eError */
} sbm_movetonextsegment_struct;

void CDECL CDECL_EXT sbm_movetonextsegment(sbm_movetonextsegment_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_MOVETONEXTSEGMENT_IEC) (sbm_movetonextsegment_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_MOVETONEXTSEGMENT_NOTIMPLEMENTED)
	#define USE_sbm_movetonextsegment
	#define EXT_sbm_movetonextsegment
	#define GET_sbm_movetonextsegment(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_movetonextsegment(p0) 
	#define CHK_sbm_movetonextsegment  FALSE
	#define EXP_sbm_movetonextsegment  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_movetonextsegment
	#define EXT_sbm_movetonextsegment
	#define GET_sbm_movetonextsegment(fl)  CAL_CMGETAPI( "sbm_movetonextsegment" ) 
	#define CAL_sbm_movetonextsegment  sbm_movetonextsegment
	#define CHK_sbm_movetonextsegment  TRUE
	#define EXP_sbm_movetonextsegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_movetonextsegment", (RTS_UINTPTR)sbm_movetonextsegment, 1, RTSITF_GET_SIGNATURE(0, 0xC8C81F37), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_movetonextsegment
	#define EXT_sbm_movetonextsegment
	#define GET_sbm_movetonextsegment(fl)  CAL_CMGETAPI( "sbm_movetonextsegment" ) 
	#define CAL_sbm_movetonextsegment  sbm_movetonextsegment
	#define CHK_sbm_movetonextsegment  TRUE
	#define EXP_sbm_movetonextsegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_movetonextsegment", (RTS_UINTPTR)sbm_movetonextsegment, 1, RTSITF_GET_SIGNATURE(0, 0xC8C81F37), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_movetonextsegment
	#define EXT_CmpCAASegBufferMansbm_movetonextsegment
	#define GET_CmpCAASegBufferMansbm_movetonextsegment  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_movetonextsegment  sbm_movetonextsegment
	#define CHK_CmpCAASegBufferMansbm_movetonextsegment  TRUE
	#define EXP_CmpCAASegBufferMansbm_movetonextsegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_movetonextsegment", (RTS_UINTPTR)sbm_movetonextsegment, 1, RTSITF_GET_SIGNATURE(0, 0xC8C81F37), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_movetonextsegment
	#define EXT_sbm_movetonextsegment
	#define GET_sbm_movetonextsegment(fl)  CAL_CMGETAPI( "sbm_movetonextsegment" ) 
	#define CAL_sbm_movetonextsegment  sbm_movetonextsegment
	#define CHK_sbm_movetonextsegment  TRUE
	#define EXP_sbm_movetonextsegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_movetonextsegment", (RTS_UINTPTR)sbm_movetonextsegment, 1, RTSITF_GET_SIGNATURE(0, 0xC8C81F37), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_movetonextsegment  PFSBM_MOVETONEXTSEGMENT_IEC pfsbm_movetonextsegment;
	#define EXT_sbm_movetonextsegment  extern PFSBM_MOVETONEXTSEGMENT_IEC pfsbm_movetonextsegment;
	#define GET_sbm_movetonextsegment(fl)  s_pfCMGetAPI2( "sbm_movetonextsegment", (RTS_VOID_FCTPTR *)&pfsbm_movetonextsegment, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC8C81F37), 0x03050500)
	#define CAL_sbm_movetonextsegment  pfsbm_movetonextsegment
	#define CHK_sbm_movetonextsegment  (pfsbm_movetonextsegment != NULL)
	#define EXP_sbm_movetonextsegment   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_movetonextsegment", (RTS_UINTPTR)sbm_movetonextsegment, 1, RTSITF_GET_SIGNATURE(0, 0xC8C81F37), 0x03050500) 
#endif


/**
 * <description>sbm_slicebuffer</description>
 */
typedef struct tagsbm_slicebuffer_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	/* Buffer to split */
	CAA_SIZE szOffset;					/* VAR_INPUT */	/* Offset in Buffer */
	CAA_SIZE szLength;					/* VAR_INPUT */	/* Length of Data */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE SBM_SliceBuffer;			/* VAR_OUTPUT */	/* hNewBuffer */
} sbm_slicebuffer_struct;

void CDECL CDECL_EXT sbm_slicebuffer(sbm_slicebuffer_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_SLICEBUFFER_IEC) (sbm_slicebuffer_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_SLICEBUFFER_NOTIMPLEMENTED)
	#define USE_sbm_slicebuffer
	#define EXT_sbm_slicebuffer
	#define GET_sbm_slicebuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_slicebuffer(p0) 
	#define CHK_sbm_slicebuffer  FALSE
	#define EXP_sbm_slicebuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_slicebuffer
	#define EXT_sbm_slicebuffer
	#define GET_sbm_slicebuffer(fl)  CAL_CMGETAPI( "sbm_slicebuffer" ) 
	#define CAL_sbm_slicebuffer  sbm_slicebuffer
	#define CHK_sbm_slicebuffer  TRUE
	#define EXP_sbm_slicebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_slicebuffer", (RTS_UINTPTR)sbm_slicebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x8AB6BC00), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_slicebuffer
	#define EXT_sbm_slicebuffer
	#define GET_sbm_slicebuffer(fl)  CAL_CMGETAPI( "sbm_slicebuffer" ) 
	#define CAL_sbm_slicebuffer  sbm_slicebuffer
	#define CHK_sbm_slicebuffer  TRUE
	#define EXP_sbm_slicebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_slicebuffer", (RTS_UINTPTR)sbm_slicebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x8AB6BC00), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_slicebuffer
	#define EXT_CmpCAASegBufferMansbm_slicebuffer
	#define GET_CmpCAASegBufferMansbm_slicebuffer  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_slicebuffer  sbm_slicebuffer
	#define CHK_CmpCAASegBufferMansbm_slicebuffer  TRUE
	#define EXP_CmpCAASegBufferMansbm_slicebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_slicebuffer", (RTS_UINTPTR)sbm_slicebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x8AB6BC00), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_slicebuffer
	#define EXT_sbm_slicebuffer
	#define GET_sbm_slicebuffer(fl)  CAL_CMGETAPI( "sbm_slicebuffer" ) 
	#define CAL_sbm_slicebuffer  sbm_slicebuffer
	#define CHK_sbm_slicebuffer  TRUE
	#define EXP_sbm_slicebuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_slicebuffer", (RTS_UINTPTR)sbm_slicebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x8AB6BC00), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_slicebuffer  PFSBM_SLICEBUFFER_IEC pfsbm_slicebuffer;
	#define EXT_sbm_slicebuffer  extern PFSBM_SLICEBUFFER_IEC pfsbm_slicebuffer;
	#define GET_sbm_slicebuffer(fl)  s_pfCMGetAPI2( "sbm_slicebuffer", (RTS_VOID_FCTPTR *)&pfsbm_slicebuffer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8AB6BC00), 0x03050500)
	#define CAL_sbm_slicebuffer  pfsbm_slicebuffer
	#define CHK_sbm_slicebuffer  (pfsbm_slicebuffer != NULL)
	#define EXP_sbm_slicebuffer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_slicebuffer", (RTS_UINTPTR)sbm_slicebuffer, 1, RTSITF_GET_SIGNATURE(0, 0x8AB6BC00), 0x03050500) 
#endif


/**
 * <description>sbm_getsupplierversion</description>
 */
typedef struct tagsbm_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD SBM_GetSupplierVersion;	/* VAR_OUTPUT */	
} sbm_getsupplierversion_struct;

void CDECL CDECL_EXT sbm_getsupplierversion(sbm_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFSBM_GETSUPPLIERVERSION_IEC) (sbm_getsupplierversion_struct *p);
#if defined(CMPCAASEGBUFFERMAN_NOTIMPLEMENTED) || defined(SBM_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_sbm_getsupplierversion
	#define EXT_sbm_getsupplierversion
	#define GET_sbm_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sbm_getsupplierversion(p0) 
	#define CHK_sbm_getsupplierversion  FALSE
	#define EXP_sbm_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sbm_getsupplierversion
	#define EXT_sbm_getsupplierversion
	#define GET_sbm_getsupplierversion(fl)  CAL_CMGETAPI( "sbm_getsupplierversion" ) 
	#define CAL_sbm_getsupplierversion  sbm_getsupplierversion
	#define CHK_sbm_getsupplierversion  TRUE
	#define EXP_sbm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getsupplierversion", (RTS_UINTPTR)sbm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xB2BCF041), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASEGBUFFERMAN_EXTERNAL)
	#define USE_sbm_getsupplierversion
	#define EXT_sbm_getsupplierversion
	#define GET_sbm_getsupplierversion(fl)  CAL_CMGETAPI( "sbm_getsupplierversion" ) 
	#define CAL_sbm_getsupplierversion  sbm_getsupplierversion
	#define CHK_sbm_getsupplierversion  TRUE
	#define EXP_sbm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getsupplierversion", (RTS_UINTPTR)sbm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xB2BCF041), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASegBufferMansbm_getsupplierversion
	#define EXT_CmpCAASegBufferMansbm_getsupplierversion
	#define GET_CmpCAASegBufferMansbm_getsupplierversion  ERR_OK
	#define CAL_CmpCAASegBufferMansbm_getsupplierversion  sbm_getsupplierversion
	#define CHK_CmpCAASegBufferMansbm_getsupplierversion  TRUE
	#define EXP_CmpCAASegBufferMansbm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getsupplierversion", (RTS_UINTPTR)sbm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xB2BCF041), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sbm_getsupplierversion
	#define EXT_sbm_getsupplierversion
	#define GET_sbm_getsupplierversion(fl)  CAL_CMGETAPI( "sbm_getsupplierversion" ) 
	#define CAL_sbm_getsupplierversion  sbm_getsupplierversion
	#define CHK_sbm_getsupplierversion  TRUE
	#define EXP_sbm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getsupplierversion", (RTS_UINTPTR)sbm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xB2BCF041), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sbm_getsupplierversion  PFSBM_GETSUPPLIERVERSION_IEC pfsbm_getsupplierversion;
	#define EXT_sbm_getsupplierversion  extern PFSBM_GETSUPPLIERVERSION_IEC pfsbm_getsupplierversion;
	#define GET_sbm_getsupplierversion(fl)  s_pfCMGetAPI2( "sbm_getsupplierversion", (RTS_VOID_FCTPTR *)&pfsbm_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB2BCF041), 0x03050500)
	#define CAL_sbm_getsupplierversion  pfsbm_getsupplierversion
	#define CHK_sbm_getsupplierversion  (pfsbm_getsupplierversion != NULL)
	#define EXP_sbm_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sbm_getsupplierversion", (RTS_UINTPTR)sbm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xB2BCF041), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



typedef struct
{
	IBase_C *pBase;
	PFSBM_INIT ISBM_Init;
 	PFSBM_EXIT ISBM_Exit;
 	PFSBM_CHAINBUFFER ISBM_ChainBuffer;
 	PFSBM_COPYBUFFERDATA ISBM_CopyBufferData;
 	PFSBM_CREATEBUFFER ISBM_CreateBuffer;
 	PFSBM_DELETEBUFFER ISBM_DeleteBuffer;
 	PFSBM_BUFFERADDREF ISBM_BufferAddRef;
 	PFSBM_GETBUFFERSIZE ISBM_GetBufferSize;
 	PFSBM_GETSEGMENTDATAPOINTER ISBM_GetSegmentDataPointer;
 	PFSBM_MOVETOBUFFEROFFSET ISBM_MoveToBufferOffset;
 	PFSBM_MOVETONEXTSEGMENT ISBM_MoveToNextSegment;
 	PFSBM_SLICEBUFFER ISBM_SliceBuffer;
 	PFSBM_CREATEQUEUE ISBM_CreateQueue;
 	PFSBM_DELETEQUEUE ISBM_DeleteQueue;
 	PFSBM_DEQUEUEBUFFER ISBM_DequeueBuffer;
 	PFSBM_ENQUEUEBUFFER ISBM_EnqueueBuffer;
 	PFSBM_GETQUEUELENGTH ISBM_GetQueueLength;
 	PFSBM_GETSUPPLIERVERSION ISBM_GetSupplierVersion;
 } ICmpCAASegBufferMan_C;

#ifdef CPLUSPLUS
class ICmpCAASegBufferMan : public IBase
{
	public:
		virtual CAA_ERROR CDECL ISBM_Init(void) =0;
		virtual CAA_ERROR CDECL ISBM_Exit(void) =0;
		virtual SBM_PBUFFER CDECL ISBM_ChainBuffer(SBM_PBUFFER pHead, SBM_PBUFFER pTail, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ISBM_CopyBufferData(SBM_PBUFFER pBuffer, CAA_SIZE szOffset, CAA_SIZE szLength, CAA_PVOID pData, CAA_SIZE szSize) =0;
		virtual SBM_PBUFFER CDECL ISBM_CreateBuffer(CAA_SIZE szSize, CAA_PVOID pData, CAA_BOOL xPermanent, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ISBM_DeleteBuffer(SBM_PBUFFER pBuffer) =0;
		virtual CAA_ERROR CDECL ISBM_BufferAddRef(SBM_PBUFFER pBuffer) =0;
		virtual CAA_SIZE CDECL ISBM_GetBufferSize(SBM_PBUFFER pBuffer, CAA_ERROR* peError) =0;
		virtual CAA_PVOID CDECL ISBM_GetSegmentDataPointer(SBM_PBUFFER pBuffer, CAA_SIZE* pszSize, CAA_BOOL* pxPermanent, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ISBM_MoveToBufferOffset(SBM_PBUFFER pBuffer, CAA_SIZE szOffset) =0;
		virtual CAA_ERROR CDECL ISBM_MoveToNextSegment(SBM_PBUFFER pBuffer) =0;
		virtual SBM_PBUFFER CDECL ISBM_SliceBuffer(SBM_PBUFFER pBuffer, CAA_SIZE szOffset, CAA_SIZE szLength, CAA_ERROR* peError) =0;
		virtual SBM_PQUEUE CDECL ISBM_CreateQueue(CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ISBM_DeleteQueue(SBM_PQUEUE pQueue) =0;
		virtual SBM_PBUFFER CDECL ISBM_DequeueBuffer(SBM_PQUEUE pQueue, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ISBM_EnqueueBuffer(SBM_PQUEUE pQueue, SBM_PBUFFER hBuffer) =0;
		virtual CAA_SIZE CDECL ISBM_GetQueueLength(SBM_PQUEUE pQueue, CAA_ERROR* peError) =0;
		virtual CAA_UINT CDECL ISBM_GetSupplierVersion(CAA_BOOL xDummy) =0;
};
	#ifndef ITF_CmpCAASegBufferMan
		#define ITF_CmpCAASegBufferMan static ICmpCAASegBufferMan *pICmpCAASegBufferMan = NULL;
	#endif
	#define EXTITF_CmpCAASegBufferMan
#else	/*CPLUSPLUS*/
	typedef ICmpCAASegBufferMan_C		ICmpCAASegBufferMan;
	#ifndef ITF_CmpCAASegBufferMan
		#define ITF_CmpCAASegBufferMan
	#endif
	#define EXTITF_CmpCAASegBufferMan
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAASEGBUFFERMANITF_H_*/
