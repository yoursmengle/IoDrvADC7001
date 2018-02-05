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


	
	
#ifndef _CMPSECURECHANNELITF_H_
#define _CMPSECURECHANNELITF_H_

#include "CmpStd.h"

 

 




#include "CmpCommunicationLibItf.h"

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
RTS_RESULT CDECL SecChServerHandleRequest(RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT pduRequest, PROTOCOL_DATA_UNIT pduReply, RTS_UI32 bFirstCall);
typedef RTS_RESULT (CDECL * PFSECCHSERVERHANDLEREQUEST) (RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT pduRequest, PROTOCOL_DATA_UNIT pduReply, RTS_UI32 bFirstCall);
#if defined(CMPSECURECHANNEL_NOTIMPLEMENTED) || defined(SECCHSERVERHANDLEREQUEST_NOTIMPLEMENTED)
	#define USE_SecChServerHandleRequest
	#define EXT_SecChServerHandleRequest
	#define GET_SecChServerHandleRequest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecChServerHandleRequest(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SecChServerHandleRequest  FALSE
	#define EXP_SecChServerHandleRequest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecChServerHandleRequest
	#define EXT_SecChServerHandleRequest
	#define GET_SecChServerHandleRequest(fl)  CAL_CMGETAPI( "SecChServerHandleRequest" ) 
	#define CAL_SecChServerHandleRequest  SecChServerHandleRequest
	#define CHK_SecChServerHandleRequest  TRUE
	#define EXP_SecChServerHandleRequest  CAL_CMEXPAPI( "SecChServerHandleRequest" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURECHANNEL_EXTERNAL)
	#define USE_SecChServerHandleRequest
	#define EXT_SecChServerHandleRequest
	#define GET_SecChServerHandleRequest(fl)  CAL_CMGETAPI( "SecChServerHandleRequest" ) 
	#define CAL_SecChServerHandleRequest  SecChServerHandleRequest
	#define CHK_SecChServerHandleRequest  TRUE
	#define EXP_SecChServerHandleRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerHandleRequest", (RTS_UINTPTR)SecChServerHandleRequest, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecureChannelSecChServerHandleRequest
	#define EXT_CmpSecureChannelSecChServerHandleRequest
	#define GET_CmpSecureChannelSecChServerHandleRequest  ERR_OK
	#define CAL_CmpSecureChannelSecChServerHandleRequest pICmpSecureChannel->ISecChServerHandleRequest
	#define CHK_CmpSecureChannelSecChServerHandleRequest (pICmpSecureChannel != NULL)
	#define EXP_CmpSecureChannelSecChServerHandleRequest  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecChServerHandleRequest
	#define EXT_SecChServerHandleRequest
	#define GET_SecChServerHandleRequest(fl)  CAL_CMGETAPI( "SecChServerHandleRequest" ) 
	#define CAL_SecChServerHandleRequest pICmpSecureChannel->ISecChServerHandleRequest
	#define CHK_SecChServerHandleRequest (pICmpSecureChannel != NULL)
	#define EXP_SecChServerHandleRequest  CAL_CMEXPAPI( "SecChServerHandleRequest" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecChServerHandleRequest  PFSECCHSERVERHANDLEREQUEST pfSecChServerHandleRequest;
	#define EXT_SecChServerHandleRequest  extern PFSECCHSERVERHANDLEREQUEST pfSecChServerHandleRequest;
	#define GET_SecChServerHandleRequest(fl)  s_pfCMGetAPI2( "SecChServerHandleRequest", (RTS_VOID_FCTPTR *)&pfSecChServerHandleRequest, (fl), 0, 0)
	#define CAL_SecChServerHandleRequest  pfSecChServerHandleRequest
	#define CHK_SecChServerHandleRequest  (pfSecChServerHandleRequest != NULL)
	#define EXP_SecChServerHandleRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerHandleRequest", (RTS_UINTPTR)SecChServerHandleRequest, 0, 0) 
#endif






/* -- Functions exported to the layer 6 network component. Only to be called by CmpSrv. -- */

/**
* <description>
*   Retrieves the number of available server channels.
*   This is equal to the max. number of clients, which can be connected at the same time.
* </description>
* <param name="pui16MaxChannels" type="OUT">Number of of channels.</param>
* <result>error code</result>
*/
RTS_RESULT CDECL SecChServerGetMaxChannels(RTS_UI16 *pui16MaxChannels);
typedef RTS_RESULT (CDECL * PFSECCHSERVERGETMAXCHANNELS) (RTS_UI16 *pui16MaxChannels);
#if defined(CMPSECURECHANNEL_NOTIMPLEMENTED) || defined(SECCHSERVERGETMAXCHANNELS_NOTIMPLEMENTED)
	#define USE_SecChServerGetMaxChannels
	#define EXT_SecChServerGetMaxChannels
	#define GET_SecChServerGetMaxChannels(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecChServerGetMaxChannels(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SecChServerGetMaxChannels  FALSE
	#define EXP_SecChServerGetMaxChannels  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecChServerGetMaxChannels
	#define EXT_SecChServerGetMaxChannels
	#define GET_SecChServerGetMaxChannels(fl)  CAL_CMGETAPI( "SecChServerGetMaxChannels" ) 
	#define CAL_SecChServerGetMaxChannels  SecChServerGetMaxChannels
	#define CHK_SecChServerGetMaxChannels  TRUE
	#define EXP_SecChServerGetMaxChannels  CAL_CMEXPAPI( "SecChServerGetMaxChannels" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURECHANNEL_EXTERNAL)
	#define USE_SecChServerGetMaxChannels
	#define EXT_SecChServerGetMaxChannels
	#define GET_SecChServerGetMaxChannels(fl)  CAL_CMGETAPI( "SecChServerGetMaxChannels" ) 
	#define CAL_SecChServerGetMaxChannels  SecChServerGetMaxChannels
	#define CHK_SecChServerGetMaxChannels  TRUE
	#define EXP_SecChServerGetMaxChannels  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerGetMaxChannels", (RTS_UINTPTR)SecChServerGetMaxChannels, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecureChannelSecChServerGetMaxChannels
	#define EXT_CmpSecureChannelSecChServerGetMaxChannels
	#define GET_CmpSecureChannelSecChServerGetMaxChannels  ERR_OK
	#define CAL_CmpSecureChannelSecChServerGetMaxChannels pICmpSecureChannel->ISecChServerGetMaxChannels
	#define CHK_CmpSecureChannelSecChServerGetMaxChannels (pICmpSecureChannel != NULL)
	#define EXP_CmpSecureChannelSecChServerGetMaxChannels  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecChServerGetMaxChannels
	#define EXT_SecChServerGetMaxChannels
	#define GET_SecChServerGetMaxChannels(fl)  CAL_CMGETAPI( "SecChServerGetMaxChannels" ) 
	#define CAL_SecChServerGetMaxChannels pICmpSecureChannel->ISecChServerGetMaxChannels
	#define CHK_SecChServerGetMaxChannels (pICmpSecureChannel != NULL)
	#define EXP_SecChServerGetMaxChannels  CAL_CMEXPAPI( "SecChServerGetMaxChannels" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecChServerGetMaxChannels  PFSECCHSERVERGETMAXCHANNELS pfSecChServerGetMaxChannels;
	#define EXT_SecChServerGetMaxChannels  extern PFSECCHSERVERGETMAXCHANNELS pfSecChServerGetMaxChannels;
	#define GET_SecChServerGetMaxChannels(fl)  s_pfCMGetAPI2( "SecChServerGetMaxChannels", (RTS_VOID_FCTPTR *)&pfSecChServerGetMaxChannels, (fl), 0, 0)
	#define CAL_SecChServerGetMaxChannels  pfSecChServerGetMaxChannels
	#define CHK_SecChServerGetMaxChannels  (pfSecChServerGetMaxChannels != NULL)
	#define EXP_SecChServerGetMaxChannels  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerGetMaxChannels", (RTS_UINTPTR)SecChServerGetMaxChannels, 0, 0) 
#endif




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
RTS_RESULT CDECL SecChServerGetChannelInfoByIndex(RTS_UI16 ui16ChannelIndex, RTS_UI32 *pui32ServerState, CHANNELINFO *pChInfoBuffer, RTS_SIZE *psiBufferLen);
typedef RTS_RESULT (CDECL * PFSECCHSERVERGETCHANNELINFOBYINDEX) (RTS_UI16 ui16ChannelIndex, RTS_UI32 *pui32ServerState, CHANNELINFO *pChInfoBuffer, RTS_SIZE *psiBufferLen);
#if defined(CMPSECURECHANNEL_NOTIMPLEMENTED) || defined(SECCHSERVERGETCHANNELINFOBYINDEX_NOTIMPLEMENTED)
	#define USE_SecChServerGetChannelInfoByIndex
	#define EXT_SecChServerGetChannelInfoByIndex
	#define GET_SecChServerGetChannelInfoByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecChServerGetChannelInfoByIndex(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SecChServerGetChannelInfoByIndex  FALSE
	#define EXP_SecChServerGetChannelInfoByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecChServerGetChannelInfoByIndex
	#define EXT_SecChServerGetChannelInfoByIndex
	#define GET_SecChServerGetChannelInfoByIndex(fl)  CAL_CMGETAPI( "SecChServerGetChannelInfoByIndex" ) 
	#define CAL_SecChServerGetChannelInfoByIndex  SecChServerGetChannelInfoByIndex
	#define CHK_SecChServerGetChannelInfoByIndex  TRUE
	#define EXP_SecChServerGetChannelInfoByIndex  CAL_CMEXPAPI( "SecChServerGetChannelInfoByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURECHANNEL_EXTERNAL)
	#define USE_SecChServerGetChannelInfoByIndex
	#define EXT_SecChServerGetChannelInfoByIndex
	#define GET_SecChServerGetChannelInfoByIndex(fl)  CAL_CMGETAPI( "SecChServerGetChannelInfoByIndex" ) 
	#define CAL_SecChServerGetChannelInfoByIndex  SecChServerGetChannelInfoByIndex
	#define CHK_SecChServerGetChannelInfoByIndex  TRUE
	#define EXP_SecChServerGetChannelInfoByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerGetChannelInfoByIndex", (RTS_UINTPTR)SecChServerGetChannelInfoByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecureChannelSecChServerGetChannelInfoByIndex
	#define EXT_CmpSecureChannelSecChServerGetChannelInfoByIndex
	#define GET_CmpSecureChannelSecChServerGetChannelInfoByIndex  ERR_OK
	#define CAL_CmpSecureChannelSecChServerGetChannelInfoByIndex pICmpSecureChannel->ISecChServerGetChannelInfoByIndex
	#define CHK_CmpSecureChannelSecChServerGetChannelInfoByIndex (pICmpSecureChannel != NULL)
	#define EXP_CmpSecureChannelSecChServerGetChannelInfoByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecChServerGetChannelInfoByIndex
	#define EXT_SecChServerGetChannelInfoByIndex
	#define GET_SecChServerGetChannelInfoByIndex(fl)  CAL_CMGETAPI( "SecChServerGetChannelInfoByIndex" ) 
	#define CAL_SecChServerGetChannelInfoByIndex pICmpSecureChannel->ISecChServerGetChannelInfoByIndex
	#define CHK_SecChServerGetChannelInfoByIndex (pICmpSecureChannel != NULL)
	#define EXP_SecChServerGetChannelInfoByIndex  CAL_CMEXPAPI( "SecChServerGetChannelInfoByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecChServerGetChannelInfoByIndex  PFSECCHSERVERGETCHANNELINFOBYINDEX pfSecChServerGetChannelInfoByIndex;
	#define EXT_SecChServerGetChannelInfoByIndex  extern PFSECCHSERVERGETCHANNELINFOBYINDEX pfSecChServerGetChannelInfoByIndex;
	#define GET_SecChServerGetChannelInfoByIndex(fl)  s_pfCMGetAPI2( "SecChServerGetChannelInfoByIndex", (RTS_VOID_FCTPTR *)&pfSecChServerGetChannelInfoByIndex, (fl), 0, 0)
	#define CAL_SecChServerGetChannelInfoByIndex  pfSecChServerGetChannelInfoByIndex
	#define CHK_SecChServerGetChannelInfoByIndex  (pfSecChServerGetChannelInfoByIndex != NULL)
	#define EXP_SecChServerGetChannelInfoByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerGetChannelInfoByIndex", (RTS_UINTPTR)SecChServerGetChannelInfoByIndex, 0, 0) 
#endif




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
RTS_RESULT CDECL SecChServerGetStatus(RTS_UI32 ui32ChannelHandle, RTS_UI16 *pui16Status, RTS_UI8 *pui8ScalingFactor, RTS_I32 *pi32ItemsComplete, RTS_I32 *pi32TotalItems);
typedef RTS_RESULT (CDECL * PFSECCHSERVERGETSTATUS) (RTS_UI32 ui32ChannelHandle, RTS_UI16 *pui16Status, RTS_UI8 *pui8ScalingFactor, RTS_I32 *pi32ItemsComplete, RTS_I32 *pi32TotalItems);
#if defined(CMPSECURECHANNEL_NOTIMPLEMENTED) || defined(SECCHSERVERGETSTATUS_NOTIMPLEMENTED)
	#define USE_SecChServerGetStatus
	#define EXT_SecChServerGetStatus
	#define GET_SecChServerGetStatus(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecChServerGetStatus(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SecChServerGetStatus  FALSE
	#define EXP_SecChServerGetStatus  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecChServerGetStatus
	#define EXT_SecChServerGetStatus
	#define GET_SecChServerGetStatus(fl)  CAL_CMGETAPI( "SecChServerGetStatus" ) 
	#define CAL_SecChServerGetStatus  SecChServerGetStatus
	#define CHK_SecChServerGetStatus  TRUE
	#define EXP_SecChServerGetStatus  CAL_CMEXPAPI( "SecChServerGetStatus" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURECHANNEL_EXTERNAL)
	#define USE_SecChServerGetStatus
	#define EXT_SecChServerGetStatus
	#define GET_SecChServerGetStatus(fl)  CAL_CMGETAPI( "SecChServerGetStatus" ) 
	#define CAL_SecChServerGetStatus  SecChServerGetStatus
	#define CHK_SecChServerGetStatus  TRUE
	#define EXP_SecChServerGetStatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerGetStatus", (RTS_UINTPTR)SecChServerGetStatus, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecureChannelSecChServerGetStatus
	#define EXT_CmpSecureChannelSecChServerGetStatus
	#define GET_CmpSecureChannelSecChServerGetStatus  ERR_OK
	#define CAL_CmpSecureChannelSecChServerGetStatus pICmpSecureChannel->ISecChServerGetStatus
	#define CHK_CmpSecureChannelSecChServerGetStatus (pICmpSecureChannel != NULL)
	#define EXP_CmpSecureChannelSecChServerGetStatus  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecChServerGetStatus
	#define EXT_SecChServerGetStatus
	#define GET_SecChServerGetStatus(fl)  CAL_CMGETAPI( "SecChServerGetStatus" ) 
	#define CAL_SecChServerGetStatus pICmpSecureChannel->ISecChServerGetStatus
	#define CHK_SecChServerGetStatus (pICmpSecureChannel != NULL)
	#define EXP_SecChServerGetStatus  CAL_CMEXPAPI( "SecChServerGetStatus" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecChServerGetStatus  PFSECCHSERVERGETSTATUS pfSecChServerGetStatus;
	#define EXT_SecChServerGetStatus  extern PFSECCHSERVERGETSTATUS pfSecChServerGetStatus;
	#define GET_SecChServerGetStatus(fl)  s_pfCMGetAPI2( "SecChServerGetStatus", (RTS_VOID_FCTPTR *)&pfSecChServerGetStatus, (fl), 0, 0)
	#define CAL_SecChServerGetStatus  pfSecChServerGetStatus
	#define CHK_SecChServerGetStatus  (pfSecChServerGetStatus != NULL)
	#define EXP_SecChServerGetStatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerGetStatus", (RTS_UINTPTR)SecChServerGetStatus, 0, 0) 
#endif




/**
* <description>
*   Retrieves the current request and reply buffer.
* </description>
* <param name="ui32ChannelHandle" type="IN">Id of the channel for which the session id should be read.</param>
* <param name="ppduRequest" type="INOUT">Caller allocated PDU to be filled with pointer and length of the received request.</param>
* <param name="ppduReplyBuffer" type="INOUT">Caller allocated PDU to be filled with pointer and length of the reply.</param>
* <result>error code</result>
*/
RTS_RESULT CDECL SecChServerGetRequest(RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT *ppduRequest, PROTOCOL_DATA_UNIT *ppduReplyBuffer);
typedef RTS_RESULT (CDECL * PFSECCHSERVERGETREQUEST) (RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT *ppduRequest, PROTOCOL_DATA_UNIT *ppduReplyBuffer);
#if defined(CMPSECURECHANNEL_NOTIMPLEMENTED) || defined(SECCHSERVERGETREQUEST_NOTIMPLEMENTED)
	#define USE_SecChServerGetRequest
	#define EXT_SecChServerGetRequest
	#define GET_SecChServerGetRequest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecChServerGetRequest(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SecChServerGetRequest  FALSE
	#define EXP_SecChServerGetRequest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecChServerGetRequest
	#define EXT_SecChServerGetRequest
	#define GET_SecChServerGetRequest(fl)  CAL_CMGETAPI( "SecChServerGetRequest" ) 
	#define CAL_SecChServerGetRequest  SecChServerGetRequest
	#define CHK_SecChServerGetRequest  TRUE
	#define EXP_SecChServerGetRequest  CAL_CMEXPAPI( "SecChServerGetRequest" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURECHANNEL_EXTERNAL)
	#define USE_SecChServerGetRequest
	#define EXT_SecChServerGetRequest
	#define GET_SecChServerGetRequest(fl)  CAL_CMGETAPI( "SecChServerGetRequest" ) 
	#define CAL_SecChServerGetRequest  SecChServerGetRequest
	#define CHK_SecChServerGetRequest  TRUE
	#define EXP_SecChServerGetRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerGetRequest", (RTS_UINTPTR)SecChServerGetRequest, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecureChannelSecChServerGetRequest
	#define EXT_CmpSecureChannelSecChServerGetRequest
	#define GET_CmpSecureChannelSecChServerGetRequest  ERR_OK
	#define CAL_CmpSecureChannelSecChServerGetRequest pICmpSecureChannel->ISecChServerGetRequest
	#define CHK_CmpSecureChannelSecChServerGetRequest (pICmpSecureChannel != NULL)
	#define EXP_CmpSecureChannelSecChServerGetRequest  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecChServerGetRequest
	#define EXT_SecChServerGetRequest
	#define GET_SecChServerGetRequest(fl)  CAL_CMGETAPI( "SecChServerGetRequest" ) 
	#define CAL_SecChServerGetRequest pICmpSecureChannel->ISecChServerGetRequest
	#define CHK_SecChServerGetRequest (pICmpSecureChannel != NULL)
	#define EXP_SecChServerGetRequest  CAL_CMEXPAPI( "SecChServerGetRequest" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecChServerGetRequest  PFSECCHSERVERGETREQUEST pfSecChServerGetRequest;
	#define EXT_SecChServerGetRequest  extern PFSECCHSERVERGETREQUEST pfSecChServerGetRequest;
	#define GET_SecChServerGetRequest(fl)  s_pfCMGetAPI2( "SecChServerGetRequest", (RTS_VOID_FCTPTR *)&pfSecChServerGetRequest, (fl), 0, 0)
	#define CAL_SecChServerGetRequest  pfSecChServerGetRequest
	#define CHK_SecChServerGetRequest  (pfSecChServerGetRequest != NULL)
	#define EXP_SecChServerGetRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerGetRequest", (RTS_UINTPTR)SecChServerGetRequest, 0, 0) 
#endif




/**
* <description>
*   Commits the filled reply buffer to the channel and triggers sending the reply.
* </description>
* <param name="ui32ChannelHandle" type="IN">Id of the channel for which the session id should be read.</param>
* <param name="pduData" type="IN">Pointer to the reply buffer</param>
* <result>error code</result>
*/
RTS_RESULT CDECL SecChServerFinishRequest(RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT pduData);
typedef RTS_RESULT (CDECL * PFSECCHSERVERFINISHREQUEST) (RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT pduData);
#if defined(CMPSECURECHANNEL_NOTIMPLEMENTED) || defined(SECCHSERVERFINISHREQUEST_NOTIMPLEMENTED)
	#define USE_SecChServerFinishRequest
	#define EXT_SecChServerFinishRequest
	#define GET_SecChServerFinishRequest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecChServerFinishRequest(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SecChServerFinishRequest  FALSE
	#define EXP_SecChServerFinishRequest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecChServerFinishRequest
	#define EXT_SecChServerFinishRequest
	#define GET_SecChServerFinishRequest(fl)  CAL_CMGETAPI( "SecChServerFinishRequest" ) 
	#define CAL_SecChServerFinishRequest  SecChServerFinishRequest
	#define CHK_SecChServerFinishRequest  TRUE
	#define EXP_SecChServerFinishRequest  CAL_CMEXPAPI( "SecChServerFinishRequest" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURECHANNEL_EXTERNAL)
	#define USE_SecChServerFinishRequest
	#define EXT_SecChServerFinishRequest
	#define GET_SecChServerFinishRequest(fl)  CAL_CMGETAPI( "SecChServerFinishRequest" ) 
	#define CAL_SecChServerFinishRequest  SecChServerFinishRequest
	#define CHK_SecChServerFinishRequest  TRUE
	#define EXP_SecChServerFinishRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerFinishRequest", (RTS_UINTPTR)SecChServerFinishRequest, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecureChannelSecChServerFinishRequest
	#define EXT_CmpSecureChannelSecChServerFinishRequest
	#define GET_CmpSecureChannelSecChServerFinishRequest  ERR_OK
	#define CAL_CmpSecureChannelSecChServerFinishRequest pICmpSecureChannel->ISecChServerFinishRequest
	#define CHK_CmpSecureChannelSecChServerFinishRequest (pICmpSecureChannel != NULL)
	#define EXP_CmpSecureChannelSecChServerFinishRequest  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecChServerFinishRequest
	#define EXT_SecChServerFinishRequest
	#define GET_SecChServerFinishRequest(fl)  CAL_CMGETAPI( "SecChServerFinishRequest" ) 
	#define CAL_SecChServerFinishRequest pICmpSecureChannel->ISecChServerFinishRequest
	#define CHK_SecChServerFinishRequest (pICmpSecureChannel != NULL)
	#define EXP_SecChServerFinishRequest  CAL_CMEXPAPI( "SecChServerFinishRequest" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecChServerFinishRequest  PFSECCHSERVERFINISHREQUEST pfSecChServerFinishRequest;
	#define EXT_SecChServerFinishRequest  extern PFSECCHSERVERFINISHREQUEST pfSecChServerFinishRequest;
	#define GET_SecChServerFinishRequest(fl)  s_pfCMGetAPI2( "SecChServerFinishRequest", (RTS_VOID_FCTPTR *)&pfSecChServerFinishRequest, (fl), 0, 0)
	#define CAL_SecChServerFinishRequest  pfSecChServerFinishRequest
	#define CHK_SecChServerFinishRequest  (pfSecChServerFinishRequest != NULL)
	#define EXP_SecChServerFinishRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerFinishRequest", (RTS_UINTPTR)SecChServerFinishRequest, 0, 0) 
#endif




/**
* <description>
*   Stores the session id in the channel server status structure.
* </description>
* <param name="ui32ChannelHandle" type="IN">Id of the channel for which the session id should be set.</param>
* <param name="ui32SessionId" type="IN">New session id fo the channel.</param>
* <result>error code</result>
*/
RTS_RESULT CDECL SecChServerSetSessionId(RTS_UI32 ui32ChannelHandle, RTS_UI32 ui32SessionId);
typedef RTS_RESULT (CDECL * PFSECCHSERVERSETSESSIONID) (RTS_UI32 ui32ChannelHandle, RTS_UI32 ui32SessionId);
#if defined(CMPSECURECHANNEL_NOTIMPLEMENTED) || defined(SECCHSERVERSETSESSIONID_NOTIMPLEMENTED)
	#define USE_SecChServerSetSessionId
	#define EXT_SecChServerSetSessionId
	#define GET_SecChServerSetSessionId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecChServerSetSessionId(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SecChServerSetSessionId  FALSE
	#define EXP_SecChServerSetSessionId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecChServerSetSessionId
	#define EXT_SecChServerSetSessionId
	#define GET_SecChServerSetSessionId(fl)  CAL_CMGETAPI( "SecChServerSetSessionId" ) 
	#define CAL_SecChServerSetSessionId  SecChServerSetSessionId
	#define CHK_SecChServerSetSessionId  TRUE
	#define EXP_SecChServerSetSessionId  CAL_CMEXPAPI( "SecChServerSetSessionId" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURECHANNEL_EXTERNAL)
	#define USE_SecChServerSetSessionId
	#define EXT_SecChServerSetSessionId
	#define GET_SecChServerSetSessionId(fl)  CAL_CMGETAPI( "SecChServerSetSessionId" ) 
	#define CAL_SecChServerSetSessionId  SecChServerSetSessionId
	#define CHK_SecChServerSetSessionId  TRUE
	#define EXP_SecChServerSetSessionId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerSetSessionId", (RTS_UINTPTR)SecChServerSetSessionId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecureChannelSecChServerSetSessionId
	#define EXT_CmpSecureChannelSecChServerSetSessionId
	#define GET_CmpSecureChannelSecChServerSetSessionId  ERR_OK
	#define CAL_CmpSecureChannelSecChServerSetSessionId pICmpSecureChannel->ISecChServerSetSessionId
	#define CHK_CmpSecureChannelSecChServerSetSessionId (pICmpSecureChannel != NULL)
	#define EXP_CmpSecureChannelSecChServerSetSessionId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecChServerSetSessionId
	#define EXT_SecChServerSetSessionId
	#define GET_SecChServerSetSessionId(fl)  CAL_CMGETAPI( "SecChServerSetSessionId" ) 
	#define CAL_SecChServerSetSessionId pICmpSecureChannel->ISecChServerSetSessionId
	#define CHK_SecChServerSetSessionId (pICmpSecureChannel != NULL)
	#define EXP_SecChServerSetSessionId  CAL_CMEXPAPI( "SecChServerSetSessionId" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecChServerSetSessionId  PFSECCHSERVERSETSESSIONID pfSecChServerSetSessionId;
	#define EXT_SecChServerSetSessionId  extern PFSECCHSERVERSETSESSIONID pfSecChServerSetSessionId;
	#define GET_SecChServerSetSessionId(fl)  s_pfCMGetAPI2( "SecChServerSetSessionId", (RTS_VOID_FCTPTR *)&pfSecChServerSetSessionId, (fl), 0, 0)
	#define CAL_SecChServerSetSessionId  pfSecChServerSetSessionId
	#define CHK_SecChServerSetSessionId  (pfSecChServerSetSessionId != NULL)
	#define EXP_SecChServerSetSessionId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerSetSessionId", (RTS_UINTPTR)SecChServerSetSessionId, 0, 0) 
#endif




/**
* <description>
*   Retrieves the stored session id from the channel server status structure.
* </description>
* <param name="ui32ChannelHandle" type="IN">Id of the channel for which the session id should be read.</param>
* <param name="pui32SessionId" type="OUT">Pointer to return the session id.</param>
* <result>error code</result>
*/
RTS_RESULT CDECL SecChServerGetSessionId(RTS_UI32 ui32ChannelHandle, RTS_UI32 *pui32SessionId);
typedef RTS_RESULT (CDECL * PFSECCHSERVERGETSESSIONID) (RTS_UI32 ui32ChannelHandle, RTS_UI32 *pui32SessionId);
#if defined(CMPSECURECHANNEL_NOTIMPLEMENTED) || defined(SECCHSERVERGETSESSIONID_NOTIMPLEMENTED)
	#define USE_SecChServerGetSessionId
	#define EXT_SecChServerGetSessionId
	#define GET_SecChServerGetSessionId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SecChServerGetSessionId(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SecChServerGetSessionId  FALSE
	#define EXP_SecChServerGetSessionId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SecChServerGetSessionId
	#define EXT_SecChServerGetSessionId
	#define GET_SecChServerGetSessionId(fl)  CAL_CMGETAPI( "SecChServerGetSessionId" ) 
	#define CAL_SecChServerGetSessionId  SecChServerGetSessionId
	#define CHK_SecChServerGetSessionId  TRUE
	#define EXP_SecChServerGetSessionId  CAL_CMEXPAPI( "SecChServerGetSessionId" ) 
#elif defined(MIXED_LINK) && !defined(CMPSECURECHANNEL_EXTERNAL)
	#define USE_SecChServerGetSessionId
	#define EXT_SecChServerGetSessionId
	#define GET_SecChServerGetSessionId(fl)  CAL_CMGETAPI( "SecChServerGetSessionId" ) 
	#define CAL_SecChServerGetSessionId  SecChServerGetSessionId
	#define CHK_SecChServerGetSessionId  TRUE
	#define EXP_SecChServerGetSessionId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerGetSessionId", (RTS_UINTPTR)SecChServerGetSessionId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSecureChannelSecChServerGetSessionId
	#define EXT_CmpSecureChannelSecChServerGetSessionId
	#define GET_CmpSecureChannelSecChServerGetSessionId  ERR_OK
	#define CAL_CmpSecureChannelSecChServerGetSessionId pICmpSecureChannel->ISecChServerGetSessionId
	#define CHK_CmpSecureChannelSecChServerGetSessionId (pICmpSecureChannel != NULL)
	#define EXP_CmpSecureChannelSecChServerGetSessionId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SecChServerGetSessionId
	#define EXT_SecChServerGetSessionId
	#define GET_SecChServerGetSessionId(fl)  CAL_CMGETAPI( "SecChServerGetSessionId" ) 
	#define CAL_SecChServerGetSessionId pICmpSecureChannel->ISecChServerGetSessionId
	#define CHK_SecChServerGetSessionId (pICmpSecureChannel != NULL)
	#define EXP_SecChServerGetSessionId  CAL_CMEXPAPI( "SecChServerGetSessionId" ) 
#else /* DYNAMIC_LINK */
	#define USE_SecChServerGetSessionId  PFSECCHSERVERGETSESSIONID pfSecChServerGetSessionId;
	#define EXT_SecChServerGetSessionId  extern PFSECCHSERVERGETSESSIONID pfSecChServerGetSessionId;
	#define GET_SecChServerGetSessionId(fl)  s_pfCMGetAPI2( "SecChServerGetSessionId", (RTS_VOID_FCTPTR *)&pfSecChServerGetSessionId, (fl), 0, 0)
	#define CAL_SecChServerGetSessionId  pfSecChServerGetSessionId
	#define CHK_SecChServerGetSessionId  (pfSecChServerGetSessionId != NULL)
	#define EXP_SecChServerGetSessionId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SecChServerGetSessionId", (RTS_UINTPTR)SecChServerGetSessionId, 0, 0) 
#endif





#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSECCHSERVERHANDLEREQUEST ISecChServerHandleRequest;
 	PFSECCHSERVERGETMAXCHANNELS ISecChServerGetMaxChannels;
 	PFSECCHSERVERGETCHANNELINFOBYINDEX ISecChServerGetChannelInfoByIndex;
 	PFSECCHSERVERGETSTATUS ISecChServerGetStatus;
 	PFSECCHSERVERGETREQUEST ISecChServerGetRequest;
 	PFSECCHSERVERFINISHREQUEST ISecChServerFinishRequest;
 	PFSECCHSERVERSETSESSIONID ISecChServerSetSessionId;
 	PFSECCHSERVERGETSESSIONID ISecChServerGetSessionId;
 } ICmpSecureChannel_C;

#ifdef CPLUSPLUS
class ICmpSecureChannel : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISecChServerHandleRequest(RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT pduRequest, PROTOCOL_DATA_UNIT pduReply, RTS_UI32 bFirstCall) =0;
		virtual RTS_RESULT CDECL ISecChServerGetMaxChannels(RTS_UI16 *pui16MaxChannels) =0;
		virtual RTS_RESULT CDECL ISecChServerGetChannelInfoByIndex(RTS_UI16 ui16ChannelIndex, RTS_UI32 *pui32ServerState, CHANNELINFO *pChInfoBuffer, RTS_SIZE *psiBufferLen) =0;
		virtual RTS_RESULT CDECL ISecChServerGetStatus(RTS_UI32 ui32ChannelHandle, RTS_UI16 *pui16Status, RTS_UI8 *pui8ScalingFactor, RTS_I32 *pi32ItemsComplete, RTS_I32 *pi32TotalItems) =0;
		virtual RTS_RESULT CDECL ISecChServerGetRequest(RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT *ppduRequest, PROTOCOL_DATA_UNIT *ppduReplyBuffer) =0;
		virtual RTS_RESULT CDECL ISecChServerFinishRequest(RTS_UI32 ui32ChannelHandle, PROTOCOL_DATA_UNIT pduData) =0;
		virtual RTS_RESULT CDECL ISecChServerSetSessionId(RTS_UI32 ui32ChannelHandle, RTS_UI32 ui32SessionId) =0;
		virtual RTS_RESULT CDECL ISecChServerGetSessionId(RTS_UI32 ui32ChannelHandle, RTS_UI32 *pui32SessionId) =0;
};
	#ifndef ITF_CmpSecureChannel
		#define ITF_CmpSecureChannel static ICmpSecureChannel *pICmpSecureChannel = NULL;
	#endif
	#define EXTITF_CmpSecureChannel
#else	/*CPLUSPLUS*/
	typedef ICmpSecureChannel_C		ICmpSecureChannel;
	#ifndef ITF_CmpSecureChannel
		#define ITF_CmpSecureChannel
	#endif
	#define EXTITF_CmpSecureChannel
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPSECURECHANNELITF_H_*/
