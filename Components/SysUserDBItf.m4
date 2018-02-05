/**
 * <interfacename>SysUserDB</interfacename>
 * <description> 
 *	System specific part of the interface for the user management database. In the current implementation only 2 functions concerning the password are supported.
 *  
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions GmbH</copyright>
 */

SET_INTERFACE_NAME(`SysUserDB')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysUserDBSetPasswordMD5', `(char *pszUser, unsigned char *pbyPasswordMD5, int *piMaxLen)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysUserDBGetPasswordMD5', `(char *pszUser, unsigned char *pbyPasswordMD5, int *piMaxLen)')

#ifdef __cplusplus
}
#endif
