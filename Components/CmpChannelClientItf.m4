/**
 * <interfacename>CmpChannelClient</interfacename>
 * <description>
 *	Interface for the channel client.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpChannelClient')

REF_ITF(`CmpChannelMgrItf.m4')
REF_ITF(`CmpChannelClientAppItf.m4')

#ifdef __EXTERNAL_DECL
#	undef __EXTERNAL_DECL
#endif

#ifdef CM_EXTERNAL_USE_DEFINITION
#	define __EXTERNAL_DECL extern
#else
#	define __EXTERNAL_DECL
#endif


/* -- Functions exported to the application -- */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *   Request a new channel to node addrReceiver . This function is executed asynchronously.
 *   To get the result of this call use NetClientOpenChannelResult.
 * </description>
 * <param name="addrReceiver" type="IN">  Open a channel to this node </param>
 * <param name="dwCommBufferSize" type="IN">  Requested size of the communication buffer </param>
 * <param name="pdwReqId" type="OUT"> 
 *   Set to a unique request id. Use this id in NetClientOpenChannelResult to 
 *   determine the result of this call.
 * </param>
 * <result>
 *   <ul>
 *     <li>ERR_OK, if the channel has been established</li>
 *     <li>ERR_PENDING, if the function hasn't completed yet. </li>
 *     <li>ERR_NOBUFFER, if we're low on memory.</li>
 *     <li>ERR_CHC_NUMCHANNELS, 
 *         if buffers for an additional channel are not available. Possibly a smaller 
 *		   communication buffer could work. Also, this error condition might be 
 *         temporarily and could change if memory is freed elsewhere.
 *     </li>
 *   </ul>
 * </result>
*/
DEF_ITF_API(`int',`CDECL',`NetClientOpenChannel',`(PEERADDRESS addrReceiver, RTS_UI32 dwCommBufferSize, RTS_UI32 *pdwReqId)')

/** 
 * <description>
 *   Get the result of a NetClientOpenChannel request. 
 * </description>
 *
 * <param name="dwRequestId" type="IN">  The request id assigned by the NetClientOpenChannel request.</param>
 * <param name="pwChannelHandle" type="OUT"> Identifies the newly created channel.</param>
 * <param name="pdwCommBufferSize" type="OUT"> The communication buffer used for this channel.</param>
 * <param name="pbBigEndianByteOrder" type="OUT">
 *		True if the target system uses big endian byte order. Since that is typically used by motorola processors 
 *      (PowerPC etc.), it sometimes is also  referred to as "Motorola Byteorder" 
 * </param>
 *
 * <result>
 *  ERR_OK,      channel has been established
 * 	ERR_PENDING, is still in progress
 *	ERR_FAILED,  channel could not be created
 * </result>
*/
DEF_ITF_API(`int',`CDECL',`NetClientOpenChannelResult',`(RTS_UI32 dwRequestId, unsigned short *pwChannelHandle, RTS_UI32 *pdwCommBufferSize, RTS_BOOL *pbBigEndianByteOrder)')

/**
 * <description>
 *   Close a channel. This function is executed synchronously 
 * </description>
 * <param name="wChannelHandle" type="IN"> Handle to the channel </param>
 * <result>
 *   An error code, if the handle could not be closed.
 * </result>
*/
DEF_ITF_API(`int',`CDECL',`NetClientCloseChannel',`(unsigned short wChannelHandle)')

/**
 *  <description>
 *    Send a message.
 *    This call will fail, if
 *     - the channel is not in send mode
 *	   - the channel is already sending
 *     - the size of the data is greater then the commbuffersize returned by NetClientOpenChannel
 *  </description>
 *
 *	<param name="wChannelHandle" type="IN"> Handle to a channel as returned by NetClientOpenChannel</param>
 *  <param name="pduData" type="IN"> 
 *    The data to be sent. The buffer pointed to by pduData may not be changed
 *    until the package has been sent completely.
 *  </param>
*/ 
DEF_ITF_API(`int',`CDECL',`NetClientSend',`(unsigned short wChannelHandle, PROTOCOL_DATA_UNIT pduData)')

/**
 *	<description>
 *		Get the current status of an active channel.
 *	</description>
 *	<param name="wChannelHandle" type="IN"> 
 *		Handle to a channel as returned by NetClientOpenChannel
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
DEF_ITF_API(`RTS_RESULT',`CDECL',`NetClientGetStatus',`(unsigned short wChannelHandle, RTS_UI16 *pusStatus, RTS_UI8 *pbyScalingFactor, RTS_I32 *pnItemsComplete, RTS_I32 *pnTotalItems)')

/* -- Functions exported to the L4Base network component -- */

/* <description>
 *   Get the buffer for the specified channel id. 
 *
 *   NOTE:
 *   After usage the channelbuffer MUST be released by
 *   calling NetServerReleaseChannel. Failing to do so will prevent the channel
 *   from being closed and the server will eventually run out of channels.
 *   Nevertheless, this function DOES NOT provide exclusive access to the channel.
 *   The L4Base component must use appropriate semaphores to ensure exclusive access.
 * </description>
 * <param name="addrPeer" type="IN"> The second endpoint of the channel. </param>
 * <param name="wChannelId" type="IN"> The id of the channel. </param>
 * <param name="ppChBuffer" type="OUT"> Is set to the channelbuffer, if the channel exists. </param>
 **/
DEF_ITF_API(`int',`CDECL',`NetClientGetChannel',`(PEERADDRESS addrPeer, unsigned short wChannelId, CHANNELBUFFER **ppChBuffer)')

/**
 * <description>
 *   Release a channel buffer returned by NetServerGetChannel. This buffer may not be used
 *   after calling this function. Use NetServerGetChannel to acquire access to this channel again.
 * </description>
 *
 * <param name="pChBuffer" type="IN">The channel buffer to release</param>
*/
DEF_ITF_API(`int',`CDECL',`NetClientReleaseChannel',`(CHANNELBUFFER *pChBuffer)')

/**
 * <description>
 *   Called by the L4Base component each time a meta-response arrives. 
 * </description>
 * <param name="addrSender" type="IN">The sender of the response</param>
 * <param name="pduData" type="IN">The response itself</param>
*/
DEF_ITF_API(`int',`CDECL',`NetClientHandleMetaResponse',`(RTS_HANDLE hRouter, PEERADDRESS addrSender, PROTOCOL_DATA_UNIT pduData)')

/**
 * <description>
 *   Calls the pfChannelHandler once for each active server channel 
 * </description>
 * <param name="pfChannelHandler" type="IN"> Function to be called for each channel </param>
 * <param name="pParam" type="INOUT"> This param is passed to pfChannelHandler. </param>
*/
DEF_ITF_API(`void',`CDECL',`NetClientForEachChannel',`(PFCHANNELHANDLER pfChannelHandler, void * pParam)')

/**
 * <description>
 *   Called by the L4Base component whenever a complete L7 message arrived on a client channel 
 * </description>
 *  <param name="wChannelId" type="IN"></param> 
 *  <param name="addrSender" type="IN">Sender of the message</param>
 *   <param name="pduData" type="IN">Content of the message. The client must copy the contents of the message
 *                     before sending the next message, since the data pointed to by pData will
 *                     be valid only until the next message has been sent or the channel is closed.</param>
 */
DEF_ITF_API(`int',`CDECL',`NetClientMessageReceived',`(CHANNELBUFFER *pChBuffer, PROTOCOL_DATA_UNIT pduData)')

/**
 * <description>
 *   Called when a unrecoverable error occurs for pfChBuffer, eg. ERR_CHANNEL_BROKEN.
 *   The channel must be closed by the net client.
 * </description>
 *	<param name="pChBuffer" type="IN"></param>
 *	<param name="nError" type="IN">The error</param>
*/
DEF_ITF_API(`int',`CDECL',`NetClientChannelError',`(CHANNELBUFFER *pChBuffer, int nError)')

/**
 * <description>Function to register a handler interface</description>
 * <param name="wChannelHandle" type="IN">Channel handle that was retrieved by NetClientOpenChannel</param>
 * <param name="pIChannelClientApp" type="IN">Interface pointer</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NetClientRegisterAppInterface',`(unsigned short wChannelHandle, ICmpChannelClientApp *pIChannelClientApp)')

/**
 * <description>Function to register a handler interface</description>
 * <param name="wChannelHandle" type="IN">Channel handle that was retrieved by NetClientOpenChannel</param>
 * <param name="pIChannelClientApp" type="IN">Interface pointer</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NetClientUnregisterAppInterface',`(unsigned short wChannelHandle, ICmpChannelClientApp *pIChannelClientApp)')

#ifdef __cplusplus
}
#endif
