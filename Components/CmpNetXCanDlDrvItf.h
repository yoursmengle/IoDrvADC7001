 /**
 * <interfacename>CmpNetXCanDlDrv</interfacename>
 * <description> 
 *	<p>This is the CAA Can Mini Driver for NetX Can Open cards. It is based on the NetX Dl layer.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

	
	
#ifndef _CMPNETXCANDLDRVITF_H_
#define _CMPNETXCANDLDRVITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CmpIoDrvItf.h"
#include "CAATypes.h"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Maximal number of NetX CAN networks, supported by this device. This setting is mandatory
 * </description>
 */
#define NETXCMD_KEY_MAX_NETWORKS					"MaxNumberOfCanNetworks"
#define NETXCMD_INT_MAX_NETWORDS_DEFAULT			1			

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Boad number of the channel with the specified NetID. This setting is used, only if there is no setting for the
 *  board and channel number in the io configuration.
 *  Example: NetId.0.Board=0  // Channel with NetId = 0 is on Board 0
 *  If board and channel number is not set, board 0 channel 0 is used for NetId 0.
 * </description>
 */
#define NETXCMD_KEY_NETID					"NetId"
#define NETXCMD_BOARD						"Board"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Channel number of the channel with the specified NetID. This setting is used, only if there is no setting for the
 *  board and channel number in the io configuration.
 *  Example: NetId.0.Channel=0  // Channel with NetId = 0 is on NetX Channel 0
 * </description>
 */
#define NETXCMD_CHANNEL						"Channel"


#define EVTPARAMID_CmpNetXCanDlDrv 1
#define EVTVERSION_CmpNetXCanDlDrv 1


/**
 * <category>Events</category>
 * <description>
 *	Event is sent before the NetXCanDlDrv starts it configuration. If the NetX firmware must be loaded dynamically, it should 
 *	be done on this event. The user can change the values for iBourd and iChannel, to change the used netX channel for this netID. 
 *  </description>
 * <param name="pEventParam" type="IN">EVTPARAM_PacketUnhandled</param>
 */
#define EVT_START_NETX_CONFIG				MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Event parameter</category>
 * <element name="pConnector" type="IN">Connector of the NetX Can Bus, if available. Can be NULL, if no IoConfig is available</element>
 * <element name="piBoardNumber" type="INOUT">Pointer to the boardnumber for this netID. This value is only used, if there is no IoConfig</element>
 * <element name="piChannelNumber" type="INOUT">Pointer to the channelnumber for this netID</element>
 * <element name="ulNetId" type="IN">NetId of this board/channel. This value is only used, if there is no IoConfig</element>
 * <element name="xInitialConfig" type="IN">TRUE for the first configuration of the network</element>
 */
typedef struct
{
	IoConfigConnector* pConnector;
	int* piBoardNumber;
	int* piChannelNumber;
	RTS_UI32 ulNetId;
	CAA_BOOL xInitialConfig;
}EVTPARAM_StartNetXConfiguration;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Initializes a netX channel. Afterwards, the netX is passive on the bus. If the firmware is loaded dynamically, 
 *  this function could be called to initialize the netX channel. The net Id is passed as an parameter with the event EVT_START_NETX_CONFIG,
 *  the board and channel number must be evaluated by the customer. </description>
 * <param name="byNet" type="IN">CANbus net ID</param>
 * <param name="iBoard" type="IN">Number of the netX board to initialize.</param>
 * <param name="iChannel" type="IN">Number of the netX Channel to initialize.</param>
 * <result>Errorcode</result>
 */
RTS_RESULT CDECL NetX_SetupChannel(unsigned char byNet, int iBoard, int iChannel);
typedef RTS_RESULT (CDECL * PFNETX_SETUPCHANNEL) (unsigned char byNet, int iBoard, int iChannel);
#if defined(CMPNETXCANDLDRV_NOTIMPLEMENTED) || defined(NETX_SETUPCHANNEL_NOTIMPLEMENTED)
	#define USE_NetX_SetupChannel
	#define EXT_NetX_SetupChannel
	#define GET_NetX_SetupChannel(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NetX_SetupChannel(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_NetX_SetupChannel  FALSE
	#define EXP_NetX_SetupChannel  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NetX_SetupChannel
	#define EXT_NetX_SetupChannel
	#define GET_NetX_SetupChannel(fl)  CAL_CMGETAPI( "NetX_SetupChannel" ) 
	#define CAL_NetX_SetupChannel  NetX_SetupChannel
	#define CHK_NetX_SetupChannel  TRUE
	#define EXP_NetX_SetupChannel  CAL_CMEXPAPI( "NetX_SetupChannel" ) 
#elif defined(MIXED_LINK) && !defined(CMPNETXCANDLDRV_EXTERNAL)
	#define USE_NetX_SetupChannel
	#define EXT_NetX_SetupChannel
	#define GET_NetX_SetupChannel(fl)  CAL_CMGETAPI( "NetX_SetupChannel" ) 
	#define CAL_NetX_SetupChannel  NetX_SetupChannel
	#define CHK_NetX_SetupChannel  TRUE
	#define EXP_NetX_SetupChannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetX_SetupChannel", (RTS_UINTPTR)NetX_SetupChannel, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpNetXCanDlDrvNetX_SetupChannel
	#define EXT_CmpNetXCanDlDrvNetX_SetupChannel
	#define GET_CmpNetXCanDlDrvNetX_SetupChannel  ERR_OK
	#define CAL_CmpNetXCanDlDrvNetX_SetupChannel pICmpNetXCanDlDrv->INetX_SetupChannel
	#define CHK_CmpNetXCanDlDrvNetX_SetupChannel (pICmpNetXCanDlDrv != NULL)
	#define EXP_CmpNetXCanDlDrvNetX_SetupChannel  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NetX_SetupChannel
	#define EXT_NetX_SetupChannel
	#define GET_NetX_SetupChannel(fl)  CAL_CMGETAPI( "NetX_SetupChannel" ) 
	#define CAL_NetX_SetupChannel pICmpNetXCanDlDrv->INetX_SetupChannel
	#define CHK_NetX_SetupChannel (pICmpNetXCanDlDrv != NULL)
	#define EXP_NetX_SetupChannel  CAL_CMEXPAPI( "NetX_SetupChannel" ) 
#else /* DYNAMIC_LINK */
	#define USE_NetX_SetupChannel  PFNETX_SETUPCHANNEL pfNetX_SetupChannel;
	#define EXT_NetX_SetupChannel  extern PFNETX_SETUPCHANNEL pfNetX_SetupChannel;
	#define GET_NetX_SetupChannel(fl)  s_pfCMGetAPI2( "NetX_SetupChannel", (RTS_VOID_FCTPTR *)&pfNetX_SetupChannel, (fl), 0, 0)
	#define CAL_NetX_SetupChannel  pfNetX_SetupChannel
	#define CHK_NetX_SetupChannel  (pfNetX_SetupChannel != NULL)
	#define EXP_NetX_SetupChannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NetX_SetupChannel", (RTS_UINTPTR)NetX_SetupChannel, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFNETX_SETUPCHANNEL INetX_SetupChannel;
 } ICmpNetXCanDlDrv_C;

#ifdef CPLUSPLUS
class ICmpNetXCanDlDrv : public IBase
{
	public:
		virtual RTS_RESULT CDECL INetX_SetupChannel(unsigned char byNet, int iBoard, int iChannel) =0;
};
	#ifndef ITF_CmpNetXCanDlDrv
		#define ITF_CmpNetXCanDlDrv static ICmpNetXCanDlDrv *pICmpNetXCanDlDrv = NULL;
	#endif
	#define EXTITF_CmpNetXCanDlDrv
#else	/*CPLUSPLUS*/
	typedef ICmpNetXCanDlDrv_C		ICmpNetXCanDlDrv;
	#ifndef ITF_CmpNetXCanDlDrv
		#define ITF_CmpNetXCanDlDrv
	#endif
	#define EXTITF_CmpNetXCanDlDrv
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPNETXCANDLDRVITF_H_*/
