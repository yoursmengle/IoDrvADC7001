/**
 * <interfacename>CmpChannelClientApp</interfacename>
 * <description>
 *	Interface for the client application to be exported to the NetClient component.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpChannelClientApp')

REF_ITF(`CmpCommunicationLibItf.m4')

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *   Called when a layer4 message has been received.
 * </description>
 * <param name="hInstance" type="IN">Handle to the instance</param>
 * <param name="wChannelHandle" type="IN">The channel that received the message</param>
 * <param name="pduData" type="IN">The message that has been received</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`int',`CDECL',`ClientAppHandleMessage',`(RTS_HANDLE hInstance, unsigned short wChannelHandle, PROTOCOL_DATA_UNIT pduData)')

/**
 * <description>
 *   Called by the NetClient component when a channel is closed by the server or a 
 *   communication error occurs. 
 *   This function is not called when the channel is closed by a call to NetClientCloseChannel.
 * </description>
 * <param name="hInstance" type="IN">Handle to the instance</param>
 * <param name="wChannelHandle" type="IN">The closed channel</param>
 * <param name="nError" type="IN">The cause why the channel is closed</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`int',`CDECL',`ClientAppOnChannelError',`(RTS_HANDLE hInstance, unsigned short wChannelHandle, int nError)')

#ifdef __cplusplus
}
#endif
