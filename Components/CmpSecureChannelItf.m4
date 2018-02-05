/**
 * <interfacename>CmpSecureChannel</interfacename>
 * <description> 
 *	Interface for a secure channel implementation to provide a secure (TLS based) channel on top of a communication channel.
 *  In the communication stack of the CODESYS runtime system the implementation of this interface
 *  can be optionally called between CmpChannelServer and CmpSrv.
 * </description>
 *
 *  SECURITY-NOTE:
 *           The security manager must be linked statically to the runtime system core to prevent, that it cannot be removed or replaced by a malware!
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpSecureChannel')

REF_ITF(`CmpCommunicationLibItf.m4')

#ifdef CMPSECURECHANNEL_EXTERNAL
	#error CmpSecureChannel must not be overloadable so defining CMPSECURECHANNEL_EXTERNAL is forbidden because of security requirements!
#endif

/**
 * <description>
 *	Security level for the programming system communication
 * </description>
 * <element name="OnlineCommMode_ONLY_PLAIN" type="OUT">Only unencrypted communication supported</element>
 * <element name="OnlineCommMode_PLAIN_AND_ENCRYPTED" type="OUT">Encrypted and unencrypted communication supported. Can be decided by the online user</element>
 * <element name="OnlineCommMode_ONLY_ENCRYPTED" type="OUT">Only encrypted communication allowed [HIGHEST SECURITY LEVEL]</element>
 */
typedef enum
{
    OnlineCommMode_ONLY_PLAIN,
    OnlineCommMode_PLAIN_AND_ENCRYPTED,
    OnlineCommMode_ONLY_ENCRYPTED
} OnlineCommMode;

/*
 * Header used for transmitting TLS related packets on the channel
 */

typedef struct
{
	RTS_UI16		ui16HeaderTag;		/* Header indicating protocol type */
	RTS_UI16		ui16HeaderLength;	/* Length of the header beginning at ulServiceLength */
	RTS_UI16		ui16ServiceGroup;	/* Not Used -> Set to 0 */
	RTS_UI16		ui16Service;		/* Not Used -> Set to 0 */
	RTS_UI32		ui32SessionID;		/* Not Used -> Set to 0 */
	RTS_UI32		ui32ServiceLength;	/* Length of the data following after this hader */
	RTS_UI32		ui32NumBlocks;		/* Number of TLS record protocol blocks following in this message */
	RTS_UI8			ui8MajorVersion;	/* Major Version of TLS protocol inside CDS */
	RTS_UI8			ui8MinorVersion;	/* Minor version of TLS protocol inside CDS */
	RTS_UI16		ui16Reserved;		/* Reserved have to be 0 */
} HEADER_TAG_CRYPT;

/**
 * <category>SecuritySettings</category>
 * <description>All security settings of the secure channel. Can be selected in CmpSecurityManager.
 *	NOTE:
 *		Security modes must be ordered in an descending sorting, that the setting with the highest security level is found at the beginning of the list!
 * </description>
 */
#define RTS_SECURITY_SETTINGS_CMPSECURECHANNEL		{ \
														{(RTS_I32)OnlineCommMode_ONLY_ENCRYPTED, 0, "OnlineCommMode_ONLY_ENCRYPTED", "Only encrypted communication allowed [HIGHEST SECURITY LEVEL]"},\
														{(RTS_I32)OnlineCommMode_PLAIN_AND_ENCRYPTED, CMPSECMAN_FLAGS_DEFAULT, "OnlineCommMode_PLAIN_AND_ENCRYPTED", "Encrypted and unencrypted communication supported. Can be decided by the online user"},\
														{(RTS_I32)OnlineCommMode_ONLY_PLAIN, 0, "OnlineCommMode_ONLY_PLAIN", "Only unencrypted communication supported"}\
													}

#define RTS_CMPSECURECHANNEL_SECURITY_ID_SERVER				0
#define RTS_CMPSECURECHANNEL_SECURITY_ID_SELFSIGNEDCERT		RTS_SECURITY_ID_SELFSIGNEDCERT


#ifdef __cplusplus
extern "C" {
#endif


/* -- Functions exported to the layer 4 network component. Only to be called by CmpChannelServer. -- */

/**
 * <description>Handle one sevice request from the communication layer below (channel server)</description>
 * <param name="ui32ChannelHandle" type="IN">Id of the channel on which the request arrived</param>
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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SecChServerHandleRequest',`(RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT pduRequest, PROTOCOL_DATA_UNIT pduReply, RTS_UI32 bFirstCall)')



/* -- Functions exported to the layer 6 network component. Only to be called by CmpSrv. -- */

/**
* <description>
*   Retrieves the number of available server channels.
*   This is equal to the max. number of clients, which can be connected at the same time.
* </description>
* <param name="pui16MaxChannels" type="OUT">Number of of channels.</param>
* <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL', `SecChServerGetMaxChannels',`(RTS_UI16 *pui16MaxChannels)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL', `SecChServerGetChannelInfoByIndex',`(RTS_UI16 ui16ChannelIndex, RTS_UI32 *pui32ServerState, CHANNELINFO *pChInfoBuffer, RTS_SIZE *psiBufferLen)')

/**
*	<description>
*		Get the current status of an active channel.
*	</description>
*	<param name="ui32ChannelHandle" type="IN">
*		Id of the channel
*	</param>
*	<param name="pui16Status" type="OUT">
*		Is set to the current progress state. The PROGRESS_xxx constants define valied values.
*	</param>
*  <param name="pui8ScalingFactor" type="OUT">
*		Provides the scaling factor for pnItemsComplete and pnTotalItems. These values have been scaled
*		down by dividing them through 2^ScalingFactor
*		(i.e. they have been right shifted by ScalingFactor bits).
*  </param>
*	<param name="pi32ItemsComplete" type="OUT">
*		Number of items completed (eg. the number of bytes transfered).
*  </param>
* 	<param name="pi32TotalItems" type="OUT">
*		Total number of item. Is set to -1 if unknown.
*  </param>
*  <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`SecChServerGetStatus',`(RTS_UI32 ui32ChannelHandle, RTS_UI16 *pui16Status, RTS_UI8 *pui8ScalingFactor, RTS_I32 *pi32ItemsComplete, RTS_I32 *pi32TotalItems)')

/**
* <description>
*   Retrieves the current request and reply buffer.
* </description>
* <param name="ui32ChannelHandle" type="IN">Id of the channel for which the session id should be read.</param>
* <param name="ppduRequest" type="INOUT">Caller allocated PDU to be filled with pointer and length of the received request.</param>
* <param name="ppduReplyBuffer" type="INOUT">Caller allocated PDU to be filled with pointer and length of the reply.</param>
* <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL', `SecChServerGetRequest',`(RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT *ppduRequest, PROTOCOL_DATA_UNIT *ppduReplyBuffer)')

/**
* <description>
*   Commits the filled reply buffer to the channel and triggers sending the reply.
* </description>
* <param name="ui32ChannelHandle" type="IN">Id of the channel for which the session id should be read.</param>
* <param name="pduData" type="IN">Pointer to the reply buffer</param>
* <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL', `SecChServerFinishRequest',`(RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT pduData)')

/**
* <description>
*   Stores the session id in the channel server status structure.
* </description>
* <param name="ui32ChannelHandle" type="IN">Id of the channel for which the session id should be set.</param>
* <param name="ui32SessionId" type="IN">New session id fo the channel.</param>
* <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL', `SecChServerSetSessionId',`(RTS_UI32 ui32ChannelHandle, RTS_UI32 ui32SessionId)')

/**
* <description>
*   Retrieves the stored session id from the channel server status structure.
* </description>
* <param name="ui32ChannelHandle" type="IN">Id of the channel for which the session id should be read.</param>
* <param name="pui32SessionId" type="OUT">Pointer to return the session id.</param>
* <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL', `SecChServerGetSessionId',`(RTS_UI32 ui32ChannelHandle, RTS_UI32 *pui32SessionId)')


#ifdef __cplusplus
}
#endif
