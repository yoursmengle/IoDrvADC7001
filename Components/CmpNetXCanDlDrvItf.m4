/**
 * <interfacename>CmpNetXCanDlDrv</interfacename>
 * <description> 
 *	<p>This is the CAA Can Mini Driver for NetX Can Open cards. It is based on the NetX Dl layer.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */
SET_INTERFACE_NAME(`CmpNetXCanDlDrv')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`NetX_SetupChannel',`(unsigned char byNet, int iBoard, int iChannel)')

#ifdef __cplusplus
}
#endif
