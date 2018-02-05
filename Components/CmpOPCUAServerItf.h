 /**
 * <interfacename>CmpOPCUAServer</interfacename>
 * <description></description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPOPCUASERVERITF_H_
#define _CMPOPCUASERVERITF_H_

#include "CmpStd.h"

 

 



#include "CmpOPCUAProviderItf.h"
#include "CmpSecurityManagerItf.h"
#include "CmpEventMgrItf.h"

#include "opcua.h"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Configure the name network adapter to be used by the OPC UA server. By Default OPC UA will bind to ANY adress.</description>
 */
#define CMPOPCUAKEY_STRING_NETWORK_ADAPTER					"NetworkAdapter"
#ifndef CMPOPCUAVALUE_STRING_NETWORK_ADAPTER_DEFAULT	
	#define CMPOPCUAVALUE_STRING_NETWORK_ADAPTER_DEFAULT	""
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Configure the port used by the OPC UA server. Default: 4840</description>
 */
#define CMPOPCUAKEY_INT_NETWORK_PORT						"NetworkPort"
#ifndef CMPOPCUAVALUE_INT_NETWORK_PORT_DEFAULT
	#define CMPOPCUAVALUE_INT_NETWORK_PORT_DEFAULT			4840
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Use this setting to add the loopback adapter as an OPC UA endpoint if it is missing in your configuration.</description>
 */
#define CMPOPCUAKEY_INT_USE_LOOPBACK						"UseLoopback"
#ifndef CMPOPCUAVALUE_INT_USE_LOOPBACK_DEFAULT	
	#define CMPOPCUAVALUE_INT_USE_LOOPBACK_DEFAULT			1
#endif

 /**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Use this setting to set the network adapter update rate in ms. This rate is used to rescan the adapters and to add / remove the adapters.</description>
 */
#define CMPOPCUASERVERKEY_INT_ADAPTER_UPDATE_RATE						"AdapterUpdateReate"
#ifndef CMPOPCUASERVERVALUE_INT_ADAPTER_UPDATE_RATE_DEFAULT
#define CMPOPCUASERVERVALUE_INT_ADAPTER_UPDATE_RATE_DEFAULT		5000
#endif


/**
 * <category>SecuritySettings</category>
 * <description>Availabe security policies.</description>
 * <element name="CmpOPCUAServer_SecurityPolicy_Basic128Rsa15" type="IN">Support of http://opcfoundation.org/UA/SecurityPolicy#Basic128Rsa15 and higher</element>
 * <element name="CmpOPCUAServer_SecurityPolicy_Basic256" type="IN">Support of http://opcfoundation.org/UA/SecurityPolicy#Basic256 and higher</element>
 * <element name="CmpOPCUAServer_SecurityPolicy_Basic256Sha256" type="IN">Support of http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256 and higher</element>
 */
 typedef enum
 {
    CmpOPCUAServer_SecurityPolicy_Basic128Rsa15,
    CmpOPCUAServer_SecurityPolicy_Basic256,
    CmpOPCUAServer_SecurityPolicy_Basic256Sha256
 }CmpOPCUAServer_SecurityPolicy;
 
#if !CMPOPCUASTACK_ALLOW_SHA1_BASED_SECURITY
#define CMP_OPCUA_SERVER_COMM_SECURITY_POLICY   { \
													{(RTS_I32)CmpOPCUAServer_SecurityPolicy_Basic256Sha256, CMPSECMAN_FLAGS_DEFAULT, OpcUa_SecurityPolicy_Basic256Sha256, "Support for all policies beginning with Basic256Sha256 (AES 256 with SHA256) [By now highest security]"}\
												}
#else
#define CMP_OPCUA_SERVER_COMM_SECURITY_POLICY   { \
													{(RTS_I32)CmpOPCUAServer_SecurityPolicy_Basic256Sha256, CMPSECMAN_FLAGS_NONE, OpcUa_SecurityPolicy_Basic256Sha256, "Support for all policies beginning with Basic256Sha256 (AES 256 with SHA256) [By now highest security]"},\
													{(RTS_I32)CmpOPCUAServer_SecurityPolicy_Basic256, CMPSECMAN_FLAGS_NONE, OpcUa_SecurityPolicy_Basic256, "Support for all policies beginning with Basic256 (AES 256 with SHA1)"},\
													{(RTS_I32)CmpOPCUAServer_SecurityPolicy_Basic128Rsa15, CMPSECMAN_FLAGS_DEFAULT, OpcUa_SecurityPolicy_Basic128Rsa15, "Support for all policies beginning with Basic128Rsa15 (AES 128 with SHA1)"}\
												}
#endif

#define CMP_OPCUA_SERVER_SECSETTG_ID_SEC_POLICY     0
   
/**
 * <category>SecuritySettings</category>
 * <description>Available communication modes.</description>
 * <element name="CmpOPCUAServer_CommunicationMode_OnlyPlaintext" type="IN">No security Available: Only security policy None allowed. (Default without CmpSecurityManager)</element>
 * <element name="CmpOPCUAServer_CommunicationMode_PlainAndSecure" type="IN">Support all available modes. Inlcudes None, Signed, Signed + Encrypted (Default with CmpSecurityManager)</element>
 * <element name="CmpOPCUAServer_CommunicationMode_OnlySigned" type="IN">Support for the selected secure policies. But only signing will be activated.</element>
 * <element name="CmpOPCUAServer_CommunicationMode_SignedAndEncrypted" type="IN">Support of the selected secure policies. Avtivate Signing and Encryption. [HIGHES SECURITY LEVEL]</element>
 */   
typedef enum
{
    CmpOPCUAServer_CommunicationMode_OnlyPlaintext,
    CmpOPCUAServer_CommunicationMode_PlainAndSecure,
    CmpOPCUAServer_CommunicationMode_OnlySigned,
    CmpOPCUAServer_CommunicationMode_SignedAndEncrypted
}CmpOPCUAServer_CommunicationMode;

#define CMP_OPCUA_SERVER_COMM_SECURITY_MODE     {\
                                                    {(RTS_I32)CmpOPCUAServer_CommunicationMode_SignedAndEncrypted, CMPSECMAN_FLAGS_NONE, "SIGNED_AND_ENCRYPTED", "Only signed and encrypted communications profiles are added [HIGHEST_SECURITY_LEVEL]"},\
                                                    {(RTS_I32)CmpOPCUAServer_CommunicationMode_OnlySigned, CMPSECMAN_FLAGS_NONE, "ONLY_SIGNED", "Enforce a signed communication. Encryption optional available."},\
                                                    {(RTS_I32)CmpOPCUAServer_CommunicationMode_PlainAndSecure, CMPSECMAN_FLAGS_DEFAULT, "ALL_MODES", "Add all available modes. No security, just signed, signed and encrypted"},\
                                                    {(RTS_I32)CmpOPCUAServer_CommunicationMode_OnlyPlaintext, CMPSECMAN_FLAGS_NONE, "ONLY_PLAINTEXT", "Support only plaintext communication. Default without security manager."}\
                                                }
#define CMP_OPCUA_SERVER_SECSETTG_ID_COMM_MODE     1

/**
 * <category>SecuritySettings</category>
 * <description>This setting allows to disable the CmpOPCUAServer.</description>
 * <element name="CmpOPCUAServer_Deactivated" type="IN">The OPC UA server will be loaded as a component. But it will not be active. No ports will be opened.</element>
 * <element name="CmpOPCUAServer_Activated" type="IN">The OPC UA server is activated. (Default with and without CmpSecurityManager)</element>
 */
typedef enum
{
	CmpOPCUAServer_Deactivated,
	CmpOPCUAServer_Activated
}CmpOPCUAServer_Activation;
#define CMP_OPCUA_SERVER_ACTIVATION             {\
                                                    {(RTS_I32)CmpOPCUAServer_Deactivated, CMPSECMAN_FLAGS_NONE, "DEACTIVATED", "Deactivates the OPC UA Server"},\
                                                    {(RTS_I32)CmpOPCUAServer_Activated, CMPSECMAN_FLAGS_DEFAULT, "ACTIVATED", "Activates the OPC UA Server. [Default]"}\
                                                }
#define CMP_OPCUA_SERVER_SECSETTG_ID_ACTIVATION    2

/*
 * The following IDs are used for editable string settings.
 */
#define CMP_OPCUA_SERVER_SECSETTG_ID_APPNAME       3
#define CMP_OPCUA_SERVER_SECSETTG_ID_ORG_NAME      4
#define CMP_OPCUA_SERVER_SECSETTG__ID_LOCATION     5
#define CMP_OPCUA_SERVER_SECSETTG_ID_STATE         6
#define CMP_OPCUA_SERVER_SECSETTG_ID_COUNTRY       7


/*
 * Event definitions
 */


#define CMPOPCUASERVER_SESSION_ADDED        1
#define CMPOPCUASERVER_SESSION_CHANGED      2
#define CMPOPCUASERVER_SESSION_REMOVED      3
/**
 * <category>Event parameter</category>
 * <element name="event" type="OUT">Type of session change. Can be one of added, changed or removed. See CMPOPCUASERVER_SESSION_* values.</element>
 * <element name="ui32SessionId" type="OUT">SessionID of added, changed or removed session.</element>
 */
typedef struct
{
	RTS_UI32 event;
    RTS_UI32 ui32SessionId;
} EVTPARAM_CmpOPCUAServerSessionsChanged;
#define EVTPARAMID_CmpOPCUAServerSessionsChanged						0x0001
#define EVTVERSION_CmpOPCUAServerSessionsChanged						0x0001

/**
 * <category>Events</category>
 * <description>Event is sent if a session has been added, removed or changed.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpOPCUAServerSessionsChanged</param>
 */
#define EVT_CmpOPCUAServerSessionsChanged					MAKE_EVENTID(EVTCLASS_INFO, 1)

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Enum: OpcUaServer_MessageSecurityMode</description>
 */
#define OPCUASERVER_MESSAGESECURITYMODE_INVALID    RTS_IEC_DWORD_C(0x0)	
#define OPCUASERVER_MESSAGESECURITYMODE_NONE    RTS_IEC_DWORD_C(0x1)	
#define OPCUASERVER_MESSAGESECURITYMODE_SIGN    RTS_IEC_DWORD_C(0x2)	
#define OPCUASERVER_MESSAGESECURITYMODE_SIGNANDENCRYPT    RTS_IEC_DWORD_C(0x3)	
/* Typed enum definition */
#define OPCUASERVER_MESSAGESECURITYMODE    RTS_IEC_DWORD

/**
 * <description>Enum: OpcUaServer_SessionEvents</description>
 */
#define OPCUASERVER_SESSIONEVENTS_SESSION_ADDED    RTS_IEC_DWORD_C(0x1)	
#define OPCUASERVER_SESSIONEVENTS_SESSION_CHANGED    RTS_IEC_DWORD_C(0x2)	
#define OPCUASERVER_SESSIONEVENTS_SESSION_REMOVED    RTS_IEC_DWORD_C(0x3)	
/* Typed enum definition */
#define OPCUASERVER_SESSIONEVENTS    RTS_IEC_DWORD

/**
 * <description>OpcUaServer_Session_Information</description>
 */
typedef struct tagOpcUaServer_Session_Information
{
	RTS_IEC_DWORD dwSessionId;		
	INADDR clientAddress;		/* SessionID of the session. */
	RTS_IEC_WSTRING pwsSessionName[256];		/* IpAddress of the client. In host byteorder. */
	RTS_IEC_WSTRING pwsApplicationName[256];		/* Sessionname. This is set by the client. */
	RTS_IEC_WSTRING pwsApplicationUri[256];		/* Applicationname of client. */
	RTS_IEC_WSTRING pwsProductUri[256];		/* URI of the client instance. */
	RTS_IEC_WSTRING pwsSecurityPolicy[256];		/* URI of client type. */
	RTS_IEC_DWORD securityMode;		/* Security profile used by this session. */
	RTS_IEC_HANDLE hClientCertificate;		/* Security mode of the session. */
	RTS_IEC_HANDLE hUser;		/* Handle to the clients certificate. Only valid for secure connections. RTS_INVALID_HANDLE if not available. */
} OpcUaServer_Session_Information;

/**
 * This function returns the first available session. Use this function and 
 * OpcUaServerGetNextSession to get the initial session configuration. To get notified about 
 * changes register to the EVT_CmpOPCUAServerSessionsChanged event.</description>
 *
 * :return: SessionId of the first session. 0xFFFFFFFF if no session is availble.</result>
 */
typedef struct tagopcuaservergetfirstsession_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_DWORD OpcUaServerGetFirstSession;	/* VAR_OUTPUT */	
} opcuaservergetfirstsession_struct;

void CDECL CDECL_EXT opcuaservergetfirstsession(opcuaservergetfirstsession_struct *p);
typedef void (CDECL CDECL_EXT* PFOPCUASERVERGETFIRSTSESSION_IEC) (opcuaservergetfirstsession_struct *p);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERGETFIRSTSESSION_NOTIMPLEMENTED)
	#define USE_opcuaservergetfirstsession
	#define EXT_opcuaservergetfirstsession
	#define GET_opcuaservergetfirstsession(fl)  ERR_NOTIMPLEMENTED
	#define CAL_opcuaservergetfirstsession(p0) 
	#define CHK_opcuaservergetfirstsession  FALSE
	#define EXP_opcuaservergetfirstsession  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_opcuaservergetfirstsession
	#define EXT_opcuaservergetfirstsession
	#define GET_opcuaservergetfirstsession(fl)  CAL_CMGETAPI( "opcuaservergetfirstsession" ) 
	#define CAL_opcuaservergetfirstsession  opcuaservergetfirstsession
	#define CHK_opcuaservergetfirstsession  TRUE
	#define EXP_opcuaservergetfirstsession  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetfirstsession", (RTS_UINTPTR)opcuaservergetfirstsession, 1, 0xACB7E0DC, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_opcuaservergetfirstsession
	#define EXT_opcuaservergetfirstsession
	#define GET_opcuaservergetfirstsession(fl)  CAL_CMGETAPI( "opcuaservergetfirstsession" ) 
	#define CAL_opcuaservergetfirstsession  opcuaservergetfirstsession
	#define CHK_opcuaservergetfirstsession  TRUE
	#define EXP_opcuaservergetfirstsession  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetfirstsession", (RTS_UINTPTR)opcuaservergetfirstsession, 1, 0xACB7E0DC, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServeropcuaservergetfirstsession
	#define EXT_CmpOPCUAServeropcuaservergetfirstsession
	#define GET_CmpOPCUAServeropcuaservergetfirstsession  ERR_OK
	#define CAL_CmpOPCUAServeropcuaservergetfirstsession  opcuaservergetfirstsession
	#define CHK_CmpOPCUAServeropcuaservergetfirstsession  TRUE
	#define EXP_CmpOPCUAServeropcuaservergetfirstsession  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetfirstsession", (RTS_UINTPTR)opcuaservergetfirstsession, 1, 0xACB7E0DC, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_opcuaservergetfirstsession
	#define EXT_opcuaservergetfirstsession
	#define GET_opcuaservergetfirstsession(fl)  CAL_CMGETAPI( "opcuaservergetfirstsession" ) 
	#define CAL_opcuaservergetfirstsession  opcuaservergetfirstsession
	#define CHK_opcuaservergetfirstsession  TRUE
	#define EXP_opcuaservergetfirstsession  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetfirstsession", (RTS_UINTPTR)opcuaservergetfirstsession, 1, 0xACB7E0DC, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_opcuaservergetfirstsession  PFOPCUASERVERGETFIRSTSESSION_IEC pfopcuaservergetfirstsession;
	#define EXT_opcuaservergetfirstsession  extern PFOPCUASERVERGETFIRSTSESSION_IEC pfopcuaservergetfirstsession;
	#define GET_opcuaservergetfirstsession(fl)  s_pfCMGetAPI2( "opcuaservergetfirstsession", (RTS_VOID_FCTPTR *)&pfopcuaservergetfirstsession, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xACB7E0DC, 0x03050C00)
	#define CAL_opcuaservergetfirstsession  pfopcuaservergetfirstsession
	#define CHK_opcuaservergetfirstsession  (pfopcuaservergetfirstsession != NULL)
	#define EXP_opcuaservergetfirstsession   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetfirstsession", (RTS_UINTPTR)opcuaservergetfirstsession, 1, 0xACB7E0DC, 0x03050C00) 
#endif


/**
 * This function returns the next available session.</description>
 *
 * :result: SessionId of the first session. 0xFFFFFFFF if no session is availble.
 */
typedef struct tagopcuaservergetnextsession_struct
{
	RTS_IEC_DWORD dwLastSession;		/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* SessionID of the last session. */
	RTS_IEC_DWORD OpcUaServerGetNextSession;	/* VAR_OUTPUT */	
} opcuaservergetnextsession_struct;

void CDECL CDECL_EXT opcuaservergetnextsession(opcuaservergetnextsession_struct *p);
typedef void (CDECL CDECL_EXT* PFOPCUASERVERGETNEXTSESSION_IEC) (opcuaservergetnextsession_struct *p);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERGETNEXTSESSION_NOTIMPLEMENTED)
	#define USE_opcuaservergetnextsession
	#define EXT_opcuaservergetnextsession
	#define GET_opcuaservergetnextsession(fl)  ERR_NOTIMPLEMENTED
	#define CAL_opcuaservergetnextsession(p0) 
	#define CHK_opcuaservergetnextsession  FALSE
	#define EXP_opcuaservergetnextsession  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_opcuaservergetnextsession
	#define EXT_opcuaservergetnextsession
	#define GET_opcuaservergetnextsession(fl)  CAL_CMGETAPI( "opcuaservergetnextsession" ) 
	#define CAL_opcuaservergetnextsession  opcuaservergetnextsession
	#define CHK_opcuaservergetnextsession  TRUE
	#define EXP_opcuaservergetnextsession  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetnextsession", (RTS_UINTPTR)opcuaservergetnextsession, 1, 0xE2BBF24A, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_opcuaservergetnextsession
	#define EXT_opcuaservergetnextsession
	#define GET_opcuaservergetnextsession(fl)  CAL_CMGETAPI( "opcuaservergetnextsession" ) 
	#define CAL_opcuaservergetnextsession  opcuaservergetnextsession
	#define CHK_opcuaservergetnextsession  TRUE
	#define EXP_opcuaservergetnextsession  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetnextsession", (RTS_UINTPTR)opcuaservergetnextsession, 1, 0xE2BBF24A, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServeropcuaservergetnextsession
	#define EXT_CmpOPCUAServeropcuaservergetnextsession
	#define GET_CmpOPCUAServeropcuaservergetnextsession  ERR_OK
	#define CAL_CmpOPCUAServeropcuaservergetnextsession  opcuaservergetnextsession
	#define CHK_CmpOPCUAServeropcuaservergetnextsession  TRUE
	#define EXP_CmpOPCUAServeropcuaservergetnextsession  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetnextsession", (RTS_UINTPTR)opcuaservergetnextsession, 1, 0xE2BBF24A, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_opcuaservergetnextsession
	#define EXT_opcuaservergetnextsession
	#define GET_opcuaservergetnextsession(fl)  CAL_CMGETAPI( "opcuaservergetnextsession" ) 
	#define CAL_opcuaservergetnextsession  opcuaservergetnextsession
	#define CHK_opcuaservergetnextsession  TRUE
	#define EXP_opcuaservergetnextsession  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetnextsession", (RTS_UINTPTR)opcuaservergetnextsession, 1, 0xE2BBF24A, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_opcuaservergetnextsession  PFOPCUASERVERGETNEXTSESSION_IEC pfopcuaservergetnextsession;
	#define EXT_opcuaservergetnextsession  extern PFOPCUASERVERGETNEXTSESSION_IEC pfopcuaservergetnextsession;
	#define GET_opcuaservergetnextsession(fl)  s_pfCMGetAPI2( "opcuaservergetnextsession", (RTS_VOID_FCTPTR *)&pfopcuaservergetnextsession, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE2BBF24A, 0x03050C00)
	#define CAL_opcuaservergetnextsession  pfopcuaservergetnextsession
	#define CHK_opcuaservergetnextsession  (pfopcuaservergetnextsession != NULL)
	#define EXP_opcuaservergetnextsession   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetnextsession", (RTS_UINTPTR)opcuaservergetnextsession, 1, 0xE2BBF24A, 0x03050C00) 
#endif


/**
 * This function returns details about a specific session.
 *
 * :return: Result of the operation. ERR_NOT_OBJECT if the sessions is available. ERR_OK if everything went fine.
 */
typedef struct tagopcuaservergetsessioninfo_struct
{
	RTS_IEC_DWORD dwSessionId;			/* VAR_INPUT */	
	OpcUaServer_Session_Information *pInformation;	/* VAR_INPUT */	/* SessionID of the session. */
	RTS_IEC_RESULT OpcUaServerGetSessionInfo;	/* VAR_OUTPUT */	
} opcuaservergetsessioninfo_struct;

void CDECL CDECL_EXT opcuaservergetsessioninfo(opcuaservergetsessioninfo_struct *p);
typedef void (CDECL CDECL_EXT* PFOPCUASERVERGETSESSIONINFO_IEC) (opcuaservergetsessioninfo_struct *p);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERGETSESSIONINFO_NOTIMPLEMENTED)
	#define USE_opcuaservergetsessioninfo
	#define EXT_opcuaservergetsessioninfo
	#define GET_opcuaservergetsessioninfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_opcuaservergetsessioninfo(p0) 
	#define CHK_opcuaservergetsessioninfo  FALSE
	#define EXP_opcuaservergetsessioninfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_opcuaservergetsessioninfo
	#define EXT_opcuaservergetsessioninfo
	#define GET_opcuaservergetsessioninfo(fl)  CAL_CMGETAPI( "opcuaservergetsessioninfo" ) 
	#define CAL_opcuaservergetsessioninfo  opcuaservergetsessioninfo
	#define CHK_opcuaservergetsessioninfo  TRUE
	#define EXP_opcuaservergetsessioninfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetsessioninfo", (RTS_UINTPTR)opcuaservergetsessioninfo, 1, 0x6AE85AE6, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_opcuaservergetsessioninfo
	#define EXT_opcuaservergetsessioninfo
	#define GET_opcuaservergetsessioninfo(fl)  CAL_CMGETAPI( "opcuaservergetsessioninfo" ) 
	#define CAL_opcuaservergetsessioninfo  opcuaservergetsessioninfo
	#define CHK_opcuaservergetsessioninfo  TRUE
	#define EXP_opcuaservergetsessioninfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetsessioninfo", (RTS_UINTPTR)opcuaservergetsessioninfo, 1, 0x6AE85AE6, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServeropcuaservergetsessioninfo
	#define EXT_CmpOPCUAServeropcuaservergetsessioninfo
	#define GET_CmpOPCUAServeropcuaservergetsessioninfo  ERR_OK
	#define CAL_CmpOPCUAServeropcuaservergetsessioninfo  opcuaservergetsessioninfo
	#define CHK_CmpOPCUAServeropcuaservergetsessioninfo  TRUE
	#define EXP_CmpOPCUAServeropcuaservergetsessioninfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetsessioninfo", (RTS_UINTPTR)opcuaservergetsessioninfo, 1, 0x6AE85AE6, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_opcuaservergetsessioninfo
	#define EXT_opcuaservergetsessioninfo
	#define GET_opcuaservergetsessioninfo(fl)  CAL_CMGETAPI( "opcuaservergetsessioninfo" ) 
	#define CAL_opcuaservergetsessioninfo  opcuaservergetsessioninfo
	#define CHK_opcuaservergetsessioninfo  TRUE
	#define EXP_opcuaservergetsessioninfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetsessioninfo", (RTS_UINTPTR)opcuaservergetsessioninfo, 1, 0x6AE85AE6, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_opcuaservergetsessioninfo  PFOPCUASERVERGETSESSIONINFO_IEC pfopcuaservergetsessioninfo;
	#define EXT_opcuaservergetsessioninfo  extern PFOPCUASERVERGETSESSIONINFO_IEC pfopcuaservergetsessioninfo;
	#define GET_opcuaservergetsessioninfo(fl)  s_pfCMGetAPI2( "opcuaservergetsessioninfo", (RTS_VOID_FCTPTR *)&pfopcuaservergetsessioninfo, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x6AE85AE6, 0x03050C00)
	#define CAL_opcuaservergetsessioninfo  pfopcuaservergetsessioninfo
	#define CHK_opcuaservergetsessioninfo  (pfopcuaservergetsessioninfo != NULL)
	#define EXP_opcuaservergetsessioninfo   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"opcuaservergetsessioninfo", (RTS_UINTPTR)opcuaservergetsessioninfo, 1, 0x6AE85AE6, 0x03050C00) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#define Max_NumericRanges 5
typedef enum _NumericRangeType
{
	RangeType_Index = 0,
	RangeType_Range
} NumericRangeType;


/**
 * <element name="uiFrom">Index or start of range if Type = Range.</element>
 * <element name="uiTo">End of range if Type = Range, unused otherwise.</element>
 */
typedef struct _NumericRange
{
	NumericRangeType Type;
	OpcUa_Int32 uiFrom;
	OpcUa_Int32 uiTo;
} NumericRange;

typedef struct _OpcUaServer_SimpleBrowsePath
{
    OpcUa_UInt32 ui32NumOfElements;     /* Number of qualified names building the actual browse path */
    OpcUa_QualifiedName* pBrowsePath;   /* Pointer to an array of qualified names building the path.*/
}OpcUaServer_BrowsePath;


/**
 * <description>Register a new data provider within the OPC UA server.</description>
 * <param name="providerInterface" type="IN">Table of the provider interface.</param>
 * <result>Operation result:
 * </result>
 **/
RTS_RESULT CDECL OpcUaServerRegisterProvider(OpcUaProvider_Info* providerInterface);
typedef RTS_RESULT (CDECL * PFOPCUASERVERREGISTERPROVIDER) (OpcUaProvider_Info* providerInterface);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERREGISTERPROVIDER_NOTIMPLEMENTED)
	#define USE_OpcUaServerRegisterProvider
	#define EXT_OpcUaServerRegisterProvider
	#define GET_OpcUaServerRegisterProvider(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerRegisterProvider(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerRegisterProvider  FALSE
	#define EXP_OpcUaServerRegisterProvider  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerRegisterProvider
	#define EXT_OpcUaServerRegisterProvider
	#define GET_OpcUaServerRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerRegisterProvider" ) 
	#define CAL_OpcUaServerRegisterProvider  OpcUaServerRegisterProvider
	#define CHK_OpcUaServerRegisterProvider  TRUE
	#define EXP_OpcUaServerRegisterProvider  CAL_CMEXPAPI( "OpcUaServerRegisterProvider" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerRegisterProvider
	#define EXT_OpcUaServerRegisterProvider
	#define GET_OpcUaServerRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerRegisterProvider" ) 
	#define CAL_OpcUaServerRegisterProvider  OpcUaServerRegisterProvider
	#define CHK_OpcUaServerRegisterProvider  TRUE
	#define EXP_OpcUaServerRegisterProvider  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterProvider", (RTS_UINTPTR)OpcUaServerRegisterProvider, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerRegisterProvider
	#define EXT_CmpOPCUAServerOpcUaServerRegisterProvider
	#define GET_CmpOPCUAServerOpcUaServerRegisterProvider  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerRegisterProvider pICmpOPCUAServer->IOpcUaServerRegisterProvider
	#define CHK_CmpOPCUAServerOpcUaServerRegisterProvider (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerRegisterProvider  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerRegisterProvider
	#define EXT_OpcUaServerRegisterProvider
	#define GET_OpcUaServerRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerRegisterProvider" ) 
	#define CAL_OpcUaServerRegisterProvider pICmpOPCUAServer->IOpcUaServerRegisterProvider
	#define CHK_OpcUaServerRegisterProvider (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerRegisterProvider  CAL_CMEXPAPI( "OpcUaServerRegisterProvider" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerRegisterProvider  PFOPCUASERVERREGISTERPROVIDER pfOpcUaServerRegisterProvider;
	#define EXT_OpcUaServerRegisterProvider  extern PFOPCUASERVERREGISTERPROVIDER pfOpcUaServerRegisterProvider;
	#define GET_OpcUaServerRegisterProvider(fl)  s_pfCMGetAPI2( "OpcUaServerRegisterProvider", (RTS_VOID_FCTPTR *)&pfOpcUaServerRegisterProvider, (fl), 0, 0)
	#define CAL_OpcUaServerRegisterProvider  pfOpcUaServerRegisterProvider
	#define CHK_OpcUaServerRegisterProvider  (pfOpcUaServerRegisterProvider != NULL)
	#define EXP_OpcUaServerRegisterProvider  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterProvider", (RTS_UINTPTR)OpcUaServerRegisterProvider, 0, 0) 
#endif




/**
 * <description>Unregister an already registered data provider within the OPC UA server. 
 *
 * IMPLEMENTATION NOTE: Use CH_EXIT_TASK or later to unregister the provider. Don't unregister the provider while the
 * OPC UA server is running. This may lead to undefined behavior.
 * </description>
 * <param name="providerInterface" type="IN">Table of the provider interface.</param>
 * <result>Operation result:
 * </result>
 **/
RTS_RESULT CDECL OpcUaServerUnRegisterProvider(OpcUaProvider_Info* providerInterface);
typedef RTS_RESULT (CDECL * PFOPCUASERVERUNREGISTERPROVIDER) (OpcUaProvider_Info* providerInterface);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERUNREGISTERPROVIDER_NOTIMPLEMENTED)
	#define USE_OpcUaServerUnRegisterProvider
	#define EXT_OpcUaServerUnRegisterProvider
	#define GET_OpcUaServerUnRegisterProvider(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerUnRegisterProvider(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerUnRegisterProvider  FALSE
	#define EXP_OpcUaServerUnRegisterProvider  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerUnRegisterProvider
	#define EXT_OpcUaServerUnRegisterProvider
	#define GET_OpcUaServerUnRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerUnRegisterProvider" ) 
	#define CAL_OpcUaServerUnRegisterProvider  OpcUaServerUnRegisterProvider
	#define CHK_OpcUaServerUnRegisterProvider  TRUE
	#define EXP_OpcUaServerUnRegisterProvider  CAL_CMEXPAPI( "OpcUaServerUnRegisterProvider" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerUnRegisterProvider
	#define EXT_OpcUaServerUnRegisterProvider
	#define GET_OpcUaServerUnRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerUnRegisterProvider" ) 
	#define CAL_OpcUaServerUnRegisterProvider  OpcUaServerUnRegisterProvider
	#define CHK_OpcUaServerUnRegisterProvider  TRUE
	#define EXP_OpcUaServerUnRegisterProvider  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerUnRegisterProvider", (RTS_UINTPTR)OpcUaServerUnRegisterProvider, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerUnRegisterProvider
	#define EXT_CmpOPCUAServerOpcUaServerUnRegisterProvider
	#define GET_CmpOPCUAServerOpcUaServerUnRegisterProvider  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerUnRegisterProvider pICmpOPCUAServer->IOpcUaServerUnRegisterProvider
	#define CHK_CmpOPCUAServerOpcUaServerUnRegisterProvider (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerUnRegisterProvider  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerUnRegisterProvider
	#define EXT_OpcUaServerUnRegisterProvider
	#define GET_OpcUaServerUnRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerUnRegisterProvider" ) 
	#define CAL_OpcUaServerUnRegisterProvider pICmpOPCUAServer->IOpcUaServerUnRegisterProvider
	#define CHK_OpcUaServerUnRegisterProvider (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerUnRegisterProvider  CAL_CMEXPAPI( "OpcUaServerUnRegisterProvider" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerUnRegisterProvider  PFOPCUASERVERUNREGISTERPROVIDER pfOpcUaServerUnRegisterProvider;
	#define EXT_OpcUaServerUnRegisterProvider  extern PFOPCUASERVERUNREGISTERPROVIDER pfOpcUaServerUnRegisterProvider;
	#define GET_OpcUaServerUnRegisterProvider(fl)  s_pfCMGetAPI2( "OpcUaServerUnRegisterProvider", (RTS_VOID_FCTPTR *)&pfOpcUaServerUnRegisterProvider, (fl), 0, 0)
	#define CAL_OpcUaServerUnRegisterProvider  pfOpcUaServerUnRegisterProvider
	#define CHK_OpcUaServerUnRegisterProvider  (pfOpcUaServerUnRegisterProvider != NULL)
	#define EXP_OpcUaServerUnRegisterProvider  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerUnRegisterProvider", (RTS_UINTPTR)OpcUaServerUnRegisterProvider, 0, 0) 
#endif




/**
 * <description>Check if to follow OPCU UA referencetype ID. Since referenctype IDs may are derived only the server who knows all IDs can check this.</description>
 * <param name="pRequestedReference" type="IN">The referencetype ID the client requested.</param>
 * <param name="bIncludeSubtypes" type="IN">The flag if subtypes should be followed too. Set by the client.</param>
 * <param name="pReferenceToCheck" type="IN">The referencetype ID the compare against. Usually the referencetype ID of the current node (e.g. while browsing) in the adress space.</param>
 * <result>The function returns OpcUa_True if following the referencetype ID is allowd. OpcUa_False is returned otherwhise.</result>
 **/
OpcUa_Boolean CDECL OpcUaServerCheckReferenceRecursive(const OpcUa_NodeId* pRequestedReference, OpcUa_Boolean bIncludeSubtypes, const OpcUa_NodeId* pReferenceToCheck);
typedef OpcUa_Boolean (CDECL * PFOPCUASERVERCHECKREFERENCERECURSIVE) (const OpcUa_NodeId* pRequestedReference, OpcUa_Boolean bIncludeSubtypes, const OpcUa_NodeId* pReferenceToCheck);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERCHECKREFERENCERECURSIVE_NOTIMPLEMENTED)
	#define USE_OpcUaServerCheckReferenceRecursive
	#define EXT_OpcUaServerCheckReferenceRecursive
	#define GET_OpcUaServerCheckReferenceRecursive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerCheckReferenceRecursive(p0,p1,p2)  (OpcUa_Boolean)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerCheckReferenceRecursive  FALSE
	#define EXP_OpcUaServerCheckReferenceRecursive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerCheckReferenceRecursive
	#define EXT_OpcUaServerCheckReferenceRecursive
	#define GET_OpcUaServerCheckReferenceRecursive(fl)  CAL_CMGETAPI( "OpcUaServerCheckReferenceRecursive" ) 
	#define CAL_OpcUaServerCheckReferenceRecursive  OpcUaServerCheckReferenceRecursive
	#define CHK_OpcUaServerCheckReferenceRecursive  TRUE
	#define EXP_OpcUaServerCheckReferenceRecursive  CAL_CMEXPAPI( "OpcUaServerCheckReferenceRecursive" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerCheckReferenceRecursive
	#define EXT_OpcUaServerCheckReferenceRecursive
	#define GET_OpcUaServerCheckReferenceRecursive(fl)  CAL_CMGETAPI( "OpcUaServerCheckReferenceRecursive" ) 
	#define CAL_OpcUaServerCheckReferenceRecursive  OpcUaServerCheckReferenceRecursive
	#define CHK_OpcUaServerCheckReferenceRecursive  TRUE
	#define EXP_OpcUaServerCheckReferenceRecursive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerCheckReferenceRecursive", (RTS_UINTPTR)OpcUaServerCheckReferenceRecursive, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerCheckReferenceRecursive
	#define EXT_CmpOPCUAServerOpcUaServerCheckReferenceRecursive
	#define GET_CmpOPCUAServerOpcUaServerCheckReferenceRecursive  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerCheckReferenceRecursive pICmpOPCUAServer->IOpcUaServerCheckReferenceRecursive
	#define CHK_CmpOPCUAServerOpcUaServerCheckReferenceRecursive (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerCheckReferenceRecursive  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerCheckReferenceRecursive
	#define EXT_OpcUaServerCheckReferenceRecursive
	#define GET_OpcUaServerCheckReferenceRecursive(fl)  CAL_CMGETAPI( "OpcUaServerCheckReferenceRecursive" ) 
	#define CAL_OpcUaServerCheckReferenceRecursive pICmpOPCUAServer->IOpcUaServerCheckReferenceRecursive
	#define CHK_OpcUaServerCheckReferenceRecursive (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerCheckReferenceRecursive  CAL_CMEXPAPI( "OpcUaServerCheckReferenceRecursive" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerCheckReferenceRecursive  PFOPCUASERVERCHECKREFERENCERECURSIVE pfOpcUaServerCheckReferenceRecursive;
	#define EXT_OpcUaServerCheckReferenceRecursive  extern PFOPCUASERVERCHECKREFERENCERECURSIVE pfOpcUaServerCheckReferenceRecursive;
	#define GET_OpcUaServerCheckReferenceRecursive(fl)  s_pfCMGetAPI2( "OpcUaServerCheckReferenceRecursive", (RTS_VOID_FCTPTR *)&pfOpcUaServerCheckReferenceRecursive, (fl), 0, 0)
	#define CAL_OpcUaServerCheckReferenceRecursive  pfOpcUaServerCheckReferenceRecursive
	#define CHK_OpcUaServerCheckReferenceRecursive  (pfOpcUaServerCheckReferenceRecursive != NULL)
	#define EXP_OpcUaServerCheckReferenceRecursive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerCheckReferenceRecursive", (RTS_UINTPTR)OpcUaServerCheckReferenceRecursive, 0, 0) 
#endif




/**
 * <description>This funtion checks if a referencetype ID is valid.</description>
 * <param name="pRefTypeId" type="IN">Referecetype ID to check.</param>
 * <result>Returns either OpcUa_Good or OpcUa_BadRefereceTypeIdInvalid.</result>
 **/
OpcUa_StatusCode CDECL OpcUaServerCheckIfReferenceIsValid(const OpcUa_NodeId* pRefTypeId);
typedef OpcUa_StatusCode (CDECL * PFOPCUASERVERCHECKIFREFERENCEISVALID) (const OpcUa_NodeId* pRefTypeId);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERCHECKIFREFERENCEISVALID_NOTIMPLEMENTED)
	#define USE_OpcUaServerCheckIfReferenceIsValid
	#define EXT_OpcUaServerCheckIfReferenceIsValid
	#define GET_OpcUaServerCheckIfReferenceIsValid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerCheckIfReferenceIsValid(p0)  (OpcUa_StatusCode)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerCheckIfReferenceIsValid  FALSE
	#define EXP_OpcUaServerCheckIfReferenceIsValid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerCheckIfReferenceIsValid
	#define EXT_OpcUaServerCheckIfReferenceIsValid
	#define GET_OpcUaServerCheckIfReferenceIsValid(fl)  CAL_CMGETAPI( "OpcUaServerCheckIfReferenceIsValid" ) 
	#define CAL_OpcUaServerCheckIfReferenceIsValid  OpcUaServerCheckIfReferenceIsValid
	#define CHK_OpcUaServerCheckIfReferenceIsValid  TRUE
	#define EXP_OpcUaServerCheckIfReferenceIsValid  CAL_CMEXPAPI( "OpcUaServerCheckIfReferenceIsValid" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerCheckIfReferenceIsValid
	#define EXT_OpcUaServerCheckIfReferenceIsValid
	#define GET_OpcUaServerCheckIfReferenceIsValid(fl)  CAL_CMGETAPI( "OpcUaServerCheckIfReferenceIsValid" ) 
	#define CAL_OpcUaServerCheckIfReferenceIsValid  OpcUaServerCheckIfReferenceIsValid
	#define CHK_OpcUaServerCheckIfReferenceIsValid  TRUE
	#define EXP_OpcUaServerCheckIfReferenceIsValid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerCheckIfReferenceIsValid", (RTS_UINTPTR)OpcUaServerCheckIfReferenceIsValid, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid
	#define EXT_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid
	#define GET_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid pICmpOPCUAServer->IOpcUaServerCheckIfReferenceIsValid
	#define CHK_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerCheckIfReferenceIsValid
	#define EXT_OpcUaServerCheckIfReferenceIsValid
	#define GET_OpcUaServerCheckIfReferenceIsValid(fl)  CAL_CMGETAPI( "OpcUaServerCheckIfReferenceIsValid" ) 
	#define CAL_OpcUaServerCheckIfReferenceIsValid pICmpOPCUAServer->IOpcUaServerCheckIfReferenceIsValid
	#define CHK_OpcUaServerCheckIfReferenceIsValid (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerCheckIfReferenceIsValid  CAL_CMEXPAPI( "OpcUaServerCheckIfReferenceIsValid" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerCheckIfReferenceIsValid  PFOPCUASERVERCHECKIFREFERENCEISVALID pfOpcUaServerCheckIfReferenceIsValid;
	#define EXT_OpcUaServerCheckIfReferenceIsValid  extern PFOPCUASERVERCHECKIFREFERENCEISVALID pfOpcUaServerCheckIfReferenceIsValid;
	#define GET_OpcUaServerCheckIfReferenceIsValid(fl)  s_pfCMGetAPI2( "OpcUaServerCheckIfReferenceIsValid", (RTS_VOID_FCTPTR *)&pfOpcUaServerCheckIfReferenceIsValid, (fl), 0, 0)
	#define CAL_OpcUaServerCheckIfReferenceIsValid  pfOpcUaServerCheckIfReferenceIsValid
	#define CHK_OpcUaServerCheckIfReferenceIsValid  (pfOpcUaServerCheckIfReferenceIsValid != NULL)
	#define EXP_OpcUaServerCheckIfReferenceIsValid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerCheckIfReferenceIsValid", (RTS_UINTPTR)OpcUaServerCheckIfReferenceIsValid, 0, 0) 
#endif




/**
 * <description>Get the namespace index of the given namespace. Do not relay on constant referencetype IDs. They may depend on the registration order of different providers.</description>
 * <param name="pNamespace" type="IN">The namespace of intrest.</param>
 * <result>-1: If the namespace is not registerd yet. index: The index of the namespace. This does not change while the server is running.</result>
 **/
OpcUa_Int16 CDECL OpcUaServerGetNamespaceIndex(OpcUa_String* pNamespace);
typedef OpcUa_Int16 (CDECL * PFOPCUASERVERGETNAMESPACEINDEX) (OpcUa_String* pNamespace);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERGETNAMESPACEINDEX_NOTIMPLEMENTED)
	#define USE_OpcUaServerGetNamespaceIndex
	#define EXT_OpcUaServerGetNamespaceIndex
	#define GET_OpcUaServerGetNamespaceIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerGetNamespaceIndex(p0)  (OpcUa_Int16)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerGetNamespaceIndex  FALSE
	#define EXP_OpcUaServerGetNamespaceIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerGetNamespaceIndex
	#define EXT_OpcUaServerGetNamespaceIndex
	#define GET_OpcUaServerGetNamespaceIndex(fl)  CAL_CMGETAPI( "OpcUaServerGetNamespaceIndex" ) 
	#define CAL_OpcUaServerGetNamespaceIndex  OpcUaServerGetNamespaceIndex
	#define CHK_OpcUaServerGetNamespaceIndex  TRUE
	#define EXP_OpcUaServerGetNamespaceIndex  CAL_CMEXPAPI( "OpcUaServerGetNamespaceIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerGetNamespaceIndex
	#define EXT_OpcUaServerGetNamespaceIndex
	#define GET_OpcUaServerGetNamespaceIndex(fl)  CAL_CMGETAPI( "OpcUaServerGetNamespaceIndex" ) 
	#define CAL_OpcUaServerGetNamespaceIndex  OpcUaServerGetNamespaceIndex
	#define CHK_OpcUaServerGetNamespaceIndex  TRUE
	#define EXP_OpcUaServerGetNamespaceIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetNamespaceIndex", (RTS_UINTPTR)OpcUaServerGetNamespaceIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerGetNamespaceIndex
	#define EXT_CmpOPCUAServerOpcUaServerGetNamespaceIndex
	#define GET_CmpOPCUAServerOpcUaServerGetNamespaceIndex  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerGetNamespaceIndex pICmpOPCUAServer->IOpcUaServerGetNamespaceIndex
	#define CHK_CmpOPCUAServerOpcUaServerGetNamespaceIndex (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerGetNamespaceIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerGetNamespaceIndex
	#define EXT_OpcUaServerGetNamespaceIndex
	#define GET_OpcUaServerGetNamespaceIndex(fl)  CAL_CMGETAPI( "OpcUaServerGetNamespaceIndex" ) 
	#define CAL_OpcUaServerGetNamespaceIndex pICmpOPCUAServer->IOpcUaServerGetNamespaceIndex
	#define CHK_OpcUaServerGetNamespaceIndex (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerGetNamespaceIndex  CAL_CMEXPAPI( "OpcUaServerGetNamespaceIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerGetNamespaceIndex  PFOPCUASERVERGETNAMESPACEINDEX pfOpcUaServerGetNamespaceIndex;
	#define EXT_OpcUaServerGetNamespaceIndex  extern PFOPCUASERVERGETNAMESPACEINDEX pfOpcUaServerGetNamespaceIndex;
	#define GET_OpcUaServerGetNamespaceIndex(fl)  s_pfCMGetAPI2( "OpcUaServerGetNamespaceIndex", (RTS_VOID_FCTPTR *)&pfOpcUaServerGetNamespaceIndex, (fl), 0, 0)
	#define CAL_OpcUaServerGetNamespaceIndex  pfOpcUaServerGetNamespaceIndex
	#define CHK_OpcUaServerGetNamespaceIndex  (pfOpcUaServerGetNamespaceIndex != NULL)
	#define EXP_OpcUaServerGetNamespaceIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetNamespaceIndex", (RTS_UINTPTR)OpcUaServerGetNamespaceIndex, 0, 0) 
#endif




/**
 * <description>Register a new namespace to the server. If the namespace is registerd already this index is retruned.</description>
 * <param name="pNamespace" type="IN">Namespace to register at the server.</param>
 * <result>Returns the index of the registerd namespace.</result>
 **/
OpcUa_Int16 CDECL OpcUaServerRegisterNamespace(OpcUa_String* pNamespace);
typedef OpcUa_Int16 (CDECL * PFOPCUASERVERREGISTERNAMESPACE) (OpcUa_String* pNamespace);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERREGISTERNAMESPACE_NOTIMPLEMENTED)
	#define USE_OpcUaServerRegisterNamespace
	#define EXT_OpcUaServerRegisterNamespace
	#define GET_OpcUaServerRegisterNamespace(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerRegisterNamespace(p0)  (OpcUa_Int16)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerRegisterNamespace  FALSE
	#define EXP_OpcUaServerRegisterNamespace  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerRegisterNamespace
	#define EXT_OpcUaServerRegisterNamespace
	#define GET_OpcUaServerRegisterNamespace(fl)  CAL_CMGETAPI( "OpcUaServerRegisterNamespace" ) 
	#define CAL_OpcUaServerRegisterNamespace  OpcUaServerRegisterNamespace
	#define CHK_OpcUaServerRegisterNamespace  TRUE
	#define EXP_OpcUaServerRegisterNamespace  CAL_CMEXPAPI( "OpcUaServerRegisterNamespace" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerRegisterNamespace
	#define EXT_OpcUaServerRegisterNamespace
	#define GET_OpcUaServerRegisterNamespace(fl)  CAL_CMGETAPI( "OpcUaServerRegisterNamespace" ) 
	#define CAL_OpcUaServerRegisterNamespace  OpcUaServerRegisterNamespace
	#define CHK_OpcUaServerRegisterNamespace  TRUE
	#define EXP_OpcUaServerRegisterNamespace  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterNamespace", (RTS_UINTPTR)OpcUaServerRegisterNamespace, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerRegisterNamespace
	#define EXT_CmpOPCUAServerOpcUaServerRegisterNamespace
	#define GET_CmpOPCUAServerOpcUaServerRegisterNamespace  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerRegisterNamespace pICmpOPCUAServer->IOpcUaServerRegisterNamespace
	#define CHK_CmpOPCUAServerOpcUaServerRegisterNamespace (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerRegisterNamespace  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerRegisterNamespace
	#define EXT_OpcUaServerRegisterNamespace
	#define GET_OpcUaServerRegisterNamespace(fl)  CAL_CMGETAPI( "OpcUaServerRegisterNamespace" ) 
	#define CAL_OpcUaServerRegisterNamespace pICmpOPCUAServer->IOpcUaServerRegisterNamespace
	#define CHK_OpcUaServerRegisterNamespace (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerRegisterNamespace  CAL_CMEXPAPI( "OpcUaServerRegisterNamespace" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerRegisterNamespace  PFOPCUASERVERREGISTERNAMESPACE pfOpcUaServerRegisterNamespace;
	#define EXT_OpcUaServerRegisterNamespace  extern PFOPCUASERVERREGISTERNAMESPACE pfOpcUaServerRegisterNamespace;
	#define GET_OpcUaServerRegisterNamespace(fl)  s_pfCMGetAPI2( "OpcUaServerRegisterNamespace", (RTS_VOID_FCTPTR *)&pfOpcUaServerRegisterNamespace, (fl), 0, 0)
	#define CAL_OpcUaServerRegisterNamespace  pfOpcUaServerRegisterNamespace
	#define CHK_OpcUaServerRegisterNamespace  (pfOpcUaServerRegisterNamespace != NULL)
	#define EXP_OpcUaServerRegisterNamespace  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterNamespace", (RTS_UINTPTR)OpcUaServerRegisterNamespace, 0, 0) 
#endif




/**
 * <description>Parse the index range string which is part of some OPC UA requests with arrays to a strcutred form.</description>
 * <param name="pString" type="IN">String to parse.</param>
 * <param name="pRangeArray" type="INOUT">Pointer to the arrays where to store the parsed index ranges.</param>
 * <param name="pMaxRanges" type="IN">Maximum length of the array.</param>
 * <result>Returns the index of the registerd namespace.</result>
 **/
OpcUa_StatusCode CDECL OpcUaServerParseIndexRange(const OpcUa_String *pString, NumericRange *pRangeArray, OpcUa_UInt32 *pMaxRanges);
typedef OpcUa_StatusCode (CDECL * PFOPCUASERVERPARSEINDEXRANGE) (const OpcUa_String *pString, NumericRange *pRangeArray, OpcUa_UInt32 *pMaxRanges);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERPARSEINDEXRANGE_NOTIMPLEMENTED)
	#define USE_OpcUaServerParseIndexRange
	#define EXT_OpcUaServerParseIndexRange
	#define GET_OpcUaServerParseIndexRange(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerParseIndexRange(p0,p1,p2)  (OpcUa_StatusCode)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerParseIndexRange  FALSE
	#define EXP_OpcUaServerParseIndexRange  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerParseIndexRange
	#define EXT_OpcUaServerParseIndexRange
	#define GET_OpcUaServerParseIndexRange(fl)  CAL_CMGETAPI( "OpcUaServerParseIndexRange" ) 
	#define CAL_OpcUaServerParseIndexRange  OpcUaServerParseIndexRange
	#define CHK_OpcUaServerParseIndexRange  TRUE
	#define EXP_OpcUaServerParseIndexRange  CAL_CMEXPAPI( "OpcUaServerParseIndexRange" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerParseIndexRange
	#define EXT_OpcUaServerParseIndexRange
	#define GET_OpcUaServerParseIndexRange(fl)  CAL_CMGETAPI( "OpcUaServerParseIndexRange" ) 
	#define CAL_OpcUaServerParseIndexRange  OpcUaServerParseIndexRange
	#define CHK_OpcUaServerParseIndexRange  TRUE
	#define EXP_OpcUaServerParseIndexRange  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerParseIndexRange", (RTS_UINTPTR)OpcUaServerParseIndexRange, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerParseIndexRange
	#define EXT_CmpOPCUAServerOpcUaServerParseIndexRange
	#define GET_CmpOPCUAServerOpcUaServerParseIndexRange  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerParseIndexRange pICmpOPCUAServer->IOpcUaServerParseIndexRange
	#define CHK_CmpOPCUAServerOpcUaServerParseIndexRange (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerParseIndexRange  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerParseIndexRange
	#define EXT_OpcUaServerParseIndexRange
	#define GET_OpcUaServerParseIndexRange(fl)  CAL_CMGETAPI( "OpcUaServerParseIndexRange" ) 
	#define CAL_OpcUaServerParseIndexRange pICmpOPCUAServer->IOpcUaServerParseIndexRange
	#define CHK_OpcUaServerParseIndexRange (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerParseIndexRange  CAL_CMEXPAPI( "OpcUaServerParseIndexRange" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerParseIndexRange  PFOPCUASERVERPARSEINDEXRANGE pfOpcUaServerParseIndexRange;
	#define EXT_OpcUaServerParseIndexRange  extern PFOPCUASERVERPARSEINDEXRANGE pfOpcUaServerParseIndexRange;
	#define GET_OpcUaServerParseIndexRange(fl)  s_pfCMGetAPI2( "OpcUaServerParseIndexRange", (RTS_VOID_FCTPTR *)&pfOpcUaServerParseIndexRange, (fl), 0, 0)
	#define CAL_OpcUaServerParseIndexRange  pfOpcUaServerParseIndexRange
	#define CHK_OpcUaServerParseIndexRange  (pfOpcUaServerParseIndexRange != NULL)
	#define EXP_OpcUaServerParseIndexRange  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerParseIndexRange", (RTS_UINTPTR)OpcUaServerParseIndexRange, 0, 0) 
#endif




/**
 * <description>This function returns the mininum sampling rate supported by the server.</description>
 **/
OpcUa_Double CDECL OpcUaServerGetMinimumSamplingRate(void);
typedef OpcUa_Double (CDECL * PFOPCUASERVERGETMINIMUMSAMPLINGRATE) (void);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERGETMINIMUMSAMPLINGRATE_NOTIMPLEMENTED)
	#define USE_OpcUaServerGetMinimumSamplingRate
	#define EXT_OpcUaServerGetMinimumSamplingRate
	#define GET_OpcUaServerGetMinimumSamplingRate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerGetMinimumSamplingRate()  (OpcUa_Double)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerGetMinimumSamplingRate  FALSE
	#define EXP_OpcUaServerGetMinimumSamplingRate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerGetMinimumSamplingRate
	#define EXT_OpcUaServerGetMinimumSamplingRate
	#define GET_OpcUaServerGetMinimumSamplingRate(fl)  CAL_CMGETAPI( "OpcUaServerGetMinimumSamplingRate" ) 
	#define CAL_OpcUaServerGetMinimumSamplingRate  OpcUaServerGetMinimumSamplingRate
	#define CHK_OpcUaServerGetMinimumSamplingRate  TRUE
	#define EXP_OpcUaServerGetMinimumSamplingRate  CAL_CMEXPAPI( "OpcUaServerGetMinimumSamplingRate" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerGetMinimumSamplingRate
	#define EXT_OpcUaServerGetMinimumSamplingRate
	#define GET_OpcUaServerGetMinimumSamplingRate(fl)  CAL_CMGETAPI( "OpcUaServerGetMinimumSamplingRate" ) 
	#define CAL_OpcUaServerGetMinimumSamplingRate  OpcUaServerGetMinimumSamplingRate
	#define CHK_OpcUaServerGetMinimumSamplingRate  TRUE
	#define EXP_OpcUaServerGetMinimumSamplingRate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetMinimumSamplingRate", (RTS_UINTPTR)OpcUaServerGetMinimumSamplingRate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate
	#define EXT_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate
	#define GET_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate pICmpOPCUAServer->IOpcUaServerGetMinimumSamplingRate
	#define CHK_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerGetMinimumSamplingRate
	#define EXT_OpcUaServerGetMinimumSamplingRate
	#define GET_OpcUaServerGetMinimumSamplingRate(fl)  CAL_CMGETAPI( "OpcUaServerGetMinimumSamplingRate" ) 
	#define CAL_OpcUaServerGetMinimumSamplingRate pICmpOPCUAServer->IOpcUaServerGetMinimumSamplingRate
	#define CHK_OpcUaServerGetMinimumSamplingRate (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerGetMinimumSamplingRate  CAL_CMEXPAPI( "OpcUaServerGetMinimumSamplingRate" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerGetMinimumSamplingRate  PFOPCUASERVERGETMINIMUMSAMPLINGRATE pfOpcUaServerGetMinimumSamplingRate;
	#define EXT_OpcUaServerGetMinimumSamplingRate  extern PFOPCUASERVERGETMINIMUMSAMPLINGRATE pfOpcUaServerGetMinimumSamplingRate;
	#define GET_OpcUaServerGetMinimumSamplingRate(fl)  s_pfCMGetAPI2( "OpcUaServerGetMinimumSamplingRate", (RTS_VOID_FCTPTR *)&pfOpcUaServerGetMinimumSamplingRate, (fl), 0, 0)
	#define CAL_OpcUaServerGetMinimumSamplingRate  pfOpcUaServerGetMinimumSamplingRate
	#define CHK_OpcUaServerGetMinimumSamplingRate  (pfOpcUaServerGetMinimumSamplingRate != NULL)
	#define EXP_OpcUaServerGetMinimumSamplingRate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetMinimumSamplingRate", (RTS_UINTPTR)OpcUaServerGetMinimumSamplingRate, 0, 0) 
#endif




/* Server event handling */

/**
 * <description>Registers a node defined by a provider as an event notifier. The node should have the SubscriptToEvents flags set. Since events are ordered hierarchical the parent
 * event notifier node has to be given. This function allows to notifiy the events in a performant way. The corresponding references have to be added by the provider by himself.</description>
 * <param name="pNode" type="IN">NodeId of the EventNotifier node</param>
 * <param name="pParentNotifier" type="IN">Pointer to the parent EventNotifier node. If NULL the server node will be assumed.</param>
 * <param name="pResult" type="IN">Pointer to result. 
 *      - ERR_OK if everything went fine. 
 *      - ERR_NOTIMPLEMENTED if eventing is not available in the configuration. 
 *      - ERR_DUPLICATE if the node was already registered. The handle of the original one is returned. Use OpcUaServerUnregisterEventNotifier to unregister.
 *      - ERR_FAILED if something failed.</param>
 * <result>Handle to the registered node. Has to be used by OpcUaServerFireEvent and OpcUaServerUnregisterEventNotifier</result>
 */
RTS_HANDLE CDECL OpcUaServerRegisterEventNotifier(OpcUa_NodeId* pNode, OpcUa_NodeId* pParentNotifier, RTS_RESULT* pResult);
typedef RTS_HANDLE (CDECL * PFOPCUASERVERREGISTEREVENTNOTIFIER) (OpcUa_NodeId* pNode, OpcUa_NodeId* pParentNotifier, RTS_RESULT* pResult);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERREGISTEREVENTNOTIFIER_NOTIMPLEMENTED)
	#define USE_OpcUaServerRegisterEventNotifier
	#define EXT_OpcUaServerRegisterEventNotifier
	#define GET_OpcUaServerRegisterEventNotifier(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerRegisterEventNotifier(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_OpcUaServerRegisterEventNotifier  FALSE
	#define EXP_OpcUaServerRegisterEventNotifier  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerRegisterEventNotifier
	#define EXT_OpcUaServerRegisterEventNotifier
	#define GET_OpcUaServerRegisterEventNotifier(fl)  CAL_CMGETAPI( "OpcUaServerRegisterEventNotifier" ) 
	#define CAL_OpcUaServerRegisterEventNotifier  OpcUaServerRegisterEventNotifier
	#define CHK_OpcUaServerRegisterEventNotifier  TRUE
	#define EXP_OpcUaServerRegisterEventNotifier  CAL_CMEXPAPI( "OpcUaServerRegisterEventNotifier" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerRegisterEventNotifier
	#define EXT_OpcUaServerRegisterEventNotifier
	#define GET_OpcUaServerRegisterEventNotifier(fl)  CAL_CMGETAPI( "OpcUaServerRegisterEventNotifier" ) 
	#define CAL_OpcUaServerRegisterEventNotifier  OpcUaServerRegisterEventNotifier
	#define CHK_OpcUaServerRegisterEventNotifier  TRUE
	#define EXP_OpcUaServerRegisterEventNotifier  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterEventNotifier", (RTS_UINTPTR)OpcUaServerRegisterEventNotifier, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerRegisterEventNotifier
	#define EXT_CmpOPCUAServerOpcUaServerRegisterEventNotifier
	#define GET_CmpOPCUAServerOpcUaServerRegisterEventNotifier  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerRegisterEventNotifier pICmpOPCUAServer->IOpcUaServerRegisterEventNotifier
	#define CHK_CmpOPCUAServerOpcUaServerRegisterEventNotifier (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerRegisterEventNotifier  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerRegisterEventNotifier
	#define EXT_OpcUaServerRegisterEventNotifier
	#define GET_OpcUaServerRegisterEventNotifier(fl)  CAL_CMGETAPI( "OpcUaServerRegisterEventNotifier" ) 
	#define CAL_OpcUaServerRegisterEventNotifier pICmpOPCUAServer->IOpcUaServerRegisterEventNotifier
	#define CHK_OpcUaServerRegisterEventNotifier (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerRegisterEventNotifier  CAL_CMEXPAPI( "OpcUaServerRegisterEventNotifier" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerRegisterEventNotifier  PFOPCUASERVERREGISTEREVENTNOTIFIER pfOpcUaServerRegisterEventNotifier;
	#define EXT_OpcUaServerRegisterEventNotifier  extern PFOPCUASERVERREGISTEREVENTNOTIFIER pfOpcUaServerRegisterEventNotifier;
	#define GET_OpcUaServerRegisterEventNotifier(fl)  s_pfCMGetAPI2( "OpcUaServerRegisterEventNotifier", (RTS_VOID_FCTPTR *)&pfOpcUaServerRegisterEventNotifier, (fl), 0, 0)
	#define CAL_OpcUaServerRegisterEventNotifier  pfOpcUaServerRegisterEventNotifier
	#define CHK_OpcUaServerRegisterEventNotifier  (pfOpcUaServerRegisterEventNotifier != NULL)
	#define EXP_OpcUaServerRegisterEventNotifier  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterEventNotifier", (RTS_UINTPTR)OpcUaServerRegisterEventNotifier, 0, 0) 
#endif




/**
 * <description>Unregisters an event notifier. As events are organized hierarchical the complete subtree will be removed.</description>
 * <param name="hNotifier" type="IN">Handle to the event notifier.</param>
 * <result>Result of operation. ERR_OK if everything went fine. ERR_INVALID_HANDLE if hNotifier was not a valid handle. ERR_FAILED in other cases.</result>
 */
RTS_RESULT CDECL OpcUaServerUnregisterEventNotifier(RTS_HANDLE hNotifier);
typedef RTS_RESULT (CDECL * PFOPCUASERVERUNREGISTEREVENTNOTIFIER) (RTS_HANDLE hNotifier);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERUNREGISTEREVENTNOTIFIER_NOTIMPLEMENTED)
	#define USE_OpcUaServerUnregisterEventNotifier
	#define EXT_OpcUaServerUnregisterEventNotifier
	#define GET_OpcUaServerUnregisterEventNotifier(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerUnregisterEventNotifier(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerUnregisterEventNotifier  FALSE
	#define EXP_OpcUaServerUnregisterEventNotifier  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerUnregisterEventNotifier
	#define EXT_OpcUaServerUnregisterEventNotifier
	#define GET_OpcUaServerUnregisterEventNotifier(fl)  CAL_CMGETAPI( "OpcUaServerUnregisterEventNotifier" ) 
	#define CAL_OpcUaServerUnregisterEventNotifier  OpcUaServerUnregisterEventNotifier
	#define CHK_OpcUaServerUnregisterEventNotifier  TRUE
	#define EXP_OpcUaServerUnregisterEventNotifier  CAL_CMEXPAPI( "OpcUaServerUnregisterEventNotifier" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerUnregisterEventNotifier
	#define EXT_OpcUaServerUnregisterEventNotifier
	#define GET_OpcUaServerUnregisterEventNotifier(fl)  CAL_CMGETAPI( "OpcUaServerUnregisterEventNotifier" ) 
	#define CAL_OpcUaServerUnregisterEventNotifier  OpcUaServerUnregisterEventNotifier
	#define CHK_OpcUaServerUnregisterEventNotifier  TRUE
	#define EXP_OpcUaServerUnregisterEventNotifier  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerUnregisterEventNotifier", (RTS_UINTPTR)OpcUaServerUnregisterEventNotifier, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerUnregisterEventNotifier
	#define EXT_CmpOPCUAServerOpcUaServerUnregisterEventNotifier
	#define GET_CmpOPCUAServerOpcUaServerUnregisterEventNotifier  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerUnregisterEventNotifier pICmpOPCUAServer->IOpcUaServerUnregisterEventNotifier
	#define CHK_CmpOPCUAServerOpcUaServerUnregisterEventNotifier (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerUnregisterEventNotifier  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerUnregisterEventNotifier
	#define EXT_OpcUaServerUnregisterEventNotifier
	#define GET_OpcUaServerUnregisterEventNotifier(fl)  CAL_CMGETAPI( "OpcUaServerUnregisterEventNotifier" ) 
	#define CAL_OpcUaServerUnregisterEventNotifier pICmpOPCUAServer->IOpcUaServerUnregisterEventNotifier
	#define CHK_OpcUaServerUnregisterEventNotifier (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerUnregisterEventNotifier  CAL_CMEXPAPI( "OpcUaServerUnregisterEventNotifier" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerUnregisterEventNotifier  PFOPCUASERVERUNREGISTEREVENTNOTIFIER pfOpcUaServerUnregisterEventNotifier;
	#define EXT_OpcUaServerUnregisterEventNotifier  extern PFOPCUASERVERUNREGISTEREVENTNOTIFIER pfOpcUaServerUnregisterEventNotifier;
	#define GET_OpcUaServerUnregisterEventNotifier(fl)  s_pfCMGetAPI2( "OpcUaServerUnregisterEventNotifier", (RTS_VOID_FCTPTR *)&pfOpcUaServerUnregisterEventNotifier, (fl), 0, 0)
	#define CAL_OpcUaServerUnregisterEventNotifier  pfOpcUaServerUnregisterEventNotifier
	#define CHK_OpcUaServerUnregisterEventNotifier  (pfOpcUaServerUnregisterEventNotifier != NULL)
	#define EXP_OpcUaServerUnregisterEventNotifier  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerUnregisterEventNotifier", (RTS_UINTPTR)OpcUaServerUnregisterEventNotifier, 0, 0) 
#endif




/**
 * <description>Registers a new event at the server. This function registers the event fields of the event type to fire this event.
 * This registered event is used to fire an acutual event. The fired event contains only the corresponding values. They have to have
 * the same order as registered in this function. The mandatory fields of the BaseEventType are added by default. They don't have to be set. These are:
 *  - EventType: The value will be filled up by the server. Type of the event: Datatype: OpcUa_NodeId
 *  - EventId: Unique Id of the event: Datatype: OpcUa_ByteString
 *  - SourceNode: NodeId of the event source node. Datatype: OpcUa_NodeId
 *  - SourceName: Name of the event source. Datatype: OpcUa_String
 *  - Time: UtcTimestamp when the event occured. Datatype: OpcUa_DateTime
 *  - ReceiveTime: The value will be filled up by the server. Datatype: OpcUa_DateTime.</param>
 *  - Message: Message of the event. Datatype: OpcUa_LocalizedText
 *  - Severity: Severity of the event. Datatype: OpcUa_UInt16. Range from 1 to 1000 is allowed
 * <param name="providerInterface" type="IN">Pointer to the provider which registeres this event.</param>
 * <param name="pEventTypeId" type="IN">NodeId of the event type.</param>
 * <param name="ui32NumOfFields" type="IN">Number of browse paths of the event.</param>
 * <param name="pEventFields" type="IN">Browse paths of the event fields.</param>
 * <param name="pResult" type="IN">Pointer to result. 
 *      - ERR_OK if everything went fine. 
 *      - ERR_NOTIMPLEMENTED if eventing is not available in the configuration. 
 *      - ERR_DUPLICATE if the node was already registered. The handle of the original one is returned. Use OpcUaServerUnregisterEvent to unregister.
 *      - ERR_FAILED if something failed.</param>
 * <result>Handle to the registered node. Has to be used by OpcUaServerFireEvent and OpcUaServerUnregisterEvent</result>
 */
RTS_HANDLE CDECL OpcUaServerRegisterEvent(OpcUaProvider_Info* providerInterface, OpcUa_NodeId* pEventTypeId, OpcUa_UInt32 ui32NumOfFields, OpcUaServer_BrowsePath* pEventFields, RTS_RESULT* pResult);
typedef RTS_HANDLE (CDECL * PFOPCUASERVERREGISTEREVENT) (OpcUaProvider_Info* providerInterface, OpcUa_NodeId* pEventTypeId, OpcUa_UInt32 ui32NumOfFields, OpcUaServer_BrowsePath* pEventFields, RTS_RESULT* pResult);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERREGISTEREVENT_NOTIMPLEMENTED)
	#define USE_OpcUaServerRegisterEvent
	#define EXT_OpcUaServerRegisterEvent
	#define GET_OpcUaServerRegisterEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerRegisterEvent(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_OpcUaServerRegisterEvent  FALSE
	#define EXP_OpcUaServerRegisterEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerRegisterEvent
	#define EXT_OpcUaServerRegisterEvent
	#define GET_OpcUaServerRegisterEvent(fl)  CAL_CMGETAPI( "OpcUaServerRegisterEvent" ) 
	#define CAL_OpcUaServerRegisterEvent  OpcUaServerRegisterEvent
	#define CHK_OpcUaServerRegisterEvent  TRUE
	#define EXP_OpcUaServerRegisterEvent  CAL_CMEXPAPI( "OpcUaServerRegisterEvent" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerRegisterEvent
	#define EXT_OpcUaServerRegisterEvent
	#define GET_OpcUaServerRegisterEvent(fl)  CAL_CMGETAPI( "OpcUaServerRegisterEvent" ) 
	#define CAL_OpcUaServerRegisterEvent  OpcUaServerRegisterEvent
	#define CHK_OpcUaServerRegisterEvent  TRUE
	#define EXP_OpcUaServerRegisterEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterEvent", (RTS_UINTPTR)OpcUaServerRegisterEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerRegisterEvent
	#define EXT_CmpOPCUAServerOpcUaServerRegisterEvent
	#define GET_CmpOPCUAServerOpcUaServerRegisterEvent  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerRegisterEvent pICmpOPCUAServer->IOpcUaServerRegisterEvent
	#define CHK_CmpOPCUAServerOpcUaServerRegisterEvent (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerRegisterEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerRegisterEvent
	#define EXT_OpcUaServerRegisterEvent
	#define GET_OpcUaServerRegisterEvent(fl)  CAL_CMGETAPI( "OpcUaServerRegisterEvent" ) 
	#define CAL_OpcUaServerRegisterEvent pICmpOPCUAServer->IOpcUaServerRegisterEvent
	#define CHK_OpcUaServerRegisterEvent (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerRegisterEvent  CAL_CMEXPAPI( "OpcUaServerRegisterEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerRegisterEvent  PFOPCUASERVERREGISTEREVENT pfOpcUaServerRegisterEvent;
	#define EXT_OpcUaServerRegisterEvent  extern PFOPCUASERVERREGISTEREVENT pfOpcUaServerRegisterEvent;
	#define GET_OpcUaServerRegisterEvent(fl)  s_pfCMGetAPI2( "OpcUaServerRegisterEvent", (RTS_VOID_FCTPTR *)&pfOpcUaServerRegisterEvent, (fl), 0, 0)
	#define CAL_OpcUaServerRegisterEvent  pfOpcUaServerRegisterEvent
	#define CHK_OpcUaServerRegisterEvent  (pfOpcUaServerRegisterEvent != NULL)
	#define EXP_OpcUaServerRegisterEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterEvent", (RTS_UINTPTR)OpcUaServerRegisterEvent, 0, 0) 
#endif




/**
 * <description>Unregisters an event event.</description>
 * <param name="hNotifier" type="IN">Handle to the event</param>
 * <result>Result of operation. ERR_OK if everything went fine. ERR_INVALID_HANDLE if hEvent was not a valid handle. ERR_FAILED in other cases.</result>
 */
RTS_RESULT CDECL OpcUaServerUnregisterEvent(RTS_HANDLE hEvent);
typedef RTS_RESULT (CDECL * PFOPCUASERVERUNREGISTEREVENT) (RTS_HANDLE hEvent);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERUNREGISTEREVENT_NOTIMPLEMENTED)
	#define USE_OpcUaServerUnregisterEvent
	#define EXT_OpcUaServerUnregisterEvent
	#define GET_OpcUaServerUnregisterEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerUnregisterEvent(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerUnregisterEvent  FALSE
	#define EXP_OpcUaServerUnregisterEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerUnregisterEvent
	#define EXT_OpcUaServerUnregisterEvent
	#define GET_OpcUaServerUnregisterEvent(fl)  CAL_CMGETAPI( "OpcUaServerUnregisterEvent" ) 
	#define CAL_OpcUaServerUnregisterEvent  OpcUaServerUnregisterEvent
	#define CHK_OpcUaServerUnregisterEvent  TRUE
	#define EXP_OpcUaServerUnregisterEvent  CAL_CMEXPAPI( "OpcUaServerUnregisterEvent" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerUnregisterEvent
	#define EXT_OpcUaServerUnregisterEvent
	#define GET_OpcUaServerUnregisterEvent(fl)  CAL_CMGETAPI( "OpcUaServerUnregisterEvent" ) 
	#define CAL_OpcUaServerUnregisterEvent  OpcUaServerUnregisterEvent
	#define CHK_OpcUaServerUnregisterEvent  TRUE
	#define EXP_OpcUaServerUnregisterEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerUnregisterEvent", (RTS_UINTPTR)OpcUaServerUnregisterEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerUnregisterEvent
	#define EXT_CmpOPCUAServerOpcUaServerUnregisterEvent
	#define GET_CmpOPCUAServerOpcUaServerUnregisterEvent  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerUnregisterEvent pICmpOPCUAServer->IOpcUaServerUnregisterEvent
	#define CHK_CmpOPCUAServerOpcUaServerUnregisterEvent (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerUnregisterEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerUnregisterEvent
	#define EXT_OpcUaServerUnregisterEvent
	#define GET_OpcUaServerUnregisterEvent(fl)  CAL_CMGETAPI( "OpcUaServerUnregisterEvent" ) 
	#define CAL_OpcUaServerUnregisterEvent pICmpOPCUAServer->IOpcUaServerUnregisterEvent
	#define CHK_OpcUaServerUnregisterEvent (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerUnregisterEvent  CAL_CMEXPAPI( "OpcUaServerUnregisterEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerUnregisterEvent  PFOPCUASERVERUNREGISTEREVENT pfOpcUaServerUnregisterEvent;
	#define EXT_OpcUaServerUnregisterEvent  extern PFOPCUASERVERUNREGISTEREVENT pfOpcUaServerUnregisterEvent;
	#define GET_OpcUaServerUnregisterEvent(fl)  s_pfCMGetAPI2( "OpcUaServerUnregisterEvent", (RTS_VOID_FCTPTR *)&pfOpcUaServerUnregisterEvent, (fl), 0, 0)
	#define CAL_OpcUaServerUnregisterEvent  pfOpcUaServerUnregisterEvent
	#define CHK_OpcUaServerUnregisterEvent  (pfOpcUaServerUnregisterEvent != NULL)
	#define EXP_OpcUaServerUnregisterEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerUnregisterEvent", (RTS_UINTPTR)OpcUaServerUnregisterEvent, 0, 0) 
#endif




/**
 * <description>Send an event to the OPC UA Server. This event will be transmitted to all monitored items where the monitoring parameters match to the sent event.
 * According to the OPC UA specification events are also notified to the parent event notifier nodes. By doing so the server object will receive all events. The mandatory property ReveiveTime will be set by 
 * the server automatically. This function has all required attributes of the BaseEventType as parameters. Optional attributes or attributes of derived types can be set by last three parameters.</description>
 * <param name="hNotifier" type="IN">Handle to the event notifier.</param>
 * <param name="hEvent" type="IN">Handle to the registered event.</param>
 * <param name="pValues" type="IN">Pointer to the event instance values. Must have the same order as the registered fields of hEvent.
 * Note: The mandatory event fields of the BaseEventType must be available in pValues. Since EventType and ReceiveTime are handled by the server internally these values don't have to be set in pValues.
*  Therefor the minimum number of values is 6. The following order is used, Add the additional fields after these fields:
 *  1. EventId: Unique Id of the event: Datatype: OpcUa_ByteString
 *  2. SourceNode: NodeId of the event source node. Datatype: OpcUa_NodeId
 *  3. SourceName: Name of the event source. Datatype: OpcUa_String
 *  4. Time: UtcTimestamp when the event occured. Datatype: OpcUa_UtcTime
 *  5. Message: Message of the event. Datatype: OpcUa_LocalizedText
 *  6. Severity: Severity of the event. Datatype: OpcUa_UInt16. Range from 1 to 1000 is allowed</param>
 * <result>Result of the Operation. 
 *      - ERR_OK if everything went fine. 
 *      - ERR_PARAMETER if some parameter is invalid.
 *      - ERR_INVALID_HANDLE if hNotifier or hEvent is not a valid handle.
 *      - ERR_NOTIMPLEMENTED if eventing is not supported by the OPC UA Server. 
 *      - ERR_FAILED if something went wrong.</result>
 */
RTS_RESULT CDECL OpcUaServerFireEvent(RTS_HANDLE hNotifier, RTS_HANDLE hEvent, OpcUa_Variant* pValues);
typedef RTS_RESULT (CDECL * PFOPCUASERVERFIREEVENT) (RTS_HANDLE hNotifier, RTS_HANDLE hEvent, OpcUa_Variant* pValues);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERFIREEVENT_NOTIMPLEMENTED)
	#define USE_OpcUaServerFireEvent
	#define EXT_OpcUaServerFireEvent
	#define GET_OpcUaServerFireEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerFireEvent(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerFireEvent  FALSE
	#define EXP_OpcUaServerFireEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerFireEvent
	#define EXT_OpcUaServerFireEvent
	#define GET_OpcUaServerFireEvent(fl)  CAL_CMGETAPI( "OpcUaServerFireEvent" ) 
	#define CAL_OpcUaServerFireEvent  OpcUaServerFireEvent
	#define CHK_OpcUaServerFireEvent  TRUE
	#define EXP_OpcUaServerFireEvent  CAL_CMEXPAPI( "OpcUaServerFireEvent" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerFireEvent
	#define EXT_OpcUaServerFireEvent
	#define GET_OpcUaServerFireEvent(fl)  CAL_CMGETAPI( "OpcUaServerFireEvent" ) 
	#define CAL_OpcUaServerFireEvent  OpcUaServerFireEvent
	#define CHK_OpcUaServerFireEvent  TRUE
	#define EXP_OpcUaServerFireEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerFireEvent", (RTS_UINTPTR)OpcUaServerFireEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerFireEvent
	#define EXT_CmpOPCUAServerOpcUaServerFireEvent
	#define GET_CmpOPCUAServerOpcUaServerFireEvent  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerFireEvent pICmpOPCUAServer->IOpcUaServerFireEvent
	#define CHK_CmpOPCUAServerOpcUaServerFireEvent (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerFireEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerFireEvent
	#define EXT_OpcUaServerFireEvent
	#define GET_OpcUaServerFireEvent(fl)  CAL_CMGETAPI( "OpcUaServerFireEvent" ) 
	#define CAL_OpcUaServerFireEvent pICmpOPCUAServer->IOpcUaServerFireEvent
	#define CHK_OpcUaServerFireEvent (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerFireEvent  CAL_CMEXPAPI( "OpcUaServerFireEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerFireEvent  PFOPCUASERVERFIREEVENT pfOpcUaServerFireEvent;
	#define EXT_OpcUaServerFireEvent  extern PFOPCUASERVERFIREEVENT pfOpcUaServerFireEvent;
	#define GET_OpcUaServerFireEvent(fl)  s_pfCMGetAPI2( "OpcUaServerFireEvent", (RTS_VOID_FCTPTR *)&pfOpcUaServerFireEvent, (fl), 0, 0)
	#define CAL_OpcUaServerFireEvent  pfOpcUaServerFireEvent
	#define CHK_OpcUaServerFireEvent  (pfOpcUaServerFireEvent != NULL)
	#define EXP_OpcUaServerFireEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerFireEvent", (RTS_UINTPTR)OpcUaServerFireEvent, 0, 0) 
#endif




/* Server diagnostig information */

/**
 * <description>This function returns the first available session. Use this function and 
 * OpcUaServerGetNextSession to get the initial session configuration. To get notified about 
 * changes register to the EVT_CmpOPCUAServerSessionsChanged event.</description>
 * <param name="pResult" type="OUT">Result of the operation. ERR_NOT_OBJECT if no sessions are available.</param>
 * <result>SessionId of the first session. 0xFFFFFFFF if no session is availble.</result>
 */
RTS_UI32 CDECL OpcUaServerGetFirstSession(RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFOPCUASERVERGETFIRSTSESSION) (RTS_RESULT* pResult);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERGETFIRSTSESSION_NOTIMPLEMENTED)
	#define USE_OpcUaServerGetFirstSession
	#define EXT_OpcUaServerGetFirstSession
	#define GET_OpcUaServerGetFirstSession(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerGetFirstSession(p0)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerGetFirstSession  FALSE
	#define EXP_OpcUaServerGetFirstSession  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerGetFirstSession
	#define EXT_OpcUaServerGetFirstSession
	#define GET_OpcUaServerGetFirstSession(fl)  CAL_CMGETAPI( "OpcUaServerGetFirstSession" ) 
	#define CAL_OpcUaServerGetFirstSession  OpcUaServerGetFirstSession
	#define CHK_OpcUaServerGetFirstSession  TRUE
	#define EXP_OpcUaServerGetFirstSession  CAL_CMEXPAPI( "OpcUaServerGetFirstSession" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerGetFirstSession
	#define EXT_OpcUaServerGetFirstSession
	#define GET_OpcUaServerGetFirstSession(fl)  CAL_CMGETAPI( "OpcUaServerGetFirstSession" ) 
	#define CAL_OpcUaServerGetFirstSession  OpcUaServerGetFirstSession
	#define CHK_OpcUaServerGetFirstSession  TRUE
	#define EXP_OpcUaServerGetFirstSession  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetFirstSession", (RTS_UINTPTR)OpcUaServerGetFirstSession, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerGetFirstSession
	#define EXT_CmpOPCUAServerOpcUaServerGetFirstSession
	#define GET_CmpOPCUAServerOpcUaServerGetFirstSession  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerGetFirstSession pICmpOPCUAServer->IOpcUaServerGetFirstSession
	#define CHK_CmpOPCUAServerOpcUaServerGetFirstSession (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerGetFirstSession  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerGetFirstSession
	#define EXT_OpcUaServerGetFirstSession
	#define GET_OpcUaServerGetFirstSession(fl)  CAL_CMGETAPI( "OpcUaServerGetFirstSession" ) 
	#define CAL_OpcUaServerGetFirstSession pICmpOPCUAServer->IOpcUaServerGetFirstSession
	#define CHK_OpcUaServerGetFirstSession (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerGetFirstSession  CAL_CMEXPAPI( "OpcUaServerGetFirstSession" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerGetFirstSession  PFOPCUASERVERGETFIRSTSESSION pfOpcUaServerGetFirstSession;
	#define EXT_OpcUaServerGetFirstSession  extern PFOPCUASERVERGETFIRSTSESSION pfOpcUaServerGetFirstSession;
	#define GET_OpcUaServerGetFirstSession(fl)  s_pfCMGetAPI2( "OpcUaServerGetFirstSession", (RTS_VOID_FCTPTR *)&pfOpcUaServerGetFirstSession, (fl), 0, 0)
	#define CAL_OpcUaServerGetFirstSession  pfOpcUaServerGetFirstSession
	#define CHK_OpcUaServerGetFirstSession  (pfOpcUaServerGetFirstSession != NULL)
	#define EXP_OpcUaServerGetFirstSession  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetFirstSession", (RTS_UINTPTR)OpcUaServerGetFirstSession, 0, 0) 
#endif




/**
 * <description>This function returns the next available session.</description>
 * <param name="ui32LastSessionId" type="IN">SessionID of the last session.</param>
 * <param name="pResult" type="OUT">Result of the operation. ERR_NOT_OBJECT if no sessions are available or ui32LastSession was invalid.</param>
 * <result>SessionId of the first session. 0xFFFFFFFF if no session is availble.</result>
 */
RTS_UI32 CDECL OpcUaServerGetNextSession(RTS_UI32 ui32LastSessionId, RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFOPCUASERVERGETNEXTSESSION) (RTS_UI32 ui32LastSessionId, RTS_RESULT* pResult);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERGETNEXTSESSION_NOTIMPLEMENTED)
	#define USE_OpcUaServerGetNextSession
	#define EXT_OpcUaServerGetNextSession
	#define GET_OpcUaServerGetNextSession(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerGetNextSession(p0,p1)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerGetNextSession  FALSE
	#define EXP_OpcUaServerGetNextSession  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerGetNextSession
	#define EXT_OpcUaServerGetNextSession
	#define GET_OpcUaServerGetNextSession(fl)  CAL_CMGETAPI( "OpcUaServerGetNextSession" ) 
	#define CAL_OpcUaServerGetNextSession  OpcUaServerGetNextSession
	#define CHK_OpcUaServerGetNextSession  TRUE
	#define EXP_OpcUaServerGetNextSession  CAL_CMEXPAPI( "OpcUaServerGetNextSession" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerGetNextSession
	#define EXT_OpcUaServerGetNextSession
	#define GET_OpcUaServerGetNextSession(fl)  CAL_CMGETAPI( "OpcUaServerGetNextSession" ) 
	#define CAL_OpcUaServerGetNextSession  OpcUaServerGetNextSession
	#define CHK_OpcUaServerGetNextSession  TRUE
	#define EXP_OpcUaServerGetNextSession  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetNextSession", (RTS_UINTPTR)OpcUaServerGetNextSession, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerGetNextSession
	#define EXT_CmpOPCUAServerOpcUaServerGetNextSession
	#define GET_CmpOPCUAServerOpcUaServerGetNextSession  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerGetNextSession pICmpOPCUAServer->IOpcUaServerGetNextSession
	#define CHK_CmpOPCUAServerOpcUaServerGetNextSession (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerGetNextSession  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerGetNextSession
	#define EXT_OpcUaServerGetNextSession
	#define GET_OpcUaServerGetNextSession(fl)  CAL_CMGETAPI( "OpcUaServerGetNextSession" ) 
	#define CAL_OpcUaServerGetNextSession pICmpOPCUAServer->IOpcUaServerGetNextSession
	#define CHK_OpcUaServerGetNextSession (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerGetNextSession  CAL_CMEXPAPI( "OpcUaServerGetNextSession" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerGetNextSession  PFOPCUASERVERGETNEXTSESSION pfOpcUaServerGetNextSession;
	#define EXT_OpcUaServerGetNextSession  extern PFOPCUASERVERGETNEXTSESSION pfOpcUaServerGetNextSession;
	#define GET_OpcUaServerGetNextSession(fl)  s_pfCMGetAPI2( "OpcUaServerGetNextSession", (RTS_VOID_FCTPTR *)&pfOpcUaServerGetNextSession, (fl), 0, 0)
	#define CAL_OpcUaServerGetNextSession  pfOpcUaServerGetNextSession
	#define CHK_OpcUaServerGetNextSession  (pfOpcUaServerGetNextSession != NULL)
	#define EXP_OpcUaServerGetNextSession  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetNextSession", (RTS_UINTPTR)OpcUaServerGetNextSession, 0, 0) 
#endif




/**
 * <description>This function returns details about a specific session.</description>
 * <param name="ui32SessionId" type="IN">SessionID of the session.</param>
 * <param name="OpcUaServer_Session_Information" type="INOUT">Pointer to the information structure filled up by this function.</param>
 * <result> - ERR_OK if information is complete. 
 *          - ERR_CONVERSION_INCOMPLETE if some information got lost in conversion from UTF-8 to WSTRINGs
 *          - ERR_FAILED if something failed.
 *          - ERR_NO_OBJECT if session id was invalid.</param>
 */
RTS_RESULT CDECL OpcUaServerGetSessionInfo(RTS_UI32 ui32SessionId, OpcUaServer_Session_Information* pInformation);
typedef RTS_RESULT (CDECL * PFOPCUASERVERGETSESSIONINFO) (RTS_UI32 ui32SessionId, OpcUaServer_Session_Information* pInformation);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERGETSESSIONINFO_NOTIMPLEMENTED)
	#define USE_OpcUaServerGetSessionInfo
	#define EXT_OpcUaServerGetSessionInfo
	#define GET_OpcUaServerGetSessionInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerGetSessionInfo(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerGetSessionInfo  FALSE
	#define EXP_OpcUaServerGetSessionInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerGetSessionInfo
	#define EXT_OpcUaServerGetSessionInfo
	#define GET_OpcUaServerGetSessionInfo(fl)  CAL_CMGETAPI( "OpcUaServerGetSessionInfo" ) 
	#define CAL_OpcUaServerGetSessionInfo  OpcUaServerGetSessionInfo
	#define CHK_OpcUaServerGetSessionInfo  TRUE
	#define EXP_OpcUaServerGetSessionInfo  CAL_CMEXPAPI( "OpcUaServerGetSessionInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerGetSessionInfo
	#define EXT_OpcUaServerGetSessionInfo
	#define GET_OpcUaServerGetSessionInfo(fl)  CAL_CMGETAPI( "OpcUaServerGetSessionInfo" ) 
	#define CAL_OpcUaServerGetSessionInfo  OpcUaServerGetSessionInfo
	#define CHK_OpcUaServerGetSessionInfo  TRUE
	#define EXP_OpcUaServerGetSessionInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetSessionInfo", (RTS_UINTPTR)OpcUaServerGetSessionInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerGetSessionInfo
	#define EXT_CmpOPCUAServerOpcUaServerGetSessionInfo
	#define GET_CmpOPCUAServerOpcUaServerGetSessionInfo  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerGetSessionInfo pICmpOPCUAServer->IOpcUaServerGetSessionInfo
	#define CHK_CmpOPCUAServerOpcUaServerGetSessionInfo (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerGetSessionInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerGetSessionInfo
	#define EXT_OpcUaServerGetSessionInfo
	#define GET_OpcUaServerGetSessionInfo(fl)  CAL_CMGETAPI( "OpcUaServerGetSessionInfo" ) 
	#define CAL_OpcUaServerGetSessionInfo pICmpOPCUAServer->IOpcUaServerGetSessionInfo
	#define CHK_OpcUaServerGetSessionInfo (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerGetSessionInfo  CAL_CMEXPAPI( "OpcUaServerGetSessionInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerGetSessionInfo  PFOPCUASERVERGETSESSIONINFO pfOpcUaServerGetSessionInfo;
	#define EXT_OpcUaServerGetSessionInfo  extern PFOPCUASERVERGETSESSIONINFO pfOpcUaServerGetSessionInfo;
	#define GET_OpcUaServerGetSessionInfo(fl)  s_pfCMGetAPI2( "OpcUaServerGetSessionInfo", (RTS_VOID_FCTPTR *)&pfOpcUaServerGetSessionInfo, (fl), 0, 0)
	#define CAL_OpcUaServerGetSessionInfo  pfOpcUaServerGetSessionInfo
	#define CHK_OpcUaServerGetSessionInfo  (pfOpcUaServerGetSessionInfo != NULL)
	#define EXP_OpcUaServerGetSessionInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetSessionInfo", (RTS_UINTPTR)OpcUaServerGetSessionInfo, 0, 0) 
#endif








typedef struct
{
	IBase_C *pBase;
	PFOPCUASERVERREGISTERPROVIDER IOpcUaServerRegisterProvider;
 	PFOPCUASERVERUNREGISTERPROVIDER IOpcUaServerUnRegisterProvider;
 	PFOPCUASERVERCHECKREFERENCERECURSIVE IOpcUaServerCheckReferenceRecursive;
 	PFOPCUASERVERCHECKIFREFERENCEISVALID IOpcUaServerCheckIfReferenceIsValid;
 	PFOPCUASERVERGETNAMESPACEINDEX IOpcUaServerGetNamespaceIndex;
 	PFOPCUASERVERREGISTERNAMESPACE IOpcUaServerRegisterNamespace;
 	PFOPCUASERVERPARSEINDEXRANGE IOpcUaServerParseIndexRange;
 	PFOPCUASERVERGETMINIMUMSAMPLINGRATE IOpcUaServerGetMinimumSamplingRate;
 	PFOPCUASERVERREGISTEREVENTNOTIFIER IOpcUaServerRegisterEventNotifier;
 	PFOPCUASERVERUNREGISTEREVENTNOTIFIER IOpcUaServerUnregisterEventNotifier;
 	PFOPCUASERVERREGISTEREVENT IOpcUaServerRegisterEvent;
 	PFOPCUASERVERUNREGISTEREVENT IOpcUaServerUnregisterEvent;
 	PFOPCUASERVERFIREEVENT IOpcUaServerFireEvent;
 	PFOPCUASERVERGETFIRSTSESSION IOpcUaServerGetFirstSession;
 	PFOPCUASERVERGETNEXTSESSION IOpcUaServerGetNextSession;
 	PFOPCUASERVERGETSESSIONINFO IOpcUaServerGetSessionInfo;
 } ICmpOPCUAServer_C;

#ifdef CPLUSPLUS
class ICmpOPCUAServer : public IBase
{
	public:
		virtual RTS_RESULT CDECL IOpcUaServerRegisterProvider(OpcUaProvider_Info* providerInterface) =0;
		virtual RTS_RESULT CDECL IOpcUaServerUnRegisterProvider(OpcUaProvider_Info* providerInterface) =0;
		virtual OpcUa_Boolean CDECL IOpcUaServerCheckReferenceRecursive(const OpcUa_NodeId* pRequestedReference, OpcUa_Boolean bIncludeSubtypes, const OpcUa_NodeId* pReferenceToCheck) =0;
		virtual OpcUa_StatusCode CDECL IOpcUaServerCheckIfReferenceIsValid(const OpcUa_NodeId* pRefTypeId) =0;
		virtual OpcUa_Int16 CDECL IOpcUaServerGetNamespaceIndex(OpcUa_String* pNamespace) =0;
		virtual OpcUa_Int16 CDECL IOpcUaServerRegisterNamespace(OpcUa_String* pNamespace) =0;
		virtual OpcUa_StatusCode CDECL IOpcUaServerParseIndexRange(const OpcUa_String *pString, NumericRange *pRangeArray, OpcUa_UInt32 *pMaxRanges) =0;
		virtual OpcUa_Double CDECL IOpcUaServerGetMinimumSamplingRate(void) =0;
		virtual RTS_HANDLE CDECL IOpcUaServerRegisterEventNotifier(OpcUa_NodeId* pNode, OpcUa_NodeId* pParentNotifier, RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL IOpcUaServerUnregisterEventNotifier(RTS_HANDLE hNotifier) =0;
		virtual RTS_HANDLE CDECL IOpcUaServerRegisterEvent(OpcUaProvider_Info* providerInterface, OpcUa_NodeId* pEventTypeId, OpcUa_UInt32 ui32NumOfFields, OpcUaServer_BrowsePath* pEventFields, RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL IOpcUaServerUnregisterEvent(RTS_HANDLE hEvent) =0;
		virtual RTS_RESULT CDECL IOpcUaServerFireEvent(RTS_HANDLE hNotifier, RTS_HANDLE hEvent, OpcUa_Variant* pValues) =0;
		virtual RTS_UI32 CDECL IOpcUaServerGetFirstSession(RTS_RESULT* pResult) =0;
		virtual RTS_UI32 CDECL IOpcUaServerGetNextSession(RTS_UI32 ui32LastSessionId, RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL IOpcUaServerGetSessionInfo(RTS_UI32 ui32SessionId, OpcUaServer_Session_Information* pInformation) =0;
};
	#ifndef ITF_CmpOPCUAServer
		#define ITF_CmpOPCUAServer static ICmpOPCUAServer *pICmpOPCUAServer = NULL;
	#endif
	#define EXTITF_CmpOPCUAServer
#else	/*CPLUSPLUS*/
	typedef ICmpOPCUAServer_C		ICmpOPCUAServer;
	#ifndef ITF_CmpOPCUAServer
		#define ITF_CmpOPCUAServer
	#endif
	#define EXTITF_CmpOPCUAServer
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPOPCUASERVERITF_H_*/
