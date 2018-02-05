/**
 * <interfacename>CmpOPCUAServer</interfacename>
 * <description></description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpOPCUAServer')
REF_ITF(`CmpOPCUAProviderItf.m4')
REF_ITF(`CmpSecurityManagerItf.m4')
REF_ITF(`CmpEventMgrItf.m4')

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
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

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

DEF_API(`void',`CDECL',`opcuaservergetfirstsession',`(opcuaservergetfirstsession_struct *p)',1,0xACB7E0DC,0x03050C00)

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

DEF_API(`void',`CDECL',`opcuaservergetnextsession',`(opcuaservergetnextsession_struct *p)',1,0xE2BBF24A,0x03050C00)

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

DEF_API(`void',`CDECL',`opcuaservergetsessioninfo',`(opcuaservergetsessioninfo_struct *p)',1,0x6AE85AE6,0x03050C00)

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`OpcUaServerRegisterProvider',`(OpcUaProvider_Info* providerInterface)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`OpcUaServerUnRegisterProvider',`(OpcUaProvider_Info* providerInterface)')

/**
 * <description>Check if to follow OPCU UA referencetype ID. Since referenctype IDs may are derived only the server who knows all IDs can check this.</description>
 * <param name="pRequestedReference" type="IN">The referencetype ID the client requested.</param>
 * <param name="bIncludeSubtypes" type="IN">The flag if subtypes should be followed too. Set by the client.</param>
 * <param name="pReferenceToCheck" type="IN">The referencetype ID the compare against. Usually the referencetype ID of the current node (e.g. while browsing) in the adress space.</param>
 * <result>The function returns OpcUa_True if following the referencetype ID is allowd. OpcUa_False is returned otherwhise.</result>
 **/
DEF_ITF_API(`OpcUa_Boolean',`CDECL',`OpcUaServerCheckReferenceRecursive',`(const OpcUa_NodeId* pRequestedReference, OpcUa_Boolean bIncludeSubtypes, const OpcUa_NodeId* pReferenceToCheck)')

/**
 * <description>This funtion checks if a referencetype ID is valid.</description>
 * <param name="pRefTypeId" type="IN">Referecetype ID to check.</param>
 * <result>Returns either OpcUa_Good or OpcUa_BadRefereceTypeIdInvalid.</result>
 **/
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaServerCheckIfReferenceIsValid',`(const OpcUa_NodeId* pRefTypeId)')

/**
 * <description>Get the namespace index of the given namespace. Do not relay on constant referencetype IDs. They may depend on the registration order of different providers.</description>
 * <param name="pNamespace" type="IN">The namespace of intrest.</param>
 * <result>-1: If the namespace is not registerd yet. index: The index of the namespace. This does not change while the server is running.</result>
 **/
DEF_ITF_API(`OpcUa_Int16',`CDECL',`OpcUaServerGetNamespaceIndex',`(OpcUa_String* pNamespace)')

/**
 * <description>Register a new namespace to the server. If the namespace is registerd already this index is retruned.</description>
 * <param name="pNamespace" type="IN">Namespace to register at the server.</param>
 * <result>Returns the index of the registerd namespace.</result>
 **/
DEF_ITF_API(`OpcUa_Int16',`CDECL',`OpcUaServerRegisterNamespace',`(OpcUa_String* pNamespace)')

/**
 * <description>Parse the index range string which is part of some OPC UA requests with arrays to a strcutred form.</description>
 * <param name="pString" type="IN">String to parse.</param>
 * <param name="pRangeArray" type="INOUT">Pointer to the arrays where to store the parsed index ranges.</param>
 * <param name="pMaxRanges" type="IN">Maximum length of the array.</param>
 * <result>Returns the index of the registerd namespace.</result>
 **/
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaServerParseIndexRange',`(const OpcUa_String *pString, NumericRange *pRangeArray, OpcUa_UInt32 *pMaxRanges)')

/**
 * <description>This function returns the mininum sampling rate supported by the server.</description>
 **/
DEF_ITF_API(`OpcUa_Double',`CDECL',`OpcUaServerGetMinimumSamplingRate',`(void)')

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
DEF_ITF_API(`RTS_HANDLE',`CDECL',`OpcUaServerRegisterEventNotifier',`(OpcUa_NodeId* pNode, OpcUa_NodeId* pParentNotifier, RTS_RESULT* pResult)')

/**
 * <description>Unregisters an event notifier. As events are organized hierarchical the complete subtree will be removed.</description>
 * <param name="hNotifier" type="IN">Handle to the event notifier.</param>
 * <result>Result of operation. ERR_OK if everything went fine. ERR_INVALID_HANDLE if hNotifier was not a valid handle. ERR_FAILED in other cases.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`OpcUaServerUnregisterEventNotifier',`(RTS_HANDLE hNotifier)')

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
DEF_ITF_API(`RTS_HANDLE',`CDECL',`OpcUaServerRegisterEvent',`(OpcUaProvider_Info* providerInterface, OpcUa_NodeId* pEventTypeId, OpcUa_UInt32 ui32NumOfFields, OpcUaServer_BrowsePath* pEventFields, RTS_RESULT* pResult)')

/**
 * <description>Unregisters an event event.</description>
 * <param name="hNotifier" type="IN">Handle to the event</param>
 * <result>Result of operation. ERR_OK if everything went fine. ERR_INVALID_HANDLE if hEvent was not a valid handle. ERR_FAILED in other cases.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`OpcUaServerUnregisterEvent',`(RTS_HANDLE hEvent)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`OpcUaServerFireEvent',`(RTS_HANDLE hNotifier, RTS_HANDLE hEvent, OpcUa_Variant* pValues)')

/* Server diagnostig information */

/**
 * <description>This function returns the first available session. Use this function and 
 * OpcUaServerGetNextSession to get the initial session configuration. To get notified about 
 * changes register to the EVT_CmpOPCUAServerSessionsChanged event.</description>
 * <param name="pResult" type="OUT">Result of the operation. ERR_NOT_OBJECT if no sessions are available.</param>
 * <result>SessionId of the first session. 0xFFFFFFFF if no session is availble.</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`OpcUaServerGetFirstSession',`(RTS_RESULT* pResult)')

/**
 * <description>This function returns the next available session.</description>
 * <param name="ui32LastSessionId" type="IN">SessionID of the last session.</param>
 * <param name="pResult" type="OUT">Result of the operation. ERR_NOT_OBJECT if no sessions are available or ui32LastSession was invalid.</param>
 * <result>SessionId of the first session. 0xFFFFFFFF if no session is availble.</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`OpcUaServerGetNextSession',`(RTS_UI32 ui32LastSessionId, RTS_RESULT* pResult)')

/**
 * <description>This function returns details about a specific session.</description>
 * <param name="ui32SessionId" type="IN">SessionID of the session.</param>
 * <param name="OpcUaServer_Session_Information" type="INOUT">Pointer to the information structure filled up by this function.</param>
 * <result> - ERR_OK if information is complete. 
 *          - ERR_CONVERSION_INCOMPLETE if some information got lost in conversion from UTF-8 to WSTRINGs
 *          - ERR_FAILED if something failed.
 *          - ERR_NO_OBJECT if session id was invalid.</param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`OpcUaServerGetSessionInfo',`(RTS_UI32 ui32SessionId, OpcUaServer_Session_Information* pInformation)')


