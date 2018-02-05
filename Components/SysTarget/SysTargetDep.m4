/**
 * <name>SysTarget</name>
 * <description> 
 *	Target specific functions
 * </description>
 *
 * <copyright>(c) 2003-2018 3S-Smart Software Solutions</copyright>
 */
SET_COMPONENT_NAME(`SysTarget')
COMPONENT_SOURCES(`SysTarget.c')
COMPONENT_SYSSOURCES(`SysTarget*.c')

COMPONENT_VERSION(`0x03050C01')
COMPONENT_VENDORID(`RTS_VENDORID_3S')

CATEGORY(`System')

USE_ITF(`CMItf.m4')
USE_ITF(`CMUtilsItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`SysMemItf.m4')
USE_ITF(`SysTargetItf.m4')
USE_ITF(`SysCpuHandlingItf.m4')
USE_ITF(`CmpSIL2Itf.m4')
USE_ITF(`CmpChecksumItf.m4')
USE_ITF(`CmpEventMgrItf.m4')

IMPLEMENT_ITF(`SysTargetItf.m4')

OPTIONAL_IMPORTS(
SIL2CheckCallerContext,
CRC32Init,
CRC32Update,
CRC32Finish,
EventCreate3,
EventDelete,
EventPost2)

REQUIRED_IMPORTS(
CMUtlSafeStrCpy,
CMUtlsnprintf,
CMUtlSafeStrCat,
CMUtlwstrcpy,
CMUtlwstrcat,
CMUtlwstrlen,
CMUtlStrToW,
CMCheckSysTargetSignature,
SettgGetWStringValue,
SettgGetStringValue,
SettgGetIntValue,
SettgSetWStringValue,
SettgRemoveKey,
SysMemSwap,
SysTargetGetConfiguredNodeName,
SysTargetGetType,
SysTargetGetId,
SysTargetGetVersion)
