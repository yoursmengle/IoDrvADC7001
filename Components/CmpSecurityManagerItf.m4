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

SET_INTERFACE_NAME(`CmpSecurityManager')

#include "CmpStd.h"
REF_ITF(`CmpX509CertItf.m4')

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
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SecManRegisterSettings',`(CMPID cmpId, RTS_UI32 ui32UsageID, SecuritySetting *pSettings, RTS_UI32 ui32Settings, RTS_RESULT *pResult)')

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
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SecManRegisterEditableSetting',`(CMPID cmpId, RTS_UI32 ui32UsageID, SecurityEditableSetting *pSetting, RTS_RESULT *pResult)')

/**
 * <description>Unregister security settings</description>
 * <param name="hSecuritySettings" type="IN">Handle to the security settings returned by SecManRegisterSettings() or SecManFindSettings() or SecManRegisterEditableSetting()</param>
 * <result>Result of the operation</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Unregister succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hSecuritySettings invalid</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SecManUnregisterSettings',`(RTS_HANDLE hSecuritySettings)')

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
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SecManFindSettings',`(CMPID cmpId, RTS_UI32 ui32UsageID, RTS_RESULT *pResult)')

/**
 * <description>Get the selected setting because of the security policy of the target!</description>
 * <param name="hSecuritySettings" type="IN">Handle to the security settings returned by SecManRegisterSettings() or SecManFindSettings()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">One setting is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">hSecuritySettings is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">No setting selected</errorcode>
 * <result>Pointer to the security setting which is selected on the target</result>
 */
DEF_ITF_API(`SecuritySetting *',`CDECL',`SecManGetSetting',`(RTS_HANDLE hSecuritySettings, RTS_RESULT *pResult)')

/**
 * <description>Get the edited value setting because of the security policy of the target!</description>
 * <param name="hSecuritySettings" type="IN">Handle to the security settings returned by SecManRegisterSettings() or SecManFindSettings()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">One setting is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">hSecuritySettings is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">No setting selected</errorcode>
 * <result>Pointer to the security setting which is selected on the target</result>
 */
DEF_ITF_API(`SecurityEditableSetting *',`CDECL',`SecManGetEditableSetting',`(RTS_HANDLE hSecuritySettings, RTS_RESULT *pResult)')

/**
 * <description>Function to overload the certificate info from a specified server resp. for a usage</description>
 * <param name="cmpId" type="IN">ComponentID of the server that provides security features</settings</param>
 * <param name="pCertInfo" type="IN">Pointer to the preinitialized certificate info</param>
 * <result>Result of the operation</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Certificate info was overloaded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">No overload done</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SecManFillCertificateInfo',`(CMPID cmpId, RtsX509CertInfo *pCertInfo)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SecManCheckTlsContext',`(RTS_UI32 ui32TlsMethod, char* pszCipherList, RTS_I32 i32VerifyMode)')

#ifdef __cplusplus
}
#endif
