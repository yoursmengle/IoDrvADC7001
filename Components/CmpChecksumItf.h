 /**
 * <interfacename>CmpChecksum</interfacename>
 * <description>
 *	Interface for the checksum utility component.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPCHECKSUMITF_H_
#define _CMPCHECKSUMITF_H_

#include "CmpStd.h"

 

 





/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>crc16finish</description>
 */
typedef struct tagcrc16finish_struct
{
	RTS_IEC_WORD ulCRC;					/* VAR_INPUT */	
	RTS_IEC_WORD CRC16Finish;			/* VAR_OUTPUT */	
} crc16finish_struct;

void CDECL CDECL_EXT crc16finish(crc16finish_struct *p);
typedef void (CDECL CDECL_EXT* PFCRC16FINISH_IEC) (crc16finish_struct *p);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC16FINISH_NOTIMPLEMENTED)
	#define USE_crc16finish
	#define EXT_crc16finish
	#define GET_crc16finish(fl)  ERR_NOTIMPLEMENTED
	#define CAL_crc16finish(p0) 
	#define CHK_crc16finish  FALSE
	#define EXP_crc16finish  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_crc16finish
	#define EXT_crc16finish
	#define GET_crc16finish(fl)  CAL_CMGETAPI( "crc16finish" ) 
	#define CAL_crc16finish  crc16finish
	#define CHK_crc16finish  TRUE
	#define EXP_crc16finish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16finish", (RTS_UINTPTR)crc16finish, 1, 0x614D590C, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_crc16finish
	#define EXT_crc16finish
	#define GET_crc16finish(fl)  CAL_CMGETAPI( "crc16finish" ) 
	#define CAL_crc16finish  crc16finish
	#define CHK_crc16finish  TRUE
	#define EXP_crc16finish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16finish", (RTS_UINTPTR)crc16finish, 1, 0x614D590C, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumcrc16finish
	#define EXT_CmpChecksumcrc16finish
	#define GET_CmpChecksumcrc16finish  ERR_OK
	#define CAL_CmpChecksumcrc16finish  crc16finish
	#define CHK_CmpChecksumcrc16finish  TRUE
	#define EXP_CmpChecksumcrc16finish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16finish", (RTS_UINTPTR)crc16finish, 1, 0x614D590C, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_crc16finish
	#define EXT_crc16finish
	#define GET_crc16finish(fl)  CAL_CMGETAPI( "crc16finish" ) 
	#define CAL_crc16finish  crc16finish
	#define CHK_crc16finish  TRUE
	#define EXP_crc16finish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16finish", (RTS_UINTPTR)crc16finish, 1, 0x614D590C, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_crc16finish  PFCRC16FINISH_IEC pfcrc16finish;
	#define EXT_crc16finish  extern PFCRC16FINISH_IEC pfcrc16finish;
	#define GET_crc16finish(fl)  s_pfCMGetAPI2( "crc16finish", (RTS_VOID_FCTPTR *)&pfcrc16finish, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x614D590C, 0x03050500)
	#define CAL_crc16finish  pfcrc16finish
	#define CHK_crc16finish  (pfcrc16finish != NULL)
	#define EXP_crc16finish   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16finish", (RTS_UINTPTR)crc16finish, 1, 0x614D590C, 0x03050500) 
#endif


/**
 * <description>crc16init</description>
 */
typedef struct tagcrc16init_struct
{
	RTS_IEC_WORD CRC16Init;				/* VAR_OUTPUT */	
} crc16init_struct;

void CDECL CDECL_EXT crc16init(crc16init_struct *p);
typedef void (CDECL CDECL_EXT* PFCRC16INIT_IEC) (crc16init_struct *p);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC16INIT_NOTIMPLEMENTED)
	#define USE_crc16init
	#define EXT_crc16init
	#define GET_crc16init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_crc16init(p0) 
	#define CHK_crc16init  FALSE
	#define EXP_crc16init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_crc16init
	#define EXT_crc16init
	#define GET_crc16init(fl)  CAL_CMGETAPI( "crc16init" ) 
	#define CAL_crc16init  crc16init
	#define CHK_crc16init  TRUE
	#define EXP_crc16init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16init", (RTS_UINTPTR)crc16init, 1, 0xED70411E, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_crc16init
	#define EXT_crc16init
	#define GET_crc16init(fl)  CAL_CMGETAPI( "crc16init" ) 
	#define CAL_crc16init  crc16init
	#define CHK_crc16init  TRUE
	#define EXP_crc16init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16init", (RTS_UINTPTR)crc16init, 1, 0xED70411E, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumcrc16init
	#define EXT_CmpChecksumcrc16init
	#define GET_CmpChecksumcrc16init  ERR_OK
	#define CAL_CmpChecksumcrc16init  crc16init
	#define CHK_CmpChecksumcrc16init  TRUE
	#define EXP_CmpChecksumcrc16init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16init", (RTS_UINTPTR)crc16init, 1, 0xED70411E, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_crc16init
	#define EXT_crc16init
	#define GET_crc16init(fl)  CAL_CMGETAPI( "crc16init" ) 
	#define CAL_crc16init  crc16init
	#define CHK_crc16init  TRUE
	#define EXP_crc16init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16init", (RTS_UINTPTR)crc16init, 1, 0xED70411E, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_crc16init  PFCRC16INIT_IEC pfcrc16init;
	#define EXT_crc16init  extern PFCRC16INIT_IEC pfcrc16init;
	#define GET_crc16init(fl)  s_pfCMGetAPI2( "crc16init", (RTS_VOID_FCTPTR *)&pfcrc16init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xED70411E, 0x03050500)
	#define CAL_crc16init  pfcrc16init
	#define CHK_crc16init  (pfcrc16init != NULL)
	#define EXP_crc16init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16init", (RTS_UINTPTR)crc16init, 1, 0xED70411E, 0x03050500) 
#endif


/**
 * <description>crc16update</description>
 */
typedef struct tagcrc16update_struct
{
	RTS_IEC_WORD ulCRC;					/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_XWORD ulSize;				/* VAR_INPUT */	
	RTS_IEC_WORD CRC16Update;			/* VAR_OUTPUT */	
} crc16update_struct;

void CDECL CDECL_EXT crc16update(crc16update_struct *p);
typedef void (CDECL CDECL_EXT* PFCRC16UPDATE_IEC) (crc16update_struct *p);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC16UPDATE_NOTIMPLEMENTED)
	#define USE_crc16update
	#define EXT_crc16update
	#define GET_crc16update(fl)  ERR_NOTIMPLEMENTED
	#define CAL_crc16update(p0) 
	#define CHK_crc16update  FALSE
	#define EXP_crc16update  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_crc16update
	#define EXT_crc16update
	#define GET_crc16update(fl)  CAL_CMGETAPI( "crc16update" ) 
	#define CAL_crc16update  crc16update
	#define CHK_crc16update  TRUE
	#define EXP_crc16update  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16update", (RTS_UINTPTR)crc16update, 1, RTSITF_GET_SIGNATURE(0, 0x3373C5C6), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_crc16update
	#define EXT_crc16update
	#define GET_crc16update(fl)  CAL_CMGETAPI( "crc16update" ) 
	#define CAL_crc16update  crc16update
	#define CHK_crc16update  TRUE
	#define EXP_crc16update  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16update", (RTS_UINTPTR)crc16update, 1, RTSITF_GET_SIGNATURE(0, 0x3373C5C6), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumcrc16update
	#define EXT_CmpChecksumcrc16update
	#define GET_CmpChecksumcrc16update  ERR_OK
	#define CAL_CmpChecksumcrc16update  crc16update
	#define CHK_CmpChecksumcrc16update  TRUE
	#define EXP_CmpChecksumcrc16update  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16update", (RTS_UINTPTR)crc16update, 1, RTSITF_GET_SIGNATURE(0, 0x3373C5C6), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_crc16update
	#define EXT_crc16update
	#define GET_crc16update(fl)  CAL_CMGETAPI( "crc16update" ) 
	#define CAL_crc16update  crc16update
	#define CHK_crc16update  TRUE
	#define EXP_crc16update  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16update", (RTS_UINTPTR)crc16update, 1, RTSITF_GET_SIGNATURE(0, 0x3373C5C6), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_crc16update  PFCRC16UPDATE_IEC pfcrc16update;
	#define EXT_crc16update  extern PFCRC16UPDATE_IEC pfcrc16update;
	#define GET_crc16update(fl)  s_pfCMGetAPI2( "crc16update", (RTS_VOID_FCTPTR *)&pfcrc16update, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x3373C5C6), 0x03050500)
	#define CAL_crc16update  pfcrc16update
	#define CHK_crc16update  (pfcrc16update != NULL)
	#define EXP_crc16update   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc16update", (RTS_UINTPTR)crc16update, 1, RTSITF_GET_SIGNATURE(0, 0x3373C5C6), 0x03050500) 
#endif


/**
 * <description>crc32finish</description>
 */
typedef struct tagcrc32finish_struct
{
	RTS_IEC_DWORD ulCRC;				/* VAR_INPUT */	
	RTS_IEC_DWORD CRC32Finish;			/* VAR_OUTPUT */	
} crc32finish_struct;

void CDECL CDECL_EXT crc32finish(crc32finish_struct *p);
typedef void (CDECL CDECL_EXT* PFCRC32FINISH_IEC) (crc32finish_struct *p);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC32FINISH_NOTIMPLEMENTED)
	#define USE_crc32finish
	#define EXT_crc32finish
	#define GET_crc32finish(fl)  ERR_NOTIMPLEMENTED
	#define CAL_crc32finish(p0) 
	#define CHK_crc32finish  FALSE
	#define EXP_crc32finish  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_crc32finish
	#define EXT_crc32finish
	#define GET_crc32finish(fl)  CAL_CMGETAPI( "crc32finish" ) 
	#define CAL_crc32finish  crc32finish
	#define CHK_crc32finish  TRUE
	#define EXP_crc32finish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32finish", (RTS_UINTPTR)crc32finish, 1, 0x4BF5AEF0, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_crc32finish
	#define EXT_crc32finish
	#define GET_crc32finish(fl)  CAL_CMGETAPI( "crc32finish" ) 
	#define CAL_crc32finish  crc32finish
	#define CHK_crc32finish  TRUE
	#define EXP_crc32finish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32finish", (RTS_UINTPTR)crc32finish, 1, 0x4BF5AEF0, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumcrc32finish
	#define EXT_CmpChecksumcrc32finish
	#define GET_CmpChecksumcrc32finish  ERR_OK
	#define CAL_CmpChecksumcrc32finish  crc32finish
	#define CHK_CmpChecksumcrc32finish  TRUE
	#define EXP_CmpChecksumcrc32finish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32finish", (RTS_UINTPTR)crc32finish, 1, 0x4BF5AEF0, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_crc32finish
	#define EXT_crc32finish
	#define GET_crc32finish(fl)  CAL_CMGETAPI( "crc32finish" ) 
	#define CAL_crc32finish  crc32finish
	#define CHK_crc32finish  TRUE
	#define EXP_crc32finish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32finish", (RTS_UINTPTR)crc32finish, 1, 0x4BF5AEF0, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_crc32finish  PFCRC32FINISH_IEC pfcrc32finish;
	#define EXT_crc32finish  extern PFCRC32FINISH_IEC pfcrc32finish;
	#define GET_crc32finish(fl)  s_pfCMGetAPI2( "crc32finish", (RTS_VOID_FCTPTR *)&pfcrc32finish, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4BF5AEF0, 0x03050500)
	#define CAL_crc32finish  pfcrc32finish
	#define CHK_crc32finish  (pfcrc32finish != NULL)
	#define EXP_crc32finish   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32finish", (RTS_UINTPTR)crc32finish, 1, 0x4BF5AEF0, 0x03050500) 
#endif


/**
 * <description>crc32init</description>
 */
typedef struct tagcrc32init_struct
{
	RTS_IEC_DWORD CRC32Init;			/* VAR_OUTPUT */	
} crc32init_struct;

void CDECL CDECL_EXT crc32init(crc32init_struct *p);
typedef void (CDECL CDECL_EXT* PFCRC32INIT_IEC) (crc32init_struct *p);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC32INIT_NOTIMPLEMENTED)
	#define USE_crc32init
	#define EXT_crc32init
	#define GET_crc32init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_crc32init(p0) 
	#define CHK_crc32init  FALSE
	#define EXP_crc32init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_crc32init
	#define EXT_crc32init
	#define GET_crc32init(fl)  CAL_CMGETAPI( "crc32init" ) 
	#define CAL_crc32init  crc32init
	#define CHK_crc32init  TRUE
	#define EXP_crc32init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32init", (RTS_UINTPTR)crc32init, 1, 0x4847BC72, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_crc32init
	#define EXT_crc32init
	#define GET_crc32init(fl)  CAL_CMGETAPI( "crc32init" ) 
	#define CAL_crc32init  crc32init
	#define CHK_crc32init  TRUE
	#define EXP_crc32init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32init", (RTS_UINTPTR)crc32init, 1, 0x4847BC72, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumcrc32init
	#define EXT_CmpChecksumcrc32init
	#define GET_CmpChecksumcrc32init  ERR_OK
	#define CAL_CmpChecksumcrc32init  crc32init
	#define CHK_CmpChecksumcrc32init  TRUE
	#define EXP_CmpChecksumcrc32init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32init", (RTS_UINTPTR)crc32init, 1, 0x4847BC72, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_crc32init
	#define EXT_crc32init
	#define GET_crc32init(fl)  CAL_CMGETAPI( "crc32init" ) 
	#define CAL_crc32init  crc32init
	#define CHK_crc32init  TRUE
	#define EXP_crc32init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32init", (RTS_UINTPTR)crc32init, 1, 0x4847BC72, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_crc32init  PFCRC32INIT_IEC pfcrc32init;
	#define EXT_crc32init  extern PFCRC32INIT_IEC pfcrc32init;
	#define GET_crc32init(fl)  s_pfCMGetAPI2( "crc32init", (RTS_VOID_FCTPTR *)&pfcrc32init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4847BC72, 0x03050500)
	#define CAL_crc32init  pfcrc32init
	#define CHK_crc32init  (pfcrc32init != NULL)
	#define EXP_crc32init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32init", (RTS_UINTPTR)crc32init, 1, 0x4847BC72, 0x03050500) 
#endif


/**
 * <description>crc32update</description>
 */
typedef struct tagcrc32update_struct
{
	RTS_IEC_DWORD ulCRC;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_XWORD ulSize;				/* VAR_INPUT */	
	RTS_IEC_DWORD CRC32Update;			/* VAR_OUTPUT */	
} crc32update_struct;

void CDECL CDECL_EXT crc32update(crc32update_struct *p);
typedef void (CDECL CDECL_EXT* PFCRC32UPDATE_IEC) (crc32update_struct *p);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC32UPDATE_NOTIMPLEMENTED)
	#define USE_crc32update
	#define EXT_crc32update
	#define GET_crc32update(fl)  ERR_NOTIMPLEMENTED
	#define CAL_crc32update(p0) 
	#define CHK_crc32update  FALSE
	#define EXP_crc32update  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_crc32update
	#define EXT_crc32update
	#define GET_crc32update(fl)  CAL_CMGETAPI( "crc32update" ) 
	#define CAL_crc32update  crc32update
	#define CHK_crc32update  TRUE
	#define EXP_crc32update  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32update", (RTS_UINTPTR)crc32update, 1, RTSITF_GET_SIGNATURE(0, 0x19CB323A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_crc32update
	#define EXT_crc32update
	#define GET_crc32update(fl)  CAL_CMGETAPI( "crc32update" ) 
	#define CAL_crc32update  crc32update
	#define CHK_crc32update  TRUE
	#define EXP_crc32update  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32update", (RTS_UINTPTR)crc32update, 1, RTSITF_GET_SIGNATURE(0, 0x19CB323A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumcrc32update
	#define EXT_CmpChecksumcrc32update
	#define GET_CmpChecksumcrc32update  ERR_OK
	#define CAL_CmpChecksumcrc32update  crc32update
	#define CHK_CmpChecksumcrc32update  TRUE
	#define EXP_CmpChecksumcrc32update  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32update", (RTS_UINTPTR)crc32update, 1, RTSITF_GET_SIGNATURE(0, 0x19CB323A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_crc32update
	#define EXT_crc32update
	#define GET_crc32update(fl)  CAL_CMGETAPI( "crc32update" ) 
	#define CAL_crc32update  crc32update
	#define CHK_crc32update  TRUE
	#define EXP_crc32update  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32update", (RTS_UINTPTR)crc32update, 1, RTSITF_GET_SIGNATURE(0, 0x19CB323A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_crc32update  PFCRC32UPDATE_IEC pfcrc32update;
	#define EXT_crc32update  extern PFCRC32UPDATE_IEC pfcrc32update;
	#define GET_crc32update(fl)  s_pfCMGetAPI2( "crc32update", (RTS_VOID_FCTPTR *)&pfcrc32update, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x19CB323A), 0x03050500)
	#define CAL_crc32update  pfcrc32update
	#define CHK_crc32update  (pfcrc32update != NULL)
	#define EXP_crc32update   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32update", (RTS_UINTPTR)crc32update, 1, RTSITF_GET_SIGNATURE(0, 0x19CB323A), 0x03050500) 
#endif


/**
 * <description>crc32update2</description>
 */
typedef struct tagcrc32update2_struct
{
	RTS_IEC_DWORD ulCRC;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_XWORD ulSize;				/* VAR_INPUT */	
	RTS_IEC_DWORD CRC32Update2;			/* VAR_OUTPUT */	
} crc32update2_struct;

void CDECL CDECL_EXT crc32update2(crc32update2_struct *p);
typedef void (CDECL CDECL_EXT* PFCRC32UPDATE2_IEC) (crc32update2_struct *p);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC32UPDATE2_NOTIMPLEMENTED)
	#define USE_crc32update2
	#define EXT_crc32update2
	#define GET_crc32update2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_crc32update2(p0) 
	#define CHK_crc32update2  FALSE
	#define EXP_crc32update2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_crc32update2
	#define EXT_crc32update2
	#define GET_crc32update2(fl)  CAL_CMGETAPI( "crc32update2" ) 
	#define CAL_crc32update2  crc32update2
	#define CHK_crc32update2  TRUE
	#define EXP_crc32update2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32update2", (RTS_UINTPTR)crc32update2, 1, RTSITF_GET_SIGNATURE(0, 0xEE853B38), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_crc32update2
	#define EXT_crc32update2
	#define GET_crc32update2(fl)  CAL_CMGETAPI( "crc32update2" ) 
	#define CAL_crc32update2  crc32update2
	#define CHK_crc32update2  TRUE
	#define EXP_crc32update2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32update2", (RTS_UINTPTR)crc32update2, 1, RTSITF_GET_SIGNATURE(0, 0xEE853B38), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumcrc32update2
	#define EXT_CmpChecksumcrc32update2
	#define GET_CmpChecksumcrc32update2  ERR_OK
	#define CAL_CmpChecksumcrc32update2  crc32update2
	#define CHK_CmpChecksumcrc32update2  TRUE
	#define EXP_CmpChecksumcrc32update2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32update2", (RTS_UINTPTR)crc32update2, 1, RTSITF_GET_SIGNATURE(0, 0xEE853B38), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_crc32update2
	#define EXT_crc32update2
	#define GET_crc32update2(fl)  CAL_CMGETAPI( "crc32update2" ) 
	#define CAL_crc32update2  crc32update2
	#define CHK_crc32update2  TRUE
	#define EXP_crc32update2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32update2", (RTS_UINTPTR)crc32update2, 1, RTSITF_GET_SIGNATURE(0, 0xEE853B38), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_crc32update2  PFCRC32UPDATE2_IEC pfcrc32update2;
	#define EXT_crc32update2  extern PFCRC32UPDATE2_IEC pfcrc32update2;
	#define GET_crc32update2(fl)  s_pfCMGetAPI2( "crc32update2", (RTS_VOID_FCTPTR *)&pfcrc32update2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xEE853B38), 0x03050500)
	#define CAL_crc32update2  pfcrc32update2
	#define CHK_crc32update2  (pfcrc32update2 != NULL)
	#define EXP_crc32update2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"crc32update2", (RTS_UINTPTR)crc32update2, 1, RTSITF_GET_SIGNATURE(0, 0xEE853B38), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Implementation of a 16-Bit CRC. The CRC is based on the 
 *  CCITT polynom x^16 + x^12 + x^5 + 1.
 *  Since there seem to be different opinions about "the" CCITT CRC-16,
 *  here a description of the options used in this api:
 *  - Bits are shifted in with MSB first
 *  - Input bytes are NOT reversed
 *  - The final CRC is NOT reversed
 *  - Initial value is 0xFFFF
 *  - 16 Zero-bits are implicitly appended to the end of the message
 *  - The "checkvalue" is 0xE5CC (ie. the CRC of the ASCII string '123456789')
 * </description>
 */
RTS_UI16 CDECL CRC16Init(void);
typedef RTS_UI16 (CDECL * PFCRC16INIT) (void);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC16INIT_NOTIMPLEMENTED)
	#define USE_CRC16Init
	#define EXT_CRC16Init
	#define GET_CRC16Init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CRC16Init() (RTS_UI16)ERR_NOTIMPLEMENTED
	#define CHK_CRC16Init  FALSE
	#define EXP_CRC16Init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CRC16Init
	#define EXT_CRC16Init
	#define GET_CRC16Init(fl)  CAL_CMGETAPI( "CRC16Init" ) 
	#define CAL_CRC16Init  CRC16Init
	#define CHK_CRC16Init  TRUE
	#define EXP_CRC16Init  CAL_CMEXPAPI( "CRC16Init" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_CRC16Init
	#define EXT_CRC16Init
	#define GET_CRC16Init(fl)  CAL_CMGETAPI( "CRC16Init" ) 
	#define CAL_CRC16Init  CRC16Init
	#define CHK_CRC16Init  TRUE
	#define EXP_CRC16Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC16Init", (RTS_UINTPTR)CRC16Init, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumCRC16Init
	#define EXT_CmpChecksumCRC16Init
	#define GET_CmpChecksumCRC16Init  ERR_OK
	#define CAL_CmpChecksumCRC16Init  CRC16Init
	#define CHK_CmpChecksumCRC16Init  TRUE
	#define EXP_CmpChecksumCRC16Init  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CRC16Init
	#define EXT_CRC16Init
	#define GET_CRC16Init(fl)  CAL_CMGETAPI( "CRC16Init" ) 
	#define CAL_CRC16Init  CRC16Init
	#define CHK_CRC16Init  TRUE
	#define EXP_CRC16Init  CAL_CMEXPAPI( "CRC16Init" ) 
#else /* DYNAMIC_LINK */
	#define USE_CRC16Init  PFCRC16INIT pfCRC16Init;
	#define EXT_CRC16Init  extern PFCRC16INIT pfCRC16Init;
	#define GET_CRC16Init(fl)  s_pfCMGetAPI2( "CRC16Init", (RTS_VOID_FCTPTR *)&pfCRC16Init, (fl), 0, 0)
	#define CAL_CRC16Init  pfCRC16Init
	#define CHK_CRC16Init  (pfCRC16Init != NULL)
	#define EXP_CRC16Init   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC16Init", (RTS_UINTPTR)CRC16Init, 0, 0) 
#endif


/**
 * <description>
 *   Update the CRC with a block of data. Before the first call you have to initialize the
 *   CRC by calling CRC16Init.
 * </description>
 * <param name="usCRC" type="IN">
 *   The previous value of the crc as returned by the last call to CRC16Init or 
 *   CRC16Update.
 * </param>
 * <param name="pData" type="IN">
 *   Points at the data which should be added to the crc.
 * </param>
 * <param name="ulSize" type="IN">
 *   The number of bytes in pData.
 * </param>
 * <result>
 *   Returns the updated crc.
 * </result>
 */
RTS_UI16 CDECL CRC16Update(RTS_UI16 usCRC, const unsigned char * pData, RTS_SIZE ulSize);
typedef RTS_UI16 (CDECL * PFCRC16UPDATE) (RTS_UI16 usCRC, const unsigned char * pData, RTS_SIZE ulSize);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC16UPDATE_NOTIMPLEMENTED)
	#define USE_CRC16Update
	#define EXT_CRC16Update
	#define GET_CRC16Update(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CRC16Update(p0,p1,p2) (RTS_UI16)ERR_NOTIMPLEMENTED
	#define CHK_CRC16Update  FALSE
	#define EXP_CRC16Update  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CRC16Update
	#define EXT_CRC16Update
	#define GET_CRC16Update(fl)  CAL_CMGETAPI( "CRC16Update" ) 
	#define CAL_CRC16Update  CRC16Update
	#define CHK_CRC16Update  TRUE
	#define EXP_CRC16Update  CAL_CMEXPAPI( "CRC16Update" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_CRC16Update
	#define EXT_CRC16Update
	#define GET_CRC16Update(fl)  CAL_CMGETAPI( "CRC16Update" ) 
	#define CAL_CRC16Update  CRC16Update
	#define CHK_CRC16Update  TRUE
	#define EXP_CRC16Update  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC16Update", (RTS_UINTPTR)CRC16Update, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumCRC16Update
	#define EXT_CmpChecksumCRC16Update
	#define GET_CmpChecksumCRC16Update  ERR_OK
	#define CAL_CmpChecksumCRC16Update  CRC16Update
	#define CHK_CmpChecksumCRC16Update  TRUE
	#define EXP_CmpChecksumCRC16Update  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CRC16Update
	#define EXT_CRC16Update
	#define GET_CRC16Update(fl)  CAL_CMGETAPI( "CRC16Update" ) 
	#define CAL_CRC16Update  CRC16Update
	#define CHK_CRC16Update  TRUE
	#define EXP_CRC16Update  CAL_CMEXPAPI( "CRC16Update" ) 
#else /* DYNAMIC_LINK */
	#define USE_CRC16Update  PFCRC16UPDATE pfCRC16Update;
	#define EXT_CRC16Update  extern PFCRC16UPDATE pfCRC16Update;
	#define GET_CRC16Update(fl)  s_pfCMGetAPI2( "CRC16Update", (RTS_VOID_FCTPTR *)&pfCRC16Update, (fl), 0, 0)
	#define CAL_CRC16Update  pfCRC16Update
	#define CHK_CRC16Update  (pfCRC16Update != NULL)
	#define EXP_CRC16Update   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC16Update", (RTS_UINTPTR)CRC16Update, 0, 0) 
#endif


/**
 * <description>
 *   For the CRC to be valid it has to be finished after it is updated with all data.
 *   Use this as the last step during calculating your CRC.
 * </description>
 * <param name="usCRC" type="IN">
 *  The current value of the crc to be finished.
 * </param>
 * <result>
 *	 The checksum over all data passed in via CRC16Update.
 * </result>
 */
RTS_UI16 CDECL CRC16Finish(RTS_UI16 usCRC);
typedef RTS_UI16 (CDECL * PFCRC16FINISH) (RTS_UI16 usCRC);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC16FINISH_NOTIMPLEMENTED)
	#define USE_CRC16Finish
	#define EXT_CRC16Finish
	#define GET_CRC16Finish(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CRC16Finish(p0) (RTS_UI16)ERR_NOTIMPLEMENTED
	#define CHK_CRC16Finish  FALSE
	#define EXP_CRC16Finish  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CRC16Finish
	#define EXT_CRC16Finish
	#define GET_CRC16Finish(fl)  CAL_CMGETAPI( "CRC16Finish" ) 
	#define CAL_CRC16Finish  CRC16Finish
	#define CHK_CRC16Finish  TRUE
	#define EXP_CRC16Finish  CAL_CMEXPAPI( "CRC16Finish" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_CRC16Finish
	#define EXT_CRC16Finish
	#define GET_CRC16Finish(fl)  CAL_CMGETAPI( "CRC16Finish" ) 
	#define CAL_CRC16Finish  CRC16Finish
	#define CHK_CRC16Finish  TRUE
	#define EXP_CRC16Finish  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC16Finish", (RTS_UINTPTR)CRC16Finish, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumCRC16Finish
	#define EXT_CmpChecksumCRC16Finish
	#define GET_CmpChecksumCRC16Finish  ERR_OK
	#define CAL_CmpChecksumCRC16Finish  CRC16Finish
	#define CHK_CmpChecksumCRC16Finish  TRUE
	#define EXP_CmpChecksumCRC16Finish  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CRC16Finish
	#define EXT_CRC16Finish
	#define GET_CRC16Finish(fl)  CAL_CMGETAPI( "CRC16Finish" ) 
	#define CAL_CRC16Finish  CRC16Finish
	#define CHK_CRC16Finish  TRUE
	#define EXP_CRC16Finish  CAL_CMEXPAPI( "CRC16Finish" ) 
#else /* DYNAMIC_LINK */
	#define USE_CRC16Finish  PFCRC16FINISH pfCRC16Finish;
	#define EXT_CRC16Finish  extern PFCRC16FINISH pfCRC16Finish;
	#define GET_CRC16Finish(fl)  s_pfCMGetAPI2( "CRC16Finish", (RTS_VOID_FCTPTR *)&pfCRC16Finish, (fl), 0, 0)
	#define CAL_CRC16Finish  pfCRC16Finish
	#define CHK_CRC16Finish  (pfCRC16Finish != NULL)
	#define EXP_CRC16Finish   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC16Finish", (RTS_UINTPTR)CRC16Finish, 0, 0) 
#endif


/**
 * <description>Implementation of a initial 32-Bit CRC. Initial value is 0xFFFFFFFF.</description>
 * <parampseudo name="InitValue" type="IN" range="[INIT_VAL32]">Define that sets the Initial Value</parampseudo>
 * <result>Returns the initial CRC value.</result>
 */
RTS_UI32 CDECL CRC32Init(void);
typedef RTS_UI32 (CDECL * PFCRC32INIT) (void);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC32INIT_NOTIMPLEMENTED)
	#define USE_CRC32Init
	#define EXT_CRC32Init
	#define GET_CRC32Init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CRC32Init() (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_CRC32Init  FALSE
	#define EXP_CRC32Init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CRC32Init
	#define EXT_CRC32Init
	#define GET_CRC32Init(fl)  CAL_CMGETAPI( "CRC32Init" ) 
	#define CAL_CRC32Init  CRC32Init
	#define CHK_CRC32Init  TRUE
	#define EXP_CRC32Init  CAL_CMEXPAPI( "CRC32Init" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_CRC32Init
	#define EXT_CRC32Init
	#define GET_CRC32Init(fl)  CAL_CMGETAPI( "CRC32Init" ) 
	#define CAL_CRC32Init  CRC32Init
	#define CHK_CRC32Init  TRUE
	#define EXP_CRC32Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC32Init", (RTS_UINTPTR)CRC32Init, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumCRC32Init
	#define EXT_CmpChecksumCRC32Init
	#define GET_CmpChecksumCRC32Init  ERR_OK
	#define CAL_CmpChecksumCRC32Init  CRC32Init
	#define CHK_CmpChecksumCRC32Init  TRUE
	#define EXP_CmpChecksumCRC32Init  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CRC32Init
	#define EXT_CRC32Init
	#define GET_CRC32Init(fl)  CAL_CMGETAPI( "CRC32Init" ) 
	#define CAL_CRC32Init  CRC32Init
	#define CHK_CRC32Init  TRUE
	#define EXP_CRC32Init  CAL_CMEXPAPI( "CRC32Init" ) 
#else /* DYNAMIC_LINK */
	#define USE_CRC32Init  PFCRC32INIT pfCRC32Init;
	#define EXT_CRC32Init  extern PFCRC32INIT pfCRC32Init;
	#define GET_CRC32Init(fl)  s_pfCMGetAPI2( "CRC32Init", (RTS_VOID_FCTPTR *)&pfCRC32Init, (fl), 0, 0)
	#define CAL_CRC32Init  pfCRC32Init
	#define CHK_CRC32Init  (pfCRC32Init != NULL)
	#define EXP_CRC32Init   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC32Init", (RTS_UINTPTR)CRC32Init, 0, 0) 
#endif


/**
 * 
 * <description>
 * <p>Obsolete: Use CRC32Update2 instead!</p>
 * <p>Update the CRC with a block of data. Before the first call you have to initialize the
 *   crc by calling CRC32Init. Must only be used, if the CRC is calculated in one step and not
 *   using several calls of CRC32Update for adding data to the CRC.</p>
 *	 <p>ATTENTION: You have to finish the CRC with the function CRC32Finish()!</p>
 * </description>
 * <param name="ulCRC" type="IN">
 *   The previous value of the crc as returned by the last call to CRC32Init.
 * </param>
 * <param name="pData" type="IN">
 *   Points at the data for which the CRC should be calculated.
 * </param>
 * <param name="ulSize" type="IN">
 *   The number of bytes in pData.
 * </param>
 * <result>
 *   Returns the updated CRC.
 * </result>
 */
RTS_UI32 CDECL CRC32Update(RTS_UI32 ulCRC, const unsigned char *pData, RTS_SIZE ulSize);
typedef RTS_UI32 (CDECL * PFCRC32UPDATE) (RTS_UI32 ulCRC, const unsigned char *pData, RTS_SIZE ulSize);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC32UPDATE_NOTIMPLEMENTED)
	#define USE_CRC32Update
	#define EXT_CRC32Update
	#define GET_CRC32Update(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CRC32Update(p0,p1,p2) (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_CRC32Update  FALSE
	#define EXP_CRC32Update  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CRC32Update
	#define EXT_CRC32Update
	#define GET_CRC32Update(fl)  CAL_CMGETAPI( "CRC32Update" ) 
	#define CAL_CRC32Update  CRC32Update
	#define CHK_CRC32Update  TRUE
	#define EXP_CRC32Update  CAL_CMEXPAPI( "CRC32Update" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_CRC32Update
	#define EXT_CRC32Update
	#define GET_CRC32Update(fl)  CAL_CMGETAPI( "CRC32Update" ) 
	#define CAL_CRC32Update  CRC32Update
	#define CHK_CRC32Update  TRUE
	#define EXP_CRC32Update  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC32Update", (RTS_UINTPTR)CRC32Update, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumCRC32Update
	#define EXT_CmpChecksumCRC32Update
	#define GET_CmpChecksumCRC32Update  ERR_OK
	#define CAL_CmpChecksumCRC32Update  CRC32Update
	#define CHK_CmpChecksumCRC32Update  TRUE
	#define EXP_CmpChecksumCRC32Update  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CRC32Update
	#define EXT_CRC32Update
	#define GET_CRC32Update(fl)  CAL_CMGETAPI( "CRC32Update" ) 
	#define CAL_CRC32Update  CRC32Update
	#define CHK_CRC32Update  TRUE
	#define EXP_CRC32Update  CAL_CMEXPAPI( "CRC32Update" ) 
#else /* DYNAMIC_LINK */
	#define USE_CRC32Update  PFCRC32UPDATE pfCRC32Update;
	#define EXT_CRC32Update  extern PFCRC32UPDATE pfCRC32Update;
	#define GET_CRC32Update(fl)  s_pfCMGetAPI2( "CRC32Update", (RTS_VOID_FCTPTR *)&pfCRC32Update, (fl), 0, 0)
	#define CAL_CRC32Update  pfCRC32Update
	#define CHK_CRC32Update  (pfCRC32Update != NULL)
	#define EXP_CRC32Update   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC32Update", (RTS_UINTPTR)CRC32Update, 0, 0) 
#endif


/**
 * <description>
 * <p>Obsolete: Use CRC32Finish2 instead!</p>
 * <p>For the CRC to be valid it has to be finished after it is updated with all data.
 *   Use this as the last step during calculating your CRC.</p>
 *   <p>In opposite to the other CRC algorithms, the resulting CRC is swapped to IntelByteOrder.</p>
 * </description>
 * <param name="ulCRC" type="IN">
 *  The current value of the CRC to be finished.
 * </param>
 * <result>
 *	 The checksum over all data passed in via CRC32Update.
 * </result>
 */
RTS_UI32 CDECL CRC32Finish(RTS_UI32 ulCRC);
typedef RTS_UI32 (CDECL * PFCRC32FINISH) (RTS_UI32 ulCRC);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC32FINISH_NOTIMPLEMENTED)
	#define USE_CRC32Finish
	#define EXT_CRC32Finish
	#define GET_CRC32Finish(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CRC32Finish(p0) (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_CRC32Finish  FALSE
	#define EXP_CRC32Finish  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CRC32Finish
	#define EXT_CRC32Finish
	#define GET_CRC32Finish(fl)  CAL_CMGETAPI( "CRC32Finish" ) 
	#define CAL_CRC32Finish  CRC32Finish
	#define CHK_CRC32Finish  TRUE
	#define EXP_CRC32Finish  CAL_CMEXPAPI( "CRC32Finish" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_CRC32Finish
	#define EXT_CRC32Finish
	#define GET_CRC32Finish(fl)  CAL_CMGETAPI( "CRC32Finish" ) 
	#define CAL_CRC32Finish  CRC32Finish
	#define CHK_CRC32Finish  TRUE
	#define EXP_CRC32Finish  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC32Finish", (RTS_UINTPTR)CRC32Finish, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumCRC32Finish
	#define EXT_CmpChecksumCRC32Finish
	#define GET_CmpChecksumCRC32Finish  ERR_OK
	#define CAL_CmpChecksumCRC32Finish  CRC32Finish
	#define CHK_CmpChecksumCRC32Finish  TRUE
	#define EXP_CmpChecksumCRC32Finish  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CRC32Finish
	#define EXT_CRC32Finish
	#define GET_CRC32Finish(fl)  CAL_CMGETAPI( "CRC32Finish" ) 
	#define CAL_CRC32Finish  CRC32Finish
	#define CHK_CRC32Finish  TRUE
	#define EXP_CRC32Finish  CAL_CMEXPAPI( "CRC32Finish" ) 
#else /* DYNAMIC_LINK */
	#define USE_CRC32Finish  PFCRC32FINISH pfCRC32Finish;
	#define EXT_CRC32Finish  extern PFCRC32FINISH pfCRC32Finish;
	#define GET_CRC32Finish(fl)  s_pfCMGetAPI2( "CRC32Finish", (RTS_VOID_FCTPTR *)&pfCRC32Finish, (fl), 0, 0)
	#define CAL_CRC32Finish  pfCRC32Finish
	#define CHK_CRC32Finish  (pfCRC32Finish != NULL)
	#define EXP_CRC32Finish   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC32Finish", (RTS_UINTPTR)CRC32Finish, 0, 0) 
#endif


/**
 * <description>
 *   Update the CRC with a block of data. Before the first call you have to initialize the
 *   CRC by calling CRC32Init.
 *	 ATTENTION: You have to finish the CRC with the function CRC32Finish2()!
 * </description>
 * <param name="ulCRC" type="IN" range="[0,VALID_CRC32]">
 *   The previous value of the CRC as returned by the last call to CRC32Init or 
 *   CRC32Update2.
 * </param>
 * <param name="pData" type="IN" range="[VALID_DATA_POINTER]">
 *   Points at the data which should be added to the CRC.
 * </param>
 * <param name="ulSize" type="IN" range="[0,VALID_CRC32SIZE]">
 *   The number of bytes in pData.
 * </param>
 * <result>
 *   Returns the updated CRC.
 * </result>
 */
RTS_UI32 CDECL CRC32Update2(RTS_UI32 ulCRC, const unsigned char *pData, RTS_SIZE ulSize);
typedef RTS_UI32 (CDECL * PFCRC32UPDATE2) (RTS_UI32 ulCRC, const unsigned char *pData, RTS_SIZE ulSize);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC32UPDATE2_NOTIMPLEMENTED)
	#define USE_CRC32Update2
	#define EXT_CRC32Update2
	#define GET_CRC32Update2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CRC32Update2(p0,p1,p2) (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_CRC32Update2  FALSE
	#define EXP_CRC32Update2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CRC32Update2
	#define EXT_CRC32Update2
	#define GET_CRC32Update2(fl)  CAL_CMGETAPI( "CRC32Update2" ) 
	#define CAL_CRC32Update2  CRC32Update2
	#define CHK_CRC32Update2  TRUE
	#define EXP_CRC32Update2  CAL_CMEXPAPI( "CRC32Update2" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_CRC32Update2
	#define EXT_CRC32Update2
	#define GET_CRC32Update2(fl)  CAL_CMGETAPI( "CRC32Update2" ) 
	#define CAL_CRC32Update2  CRC32Update2
	#define CHK_CRC32Update2  TRUE
	#define EXP_CRC32Update2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC32Update2", (RTS_UINTPTR)CRC32Update2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumCRC32Update2
	#define EXT_CmpChecksumCRC32Update2
	#define GET_CmpChecksumCRC32Update2  ERR_OK
	#define CAL_CmpChecksumCRC32Update2  CRC32Update2
	#define CHK_CmpChecksumCRC32Update2  TRUE
	#define EXP_CmpChecksumCRC32Update2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CRC32Update2
	#define EXT_CRC32Update2
	#define GET_CRC32Update2(fl)  CAL_CMGETAPI( "CRC32Update2" ) 
	#define CAL_CRC32Update2  CRC32Update2
	#define CHK_CRC32Update2  TRUE
	#define EXP_CRC32Update2  CAL_CMEXPAPI( "CRC32Update2" ) 
#else /* DYNAMIC_LINK */
	#define USE_CRC32Update2  PFCRC32UPDATE2 pfCRC32Update2;
	#define EXT_CRC32Update2  extern PFCRC32UPDATE2 pfCRC32Update2;
	#define GET_CRC32Update2(fl)  s_pfCMGetAPI2( "CRC32Update2", (RTS_VOID_FCTPTR *)&pfCRC32Update2, (fl), 0, 0)
	#define CAL_CRC32Update2  pfCRC32Update2
	#define CHK_CRC32Update2  (pfCRC32Update2 != NULL)
	#define EXP_CRC32Update2   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC32Update2", (RTS_UINTPTR)CRC32Update2, 0, 0) 
#endif


/**
 * <description>
 *   For the CRC to be valid it has to be finished after it is updated with all data.
 *   Use this as the last step during calculating your CRC.
 * </description>
 * <param name="ulCRC" type="IN" range="[0,VALID_CRC32]">
 *  The current value of the CRC to be finished.
 * </param>
 * <result>
 *	 The checksum over all data passed in via CRC32Update.
 * </result>
 */
RTS_UI32 CDECL CRC32Finish2(RTS_UI32 ulCRC);
typedef RTS_UI32 (CDECL * PFCRC32FINISH2) (RTS_UI32 ulCRC);
#if defined(CMPCHECKSUM_NOTIMPLEMENTED) || defined(CRC32FINISH2_NOTIMPLEMENTED)
	#define USE_CRC32Finish2
	#define EXT_CRC32Finish2
	#define GET_CRC32Finish2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CRC32Finish2(p0) (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_CRC32Finish2  FALSE
	#define EXP_CRC32Finish2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CRC32Finish2
	#define EXT_CRC32Finish2
	#define GET_CRC32Finish2(fl)  CAL_CMGETAPI( "CRC32Finish2" ) 
	#define CAL_CRC32Finish2  CRC32Finish2
	#define CHK_CRC32Finish2  TRUE
	#define EXP_CRC32Finish2  CAL_CMEXPAPI( "CRC32Finish2" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHECKSUM_EXTERNAL)
	#define USE_CRC32Finish2
	#define EXT_CRC32Finish2
	#define GET_CRC32Finish2(fl)  CAL_CMGETAPI( "CRC32Finish2" ) 
	#define CAL_CRC32Finish2  CRC32Finish2
	#define CHK_CRC32Finish2  TRUE
	#define EXP_CRC32Finish2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC32Finish2", (RTS_UINTPTR)CRC32Finish2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChecksumCRC32Finish2
	#define EXT_CmpChecksumCRC32Finish2
	#define GET_CmpChecksumCRC32Finish2  ERR_OK
	#define CAL_CmpChecksumCRC32Finish2  CRC32Finish2
	#define CHK_CmpChecksumCRC32Finish2  TRUE
	#define EXP_CmpChecksumCRC32Finish2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CRC32Finish2
	#define EXT_CRC32Finish2
	#define GET_CRC32Finish2(fl)  CAL_CMGETAPI( "CRC32Finish2" ) 
	#define CAL_CRC32Finish2  CRC32Finish2
	#define CHK_CRC32Finish2  TRUE
	#define EXP_CRC32Finish2  CAL_CMEXPAPI( "CRC32Finish2" ) 
#else /* DYNAMIC_LINK */
	#define USE_CRC32Finish2  PFCRC32FINISH2 pfCRC32Finish2;
	#define EXT_CRC32Finish2  extern PFCRC32FINISH2 pfCRC32Finish2;
	#define GET_CRC32Finish2(fl)  s_pfCMGetAPI2( "CRC32Finish2", (RTS_VOID_FCTPTR *)&pfCRC32Finish2, (fl), 0, 0)
	#define CAL_CRC32Finish2  pfCRC32Finish2
	#define CHK_CRC32Finish2  (pfCRC32Finish2 != NULL)
	#define EXP_CRC32Finish2   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CRC32Finish2", (RTS_UINTPTR)CRC32Finish2, 0, 0) 
#endif


#ifdef __cplusplus
}
#endif




typedef struct
{
	IBase_C *pBase;
} ICmpChecksum_C;

#ifdef CPLUSPLUS
class ICmpChecksum : public IBase
{
	public:
};
	#ifndef ITF_CmpChecksum
		#define ITF_CmpChecksum static ICmpChecksum *pICmpChecksum = NULL;
	#endif
	#define EXTITF_CmpChecksum
#else	/*CPLUSPLUS*/
	typedef ICmpChecksum_C		ICmpChecksum;
	#ifndef ITF_CmpChecksum
		#define ITF_CmpChecksum
	#endif
	#define EXTITF_CmpChecksum
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCHECKSUMITF_H_*/
