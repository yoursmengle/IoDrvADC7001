 /**
 * <description>
 *  <p>
 *	Interface for the channel server.
 *  </p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPCHANNELSERVERITF_H_
#define _CMPCHANNELSERVERITF_H_

#include "CmpStd.h"

 

 




#include "CmpChannelMgrItf.h"
#include "CmpEventMgrItf.h"


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Defines the available overall amount of memory to be used by all channels.
 *	Since each channel needs separate send and receive buffers for each channel the available 
 *  communication buffer per channel is BUFFERSIZE / (2*MAXCHANNELS).
 * </description>
 */
#define CHANNELSERVERKEY_INT_BUFFERSIZE								"BufferSize"
#define CHANNELSERVERVALUE_INT_BUFFERSIZE_DEFAULT					NETSERVER_BUFFERSIZE

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Number of communciation channels (concurrently client connections).  
 * </description>
 */
#define CHANNELSERVERKEY_INT_MAXCHANNELS							"MaxChannels"
#define CHANNELSERVERVALUE_INT_MAXCHANNELS_DEFAULT					NETSERVER_MAXCHANNELS


/* -- Events triggered by the channel server. -- */

/**
 * <category>Event parameter</category>
 * <element name="ulChannelHandle" type="IN">
 *   The channelhandle is always a combination of two words (16 bit).
 *   The low word (ulChannelHandle masked with 0xFFFF) is the id of 
 *   the "physical" channel. The highword is the id of the client using this channel
 *   (multiple clients may use the same channel in a round robbin manner).
 *   A highword of 0xFFFF indicates, that the channel is completely closed
 *   and all clients have disconnected. In all other cases the channel is still
 *   open, only that client has disconnected.
 *   When attaching any resources to a specific channel (eg. open files, logins, ...)
 *   the component should release the resource when the client detaches as
 *   well as release all clients resources when the channel is completely closed.
 * </element>
 * <element name="errReason" type="IN">
 *	  An error code describing the reason for closing the channel 
 * </element>
 */
typedef struct
{
	RTS_UI32   ulChannelHandle;
	RTS_RESULT  errReason;
} EVTPARAM_CmpChS_ChannelClosed;
#define EVTPARAMID_CmpChS_ChannelClosed 0x0001
#define EVTVERSION_CmpChS_ChannelClosed 0x0001

/* Used for compatability reasons */
typedef EVTPARAM_CmpChS_ChannelClosed EVTPARAM_ChannelClosed;
#define EVTPARAMID_CmpChannelServer EVTPARAMID_CmpChS_ChannelClosed
#define EVTVERSION_CmpChannelServer EVTVERSION_CmpChS_ChannelClosed

/**
 * <category>Event parameter</category>
 * <element name="ulChannelHandle" type="IN">
 *   The channelhandle is always a combination of two words (16 bit).
 *   The low word (ulChannelHandle masked with 0xFFFF) is the id of 
 *   the "physical" channel. The highword is the id of the client using this channel
 *   (multiple clients may use the same channel in a round robbin manner).
 *   A highword of 0xFFFF indicates, that the channel is completely closed
 *   and all clients have disconnected. In all other cases the channel is still
 *   open, only that client has disconnected.
 *   When attaching any resources to a specific channel (eg. open files, logins, ...)
 *   the component should release the resource when the client detaches as
 *   well as release all clients resources when the channel is completely closed.
 * </element>
 */
typedef struct
{
	RTS_UI32   ulChannelHandle;
} EVTPARAM_CmpChS_ChannelOpened;
#define EVTPARAMID_CmpChS_ChannelOpened 0x0002
#define EVTVERSION_CmpChS_ChannelOpened 0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when a channel is closed.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpChS_ChannelClosed</param>
 */
#define EVT_ChSChannelClosed	MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent when a channel is closed.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpChS_ChannelOpened</param>
 */
#define EVT_ChSChannelOpened	MAKE_EVENTID(EVTCLASS_INFO, 2)

/* -- Functions exported to the runtime system -- */

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * <description>
 *   Retrieves the number of available server channels. 
 *   This is equal to the max. number of clients, which can be connected at the same time.  
 * </description>
 * <param name="pwMaxChannels" type="OUT">Number of of channels.</param>
 * <result>error code</result>
*/
RTS_RESULT CDECL NetServerGetMaxChannels(RTS_UI16 *pwMaxChannels);
typedef RTS_RESULT (CDECL * PFNETSERVERGETMAXCHANNELS) (RTS_UI16 *pwMaxChannels);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERGETMAXCHANNELS_NOTIMPLEMENTED)
	#define USE_NetServerGetMaxChannels
	#define EXT_NetServerGetMaxChannels
	#define GET_NetServerGetMaxChannels(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerGetMaxChannels(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_NetServerGetMaxChannels  FALSE
	#define EXP_NetServerGetMaxChannels  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerGetMaxChannels
	#define EXT_NetServerGetMaxChannels
	#define GET_NetServerGetMaxChannels(fl)  CAL_CMGETAPI( "NetServerGetMaxChannels" ) 
	#define CAL_NetServerGetMaxChannels  NetServerGetMaxChannels
	#define CHK_NetServerGetMaxChannels  TRUE
	#define EXP_NetServerGetMaxChannels  CAL_CMEXPAPI( "NetServerGetMaxChannels" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerGetMaxChannels
	#define EXT_NetServerGetMaxChannels
	#define GET_NetServerGetMaxChannels(fl)  CAL_CMGETAPI( "NetServerGetMaxChannels" ) 
	#define CAL_NetServerGetMaxChannels  NetServerGetMaxChannels
	#define CHK_NetServerGetMaxChannels  TRUE
	#define EXP_NetServerGetMaxChannels  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetMaxChannels", (RTS_UINTPTR)NetServerGetMaxChannels, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerGetMaxChannels
	#define EXT_CmpChannelServerNetServerGetMaxChannels
	#define GET_CmpChannelServerNetServerGetMaxChannels  ERR_OK
	#define CAL_CmpChannelServerNetServerGetMaxChannels pICmpChannelServer->INetServerGetMaxChannels
	#define CHK_CmpChannelServerNetServerGetMaxChannels (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerGetMaxChannels  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerGetMaxChannels
	#define EXT_NetServerGetMaxChannels
	#define GET_NetServerGetMaxChannels(fl)  CAL_CMGETAPI( "NetServerGetMaxChannels" ) 
	#define CAL_NetServerGetMaxChannels pICmpChannelServer->INetServerGetMaxChannels
	#define CHK_NetServerGetMaxChannels (pICmpChannelServer != NULL)
	#define EXP_NetServerGetMaxChannels  CAL_CMEXPAPI( "NetServerGetMaxChannels" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerGetMaxChannels  PFNETSERVERGETMAXCHANNELS pfNetServerGetMaxChannels;
	#define EXT_NetServerGetMaxChannels  extern PFNETSERVERGETMAXCHANNELS pfNetServerGetMaxChannels;
	#define GET_NetServerGetMaxChannels(fl)  s_pfCMGetAPI2( "NetServerGetMaxChannels", (RTS_VOID_FCTPTR *)&pfNetServerGetMaxChannels, (fl), 0, 0)
	#define CAL_NetServerGetMaxChannels  pfNetServerGetMaxChannels
	#define CHK_NetServerGetMaxChannels  (pfNetServerGetMaxChannels != NULL)
	#define EXP_NetServerGetMaxChannels  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetMaxChannels", (RTS_UINTPTR)NetServerGetMaxChannels, 0, 0) 
#endif




/**
* <description>
*   Retrieves the max. size of the send and receive buffer of the communication channels. 
*   This size cannot be exceeded by any online service or service reply.
* </description>
* <param name="pi32MaxChannelBufferSize" type="OUT">Max. size of each communication buffer.</param>
* <result>error code</result>
*/
RTS_RESULT CDECL NetServerGetMaxChannelBufferSize(RTS_I32 *pi32MaxChannelBufferSize);
typedef RTS_RESULT (CDECL * PFNETSERVERGETMAXCHANNELBUFFERSIZE) (RTS_I32 *pi32MaxChannelBufferSize);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERGETMAXCHANNELBUFFERSIZE_NOTIMPLEMENTED)
	#define USE_NetServerGetMaxChannelBufferSize
	#define EXT_NetServerGetMaxChannelBufferSize
	#define GET_NetServerGetMaxChannelBufferSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerGetMaxChannelBufferSize(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_NetServerGetMaxChannelBufferSize  FALSE
	#define EXP_NetServerGetMaxChannelBufferSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerGetMaxChannelBufferSize
	#define EXT_NetServerGetMaxChannelBufferSize
	#define GET_NetServerGetMaxChannelBufferSize(fl)  CAL_CMGETAPI( "NetServerGetMaxChannelBufferSize" ) 
	#define CAL_NetServerGetMaxChannelBufferSize  NetServerGetMaxChannelBufferSize
	#define CHK_NetServerGetMaxChannelBufferSize  TRUE
	#define EXP_NetServerGetMaxChannelBufferSize  CAL_CMEXPAPI( "NetServerGetMaxChannelBufferSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerGetMaxChannelBufferSize
	#define EXT_NetServerGetMaxChannelBufferSize
	#define GET_NetServerGetMaxChannelBufferSize(fl)  CAL_CMGETAPI( "NetServerGetMaxChannelBufferSize" ) 
	#define CAL_NetServerGetMaxChannelBufferSize  NetServerGetMaxChannelBufferSize
	#define CHK_NetServerGetMaxChannelBufferSize  TRUE
	#define EXP_NetServerGetMaxChannelBufferSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetMaxChannelBufferSize", (RTS_UINTPTR)NetServerGetMaxChannelBufferSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerGetMaxChannelBufferSize
	#define EXT_CmpChannelServerNetServerGetMaxChannelBufferSize
	#define GET_CmpChannelServerNetServerGetMaxChannelBufferSize  ERR_OK
	#define CAL_CmpChannelServerNetServerGetMaxChannelBufferSize pICmpChannelServer->INetServerGetMaxChannelBufferSize
	#define CHK_CmpChannelServerNetServerGetMaxChannelBufferSize (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerGetMaxChannelBufferSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerGetMaxChannelBufferSize
	#define EXT_NetServerGetMaxChannelBufferSize
	#define GET_NetServerGetMaxChannelBufferSize(fl)  CAL_CMGETAPI( "NetServerGetMaxChannelBufferSize" ) 
	#define CAL_NetServerGetMaxChannelBufferSize pICmpChannelServer->INetServerGetMaxChannelBufferSize
	#define CHK_NetServerGetMaxChannelBufferSize (pICmpChannelServer != NULL)
	#define EXP_NetServerGetMaxChannelBufferSize  CAL_CMEXPAPI( "NetServerGetMaxChannelBufferSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerGetMaxChannelBufferSize  PFNETSERVERGETMAXCHANNELBUFFERSIZE pfNetServerGetMaxChannelBufferSize;
	#define EXT_NetServerGetMaxChannelBufferSize  extern PFNETSERVERGETMAXCHANNELBUFFERSIZE pfNetServerGetMaxChannelBufferSize;
	#define GET_NetServerGetMaxChannelBufferSize(fl)  s_pfCMGetAPI2( "NetServerGetMaxChannelBufferSize", (RTS_VOID_FCTPTR *)&pfNetServerGetMaxChannelBufferSize, (fl), 0, 0)
	#define CAL_NetServerGetMaxChannelBufferSize  pfNetServerGetMaxChannelBufferSize
	#define CHK_NetServerGetMaxChannelBufferSize  (pfNetServerGetMaxChannelBufferSize != NULL)
	#define EXP_NetServerGetMaxChannelBufferSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetMaxChannelBufferSize", (RTS_UINTPTR)NetServerGetMaxChannelBufferSize, 0, 0) 
#endif




/** 
 * <description>
 *   OBSOLETE: Function will be removed in future versions!!! Use NetServerGetChannelInfoByIndex2 instead. 
 *   Retrieves general information for the specified server channel. This function is intended for information purpoeses only.
 * </description>
 * <param name="ui16ChannelIndex" type="IN">Index of the channel. Allowed range: 0..MaxChannels-1.</param>
 * <param name="pui32ServerState" type="OUT">State of the server channel, see category "channel server state" for CSSTATE_ values in CmpCommunicationLibItf.</param>
 * <param name="pChInfoBuffer" type="INOUT">Caller allocated buffer, to which the content of the internal channel buffer structure is copied to.</param>
 * <param name="psiBufferLen" type="INOUT">Pointer to the size of the buffer in bytes, returns the number of copied bytes.</param>
 * <result>error code</result>
*/
RTS_RESULT CDECL NetServerGetChannelInfoByIndex(RTS_UI16 ui16ChannelIndex, RTS_UI32 *pui32ServerState, CHANNELBUFFER *pChInfoBuffer, RTS_SIZE *psiBufferLen);
typedef RTS_RESULT (CDECL * PFNETSERVERGETCHANNELINFOBYINDEX) (RTS_UI16 ui16ChannelIndex, RTS_UI32 *pui32ServerState, CHANNELBUFFER *pChInfoBuffer, RTS_SIZE *psiBufferLen);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERGETCHANNELINFOBYINDEX_NOTIMPLEMENTED)
	#define USE_NetServerGetChannelInfoByIndex
	#define EXT_NetServerGetChannelInfoByIndex
	#define GET_NetServerGetChannelInfoByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerGetChannelInfoByIndex(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_NetServerGetChannelInfoByIndex  FALSE
	#define EXP_NetServerGetChannelInfoByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerGetChannelInfoByIndex
	#define EXT_NetServerGetChannelInfoByIndex
	#define GET_NetServerGetChannelInfoByIndex(fl)  CAL_CMGETAPI( "NetServerGetChannelInfoByIndex" ) 
	#define CAL_NetServerGetChannelInfoByIndex  NetServerGetChannelInfoByIndex
	#define CHK_NetServerGetChannelInfoByIndex  TRUE
	#define EXP_NetServerGetChannelInfoByIndex  CAL_CMEXPAPI( "NetServerGetChannelInfoByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerGetChannelInfoByIndex
	#define EXT_NetServerGetChannelInfoByIndex
	#define GET_NetServerGetChannelInfoByIndex(fl)  CAL_CMGETAPI( "NetServerGetChannelInfoByIndex" ) 
	#define CAL_NetServerGetChannelInfoByIndex  NetServerGetChannelInfoByIndex
	#define CHK_NetServerGetChannelInfoByIndex  TRUE
	#define EXP_NetServerGetChannelInfoByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetChannelInfoByIndex", (RTS_UINTPTR)NetServerGetChannelInfoByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerGetChannelInfoByIndex
	#define EXT_CmpChannelServerNetServerGetChannelInfoByIndex
	#define GET_CmpChannelServerNetServerGetChannelInfoByIndex  ERR_OK
	#define CAL_CmpChannelServerNetServerGetChannelInfoByIndex pICmpChannelServer->INetServerGetChannelInfoByIndex
	#define CHK_CmpChannelServerNetServerGetChannelInfoByIndex (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerGetChannelInfoByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerGetChannelInfoByIndex
	#define EXT_NetServerGetChannelInfoByIndex
	#define GET_NetServerGetChannelInfoByIndex(fl)  CAL_CMGETAPI( "NetServerGetChannelInfoByIndex" ) 
	#define CAL_NetServerGetChannelInfoByIndex pICmpChannelServer->INetServerGetChannelInfoByIndex
	#define CHK_NetServerGetChannelInfoByIndex (pICmpChannelServer != NULL)
	#define EXP_NetServerGetChannelInfoByIndex  CAL_CMEXPAPI( "NetServerGetChannelInfoByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerGetChannelInfoByIndex  PFNETSERVERGETCHANNELINFOBYINDEX pfNetServerGetChannelInfoByIndex;
	#define EXT_NetServerGetChannelInfoByIndex  extern PFNETSERVERGETCHANNELINFOBYINDEX pfNetServerGetChannelInfoByIndex;
	#define GET_NetServerGetChannelInfoByIndex(fl)  s_pfCMGetAPI2( "NetServerGetChannelInfoByIndex", (RTS_VOID_FCTPTR *)&pfNetServerGetChannelInfoByIndex, (fl), 0, 0)
	#define CAL_NetServerGetChannelInfoByIndex  pfNetServerGetChannelInfoByIndex
	#define CHK_NetServerGetChannelInfoByIndex  (pfNetServerGetChannelInfoByIndex != NULL)
	#define EXP_NetServerGetChannelInfoByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetChannelInfoByIndex", (RTS_UINTPTR)NetServerGetChannelInfoByIndex, 0, 0) 
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
RTS_RESULT CDECL NetServerGetChannelInfoByIndex2(RTS_UI16 ui16ChannelIndex, RTS_UI32 *pui32ServerState, CHANNELINFO *pChInfoBuffer, RTS_SIZE *psiBufferLen);
typedef RTS_RESULT (CDECL * PFNETSERVERGETCHANNELINFOBYINDEX2) (RTS_UI16 ui16ChannelIndex, RTS_UI32 *pui32ServerState, CHANNELINFO *pChInfoBuffer, RTS_SIZE *psiBufferLen);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERGETCHANNELINFOBYINDEX2_NOTIMPLEMENTED)
	#define USE_NetServerGetChannelInfoByIndex2
	#define EXT_NetServerGetChannelInfoByIndex2
	#define GET_NetServerGetChannelInfoByIndex2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerGetChannelInfoByIndex2(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_NetServerGetChannelInfoByIndex2  FALSE
	#define EXP_NetServerGetChannelInfoByIndex2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerGetChannelInfoByIndex2
	#define EXT_NetServerGetChannelInfoByIndex2
	#define GET_NetServerGetChannelInfoByIndex2(fl)  CAL_CMGETAPI( "NetServerGetChannelInfoByIndex2" ) 
	#define CAL_NetServerGetChannelInfoByIndex2  NetServerGetChannelInfoByIndex2
	#define CHK_NetServerGetChannelInfoByIndex2  TRUE
	#define EXP_NetServerGetChannelInfoByIndex2  CAL_CMEXPAPI( "NetServerGetChannelInfoByIndex2" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerGetChannelInfoByIndex2
	#define EXT_NetServerGetChannelInfoByIndex2
	#define GET_NetServerGetChannelInfoByIndex2(fl)  CAL_CMGETAPI( "NetServerGetChannelInfoByIndex2" ) 
	#define CAL_NetServerGetChannelInfoByIndex2  NetServerGetChannelInfoByIndex2
	#define CHK_NetServerGetChannelInfoByIndex2  TRUE
	#define EXP_NetServerGetChannelInfoByIndex2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetChannelInfoByIndex2", (RTS_UINTPTR)NetServerGetChannelInfoByIndex2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerGetChannelInfoByIndex2
	#define EXT_CmpChannelServerNetServerGetChannelInfoByIndex2
	#define GET_CmpChannelServerNetServerGetChannelInfoByIndex2  ERR_OK
	#define CAL_CmpChannelServerNetServerGetChannelInfoByIndex2 pICmpChannelServer->INetServerGetChannelInfoByIndex2
	#define CHK_CmpChannelServerNetServerGetChannelInfoByIndex2 (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerGetChannelInfoByIndex2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerGetChannelInfoByIndex2
	#define EXT_NetServerGetChannelInfoByIndex2
	#define GET_NetServerGetChannelInfoByIndex2(fl)  CAL_CMGETAPI( "NetServerGetChannelInfoByIndex2" ) 
	#define CAL_NetServerGetChannelInfoByIndex2 pICmpChannelServer->INetServerGetChannelInfoByIndex2
	#define CHK_NetServerGetChannelInfoByIndex2 (pICmpChannelServer != NULL)
	#define EXP_NetServerGetChannelInfoByIndex2  CAL_CMEXPAPI( "NetServerGetChannelInfoByIndex2" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerGetChannelInfoByIndex2  PFNETSERVERGETCHANNELINFOBYINDEX2 pfNetServerGetChannelInfoByIndex2;
	#define EXT_NetServerGetChannelInfoByIndex2  extern PFNETSERVERGETCHANNELINFOBYINDEX2 pfNetServerGetChannelInfoByIndex2;
	#define GET_NetServerGetChannelInfoByIndex2(fl)  s_pfCMGetAPI2( "NetServerGetChannelInfoByIndex2", (RTS_VOID_FCTPTR *)&pfNetServerGetChannelInfoByIndex2, (fl), 0, 0)
	#define CAL_NetServerGetChannelInfoByIndex2  pfNetServerGetChannelInfoByIndex2
	#define CHK_NetServerGetChannelInfoByIndex2  (pfNetServerGetChannelInfoByIndex2 != NULL)
	#define EXP_NetServerGetChannelInfoByIndex2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetChannelInfoByIndex2", (RTS_UINTPTR)NetServerGetChannelInfoByIndex2, 0, 0) 
#endif




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
RTS_RESULT CDECL NetServerGetStatus(RTS_UI32 ulChannelHandle, RTS_UI16 *pusStatus, RTS_UI8 *pbyScalingFactor, RTS_I32 *pnItemsComplete, RTS_I32 *pnTotalItems);
typedef RTS_RESULT (CDECL * PFNETSERVERGETSTATUS) (RTS_UI32 ulChannelHandle, RTS_UI16 *pusStatus, RTS_UI8 *pbyScalingFactor, RTS_I32 *pnItemsComplete, RTS_I32 *pnTotalItems);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERGETSTATUS_NOTIMPLEMENTED)
	#define USE_NetServerGetStatus
	#define EXT_NetServerGetStatus
	#define GET_NetServerGetStatus(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerGetStatus(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_NetServerGetStatus  FALSE
	#define EXP_NetServerGetStatus  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerGetStatus
	#define EXT_NetServerGetStatus
	#define GET_NetServerGetStatus(fl)  CAL_CMGETAPI( "NetServerGetStatus" ) 
	#define CAL_NetServerGetStatus  NetServerGetStatus
	#define CHK_NetServerGetStatus  TRUE
	#define EXP_NetServerGetStatus  CAL_CMEXPAPI( "NetServerGetStatus" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerGetStatus
	#define EXT_NetServerGetStatus
	#define GET_NetServerGetStatus(fl)  CAL_CMGETAPI( "NetServerGetStatus" ) 
	#define CAL_NetServerGetStatus  NetServerGetStatus
	#define CHK_NetServerGetStatus  TRUE
	#define EXP_NetServerGetStatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetStatus", (RTS_UINTPTR)NetServerGetStatus, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerGetStatus
	#define EXT_CmpChannelServerNetServerGetStatus
	#define GET_CmpChannelServerNetServerGetStatus  ERR_OK
	#define CAL_CmpChannelServerNetServerGetStatus pICmpChannelServer->INetServerGetStatus
	#define CHK_CmpChannelServerNetServerGetStatus (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerGetStatus  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerGetStatus
	#define EXT_NetServerGetStatus
	#define GET_NetServerGetStatus(fl)  CAL_CMGETAPI( "NetServerGetStatus" ) 
	#define CAL_NetServerGetStatus pICmpChannelServer->INetServerGetStatus
	#define CHK_NetServerGetStatus (pICmpChannelServer != NULL)
	#define EXP_NetServerGetStatus  CAL_CMEXPAPI( "NetServerGetStatus" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerGetStatus  PFNETSERVERGETSTATUS pfNetServerGetStatus;
	#define EXT_NetServerGetStatus  extern PFNETSERVERGETSTATUS pfNetServerGetStatus;
	#define GET_NetServerGetStatus(fl)  s_pfCMGetAPI2( "NetServerGetStatus", (RTS_VOID_FCTPTR *)&pfNetServerGetStatus, (fl), 0, 0)
	#define CAL_NetServerGetStatus  pfNetServerGetStatus
	#define CHK_NetServerGetStatus  (pfNetServerGetStatus != NULL)
	#define EXP_NetServerGetStatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetStatus", (RTS_UINTPTR)NetServerGetStatus, 0, 0) 
#endif




/**
* <description>
*   Retrieves the current request and reply buffer.
* </description>
* <param name="ulChannelHandle" type="IN">Id of the channel for which the session id should be read.</param>
* <param name="ppduRequest" type="INOUT">Caller allocated PDU to be filled with pointer and length of the received request.</param>
* <param name="ppduReplyBuffer" type="INOUT">Caller allocated PDU to be filled with pointer and length of the reply.</param>
* <result>error code</result>
*/
RTS_RESULT CDECL NetServerGetRequest(RTS_UI32 ulChannelHandle, PROTOCOL_DATA_UNIT * ppduRequest, PROTOCOL_DATA_UNIT * ppduReplyBuffer);
typedef RTS_RESULT (CDECL * PFNETSERVERGETREQUEST) (RTS_UI32 ulChannelHandle, PROTOCOL_DATA_UNIT * ppduRequest, PROTOCOL_DATA_UNIT * ppduReplyBuffer);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERGETREQUEST_NOTIMPLEMENTED)
	#define USE_NetServerGetRequest
	#define EXT_NetServerGetRequest
	#define GET_NetServerGetRequest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerGetRequest(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_NetServerGetRequest  FALSE
	#define EXP_NetServerGetRequest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerGetRequest
	#define EXT_NetServerGetRequest
	#define GET_NetServerGetRequest(fl)  CAL_CMGETAPI( "NetServerGetRequest" ) 
	#define CAL_NetServerGetRequest  NetServerGetRequest
	#define CHK_NetServerGetRequest  TRUE
	#define EXP_NetServerGetRequest  CAL_CMEXPAPI( "NetServerGetRequest" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerGetRequest
	#define EXT_NetServerGetRequest
	#define GET_NetServerGetRequest(fl)  CAL_CMGETAPI( "NetServerGetRequest" ) 
	#define CAL_NetServerGetRequest  NetServerGetRequest
	#define CHK_NetServerGetRequest  TRUE
	#define EXP_NetServerGetRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetRequest", (RTS_UINTPTR)NetServerGetRequest, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerGetRequest
	#define EXT_CmpChannelServerNetServerGetRequest
	#define GET_CmpChannelServerNetServerGetRequest  ERR_OK
	#define CAL_CmpChannelServerNetServerGetRequest pICmpChannelServer->INetServerGetRequest
	#define CHK_CmpChannelServerNetServerGetRequest (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerGetRequest  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerGetRequest
	#define EXT_NetServerGetRequest
	#define GET_NetServerGetRequest(fl)  CAL_CMGETAPI( "NetServerGetRequest" ) 
	#define CAL_NetServerGetRequest pICmpChannelServer->INetServerGetRequest
	#define CHK_NetServerGetRequest (pICmpChannelServer != NULL)
	#define EXP_NetServerGetRequest  CAL_CMEXPAPI( "NetServerGetRequest" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerGetRequest  PFNETSERVERGETREQUEST pfNetServerGetRequest;
	#define EXT_NetServerGetRequest  extern PFNETSERVERGETREQUEST pfNetServerGetRequest;
	#define GET_NetServerGetRequest(fl)  s_pfCMGetAPI2( "NetServerGetRequest", (RTS_VOID_FCTPTR *)&pfNetServerGetRequest, (fl), 0, 0)
	#define CAL_NetServerGetRequest  pfNetServerGetRequest
	#define CHK_NetServerGetRequest  (pfNetServerGetRequest != NULL)
	#define EXP_NetServerGetRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetRequest", (RTS_UINTPTR)NetServerGetRequest, 0, 0) 
#endif




/**
* <description>
*   Commits the filled reply buffer to the channel and triggers sending the reply.
* </description>
* <param name="ulChannelHandle" type="IN">Id of the channel for which the session id should be read.</param>
* <param name="pduData" type="IN">Pointer to the reply buffer</param>
* <result>error code</result>
*/
RTS_RESULT CDECL NetServerFinishRequest(RTS_UI32 ulChannelHandle, PROTOCOL_DATA_UNIT pduData);
typedef RTS_RESULT (CDECL * PFNETSERVERFINISHREQUEST) (RTS_UI32 ulChannelHandle, PROTOCOL_DATA_UNIT pduData);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERFINISHREQUEST_NOTIMPLEMENTED)
	#define USE_NetServerFinishRequest
	#define EXT_NetServerFinishRequest
	#define GET_NetServerFinishRequest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerFinishRequest(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_NetServerFinishRequest  FALSE
	#define EXP_NetServerFinishRequest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerFinishRequest
	#define EXT_NetServerFinishRequest
	#define GET_NetServerFinishRequest(fl)  CAL_CMGETAPI( "NetServerFinishRequest" ) 
	#define CAL_NetServerFinishRequest  NetServerFinishRequest
	#define CHK_NetServerFinishRequest  TRUE
	#define EXP_NetServerFinishRequest  CAL_CMEXPAPI( "NetServerFinishRequest" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerFinishRequest
	#define EXT_NetServerFinishRequest
	#define GET_NetServerFinishRequest(fl)  CAL_CMGETAPI( "NetServerFinishRequest" ) 
	#define CAL_NetServerFinishRequest  NetServerFinishRequest
	#define CHK_NetServerFinishRequest  TRUE
	#define EXP_NetServerFinishRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerFinishRequest", (RTS_UINTPTR)NetServerFinishRequest, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerFinishRequest
	#define EXT_CmpChannelServerNetServerFinishRequest
	#define GET_CmpChannelServerNetServerFinishRequest  ERR_OK
	#define CAL_CmpChannelServerNetServerFinishRequest pICmpChannelServer->INetServerFinishRequest
	#define CHK_CmpChannelServerNetServerFinishRequest (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerFinishRequest  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerFinishRequest
	#define EXT_NetServerFinishRequest
	#define GET_NetServerFinishRequest(fl)  CAL_CMGETAPI( "NetServerFinishRequest" ) 
	#define CAL_NetServerFinishRequest pICmpChannelServer->INetServerFinishRequest
	#define CHK_NetServerFinishRequest (pICmpChannelServer != NULL)
	#define EXP_NetServerFinishRequest  CAL_CMEXPAPI( "NetServerFinishRequest" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerFinishRequest  PFNETSERVERFINISHREQUEST pfNetServerFinishRequest;
	#define EXT_NetServerFinishRequest  extern PFNETSERVERFINISHREQUEST pfNetServerFinishRequest;
	#define GET_NetServerFinishRequest(fl)  s_pfCMGetAPI2( "NetServerFinishRequest", (RTS_VOID_FCTPTR *)&pfNetServerFinishRequest, (fl), 0, 0)
	#define CAL_NetServerFinishRequest  pfNetServerFinishRequest
	#define CHK_NetServerFinishRequest  (pfNetServerFinishRequest != NULL)
	#define EXP_NetServerFinishRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerFinishRequest", (RTS_UINTPTR)NetServerFinishRequest, 0, 0) 
#endif




/** 
 * <description>
 *   Stores the session id in the channel server status structure.  
 * </description>
 * <param name="ulChannelHandle" type="IN">Id of the channel for which the session id should be set.</param>
 * <param name="ulSessionId" type="IN">New session id fo the channel.</param>
 * <result>error code</result>
*/
RTS_RESULT CDECL NetServerSetSessionId(RTS_UI32 ulChannelHandle, RTS_UI32 ulSessionId);
typedef RTS_RESULT (CDECL * PFNETSERVERSETSESSIONID) (RTS_UI32 ulChannelHandle, RTS_UI32 ulSessionId);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERSETSESSIONID_NOTIMPLEMENTED)
	#define USE_NetServerSetSessionId
	#define EXT_NetServerSetSessionId
	#define GET_NetServerSetSessionId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerSetSessionId(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_NetServerSetSessionId  FALSE
	#define EXP_NetServerSetSessionId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerSetSessionId
	#define EXT_NetServerSetSessionId
	#define GET_NetServerSetSessionId(fl)  CAL_CMGETAPI( "NetServerSetSessionId" ) 
	#define CAL_NetServerSetSessionId  NetServerSetSessionId
	#define CHK_NetServerSetSessionId  TRUE
	#define EXP_NetServerSetSessionId  CAL_CMEXPAPI( "NetServerSetSessionId" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerSetSessionId
	#define EXT_NetServerSetSessionId
	#define GET_NetServerSetSessionId(fl)  CAL_CMGETAPI( "NetServerSetSessionId" ) 
	#define CAL_NetServerSetSessionId  NetServerSetSessionId
	#define CHK_NetServerSetSessionId  TRUE
	#define EXP_NetServerSetSessionId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerSetSessionId", (RTS_UINTPTR)NetServerSetSessionId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerSetSessionId
	#define EXT_CmpChannelServerNetServerSetSessionId
	#define GET_CmpChannelServerNetServerSetSessionId  ERR_OK
	#define CAL_CmpChannelServerNetServerSetSessionId pICmpChannelServer->INetServerSetSessionId
	#define CHK_CmpChannelServerNetServerSetSessionId (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerSetSessionId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerSetSessionId
	#define EXT_NetServerSetSessionId
	#define GET_NetServerSetSessionId(fl)  CAL_CMGETAPI( "NetServerSetSessionId" ) 
	#define CAL_NetServerSetSessionId pICmpChannelServer->INetServerSetSessionId
	#define CHK_NetServerSetSessionId (pICmpChannelServer != NULL)
	#define EXP_NetServerSetSessionId  CAL_CMEXPAPI( "NetServerSetSessionId" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerSetSessionId  PFNETSERVERSETSESSIONID pfNetServerSetSessionId;
	#define EXT_NetServerSetSessionId  extern PFNETSERVERSETSESSIONID pfNetServerSetSessionId;
	#define GET_NetServerSetSessionId(fl)  s_pfCMGetAPI2( "NetServerSetSessionId", (RTS_VOID_FCTPTR *)&pfNetServerSetSessionId, (fl), 0, 0)
	#define CAL_NetServerSetSessionId  pfNetServerSetSessionId
	#define CHK_NetServerSetSessionId  (pfNetServerSetSessionId != NULL)
	#define EXP_NetServerSetSessionId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerSetSessionId", (RTS_UINTPTR)NetServerSetSessionId, 0, 0) 
#endif




/** 
 * <description>
 *   Retrieves the stored session id from the channel server status structure.  
 * </description>
 * <param name="ulChannelHandle" type="IN">Id of the channel for which the session id should be read.</param>
 * <param name="pulSessionId" type="OUT">Pointer to return the session id.</param>
 * <result>error code</result>
*/
RTS_RESULT CDECL NetServerGetSessionId(RTS_UI32 ulChannelHandle, RTS_UI32 *pulSessionId);
typedef RTS_RESULT (CDECL * PFNETSERVERGETSESSIONID) (RTS_UI32 ulChannelHandle, RTS_UI32 *pulSessionId);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERGETSESSIONID_NOTIMPLEMENTED)
	#define USE_NetServerGetSessionId
	#define EXT_NetServerGetSessionId
	#define GET_NetServerGetSessionId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerGetSessionId(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_NetServerGetSessionId  FALSE
	#define EXP_NetServerGetSessionId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerGetSessionId
	#define EXT_NetServerGetSessionId
	#define GET_NetServerGetSessionId(fl)  CAL_CMGETAPI( "NetServerGetSessionId" ) 
	#define CAL_NetServerGetSessionId  NetServerGetSessionId
	#define CHK_NetServerGetSessionId  TRUE
	#define EXP_NetServerGetSessionId  CAL_CMEXPAPI( "NetServerGetSessionId" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerGetSessionId
	#define EXT_NetServerGetSessionId
	#define GET_NetServerGetSessionId(fl)  CAL_CMGETAPI( "NetServerGetSessionId" ) 
	#define CAL_NetServerGetSessionId  NetServerGetSessionId
	#define CHK_NetServerGetSessionId  TRUE
	#define EXP_NetServerGetSessionId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetSessionId", (RTS_UINTPTR)NetServerGetSessionId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerGetSessionId
	#define EXT_CmpChannelServerNetServerGetSessionId
	#define GET_CmpChannelServerNetServerGetSessionId  ERR_OK
	#define CAL_CmpChannelServerNetServerGetSessionId pICmpChannelServer->INetServerGetSessionId
	#define CHK_CmpChannelServerNetServerGetSessionId (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerGetSessionId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerGetSessionId
	#define EXT_NetServerGetSessionId
	#define GET_NetServerGetSessionId(fl)  CAL_CMGETAPI( "NetServerGetSessionId" ) 
	#define CAL_NetServerGetSessionId pICmpChannelServer->INetServerGetSessionId
	#define CHK_NetServerGetSessionId (pICmpChannelServer != NULL)
	#define EXP_NetServerGetSessionId  CAL_CMEXPAPI( "NetServerGetSessionId" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerGetSessionId  PFNETSERVERGETSESSIONID pfNetServerGetSessionId;
	#define EXT_NetServerGetSessionId  extern PFNETSERVERGETSESSIONID pfNetServerGetSessionId;
	#define GET_NetServerGetSessionId(fl)  s_pfCMGetAPI2( "NetServerGetSessionId", (RTS_VOID_FCTPTR *)&pfNetServerGetSessionId, (fl), 0, 0)
	#define CAL_NetServerGetSessionId  pfNetServerGetSessionId
	#define CHK_NetServerGetSessionId  (pfNetServerGetSessionId != NULL)
	#define EXP_NetServerGetSessionId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetSessionId", (RTS_UINTPTR)NetServerGetSessionId, 0, 0) 
#endif





/* -- Functions exported to the L4Base network component -- */

/** 
 * <description>
 *   Get the buffer for the specified channel id. 
 *
 *  NOTE:
 *  After usage the channelbuffer MUST be released by
 *  calling NetServerReleaseChannel. Failing to do so will prevent the channel
 *  from being closed and the server will eventually run out of channels.
 *  Nevertheless, this function DOES NOT provide exclusive access to the channel.
 *  The L4Base component must use appropriate semaphores to ensure exclusive access.
 * </description>
 * <param name = "addrPeer" type="IN">The second endpoint of the channel</param>
 *  <param name="wChannelId" type = "IN">The id of the channel.</param>
 *  <param name="ppChBuffer" type = "OUT">Is set to the channelbuffer, if the channel exists.</param>
*/
int CDECL NetServerGetChannel(PEERADDRESS addrPeer, unsigned short wChannelId, CHANNELBUFFER **ppChBuffer);
typedef int (CDECL * PFNETSERVERGETCHANNEL) (PEERADDRESS addrPeer, unsigned short wChannelId, CHANNELBUFFER **ppChBuffer);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERGETCHANNEL_NOTIMPLEMENTED)
	#define USE_NetServerGetChannel
	#define EXT_NetServerGetChannel
	#define GET_NetServerGetChannel(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerGetChannel(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_NetServerGetChannel  FALSE
	#define EXP_NetServerGetChannel  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerGetChannel
	#define EXT_NetServerGetChannel
	#define GET_NetServerGetChannel(fl)  CAL_CMGETAPI( "NetServerGetChannel" ) 
	#define CAL_NetServerGetChannel  NetServerGetChannel
	#define CHK_NetServerGetChannel  TRUE
	#define EXP_NetServerGetChannel  CAL_CMEXPAPI( "NetServerGetChannel" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerGetChannel
	#define EXT_NetServerGetChannel
	#define GET_NetServerGetChannel(fl)  CAL_CMGETAPI( "NetServerGetChannel" ) 
	#define CAL_NetServerGetChannel  NetServerGetChannel
	#define CHK_NetServerGetChannel  TRUE
	#define EXP_NetServerGetChannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetChannel", (RTS_UINTPTR)NetServerGetChannel, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerGetChannel
	#define EXT_CmpChannelServerNetServerGetChannel
	#define GET_CmpChannelServerNetServerGetChannel  ERR_OK
	#define CAL_CmpChannelServerNetServerGetChannel pICmpChannelServer->INetServerGetChannel
	#define CHK_CmpChannelServerNetServerGetChannel (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerGetChannel  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerGetChannel
	#define EXT_NetServerGetChannel
	#define GET_NetServerGetChannel(fl)  CAL_CMGETAPI( "NetServerGetChannel" ) 
	#define CAL_NetServerGetChannel pICmpChannelServer->INetServerGetChannel
	#define CHK_NetServerGetChannel (pICmpChannelServer != NULL)
	#define EXP_NetServerGetChannel  CAL_CMEXPAPI( "NetServerGetChannel" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerGetChannel  PFNETSERVERGETCHANNEL pfNetServerGetChannel;
	#define EXT_NetServerGetChannel  extern PFNETSERVERGETCHANNEL pfNetServerGetChannel;
	#define GET_NetServerGetChannel(fl)  s_pfCMGetAPI2( "NetServerGetChannel", (RTS_VOID_FCTPTR *)&pfNetServerGetChannel, (fl), 0, 0)
	#define CAL_NetServerGetChannel  pfNetServerGetChannel
	#define CHK_NetServerGetChannel  (pfNetServerGetChannel != NULL)
	#define EXP_NetServerGetChannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerGetChannel", (RTS_UINTPTR)NetServerGetChannel, 0, 0) 
#endif




/**
 * <description>
 *   Release a channel buffer returned by NetServerGetChannel. This buffer may not be used
 *   after calling this function. Use NetServerGetChannel to acquire access to this channel again.
 * </description>
 * <param name="pChBuffer" type = "IN">The channel buffer to release</param>
*/
int CDECL NetServerReleaseChannel(CHANNELBUFFER *pChBuffer);
typedef int (CDECL * PFNETSERVERRELEASECHANNEL) (CHANNELBUFFER *pChBuffer);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERRELEASECHANNEL_NOTIMPLEMENTED)
	#define USE_NetServerReleaseChannel
	#define EXT_NetServerReleaseChannel
	#define GET_NetServerReleaseChannel(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerReleaseChannel(p0)  (int)ERR_NOTIMPLEMENTED
	#define CHK_NetServerReleaseChannel  FALSE
	#define EXP_NetServerReleaseChannel  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerReleaseChannel
	#define EXT_NetServerReleaseChannel
	#define GET_NetServerReleaseChannel(fl)  CAL_CMGETAPI( "NetServerReleaseChannel" ) 
	#define CAL_NetServerReleaseChannel  NetServerReleaseChannel
	#define CHK_NetServerReleaseChannel  TRUE
	#define EXP_NetServerReleaseChannel  CAL_CMEXPAPI( "NetServerReleaseChannel" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerReleaseChannel
	#define EXT_NetServerReleaseChannel
	#define GET_NetServerReleaseChannel(fl)  CAL_CMGETAPI( "NetServerReleaseChannel" ) 
	#define CAL_NetServerReleaseChannel  NetServerReleaseChannel
	#define CHK_NetServerReleaseChannel  TRUE
	#define EXP_NetServerReleaseChannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerReleaseChannel", (RTS_UINTPTR)NetServerReleaseChannel, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerReleaseChannel
	#define EXT_CmpChannelServerNetServerReleaseChannel
	#define GET_CmpChannelServerNetServerReleaseChannel  ERR_OK
	#define CAL_CmpChannelServerNetServerReleaseChannel pICmpChannelServer->INetServerReleaseChannel
	#define CHK_CmpChannelServerNetServerReleaseChannel (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerReleaseChannel  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerReleaseChannel
	#define EXT_NetServerReleaseChannel
	#define GET_NetServerReleaseChannel(fl)  CAL_CMGETAPI( "NetServerReleaseChannel" ) 
	#define CAL_NetServerReleaseChannel pICmpChannelServer->INetServerReleaseChannel
	#define CHK_NetServerReleaseChannel (pICmpChannelServer != NULL)
	#define EXP_NetServerReleaseChannel  CAL_CMEXPAPI( "NetServerReleaseChannel" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerReleaseChannel  PFNETSERVERRELEASECHANNEL pfNetServerReleaseChannel;
	#define EXT_NetServerReleaseChannel  extern PFNETSERVERRELEASECHANNEL pfNetServerReleaseChannel;
	#define GET_NetServerReleaseChannel(fl)  s_pfCMGetAPI2( "NetServerReleaseChannel", (RTS_VOID_FCTPTR *)&pfNetServerReleaseChannel, (fl), 0, 0)
	#define CAL_NetServerReleaseChannel  pfNetServerReleaseChannel
	#define CHK_NetServerReleaseChannel  (pfNetServerReleaseChannel != NULL)
	#define EXP_NetServerReleaseChannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerReleaseChannel", (RTS_UINTPTR)NetServerReleaseChannel, 0, 0) 
#endif




/* Called by the L4Base component each time a meta-request arrives. The server is
   responsible for handling all meta-requests. 
   addrSender IN  The sender of the request
   pduData    IN  The request itself
*/
int CDECL NetServerHandleMetaRequest(RTS_HANDLE hRouter, PEERADDRESS addrSender, PROTOCOL_DATA_UNIT pduData);
typedef int (CDECL * PFNETSERVERHANDLEMETAREQUEST) (RTS_HANDLE hRouter, PEERADDRESS addrSender, PROTOCOL_DATA_UNIT pduData);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERHANDLEMETAREQUEST_NOTIMPLEMENTED)
	#define USE_NetServerHandleMetaRequest
	#define EXT_NetServerHandleMetaRequest
	#define GET_NetServerHandleMetaRequest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerHandleMetaRequest(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_NetServerHandleMetaRequest  FALSE
	#define EXP_NetServerHandleMetaRequest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerHandleMetaRequest
	#define EXT_NetServerHandleMetaRequest
	#define GET_NetServerHandleMetaRequest(fl)  CAL_CMGETAPI( "NetServerHandleMetaRequest" ) 
	#define CAL_NetServerHandleMetaRequest  NetServerHandleMetaRequest
	#define CHK_NetServerHandleMetaRequest  TRUE
	#define EXP_NetServerHandleMetaRequest  CAL_CMEXPAPI( "NetServerHandleMetaRequest" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerHandleMetaRequest
	#define EXT_NetServerHandleMetaRequest
	#define GET_NetServerHandleMetaRequest(fl)  CAL_CMGETAPI( "NetServerHandleMetaRequest" ) 
	#define CAL_NetServerHandleMetaRequest  NetServerHandleMetaRequest
	#define CHK_NetServerHandleMetaRequest  TRUE
	#define EXP_NetServerHandleMetaRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerHandleMetaRequest", (RTS_UINTPTR)NetServerHandleMetaRequest, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerHandleMetaRequest
	#define EXT_CmpChannelServerNetServerHandleMetaRequest
	#define GET_CmpChannelServerNetServerHandleMetaRequest  ERR_OK
	#define CAL_CmpChannelServerNetServerHandleMetaRequest pICmpChannelServer->INetServerHandleMetaRequest
	#define CHK_CmpChannelServerNetServerHandleMetaRequest (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerHandleMetaRequest  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerHandleMetaRequest
	#define EXT_NetServerHandleMetaRequest
	#define GET_NetServerHandleMetaRequest(fl)  CAL_CMGETAPI( "NetServerHandleMetaRequest" ) 
	#define CAL_NetServerHandleMetaRequest pICmpChannelServer->INetServerHandleMetaRequest
	#define CHK_NetServerHandleMetaRequest (pICmpChannelServer != NULL)
	#define EXP_NetServerHandleMetaRequest  CAL_CMEXPAPI( "NetServerHandleMetaRequest" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerHandleMetaRequest  PFNETSERVERHANDLEMETAREQUEST pfNetServerHandleMetaRequest;
	#define EXT_NetServerHandleMetaRequest  extern PFNETSERVERHANDLEMETAREQUEST pfNetServerHandleMetaRequest;
	#define GET_NetServerHandleMetaRequest(fl)  s_pfCMGetAPI2( "NetServerHandleMetaRequest", (RTS_VOID_FCTPTR *)&pfNetServerHandleMetaRequest, (fl), 0, 0)
	#define CAL_NetServerHandleMetaRequest  pfNetServerHandleMetaRequest
	#define CHK_NetServerHandleMetaRequest  (pfNetServerHandleMetaRequest != NULL)
	#define EXP_NetServerHandleMetaRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerHandleMetaRequest", (RTS_UINTPTR)NetServerHandleMetaRequest, 0, 0) 
#endif




/* Calls the pfChannelHandler once for each active server channel 
   pfChannelHandler IN     Function to be called for each channel
   pParam           IN/OUT This param is passed to pfChannelHandler.
*/
void CDECL NetServerForEachChannel(PFCHANNELHANDLER pfChannelHandler, void * pParam);
typedef void (CDECL * PFNETSERVERFOREACHCHANNEL) (PFCHANNELHANDLER pfChannelHandler, void * pParam);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERFOREACHCHANNEL_NOTIMPLEMENTED)
	#define USE_NetServerForEachChannel
	#define EXT_NetServerForEachChannel
	#define GET_NetServerForEachChannel(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerForEachChannel(p0,p1)  
	#define CHK_NetServerForEachChannel  FALSE
	#define EXP_NetServerForEachChannel  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerForEachChannel
	#define EXT_NetServerForEachChannel
	#define GET_NetServerForEachChannel(fl)  CAL_CMGETAPI( "NetServerForEachChannel" ) 
	#define CAL_NetServerForEachChannel  NetServerForEachChannel
	#define CHK_NetServerForEachChannel  TRUE
	#define EXP_NetServerForEachChannel  CAL_CMEXPAPI( "NetServerForEachChannel" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerForEachChannel
	#define EXT_NetServerForEachChannel
	#define GET_NetServerForEachChannel(fl)  CAL_CMGETAPI( "NetServerForEachChannel" ) 
	#define CAL_NetServerForEachChannel  NetServerForEachChannel
	#define CHK_NetServerForEachChannel  TRUE
	#define EXP_NetServerForEachChannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerForEachChannel", (RTS_UINTPTR)NetServerForEachChannel, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerForEachChannel
	#define EXT_CmpChannelServerNetServerForEachChannel
	#define GET_CmpChannelServerNetServerForEachChannel  ERR_OK
	#define CAL_CmpChannelServerNetServerForEachChannel pICmpChannelServer->INetServerForEachChannel
	#define CHK_CmpChannelServerNetServerForEachChannel (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerForEachChannel  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerForEachChannel
	#define EXT_NetServerForEachChannel
	#define GET_NetServerForEachChannel(fl)  CAL_CMGETAPI( "NetServerForEachChannel" ) 
	#define CAL_NetServerForEachChannel pICmpChannelServer->INetServerForEachChannel
	#define CHK_NetServerForEachChannel (pICmpChannelServer != NULL)
	#define EXP_NetServerForEachChannel  CAL_CMEXPAPI( "NetServerForEachChannel" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerForEachChannel  PFNETSERVERFOREACHCHANNEL pfNetServerForEachChannel;
	#define EXT_NetServerForEachChannel  extern PFNETSERVERFOREACHCHANNEL pfNetServerForEachChannel;
	#define GET_NetServerForEachChannel(fl)  s_pfCMGetAPI2( "NetServerForEachChannel", (RTS_VOID_FCTPTR *)&pfNetServerForEachChannel, (fl), 0, 0)
	#define CAL_NetServerForEachChannel  pfNetServerForEachChannel
	#define CHK_NetServerForEachChannel  (pfNetServerForEachChannel != NULL)
	#define EXP_NetServerForEachChannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerForEachChannel", (RTS_UINTPTR)NetServerForEachChannel, 0, 0) 
#endif




/**
 * <description>Obsolete: Use NetServerMessageReceived3 instead. Will be removed in future versions!</description>
 */
int CDECL NetServerMessageReceived(CHANNELBUFFER *pChBuffer, PROTOCOL_DATA_UNIT pduData);
typedef int (CDECL * PFNETSERVERMESSAGERECEIVED) (CHANNELBUFFER *pChBuffer, PROTOCOL_DATA_UNIT pduData);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERMESSAGERECEIVED_NOTIMPLEMENTED)
	#define USE_NetServerMessageReceived
	#define EXT_NetServerMessageReceived
	#define GET_NetServerMessageReceived(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerMessageReceived(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_NetServerMessageReceived  FALSE
	#define EXP_NetServerMessageReceived  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerMessageReceived
	#define EXT_NetServerMessageReceived
	#define GET_NetServerMessageReceived(fl)  CAL_CMGETAPI( "NetServerMessageReceived" ) 
	#define CAL_NetServerMessageReceived  NetServerMessageReceived
	#define CHK_NetServerMessageReceived  TRUE
	#define EXP_NetServerMessageReceived  CAL_CMEXPAPI( "NetServerMessageReceived" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerMessageReceived
	#define EXT_NetServerMessageReceived
	#define GET_NetServerMessageReceived(fl)  CAL_CMGETAPI( "NetServerMessageReceived" ) 
	#define CAL_NetServerMessageReceived  NetServerMessageReceived
	#define CHK_NetServerMessageReceived  TRUE
	#define EXP_NetServerMessageReceived  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerMessageReceived", (RTS_UINTPTR)NetServerMessageReceived, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerMessageReceived
	#define EXT_CmpChannelServerNetServerMessageReceived
	#define GET_CmpChannelServerNetServerMessageReceived  ERR_OK
	#define CAL_CmpChannelServerNetServerMessageReceived pICmpChannelServer->INetServerMessageReceived
	#define CHK_CmpChannelServerNetServerMessageReceived (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerMessageReceived  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerMessageReceived
	#define EXT_NetServerMessageReceived
	#define GET_NetServerMessageReceived(fl)  CAL_CMGETAPI( "NetServerMessageReceived" ) 
	#define CAL_NetServerMessageReceived pICmpChannelServer->INetServerMessageReceived
	#define CHK_NetServerMessageReceived (pICmpChannelServer != NULL)
	#define EXP_NetServerMessageReceived  CAL_CMEXPAPI( "NetServerMessageReceived" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerMessageReceived  PFNETSERVERMESSAGERECEIVED pfNetServerMessageReceived;
	#define EXT_NetServerMessageReceived  extern PFNETSERVERMESSAGERECEIVED pfNetServerMessageReceived;
	#define GET_NetServerMessageReceived(fl)  s_pfCMGetAPI2( "NetServerMessageReceived", (RTS_VOID_FCTPTR *)&pfNetServerMessageReceived, (fl), 0, 0)
	#define CAL_NetServerMessageReceived  pfNetServerMessageReceived
	#define CHK_NetServerMessageReceived  (pfNetServerMessageReceived != NULL)
	#define EXP_NetServerMessageReceived  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerMessageReceived", (RTS_UINTPTR)NetServerMessageReceived, 0, 0) 
#endif




/**
 * <description>Obsolete: Use NetServerMessageReceived3 instead. Will be removed in future versions!</description>
 */
int CDECL NetServerMessageReceived2(RTS_HANDLE hRouter, CHANNELBUFFER *pChBuffer, PROTOCOL_DATA_UNIT pduData);
typedef int (CDECL * PFNETSERVERMESSAGERECEIVED2) (RTS_HANDLE hRouter, CHANNELBUFFER *pChBuffer, PROTOCOL_DATA_UNIT pduData);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERMESSAGERECEIVED2_NOTIMPLEMENTED)
	#define USE_NetServerMessageReceived2
	#define EXT_NetServerMessageReceived2
	#define GET_NetServerMessageReceived2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerMessageReceived2(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_NetServerMessageReceived2  FALSE
	#define EXP_NetServerMessageReceived2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerMessageReceived2
	#define EXT_NetServerMessageReceived2
	#define GET_NetServerMessageReceived2(fl)  CAL_CMGETAPI( "NetServerMessageReceived2" ) 
	#define CAL_NetServerMessageReceived2  NetServerMessageReceived2
	#define CHK_NetServerMessageReceived2  TRUE
	#define EXP_NetServerMessageReceived2  CAL_CMEXPAPI( "NetServerMessageReceived2" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerMessageReceived2
	#define EXT_NetServerMessageReceived2
	#define GET_NetServerMessageReceived2(fl)  CAL_CMGETAPI( "NetServerMessageReceived2" ) 
	#define CAL_NetServerMessageReceived2  NetServerMessageReceived2
	#define CHK_NetServerMessageReceived2  TRUE
	#define EXP_NetServerMessageReceived2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerMessageReceived2", (RTS_UINTPTR)NetServerMessageReceived2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerMessageReceived2
	#define EXT_CmpChannelServerNetServerMessageReceived2
	#define GET_CmpChannelServerNetServerMessageReceived2  ERR_OK
	#define CAL_CmpChannelServerNetServerMessageReceived2 pICmpChannelServer->INetServerMessageReceived2
	#define CHK_CmpChannelServerNetServerMessageReceived2 (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerMessageReceived2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerMessageReceived2
	#define EXT_NetServerMessageReceived2
	#define GET_NetServerMessageReceived2(fl)  CAL_CMGETAPI( "NetServerMessageReceived2" ) 
	#define CAL_NetServerMessageReceived2 pICmpChannelServer->INetServerMessageReceived2
	#define CHK_NetServerMessageReceived2 (pICmpChannelServer != NULL)
	#define EXP_NetServerMessageReceived2  CAL_CMEXPAPI( "NetServerMessageReceived2" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerMessageReceived2  PFNETSERVERMESSAGERECEIVED2 pfNetServerMessageReceived2;
	#define EXT_NetServerMessageReceived2  extern PFNETSERVERMESSAGERECEIVED2 pfNetServerMessageReceived2;
	#define GET_NetServerMessageReceived2(fl)  s_pfCMGetAPI2( "NetServerMessageReceived2", (RTS_VOID_FCTPTR *)&pfNetServerMessageReceived2, (fl), 0, 0)
	#define CAL_NetServerMessageReceived2  pfNetServerMessageReceived2
	#define CHK_NetServerMessageReceived2  (pfNetServerMessageReceived2 != NULL)
	#define EXP_NetServerMessageReceived2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerMessageReceived2", (RTS_UINTPTR)NetServerMessageReceived2, 0, 0) 
#endif




/**
 * <description>Called by the L4Base component whenever a complete L7 message arrived on a server channel</description>
 * <param name="pChBuffer" type="IN">Pointer to the channel buffer</param>
 * <param name="pduData" type="IN">Content of the message. The data pointed to by will be valid only until 
 *  the reply has been passed to channel manager or the channel is closed.</param>
 * <param name="bFirstCall" type="IN">0: Tells the function, if it was already called for the same request before (0) or not (1).</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Received service was completely handeled.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PENDING">Received service will be handled asynchronously by the higher layers, 
 * but the caller has not to take care about this.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_CALL_AGAIN">Received service will be handled asynchronously. 
 * To progress this function have to be called again for the same received service data with bFirstCall=0.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Error occured, channel close has been triggered.</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL NetServerMessageReceived3(CHANNELBUFFER *pChBuffer, PROTOCOL_DATA_UNIT pduData, RTS_UI32 bFirstCall);
typedef RTS_RESULT (CDECL * PFNETSERVERMESSAGERECEIVED3) (CHANNELBUFFER *pChBuffer, PROTOCOL_DATA_UNIT pduData, RTS_UI32 bFirstCall);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERMESSAGERECEIVED3_NOTIMPLEMENTED)
	#define USE_NetServerMessageReceived3
	#define EXT_NetServerMessageReceived3
	#define GET_NetServerMessageReceived3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerMessageReceived3(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_NetServerMessageReceived3  FALSE
	#define EXP_NetServerMessageReceived3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerMessageReceived3
	#define EXT_NetServerMessageReceived3
	#define GET_NetServerMessageReceived3(fl)  CAL_CMGETAPI( "NetServerMessageReceived3" ) 
	#define CAL_NetServerMessageReceived3  NetServerMessageReceived3
	#define CHK_NetServerMessageReceived3  TRUE
	#define EXP_NetServerMessageReceived3  CAL_CMEXPAPI( "NetServerMessageReceived3" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerMessageReceived3
	#define EXT_NetServerMessageReceived3
	#define GET_NetServerMessageReceived3(fl)  CAL_CMGETAPI( "NetServerMessageReceived3" ) 
	#define CAL_NetServerMessageReceived3  NetServerMessageReceived3
	#define CHK_NetServerMessageReceived3  TRUE
	#define EXP_NetServerMessageReceived3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerMessageReceived3", (RTS_UINTPTR)NetServerMessageReceived3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerMessageReceived3
	#define EXT_CmpChannelServerNetServerMessageReceived3
	#define GET_CmpChannelServerNetServerMessageReceived3  ERR_OK
	#define CAL_CmpChannelServerNetServerMessageReceived3 pICmpChannelServer->INetServerMessageReceived3
	#define CHK_CmpChannelServerNetServerMessageReceived3 (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerMessageReceived3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerMessageReceived3
	#define EXT_NetServerMessageReceived3
	#define GET_NetServerMessageReceived3(fl)  CAL_CMGETAPI( "NetServerMessageReceived3" ) 
	#define CAL_NetServerMessageReceived3 pICmpChannelServer->INetServerMessageReceived3
	#define CHK_NetServerMessageReceived3 (pICmpChannelServer != NULL)
	#define EXP_NetServerMessageReceived3  CAL_CMEXPAPI( "NetServerMessageReceived3" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerMessageReceived3  PFNETSERVERMESSAGERECEIVED3 pfNetServerMessageReceived3;
	#define EXT_NetServerMessageReceived3  extern PFNETSERVERMESSAGERECEIVED3 pfNetServerMessageReceived3;
	#define GET_NetServerMessageReceived3(fl)  s_pfCMGetAPI2( "NetServerMessageReceived3", (RTS_VOID_FCTPTR *)&pfNetServerMessageReceived3, (fl), 0, 0)
	#define CAL_NetServerMessageReceived3  pfNetServerMessageReceived3
	#define CHK_NetServerMessageReceived3  (pfNetServerMessageReceived3 != NULL)
	#define EXP_NetServerMessageReceived3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerMessageReceived3", (RTS_UINTPTR)NetServerMessageReceived3, 0, 0) 
#endif




/* Called when a unrecoverable error occurs for pfChBuffer, eg. ERR_CHANNEL_BROKEN.
   The channel must be closed by the net server.
	pChBuffer  IN
	nError     IN  The error 
*/
int CDECL NetServerChannelError(CHANNELBUFFER *pChBuffer, int nError);
typedef int (CDECL * PFNETSERVERCHANNELERROR) (CHANNELBUFFER *pChBuffer, int nError);
#if defined(CMPCHANNELSERVER_NOTIMPLEMENTED) || defined(NETSERVERCHANNELERROR_NOTIMPLEMENTED)
	#define USE_NetServerChannelError
	#define EXT_NetServerChannelError
	#define GET_NetServerChannelError(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetServerChannelError(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_NetServerChannelError  FALSE
	#define EXP_NetServerChannelError  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetServerChannelError
	#define EXT_NetServerChannelError
	#define GET_NetServerChannelError(fl)  CAL_CMGETAPI( "NetServerChannelError" ) 
	#define CAL_NetServerChannelError  NetServerChannelError
	#define CHK_NetServerChannelError  TRUE
	#define EXP_NetServerChannelError  CAL_CMEXPAPI( "NetServerChannelError" ) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELSERVER_EXTERNAL)
	#define USE_NetServerChannelError
	#define EXT_NetServerChannelError
	#define GET_NetServerChannelError(fl)  CAL_CMGETAPI( "NetServerChannelError" ) 
	#define CAL_NetServerChannelError  NetServerChannelError
	#define CHK_NetServerChannelError  TRUE
	#define EXP_NetServerChannelError  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerChannelError", (RTS_UINTPTR)NetServerChannelError, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelServerNetServerChannelError
	#define EXT_CmpChannelServerNetServerChannelError
	#define GET_CmpChannelServerNetServerChannelError  ERR_OK
	#define CAL_CmpChannelServerNetServerChannelError pICmpChannelServer->INetServerChannelError
	#define CHK_CmpChannelServerNetServerChannelError (pICmpChannelServer != NULL)
	#define EXP_CmpChannelServerNetServerChannelError  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetServerChannelError
	#define EXT_NetServerChannelError
	#define GET_NetServerChannelError(fl)  CAL_CMGETAPI( "NetServerChannelError" ) 
	#define CAL_NetServerChannelError pICmpChannelServer->INetServerChannelError
	#define CHK_NetServerChannelError (pICmpChannelServer != NULL)
	#define EXP_NetServerChannelError  CAL_CMEXPAPI( "NetServerChannelError" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetServerChannelError  PFNETSERVERCHANNELERROR pfNetServerChannelError;
	#define EXT_NetServerChannelError  extern PFNETSERVERCHANNELERROR pfNetServerChannelError;
	#define GET_NetServerChannelError(fl)  s_pfCMGetAPI2( "NetServerChannelError", (RTS_VOID_FCTPTR *)&pfNetServerChannelError, (fl), 0, 0)
	#define CAL_NetServerChannelError  pfNetServerChannelError
	#define CHK_NetServerChannelError  (pfNetServerChannelError != NULL)
	#define EXP_NetServerChannelError  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetServerChannelError", (RTS_UINTPTR)NetServerChannelError, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFNETSERVERGETMAXCHANNELS INetServerGetMaxChannels;
 	PFNETSERVERGETMAXCHANNELBUFFERSIZE INetServerGetMaxChannelBufferSize;
 	PFNETSERVERGETCHANNELINFOBYINDEX INetServerGetChannelInfoByIndex;
 	PFNETSERVERGETCHANNELINFOBYINDEX2 INetServerGetChannelInfoByIndex2;
 	PFNETSERVERGETSTATUS INetServerGetStatus;
 	PFNETSERVERGETREQUEST INetServerGetRequest;
 	PFNETSERVERFINISHREQUEST INetServerFinishRequest;
 	PFNETSERVERSETSESSIONID INetServerSetSessionId;
 	PFNETSERVERGETSESSIONID INetServerGetSessionId;
 	PFNETSERVERGETCHANNEL INetServerGetChannel;
 	PFNETSERVERRELEASECHANNEL INetServerReleaseChannel;
 	PFNETSERVERHANDLEMETAREQUEST INetServerHandleMetaRequest;
 	PFNETSERVERFOREACHCHANNEL INetServerForEachChannel;
 	PFNETSERVERMESSAGERECEIVED INetServerMessageReceived;
 	PFNETSERVERMESSAGERECEIVED2 INetServerMessageReceived2;
 	PFNETSERVERMESSAGERECEIVED3 INetServerMessageReceived3;
 	PFNETSERVERCHANNELERROR INetServerChannelError;
 } ICmpChannelServer_C;

#ifdef CPLUSPLUS
class ICmpChannelServer : public IBase
{
	public:
		virtual RTS_RESULT CDECL INetServerGetMaxChannels(RTS_UI16 *pwMaxChannels) =0;
		virtual RTS_RESULT CDECL INetServerGetMaxChannelBufferSize(RTS_I32 *pi32MaxChannelBufferSize) =0;
		virtual RTS_RESULT CDECL INetServerGetChannelInfoByIndex(RTS_UI16 ui16ChannelIndex, RTS_UI32 *pui32ServerState, CHANNELBUFFER *pChInfoBuffer, RTS_SIZE *psiBufferLen) =0;
		virtual RTS_RESULT CDECL INetServerGetChannelInfoByIndex2(RTS_UI16 ui16ChannelIndex, RTS_UI32 *pui32ServerState, CHANNELINFO *pChInfoBuffer, RTS_SIZE *psiBufferLen) =0;
		virtual RTS_RESULT CDECL INetServerGetStatus(RTS_UI32 ulChannelHandle, RTS_UI16 *pusStatus, RTS_UI8 *pbyScalingFactor, RTS_I32 *pnItemsComplete, RTS_I32 *pnTotalItems) =0;
		virtual RTS_RESULT CDECL INetServerGetRequest(RTS_UI32 ulChannelHandle, PROTOCOL_DATA_UNIT * ppduRequest, PROTOCOL_DATA_UNIT * ppduReplyBuffer) =0;
		virtual RTS_RESULT CDECL INetServerFinishRequest(RTS_UI32 ulChannelHandle, PROTOCOL_DATA_UNIT pduData) =0;
		virtual RTS_RESULT CDECL INetServerSetSessionId(RTS_UI32 ulChannelHandle, RTS_UI32 ulSessionId) =0;
		virtual RTS_RESULT CDECL INetServerGetSessionId(RTS_UI32 ulChannelHandle, RTS_UI32 *pulSessionId) =0;
		virtual int CDECL INetServerGetChannel(PEERADDRESS addrPeer, unsigned short wChannelId, CHANNELBUFFER **ppChBuffer) =0;
		virtual int CDECL INetServerReleaseChannel(CHANNELBUFFER *pChBuffer) =0;
		virtual int CDECL INetServerHandleMetaRequest(RTS_HANDLE hRouter, PEERADDRESS addrSender, PROTOCOL_DATA_UNIT pduData) =0;
		virtual void CDECL INetServerForEachChannel(PFCHANNELHANDLER pfChannelHandler, void * pParam) =0;
		virtual int CDECL INetServerMessageReceived(CHANNELBUFFER *pChBuffer, PROTOCOL_DATA_UNIT pduData) =0;
		virtual int CDECL INetServerMessageReceived2(RTS_HANDLE hRouter, CHANNELBUFFER *pChBuffer, PROTOCOL_DATA_UNIT pduData) =0;
		virtual RTS_RESULT CDECL INetServerMessageReceived3(CHANNELBUFFER *pChBuffer, PROTOCOL_DATA_UNIT pduData, RTS_UI32 bFirstCall) =0;
		virtual int CDECL INetServerChannelError(CHANNELBUFFER *pChBuffer, int nError) =0;
};
	#ifndef ITF_CmpChannelServer
		#define ITF_CmpChannelServer static ICmpChannelServer *pICmpChannelServer = NULL;
	#endif
	#define EXTITF_CmpChannelServer
#else	/*CPLUSPLUS*/
	typedef ICmpChannelServer_C		ICmpChannelServer;
	#ifndef ITF_CmpChannelServer
		#define ITF_CmpChannelServer
	#endif
	#define EXTITF_CmpChannelServer
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCHANNELSERVERITF_H_*/
