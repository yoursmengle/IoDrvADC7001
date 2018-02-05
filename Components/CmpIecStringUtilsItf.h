 
	
	
#ifndef _CMPIECSTRINGUTILSITF_H_
#define _CMPIECSTRINGUTILSITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Does a sprintf for the given format string and the given variable. Will not return NULL!
 */
typedef struct tagstusprintf_struct
{
	RTS_IEC_STRING *pstFormat;			/* VAR_INPUT */	/* the formatstring */
	RTS_IEC_DWORD *pVarAdr;				/* VAR_INPUT */	/* the address of the variable that shall be printed */
	RTS_IEC_DWORD udiVarType;			/* VAR_INPUT, Enum: TYPE_CLASS */
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	/* the buffer where the text is to be printed */
	RTS_IEC_UDINT dwBufferSize;			/* VAR_INPUT */	/* the size of the buffer in bytes */
	RTS_IEC_INT StuSprintf;				/* VAR_OUTPUT */	
} stusprintf_struct;

void CDECL CDECL_EXT stusprintf(stusprintf_struct *p);
typedef void (CDECL CDECL_EXT* PFSTUSPRINTF_IEC) (stusprintf_struct *p);
#if defined(CMPIECSTRINGUTILS_NOTIMPLEMENTED) || defined(STUSPRINTF_NOTIMPLEMENTED)
	#define USE_stusprintf
	#define EXT_stusprintf
	#define GET_stusprintf(fl)  ERR_NOTIMPLEMENTED
	#define CAL_stusprintf(p0) 
	#define CHK_stusprintf  FALSE
	#define EXP_stusprintf  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_stusprintf
	#define EXT_stusprintf
	#define GET_stusprintf(fl)  CAL_CMGETAPI( "stusprintf" ) 
	#define CAL_stusprintf  stusprintf
	#define CHK_stusprintf  TRUE
	#define EXP_stusprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stusprintf", (RTS_UINTPTR)stusprintf, 1, 0, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPIECSTRINGUTILS_EXTERNAL)
	#define USE_stusprintf
	#define EXT_stusprintf
	#define GET_stusprintf(fl)  CAL_CMGETAPI( "stusprintf" ) 
	#define CAL_stusprintf  stusprintf
	#define CHK_stusprintf  TRUE
	#define EXP_stusprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stusprintf", (RTS_UINTPTR)stusprintf, 1, 0, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecStringUtilsstusprintf
	#define EXT_CmpIecStringUtilsstusprintf
	#define GET_CmpIecStringUtilsstusprintf  ERR_OK
	#define CAL_CmpIecStringUtilsstusprintf  stusprintf
	#define CHK_CmpIecStringUtilsstusprintf  TRUE
	#define EXP_CmpIecStringUtilsstusprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stusprintf", (RTS_UINTPTR)stusprintf, 1, 0, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_stusprintf
	#define EXT_stusprintf
	#define GET_stusprintf(fl)  CAL_CMGETAPI( "stusprintf" ) 
	#define CAL_stusprintf  stusprintf
	#define CHK_stusprintf  TRUE
	#define EXP_stusprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stusprintf", (RTS_UINTPTR)stusprintf, 1, 0, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_stusprintf  PFSTUSPRINTF_IEC pfstusprintf;
	#define EXT_stusprintf  extern PFSTUSPRINTF_IEC pfstusprintf;
	#define GET_stusprintf(fl)  s_pfCMGetAPI2( "stusprintf", (RTS_VOID_FCTPTR *)&pfstusprintf, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050500)
	#define CAL_stusprintf  pfstusprintf
	#define CHK_stusprintf  (pfstusprintf != NULL)
	#define EXP_stusprintf   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stusprintf", (RTS_UINTPTR)stusprintf, 1, 0, 0x03050500) 
#endif


/**
 * Does a sprintf for the given format string and the given variable. Will not return NULL!
 */
typedef struct tagstusprintfw_struct
{
	RTS_IEC_WSTRING *wstFormat;			/* VAR_INPUT */	/* the formatstring */
	RTS_IEC_DWORD *pVarAdr;				/* VAR_INPUT */	/* the address of the variable that shall be printed */
	RTS_IEC_DWORD udiVarType;			/* VAR_INPUT, Enum: TYPE_CLASS */
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	/* the buffer where the text is to be printed */
	RTS_IEC_UDINT dwBufferSize;			/* VAR_INPUT */	/* the size of the buffer in bytes, not in wstring characters! */
	RTS_IEC_INT StuSprintfW;			/* VAR_OUTPUT */	
} stusprintfw_struct;

void CDECL CDECL_EXT stusprintfw(stusprintfw_struct *p);
typedef void (CDECL CDECL_EXT* PFSTUSPRINTFW_IEC) (stusprintfw_struct *p);
#if defined(CMPIECSTRINGUTILS_NOTIMPLEMENTED) || defined(STUSPRINTFW_NOTIMPLEMENTED)
	#define USE_stusprintfw
	#define EXT_stusprintfw
	#define GET_stusprintfw(fl)  ERR_NOTIMPLEMENTED
	#define CAL_stusprintfw(p0) 
	#define CHK_stusprintfw  FALSE
	#define EXP_stusprintfw  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_stusprintfw
	#define EXT_stusprintfw
	#define GET_stusprintfw(fl)  CAL_CMGETAPI( "stusprintfw" ) 
	#define CAL_stusprintfw  stusprintfw
	#define CHK_stusprintfw  TRUE
	#define EXP_stusprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stusprintfw", (RTS_UINTPTR)stusprintfw, 1, 0, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPIECSTRINGUTILS_EXTERNAL)
	#define USE_stusprintfw
	#define EXT_stusprintfw
	#define GET_stusprintfw(fl)  CAL_CMGETAPI( "stusprintfw" ) 
	#define CAL_stusprintfw  stusprintfw
	#define CHK_stusprintfw  TRUE
	#define EXP_stusprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stusprintfw", (RTS_UINTPTR)stusprintfw, 1, 0, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecStringUtilsstusprintfw
	#define EXT_CmpIecStringUtilsstusprintfw
	#define GET_CmpIecStringUtilsstusprintfw  ERR_OK
	#define CAL_CmpIecStringUtilsstusprintfw  stusprintfw
	#define CHK_CmpIecStringUtilsstusprintfw  TRUE
	#define EXP_CmpIecStringUtilsstusprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stusprintfw", (RTS_UINTPTR)stusprintfw, 1, 0, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_stusprintfw
	#define EXT_stusprintfw
	#define GET_stusprintfw(fl)  CAL_CMGETAPI( "stusprintfw" ) 
	#define CAL_stusprintfw  stusprintfw
	#define CHK_stusprintfw  TRUE
	#define EXP_stusprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stusprintfw", (RTS_UINTPTR)stusprintfw, 1, 0, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_stusprintfw  PFSTUSPRINTFW_IEC pfstusprintfw;
	#define EXT_stusprintfw  extern PFSTUSPRINTFW_IEC pfstusprintfw;
	#define GET_stusprintfw(fl)  s_pfCMGetAPI2( "stusprintfw", (RTS_VOID_FCTPTR *)&pfstusprintfw, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050500)
	#define CAL_stusprintfw  pfstusprintfw
	#define CHK_stusprintfw  (pfstusprintfw != NULL)
	#define EXP_stusprintfw   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stusprintfw", (RTS_UINTPTR)stusprintfw, 1, 0, 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpIecStringUtils_C;

#ifdef CPLUSPLUS
class ICmpIecStringUtils : public IBase
{
	public:
};
	#ifndef ITF_CmpIecStringUtils
		#define ITF_CmpIecStringUtils static ICmpIecStringUtils *pICmpIecStringUtils = NULL;
	#endif
	#define EXTITF_CmpIecStringUtils
#else	/*CPLUSPLUS*/
	typedef ICmpIecStringUtils_C		ICmpIecStringUtils;
	#ifndef ITF_CmpIecStringUtils
		#define ITF_CmpIecStringUtils
	#endif
	#define EXTITF_CmpIecStringUtils
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIECSTRINGUTILSITF_H_*/
