 /**
 * <interfacename>CmpBitmapPool</interfacename>
 * <description> 
 *	<p>Interface for the bitmap pool manager.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPBITMAPPOOLITF_H_
#define _CMPBITMAPPOOLITF_H_

#include "CmpStd.h"

 

 




/**
 * <category>BimapPool Settings</category>
 * <description>Setting which decides about the file that contains the contents of the bitmappool</description>
 *
 */
#ifndef BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT
	#define BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT "IPCBitmapPool"
#endif /* BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT */

#ifndef BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT_EXTENSION
	/* tmb was chosen (instead of possibly tmp) to be able to distinguis between the temporary files used in the filetransfer and
		this temporary file */
	#define BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT_EXTENSION ".tmb"			
#endif /* BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT_EXTENSION */

/**
 * <description>Setting which decides about the path where the configuration file and all 
 * the bitmaps are saved. Default is the current working directory.</description>
 *
 */
#define BMPPOOL_KEY_BASEPATH "BitmapPath"
#define BMPPOOL_VALUE_BASEPATH_DEFAULT ""

typedef struct
{
	RTS_IEC_STRING* pszId;
	RTS_IEC_STRING* pszPath;
	RTS_I32	Result;
} bitmappoolregister_struct;

typedef struct
{
	RTS_IEC_STRING* pszId;
	RTS_I32	Result;
} bitmappoolunregister_struct;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> Add a bitmap pool entry from plc program</description>
 * <param name="pEntry" type="IN">Pointer to entry structure</param>
 * <result></result>
 */
void CDECL CDECL_EXT bmppoolregister(bitmappoolregister_struct *pEntry);
typedef void (CDECL CDECL_EXT* PFBMPPOOLREGISTER_IEC) (bitmappoolregister_struct *pEntry);
#if defined(CMPBITMAPPOOL_NOTIMPLEMENTED) || defined(BMPPOOLREGISTER_NOTIMPLEMENTED)
	#define USE_bmppoolregister
	#define EXT_bmppoolregister
	#define GET_bmppoolregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_bmppoolregister(p0) 
	#define CHK_bmppoolregister  FALSE
	#define EXP_bmppoolregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_bmppoolregister
	#define EXT_bmppoolregister
	#define GET_bmppoolregister(fl)  CAL_CMGETAPI( "bmppoolregister" ) 
	#define CAL_bmppoolregister  bmppoolregister
	#define CHK_bmppoolregister  TRUE
	#define EXP_bmppoolregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"bmppoolregister", (RTS_UINTPTR)bmppoolregister, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPBITMAPPOOL_EXTERNAL)
	#define USE_bmppoolregister
	#define EXT_bmppoolregister
	#define GET_bmppoolregister(fl)  CAL_CMGETAPI( "bmppoolregister" ) 
	#define CAL_bmppoolregister  bmppoolregister
	#define CHK_bmppoolregister  TRUE
	#define EXP_bmppoolregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"bmppoolregister", (RTS_UINTPTR)bmppoolregister, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBitmapPoolbmppoolregister
	#define EXT_CmpBitmapPoolbmppoolregister
	#define GET_CmpBitmapPoolbmppoolregister  ERR_OK
	#define CAL_CmpBitmapPoolbmppoolregister  bmppoolregister
	#define CHK_CmpBitmapPoolbmppoolregister  TRUE
	#define EXP_CmpBitmapPoolbmppoolregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"bmppoolregister", (RTS_UINTPTR)bmppoolregister, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_bmppoolregister
	#define EXT_bmppoolregister
	#define GET_bmppoolregister(fl)  CAL_CMGETAPI( "bmppoolregister" ) 
	#define CAL_bmppoolregister  bmppoolregister
	#define CHK_bmppoolregister  TRUE
	#define EXP_bmppoolregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"bmppoolregister", (RTS_UINTPTR)bmppoolregister, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_bmppoolregister  PFBMPPOOLREGISTER_IEC pfbmppoolregister;
	#define EXT_bmppoolregister  extern PFBMPPOOLREGISTER_IEC pfbmppoolregister;
	#define GET_bmppoolregister(fl)  s_pfCMGetAPI2( "bmppoolregister", (RTS_VOID_FCTPTR *)&pfbmppoolregister, (fl), 0, 0)
	#define CAL_bmppoolregister  pfbmppoolregister
	#define CHK_bmppoolregister  (pfbmppoolregister != NULL)
	#define EXP_bmppoolregister   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"bmppoolregister", (RTS_UINTPTR)bmppoolregister, 1, 0) 
#endif


/**
 * <description> Remove a bitmap pool entry from plc program</description>
 * <param name="pEntry" type="IN">Pointer to entry structure</param>
 * <result></result>
 */
void CDECL CDECL_EXT bmppoolunregister(bitmappoolunregister_struct *pEntry);
typedef void (CDECL CDECL_EXT* PFBMPPOOLUNREGISTER_IEC) (bitmappoolunregister_struct *pEntry);
#if defined(CMPBITMAPPOOL_NOTIMPLEMENTED) || defined(BMPPOOLUNREGISTER_NOTIMPLEMENTED)
	#define USE_bmppoolunregister
	#define EXT_bmppoolunregister
	#define GET_bmppoolunregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_bmppoolunregister(p0) 
	#define CHK_bmppoolunregister  FALSE
	#define EXP_bmppoolunregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_bmppoolunregister
	#define EXT_bmppoolunregister
	#define GET_bmppoolunregister(fl)  CAL_CMGETAPI( "bmppoolunregister" ) 
	#define CAL_bmppoolunregister  bmppoolunregister
	#define CHK_bmppoolunregister  TRUE
	#define EXP_bmppoolunregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"bmppoolunregister", (RTS_UINTPTR)bmppoolunregister, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPBITMAPPOOL_EXTERNAL)
	#define USE_bmppoolunregister
	#define EXT_bmppoolunregister
	#define GET_bmppoolunregister(fl)  CAL_CMGETAPI( "bmppoolunregister" ) 
	#define CAL_bmppoolunregister  bmppoolunregister
	#define CHK_bmppoolunregister  TRUE
	#define EXP_bmppoolunregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"bmppoolunregister", (RTS_UINTPTR)bmppoolunregister, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBitmapPoolbmppoolunregister
	#define EXT_CmpBitmapPoolbmppoolunregister
	#define GET_CmpBitmapPoolbmppoolunregister  ERR_OK
	#define CAL_CmpBitmapPoolbmppoolunregister  bmppoolunregister
	#define CHK_CmpBitmapPoolbmppoolunregister  TRUE
	#define EXP_CmpBitmapPoolbmppoolunregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"bmppoolunregister", (RTS_UINTPTR)bmppoolunregister, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_bmppoolunregister
	#define EXT_bmppoolunregister
	#define GET_bmppoolunregister(fl)  CAL_CMGETAPI( "bmppoolunregister" ) 
	#define CAL_bmppoolunregister  bmppoolunregister
	#define CHK_bmppoolunregister  TRUE
	#define EXP_bmppoolunregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"bmppoolunregister", (RTS_UINTPTR)bmppoolunregister, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_bmppoolunregister  PFBMPPOOLUNREGISTER_IEC pfbmppoolunregister;
	#define EXT_bmppoolunregister  extern PFBMPPOOLUNREGISTER_IEC pfbmppoolunregister;
	#define GET_bmppoolunregister(fl)  s_pfCMGetAPI2( "bmppoolunregister", (RTS_VOID_FCTPTR *)&pfbmppoolunregister, (fl), 0, 0)
	#define CAL_bmppoolunregister  pfbmppoolunregister
	#define CHK_bmppoolunregister  (pfbmppoolunregister != NULL)
	#define EXP_bmppoolunregister   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"bmppoolunregister", (RTS_UINTPTR)bmppoolunregister, 1, 0) 
#endif


/**
 * <description>Registers a bitmap within the bitmappool.</description>
 * <param name="pszBmpId" type="IN">Id of the bitmap to register.</param>
 * <param name="pszPath" type="IN">The path of the registered bitmap.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL BmpPoolRegister(const char *pszBmpId, const char *pszPath);
typedef RTS_RESULT (CDECL * PFBMPPOOLREGISTER) (const char *pszBmpId, const char *pszPath);
#if defined(CMPBITMAPPOOL_NOTIMPLEMENTED) || defined(BMPPOOLREGISTER_NOTIMPLEMENTED)
	#define USE_BmpPoolRegister
	#define EXT_BmpPoolRegister
	#define GET_BmpPoolRegister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BmpPoolRegister(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BmpPoolRegister  FALSE
	#define EXP_BmpPoolRegister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BmpPoolRegister
	#define EXT_BmpPoolRegister
	#define GET_BmpPoolRegister(fl)  CAL_CMGETAPI( "BmpPoolRegister" ) 
	#define CAL_BmpPoolRegister  BmpPoolRegister
	#define CHK_BmpPoolRegister  TRUE
	#define EXP_BmpPoolRegister  CAL_CMEXPAPI( "BmpPoolRegister" ) 
#elif defined(MIXED_LINK) && !defined(CMPBITMAPPOOL_EXTERNAL)
	#define USE_BmpPoolRegister
	#define EXT_BmpPoolRegister
	#define GET_BmpPoolRegister(fl)  CAL_CMGETAPI( "BmpPoolRegister" ) 
	#define CAL_BmpPoolRegister  BmpPoolRegister
	#define CHK_BmpPoolRegister  TRUE
	#define EXP_BmpPoolRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolRegister", (RTS_UINTPTR)BmpPoolRegister, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBitmapPoolBmpPoolRegister
	#define EXT_CmpBitmapPoolBmpPoolRegister
	#define GET_CmpBitmapPoolBmpPoolRegister  ERR_OK
	#define CAL_CmpBitmapPoolBmpPoolRegister pICmpBitmapPool->IBmpPoolRegister
	#define CHK_CmpBitmapPoolBmpPoolRegister (pICmpBitmapPool != NULL)
	#define EXP_CmpBitmapPoolBmpPoolRegister  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BmpPoolRegister
	#define EXT_BmpPoolRegister
	#define GET_BmpPoolRegister(fl)  CAL_CMGETAPI( "BmpPoolRegister" ) 
	#define CAL_BmpPoolRegister pICmpBitmapPool->IBmpPoolRegister
	#define CHK_BmpPoolRegister (pICmpBitmapPool != NULL)
	#define EXP_BmpPoolRegister  CAL_CMEXPAPI( "BmpPoolRegister" ) 
#else /* DYNAMIC_LINK */
	#define USE_BmpPoolRegister  PFBMPPOOLREGISTER pfBmpPoolRegister;
	#define EXT_BmpPoolRegister  extern PFBMPPOOLREGISTER pfBmpPoolRegister;
	#define GET_BmpPoolRegister(fl)  s_pfCMGetAPI2( "BmpPoolRegister", (RTS_VOID_FCTPTR *)&pfBmpPoolRegister, (fl), 0, 0)
	#define CAL_BmpPoolRegister  pfBmpPoolRegister
	#define CHK_BmpPoolRegister  (pfBmpPoolRegister != NULL)
	#define EXP_BmpPoolRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolRegister", (RTS_UINTPTR)BmpPoolRegister, 0, 0) 
#endif




/**
 * <description>Removes a bitmap from the bitmappool.</description>
 * <param name="pszBmpId" type="IN">Id of the searched bitmap.</param>
 * <result>error code: ERR_OK in case of success, ERR_PARAMETER if the bitmap is not registered</result>
 */
RTS_RESULT CDECL BmpPoolUnregister(const char *pszBmpId);
typedef RTS_RESULT (CDECL * PFBMPPOOLUNREGISTER) (const char *pszBmpId);
#if defined(CMPBITMAPPOOL_NOTIMPLEMENTED) || defined(BMPPOOLUNREGISTER_NOTIMPLEMENTED)
	#define USE_BmpPoolUnregister
	#define EXT_BmpPoolUnregister
	#define GET_BmpPoolUnregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BmpPoolUnregister(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BmpPoolUnregister  FALSE
	#define EXP_BmpPoolUnregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BmpPoolUnregister
	#define EXT_BmpPoolUnregister
	#define GET_BmpPoolUnregister(fl)  CAL_CMGETAPI( "BmpPoolUnregister" ) 
	#define CAL_BmpPoolUnregister  BmpPoolUnregister
	#define CHK_BmpPoolUnregister  TRUE
	#define EXP_BmpPoolUnregister  CAL_CMEXPAPI( "BmpPoolUnregister" ) 
#elif defined(MIXED_LINK) && !defined(CMPBITMAPPOOL_EXTERNAL)
	#define USE_BmpPoolUnregister
	#define EXT_BmpPoolUnregister
	#define GET_BmpPoolUnregister(fl)  CAL_CMGETAPI( "BmpPoolUnregister" ) 
	#define CAL_BmpPoolUnregister  BmpPoolUnregister
	#define CHK_BmpPoolUnregister  TRUE
	#define EXP_BmpPoolUnregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolUnregister", (RTS_UINTPTR)BmpPoolUnregister, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBitmapPoolBmpPoolUnregister
	#define EXT_CmpBitmapPoolBmpPoolUnregister
	#define GET_CmpBitmapPoolBmpPoolUnregister  ERR_OK
	#define CAL_CmpBitmapPoolBmpPoolUnregister pICmpBitmapPool->IBmpPoolUnregister
	#define CHK_CmpBitmapPoolBmpPoolUnregister (pICmpBitmapPool != NULL)
	#define EXP_CmpBitmapPoolBmpPoolUnregister  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BmpPoolUnregister
	#define EXT_BmpPoolUnregister
	#define GET_BmpPoolUnregister(fl)  CAL_CMGETAPI( "BmpPoolUnregister" ) 
	#define CAL_BmpPoolUnregister pICmpBitmapPool->IBmpPoolUnregister
	#define CHK_BmpPoolUnregister (pICmpBitmapPool != NULL)
	#define EXP_BmpPoolUnregister  CAL_CMEXPAPI( "BmpPoolUnregister" ) 
#else /* DYNAMIC_LINK */
	#define USE_BmpPoolUnregister  PFBMPPOOLUNREGISTER pfBmpPoolUnregister;
	#define EXT_BmpPoolUnregister  extern PFBMPPOOLUNREGISTER pfBmpPoolUnregister;
	#define GET_BmpPoolUnregister(fl)  s_pfCMGetAPI2( "BmpPoolUnregister", (RTS_VOID_FCTPTR *)&pfBmpPoolUnregister, (fl), 0, 0)
	#define CAL_BmpPoolUnregister  pfBmpPoolUnregister
	#define CHK_BmpPoolUnregister  (pfBmpPoolUnregister != NULL)
	#define EXP_BmpPoolUnregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolUnregister", (RTS_UINTPTR)BmpPoolUnregister, 0, 0) 
#endif




/**
 * OBSOLETE FUNCTION: This function should not be used anymore.
 * <description>Returns the path of a bitmap that is handled by the BitmapPool</description>
 * <param name="pszBmpId" type="IN">Id of the searched bitmap.</param>
 * <param name="pszBmpPath" type="OUT">A string containing the path of the requested bitmap or NULL if 
 * it hasn't been found. The returned pointer will point to a string within the bitmap pool, so do not free
 * the returned string.</param>
 * <result>error code: ERR_OK, ERR_PARAMETER or ERR_INVALIDID if the bitmap is not registered</result>
 */
RTS_RESULT CDECL BmpPoolGetPath(const char *pszBmpId, const char **ppszBmpPath);
typedef RTS_RESULT (CDECL * PFBMPPOOLGETPATH) (const char *pszBmpId, const char **ppszBmpPath);
#if defined(CMPBITMAPPOOL_NOTIMPLEMENTED) || defined(BMPPOOLGETPATH_NOTIMPLEMENTED)
	#define USE_BmpPoolGetPath
	#define EXT_BmpPoolGetPath
	#define GET_BmpPoolGetPath(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BmpPoolGetPath(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BmpPoolGetPath  FALSE
	#define EXP_BmpPoolGetPath  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BmpPoolGetPath
	#define EXT_BmpPoolGetPath
	#define GET_BmpPoolGetPath(fl)  CAL_CMGETAPI( "BmpPoolGetPath" ) 
	#define CAL_BmpPoolGetPath  BmpPoolGetPath
	#define CHK_BmpPoolGetPath  TRUE
	#define EXP_BmpPoolGetPath  CAL_CMEXPAPI( "BmpPoolGetPath" ) 
#elif defined(MIXED_LINK) && !defined(CMPBITMAPPOOL_EXTERNAL)
	#define USE_BmpPoolGetPath
	#define EXT_BmpPoolGetPath
	#define GET_BmpPoolGetPath(fl)  CAL_CMGETAPI( "BmpPoolGetPath" ) 
	#define CAL_BmpPoolGetPath  BmpPoolGetPath
	#define CHK_BmpPoolGetPath  TRUE
	#define EXP_BmpPoolGetPath  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolGetPath", (RTS_UINTPTR)BmpPoolGetPath, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBitmapPoolBmpPoolGetPath
	#define EXT_CmpBitmapPoolBmpPoolGetPath
	#define GET_CmpBitmapPoolBmpPoolGetPath  ERR_OK
	#define CAL_CmpBitmapPoolBmpPoolGetPath  BmpPoolGetPath
	#define CHK_CmpBitmapPoolBmpPoolGetPath  TRUE
	#define EXP_CmpBitmapPoolBmpPoolGetPath  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BmpPoolGetPath
	#define EXT_BmpPoolGetPath
	#define GET_BmpPoolGetPath(fl)  CAL_CMGETAPI( "BmpPoolGetPath" ) 
	#define CAL_BmpPoolGetPath  BmpPoolGetPath
	#define CHK_BmpPoolGetPath  TRUE
	#define EXP_BmpPoolGetPath  CAL_CMEXPAPI( "BmpPoolGetPath" ) 
#else /* DYNAMIC_LINK */
	#define USE_BmpPoolGetPath  PFBMPPOOLGETPATH pfBmpPoolGetPath;
	#define EXT_BmpPoolGetPath  extern PFBMPPOOLGETPATH pfBmpPoolGetPath;
	#define GET_BmpPoolGetPath(fl)  s_pfCMGetAPI2( "BmpPoolGetPath", (RTS_VOID_FCTPTR *)&pfBmpPoolGetPath, (fl), 0, 0)
	#define CAL_BmpPoolGetPath  pfBmpPoolGetPath
	#define CHK_BmpPoolGetPath  (pfBmpPoolGetPath != NULL)
	#define EXP_BmpPoolGetPath   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolGetPath", (RTS_UINTPTR)BmpPoolGetPath, 0, 0) 
#endif


/**
 * <description>Clears the content of the bitmappool</description>
 * <result>error code</result>
 */
RTS_RESULT CDECL BmpPoolClear(void);
typedef RTS_RESULT (CDECL * PFBMPPOOLCLEAR) (void);
#if defined(CMPBITMAPPOOL_NOTIMPLEMENTED) || defined(BMPPOOLCLEAR_NOTIMPLEMENTED)
	#define USE_BmpPoolClear
	#define EXT_BmpPoolClear
	#define GET_BmpPoolClear(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BmpPoolClear() (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BmpPoolClear  FALSE
	#define EXP_BmpPoolClear  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BmpPoolClear
	#define EXT_BmpPoolClear
	#define GET_BmpPoolClear(fl)  CAL_CMGETAPI( "BmpPoolClear" ) 
	#define CAL_BmpPoolClear  BmpPoolClear
	#define CHK_BmpPoolClear  TRUE
	#define EXP_BmpPoolClear  CAL_CMEXPAPI( "BmpPoolClear" ) 
#elif defined(MIXED_LINK) && !defined(CMPBITMAPPOOL_EXTERNAL)
	#define USE_BmpPoolClear
	#define EXT_BmpPoolClear
	#define GET_BmpPoolClear(fl)  CAL_CMGETAPI( "BmpPoolClear" ) 
	#define CAL_BmpPoolClear  BmpPoolClear
	#define CHK_BmpPoolClear  TRUE
	#define EXP_BmpPoolClear  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolClear", (RTS_UINTPTR)BmpPoolClear, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBitmapPoolBmpPoolClear
	#define EXT_CmpBitmapPoolBmpPoolClear
	#define GET_CmpBitmapPoolBmpPoolClear  ERR_OK
	#define CAL_CmpBitmapPoolBmpPoolClear  BmpPoolClear
	#define CHK_CmpBitmapPoolBmpPoolClear  TRUE
	#define EXP_CmpBitmapPoolBmpPoolClear  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BmpPoolClear
	#define EXT_BmpPoolClear
	#define GET_BmpPoolClear(fl)  CAL_CMGETAPI( "BmpPoolClear" ) 
	#define CAL_BmpPoolClear  BmpPoolClear
	#define CHK_BmpPoolClear  TRUE
	#define EXP_BmpPoolClear  CAL_CMEXPAPI( "BmpPoolClear" ) 
#else /* DYNAMIC_LINK */
	#define USE_BmpPoolClear  PFBMPPOOLCLEAR pfBmpPoolClear;
	#define EXT_BmpPoolClear  extern PFBMPPOOLCLEAR pfBmpPoolClear;
	#define GET_BmpPoolClear(fl)  s_pfCMGetAPI2( "BmpPoolClear", (RTS_VOID_FCTPTR *)&pfBmpPoolClear, (fl), 0, 0)
	#define CAL_BmpPoolClear  pfBmpPoolClear
	#define CHK_BmpPoolClear  (pfBmpPoolClear != NULL)
	#define EXP_BmpPoolClear   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolClear", (RTS_UINTPTR)BmpPoolClear, 0, 0) 
#endif


/**
 * <description>Loads the contents of the bitmappool from the configured location.</description>
 * <result>error code</result>
 */
RTS_RESULT CDECL BmpPoolReadContents(char *pszFilePath, RTS_BOOL bDelete);
typedef RTS_RESULT (CDECL * PFBMPPOOLREADCONTENTS) (char *pszFilePath, RTS_BOOL bDelete);
#if defined(CMPBITMAPPOOL_NOTIMPLEMENTED) || defined(BMPPOOLREADCONTENTS_NOTIMPLEMENTED)
	#define USE_BmpPoolReadContents
	#define EXT_BmpPoolReadContents
	#define GET_BmpPoolReadContents(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BmpPoolReadContents(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BmpPoolReadContents  FALSE
	#define EXP_BmpPoolReadContents  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BmpPoolReadContents
	#define EXT_BmpPoolReadContents
	#define GET_BmpPoolReadContents(fl)  CAL_CMGETAPI( "BmpPoolReadContents" ) 
	#define CAL_BmpPoolReadContents  BmpPoolReadContents
	#define CHK_BmpPoolReadContents  TRUE
	#define EXP_BmpPoolReadContents  CAL_CMEXPAPI( "BmpPoolReadContents" ) 
#elif defined(MIXED_LINK) && !defined(CMPBITMAPPOOL_EXTERNAL)
	#define USE_BmpPoolReadContents
	#define EXT_BmpPoolReadContents
	#define GET_BmpPoolReadContents(fl)  CAL_CMGETAPI( "BmpPoolReadContents" ) 
	#define CAL_BmpPoolReadContents  BmpPoolReadContents
	#define CHK_BmpPoolReadContents  TRUE
	#define EXP_BmpPoolReadContents  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolReadContents", (RTS_UINTPTR)BmpPoolReadContents, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBitmapPoolBmpPoolReadContents
	#define EXT_CmpBitmapPoolBmpPoolReadContents
	#define GET_CmpBitmapPoolBmpPoolReadContents  ERR_OK
	#define CAL_CmpBitmapPoolBmpPoolReadContents  BmpPoolReadContents
	#define CHK_CmpBitmapPoolBmpPoolReadContents  TRUE
	#define EXP_CmpBitmapPoolBmpPoolReadContents  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BmpPoolReadContents
	#define EXT_BmpPoolReadContents
	#define GET_BmpPoolReadContents(fl)  CAL_CMGETAPI( "BmpPoolReadContents" ) 
	#define CAL_BmpPoolReadContents  BmpPoolReadContents
	#define CHK_BmpPoolReadContents  TRUE
	#define EXP_BmpPoolReadContents  CAL_CMEXPAPI( "BmpPoolReadContents" ) 
#else /* DYNAMIC_LINK */
	#define USE_BmpPoolReadContents  PFBMPPOOLREADCONTENTS pfBmpPoolReadContents;
	#define EXT_BmpPoolReadContents  extern PFBMPPOOLREADCONTENTS pfBmpPoolReadContents;
	#define GET_BmpPoolReadContents(fl)  s_pfCMGetAPI2( "BmpPoolReadContents", (RTS_VOID_FCTPTR *)&pfBmpPoolReadContents, (fl), 0, 0)
	#define CAL_BmpPoolReadContents  pfBmpPoolReadContents
	#define CHK_BmpPoolReadContents  (pfBmpPoolReadContents != NULL)
	#define EXP_BmpPoolReadContents   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolReadContents", (RTS_UINTPTR)BmpPoolReadContents, 0, 0) 
#endif


/**
 * <description>Saves the contents of the bitmappool in the configured location.</description>
 * <result>error code</result>
 */
RTS_RESULT CDECL BmpPoolWriteContents(char **ppszFilePath);
typedef RTS_RESULT (CDECL * PFBMPPOOLWRITECONTENTS) (char **ppszFilePath);
#if defined(CMPBITMAPPOOL_NOTIMPLEMENTED) || defined(BMPPOOLWRITECONTENTS_NOTIMPLEMENTED)
	#define USE_BmpPoolWriteContents
	#define EXT_BmpPoolWriteContents
	#define GET_BmpPoolWriteContents(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BmpPoolWriteContents(p0) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BmpPoolWriteContents  FALSE
	#define EXP_BmpPoolWriteContents  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BmpPoolWriteContents
	#define EXT_BmpPoolWriteContents
	#define GET_BmpPoolWriteContents(fl)  CAL_CMGETAPI( "BmpPoolWriteContents" ) 
	#define CAL_BmpPoolWriteContents  BmpPoolWriteContents
	#define CHK_BmpPoolWriteContents  TRUE
	#define EXP_BmpPoolWriteContents  CAL_CMEXPAPI( "BmpPoolWriteContents" ) 
#elif defined(MIXED_LINK) && !defined(CMPBITMAPPOOL_EXTERNAL)
	#define USE_BmpPoolWriteContents
	#define EXT_BmpPoolWriteContents
	#define GET_BmpPoolWriteContents(fl)  CAL_CMGETAPI( "BmpPoolWriteContents" ) 
	#define CAL_BmpPoolWriteContents  BmpPoolWriteContents
	#define CHK_BmpPoolWriteContents  TRUE
	#define EXP_BmpPoolWriteContents  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolWriteContents", (RTS_UINTPTR)BmpPoolWriteContents, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBitmapPoolBmpPoolWriteContents
	#define EXT_CmpBitmapPoolBmpPoolWriteContents
	#define GET_CmpBitmapPoolBmpPoolWriteContents  ERR_OK
	#define CAL_CmpBitmapPoolBmpPoolWriteContents  BmpPoolWriteContents
	#define CHK_CmpBitmapPoolBmpPoolWriteContents  TRUE
	#define EXP_CmpBitmapPoolBmpPoolWriteContents  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BmpPoolWriteContents
	#define EXT_BmpPoolWriteContents
	#define GET_BmpPoolWriteContents(fl)  CAL_CMGETAPI( "BmpPoolWriteContents" ) 
	#define CAL_BmpPoolWriteContents  BmpPoolWriteContents
	#define CHK_BmpPoolWriteContents  TRUE
	#define EXP_BmpPoolWriteContents  CAL_CMEXPAPI( "BmpPoolWriteContents" ) 
#else /* DYNAMIC_LINK */
	#define USE_BmpPoolWriteContents  PFBMPPOOLWRITECONTENTS pfBmpPoolWriteContents;
	#define EXT_BmpPoolWriteContents  extern PFBMPPOOLWRITECONTENTS pfBmpPoolWriteContents;
	#define GET_BmpPoolWriteContents(fl)  s_pfCMGetAPI2( "BmpPoolWriteContents", (RTS_VOID_FCTPTR *)&pfBmpPoolWriteContents, (fl), 0, 0)
	#define CAL_BmpPoolWriteContents  pfBmpPoolWriteContents
	#define CHK_BmpPoolWriteContents  (pfBmpPoolWriteContents != NULL)
	#define EXP_BmpPoolWriteContents   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolWriteContents", (RTS_UINTPTR)BmpPoolWriteContents, 0, 0) 
#endif


/**
 * <description>
 *	This callback function can be implemented by components iterating over the content of an imagepool using <see>BmpPoolForeachEntry</see>.
 * </description>
 * <param name="pData" type="IN">The pointer that was passed in the call to BmpPoolForeachEntry</param>
 * <param name="pszId" type="IN">The id of an entry</param>
 * <param name="pszPath" type="IN">The path of an entry</param>
 * <result>
 *	Should return ERR_OK to continue the iteration or an error code to cancel the iteration.
 * </result>
 */
typedef RTS_RESULT (CDECL *PFForeachBmpPoolEntry)(void* pData, char* pszId, char* pszPath);

/**
 * <description>Call this function to iterate over all entries of the imagepool.</description>
 * <param name="pData" type="IN">A pointer to arbitrary data that will be passed to each callback.</param>
 * <param name="pfCallback" type="IN">The callback function that will be called for each entry of the imagepool</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL BmpPoolForeachEntry(void* pData, PFForeachBmpPoolEntry pfCallback);
typedef RTS_RESULT (CDECL * PFBMPPOOLFOREACHENTRY) (void* pData, PFForeachBmpPoolEntry pfCallback);
#if defined(CMPBITMAPPOOL_NOTIMPLEMENTED) || defined(BMPPOOLFOREACHENTRY_NOTIMPLEMENTED)
	#define USE_BmpPoolForeachEntry
	#define EXT_BmpPoolForeachEntry
	#define GET_BmpPoolForeachEntry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BmpPoolForeachEntry(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BmpPoolForeachEntry  FALSE
	#define EXP_BmpPoolForeachEntry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BmpPoolForeachEntry
	#define EXT_BmpPoolForeachEntry
	#define GET_BmpPoolForeachEntry(fl)  CAL_CMGETAPI( "BmpPoolForeachEntry" ) 
	#define CAL_BmpPoolForeachEntry  BmpPoolForeachEntry
	#define CHK_BmpPoolForeachEntry  TRUE
	#define EXP_BmpPoolForeachEntry  CAL_CMEXPAPI( "BmpPoolForeachEntry" ) 
#elif defined(MIXED_LINK) && !defined(CMPBITMAPPOOL_EXTERNAL)
	#define USE_BmpPoolForeachEntry
	#define EXT_BmpPoolForeachEntry
	#define GET_BmpPoolForeachEntry(fl)  CAL_CMGETAPI( "BmpPoolForeachEntry" ) 
	#define CAL_BmpPoolForeachEntry  BmpPoolForeachEntry
	#define CHK_BmpPoolForeachEntry  TRUE
	#define EXP_BmpPoolForeachEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolForeachEntry", (RTS_UINTPTR)BmpPoolForeachEntry, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBitmapPoolBmpPoolForeachEntry
	#define EXT_CmpBitmapPoolBmpPoolForeachEntry
	#define GET_CmpBitmapPoolBmpPoolForeachEntry  ERR_OK
	#define CAL_CmpBitmapPoolBmpPoolForeachEntry  BmpPoolForeachEntry
	#define CHK_CmpBitmapPoolBmpPoolForeachEntry  TRUE
	#define EXP_CmpBitmapPoolBmpPoolForeachEntry  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BmpPoolForeachEntry
	#define EXT_BmpPoolForeachEntry
	#define GET_BmpPoolForeachEntry(fl)  CAL_CMGETAPI( "BmpPoolForeachEntry" ) 
	#define CAL_BmpPoolForeachEntry  BmpPoolForeachEntry
	#define CHK_BmpPoolForeachEntry  TRUE
	#define EXP_BmpPoolForeachEntry  CAL_CMEXPAPI( "BmpPoolForeachEntry" ) 
#else /* DYNAMIC_LINK */
	#define USE_BmpPoolForeachEntry  PFBMPPOOLFOREACHENTRY pfBmpPoolForeachEntry;
	#define EXT_BmpPoolForeachEntry  extern PFBMPPOOLFOREACHENTRY pfBmpPoolForeachEntry;
	#define GET_BmpPoolForeachEntry(fl)  s_pfCMGetAPI2( "BmpPoolForeachEntry", (RTS_VOID_FCTPTR *)&pfBmpPoolForeachEntry, (fl), 0, 0)
	#define CAL_BmpPoolForeachEntry  pfBmpPoolForeachEntry
	#define CHK_BmpPoolForeachEntry  (pfBmpPoolForeachEntry != NULL)
	#define EXP_BmpPoolForeachEntry   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BmpPoolForeachEntry", (RTS_UINTPTR)BmpPoolForeachEntry, 0, 0) 
#endif


#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFBMPPOOLREGISTER IBmpPoolRegister;
 	PFBMPPOOLUNREGISTER IBmpPoolUnregister;
 } ICmpBitmapPool_C;

#ifdef CPLUSPLUS
class ICmpBitmapPool : public IBase
{
	public:
		virtual RTS_RESULT CDECL IBmpPoolRegister(const char *pszBmpId, const char *pszPath) =0;
		virtual RTS_RESULT CDECL IBmpPoolUnregister(const char *pszBmpId) =0;
};
	#ifndef ITF_CmpBitmapPool
		#define ITF_CmpBitmapPool static ICmpBitmapPool *pICmpBitmapPool = NULL;
	#endif
	#define EXTITF_CmpBitmapPool
#else	/*CPLUSPLUS*/
	typedef ICmpBitmapPool_C		ICmpBitmapPool;
	#ifndef ITF_CmpBitmapPool
		#define ITF_CmpBitmapPool
	#endif
	#define EXTITF_CmpBitmapPool
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPBITMAPPOOLITF_H_*/
