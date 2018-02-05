 /**
 * <interfacename>SysUserDB</interfacename>
 * <description> 
 *	System specific part of the interface for the user management database. In the current implementation only 2 functions concerning the password are supported.
 *  
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions GmbH</copyright>
 */


	
	
#ifndef _SYSUSERDBITF_H_
#define _SYSUSERDBITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysUserDBOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysUserDBOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Set or overwrite the password credential of the user</description>
 * <param name="pszUser" type="IN">User name</param>
 * <param name="pbyPasswordMD5" type="IN">Pointer to MD5 hash of the password</param>
 * <param name="piMaxLen" type="INOUT">Pointer to password MD5 hash length. If it is too short, needed length is returned if error code is ERR_BUFFERSIZE</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or piMaxLen = NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">If password is too short. Needed length is returned in *piMaxLen </errorcode>
 */
RTS_RESULT CDECL SysUserDBSetPasswordMD5(char *pszUser, unsigned char *pbyPasswordMD5, int *piMaxLen);
typedef RTS_RESULT (CDECL * PFSYSUSERDBSETPASSWORDMD5) (char *pszUser, unsigned char *pbyPasswordMD5, int *piMaxLen);
#if defined(SYSUSERDB_NOTIMPLEMENTED) || defined(SYSUSERDBSETPASSWORDMD5_NOTIMPLEMENTED)
	#define USE_SysUserDBSetPasswordMD5
	#define EXT_SysUserDBSetPasswordMD5
	#define GET_SysUserDBSetPasswordMD5(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysUserDBSetPasswordMD5(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysUserDBSetPasswordMD5  FALSE
	#define EXP_SysUserDBSetPasswordMD5  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysUserDBSetPasswordMD5
	#define EXT_SysUserDBSetPasswordMD5
	#define GET_SysUserDBSetPasswordMD5(fl)  CAL_CMGETAPI( "SysUserDBSetPasswordMD5" ) 
	#define CAL_SysUserDBSetPasswordMD5  SysUserDBSetPasswordMD5
	#define CHK_SysUserDBSetPasswordMD5  TRUE
	#define EXP_SysUserDBSetPasswordMD5  CAL_CMEXPAPI( "SysUserDBSetPasswordMD5" ) 
#elif defined(MIXED_LINK) && !defined(SYSUSERDB_EXTERNAL)
	#define USE_SysUserDBSetPasswordMD5
	#define EXT_SysUserDBSetPasswordMD5
	#define GET_SysUserDBSetPasswordMD5(fl)  CAL_CMGETAPI( "SysUserDBSetPasswordMD5" ) 
	#define CAL_SysUserDBSetPasswordMD5  SysUserDBSetPasswordMD5
	#define CHK_SysUserDBSetPasswordMD5  TRUE
	#define EXP_SysUserDBSetPasswordMD5  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysUserDBSetPasswordMD5", (RTS_UINTPTR)SysUserDBSetPasswordMD5, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysUserDBSysUserDBSetPasswordMD5
	#define EXT_SysUserDBSysUserDBSetPasswordMD5
	#define GET_SysUserDBSysUserDBSetPasswordMD5  ERR_OK
	#define CAL_SysUserDBSysUserDBSetPasswordMD5 pISysUserDB->ISysUserDBSetPasswordMD5
	#define CHK_SysUserDBSysUserDBSetPasswordMD5 (pISysUserDB != NULL)
	#define EXP_SysUserDBSysUserDBSetPasswordMD5  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysUserDBSetPasswordMD5
	#define EXT_SysUserDBSetPasswordMD5
	#define GET_SysUserDBSetPasswordMD5(fl)  CAL_CMGETAPI( "SysUserDBSetPasswordMD5" ) 
	#define CAL_SysUserDBSetPasswordMD5 pISysUserDB->ISysUserDBSetPasswordMD5
	#define CHK_SysUserDBSetPasswordMD5 (pISysUserDB != NULL)
	#define EXP_SysUserDBSetPasswordMD5  CAL_CMEXPAPI( "SysUserDBSetPasswordMD5" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysUserDBSetPasswordMD5  PFSYSUSERDBSETPASSWORDMD5 pfSysUserDBSetPasswordMD5;
	#define EXT_SysUserDBSetPasswordMD5  extern PFSYSUSERDBSETPASSWORDMD5 pfSysUserDBSetPasswordMD5;
	#define GET_SysUserDBSetPasswordMD5(fl)  s_pfCMGetAPI2( "SysUserDBSetPasswordMD5", (RTS_VOID_FCTPTR *)&pfSysUserDBSetPasswordMD5, (fl), 0, 0)
	#define CAL_SysUserDBSetPasswordMD5  pfSysUserDBSetPasswordMD5
	#define CHK_SysUserDBSetPasswordMD5  (pfSysUserDBSetPasswordMD5 != NULL)
	#define EXP_SysUserDBSetPasswordMD5  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysUserDBSetPasswordMD5", (RTS_UINTPTR)SysUserDBSetPasswordMD5, 0, 0) 
#endif




/**
 * <description>Get the password credential of the user</description>
 * <param name="pszUser" type="IN">User name</param>
 * <param name="pbyPasswordMD5" type="IN">Pointer to MD5 hash of the password</param>
 * <param name="piMaxLen" type="INOUT">Pointer to password MD5 hash length. If it is too short, needed length is returned if error code is ERR_BUFFERSIZE</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or piMaxLen = NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">If password buffer is too short. Needed length is returned in *piMaxLen </errorcode>
 */
RTS_RESULT CDECL SysUserDBGetPasswordMD5(char *pszUser, unsigned char *pbyPasswordMD5, int *piMaxLen);
typedef RTS_RESULT (CDECL * PFSYSUSERDBGETPASSWORDMD5) (char *pszUser, unsigned char *pbyPasswordMD5, int *piMaxLen);
#if defined(SYSUSERDB_NOTIMPLEMENTED) || defined(SYSUSERDBGETPASSWORDMD5_NOTIMPLEMENTED)
	#define USE_SysUserDBGetPasswordMD5
	#define EXT_SysUserDBGetPasswordMD5
	#define GET_SysUserDBGetPasswordMD5(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysUserDBGetPasswordMD5(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysUserDBGetPasswordMD5  FALSE
	#define EXP_SysUserDBGetPasswordMD5  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysUserDBGetPasswordMD5
	#define EXT_SysUserDBGetPasswordMD5
	#define GET_SysUserDBGetPasswordMD5(fl)  CAL_CMGETAPI( "SysUserDBGetPasswordMD5" ) 
	#define CAL_SysUserDBGetPasswordMD5  SysUserDBGetPasswordMD5
	#define CHK_SysUserDBGetPasswordMD5  TRUE
	#define EXP_SysUserDBGetPasswordMD5  CAL_CMEXPAPI( "SysUserDBGetPasswordMD5" ) 
#elif defined(MIXED_LINK) && !defined(SYSUSERDB_EXTERNAL)
	#define USE_SysUserDBGetPasswordMD5
	#define EXT_SysUserDBGetPasswordMD5
	#define GET_SysUserDBGetPasswordMD5(fl)  CAL_CMGETAPI( "SysUserDBGetPasswordMD5" ) 
	#define CAL_SysUserDBGetPasswordMD5  SysUserDBGetPasswordMD5
	#define CHK_SysUserDBGetPasswordMD5  TRUE
	#define EXP_SysUserDBGetPasswordMD5  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysUserDBGetPasswordMD5", (RTS_UINTPTR)SysUserDBGetPasswordMD5, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysUserDBSysUserDBGetPasswordMD5
	#define EXT_SysUserDBSysUserDBGetPasswordMD5
	#define GET_SysUserDBSysUserDBGetPasswordMD5  ERR_OK
	#define CAL_SysUserDBSysUserDBGetPasswordMD5 pISysUserDB->ISysUserDBGetPasswordMD5
	#define CHK_SysUserDBSysUserDBGetPasswordMD5 (pISysUserDB != NULL)
	#define EXP_SysUserDBSysUserDBGetPasswordMD5  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysUserDBGetPasswordMD5
	#define EXT_SysUserDBGetPasswordMD5
	#define GET_SysUserDBGetPasswordMD5(fl)  CAL_CMGETAPI( "SysUserDBGetPasswordMD5" ) 
	#define CAL_SysUserDBGetPasswordMD5 pISysUserDB->ISysUserDBGetPasswordMD5
	#define CHK_SysUserDBGetPasswordMD5 (pISysUserDB != NULL)
	#define EXP_SysUserDBGetPasswordMD5  CAL_CMEXPAPI( "SysUserDBGetPasswordMD5" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysUserDBGetPasswordMD5  PFSYSUSERDBGETPASSWORDMD5 pfSysUserDBGetPasswordMD5;
	#define EXT_SysUserDBGetPasswordMD5  extern PFSYSUSERDBGETPASSWORDMD5 pfSysUserDBGetPasswordMD5;
	#define GET_SysUserDBGetPasswordMD5(fl)  s_pfCMGetAPI2( "SysUserDBGetPasswordMD5", (RTS_VOID_FCTPTR *)&pfSysUserDBGetPasswordMD5, (fl), 0, 0)
	#define CAL_SysUserDBGetPasswordMD5  pfSysUserDBGetPasswordMD5
	#define CHK_SysUserDBGetPasswordMD5  (pfSysUserDBGetPasswordMD5 != NULL)
	#define EXP_SysUserDBGetPasswordMD5  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysUserDBGetPasswordMD5", (RTS_UINTPTR)SysUserDBGetPasswordMD5, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSUSERDBSETPASSWORDMD5 ISysUserDBSetPasswordMD5;
 	PFSYSUSERDBGETPASSWORDMD5 ISysUserDBGetPasswordMD5;
 } ISysUserDB_C;

#ifdef CPLUSPLUS
class ISysUserDB : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISysUserDBSetPasswordMD5(char *pszUser, unsigned char *pbyPasswordMD5, int *piMaxLen) =0;
		virtual RTS_RESULT CDECL ISysUserDBGetPasswordMD5(char *pszUser, unsigned char *pbyPasswordMD5, int *piMaxLen) =0;
};
	#ifndef ITF_SysUserDB
		#define ITF_SysUserDB static ISysUserDB *pISysUserDB = NULL;
	#endif
	#define EXTITF_SysUserDB
#else	/*CPLUSPLUS*/
	typedef ISysUserDB_C		ISysUserDB;
	#ifndef ITF_SysUserDB
		#define ITF_SysUserDB
	#endif
	#define EXTITF_SysUserDB
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSUSERDBITF_H_*/
