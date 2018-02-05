 /**
 * <interfacename>CmpSecurityManager</interfacename>
 * <description>
 *	The security manager interface is used to specify the level of all available security features in one central component.
 *	Additionally the X.509 certificates for servers in the runtime system can be specified here.
 *
 *	The actual available security features (for which the level can be specified) are:
 *		1. Programming system communication: encrypted / unencrypted
 *		2. IEC application code and bootproject: signed / unsigned, encrypted / unencrypted 
 *		3. WebServer: http / https
 *
 *	NOTE:
 *		This list will be extended in the future, if new security features are available and the corresponding security level must be specified!
 *
 *  SECURITY-NOTE:
 *		The security manager must be linked statically to the runtime system core to prevent, that it cannot be removed or replaced by a malware!
 *
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPSECURITYMANAGERITF_H_
#define _CMPSECURITYMANAGERITF_H_

#include "CmpStd.h"

 

 




#include "CmpStd.h"
#include "CmpX509CertItf.h"

#ifdef CMPSECURITYMANAGER_EXTERNAL
	#error CmpSecurityManager must not be overloadable so defining CMPSECURITYMANAGER_EXTERNAL is forbidden because of security requirements!
#endif

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="CMPSECURITYMANAGER_SET_SECURITY_LEVEL_MAXIMUM">Set security level to maximum for all available security features!</element>
 */

 /**
 * <category>Static defines</category>
 * <description>Number of static security settings to store</description>
 */
#ifndef RTS_SECMAN_NUMOF_STATIC_SETTINGS
	#define RTS_SECMAN_NUMOF_STATIC_SETTINGS			10
#endif

/**
 * <category>Application flags</category>
 * <description>
 *	Flags to specify properties of an application
 * </description>
 */
#define CMPSECMAN_FLAGS_NONE		        0
#define CMPSECMAN_FLAGS_DEFAULT		        0x00000001

#define CMPSECMAN_FLAGS_SELECTABLESETTING	0x00000002
#define CMPSECMAN_FLAGS_EDITABLESETTING		0x00000004

#define CMPSECMAN_FLAGS_STRINGSETTING		0x00000010
#define CMPSECMAN_FLAGS_INTSETTING		    0x00000020
 
/**
 * <description>
 *	This structure stores a single selection of a selectable settings. Each 
 *  possible selection is a single struture element when registering the setting.
 *  The registration can be done using SecManRegisterSettings function. The 
 *  selected setting can be retrieved by using SecManGetSetting.
 * </description>
 * <element name="secID" type="IN">ID of the security setting. Must be unique per ComponentID and UsageID</element>
 * <element name="flags" type="IN">Flags of the entry. See "SecuritySettingFlags" for details.</element>
 * <element name="pszSecName" type="IN">Name of the security setting</element>
 * <element name="pszDescription" type="IN">Description of the security setting</element>
 */
typedef struct _SecuritySetting
{
	RTS_I32 secID;
	RTS_UI32 flags;
	char *pszSecName;
	char *pszDescription;
} SecuritySetting;


typedef union _SecuritySettingValue
{
    RTS_I32 intSetting;
    char *stringSetting;
} SecuritySettingValue;

/**
 * <description>
 *	This structure stores a editable setting. The setting can be registerd using
 *  SecManRegisterEditableSetting function. The default value given when registring
 *  will be returned until the setting has been changed by the someone. Then the
 *  changed value will be returned. To indicate if a string or an intager is stored
 *  use either CMPSECMAN_FLAGS_STRINGSETTING or CMPSECMAN_FLAGS_INTSETTING. The
 *  corresponding field in the secValue union is then used.
 *  Use the function SecManGetSettingValue to retrieve the valued stored.
 * </description>
 * <element name="secID" type="IN">ID of the security setting. Must be unique per ComponentID and UsageID</element>
 * <element name="flags" type="IN">Flags of the entry. See "SecuritySettingFlags" for details.</element>
 * <element name="pszSecName" type="IN">Name of the security setting</element>
 * <element name="pszDescription" type="IN">Description of the security setting</element>
 */
typedef struct _SecurityEditableSetting
{
	RTS_UI32 flags;
	char *pszSecName;
	char *pszDescription;
	SecuritySettingValue secValue;
} SecurityEditableSetting;


/**
 * <description>SecurityID</description>
 * <element name="CREATE_SELFSIGNED_CERT" type="IN">Create a selfsigned cert</element>
 * <element name="DONT_CREATE_SELFSIGNED_CERT" type="IN">Don't create a selfsigned cert</element>
 */
typedef enum RTS_SECURITYSETTINGS_SELFSIGNED_CERT
{
	CREATE_SELFSIGNED_CERT,
	DONT_CREATE_SELFSIGNED_CERT
} RTS_SECURITYSETTINGS_SELFSIGNED_CERT;

/**
 * <category>SecuritySettings</category>
 * <description>Security settings to specify, if a selfsigned cert should be created by default if not available</description>
 * <element name="CREATE_SELFSIGNED_CERT" type="IN">Create a selfsigned cert</element>
 * <element name="DONT_CREATE_SELFSIGNED_CERT" type="IN">Don't create a selfsigned cert</element>
 */
#define RTS_SECURITY_SETTINGS_SELFSIGNED_CERT	{ \
													{(RTS_I32)CREATE_SELFSIGNED_CERT, CMPSECMAN_FLAGS_DEFAULT, "CreateSelfSignedCert", "Create a selfsigned cert"},\
													{(RTS_I32)DONT_CREATE_SELFSIGNED_CERT, 0, "DontCreateSelfSignedCert", "Don't create a selfsigned cert"}\
												}

#define RTS_SECURITY_ID_SELFSIGNEDCERT			0x01FFFFFF


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	With this setting you can configure, if all certificates and parameter should be created automatically during startup:
 *	- Create all needed selfsigned server certificates during startup, if the corresponding certificate is not available or outdated
 *  - Create DiffieHellman parameters during startup. This could take some minutes up to several hours and could consume a lot of processor load!
 * </description>
 */
#define SECURITYMANAGERKEY_INT_CREATE_ALL_ON_STARTUP					"CreateAllOnStartup"
#ifndef SECURITYMANAGERVALUE_INT_CREATE_ALL_ON_STARTUP_DEFAULT
	#define SECURITYMANAGERVALUE_INT_CREATE_ALL_ON_STARTUP_DEFAULT		0
#endif


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Function to manage all security settings of a component</description>
 * <param name="cmpId" type="IN">ComponentID of the server that provides security features</settings</param>
 * <param name="nUsageID" type="IN">UsageID. This must only be unique for one component</param>
 * <param name="pSettings" type="IN">Pointer to the security settings</param>
 * <param name="nSettings" type="IN">Number of security settings</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Settings could be registered</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">CmpSecurityManager is not yet initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_MEMORY">No memory to register security settings</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_DUPLICATE">The setting was registered already. The handle of the existing is returned.</errorcode>
 * <result>Handle to the registered security settings</result>
 */
RTS_HANDLE CDECL SecManRegisterSettings(CMPID cmpId, RTS_UI32 ui32UsageID, SecuritySetting *pSettings, RTS_UI32 ui32Settings, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSECMANREGISTERSETTINGS) (CMPID cmpId, RTS_UI32 ui32UsageID, SecuritySetting *pSettings, RTS_UI32 ui32Settings, RTS_RESULT *pResult);
#if defined(CMPSECURITYMANAGER_NOTIMPLEMENTED) || defined(SECMANREGISTERSETTINGS_NOTIMPLEMENTED)
	#define USE_SecManRegisterSettings
	#define EXT_SecManRegisterSettings
	#define GET_SecManRegisterSettings(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecManRegisterSettings(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SecManRegisterSettings  FALSE
	#define EXP_SecManRegisterSettings  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecManRegisterSettings
	#define EXT_SecManRegisterSettings
	#define GET_SecManRegisterSettings(fl)  CAL_CMGETAPI( "SecManRegisterSettings" ) 
	#define CAL_SecManRegisterSettings  SecManRegisterSettings
	#define CHK_SecManRegisterSettings  TRUE
	#define EXP_SecManRegisterSettings  CAL_CMEXPAPI( "SecManRegisterSettings" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURITYMANAGER_EXTERNAL)
	#define USE_SecManRegisterSettings
	#define EXT_SecManRegisterSettings
	#define GET_SecManRegisterSettings(fl)  CAL_CMGETAPI( "SecManRegisterSettings" ) 
	#define CAL_SecManRegisterSettings  SecManRegisterSettings
	#define CHK_SecManRegisterSettings  TRUE
	#define EXP_SecManRegisterSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManRegisterSettings", (RTS_UINTPTR)SecManRegisterSettings, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecurityManagerSecManRegisterSettings
	#define EXT_CmpSecurityManagerSecManRegisterSettings
	#define GET_CmpSecurityManagerSecManRegisterSettings  ERR_OK
	#define CAL_CmpSecurityManagerSecManRegisterSettings pICmpSecurityManager->ISecManRegisterSettings
	#define CHK_CmpSecurityManagerSecManRegisterSettings (pICmpSecurityManager != NULL)
	#define EXP_CmpSecurityManagerSecManRegisterSettings  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecManRegisterSettings
	#define EXT_SecManRegisterSettings
	#define GET_SecManRegisterSettings(fl)  CAL_CMGETAPI( "SecManRegisterSettings" ) 
	#define CAL_SecManRegisterSettings pICmpSecurityManager->ISecManRegisterSettings
	#define CHK_SecManRegisterSettings (pICmpSecurityManager != NULL)
	#define EXP_SecManRegisterSettings  CAL_CMEXPAPI( "SecManRegisterSettings" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecManRegisterSettings  PFSECMANREGISTERSETTINGS pfSecManRegisterSettings;
	#define EXT_SecManRegisterSettings  extern PFSECMANREGISTERSETTINGS pfSecManRegisterSettings;
	#define GET_SecManRegisterSettings(fl)  s_pfCMGetAPI2( "SecManRegisterSettings", (RTS_VOID_FCTPTR *)&pfSecManRegisterSettings, (fl), 0, 0)
	#define CAL_SecManRegisterSettings  pfSecManRegisterSettings
	#define CHK_SecManRegisterSettings  (pfSecManRegisterSettings != NULL)
	#define EXP_SecManRegisterSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManRegisterSettings", (RTS_UINTPTR)SecManRegisterSettings, 0, 0) 
#endif




/**
 * <description>Function to register a editable security setting of a component</description>
 * <param name="cmpId" type="IN">ComponentID of the server that provides security features</settings</param>
 * <param name="nUsageID" type="IN">UsageID. This must only be unique for one component</param>
 * <param name="pSetting" type="IN">Pointer to the editable security settings</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Settings could be registered</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">CmpSecurityManager is not yet initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_MEMORY">No memory to register security settings</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_DUPLICATE">The setting was registered already. The handle of the existing is returned.</errorcode>
 * <result>Handle to the registered security settings</result>
 */
RTS_HANDLE CDECL SecManRegisterEditableSetting(CMPID cmpId, RTS_UI32 ui32UsageID, SecurityEditableSetting *pSetting, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSECMANREGISTEREDITABLESETTING) (CMPID cmpId, RTS_UI32 ui32UsageID, SecurityEditableSetting *pSetting, RTS_RESULT *pResult);
#if defined(CMPSECURITYMANAGER_NOTIMPLEMENTED) || defined(SECMANREGISTEREDITABLESETTING_NOTIMPLEMENTED)
	#define USE_SecManRegisterEditableSetting
	#define EXT_SecManRegisterEditableSetting
	#define GET_SecManRegisterEditableSetting(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecManRegisterEditableSetting(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SecManRegisterEditableSetting  FALSE
	#define EXP_SecManRegisterEditableSetting  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecManRegisterEditableSetting
	#define EXT_SecManRegisterEditableSetting
	#define GET_SecManRegisterEditableSetting(fl)  CAL_CMGETAPI( "SecManRegisterEditableSetting" ) 
	#define CAL_SecManRegisterEditableSetting  SecManRegisterEditableSetting
	#define CHK_SecManRegisterEditableSetting  TRUE
	#define EXP_SecManRegisterEditableSetting  CAL_CMEXPAPI( "SecManRegisterEditableSetting" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURITYMANAGER_EXTERNAL)
	#define USE_SecManRegisterEditableSetting
	#define EXT_SecManRegisterEditableSetting
	#define GET_SecManRegisterEditableSetting(fl)  CAL_CMGETAPI( "SecManRegisterEditableSetting" ) 
	#define CAL_SecManRegisterEditableSetting  SecManRegisterEditableSetting
	#define CHK_SecManRegisterEditableSetting  TRUE
	#define EXP_SecManRegisterEditableSetting  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManRegisterEditableSetting", (RTS_UINTPTR)SecManRegisterEditableSetting, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecurityManagerSecManRegisterEditableSetting
	#define EXT_CmpSecurityManagerSecManRegisterEditableSetting
	#define GET_CmpSecurityManagerSecManRegisterEditableSetting  ERR_OK
	#define CAL_CmpSecurityManagerSecManRegisterEditableSetting pICmpSecurityManager->ISecManRegisterEditableSetting
	#define CHK_CmpSecurityManagerSecManRegisterEditableSetting (pICmpSecurityManager != NULL)
	#define EXP_CmpSecurityManagerSecManRegisterEditableSetting  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecManRegisterEditableSetting
	#define EXT_SecManRegisterEditableSetting
	#define GET_SecManRegisterEditableSetting(fl)  CAL_CMGETAPI( "SecManRegisterEditableSetting" ) 
	#define CAL_SecManRegisterEditableSetting pICmpSecurityManager->ISecManRegisterEditableSetting
	#define CHK_SecManRegisterEditableSetting (pICmpSecurityManager != NULL)
	#define EXP_SecManRegisterEditableSetting  CAL_CMEXPAPI( "SecManRegisterEditableSetting" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecManRegisterEditableSetting  PFSECMANREGISTEREDITABLESETTING pfSecManRegisterEditableSetting;
	#define EXT_SecManRegisterEditableSetting  extern PFSECMANREGISTEREDITABLESETTING pfSecManRegisterEditableSetting;
	#define GET_SecManRegisterEditableSetting(fl)  s_pfCMGetAPI2( "SecManRegisterEditableSetting", (RTS_VOID_FCTPTR *)&pfSecManRegisterEditableSetting, (fl), 0, 0)
	#define CAL_SecManRegisterEditableSetting  pfSecManRegisterEditableSetting
	#define CHK_SecManRegisterEditableSetting  (pfSecManRegisterEditableSetting != NULL)
	#define EXP_SecManRegisterEditableSetting  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManRegisterEditableSetting", (RTS_UINTPTR)SecManRegisterEditableSetting, 0, 0) 
#endif




/**
 * <description>Unregister security settings</description>
 * <param name="hSecuritySettings" type="IN">Handle to the security settings returned by SecManRegisterSettings() or SecManFindSettings() or SecManRegisterEditableSetting()</param>
 * <result>Result of the operation</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Unregister succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hSecuritySettings invalid</errorcode>
 */
RTS_RESULT CDECL SecManUnregisterSettings(RTS_HANDLE hSecuritySettings);
typedef RTS_RESULT (CDECL * PFSECMANUNREGISTERSETTINGS) (RTS_HANDLE hSecuritySettings);
#if defined(CMPSECURITYMANAGER_NOTIMPLEMENTED) || defined(SECMANUNREGISTERSETTINGS_NOTIMPLEMENTED)
	#define USE_SecManUnregisterSettings
	#define EXT_SecManUnregisterSettings
	#define GET_SecManUnregisterSettings(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecManUnregisterSettings(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SecManUnregisterSettings  FALSE
	#define EXP_SecManUnregisterSettings  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecManUnregisterSettings
	#define EXT_SecManUnregisterSettings
	#define GET_SecManUnregisterSettings(fl)  CAL_CMGETAPI( "SecManUnregisterSettings" ) 
	#define CAL_SecManUnregisterSettings  SecManUnregisterSettings
	#define CHK_SecManUnregisterSettings  TRUE
	#define EXP_SecManUnregisterSettings  CAL_CMEXPAPI( "SecManUnregisterSettings" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURITYMANAGER_EXTERNAL)
	#define USE_SecManUnregisterSettings
	#define EXT_SecManUnregisterSettings
	#define GET_SecManUnregisterSettings(fl)  CAL_CMGETAPI( "SecManUnregisterSettings" ) 
	#define CAL_SecManUnregisterSettings  SecManUnregisterSettings
	#define CHK_SecManUnregisterSettings  TRUE
	#define EXP_SecManUnregisterSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManUnregisterSettings", (RTS_UINTPTR)SecManUnregisterSettings, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecurityManagerSecManUnregisterSettings
	#define EXT_CmpSecurityManagerSecManUnregisterSettings
	#define GET_CmpSecurityManagerSecManUnregisterSettings  ERR_OK
	#define CAL_CmpSecurityManagerSecManUnregisterSettings pICmpSecurityManager->ISecManUnregisterSettings
	#define CHK_CmpSecurityManagerSecManUnregisterSettings (pICmpSecurityManager != NULL)
	#define EXP_CmpSecurityManagerSecManUnregisterSettings  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecManUnregisterSettings
	#define EXT_SecManUnregisterSettings
	#define GET_SecManUnregisterSettings(fl)  CAL_CMGETAPI( "SecManUnregisterSettings" ) 
	#define CAL_SecManUnregisterSettings pICmpSecurityManager->ISecManUnregisterSettings
	#define CHK_SecManUnregisterSettings (pICmpSecurityManager != NULL)
	#define EXP_SecManUnregisterSettings  CAL_CMEXPAPI( "SecManUnregisterSettings" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecManUnregisterSettings  PFSECMANUNREGISTERSETTINGS pfSecManUnregisterSettings;
	#define EXT_SecManUnregisterSettings  extern PFSECMANUNREGISTERSETTINGS pfSecManUnregisterSettings;
	#define GET_SecManUnregisterSettings(fl)  s_pfCMGetAPI2( "SecManUnregisterSettings", (RTS_VOID_FCTPTR *)&pfSecManUnregisterSettings, (fl), 0, 0)
	#define CAL_SecManUnregisterSettings  pfSecManUnregisterSettings
	#define CHK_SecManUnregisterSettings  (pfSecManUnregisterSettings != NULL)
	#define EXP_SecManUnregisterSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManUnregisterSettings", (RTS_UINTPTR)SecManUnregisterSettings, 0, 0) 
#endif




/**
 * <description>Find settings specified by componentID and usageID</description>
 * <param name="cmpId" type="IN">ComponentID of the server that provides security features</settings</param>
 * <param name="nUsageID" type="IN">UsageID. This must only be unique for one component</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Settings could be found</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">CmpSecurityManager is not yet initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">No settings registered</errorcode>
 * <result>Handle to the registered security settings</result>
 */
RTS_HANDLE CDECL SecManFindSettings(CMPID cmpId, RTS_UI32 ui32UsageID, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSECMANFINDSETTINGS) (CMPID cmpId, RTS_UI32 ui32UsageID, RTS_RESULT *pResult);
#if defined(CMPSECURITYMANAGER_NOTIMPLEMENTED) || defined(SECMANFINDSETTINGS_NOTIMPLEMENTED)
	#define USE_SecManFindSettings
	#define EXT_SecManFindSettings
	#define GET_SecManFindSettings(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecManFindSettings(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SecManFindSettings  FALSE
	#define EXP_SecManFindSettings  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecManFindSettings
	#define EXT_SecManFindSettings
	#define GET_SecManFindSettings(fl)  CAL_CMGETAPI( "SecManFindSettings" ) 
	#define CAL_SecManFindSettings  SecManFindSettings
	#define CHK_SecManFindSettings  TRUE
	#define EXP_SecManFindSettings  CAL_CMEXPAPI( "SecManFindSettings" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURITYMANAGER_EXTERNAL)
	#define USE_SecManFindSettings
	#define EXT_SecManFindSettings
	#define GET_SecManFindSettings(fl)  CAL_CMGETAPI( "SecManFindSettings" ) 
	#define CAL_SecManFindSettings  SecManFindSettings
	#define CHK_SecManFindSettings  TRUE
	#define EXP_SecManFindSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManFindSettings", (RTS_UINTPTR)SecManFindSettings, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecurityManagerSecManFindSettings
	#define EXT_CmpSecurityManagerSecManFindSettings
	#define GET_CmpSecurityManagerSecManFindSettings  ERR_OK
	#define CAL_CmpSecurityManagerSecManFindSettings pICmpSecurityManager->ISecManFindSettings
	#define CHK_CmpSecurityManagerSecManFindSettings (pICmpSecurityManager != NULL)
	#define EXP_CmpSecurityManagerSecManFindSettings  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecManFindSettings
	#define EXT_SecManFindSettings
	#define GET_SecManFindSettings(fl)  CAL_CMGETAPI( "SecManFindSettings" ) 
	#define CAL_SecManFindSettings pICmpSecurityManager->ISecManFindSettings
	#define CHK_SecManFindSettings (pICmpSecurityManager != NULL)
	#define EXP_SecManFindSettings  CAL_CMEXPAPI( "SecManFindSettings" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecManFindSettings  PFSECMANFINDSETTINGS pfSecManFindSettings;
	#define EXT_SecManFindSettings  extern PFSECMANFINDSETTINGS pfSecManFindSettings;
	#define GET_SecManFindSettings(fl)  s_pfCMGetAPI2( "SecManFindSettings", (RTS_VOID_FCTPTR *)&pfSecManFindSettings, (fl), 0, 0)
	#define CAL_SecManFindSettings  pfSecManFindSettings
	#define CHK_SecManFindSettings  (pfSecManFindSettings != NULL)
	#define EXP_SecManFindSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManFindSettings", (RTS_UINTPTR)SecManFindSettings, 0, 0) 
#endif




/**
 * <description>Get the selected setting because of the security policy of the target!</description>
 * <param name="hSecuritySettings" type="IN">Handle to the security settings returned by SecManRegisterSettings() or SecManFindSettings()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">One setting is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">hSecuritySettings is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">No setting selected</errorcode>
 * <result>Pointer to the security setting which is selected on the target</result>
 */
SecuritySetting * CDECL SecManGetSetting(RTS_HANDLE hSecuritySettings, RTS_RESULT *pResult);
typedef SecuritySetting * (CDECL * PFSECMANGETSETTING) (RTS_HANDLE hSecuritySettings, RTS_RESULT *pResult);
#if defined(CMPSECURITYMANAGER_NOTIMPLEMENTED) || defined(SECMANGETSETTING_NOTIMPLEMENTED)
	#define USE_SecManGetSetting
	#define EXT_SecManGetSetting
	#define GET_SecManGetSetting(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecManGetSetting(p0,p1)  (SecuritySetting *)ERR_NOTIMPLEMENTED
	#define CHK_SecManGetSetting  FALSE
	#define EXP_SecManGetSetting  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecManGetSetting
	#define EXT_SecManGetSetting
	#define GET_SecManGetSetting(fl)  CAL_CMGETAPI( "SecManGetSetting" ) 
	#define CAL_SecManGetSetting  SecManGetSetting
	#define CHK_SecManGetSetting  TRUE
	#define EXP_SecManGetSetting  CAL_CMEXPAPI( "SecManGetSetting" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURITYMANAGER_EXTERNAL)
	#define USE_SecManGetSetting
	#define EXT_SecManGetSetting
	#define GET_SecManGetSetting(fl)  CAL_CMGETAPI( "SecManGetSetting" ) 
	#define CAL_SecManGetSetting  SecManGetSetting
	#define CHK_SecManGetSetting  TRUE
	#define EXP_SecManGetSetting  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManGetSetting", (RTS_UINTPTR)SecManGetSetting, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecurityManagerSecManGetSetting
	#define EXT_CmpSecurityManagerSecManGetSetting
	#define GET_CmpSecurityManagerSecManGetSetting  ERR_OK
	#define CAL_CmpSecurityManagerSecManGetSetting pICmpSecurityManager->ISecManGetSetting
	#define CHK_CmpSecurityManagerSecManGetSetting (pICmpSecurityManager != NULL)
	#define EXP_CmpSecurityManagerSecManGetSetting  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecManGetSetting
	#define EXT_SecManGetSetting
	#define GET_SecManGetSetting(fl)  CAL_CMGETAPI( "SecManGetSetting" ) 
	#define CAL_SecManGetSetting pICmpSecurityManager->ISecManGetSetting
	#define CHK_SecManGetSetting (pICmpSecurityManager != NULL)
	#define EXP_SecManGetSetting  CAL_CMEXPAPI( "SecManGetSetting" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecManGetSetting  PFSECMANGETSETTING pfSecManGetSetting;
	#define EXT_SecManGetSetting  extern PFSECMANGETSETTING pfSecManGetSetting;
	#define GET_SecManGetSetting(fl)  s_pfCMGetAPI2( "SecManGetSetting", (RTS_VOID_FCTPTR *)&pfSecManGetSetting, (fl), 0, 0)
	#define CAL_SecManGetSetting  pfSecManGetSetting
	#define CHK_SecManGetSetting  (pfSecManGetSetting != NULL)
	#define EXP_SecManGetSetting  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManGetSetting", (RTS_UINTPTR)SecManGetSetting, 0, 0) 
#endif




/**
 * <description>Get the edited value setting because of the security policy of the target!</description>
 * <param name="hSecuritySettings" type="IN">Handle to the security settings returned by SecManRegisterSettings() or SecManFindSettings()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">One setting is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">hSecuritySettings is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">No setting selected</errorcode>
 * <result>Pointer to the security setting which is selected on the target</result>
 */
SecurityEditableSetting * CDECL SecManGetEditableSetting(RTS_HANDLE hSecuritySettings, RTS_RESULT *pResult);
typedef SecurityEditableSetting * (CDECL * PFSECMANGETEDITABLESETTING) (RTS_HANDLE hSecuritySettings, RTS_RESULT *pResult);
#if defined(CMPSECURITYMANAGER_NOTIMPLEMENTED) || defined(SECMANGETEDITABLESETTING_NOTIMPLEMENTED)
	#define USE_SecManGetEditableSetting
	#define EXT_SecManGetEditableSetting
	#define GET_SecManGetEditableSetting(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecManGetEditableSetting(p0,p1)  (SecurityEditableSetting *)ERR_NOTIMPLEMENTED
	#define CHK_SecManGetEditableSetting  FALSE
	#define EXP_SecManGetEditableSetting  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecManGetEditableSetting
	#define EXT_SecManGetEditableSetting
	#define GET_SecManGetEditableSetting(fl)  CAL_CMGETAPI( "SecManGetEditableSetting" ) 
	#define CAL_SecManGetEditableSetting  SecManGetEditableSetting
	#define CHK_SecManGetEditableSetting  TRUE
	#define EXP_SecManGetEditableSetting  CAL_CMEXPAPI( "SecManGetEditableSetting" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURITYMANAGER_EXTERNAL)
	#define USE_SecManGetEditableSetting
	#define EXT_SecManGetEditableSetting
	#define GET_SecManGetEditableSetting(fl)  CAL_CMGETAPI( "SecManGetEditableSetting" ) 
	#define CAL_SecManGetEditableSetting  SecManGetEditableSetting
	#define CHK_SecManGetEditableSetting  TRUE
	#define EXP_SecManGetEditableSetting  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManGetEditableSetting", (RTS_UINTPTR)SecManGetEditableSetting, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecurityManagerSecManGetEditableSetting
	#define EXT_CmpSecurityManagerSecManGetEditableSetting
	#define GET_CmpSecurityManagerSecManGetEditableSetting  ERR_OK
	#define CAL_CmpSecurityManagerSecManGetEditableSetting pICmpSecurityManager->ISecManGetEditableSetting
	#define CHK_CmpSecurityManagerSecManGetEditableSetting (pICmpSecurityManager != NULL)
	#define EXP_CmpSecurityManagerSecManGetEditableSetting  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecManGetEditableSetting
	#define EXT_SecManGetEditableSetting
	#define GET_SecManGetEditableSetting(fl)  CAL_CMGETAPI( "SecManGetEditableSetting" ) 
	#define CAL_SecManGetEditableSetting pICmpSecurityManager->ISecManGetEditableSetting
	#define CHK_SecManGetEditableSetting (pICmpSecurityManager != NULL)
	#define EXP_SecManGetEditableSetting  CAL_CMEXPAPI( "SecManGetEditableSetting" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecManGetEditableSetting  PFSECMANGETEDITABLESETTING pfSecManGetEditableSetting;
	#define EXT_SecManGetEditableSetting  extern PFSECMANGETEDITABLESETTING pfSecManGetEditableSetting;
	#define GET_SecManGetEditableSetting(fl)  s_pfCMGetAPI2( "SecManGetEditableSetting", (RTS_VOID_FCTPTR *)&pfSecManGetEditableSetting, (fl), 0, 0)
	#define CAL_SecManGetEditableSetting  pfSecManGetEditableSetting
	#define CHK_SecManGetEditableSetting  (pfSecManGetEditableSetting != NULL)
	#define EXP_SecManGetEditableSetting  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManGetEditableSetting", (RTS_UINTPTR)SecManGetEditableSetting, 0, 0) 
#endif




/**
 * <description>Function to overload the certificate info from a specified server resp. for a usage</description>
 * <param name="cmpId" type="IN">ComponentID of the server that provides security features</settings</param>
 * <param name="pCertInfo" type="IN">Pointer to the preinitialized certificate info</param>
 * <result>Result of the operation</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Certificate info was overloaded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">No overload done</errorcode>
 */
RTS_RESULT CDECL SecManFillCertificateInfo(CMPID cmpId, RtsX509CertInfo *pCertInfo);
typedef RTS_RESULT (CDECL * PFSECMANFILLCERTIFICATEINFO) (CMPID cmpId, RtsX509CertInfo *pCertInfo);
#if defined(CMPSECURITYMANAGER_NOTIMPLEMENTED) || defined(SECMANFILLCERTIFICATEINFO_NOTIMPLEMENTED)
	#define USE_SecManFillCertificateInfo
	#define EXT_SecManFillCertificateInfo
	#define GET_SecManFillCertificateInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecManFillCertificateInfo(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SecManFillCertificateInfo  FALSE
	#define EXP_SecManFillCertificateInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecManFillCertificateInfo
	#define EXT_SecManFillCertificateInfo
	#define GET_SecManFillCertificateInfo(fl)  CAL_CMGETAPI( "SecManFillCertificateInfo" ) 
	#define CAL_SecManFillCertificateInfo  SecManFillCertificateInfo
	#define CHK_SecManFillCertificateInfo  TRUE
	#define EXP_SecManFillCertificateInfo  CAL_CMEXPAPI( "SecManFillCertificateInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURITYMANAGER_EXTERNAL)
	#define USE_SecManFillCertificateInfo
	#define EXT_SecManFillCertificateInfo
	#define GET_SecManFillCertificateInfo(fl)  CAL_CMGETAPI( "SecManFillCertificateInfo" ) 
	#define CAL_SecManFillCertificateInfo  SecManFillCertificateInfo
	#define CHK_SecManFillCertificateInfo  TRUE
	#define EXP_SecManFillCertificateInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManFillCertificateInfo", (RTS_UINTPTR)SecManFillCertificateInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecurityManagerSecManFillCertificateInfo
	#define EXT_CmpSecurityManagerSecManFillCertificateInfo
	#define GET_CmpSecurityManagerSecManFillCertificateInfo  ERR_OK
	#define CAL_CmpSecurityManagerSecManFillCertificateInfo pICmpSecurityManager->ISecManFillCertificateInfo
	#define CHK_CmpSecurityManagerSecManFillCertificateInfo (pICmpSecurityManager != NULL)
	#define EXP_CmpSecurityManagerSecManFillCertificateInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecManFillCertificateInfo
	#define EXT_SecManFillCertificateInfo
	#define GET_SecManFillCertificateInfo(fl)  CAL_CMGETAPI( "SecManFillCertificateInfo" ) 
	#define CAL_SecManFillCertificateInfo pICmpSecurityManager->ISecManFillCertificateInfo
	#define CHK_SecManFillCertificateInfo (pICmpSecurityManager != NULL)
	#define EXP_SecManFillCertificateInfo  CAL_CMEXPAPI( "SecManFillCertificateInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecManFillCertificateInfo  PFSECMANFILLCERTIFICATEINFO pfSecManFillCertificateInfo;
	#define EXT_SecManFillCertificateInfo  extern PFSECMANFILLCERTIFICATEINFO pfSecManFillCertificateInfo;
	#define GET_SecManFillCertificateInfo(fl)  s_pfCMGetAPI2( "SecManFillCertificateInfo", (RTS_VOID_FCTPTR *)&pfSecManFillCertificateInfo, (fl), 0, 0)
	#define CAL_SecManFillCertificateInfo  pfSecManFillCertificateInfo
	#define CHK_SecManFillCertificateInfo  (pfSecManFillCertificateInfo != NULL)
	#define EXP_SecManFillCertificateInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManFillCertificateInfo", (RTS_UINTPTR)SecManFillCertificateInfo, 0, 0) 
#endif




/**
 * <description>This function checks a TLS context that is created via TlsCreateContext() resp. TlsCreateContext2(). Here the TlsMethod, CipherList and VerifyMethod
 * can be checked against own security policy!
 *
 * NOTE:
 *	This is only a callback function from the implementation of the CmpTlsItf! So don't us it directly!
 * </description>
 * <param name="ui32TlsMethod" type="IN">Mode of the TLS connections. See: TLS_METHOD_... macros</param>
 * <param name="szCipherList" type="IN">Cipher selection of the TLS connection. See CipherList setting for details. If NULL the default of the setting will be used.</param>
 * <param name="i32VerifyMode" type="IN">Verify mode of the TLS connection. See: TLS_VERIFY... macros. Default server: NONE; Default client: VERIFY_PEER.</param>
 * <result>Result of the operation</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">All context settings are complying the security policy</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">At least one context setting is not complying the security policy!</errorcode>
 */
RTS_RESULT CDECL SecManCheckTlsContext(RTS_UI32 ui32TlsMethod, char* pszCipherList, RTS_I32 i32VerifyMode);
typedef RTS_RESULT (CDECL * PFSECMANCHECKTLSCONTEXT) (RTS_UI32 ui32TlsMethod, char* pszCipherList, RTS_I32 i32VerifyMode);
#if defined(CMPSECURITYMANAGER_NOTIMPLEMENTED) || defined(SECMANCHECKTLSCONTEXT_NOTIMPLEMENTED)
	#define USE_SecManCheckTlsContext
	#define EXT_SecManCheckTlsContext
	#define GET_SecManCheckTlsContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecManCheckTlsContext(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SecManCheckTlsContext  FALSE
	#define EXP_SecManCheckTlsContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecManCheckTlsContext
	#define EXT_SecManCheckTlsContext
	#define GET_SecManCheckTlsContext(fl)  CAL_CMGETAPI( "SecManCheckTlsContext" ) 
	#define CAL_SecManCheckTlsContext  SecManCheckTlsContext
	#define CHK_SecManCheckTlsContext  TRUE
	#define EXP_SecManCheckTlsContext  CAL_CMEXPAPI( "SecManCheckTlsContext" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURITYMANAGER_EXTERNAL)
	#define USE_SecManCheckTlsContext
	#define EXT_SecManCheckTlsContext
	#define GET_SecManCheckTlsContext(fl)  CAL_CMGETAPI( "SecManCheckTlsContext" ) 
	#define CAL_SecManCheckTlsContext  SecManCheckTlsContext
	#define CHK_SecManCheckTlsContext  TRUE
	#define EXP_SecManCheckTlsContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManCheckTlsContext", (RTS_UINTPTR)SecManCheckTlsContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecurityManagerSecManCheckTlsContext
	#define EXT_CmpSecurityManagerSecManCheckTlsContext
	#define GET_CmpSecurityManagerSecManCheckTlsContext  ERR_OK
	#define CAL_CmpSecurityManagerSecManCheckTlsContext pICmpSecurityManager->ISecManCheckTlsContext
	#define CHK_CmpSecurityManagerSecManCheckTlsContext (pICmpSecurityManager != NULL)
	#define EXP_CmpSecurityManagerSecManCheckTlsContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecManCheckTlsContext
	#define EXT_SecManCheckTlsContext
	#define GET_SecManCheckTlsContext(fl)  CAL_CMGETAPI( "SecManCheckTlsContext" ) 
	#define CAL_SecManCheckTlsContext pICmpSecurityManager->ISecManCheckTlsContext
	#define CHK_SecManCheckTlsContext (pICmpSecurityManager != NULL)
	#define EXP_SecManCheckTlsContext  CAL_CMEXPAPI( "SecManCheckTlsContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecManCheckTlsContext  PFSECMANCHECKTLSCONTEXT pfSecManCheckTlsContext;
	#define EXT_SecManCheckTlsContext  extern PFSECMANCHECKTLSCONTEXT pfSecManCheckTlsContext;
	#define GET_SecManCheckTlsContext(fl)  s_pfCMGetAPI2( "SecManCheckTlsContext", (RTS_VOID_FCTPTR *)&pfSecManCheckTlsContext, (fl), 0, 0)
	#define CAL_SecManCheckTlsContext  pfSecManCheckTlsContext
	#define CHK_SecManCheckTlsContext  (pfSecManCheckTlsContext != NULL)
	#define EXP_SecManCheckTlsContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecManCheckTlsContext", (RTS_UINTPTR)SecManCheckTlsContext, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSECMANREGISTERSETTINGS ISecManRegisterSettings;
 	PFSECMANREGISTEREDITABLESETTING ISecManRegisterEditableSetting;
 	PFSECMANUNREGISTERSETTINGS ISecManUnregisterSettings;
 	PFSECMANFINDSETTINGS ISecManFindSettings;
 	PFSECMANGETSETTING ISecManGetSetting;
 	PFSECMANGETEDITABLESETTING ISecManGetEditableSetting;
 	PFSECMANFILLCERTIFICATEINFO ISecManFillCertificateInfo;
 	PFSECMANCHECKTLSCONTEXT ISecManCheckTlsContext;
 } ICmpSecurityManager_C;

#ifdef CPLUSPLUS
class ICmpSecurityManager : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISecManRegisterSettings(CMPID cmpId, RTS_UI32 ui32UsageID, SecuritySetting *pSettings, RTS_UI32 ui32Settings, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ISecManRegisterEditableSetting(CMPID cmpId, RTS_UI32 ui32UsageID, SecurityEditableSetting *pSetting, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISecManUnregisterSettings(RTS_HANDLE hSecuritySettings) =0;
		virtual RTS_HANDLE CDECL ISecManFindSettings(CMPID cmpId, RTS_UI32 ui32UsageID, RTS_RESULT *pResult) =0;
		virtual SecuritySetting * CDECL ISecManGetSetting(RTS_HANDLE hSecuritySettings, RTS_RESULT *pResult) =0;
		virtual SecurityEditableSetting * CDECL ISecManGetEditableSetting(RTS_HANDLE hSecuritySettings, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISecManFillCertificateInfo(CMPID cmpId, RtsX509CertInfo *pCertInfo) =0;
		virtual RTS_RESULT CDECL ISecManCheckTlsContext(RTS_UI32 ui32TlsMethod, char* pszCipherList, RTS_I32 i32VerifyMode) =0;
};
	#ifndef ITF_CmpSecurityManager
		#define ITF_CmpSecurityManager static ICmpSecurityManager *pICmpSecurityManager = NULL;
	#endif
	#define EXTITF_CmpSecurityManager
#else	/*CPLUSPLUS*/
	typedef ICmpSecurityManager_C		ICmpSecurityManager;
	#ifndef ITF_CmpSecurityManager
		#define ITF_CmpSecurityManager
	#endif
	#define EXTITF_CmpSecurityManager
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPSECURITYMANAGERITF_H_*/
