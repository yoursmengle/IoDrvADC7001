 /**
 * <interfacename>CmpBinTagUtilIec</interfacename>
 * <description> 
 *	<p>Interface of the IEC binary tag utility</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPBINTAGUTILIECITF_H_
#define _CMPBINTAGUTILIECITF_H_

#include "CmpStd.h"

 

 




/* --------- The writer interface ---------- */

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>BTagAlignment</description>
 */
typedef struct tagBTagAlignment
{
	RTS_IEC_UINT uiModulus;		
	RTS_IEC_UINT uiRemainder;		
} BTagAlignment;

/**
 * <description>btagreadercreate</description>
 */
typedef struct tagbtagreadercreate_struct
{
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagReaderCreate;	/* VAR_OUTPUT */	
} btagreadercreate_struct;

void CDECL CDECL_EXT btagreadercreate(btagreadercreate_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERCREATE_IEC) (btagreadercreate_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERCREATE_NOTIMPLEMENTED)
	#define USE_btagreadercreate
	#define EXT_btagreadercreate
	#define GET_btagreadercreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreadercreate(p0) 
	#define CHK_btagreadercreate  FALSE
	#define EXP_btagreadercreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreadercreate
	#define EXT_btagreadercreate
	#define GET_btagreadercreate(fl)  CAL_CMGETAPI( "btagreadercreate" ) 
	#define CAL_btagreadercreate  btagreadercreate
	#define CHK_btagreadercreate  TRUE
	#define EXP_btagreadercreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadercreate", (RTS_UINTPTR)btagreadercreate, 1, RTSITF_GET_SIGNATURE(0, 0x1A997D85), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreadercreate
	#define EXT_btagreadercreate
	#define GET_btagreadercreate(fl)  CAL_CMGETAPI( "btagreadercreate" ) 
	#define CAL_btagreadercreate  btagreadercreate
	#define CHK_btagreadercreate  TRUE
	#define EXP_btagreadercreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadercreate", (RTS_UINTPTR)btagreadercreate, 1, RTSITF_GET_SIGNATURE(0, 0x1A997D85), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreadercreate
	#define EXT_CmpBinTagUtilIecbtagreadercreate
	#define GET_CmpBinTagUtilIecbtagreadercreate  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreadercreate  btagreadercreate
	#define CHK_CmpBinTagUtilIecbtagreadercreate  TRUE
	#define EXP_CmpBinTagUtilIecbtagreadercreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadercreate", (RTS_UINTPTR)btagreadercreate, 1, RTSITF_GET_SIGNATURE(0, 0x1A997D85), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreadercreate
	#define EXT_btagreadercreate
	#define GET_btagreadercreate(fl)  CAL_CMGETAPI( "btagreadercreate" ) 
	#define CAL_btagreadercreate  btagreadercreate
	#define CHK_btagreadercreate  TRUE
	#define EXP_btagreadercreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadercreate", (RTS_UINTPTR)btagreadercreate, 1, RTSITF_GET_SIGNATURE(0, 0x1A997D85), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreadercreate  PFBTAGREADERCREATE_IEC pfbtagreadercreate;
	#define EXT_btagreadercreate  extern PFBTAGREADERCREATE_IEC pfbtagreadercreate;
	#define GET_btagreadercreate(fl)  s_pfCMGetAPI2( "btagreadercreate", (RTS_VOID_FCTPTR *)&pfbtagreadercreate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1A997D85), 0x03050500)
	#define CAL_btagreadercreate  pfbtagreadercreate
	#define CHK_btagreadercreate  (pfbtagreadercreate != NULL)
	#define EXP_btagreadercreate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadercreate", (RTS_UINTPTR)btagreadercreate, 1, RTSITF_GET_SIGNATURE(0, 0x1A997D85), 0x03050500) 
#endif


/**
 * <description>btagreadercreatedynamic</description>
 */
typedef struct tagbtagreadercreatedynamic_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagReaderCreateDynamic;	/* VAR_OUTPUT */	
} btagreadercreatedynamic_struct;

void CDECL CDECL_EXT btagreadercreatedynamic(btagreadercreatedynamic_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERCREATEDYNAMIC_IEC) (btagreadercreatedynamic_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERCREATEDYNAMIC_NOTIMPLEMENTED)
	#define USE_btagreadercreatedynamic
	#define EXT_btagreadercreatedynamic
	#define GET_btagreadercreatedynamic(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreadercreatedynamic(p0) 
	#define CHK_btagreadercreatedynamic  FALSE
	#define EXP_btagreadercreatedynamic  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreadercreatedynamic
	#define EXT_btagreadercreatedynamic
	#define GET_btagreadercreatedynamic(fl)  CAL_CMGETAPI( "btagreadercreatedynamic" ) 
	#define CAL_btagreadercreatedynamic  btagreadercreatedynamic
	#define CHK_btagreadercreatedynamic  TRUE
	#define EXP_btagreadercreatedynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadercreatedynamic", (RTS_UINTPTR)btagreadercreatedynamic, 1, RTSITF_GET_SIGNATURE(0, 0xE334F937), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreadercreatedynamic
	#define EXT_btagreadercreatedynamic
	#define GET_btagreadercreatedynamic(fl)  CAL_CMGETAPI( "btagreadercreatedynamic" ) 
	#define CAL_btagreadercreatedynamic  btagreadercreatedynamic
	#define CHK_btagreadercreatedynamic  TRUE
	#define EXP_btagreadercreatedynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadercreatedynamic", (RTS_UINTPTR)btagreadercreatedynamic, 1, RTSITF_GET_SIGNATURE(0, 0xE334F937), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreadercreatedynamic
	#define EXT_CmpBinTagUtilIecbtagreadercreatedynamic
	#define GET_CmpBinTagUtilIecbtagreadercreatedynamic  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreadercreatedynamic  btagreadercreatedynamic
	#define CHK_CmpBinTagUtilIecbtagreadercreatedynamic  TRUE
	#define EXP_CmpBinTagUtilIecbtagreadercreatedynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadercreatedynamic", (RTS_UINTPTR)btagreadercreatedynamic, 1, RTSITF_GET_SIGNATURE(0, 0xE334F937), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreadercreatedynamic
	#define EXT_btagreadercreatedynamic
	#define GET_btagreadercreatedynamic(fl)  CAL_CMGETAPI( "btagreadercreatedynamic" ) 
	#define CAL_btagreadercreatedynamic  btagreadercreatedynamic
	#define CHK_btagreadercreatedynamic  TRUE
	#define EXP_btagreadercreatedynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadercreatedynamic", (RTS_UINTPTR)btagreadercreatedynamic, 1, RTSITF_GET_SIGNATURE(0, 0xE334F937), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreadercreatedynamic  PFBTAGREADERCREATEDYNAMIC_IEC pfbtagreadercreatedynamic;
	#define EXT_btagreadercreatedynamic  extern PFBTAGREADERCREATEDYNAMIC_IEC pfbtagreadercreatedynamic;
	#define GET_btagreadercreatedynamic(fl)  s_pfCMGetAPI2( "btagreadercreatedynamic", (RTS_VOID_FCTPTR *)&pfbtagreadercreatedynamic, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE334F937), 0x03050500)
	#define CAL_btagreadercreatedynamic  pfbtagreadercreatedynamic
	#define CHK_btagreadercreatedynamic  (pfbtagreadercreatedynamic != NULL)
	#define EXP_btagreadercreatedynamic   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadercreatedynamic", (RTS_UINTPTR)btagreadercreatedynamic, 1, RTSITF_GET_SIGNATURE(0, 0xE334F937), 0x03050500) 
#endif


/**
 * <description>btagreaderdestroy</description>
 */
typedef struct tagbtagreaderdestroy_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderDestroy;	/* VAR_OUTPUT */	
} btagreaderdestroy_struct;

void CDECL CDECL_EXT btagreaderdestroy(btagreaderdestroy_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERDESTROY_IEC) (btagreaderdestroy_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERDESTROY_NOTIMPLEMENTED)
	#define USE_btagreaderdestroy
	#define EXT_btagreaderdestroy
	#define GET_btagreaderdestroy(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreaderdestroy(p0) 
	#define CHK_btagreaderdestroy  FALSE
	#define EXP_btagreaderdestroy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreaderdestroy
	#define EXT_btagreaderdestroy
	#define GET_btagreaderdestroy(fl)  CAL_CMGETAPI( "btagreaderdestroy" ) 
	#define CAL_btagreaderdestroy  btagreaderdestroy
	#define CHK_btagreaderdestroy  TRUE
	#define EXP_btagreaderdestroy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderdestroy", (RTS_UINTPTR)btagreaderdestroy, 1, RTSITF_GET_SIGNATURE(0, 0x516D60C3), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreaderdestroy
	#define EXT_btagreaderdestroy
	#define GET_btagreaderdestroy(fl)  CAL_CMGETAPI( "btagreaderdestroy" ) 
	#define CAL_btagreaderdestroy  btagreaderdestroy
	#define CHK_btagreaderdestroy  TRUE
	#define EXP_btagreaderdestroy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderdestroy", (RTS_UINTPTR)btagreaderdestroy, 1, RTSITF_GET_SIGNATURE(0, 0x516D60C3), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreaderdestroy
	#define EXT_CmpBinTagUtilIecbtagreaderdestroy
	#define GET_CmpBinTagUtilIecbtagreaderdestroy  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreaderdestroy  btagreaderdestroy
	#define CHK_CmpBinTagUtilIecbtagreaderdestroy  TRUE
	#define EXP_CmpBinTagUtilIecbtagreaderdestroy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderdestroy", (RTS_UINTPTR)btagreaderdestroy, 1, RTSITF_GET_SIGNATURE(0, 0x516D60C3), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreaderdestroy
	#define EXT_btagreaderdestroy
	#define GET_btagreaderdestroy(fl)  CAL_CMGETAPI( "btagreaderdestroy" ) 
	#define CAL_btagreaderdestroy  btagreaderdestroy
	#define CHK_btagreaderdestroy  TRUE
	#define EXP_btagreaderdestroy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderdestroy", (RTS_UINTPTR)btagreaderdestroy, 1, RTSITF_GET_SIGNATURE(0, 0x516D60C3), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreaderdestroy  PFBTAGREADERDESTROY_IEC pfbtagreaderdestroy;
	#define EXT_btagreaderdestroy  extern PFBTAGREADERDESTROY_IEC pfbtagreaderdestroy;
	#define GET_btagreaderdestroy(fl)  s_pfCMGetAPI2( "btagreaderdestroy", (RTS_VOID_FCTPTR *)&pfbtagreaderdestroy, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x516D60C3), 0x03050500)
	#define CAL_btagreaderdestroy  pfbtagreaderdestroy
	#define CHK_btagreaderdestroy  (pfbtagreaderdestroy != NULL)
	#define EXP_btagreaderdestroy   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderdestroy", (RTS_UINTPTR)btagreaderdestroy, 1, RTSITF_GET_SIGNATURE(0, 0x516D60C3), 0x03050500) 
#endif


/**
 * <description>btagreadergetcomplexcontent</description>
 */
typedef struct tagbtagreadergetcomplexcontent_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_BYTE **ppBuffer;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pulSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderGetComplexContent;	/* VAR_OUTPUT */	
} btagreadergetcomplexcontent_struct;

void CDECL CDECL_EXT btagreadergetcomplexcontent(btagreadergetcomplexcontent_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERGETCOMPLEXCONTENT_IEC) (btagreadergetcomplexcontent_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERGETCOMPLEXCONTENT_NOTIMPLEMENTED)
	#define USE_btagreadergetcomplexcontent
	#define EXT_btagreadergetcomplexcontent
	#define GET_btagreadergetcomplexcontent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreadergetcomplexcontent(p0) 
	#define CHK_btagreadergetcomplexcontent  FALSE
	#define EXP_btagreadergetcomplexcontent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreadergetcomplexcontent
	#define EXT_btagreadergetcomplexcontent
	#define GET_btagreadergetcomplexcontent(fl)  CAL_CMGETAPI( "btagreadergetcomplexcontent" ) 
	#define CAL_btagreadergetcomplexcontent  btagreadergetcomplexcontent
	#define CHK_btagreadergetcomplexcontent  TRUE
	#define EXP_btagreadergetcomplexcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetcomplexcontent", (RTS_UINTPTR)btagreadergetcomplexcontent, 1, RTSITF_GET_SIGNATURE(0, 0x129CC395), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreadergetcomplexcontent
	#define EXT_btagreadergetcomplexcontent
	#define GET_btagreadergetcomplexcontent(fl)  CAL_CMGETAPI( "btagreadergetcomplexcontent" ) 
	#define CAL_btagreadergetcomplexcontent  btagreadergetcomplexcontent
	#define CHK_btagreadergetcomplexcontent  TRUE
	#define EXP_btagreadergetcomplexcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetcomplexcontent", (RTS_UINTPTR)btagreadergetcomplexcontent, 1, RTSITF_GET_SIGNATURE(0, 0x129CC395), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreadergetcomplexcontent
	#define EXT_CmpBinTagUtilIecbtagreadergetcomplexcontent
	#define GET_CmpBinTagUtilIecbtagreadergetcomplexcontent  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreadergetcomplexcontent  btagreadergetcomplexcontent
	#define CHK_CmpBinTagUtilIecbtagreadergetcomplexcontent  TRUE
	#define EXP_CmpBinTagUtilIecbtagreadergetcomplexcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetcomplexcontent", (RTS_UINTPTR)btagreadergetcomplexcontent, 1, RTSITF_GET_SIGNATURE(0, 0x129CC395), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreadergetcomplexcontent
	#define EXT_btagreadergetcomplexcontent
	#define GET_btagreadergetcomplexcontent(fl)  CAL_CMGETAPI( "btagreadergetcomplexcontent" ) 
	#define CAL_btagreadergetcomplexcontent  btagreadergetcomplexcontent
	#define CHK_btagreadergetcomplexcontent  TRUE
	#define EXP_btagreadergetcomplexcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetcomplexcontent", (RTS_UINTPTR)btagreadergetcomplexcontent, 1, RTSITF_GET_SIGNATURE(0, 0x129CC395), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreadergetcomplexcontent  PFBTAGREADERGETCOMPLEXCONTENT_IEC pfbtagreadergetcomplexcontent;
	#define EXT_btagreadergetcomplexcontent  extern PFBTAGREADERGETCOMPLEXCONTENT_IEC pfbtagreadergetcomplexcontent;
	#define GET_btagreadergetcomplexcontent(fl)  s_pfCMGetAPI2( "btagreadergetcomplexcontent", (RTS_VOID_FCTPTR *)&pfbtagreadergetcomplexcontent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x129CC395), 0x03050500)
	#define CAL_btagreadergetcomplexcontent  pfbtagreadergetcomplexcontent
	#define CHK_btagreadergetcomplexcontent  (pfbtagreadergetcomplexcontent != NULL)
	#define EXP_btagreadergetcomplexcontent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetcomplexcontent", (RTS_UINTPTR)btagreadergetcomplexcontent, 1, RTSITF_GET_SIGNATURE(0, 0x129CC395), 0x03050500) 
#endif


/**
 * <description>btagreadergetcontent</description>
 */
typedef struct tagbtagreadergetcontent_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_BYTE **ppBuffer;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pulSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderGetContent;	/* VAR_OUTPUT */	
} btagreadergetcontent_struct;

void CDECL CDECL_EXT btagreadergetcontent(btagreadergetcontent_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERGETCONTENT_IEC) (btagreadergetcontent_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERGETCONTENT_NOTIMPLEMENTED)
	#define USE_btagreadergetcontent
	#define EXT_btagreadergetcontent
	#define GET_btagreadergetcontent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreadergetcontent(p0) 
	#define CHK_btagreadergetcontent  FALSE
	#define EXP_btagreadergetcontent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreadergetcontent
	#define EXT_btagreadergetcontent
	#define GET_btagreadergetcontent(fl)  CAL_CMGETAPI( "btagreadergetcontent" ) 
	#define CAL_btagreadergetcontent  btagreadergetcontent
	#define CHK_btagreadergetcontent  TRUE
	#define EXP_btagreadergetcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetcontent", (RTS_UINTPTR)btagreadergetcontent, 1, RTSITF_GET_SIGNATURE(0, 0x61AF7447), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreadergetcontent
	#define EXT_btagreadergetcontent
	#define GET_btagreadergetcontent(fl)  CAL_CMGETAPI( "btagreadergetcontent" ) 
	#define CAL_btagreadergetcontent  btagreadergetcontent
	#define CHK_btagreadergetcontent  TRUE
	#define EXP_btagreadergetcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetcontent", (RTS_UINTPTR)btagreadergetcontent, 1, RTSITF_GET_SIGNATURE(0, 0x61AF7447), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreadergetcontent
	#define EXT_CmpBinTagUtilIecbtagreadergetcontent
	#define GET_CmpBinTagUtilIecbtagreadergetcontent  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreadergetcontent  btagreadergetcontent
	#define CHK_CmpBinTagUtilIecbtagreadergetcontent  TRUE
	#define EXP_CmpBinTagUtilIecbtagreadergetcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetcontent", (RTS_UINTPTR)btagreadergetcontent, 1, RTSITF_GET_SIGNATURE(0, 0x61AF7447), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreadergetcontent
	#define EXT_btagreadergetcontent
	#define GET_btagreadergetcontent(fl)  CAL_CMGETAPI( "btagreadergetcontent" ) 
	#define CAL_btagreadergetcontent  btagreadergetcontent
	#define CHK_btagreadergetcontent  TRUE
	#define EXP_btagreadergetcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetcontent", (RTS_UINTPTR)btagreadergetcontent, 1, RTSITF_GET_SIGNATURE(0, 0x61AF7447), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreadergetcontent  PFBTAGREADERGETCONTENT_IEC pfbtagreadergetcontent;
	#define EXT_btagreadergetcontent  extern PFBTAGREADERGETCONTENT_IEC pfbtagreadergetcontent;
	#define GET_btagreadergetcontent(fl)  s_pfCMGetAPI2( "btagreadergetcontent", (RTS_VOID_FCTPTR *)&pfbtagreadergetcontent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x61AF7447), 0x03050500)
	#define CAL_btagreadergetcontent  pfbtagreadergetcontent
	#define CHK_btagreadergetcontent  (pfbtagreadergetcontent != NULL)
	#define EXP_btagreadergetcontent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetcontent", (RTS_UINTPTR)btagreadergetcontent, 1, RTSITF_GET_SIGNATURE(0, 0x61AF7447), 0x03050500) 
#endif


/**
 * <description>btagreadergetstring</description>
 */
typedef struct tagbtagreadergetstring_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_BYTE **ppBuffer;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pulSize;				/* VAR_INPUT */	
	RTS_IEC_BOOL bAddEndOfString;		/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderGetString;	/* VAR_OUTPUT */	
} btagreadergetstring_struct;

void CDECL CDECL_EXT btagreadergetstring(btagreadergetstring_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERGETSTRING_IEC) (btagreadergetstring_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERGETSTRING_NOTIMPLEMENTED)
	#define USE_btagreadergetstring
	#define EXT_btagreadergetstring
	#define GET_btagreadergetstring(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreadergetstring(p0) 
	#define CHK_btagreadergetstring  FALSE
	#define EXP_btagreadergetstring  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreadergetstring
	#define EXT_btagreadergetstring
	#define GET_btagreadergetstring(fl)  CAL_CMGETAPI( "btagreadergetstring" ) 
	#define CAL_btagreadergetstring  btagreadergetstring
	#define CHK_btagreadergetstring  TRUE
	#define EXP_btagreadergetstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetstring", (RTS_UINTPTR)btagreadergetstring, 1, RTSITF_GET_SIGNATURE(0, 0x752DCAA9), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreadergetstring
	#define EXT_btagreadergetstring
	#define GET_btagreadergetstring(fl)  CAL_CMGETAPI( "btagreadergetstring" ) 
	#define CAL_btagreadergetstring  btagreadergetstring
	#define CHK_btagreadergetstring  TRUE
	#define EXP_btagreadergetstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetstring", (RTS_UINTPTR)btagreadergetstring, 1, RTSITF_GET_SIGNATURE(0, 0x752DCAA9), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreadergetstring
	#define EXT_CmpBinTagUtilIecbtagreadergetstring
	#define GET_CmpBinTagUtilIecbtagreadergetstring  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreadergetstring  btagreadergetstring
	#define CHK_CmpBinTagUtilIecbtagreadergetstring  TRUE
	#define EXP_CmpBinTagUtilIecbtagreadergetstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetstring", (RTS_UINTPTR)btagreadergetstring, 1, RTSITF_GET_SIGNATURE(0, 0x752DCAA9), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreadergetstring
	#define EXT_btagreadergetstring
	#define GET_btagreadergetstring(fl)  CAL_CMGETAPI( "btagreadergetstring" ) 
	#define CAL_btagreadergetstring  btagreadergetstring
	#define CHK_btagreadergetstring  TRUE
	#define EXP_btagreadergetstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetstring", (RTS_UINTPTR)btagreadergetstring, 1, RTSITF_GET_SIGNATURE(0, 0x752DCAA9), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreadergetstring  PFBTAGREADERGETSTRING_IEC pfbtagreadergetstring;
	#define EXT_btagreadergetstring  extern PFBTAGREADERGETSTRING_IEC pfbtagreadergetstring;
	#define GET_btagreadergetstring(fl)  s_pfCMGetAPI2( "btagreadergetstring", (RTS_VOID_FCTPTR *)&pfbtagreadergetstring, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x752DCAA9), 0x03050500)
	#define CAL_btagreadergetstring  pfbtagreadergetstring
	#define CHK_btagreadergetstring  (pfbtagreadergetstring != NULL)
	#define EXP_btagreadergetstring   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergetstring", (RTS_UINTPTR)btagreadergetstring, 1, RTSITF_GET_SIGNATURE(0, 0x752DCAA9), 0x03050500) 
#endif


/**
 * <description>btagreadergettagid</description>
 */
typedef struct tagbtagreadergettagid_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pulTagId;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderGetTagId;	/* VAR_OUTPUT */	
} btagreadergettagid_struct;

void CDECL CDECL_EXT btagreadergettagid(btagreadergettagid_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERGETTAGID_IEC) (btagreadergettagid_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERGETTAGID_NOTIMPLEMENTED)
	#define USE_btagreadergettagid
	#define EXT_btagreadergettagid
	#define GET_btagreadergettagid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreadergettagid(p0) 
	#define CHK_btagreadergettagid  FALSE
	#define EXP_btagreadergettagid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreadergettagid
	#define EXT_btagreadergettagid
	#define GET_btagreadergettagid(fl)  CAL_CMGETAPI( "btagreadergettagid" ) 
	#define CAL_btagreadergettagid  btagreadergettagid
	#define CHK_btagreadergettagid  TRUE
	#define EXP_btagreadergettagid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergettagid", (RTS_UINTPTR)btagreadergettagid, 1, RTSITF_GET_SIGNATURE(0, 0x597C68FC), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreadergettagid
	#define EXT_btagreadergettagid
	#define GET_btagreadergettagid(fl)  CAL_CMGETAPI( "btagreadergettagid" ) 
	#define CAL_btagreadergettagid  btagreadergettagid
	#define CHK_btagreadergettagid  TRUE
	#define EXP_btagreadergettagid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergettagid", (RTS_UINTPTR)btagreadergettagid, 1, RTSITF_GET_SIGNATURE(0, 0x597C68FC), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreadergettagid
	#define EXT_CmpBinTagUtilIecbtagreadergettagid
	#define GET_CmpBinTagUtilIecbtagreadergettagid  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreadergettagid  btagreadergettagid
	#define CHK_CmpBinTagUtilIecbtagreadergettagid  TRUE
	#define EXP_CmpBinTagUtilIecbtagreadergettagid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergettagid", (RTS_UINTPTR)btagreadergettagid, 1, RTSITF_GET_SIGNATURE(0, 0x597C68FC), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreadergettagid
	#define EXT_btagreadergettagid
	#define GET_btagreadergettagid(fl)  CAL_CMGETAPI( "btagreadergettagid" ) 
	#define CAL_btagreadergettagid  btagreadergettagid
	#define CHK_btagreadergettagid  TRUE
	#define EXP_btagreadergettagid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergettagid", (RTS_UINTPTR)btagreadergettagid, 1, RTSITF_GET_SIGNATURE(0, 0x597C68FC), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreadergettagid  PFBTAGREADERGETTAGID_IEC pfbtagreadergettagid;
	#define EXT_btagreadergettagid  extern PFBTAGREADERGETTAGID_IEC pfbtagreadergettagid;
	#define GET_btagreadergettagid(fl)  s_pfCMGetAPI2( "btagreadergettagid", (RTS_VOID_FCTPTR *)&pfbtagreadergettagid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x597C68FC), 0x03050500)
	#define CAL_btagreadergettagid  pfbtagreadergettagid
	#define CHK_btagreadergettagid  (pfbtagreadergettagid != NULL)
	#define EXP_btagreadergettagid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergettagid", (RTS_UINTPTR)btagreadergettagid, 1, RTSITF_GET_SIGNATURE(0, 0x597C68FC), 0x03050500) 
#endif


/**
 * <description>btagreadergettaglen</description>
 */
typedef struct tagbtagreadergettaglen_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pulTagLen;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderGetTagLen;	/* VAR_OUTPUT */	
} btagreadergettaglen_struct;

void CDECL CDECL_EXT btagreadergettaglen(btagreadergettaglen_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERGETTAGLEN_IEC) (btagreadergettaglen_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERGETTAGLEN_NOTIMPLEMENTED)
	#define USE_btagreadergettaglen
	#define EXT_btagreadergettaglen
	#define GET_btagreadergettaglen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreadergettaglen(p0) 
	#define CHK_btagreadergettaglen  FALSE
	#define EXP_btagreadergettaglen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreadergettaglen
	#define EXT_btagreadergettaglen
	#define GET_btagreadergettaglen(fl)  CAL_CMGETAPI( "btagreadergettaglen" ) 
	#define CAL_btagreadergettaglen  btagreadergettaglen
	#define CHK_btagreadergettaglen  TRUE
	#define EXP_btagreadergettaglen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergettaglen", (RTS_UINTPTR)btagreadergettaglen, 1, RTSITF_GET_SIGNATURE(0, 0xCE73E40F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreadergettaglen
	#define EXT_btagreadergettaglen
	#define GET_btagreadergettaglen(fl)  CAL_CMGETAPI( "btagreadergettaglen" ) 
	#define CAL_btagreadergettaglen  btagreadergettaglen
	#define CHK_btagreadergettaglen  TRUE
	#define EXP_btagreadergettaglen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergettaglen", (RTS_UINTPTR)btagreadergettaglen, 1, RTSITF_GET_SIGNATURE(0, 0xCE73E40F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreadergettaglen
	#define EXT_CmpBinTagUtilIecbtagreadergettaglen
	#define GET_CmpBinTagUtilIecbtagreadergettaglen  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreadergettaglen  btagreadergettaglen
	#define CHK_CmpBinTagUtilIecbtagreadergettaglen  TRUE
	#define EXP_CmpBinTagUtilIecbtagreadergettaglen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergettaglen", (RTS_UINTPTR)btagreadergettaglen, 1, RTSITF_GET_SIGNATURE(0, 0xCE73E40F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreadergettaglen
	#define EXT_btagreadergettaglen
	#define GET_btagreadergettaglen(fl)  CAL_CMGETAPI( "btagreadergettaglen" ) 
	#define CAL_btagreadergettaglen  btagreadergettaglen
	#define CHK_btagreadergettaglen  TRUE
	#define EXP_btagreadergettaglen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergettaglen", (RTS_UINTPTR)btagreadergettaglen, 1, RTSITF_GET_SIGNATURE(0, 0xCE73E40F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreadergettaglen  PFBTAGREADERGETTAGLEN_IEC pfbtagreadergettaglen;
	#define EXT_btagreadergettaglen  extern PFBTAGREADERGETTAGLEN_IEC pfbtagreadergettaglen;
	#define GET_btagreadergettaglen(fl)  s_pfCMGetAPI2( "btagreadergettaglen", (RTS_VOID_FCTPTR *)&pfbtagreadergettaglen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCE73E40F), 0x03050500)
	#define CAL_btagreadergettaglen  pfbtagreadergettaglen
	#define CHK_btagreadergettaglen  (pfbtagreadergettaglen != NULL)
	#define EXP_btagreadergettaglen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadergettaglen", (RTS_UINTPTR)btagreadergettaglen, 1, RTSITF_GET_SIGNATURE(0, 0xCE73E40F), 0x03050500) 
#endif


/**
 * <description>btagreaderinit</description>
 */
typedef struct tagbtagreaderinit_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwBufferSize;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderInit;		/* VAR_OUTPUT */	
} btagreaderinit_struct;

void CDECL CDECL_EXT btagreaderinit(btagreaderinit_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERINIT_IEC) (btagreaderinit_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERINIT_NOTIMPLEMENTED)
	#define USE_btagreaderinit
	#define EXT_btagreaderinit
	#define GET_btagreaderinit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreaderinit(p0) 
	#define CHK_btagreaderinit  FALSE
	#define EXP_btagreaderinit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreaderinit
	#define EXT_btagreaderinit
	#define GET_btagreaderinit(fl)  CAL_CMGETAPI( "btagreaderinit" ) 
	#define CAL_btagreaderinit  btagreaderinit
	#define CHK_btagreaderinit  TRUE
	#define EXP_btagreaderinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderinit", (RTS_UINTPTR)btagreaderinit, 1, RTSITF_GET_SIGNATURE(0, 0x02485C09), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreaderinit
	#define EXT_btagreaderinit
	#define GET_btagreaderinit(fl)  CAL_CMGETAPI( "btagreaderinit" ) 
	#define CAL_btagreaderinit  btagreaderinit
	#define CHK_btagreaderinit  TRUE
	#define EXP_btagreaderinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderinit", (RTS_UINTPTR)btagreaderinit, 1, RTSITF_GET_SIGNATURE(0, 0x02485C09), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreaderinit
	#define EXT_CmpBinTagUtilIecbtagreaderinit
	#define GET_CmpBinTagUtilIecbtagreaderinit  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreaderinit  btagreaderinit
	#define CHK_CmpBinTagUtilIecbtagreaderinit  TRUE
	#define EXP_CmpBinTagUtilIecbtagreaderinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderinit", (RTS_UINTPTR)btagreaderinit, 1, RTSITF_GET_SIGNATURE(0, 0x02485C09), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreaderinit
	#define EXT_btagreaderinit
	#define GET_btagreaderinit(fl)  CAL_CMGETAPI( "btagreaderinit" ) 
	#define CAL_btagreaderinit  btagreaderinit
	#define CHK_btagreaderinit  TRUE
	#define EXP_btagreaderinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderinit", (RTS_UINTPTR)btagreaderinit, 1, RTSITF_GET_SIGNATURE(0, 0x02485C09), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreaderinit  PFBTAGREADERINIT_IEC pfbtagreaderinit;
	#define EXT_btagreaderinit  extern PFBTAGREADERINIT_IEC pfbtagreaderinit;
	#define GET_btagreaderinit(fl)  s_pfCMGetAPI2( "btagreaderinit", (RTS_VOID_FCTPTR *)&pfbtagreaderinit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x02485C09), 0x03050500)
	#define CAL_btagreaderinit  pfbtagreaderinit
	#define CHK_btagreaderinit  (pfbtagreaderinit != NULL)
	#define EXP_btagreaderinit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderinit", (RTS_UINTPTR)btagreaderinit, 1, RTSITF_GET_SIGNATURE(0, 0x02485C09), 0x03050500) 
#endif


/**
 * <description>btagreaderisdatatag</description>
 */
typedef struct tagbtagreaderisdatatag_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_BOOL *pbDataTag;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderIsDataTag;	/* VAR_OUTPUT */	
} btagreaderisdatatag_struct;

void CDECL CDECL_EXT btagreaderisdatatag(btagreaderisdatatag_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERISDATATAG_IEC) (btagreaderisdatatag_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERISDATATAG_NOTIMPLEMENTED)
	#define USE_btagreaderisdatatag
	#define EXT_btagreaderisdatatag
	#define GET_btagreaderisdatatag(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreaderisdatatag(p0) 
	#define CHK_btagreaderisdatatag  FALSE
	#define EXP_btagreaderisdatatag  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreaderisdatatag
	#define EXT_btagreaderisdatatag
	#define GET_btagreaderisdatatag(fl)  CAL_CMGETAPI( "btagreaderisdatatag" ) 
	#define CAL_btagreaderisdatatag  btagreaderisdatatag
	#define CHK_btagreaderisdatatag  TRUE
	#define EXP_btagreaderisdatatag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderisdatatag", (RTS_UINTPTR)btagreaderisdatatag, 1, RTSITF_GET_SIGNATURE(0, 0x0BABA36F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreaderisdatatag
	#define EXT_btagreaderisdatatag
	#define GET_btagreaderisdatatag(fl)  CAL_CMGETAPI( "btagreaderisdatatag" ) 
	#define CAL_btagreaderisdatatag  btagreaderisdatatag
	#define CHK_btagreaderisdatatag  TRUE
	#define EXP_btagreaderisdatatag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderisdatatag", (RTS_UINTPTR)btagreaderisdatatag, 1, RTSITF_GET_SIGNATURE(0, 0x0BABA36F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreaderisdatatag
	#define EXT_CmpBinTagUtilIecbtagreaderisdatatag
	#define GET_CmpBinTagUtilIecbtagreaderisdatatag  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreaderisdatatag  btagreaderisdatatag
	#define CHK_CmpBinTagUtilIecbtagreaderisdatatag  TRUE
	#define EXP_CmpBinTagUtilIecbtagreaderisdatatag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderisdatatag", (RTS_UINTPTR)btagreaderisdatatag, 1, RTSITF_GET_SIGNATURE(0, 0x0BABA36F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreaderisdatatag
	#define EXT_btagreaderisdatatag
	#define GET_btagreaderisdatatag(fl)  CAL_CMGETAPI( "btagreaderisdatatag" ) 
	#define CAL_btagreaderisdatatag  btagreaderisdatatag
	#define CHK_btagreaderisdatatag  TRUE
	#define EXP_btagreaderisdatatag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderisdatatag", (RTS_UINTPTR)btagreaderisdatatag, 1, RTSITF_GET_SIGNATURE(0, 0x0BABA36F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreaderisdatatag  PFBTAGREADERISDATATAG_IEC pfbtagreaderisdatatag;
	#define EXT_btagreaderisdatatag  extern PFBTAGREADERISDATATAG_IEC pfbtagreaderisdatatag;
	#define GET_btagreaderisdatatag(fl)  s_pfCMGetAPI2( "btagreaderisdatatag", (RTS_VOID_FCTPTR *)&pfbtagreaderisdatatag, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0BABA36F), 0x03050500)
	#define CAL_btagreaderisdatatag  pfbtagreaderisdatatag
	#define CHK_btagreaderisdatatag  (pfbtagreaderisdatatag != NULL)
	#define EXP_btagreaderisdatatag   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderisdatatag", (RTS_UINTPTR)btagreaderisdatatag, 1, RTSITF_GET_SIGNATURE(0, 0x0BABA36F), 0x03050500) 
#endif


/**
 * <description>btagreadermovenext</description>
 */
typedef struct tagbtagreadermovenext_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_DINT *pnElementType;		/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderMoveNext;	/* VAR_OUTPUT */	
} btagreadermovenext_struct;

void CDECL CDECL_EXT btagreadermovenext(btagreadermovenext_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERMOVENEXT_IEC) (btagreadermovenext_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERMOVENEXT_NOTIMPLEMENTED)
	#define USE_btagreadermovenext
	#define EXT_btagreadermovenext
	#define GET_btagreadermovenext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreadermovenext(p0) 
	#define CHK_btagreadermovenext  FALSE
	#define EXP_btagreadermovenext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreadermovenext
	#define EXT_btagreadermovenext
	#define GET_btagreadermovenext(fl)  CAL_CMGETAPI( "btagreadermovenext" ) 
	#define CAL_btagreadermovenext  btagreadermovenext
	#define CHK_btagreadermovenext  TRUE
	#define EXP_btagreadermovenext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadermovenext", (RTS_UINTPTR)btagreadermovenext, 1, RTSITF_GET_SIGNATURE(0, 0x4B1EFC23), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreadermovenext
	#define EXT_btagreadermovenext
	#define GET_btagreadermovenext(fl)  CAL_CMGETAPI( "btagreadermovenext" ) 
	#define CAL_btagreadermovenext  btagreadermovenext
	#define CHK_btagreadermovenext  TRUE
	#define EXP_btagreadermovenext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadermovenext", (RTS_UINTPTR)btagreadermovenext, 1, RTSITF_GET_SIGNATURE(0, 0x4B1EFC23), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreadermovenext
	#define EXT_CmpBinTagUtilIecbtagreadermovenext
	#define GET_CmpBinTagUtilIecbtagreadermovenext  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreadermovenext  btagreadermovenext
	#define CHK_CmpBinTagUtilIecbtagreadermovenext  TRUE
	#define EXP_CmpBinTagUtilIecbtagreadermovenext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadermovenext", (RTS_UINTPTR)btagreadermovenext, 1, RTSITF_GET_SIGNATURE(0, 0x4B1EFC23), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreadermovenext
	#define EXT_btagreadermovenext
	#define GET_btagreadermovenext(fl)  CAL_CMGETAPI( "btagreadermovenext" ) 
	#define CAL_btagreadermovenext  btagreadermovenext
	#define CHK_btagreadermovenext  TRUE
	#define EXP_btagreadermovenext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadermovenext", (RTS_UINTPTR)btagreadermovenext, 1, RTSITF_GET_SIGNATURE(0, 0x4B1EFC23), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreadermovenext  PFBTAGREADERMOVENEXT_IEC pfbtagreadermovenext;
	#define EXT_btagreadermovenext  extern PFBTAGREADERMOVENEXT_IEC pfbtagreadermovenext;
	#define GET_btagreadermovenext(fl)  s_pfCMGetAPI2( "btagreadermovenext", (RTS_VOID_FCTPTR *)&pfbtagreadermovenext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4B1EFC23), 0x03050500)
	#define CAL_btagreadermovenext  pfbtagreadermovenext
	#define CHK_btagreadermovenext  (pfbtagreadermovenext != NULL)
	#define EXP_btagreadermovenext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreadermovenext", (RTS_UINTPTR)btagreadermovenext, 1, RTSITF_GET_SIGNATURE(0, 0x4B1EFC23), 0x03050500) 
#endif


/**
 * <description>btagreaderpeeknext</description>
 */
typedef struct tagbtagreaderpeeknext_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_DINT BTagReaderPeekNext;	/* VAR_OUTPUT, Enum: BTAGELEMENTTYPE */
} btagreaderpeeknext_struct;

void CDECL CDECL_EXT btagreaderpeeknext(btagreaderpeeknext_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERPEEKNEXT_IEC) (btagreaderpeeknext_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERPEEKNEXT_NOTIMPLEMENTED)
	#define USE_btagreaderpeeknext
	#define EXT_btagreaderpeeknext
	#define GET_btagreaderpeeknext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreaderpeeknext(p0) 
	#define CHK_btagreaderpeeknext  FALSE
	#define EXP_btagreaderpeeknext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreaderpeeknext
	#define EXT_btagreaderpeeknext
	#define GET_btagreaderpeeknext(fl)  CAL_CMGETAPI( "btagreaderpeeknext" ) 
	#define CAL_btagreaderpeeknext  btagreaderpeeknext
	#define CHK_btagreaderpeeknext  TRUE
	#define EXP_btagreaderpeeknext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderpeeknext", (RTS_UINTPTR)btagreaderpeeknext, 1, RTSITF_GET_SIGNATURE(0, 0x9310CF7A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreaderpeeknext
	#define EXT_btagreaderpeeknext
	#define GET_btagreaderpeeknext(fl)  CAL_CMGETAPI( "btagreaderpeeknext" ) 
	#define CAL_btagreaderpeeknext  btagreaderpeeknext
	#define CHK_btagreaderpeeknext  TRUE
	#define EXP_btagreaderpeeknext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderpeeknext", (RTS_UINTPTR)btagreaderpeeknext, 1, RTSITF_GET_SIGNATURE(0, 0x9310CF7A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreaderpeeknext
	#define EXT_CmpBinTagUtilIecbtagreaderpeeknext
	#define GET_CmpBinTagUtilIecbtagreaderpeeknext  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreaderpeeknext  btagreaderpeeknext
	#define CHK_CmpBinTagUtilIecbtagreaderpeeknext  TRUE
	#define EXP_CmpBinTagUtilIecbtagreaderpeeknext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderpeeknext", (RTS_UINTPTR)btagreaderpeeknext, 1, RTSITF_GET_SIGNATURE(0, 0x9310CF7A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreaderpeeknext
	#define EXT_btagreaderpeeknext
	#define GET_btagreaderpeeknext(fl)  CAL_CMGETAPI( "btagreaderpeeknext" ) 
	#define CAL_btagreaderpeeknext  btagreaderpeeknext
	#define CHK_btagreaderpeeknext  TRUE
	#define EXP_btagreaderpeeknext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderpeeknext", (RTS_UINTPTR)btagreaderpeeknext, 1, RTSITF_GET_SIGNATURE(0, 0x9310CF7A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreaderpeeknext  PFBTAGREADERPEEKNEXT_IEC pfbtagreaderpeeknext;
	#define EXT_btagreaderpeeknext  extern PFBTAGREADERPEEKNEXT_IEC pfbtagreaderpeeknext;
	#define GET_btagreaderpeeknext(fl)  s_pfCMGetAPI2( "btagreaderpeeknext", (RTS_VOID_FCTPTR *)&pfbtagreaderpeeknext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9310CF7A), 0x03050500)
	#define CAL_btagreaderpeeknext  pfbtagreaderpeeknext
	#define CHK_btagreaderpeeknext  (pfbtagreaderpeeknext != NULL)
	#define EXP_btagreaderpeeknext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderpeeknext", (RTS_UINTPTR)btagreaderpeeknext, 1, RTSITF_GET_SIGNATURE(0, 0x9310CF7A), 0x03050500) 
#endif


/**
 * <description>btagreaderskipcontent</description>
 */
typedef struct tagbtagreaderskipcontent_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderSkipContent;	/* VAR_OUTPUT */	
} btagreaderskipcontent_struct;

void CDECL CDECL_EXT btagreaderskipcontent(btagreaderskipcontent_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGREADERSKIPCONTENT_IEC) (btagreaderskipcontent_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGREADERSKIPCONTENT_NOTIMPLEMENTED)
	#define USE_btagreaderskipcontent
	#define EXT_btagreaderskipcontent
	#define GET_btagreaderskipcontent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagreaderskipcontent(p0) 
	#define CHK_btagreaderskipcontent  FALSE
	#define EXP_btagreaderskipcontent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagreaderskipcontent
	#define EXT_btagreaderskipcontent
	#define GET_btagreaderskipcontent(fl)  CAL_CMGETAPI( "btagreaderskipcontent" ) 
	#define CAL_btagreaderskipcontent  btagreaderskipcontent
	#define CHK_btagreaderskipcontent  TRUE
	#define EXP_btagreaderskipcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderskipcontent", (RTS_UINTPTR)btagreaderskipcontent, 1, RTSITF_GET_SIGNATURE(0, 0x4BB13EDE), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagreaderskipcontent
	#define EXT_btagreaderskipcontent
	#define GET_btagreaderskipcontent(fl)  CAL_CMGETAPI( "btagreaderskipcontent" ) 
	#define CAL_btagreaderskipcontent  btagreaderskipcontent
	#define CHK_btagreaderskipcontent  TRUE
	#define EXP_btagreaderskipcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderskipcontent", (RTS_UINTPTR)btagreaderskipcontent, 1, RTSITF_GET_SIGNATURE(0, 0x4BB13EDE), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagreaderskipcontent
	#define EXT_CmpBinTagUtilIecbtagreaderskipcontent
	#define GET_CmpBinTagUtilIecbtagreaderskipcontent  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagreaderskipcontent  btagreaderskipcontent
	#define CHK_CmpBinTagUtilIecbtagreaderskipcontent  TRUE
	#define EXP_CmpBinTagUtilIecbtagreaderskipcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderskipcontent", (RTS_UINTPTR)btagreaderskipcontent, 1, RTSITF_GET_SIGNATURE(0, 0x4BB13EDE), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagreaderskipcontent
	#define EXT_btagreaderskipcontent
	#define GET_btagreaderskipcontent(fl)  CAL_CMGETAPI( "btagreaderskipcontent" ) 
	#define CAL_btagreaderskipcontent  btagreaderskipcontent
	#define CHK_btagreaderskipcontent  TRUE
	#define EXP_btagreaderskipcontent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderskipcontent", (RTS_UINTPTR)btagreaderskipcontent, 1, RTSITF_GET_SIGNATURE(0, 0x4BB13EDE), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagreaderskipcontent  PFBTAGREADERSKIPCONTENT_IEC pfbtagreaderskipcontent;
	#define EXT_btagreaderskipcontent  extern PFBTAGREADERSKIPCONTENT_IEC pfbtagreaderskipcontent;
	#define GET_btagreaderskipcontent(fl)  s_pfCMGetAPI2( "btagreaderskipcontent", (RTS_VOID_FCTPTR *)&pfbtagreaderskipcontent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4BB13EDE), 0x03050500)
	#define CAL_btagreaderskipcontent  pfbtagreaderskipcontent
	#define CHK_btagreaderskipcontent  (pfbtagreaderskipcontent != NULL)
	#define EXP_btagreaderskipcontent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagreaderskipcontent", (RTS_UINTPTR)btagreaderskipcontent, 1, RTSITF_GET_SIGNATURE(0, 0x4BB13EDE), 0x03050500) 
#endif


/**
 * <description>btagswapheader</description>
 */
typedef struct tagbtagswapheader_struct
{
	RTS_IEC_DWORD *pHeaderTag;			/* VAR_INPUT */	/* A pointer to the header tag that has to be swapped correctly */
	RTS_IEC_DINT bSwap;					/* VAR_INPUT */	/* Determines if the header should be swapped (1) or not (0) */
	RTS_IEC_DWORD BTagSwapHeader;		/* VAR_OUTPUT */	
} btagswapheader_struct;

void CDECL CDECL_EXT btagswapheader(btagswapheader_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGSWAPHEADER_IEC) (btagswapheader_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGSWAPHEADER_NOTIMPLEMENTED)
	#define USE_btagswapheader
	#define EXT_btagswapheader
	#define GET_btagswapheader(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagswapheader(p0) 
	#define CHK_btagswapheader  FALSE
	#define EXP_btagswapheader  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagswapheader
	#define EXT_btagswapheader
	#define GET_btagswapheader(fl)  CAL_CMGETAPI( "btagswapheader" ) 
	#define CAL_btagswapheader  btagswapheader
	#define CHK_btagswapheader  TRUE
	#define EXP_btagswapheader  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagswapheader", (RTS_UINTPTR)btagswapheader, 1, 0x5C8E76D6, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagswapheader
	#define EXT_btagswapheader
	#define GET_btagswapheader(fl)  CAL_CMGETAPI( "btagswapheader" ) 
	#define CAL_btagswapheader  btagswapheader
	#define CHK_btagswapheader  TRUE
	#define EXP_btagswapheader  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagswapheader", (RTS_UINTPTR)btagswapheader, 1, 0x5C8E76D6, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagswapheader
	#define EXT_CmpBinTagUtilIecbtagswapheader
	#define GET_CmpBinTagUtilIecbtagswapheader  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagswapheader  btagswapheader
	#define CHK_CmpBinTagUtilIecbtagswapheader  TRUE
	#define EXP_CmpBinTagUtilIecbtagswapheader  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagswapheader", (RTS_UINTPTR)btagswapheader, 1, 0x5C8E76D6, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagswapheader
	#define EXT_btagswapheader
	#define GET_btagswapheader(fl)  CAL_CMGETAPI( "btagswapheader" ) 
	#define CAL_btagswapheader  btagswapheader
	#define CHK_btagswapheader  TRUE
	#define EXP_btagswapheader  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagswapheader", (RTS_UINTPTR)btagswapheader, 1, 0x5C8E76D6, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagswapheader  PFBTAGSWAPHEADER_IEC pfbtagswapheader;
	#define EXT_btagswapheader  extern PFBTAGSWAPHEADER_IEC pfbtagswapheader;
	#define GET_btagswapheader(fl)  s_pfCMGetAPI2( "btagswapheader", (RTS_VOID_FCTPTR *)&pfbtagswapheader, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x5C8E76D6, 0x03050500)
	#define CAL_btagswapheader  pfbtagswapheader
	#define CHK_btagswapheader  (pfbtagswapheader != NULL)
	#define EXP_btagswapheader   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagswapheader", (RTS_UINTPTR)btagswapheader, 1, 0x5C8E76D6, 0x03050500) 
#endif


/**
 * <description>btagwriterappendblob</description>
 */
typedef struct tagbtagwriterappendblob_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwDataSize;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterAppendBlob;	/* VAR_OUTPUT */	
} btagwriterappendblob_struct;

void CDECL CDECL_EXT btagwriterappendblob(btagwriterappendblob_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERAPPENDBLOB_IEC) (btagwriterappendblob_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERAPPENDBLOB_NOTIMPLEMENTED)
	#define USE_btagwriterappendblob
	#define EXT_btagwriterappendblob
	#define GET_btagwriterappendblob(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterappendblob(p0) 
	#define CHK_btagwriterappendblob  FALSE
	#define EXP_btagwriterappendblob  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterappendblob
	#define EXT_btagwriterappendblob
	#define GET_btagwriterappendblob(fl)  CAL_CMGETAPI( "btagwriterappendblob" ) 
	#define CAL_btagwriterappendblob  btagwriterappendblob
	#define CHK_btagwriterappendblob  TRUE
	#define EXP_btagwriterappendblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendblob", (RTS_UINTPTR)btagwriterappendblob, 1, RTSITF_GET_SIGNATURE(0, 0xDF96F47F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterappendblob
	#define EXT_btagwriterappendblob
	#define GET_btagwriterappendblob(fl)  CAL_CMGETAPI( "btagwriterappendblob" ) 
	#define CAL_btagwriterappendblob  btagwriterappendblob
	#define CHK_btagwriterappendblob  TRUE
	#define EXP_btagwriterappendblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendblob", (RTS_UINTPTR)btagwriterappendblob, 1, RTSITF_GET_SIGNATURE(0, 0xDF96F47F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterappendblob
	#define EXT_CmpBinTagUtilIecbtagwriterappendblob
	#define GET_CmpBinTagUtilIecbtagwriterappendblob  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterappendblob  btagwriterappendblob
	#define CHK_CmpBinTagUtilIecbtagwriterappendblob  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterappendblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendblob", (RTS_UINTPTR)btagwriterappendblob, 1, RTSITF_GET_SIGNATURE(0, 0xDF96F47F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterappendblob
	#define EXT_btagwriterappendblob
	#define GET_btagwriterappendblob(fl)  CAL_CMGETAPI( "btagwriterappendblob" ) 
	#define CAL_btagwriterappendblob  btagwriterappendblob
	#define CHK_btagwriterappendblob  TRUE
	#define EXP_btagwriterappendblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendblob", (RTS_UINTPTR)btagwriterappendblob, 1, RTSITF_GET_SIGNATURE(0, 0xDF96F47F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterappendblob  PFBTAGWRITERAPPENDBLOB_IEC pfbtagwriterappendblob;
	#define EXT_btagwriterappendblob  extern PFBTAGWRITERAPPENDBLOB_IEC pfbtagwriterappendblob;
	#define GET_btagwriterappendblob(fl)  s_pfCMGetAPI2( "btagwriterappendblob", (RTS_VOID_FCTPTR *)&pfbtagwriterappendblob, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDF96F47F), 0x03050500)
	#define CAL_btagwriterappendblob  pfbtagwriterappendblob
	#define CHK_btagwriterappendblob  (pfbtagwriterappendblob != NULL)
	#define EXP_btagwriterappendblob   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendblob", (RTS_UINTPTR)btagwriterappendblob, 1, RTSITF_GET_SIGNATURE(0, 0xDF96F47F), 0x03050500) 
#endif


/**
 * <description>btagwriterappenddummybytes</description>
 */
typedef struct tagbtagwriterappenddummybytes_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE btFill;				/* VAR_INPUT */	
	RTS_IEC_DWORD ulCount;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterAppendDummyBytes;	/* VAR_OUTPUT */	
} btagwriterappenddummybytes_struct;

void CDECL CDECL_EXT btagwriterappenddummybytes(btagwriterappenddummybytes_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERAPPENDDUMMYBYTES_IEC) (btagwriterappenddummybytes_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERAPPENDDUMMYBYTES_NOTIMPLEMENTED)
	#define USE_btagwriterappenddummybytes
	#define EXT_btagwriterappenddummybytes
	#define GET_btagwriterappenddummybytes(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterappenddummybytes(p0) 
	#define CHK_btagwriterappenddummybytes  FALSE
	#define EXP_btagwriterappenddummybytes  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterappenddummybytes
	#define EXT_btagwriterappenddummybytes
	#define GET_btagwriterappenddummybytes(fl)  CAL_CMGETAPI( "btagwriterappenddummybytes" ) 
	#define CAL_btagwriterappenddummybytes  btagwriterappenddummybytes
	#define CHK_btagwriterappenddummybytes  TRUE
	#define EXP_btagwriterappenddummybytes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappenddummybytes", (RTS_UINTPTR)btagwriterappenddummybytes, 1, RTSITF_GET_SIGNATURE(0, 0xDDDCB7E7), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterappenddummybytes
	#define EXT_btagwriterappenddummybytes
	#define GET_btagwriterappenddummybytes(fl)  CAL_CMGETAPI( "btagwriterappenddummybytes" ) 
	#define CAL_btagwriterappenddummybytes  btagwriterappenddummybytes
	#define CHK_btagwriterappenddummybytes  TRUE
	#define EXP_btagwriterappenddummybytes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappenddummybytes", (RTS_UINTPTR)btagwriterappenddummybytes, 1, RTSITF_GET_SIGNATURE(0, 0xDDDCB7E7), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterappenddummybytes
	#define EXT_CmpBinTagUtilIecbtagwriterappenddummybytes
	#define GET_CmpBinTagUtilIecbtagwriterappenddummybytes  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterappenddummybytes  btagwriterappenddummybytes
	#define CHK_CmpBinTagUtilIecbtagwriterappenddummybytes  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterappenddummybytes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappenddummybytes", (RTS_UINTPTR)btagwriterappenddummybytes, 1, RTSITF_GET_SIGNATURE(0, 0xDDDCB7E7), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterappenddummybytes
	#define EXT_btagwriterappenddummybytes
	#define GET_btagwriterappenddummybytes(fl)  CAL_CMGETAPI( "btagwriterappenddummybytes" ) 
	#define CAL_btagwriterappenddummybytes  btagwriterappenddummybytes
	#define CHK_btagwriterappenddummybytes  TRUE
	#define EXP_btagwriterappenddummybytes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappenddummybytes", (RTS_UINTPTR)btagwriterappenddummybytes, 1, RTSITF_GET_SIGNATURE(0, 0xDDDCB7E7), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterappenddummybytes  PFBTAGWRITERAPPENDDUMMYBYTES_IEC pfbtagwriterappenddummybytes;
	#define EXT_btagwriterappenddummybytes  extern PFBTAGWRITERAPPENDDUMMYBYTES_IEC pfbtagwriterappenddummybytes;
	#define GET_btagwriterappenddummybytes(fl)  s_pfCMGetAPI2( "btagwriterappenddummybytes", (RTS_VOID_FCTPTR *)&pfbtagwriterappenddummybytes, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDDDCB7E7), 0x03050500)
	#define CAL_btagwriterappenddummybytes  pfbtagwriterappenddummybytes
	#define CHK_btagwriterappenddummybytes  (pfbtagwriterappenddummybytes != NULL)
	#define EXP_btagwriterappenddummybytes   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappenddummybytes", (RTS_UINTPTR)btagwriterappenddummybytes, 1, RTSITF_GET_SIGNATURE(0, 0xDDDCB7E7), 0x03050500) 
#endif


/**
 * <description>btagwriterappendfillbytes</description>
 */
typedef struct tagbtagwriterappendfillbytes_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE btFill;				/* VAR_INPUT */	
	BTagAlignment alignment;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterAppendFillBytes;	/* VAR_OUTPUT */	
} btagwriterappendfillbytes_struct;

void CDECL CDECL_EXT btagwriterappendfillbytes(btagwriterappendfillbytes_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERAPPENDFILLBYTES_IEC) (btagwriterappendfillbytes_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERAPPENDFILLBYTES_NOTIMPLEMENTED)
	#define USE_btagwriterappendfillbytes
	#define EXT_btagwriterappendfillbytes
	#define GET_btagwriterappendfillbytes(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterappendfillbytes(p0) 
	#define CHK_btagwriterappendfillbytes  FALSE
	#define EXP_btagwriterappendfillbytes  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterappendfillbytes
	#define EXT_btagwriterappendfillbytes
	#define GET_btagwriterappendfillbytes(fl)  CAL_CMGETAPI( "btagwriterappendfillbytes" ) 
	#define CAL_btagwriterappendfillbytes  btagwriterappendfillbytes
	#define CHK_btagwriterappendfillbytes  TRUE
	#define EXP_btagwriterappendfillbytes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendfillbytes", (RTS_UINTPTR)btagwriterappendfillbytes, 1, RTSITF_GET_SIGNATURE(0, 0x4EFA2ED1), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterappendfillbytes
	#define EXT_btagwriterappendfillbytes
	#define GET_btagwriterappendfillbytes(fl)  CAL_CMGETAPI( "btagwriterappendfillbytes" ) 
	#define CAL_btagwriterappendfillbytes  btagwriterappendfillbytes
	#define CHK_btagwriterappendfillbytes  TRUE
	#define EXP_btagwriterappendfillbytes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendfillbytes", (RTS_UINTPTR)btagwriterappendfillbytes, 1, RTSITF_GET_SIGNATURE(0, 0x4EFA2ED1), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterappendfillbytes
	#define EXT_CmpBinTagUtilIecbtagwriterappendfillbytes
	#define GET_CmpBinTagUtilIecbtagwriterappendfillbytes  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterappendfillbytes  btagwriterappendfillbytes
	#define CHK_CmpBinTagUtilIecbtagwriterappendfillbytes  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterappendfillbytes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendfillbytes", (RTS_UINTPTR)btagwriterappendfillbytes, 1, RTSITF_GET_SIGNATURE(0, 0x4EFA2ED1), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterappendfillbytes
	#define EXT_btagwriterappendfillbytes
	#define GET_btagwriterappendfillbytes(fl)  CAL_CMGETAPI( "btagwriterappendfillbytes" ) 
	#define CAL_btagwriterappendfillbytes  btagwriterappendfillbytes
	#define CHK_btagwriterappendfillbytes  TRUE
	#define EXP_btagwriterappendfillbytes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendfillbytes", (RTS_UINTPTR)btagwriterappendfillbytes, 1, RTSITF_GET_SIGNATURE(0, 0x4EFA2ED1), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterappendfillbytes  PFBTAGWRITERAPPENDFILLBYTES_IEC pfbtagwriterappendfillbytes;
	#define EXT_btagwriterappendfillbytes  extern PFBTAGWRITERAPPENDFILLBYTES_IEC pfbtagwriterappendfillbytes;
	#define GET_btagwriterappendfillbytes(fl)  s_pfCMGetAPI2( "btagwriterappendfillbytes", (RTS_VOID_FCTPTR *)&pfbtagwriterappendfillbytes, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4EFA2ED1), 0x03050500)
	#define CAL_btagwriterappendfillbytes  pfbtagwriterappendfillbytes
	#define CHK_btagwriterappendfillbytes  (pfbtagwriterappendfillbytes != NULL)
	#define EXP_btagwriterappendfillbytes   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendfillbytes", (RTS_UINTPTR)btagwriterappendfillbytes, 1, RTSITF_GET_SIGNATURE(0, 0x4EFA2ED1), 0x03050500) 
#endif


/**
 * <description>btagwriterappendraw</description>
 */
typedef struct tagbtagwriterappendraw_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE **ppData;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterAppendRaw;	/* VAR_OUTPUT */	
} btagwriterappendraw_struct;

void CDECL CDECL_EXT btagwriterappendraw(btagwriterappendraw_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERAPPENDRAW_IEC) (btagwriterappendraw_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERAPPENDRAW_NOTIMPLEMENTED)
	#define USE_btagwriterappendraw
	#define EXT_btagwriterappendraw
	#define GET_btagwriterappendraw(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterappendraw(p0) 
	#define CHK_btagwriterappendraw  FALSE
	#define EXP_btagwriterappendraw  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterappendraw
	#define EXT_btagwriterappendraw
	#define GET_btagwriterappendraw(fl)  CAL_CMGETAPI( "btagwriterappendraw" ) 
	#define CAL_btagwriterappendraw  btagwriterappendraw
	#define CHK_btagwriterappendraw  TRUE
	#define EXP_btagwriterappendraw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendraw", (RTS_UINTPTR)btagwriterappendraw, 1, RTSITF_GET_SIGNATURE(0, 0xBB6DE51A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterappendraw
	#define EXT_btagwriterappendraw
	#define GET_btagwriterappendraw(fl)  CAL_CMGETAPI( "btagwriterappendraw" ) 
	#define CAL_btagwriterappendraw  btagwriterappendraw
	#define CHK_btagwriterappendraw  TRUE
	#define EXP_btagwriterappendraw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendraw", (RTS_UINTPTR)btagwriterappendraw, 1, RTSITF_GET_SIGNATURE(0, 0xBB6DE51A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterappendraw
	#define EXT_CmpBinTagUtilIecbtagwriterappendraw
	#define GET_CmpBinTagUtilIecbtagwriterappendraw  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterappendraw  btagwriterappendraw
	#define CHK_CmpBinTagUtilIecbtagwriterappendraw  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterappendraw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendraw", (RTS_UINTPTR)btagwriterappendraw, 1, RTSITF_GET_SIGNATURE(0, 0xBB6DE51A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterappendraw
	#define EXT_btagwriterappendraw
	#define GET_btagwriterappendraw(fl)  CAL_CMGETAPI( "btagwriterappendraw" ) 
	#define CAL_btagwriterappendraw  btagwriterappendraw
	#define CHK_btagwriterappendraw  TRUE
	#define EXP_btagwriterappendraw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendraw", (RTS_UINTPTR)btagwriterappendraw, 1, RTSITF_GET_SIGNATURE(0, 0xBB6DE51A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterappendraw  PFBTAGWRITERAPPENDRAW_IEC pfbtagwriterappendraw;
	#define EXT_btagwriterappendraw  extern PFBTAGWRITERAPPENDRAW_IEC pfbtagwriterappendraw;
	#define GET_btagwriterappendraw(fl)  s_pfCMGetAPI2( "btagwriterappendraw", (RTS_VOID_FCTPTR *)&pfbtagwriterappendraw, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xBB6DE51A), 0x03050500)
	#define CAL_btagwriterappendraw  pfbtagwriterappendraw
	#define CHK_btagwriterappendraw  (pfbtagwriterappendraw != NULL)
	#define EXP_btagwriterappendraw   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendraw", (RTS_UINTPTR)btagwriterappendraw, 1, RTSITF_GET_SIGNATURE(0, 0xBB6DE51A), 0x03050500) 
#endif


/**
 * <description>btagwriterappendwstring</description>
 */
typedef struct tagbtagwriterappendwstring_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_WSTRING *wszString;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterAppendWString;	/* VAR_OUTPUT */	
} btagwriterappendwstring_struct;

void CDECL CDECL_EXT btagwriterappendwstring(btagwriterappendwstring_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERAPPENDWSTRING_IEC) (btagwriterappendwstring_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERAPPENDWSTRING_NOTIMPLEMENTED)
	#define USE_btagwriterappendwstring
	#define EXT_btagwriterappendwstring
	#define GET_btagwriterappendwstring(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterappendwstring(p0) 
	#define CHK_btagwriterappendwstring  FALSE
	#define EXP_btagwriterappendwstring  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterappendwstring
	#define EXT_btagwriterappendwstring
	#define GET_btagwriterappendwstring(fl)  CAL_CMGETAPI( "btagwriterappendwstring" ) 
	#define CAL_btagwriterappendwstring  btagwriterappendwstring
	#define CHK_btagwriterappendwstring  TRUE
	#define EXP_btagwriterappendwstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendwstring", (RTS_UINTPTR)btagwriterappendwstring, 1, RTSITF_GET_SIGNATURE(0, 0xF11A95EC), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterappendwstring
	#define EXT_btagwriterappendwstring
	#define GET_btagwriterappendwstring(fl)  CAL_CMGETAPI( "btagwriterappendwstring" ) 
	#define CAL_btagwriterappendwstring  btagwriterappendwstring
	#define CHK_btagwriterappendwstring  TRUE
	#define EXP_btagwriterappendwstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendwstring", (RTS_UINTPTR)btagwriterappendwstring, 1, RTSITF_GET_SIGNATURE(0, 0xF11A95EC), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterappendwstring
	#define EXT_CmpBinTagUtilIecbtagwriterappendwstring
	#define GET_CmpBinTagUtilIecbtagwriterappendwstring  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterappendwstring  btagwriterappendwstring
	#define CHK_CmpBinTagUtilIecbtagwriterappendwstring  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterappendwstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendwstring", (RTS_UINTPTR)btagwriterappendwstring, 1, RTSITF_GET_SIGNATURE(0, 0xF11A95EC), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterappendwstring
	#define EXT_btagwriterappendwstring
	#define GET_btagwriterappendwstring(fl)  CAL_CMGETAPI( "btagwriterappendwstring" ) 
	#define CAL_btagwriterappendwstring  btagwriterappendwstring
	#define CHK_btagwriterappendwstring  TRUE
	#define EXP_btagwriterappendwstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendwstring", (RTS_UINTPTR)btagwriterappendwstring, 1, RTSITF_GET_SIGNATURE(0, 0xF11A95EC), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterappendwstring  PFBTAGWRITERAPPENDWSTRING_IEC pfbtagwriterappendwstring;
	#define EXT_btagwriterappendwstring  extern PFBTAGWRITERAPPENDWSTRING_IEC pfbtagwriterappendwstring;
	#define GET_btagwriterappendwstring(fl)  s_pfCMGetAPI2( "btagwriterappendwstring", (RTS_VOID_FCTPTR *)&pfbtagwriterappendwstring, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF11A95EC), 0x03050500)
	#define CAL_btagwriterappendwstring  pfbtagwriterappendwstring
	#define CHK_btagwriterappendwstring  (pfbtagwriterappendwstring != NULL)
	#define EXP_btagwriterappendwstring   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterappendwstring", (RTS_UINTPTR)btagwriterappendwstring, 1, RTSITF_GET_SIGNATURE(0, 0xF11A95EC), 0x03050500) 
#endif


/**
 * <description>btagwritercreate</description>
 */
typedef struct tagbtagwritercreate_struct
{
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagWriterCreate;	/* VAR_OUTPUT */	
} btagwritercreate_struct;

void CDECL CDECL_EXT btagwritercreate(btagwritercreate_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERCREATE_IEC) (btagwritercreate_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERCREATE_NOTIMPLEMENTED)
	#define USE_btagwritercreate
	#define EXT_btagwritercreate
	#define GET_btagwritercreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwritercreate(p0) 
	#define CHK_btagwritercreate  FALSE
	#define EXP_btagwritercreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwritercreate
	#define EXT_btagwritercreate
	#define GET_btagwritercreate(fl)  CAL_CMGETAPI( "btagwritercreate" ) 
	#define CAL_btagwritercreate  btagwritercreate
	#define CHK_btagwritercreate  TRUE
	#define EXP_btagwritercreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreate", (RTS_UINTPTR)btagwritercreate, 1, RTSITF_GET_SIGNATURE(0, 0xB9D46425), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwritercreate
	#define EXT_btagwritercreate
	#define GET_btagwritercreate(fl)  CAL_CMGETAPI( "btagwritercreate" ) 
	#define CAL_btagwritercreate  btagwritercreate
	#define CHK_btagwritercreate  TRUE
	#define EXP_btagwritercreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreate", (RTS_UINTPTR)btagwritercreate, 1, RTSITF_GET_SIGNATURE(0, 0xB9D46425), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwritercreate
	#define EXT_CmpBinTagUtilIecbtagwritercreate
	#define GET_CmpBinTagUtilIecbtagwritercreate  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwritercreate  btagwritercreate
	#define CHK_CmpBinTagUtilIecbtagwritercreate  TRUE
	#define EXP_CmpBinTagUtilIecbtagwritercreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreate", (RTS_UINTPTR)btagwritercreate, 1, RTSITF_GET_SIGNATURE(0, 0xB9D46425), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwritercreate
	#define EXT_btagwritercreate
	#define GET_btagwritercreate(fl)  CAL_CMGETAPI( "btagwritercreate" ) 
	#define CAL_btagwritercreate  btagwritercreate
	#define CHK_btagwritercreate  TRUE
	#define EXP_btagwritercreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreate", (RTS_UINTPTR)btagwritercreate, 1, RTSITF_GET_SIGNATURE(0, 0xB9D46425), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwritercreate  PFBTAGWRITERCREATE_IEC pfbtagwritercreate;
	#define EXT_btagwritercreate  extern PFBTAGWRITERCREATE_IEC pfbtagwritercreate;
	#define GET_btagwritercreate(fl)  s_pfCMGetAPI2( "btagwritercreate", (RTS_VOID_FCTPTR *)&pfbtagwritercreate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB9D46425), 0x03050500)
	#define CAL_btagwritercreate  pfbtagwritercreate
	#define CHK_btagwritercreate  (pfbtagwritercreate != NULL)
	#define EXP_btagwritercreate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreate", (RTS_UINTPTR)btagwritercreate, 1, RTSITF_GET_SIGNATURE(0, 0xB9D46425), 0x03050500) 
#endif


/**
 * <description>btagwritercreatedynamic</description>
 */
typedef struct tagbtagwritercreatedynamic_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagWriterCreateDynamic;	/* VAR_OUTPUT */	
} btagwritercreatedynamic_struct;

void CDECL CDECL_EXT btagwritercreatedynamic(btagwritercreatedynamic_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERCREATEDYNAMIC_IEC) (btagwritercreatedynamic_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERCREATEDYNAMIC_NOTIMPLEMENTED)
	#define USE_btagwritercreatedynamic
	#define EXT_btagwritercreatedynamic
	#define GET_btagwritercreatedynamic(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwritercreatedynamic(p0) 
	#define CHK_btagwritercreatedynamic  FALSE
	#define EXP_btagwritercreatedynamic  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwritercreatedynamic
	#define EXT_btagwritercreatedynamic
	#define GET_btagwritercreatedynamic(fl)  CAL_CMGETAPI( "btagwritercreatedynamic" ) 
	#define CAL_btagwritercreatedynamic  btagwritercreatedynamic
	#define CHK_btagwritercreatedynamic  TRUE
	#define EXP_btagwritercreatedynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatedynamic", (RTS_UINTPTR)btagwritercreatedynamic, 1, RTSITF_GET_SIGNATURE(0, 0x3E261347), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwritercreatedynamic
	#define EXT_btagwritercreatedynamic
	#define GET_btagwritercreatedynamic(fl)  CAL_CMGETAPI( "btagwritercreatedynamic" ) 
	#define CAL_btagwritercreatedynamic  btagwritercreatedynamic
	#define CHK_btagwritercreatedynamic  TRUE
	#define EXP_btagwritercreatedynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatedynamic", (RTS_UINTPTR)btagwritercreatedynamic, 1, RTSITF_GET_SIGNATURE(0, 0x3E261347), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwritercreatedynamic
	#define EXT_CmpBinTagUtilIecbtagwritercreatedynamic
	#define GET_CmpBinTagUtilIecbtagwritercreatedynamic  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwritercreatedynamic  btagwritercreatedynamic
	#define CHK_CmpBinTagUtilIecbtagwritercreatedynamic  TRUE
	#define EXP_CmpBinTagUtilIecbtagwritercreatedynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatedynamic", (RTS_UINTPTR)btagwritercreatedynamic, 1, RTSITF_GET_SIGNATURE(0, 0x3E261347), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwritercreatedynamic
	#define EXT_btagwritercreatedynamic
	#define GET_btagwritercreatedynamic(fl)  CAL_CMGETAPI( "btagwritercreatedynamic" ) 
	#define CAL_btagwritercreatedynamic  btagwritercreatedynamic
	#define CHK_btagwritercreatedynamic  TRUE
	#define EXP_btagwritercreatedynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatedynamic", (RTS_UINTPTR)btagwritercreatedynamic, 1, RTSITF_GET_SIGNATURE(0, 0x3E261347), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwritercreatedynamic  PFBTAGWRITERCREATEDYNAMIC_IEC pfbtagwritercreatedynamic;
	#define EXT_btagwritercreatedynamic  extern PFBTAGWRITERCREATEDYNAMIC_IEC pfbtagwritercreatedynamic;
	#define GET_btagwritercreatedynamic(fl)  s_pfCMGetAPI2( "btagwritercreatedynamic", (RTS_VOID_FCTPTR *)&pfbtagwritercreatedynamic, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x3E261347), 0x03050500)
	#define CAL_btagwritercreatedynamic  pfbtagwritercreatedynamic
	#define CHK_btagwritercreatedynamic  (pfbtagwritercreatedynamic != NULL)
	#define EXP_btagwritercreatedynamic   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatedynamic", (RTS_UINTPTR)btagwritercreatedynamic, 1, RTSITF_GET_SIGNATURE(0, 0x3E261347), 0x03050500) 
#endif


/**
 * <description>btagwritercreatesavepoint</description>
 */
typedef struct tagbtagwritercreatesavepoint_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwDataSize;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagWriterCreateSavePoint;	/* VAR_OUTPUT */	
} btagwritercreatesavepoint_struct;

void CDECL CDECL_EXT btagwritercreatesavepoint(btagwritercreatesavepoint_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERCREATESAVEPOINT_IEC) (btagwritercreatesavepoint_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERCREATESAVEPOINT_NOTIMPLEMENTED)
	#define USE_btagwritercreatesavepoint
	#define EXT_btagwritercreatesavepoint
	#define GET_btagwritercreatesavepoint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwritercreatesavepoint(p0) 
	#define CHK_btagwritercreatesavepoint  FALSE
	#define EXP_btagwritercreatesavepoint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwritercreatesavepoint
	#define EXT_btagwritercreatesavepoint
	#define GET_btagwritercreatesavepoint(fl)  CAL_CMGETAPI( "btagwritercreatesavepoint" ) 
	#define CAL_btagwritercreatesavepoint  btagwritercreatesavepoint
	#define CHK_btagwritercreatesavepoint  TRUE
	#define EXP_btagwritercreatesavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatesavepoint", (RTS_UINTPTR)btagwritercreatesavepoint, 1, RTSITF_GET_SIGNATURE(0, 0xA762E901), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwritercreatesavepoint
	#define EXT_btagwritercreatesavepoint
	#define GET_btagwritercreatesavepoint(fl)  CAL_CMGETAPI( "btagwritercreatesavepoint" ) 
	#define CAL_btagwritercreatesavepoint  btagwritercreatesavepoint
	#define CHK_btagwritercreatesavepoint  TRUE
	#define EXP_btagwritercreatesavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatesavepoint", (RTS_UINTPTR)btagwritercreatesavepoint, 1, RTSITF_GET_SIGNATURE(0, 0xA762E901), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwritercreatesavepoint
	#define EXT_CmpBinTagUtilIecbtagwritercreatesavepoint
	#define GET_CmpBinTagUtilIecbtagwritercreatesavepoint  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwritercreatesavepoint  btagwritercreatesavepoint
	#define CHK_CmpBinTagUtilIecbtagwritercreatesavepoint  TRUE
	#define EXP_CmpBinTagUtilIecbtagwritercreatesavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatesavepoint", (RTS_UINTPTR)btagwritercreatesavepoint, 1, RTSITF_GET_SIGNATURE(0, 0xA762E901), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwritercreatesavepoint
	#define EXT_btagwritercreatesavepoint
	#define GET_btagwritercreatesavepoint(fl)  CAL_CMGETAPI( "btagwritercreatesavepoint" ) 
	#define CAL_btagwritercreatesavepoint  btagwritercreatesavepoint
	#define CHK_btagwritercreatesavepoint  TRUE
	#define EXP_btagwritercreatesavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatesavepoint", (RTS_UINTPTR)btagwritercreatesavepoint, 1, RTSITF_GET_SIGNATURE(0, 0xA762E901), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwritercreatesavepoint  PFBTAGWRITERCREATESAVEPOINT_IEC pfbtagwritercreatesavepoint;
	#define EXT_btagwritercreatesavepoint  extern PFBTAGWRITERCREATESAVEPOINT_IEC pfbtagwritercreatesavepoint;
	#define GET_btagwritercreatesavepoint(fl)  s_pfCMGetAPI2( "btagwritercreatesavepoint", (RTS_VOID_FCTPTR *)&pfbtagwritercreatesavepoint, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA762E901), 0x03050500)
	#define CAL_btagwritercreatesavepoint  pfbtagwritercreatesavepoint
	#define CHK_btagwritercreatesavepoint  (pfbtagwritercreatesavepoint != NULL)
	#define EXP_btagwritercreatesavepoint   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatesavepoint", (RTS_UINTPTR)btagwritercreatesavepoint, 1, RTSITF_GET_SIGNATURE(0, 0xA762E901), 0x03050500) 
#endif


/**
 * <description>btagwritercreatesavepointdynamic</description>
 */
typedef struct tagbtagwritercreatesavepointdynamic_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagWriterCreateSavePointDynamic;	/* VAR_OUTPUT */	
} btagwritercreatesavepointdynamic_struct;

void CDECL CDECL_EXT btagwritercreatesavepointdynamic(btagwritercreatesavepointdynamic_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERCREATESAVEPOINTDYNAMIC_IEC) (btagwritercreatesavepointdynamic_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERCREATESAVEPOINTDYNAMIC_NOTIMPLEMENTED)
	#define USE_btagwritercreatesavepointdynamic
	#define EXT_btagwritercreatesavepointdynamic
	#define GET_btagwritercreatesavepointdynamic(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwritercreatesavepointdynamic(p0) 
	#define CHK_btagwritercreatesavepointdynamic  FALSE
	#define EXP_btagwritercreatesavepointdynamic  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwritercreatesavepointdynamic
	#define EXT_btagwritercreatesavepointdynamic
	#define GET_btagwritercreatesavepointdynamic(fl)  CAL_CMGETAPI( "btagwritercreatesavepointdynamic" ) 
	#define CAL_btagwritercreatesavepointdynamic  btagwritercreatesavepointdynamic
	#define CHK_btagwritercreatesavepointdynamic  TRUE
	#define EXP_btagwritercreatesavepointdynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatesavepointdynamic", (RTS_UINTPTR)btagwritercreatesavepointdynamic, 1, RTSITF_GET_SIGNATURE(0, 0xA2C52642), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwritercreatesavepointdynamic
	#define EXT_btagwritercreatesavepointdynamic
	#define GET_btagwritercreatesavepointdynamic(fl)  CAL_CMGETAPI( "btagwritercreatesavepointdynamic" ) 
	#define CAL_btagwritercreatesavepointdynamic  btagwritercreatesavepointdynamic
	#define CHK_btagwritercreatesavepointdynamic  TRUE
	#define EXP_btagwritercreatesavepointdynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatesavepointdynamic", (RTS_UINTPTR)btagwritercreatesavepointdynamic, 1, RTSITF_GET_SIGNATURE(0, 0xA2C52642), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwritercreatesavepointdynamic
	#define EXT_CmpBinTagUtilIecbtagwritercreatesavepointdynamic
	#define GET_CmpBinTagUtilIecbtagwritercreatesavepointdynamic  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwritercreatesavepointdynamic  btagwritercreatesavepointdynamic
	#define CHK_CmpBinTagUtilIecbtagwritercreatesavepointdynamic  TRUE
	#define EXP_CmpBinTagUtilIecbtagwritercreatesavepointdynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatesavepointdynamic", (RTS_UINTPTR)btagwritercreatesavepointdynamic, 1, RTSITF_GET_SIGNATURE(0, 0xA2C52642), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwritercreatesavepointdynamic
	#define EXT_btagwritercreatesavepointdynamic
	#define GET_btagwritercreatesavepointdynamic(fl)  CAL_CMGETAPI( "btagwritercreatesavepointdynamic" ) 
	#define CAL_btagwritercreatesavepointdynamic  btagwritercreatesavepointdynamic
	#define CHK_btagwritercreatesavepointdynamic  TRUE
	#define EXP_btagwritercreatesavepointdynamic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatesavepointdynamic", (RTS_UINTPTR)btagwritercreatesavepointdynamic, 1, RTSITF_GET_SIGNATURE(0, 0xA2C52642), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwritercreatesavepointdynamic  PFBTAGWRITERCREATESAVEPOINTDYNAMIC_IEC pfbtagwritercreatesavepointdynamic;
	#define EXT_btagwritercreatesavepointdynamic  extern PFBTAGWRITERCREATESAVEPOINTDYNAMIC_IEC pfbtagwritercreatesavepointdynamic;
	#define GET_btagwritercreatesavepointdynamic(fl)  s_pfCMGetAPI2( "btagwritercreatesavepointdynamic", (RTS_VOID_FCTPTR *)&pfbtagwritercreatesavepointdynamic, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA2C52642), 0x03050500)
	#define CAL_btagwritercreatesavepointdynamic  pfbtagwritercreatesavepointdynamic
	#define CHK_btagwritercreatesavepointdynamic  (pfbtagwritercreatesavepointdynamic != NULL)
	#define EXP_btagwritercreatesavepointdynamic   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwritercreatesavepointdynamic", (RTS_UINTPTR)btagwritercreatesavepointdynamic, 1, RTSITF_GET_SIGNATURE(0, 0xA2C52642), 0x03050500) 
#endif


/**
 * <description>btagwriterdestroy</description>
 */
typedef struct tagbtagwriterdestroy_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterDestroy;	/* VAR_OUTPUT */	
} btagwriterdestroy_struct;

void CDECL CDECL_EXT btagwriterdestroy(btagwriterdestroy_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERDESTROY_IEC) (btagwriterdestroy_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERDESTROY_NOTIMPLEMENTED)
	#define USE_btagwriterdestroy
	#define EXT_btagwriterdestroy
	#define GET_btagwriterdestroy(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterdestroy(p0) 
	#define CHK_btagwriterdestroy  FALSE
	#define EXP_btagwriterdestroy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterdestroy
	#define EXT_btagwriterdestroy
	#define GET_btagwriterdestroy(fl)  CAL_CMGETAPI( "btagwriterdestroy" ) 
	#define CAL_btagwriterdestroy  btagwriterdestroy
	#define CHK_btagwriterdestroy  TRUE
	#define EXP_btagwriterdestroy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterdestroy", (RTS_UINTPTR)btagwriterdestroy, 1, RTSITF_GET_SIGNATURE(0, 0xDF047A85), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterdestroy
	#define EXT_btagwriterdestroy
	#define GET_btagwriterdestroy(fl)  CAL_CMGETAPI( "btagwriterdestroy" ) 
	#define CAL_btagwriterdestroy  btagwriterdestroy
	#define CHK_btagwriterdestroy  TRUE
	#define EXP_btagwriterdestroy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterdestroy", (RTS_UINTPTR)btagwriterdestroy, 1, RTSITF_GET_SIGNATURE(0, 0xDF047A85), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterdestroy
	#define EXT_CmpBinTagUtilIecbtagwriterdestroy
	#define GET_CmpBinTagUtilIecbtagwriterdestroy  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterdestroy  btagwriterdestroy
	#define CHK_CmpBinTagUtilIecbtagwriterdestroy  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterdestroy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterdestroy", (RTS_UINTPTR)btagwriterdestroy, 1, RTSITF_GET_SIGNATURE(0, 0xDF047A85), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterdestroy
	#define EXT_btagwriterdestroy
	#define GET_btagwriterdestroy(fl)  CAL_CMGETAPI( "btagwriterdestroy" ) 
	#define CAL_btagwriterdestroy  btagwriterdestroy
	#define CHK_btagwriterdestroy  TRUE
	#define EXP_btagwriterdestroy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterdestroy", (RTS_UINTPTR)btagwriterdestroy, 1, RTSITF_GET_SIGNATURE(0, 0xDF047A85), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterdestroy  PFBTAGWRITERDESTROY_IEC pfbtagwriterdestroy;
	#define EXT_btagwriterdestroy  extern PFBTAGWRITERDESTROY_IEC pfbtagwriterdestroy;
	#define GET_btagwriterdestroy(fl)  s_pfCMGetAPI2( "btagwriterdestroy", (RTS_VOID_FCTPTR *)&pfbtagwriterdestroy, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDF047A85), 0x03050500)
	#define CAL_btagwriterdestroy  pfbtagwriterdestroy
	#define CHK_btagwriterdestroy  (pfbtagwriterdestroy != NULL)
	#define EXP_btagwriterdestroy   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterdestroy", (RTS_UINTPTR)btagwriterdestroy, 1, RTSITF_GET_SIGNATURE(0, 0xDF047A85), 0x03050500) 
#endif


/**
 * <description>btagwriterdestroysavepoint</description>
 */
typedef struct tagbtagwriterdestroysavepoint_struct
{
	RTS_IEC_HANDLE hSavePoint;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterDestroySavePoint;	/* VAR_OUTPUT */	
} btagwriterdestroysavepoint_struct;

void CDECL CDECL_EXT btagwriterdestroysavepoint(btagwriterdestroysavepoint_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERDESTROYSAVEPOINT_IEC) (btagwriterdestroysavepoint_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERDESTROYSAVEPOINT_NOTIMPLEMENTED)
	#define USE_btagwriterdestroysavepoint
	#define EXT_btagwriterdestroysavepoint
	#define GET_btagwriterdestroysavepoint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterdestroysavepoint(p0) 
	#define CHK_btagwriterdestroysavepoint  FALSE
	#define EXP_btagwriterdestroysavepoint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterdestroysavepoint
	#define EXT_btagwriterdestroysavepoint
	#define GET_btagwriterdestroysavepoint(fl)  CAL_CMGETAPI( "btagwriterdestroysavepoint" ) 
	#define CAL_btagwriterdestroysavepoint  btagwriterdestroysavepoint
	#define CHK_btagwriterdestroysavepoint  TRUE
	#define EXP_btagwriterdestroysavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterdestroysavepoint", (RTS_UINTPTR)btagwriterdestroysavepoint, 1, RTSITF_GET_SIGNATURE(0, 0x445E5755), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterdestroysavepoint
	#define EXT_btagwriterdestroysavepoint
	#define GET_btagwriterdestroysavepoint(fl)  CAL_CMGETAPI( "btagwriterdestroysavepoint" ) 
	#define CAL_btagwriterdestroysavepoint  btagwriterdestroysavepoint
	#define CHK_btagwriterdestroysavepoint  TRUE
	#define EXP_btagwriterdestroysavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterdestroysavepoint", (RTS_UINTPTR)btagwriterdestroysavepoint, 1, RTSITF_GET_SIGNATURE(0, 0x445E5755), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterdestroysavepoint
	#define EXT_CmpBinTagUtilIecbtagwriterdestroysavepoint
	#define GET_CmpBinTagUtilIecbtagwriterdestroysavepoint  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterdestroysavepoint  btagwriterdestroysavepoint
	#define CHK_CmpBinTagUtilIecbtagwriterdestroysavepoint  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterdestroysavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterdestroysavepoint", (RTS_UINTPTR)btagwriterdestroysavepoint, 1, RTSITF_GET_SIGNATURE(0, 0x445E5755), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterdestroysavepoint
	#define EXT_btagwriterdestroysavepoint
	#define GET_btagwriterdestroysavepoint(fl)  CAL_CMGETAPI( "btagwriterdestroysavepoint" ) 
	#define CAL_btagwriterdestroysavepoint  btagwriterdestroysavepoint
	#define CHK_btagwriterdestroysavepoint  TRUE
	#define EXP_btagwriterdestroysavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterdestroysavepoint", (RTS_UINTPTR)btagwriterdestroysavepoint, 1, RTSITF_GET_SIGNATURE(0, 0x445E5755), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterdestroysavepoint  PFBTAGWRITERDESTROYSAVEPOINT_IEC pfbtagwriterdestroysavepoint;
	#define EXT_btagwriterdestroysavepoint  extern PFBTAGWRITERDESTROYSAVEPOINT_IEC pfbtagwriterdestroysavepoint;
	#define GET_btagwriterdestroysavepoint(fl)  s_pfCMGetAPI2( "btagwriterdestroysavepoint", (RTS_VOID_FCTPTR *)&pfbtagwriterdestroysavepoint, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x445E5755), 0x03050500)
	#define CAL_btagwriterdestroysavepoint  pfbtagwriterdestroysavepoint
	#define CHK_btagwriterdestroysavepoint  (pfbtagwriterdestroysavepoint != NULL)
	#define EXP_btagwriterdestroysavepoint   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterdestroysavepoint", (RTS_UINTPTR)btagwriterdestroysavepoint, 1, RTSITF_GET_SIGNATURE(0, 0x445E5755), 0x03050500) 
#endif


/**
 * <description>btagwriterendtag</description>
 */
typedef struct tagbtagwriterendtag_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiTagId;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterEndTag;	/* VAR_OUTPUT */	
} btagwriterendtag_struct;

void CDECL CDECL_EXT btagwriterendtag(btagwriterendtag_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERENDTAG_IEC) (btagwriterendtag_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERENDTAG_NOTIMPLEMENTED)
	#define USE_btagwriterendtag
	#define EXT_btagwriterendtag
	#define GET_btagwriterendtag(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterendtag(p0) 
	#define CHK_btagwriterendtag  FALSE
	#define EXP_btagwriterendtag  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterendtag
	#define EXT_btagwriterendtag
	#define GET_btagwriterendtag(fl)  CAL_CMGETAPI( "btagwriterendtag" ) 
	#define CAL_btagwriterendtag  btagwriterendtag
	#define CHK_btagwriterendtag  TRUE
	#define EXP_btagwriterendtag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterendtag", (RTS_UINTPTR)btagwriterendtag, 1, RTSITF_GET_SIGNATURE(0, 0x8152E9BA), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterendtag
	#define EXT_btagwriterendtag
	#define GET_btagwriterendtag(fl)  CAL_CMGETAPI( "btagwriterendtag" ) 
	#define CAL_btagwriterendtag  btagwriterendtag
	#define CHK_btagwriterendtag  TRUE
	#define EXP_btagwriterendtag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterendtag", (RTS_UINTPTR)btagwriterendtag, 1, RTSITF_GET_SIGNATURE(0, 0x8152E9BA), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterendtag
	#define EXT_CmpBinTagUtilIecbtagwriterendtag
	#define GET_CmpBinTagUtilIecbtagwriterendtag  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterendtag  btagwriterendtag
	#define CHK_CmpBinTagUtilIecbtagwriterendtag  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterendtag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterendtag", (RTS_UINTPTR)btagwriterendtag, 1, RTSITF_GET_SIGNATURE(0, 0x8152E9BA), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterendtag
	#define EXT_btagwriterendtag
	#define GET_btagwriterendtag(fl)  CAL_CMGETAPI( "btagwriterendtag" ) 
	#define CAL_btagwriterendtag  btagwriterendtag
	#define CHK_btagwriterendtag  TRUE
	#define EXP_btagwriterendtag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterendtag", (RTS_UINTPTR)btagwriterendtag, 1, RTSITF_GET_SIGNATURE(0, 0x8152E9BA), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterendtag  PFBTAGWRITERENDTAG_IEC pfbtagwriterendtag;
	#define EXT_btagwriterendtag  extern PFBTAGWRITERENDTAG_IEC pfbtagwriterendtag;
	#define GET_btagwriterendtag(fl)  s_pfCMGetAPI2( "btagwriterendtag", (RTS_VOID_FCTPTR *)&pfbtagwriterendtag, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8152E9BA), 0x03050500)
	#define CAL_btagwriterendtag  pfbtagwriterendtag
	#define CHK_btagwriterendtag  (pfbtagwriterendtag != NULL)
	#define EXP_btagwriterendtag   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterendtag", (RTS_UINTPTR)btagwriterendtag, 1, RTSITF_GET_SIGNATURE(0, 0x8152E9BA), 0x03050500) 
#endif


/**
 * <description>btagwriterfinish</description>
 */
typedef struct tagbtagwriterfinish_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE **ppBuffer;			/* VAR_INPUT */	
	RTS_IEC_UDINT *puiSize;				/* VAR_INPUT */	/* number of written bytes */
	RTS_IEC_RESULT BTagWriterFinish;	/* VAR_OUTPUT */	
} btagwriterfinish_struct;

void CDECL CDECL_EXT btagwriterfinish(btagwriterfinish_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERFINISH_IEC) (btagwriterfinish_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERFINISH_NOTIMPLEMENTED)
	#define USE_btagwriterfinish
	#define EXT_btagwriterfinish
	#define GET_btagwriterfinish(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterfinish(p0) 
	#define CHK_btagwriterfinish  FALSE
	#define EXP_btagwriterfinish  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterfinish
	#define EXT_btagwriterfinish
	#define GET_btagwriterfinish(fl)  CAL_CMGETAPI( "btagwriterfinish" ) 
	#define CAL_btagwriterfinish  btagwriterfinish
	#define CHK_btagwriterfinish  TRUE
	#define EXP_btagwriterfinish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterfinish", (RTS_UINTPTR)btagwriterfinish, 1, RTSITF_GET_SIGNATURE(0, 0x8D01C919), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterfinish
	#define EXT_btagwriterfinish
	#define GET_btagwriterfinish(fl)  CAL_CMGETAPI( "btagwriterfinish" ) 
	#define CAL_btagwriterfinish  btagwriterfinish
	#define CHK_btagwriterfinish  TRUE
	#define EXP_btagwriterfinish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterfinish", (RTS_UINTPTR)btagwriterfinish, 1, RTSITF_GET_SIGNATURE(0, 0x8D01C919), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterfinish
	#define EXT_CmpBinTagUtilIecbtagwriterfinish
	#define GET_CmpBinTagUtilIecbtagwriterfinish  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterfinish  btagwriterfinish
	#define CHK_CmpBinTagUtilIecbtagwriterfinish  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterfinish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterfinish", (RTS_UINTPTR)btagwriterfinish, 1, RTSITF_GET_SIGNATURE(0, 0x8D01C919), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterfinish
	#define EXT_btagwriterfinish
	#define GET_btagwriterfinish(fl)  CAL_CMGETAPI( "btagwriterfinish" ) 
	#define CAL_btagwriterfinish  btagwriterfinish
	#define CHK_btagwriterfinish  TRUE
	#define EXP_btagwriterfinish  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterfinish", (RTS_UINTPTR)btagwriterfinish, 1, RTSITF_GET_SIGNATURE(0, 0x8D01C919), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterfinish  PFBTAGWRITERFINISH_IEC pfbtagwriterfinish;
	#define EXT_btagwriterfinish  extern PFBTAGWRITERFINISH_IEC pfbtagwriterfinish;
	#define GET_btagwriterfinish(fl)  s_pfCMGetAPI2( "btagwriterfinish", (RTS_VOID_FCTPTR *)&pfbtagwriterfinish, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8D01C919), 0x03050500)
	#define CAL_btagwriterfinish  pfbtagwriterfinish
	#define CHK_btagwriterfinish  (pfbtagwriterfinish != NULL)
	#define EXP_btagwriterfinish   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterfinish", (RTS_UINTPTR)btagwriterfinish, 1, RTSITF_GET_SIGNATURE(0, 0x8D01C919), 0x03050500) 
#endif


/**
 * <description>btagwriterinit</description>
 */
typedef struct tagbtagwriterinit_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwBufferSize;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterInit;		/* VAR_OUTPUT */	
} btagwriterinit_struct;

void CDECL CDECL_EXT btagwriterinit(btagwriterinit_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERINIT_IEC) (btagwriterinit_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERINIT_NOTIMPLEMENTED)
	#define USE_btagwriterinit
	#define EXT_btagwriterinit
	#define GET_btagwriterinit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterinit(p0) 
	#define CHK_btagwriterinit  FALSE
	#define EXP_btagwriterinit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterinit
	#define EXT_btagwriterinit
	#define GET_btagwriterinit(fl)  CAL_CMGETAPI( "btagwriterinit" ) 
	#define CAL_btagwriterinit  btagwriterinit
	#define CHK_btagwriterinit  TRUE
	#define EXP_btagwriterinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterinit", (RTS_UINTPTR)btagwriterinit, 1, RTSITF_GET_SIGNATURE(0, 0x3101147D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterinit
	#define EXT_btagwriterinit
	#define GET_btagwriterinit(fl)  CAL_CMGETAPI( "btagwriterinit" ) 
	#define CAL_btagwriterinit  btagwriterinit
	#define CHK_btagwriterinit  TRUE
	#define EXP_btagwriterinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterinit", (RTS_UINTPTR)btagwriterinit, 1, RTSITF_GET_SIGNATURE(0, 0x3101147D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterinit
	#define EXT_CmpBinTagUtilIecbtagwriterinit
	#define GET_CmpBinTagUtilIecbtagwriterinit  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterinit  btagwriterinit
	#define CHK_CmpBinTagUtilIecbtagwriterinit  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterinit", (RTS_UINTPTR)btagwriterinit, 1, RTSITF_GET_SIGNATURE(0, 0x3101147D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterinit
	#define EXT_btagwriterinit
	#define GET_btagwriterinit(fl)  CAL_CMGETAPI( "btagwriterinit" ) 
	#define CAL_btagwriterinit  btagwriterinit
	#define CHK_btagwriterinit  TRUE
	#define EXP_btagwriterinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterinit", (RTS_UINTPTR)btagwriterinit, 1, RTSITF_GET_SIGNATURE(0, 0x3101147D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterinit  PFBTAGWRITERINIT_IEC pfbtagwriterinit;
	#define EXT_btagwriterinit  extern PFBTAGWRITERINIT_IEC pfbtagwriterinit;
	#define GET_btagwriterinit(fl)  s_pfCMGetAPI2( "btagwriterinit", (RTS_VOID_FCTPTR *)&pfbtagwriterinit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x3101147D), 0x03050500)
	#define CAL_btagwriterinit  pfbtagwriterinit
	#define CHK_btagwriterinit  (pfbtagwriterinit != NULL)
	#define EXP_btagwriterinit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterinit", (RTS_UINTPTR)btagwriterinit, 1, RTSITF_GET_SIGNATURE(0, 0x3101147D), 0x03050500) 
#endif


/**
 * <description>btagwriterinit2</description>
 */
typedef struct tagbtagwriterinit2_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwBufferSize;			/* VAR_INPUT */	
	RTS_IEC_DINT bSwap;					/* VAR_INPUT */	/* Clients have TO set THIS flag (1), IF the addressed server has a different BYTE order. 
 Must be always FALSE (0) for server implementations or if the client has the same byte order as the server. */
	RTS_IEC_RESULT BTagWriterInit2;		/* VAR_OUTPUT */	
} btagwriterinit2_struct;

void CDECL CDECL_EXT btagwriterinit2(btagwriterinit2_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERINIT2_IEC) (btagwriterinit2_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERINIT2_NOTIMPLEMENTED)
	#define USE_btagwriterinit2
	#define EXT_btagwriterinit2
	#define GET_btagwriterinit2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterinit2(p0) 
	#define CHK_btagwriterinit2  FALSE
	#define EXP_btagwriterinit2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterinit2
	#define EXT_btagwriterinit2
	#define GET_btagwriterinit2(fl)  CAL_CMGETAPI( "btagwriterinit2" ) 
	#define CAL_btagwriterinit2  btagwriterinit2
	#define CHK_btagwriterinit2  TRUE
	#define EXP_btagwriterinit2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterinit2", (RTS_UINTPTR)btagwriterinit2, 1, RTSITF_GET_SIGNATURE(0, 0x47EB6D2D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterinit2
	#define EXT_btagwriterinit2
	#define GET_btagwriterinit2(fl)  CAL_CMGETAPI( "btagwriterinit2" ) 
	#define CAL_btagwriterinit2  btagwriterinit2
	#define CHK_btagwriterinit2  TRUE
	#define EXP_btagwriterinit2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterinit2", (RTS_UINTPTR)btagwriterinit2, 1, RTSITF_GET_SIGNATURE(0, 0x47EB6D2D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterinit2
	#define EXT_CmpBinTagUtilIecbtagwriterinit2
	#define GET_CmpBinTagUtilIecbtagwriterinit2  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterinit2  btagwriterinit2
	#define CHK_CmpBinTagUtilIecbtagwriterinit2  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterinit2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterinit2", (RTS_UINTPTR)btagwriterinit2, 1, RTSITF_GET_SIGNATURE(0, 0x47EB6D2D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterinit2
	#define EXT_btagwriterinit2
	#define GET_btagwriterinit2(fl)  CAL_CMGETAPI( "btagwriterinit2" ) 
	#define CAL_btagwriterinit2  btagwriterinit2
	#define CHK_btagwriterinit2  TRUE
	#define EXP_btagwriterinit2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterinit2", (RTS_UINTPTR)btagwriterinit2, 1, RTSITF_GET_SIGNATURE(0, 0x47EB6D2D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterinit2  PFBTAGWRITERINIT2_IEC pfbtagwriterinit2;
	#define EXT_btagwriterinit2  extern PFBTAGWRITERINIT2_IEC pfbtagwriterinit2;
	#define GET_btagwriterinit2(fl)  s_pfCMGetAPI2( "btagwriterinit2", (RTS_VOID_FCTPTR *)&pfbtagwriterinit2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x47EB6D2D), 0x03050500)
	#define CAL_btagwriterinit2  pfbtagwriterinit2
	#define CHK_btagwriterinit2  (pfbtagwriterinit2 != NULL)
	#define EXP_btagwriterinit2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterinit2", (RTS_UINTPTR)btagwriterinit2, 1, RTSITF_GET_SIGNATURE(0, 0x47EB6D2D), 0x03050500) 
#endif


/**
 * <description>btagwriterrestoresavepoint</description>
 */
typedef struct tagbtagwriterrestoresavepoint_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_HANDLE hSavePoint;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterRestoreSavePoint;	/* VAR_OUTPUT */	
} btagwriterrestoresavepoint_struct;

void CDECL CDECL_EXT btagwriterrestoresavepoint(btagwriterrestoresavepoint_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERRESTORESAVEPOINT_IEC) (btagwriterrestoresavepoint_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERRESTORESAVEPOINT_NOTIMPLEMENTED)
	#define USE_btagwriterrestoresavepoint
	#define EXT_btagwriterrestoresavepoint
	#define GET_btagwriterrestoresavepoint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterrestoresavepoint(p0) 
	#define CHK_btagwriterrestoresavepoint  FALSE
	#define EXP_btagwriterrestoresavepoint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterrestoresavepoint
	#define EXT_btagwriterrestoresavepoint
	#define GET_btagwriterrestoresavepoint(fl)  CAL_CMGETAPI( "btagwriterrestoresavepoint" ) 
	#define CAL_btagwriterrestoresavepoint  btagwriterrestoresavepoint
	#define CHK_btagwriterrestoresavepoint  TRUE
	#define EXP_btagwriterrestoresavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterrestoresavepoint", (RTS_UINTPTR)btagwriterrestoresavepoint, 1, RTSITF_GET_SIGNATURE(0, 0xCEE4117D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterrestoresavepoint
	#define EXT_btagwriterrestoresavepoint
	#define GET_btagwriterrestoresavepoint(fl)  CAL_CMGETAPI( "btagwriterrestoresavepoint" ) 
	#define CAL_btagwriterrestoresavepoint  btagwriterrestoresavepoint
	#define CHK_btagwriterrestoresavepoint  TRUE
	#define EXP_btagwriterrestoresavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterrestoresavepoint", (RTS_UINTPTR)btagwriterrestoresavepoint, 1, RTSITF_GET_SIGNATURE(0, 0xCEE4117D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterrestoresavepoint
	#define EXT_CmpBinTagUtilIecbtagwriterrestoresavepoint
	#define GET_CmpBinTagUtilIecbtagwriterrestoresavepoint  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterrestoresavepoint  btagwriterrestoresavepoint
	#define CHK_CmpBinTagUtilIecbtagwriterrestoresavepoint  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterrestoresavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterrestoresavepoint", (RTS_UINTPTR)btagwriterrestoresavepoint, 1, RTSITF_GET_SIGNATURE(0, 0xCEE4117D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterrestoresavepoint
	#define EXT_btagwriterrestoresavepoint
	#define GET_btagwriterrestoresavepoint(fl)  CAL_CMGETAPI( "btagwriterrestoresavepoint" ) 
	#define CAL_btagwriterrestoresavepoint  btagwriterrestoresavepoint
	#define CHK_btagwriterrestoresavepoint  TRUE
	#define EXP_btagwriterrestoresavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterrestoresavepoint", (RTS_UINTPTR)btagwriterrestoresavepoint, 1, RTSITF_GET_SIGNATURE(0, 0xCEE4117D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterrestoresavepoint  PFBTAGWRITERRESTORESAVEPOINT_IEC pfbtagwriterrestoresavepoint;
	#define EXT_btagwriterrestoresavepoint  extern PFBTAGWRITERRESTORESAVEPOINT_IEC pfbtagwriterrestoresavepoint;
	#define GET_btagwriterrestoresavepoint(fl)  s_pfCMGetAPI2( "btagwriterrestoresavepoint", (RTS_VOID_FCTPTR *)&pfbtagwriterrestoresavepoint, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCEE4117D), 0x03050500)
	#define CAL_btagwriterrestoresavepoint  pfbtagwriterrestoresavepoint
	#define CHK_btagwriterrestoresavepoint  (pfbtagwriterrestoresavepoint != NULL)
	#define EXP_btagwriterrestoresavepoint   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterrestoresavepoint", (RTS_UINTPTR)btagwriterrestoresavepoint, 1, RTSITF_GET_SIGNATURE(0, 0xCEE4117D), 0x03050500) 
#endif


/**
 * <description>btagwriterstarttag</description>
 */
typedef struct tagbtagwriterstarttag_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiTagId;				/* VAR_INPUT */	
	BTagAlignment alignment;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiMinLengthSize;		/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterStartTag;	/* VAR_OUTPUT */	
} btagwriterstarttag_struct;

void CDECL CDECL_EXT btagwriterstarttag(btagwriterstarttag_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERSTARTTAG_IEC) (btagwriterstarttag_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERSTARTTAG_NOTIMPLEMENTED)
	#define USE_btagwriterstarttag
	#define EXT_btagwriterstarttag
	#define GET_btagwriterstarttag(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterstarttag(p0) 
	#define CHK_btagwriterstarttag  FALSE
	#define EXP_btagwriterstarttag  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterstarttag
	#define EXT_btagwriterstarttag
	#define GET_btagwriterstarttag(fl)  CAL_CMGETAPI( "btagwriterstarttag" ) 
	#define CAL_btagwriterstarttag  btagwriterstarttag
	#define CHK_btagwriterstarttag  TRUE
	#define EXP_btagwriterstarttag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterstarttag", (RTS_UINTPTR)btagwriterstarttag, 1, RTSITF_GET_SIGNATURE(0, 0xA356707B), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterstarttag
	#define EXT_btagwriterstarttag
	#define GET_btagwriterstarttag(fl)  CAL_CMGETAPI( "btagwriterstarttag" ) 
	#define CAL_btagwriterstarttag  btagwriterstarttag
	#define CHK_btagwriterstarttag  TRUE
	#define EXP_btagwriterstarttag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterstarttag", (RTS_UINTPTR)btagwriterstarttag, 1, RTSITF_GET_SIGNATURE(0, 0xA356707B), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterstarttag
	#define EXT_CmpBinTagUtilIecbtagwriterstarttag
	#define GET_CmpBinTagUtilIecbtagwriterstarttag  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterstarttag  btagwriterstarttag
	#define CHK_CmpBinTagUtilIecbtagwriterstarttag  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterstarttag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterstarttag", (RTS_UINTPTR)btagwriterstarttag, 1, RTSITF_GET_SIGNATURE(0, 0xA356707B), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterstarttag
	#define EXT_btagwriterstarttag
	#define GET_btagwriterstarttag(fl)  CAL_CMGETAPI( "btagwriterstarttag" ) 
	#define CAL_btagwriterstarttag  btagwriterstarttag
	#define CHK_btagwriterstarttag  TRUE
	#define EXP_btagwriterstarttag  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterstarttag", (RTS_UINTPTR)btagwriterstarttag, 1, RTSITF_GET_SIGNATURE(0, 0xA356707B), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterstarttag  PFBTAGWRITERSTARTTAG_IEC pfbtagwriterstarttag;
	#define EXT_btagwriterstarttag  extern PFBTAGWRITERSTARTTAG_IEC pfbtagwriterstarttag;
	#define GET_btagwriterstarttag(fl)  s_pfCMGetAPI2( "btagwriterstarttag", (RTS_VOID_FCTPTR *)&pfbtagwriterstarttag, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA356707B), 0x03050500)
	#define CAL_btagwriterstarttag  pfbtagwriterstarttag
	#define CHK_btagwriterstarttag  (pfbtagwriterstarttag != NULL)
	#define EXP_btagwriterstarttag   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterstarttag", (RTS_UINTPTR)btagwriterstarttag, 1, RTSITF_GET_SIGNATURE(0, 0xA356707B), 0x03050500) 
#endif


/**
 * <description>btagwriterswitchbuffer</description>
 */
typedef struct tagbtagwriterswitchbuffer_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pNewBuffer;			/* VAR_INPUT */	
	RTS_IEC_DWORD dwNewBufferSize;		/* VAR_INPUT */	
	RTS_IEC_BYTE **ppOldBuffer;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterSwitchBuffer;	/* VAR_OUTPUT */	
} btagwriterswitchbuffer_struct;

void CDECL CDECL_EXT btagwriterswitchbuffer(btagwriterswitchbuffer_struct *p);
typedef void (CDECL CDECL_EXT* PFBTAGWRITERSWITCHBUFFER_IEC) (btagwriterswitchbuffer_struct *p);
#if defined(CMPBINTAGUTILIEC_NOTIMPLEMENTED) || defined(BTAGWRITERSWITCHBUFFER_NOTIMPLEMENTED)
	#define USE_btagwriterswitchbuffer
	#define EXT_btagwriterswitchbuffer
	#define GET_btagwriterswitchbuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_btagwriterswitchbuffer(p0) 
	#define CHK_btagwriterswitchbuffer  FALSE
	#define EXP_btagwriterswitchbuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_btagwriterswitchbuffer
	#define EXT_btagwriterswitchbuffer
	#define GET_btagwriterswitchbuffer(fl)  CAL_CMGETAPI( "btagwriterswitchbuffer" ) 
	#define CAL_btagwriterswitchbuffer  btagwriterswitchbuffer
	#define CHK_btagwriterswitchbuffer  TRUE
	#define EXP_btagwriterswitchbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterswitchbuffer", (RTS_UINTPTR)btagwriterswitchbuffer, 1, RTSITF_GET_SIGNATURE(0, 0x7C1CA317), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPBINTAGUTILIEC_EXTERNAL)
	#define USE_btagwriterswitchbuffer
	#define EXT_btagwriterswitchbuffer
	#define GET_btagwriterswitchbuffer(fl)  CAL_CMGETAPI( "btagwriterswitchbuffer" ) 
	#define CAL_btagwriterswitchbuffer  btagwriterswitchbuffer
	#define CHK_btagwriterswitchbuffer  TRUE
	#define EXP_btagwriterswitchbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterswitchbuffer", (RTS_UINTPTR)btagwriterswitchbuffer, 1, RTSITF_GET_SIGNATURE(0, 0x7C1CA317), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBinTagUtilIecbtagwriterswitchbuffer
	#define EXT_CmpBinTagUtilIecbtagwriterswitchbuffer
	#define GET_CmpBinTagUtilIecbtagwriterswitchbuffer  ERR_OK
	#define CAL_CmpBinTagUtilIecbtagwriterswitchbuffer  btagwriterswitchbuffer
	#define CHK_CmpBinTagUtilIecbtagwriterswitchbuffer  TRUE
	#define EXP_CmpBinTagUtilIecbtagwriterswitchbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterswitchbuffer", (RTS_UINTPTR)btagwriterswitchbuffer, 1, RTSITF_GET_SIGNATURE(0, 0x7C1CA317), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_btagwriterswitchbuffer
	#define EXT_btagwriterswitchbuffer
	#define GET_btagwriterswitchbuffer(fl)  CAL_CMGETAPI( "btagwriterswitchbuffer" ) 
	#define CAL_btagwriterswitchbuffer  btagwriterswitchbuffer
	#define CHK_btagwriterswitchbuffer  TRUE
	#define EXP_btagwriterswitchbuffer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterswitchbuffer", (RTS_UINTPTR)btagwriterswitchbuffer, 1, RTSITF_GET_SIGNATURE(0, 0x7C1CA317), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_btagwriterswitchbuffer  PFBTAGWRITERSWITCHBUFFER_IEC pfbtagwriterswitchbuffer;
	#define EXT_btagwriterswitchbuffer  extern PFBTAGWRITERSWITCHBUFFER_IEC pfbtagwriterswitchbuffer;
	#define GET_btagwriterswitchbuffer(fl)  s_pfCMGetAPI2( "btagwriterswitchbuffer", (RTS_VOID_FCTPTR *)&pfbtagwriterswitchbuffer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7C1CA317), 0x03050500)
	#define CAL_btagwriterswitchbuffer  pfbtagwriterswitchbuffer
	#define CHK_btagwriterswitchbuffer  (pfbtagwriterswitchbuffer != NULL)
	#define EXP_btagwriterswitchbuffer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"btagwriterswitchbuffer", (RTS_UINTPTR)btagwriterswitchbuffer, 1, RTSITF_GET_SIGNATURE(0, 0x7C1CA317), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpBinTagUtilIec_C;

#ifdef CPLUSPLUS
class ICmpBinTagUtilIec : public IBase
{
	public:
};
	#ifndef ITF_CmpBinTagUtilIec
		#define ITF_CmpBinTagUtilIec static ICmpBinTagUtilIec *pICmpBinTagUtilIec = NULL;
	#endif
	#define EXTITF_CmpBinTagUtilIec
#else	/*CPLUSPLUS*/
	typedef ICmpBinTagUtilIec_C		ICmpBinTagUtilIec;
	#ifndef ITF_CmpBinTagUtilIec
		#define ITF_CmpBinTagUtilIec
	#endif
	#define EXTITF_CmpBinTagUtilIec
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPBINTAGUTILIECITF_H_*/
