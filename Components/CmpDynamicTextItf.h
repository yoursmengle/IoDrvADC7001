 /**
 * <interfacename>CmpDynamicText</interfacename>
 * <description>
 *	Interface for the dynamic text component.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPDYNAMICTEXTITF_H_
#define _CMPDYNAMICTEXTITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/* Hook definitions (0..10000 reserved for core components) */

/**
 * <description>Setting which decides about the path where the text files are saved. 
 * Default is the current working directory.</description>
 *
 */
#define DYNAMICTEXT_KEY_BASEPATH "TextListPath"
#define DYNAMICTEXT_KEY_TEXTLISTFILE "TextListFile"
#define DYNAMICTEXT_KEY_STARTUPLANGUAGE "StartupLanguage"
#define DYNAMICTEXT_KEY_MAX_SCAN_LINE "MaxTextListLine"
#define DYNAMICTEXT_VALUE_BASEPATH_DEFAULT "$visu$"

#ifndef DYNAMICTEXT_MAX_SCAN_LINE
	#define DYNAMICTEXT_MAX_SCAN_LINE 50000
#endif

#ifndef DYNAMICTEXT_MAX_SYMBOLS
	#define DYNAMICTEXT_MAX_SYMBOLS 10000
#endif

#ifndef DYNAMICTEXT_MAX_SYMBOLS_TEXTLISTS
#define DYNAMICTEXT_MAX_SYMBOLS_TEXTLISTS 100
#endif

typedef struct
{
	RTS_IEC_STRING pszLanguage[21];
	RTS_BOOL xOut;
} dynamictextchangelanguage_struct;

typedef struct
{
	RTS_IEC_STRING* pszPrefix;
	RTS_IEC_STRING* pszId;
	RTS_IEC_STRING* pszOut;
} dynamictextgettext_struct;

typedef struct
{
	RTS_IEC_STRING* pszPrefix;	/* TOCHECK: wstring for inputs here? */
	RTS_IEC_STRING* pszId;
	RTS_IEC_WSTRING* wszOut;
} dynamictextgettextw_struct;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> Function to change the language of all language specific texts. </description>
 * <param name="pEntry" type="IN">Pointer to entry structure</param>
 * <result></result>
 */
void CDECL CDECL_EXT dynamictextchangelanguage(dynamictextchangelanguage_struct *pEntry);
typedef void (CDECL CDECL_EXT* PFDYNAMICTEXTCHANGELANGUAGE_IEC) (dynamictextchangelanguage_struct *pEntry);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(DYNAMICTEXTCHANGELANGUAGE_NOTIMPLEMENTED)
	#define USE_dynamictextchangelanguage
	#define EXT_dynamictextchangelanguage
	#define GET_dynamictextchangelanguage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dynamictextchangelanguage(p0) 
	#define CHK_dynamictextchangelanguage  FALSE
	#define EXP_dynamictextchangelanguage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dynamictextchangelanguage
	#define EXT_dynamictextchangelanguage
	#define GET_dynamictextchangelanguage(fl)  CAL_CMGETAPI( "dynamictextchangelanguage" ) 
	#define CAL_dynamictextchangelanguage  dynamictextchangelanguage
	#define CHK_dynamictextchangelanguage  TRUE
	#define EXP_dynamictextchangelanguage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextchangelanguage", (RTS_UINTPTR)dynamictextchangelanguage, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_dynamictextchangelanguage
	#define EXT_dynamictextchangelanguage
	#define GET_dynamictextchangelanguage(fl)  CAL_CMGETAPI( "dynamictextchangelanguage" ) 
	#define CAL_dynamictextchangelanguage  dynamictextchangelanguage
	#define CHK_dynamictextchangelanguage  TRUE
	#define EXP_dynamictextchangelanguage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextchangelanguage", (RTS_UINTPTR)dynamictextchangelanguage, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextdynamictextchangelanguage
	#define EXT_CmpDynamicTextdynamictextchangelanguage
	#define GET_CmpDynamicTextdynamictextchangelanguage  ERR_OK
	#define CAL_CmpDynamicTextdynamictextchangelanguage  dynamictextchangelanguage
	#define CHK_CmpDynamicTextdynamictextchangelanguage  TRUE
	#define EXP_CmpDynamicTextdynamictextchangelanguage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextchangelanguage", (RTS_UINTPTR)dynamictextchangelanguage, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_dynamictextchangelanguage
	#define EXT_dynamictextchangelanguage
	#define GET_dynamictextchangelanguage(fl)  CAL_CMGETAPI( "dynamictextchangelanguage" ) 
	#define CAL_dynamictextchangelanguage  dynamictextchangelanguage
	#define CHK_dynamictextchangelanguage  TRUE
	#define EXP_dynamictextchangelanguage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextchangelanguage", (RTS_UINTPTR)dynamictextchangelanguage, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_dynamictextchangelanguage  PFDYNAMICTEXTCHANGELANGUAGE_IEC pfdynamictextchangelanguage;
	#define EXT_dynamictextchangelanguage  extern PFDYNAMICTEXTCHANGELANGUAGE_IEC pfdynamictextchangelanguage;
	#define GET_dynamictextchangelanguage(fl)  s_pfCMGetAPI2( "dynamictextchangelanguage", (RTS_VOID_FCTPTR *)&pfdynamictextchangelanguage, (fl), 0, 0)
	#define CAL_dynamictextchangelanguage  pfdynamictextchangelanguage
	#define CHK_dynamictextchangelanguage  (pfdynamictextchangelanguage != NULL)
	#define EXP_dynamictextchangelanguage   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextchangelanguage", (RTS_UINTPTR)dynamictextchangelanguage, 1, 0) 
#endif


/**
 * <description> Provides functionality to gain language specific texts from a dynamic text file </description>
 * <param name="pszPrefix" type="IN">The prefix specifier</param>
 * <param name="pszId" type="IN">The id specifier</param>
 * <param name="pszOut" type="OUT">The corresponding text</param>
 */
void CDECL CDECL_EXT dynamictextgettext(dynamictextgettext_struct *pEntry);
typedef void (CDECL CDECL_EXT* PFDYNAMICTEXTGETTEXT_IEC) (dynamictextgettext_struct *pEntry);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(DYNAMICTEXTGETTEXT_NOTIMPLEMENTED)
	#define USE_dynamictextgettext
	#define EXT_dynamictextgettext
	#define GET_dynamictextgettext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dynamictextgettext(p0) 
	#define CHK_dynamictextgettext  FALSE
	#define EXP_dynamictextgettext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dynamictextgettext
	#define EXT_dynamictextgettext
	#define GET_dynamictextgettext(fl)  CAL_CMGETAPI( "dynamictextgettext" ) 
	#define CAL_dynamictextgettext  dynamictextgettext
	#define CHK_dynamictextgettext  TRUE
	#define EXP_dynamictextgettext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgettext", (RTS_UINTPTR)dynamictextgettext, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_dynamictextgettext
	#define EXT_dynamictextgettext
	#define GET_dynamictextgettext(fl)  CAL_CMGETAPI( "dynamictextgettext" ) 
	#define CAL_dynamictextgettext  dynamictextgettext
	#define CHK_dynamictextgettext  TRUE
	#define EXP_dynamictextgettext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgettext", (RTS_UINTPTR)dynamictextgettext, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextdynamictextgettext
	#define EXT_CmpDynamicTextdynamictextgettext
	#define GET_CmpDynamicTextdynamictextgettext  ERR_OK
	#define CAL_CmpDynamicTextdynamictextgettext  dynamictextgettext
	#define CHK_CmpDynamicTextdynamictextgettext  TRUE
	#define EXP_CmpDynamicTextdynamictextgettext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgettext", (RTS_UINTPTR)dynamictextgettext, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_dynamictextgettext
	#define EXT_dynamictextgettext
	#define GET_dynamictextgettext(fl)  CAL_CMGETAPI( "dynamictextgettext" ) 
	#define CAL_dynamictextgettext  dynamictextgettext
	#define CHK_dynamictextgettext  TRUE
	#define EXP_dynamictextgettext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgettext", (RTS_UINTPTR)dynamictextgettext, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_dynamictextgettext  PFDYNAMICTEXTGETTEXT_IEC pfdynamictextgettext;
	#define EXT_dynamictextgettext  extern PFDYNAMICTEXTGETTEXT_IEC pfdynamictextgettext;
	#define GET_dynamictextgettext(fl)  s_pfCMGetAPI2( "dynamictextgettext", (RTS_VOID_FCTPTR *)&pfdynamictextgettext, (fl), 0, 0)
	#define CAL_dynamictextgettext  pfdynamictextgettext
	#define CHK_dynamictextgettext  (pfdynamictextgettext != NULL)
	#define EXP_dynamictextgettext   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgettext", (RTS_UINTPTR)dynamictextgettext, 1, 0) 
#endif


/**
 * <description> WString version of VisuFctGetText, for further documentation see VisuFctGetText </description>
 */
void CDECL CDECL_EXT dynamictextgettextw(dynamictextgettextw_struct *pEntry);
typedef void (CDECL CDECL_EXT* PFDYNAMICTEXTGETTEXTW_IEC) (dynamictextgettextw_struct *pEntry);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(DYNAMICTEXTGETTEXTW_NOTIMPLEMENTED)
	#define USE_dynamictextgettextw
	#define EXT_dynamictextgettextw
	#define GET_dynamictextgettextw(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dynamictextgettextw(p0) 
	#define CHK_dynamictextgettextw  FALSE
	#define EXP_dynamictextgettextw  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dynamictextgettextw
	#define EXT_dynamictextgettextw
	#define GET_dynamictextgettextw(fl)  CAL_CMGETAPI( "dynamictextgettextw" ) 
	#define CAL_dynamictextgettextw  dynamictextgettextw
	#define CHK_dynamictextgettextw  TRUE
	#define EXP_dynamictextgettextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgettextw", (RTS_UINTPTR)dynamictextgettextw, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_dynamictextgettextw
	#define EXT_dynamictextgettextw
	#define GET_dynamictextgettextw(fl)  CAL_CMGETAPI( "dynamictextgettextw" ) 
	#define CAL_dynamictextgettextw  dynamictextgettextw
	#define CHK_dynamictextgettextw  TRUE
	#define EXP_dynamictextgettextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgettextw", (RTS_UINTPTR)dynamictextgettextw, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextdynamictextgettextw
	#define EXT_CmpDynamicTextdynamictextgettextw
	#define GET_CmpDynamicTextdynamictextgettextw  ERR_OK
	#define CAL_CmpDynamicTextdynamictextgettextw  dynamictextgettextw
	#define CHK_CmpDynamicTextdynamictextgettextw  TRUE
	#define EXP_CmpDynamicTextdynamictextgettextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgettextw", (RTS_UINTPTR)dynamictextgettextw, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_dynamictextgettextw
	#define EXT_dynamictextgettextw
	#define GET_dynamictextgettextw(fl)  CAL_CMGETAPI( "dynamictextgettextw" ) 
	#define CAL_dynamictextgettextw  dynamictextgettextw
	#define CHK_dynamictextgettextw  TRUE
	#define EXP_dynamictextgettextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgettextw", (RTS_UINTPTR)dynamictextgettextw, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_dynamictextgettextw  PFDYNAMICTEXTGETTEXTW_IEC pfdynamictextgettextw;
	#define EXT_dynamictextgettextw  extern PFDYNAMICTEXTGETTEXTW_IEC pfdynamictextgettextw;
	#define GET_dynamictextgettextw(fl)  s_pfCMGetAPI2( "dynamictextgettextw", (RTS_VOID_FCTPTR *)&pfdynamictextgettextw, (fl), 0, 0)
	#define CAL_dynamictextgettextw  pfdynamictextgettextw
	#define CHK_dynamictextgettextw  (pfdynamictextgettextw != NULL)
	#define EXP_dynamictextgettextw   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgettextw", (RTS_UINTPTR)dynamictextgettextw, 1, 0) 
#endif


/**
 * <description> Provides functionality to gain default texts from a dynamic text file </description>
 * <param name="pszPrefix" type="IN">The prefix specifier</param>
 * <param name="pszId" type="IN">The id specifier</param>
 * <param name="pszOut" type="OUT">The corresponding text</param>
 */
void CDECL CDECL_EXT dynamictextgetdefaulttext(dynamictextgettext_struct *pEntry);
typedef void (CDECL CDECL_EXT* PFDYNAMICTEXTGETDEFAULTTEXT_IEC) (dynamictextgettext_struct *pEntry);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(DYNAMICTEXTGETDEFAULTTEXT_NOTIMPLEMENTED)
	#define USE_dynamictextgetdefaulttext
	#define EXT_dynamictextgetdefaulttext
	#define GET_dynamictextgetdefaulttext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dynamictextgetdefaulttext(p0) 
	#define CHK_dynamictextgetdefaulttext  FALSE
	#define EXP_dynamictextgetdefaulttext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dynamictextgetdefaulttext
	#define EXT_dynamictextgetdefaulttext
	#define GET_dynamictextgetdefaulttext(fl)  CAL_CMGETAPI( "dynamictextgetdefaulttext" ) 
	#define CAL_dynamictextgetdefaulttext  dynamictextgetdefaulttext
	#define CHK_dynamictextgetdefaulttext  TRUE
	#define EXP_dynamictextgetdefaulttext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetdefaulttext", (RTS_UINTPTR)dynamictextgetdefaulttext, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_dynamictextgetdefaulttext
	#define EXT_dynamictextgetdefaulttext
	#define GET_dynamictextgetdefaulttext(fl)  CAL_CMGETAPI( "dynamictextgetdefaulttext" ) 
	#define CAL_dynamictextgetdefaulttext  dynamictextgetdefaulttext
	#define CHK_dynamictextgetdefaulttext  TRUE
	#define EXP_dynamictextgetdefaulttext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetdefaulttext", (RTS_UINTPTR)dynamictextgetdefaulttext, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextdynamictextgetdefaulttext
	#define EXT_CmpDynamicTextdynamictextgetdefaulttext
	#define GET_CmpDynamicTextdynamictextgetdefaulttext  ERR_OK
	#define CAL_CmpDynamicTextdynamictextgetdefaulttext  dynamictextgetdefaulttext
	#define CHK_CmpDynamicTextdynamictextgetdefaulttext  TRUE
	#define EXP_CmpDynamicTextdynamictextgetdefaulttext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetdefaulttext", (RTS_UINTPTR)dynamictextgetdefaulttext, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_dynamictextgetdefaulttext
	#define EXT_dynamictextgetdefaulttext
	#define GET_dynamictextgetdefaulttext(fl)  CAL_CMGETAPI( "dynamictextgetdefaulttext" ) 
	#define CAL_dynamictextgetdefaulttext  dynamictextgetdefaulttext
	#define CHK_dynamictextgetdefaulttext  TRUE
	#define EXP_dynamictextgetdefaulttext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetdefaulttext", (RTS_UINTPTR)dynamictextgetdefaulttext, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_dynamictextgetdefaulttext  PFDYNAMICTEXTGETDEFAULTTEXT_IEC pfdynamictextgetdefaulttext;
	#define EXT_dynamictextgetdefaulttext  extern PFDYNAMICTEXTGETDEFAULTTEXT_IEC pfdynamictextgetdefaulttext;
	#define GET_dynamictextgetdefaulttext(fl)  s_pfCMGetAPI2( "dynamictextgetdefaulttext", (RTS_VOID_FCTPTR *)&pfdynamictextgetdefaulttext, (fl), 0, 0)
	#define CAL_dynamictextgetdefaulttext  pfdynamictextgetdefaulttext
	#define CHK_dynamictextgetdefaulttext  (pfdynamictextgetdefaulttext != NULL)
	#define EXP_dynamictextgetdefaulttext   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetdefaulttext", (RTS_UINTPTR)dynamictextgetdefaulttext, 1, 0) 
#endif


/**
 * <description> WString version of VisuFctGetDefaultText, for further documentation see VisuFctGetDefaultText </description>
 */
void CDECL CDECL_EXT dynamictextgetdefaulttextw(dynamictextgettextw_struct *pEntry);
typedef void (CDECL CDECL_EXT* PFDYNAMICTEXTGETDEFAULTTEXTW_IEC) (dynamictextgettextw_struct *pEntry);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(DYNAMICTEXTGETDEFAULTTEXTW_NOTIMPLEMENTED)
	#define USE_dynamictextgetdefaulttextw
	#define EXT_dynamictextgetdefaulttextw
	#define GET_dynamictextgetdefaulttextw(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dynamictextgetdefaulttextw(p0) 
	#define CHK_dynamictextgetdefaulttextw  FALSE
	#define EXP_dynamictextgetdefaulttextw  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dynamictextgetdefaulttextw
	#define EXT_dynamictextgetdefaulttextw
	#define GET_dynamictextgetdefaulttextw(fl)  CAL_CMGETAPI( "dynamictextgetdefaulttextw" ) 
	#define CAL_dynamictextgetdefaulttextw  dynamictextgetdefaulttextw
	#define CHK_dynamictextgetdefaulttextw  TRUE
	#define EXP_dynamictextgetdefaulttextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetdefaulttextw", (RTS_UINTPTR)dynamictextgetdefaulttextw, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_dynamictextgetdefaulttextw
	#define EXT_dynamictextgetdefaulttextw
	#define GET_dynamictextgetdefaulttextw(fl)  CAL_CMGETAPI( "dynamictextgetdefaulttextw" ) 
	#define CAL_dynamictextgetdefaulttextw  dynamictextgetdefaulttextw
	#define CHK_dynamictextgetdefaulttextw  TRUE
	#define EXP_dynamictextgetdefaulttextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetdefaulttextw", (RTS_UINTPTR)dynamictextgetdefaulttextw, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextdynamictextgetdefaulttextw
	#define EXT_CmpDynamicTextdynamictextgetdefaulttextw
	#define GET_CmpDynamicTextdynamictextgetdefaulttextw  ERR_OK
	#define CAL_CmpDynamicTextdynamictextgetdefaulttextw  dynamictextgetdefaulttextw
	#define CHK_CmpDynamicTextdynamictextgetdefaulttextw  TRUE
	#define EXP_CmpDynamicTextdynamictextgetdefaulttextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetdefaulttextw", (RTS_UINTPTR)dynamictextgetdefaulttextw, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_dynamictextgetdefaulttextw
	#define EXT_dynamictextgetdefaulttextw
	#define GET_dynamictextgetdefaulttextw(fl)  CAL_CMGETAPI( "dynamictextgetdefaulttextw" ) 
	#define CAL_dynamictextgetdefaulttextw  dynamictextgetdefaulttextw
	#define CHK_dynamictextgetdefaulttextw  TRUE
	#define EXP_dynamictextgetdefaulttextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetdefaulttextw", (RTS_UINTPTR)dynamictextgetdefaulttextw, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_dynamictextgetdefaulttextw  PFDYNAMICTEXTGETDEFAULTTEXTW_IEC pfdynamictextgetdefaulttextw;
	#define EXT_dynamictextgetdefaulttextw  extern PFDYNAMICTEXTGETDEFAULTTEXTW_IEC pfdynamictextgetdefaulttextw;
	#define GET_dynamictextgetdefaulttextw(fl)  s_pfCMGetAPI2( "dynamictextgetdefaulttextw", (RTS_VOID_FCTPTR *)&pfdynamictextgetdefaulttextw, (fl), 0, 0)
	#define CAL_dynamictextgetdefaulttextw  pfdynamictextgetdefaulttextw
	#define CHK_dynamictextgetdefaulttextw  (pfdynamictextgetdefaulttextw != NULL)
	#define EXP_dynamictextgetdefaulttextw   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetdefaulttextw", (RTS_UINTPTR)dynamictextgetdefaulttextw, 1, 0) 
#endif


/**
 * <description>This function loads the default texts from the currently registered text files.
 * as a IEC-String (char* in the runtime) </description>
 */
typedef struct tagdynamictextloaddefaulttexts_struct
{
	RTS_IEC_UDINT DynamicTextLoadDefaultTexts;	/* VAR_OUTPUT */
} dynamictextloaddefaulttexts_struct;

void CDECL CDECL_EXT dynamictextloaddefaulttexts(dynamictextloaddefaulttexts_struct *p);
typedef void (CDECL CDECL_EXT* PFDYNAMICTEXTLOADDEFAULTTEXTS_IEC) (dynamictextloaddefaulttexts_struct *p);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(DYNAMICTEXTLOADDEFAULTTEXTS_NOTIMPLEMENTED)
	#define USE_dynamictextloaddefaulttexts
	#define EXT_dynamictextloaddefaulttexts
	#define GET_dynamictextloaddefaulttexts(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dynamictextloaddefaulttexts(p0) 
	#define CHK_dynamictextloaddefaulttexts  FALSE
	#define EXP_dynamictextloaddefaulttexts  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dynamictextloaddefaulttexts
	#define EXT_dynamictextloaddefaulttexts
	#define GET_dynamictextloaddefaulttexts(fl)  CAL_CMGETAPI( "dynamictextloaddefaulttexts" ) 
	#define CAL_dynamictextloaddefaulttexts  dynamictextloaddefaulttexts
	#define CHK_dynamictextloaddefaulttexts  TRUE
	#define EXP_dynamictextloaddefaulttexts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextloaddefaulttexts", (RTS_UINTPTR)dynamictextloaddefaulttexts, 1, 0xBC5AF7A3, 0x3040100) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_dynamictextloaddefaulttexts
	#define EXT_dynamictextloaddefaulttexts
	#define GET_dynamictextloaddefaulttexts(fl)  CAL_CMGETAPI( "dynamictextloaddefaulttexts" ) 
	#define CAL_dynamictextloaddefaulttexts  dynamictextloaddefaulttexts
	#define CHK_dynamictextloaddefaulttexts  TRUE
	#define EXP_dynamictextloaddefaulttexts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextloaddefaulttexts", (RTS_UINTPTR)dynamictextloaddefaulttexts, 1, 0xBC5AF7A3, 0x3040100) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextdynamictextloaddefaulttexts
	#define EXT_CmpDynamicTextdynamictextloaddefaulttexts
	#define GET_CmpDynamicTextdynamictextloaddefaulttexts  ERR_OK
	#define CAL_CmpDynamicTextdynamictextloaddefaulttexts  dynamictextloaddefaulttexts
	#define CHK_CmpDynamicTextdynamictextloaddefaulttexts  TRUE
	#define EXP_CmpDynamicTextdynamictextloaddefaulttexts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextloaddefaulttexts", (RTS_UINTPTR)dynamictextloaddefaulttexts, 1, 0xBC5AF7A3, 0x3040100) 
#elif defined(CPLUSPLUS)
	#define USE_dynamictextloaddefaulttexts
	#define EXT_dynamictextloaddefaulttexts
	#define GET_dynamictextloaddefaulttexts(fl)  CAL_CMGETAPI( "dynamictextloaddefaulttexts" ) 
	#define CAL_dynamictextloaddefaulttexts  dynamictextloaddefaulttexts
	#define CHK_dynamictextloaddefaulttexts  TRUE
	#define EXP_dynamictextloaddefaulttexts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextloaddefaulttexts", (RTS_UINTPTR)dynamictextloaddefaulttexts, 1, 0xBC5AF7A3, 0x3040100) 
#else /* DYNAMIC_LINK */
	#define USE_dynamictextloaddefaulttexts  PFDYNAMICTEXTLOADDEFAULTTEXTS_IEC pfdynamictextloaddefaulttexts;
	#define EXT_dynamictextloaddefaulttexts  extern PFDYNAMICTEXTLOADDEFAULTTEXTS_IEC pfdynamictextloaddefaulttexts;
	#define GET_dynamictextloaddefaulttexts(fl)  s_pfCMGetAPI2( "dynamictextloaddefaulttexts", (RTS_VOID_FCTPTR *)&pfdynamictextloaddefaulttexts, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xBC5AF7A3, 0x3040100)
	#define CAL_dynamictextloaddefaulttexts  pfdynamictextloaddefaulttexts
	#define CHK_dynamictextloaddefaulttexts  (pfdynamictextloaddefaulttexts != NULL)
	#define EXP_dynamictextloaddefaulttexts   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextloaddefaulttexts", (RTS_UINTPTR)dynamictextloaddefaulttexts, 1, 0xBC5AF7A3, 0x3040100) 
#endif


/**
 * <description>This function reloads all currently registered text files for the currently assigned language.
 * This function could be used for example when you know that a textfile was updated externally and you want
 * to reload those files.</description>
 */
typedef struct tagdynamictextreloadtexts_struct
{
	RTS_IEC_UDINT DynamicTextReloadTexts;	/* VAR_OUTPUT */
} dynamictextreloadtexts_struct;

void CDECL CDECL_EXT dynamictextreloadtexts(dynamictextreloadtexts_struct *p);
typedef void (CDECL CDECL_EXT* PFDYNAMICTEXTRELOADTEXTS_IEC) (dynamictextreloadtexts_struct *p);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(DYNAMICTEXTRELOADTEXTS_NOTIMPLEMENTED)
	#define USE_dynamictextreloadtexts
	#define EXT_dynamictextreloadtexts
	#define GET_dynamictextreloadtexts(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dynamictextreloadtexts(p0) 
	#define CHK_dynamictextreloadtexts  FALSE
	#define EXP_dynamictextreloadtexts  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dynamictextreloadtexts
	#define EXT_dynamictextreloadtexts
	#define GET_dynamictextreloadtexts(fl)  CAL_CMGETAPI( "dynamictextreloadtexts" ) 
	#define CAL_dynamictextreloadtexts  dynamictextreloadtexts
	#define CHK_dynamictextreloadtexts  TRUE
	#define EXP_dynamictextreloadtexts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextreloadtexts", (RTS_UINTPTR)dynamictextreloadtexts, 1, 0x50855C4B, 0x3040100) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_dynamictextreloadtexts
	#define EXT_dynamictextreloadtexts
	#define GET_dynamictextreloadtexts(fl)  CAL_CMGETAPI( "dynamictextreloadtexts" ) 
	#define CAL_dynamictextreloadtexts  dynamictextreloadtexts
	#define CHK_dynamictextreloadtexts  TRUE
	#define EXP_dynamictextreloadtexts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextreloadtexts", (RTS_UINTPTR)dynamictextreloadtexts, 1, 0x50855C4B, 0x3040100) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextdynamictextreloadtexts
	#define EXT_CmpDynamicTextdynamictextreloadtexts
	#define GET_CmpDynamicTextdynamictextreloadtexts  ERR_OK
	#define CAL_CmpDynamicTextdynamictextreloadtexts  dynamictextreloadtexts
	#define CHK_CmpDynamicTextdynamictextreloadtexts  TRUE
	#define EXP_CmpDynamicTextdynamictextreloadtexts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextreloadtexts", (RTS_UINTPTR)dynamictextreloadtexts, 1, 0x50855C4B, 0x3040100) 
#elif defined(CPLUSPLUS)
	#define USE_dynamictextreloadtexts
	#define EXT_dynamictextreloadtexts
	#define GET_dynamictextreloadtexts(fl)  CAL_CMGETAPI( "dynamictextreloadtexts" ) 
	#define CAL_dynamictextreloadtexts  dynamictextreloadtexts
	#define CHK_dynamictextreloadtexts  TRUE
	#define EXP_dynamictextreloadtexts  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextreloadtexts", (RTS_UINTPTR)dynamictextreloadtexts, 1, 0x50855C4B, 0x3040100) 
#else /* DYNAMIC_LINK */
	#define USE_dynamictextreloadtexts  PFDYNAMICTEXTRELOADTEXTS_IEC pfdynamictextreloadtexts;
	#define EXT_dynamictextreloadtexts  extern PFDYNAMICTEXTRELOADTEXTS_IEC pfdynamictextreloadtexts;
	#define GET_dynamictextreloadtexts(fl)  s_pfCMGetAPI2( "dynamictextreloadtexts", (RTS_VOID_FCTPTR *)&pfdynamictextreloadtexts, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x50855C4B, 0x3040100)
	#define CAL_dynamictextreloadtexts  pfdynamictextreloadtexts
	#define CHK_dynamictextreloadtexts  (pfdynamictextreloadtexts != NULL)
	#define EXP_dynamictextreloadtexts   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextreloadtexts", (RTS_UINTPTR)dynamictextreloadtexts, 1, 0x50855C4B, 0x3040100) 
#endif


/**
 * <description><p>This method returns the name of the currently loaded language if there is 
 * any.</p>
 * <p>If no language is loaded (there was no call to DynamicTextChangeLanguage before), then an 
 * empty string will be returned.</p></description>
 */
typedef struct tagdynamictextgetcurrentlanguage_struct
{
	RTS_IEC_STRING DynamicTextGetCurrentLanguage[81];	/* VAR_OUTPUT */
} dynamictextgetcurrentlanguage_struct;

void CDECL CDECL_EXT dynamictextgetcurrentlanguage(dynamictextgetcurrentlanguage_struct *p);
typedef void (CDECL CDECL_EXT* PFDYNAMICTEXTGETCURRENTLANGUAGE_IEC) (dynamictextgetcurrentlanguage_struct *p);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(DYNAMICTEXTGETCURRENTLANGUAGE_NOTIMPLEMENTED)
	#define USE_dynamictextgetcurrentlanguage
	#define EXT_dynamictextgetcurrentlanguage
	#define GET_dynamictextgetcurrentlanguage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dynamictextgetcurrentlanguage(p0) 
	#define CHK_dynamictextgetcurrentlanguage  FALSE
	#define EXP_dynamictextgetcurrentlanguage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dynamictextgetcurrentlanguage
	#define EXT_dynamictextgetcurrentlanguage
	#define GET_dynamictextgetcurrentlanguage(fl)  CAL_CMGETAPI( "dynamictextgetcurrentlanguage" ) 
	#define CAL_dynamictextgetcurrentlanguage  dynamictextgetcurrentlanguage
	#define CHK_dynamictextgetcurrentlanguage  TRUE
	#define EXP_dynamictextgetcurrentlanguage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetcurrentlanguage", (RTS_UINTPTR)dynamictextgetcurrentlanguage, 1, 0x282B626C, 0x3040100) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_dynamictextgetcurrentlanguage
	#define EXT_dynamictextgetcurrentlanguage
	#define GET_dynamictextgetcurrentlanguage(fl)  CAL_CMGETAPI( "dynamictextgetcurrentlanguage" ) 
	#define CAL_dynamictextgetcurrentlanguage  dynamictextgetcurrentlanguage
	#define CHK_dynamictextgetcurrentlanguage  TRUE
	#define EXP_dynamictextgetcurrentlanguage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetcurrentlanguage", (RTS_UINTPTR)dynamictextgetcurrentlanguage, 1, 0x282B626C, 0x3040100) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextdynamictextgetcurrentlanguage
	#define EXT_CmpDynamicTextdynamictextgetcurrentlanguage
	#define GET_CmpDynamicTextdynamictextgetcurrentlanguage  ERR_OK
	#define CAL_CmpDynamicTextdynamictextgetcurrentlanguage  dynamictextgetcurrentlanguage
	#define CHK_CmpDynamicTextdynamictextgetcurrentlanguage  TRUE
	#define EXP_CmpDynamicTextdynamictextgetcurrentlanguage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetcurrentlanguage", (RTS_UINTPTR)dynamictextgetcurrentlanguage, 1, 0x282B626C, 0x3040100) 
#elif defined(CPLUSPLUS)
	#define USE_dynamictextgetcurrentlanguage
	#define EXT_dynamictextgetcurrentlanguage
	#define GET_dynamictextgetcurrentlanguage(fl)  CAL_CMGETAPI( "dynamictextgetcurrentlanguage" ) 
	#define CAL_dynamictextgetcurrentlanguage  dynamictextgetcurrentlanguage
	#define CHK_dynamictextgetcurrentlanguage  TRUE
	#define EXP_dynamictextgetcurrentlanguage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetcurrentlanguage", (RTS_UINTPTR)dynamictextgetcurrentlanguage, 1, 0x282B626C, 0x3040100) 
#else /* DYNAMIC_LINK */
	#define USE_dynamictextgetcurrentlanguage  PFDYNAMICTEXTGETCURRENTLANGUAGE_IEC pfdynamictextgetcurrentlanguage;
	#define EXT_dynamictextgetcurrentlanguage  extern PFDYNAMICTEXTGETCURRENTLANGUAGE_IEC pfdynamictextgetcurrentlanguage;
	#define GET_dynamictextgetcurrentlanguage(fl)  s_pfCMGetAPI2( "dynamictextgetcurrentlanguage", (RTS_VOID_FCTPTR *)&pfdynamictextgetcurrentlanguage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x282B626C, 0x3040100)
	#define CAL_dynamictextgetcurrentlanguage  pfdynamictextgetcurrentlanguage
	#define CHK_dynamictextgetcurrentlanguage  (pfdynamictextgetcurrentlanguage != NULL)
	#define EXP_dynamictextgetcurrentlanguage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextgetcurrentlanguage", (RTS_UINTPTR)dynamictextgetcurrentlanguage, 1, 0x282B626C, 0x3040100) 
#endif


/**
 * This function registers a dynamic text file.
 * These registered text files are considered when load or reload is called
 * on the CmpDynamicText component.  
 */
typedef struct tagdynamictextregisterfile_struct
{
	RTS_IEC_STRING *szFile;				/* VAR_INPUT */	
	RTS_IEC_RESULT DynamicTextRegisterFile;	/* VAR_OUTPUT */	
} dynamictextregisterfile_struct;

void CDECL CDECL_EXT dynamictextregisterfile(dynamictextregisterfile_struct *p);
typedef void (CDECL CDECL_EXT* PFDYNAMICTEXTREGISTERFILE_IEC) (dynamictextregisterfile_struct *p);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(DYNAMICTEXTREGISTERFILE_NOTIMPLEMENTED)
	#define USE_dynamictextregisterfile
	#define EXT_dynamictextregisterfile
	#define GET_dynamictextregisterfile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dynamictextregisterfile(p0) 
	#define CHK_dynamictextregisterfile  FALSE
	#define EXP_dynamictextregisterfile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dynamictextregisterfile
	#define EXT_dynamictextregisterfile
	#define GET_dynamictextregisterfile(fl)  CAL_CMGETAPI( "dynamictextregisterfile" ) 
	#define CAL_dynamictextregisterfile  dynamictextregisterfile
	#define CHK_dynamictextregisterfile  TRUE
	#define EXP_dynamictextregisterfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextregisterfile", (RTS_UINTPTR)dynamictextregisterfile, 1, RTSITF_GET_SIGNATURE(0x0C950958, 0), 0x03050700) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_dynamictextregisterfile
	#define EXT_dynamictextregisterfile
	#define GET_dynamictextregisterfile(fl)  CAL_CMGETAPI( "dynamictextregisterfile" ) 
	#define CAL_dynamictextregisterfile  dynamictextregisterfile
	#define CHK_dynamictextregisterfile  TRUE
	#define EXP_dynamictextregisterfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextregisterfile", (RTS_UINTPTR)dynamictextregisterfile, 1, RTSITF_GET_SIGNATURE(0x0C950958, 0), 0x03050700) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextdynamictextregisterfile
	#define EXT_CmpDynamicTextdynamictextregisterfile
	#define GET_CmpDynamicTextdynamictextregisterfile  ERR_OK
	#define CAL_CmpDynamicTextdynamictextregisterfile  dynamictextregisterfile
	#define CHK_CmpDynamicTextdynamictextregisterfile  TRUE
	#define EXP_CmpDynamicTextdynamictextregisterfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextregisterfile", (RTS_UINTPTR)dynamictextregisterfile, 1, RTSITF_GET_SIGNATURE(0x0C950958, 0), 0x03050700) 
#elif defined(CPLUSPLUS)
	#define USE_dynamictextregisterfile
	#define EXT_dynamictextregisterfile
	#define GET_dynamictextregisterfile(fl)  CAL_CMGETAPI( "dynamictextregisterfile" ) 
	#define CAL_dynamictextregisterfile  dynamictextregisterfile
	#define CHK_dynamictextregisterfile  TRUE
	#define EXP_dynamictextregisterfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextregisterfile", (RTS_UINTPTR)dynamictextregisterfile, 1, RTSITF_GET_SIGNATURE(0x0C950958, 0), 0x03050700) 
#else /* DYNAMIC_LINK */
	#define USE_dynamictextregisterfile  PFDYNAMICTEXTREGISTERFILE_IEC pfdynamictextregisterfile;
	#define EXT_dynamictextregisterfile  extern PFDYNAMICTEXTREGISTERFILE_IEC pfdynamictextregisterfile;
	#define GET_dynamictextregisterfile(fl)  s_pfCMGetAPI2( "dynamictextregisterfile", (RTS_VOID_FCTPTR *)&pfdynamictextregisterfile, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x0C950958, 0), 0x03050700)
	#define CAL_dynamictextregisterfile  pfdynamictextregisterfile
	#define CHK_dynamictextregisterfile  (pfdynamictextregisterfile != NULL)
	#define EXP_dynamictextregisterfile   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextregisterfile", (RTS_UINTPTR)dynamictextregisterfile, 1, RTSITF_GET_SIGNATURE(0x0C950958, 0), 0x03050700) 
#endif


/**
 * This function unregisters a dynamic text file.
 * The registered text files are considered when load or reload is called
 * on the CmpDynamicText component.  
 */
typedef struct tagdynamictextunregisterfile_struct
{
	RTS_IEC_STRING *szFile;				/* VAR_INPUT */	
	RTS_IEC_RESULT DynamicTextUnRegisterFile;	/* VAR_OUTPUT */	
} dynamictextunregisterfile_struct;

void CDECL CDECL_EXT dynamictextunregisterfile(dynamictextunregisterfile_struct *p);
typedef void (CDECL CDECL_EXT* PFDYNAMICTEXTUNREGISTERFILE_IEC) (dynamictextunregisterfile_struct *p);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(DYNAMICTEXTUNREGISTERFILE_NOTIMPLEMENTED)
	#define USE_dynamictextunregisterfile
	#define EXT_dynamictextunregisterfile
	#define GET_dynamictextunregisterfile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dynamictextunregisterfile(p0) 
	#define CHK_dynamictextunregisterfile  FALSE
	#define EXP_dynamictextunregisterfile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dynamictextunregisterfile
	#define EXT_dynamictextunregisterfile
	#define GET_dynamictextunregisterfile(fl)  CAL_CMGETAPI( "dynamictextunregisterfile" ) 
	#define CAL_dynamictextunregisterfile  dynamictextunregisterfile
	#define CHK_dynamictextunregisterfile  TRUE
	#define EXP_dynamictextunregisterfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextunregisterfile", (RTS_UINTPTR)dynamictextunregisterfile, 1, RTSITF_GET_SIGNATURE(0x1476C0B1, 0), 0x03050700) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_dynamictextunregisterfile
	#define EXT_dynamictextunregisterfile
	#define GET_dynamictextunregisterfile(fl)  CAL_CMGETAPI( "dynamictextunregisterfile" ) 
	#define CAL_dynamictextunregisterfile  dynamictextunregisterfile
	#define CHK_dynamictextunregisterfile  TRUE
	#define EXP_dynamictextunregisterfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextunregisterfile", (RTS_UINTPTR)dynamictextunregisterfile, 1, RTSITF_GET_SIGNATURE(0x1476C0B1, 0), 0x03050700) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextdynamictextunregisterfile
	#define EXT_CmpDynamicTextdynamictextunregisterfile
	#define GET_CmpDynamicTextdynamictextunregisterfile  ERR_OK
	#define CAL_CmpDynamicTextdynamictextunregisterfile  dynamictextunregisterfile
	#define CHK_CmpDynamicTextdynamictextunregisterfile  TRUE
	#define EXP_CmpDynamicTextdynamictextunregisterfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextunregisterfile", (RTS_UINTPTR)dynamictextunregisterfile, 1, RTSITF_GET_SIGNATURE(0x1476C0B1, 0), 0x03050700) 
#elif defined(CPLUSPLUS)
	#define USE_dynamictextunregisterfile
	#define EXT_dynamictextunregisterfile
	#define GET_dynamictextunregisterfile(fl)  CAL_CMGETAPI( "dynamictextunregisterfile" ) 
	#define CAL_dynamictextunregisterfile  dynamictextunregisterfile
	#define CHK_dynamictextunregisterfile  TRUE
	#define EXP_dynamictextunregisterfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextunregisterfile", (RTS_UINTPTR)dynamictextunregisterfile, 1, RTSITF_GET_SIGNATURE(0x1476C0B1, 0), 0x03050700) 
#else /* DYNAMIC_LINK */
	#define USE_dynamictextunregisterfile  PFDYNAMICTEXTUNREGISTERFILE_IEC pfdynamictextunregisterfile;
	#define EXT_dynamictextunregisterfile  extern PFDYNAMICTEXTUNREGISTERFILE_IEC pfdynamictextunregisterfile;
	#define GET_dynamictextunregisterfile(fl)  s_pfCMGetAPI2( "dynamictextunregisterfile", (RTS_VOID_FCTPTR *)&pfdynamictextunregisterfile, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x1476C0B1, 0), 0x03050700)
	#define CAL_dynamictextunregisterfile  pfdynamictextunregisterfile
	#define CHK_dynamictextunregisterfile  (pfdynamictextunregisterfile != NULL)
	#define EXP_dynamictextunregisterfile   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextunregisterfile", (RTS_UINTPTR)dynamictextunregisterfile, 1, RTSITF_GET_SIGNATURE(0x1476C0B1, 0), 0x03050700) 
#endif


/**
 * This function sets an optional path where the dynamic text files
 * are searched when they are loaded or reloaded by the CmpDynamicText component. 
 */
typedef struct tagdynamictextregisterpath_struct
{
	RTS_IEC_STRING *szPath;				/* VAR_INPUT */	
	RTS_IEC_RESULT DynamicTextRegisterPath;	/* VAR_OUTPUT */	
} dynamictextregisterpath_struct;

void CDECL CDECL_EXT dynamictextregisterpath(dynamictextregisterpath_struct *p);
typedef void (CDECL CDECL_EXT* PFDYNAMICTEXTREGISTERPATH_IEC) (dynamictextregisterpath_struct *p);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(DYNAMICTEXTREGISTERPATH_NOTIMPLEMENTED)
	#define USE_dynamictextregisterpath
	#define EXT_dynamictextregisterpath
	#define GET_dynamictextregisterpath(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dynamictextregisterpath(p0) 
	#define CHK_dynamictextregisterpath  FALSE
	#define EXP_dynamictextregisterpath  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dynamictextregisterpath
	#define EXT_dynamictextregisterpath
	#define GET_dynamictextregisterpath(fl)  CAL_CMGETAPI( "dynamictextregisterpath" ) 
	#define CAL_dynamictextregisterpath  dynamictextregisterpath
	#define CHK_dynamictextregisterpath  TRUE
	#define EXP_dynamictextregisterpath  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextregisterpath", (RTS_UINTPTR)dynamictextregisterpath, 1, RTSITF_GET_SIGNATURE(0x1DBE3355, 0), 0x03050700) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_dynamictextregisterpath
	#define EXT_dynamictextregisterpath
	#define GET_dynamictextregisterpath(fl)  CAL_CMGETAPI( "dynamictextregisterpath" ) 
	#define CAL_dynamictextregisterpath  dynamictextregisterpath
	#define CHK_dynamictextregisterpath  TRUE
	#define EXP_dynamictextregisterpath  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextregisterpath", (RTS_UINTPTR)dynamictextregisterpath, 1, RTSITF_GET_SIGNATURE(0x1DBE3355, 0), 0x03050700) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextdynamictextregisterpath
	#define EXT_CmpDynamicTextdynamictextregisterpath
	#define GET_CmpDynamicTextdynamictextregisterpath  ERR_OK
	#define CAL_CmpDynamicTextdynamictextregisterpath  dynamictextregisterpath
	#define CHK_CmpDynamicTextdynamictextregisterpath  TRUE
	#define EXP_CmpDynamicTextdynamictextregisterpath  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextregisterpath", (RTS_UINTPTR)dynamictextregisterpath, 1, RTSITF_GET_SIGNATURE(0x1DBE3355, 0), 0x03050700) 
#elif defined(CPLUSPLUS)
	#define USE_dynamictextregisterpath
	#define EXT_dynamictextregisterpath
	#define GET_dynamictextregisterpath(fl)  CAL_CMGETAPI( "dynamictextregisterpath" ) 
	#define CAL_dynamictextregisterpath  dynamictextregisterpath
	#define CHK_dynamictextregisterpath  TRUE
	#define EXP_dynamictextregisterpath  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextregisterpath", (RTS_UINTPTR)dynamictextregisterpath, 1, RTSITF_GET_SIGNATURE(0x1DBE3355, 0), 0x03050700) 
#else /* DYNAMIC_LINK */
	#define USE_dynamictextregisterpath  PFDYNAMICTEXTREGISTERPATH_IEC pfdynamictextregisterpath;
	#define EXT_dynamictextregisterpath  extern PFDYNAMICTEXTREGISTERPATH_IEC pfdynamictextregisterpath;
	#define GET_dynamictextregisterpath(fl)  s_pfCMGetAPI2( "dynamictextregisterpath", (RTS_VOID_FCTPTR *)&pfdynamictextregisterpath, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x1DBE3355, 0), 0x03050700)
	#define CAL_dynamictextregisterpath  pfdynamictextregisterpath
	#define CHK_dynamictextregisterpath  (pfdynamictextregisterpath != NULL)
	#define EXP_dynamictextregisterpath   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dynamictextregisterpath", (RTS_UINTPTR)dynamictextregisterpath, 1, RTSITF_GET_SIGNATURE(0x1DBE3355, 0), 0x03050700) 
#endif


/**
 * OBSOLETE FUNCTION: Use dynamictextchangelanguage instead
 * <description> Function to change the language of all language specific texts.</description>
 * <param name="pszLanguage" type="IN">The new language</param>
 */
void CDECL CDECL_EXT visufctchangelanguage(dynamictextchangelanguage_struct* pParam);
typedef void (CDECL CDECL_EXT* PFVISUFCTCHANGELANGUAGE_IEC) (dynamictextchangelanguage_struct* pParam);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(VISUFCTCHANGELANGUAGE_NOTIMPLEMENTED)
	#define USE_visufctchangelanguage
	#define EXT_visufctchangelanguage
	#define GET_visufctchangelanguage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_visufctchangelanguage(p0) 
	#define CHK_visufctchangelanguage  FALSE
	#define EXP_visufctchangelanguage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_visufctchangelanguage
	#define EXT_visufctchangelanguage
	#define GET_visufctchangelanguage(fl)  CAL_CMGETAPI( "visufctchangelanguage" ) 
	#define CAL_visufctchangelanguage  visufctchangelanguage
	#define CHK_visufctchangelanguage  TRUE
	#define EXP_visufctchangelanguage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctchangelanguage", (RTS_UINTPTR)visufctchangelanguage, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_visufctchangelanguage
	#define EXT_visufctchangelanguage
	#define GET_visufctchangelanguage(fl)  CAL_CMGETAPI( "visufctchangelanguage" ) 
	#define CAL_visufctchangelanguage  visufctchangelanguage
	#define CHK_visufctchangelanguage  TRUE
	#define EXP_visufctchangelanguage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctchangelanguage", (RTS_UINTPTR)visufctchangelanguage, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextvisufctchangelanguage
	#define EXT_CmpDynamicTextvisufctchangelanguage
	#define GET_CmpDynamicTextvisufctchangelanguage  ERR_OK
	#define CAL_CmpDynamicTextvisufctchangelanguage  visufctchangelanguage
	#define CHK_CmpDynamicTextvisufctchangelanguage  TRUE
	#define EXP_CmpDynamicTextvisufctchangelanguage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctchangelanguage", (RTS_UINTPTR)visufctchangelanguage, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_visufctchangelanguage
	#define EXT_visufctchangelanguage
	#define GET_visufctchangelanguage(fl)  CAL_CMGETAPI( "visufctchangelanguage" ) 
	#define CAL_visufctchangelanguage  visufctchangelanguage
	#define CHK_visufctchangelanguage  TRUE
	#define EXP_visufctchangelanguage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctchangelanguage", (RTS_UINTPTR)visufctchangelanguage, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_visufctchangelanguage  PFVISUFCTCHANGELANGUAGE_IEC pfvisufctchangelanguage;
	#define EXT_visufctchangelanguage  extern PFVISUFCTCHANGELANGUAGE_IEC pfvisufctchangelanguage;
	#define GET_visufctchangelanguage(fl)  s_pfCMGetAPI2( "visufctchangelanguage", (RTS_VOID_FCTPTR *)&pfvisufctchangelanguage, (fl), 0, 0)
	#define CAL_visufctchangelanguage  pfvisufctchangelanguage
	#define CHK_visufctchangelanguage  (pfvisufctchangelanguage != NULL)
	#define EXP_visufctchangelanguage   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctchangelanguage", (RTS_UINTPTR)visufctchangelanguage, 1, 0) 
#endif


/**
 * OBSOLETE FUNCTION: Use dynamictextgettext instead
 * <description> Provides functionality to gain language specific texts from a dynamic text file </description>
 * <param name="pszPrefix" type="IN">The prefix specifier</param>
 * <param name="pszId" type="IN">The id specifier</param>
 * <param name="pszOut" type="OUT">The corresponding text</param>
 */
void CDECL CDECL_EXT visufctgettext(dynamictextgettext_struct* pParam);
typedef void (CDECL CDECL_EXT* PFVISUFCTGETTEXT_IEC) (dynamictextgettext_struct* pParam);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(VISUFCTGETTEXT_NOTIMPLEMENTED)
	#define USE_visufctgettext
	#define EXT_visufctgettext
	#define GET_visufctgettext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_visufctgettext(p0) 
	#define CHK_visufctgettext  FALSE
	#define EXP_visufctgettext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_visufctgettext
	#define EXT_visufctgettext
	#define GET_visufctgettext(fl)  CAL_CMGETAPI( "visufctgettext" ) 
	#define CAL_visufctgettext  visufctgettext
	#define CHK_visufctgettext  TRUE
	#define EXP_visufctgettext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgettext", (RTS_UINTPTR)visufctgettext, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_visufctgettext
	#define EXT_visufctgettext
	#define GET_visufctgettext(fl)  CAL_CMGETAPI( "visufctgettext" ) 
	#define CAL_visufctgettext  visufctgettext
	#define CHK_visufctgettext  TRUE
	#define EXP_visufctgettext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgettext", (RTS_UINTPTR)visufctgettext, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextvisufctgettext
	#define EXT_CmpDynamicTextvisufctgettext
	#define GET_CmpDynamicTextvisufctgettext  ERR_OK
	#define CAL_CmpDynamicTextvisufctgettext  visufctgettext
	#define CHK_CmpDynamicTextvisufctgettext  TRUE
	#define EXP_CmpDynamicTextvisufctgettext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgettext", (RTS_UINTPTR)visufctgettext, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_visufctgettext
	#define EXT_visufctgettext
	#define GET_visufctgettext(fl)  CAL_CMGETAPI( "visufctgettext" ) 
	#define CAL_visufctgettext  visufctgettext
	#define CHK_visufctgettext  TRUE
	#define EXP_visufctgettext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgettext", (RTS_UINTPTR)visufctgettext, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_visufctgettext  PFVISUFCTGETTEXT_IEC pfvisufctgettext;
	#define EXT_visufctgettext  extern PFVISUFCTGETTEXT_IEC pfvisufctgettext;
	#define GET_visufctgettext(fl)  s_pfCMGetAPI2( "visufctgettext", (RTS_VOID_FCTPTR *)&pfvisufctgettext, (fl), 0, 0)
	#define CAL_visufctgettext  pfvisufctgettext
	#define CHK_visufctgettext  (pfvisufctgettext != NULL)
	#define EXP_visufctgettext   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgettext", (RTS_UINTPTR)visufctgettext, 1, 0) 
#endif


/**
 * OBSOLETE FUNCTION: Use dynamictextgettextw instead
 * <description> WString version of VisuFctGetText, for further documentation see VisuFctGetText </description>
 */
void CDECL CDECL_EXT visufctgettextw(dynamictextgettextw_struct* pParam);
typedef void (CDECL CDECL_EXT* PFVISUFCTGETTEXTW_IEC) (dynamictextgettextw_struct* pParam);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(VISUFCTGETTEXTW_NOTIMPLEMENTED)
	#define USE_visufctgettextw
	#define EXT_visufctgettextw
	#define GET_visufctgettextw(fl)  ERR_NOTIMPLEMENTED
	#define CAL_visufctgettextw(p0) 
	#define CHK_visufctgettextw  FALSE
	#define EXP_visufctgettextw  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_visufctgettextw
	#define EXT_visufctgettextw
	#define GET_visufctgettextw(fl)  CAL_CMGETAPI( "visufctgettextw" ) 
	#define CAL_visufctgettextw  visufctgettextw
	#define CHK_visufctgettextw  TRUE
	#define EXP_visufctgettextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgettextw", (RTS_UINTPTR)visufctgettextw, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_visufctgettextw
	#define EXT_visufctgettextw
	#define GET_visufctgettextw(fl)  CAL_CMGETAPI( "visufctgettextw" ) 
	#define CAL_visufctgettextw  visufctgettextw
	#define CHK_visufctgettextw  TRUE
	#define EXP_visufctgettextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgettextw", (RTS_UINTPTR)visufctgettextw, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextvisufctgettextw
	#define EXT_CmpDynamicTextvisufctgettextw
	#define GET_CmpDynamicTextvisufctgettextw  ERR_OK
	#define CAL_CmpDynamicTextvisufctgettextw  visufctgettextw
	#define CHK_CmpDynamicTextvisufctgettextw  TRUE
	#define EXP_CmpDynamicTextvisufctgettextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgettextw", (RTS_UINTPTR)visufctgettextw, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_visufctgettextw
	#define EXT_visufctgettextw
	#define GET_visufctgettextw(fl)  CAL_CMGETAPI( "visufctgettextw" ) 
	#define CAL_visufctgettextw  visufctgettextw
	#define CHK_visufctgettextw  TRUE
	#define EXP_visufctgettextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgettextw", (RTS_UINTPTR)visufctgettextw, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_visufctgettextw  PFVISUFCTGETTEXTW_IEC pfvisufctgettextw;
	#define EXT_visufctgettextw  extern PFVISUFCTGETTEXTW_IEC pfvisufctgettextw;
	#define GET_visufctgettextw(fl)  s_pfCMGetAPI2( "visufctgettextw", (RTS_VOID_FCTPTR *)&pfvisufctgettextw, (fl), 0, 0)
	#define CAL_visufctgettextw  pfvisufctgettextw
	#define CHK_visufctgettextw  (pfvisufctgettextw != NULL)
	#define EXP_visufctgettextw   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgettextw", (RTS_UINTPTR)visufctgettextw, 1, 0) 
#endif


/**
 * OBSOLETE FUNCTION: Use dynamictextgetdefaulttext instead
 * <description> Provides functionality to gain default texts from a dynamic text file </description>
 * <param name="pszPrefix" type="IN">The prefix specifier</param>
 * <param name="pszId" type="IN">The id specifier</param>
 * <param name="pszOut" type="OUT">The corresponding text</param>
 */
void CDECL CDECL_EXT visufctgetdefaulttext(dynamictextgettext_struct* pParam);
typedef void (CDECL CDECL_EXT* PFVISUFCTGETDEFAULTTEXT_IEC) (dynamictextgettext_struct* pParam);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(VISUFCTGETDEFAULTTEXT_NOTIMPLEMENTED)
	#define USE_visufctgetdefaulttext
	#define EXT_visufctgetdefaulttext
	#define GET_visufctgetdefaulttext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_visufctgetdefaulttext(p0) 
	#define CHK_visufctgetdefaulttext  FALSE
	#define EXP_visufctgetdefaulttext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_visufctgetdefaulttext
	#define EXT_visufctgetdefaulttext
	#define GET_visufctgetdefaulttext(fl)  CAL_CMGETAPI( "visufctgetdefaulttext" ) 
	#define CAL_visufctgetdefaulttext  visufctgetdefaulttext
	#define CHK_visufctgetdefaulttext  TRUE
	#define EXP_visufctgetdefaulttext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgetdefaulttext", (RTS_UINTPTR)visufctgetdefaulttext, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_visufctgetdefaulttext
	#define EXT_visufctgetdefaulttext
	#define GET_visufctgetdefaulttext(fl)  CAL_CMGETAPI( "visufctgetdefaulttext" ) 
	#define CAL_visufctgetdefaulttext  visufctgetdefaulttext
	#define CHK_visufctgetdefaulttext  TRUE
	#define EXP_visufctgetdefaulttext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgetdefaulttext", (RTS_UINTPTR)visufctgetdefaulttext, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextvisufctgetdefaulttext
	#define EXT_CmpDynamicTextvisufctgetdefaulttext
	#define GET_CmpDynamicTextvisufctgetdefaulttext  ERR_OK
	#define CAL_CmpDynamicTextvisufctgetdefaulttext  visufctgetdefaulttext
	#define CHK_CmpDynamicTextvisufctgetdefaulttext  TRUE
	#define EXP_CmpDynamicTextvisufctgetdefaulttext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgetdefaulttext", (RTS_UINTPTR)visufctgetdefaulttext, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_visufctgetdefaulttext
	#define EXT_visufctgetdefaulttext
	#define GET_visufctgetdefaulttext(fl)  CAL_CMGETAPI( "visufctgetdefaulttext" ) 
	#define CAL_visufctgetdefaulttext  visufctgetdefaulttext
	#define CHK_visufctgetdefaulttext  TRUE
	#define EXP_visufctgetdefaulttext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgetdefaulttext", (RTS_UINTPTR)visufctgetdefaulttext, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_visufctgetdefaulttext  PFVISUFCTGETDEFAULTTEXT_IEC pfvisufctgetdefaulttext;
	#define EXT_visufctgetdefaulttext  extern PFVISUFCTGETDEFAULTTEXT_IEC pfvisufctgetdefaulttext;
	#define GET_visufctgetdefaulttext(fl)  s_pfCMGetAPI2( "visufctgetdefaulttext", (RTS_VOID_FCTPTR *)&pfvisufctgetdefaulttext, (fl), 0, 0)
	#define CAL_visufctgetdefaulttext  pfvisufctgetdefaulttext
	#define CHK_visufctgetdefaulttext  (pfvisufctgetdefaulttext != NULL)
	#define EXP_visufctgetdefaulttext   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgetdefaulttext", (RTS_UINTPTR)visufctgetdefaulttext, 1, 0) 
#endif


/**
 * OBSOLETE FUNCTION: Use dynamictextgetdefaulttextw instead
 * <description> WString version of VisuFctGetDefaultText, for further documentation see VisuFctGetDefaultText </description>
 */
void CDECL CDECL_EXT visufctgetdefaulttextw(dynamictextgettextw_struct* pParam);
typedef void (CDECL CDECL_EXT* PFVISUFCTGETDEFAULTTEXTW_IEC) (dynamictextgettextw_struct* pParam);
#if defined(CMPDYNAMICTEXT_NOTIMPLEMENTED) || defined(VISUFCTGETDEFAULTTEXTW_NOTIMPLEMENTED)
	#define USE_visufctgetdefaulttextw
	#define EXT_visufctgetdefaulttextw
	#define GET_visufctgetdefaulttextw(fl)  ERR_NOTIMPLEMENTED
	#define CAL_visufctgetdefaulttextw(p0) 
	#define CHK_visufctgetdefaulttextw  FALSE
	#define EXP_visufctgetdefaulttextw  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_visufctgetdefaulttextw
	#define EXT_visufctgetdefaulttextw
	#define GET_visufctgetdefaulttextw(fl)  CAL_CMGETAPI( "visufctgetdefaulttextw" ) 
	#define CAL_visufctgetdefaulttextw  visufctgetdefaulttextw
	#define CHK_visufctgetdefaulttextw  TRUE
	#define EXP_visufctgetdefaulttextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgetdefaulttextw", (RTS_UINTPTR)visufctgetdefaulttextw, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPDYNAMICTEXT_EXTERNAL)
	#define USE_visufctgetdefaulttextw
	#define EXT_visufctgetdefaulttextw
	#define GET_visufctgetdefaulttextw(fl)  CAL_CMGETAPI( "visufctgetdefaulttextw" ) 
	#define CAL_visufctgetdefaulttextw  visufctgetdefaulttextw
	#define CHK_visufctgetdefaulttextw  TRUE
	#define EXP_visufctgetdefaulttextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgetdefaulttextw", (RTS_UINTPTR)visufctgetdefaulttextw, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpDynamicTextvisufctgetdefaulttextw
	#define EXT_CmpDynamicTextvisufctgetdefaulttextw
	#define GET_CmpDynamicTextvisufctgetdefaulttextw  ERR_OK
	#define CAL_CmpDynamicTextvisufctgetdefaulttextw  visufctgetdefaulttextw
	#define CHK_CmpDynamicTextvisufctgetdefaulttextw  TRUE
	#define EXP_CmpDynamicTextvisufctgetdefaulttextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgetdefaulttextw", (RTS_UINTPTR)visufctgetdefaulttextw, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_visufctgetdefaulttextw
	#define EXT_visufctgetdefaulttextw
	#define GET_visufctgetdefaulttextw(fl)  CAL_CMGETAPI( "visufctgetdefaulttextw" ) 
	#define CAL_visufctgetdefaulttextw  visufctgetdefaulttextw
	#define CHK_visufctgetdefaulttextw  TRUE
	#define EXP_visufctgetdefaulttextw  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgetdefaulttextw", (RTS_UINTPTR)visufctgetdefaulttextw, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_visufctgetdefaulttextw  PFVISUFCTGETDEFAULTTEXTW_IEC pfvisufctgetdefaulttextw;
	#define EXT_visufctgetdefaulttextw  extern PFVISUFCTGETDEFAULTTEXTW_IEC pfvisufctgetdefaulttextw;
	#define GET_visufctgetdefaulttextw(fl)  s_pfCMGetAPI2( "visufctgetdefaulttextw", (RTS_VOID_FCTPTR *)&pfvisufctgetdefaulttextw, (fl), 0, 0)
	#define CAL_visufctgetdefaulttextw  pfvisufctgetdefaulttextw
	#define CHK_visufctgetdefaulttextw  (pfvisufctgetdefaulttextw != NULL)
	#define EXP_visufctgetdefaulttextw   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"visufctgetdefaulttextw", (RTS_UINTPTR)visufctgetdefaulttextw, 1, 0) 
#endif



#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpDynamicText_C;

#ifdef CPLUSPLUS
class ICmpDynamicText : public IBase
{
	public:
};
	#ifndef ITF_CmpDynamicText
		#define ITF_CmpDynamicText static ICmpDynamicText *pICmpDynamicText = NULL;
	#endif
	#define EXTITF_CmpDynamicText
#else	/*CPLUSPLUS*/
	typedef ICmpDynamicText_C		ICmpDynamicText;
	#ifndef ITF_CmpDynamicText
		#define ITF_CmpDynamicText
	#endif
	#define EXTITF_CmpDynamicText
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPDYNAMICTEXTITF_H_*/
