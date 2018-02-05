 /**
 * <interfacename>SysFileStream23</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _SYSFILESTREAMITF_H_
#define _SYSFILESTREAMITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>sysfilestreamclearerr</description>
 */
typedef struct tagsysfilestreamclearerr_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamClearerr;	/* VAR_OUTPUT */
} sysfilestreamclearerr_struct;

void CDECL CDECL_EXT sysfilestreamclearerr(sysfilestreamclearerr_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMCLEARERR_IEC) (sysfilestreamclearerr_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMCLEARERR_NOTIMPLEMENTED)
	#define USE_sysfilestreamclearerr
	#define EXT_sysfilestreamclearerr
	#define GET_sysfilestreamclearerr(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamclearerr(p0) 
	#define CHK_sysfilestreamclearerr  FALSE
	#define EXP_sysfilestreamclearerr  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamclearerr
	#define EXT_sysfilestreamclearerr
	#define GET_sysfilestreamclearerr(fl)  CAL_CMGETAPI( "sysfilestreamclearerr" ) 
	#define CAL_sysfilestreamclearerr  sysfilestreamclearerr
	#define CHK_sysfilestreamclearerr  TRUE
	#define EXP_sysfilestreamclearerr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamclearerr", (RTS_UINTPTR)sysfilestreamclearerr, 1, RTSITF_GET_SIGNATURE(0, 0x1B38E038), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamclearerr
	#define EXT_sysfilestreamclearerr
	#define GET_sysfilestreamclearerr(fl)  CAL_CMGETAPI( "sysfilestreamclearerr" ) 
	#define CAL_sysfilestreamclearerr  sysfilestreamclearerr
	#define CHK_sysfilestreamclearerr  TRUE
	#define EXP_sysfilestreamclearerr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamclearerr", (RTS_UINTPTR)sysfilestreamclearerr, 1, RTSITF_GET_SIGNATURE(0, 0x1B38E038), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamclearerr
	#define EXT_SysFileStreamsysfilestreamclearerr
	#define GET_SysFileStreamsysfilestreamclearerr  ERR_OK
	#define CAL_SysFileStreamsysfilestreamclearerr  sysfilestreamclearerr
	#define CHK_SysFileStreamsysfilestreamclearerr  TRUE
	#define EXP_SysFileStreamsysfilestreamclearerr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamclearerr", (RTS_UINTPTR)sysfilestreamclearerr, 1, RTSITF_GET_SIGNATURE(0, 0x1B38E038), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamclearerr
	#define EXT_sysfilestreamclearerr
	#define GET_sysfilestreamclearerr(fl)  CAL_CMGETAPI( "sysfilestreamclearerr" ) 
	#define CAL_sysfilestreamclearerr  sysfilestreamclearerr
	#define CHK_sysfilestreamclearerr  TRUE
	#define EXP_sysfilestreamclearerr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamclearerr", (RTS_UINTPTR)sysfilestreamclearerr, 1, RTSITF_GET_SIGNATURE(0, 0x1B38E038), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamclearerr  PFSYSFILESTREAMCLEARERR_IEC pfsysfilestreamclearerr;
	#define EXT_sysfilestreamclearerr  extern PFSYSFILESTREAMCLEARERR_IEC pfsysfilestreamclearerr;
	#define GET_sysfilestreamclearerr(fl)  s_pfCMGetAPI2( "sysfilestreamclearerr", (RTS_VOID_FCTPTR *)&pfsysfilestreamclearerr, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1B38E038), 0x03050000)
	#define CAL_sysfilestreamclearerr  pfsysfilestreamclearerr
	#define CHK_sysfilestreamclearerr  (pfsysfilestreamclearerr != NULL)
	#define EXP_sysfilestreamclearerr   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamclearerr", (RTS_UINTPTR)sysfilestreamclearerr, 1, RTSITF_GET_SIGNATURE(0, 0x1B38E038), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfclose</description>
 */
typedef struct tagsysfilestreamfclose_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFClose;	/* VAR_OUTPUT */
} sysfilestreamfclose_struct;

void CDECL CDECL_EXT sysfilestreamfclose(sysfilestreamfclose_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFCLOSE_IEC) (sysfilestreamfclose_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFCLOSE_NOTIMPLEMENTED)
	#define USE_sysfilestreamfclose
	#define EXT_sysfilestreamfclose
	#define GET_sysfilestreamfclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfclose(p0) 
	#define CHK_sysfilestreamfclose  FALSE
	#define EXP_sysfilestreamfclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfclose
	#define EXT_sysfilestreamfclose
	#define GET_sysfilestreamfclose(fl)  CAL_CMGETAPI( "sysfilestreamfclose" ) 
	#define CAL_sysfilestreamfclose  sysfilestreamfclose
	#define CHK_sysfilestreamfclose  TRUE
	#define EXP_sysfilestreamfclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfclose", (RTS_UINTPTR)sysfilestreamfclose, 1, RTSITF_GET_SIGNATURE(0, 0x01C196F3), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfclose
	#define EXT_sysfilestreamfclose
	#define GET_sysfilestreamfclose(fl)  CAL_CMGETAPI( "sysfilestreamfclose" ) 
	#define CAL_sysfilestreamfclose  sysfilestreamfclose
	#define CHK_sysfilestreamfclose  TRUE
	#define EXP_sysfilestreamfclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfclose", (RTS_UINTPTR)sysfilestreamfclose, 1, RTSITF_GET_SIGNATURE(0, 0x01C196F3), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfclose
	#define EXT_SysFileStreamsysfilestreamfclose
	#define GET_SysFileStreamsysfilestreamfclose  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfclose  sysfilestreamfclose
	#define CHK_SysFileStreamsysfilestreamfclose  TRUE
	#define EXP_SysFileStreamsysfilestreamfclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfclose", (RTS_UINTPTR)sysfilestreamfclose, 1, RTSITF_GET_SIGNATURE(0, 0x01C196F3), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfclose
	#define EXT_sysfilestreamfclose
	#define GET_sysfilestreamfclose(fl)  CAL_CMGETAPI( "sysfilestreamfclose" ) 
	#define CAL_sysfilestreamfclose  sysfilestreamfclose
	#define CHK_sysfilestreamfclose  TRUE
	#define EXP_sysfilestreamfclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfclose", (RTS_UINTPTR)sysfilestreamfclose, 1, RTSITF_GET_SIGNATURE(0, 0x01C196F3), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfclose  PFSYSFILESTREAMFCLOSE_IEC pfsysfilestreamfclose;
	#define EXT_sysfilestreamfclose  extern PFSYSFILESTREAMFCLOSE_IEC pfsysfilestreamfclose;
	#define GET_sysfilestreamfclose(fl)  s_pfCMGetAPI2( "sysfilestreamfclose", (RTS_VOID_FCTPTR *)&pfsysfilestreamfclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x01C196F3), 0x03050000)
	#define CAL_sysfilestreamfclose  pfsysfilestreamfclose
	#define CHK_sysfilestreamfclose  (pfsysfilestreamfclose != NULL)
	#define EXP_sysfilestreamfclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfclose", (RTS_UINTPTR)sysfilestreamfclose, 1, RTSITF_GET_SIGNATURE(0, 0x01C196F3), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfeof</description>
 */
typedef struct tagsysfilestreamfeof_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFEOF;		/* VAR_OUTPUT */
} sysfilestreamfeof_struct;

void CDECL CDECL_EXT sysfilestreamfeof(sysfilestreamfeof_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFEOF_IEC) (sysfilestreamfeof_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFEOF_NOTIMPLEMENTED)
	#define USE_sysfilestreamfeof
	#define EXT_sysfilestreamfeof
	#define GET_sysfilestreamfeof(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfeof(p0) 
	#define CHK_sysfilestreamfeof  FALSE
	#define EXP_sysfilestreamfeof  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfeof
	#define EXT_sysfilestreamfeof
	#define GET_sysfilestreamfeof(fl)  CAL_CMGETAPI( "sysfilestreamfeof" ) 
	#define CAL_sysfilestreamfeof  sysfilestreamfeof
	#define CHK_sysfilestreamfeof  TRUE
	#define EXP_sysfilestreamfeof  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfeof", (RTS_UINTPTR)sysfilestreamfeof, 1, RTSITF_GET_SIGNATURE(0, 0xCCFD6E4A), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfeof
	#define EXT_sysfilestreamfeof
	#define GET_sysfilestreamfeof(fl)  CAL_CMGETAPI( "sysfilestreamfeof" ) 
	#define CAL_sysfilestreamfeof  sysfilestreamfeof
	#define CHK_sysfilestreamfeof  TRUE
	#define EXP_sysfilestreamfeof  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfeof", (RTS_UINTPTR)sysfilestreamfeof, 1, RTSITF_GET_SIGNATURE(0, 0xCCFD6E4A), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfeof
	#define EXT_SysFileStreamsysfilestreamfeof
	#define GET_SysFileStreamsysfilestreamfeof  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfeof  sysfilestreamfeof
	#define CHK_SysFileStreamsysfilestreamfeof  TRUE
	#define EXP_SysFileStreamsysfilestreamfeof  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfeof", (RTS_UINTPTR)sysfilestreamfeof, 1, RTSITF_GET_SIGNATURE(0, 0xCCFD6E4A), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfeof
	#define EXT_sysfilestreamfeof
	#define GET_sysfilestreamfeof(fl)  CAL_CMGETAPI( "sysfilestreamfeof" ) 
	#define CAL_sysfilestreamfeof  sysfilestreamfeof
	#define CHK_sysfilestreamfeof  TRUE
	#define EXP_sysfilestreamfeof  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfeof", (RTS_UINTPTR)sysfilestreamfeof, 1, RTSITF_GET_SIGNATURE(0, 0xCCFD6E4A), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfeof  PFSYSFILESTREAMFEOF_IEC pfsysfilestreamfeof;
	#define EXT_sysfilestreamfeof  extern PFSYSFILESTREAMFEOF_IEC pfsysfilestreamfeof;
	#define GET_sysfilestreamfeof(fl)  s_pfCMGetAPI2( "sysfilestreamfeof", (RTS_VOID_FCTPTR *)&pfsysfilestreamfeof, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCCFD6E4A), 0x03050000)
	#define CAL_sysfilestreamfeof  pfsysfilestreamfeof
	#define CHK_sysfilestreamfeof  (pfsysfilestreamfeof != NULL)
	#define EXP_sysfilestreamfeof   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfeof", (RTS_UINTPTR)sysfilestreamfeof, 1, RTSITF_GET_SIGNATURE(0, 0xCCFD6E4A), 0x03050000) 
#endif


/**
 * <description>sysfilestreamferror</description>
 */
typedef struct tagsysfilestreamferror_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFError;	/* VAR_OUTPUT */
} sysfilestreamferror_struct;

void CDECL CDECL_EXT sysfilestreamferror(sysfilestreamferror_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFERROR_IEC) (sysfilestreamferror_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFERROR_NOTIMPLEMENTED)
	#define USE_sysfilestreamferror
	#define EXT_sysfilestreamferror
	#define GET_sysfilestreamferror(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamferror(p0) 
	#define CHK_sysfilestreamferror  FALSE
	#define EXP_sysfilestreamferror  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamferror
	#define EXT_sysfilestreamferror
	#define GET_sysfilestreamferror(fl)  CAL_CMGETAPI( "sysfilestreamferror" ) 
	#define CAL_sysfilestreamferror  sysfilestreamferror
	#define CHK_sysfilestreamferror  TRUE
	#define EXP_sysfilestreamferror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamferror", (RTS_UINTPTR)sysfilestreamferror, 1, RTSITF_GET_SIGNATURE(0, 0x7C8AC3DB), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamferror
	#define EXT_sysfilestreamferror
	#define GET_sysfilestreamferror(fl)  CAL_CMGETAPI( "sysfilestreamferror" ) 
	#define CAL_sysfilestreamferror  sysfilestreamferror
	#define CHK_sysfilestreamferror  TRUE
	#define EXP_sysfilestreamferror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamferror", (RTS_UINTPTR)sysfilestreamferror, 1, RTSITF_GET_SIGNATURE(0, 0x7C8AC3DB), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamferror
	#define EXT_SysFileStreamsysfilestreamferror
	#define GET_SysFileStreamsysfilestreamferror  ERR_OK
	#define CAL_SysFileStreamsysfilestreamferror  sysfilestreamferror
	#define CHK_SysFileStreamsysfilestreamferror  TRUE
	#define EXP_SysFileStreamsysfilestreamferror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamferror", (RTS_UINTPTR)sysfilestreamferror, 1, RTSITF_GET_SIGNATURE(0, 0x7C8AC3DB), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamferror
	#define EXT_sysfilestreamferror
	#define GET_sysfilestreamferror(fl)  CAL_CMGETAPI( "sysfilestreamferror" ) 
	#define CAL_sysfilestreamferror  sysfilestreamferror
	#define CHK_sysfilestreamferror  TRUE
	#define EXP_sysfilestreamferror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamferror", (RTS_UINTPTR)sysfilestreamferror, 1, RTSITF_GET_SIGNATURE(0, 0x7C8AC3DB), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamferror  PFSYSFILESTREAMFERROR_IEC pfsysfilestreamferror;
	#define EXT_sysfilestreamferror  extern PFSYSFILESTREAMFERROR_IEC pfsysfilestreamferror;
	#define GET_sysfilestreamferror(fl)  s_pfCMGetAPI2( "sysfilestreamferror", (RTS_VOID_FCTPTR *)&pfsysfilestreamferror, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7C8AC3DB), 0x03050000)
	#define CAL_sysfilestreamferror  pfsysfilestreamferror
	#define CHK_sysfilestreamferror  (pfsysfilestreamferror != NULL)
	#define EXP_sysfilestreamferror   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamferror", (RTS_UINTPTR)sysfilestreamferror, 1, RTSITF_GET_SIGNATURE(0, 0x7C8AC3DB), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfflush</description>
 */
typedef struct tagsysfilestreamfflush_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFFlush;	/* VAR_OUTPUT */
} sysfilestreamfflush_struct;

void CDECL CDECL_EXT sysfilestreamfflush(sysfilestreamfflush_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFFLUSH_IEC) (sysfilestreamfflush_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFFLUSH_NOTIMPLEMENTED)
	#define USE_sysfilestreamfflush
	#define EXT_sysfilestreamfflush
	#define GET_sysfilestreamfflush(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfflush(p0) 
	#define CHK_sysfilestreamfflush  FALSE
	#define EXP_sysfilestreamfflush  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfflush
	#define EXT_sysfilestreamfflush
	#define GET_sysfilestreamfflush(fl)  CAL_CMGETAPI( "sysfilestreamfflush" ) 
	#define CAL_sysfilestreamfflush  sysfilestreamfflush
	#define CHK_sysfilestreamfflush  TRUE
	#define EXP_sysfilestreamfflush  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfflush", (RTS_UINTPTR)sysfilestreamfflush, 1, RTSITF_GET_SIGNATURE(0, 0x4FE8ECB6), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfflush
	#define EXT_sysfilestreamfflush
	#define GET_sysfilestreamfflush(fl)  CAL_CMGETAPI( "sysfilestreamfflush" ) 
	#define CAL_sysfilestreamfflush  sysfilestreamfflush
	#define CHK_sysfilestreamfflush  TRUE
	#define EXP_sysfilestreamfflush  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfflush", (RTS_UINTPTR)sysfilestreamfflush, 1, RTSITF_GET_SIGNATURE(0, 0x4FE8ECB6), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfflush
	#define EXT_SysFileStreamsysfilestreamfflush
	#define GET_SysFileStreamsysfilestreamfflush  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfflush  sysfilestreamfflush
	#define CHK_SysFileStreamsysfilestreamfflush  TRUE
	#define EXP_SysFileStreamsysfilestreamfflush  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfflush", (RTS_UINTPTR)sysfilestreamfflush, 1, RTSITF_GET_SIGNATURE(0, 0x4FE8ECB6), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfflush
	#define EXT_sysfilestreamfflush
	#define GET_sysfilestreamfflush(fl)  CAL_CMGETAPI( "sysfilestreamfflush" ) 
	#define CAL_sysfilestreamfflush  sysfilestreamfflush
	#define CHK_sysfilestreamfflush  TRUE
	#define EXP_sysfilestreamfflush  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfflush", (RTS_UINTPTR)sysfilestreamfflush, 1, RTSITF_GET_SIGNATURE(0, 0x4FE8ECB6), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfflush  PFSYSFILESTREAMFFLUSH_IEC pfsysfilestreamfflush;
	#define EXT_sysfilestreamfflush  extern PFSYSFILESTREAMFFLUSH_IEC pfsysfilestreamfflush;
	#define GET_sysfilestreamfflush(fl)  s_pfCMGetAPI2( "sysfilestreamfflush", (RTS_VOID_FCTPTR *)&pfsysfilestreamfflush, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4FE8ECB6), 0x03050000)
	#define CAL_sysfilestreamfflush  pfsysfilestreamfflush
	#define CHK_sysfilestreamfflush  (pfsysfilestreamfflush != NULL)
	#define EXP_sysfilestreamfflush   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfflush", (RTS_UINTPTR)sysfilestreamfflush, 1, RTSITF_GET_SIGNATURE(0, 0x4FE8ECB6), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfgetc</description>
 */
typedef struct tagsysfilestreamfgetc_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFGetC;	/* VAR_OUTPUT */
} sysfilestreamfgetc_struct;

void CDECL CDECL_EXT sysfilestreamfgetc(sysfilestreamfgetc_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFGETC_IEC) (sysfilestreamfgetc_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFGETC_NOTIMPLEMENTED)
	#define USE_sysfilestreamfgetc
	#define EXT_sysfilestreamfgetc
	#define GET_sysfilestreamfgetc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfgetc(p0) 
	#define CHK_sysfilestreamfgetc  FALSE
	#define EXP_sysfilestreamfgetc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfgetc
	#define EXT_sysfilestreamfgetc
	#define GET_sysfilestreamfgetc(fl)  CAL_CMGETAPI( "sysfilestreamfgetc" ) 
	#define CAL_sysfilestreamfgetc  sysfilestreamfgetc
	#define CHK_sysfilestreamfgetc  TRUE
	#define EXP_sysfilestreamfgetc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgetc", (RTS_UINTPTR)sysfilestreamfgetc, 1, RTSITF_GET_SIGNATURE(0, 0x73628B5F), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfgetc
	#define EXT_sysfilestreamfgetc
	#define GET_sysfilestreamfgetc(fl)  CAL_CMGETAPI( "sysfilestreamfgetc" ) 
	#define CAL_sysfilestreamfgetc  sysfilestreamfgetc
	#define CHK_sysfilestreamfgetc  TRUE
	#define EXP_sysfilestreamfgetc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgetc", (RTS_UINTPTR)sysfilestreamfgetc, 1, RTSITF_GET_SIGNATURE(0, 0x73628B5F), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfgetc
	#define EXT_SysFileStreamsysfilestreamfgetc
	#define GET_SysFileStreamsysfilestreamfgetc  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfgetc  sysfilestreamfgetc
	#define CHK_SysFileStreamsysfilestreamfgetc  TRUE
	#define EXP_SysFileStreamsysfilestreamfgetc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgetc", (RTS_UINTPTR)sysfilestreamfgetc, 1, RTSITF_GET_SIGNATURE(0, 0x73628B5F), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfgetc
	#define EXT_sysfilestreamfgetc
	#define GET_sysfilestreamfgetc(fl)  CAL_CMGETAPI( "sysfilestreamfgetc" ) 
	#define CAL_sysfilestreamfgetc  sysfilestreamfgetc
	#define CHK_sysfilestreamfgetc  TRUE
	#define EXP_sysfilestreamfgetc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgetc", (RTS_UINTPTR)sysfilestreamfgetc, 1, RTSITF_GET_SIGNATURE(0, 0x73628B5F), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfgetc  PFSYSFILESTREAMFGETC_IEC pfsysfilestreamfgetc;
	#define EXT_sysfilestreamfgetc  extern PFSYSFILESTREAMFGETC_IEC pfsysfilestreamfgetc;
	#define GET_sysfilestreamfgetc(fl)  s_pfCMGetAPI2( "sysfilestreamfgetc", (RTS_VOID_FCTPTR *)&pfsysfilestreamfgetc, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x73628B5F), 0x03050000)
	#define CAL_sysfilestreamfgetc  pfsysfilestreamfgetc
	#define CHK_sysfilestreamfgetc  (pfsysfilestreamfgetc != NULL)
	#define EXP_sysfilestreamfgetc   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgetc", (RTS_UINTPTR)sysfilestreamfgetc, 1, RTSITF_GET_SIGNATURE(0, 0x73628B5F), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfgetpos</description>
 */
typedef struct tagsysfilestreamfgetpos_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_BYTE *pFPos;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFGetPos;	/* VAR_OUTPUT */
} sysfilestreamfgetpos_struct;

void CDECL CDECL_EXT sysfilestreamfgetpos(sysfilestreamfgetpos_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFGETPOS_IEC) (sysfilestreamfgetpos_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFGETPOS_NOTIMPLEMENTED)
	#define USE_sysfilestreamfgetpos
	#define EXT_sysfilestreamfgetpos
	#define GET_sysfilestreamfgetpos(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfgetpos(p0) 
	#define CHK_sysfilestreamfgetpos  FALSE
	#define EXP_sysfilestreamfgetpos  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfgetpos
	#define EXT_sysfilestreamfgetpos
	#define GET_sysfilestreamfgetpos(fl)  CAL_CMGETAPI( "sysfilestreamfgetpos" ) 
	#define CAL_sysfilestreamfgetpos  sysfilestreamfgetpos
	#define CHK_sysfilestreamfgetpos  TRUE
	#define EXP_sysfilestreamfgetpos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgetpos", (RTS_UINTPTR)sysfilestreamfgetpos, 1, RTSITF_GET_SIGNATURE(0, 0xBFEA66FC), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfgetpos
	#define EXT_sysfilestreamfgetpos
	#define GET_sysfilestreamfgetpos(fl)  CAL_CMGETAPI( "sysfilestreamfgetpos" ) 
	#define CAL_sysfilestreamfgetpos  sysfilestreamfgetpos
	#define CHK_sysfilestreamfgetpos  TRUE
	#define EXP_sysfilestreamfgetpos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgetpos", (RTS_UINTPTR)sysfilestreamfgetpos, 1, RTSITF_GET_SIGNATURE(0, 0xBFEA66FC), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfgetpos
	#define EXT_SysFileStreamsysfilestreamfgetpos
	#define GET_SysFileStreamsysfilestreamfgetpos  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfgetpos  sysfilestreamfgetpos
	#define CHK_SysFileStreamsysfilestreamfgetpos  TRUE
	#define EXP_SysFileStreamsysfilestreamfgetpos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgetpos", (RTS_UINTPTR)sysfilestreamfgetpos, 1, RTSITF_GET_SIGNATURE(0, 0xBFEA66FC), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfgetpos
	#define EXT_sysfilestreamfgetpos
	#define GET_sysfilestreamfgetpos(fl)  CAL_CMGETAPI( "sysfilestreamfgetpos" ) 
	#define CAL_sysfilestreamfgetpos  sysfilestreamfgetpos
	#define CHK_sysfilestreamfgetpos  TRUE
	#define EXP_sysfilestreamfgetpos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgetpos", (RTS_UINTPTR)sysfilestreamfgetpos, 1, RTSITF_GET_SIGNATURE(0, 0xBFEA66FC), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfgetpos  PFSYSFILESTREAMFGETPOS_IEC pfsysfilestreamfgetpos;
	#define EXT_sysfilestreamfgetpos  extern PFSYSFILESTREAMFGETPOS_IEC pfsysfilestreamfgetpos;
	#define GET_sysfilestreamfgetpos(fl)  s_pfCMGetAPI2( "sysfilestreamfgetpos", (RTS_VOID_FCTPTR *)&pfsysfilestreamfgetpos, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xBFEA66FC), 0x03050000)
	#define CAL_sysfilestreamfgetpos  pfsysfilestreamfgetpos
	#define CHK_sysfilestreamfgetpos  (pfsysfilestreamfgetpos != NULL)
	#define EXP_sysfilestreamfgetpos   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgetpos", (RTS_UINTPTR)sysfilestreamfgetpos, 1, RTSITF_GET_SIGNATURE(0, 0xBFEA66FC), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfgets</description>
 */
typedef struct tagsysfilestreamfgets_struct
{
	RTS_IEC_STRING *str;				/* VAR_INPUT */
	RTS_IEC_DINT n;						/* VAR_INPUT */
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *SysFileStreamFGetS;	/* VAR_OUTPUT */
} sysfilestreamfgets_struct;

void CDECL CDECL_EXT sysfilestreamfgets(sysfilestreamfgets_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFGETS_IEC) (sysfilestreamfgets_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFGETS_NOTIMPLEMENTED)
	#define USE_sysfilestreamfgets
	#define EXT_sysfilestreamfgets
	#define GET_sysfilestreamfgets(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfgets(p0) 
	#define CHK_sysfilestreamfgets  FALSE
	#define EXP_sysfilestreamfgets  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfgets
	#define EXT_sysfilestreamfgets
	#define GET_sysfilestreamfgets(fl)  CAL_CMGETAPI( "sysfilestreamfgets" ) 
	#define CAL_sysfilestreamfgets  sysfilestreamfgets
	#define CHK_sysfilestreamfgets  TRUE
	#define EXP_sysfilestreamfgets  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgets", (RTS_UINTPTR)sysfilestreamfgets, 1, RTSITF_GET_SIGNATURE(0, 0x8E1D114C), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfgets
	#define EXT_sysfilestreamfgets
	#define GET_sysfilestreamfgets(fl)  CAL_CMGETAPI( "sysfilestreamfgets" ) 
	#define CAL_sysfilestreamfgets  sysfilestreamfgets
	#define CHK_sysfilestreamfgets  TRUE
	#define EXP_sysfilestreamfgets  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgets", (RTS_UINTPTR)sysfilestreamfgets, 1, RTSITF_GET_SIGNATURE(0, 0x8E1D114C), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfgets
	#define EXT_SysFileStreamsysfilestreamfgets
	#define GET_SysFileStreamsysfilestreamfgets  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfgets  sysfilestreamfgets
	#define CHK_SysFileStreamsysfilestreamfgets  TRUE
	#define EXP_SysFileStreamsysfilestreamfgets  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgets", (RTS_UINTPTR)sysfilestreamfgets, 1, RTSITF_GET_SIGNATURE(0, 0x8E1D114C), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfgets
	#define EXT_sysfilestreamfgets
	#define GET_sysfilestreamfgets(fl)  CAL_CMGETAPI( "sysfilestreamfgets" ) 
	#define CAL_sysfilestreamfgets  sysfilestreamfgets
	#define CHK_sysfilestreamfgets  TRUE
	#define EXP_sysfilestreamfgets  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgets", (RTS_UINTPTR)sysfilestreamfgets, 1, RTSITF_GET_SIGNATURE(0, 0x8E1D114C), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfgets  PFSYSFILESTREAMFGETS_IEC pfsysfilestreamfgets;
	#define EXT_sysfilestreamfgets  extern PFSYSFILESTREAMFGETS_IEC pfsysfilestreamfgets;
	#define GET_sysfilestreamfgets(fl)  s_pfCMGetAPI2( "sysfilestreamfgets", (RTS_VOID_FCTPTR *)&pfsysfilestreamfgets, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8E1D114C), 0x03050000)
	#define CAL_sysfilestreamfgets  pfsysfilestreamfgets
	#define CHK_sysfilestreamfgets  (pfsysfilestreamfgets != NULL)
	#define EXP_sysfilestreamfgets   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfgets", (RTS_UINTPTR)sysfilestreamfgets, 1, RTSITF_GET_SIGNATURE(0, 0x8E1D114C), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfopen</description>
 */
typedef struct tagsysfilestreamfopen_struct
{
	RTS_IEC_STRING *FileName;			/* VAR_INPUT */
	RTS_IEC_STRING *Mode;				/* VAR_INPUT */
	RTS_IEC_HANDLE SysFileStreamFOpen;	/* VAR_OUTPUT */
} sysfilestreamfopen_struct;

void CDECL CDECL_EXT sysfilestreamfopen(sysfilestreamfopen_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFOPEN_IEC) (sysfilestreamfopen_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFOPEN_NOTIMPLEMENTED)
	#define USE_sysfilestreamfopen
	#define EXT_sysfilestreamfopen
	#define GET_sysfilestreamfopen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfopen(p0) 
	#define CHK_sysfilestreamfopen  FALSE
	#define EXP_sysfilestreamfopen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfopen
	#define EXT_sysfilestreamfopen
	#define GET_sysfilestreamfopen(fl)  CAL_CMGETAPI( "sysfilestreamfopen" ) 
	#define CAL_sysfilestreamfopen  sysfilestreamfopen
	#define CHK_sysfilestreamfopen  TRUE
	#define EXP_sysfilestreamfopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfopen", (RTS_UINTPTR)sysfilestreamfopen, 1, RTSITF_GET_SIGNATURE(0, 0x0AD9CD95), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfopen
	#define EXT_sysfilestreamfopen
	#define GET_sysfilestreamfopen(fl)  CAL_CMGETAPI( "sysfilestreamfopen" ) 
	#define CAL_sysfilestreamfopen  sysfilestreamfopen
	#define CHK_sysfilestreamfopen  TRUE
	#define EXP_sysfilestreamfopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfopen", (RTS_UINTPTR)sysfilestreamfopen, 1, RTSITF_GET_SIGNATURE(0, 0x0AD9CD95), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfopen
	#define EXT_SysFileStreamsysfilestreamfopen
	#define GET_SysFileStreamsysfilestreamfopen  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfopen  sysfilestreamfopen
	#define CHK_SysFileStreamsysfilestreamfopen  TRUE
	#define EXP_SysFileStreamsysfilestreamfopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfopen", (RTS_UINTPTR)sysfilestreamfopen, 1, RTSITF_GET_SIGNATURE(0, 0x0AD9CD95), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfopen
	#define EXT_sysfilestreamfopen
	#define GET_sysfilestreamfopen(fl)  CAL_CMGETAPI( "sysfilestreamfopen" ) 
	#define CAL_sysfilestreamfopen  sysfilestreamfopen
	#define CHK_sysfilestreamfopen  TRUE
	#define EXP_sysfilestreamfopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfopen", (RTS_UINTPTR)sysfilestreamfopen, 1, RTSITF_GET_SIGNATURE(0, 0x0AD9CD95), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfopen  PFSYSFILESTREAMFOPEN_IEC pfsysfilestreamfopen;
	#define EXT_sysfilestreamfopen  extern PFSYSFILESTREAMFOPEN_IEC pfsysfilestreamfopen;
	#define GET_sysfilestreamfopen(fl)  s_pfCMGetAPI2( "sysfilestreamfopen", (RTS_VOID_FCTPTR *)&pfsysfilestreamfopen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0AD9CD95), 0x03050000)
	#define CAL_sysfilestreamfopen  pfsysfilestreamfopen
	#define CHK_sysfilestreamfopen  (pfsysfilestreamfopen != NULL)
	#define EXP_sysfilestreamfopen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfopen", (RTS_UINTPTR)sysfilestreamfopen, 1, RTSITF_GET_SIGNATURE(0, 0x0AD9CD95), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfprintf_int</description>
 */
typedef struct tagsysfilestreamfprintf_int_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_DINT nArg;					/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFPrintf_Int;	/* VAR_OUTPUT */
} sysfilestreamfprintf_int_struct;

void CDECL CDECL_EXT sysfilestreamfprintf_int(sysfilestreamfprintf_int_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFPRINTF_INT_IEC) (sysfilestreamfprintf_int_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPRINTF_INT_NOTIMPLEMENTED)
	#define USE_sysfilestreamfprintf_int
	#define EXT_sysfilestreamfprintf_int
	#define GET_sysfilestreamfprintf_int(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfprintf_int(p0) 
	#define CHK_sysfilestreamfprintf_int  FALSE
	#define EXP_sysfilestreamfprintf_int  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfprintf_int
	#define EXT_sysfilestreamfprintf_int
	#define GET_sysfilestreamfprintf_int(fl)  CAL_CMGETAPI( "sysfilestreamfprintf_int" ) 
	#define CAL_sysfilestreamfprintf_int  sysfilestreamfprintf_int
	#define CHK_sysfilestreamfprintf_int  TRUE
	#define EXP_sysfilestreamfprintf_int  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_int", (RTS_UINTPTR)sysfilestreamfprintf_int, 1, RTSITF_GET_SIGNATURE(0, 0x2BB939E3), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfprintf_int
	#define EXT_sysfilestreamfprintf_int
	#define GET_sysfilestreamfprintf_int(fl)  CAL_CMGETAPI( "sysfilestreamfprintf_int" ) 
	#define CAL_sysfilestreamfprintf_int  sysfilestreamfprintf_int
	#define CHK_sysfilestreamfprintf_int  TRUE
	#define EXP_sysfilestreamfprintf_int  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_int", (RTS_UINTPTR)sysfilestreamfprintf_int, 1, RTSITF_GET_SIGNATURE(0, 0x2BB939E3), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfprintf_int
	#define EXT_SysFileStreamsysfilestreamfprintf_int
	#define GET_SysFileStreamsysfilestreamfprintf_int  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfprintf_int  sysfilestreamfprintf_int
	#define CHK_SysFileStreamsysfilestreamfprintf_int  TRUE
	#define EXP_SysFileStreamsysfilestreamfprintf_int  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_int", (RTS_UINTPTR)sysfilestreamfprintf_int, 1, RTSITF_GET_SIGNATURE(0, 0x2BB939E3), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfprintf_int
	#define EXT_sysfilestreamfprintf_int
	#define GET_sysfilestreamfprintf_int(fl)  CAL_CMGETAPI( "sysfilestreamfprintf_int" ) 
	#define CAL_sysfilestreamfprintf_int  sysfilestreamfprintf_int
	#define CHK_sysfilestreamfprintf_int  TRUE
	#define EXP_sysfilestreamfprintf_int  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_int", (RTS_UINTPTR)sysfilestreamfprintf_int, 1, RTSITF_GET_SIGNATURE(0, 0x2BB939E3), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfprintf_int  PFSYSFILESTREAMFPRINTF_INT_IEC pfsysfilestreamfprintf_int;
	#define EXT_sysfilestreamfprintf_int  extern PFSYSFILESTREAMFPRINTF_INT_IEC pfsysfilestreamfprintf_int;
	#define GET_sysfilestreamfprintf_int(fl)  s_pfCMGetAPI2( "sysfilestreamfprintf_int", (RTS_VOID_FCTPTR *)&pfsysfilestreamfprintf_int, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2BB939E3), 0x03050000)
	#define CAL_sysfilestreamfprintf_int  pfsysfilestreamfprintf_int
	#define CHK_sysfilestreamfprintf_int  (pfsysfilestreamfprintf_int != NULL)
	#define EXP_sysfilestreamfprintf_int   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_int", (RTS_UINTPTR)sysfilestreamfprintf_int, 1, RTSITF_GET_SIGNATURE(0, 0x2BB939E3), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfprintf_real</description>
 */
typedef struct tagsysfilestreamfprintf_real_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_REAL rArg;					/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFPrintf_Real;	/* VAR_OUTPUT */
} sysfilestreamfprintf_real_struct;

void CDECL CDECL_EXT sysfilestreamfprintf_real(sysfilestreamfprintf_real_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFPRINTF_REAL_IEC) (sysfilestreamfprintf_real_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPRINTF_REAL_NOTIMPLEMENTED)
	#define USE_sysfilestreamfprintf_real
	#define EXT_sysfilestreamfprintf_real
	#define GET_sysfilestreamfprintf_real(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfprintf_real(p0) 
	#define CHK_sysfilestreamfprintf_real  FALSE
	#define EXP_sysfilestreamfprintf_real  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfprintf_real
	#define EXT_sysfilestreamfprintf_real
	#define GET_sysfilestreamfprintf_real(fl)  CAL_CMGETAPI( "sysfilestreamfprintf_real" ) 
	#define CAL_sysfilestreamfprintf_real  sysfilestreamfprintf_real
	#define CHK_sysfilestreamfprintf_real  TRUE
	#define EXP_sysfilestreamfprintf_real  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_real", (RTS_UINTPTR)sysfilestreamfprintf_real, 1, RTSITF_GET_SIGNATURE(0, 0x6F4D6A7C), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfprintf_real
	#define EXT_sysfilestreamfprintf_real
	#define GET_sysfilestreamfprintf_real(fl)  CAL_CMGETAPI( "sysfilestreamfprintf_real" ) 
	#define CAL_sysfilestreamfprintf_real  sysfilestreamfprintf_real
	#define CHK_sysfilestreamfprintf_real  TRUE
	#define EXP_sysfilestreamfprintf_real  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_real", (RTS_UINTPTR)sysfilestreamfprintf_real, 1, RTSITF_GET_SIGNATURE(0, 0x6F4D6A7C), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfprintf_real
	#define EXT_SysFileStreamsysfilestreamfprintf_real
	#define GET_SysFileStreamsysfilestreamfprintf_real  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfprintf_real  sysfilestreamfprintf_real
	#define CHK_SysFileStreamsysfilestreamfprintf_real  TRUE
	#define EXP_SysFileStreamsysfilestreamfprintf_real  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_real", (RTS_UINTPTR)sysfilestreamfprintf_real, 1, RTSITF_GET_SIGNATURE(0, 0x6F4D6A7C), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfprintf_real
	#define EXT_sysfilestreamfprintf_real
	#define GET_sysfilestreamfprintf_real(fl)  CAL_CMGETAPI( "sysfilestreamfprintf_real" ) 
	#define CAL_sysfilestreamfprintf_real  sysfilestreamfprintf_real
	#define CHK_sysfilestreamfprintf_real  TRUE
	#define EXP_sysfilestreamfprintf_real  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_real", (RTS_UINTPTR)sysfilestreamfprintf_real, 1, RTSITF_GET_SIGNATURE(0, 0x6F4D6A7C), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfprintf_real  PFSYSFILESTREAMFPRINTF_REAL_IEC pfsysfilestreamfprintf_real;
	#define EXT_sysfilestreamfprintf_real  extern PFSYSFILESTREAMFPRINTF_REAL_IEC pfsysfilestreamfprintf_real;
	#define GET_sysfilestreamfprintf_real(fl)  s_pfCMGetAPI2( "sysfilestreamfprintf_real", (RTS_VOID_FCTPTR *)&pfsysfilestreamfprintf_real, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6F4D6A7C), 0x03050000)
	#define CAL_sysfilestreamfprintf_real  pfsysfilestreamfprintf_real
	#define CHK_sysfilestreamfprintf_real  (pfsysfilestreamfprintf_real != NULL)
	#define EXP_sysfilestreamfprintf_real   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_real", (RTS_UINTPTR)sysfilestreamfprintf_real, 1, RTSITF_GET_SIGNATURE(0, 0x6F4D6A7C), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfprintf_string</description>
 */
typedef struct tagsysfilestreamfprintf_string_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_STRING *sArg;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFPrintf_String;	/* VAR_OUTPUT */
} sysfilestreamfprintf_string_struct;

void CDECL CDECL_EXT sysfilestreamfprintf_string(sysfilestreamfprintf_string_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFPRINTF_STRING_IEC) (sysfilestreamfprintf_string_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPRINTF_STRING_NOTIMPLEMENTED)
	#define USE_sysfilestreamfprintf_string
	#define EXT_sysfilestreamfprintf_string
	#define GET_sysfilestreamfprintf_string(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfprintf_string(p0) 
	#define CHK_sysfilestreamfprintf_string  FALSE
	#define EXP_sysfilestreamfprintf_string  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfprintf_string
	#define EXT_sysfilestreamfprintf_string
	#define GET_sysfilestreamfprintf_string(fl)  CAL_CMGETAPI( "sysfilestreamfprintf_string" ) 
	#define CAL_sysfilestreamfprintf_string  sysfilestreamfprintf_string
	#define CHK_sysfilestreamfprintf_string  TRUE
	#define EXP_sysfilestreamfprintf_string  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_string", (RTS_UINTPTR)sysfilestreamfprintf_string, 1, RTSITF_GET_SIGNATURE(0, 0x7E3FE324), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfprintf_string
	#define EXT_sysfilestreamfprintf_string
	#define GET_sysfilestreamfprintf_string(fl)  CAL_CMGETAPI( "sysfilestreamfprintf_string" ) 
	#define CAL_sysfilestreamfprintf_string  sysfilestreamfprintf_string
	#define CHK_sysfilestreamfprintf_string  TRUE
	#define EXP_sysfilestreamfprintf_string  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_string", (RTS_UINTPTR)sysfilestreamfprintf_string, 1, RTSITF_GET_SIGNATURE(0, 0x7E3FE324), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfprintf_string
	#define EXT_SysFileStreamsysfilestreamfprintf_string
	#define GET_SysFileStreamsysfilestreamfprintf_string  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfprintf_string  sysfilestreamfprintf_string
	#define CHK_SysFileStreamsysfilestreamfprintf_string  TRUE
	#define EXP_SysFileStreamsysfilestreamfprintf_string  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_string", (RTS_UINTPTR)sysfilestreamfprintf_string, 1, RTSITF_GET_SIGNATURE(0, 0x7E3FE324), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfprintf_string
	#define EXT_sysfilestreamfprintf_string
	#define GET_sysfilestreamfprintf_string(fl)  CAL_CMGETAPI( "sysfilestreamfprintf_string" ) 
	#define CAL_sysfilestreamfprintf_string  sysfilestreamfprintf_string
	#define CHK_sysfilestreamfprintf_string  TRUE
	#define EXP_sysfilestreamfprintf_string  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_string", (RTS_UINTPTR)sysfilestreamfprintf_string, 1, RTSITF_GET_SIGNATURE(0, 0x7E3FE324), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfprintf_string  PFSYSFILESTREAMFPRINTF_STRING_IEC pfsysfilestreamfprintf_string;
	#define EXT_sysfilestreamfprintf_string  extern PFSYSFILESTREAMFPRINTF_STRING_IEC pfsysfilestreamfprintf_string;
	#define GET_sysfilestreamfprintf_string(fl)  s_pfCMGetAPI2( "sysfilestreamfprintf_string", (RTS_VOID_FCTPTR *)&pfsysfilestreamfprintf_string, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7E3FE324), 0x03050000)
	#define CAL_sysfilestreamfprintf_string  pfsysfilestreamfprintf_string
	#define CHK_sysfilestreamfprintf_string  (pfsysfilestreamfprintf_string != NULL)
	#define EXP_sysfilestreamfprintf_string   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfprintf_string", (RTS_UINTPTR)sysfilestreamfprintf_string, 1, RTSITF_GET_SIGNATURE(0, 0x7E3FE324), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfputc</description>
 */
typedef struct tagsysfilestreamfputc_struct
{
	RTS_IEC_DINT c;						/* VAR_INPUT */
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFPutC;	/* VAR_OUTPUT */
} sysfilestreamfputc_struct;

void CDECL CDECL_EXT sysfilestreamfputc(sysfilestreamfputc_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFPUTC_IEC) (sysfilestreamfputc_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPUTC_NOTIMPLEMENTED)
	#define USE_sysfilestreamfputc
	#define EXT_sysfilestreamfputc
	#define GET_sysfilestreamfputc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfputc(p0) 
	#define CHK_sysfilestreamfputc  FALSE
	#define EXP_sysfilestreamfputc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfputc
	#define EXT_sysfilestreamfputc
	#define GET_sysfilestreamfputc(fl)  CAL_CMGETAPI( "sysfilestreamfputc" ) 
	#define CAL_sysfilestreamfputc  sysfilestreamfputc
	#define CHK_sysfilestreamfputc  TRUE
	#define EXP_sysfilestreamfputc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfputc", (RTS_UINTPTR)sysfilestreamfputc, 1, RTSITF_GET_SIGNATURE(0, 0x0E6EACA5), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfputc
	#define EXT_sysfilestreamfputc
	#define GET_sysfilestreamfputc(fl)  CAL_CMGETAPI( "sysfilestreamfputc" ) 
	#define CAL_sysfilestreamfputc  sysfilestreamfputc
	#define CHK_sysfilestreamfputc  TRUE
	#define EXP_sysfilestreamfputc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfputc", (RTS_UINTPTR)sysfilestreamfputc, 1, RTSITF_GET_SIGNATURE(0, 0x0E6EACA5), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfputc
	#define EXT_SysFileStreamsysfilestreamfputc
	#define GET_SysFileStreamsysfilestreamfputc  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfputc  sysfilestreamfputc
	#define CHK_SysFileStreamsysfilestreamfputc  TRUE
	#define EXP_SysFileStreamsysfilestreamfputc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfputc", (RTS_UINTPTR)sysfilestreamfputc, 1, RTSITF_GET_SIGNATURE(0, 0x0E6EACA5), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfputc
	#define EXT_sysfilestreamfputc
	#define GET_sysfilestreamfputc(fl)  CAL_CMGETAPI( "sysfilestreamfputc" ) 
	#define CAL_sysfilestreamfputc  sysfilestreamfputc
	#define CHK_sysfilestreamfputc  TRUE
	#define EXP_sysfilestreamfputc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfputc", (RTS_UINTPTR)sysfilestreamfputc, 1, RTSITF_GET_SIGNATURE(0, 0x0E6EACA5), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfputc  PFSYSFILESTREAMFPUTC_IEC pfsysfilestreamfputc;
	#define EXT_sysfilestreamfputc  extern PFSYSFILESTREAMFPUTC_IEC pfsysfilestreamfputc;
	#define GET_sysfilestreamfputc(fl)  s_pfCMGetAPI2( "sysfilestreamfputc", (RTS_VOID_FCTPTR *)&pfsysfilestreamfputc, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0E6EACA5), 0x03050000)
	#define CAL_sysfilestreamfputc  pfsysfilestreamfputc
	#define CHK_sysfilestreamfputc  (pfsysfilestreamfputc != NULL)
	#define EXP_sysfilestreamfputc   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfputc", (RTS_UINTPTR)sysfilestreamfputc, 1, RTSITF_GET_SIGNATURE(0, 0x0E6EACA5), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfputs</description>
 */
typedef struct tagsysfilestreamfputs_struct
{
	RTS_IEC_STRING *str;				/* VAR_INPUT */
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFPutS;	/* VAR_OUTPUT */
} sysfilestreamfputs_struct;

void CDECL CDECL_EXT sysfilestreamfputs(sysfilestreamfputs_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFPUTS_IEC) (sysfilestreamfputs_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPUTS_NOTIMPLEMENTED)
	#define USE_sysfilestreamfputs
	#define EXT_sysfilestreamfputs
	#define GET_sysfilestreamfputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfputs(p0) 
	#define CHK_sysfilestreamfputs  FALSE
	#define EXP_sysfilestreamfputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfputs
	#define EXT_sysfilestreamfputs
	#define GET_sysfilestreamfputs(fl)  CAL_CMGETAPI( "sysfilestreamfputs" ) 
	#define CAL_sysfilestreamfputs  sysfilestreamfputs
	#define CHK_sysfilestreamfputs  TRUE
	#define EXP_sysfilestreamfputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfputs", (RTS_UINTPTR)sysfilestreamfputs, 1, RTSITF_GET_SIGNATURE(0, 0x386D65D8), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfputs
	#define EXT_sysfilestreamfputs
	#define GET_sysfilestreamfputs(fl)  CAL_CMGETAPI( "sysfilestreamfputs" ) 
	#define CAL_sysfilestreamfputs  sysfilestreamfputs
	#define CHK_sysfilestreamfputs  TRUE
	#define EXP_sysfilestreamfputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfputs", (RTS_UINTPTR)sysfilestreamfputs, 1, RTSITF_GET_SIGNATURE(0, 0x386D65D8), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfputs
	#define EXT_SysFileStreamsysfilestreamfputs
	#define GET_SysFileStreamsysfilestreamfputs  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfputs  sysfilestreamfputs
	#define CHK_SysFileStreamsysfilestreamfputs  TRUE
	#define EXP_SysFileStreamsysfilestreamfputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfputs", (RTS_UINTPTR)sysfilestreamfputs, 1, RTSITF_GET_SIGNATURE(0, 0x386D65D8), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfputs
	#define EXT_sysfilestreamfputs
	#define GET_sysfilestreamfputs(fl)  CAL_CMGETAPI( "sysfilestreamfputs" ) 
	#define CAL_sysfilestreamfputs  sysfilestreamfputs
	#define CHK_sysfilestreamfputs  TRUE
	#define EXP_sysfilestreamfputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfputs", (RTS_UINTPTR)sysfilestreamfputs, 1, RTSITF_GET_SIGNATURE(0, 0x386D65D8), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfputs  PFSYSFILESTREAMFPUTS_IEC pfsysfilestreamfputs;
	#define EXT_sysfilestreamfputs  extern PFSYSFILESTREAMFPUTS_IEC pfsysfilestreamfputs;
	#define GET_sysfilestreamfputs(fl)  s_pfCMGetAPI2( "sysfilestreamfputs", (RTS_VOID_FCTPTR *)&pfsysfilestreamfputs, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x386D65D8), 0x03050000)
	#define CAL_sysfilestreamfputs  pfsysfilestreamfputs
	#define CHK_sysfilestreamfputs  (pfsysfilestreamfputs != NULL)
	#define EXP_sysfilestreamfputs   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfputs", (RTS_UINTPTR)sysfilestreamfputs, 1, RTSITF_GET_SIGNATURE(0, 0x386D65D8), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfread</description>
 */
typedef struct tagsysfilestreamfread_struct
{
	RTS_IEC_BYTE *Buffer;				/* VAR_INPUT */
	RTS_IEC_DWORD Size;					/* VAR_INPUT */
	RTS_IEC_DWORD NObjs;				/* VAR_INPUT */
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DWORD SysFileStreamFRead;	/* VAR_OUTPUT */
} sysfilestreamfread_struct;

void CDECL CDECL_EXT sysfilestreamfread(sysfilestreamfread_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFREAD_IEC) (sysfilestreamfread_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFREAD_NOTIMPLEMENTED)
	#define USE_sysfilestreamfread
	#define EXT_sysfilestreamfread
	#define GET_sysfilestreamfread(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfread(p0) 
	#define CHK_sysfilestreamfread  FALSE
	#define EXP_sysfilestreamfread  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfread
	#define EXT_sysfilestreamfread
	#define GET_sysfilestreamfread(fl)  CAL_CMGETAPI( "sysfilestreamfread" ) 
	#define CAL_sysfilestreamfread  sysfilestreamfread
	#define CHK_sysfilestreamfread  TRUE
	#define EXP_sysfilestreamfread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfread", (RTS_UINTPTR)sysfilestreamfread, 1, RTSITF_GET_SIGNATURE(0, 0x04A4CE64), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfread
	#define EXT_sysfilestreamfread
	#define GET_sysfilestreamfread(fl)  CAL_CMGETAPI( "sysfilestreamfread" ) 
	#define CAL_sysfilestreamfread  sysfilestreamfread
	#define CHK_sysfilestreamfread  TRUE
	#define EXP_sysfilestreamfread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfread", (RTS_UINTPTR)sysfilestreamfread, 1, RTSITF_GET_SIGNATURE(0, 0x04A4CE64), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfread
	#define EXT_SysFileStreamsysfilestreamfread
	#define GET_SysFileStreamsysfilestreamfread  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfread  sysfilestreamfread
	#define CHK_SysFileStreamsysfilestreamfread  TRUE
	#define EXP_SysFileStreamsysfilestreamfread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfread", (RTS_UINTPTR)sysfilestreamfread, 1, RTSITF_GET_SIGNATURE(0, 0x04A4CE64), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfread
	#define EXT_sysfilestreamfread
	#define GET_sysfilestreamfread(fl)  CAL_CMGETAPI( "sysfilestreamfread" ) 
	#define CAL_sysfilestreamfread  sysfilestreamfread
	#define CHK_sysfilestreamfread  TRUE
	#define EXP_sysfilestreamfread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfread", (RTS_UINTPTR)sysfilestreamfread, 1, RTSITF_GET_SIGNATURE(0, 0x04A4CE64), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfread  PFSYSFILESTREAMFREAD_IEC pfsysfilestreamfread;
	#define EXT_sysfilestreamfread  extern PFSYSFILESTREAMFREAD_IEC pfsysfilestreamfread;
	#define GET_sysfilestreamfread(fl)  s_pfCMGetAPI2( "sysfilestreamfread", (RTS_VOID_FCTPTR *)&pfsysfilestreamfread, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x04A4CE64), 0x03050000)
	#define CAL_sysfilestreamfread  pfsysfilestreamfread
	#define CHK_sysfilestreamfread  (pfsysfilestreamfread != NULL)
	#define EXP_sysfilestreamfread   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfread", (RTS_UINTPTR)sysfilestreamfread, 1, RTSITF_GET_SIGNATURE(0, 0x04A4CE64), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfscanf_int</description>
 */
typedef struct tagsysfilestreamfscanf_int_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_DINT *pnArg;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFScanf_Int;	/* VAR_OUTPUT */
} sysfilestreamfscanf_int_struct;

void CDECL CDECL_EXT sysfilestreamfscanf_int(sysfilestreamfscanf_int_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFSCANF_INT_IEC) (sysfilestreamfscanf_int_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFSCANF_INT_NOTIMPLEMENTED)
	#define USE_sysfilestreamfscanf_int
	#define EXT_sysfilestreamfscanf_int
	#define GET_sysfilestreamfscanf_int(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfscanf_int(p0) 
	#define CHK_sysfilestreamfscanf_int  FALSE
	#define EXP_sysfilestreamfscanf_int  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfscanf_int
	#define EXT_sysfilestreamfscanf_int
	#define GET_sysfilestreamfscanf_int(fl)  CAL_CMGETAPI( "sysfilestreamfscanf_int" ) 
	#define CAL_sysfilestreamfscanf_int  sysfilestreamfscanf_int
	#define CHK_sysfilestreamfscanf_int  TRUE
	#define EXP_sysfilestreamfscanf_int  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_int", (RTS_UINTPTR)sysfilestreamfscanf_int, 1, RTSITF_GET_SIGNATURE(0, 0x797A9171), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfscanf_int
	#define EXT_sysfilestreamfscanf_int
	#define GET_sysfilestreamfscanf_int(fl)  CAL_CMGETAPI( "sysfilestreamfscanf_int" ) 
	#define CAL_sysfilestreamfscanf_int  sysfilestreamfscanf_int
	#define CHK_sysfilestreamfscanf_int  TRUE
	#define EXP_sysfilestreamfscanf_int  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_int", (RTS_UINTPTR)sysfilestreamfscanf_int, 1, RTSITF_GET_SIGNATURE(0, 0x797A9171), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfscanf_int
	#define EXT_SysFileStreamsysfilestreamfscanf_int
	#define GET_SysFileStreamsysfilestreamfscanf_int  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfscanf_int  sysfilestreamfscanf_int
	#define CHK_SysFileStreamsysfilestreamfscanf_int  TRUE
	#define EXP_SysFileStreamsysfilestreamfscanf_int  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_int", (RTS_UINTPTR)sysfilestreamfscanf_int, 1, RTSITF_GET_SIGNATURE(0, 0x797A9171), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfscanf_int
	#define EXT_sysfilestreamfscanf_int
	#define GET_sysfilestreamfscanf_int(fl)  CAL_CMGETAPI( "sysfilestreamfscanf_int" ) 
	#define CAL_sysfilestreamfscanf_int  sysfilestreamfscanf_int
	#define CHK_sysfilestreamfscanf_int  TRUE
	#define EXP_sysfilestreamfscanf_int  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_int", (RTS_UINTPTR)sysfilestreamfscanf_int, 1, RTSITF_GET_SIGNATURE(0, 0x797A9171), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfscanf_int  PFSYSFILESTREAMFSCANF_INT_IEC pfsysfilestreamfscanf_int;
	#define EXT_sysfilestreamfscanf_int  extern PFSYSFILESTREAMFSCANF_INT_IEC pfsysfilestreamfscanf_int;
	#define GET_sysfilestreamfscanf_int(fl)  s_pfCMGetAPI2( "sysfilestreamfscanf_int", (RTS_VOID_FCTPTR *)&pfsysfilestreamfscanf_int, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x797A9171), 0x03050000)
	#define CAL_sysfilestreamfscanf_int  pfsysfilestreamfscanf_int
	#define CHK_sysfilestreamfscanf_int  (pfsysfilestreamfscanf_int != NULL)
	#define EXP_sysfilestreamfscanf_int   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_int", (RTS_UINTPTR)sysfilestreamfscanf_int, 1, RTSITF_GET_SIGNATURE(0, 0x797A9171), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfscanf_real</description>
 */
typedef struct tagsysfilestreamfscanf_real_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_REAL *pfArg;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFScanf_Real;	/* VAR_OUTPUT */
} sysfilestreamfscanf_real_struct;

void CDECL CDECL_EXT sysfilestreamfscanf_real(sysfilestreamfscanf_real_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFSCANF_REAL_IEC) (sysfilestreamfscanf_real_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFSCANF_REAL_NOTIMPLEMENTED)
	#define USE_sysfilestreamfscanf_real
	#define EXT_sysfilestreamfscanf_real
	#define GET_sysfilestreamfscanf_real(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfscanf_real(p0) 
	#define CHK_sysfilestreamfscanf_real  FALSE
	#define EXP_sysfilestreamfscanf_real  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfscanf_real
	#define EXT_sysfilestreamfscanf_real
	#define GET_sysfilestreamfscanf_real(fl)  CAL_CMGETAPI( "sysfilestreamfscanf_real" ) 
	#define CAL_sysfilestreamfscanf_real  sysfilestreamfscanf_real
	#define CHK_sysfilestreamfscanf_real  TRUE
	#define EXP_sysfilestreamfscanf_real  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_real", (RTS_UINTPTR)sysfilestreamfscanf_real, 1, RTSITF_GET_SIGNATURE(0, 0x35DAE113), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfscanf_real
	#define EXT_sysfilestreamfscanf_real
	#define GET_sysfilestreamfscanf_real(fl)  CAL_CMGETAPI( "sysfilestreamfscanf_real" ) 
	#define CAL_sysfilestreamfscanf_real  sysfilestreamfscanf_real
	#define CHK_sysfilestreamfscanf_real  TRUE
	#define EXP_sysfilestreamfscanf_real  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_real", (RTS_UINTPTR)sysfilestreamfscanf_real, 1, RTSITF_GET_SIGNATURE(0, 0x35DAE113), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfscanf_real
	#define EXT_SysFileStreamsysfilestreamfscanf_real
	#define GET_SysFileStreamsysfilestreamfscanf_real  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfscanf_real  sysfilestreamfscanf_real
	#define CHK_SysFileStreamsysfilestreamfscanf_real  TRUE
	#define EXP_SysFileStreamsysfilestreamfscanf_real  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_real", (RTS_UINTPTR)sysfilestreamfscanf_real, 1, RTSITF_GET_SIGNATURE(0, 0x35DAE113), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfscanf_real
	#define EXT_sysfilestreamfscanf_real
	#define GET_sysfilestreamfscanf_real(fl)  CAL_CMGETAPI( "sysfilestreamfscanf_real" ) 
	#define CAL_sysfilestreamfscanf_real  sysfilestreamfscanf_real
	#define CHK_sysfilestreamfscanf_real  TRUE
	#define EXP_sysfilestreamfscanf_real  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_real", (RTS_UINTPTR)sysfilestreamfscanf_real, 1, RTSITF_GET_SIGNATURE(0, 0x35DAE113), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfscanf_real  PFSYSFILESTREAMFSCANF_REAL_IEC pfsysfilestreamfscanf_real;
	#define EXT_sysfilestreamfscanf_real  extern PFSYSFILESTREAMFSCANF_REAL_IEC pfsysfilestreamfscanf_real;
	#define GET_sysfilestreamfscanf_real(fl)  s_pfCMGetAPI2( "sysfilestreamfscanf_real", (RTS_VOID_FCTPTR *)&pfsysfilestreamfscanf_real, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x35DAE113), 0x03050000)
	#define CAL_sysfilestreamfscanf_real  pfsysfilestreamfscanf_real
	#define CHK_sysfilestreamfscanf_real  (pfsysfilestreamfscanf_real != NULL)
	#define EXP_sysfilestreamfscanf_real   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_real", (RTS_UINTPTR)sysfilestreamfscanf_real, 1, RTSITF_GET_SIGNATURE(0, 0x35DAE113), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfscanf_string</description>
 */
typedef struct tagsysfilestreamfscanf_string_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_STRING *psArg;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFScanf_String;	/* VAR_OUTPUT */
} sysfilestreamfscanf_string_struct;

void CDECL CDECL_EXT sysfilestreamfscanf_string(sysfilestreamfscanf_string_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFSCANF_STRING_IEC) (sysfilestreamfscanf_string_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFSCANF_STRING_NOTIMPLEMENTED)
	#define USE_sysfilestreamfscanf_string
	#define EXT_sysfilestreamfscanf_string
	#define GET_sysfilestreamfscanf_string(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfscanf_string(p0) 
	#define CHK_sysfilestreamfscanf_string  FALSE
	#define EXP_sysfilestreamfscanf_string  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfscanf_string
	#define EXT_sysfilestreamfscanf_string
	#define GET_sysfilestreamfscanf_string(fl)  CAL_CMGETAPI( "sysfilestreamfscanf_string" ) 
	#define CAL_sysfilestreamfscanf_string  sysfilestreamfscanf_string
	#define CHK_sysfilestreamfscanf_string  TRUE
	#define EXP_sysfilestreamfscanf_string  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_string", (RTS_UINTPTR)sysfilestreamfscanf_string, 1, RTSITF_GET_SIGNATURE(0, 0xB5F64354), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfscanf_string
	#define EXT_sysfilestreamfscanf_string
	#define GET_sysfilestreamfscanf_string(fl)  CAL_CMGETAPI( "sysfilestreamfscanf_string" ) 
	#define CAL_sysfilestreamfscanf_string  sysfilestreamfscanf_string
	#define CHK_sysfilestreamfscanf_string  TRUE
	#define EXP_sysfilestreamfscanf_string  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_string", (RTS_UINTPTR)sysfilestreamfscanf_string, 1, RTSITF_GET_SIGNATURE(0, 0xB5F64354), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfscanf_string
	#define EXT_SysFileStreamsysfilestreamfscanf_string
	#define GET_SysFileStreamsysfilestreamfscanf_string  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfscanf_string  sysfilestreamfscanf_string
	#define CHK_SysFileStreamsysfilestreamfscanf_string  TRUE
	#define EXP_SysFileStreamsysfilestreamfscanf_string  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_string", (RTS_UINTPTR)sysfilestreamfscanf_string, 1, RTSITF_GET_SIGNATURE(0, 0xB5F64354), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfscanf_string
	#define EXT_sysfilestreamfscanf_string
	#define GET_sysfilestreamfscanf_string(fl)  CAL_CMGETAPI( "sysfilestreamfscanf_string" ) 
	#define CAL_sysfilestreamfscanf_string  sysfilestreamfscanf_string
	#define CHK_sysfilestreamfscanf_string  TRUE
	#define EXP_sysfilestreamfscanf_string  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_string", (RTS_UINTPTR)sysfilestreamfscanf_string, 1, RTSITF_GET_SIGNATURE(0, 0xB5F64354), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfscanf_string  PFSYSFILESTREAMFSCANF_STRING_IEC pfsysfilestreamfscanf_string;
	#define EXT_sysfilestreamfscanf_string  extern PFSYSFILESTREAMFSCANF_STRING_IEC pfsysfilestreamfscanf_string;
	#define GET_sysfilestreamfscanf_string(fl)  s_pfCMGetAPI2( "sysfilestreamfscanf_string", (RTS_VOID_FCTPTR *)&pfsysfilestreamfscanf_string, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB5F64354), 0x03050000)
	#define CAL_sysfilestreamfscanf_string  pfsysfilestreamfscanf_string
	#define CHK_sysfilestreamfscanf_string  (pfsysfilestreamfscanf_string != NULL)
	#define EXP_sysfilestreamfscanf_string   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfscanf_string", (RTS_UINTPTR)sysfilestreamfscanf_string, 1, RTSITF_GET_SIGNATURE(0, 0xB5F64354), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfseek</description>
 */
typedef struct tagsysfilestreamfseek_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT offset;				/* VAR_INPUT */
	RTS_IEC_DINT origin;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFSeek;	/* VAR_OUTPUT */
} sysfilestreamfseek_struct;

void CDECL CDECL_EXT sysfilestreamfseek(sysfilestreamfseek_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFSEEK_IEC) (sysfilestreamfseek_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFSEEK_NOTIMPLEMENTED)
	#define USE_sysfilestreamfseek
	#define EXT_sysfilestreamfseek
	#define GET_sysfilestreamfseek(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfseek(p0) 
	#define CHK_sysfilestreamfseek  FALSE
	#define EXP_sysfilestreamfseek  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfseek
	#define EXT_sysfilestreamfseek
	#define GET_sysfilestreamfseek(fl)  CAL_CMGETAPI( "sysfilestreamfseek" ) 
	#define CAL_sysfilestreamfseek  sysfilestreamfseek
	#define CHK_sysfilestreamfseek  TRUE
	#define EXP_sysfilestreamfseek  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfseek", (RTS_UINTPTR)sysfilestreamfseek, 1, RTSITF_GET_SIGNATURE(0, 0xFC0CF4A9), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfseek
	#define EXT_sysfilestreamfseek
	#define GET_sysfilestreamfseek(fl)  CAL_CMGETAPI( "sysfilestreamfseek" ) 
	#define CAL_sysfilestreamfseek  sysfilestreamfseek
	#define CHK_sysfilestreamfseek  TRUE
	#define EXP_sysfilestreamfseek  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfseek", (RTS_UINTPTR)sysfilestreamfseek, 1, RTSITF_GET_SIGNATURE(0, 0xFC0CF4A9), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfseek
	#define EXT_SysFileStreamsysfilestreamfseek
	#define GET_SysFileStreamsysfilestreamfseek  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfseek  sysfilestreamfseek
	#define CHK_SysFileStreamsysfilestreamfseek  TRUE
	#define EXP_SysFileStreamsysfilestreamfseek  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfseek", (RTS_UINTPTR)sysfilestreamfseek, 1, RTSITF_GET_SIGNATURE(0, 0xFC0CF4A9), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfseek
	#define EXT_sysfilestreamfseek
	#define GET_sysfilestreamfseek(fl)  CAL_CMGETAPI( "sysfilestreamfseek" ) 
	#define CAL_sysfilestreamfseek  sysfilestreamfseek
	#define CHK_sysfilestreamfseek  TRUE
	#define EXP_sysfilestreamfseek  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfseek", (RTS_UINTPTR)sysfilestreamfseek, 1, RTSITF_GET_SIGNATURE(0, 0xFC0CF4A9), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfseek  PFSYSFILESTREAMFSEEK_IEC pfsysfilestreamfseek;
	#define EXT_sysfilestreamfseek  extern PFSYSFILESTREAMFSEEK_IEC pfsysfilestreamfseek;
	#define GET_sysfilestreamfseek(fl)  s_pfCMGetAPI2( "sysfilestreamfseek", (RTS_VOID_FCTPTR *)&pfsysfilestreamfseek, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFC0CF4A9), 0x03050000)
	#define CAL_sysfilestreamfseek  pfsysfilestreamfseek
	#define CHK_sysfilestreamfseek  (pfsysfilestreamfseek != NULL)
	#define EXP_sysfilestreamfseek   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfseek", (RTS_UINTPTR)sysfilestreamfseek, 1, RTSITF_GET_SIGNATURE(0, 0xFC0CF4A9), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfsetpos</description>
 */
typedef struct tagsysfilestreamfsetpos_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_BYTE *pFPos;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFSetPos;	/* VAR_OUTPUT */
} sysfilestreamfsetpos_struct;

void CDECL CDECL_EXT sysfilestreamfsetpos(sysfilestreamfsetpos_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFSETPOS_IEC) (sysfilestreamfsetpos_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFSETPOS_NOTIMPLEMENTED)
	#define USE_sysfilestreamfsetpos
	#define EXT_sysfilestreamfsetpos
	#define GET_sysfilestreamfsetpos(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfsetpos(p0) 
	#define CHK_sysfilestreamfsetpos  FALSE
	#define EXP_sysfilestreamfsetpos  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfsetpos
	#define EXT_sysfilestreamfsetpos
	#define GET_sysfilestreamfsetpos(fl)  CAL_CMGETAPI( "sysfilestreamfsetpos" ) 
	#define CAL_sysfilestreamfsetpos  sysfilestreamfsetpos
	#define CHK_sysfilestreamfsetpos  TRUE
	#define EXP_sysfilestreamfsetpos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfsetpos", (RTS_UINTPTR)sysfilestreamfsetpos, 1, RTSITF_GET_SIGNATURE(0, 0x2E8D7680), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfsetpos
	#define EXT_sysfilestreamfsetpos
	#define GET_sysfilestreamfsetpos(fl)  CAL_CMGETAPI( "sysfilestreamfsetpos" ) 
	#define CAL_sysfilestreamfsetpos  sysfilestreamfsetpos
	#define CHK_sysfilestreamfsetpos  TRUE
	#define EXP_sysfilestreamfsetpos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfsetpos", (RTS_UINTPTR)sysfilestreamfsetpos, 1, RTSITF_GET_SIGNATURE(0, 0x2E8D7680), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfsetpos
	#define EXT_SysFileStreamsysfilestreamfsetpos
	#define GET_SysFileStreamsysfilestreamfsetpos  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfsetpos  sysfilestreamfsetpos
	#define CHK_SysFileStreamsysfilestreamfsetpos  TRUE
	#define EXP_SysFileStreamsysfilestreamfsetpos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfsetpos", (RTS_UINTPTR)sysfilestreamfsetpos, 1, RTSITF_GET_SIGNATURE(0, 0x2E8D7680), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfsetpos
	#define EXT_sysfilestreamfsetpos
	#define GET_sysfilestreamfsetpos(fl)  CAL_CMGETAPI( "sysfilestreamfsetpos" ) 
	#define CAL_sysfilestreamfsetpos  sysfilestreamfsetpos
	#define CHK_sysfilestreamfsetpos  TRUE
	#define EXP_sysfilestreamfsetpos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfsetpos", (RTS_UINTPTR)sysfilestreamfsetpos, 1, RTSITF_GET_SIGNATURE(0, 0x2E8D7680), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfsetpos  PFSYSFILESTREAMFSETPOS_IEC pfsysfilestreamfsetpos;
	#define EXT_sysfilestreamfsetpos  extern PFSYSFILESTREAMFSETPOS_IEC pfsysfilestreamfsetpos;
	#define GET_sysfilestreamfsetpos(fl)  s_pfCMGetAPI2( "sysfilestreamfsetpos", (RTS_VOID_FCTPTR *)&pfsysfilestreamfsetpos, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2E8D7680), 0x03050000)
	#define CAL_sysfilestreamfsetpos  pfsysfilestreamfsetpos
	#define CHK_sysfilestreamfsetpos  (pfsysfilestreamfsetpos != NULL)
	#define EXP_sysfilestreamfsetpos   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfsetpos", (RTS_UINTPTR)sysfilestreamfsetpos, 1, RTSITF_GET_SIGNATURE(0, 0x2E8D7680), 0x03050000) 
#endif


/**
 * <description>sysfilestreamftell</description>
 */
typedef struct tagsysfilestreamftell_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFTell;	/* VAR_OUTPUT */
} sysfilestreamftell_struct;

void CDECL CDECL_EXT sysfilestreamftell(sysfilestreamftell_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFTELL_IEC) (sysfilestreamftell_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFTELL_NOTIMPLEMENTED)
	#define USE_sysfilestreamftell
	#define EXT_sysfilestreamftell
	#define GET_sysfilestreamftell(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamftell(p0) 
	#define CHK_sysfilestreamftell  FALSE
	#define EXP_sysfilestreamftell  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamftell
	#define EXT_sysfilestreamftell
	#define GET_sysfilestreamftell(fl)  CAL_CMGETAPI( "sysfilestreamftell" ) 
	#define CAL_sysfilestreamftell  sysfilestreamftell
	#define CHK_sysfilestreamftell  TRUE
	#define EXP_sysfilestreamftell  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamftell", (RTS_UINTPTR)sysfilestreamftell, 1, RTSITF_GET_SIGNATURE(0, 0xAC140163), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamftell
	#define EXT_sysfilestreamftell
	#define GET_sysfilestreamftell(fl)  CAL_CMGETAPI( "sysfilestreamftell" ) 
	#define CAL_sysfilestreamftell  sysfilestreamftell
	#define CHK_sysfilestreamftell  TRUE
	#define EXP_sysfilestreamftell  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamftell", (RTS_UINTPTR)sysfilestreamftell, 1, RTSITF_GET_SIGNATURE(0, 0xAC140163), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamftell
	#define EXT_SysFileStreamsysfilestreamftell
	#define GET_SysFileStreamsysfilestreamftell  ERR_OK
	#define CAL_SysFileStreamsysfilestreamftell  sysfilestreamftell
	#define CHK_SysFileStreamsysfilestreamftell  TRUE
	#define EXP_SysFileStreamsysfilestreamftell  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamftell", (RTS_UINTPTR)sysfilestreamftell, 1, RTSITF_GET_SIGNATURE(0, 0xAC140163), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamftell
	#define EXT_sysfilestreamftell
	#define GET_sysfilestreamftell(fl)  CAL_CMGETAPI( "sysfilestreamftell" ) 
	#define CAL_sysfilestreamftell  sysfilestreamftell
	#define CHK_sysfilestreamftell  TRUE
	#define EXP_sysfilestreamftell  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamftell", (RTS_UINTPTR)sysfilestreamftell, 1, RTSITF_GET_SIGNATURE(0, 0xAC140163), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamftell  PFSYSFILESTREAMFTELL_IEC pfsysfilestreamftell;
	#define EXT_sysfilestreamftell  extern PFSYSFILESTREAMFTELL_IEC pfsysfilestreamftell;
	#define GET_sysfilestreamftell(fl)  s_pfCMGetAPI2( "sysfilestreamftell", (RTS_VOID_FCTPTR *)&pfsysfilestreamftell, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xAC140163), 0x03050000)
	#define CAL_sysfilestreamftell  pfsysfilestreamftell
	#define CHK_sysfilestreamftell  (pfsysfilestreamftell != NULL)
	#define EXP_sysfilestreamftell   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamftell", (RTS_UINTPTR)sysfilestreamftell, 1, RTSITF_GET_SIGNATURE(0, 0xAC140163), 0x03050000) 
#endif


/**
 * <description>sysfilestreamfwrite</description>
 */
typedef struct tagsysfilestreamfwrite_struct
{
	RTS_IEC_BYTE *Buffer;				/* VAR_INPUT */
	RTS_IEC_DWORD Size;					/* VAR_INPUT */
	RTS_IEC_DWORD NObjs;				/* VAR_INPUT */
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DWORD SysFileStreamFWrite;	/* VAR_OUTPUT */
} sysfilestreamfwrite_struct;

void CDECL CDECL_EXT sysfilestreamfwrite(sysfilestreamfwrite_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMFWRITE_IEC) (sysfilestreamfwrite_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFWRITE_NOTIMPLEMENTED)
	#define USE_sysfilestreamfwrite
	#define EXT_sysfilestreamfwrite
	#define GET_sysfilestreamfwrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamfwrite(p0) 
	#define CHK_sysfilestreamfwrite  FALSE
	#define EXP_sysfilestreamfwrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamfwrite
	#define EXT_sysfilestreamfwrite
	#define GET_sysfilestreamfwrite(fl)  CAL_CMGETAPI( "sysfilestreamfwrite" ) 
	#define CAL_sysfilestreamfwrite  sysfilestreamfwrite
	#define CHK_sysfilestreamfwrite  TRUE
	#define EXP_sysfilestreamfwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfwrite", (RTS_UINTPTR)sysfilestreamfwrite, 1, RTSITF_GET_SIGNATURE(0, 0xD0E8E5B8), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamfwrite
	#define EXT_sysfilestreamfwrite
	#define GET_sysfilestreamfwrite(fl)  CAL_CMGETAPI( "sysfilestreamfwrite" ) 
	#define CAL_sysfilestreamfwrite  sysfilestreamfwrite
	#define CHK_sysfilestreamfwrite  TRUE
	#define EXP_sysfilestreamfwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfwrite", (RTS_UINTPTR)sysfilestreamfwrite, 1, RTSITF_GET_SIGNATURE(0, 0xD0E8E5B8), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamfwrite
	#define EXT_SysFileStreamsysfilestreamfwrite
	#define GET_SysFileStreamsysfilestreamfwrite  ERR_OK
	#define CAL_SysFileStreamsysfilestreamfwrite  sysfilestreamfwrite
	#define CHK_SysFileStreamsysfilestreamfwrite  TRUE
	#define EXP_SysFileStreamsysfilestreamfwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfwrite", (RTS_UINTPTR)sysfilestreamfwrite, 1, RTSITF_GET_SIGNATURE(0, 0xD0E8E5B8), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamfwrite
	#define EXT_sysfilestreamfwrite
	#define GET_sysfilestreamfwrite(fl)  CAL_CMGETAPI( "sysfilestreamfwrite" ) 
	#define CAL_sysfilestreamfwrite  sysfilestreamfwrite
	#define CHK_sysfilestreamfwrite  TRUE
	#define EXP_sysfilestreamfwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfwrite", (RTS_UINTPTR)sysfilestreamfwrite, 1, RTSITF_GET_SIGNATURE(0, 0xD0E8E5B8), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamfwrite  PFSYSFILESTREAMFWRITE_IEC pfsysfilestreamfwrite;
	#define EXT_sysfilestreamfwrite  extern PFSYSFILESTREAMFWRITE_IEC pfsysfilestreamfwrite;
	#define GET_sysfilestreamfwrite(fl)  s_pfCMGetAPI2( "sysfilestreamfwrite", (RTS_VOID_FCTPTR *)&pfsysfilestreamfwrite, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD0E8E5B8), 0x03050000)
	#define CAL_sysfilestreamfwrite  pfsysfilestreamfwrite
	#define CHK_sysfilestreamfwrite  (pfsysfilestreamfwrite != NULL)
	#define EXP_sysfilestreamfwrite   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamfwrite", (RTS_UINTPTR)sysfilestreamfwrite, 1, RTSITF_GET_SIGNATURE(0, 0xD0E8E5B8), 0x03050000) 
#endif


/**
 * <description>sysfilestreamremove</description>
 */
typedef struct tagsysfilestreamremove_struct
{
	RTS_IEC_STRING *FileName;			/* VAR_INPUT */
	RTS_IEC_BOOL SysFileStreamRemove;	/* VAR_OUTPUT */
} sysfilestreamremove_struct;

void CDECL CDECL_EXT sysfilestreamremove(sysfilestreamremove_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMREMOVE_IEC) (sysfilestreamremove_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMREMOVE_NOTIMPLEMENTED)
	#define USE_sysfilestreamremove
	#define EXT_sysfilestreamremove
	#define GET_sysfilestreamremove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamremove(p0) 
	#define CHK_sysfilestreamremove  FALSE
	#define EXP_sysfilestreamremove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamremove
	#define EXT_sysfilestreamremove
	#define GET_sysfilestreamremove(fl)  CAL_CMGETAPI( "sysfilestreamremove" ) 
	#define CAL_sysfilestreamremove  sysfilestreamremove
	#define CHK_sysfilestreamremove  TRUE
	#define EXP_sysfilestreamremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamremove", (RTS_UINTPTR)sysfilestreamremove, 1, RTSITF_GET_SIGNATURE(0, 0xD7CA98CE), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamremove
	#define EXT_sysfilestreamremove
	#define GET_sysfilestreamremove(fl)  CAL_CMGETAPI( "sysfilestreamremove" ) 
	#define CAL_sysfilestreamremove  sysfilestreamremove
	#define CHK_sysfilestreamremove  TRUE
	#define EXP_sysfilestreamremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamremove", (RTS_UINTPTR)sysfilestreamremove, 1, RTSITF_GET_SIGNATURE(0, 0xD7CA98CE), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamremove
	#define EXT_SysFileStreamsysfilestreamremove
	#define GET_SysFileStreamsysfilestreamremove  ERR_OK
	#define CAL_SysFileStreamsysfilestreamremove  sysfilestreamremove
	#define CHK_SysFileStreamsysfilestreamremove  TRUE
	#define EXP_SysFileStreamsysfilestreamremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamremove", (RTS_UINTPTR)sysfilestreamremove, 1, RTSITF_GET_SIGNATURE(0, 0xD7CA98CE), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamremove
	#define EXT_sysfilestreamremove
	#define GET_sysfilestreamremove(fl)  CAL_CMGETAPI( "sysfilestreamremove" ) 
	#define CAL_sysfilestreamremove  sysfilestreamremove
	#define CHK_sysfilestreamremove  TRUE
	#define EXP_sysfilestreamremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamremove", (RTS_UINTPTR)sysfilestreamremove, 1, RTSITF_GET_SIGNATURE(0, 0xD7CA98CE), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamremove  PFSYSFILESTREAMREMOVE_IEC pfsysfilestreamremove;
	#define EXT_sysfilestreamremove  extern PFSYSFILESTREAMREMOVE_IEC pfsysfilestreamremove;
	#define GET_sysfilestreamremove(fl)  s_pfCMGetAPI2( "sysfilestreamremove", (RTS_VOID_FCTPTR *)&pfsysfilestreamremove, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD7CA98CE), 0x03050000)
	#define CAL_sysfilestreamremove  pfsysfilestreamremove
	#define CHK_sysfilestreamremove  (pfsysfilestreamremove != NULL)
	#define EXP_sysfilestreamremove   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamremove", (RTS_UINTPTR)sysfilestreamremove, 1, RTSITF_GET_SIGNATURE(0, 0xD7CA98CE), 0x03050000) 
#endif


/**
 * <description>sysfilestreamrename</description>
 */
typedef struct tagsysfilestreamrename_struct
{
	RTS_IEC_STRING *FileOldName;		/* VAR_INPUT */
	RTS_IEC_STRING *FileNewName;		/* VAR_INPUT */
	RTS_IEC_BOOL SysFileStreamRename;	/* VAR_OUTPUT */
} sysfilestreamrename_struct;

void CDECL CDECL_EXT sysfilestreamrename(sysfilestreamrename_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMRENAME_IEC) (sysfilestreamrename_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMRENAME_NOTIMPLEMENTED)
	#define USE_sysfilestreamrename
	#define EXT_sysfilestreamrename
	#define GET_sysfilestreamrename(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamrename(p0) 
	#define CHK_sysfilestreamrename  FALSE
	#define EXP_sysfilestreamrename  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamrename
	#define EXT_sysfilestreamrename
	#define GET_sysfilestreamrename(fl)  CAL_CMGETAPI( "sysfilestreamrename" ) 
	#define CAL_sysfilestreamrename  sysfilestreamrename
	#define CHK_sysfilestreamrename  TRUE
	#define EXP_sysfilestreamrename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamrename", (RTS_UINTPTR)sysfilestreamrename, 1, RTSITF_GET_SIGNATURE(0, 0xBE0E9BBF), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamrename
	#define EXT_sysfilestreamrename
	#define GET_sysfilestreamrename(fl)  CAL_CMGETAPI( "sysfilestreamrename" ) 
	#define CAL_sysfilestreamrename  sysfilestreamrename
	#define CHK_sysfilestreamrename  TRUE
	#define EXP_sysfilestreamrename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamrename", (RTS_UINTPTR)sysfilestreamrename, 1, RTSITF_GET_SIGNATURE(0, 0xBE0E9BBF), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamrename
	#define EXT_SysFileStreamsysfilestreamrename
	#define GET_SysFileStreamsysfilestreamrename  ERR_OK
	#define CAL_SysFileStreamsysfilestreamrename  sysfilestreamrename
	#define CHK_SysFileStreamsysfilestreamrename  TRUE
	#define EXP_SysFileStreamsysfilestreamrename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamrename", (RTS_UINTPTR)sysfilestreamrename, 1, RTSITF_GET_SIGNATURE(0, 0xBE0E9BBF), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamrename
	#define EXT_sysfilestreamrename
	#define GET_sysfilestreamrename(fl)  CAL_CMGETAPI( "sysfilestreamrename" ) 
	#define CAL_sysfilestreamrename  sysfilestreamrename
	#define CHK_sysfilestreamrename  TRUE
	#define EXP_sysfilestreamrename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamrename", (RTS_UINTPTR)sysfilestreamrename, 1, RTSITF_GET_SIGNATURE(0, 0xBE0E9BBF), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamrename  PFSYSFILESTREAMRENAME_IEC pfsysfilestreamrename;
	#define EXT_sysfilestreamrename  extern PFSYSFILESTREAMRENAME_IEC pfsysfilestreamrename;
	#define GET_sysfilestreamrename(fl)  s_pfCMGetAPI2( "sysfilestreamrename", (RTS_VOID_FCTPTR *)&pfsysfilestreamrename, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xBE0E9BBF), 0x03050000)
	#define CAL_sysfilestreamrename  pfsysfilestreamrename
	#define CHK_sysfilestreamrename  (pfsysfilestreamrename != NULL)
	#define EXP_sysfilestreamrename   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamrename", (RTS_UINTPTR)sysfilestreamrename, 1, RTSITF_GET_SIGNATURE(0, 0xBE0E9BBF), 0x03050000) 
#endif


/**
 * <description>sysfilestreamrewind</description>
 */
typedef struct tagsysfilestreamrewind_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamRewind;	/* VAR_OUTPUT */
} sysfilestreamrewind_struct;

void CDECL CDECL_EXT sysfilestreamrewind(sysfilestreamrewind_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSFILESTREAMREWIND_IEC) (sysfilestreamrewind_struct *p);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMREWIND_NOTIMPLEMENTED)
	#define USE_sysfilestreamrewind
	#define EXT_sysfilestreamrewind
	#define GET_sysfilestreamrewind(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysfilestreamrewind(p0) 
	#define CHK_sysfilestreamrewind  FALSE
	#define EXP_sysfilestreamrewind  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysfilestreamrewind
	#define EXT_sysfilestreamrewind
	#define GET_sysfilestreamrewind(fl)  CAL_CMGETAPI( "sysfilestreamrewind" ) 
	#define CAL_sysfilestreamrewind  sysfilestreamrewind
	#define CHK_sysfilestreamrewind  TRUE
	#define EXP_sysfilestreamrewind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamrewind", (RTS_UINTPTR)sysfilestreamrewind, 1, RTSITF_GET_SIGNATURE(0, 0x2C2552D5), 0x03050000) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_sysfilestreamrewind
	#define EXT_sysfilestreamrewind
	#define GET_sysfilestreamrewind(fl)  CAL_CMGETAPI( "sysfilestreamrewind" ) 
	#define CAL_sysfilestreamrewind  sysfilestreamrewind
	#define CHK_sysfilestreamrewind  TRUE
	#define EXP_sysfilestreamrewind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamrewind", (RTS_UINTPTR)sysfilestreamrewind, 1, RTSITF_GET_SIGNATURE(0, 0x2C2552D5), 0x03050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamsysfilestreamrewind
	#define EXT_SysFileStreamsysfilestreamrewind
	#define GET_SysFileStreamsysfilestreamrewind  ERR_OK
	#define CAL_SysFileStreamsysfilestreamrewind  sysfilestreamrewind
	#define CHK_SysFileStreamsysfilestreamrewind  TRUE
	#define EXP_SysFileStreamsysfilestreamrewind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamrewind", (RTS_UINTPTR)sysfilestreamrewind, 1, RTSITF_GET_SIGNATURE(0, 0x2C2552D5), 0x03050000) 
#elif defined(CPLUSPLUS)
	#define USE_sysfilestreamrewind
	#define EXT_sysfilestreamrewind
	#define GET_sysfilestreamrewind(fl)  CAL_CMGETAPI( "sysfilestreamrewind" ) 
	#define CAL_sysfilestreamrewind  sysfilestreamrewind
	#define CHK_sysfilestreamrewind  TRUE
	#define EXP_sysfilestreamrewind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamrewind", (RTS_UINTPTR)sysfilestreamrewind, 1, RTSITF_GET_SIGNATURE(0, 0x2C2552D5), 0x03050000) 
#else /* DYNAMIC_LINK */
	#define USE_sysfilestreamrewind  PFSYSFILESTREAMREWIND_IEC pfsysfilestreamrewind;
	#define EXT_sysfilestreamrewind  extern PFSYSFILESTREAMREWIND_IEC pfsysfilestreamrewind;
	#define GET_sysfilestreamrewind(fl)  s_pfCMGetAPI2( "sysfilestreamrewind", (RTS_VOID_FCTPTR *)&pfsysfilestreamrewind, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2C2552D5), 0x03050000)
	#define CAL_sysfilestreamrewind  pfsysfilestreamrewind
	#define CHK_sysfilestreamrewind  (pfsysfilestreamrewind != NULL)
	#define EXP_sysfilestreamrewind   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysfilestreamrewind", (RTS_UINTPTR)sysfilestreamrewind, 1, RTSITF_GET_SIGNATURE(0, 0x2C2552D5), 0x03050000) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

void* CDECL SysFileStreamFOpen(char *szFileName, char *szMode);
typedef void* (CDECL * PFSYSFILESTREAMFOPEN) (char *szFileName, char *szMode);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFOPEN_NOTIMPLEMENTED)
	#define USE_SysFileStreamFOpen
	#define EXT_SysFileStreamFOpen
	#define GET_SysFileStreamFOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFOpen(p0,p1)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFOpen  FALSE
	#define EXP_SysFileStreamFOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFOpen
	#define EXT_SysFileStreamFOpen
	#define GET_SysFileStreamFOpen(fl)  CAL_CMGETAPI( "SysFileStreamFOpen" ) 
	#define CAL_SysFileStreamFOpen  SysFileStreamFOpen
	#define CHK_SysFileStreamFOpen  TRUE
	#define EXP_SysFileStreamFOpen  CAL_CMEXPAPI( "SysFileStreamFOpen" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFOpen
	#define EXT_SysFileStreamFOpen
	#define GET_SysFileStreamFOpen(fl)  CAL_CMGETAPI( "SysFileStreamFOpen" ) 
	#define CAL_SysFileStreamFOpen  SysFileStreamFOpen
	#define CHK_SysFileStreamFOpen  TRUE
	#define EXP_SysFileStreamFOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFOpen", (RTS_UINTPTR)SysFileStreamFOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFOpen
	#define EXT_SysFileStreamSysFileStreamFOpen
	#define GET_SysFileStreamSysFileStreamFOpen  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFOpen  ((ISysFileStream*)s_pfCMCreateInstance(CLASSID_CSysFileStream, NULL))->ISysFileStreamFOpen
	#define CHK_SysFileStreamSysFileStreamFOpen	(s_pfCMCreateInstance != NULL && pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFOpen
	#define EXT_SysFileStreamFOpen
	#define GET_SysFileStreamFOpen(fl)  CAL_CMGETAPI( "SysFileStreamFOpen" ) 
	#define CAL_SysFileStreamFOpen  ((ISysFileStream*)s_pfCMCreateInstance(CLASSID_CSysFileStream, NULL))->ISysFileStreamFOpen
	#define CHK_SysFileStreamFOpen	(s_pfCMCreateInstance != NULL && pISysFileStream != NULL)
	#define EXP_SysFileStreamFOpen  CAL_CMEXPAPI( "SysFileStreamFOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFOpen  PFSYSFILESTREAMFOPEN pfSysFileStreamFOpen;
	#define EXT_SysFileStreamFOpen  extern PFSYSFILESTREAMFOPEN pfSysFileStreamFOpen;
	#define GET_SysFileStreamFOpen(fl)  s_pfCMGetAPI2( "SysFileStreamFOpen", (RTS_VOID_FCTPTR *)&pfSysFileStreamFOpen, (fl), 0, 0)
	#define CAL_SysFileStreamFOpen  pfSysFileStreamFOpen
	#define CHK_SysFileStreamFOpen  (pfSysFileStreamFOpen != NULL)
	#define EXP_SysFileStreamFOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFOpen", (RTS_UINTPTR)SysFileStreamFOpen, 0, 0) 
#endif



int CDECL SysFileStreamFClose(void *pFile);
typedef int (CDECL * PFSYSFILESTREAMFCLOSE) (void *pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFCLOSE_NOTIMPLEMENTED)
	#define USE_SysFileStreamFClose
	#define EXT_SysFileStreamFClose
	#define GET_SysFileStreamFClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFClose(p0)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFClose  FALSE
	#define EXP_SysFileStreamFClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFClose
	#define EXT_SysFileStreamFClose
	#define GET_SysFileStreamFClose(fl)  CAL_CMGETAPI( "SysFileStreamFClose" ) 
	#define CAL_SysFileStreamFClose  SysFileStreamFClose
	#define CHK_SysFileStreamFClose  TRUE
	#define EXP_SysFileStreamFClose  CAL_CMEXPAPI( "SysFileStreamFClose" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFClose
	#define EXT_SysFileStreamFClose
	#define GET_SysFileStreamFClose(fl)  CAL_CMGETAPI( "SysFileStreamFClose" ) 
	#define CAL_SysFileStreamFClose  SysFileStreamFClose
	#define CHK_SysFileStreamFClose  TRUE
	#define EXP_SysFileStreamFClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFClose", (RTS_UINTPTR)SysFileStreamFClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFClose
	#define EXT_SysFileStreamSysFileStreamFClose
	#define GET_SysFileStreamSysFileStreamFClose  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFClose(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysFileStream*)p0)->ISysFileStreamFClose())
	#define CHK_SysFileStreamSysFileStreamFClose  TRUE
	#define EXP_SysFileStreamSysFileStreamFClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFClose
	#define EXT_SysFileStreamFClose
	#define GET_SysFileStreamFClose(fl)  CAL_CMGETAPI( "SysFileStreamFClose" ) 
	#define CAL_SysFileStreamFClose(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysFileStream*)p0)->ISysFileStreamFClose())
	#define CHK_SysFileStreamFClose  TRUE
	#define EXP_SysFileStreamFClose  CAL_CMEXPAPI( "SysFileStreamFClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFClose  PFSYSFILESTREAMFCLOSE pfSysFileStreamFClose;
	#define EXT_SysFileStreamFClose  extern PFSYSFILESTREAMFCLOSE pfSysFileStreamFClose;
	#define GET_SysFileStreamFClose(fl)  s_pfCMGetAPI2( "SysFileStreamFClose", (RTS_VOID_FCTPTR *)&pfSysFileStreamFClose, (fl), 0, 0)
	#define CAL_SysFileStreamFClose  pfSysFileStreamFClose
	#define CHK_SysFileStreamFClose  (pfSysFileStreamFClose != NULL)
	#define EXP_SysFileStreamFClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFClose", (RTS_UINTPTR)SysFileStreamFClose, 0, 0) 
#endif



int CDECL SysFileStreamFFlush(void *pFile);
typedef int (CDECL * PFSYSFILESTREAMFFLUSH) (void *pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFFLUSH_NOTIMPLEMENTED)
	#define USE_SysFileStreamFFlush
	#define EXT_SysFileStreamFFlush
	#define GET_SysFileStreamFFlush(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFFlush(p0)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFFlush  FALSE
	#define EXP_SysFileStreamFFlush  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFFlush
	#define EXT_SysFileStreamFFlush
	#define GET_SysFileStreamFFlush(fl)  CAL_CMGETAPI( "SysFileStreamFFlush" ) 
	#define CAL_SysFileStreamFFlush  SysFileStreamFFlush
	#define CHK_SysFileStreamFFlush  TRUE
	#define EXP_SysFileStreamFFlush  CAL_CMEXPAPI( "SysFileStreamFFlush" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFFlush
	#define EXT_SysFileStreamFFlush
	#define GET_SysFileStreamFFlush(fl)  CAL_CMGETAPI( "SysFileStreamFFlush" ) 
	#define CAL_SysFileStreamFFlush  SysFileStreamFFlush
	#define CHK_SysFileStreamFFlush  TRUE
	#define EXP_SysFileStreamFFlush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFFlush", (RTS_UINTPTR)SysFileStreamFFlush, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFFlush
	#define EXT_SysFileStreamSysFileStreamFFlush
	#define GET_SysFileStreamSysFileStreamFFlush  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFFlush(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFFlush() : ((ISysFileStream*)p0)->ISysFileStreamFFlush())
	#define CHK_SysFileStreamSysFileStreamFFlush  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFFlush  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFFlush
	#define EXT_SysFileStreamFFlush
	#define GET_SysFileStreamFFlush(fl)  CAL_CMGETAPI( "SysFileStreamFFlush" ) 
	#define CAL_SysFileStreamFFlush(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFFlush() : ((ISysFileStream*)p0)->ISysFileStreamFFlush())
	#define CHK_SysFileStreamFFlush  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFFlush  CAL_CMEXPAPI( "SysFileStreamFFlush" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFFlush  PFSYSFILESTREAMFFLUSH pfSysFileStreamFFlush;
	#define EXT_SysFileStreamFFlush  extern PFSYSFILESTREAMFFLUSH pfSysFileStreamFFlush;
	#define GET_SysFileStreamFFlush(fl)  s_pfCMGetAPI2( "SysFileStreamFFlush", (RTS_VOID_FCTPTR *)&pfSysFileStreamFFlush, (fl), 0, 0)
	#define CAL_SysFileStreamFFlush  pfSysFileStreamFFlush
	#define CHK_SysFileStreamFFlush  (pfSysFileStreamFFlush != NULL)
	#define EXP_SysFileStreamFFlush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFFlush", (RTS_UINTPTR)SysFileStreamFFlush, 0, 0) 
#endif



int CDECL SysFileStreamFPrintf_Int(void *pFile, char *szFormat, int nArg);
typedef int (CDECL * PFSYSFILESTREAMFPRINTF_INT) (void *pFile, char *szFormat, int nArg);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPRINTF_INT_NOTIMPLEMENTED)
	#define USE_SysFileStreamFPrintf_Int
	#define EXT_SysFileStreamFPrintf_Int
	#define GET_SysFileStreamFPrintf_Int(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFPrintf_Int(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFPrintf_Int  FALSE
	#define EXP_SysFileStreamFPrintf_Int  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFPrintf_Int
	#define EXT_SysFileStreamFPrintf_Int
	#define GET_SysFileStreamFPrintf_Int(fl)  CAL_CMGETAPI( "SysFileStreamFPrintf_Int" ) 
	#define CAL_SysFileStreamFPrintf_Int  SysFileStreamFPrintf_Int
	#define CHK_SysFileStreamFPrintf_Int  TRUE
	#define EXP_SysFileStreamFPrintf_Int  CAL_CMEXPAPI( "SysFileStreamFPrintf_Int" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFPrintf_Int
	#define EXT_SysFileStreamFPrintf_Int
	#define GET_SysFileStreamFPrintf_Int(fl)  CAL_CMGETAPI( "SysFileStreamFPrintf_Int" ) 
	#define CAL_SysFileStreamFPrintf_Int  SysFileStreamFPrintf_Int
	#define CHK_SysFileStreamFPrintf_Int  TRUE
	#define EXP_SysFileStreamFPrintf_Int  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPrintf_Int", (RTS_UINTPTR)SysFileStreamFPrintf_Int, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFPrintf_Int
	#define EXT_SysFileStreamSysFileStreamFPrintf_Int
	#define GET_SysFileStreamSysFileStreamFPrintf_Int  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFPrintf_Int(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFPrintf_Int(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFPrintf_Int(p1,p2))
	#define CHK_SysFileStreamSysFileStreamFPrintf_Int  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFPrintf_Int  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFPrintf_Int
	#define EXT_SysFileStreamFPrintf_Int
	#define GET_SysFileStreamFPrintf_Int(fl)  CAL_CMGETAPI( "SysFileStreamFPrintf_Int" ) 
	#define CAL_SysFileStreamFPrintf_Int(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFPrintf_Int(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFPrintf_Int(p1,p2))
	#define CHK_SysFileStreamFPrintf_Int  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFPrintf_Int  CAL_CMEXPAPI( "SysFileStreamFPrintf_Int" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFPrintf_Int  PFSYSFILESTREAMFPRINTF_INT pfSysFileStreamFPrintf_Int;
	#define EXT_SysFileStreamFPrintf_Int  extern PFSYSFILESTREAMFPRINTF_INT pfSysFileStreamFPrintf_Int;
	#define GET_SysFileStreamFPrintf_Int(fl)  s_pfCMGetAPI2( "SysFileStreamFPrintf_Int", (RTS_VOID_FCTPTR *)&pfSysFileStreamFPrintf_Int, (fl), 0, 0)
	#define CAL_SysFileStreamFPrintf_Int  pfSysFileStreamFPrintf_Int
	#define CHK_SysFileStreamFPrintf_Int  (pfSysFileStreamFPrintf_Int != NULL)
	#define EXP_SysFileStreamFPrintf_Int  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPrintf_Int", (RTS_UINTPTR)SysFileStreamFPrintf_Int, 0, 0) 
#endif



int CDECL SysFileStreamFPrintf_Real(void *pFile, char *szFormat, float fArg);
typedef int (CDECL * PFSYSFILESTREAMFPRINTF_REAL) (void *pFile, char *szFormat, float fArg);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPRINTF_REAL_NOTIMPLEMENTED)
	#define USE_SysFileStreamFPrintf_Real
	#define EXT_SysFileStreamFPrintf_Real
	#define GET_SysFileStreamFPrintf_Real(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFPrintf_Real(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFPrintf_Real  FALSE
	#define EXP_SysFileStreamFPrintf_Real  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFPrintf_Real
	#define EXT_SysFileStreamFPrintf_Real
	#define GET_SysFileStreamFPrintf_Real(fl)  CAL_CMGETAPI( "SysFileStreamFPrintf_Real" ) 
	#define CAL_SysFileStreamFPrintf_Real  SysFileStreamFPrintf_Real
	#define CHK_SysFileStreamFPrintf_Real  TRUE
	#define EXP_SysFileStreamFPrintf_Real  CAL_CMEXPAPI( "SysFileStreamFPrintf_Real" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFPrintf_Real
	#define EXT_SysFileStreamFPrintf_Real
	#define GET_SysFileStreamFPrintf_Real(fl)  CAL_CMGETAPI( "SysFileStreamFPrintf_Real" ) 
	#define CAL_SysFileStreamFPrintf_Real  SysFileStreamFPrintf_Real
	#define CHK_SysFileStreamFPrintf_Real  TRUE
	#define EXP_SysFileStreamFPrintf_Real  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPrintf_Real", (RTS_UINTPTR)SysFileStreamFPrintf_Real, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFPrintf_Real
	#define EXT_SysFileStreamSysFileStreamFPrintf_Real
	#define GET_SysFileStreamSysFileStreamFPrintf_Real  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFPrintf_Real(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFPrintf_Real(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFPrintf_Real(p1,p2))
	#define CHK_SysFileStreamSysFileStreamFPrintf_Real  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFPrintf_Real  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFPrintf_Real
	#define EXT_SysFileStreamFPrintf_Real
	#define GET_SysFileStreamFPrintf_Real(fl)  CAL_CMGETAPI( "SysFileStreamFPrintf_Real" ) 
	#define CAL_SysFileStreamFPrintf_Real(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFPrintf_Real(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFPrintf_Real(p1,p2))
	#define CHK_SysFileStreamFPrintf_Real  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFPrintf_Real  CAL_CMEXPAPI( "SysFileStreamFPrintf_Real" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFPrintf_Real  PFSYSFILESTREAMFPRINTF_REAL pfSysFileStreamFPrintf_Real;
	#define EXT_SysFileStreamFPrintf_Real  extern PFSYSFILESTREAMFPRINTF_REAL pfSysFileStreamFPrintf_Real;
	#define GET_SysFileStreamFPrintf_Real(fl)  s_pfCMGetAPI2( "SysFileStreamFPrintf_Real", (RTS_VOID_FCTPTR *)&pfSysFileStreamFPrintf_Real, (fl), 0, 0)
	#define CAL_SysFileStreamFPrintf_Real  pfSysFileStreamFPrintf_Real
	#define CHK_SysFileStreamFPrintf_Real  (pfSysFileStreamFPrintf_Real != NULL)
	#define EXP_SysFileStreamFPrintf_Real  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPrintf_Real", (RTS_UINTPTR)SysFileStreamFPrintf_Real, 0, 0) 
#endif



int CDECL SysFileStreamFPrintf_String(void *pFile, char *szFormat, char *pcArg);
typedef int (CDECL * PFSYSFILESTREAMFPRINTF_STRING) (void *pFile, char *szFormat, char *pcArg);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPRINTF_STRING_NOTIMPLEMENTED)
	#define USE_SysFileStreamFPrintf_String
	#define EXT_SysFileStreamFPrintf_String
	#define GET_SysFileStreamFPrintf_String(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFPrintf_String(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFPrintf_String  FALSE
	#define EXP_SysFileStreamFPrintf_String  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFPrintf_String
	#define EXT_SysFileStreamFPrintf_String
	#define GET_SysFileStreamFPrintf_String(fl)  CAL_CMGETAPI( "SysFileStreamFPrintf_String" ) 
	#define CAL_SysFileStreamFPrintf_String  SysFileStreamFPrintf_String
	#define CHK_SysFileStreamFPrintf_String  TRUE
	#define EXP_SysFileStreamFPrintf_String  CAL_CMEXPAPI( "SysFileStreamFPrintf_String" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFPrintf_String
	#define EXT_SysFileStreamFPrintf_String
	#define GET_SysFileStreamFPrintf_String(fl)  CAL_CMGETAPI( "SysFileStreamFPrintf_String" ) 
	#define CAL_SysFileStreamFPrintf_String  SysFileStreamFPrintf_String
	#define CHK_SysFileStreamFPrintf_String  TRUE
	#define EXP_SysFileStreamFPrintf_String  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPrintf_String", (RTS_UINTPTR)SysFileStreamFPrintf_String, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFPrintf_String
	#define EXT_SysFileStreamSysFileStreamFPrintf_String
	#define GET_SysFileStreamSysFileStreamFPrintf_String  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFPrintf_String(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFPrintf_String(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFPrintf_String(p1,p2))
	#define CHK_SysFileStreamSysFileStreamFPrintf_String  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFPrintf_String  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFPrintf_String
	#define EXT_SysFileStreamFPrintf_String
	#define GET_SysFileStreamFPrintf_String(fl)  CAL_CMGETAPI( "SysFileStreamFPrintf_String" ) 
	#define CAL_SysFileStreamFPrintf_String(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFPrintf_String(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFPrintf_String(p1,p2))
	#define CHK_SysFileStreamFPrintf_String  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFPrintf_String  CAL_CMEXPAPI( "SysFileStreamFPrintf_String" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFPrintf_String  PFSYSFILESTREAMFPRINTF_STRING pfSysFileStreamFPrintf_String;
	#define EXT_SysFileStreamFPrintf_String  extern PFSYSFILESTREAMFPRINTF_STRING pfSysFileStreamFPrintf_String;
	#define GET_SysFileStreamFPrintf_String(fl)  s_pfCMGetAPI2( "SysFileStreamFPrintf_String", (RTS_VOID_FCTPTR *)&pfSysFileStreamFPrintf_String, (fl), 0, 0)
	#define CAL_SysFileStreamFPrintf_String  pfSysFileStreamFPrintf_String
	#define CHK_SysFileStreamFPrintf_String  (pfSysFileStreamFPrintf_String != NULL)
	#define EXP_SysFileStreamFPrintf_String  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPrintf_String", (RTS_UINTPTR)SysFileStreamFPrintf_String, 0, 0) 
#endif



int CDECL SysFileStreamFScanf_Int(void *pFile, char *szFormat, int *pnArg);
typedef int (CDECL * PFSYSFILESTREAMFSCANF_INT) (void *pFile, char *szFormat, int *pnArg);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFSCANF_INT_NOTIMPLEMENTED)
	#define USE_SysFileStreamFScanf_Int
	#define EXT_SysFileStreamFScanf_Int
	#define GET_SysFileStreamFScanf_Int(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFScanf_Int(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFScanf_Int  FALSE
	#define EXP_SysFileStreamFScanf_Int  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFScanf_Int
	#define EXT_SysFileStreamFScanf_Int
	#define GET_SysFileStreamFScanf_Int(fl)  CAL_CMGETAPI( "SysFileStreamFScanf_Int" ) 
	#define CAL_SysFileStreamFScanf_Int  SysFileStreamFScanf_Int
	#define CHK_SysFileStreamFScanf_Int  TRUE
	#define EXP_SysFileStreamFScanf_Int  CAL_CMEXPAPI( "SysFileStreamFScanf_Int" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFScanf_Int
	#define EXT_SysFileStreamFScanf_Int
	#define GET_SysFileStreamFScanf_Int(fl)  CAL_CMGETAPI( "SysFileStreamFScanf_Int" ) 
	#define CAL_SysFileStreamFScanf_Int  SysFileStreamFScanf_Int
	#define CHK_SysFileStreamFScanf_Int  TRUE
	#define EXP_SysFileStreamFScanf_Int  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFScanf_Int", (RTS_UINTPTR)SysFileStreamFScanf_Int, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFScanf_Int
	#define EXT_SysFileStreamSysFileStreamFScanf_Int
	#define GET_SysFileStreamSysFileStreamFScanf_Int  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFScanf_Int(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFScanf_Int(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFScanf_Int(p1,p2))
	#define CHK_SysFileStreamSysFileStreamFScanf_Int  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFScanf_Int  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFScanf_Int
	#define EXT_SysFileStreamFScanf_Int
	#define GET_SysFileStreamFScanf_Int(fl)  CAL_CMGETAPI( "SysFileStreamFScanf_Int" ) 
	#define CAL_SysFileStreamFScanf_Int(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFScanf_Int(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFScanf_Int(p1,p2))
	#define CHK_SysFileStreamFScanf_Int  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFScanf_Int  CAL_CMEXPAPI( "SysFileStreamFScanf_Int" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFScanf_Int  PFSYSFILESTREAMFSCANF_INT pfSysFileStreamFScanf_Int;
	#define EXT_SysFileStreamFScanf_Int  extern PFSYSFILESTREAMFSCANF_INT pfSysFileStreamFScanf_Int;
	#define GET_SysFileStreamFScanf_Int(fl)  s_pfCMGetAPI2( "SysFileStreamFScanf_Int", (RTS_VOID_FCTPTR *)&pfSysFileStreamFScanf_Int, (fl), 0, 0)
	#define CAL_SysFileStreamFScanf_Int  pfSysFileStreamFScanf_Int
	#define CHK_SysFileStreamFScanf_Int  (pfSysFileStreamFScanf_Int != NULL)
	#define EXP_SysFileStreamFScanf_Int  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFScanf_Int", (RTS_UINTPTR)SysFileStreamFScanf_Int, 0, 0) 
#endif



int CDECL SysFileStreamFScanf_Real(void *pFile, char *szFormat, float *pfArg);
typedef int (CDECL * PFSYSFILESTREAMFSCANF_REAL) (void *pFile, char *szFormat, float *pfArg);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFSCANF_REAL_NOTIMPLEMENTED)
	#define USE_SysFileStreamFScanf_Real
	#define EXT_SysFileStreamFScanf_Real
	#define GET_SysFileStreamFScanf_Real(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFScanf_Real(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFScanf_Real  FALSE
	#define EXP_SysFileStreamFScanf_Real  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFScanf_Real
	#define EXT_SysFileStreamFScanf_Real
	#define GET_SysFileStreamFScanf_Real(fl)  CAL_CMGETAPI( "SysFileStreamFScanf_Real" ) 
	#define CAL_SysFileStreamFScanf_Real  SysFileStreamFScanf_Real
	#define CHK_SysFileStreamFScanf_Real  TRUE
	#define EXP_SysFileStreamFScanf_Real  CAL_CMEXPAPI( "SysFileStreamFScanf_Real" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFScanf_Real
	#define EXT_SysFileStreamFScanf_Real
	#define GET_SysFileStreamFScanf_Real(fl)  CAL_CMGETAPI( "SysFileStreamFScanf_Real" ) 
	#define CAL_SysFileStreamFScanf_Real  SysFileStreamFScanf_Real
	#define CHK_SysFileStreamFScanf_Real  TRUE
	#define EXP_SysFileStreamFScanf_Real  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFScanf_Real", (RTS_UINTPTR)SysFileStreamFScanf_Real, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFScanf_Real
	#define EXT_SysFileStreamSysFileStreamFScanf_Real
	#define GET_SysFileStreamSysFileStreamFScanf_Real  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFScanf_Real(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFScanf_Real(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFScanf_Real(p1,p2))
	#define CHK_SysFileStreamSysFileStreamFScanf_Real  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFScanf_Real  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFScanf_Real
	#define EXT_SysFileStreamFScanf_Real
	#define GET_SysFileStreamFScanf_Real(fl)  CAL_CMGETAPI( "SysFileStreamFScanf_Real" ) 
	#define CAL_SysFileStreamFScanf_Real(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFScanf_Real(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFScanf_Real(p1,p2))
	#define CHK_SysFileStreamFScanf_Real  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFScanf_Real  CAL_CMEXPAPI( "SysFileStreamFScanf_Real" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFScanf_Real  PFSYSFILESTREAMFSCANF_REAL pfSysFileStreamFScanf_Real;
	#define EXT_SysFileStreamFScanf_Real  extern PFSYSFILESTREAMFSCANF_REAL pfSysFileStreamFScanf_Real;
	#define GET_SysFileStreamFScanf_Real(fl)  s_pfCMGetAPI2( "SysFileStreamFScanf_Real", (RTS_VOID_FCTPTR *)&pfSysFileStreamFScanf_Real, (fl), 0, 0)
	#define CAL_SysFileStreamFScanf_Real  pfSysFileStreamFScanf_Real
	#define CHK_SysFileStreamFScanf_Real  (pfSysFileStreamFScanf_Real != NULL)
	#define EXP_SysFileStreamFScanf_Real  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFScanf_Real", (RTS_UINTPTR)SysFileStreamFScanf_Real, 0, 0) 
#endif



int CDECL SysFileStreamFScanf_String(void *pFile, char *szFormat, char *pcArg);
typedef int (CDECL * PFSYSFILESTREAMFSCANF_STRING) (void *pFile, char *szFormat, char *pcArg);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFSCANF_STRING_NOTIMPLEMENTED)
	#define USE_SysFileStreamFScanf_String
	#define EXT_SysFileStreamFScanf_String
	#define GET_SysFileStreamFScanf_String(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFScanf_String(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFScanf_String  FALSE
	#define EXP_SysFileStreamFScanf_String  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFScanf_String
	#define EXT_SysFileStreamFScanf_String
	#define GET_SysFileStreamFScanf_String(fl)  CAL_CMGETAPI( "SysFileStreamFScanf_String" ) 
	#define CAL_SysFileStreamFScanf_String  SysFileStreamFScanf_String
	#define CHK_SysFileStreamFScanf_String  TRUE
	#define EXP_SysFileStreamFScanf_String  CAL_CMEXPAPI( "SysFileStreamFScanf_String" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFScanf_String
	#define EXT_SysFileStreamFScanf_String
	#define GET_SysFileStreamFScanf_String(fl)  CAL_CMGETAPI( "SysFileStreamFScanf_String" ) 
	#define CAL_SysFileStreamFScanf_String  SysFileStreamFScanf_String
	#define CHK_SysFileStreamFScanf_String  TRUE
	#define EXP_SysFileStreamFScanf_String  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFScanf_String", (RTS_UINTPTR)SysFileStreamFScanf_String, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFScanf_String
	#define EXT_SysFileStreamSysFileStreamFScanf_String
	#define GET_SysFileStreamSysFileStreamFScanf_String  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFScanf_String(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFScanf_String(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFScanf_String(p1,p2))
	#define CHK_SysFileStreamSysFileStreamFScanf_String  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFScanf_String  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFScanf_String
	#define EXT_SysFileStreamFScanf_String
	#define GET_SysFileStreamFScanf_String(fl)  CAL_CMGETAPI( "SysFileStreamFScanf_String" ) 
	#define CAL_SysFileStreamFScanf_String(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFScanf_String(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFScanf_String(p1,p2))
	#define CHK_SysFileStreamFScanf_String  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFScanf_String  CAL_CMEXPAPI( "SysFileStreamFScanf_String" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFScanf_String  PFSYSFILESTREAMFSCANF_STRING pfSysFileStreamFScanf_String;
	#define EXT_SysFileStreamFScanf_String  extern PFSYSFILESTREAMFSCANF_STRING pfSysFileStreamFScanf_String;
	#define GET_SysFileStreamFScanf_String(fl)  s_pfCMGetAPI2( "SysFileStreamFScanf_String", (RTS_VOID_FCTPTR *)&pfSysFileStreamFScanf_String, (fl), 0, 0)
	#define CAL_SysFileStreamFScanf_String  pfSysFileStreamFScanf_String
	#define CHK_SysFileStreamFScanf_String  (pfSysFileStreamFScanf_String != NULL)
	#define EXP_SysFileStreamFScanf_String  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFScanf_String", (RTS_UINTPTR)SysFileStreamFScanf_String, 0, 0) 
#endif



int CDECL SysFileStreamFGetC(void *pFile);
typedef int (CDECL * PFSYSFILESTREAMFGETC) (void *pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFGETC_NOTIMPLEMENTED)
	#define USE_SysFileStreamFGetC
	#define EXT_SysFileStreamFGetC
	#define GET_SysFileStreamFGetC(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFGetC(p0)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFGetC  FALSE
	#define EXP_SysFileStreamFGetC  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFGetC
	#define EXT_SysFileStreamFGetC
	#define GET_SysFileStreamFGetC(fl)  CAL_CMGETAPI( "SysFileStreamFGetC" ) 
	#define CAL_SysFileStreamFGetC  SysFileStreamFGetC
	#define CHK_SysFileStreamFGetC  TRUE
	#define EXP_SysFileStreamFGetC  CAL_CMEXPAPI( "SysFileStreamFGetC" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFGetC
	#define EXT_SysFileStreamFGetC
	#define GET_SysFileStreamFGetC(fl)  CAL_CMGETAPI( "SysFileStreamFGetC" ) 
	#define CAL_SysFileStreamFGetC  SysFileStreamFGetC
	#define CHK_SysFileStreamFGetC  TRUE
	#define EXP_SysFileStreamFGetC  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFGetC", (RTS_UINTPTR)SysFileStreamFGetC, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFGetC
	#define EXT_SysFileStreamSysFileStreamFGetC
	#define GET_SysFileStreamSysFileStreamFGetC  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFGetC(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFGetC() : ((ISysFileStream*)p0)->ISysFileStreamFGetC())
	#define CHK_SysFileStreamSysFileStreamFGetC  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFGetC  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFGetC
	#define EXT_SysFileStreamFGetC
	#define GET_SysFileStreamFGetC(fl)  CAL_CMGETAPI( "SysFileStreamFGetC" ) 
	#define CAL_SysFileStreamFGetC(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFGetC() : ((ISysFileStream*)p0)->ISysFileStreamFGetC())
	#define CHK_SysFileStreamFGetC  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFGetC  CAL_CMEXPAPI( "SysFileStreamFGetC" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFGetC  PFSYSFILESTREAMFGETC pfSysFileStreamFGetC;
	#define EXT_SysFileStreamFGetC  extern PFSYSFILESTREAMFGETC pfSysFileStreamFGetC;
	#define GET_SysFileStreamFGetC(fl)  s_pfCMGetAPI2( "SysFileStreamFGetC", (RTS_VOID_FCTPTR *)&pfSysFileStreamFGetC, (fl), 0, 0)
	#define CAL_SysFileStreamFGetC  pfSysFileStreamFGetC
	#define CHK_SysFileStreamFGetC  (pfSysFileStreamFGetC != NULL)
	#define EXP_SysFileStreamFGetC  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFGetC", (RTS_UINTPTR)SysFileStreamFGetC, 0, 0) 
#endif



int CDECL SysFileStreamFPutc(int c, void *pFile);
typedef int (CDECL * PFSYSFILESTREAMFPUTC) (int c, void *pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPUTC_NOTIMPLEMENTED)
	#define USE_SysFileStreamFPutc
	#define EXT_SysFileStreamFPutc
	#define GET_SysFileStreamFPutc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFPutc(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFPutc  FALSE
	#define EXP_SysFileStreamFPutc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFPutc
	#define EXT_SysFileStreamFPutc
	#define GET_SysFileStreamFPutc(fl)  CAL_CMGETAPI( "SysFileStreamFPutc" ) 
	#define CAL_SysFileStreamFPutc  SysFileStreamFPutc
	#define CHK_SysFileStreamFPutc  TRUE
	#define EXP_SysFileStreamFPutc  CAL_CMEXPAPI( "SysFileStreamFPutc" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFPutc
	#define EXT_SysFileStreamFPutc
	#define GET_SysFileStreamFPutc(fl)  CAL_CMGETAPI( "SysFileStreamFPutc" ) 
	#define CAL_SysFileStreamFPutc  SysFileStreamFPutc
	#define CHK_SysFileStreamFPutc  TRUE
	#define EXP_SysFileStreamFPutc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPutc", (RTS_UINTPTR)SysFileStreamFPutc, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFPutc
	#define EXT_SysFileStreamSysFileStreamFPutc
	#define GET_SysFileStreamSysFileStreamFPutc  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFPutc pISysFileStream->ISysFileStreamFPutc
	#define CHK_SysFileStreamSysFileStreamFPutc (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFPutc  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFPutc
	#define EXT_SysFileStreamFPutc
	#define GET_SysFileStreamFPutc(fl)  CAL_CMGETAPI( "SysFileStreamFPutc" ) 
	#define CAL_SysFileStreamFPutc pISysFileStream->ISysFileStreamFPutc
	#define CHK_SysFileStreamFPutc (pISysFileStream != NULL)
	#define EXP_SysFileStreamFPutc  CAL_CMEXPAPI( "SysFileStreamFPutc" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFPutc  PFSYSFILESTREAMFPUTC pfSysFileStreamFPutc;
	#define EXT_SysFileStreamFPutc  extern PFSYSFILESTREAMFPUTC pfSysFileStreamFPutc;
	#define GET_SysFileStreamFPutc(fl)  s_pfCMGetAPI2( "SysFileStreamFPutc", (RTS_VOID_FCTPTR *)&pfSysFileStreamFPutc, (fl), 0, 0)
	#define CAL_SysFileStreamFPutc  pfSysFileStreamFPutc
	#define CHK_SysFileStreamFPutc  (pfSysFileStreamFPutc != NULL)
	#define EXP_SysFileStreamFPutc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPutc", (RTS_UINTPTR)SysFileStreamFPutc, 0, 0) 
#endif



int CDECL SysFileStreamFPutc2(void *pFile, int c);
typedef int (CDECL * PFSYSFILESTREAMFPUTC2) (void *pFile, int c);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPUTC2_NOTIMPLEMENTED)
	#define USE_SysFileStreamFPutc2
	#define EXT_SysFileStreamFPutc2
	#define GET_SysFileStreamFPutc2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFPutc2(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFPutc2  FALSE
	#define EXP_SysFileStreamFPutc2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFPutc2
	#define EXT_SysFileStreamFPutc2
	#define GET_SysFileStreamFPutc2(fl)  CAL_CMGETAPI( "SysFileStreamFPutc2" ) 
	#define CAL_SysFileStreamFPutc2  SysFileStreamFPutc2
	#define CHK_SysFileStreamFPutc2  TRUE
	#define EXP_SysFileStreamFPutc2  CAL_CMEXPAPI( "SysFileStreamFPutc2" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFPutc2
	#define EXT_SysFileStreamFPutc2
	#define GET_SysFileStreamFPutc2(fl)  CAL_CMGETAPI( "SysFileStreamFPutc2" ) 
	#define CAL_SysFileStreamFPutc2  SysFileStreamFPutc2
	#define CHK_SysFileStreamFPutc2  TRUE
	#define EXP_SysFileStreamFPutc2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPutc2", (RTS_UINTPTR)SysFileStreamFPutc2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFPutc2
	#define EXT_SysFileStreamSysFileStreamFPutc2
	#define GET_SysFileStreamSysFileStreamFPutc2  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFPutc2(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFPutc2(p1) : ((ISysFileStream*)p0)->ISysFileStreamFPutc2(p1))
	#define CHK_SysFileStreamSysFileStreamFPutc2  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFPutc2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFPutc2
	#define EXT_SysFileStreamFPutc2
	#define GET_SysFileStreamFPutc2(fl)  CAL_CMGETAPI( "SysFileStreamFPutc2" ) 
	#define CAL_SysFileStreamFPutc2(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFPutc2(p1) : ((ISysFileStream*)p0)->ISysFileStreamFPutc2(p1))
	#define CHK_SysFileStreamFPutc2  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFPutc2  CAL_CMEXPAPI( "SysFileStreamFPutc2" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFPutc2  PFSYSFILESTREAMFPUTC2 pfSysFileStreamFPutc2;
	#define EXT_SysFileStreamFPutc2  extern PFSYSFILESTREAMFPUTC2 pfSysFileStreamFPutc2;
	#define GET_SysFileStreamFPutc2(fl)  s_pfCMGetAPI2( "SysFileStreamFPutc2", (RTS_VOID_FCTPTR *)&pfSysFileStreamFPutc2, (fl), 0, 0)
	#define CAL_SysFileStreamFPutc2  pfSysFileStreamFPutc2
	#define CHK_SysFileStreamFPutc2  (pfSysFileStreamFPutc2 != NULL)
	#define EXP_SysFileStreamFPutc2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPutc2", (RTS_UINTPTR)SysFileStreamFPutc2, 0, 0) 
#endif



char* CDECL SysFileStreamFGetS(char *pcDest, int n, void* pFile);
typedef char* (CDECL * PFSYSFILESTREAMFGETS) (char *pcDest, int n, void* pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFGETS_NOTIMPLEMENTED)
	#define USE_SysFileStreamFGetS
	#define EXT_SysFileStreamFGetS
	#define GET_SysFileStreamFGetS(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFGetS(p0,p1,p2)  (char*)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFGetS  FALSE
	#define EXP_SysFileStreamFGetS  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFGetS
	#define EXT_SysFileStreamFGetS
	#define GET_SysFileStreamFGetS(fl)  CAL_CMGETAPI( "SysFileStreamFGetS" ) 
	#define CAL_SysFileStreamFGetS  SysFileStreamFGetS
	#define CHK_SysFileStreamFGetS  TRUE
	#define EXP_SysFileStreamFGetS  CAL_CMEXPAPI( "SysFileStreamFGetS" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFGetS
	#define EXT_SysFileStreamFGetS
	#define GET_SysFileStreamFGetS(fl)  CAL_CMGETAPI( "SysFileStreamFGetS" ) 
	#define CAL_SysFileStreamFGetS  SysFileStreamFGetS
	#define CHK_SysFileStreamFGetS  TRUE
	#define EXP_SysFileStreamFGetS  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFGetS", (RTS_UINTPTR)SysFileStreamFGetS, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFGetS
	#define EXT_SysFileStreamSysFileStreamFGetS
	#define GET_SysFileStreamSysFileStreamFGetS  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFGetS pISysFileStream->ISysFileStreamFGetS
	#define CHK_SysFileStreamSysFileStreamFGetS (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFGetS  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFGetS
	#define EXT_SysFileStreamFGetS
	#define GET_SysFileStreamFGetS(fl)  CAL_CMGETAPI( "SysFileStreamFGetS" ) 
	#define CAL_SysFileStreamFGetS pISysFileStream->ISysFileStreamFGetS
	#define CHK_SysFileStreamFGetS (pISysFileStream != NULL)
	#define EXP_SysFileStreamFGetS  CAL_CMEXPAPI( "SysFileStreamFGetS" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFGetS  PFSYSFILESTREAMFGETS pfSysFileStreamFGetS;
	#define EXT_SysFileStreamFGetS  extern PFSYSFILESTREAMFGETS pfSysFileStreamFGetS;
	#define GET_SysFileStreamFGetS(fl)  s_pfCMGetAPI2( "SysFileStreamFGetS", (RTS_VOID_FCTPTR *)&pfSysFileStreamFGetS, (fl), 0, 0)
	#define CAL_SysFileStreamFGetS  pfSysFileStreamFGetS
	#define CHK_SysFileStreamFGetS  (pfSysFileStreamFGetS != NULL)
	#define EXP_SysFileStreamFGetS  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFGetS", (RTS_UINTPTR)SysFileStreamFGetS, 0, 0) 
#endif



char* CDECL SysFileStreamFGetS2(void* pFile, char *pcDest, int n);
typedef char* (CDECL * PFSYSFILESTREAMFGETS2) (void* pFile, char *pcDest, int n);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFGETS2_NOTIMPLEMENTED)
	#define USE_SysFileStreamFGetS2
	#define EXT_SysFileStreamFGetS2
	#define GET_SysFileStreamFGetS2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFGetS2(p0,p1,p2)  (char*)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFGetS2  FALSE
	#define EXP_SysFileStreamFGetS2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFGetS2
	#define EXT_SysFileStreamFGetS2
	#define GET_SysFileStreamFGetS2(fl)  CAL_CMGETAPI( "SysFileStreamFGetS2" ) 
	#define CAL_SysFileStreamFGetS2  SysFileStreamFGetS2
	#define CHK_SysFileStreamFGetS2  TRUE
	#define EXP_SysFileStreamFGetS2  CAL_CMEXPAPI( "SysFileStreamFGetS2" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFGetS2
	#define EXT_SysFileStreamFGetS2
	#define GET_SysFileStreamFGetS2(fl)  CAL_CMGETAPI( "SysFileStreamFGetS2" ) 
	#define CAL_SysFileStreamFGetS2  SysFileStreamFGetS2
	#define CHK_SysFileStreamFGetS2  TRUE
	#define EXP_SysFileStreamFGetS2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFGetS2", (RTS_UINTPTR)SysFileStreamFGetS2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFGetS2
	#define EXT_SysFileStreamSysFileStreamFGetS2
	#define GET_SysFileStreamSysFileStreamFGetS2  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFGetS2(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFGetS2(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFGetS2(p1,p2))
	#define CHK_SysFileStreamSysFileStreamFGetS2  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFGetS2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFGetS2
	#define EXT_SysFileStreamFGetS2
	#define GET_SysFileStreamFGetS2(fl)  CAL_CMGETAPI( "SysFileStreamFGetS2" ) 
	#define CAL_SysFileStreamFGetS2(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFGetS2(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFGetS2(p1,p2))
	#define CHK_SysFileStreamFGetS2  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFGetS2  CAL_CMEXPAPI( "SysFileStreamFGetS2" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFGetS2  PFSYSFILESTREAMFGETS2 pfSysFileStreamFGetS2;
	#define EXT_SysFileStreamFGetS2  extern PFSYSFILESTREAMFGETS2 pfSysFileStreamFGetS2;
	#define GET_SysFileStreamFGetS2(fl)  s_pfCMGetAPI2( "SysFileStreamFGetS2", (RTS_VOID_FCTPTR *)&pfSysFileStreamFGetS2, (fl), 0, 0)
	#define CAL_SysFileStreamFGetS2  pfSysFileStreamFGetS2
	#define CHK_SysFileStreamFGetS2  (pfSysFileStreamFGetS2 != NULL)
	#define EXP_SysFileStreamFGetS2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFGetS2", (RTS_UINTPTR)SysFileStreamFGetS2, 0, 0) 
#endif



int CDECL SysFileStreamFPutS(char* pcSource, void* pFile);
typedef int (CDECL * PFSYSFILESTREAMFPUTS) (char* pcSource, void* pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPUTS_NOTIMPLEMENTED)
	#define USE_SysFileStreamFPutS
	#define EXT_SysFileStreamFPutS
	#define GET_SysFileStreamFPutS(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFPutS(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFPutS  FALSE
	#define EXP_SysFileStreamFPutS  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFPutS
	#define EXT_SysFileStreamFPutS
	#define GET_SysFileStreamFPutS(fl)  CAL_CMGETAPI( "SysFileStreamFPutS" ) 
	#define CAL_SysFileStreamFPutS  SysFileStreamFPutS
	#define CHK_SysFileStreamFPutS  TRUE
	#define EXP_SysFileStreamFPutS  CAL_CMEXPAPI( "SysFileStreamFPutS" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFPutS
	#define EXT_SysFileStreamFPutS
	#define GET_SysFileStreamFPutS(fl)  CAL_CMGETAPI( "SysFileStreamFPutS" ) 
	#define CAL_SysFileStreamFPutS  SysFileStreamFPutS
	#define CHK_SysFileStreamFPutS  TRUE
	#define EXP_SysFileStreamFPutS  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPutS", (RTS_UINTPTR)SysFileStreamFPutS, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFPutS
	#define EXT_SysFileStreamSysFileStreamFPutS
	#define GET_SysFileStreamSysFileStreamFPutS  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFPutS pISysFileStream->ISysFileStreamFPutS
	#define CHK_SysFileStreamSysFileStreamFPutS (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFPutS  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFPutS
	#define EXT_SysFileStreamFPutS
	#define GET_SysFileStreamFPutS(fl)  CAL_CMGETAPI( "SysFileStreamFPutS" ) 
	#define CAL_SysFileStreamFPutS pISysFileStream->ISysFileStreamFPutS
	#define CHK_SysFileStreamFPutS (pISysFileStream != NULL)
	#define EXP_SysFileStreamFPutS  CAL_CMEXPAPI( "SysFileStreamFPutS" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFPutS  PFSYSFILESTREAMFPUTS pfSysFileStreamFPutS;
	#define EXT_SysFileStreamFPutS  extern PFSYSFILESTREAMFPUTS pfSysFileStreamFPutS;
	#define GET_SysFileStreamFPutS(fl)  s_pfCMGetAPI2( "SysFileStreamFPutS", (RTS_VOID_FCTPTR *)&pfSysFileStreamFPutS, (fl), 0, 0)
	#define CAL_SysFileStreamFPutS  pfSysFileStreamFPutS
	#define CHK_SysFileStreamFPutS  (pfSysFileStreamFPutS != NULL)
	#define EXP_SysFileStreamFPutS  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPutS", (RTS_UINTPTR)SysFileStreamFPutS, 0, 0) 
#endif



int CDECL SysFileStreamFPutS2(void* pFile, char* pcSource);
typedef int (CDECL * PFSYSFILESTREAMFPUTS2) (void* pFile, char* pcSource);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFPUTS2_NOTIMPLEMENTED)
	#define USE_SysFileStreamFPutS2
	#define EXT_SysFileStreamFPutS2
	#define GET_SysFileStreamFPutS2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFPutS2(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFPutS2  FALSE
	#define EXP_SysFileStreamFPutS2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFPutS2
	#define EXT_SysFileStreamFPutS2
	#define GET_SysFileStreamFPutS2(fl)  CAL_CMGETAPI( "SysFileStreamFPutS2" ) 
	#define CAL_SysFileStreamFPutS2  SysFileStreamFPutS2
	#define CHK_SysFileStreamFPutS2  TRUE
	#define EXP_SysFileStreamFPutS2  CAL_CMEXPAPI( "SysFileStreamFPutS2" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFPutS2
	#define EXT_SysFileStreamFPutS2
	#define GET_SysFileStreamFPutS2(fl)  CAL_CMGETAPI( "SysFileStreamFPutS2" ) 
	#define CAL_SysFileStreamFPutS2  SysFileStreamFPutS2
	#define CHK_SysFileStreamFPutS2  TRUE
	#define EXP_SysFileStreamFPutS2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPutS2", (RTS_UINTPTR)SysFileStreamFPutS2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFPutS2
	#define EXT_SysFileStreamSysFileStreamFPutS2
	#define GET_SysFileStreamSysFileStreamFPutS2  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFPutS2(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFPutS2(p1) : ((ISysFileStream*)p0)->ISysFileStreamFPutS2(p1))
	#define CHK_SysFileStreamSysFileStreamFPutS2  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFPutS2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFPutS2
	#define EXT_SysFileStreamFPutS2
	#define GET_SysFileStreamFPutS2(fl)  CAL_CMGETAPI( "SysFileStreamFPutS2" ) 
	#define CAL_SysFileStreamFPutS2(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFPutS2(p1) : ((ISysFileStream*)p0)->ISysFileStreamFPutS2(p1))
	#define CHK_SysFileStreamFPutS2  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFPutS2  CAL_CMEXPAPI( "SysFileStreamFPutS2" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFPutS2  PFSYSFILESTREAMFPUTS2 pfSysFileStreamFPutS2;
	#define EXT_SysFileStreamFPutS2  extern PFSYSFILESTREAMFPUTS2 pfSysFileStreamFPutS2;
	#define GET_SysFileStreamFPutS2(fl)  s_pfCMGetAPI2( "SysFileStreamFPutS2", (RTS_VOID_FCTPTR *)&pfSysFileStreamFPutS2, (fl), 0, 0)
	#define CAL_SysFileStreamFPutS2  pfSysFileStreamFPutS2
	#define CHK_SysFileStreamFPutS2  (pfSysFileStreamFPutS2 != NULL)
	#define EXP_SysFileStreamFPutS2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFPutS2", (RTS_UINTPTR)SysFileStreamFPutS2, 0, 0) 
#endif



unsigned int CDECL SysFileStreamFRead(void *pDest, unsigned int uiSize, unsigned int uiNObjs, void *pFile);
typedef unsigned int (CDECL * PFSYSFILESTREAMFREAD) (void *pDest, unsigned int uiSize, unsigned int uiNObjs, void *pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFREAD_NOTIMPLEMENTED)
	#define USE_SysFileStreamFRead
	#define EXT_SysFileStreamFRead
	#define GET_SysFileStreamFRead(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFRead(p0,p1,p2,p3)  (unsigned int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFRead  FALSE
	#define EXP_SysFileStreamFRead  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFRead
	#define EXT_SysFileStreamFRead
	#define GET_SysFileStreamFRead(fl)  CAL_CMGETAPI( "SysFileStreamFRead" ) 
	#define CAL_SysFileStreamFRead  SysFileStreamFRead
	#define CHK_SysFileStreamFRead  TRUE
	#define EXP_SysFileStreamFRead  CAL_CMEXPAPI( "SysFileStreamFRead" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFRead
	#define EXT_SysFileStreamFRead
	#define GET_SysFileStreamFRead(fl)  CAL_CMGETAPI( "SysFileStreamFRead" ) 
	#define CAL_SysFileStreamFRead  SysFileStreamFRead
	#define CHK_SysFileStreamFRead  TRUE
	#define EXP_SysFileStreamFRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFRead", (RTS_UINTPTR)SysFileStreamFRead, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFRead
	#define EXT_SysFileStreamSysFileStreamFRead
	#define GET_SysFileStreamSysFileStreamFRead  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFRead pISysFileStream->ISysFileStreamFRead
	#define CHK_SysFileStreamSysFileStreamFRead (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFRead  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFRead
	#define EXT_SysFileStreamFRead
	#define GET_SysFileStreamFRead(fl)  CAL_CMGETAPI( "SysFileStreamFRead" ) 
	#define CAL_SysFileStreamFRead pISysFileStream->ISysFileStreamFRead
	#define CHK_SysFileStreamFRead (pISysFileStream != NULL)
	#define EXP_SysFileStreamFRead  CAL_CMEXPAPI( "SysFileStreamFRead" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFRead  PFSYSFILESTREAMFREAD pfSysFileStreamFRead;
	#define EXT_SysFileStreamFRead  extern PFSYSFILESTREAMFREAD pfSysFileStreamFRead;
	#define GET_SysFileStreamFRead(fl)  s_pfCMGetAPI2( "SysFileStreamFRead", (RTS_VOID_FCTPTR *)&pfSysFileStreamFRead, (fl), 0, 0)
	#define CAL_SysFileStreamFRead  pfSysFileStreamFRead
	#define CHK_SysFileStreamFRead  (pfSysFileStreamFRead != NULL)
	#define EXP_SysFileStreamFRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFRead", (RTS_UINTPTR)SysFileStreamFRead, 0, 0) 
#endif



unsigned int CDECL SysFileStreamFRead2(void *pFile, void *pDest, unsigned int uiSize, unsigned int uiNObjs);
typedef unsigned int (CDECL * PFSYSFILESTREAMFREAD2) (void *pFile, void *pDest, unsigned int uiSize, unsigned int uiNObjs);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFREAD2_NOTIMPLEMENTED)
	#define USE_SysFileStreamFRead2
	#define EXT_SysFileStreamFRead2
	#define GET_SysFileStreamFRead2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFRead2(p0,p1,p2,p3)  (unsigned int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFRead2  FALSE
	#define EXP_SysFileStreamFRead2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFRead2
	#define EXT_SysFileStreamFRead2
	#define GET_SysFileStreamFRead2(fl)  CAL_CMGETAPI( "SysFileStreamFRead2" ) 
	#define CAL_SysFileStreamFRead2  SysFileStreamFRead2
	#define CHK_SysFileStreamFRead2  TRUE
	#define EXP_SysFileStreamFRead2  CAL_CMEXPAPI( "SysFileStreamFRead2" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFRead2
	#define EXT_SysFileStreamFRead2
	#define GET_SysFileStreamFRead2(fl)  CAL_CMGETAPI( "SysFileStreamFRead2" ) 
	#define CAL_SysFileStreamFRead2  SysFileStreamFRead2
	#define CHK_SysFileStreamFRead2  TRUE
	#define EXP_SysFileStreamFRead2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFRead2", (RTS_UINTPTR)SysFileStreamFRead2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFRead2
	#define EXT_SysFileStreamSysFileStreamFRead2
	#define GET_SysFileStreamSysFileStreamFRead2  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFRead2(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFRead2(p1,p2,p3) : ((ISysFileStream*)p0)->ISysFileStreamFRead2(p1,p2,p3))
	#define CHK_SysFileStreamSysFileStreamFRead2  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFRead2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFRead2
	#define EXT_SysFileStreamFRead2
	#define GET_SysFileStreamFRead2(fl)  CAL_CMGETAPI( "SysFileStreamFRead2" ) 
	#define CAL_SysFileStreamFRead2(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFRead2(p1,p2,p3) : ((ISysFileStream*)p0)->ISysFileStreamFRead2(p1,p2,p3))
	#define CHK_SysFileStreamFRead2  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFRead2  CAL_CMEXPAPI( "SysFileStreamFRead2" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFRead2  PFSYSFILESTREAMFREAD2 pfSysFileStreamFRead2;
	#define EXT_SysFileStreamFRead2  extern PFSYSFILESTREAMFREAD2 pfSysFileStreamFRead2;
	#define GET_SysFileStreamFRead2(fl)  s_pfCMGetAPI2( "SysFileStreamFRead2", (RTS_VOID_FCTPTR *)&pfSysFileStreamFRead2, (fl), 0, 0)
	#define CAL_SysFileStreamFRead2  pfSysFileStreamFRead2
	#define CHK_SysFileStreamFRead2  (pfSysFileStreamFRead2 != NULL)
	#define EXP_SysFileStreamFRead2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFRead2", (RTS_UINTPTR)SysFileStreamFRead2, 0, 0) 
#endif



unsigned int CDECL SysFileStreamFWrite(void* pSource, unsigned int uiSize, unsigned int uiNObjs, void *pFile);
typedef unsigned int (CDECL * PFSYSFILESTREAMFWRITE) (void* pSource, unsigned int uiSize, unsigned int uiNObjs, void *pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFWRITE_NOTIMPLEMENTED)
	#define USE_SysFileStreamFWrite
	#define EXT_SysFileStreamFWrite
	#define GET_SysFileStreamFWrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFWrite(p0,p1,p2,p3)  (unsigned int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFWrite  FALSE
	#define EXP_SysFileStreamFWrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFWrite
	#define EXT_SysFileStreamFWrite
	#define GET_SysFileStreamFWrite(fl)  CAL_CMGETAPI( "SysFileStreamFWrite" ) 
	#define CAL_SysFileStreamFWrite  SysFileStreamFWrite
	#define CHK_SysFileStreamFWrite  TRUE
	#define EXP_SysFileStreamFWrite  CAL_CMEXPAPI( "SysFileStreamFWrite" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFWrite
	#define EXT_SysFileStreamFWrite
	#define GET_SysFileStreamFWrite(fl)  CAL_CMGETAPI( "SysFileStreamFWrite" ) 
	#define CAL_SysFileStreamFWrite  SysFileStreamFWrite
	#define CHK_SysFileStreamFWrite  TRUE
	#define EXP_SysFileStreamFWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFWrite", (RTS_UINTPTR)SysFileStreamFWrite, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFWrite
	#define EXT_SysFileStreamSysFileStreamFWrite
	#define GET_SysFileStreamSysFileStreamFWrite  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFWrite pISysFileStream->ISysFileStreamFWrite
	#define CHK_SysFileStreamSysFileStreamFWrite (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFWrite  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFWrite
	#define EXT_SysFileStreamFWrite
	#define GET_SysFileStreamFWrite(fl)  CAL_CMGETAPI( "SysFileStreamFWrite" ) 
	#define CAL_SysFileStreamFWrite pISysFileStream->ISysFileStreamFWrite
	#define CHK_SysFileStreamFWrite (pISysFileStream != NULL)
	#define EXP_SysFileStreamFWrite  CAL_CMEXPAPI( "SysFileStreamFWrite" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFWrite  PFSYSFILESTREAMFWRITE pfSysFileStreamFWrite;
	#define EXT_SysFileStreamFWrite  extern PFSYSFILESTREAMFWRITE pfSysFileStreamFWrite;
	#define GET_SysFileStreamFWrite(fl)  s_pfCMGetAPI2( "SysFileStreamFWrite", (RTS_VOID_FCTPTR *)&pfSysFileStreamFWrite, (fl), 0, 0)
	#define CAL_SysFileStreamFWrite  pfSysFileStreamFWrite
	#define CHK_SysFileStreamFWrite  (pfSysFileStreamFWrite != NULL)
	#define EXP_SysFileStreamFWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFWrite", (RTS_UINTPTR)SysFileStreamFWrite, 0, 0) 
#endif



unsigned int CDECL SysFileStreamFWrite2(void *pFile, void* pSource, unsigned int uiSize, unsigned int uiNObjs);
typedef unsigned int (CDECL * PFSYSFILESTREAMFWRITE2) (void *pFile, void* pSource, unsigned int uiSize, unsigned int uiNObjs);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFWRITE2_NOTIMPLEMENTED)
	#define USE_SysFileStreamFWrite2
	#define EXT_SysFileStreamFWrite2
	#define GET_SysFileStreamFWrite2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFWrite2(p0,p1,p2,p3)  (unsigned int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFWrite2  FALSE
	#define EXP_SysFileStreamFWrite2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFWrite2
	#define EXT_SysFileStreamFWrite2
	#define GET_SysFileStreamFWrite2(fl)  CAL_CMGETAPI( "SysFileStreamFWrite2" ) 
	#define CAL_SysFileStreamFWrite2  SysFileStreamFWrite2
	#define CHK_SysFileStreamFWrite2  TRUE
	#define EXP_SysFileStreamFWrite2  CAL_CMEXPAPI( "SysFileStreamFWrite2" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFWrite2
	#define EXT_SysFileStreamFWrite2
	#define GET_SysFileStreamFWrite2(fl)  CAL_CMGETAPI( "SysFileStreamFWrite2" ) 
	#define CAL_SysFileStreamFWrite2  SysFileStreamFWrite2
	#define CHK_SysFileStreamFWrite2  TRUE
	#define EXP_SysFileStreamFWrite2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFWrite2", (RTS_UINTPTR)SysFileStreamFWrite2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFWrite2
	#define EXT_SysFileStreamSysFileStreamFWrite2
	#define GET_SysFileStreamSysFileStreamFWrite2  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFWrite2(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFWrite2(p1,p2,p3) : ((ISysFileStream*)p0)->ISysFileStreamFWrite2(p1,p2,p3))
	#define CHK_SysFileStreamSysFileStreamFWrite2  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFWrite2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFWrite2
	#define EXT_SysFileStreamFWrite2
	#define GET_SysFileStreamFWrite2(fl)  CAL_CMGETAPI( "SysFileStreamFWrite2" ) 
	#define CAL_SysFileStreamFWrite2(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFWrite2(p1,p2,p3) : ((ISysFileStream*)p0)->ISysFileStreamFWrite2(p1,p2,p3))
	#define CHK_SysFileStreamFWrite2  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFWrite2  CAL_CMEXPAPI( "SysFileStreamFWrite2" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFWrite2  PFSYSFILESTREAMFWRITE2 pfSysFileStreamFWrite2;
	#define EXT_SysFileStreamFWrite2  extern PFSYSFILESTREAMFWRITE2 pfSysFileStreamFWrite2;
	#define GET_SysFileStreamFWrite2(fl)  s_pfCMGetAPI2( "SysFileStreamFWrite2", (RTS_VOID_FCTPTR *)&pfSysFileStreamFWrite2, (fl), 0, 0)
	#define CAL_SysFileStreamFWrite2  pfSysFileStreamFWrite2
	#define CHK_SysFileStreamFWrite2  (pfSysFileStreamFWrite2 != NULL)
	#define EXP_SysFileStreamFWrite2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFWrite2", (RTS_UINTPTR)SysFileStreamFWrite2, 0, 0) 
#endif



int CDECL SysFileStreamFSeek(void* pFile, long lOffset, int origin);
typedef int (CDECL * PFSYSFILESTREAMFSEEK) (void* pFile, long lOffset, int origin);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFSEEK_NOTIMPLEMENTED)
	#define USE_SysFileStreamFSeek
	#define EXT_SysFileStreamFSeek
	#define GET_SysFileStreamFSeek(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFSeek(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFSeek  FALSE
	#define EXP_SysFileStreamFSeek  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFSeek
	#define EXT_SysFileStreamFSeek
	#define GET_SysFileStreamFSeek(fl)  CAL_CMGETAPI( "SysFileStreamFSeek" ) 
	#define CAL_SysFileStreamFSeek  SysFileStreamFSeek
	#define CHK_SysFileStreamFSeek  TRUE
	#define EXP_SysFileStreamFSeek  CAL_CMEXPAPI( "SysFileStreamFSeek" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFSeek
	#define EXT_SysFileStreamFSeek
	#define GET_SysFileStreamFSeek(fl)  CAL_CMGETAPI( "SysFileStreamFSeek" ) 
	#define CAL_SysFileStreamFSeek  SysFileStreamFSeek
	#define CHK_SysFileStreamFSeek  TRUE
	#define EXP_SysFileStreamFSeek  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFSeek", (RTS_UINTPTR)SysFileStreamFSeek, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFSeek
	#define EXT_SysFileStreamSysFileStreamFSeek
	#define GET_SysFileStreamSysFileStreamFSeek  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFSeek(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFSeek(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFSeek(p1,p2))
	#define CHK_SysFileStreamSysFileStreamFSeek  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFSeek  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFSeek
	#define EXT_SysFileStreamFSeek
	#define GET_SysFileStreamFSeek(fl)  CAL_CMGETAPI( "SysFileStreamFSeek" ) 
	#define CAL_SysFileStreamFSeek(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFSeek(p1,p2) : ((ISysFileStream*)p0)->ISysFileStreamFSeek(p1,p2))
	#define CHK_SysFileStreamFSeek  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFSeek  CAL_CMEXPAPI( "SysFileStreamFSeek" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFSeek  PFSYSFILESTREAMFSEEK pfSysFileStreamFSeek;
	#define EXT_SysFileStreamFSeek  extern PFSYSFILESTREAMFSEEK pfSysFileStreamFSeek;
	#define GET_SysFileStreamFSeek(fl)  s_pfCMGetAPI2( "SysFileStreamFSeek", (RTS_VOID_FCTPTR *)&pfSysFileStreamFSeek, (fl), 0, 0)
	#define CAL_SysFileStreamFSeek  pfSysFileStreamFSeek
	#define CHK_SysFileStreamFSeek  (pfSysFileStreamFSeek != NULL)
	#define EXP_SysFileStreamFSeek  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFSeek", (RTS_UINTPTR)SysFileStreamFSeek, 0, 0) 
#endif



long CDECL SysFileStreamFTell(void *pFile);
typedef long (CDECL * PFSYSFILESTREAMFTELL) (void *pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFTELL_NOTIMPLEMENTED)
	#define USE_SysFileStreamFTell
	#define EXT_SysFileStreamFTell
	#define GET_SysFileStreamFTell(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFTell(p0)  (long)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFTell  FALSE
	#define EXP_SysFileStreamFTell  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFTell
	#define EXT_SysFileStreamFTell
	#define GET_SysFileStreamFTell(fl)  CAL_CMGETAPI( "SysFileStreamFTell" ) 
	#define CAL_SysFileStreamFTell  SysFileStreamFTell
	#define CHK_SysFileStreamFTell  TRUE
	#define EXP_SysFileStreamFTell  CAL_CMEXPAPI( "SysFileStreamFTell" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFTell
	#define EXT_SysFileStreamFTell
	#define GET_SysFileStreamFTell(fl)  CAL_CMGETAPI( "SysFileStreamFTell" ) 
	#define CAL_SysFileStreamFTell  SysFileStreamFTell
	#define CHK_SysFileStreamFTell  TRUE
	#define EXP_SysFileStreamFTell  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFTell", (RTS_UINTPTR)SysFileStreamFTell, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFTell
	#define EXT_SysFileStreamSysFileStreamFTell
	#define GET_SysFileStreamSysFileStreamFTell  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFTell(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFTell() : ((ISysFileStream*)p0)->ISysFileStreamFTell())
	#define CHK_SysFileStreamSysFileStreamFTell  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFTell  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFTell
	#define EXT_SysFileStreamFTell
	#define GET_SysFileStreamFTell(fl)  CAL_CMGETAPI( "SysFileStreamFTell" ) 
	#define CAL_SysFileStreamFTell(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFTell() : ((ISysFileStream*)p0)->ISysFileStreamFTell())
	#define CHK_SysFileStreamFTell  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFTell  CAL_CMEXPAPI( "SysFileStreamFTell" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFTell  PFSYSFILESTREAMFTELL pfSysFileStreamFTell;
	#define EXT_SysFileStreamFTell  extern PFSYSFILESTREAMFTELL pfSysFileStreamFTell;
	#define GET_SysFileStreamFTell(fl)  s_pfCMGetAPI2( "SysFileStreamFTell", (RTS_VOID_FCTPTR *)&pfSysFileStreamFTell, (fl), 0, 0)
	#define CAL_SysFileStreamFTell  pfSysFileStreamFTell
	#define CHK_SysFileStreamFTell  (pfSysFileStreamFTell != NULL)
	#define EXP_SysFileStreamFTell  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFTell", (RTS_UINTPTR)SysFileStreamFTell, 0, 0) 
#endif



int CDECL SysFileStreamRewind(void *pFile);
typedef int (CDECL * PFSYSFILESTREAMREWIND) (void *pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMREWIND_NOTIMPLEMENTED)
	#define USE_SysFileStreamRewind
	#define EXT_SysFileStreamRewind
	#define GET_SysFileStreamRewind(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamRewind(p0)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamRewind  FALSE
	#define EXP_SysFileStreamRewind  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamRewind
	#define EXT_SysFileStreamRewind
	#define GET_SysFileStreamRewind(fl)  CAL_CMGETAPI( "SysFileStreamRewind" ) 
	#define CAL_SysFileStreamRewind  SysFileStreamRewind
	#define CHK_SysFileStreamRewind  TRUE
	#define EXP_SysFileStreamRewind  CAL_CMEXPAPI( "SysFileStreamRewind" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamRewind
	#define EXT_SysFileStreamRewind
	#define GET_SysFileStreamRewind(fl)  CAL_CMGETAPI( "SysFileStreamRewind" ) 
	#define CAL_SysFileStreamRewind  SysFileStreamRewind
	#define CHK_SysFileStreamRewind  TRUE
	#define EXP_SysFileStreamRewind  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamRewind", (RTS_UINTPTR)SysFileStreamRewind, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamRewind
	#define EXT_SysFileStreamSysFileStreamRewind
	#define GET_SysFileStreamSysFileStreamRewind  ERR_OK
	#define CAL_SysFileStreamSysFileStreamRewind(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamRewind() : ((ISysFileStream*)p0)->ISysFileStreamRewind())
	#define CHK_SysFileStreamSysFileStreamRewind  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamRewind  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamRewind
	#define EXT_SysFileStreamRewind
	#define GET_SysFileStreamRewind(fl)  CAL_CMGETAPI( "SysFileStreamRewind" ) 
	#define CAL_SysFileStreamRewind(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamRewind() : ((ISysFileStream*)p0)->ISysFileStreamRewind())
	#define CHK_SysFileStreamRewind  (pISysFileStream != NULL)
	#define EXP_SysFileStreamRewind  CAL_CMEXPAPI( "SysFileStreamRewind" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamRewind  PFSYSFILESTREAMREWIND pfSysFileStreamRewind;
	#define EXT_SysFileStreamRewind  extern PFSYSFILESTREAMREWIND pfSysFileStreamRewind;
	#define GET_SysFileStreamRewind(fl)  s_pfCMGetAPI2( "SysFileStreamRewind", (RTS_VOID_FCTPTR *)&pfSysFileStreamRewind, (fl), 0, 0)
	#define CAL_SysFileStreamRewind  pfSysFileStreamRewind
	#define CHK_SysFileStreamRewind  (pfSysFileStreamRewind != NULL)
	#define EXP_SysFileStreamRewind  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamRewind", (RTS_UINTPTR)SysFileStreamRewind, 0, 0) 
#endif



int CDECL SysFileStreamFGetPos(void *pFile, long *plOffset);
typedef int (CDECL * PFSYSFILESTREAMFGETPOS) (void *pFile, long *plOffset);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFGETPOS_NOTIMPLEMENTED)
	#define USE_SysFileStreamFGetPos
	#define EXT_SysFileStreamFGetPos
	#define GET_SysFileStreamFGetPos(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFGetPos(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFGetPos  FALSE
	#define EXP_SysFileStreamFGetPos  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFGetPos
	#define EXT_SysFileStreamFGetPos
	#define GET_SysFileStreamFGetPos(fl)  CAL_CMGETAPI( "SysFileStreamFGetPos" ) 
	#define CAL_SysFileStreamFGetPos  SysFileStreamFGetPos
	#define CHK_SysFileStreamFGetPos  TRUE
	#define EXP_SysFileStreamFGetPos  CAL_CMEXPAPI( "SysFileStreamFGetPos" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFGetPos
	#define EXT_SysFileStreamFGetPos
	#define GET_SysFileStreamFGetPos(fl)  CAL_CMGETAPI( "SysFileStreamFGetPos" ) 
	#define CAL_SysFileStreamFGetPos  SysFileStreamFGetPos
	#define CHK_SysFileStreamFGetPos  TRUE
	#define EXP_SysFileStreamFGetPos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFGetPos", (RTS_UINTPTR)SysFileStreamFGetPos, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFGetPos
	#define EXT_SysFileStreamSysFileStreamFGetPos
	#define GET_SysFileStreamSysFileStreamFGetPos  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFGetPos(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFGetPos(p1) : ((ISysFileStream*)p0)->ISysFileStreamFGetPos(p1))
	#define CHK_SysFileStreamSysFileStreamFGetPos  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFGetPos  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFGetPos
	#define EXT_SysFileStreamFGetPos
	#define GET_SysFileStreamFGetPos(fl)  CAL_CMGETAPI( "SysFileStreamFGetPos" ) 
	#define CAL_SysFileStreamFGetPos(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFGetPos(p1) : ((ISysFileStream*)p0)->ISysFileStreamFGetPos(p1))
	#define CHK_SysFileStreamFGetPos  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFGetPos  CAL_CMEXPAPI( "SysFileStreamFGetPos" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFGetPos  PFSYSFILESTREAMFGETPOS pfSysFileStreamFGetPos;
	#define EXT_SysFileStreamFGetPos  extern PFSYSFILESTREAMFGETPOS pfSysFileStreamFGetPos;
	#define GET_SysFileStreamFGetPos(fl)  s_pfCMGetAPI2( "SysFileStreamFGetPos", (RTS_VOID_FCTPTR *)&pfSysFileStreamFGetPos, (fl), 0, 0)
	#define CAL_SysFileStreamFGetPos  pfSysFileStreamFGetPos
	#define CHK_SysFileStreamFGetPos  (pfSysFileStreamFGetPos != NULL)
	#define EXP_SysFileStreamFGetPos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFGetPos", (RTS_UINTPTR)SysFileStreamFGetPos, 0, 0) 
#endif



int CDECL SysFileStreamFSetPos(void *pFile, long *plOffset);
typedef int (CDECL * PFSYSFILESTREAMFSETPOS) (void *pFile, long *plOffset);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFSETPOS_NOTIMPLEMENTED)
	#define USE_SysFileStreamFSetPos
	#define EXT_SysFileStreamFSetPos
	#define GET_SysFileStreamFSetPos(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFSetPos(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFSetPos  FALSE
	#define EXP_SysFileStreamFSetPos  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFSetPos
	#define EXT_SysFileStreamFSetPos
	#define GET_SysFileStreamFSetPos(fl)  CAL_CMGETAPI( "SysFileStreamFSetPos" ) 
	#define CAL_SysFileStreamFSetPos  SysFileStreamFSetPos
	#define CHK_SysFileStreamFSetPos  TRUE
	#define EXP_SysFileStreamFSetPos  CAL_CMEXPAPI( "SysFileStreamFSetPos" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFSetPos
	#define EXT_SysFileStreamFSetPos
	#define GET_SysFileStreamFSetPos(fl)  CAL_CMGETAPI( "SysFileStreamFSetPos" ) 
	#define CAL_SysFileStreamFSetPos  SysFileStreamFSetPos
	#define CHK_SysFileStreamFSetPos  TRUE
	#define EXP_SysFileStreamFSetPos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFSetPos", (RTS_UINTPTR)SysFileStreamFSetPos, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFSetPos
	#define EXT_SysFileStreamSysFileStreamFSetPos
	#define GET_SysFileStreamSysFileStreamFSetPos  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFSetPos(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFSetPos(p1) : ((ISysFileStream*)p0)->ISysFileStreamFSetPos(p1))
	#define CHK_SysFileStreamSysFileStreamFSetPos  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFSetPos  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFSetPos
	#define EXT_SysFileStreamFSetPos
	#define GET_SysFileStreamFSetPos(fl)  CAL_CMGETAPI( "SysFileStreamFSetPos" ) 
	#define CAL_SysFileStreamFSetPos(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFSetPos(p1) : ((ISysFileStream*)p0)->ISysFileStreamFSetPos(p1))
	#define CHK_SysFileStreamFSetPos  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFSetPos  CAL_CMEXPAPI( "SysFileStreamFSetPos" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFSetPos  PFSYSFILESTREAMFSETPOS pfSysFileStreamFSetPos;
	#define EXT_SysFileStreamFSetPos  extern PFSYSFILESTREAMFSETPOS pfSysFileStreamFSetPos;
	#define GET_SysFileStreamFSetPos(fl)  s_pfCMGetAPI2( "SysFileStreamFSetPos", (RTS_VOID_FCTPTR *)&pfSysFileStreamFSetPos, (fl), 0, 0)
	#define CAL_SysFileStreamFSetPos  pfSysFileStreamFSetPos
	#define CHK_SysFileStreamFSetPos  (pfSysFileStreamFSetPos != NULL)
	#define EXP_SysFileStreamFSetPos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFSetPos", (RTS_UINTPTR)SysFileStreamFSetPos, 0, 0) 
#endif



long CDECL SysFileStreamClearerr(void *pFile);
typedef long (CDECL * PFSYSFILESTREAMCLEARERR) (void *pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMCLEARERR_NOTIMPLEMENTED)
	#define USE_SysFileStreamClearerr
	#define EXT_SysFileStreamClearerr
	#define GET_SysFileStreamClearerr(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamClearerr(p0)  (long)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamClearerr  FALSE
	#define EXP_SysFileStreamClearerr  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamClearerr
	#define EXT_SysFileStreamClearerr
	#define GET_SysFileStreamClearerr(fl)  CAL_CMGETAPI( "SysFileStreamClearerr" ) 
	#define CAL_SysFileStreamClearerr  SysFileStreamClearerr
	#define CHK_SysFileStreamClearerr  TRUE
	#define EXP_SysFileStreamClearerr  CAL_CMEXPAPI( "SysFileStreamClearerr" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamClearerr
	#define EXT_SysFileStreamClearerr
	#define GET_SysFileStreamClearerr(fl)  CAL_CMGETAPI( "SysFileStreamClearerr" ) 
	#define CAL_SysFileStreamClearerr  SysFileStreamClearerr
	#define CHK_SysFileStreamClearerr  TRUE
	#define EXP_SysFileStreamClearerr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamClearerr", (RTS_UINTPTR)SysFileStreamClearerr, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamClearerr
	#define EXT_SysFileStreamSysFileStreamClearerr
	#define GET_SysFileStreamSysFileStreamClearerr  ERR_OK
	#define CAL_SysFileStreamSysFileStreamClearerr(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamClearerr() : ((ISysFileStream*)p0)->ISysFileStreamClearerr())
	#define CHK_SysFileStreamSysFileStreamClearerr  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamClearerr  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamClearerr
	#define EXT_SysFileStreamClearerr
	#define GET_SysFileStreamClearerr(fl)  CAL_CMGETAPI( "SysFileStreamClearerr" ) 
	#define CAL_SysFileStreamClearerr(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamClearerr() : ((ISysFileStream*)p0)->ISysFileStreamClearerr())
	#define CHK_SysFileStreamClearerr  (pISysFileStream != NULL)
	#define EXP_SysFileStreamClearerr  CAL_CMEXPAPI( "SysFileStreamClearerr" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamClearerr  PFSYSFILESTREAMCLEARERR pfSysFileStreamClearerr;
	#define EXT_SysFileStreamClearerr  extern PFSYSFILESTREAMCLEARERR pfSysFileStreamClearerr;
	#define GET_SysFileStreamClearerr(fl)  s_pfCMGetAPI2( "SysFileStreamClearerr", (RTS_VOID_FCTPTR *)&pfSysFileStreamClearerr, (fl), 0, 0)
	#define CAL_SysFileStreamClearerr  pfSysFileStreamClearerr
	#define CHK_SysFileStreamClearerr  (pfSysFileStreamClearerr != NULL)
	#define EXP_SysFileStreamClearerr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamClearerr", (RTS_UINTPTR)SysFileStreamClearerr, 0, 0) 
#endif



int CDECL SysFileStreamFEOF(void *pFile);
typedef int (CDECL * PFSYSFILESTREAMFEOF) (void *pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFEOF_NOTIMPLEMENTED)
	#define USE_SysFileStreamFEOF
	#define EXT_SysFileStreamFEOF
	#define GET_SysFileStreamFEOF(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFEOF(p0)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFEOF  FALSE
	#define EXP_SysFileStreamFEOF  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFEOF
	#define EXT_SysFileStreamFEOF
	#define GET_SysFileStreamFEOF(fl)  CAL_CMGETAPI( "SysFileStreamFEOF" ) 
	#define CAL_SysFileStreamFEOF  SysFileStreamFEOF
	#define CHK_SysFileStreamFEOF  TRUE
	#define EXP_SysFileStreamFEOF  CAL_CMEXPAPI( "SysFileStreamFEOF" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFEOF
	#define EXT_SysFileStreamFEOF
	#define GET_SysFileStreamFEOF(fl)  CAL_CMGETAPI( "SysFileStreamFEOF" ) 
	#define CAL_SysFileStreamFEOF  SysFileStreamFEOF
	#define CHK_SysFileStreamFEOF  TRUE
	#define EXP_SysFileStreamFEOF  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFEOF", (RTS_UINTPTR)SysFileStreamFEOF, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFEOF
	#define EXT_SysFileStreamSysFileStreamFEOF
	#define GET_SysFileStreamSysFileStreamFEOF  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFEOF(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFEOF() : ((ISysFileStream*)p0)->ISysFileStreamFEOF())
	#define CHK_SysFileStreamSysFileStreamFEOF  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFEOF  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFEOF
	#define EXT_SysFileStreamFEOF
	#define GET_SysFileStreamFEOF(fl)  CAL_CMGETAPI( "SysFileStreamFEOF" ) 
	#define CAL_SysFileStreamFEOF(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFEOF() : ((ISysFileStream*)p0)->ISysFileStreamFEOF())
	#define CHK_SysFileStreamFEOF  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFEOF  CAL_CMEXPAPI( "SysFileStreamFEOF" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFEOF  PFSYSFILESTREAMFEOF pfSysFileStreamFEOF;
	#define EXT_SysFileStreamFEOF  extern PFSYSFILESTREAMFEOF pfSysFileStreamFEOF;
	#define GET_SysFileStreamFEOF(fl)  s_pfCMGetAPI2( "SysFileStreamFEOF", (RTS_VOID_FCTPTR *)&pfSysFileStreamFEOF, (fl), 0, 0)
	#define CAL_SysFileStreamFEOF  pfSysFileStreamFEOF
	#define CHK_SysFileStreamFEOF  (pfSysFileStreamFEOF != NULL)
	#define EXP_SysFileStreamFEOF  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFEOF", (RTS_UINTPTR)SysFileStreamFEOF, 0, 0) 
#endif



int CDECL SysFileStreamFError(void *pFile);
typedef int (CDECL * PFSYSFILESTREAMFERROR) (void *pFile);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMFERROR_NOTIMPLEMENTED)
	#define USE_SysFileStreamFError
	#define EXT_SysFileStreamFError
	#define GET_SysFileStreamFError(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamFError(p0)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamFError  FALSE
	#define EXP_SysFileStreamFError  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamFError
	#define EXT_SysFileStreamFError
	#define GET_SysFileStreamFError(fl)  CAL_CMGETAPI( "SysFileStreamFError" ) 
	#define CAL_SysFileStreamFError  SysFileStreamFError
	#define CHK_SysFileStreamFError  TRUE
	#define EXP_SysFileStreamFError  CAL_CMEXPAPI( "SysFileStreamFError" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamFError
	#define EXT_SysFileStreamFError
	#define GET_SysFileStreamFError(fl)  CAL_CMGETAPI( "SysFileStreamFError" ) 
	#define CAL_SysFileStreamFError  SysFileStreamFError
	#define CHK_SysFileStreamFError  TRUE
	#define EXP_SysFileStreamFError  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFError", (RTS_UINTPTR)SysFileStreamFError, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamFError
	#define EXT_SysFileStreamSysFileStreamFError
	#define GET_SysFileStreamSysFileStreamFError  ERR_OK
	#define CAL_SysFileStreamSysFileStreamFError(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFError() : ((ISysFileStream*)p0)->ISysFileStreamFError())
	#define CHK_SysFileStreamSysFileStreamFError  (pISysFileStream != NULL)
	#define EXP_SysFileStreamSysFileStreamFError  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamFError
	#define EXT_SysFileStreamFError
	#define GET_SysFileStreamFError(fl)  CAL_CMGETAPI( "SysFileStreamFError" ) 
	#define CAL_SysFileStreamFError(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysFileStream->ISysFileStreamFError() : ((ISysFileStream*)p0)->ISysFileStreamFError())
	#define CHK_SysFileStreamFError  (pISysFileStream != NULL)
	#define EXP_SysFileStreamFError  CAL_CMEXPAPI( "SysFileStreamFError" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamFError  PFSYSFILESTREAMFERROR pfSysFileStreamFError;
	#define EXT_SysFileStreamFError  extern PFSYSFILESTREAMFERROR pfSysFileStreamFError;
	#define GET_SysFileStreamFError(fl)  s_pfCMGetAPI2( "SysFileStreamFError", (RTS_VOID_FCTPTR *)&pfSysFileStreamFError, (fl), 0, 0)
	#define CAL_SysFileStreamFError  pfSysFileStreamFError
	#define CHK_SysFileStreamFError  (pfSysFileStreamFError != NULL)
	#define EXP_SysFileStreamFError  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamFError", (RTS_UINTPTR)SysFileStreamFError, 0, 0) 
#endif



int CDECL SysFileStreamRemove(char *szFileName);
typedef int (CDECL * PFSYSFILESTREAMREMOVE) (char *szFileName);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMREMOVE_NOTIMPLEMENTED)
	#define USE_SysFileStreamRemove
	#define EXT_SysFileStreamRemove
	#define GET_SysFileStreamRemove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamRemove(p0)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamRemove  FALSE
	#define EXP_SysFileStreamRemove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamRemove
	#define EXT_SysFileStreamRemove
	#define GET_SysFileStreamRemove(fl)  CAL_CMGETAPI( "SysFileStreamRemove" ) 
	#define CAL_SysFileStreamRemove  SysFileStreamRemove
	#define CHK_SysFileStreamRemove  TRUE
	#define EXP_SysFileStreamRemove  CAL_CMEXPAPI( "SysFileStreamRemove" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamRemove
	#define EXT_SysFileStreamRemove
	#define GET_SysFileStreamRemove(fl)  CAL_CMGETAPI( "SysFileStreamRemove" ) 
	#define CAL_SysFileStreamRemove  SysFileStreamRemove
	#define CHK_SysFileStreamRemove  TRUE
	#define EXP_SysFileStreamRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamRemove", (RTS_UINTPTR)SysFileStreamRemove, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamRemove
	#define EXT_SysFileStreamSysFileStreamRemove
	#define GET_SysFileStreamSysFileStreamRemove  ERR_OK
	#define CAL_SysFileStreamSysFileStreamRemove CSysFileStream::ISysFileStreamRemove
	#define CHK_SysFileStreamSysFileStreamRemove  TRUE
	#define EXP_SysFileStreamSysFileStreamRemove  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamRemove
	#define EXT_SysFileStreamRemove
	#define GET_SysFileStreamRemove(fl)  CAL_CMGETAPI( "SysFileStreamRemove" ) 
	#define CAL_SysFileStreamRemove CSysFileStream::ISysFileStreamRemove
	#define CHK_SysFileStreamRemove  TRUE
	#define EXP_SysFileStreamRemove  CAL_CMEXPAPI( "SysFileStreamRemove" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamRemove  PFSYSFILESTREAMREMOVE pfSysFileStreamRemove;
	#define EXT_SysFileStreamRemove  extern PFSYSFILESTREAMREMOVE pfSysFileStreamRemove;
	#define GET_SysFileStreamRemove(fl)  s_pfCMGetAPI2( "SysFileStreamRemove", (RTS_VOID_FCTPTR *)&pfSysFileStreamRemove, (fl), 0, 0)
	#define CAL_SysFileStreamRemove  pfSysFileStreamRemove
	#define CHK_SysFileStreamRemove  (pfSysFileStreamRemove != NULL)
	#define EXP_SysFileStreamRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamRemove", (RTS_UINTPTR)SysFileStreamRemove, 0, 0) 
#endif



int CDECL SysFileStreamRename(char *szOldFileName, char *szNewFileName);
typedef int (CDECL * PFSYSFILESTREAMRENAME) (char *szOldFileName, char *szNewFileName);
#if defined(SYSFILESTREAM_NOTIMPLEMENTED) || defined(SYSFILESTREAMRENAME_NOTIMPLEMENTED)
	#define USE_SysFileStreamRename
	#define EXT_SysFileStreamRename
	#define GET_SysFileStreamRename(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFileStreamRename(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysFileStreamRename  FALSE
	#define EXP_SysFileStreamRename  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFileStreamRename
	#define EXT_SysFileStreamRename
	#define GET_SysFileStreamRename(fl)  CAL_CMGETAPI( "SysFileStreamRename" ) 
	#define CAL_SysFileStreamRename  SysFileStreamRename
	#define CHK_SysFileStreamRename  TRUE
	#define EXP_SysFileStreamRename  CAL_CMEXPAPI( "SysFileStreamRename" ) 
#elif defined(MIXED_LINK) && !defined(SYSFILESTREAM_EXTERNAL)
	#define USE_SysFileStreamRename
	#define EXT_SysFileStreamRename
	#define GET_SysFileStreamRename(fl)  CAL_CMGETAPI( "SysFileStreamRename" ) 
	#define CAL_SysFileStreamRename  SysFileStreamRename
	#define CHK_SysFileStreamRename  TRUE
	#define EXP_SysFileStreamRename  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamRename", (RTS_UINTPTR)SysFileStreamRename, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFileStreamSysFileStreamRename
	#define EXT_SysFileStreamSysFileStreamRename
	#define GET_SysFileStreamSysFileStreamRename  ERR_OK
	#define CAL_SysFileStreamSysFileStreamRename CSysFileStream::ISysFileStreamRename
	#define CHK_SysFileStreamSysFileStreamRename  TRUE
	#define EXP_SysFileStreamSysFileStreamRename  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFileStreamRename
	#define EXT_SysFileStreamRename
	#define GET_SysFileStreamRename(fl)  CAL_CMGETAPI( "SysFileStreamRename" ) 
	#define CAL_SysFileStreamRename CSysFileStream::ISysFileStreamRename
	#define CHK_SysFileStreamRename  TRUE
	#define EXP_SysFileStreamRename  CAL_CMEXPAPI( "SysFileStreamRename" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFileStreamRename  PFSYSFILESTREAMRENAME pfSysFileStreamRename;
	#define EXT_SysFileStreamRename  extern PFSYSFILESTREAMRENAME pfSysFileStreamRename;
	#define GET_SysFileStreamRename(fl)  s_pfCMGetAPI2( "SysFileStreamRename", (RTS_VOID_FCTPTR *)&pfSysFileStreamRename, (fl), 0, 0)
	#define CAL_SysFileStreamRename  pfSysFileStreamRename
	#define CHK_SysFileStreamRename  (pfSysFileStreamRename != NULL)
	#define EXP_SysFileStreamRename  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFileStreamRename", (RTS_UINTPTR)SysFileStreamRename, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif




typedef struct
{
	IBase_C *pBase;
	PFSYSFILESTREAMFOPEN ISysFileStreamFOpen;
 	PFSYSFILESTREAMFCLOSE ISysFileStreamFClose;
 	PFSYSFILESTREAMFFLUSH ISysFileStreamFFlush;
 	PFSYSFILESTREAMFPRINTF_INT ISysFileStreamFPrintf_Int;
 	PFSYSFILESTREAMFPRINTF_REAL ISysFileStreamFPrintf_Real;
 	PFSYSFILESTREAMFPRINTF_STRING ISysFileStreamFPrintf_String;
 	PFSYSFILESTREAMFSCANF_INT ISysFileStreamFScanf_Int;
 	PFSYSFILESTREAMFSCANF_REAL ISysFileStreamFScanf_Real;
 	PFSYSFILESTREAMFSCANF_STRING ISysFileStreamFScanf_String;
 	PFSYSFILESTREAMFGETC ISysFileStreamFGetC;
 	PFSYSFILESTREAMFPUTC ISysFileStreamFPutc;
 	PFSYSFILESTREAMFPUTC2 ISysFileStreamFPutc2;
 	PFSYSFILESTREAMFGETS ISysFileStreamFGetS;
 	PFSYSFILESTREAMFGETS2 ISysFileStreamFGetS2;
 	PFSYSFILESTREAMFPUTS ISysFileStreamFPutS;
 	PFSYSFILESTREAMFPUTS2 ISysFileStreamFPutS2;
 	PFSYSFILESTREAMFREAD ISysFileStreamFRead;
 	PFSYSFILESTREAMFREAD2 ISysFileStreamFRead2;
 	PFSYSFILESTREAMFWRITE ISysFileStreamFWrite;
 	PFSYSFILESTREAMFWRITE2 ISysFileStreamFWrite2;
 	PFSYSFILESTREAMFSEEK ISysFileStreamFSeek;
 	PFSYSFILESTREAMFTELL ISysFileStreamFTell;
 	PFSYSFILESTREAMREWIND ISysFileStreamRewind;
 	PFSYSFILESTREAMFGETPOS ISysFileStreamFGetPos;
 	PFSYSFILESTREAMFSETPOS ISysFileStreamFSetPos;
 	PFSYSFILESTREAMCLEARERR ISysFileStreamClearerr;
 	PFSYSFILESTREAMFEOF ISysFileStreamFEOF;
 	PFSYSFILESTREAMFERROR ISysFileStreamFError;
 	PFSYSFILESTREAMREMOVE ISysFileStreamRemove;
 	PFSYSFILESTREAMRENAME ISysFileStreamRename;
 } ISysFileStream_C;

#ifdef CPLUSPLUS
class ISysFileStream : public IBase
{
	public:
		virtual void* CDECL ISysFileStreamFOpen(char *szFileName, char *szMode) =0;
		virtual int CDECL ISysFileStreamFClose(void) =0;
		virtual int CDECL ISysFileStreamFFlush(void) =0;
		virtual int CDECL ISysFileStreamFPrintf_Int(char *szFormat, int nArg) =0;
		virtual int CDECL ISysFileStreamFPrintf_Real(char *szFormat, float fArg) =0;
		virtual int CDECL ISysFileStreamFPrintf_String(char *szFormat, char *pcArg) =0;
		virtual int CDECL ISysFileStreamFScanf_Int(char *szFormat, int *pnArg) =0;
		virtual int CDECL ISysFileStreamFScanf_Real(char *szFormat, float *pfArg) =0;
		virtual int CDECL ISysFileStreamFScanf_String(char *szFormat, char *pcArg) =0;
		virtual int CDECL ISysFileStreamFGetC(void) =0;
		virtual int CDECL ISysFileStreamFPutc(int c, void *pFile) =0;
		virtual int CDECL ISysFileStreamFPutc2(int c) =0;
		virtual char* CDECL ISysFileStreamFGetS(char *pcDest, int n, void* pFile) =0;
		virtual char* CDECL ISysFileStreamFGetS2(char *pcDest, int n) =0;
		virtual int CDECL ISysFileStreamFPutS(char* pcSource, void* pFile) =0;
		virtual int CDECL ISysFileStreamFPutS2(char* pcSource) =0;
		virtual unsigned int CDECL ISysFileStreamFRead(void *pDest, unsigned int uiSize, unsigned int uiNObjs, void *pFile) =0;
		virtual unsigned int CDECL ISysFileStreamFRead2(void *pDest, unsigned int uiSize, unsigned int uiNObjs) =0;
		virtual unsigned int CDECL ISysFileStreamFWrite(void* pSource, unsigned int uiSize, unsigned int uiNObjs, void *pFile) =0;
		virtual unsigned int CDECL ISysFileStreamFWrite2(void* pSource, unsigned int uiSize, unsigned int uiNObjs) =0;
		virtual int CDECL ISysFileStreamFSeek(long lOffset, int origin) =0;
		virtual long CDECL ISysFileStreamFTell(void) =0;
		virtual int CDECL ISysFileStreamRewind(void) =0;
		virtual int CDECL ISysFileStreamFGetPos(long *plOffset) =0;
		virtual int CDECL ISysFileStreamFSetPos(long *plOffset) =0;
		virtual long CDECL ISysFileStreamClearerr(void) =0;
		virtual int CDECL ISysFileStreamFEOF(void) =0;
		virtual int CDECL ISysFileStreamFError(void) =0;
		static int CDECL ISysFileStreamRemove(char *szFileName);
		static int CDECL ISysFileStreamRename(char *szOldFileName, char *szNewFileName);
};
	#ifndef ITF_SysFileStream
		#define ITF_SysFileStream static ISysFileStream *pISysFileStream = NULL;
	#endif
	#define EXTITF_SysFileStream
#else	/*CPLUSPLUS*/
	typedef ISysFileStream_C		ISysFileStream;
	#ifndef ITF_SysFileStream
		#define ITF_SysFileStream
	#endif
	#define EXTITF_SysFileStream
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSFILESTREAMITF_H_*/
