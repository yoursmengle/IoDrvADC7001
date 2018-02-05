 
	
	
#ifndef _CMPCAASDOCLIENTITF_H_
#define _CMPCAASDOCLIENTITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "ClientSdo.h"

#ifdef __cplusplus
extern "C" {
#endif

CAA_ERROR CDECL SDO_Read(SDO_READ* pParam);
typedef CAA_ERROR (CDECL * PFSDO_READ) (SDO_READ* pParam);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(SDO_READ_NOTIMPLEMENTED)
	#define USE_SDO_Read
	#define EXT_SDO_Read
	#define GET_SDO_Read(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SDO_Read(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SDO_Read  FALSE
	#define EXP_SDO_Read  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SDO_Read
	#define EXT_SDO_Read
	#define GET_SDO_Read(fl)  CAL_CMGETAPI( "SDO_Read" ) 
	#define CAL_SDO_Read  SDO_Read
	#define CHK_SDO_Read  TRUE
	#define EXP_SDO_Read  CAL_CMEXPAPI( "SDO_Read" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_SDO_Read
	#define EXT_SDO_Read
	#define GET_SDO_Read(fl)  CAL_CMGETAPI( "SDO_Read" ) 
	#define CAL_SDO_Read  SDO_Read
	#define CHK_SDO_Read  TRUE
	#define EXP_SDO_Read  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_Read", (RTS_UINTPTR)SDO_Read, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientSDO_Read
	#define EXT_CmpCAASdoClientSDO_Read
	#define GET_CmpCAASdoClientSDO_Read  ERR_OK
	#define CAL_CmpCAASdoClientSDO_Read pICmpCAASdoClient->ISDO_Read
	#define CHK_CmpCAASdoClientSDO_Read (pICmpCAASdoClient != NULL)
	#define EXP_CmpCAASdoClientSDO_Read  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SDO_Read
	#define EXT_SDO_Read
	#define GET_SDO_Read(fl)  CAL_CMGETAPI( "SDO_Read" ) 
	#define CAL_SDO_Read pICmpCAASdoClient->ISDO_Read
	#define CHK_SDO_Read (pICmpCAASdoClient != NULL)
	#define EXP_SDO_Read  CAL_CMEXPAPI( "SDO_Read" ) 
#else /* DYNAMIC_LINK */
	#define USE_SDO_Read  PFSDO_READ pfSDO_Read;
	#define EXT_SDO_Read  extern PFSDO_READ pfSDO_Read;
	#define GET_SDO_Read(fl)  s_pfCMGetAPI2( "SDO_Read", (RTS_VOID_FCTPTR *)&pfSDO_Read, (fl), 0, 0)
	#define CAL_SDO_Read  pfSDO_Read
	#define CHK_SDO_Read  (pfSDO_Read != NULL)
	#define EXP_SDO_Read  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_Read", (RTS_UINTPTR)SDO_Read, 0, 0) 
#endif



CAA_ERROR CDECL SDO_ReadEx(SDO_READ* pParam, CAA_ENUM eEvent);
typedef CAA_ERROR (CDECL * PFSDO_READEX) (SDO_READ* pParam, CAA_ENUM eEvent);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(SDO_READEX_NOTIMPLEMENTED)
	#define USE_SDO_ReadEx
	#define EXT_SDO_ReadEx
	#define GET_SDO_ReadEx(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SDO_ReadEx(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SDO_ReadEx  FALSE
	#define EXP_SDO_ReadEx  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SDO_ReadEx
	#define EXT_SDO_ReadEx
	#define GET_SDO_ReadEx(fl)  CAL_CMGETAPI( "SDO_ReadEx" ) 
	#define CAL_SDO_ReadEx  SDO_ReadEx
	#define CHK_SDO_ReadEx  TRUE
	#define EXP_SDO_ReadEx  CAL_CMEXPAPI( "SDO_ReadEx" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_SDO_ReadEx
	#define EXT_SDO_ReadEx
	#define GET_SDO_ReadEx(fl)  CAL_CMGETAPI( "SDO_ReadEx" ) 
	#define CAL_SDO_ReadEx  SDO_ReadEx
	#define CHK_SDO_ReadEx  TRUE
	#define EXP_SDO_ReadEx  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_ReadEx", (RTS_UINTPTR)SDO_ReadEx, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientSDO_ReadEx
	#define EXT_CmpCAASdoClientSDO_ReadEx
	#define GET_CmpCAASdoClientSDO_ReadEx  ERR_OK
	#define CAL_CmpCAASdoClientSDO_ReadEx pICmpCAASdoClient->ISDO_ReadEx
	#define CHK_CmpCAASdoClientSDO_ReadEx (pICmpCAASdoClient != NULL)
	#define EXP_CmpCAASdoClientSDO_ReadEx  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SDO_ReadEx
	#define EXT_SDO_ReadEx
	#define GET_SDO_ReadEx(fl)  CAL_CMGETAPI( "SDO_ReadEx" ) 
	#define CAL_SDO_ReadEx pICmpCAASdoClient->ISDO_ReadEx
	#define CHK_SDO_ReadEx (pICmpCAASdoClient != NULL)
	#define EXP_SDO_ReadEx  CAL_CMEXPAPI( "SDO_ReadEx" ) 
#else /* DYNAMIC_LINK */
	#define USE_SDO_ReadEx  PFSDO_READEX pfSDO_ReadEx;
	#define EXT_SDO_ReadEx  extern PFSDO_READEX pfSDO_ReadEx;
	#define GET_SDO_ReadEx(fl)  s_pfCMGetAPI2( "SDO_ReadEx", (RTS_VOID_FCTPTR *)&pfSDO_ReadEx, (fl), 0, 0)
	#define CAL_SDO_ReadEx  pfSDO_ReadEx
	#define CHK_SDO_ReadEx  (pfSDO_ReadEx != NULL)
	#define EXP_SDO_ReadEx  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_ReadEx", (RTS_UINTPTR)SDO_ReadEx, 0, 0) 
#endif



CAA_ERROR CDECL SDO_Write(SDO_WRITE* pParam);
typedef CAA_ERROR (CDECL * PFSDO_WRITE) (SDO_WRITE* pParam);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(SDO_WRITE_NOTIMPLEMENTED)
	#define USE_SDO_Write
	#define EXT_SDO_Write
	#define GET_SDO_Write(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SDO_Write(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SDO_Write  FALSE
	#define EXP_SDO_Write  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SDO_Write
	#define EXT_SDO_Write
	#define GET_SDO_Write(fl)  CAL_CMGETAPI( "SDO_Write" ) 
	#define CAL_SDO_Write  SDO_Write
	#define CHK_SDO_Write  TRUE
	#define EXP_SDO_Write  CAL_CMEXPAPI( "SDO_Write" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_SDO_Write
	#define EXT_SDO_Write
	#define GET_SDO_Write(fl)  CAL_CMGETAPI( "SDO_Write" ) 
	#define CAL_SDO_Write  SDO_Write
	#define CHK_SDO_Write  TRUE
	#define EXP_SDO_Write  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_Write", (RTS_UINTPTR)SDO_Write, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientSDO_Write
	#define EXT_CmpCAASdoClientSDO_Write
	#define GET_CmpCAASdoClientSDO_Write  ERR_OK
	#define CAL_CmpCAASdoClientSDO_Write pICmpCAASdoClient->ISDO_Write
	#define CHK_CmpCAASdoClientSDO_Write (pICmpCAASdoClient != NULL)
	#define EXP_CmpCAASdoClientSDO_Write  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SDO_Write
	#define EXT_SDO_Write
	#define GET_SDO_Write(fl)  CAL_CMGETAPI( "SDO_Write" ) 
	#define CAL_SDO_Write pICmpCAASdoClient->ISDO_Write
	#define CHK_SDO_Write (pICmpCAASdoClient != NULL)
	#define EXP_SDO_Write  CAL_CMEXPAPI( "SDO_Write" ) 
#else /* DYNAMIC_LINK */
	#define USE_SDO_Write  PFSDO_WRITE pfSDO_Write;
	#define EXT_SDO_Write  extern PFSDO_WRITE pfSDO_Write;
	#define GET_SDO_Write(fl)  s_pfCMGetAPI2( "SDO_Write", (RTS_VOID_FCTPTR *)&pfSDO_Write, (fl), 0, 0)
	#define CAL_SDO_Write  pfSDO_Write
	#define CHK_SDO_Write  (pfSDO_Write != NULL)
	#define EXP_SDO_Write  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_Write", (RTS_UINTPTR)SDO_Write, 0, 0) 
#endif



CAA_ERROR CDECL SDO_WriteEx(SDO_WRITE* pParam, CAA_ENUM eEvent);
typedef CAA_ERROR (CDECL * PFSDO_WRITEEX) (SDO_WRITE* pParam, CAA_ENUM eEvent);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(SDO_WRITEEX_NOTIMPLEMENTED)
	#define USE_SDO_WriteEx
	#define EXT_SDO_WriteEx
	#define GET_SDO_WriteEx(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SDO_WriteEx(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SDO_WriteEx  FALSE
	#define EXP_SDO_WriteEx  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SDO_WriteEx
	#define EXT_SDO_WriteEx
	#define GET_SDO_WriteEx(fl)  CAL_CMGETAPI( "SDO_WriteEx" ) 
	#define CAL_SDO_WriteEx  SDO_WriteEx
	#define CHK_SDO_WriteEx  TRUE
	#define EXP_SDO_WriteEx  CAL_CMEXPAPI( "SDO_WriteEx" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_SDO_WriteEx
	#define EXT_SDO_WriteEx
	#define GET_SDO_WriteEx(fl)  CAL_CMGETAPI( "SDO_WriteEx" ) 
	#define CAL_SDO_WriteEx  SDO_WriteEx
	#define CHK_SDO_WriteEx  TRUE
	#define EXP_SDO_WriteEx  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_WriteEx", (RTS_UINTPTR)SDO_WriteEx, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientSDO_WriteEx
	#define EXT_CmpCAASdoClientSDO_WriteEx
	#define GET_CmpCAASdoClientSDO_WriteEx  ERR_OK
	#define CAL_CmpCAASdoClientSDO_WriteEx pICmpCAASdoClient->ISDO_WriteEx
	#define CHK_CmpCAASdoClientSDO_WriteEx (pICmpCAASdoClient != NULL)
	#define EXP_CmpCAASdoClientSDO_WriteEx  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SDO_WriteEx
	#define EXT_SDO_WriteEx
	#define GET_SDO_WriteEx(fl)  CAL_CMGETAPI( "SDO_WriteEx" ) 
	#define CAL_SDO_WriteEx pICmpCAASdoClient->ISDO_WriteEx
	#define CHK_SDO_WriteEx (pICmpCAASdoClient != NULL)
	#define EXP_SDO_WriteEx  CAL_CMEXPAPI( "SDO_WriteEx" ) 
#else /* DYNAMIC_LINK */
	#define USE_SDO_WriteEx  PFSDO_WRITEEX pfSDO_WriteEx;
	#define EXT_SDO_WriteEx  extern PFSDO_WRITEEX pfSDO_WriteEx;
	#define GET_SDO_WriteEx(fl)  s_pfCMGetAPI2( "SDO_WriteEx", (RTS_VOID_FCTPTR *)&pfSDO_WriteEx, (fl), 0, 0)
	#define CAL_SDO_WriteEx  pfSDO_WriteEx
	#define CHK_SDO_WriteEx  (pfSDO_WriteEx != NULL)
	#define EXP_SDO_WriteEx  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_WriteEx", (RTS_UINTPTR)SDO_WriteEx, 0, 0) 
#endif



CAA_ERROR CDECL SDO_Write2(SDO_WRITE2* pParam, CAA_ENUM eEvent);
typedef CAA_ERROR (CDECL * PFSDO_WRITE2) (SDO_WRITE2* pParam, CAA_ENUM eEvent);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(SDO_WRITE2_NOTIMPLEMENTED)
	#define USE_SDO_Write2
	#define EXT_SDO_Write2
	#define GET_SDO_Write2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SDO_Write2(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SDO_Write2  FALSE
	#define EXP_SDO_Write2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SDO_Write2
	#define EXT_SDO_Write2
	#define GET_SDO_Write2(fl)  CAL_CMGETAPI( "SDO_Write2" ) 
	#define CAL_SDO_Write2  SDO_Write2
	#define CHK_SDO_Write2  TRUE
	#define EXP_SDO_Write2  CAL_CMEXPAPI( "SDO_Write2" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_SDO_Write2
	#define EXT_SDO_Write2
	#define GET_SDO_Write2(fl)  CAL_CMGETAPI( "SDO_Write2" ) 
	#define CAL_SDO_Write2  SDO_Write2
	#define CHK_SDO_Write2  TRUE
	#define EXP_SDO_Write2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_Write2", (RTS_UINTPTR)SDO_Write2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientSDO_Write2
	#define EXT_CmpCAASdoClientSDO_Write2
	#define GET_CmpCAASdoClientSDO_Write2  ERR_OK
	#define CAL_CmpCAASdoClientSDO_Write2 pICmpCAASdoClient->ISDO_Write2
	#define CHK_CmpCAASdoClientSDO_Write2 (pICmpCAASdoClient != NULL)
	#define EXP_CmpCAASdoClientSDO_Write2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SDO_Write2
	#define EXT_SDO_Write2
	#define GET_SDO_Write2(fl)  CAL_CMGETAPI( "SDO_Write2" ) 
	#define CAL_SDO_Write2 pICmpCAASdoClient->ISDO_Write2
	#define CHK_SDO_Write2 (pICmpCAASdoClient != NULL)
	#define EXP_SDO_Write2  CAL_CMEXPAPI( "SDO_Write2" ) 
#else /* DYNAMIC_LINK */
	#define USE_SDO_Write2  PFSDO_WRITE2 pfSDO_Write2;
	#define EXT_SDO_Write2  extern PFSDO_WRITE2 pfSDO_Write2;
	#define GET_SDO_Write2(fl)  s_pfCMGetAPI2( "SDO_Write2", (RTS_VOID_FCTPTR *)&pfSDO_Write2, (fl), 0, 0)
	#define CAL_SDO_Write2  pfSDO_Write2
	#define CHK_SDO_Write2  (pfSDO_Write2 != NULL)
	#define EXP_SDO_Write2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_Write2", (RTS_UINTPTR)SDO_Write2, 0, 0) 
#endif



CAA_ERROR CDECL SDO_Read2(SDO_READ2* pParam, CAA_ENUM eEvent);
typedef CAA_ERROR (CDECL * PFSDO_READ2) (SDO_READ2* pParam, CAA_ENUM eEvent);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(SDO_READ2_NOTIMPLEMENTED)
	#define USE_SDO_Read2
	#define EXT_SDO_Read2
	#define GET_SDO_Read2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SDO_Read2(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_SDO_Read2  FALSE
	#define EXP_SDO_Read2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SDO_Read2
	#define EXT_SDO_Read2
	#define GET_SDO_Read2(fl)  CAL_CMGETAPI( "SDO_Read2" ) 
	#define CAL_SDO_Read2  SDO_Read2
	#define CHK_SDO_Read2  TRUE
	#define EXP_SDO_Read2  CAL_CMEXPAPI( "SDO_Read2" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_SDO_Read2
	#define EXT_SDO_Read2
	#define GET_SDO_Read2(fl)  CAL_CMGETAPI( "SDO_Read2" ) 
	#define CAL_SDO_Read2  SDO_Read2
	#define CHK_SDO_Read2  TRUE
	#define EXP_SDO_Read2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_Read2", (RTS_UINTPTR)SDO_Read2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientSDO_Read2
	#define EXT_CmpCAASdoClientSDO_Read2
	#define GET_CmpCAASdoClientSDO_Read2  ERR_OK
	#define CAL_CmpCAASdoClientSDO_Read2 pICmpCAASdoClient->ISDO_Read2
	#define CHK_CmpCAASdoClientSDO_Read2 (pICmpCAASdoClient != NULL)
	#define EXP_CmpCAASdoClientSDO_Read2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SDO_Read2
	#define EXT_SDO_Read2
	#define GET_SDO_Read2(fl)  CAL_CMGETAPI( "SDO_Read2" ) 
	#define CAL_SDO_Read2 pICmpCAASdoClient->ISDO_Read2
	#define CHK_SDO_Read2 (pICmpCAASdoClient != NULL)
	#define EXP_SDO_Read2  CAL_CMEXPAPI( "SDO_Read2" ) 
#else /* DYNAMIC_LINK */
	#define USE_SDO_Read2  PFSDO_READ2 pfSDO_Read2;
	#define EXT_SDO_Read2  extern PFSDO_READ2 pfSDO_Read2;
	#define GET_SDO_Read2(fl)  s_pfCMGetAPI2( "SDO_Read2", (RTS_VOID_FCTPTR *)&pfSDO_Read2, (fl), 0, 0)
	#define CAL_SDO_Read2  pfSDO_Read2
	#define CHK_SDO_Read2  (pfSDO_Read2 != NULL)
	#define EXP_SDO_Read2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SDO_Read2", (RTS_UINTPTR)SDO_Read2, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>sdo_read</description>
 * SDO Read for CANopenStack before 3.5.7.0 (only for compatibility)
 */
typedef struct tagsdo_read_struct
{
	SDO_READ* pParam;	/* VAR_INPUT */
	CAA_ERROR SDO_Read;	/* VAR_OUTPUT */
} sdo_read_struct;

void CDECL CDECL_EXT sdo_read(sdo_read_struct *p);
typedef void (CDECL CDECL_EXT* PFSDO_READ_IEC) (sdo_read_struct *p);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(SDO_READ_NOTIMPLEMENTED)
	#define USE_sdo_read
	#define EXT_sdo_read
	#define GET_sdo_read(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sdo_read(p0) 
	#define CHK_sdo_read  FALSE
	#define EXP_sdo_read  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sdo_read
	#define EXT_sdo_read
	#define GET_sdo_read(fl)  CAL_CMGETAPI( "sdo_read" ) 
	#define CAL_sdo_read  sdo_read
	#define CHK_sdo_read  TRUE
	#define EXP_sdo_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_read", (RTS_UINTPTR)sdo_read, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_sdo_read
	#define EXT_sdo_read
	#define GET_sdo_read(fl)  CAL_CMGETAPI( "sdo_read" ) 
	#define CAL_sdo_read  sdo_read
	#define CHK_sdo_read  TRUE
	#define EXP_sdo_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_read", (RTS_UINTPTR)sdo_read, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientsdo_read
	#define EXT_CmpCAASdoClientsdo_read
	#define GET_CmpCAASdoClientsdo_read  ERR_OK
	#define CAL_CmpCAASdoClientsdo_read  sdo_read
	#define CHK_CmpCAASdoClientsdo_read  TRUE
	#define EXP_CmpCAASdoClientsdo_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_read", (RTS_UINTPTR)sdo_read, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_sdo_read
	#define EXT_sdo_read
	#define GET_sdo_read(fl)  CAL_CMGETAPI( "sdo_read" ) 
	#define CAL_sdo_read  sdo_read
	#define CHK_sdo_read  TRUE
	#define EXP_sdo_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_read", (RTS_UINTPTR)sdo_read, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_sdo_read  PFSDO_READ_IEC pfsdo_read;
	#define EXT_sdo_read  extern PFSDO_READ_IEC pfsdo_read;
	#define GET_sdo_read(fl)  s_pfCMGetAPI2( "sdo_read", (RTS_VOID_FCTPTR *)&pfsdo_read, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_sdo_read  pfsdo_read
	#define CHK_sdo_read  (pfsdo_read != NULL)
	#define EXP_sdo_read   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_read", (RTS_UINTPTR)sdo_read, 1, 0x0, 0x0) 
#endif


/**
 * <description>
 * SDO Write for CANopenStack before 3.5.7.0 (only for compatibility)
 * </description>
 */
typedef struct tagsdo_write_struct
{
	SDO_WRITE* pParam;		/* VAR_INPUT */
	CAA_ERROR SDO_Write;	/* VAR_OUTPUT */
} sdo_write_struct;

void CDECL CDECL_EXT sdo_write(sdo_write_struct *p);
typedef void (CDECL CDECL_EXT* PFSDO_WRITE_IEC) (sdo_write_struct *p);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(SDO_WRITE_NOTIMPLEMENTED)
	#define USE_sdo_write
	#define EXT_sdo_write
	#define GET_sdo_write(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sdo_write(p0) 
	#define CHK_sdo_write  FALSE
	#define EXP_sdo_write  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sdo_write
	#define EXT_sdo_write
	#define GET_sdo_write(fl)  CAL_CMGETAPI( "sdo_write" ) 
	#define CAL_sdo_write  sdo_write
	#define CHK_sdo_write  TRUE
	#define EXP_sdo_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_write", (RTS_UINTPTR)sdo_write, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_sdo_write
	#define EXT_sdo_write
	#define GET_sdo_write(fl)  CAL_CMGETAPI( "sdo_write" ) 
	#define CAL_sdo_write  sdo_write
	#define CHK_sdo_write  TRUE
	#define EXP_sdo_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_write", (RTS_UINTPTR)sdo_write, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientsdo_write
	#define EXT_CmpCAASdoClientsdo_write
	#define GET_CmpCAASdoClientsdo_write  ERR_OK
	#define CAL_CmpCAASdoClientsdo_write  sdo_write
	#define CHK_CmpCAASdoClientsdo_write  TRUE
	#define EXP_CmpCAASdoClientsdo_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_write", (RTS_UINTPTR)sdo_write, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_sdo_write
	#define EXT_sdo_write
	#define GET_sdo_write(fl)  CAL_CMGETAPI( "sdo_write" ) 
	#define CAL_sdo_write  sdo_write
	#define CHK_sdo_write  TRUE
	#define EXP_sdo_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_write", (RTS_UINTPTR)sdo_write, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_sdo_write  PFSDO_WRITE_IEC pfsdo_write;
	#define EXT_sdo_write  extern PFSDO_WRITE_IEC pfsdo_write;
	#define GET_sdo_write(fl)  s_pfCMGetAPI2( "sdo_write", (RTS_VOID_FCTPTR *)&pfsdo_write, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_sdo_write  pfsdo_write
	#define CHK_sdo_write  (pfsdo_write != NULL)
	#define EXP_sdo_write   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_write", (RTS_UINTPTR)sdo_write, 1, 0x0, 0x0) 
#endif


 /**
 * <description>
 * SDO Read for CANopenStack 3.5.7.0 or newer.
 * Changes: uiSize => udiSize
 * </description>
 */
typedef struct tagsdo_read2_struct
{
	SDO_READ2 *pParam;					/* VAR_INPUT */	
	RTS_IEC_INT SDO_Read2;				/* VAR_OUTPUT, Enum: ERROR */
} sdo_read2_struct;

void CDECL CDECL_EXT sdo_read2(sdo_read2_struct *p);
typedef void (CDECL CDECL_EXT* PFSDO_READ2_IEC) (sdo_read2_struct *p);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(SDO_READ2_NOTIMPLEMENTED)
	#define USE_sdo_read2
	#define EXT_sdo_read2
	#define GET_sdo_read2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sdo_read2(p0) 
	#define CHK_sdo_read2  FALSE
	#define EXP_sdo_read2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sdo_read2
	#define EXT_sdo_read2
	#define GET_sdo_read2(fl)  CAL_CMGETAPI( "sdo_read2" ) 
	#define CAL_sdo_read2  sdo_read2
	#define CHK_sdo_read2  TRUE
	#define EXP_sdo_read2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_read2", (RTS_UINTPTR)sdo_read2, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_sdo_read2
	#define EXT_sdo_read2
	#define GET_sdo_read2(fl)  CAL_CMGETAPI( "sdo_read2" ) 
	#define CAL_sdo_read2  sdo_read2
	#define CHK_sdo_read2  TRUE
	#define EXP_sdo_read2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_read2", (RTS_UINTPTR)sdo_read2, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientsdo_read2
	#define EXT_CmpCAASdoClientsdo_read2
	#define GET_CmpCAASdoClientsdo_read2  ERR_OK
	#define CAL_CmpCAASdoClientsdo_read2  sdo_read2
	#define CHK_CmpCAASdoClientsdo_read2  TRUE
	#define EXP_CmpCAASdoClientsdo_read2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_read2", (RTS_UINTPTR)sdo_read2, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_sdo_read2
	#define EXT_sdo_read2
	#define GET_sdo_read2(fl)  CAL_CMGETAPI( "sdo_read2" ) 
	#define CAL_sdo_read2  sdo_read2
	#define CHK_sdo_read2  TRUE
	#define EXP_sdo_read2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_read2", (RTS_UINTPTR)sdo_read2, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_sdo_read2  PFSDO_READ2_IEC pfsdo_read2;
	#define EXT_sdo_read2  extern PFSDO_READ2_IEC pfsdo_read2;
	#define GET_sdo_read2(fl)  s_pfCMGetAPI2( "sdo_read2", (RTS_VOID_FCTPTR *)&pfsdo_read2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_sdo_read2  pfsdo_read2
	#define CHK_sdo_read2  (pfsdo_read2 != NULL)
	#define EXP_sdo_read2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_read2", (RTS_UINTPTR)sdo_read2, 1, 0x0, 0x0) 
#endif


/**
 * <description>
 * SDO Write for CANopenStack 3.5.7.0 or newer.
 * Changes: uiSize => udiSize
 * </description>
 */
typedef struct tagsdo_write2_struct
{
	SDO_WRITE2 *pParam;					/* VAR_INPUT */	
	RTS_IEC_INT SDO_Write2;				/* VAR_OUTPUT, Enum: ERROR */
} sdo_write2_struct;

void CDECL CDECL_EXT sdo_write2(sdo_write2_struct *p);
typedef void (CDECL CDECL_EXT* PFSDO_WRITE2_IEC) (sdo_write2_struct *p);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(SDO_WRITE2_NOTIMPLEMENTED)
	#define USE_sdo_write2
	#define EXT_sdo_write2
	#define GET_sdo_write2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sdo_write2(p0) 
	#define CHK_sdo_write2  FALSE
	#define EXP_sdo_write2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sdo_write2
	#define EXT_sdo_write2
	#define GET_sdo_write2(fl)  CAL_CMGETAPI( "sdo_write2" ) 
	#define CAL_sdo_write2  sdo_write2
	#define CHK_sdo_write2  TRUE
	#define EXP_sdo_write2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_write2", (RTS_UINTPTR)sdo_write2, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_sdo_write2
	#define EXT_sdo_write2
	#define GET_sdo_write2(fl)  CAL_CMGETAPI( "sdo_write2" ) 
	#define CAL_sdo_write2  sdo_write2
	#define CHK_sdo_write2  TRUE
	#define EXP_sdo_write2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_write2", (RTS_UINTPTR)sdo_write2, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientsdo_write2
	#define EXT_CmpCAASdoClientsdo_write2
	#define GET_CmpCAASdoClientsdo_write2  ERR_OK
	#define CAL_CmpCAASdoClientsdo_write2  sdo_write2
	#define CHK_CmpCAASdoClientsdo_write2  TRUE
	#define EXP_CmpCAASdoClientsdo_write2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_write2", (RTS_UINTPTR)sdo_write2, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_sdo_write2
	#define EXT_sdo_write2
	#define GET_sdo_write2(fl)  CAL_CMGETAPI( "sdo_write2" ) 
	#define CAL_sdo_write2  sdo_write2
	#define CHK_sdo_write2  TRUE
	#define EXP_sdo_write2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_write2", (RTS_UINTPTR)sdo_write2, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_sdo_write2  PFSDO_WRITE2_IEC pfsdo_write2;
	#define EXT_sdo_write2  extern PFSDO_WRITE2_IEC pfsdo_write2;
	#define GET_sdo_write2(fl)  s_pfCMGetAPI2( "sdo_write2", (RTS_VOID_FCTPTR *)&pfsdo_write2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_sdo_write2  pfsdo_write2
	#define CHK_sdo_write2  (pfsdo_write2 != NULL)
	#define EXP_sdo_write2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdo_write2", (RTS_UINTPTR)sdo_write2, 1, 0x0, 0x0) 
#endif


/**
 * <description>nodeset__main</description>
 */
typedef struct tagnodeset_struct
{
	void* __VFTABLEPOINTER;			/* Pointer to virtual function table */

	CAA_UINT auiNodes[8];			/* Local variable */
	CAA_BOOL xThreadSafe;			/* Local variable */
	CAA_CRITSEC
	CAA_USINT usiMaxActive;			/* Local variable */
	CAA_USINT usiCurrentActive;		/* Local variable */
	CAA_UINT uiNoLimitationNodeID;	/* Local variable */
} nodeset_struct;

typedef struct
{
	nodeset_struct *pInstance;	/* VAR_INPUT */
} nodeset_main_struct;

void CDECL CDECL_EXT nodeset__main(nodeset_main_struct *p);
typedef void (CDECL CDECL_EXT* PFNODESET__MAIN_IEC) (nodeset_main_struct *p);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(NODESET__MAIN_NOTIMPLEMENTED)
	#define USE_nodeset__main
	#define EXT_nodeset__main
	#define GET_nodeset__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_nodeset__main(p0) 
	#define CHK_nodeset__main  FALSE
	#define EXP_nodeset__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_nodeset__main
	#define EXT_nodeset__main
	#define GET_nodeset__main(fl)  CAL_CMGETAPI( "nodeset__main" ) 
	#define CAL_nodeset__main  nodeset__main
	#define CHK_nodeset__main  TRUE
	#define EXP_nodeset__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__main", (RTS_UINTPTR)nodeset__main, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_nodeset__main
	#define EXT_nodeset__main
	#define GET_nodeset__main(fl)  CAL_CMGETAPI( "nodeset__main" ) 
	#define CAL_nodeset__main  nodeset__main
	#define CHK_nodeset__main  TRUE
	#define EXP_nodeset__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__main", (RTS_UINTPTR)nodeset__main, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientnodeset__main
	#define EXT_CmpCAASdoClientnodeset__main
	#define GET_CmpCAASdoClientnodeset__main  ERR_OK
	#define CAL_CmpCAASdoClientnodeset__main  nodeset__main
	#define CHK_CmpCAASdoClientnodeset__main  TRUE
	#define EXP_CmpCAASdoClientnodeset__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__main", (RTS_UINTPTR)nodeset__main, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_nodeset__main
	#define EXT_nodeset__main
	#define GET_nodeset__main(fl)  CAL_CMGETAPI( "nodeset__main" ) 
	#define CAL_nodeset__main  nodeset__main
	#define CHK_nodeset__main  TRUE
	#define EXP_nodeset__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__main", (RTS_UINTPTR)nodeset__main, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_nodeset__main  PFNODESET__MAIN_IEC pfnodeset__main;
	#define EXT_nodeset__main  extern PFNODESET__MAIN_IEC pfnodeset__main;
	#define GET_nodeset__main(fl)  s_pfCMGetAPI2( "nodeset__main", (RTS_VOID_FCTPTR *)&pfnodeset__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_nodeset__main  pfnodeset__main
	#define CHK_nodeset__main  (pfnodeset__main != NULL)
	#define EXP_nodeset__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__main", (RTS_UINTPTR)nodeset__main, 1, 0x0, 0x0) 
#endif


/**
 * <description>nodeset_fb_reinit</description>
 */
typedef struct tagnodeset_fb_reinit_struct
{
	nodeset_struct *pInstance;			/* VAR_INPUT */
	CAA_BOOL FB_ReInit;					/* VAR_OUTPUT */
} nodeset_fb_reinit_struct;

void CDECL CDECL_EXT nodeset__fb_reinit(nodeset_fb_reinit_struct *p);
typedef void (CDECL CDECL_EXT* PFNODESET__FB_REINIT_IEC) (nodeset_fb_reinit_struct *p);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(NODESET__FB_REINIT_NOTIMPLEMENTED)
	#define USE_nodeset__fb_reinit
	#define EXT_nodeset__fb_reinit
	#define GET_nodeset__fb_reinit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_nodeset__fb_reinit(p0) 
	#define CHK_nodeset__fb_reinit  FALSE
	#define EXP_nodeset__fb_reinit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_nodeset__fb_reinit
	#define EXT_nodeset__fb_reinit
	#define GET_nodeset__fb_reinit(fl)  CAL_CMGETAPI( "nodeset__fb_reinit" ) 
	#define CAL_nodeset__fb_reinit  nodeset__fb_reinit
	#define CHK_nodeset__fb_reinit  TRUE
	#define EXP_nodeset__fb_reinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_reinit", (RTS_UINTPTR)nodeset__fb_reinit, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_nodeset__fb_reinit
	#define EXT_nodeset__fb_reinit
	#define GET_nodeset__fb_reinit(fl)  CAL_CMGETAPI( "nodeset__fb_reinit" ) 
	#define CAL_nodeset__fb_reinit  nodeset__fb_reinit
	#define CHK_nodeset__fb_reinit  TRUE
	#define EXP_nodeset__fb_reinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_reinit", (RTS_UINTPTR)nodeset__fb_reinit, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientnodeset__fb_reinit
	#define EXT_CmpCAASdoClientnodeset__fb_reinit
	#define GET_CmpCAASdoClientnodeset__fb_reinit  ERR_OK
	#define CAL_CmpCAASdoClientnodeset__fb_reinit  nodeset__fb_reinit
	#define CHK_CmpCAASdoClientnodeset__fb_reinit  TRUE
	#define EXP_CmpCAASdoClientnodeset__fb_reinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_reinit", (RTS_UINTPTR)nodeset__fb_reinit, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_nodeset__fb_reinit
	#define EXT_nodeset__fb_reinit
	#define GET_nodeset__fb_reinit(fl)  CAL_CMGETAPI( "nodeset__fb_reinit" ) 
	#define CAL_nodeset__fb_reinit  nodeset__fb_reinit
	#define CHK_nodeset__fb_reinit  TRUE
	#define EXP_nodeset__fb_reinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_reinit", (RTS_UINTPTR)nodeset__fb_reinit, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_nodeset__fb_reinit  PFNODESET__FB_REINIT_IEC pfnodeset__fb_reinit;
	#define EXT_nodeset__fb_reinit  extern PFNODESET__FB_REINIT_IEC pfnodeset__fb_reinit;
	#define GET_nodeset__fb_reinit(fl)  s_pfCMGetAPI2( "nodeset__fb_reinit", (RTS_VOID_FCTPTR *)&pfnodeset__fb_reinit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_nodeset__fb_reinit  pfnodeset__fb_reinit
	#define CHK_nodeset__fb_reinit  (pfnodeset__fb_reinit != NULL)
	#define EXP_nodeset__fb_reinit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_reinit", (RTS_UINTPTR)nodeset__fb_reinit, 1, 0x0, 0x0) 
#endif


/**
 * <description>nodeset_isactive</description>
 */
typedef struct tagnodeset_isactive_struct
{
	nodeset_struct *pInstance;			/* VAR_INPUT */
	CAA_USINT usiNodeId;				/* VAR_INPUT */
	CAA_BOOL IsActive;					/* VAR_OUTPUT */
} nodeset_isactive_struct;

void CDECL CDECL_EXT nodeset__isactive(nodeset_isactive_struct *p);
typedef void (CDECL CDECL_EXT* PFNODESET__ISACTIVE_IEC) (nodeset_isactive_struct *p);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(NODESET__ISACTIVE_NOTIMPLEMENTED)
	#define USE_nodeset__isactive
	#define EXT_nodeset__isactive
	#define GET_nodeset__isactive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_nodeset__isactive(p0) 
	#define CHK_nodeset__isactive  FALSE
	#define EXP_nodeset__isactive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_nodeset__isactive
	#define EXT_nodeset__isactive
	#define GET_nodeset__isactive(fl)  CAL_CMGETAPI( "nodeset__isactive" ) 
	#define CAL_nodeset__isactive  nodeset__isactive
	#define CHK_nodeset__isactive  TRUE
	#define EXP_nodeset__isactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__isactive", (RTS_UINTPTR)nodeset__isactive, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_nodeset__isactive
	#define EXT_nodeset__isactive
	#define GET_nodeset__isactive(fl)  CAL_CMGETAPI( "nodeset__isactive" ) 
	#define CAL_nodeset__isactive  nodeset__isactive
	#define CHK_nodeset__isactive  TRUE
	#define EXP_nodeset__isactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__isactive", (RTS_UINTPTR)nodeset__isactive, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientnodeset__isactive
	#define EXT_CmpCAASdoClientnodeset__isactive
	#define GET_CmpCAASdoClientnodeset__isactive  ERR_OK
	#define CAL_CmpCAASdoClientnodeset__isactive  nodeset__isactive
	#define CHK_CmpCAASdoClientnodeset__isactive  TRUE
	#define EXP_CmpCAASdoClientnodeset__isactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__isactive", (RTS_UINTPTR)nodeset__isactive, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_nodeset__isactive
	#define EXT_nodeset__isactive
	#define GET_nodeset__isactive(fl)  CAL_CMGETAPI( "nodeset__isactive" ) 
	#define CAL_nodeset__isactive  nodeset__isactive
	#define CHK_nodeset__isactive  TRUE
	#define EXP_nodeset__isactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__isactive", (RTS_UINTPTR)nodeset__isactive, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_nodeset__isactive  PFNODESET__ISACTIVE_IEC pfnodeset__isactive;
	#define EXT_nodeset__isactive  extern PFNODESET__ISACTIVE_IEC pfnodeset__isactive;
	#define GET_nodeset__isactive(fl)  s_pfCMGetAPI2( "nodeset__isactive", (RTS_VOID_FCTPTR *)&pfnodeset__isactive, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_nodeset__isactive  pfnodeset__isactive
	#define CHK_nodeset__isactive  (pfnodeset__isactive != NULL)
	#define EXP_nodeset__isactive   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__isactive", (RTS_UINTPTR)nodeset__isactive, 1, 0x0, 0x0) 
#endif


/**
 * <description>nodeset_fb_init</description>
 */
typedef struct tagnodeset_fb_init_struct
{
	nodeset_struct *pInstance;		/* VAR_INPUT */
	CAA_BOOL bInitRetains;			/* VAR_INPUT */
	CAA_BOOL bInCopyCode;			/* VAR_INPUT */
	CAA_BOOL xThreadSafe;			/* VAR_INPUT */
	CAA_BOOL Fb_Init;				/* VAR_OUTPUT */
} nodeset_fb_init_struct;

void CDECL CDECL_EXT nodeset__fb_init(nodeset_fb_init_struct *p);
typedef void (CDECL CDECL_EXT* PFNODESET__FB_INIT_IEC) (nodeset_fb_init_struct *p);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(NODESET__FB_INIT_NOTIMPLEMENTED)
	#define USE_nodeset__fb_init
	#define EXT_nodeset__fb_init
	#define GET_nodeset__fb_init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_nodeset__fb_init(p0) 
	#define CHK_nodeset__fb_init  FALSE
	#define EXP_nodeset__fb_init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_nodeset__fb_init
	#define EXT_nodeset__fb_init
	#define GET_nodeset__fb_init(fl)  CAL_CMGETAPI( "nodeset__fb_init" ) 
	#define CAL_nodeset__fb_init  nodeset__fb_init
	#define CHK_nodeset__fb_init  TRUE
	#define EXP_nodeset__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_init", (RTS_UINTPTR)nodeset__fb_init, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_nodeset__fb_init
	#define EXT_nodeset__fb_init
	#define GET_nodeset__fb_init(fl)  CAL_CMGETAPI( "nodeset__fb_init" ) 
	#define CAL_nodeset__fb_init  nodeset__fb_init
	#define CHK_nodeset__fb_init  TRUE
	#define EXP_nodeset__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_init", (RTS_UINTPTR)nodeset__fb_init, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientnodeset__fb_init
	#define EXT_CmpCAASdoClientnodeset__fb_init
	#define GET_CmpCAASdoClientnodeset__fb_init  ERR_OK
	#define CAL_CmpCAASdoClientnodeset__fb_init  nodeset__fb_init
	#define CHK_CmpCAASdoClientnodeset__fb_init  TRUE
	#define EXP_CmpCAASdoClientnodeset__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_init", (RTS_UINTPTR)nodeset__fb_init, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_nodeset__fb_init
	#define EXT_nodeset__fb_init
	#define GET_nodeset__fb_init(fl)  CAL_CMGETAPI( "nodeset__fb_init" ) 
	#define CAL_nodeset__fb_init  nodeset__fb_init
	#define CHK_nodeset__fb_init  TRUE
	#define EXP_nodeset__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_init", (RTS_UINTPTR)nodeset__fb_init, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_nodeset__fb_init  PFNODESET__FB_INIT_IEC pfnodeset__fb_init;
	#define EXT_nodeset__fb_init  extern PFNODESET__FB_INIT_IEC pfnodeset__fb_init;
	#define GET_nodeset__fb_init(fl)  s_pfCMGetAPI2( "nodeset__fb_init", (RTS_VOID_FCTPTR *)&pfnodeset__fb_init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_nodeset__fb_init  pfnodeset__fb_init
	#define CHK_nodeset__fb_init  (pfnodeset__fb_init != NULL)
	#define EXP_nodeset__fb_init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_init", (RTS_UINTPTR)nodeset__fb_init, 1, 0x0, 0x0) 
#endif


/**
 * <description>nodeset_activate</description>
 */
typedef struct tagnodeset_activate_struct
{
	nodeset_struct *pInstance;		/* VAR_INPUT */
	CAA_USINT usiNodeId;			/* VAR_INPUT */
	CAA_BOOL Activate;				/* VAR_OUTPUT */
} nodeset_activate_struct;

void CDECL CDECL_EXT nodeset__activate(nodeset_activate_struct *p);
typedef void (CDECL CDECL_EXT* PFNODESET__ACTIVATE_IEC) (nodeset_activate_struct *p);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(NODESET__ACTIVATE_NOTIMPLEMENTED)
	#define USE_nodeset__activate
	#define EXT_nodeset__activate
	#define GET_nodeset__activate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_nodeset__activate(p0) 
	#define CHK_nodeset__activate  FALSE
	#define EXP_nodeset__activate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_nodeset__activate
	#define EXT_nodeset__activate
	#define GET_nodeset__activate(fl)  CAL_CMGETAPI( "nodeset__activate" ) 
	#define CAL_nodeset__activate  nodeset__activate
	#define CHK_nodeset__activate  TRUE
	#define EXP_nodeset__activate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__activate", (RTS_UINTPTR)nodeset__activate, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_nodeset__activate
	#define EXT_nodeset__activate
	#define GET_nodeset__activate(fl)  CAL_CMGETAPI( "nodeset__activate" ) 
	#define CAL_nodeset__activate  nodeset__activate
	#define CHK_nodeset__activate  TRUE
	#define EXP_nodeset__activate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__activate", (RTS_UINTPTR)nodeset__activate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientnodeset__activate
	#define EXT_CmpCAASdoClientnodeset__activate
	#define GET_CmpCAASdoClientnodeset__activate  ERR_OK
	#define CAL_CmpCAASdoClientnodeset__activate  nodeset__activate
	#define CHK_CmpCAASdoClientnodeset__activate  TRUE
	#define EXP_CmpCAASdoClientnodeset__activate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__activate", (RTS_UINTPTR)nodeset__activate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_nodeset__activate
	#define EXT_nodeset__activate
	#define GET_nodeset__activate(fl)  CAL_CMGETAPI( "nodeset__activate" ) 
	#define CAL_nodeset__activate  nodeset__activate
	#define CHK_nodeset__activate  TRUE
	#define EXP_nodeset__activate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__activate", (RTS_UINTPTR)nodeset__activate, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_nodeset__activate  PFNODESET__ACTIVATE_IEC pfnodeset__activate;
	#define EXT_nodeset__activate  extern PFNODESET__ACTIVATE_IEC pfnodeset__activate;
	#define GET_nodeset__activate(fl)  s_pfCMGetAPI2( "nodeset__activate", (RTS_VOID_FCTPTR *)&pfnodeset__activate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_nodeset__activate  pfnodeset__activate
	#define CHK_nodeset__activate  (pfnodeset__activate != NULL)
	#define EXP_nodeset__activate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__activate", (RTS_UINTPTR)nodeset__activate, 1, 0x0, 0x0) 
#endif


/**
 * <description>nodeset_deactivate</description>
 */
typedef struct tagnodeset_deactivate_struct
{
	nodeset_struct *pInstance;		/* VAR_INPUT */
	CAA_USINT usiNodeId;			/* VAR_INPUT */
	CAA_BOOL Deactivate;			/* VAR_OUTPUT */
} nodeset_deactivate_struct;

void CDECL CDECL_EXT nodeset__deactivate(nodeset_deactivate_struct *p);
typedef void (CDECL CDECL_EXT* PFNODESET__DEACTIVATE_IEC) (nodeset_deactivate_struct *p);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(NODESET__DEACTIVATE_NOTIMPLEMENTED)
	#define USE_nodeset__deactivate
	#define EXT_nodeset__deactivate
	#define GET_nodeset__deactivate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_nodeset__deactivate(p0) 
	#define CHK_nodeset__deactivate  FALSE
	#define EXP_nodeset__deactivate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_nodeset__deactivate
	#define EXT_nodeset__deactivate
	#define GET_nodeset__deactivate(fl)  CAL_CMGETAPI( "nodeset__deactivate" ) 
	#define CAL_nodeset__deactivate  nodeset__deactivate
	#define CHK_nodeset__deactivate  TRUE
	#define EXP_nodeset__deactivate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__deactivate", (RTS_UINTPTR)nodeset__deactivate, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_nodeset__deactivate
	#define EXT_nodeset__deactivate
	#define GET_nodeset__deactivate(fl)  CAL_CMGETAPI( "nodeset__deactivate" ) 
	#define CAL_nodeset__deactivate  nodeset__deactivate
	#define CHK_nodeset__deactivate  TRUE
	#define EXP_nodeset__deactivate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__deactivate", (RTS_UINTPTR)nodeset__deactivate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientnodeset__deactivate
	#define EXT_CmpCAASdoClientnodeset__deactivate
	#define GET_CmpCAASdoClientnodeset__deactivate  ERR_OK
	#define CAL_CmpCAASdoClientnodeset__deactivate  nodeset__deactivate
	#define CHK_CmpCAASdoClientnodeset__deactivate  TRUE
	#define EXP_CmpCAASdoClientnodeset__deactivate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__deactivate", (RTS_UINTPTR)nodeset__deactivate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_nodeset__deactivate
	#define EXT_nodeset__deactivate
	#define GET_nodeset__deactivate(fl)  CAL_CMGETAPI( "nodeset__deactivate" ) 
	#define CAL_nodeset__deactivate  nodeset__deactivate
	#define CHK_nodeset__deactivate  TRUE
	#define EXP_nodeset__deactivate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__deactivate", (RTS_UINTPTR)nodeset__deactivate, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_nodeset__deactivate  PFNODESET__DEACTIVATE_IEC pfnodeset__deactivate;
	#define EXT_nodeset__deactivate  extern PFNODESET__DEACTIVATE_IEC pfnodeset__deactivate;
	#define GET_nodeset__deactivate(fl)  s_pfCMGetAPI2( "nodeset__deactivate", (RTS_VOID_FCTPTR *)&pfnodeset__deactivate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_nodeset__deactivate  pfnodeset__deactivate
	#define CHK_nodeset__deactivate  (pfnodeset__deactivate != NULL)
	#define EXP_nodeset__deactivate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__deactivate", (RTS_UINTPTR)nodeset__deactivate, 1, 0x0, 0x0) 
#endif


/**
 * <description>nodeset_fb_exit</description>
 */
typedef struct tagnodeset_fb_exit_struct
{
	nodeset_struct *pInstance;		/* VAR_INPUT */
	CAA_BOOL bInCopyCode;			/* VAR_INPUT */
	CAA_BOOL Fb_Exit;				/* VAR_OUTPUT */
} nodeset_fb_exit_struct;

void CDECL CDECL_EXT nodeset__fb_exit(nodeset_fb_exit_struct *p);
typedef void (CDECL CDECL_EXT* PFNODESET__FB_EXIT_IEC) (nodeset_fb_exit_struct *p);
#if defined(CMPCAASDOCLIENT_NOTIMPLEMENTED) || defined(NODESET__FB_EXIT_NOTIMPLEMENTED)
	#define USE_nodeset__fb_exit
	#define EXT_nodeset__fb_exit
	#define GET_nodeset__fb_exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_nodeset__fb_exit(p0) 
	#define CHK_nodeset__fb_exit  FALSE
	#define EXP_nodeset__fb_exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_nodeset__fb_exit
	#define EXT_nodeset__fb_exit
	#define GET_nodeset__fb_exit(fl)  CAL_CMGETAPI( "nodeset__fb_exit" ) 
	#define CAL_nodeset__fb_exit  nodeset__fb_exit
	#define CHK_nodeset__fb_exit  TRUE
	#define EXP_nodeset__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_exit", (RTS_UINTPTR)nodeset__fb_exit, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOCLIENT_EXTERNAL)
	#define USE_nodeset__fb_exit
	#define EXT_nodeset__fb_exit
	#define GET_nodeset__fb_exit(fl)  CAL_CMGETAPI( "nodeset__fb_exit" ) 
	#define CAL_nodeset__fb_exit  nodeset__fb_exit
	#define CHK_nodeset__fb_exit  TRUE
	#define EXP_nodeset__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_exit", (RTS_UINTPTR)nodeset__fb_exit, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoClientnodeset__fb_exit
	#define EXT_CmpCAASdoClientnodeset__fb_exit
	#define GET_CmpCAASdoClientnodeset__fb_exit  ERR_OK
	#define CAL_CmpCAASdoClientnodeset__fb_exit  nodeset__fb_exit
	#define CHK_CmpCAASdoClientnodeset__fb_exit  TRUE
	#define EXP_CmpCAASdoClientnodeset__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_exit", (RTS_UINTPTR)nodeset__fb_exit, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_nodeset__fb_exit
	#define EXT_nodeset__fb_exit
	#define GET_nodeset__fb_exit(fl)  CAL_CMGETAPI( "nodeset__fb_exit" ) 
	#define CAL_nodeset__fb_exit  nodeset__fb_exit
	#define CHK_nodeset__fb_exit  TRUE
	#define EXP_nodeset__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_exit", (RTS_UINTPTR)nodeset__fb_exit, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_nodeset__fb_exit  PFNODESET__FB_EXIT_IEC pfnodeset__fb_exit;
	#define EXT_nodeset__fb_exit  extern PFNODESET__FB_EXIT_IEC pfnodeset__fb_exit;
	#define GET_nodeset__fb_exit(fl)  s_pfCMGetAPI2( "nodeset__fb_exit", (RTS_VOID_FCTPTR *)&pfnodeset__fb_exit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_nodeset__fb_exit  pfnodeset__fb_exit
	#define CHK_nodeset__fb_exit  (pfnodeset__fb_exit != NULL)
	#define EXP_nodeset__fb_exit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nodeset__fb_exit", (RTS_UINTPTR)nodeset__fb_exit, 1, 0x0, 0x0) 
#endif



#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



typedef struct
{
	IBase_C *pBase;
	PFSDO_READ ISDO_Read;
 	PFSDO_READEX ISDO_ReadEx;
 	PFSDO_WRITE ISDO_Write;
 	PFSDO_WRITEEX ISDO_WriteEx;
 	PFSDO_WRITE2 ISDO_Write2;
 	PFSDO_READ2 ISDO_Read2;
 } ICmpCAASdoClient_C;

#ifdef CPLUSPLUS
class ICmpCAASdoClient : public IBase
{
	public:
		virtual CAA_ERROR CDECL ISDO_Read(SDO_READ* pParam) =0;
		virtual CAA_ERROR CDECL ISDO_ReadEx(SDO_READ* pParam, CAA_ENUM eEvent) =0;
		virtual CAA_ERROR CDECL ISDO_Write(SDO_WRITE* pParam) =0;
		virtual CAA_ERROR CDECL ISDO_WriteEx(SDO_WRITE* pParam, CAA_ENUM eEvent) =0;
		virtual CAA_ERROR CDECL ISDO_Write2(SDO_WRITE2* pParam, CAA_ENUM eEvent) =0;
		virtual CAA_ERROR CDECL ISDO_Read2(SDO_READ2* pParam, CAA_ENUM eEvent) =0;
};
	#ifndef ITF_CmpCAASdoClient
		#define ITF_CmpCAASdoClient static ICmpCAASdoClient *pICmpCAASdoClient = NULL;
	#endif
	#define EXTITF_CmpCAASdoClient
#else	/*CPLUSPLUS*/
	typedef ICmpCAASdoClient_C		ICmpCAASdoClient;
	#ifndef ITF_CmpCAASdoClient
		#define ITF_CmpCAASdoClient
	#endif
	#define EXTITF_CmpCAASdoClient
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAASDOCLIENTITF_H_*/
