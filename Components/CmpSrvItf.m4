/**
 * <interfacename>CmpSrv</interfacename>
 * <description> 
 *	Interface of the level 7 server.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpSrv')

REF_ITF(`CmpBinTagUtilItf.m4')
REF_ITF(`CmpCommunicationLibItf.m4')

/**
 * <description> 
 *	Defines the default CoDeSys layer 7 protocol. 
 * </description> 
 */
#define HEADERTAG_3S		0xCD55

/**
 * <description> 
 *	Defines the default CoDeSys encrypted layer 7 protocol. 
 * </description> 
 */
#define HEADERTAG_CRYPT		0x7557

/**
 * <description> 
 *	Defines the default safety communication layer 7 protocol.
 * </description> 
 */
#define HEADERTAG_SAFETY	0x5AF4

/**
 * <category>Service Groups</category>
 * <description> 
 *	Service groups for the layer 7 communication
 * </description> 
 */
#define SG_REPLY_PREFIX			0x0080

#define SG_INVALID				0x0000
#define SG_DEVICE				0x0001
#define SG_APPLICATION			0x0002
#define SG_MONITORING			0x0003
#define SG_VISUALISATION		0x0004
#define SG_LOG					0x0005
#define SG_SETTINGS				0x0006
#define SG_ETHERCAT				0x0007
#define SG_FILE_TRANSFER		0x0008
#define SG_IEC_VAR_ACCESS		0x0009
#define SG_COMPONENT_MANAGER	0x000A
#define SG_CMPIOMGR				0x000B
#define SG_CMPUSERMGR			0x000C
#define SG_ONLINEPARAMS			0x000D
#define SG_SOFTVISION			0x000E
#define SG_TRACE_MANAGER		0x000F
#define SG_FDT					0x0010
#define SG_PLCSHELL				0x0011
#define SG_APPLICATION_BP		0x0012
#define SG_APPLICATION_FORCE	0x0013
#define SG_REDUNDANCY			0x0014
#define	SG_VISU_AUTOTEST		0x0015
#define SG_IOLINK				0x0016
#define SG_ETCSRV				0x0017
#define SG_ALARM_MANAGER		0x0018
#define SG_PROFINET				0x0019
#define SG_SIL2					0x001A
#define SG_MONITORING2			0x001B
#define	SG_SUB_NODE_COMM		0x001C	/* e. g. used for communication to a SIL3 RTS via fieldbus */
#define	SG_CMPCODEMETER			0x001D	/* used for license transfer */
#define	SG_TREND_STORAGE		0x001E	/* access to the trend storage */
#define SG_COREDUMP				0x001F
#define SG_BACKUP				0x0020
#define SG_RUNTIME_TEST			0x0021  /* Used for test and verification of the runtime */
#define SG_X509_CERT            0x0022
#define SG_MAX_DEFINED			0x0023	/* NOTE: Must be adapted, if new service group was added! */
#define SG_MAX_RESERVED			0x00FF

/**
 * <description> 
 *	Defines some special values for session ids
 * </description> 
 */
#define SRV_SESSION_ID_EMPTY				0
#define SRV_SESSION_ID_INVALID				0x00000001
#define SRV_SESSION_ID_INITAL_REQUEST		0x00000011
#define SRV_SESSION_ID_REMOTE_VISU_CLIENT	0x00000815
#define SRV_SESSION_ID_WEBSERVER			0x0000ABCD
#define SRV_SESSION_ID_VALIDATION_BIT		0x80000000

/**
 * <category>Static defines</category>
 * <description>Number of static groups</description>
 */
 #ifndef SRV_NUM_OF_STATIC_GROUPS
	#define SRV_NUM_OF_STATIC_GROUPS		SG_MAX_DEFINED
#endif

/**
 * <category>Static defines</category>
 * <description>Max number of services that can be defined for synchronous execution</description>
 */
#ifndef SRV_NUM_OF_SYNC_SERVICES
	#define SRV_NUM_OF_SYNC_SERVICES		15
#endif

/**
 * <category>Service reply tags</category>
 * <description> 
 *	Global service reply tags
 * </description> 
 */
#define TAG_ERROR						0xFF7F
#define TAG_EXTERROR_INFO				0xFF7E
#define TAG_USER_NOTIFY					0xFF7D
#define TAG_SERVICE_RESULT				0x01


/**
 * <category>Event parameter</category>
 * <element name="ulChannelId" type="IN">Id of the channel on which the request arrived</element>
 * <element name="pHeaderTag" type="IN">Pointer to the header struct of the received request</element>
 * <element name="pduData" type="IN">References the request data (without header)</element>
 * <element name="pduSendBuffer" type="OUT">Contains the buffer (pointer and length) for the reply data</element>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Received service was completely handled.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_L7_UNKNOWNCMD">Service is unknown by the event handler.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_CALL_AGAIN">Received service will be handled asynchronously. 
 * To progress this event will be posted again for the same received service data with bFirstCall=0.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_...">Another error occured, caller will send this result in a generic error tag as reply (or close the channel).</errorcode>
 * <element name="Result" type="INOUT">IN: ERR_PENDING: Signals a repeated call for the same request. All other values represent the first call. OUT: See above.</element>
 */
typedef struct
{
	RTS_UI32 ulChannelId;
	HEADER_TAG *pHeaderTag;
	PROTOCOL_DATA_UNIT pduData;
	PROTOCOL_DATA_UNIT pduSendBuffer;
	RTS_RESULT Result;
} SERVICEHANDLER_PARAMETER;

/**
 * <category>Event parameter</category>
 * <element name="pServceHandlerParameter" type="IN">Pointer to service handler structure</element>
 */
typedef struct
{
	SERVICEHANDLER_PARAMETER *pServceHandlerParameter;
} EVTPARAM_CmpSrv;
#define EVTPARAMID_CmpSrv		0x0001
#define EVTVERSION_CmpSrv		0x0002

/* EVTVERSION_CmpSrv
0x0001: First version
0x0002: Supports now result code ERR_CALL_AGAIN for asynchronous service handlers. Event paramter structure is still the same.
*/


/**
 * <category>Events</category>
 * <description>
 *	NOTE: Every service group can be opened, as it is still provided by the server component! The corresponding
 *	event will created implicitly by the server component, if EventOpen() is called.
 *	Example:
 *		Client calls:				hEvent = CAL_EventOpen([Service group], CMPID_CmpSrv, NULL);
 *		CmpSrv created the event:	hEvent = CAL_EventCreate2([Service group], CMPID_CmpSrv, 1, NULL);	
 *
 *	ATTENTION: This feature is only available right after CH_INIT3 step!
 *
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpSrv</param>
 */

#define EVT_ExecuteOnlineService					MAKE_EVENTID(EVTCLASS_INFO, 1)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Servers register this callback function to process services of a service group. The reply to 
 *	such a request must be sent using FinishRequest.
 * </description>
 * <param name="ulChannelId" type="IN">Id of the channel on which the request arrived</param>
 * <param name="pHeaderTag" type="IN">Pointer to the header struct of the message</param>
 * <param name="pduData" type="IN">References the request data (without header)</param>
 * <param name="pduSendBuffer" type="IN">Contains the length of the buffer for the reply data, and the buffer for the replay data</param>
 * <result>
 *	Should return ERR_OK (succeeded immediatly) or ERR_PENDING (service is handled asynchronously).
 *	All other results abort the request.
 * </result>
 */
typedef RTS_RESULT (CDECL *PFServiceHandler)(RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT pduSendBuffer);

/**
 * <description>
 * <p>Obsolete: Use PFServiceHandler (above) instead. Will be removed in future versions!</p>
 *	<p>Servers register this callback function to process services of a service group. The reply to 
 *	such a request must be sent using FinishRequest.</p>
 * </description>
 * <param name="hRouter" type="IN">Obsolete parameter, should be set to RTS_INVALID_HANDLE.</param>
 * <param name="ulChannelId" type="IN">Id of the channel on which the request arrived</param>
 * <param name="pHeaderTag" type="IN">Pointer to the header struct of the message</param>
 * <param name="pduData" type="IN">References the request data (without header)</param>
 * <param name="pduSendBuffer" type="IN">Contains the length of the buffer for the reply data, and the buffer for the replay data</param>
 * <result>
 *	Should return ERR_OK (succeeded immediatly) or ERR_PENDING (service is handled asynchronously).
 *	All other results abort the request.
 * </result>
 */
typedef RTS_RESULT (CDECL *PFServiceHandler2)(RTS_HANDLE hRouter, RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT pduSendBuffer);


/**
 * <description>Obsolete: Use ServerAppHandleRequest3 instead. Will be removed in future versions!</description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`ServerAppHandleRequest',`(RTS_UI32 ulChannelId, PROTOCOL_DATA_UNIT pduRequest, PROTOCOL_DATA_UNIT pduReply)')

/**
 * <description>Obsolete: Use ServerAppHandleRequest3 instead. Will be removed in future versions!</description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`ServerAppHandleRequest2',`(RTS_HANDLE hRouter, RTS_UI32 ulChannelId, PROTOCOL_DATA_UNIT pduRequest, PROTOCOL_DATA_UNIT pduReply)')

/**
 * <description>Handle one sevice request from the communication layer below (channel server)</description>
 * <param name="ulChannelId" type="IN">Id of the channel on which the request arrived</param>
 * <param name="pduRequest" type="IN">Pointer to the request</param>
 * <param name="pduReply" type="OUT">Pointer to the request reply buffer</param>
 * <param name="bFirstCall" type="IN">0: Tells the function, if it was already called for the same request before (0) or not (1).</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Received service was completely handeled.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PENDING">Received service will be handled asynchronously, 
 * but the caller has not to take care about this anymore.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_CALL_AGAIN">Received service will be handled asynchronously. 
 * To progress this function have to be called again for the same received service data with bFirstCall=0.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_...">Another error occured, channel should be closed.</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`ServerAppHandleRequest3',`(RTS_UI32 ulChannelId, PROTOCOL_DATA_UNIT pduRequest, PROTOCOL_DATA_UNIT pduReply, RTS_UI32 bFirstCall)')

/**
 * <description>Register a handler for requests to a specific service group</description>
 * <param name="ulServiceGroup" type="IN">The service group which is handled by the provided function</param>
 * <param name="pfServiceHandler" type="IN">A handler function.</param>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerRegisterServiceHandler', `(RTS_UI32 ulServiceGroup, PFServiceHandler pfServiceHandler)')

/**
 * <description>
 * <p>Obsolete: Use ServerRegisterServiceHandler instead. Will be removed in future versions!</p>
 * <p>Register a handler for requests to a specific service group</p></description>
 * <param name="ulServiceGroup" type="IN">The service group which is handled by the provided function</param>
 * <param name="pfServiceHandler" type="IN">A handler function.</param>
 * <param name="pszRouter" type="IN">Obsolete parameter, should be set to NULL.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerRegisterServiceHandler2', `(RTS_UI32 ulServiceGroup, PFServiceHandler pfServiceHandler, char *pszRouter)')

/**
 * <description>
 * <p>Obsolete: Use ServerRegisterServiceHandler instead. Will be removed in future versions!</p>
 * <p>Register a handler for requests to a specific service group</p></description>
 * <param name="ulServiceGroup" type="IN">The service group which is handled by the provided function</param>
 * <param name="pfServiceHandler2" type="IN">A handler function.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerRegisterServiceHandler3', `(RTS_UI32 ulServiceGroup, PFServiceHandler2 pfServiceHandler2)')

/**
 * <description>Unregister a handler for requests to a specific service group</description>
 * <param name="ulServiceGroup" type="IN">The service group which is handled by the provided function</param>
 * <param name="pfServiceHandler" type="IN">A handler function.</param>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerUnRegisterServiceHandler', `(RTS_UI32 ulServiceGroup, PFServiceHandler pfServiceHandler)')

/**
 * <description>
 *	 Register a handler for requests of a specific protocol other then HEADERTAG_3S. All requests with that protocol
 *   will be sent to this handler.
 * </description>
 * <param name="usProtocolId" type="IN">The protocol id which is handled by the provided function</param>
 * <param name="pfServiceHandler" type="IN">A handler function.</param>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerRegisterProtocolHandler', `(RTS_UI16 usProtocolId, PFServiceHandler pfServiceHandler)')

/**
 * <description>
 * <p>Obsolete: Use ServerRegisterProtocolHandler instead. Will be removed in future versions!</p>
 * <p> Register a handler for requests of a specific protocol other then HEADERTAG_3S. All requests with that protocol
 *   will be sent to this handler.</p>
 * </description>
 * <param name="usProtocolId" type="IN">The protocol id which is handled by the provided function</param>
 * <param name="pfServiceHandler" type="IN">A handler function.</param>
 * <param name="pszRouter" type="IN">Obsolete parameter, should be set to NULL.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerRegisterProtocolHandler2', `(RTS_UI16 usProtocolId, PFServiceHandler pfServiceHandler, char *pszRouter)')

/**
 * <description>
 *	 Unregister a handler for requests of a specific protocol.
 * </description>
 * <param name="usProtocolId" type="IN">The protocol id which is handled by the provided function</param>
 * <param name="pfServiceHandler" type="IN">A handler function.</param>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerUnRegisterProtocolHandler', `(RTS_UI16 usProtocolId, PFServiceHandler pfServiceHandler)')

/**
 * <description>
 *   Send a reply to a request previously received by a service handler 
 * </description>
 * <param name="ulChannelId" type="IN">
 *   Id of the channel on which to answer a reply. Must be the same that was passed in to the service
 *   handler function.
 * </param>
 * <param name="pduData" type="IN"> 
 *   Contains the buffer and the length of the reply data. Buffer must be the same as the one passed in 
 *   to the service handler function, the length must not be greater then the maximum reply buffer length.
 * </param>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerFinishRequest', `(RTS_UI32 ulChannelId, PROTOCOL_DATA_UNIT pduData)')

/**
 * <description>Generates a unique session Id</description>
 * <param name="pulSessionId" type="OUT">Pointer to get back the generated session Id</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerGenerateSessionId', `(RTS_UI32 *pulSessionId)')

/** 
 * <description>
 *   Stores the session id in the channel instance.  
 * </description>
 * <param name="ulChannelHandle" type="IN">Id of the channel for which the session id should be set.</param>
 * <param name="ulSessionId" type="IN">New session id fo the channel.</param>
 * <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL', `ServerSetSessionId',`(RTS_UI32 ulChannelHandle, RTS_UI32 ulSessionId)')

/** 
 * <description>
 *   Retrieves the stored session id from the channel instance.  
 * </description>
 * <param name="ulChannelHandle" type="IN">Id of the channel for which the session id should be read.</param>
 * <param name="pulSessionId" type="OUT">Pointer to return the session id.</param>
 * <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL', `ServerGetSessionId',`(RTS_UI32 ulChannelHandle, RTS_UI32 *pulSessionId)')

/**
* <description>
*   Retrieves the number of available server channels.
*   This is equal to the max. number of clients, which can be connected at the same time.
* </description>
* <param name="pwMaxChannels" type="OUT">Number of of channels.</param>
* <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL', `ServerGetMaxChannels',`(RTS_UI16 *pwMaxChannels)')

/**
* <description>
*   Retrieves general information for the specified server channel. This function is intended for information purpoeses only.
* </description>
* <param name="ui16ChannelIndex" type="IN">Index of the channel. Allowed range: 0..MaxChannels-1.</param>
* <param name="pui32ServerState" type="OUT">State of the server channel, see category "channel server state" for CSSTATE_ values in CmpCommunicationLibItf.</param>
* <param name="pChInfoBuffer" type="INOUT">Caller allocated buffer, which is filled by the CHANNELINFO structure. If the the state is CSSTATE_FREE, no structure is returned.</param>
* <param name="psiBufferLen" type="INOUT">Pointer to the size of the buffer in bytes, returns the number of copied bytes.</param>
* <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL', `ServerGetChannelInfoByIndex',`(RTS_UI16 ui16ChannelIndex, RTS_UI32 *pui32ServerState, CHANNELINFO *pChInfoBuffer, RTS_SIZE *psiBufferLen)')

/**
*	<description>
*		Get the current status of an active channel.
*	</description>
*	<param name="wChannelHandle" type="IN">
*		Id of the channel
*	</param>
*	<param name="pusStatus" type="OUT">
*		Is set to the current progress state. The PROGRESS_xxx constants define valied values.
*	</param>
*  <param name="pbyScalingFactor" type="OUT">
*		Provides the scaling factor for pnItemsComplete and pnTotalItems. These values have been scaled
*		down by dividing them through 2^ScalingFactor
*		(i.e. they have been right shifted by ScalingFactor bits).
*  </param>
*	<param name="pnItemsComplete" type="OUT">
*		Number of items completed (eg. the number of bytes transfered).
*  </param>
* 	<param name="pnTotalItems" type="OUT">
*		Total number of item. Is set to -1 if unknown.
*  </param>
*  <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`ServerGetStatus',`(RTS_UI32 ulChannelHandle, RTS_UI16 *pusStatus, RTS_UI8 *pbyScalingFactor, RTS_I32 *pnItemsComplete, RTS_I32 *pnTotalItems)')

/**
 * <description>Set redundancy mode to enable synchronous execution of services (called by CmpRedundancy)</description>
 * <param name="bRedundant" type="IN"></param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerSetRedundancyMode', `(RTS_BOOL bRedundant)')

/**
 * <description>Set redundancy mode standby to enable session id handling for standby controller (called by CmpRedundancy)</description>
 * <param name="bRedundanyStandby" type="IN"></param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerSetRedundancyModeStandby', `(RTS_BOOL bRedundanyStandby)')

/**
 * <description>Set flag to execute online service (called by CmpRedundancy)</description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerExecuteOnlineService', `(void)')

/**
 * <description>Handle one request (called by CmpRedundancy)</description> 
 * <param name="ulChannelId" type="IN">Id of the channel on which the request arrived</param>
 * <param name="pduRequest" type="IN">Pointer to the request</param>
 * <param name="pduReply" type="OUT">Pointer to the request reply</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ServerHandleRequest', `(RTS_UI32 ulChannelId, PROTOCOL_DATA_UNIT pduRequest, PROTOCOL_DATA_UNIT pduReply)')

/**
 * <description>Get the last log entry of class LOG_USER_NOTIFY as a toplevel online service tag</description>
 * <param name="pWriter" type="IN">Pointer to the bintag writer to get the service tag</param>
 * <param name="pduSendBuffer" type="IN">Pointer to the send buffer to reset the content of the bintag writer</param>
 * <result>Error code:
 *	<ul>
 *		<li>ERR_OK: There is still an unread log entry of the type LOG_USER_NOTIFY</li>
 *		<li>ERR_NO_OBJECT: No pending log entry of the type LOG_USER_NOTIFY</li>
 *		<li>ERR_NOT_SUPPORTED: Service not supported</li>
 *	</ul>
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SrvGetUserNotificationService', `(BINTAGWRITER *pWriter, PROTOCOL_DATA_UNIT *pduSendBuffer)')

/**
 * <description>Get the last log entry of class LOG_USER_NOTIFY as a toplevel online service tag</description>
 * <param name="pWriter" type="IN">Pointer to the bintag writer to get the service tag</param>
 * <param name="pduSendBuffer" type="IN">Pointer to the send buffer to reset the content of the bintag writer</param>
 * <param name="ulTagId" type="IN">TagId to send user notify info</param>
 * <result>Error code:
 *	<ul>
 *		<li>ERR_OK: There is still an unread log entry of the type LOG_USER_NOTIFY</li>
 *		<li>ERR_NO_OBJECT: No pending log entry of the type LOG_USER_NOTIFY</li>
 *		<li>ERR_NOT_SUPPORTED: Service not supported</li>
 *	</ul>
 * </result>cmpsrv
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SrvGetUserNotificationService2', `(BINTAGWRITER *pWriter, PROTOCOL_DATA_UNIT *pduSendBuffer, unsigned long ulTagId)')

#ifdef __cplusplus
}
#endif
