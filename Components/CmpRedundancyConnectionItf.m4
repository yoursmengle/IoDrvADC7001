/**
 * <interfacename>CmpRedundancyConnection</interfacename>
 * <description> 
 *	<p>This is the interface of the redundancy connection. The redundancy connection is responsible for data exchange
 *	between the two redundancy partners. The redundancy component itself is managing the connections. This component
 *	is responsible to establish, close and perform communication under control of the redundancy component itself.
 *	There is a default implementation using IP protocols TCP and UDP. It is possible to use alternative protocols,
 *	by implementing this interface and replacing the default component based on IP protocols.
 *	There are two different kinds of data exchange:
 *	<ul>
 *		<li>Sending and receiving synchronisation messages</li>
 *		<li>Sending and receiving data messages</li>
 *	</ul>
 *	</p>
 *	<p> Synchronisation messages are used during redundant operation. They are exchanged every task cycle.
 *	Data messages are used during synchronisation phase. They are used to transmit the boot application file, and global data.
 *	</p>
 *	<p> Default implementation is using UDP for synchronisation messages, and TCP for data messages.
 *	</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpRedundancyConnection')

#include "CmpItf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Open a redundancy connection for synchronisation. This connection will be used to receive data from redundancy partner. Synchronisation messages
 *	are quite small, but must be transmitted in realtime.
 * </description>
 * <param name="mode" type="IN">Indicates if the socked was opened in sync mode or data mode, and if used for send or received, or server or client.
 *	The following modes apply:
 *	RCOM_SyncReceive: Open a redundancy connection for sync messages receive.
 *		A UDP socket is opend and bind to local address in default implementation.
 *	RCOM_SyncSend: Open a redundancy connection for sync messages transmit.
 *		A UDP socket is opend in default implementation.
 *	RCOM_DataClient: Open a redundancy connection for data exchange. This connection will be used as client side for data transfer.
 *		The standby partner is playing the role of the communication client.
 *		Data transfer messages are quite big, and should be transmitted as fast as possible.
 *		A TCP socket is opend in default implementation, and connect to partner.
 *	RCOM_DataServer: Open a redundancy connection for data exchange. This connection will be used as server side for data transfer.
 *		The standalone and active partner is playing the role of the communication server.
 *		Data transfer messages are quite big, and should be transmitted as fast as possible.
 *		A TCP socket is opend in default implementation, and bind and listen. This socket is waiting for a client connection.
 * </param>
 * <result>Handle of connection, for example socket number. Will be used to send and receive data. In case of error RTS_INVALID_HANDLE will be returned.</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`RdcyConnectionOpen',`(REDUNDANCY_COMM_MODE mode, RTS_UI32 uiMessageSize)')

/**
 * <description>
 *	Close a redundancy connection previously opened with RdcyConnectionOpen.
 * </description>
 * <param name="hConnection" type="IN">Handle to the connection</param>
 * <param name="mode" type="IN">Indicates if the socked was opened in sync mode or data mode, see RdcyConnectionOpen.
 *	Additional mode is RCOM_DataWork. This mode is used to close a client connection, to make server socket again waiting for 
 *	a new client connection</param>
 * <result>ERR_OK in case of success, other error code in case of error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RdcyConnectionClose',`(RTS_HANDLE hConnection, REDUNDANCY_COMM_MODE mode)')

/**
 * <description>
 *	Return unique address of local device. Used to determine active/standby state in case both devices boot up at the same time. The device with higher address 
 *	will be active. (if devices do not boot up at the same time, first device booting up will be first standalone, and then active when second device boots.
 * </description>
 * <result>Unique address of device as DWORD.</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`RdcyConnectionGetOwnAddress',`(void)')

/**
 * <description>
 *	Receive synchronisation data from partner device. 
 * </description>
 * <param name="hConnection" type="IN">Handle to the connection, previously opened with RdcyConnectionOpen</param>
 * <param name="pbyData" type="IN">Buffer to receive the received data</param>
 * <param name="diDataSize" type="IN">Size of receive buffer, in bytes</param>
 * <param name="pReply" type="IN">Pointer to CLIENT_REPLY structure, containing information about received data</param>
 * <result>TRUE in case of success, FALSE in case of error.</result>
 */
DEF_ITF_API(`RTS_BOOL',`CDECL',`RdcyConnectionReceiveSync',`(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize, CLIENT_REPLY *pReply)')

/**
 * <description>
 *	Determine the number of bytes that can be read. Return 0 if no data is available.
 * </description>
 * <param name="hConnection" type="IN">Handle to the connection, previously opened with RdcyConnectionOpen</param>
 * <param name="ulTimeout" type="IN">Timeout in milliseconds</param>
 * <result>Number of bytes that can be read with a following call of RdcyConnectionReceiveSync.</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`RdcyConnectionGetReceiveSize',`(RTS_HANDLE hConnection, RTS_UI32 ulTimeout)')

/**
 * <description>
 *	Send synchronisation data to partner device. 
 * </description>
 * <param name="hConnection" type="IN">Handle to the connection, previously opened with RdcyConnectionOpen</param>
 * <param name="pbyData" type="IN">Buffer with data to send</param>
 * <param name="diDataSize" type="IN">Size of data to send, in bytes</param>
 * <result>Number of bytes successfully sent. 0 in case of error.</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`RdcyConnectionSendSync',`(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize)')

/**
 * <description>
 *	Receive data from partner device.
 *	To see how much data is in the message, you can cast received bytes to RedundancyTlgHeader and look at member dwLen.
 * </description>
 * <param name="hConnection" type="IN">Handle to the connection, previously opened with RdcyConnectionOpen, in
 *	mode RCOM_DataClient or RCOM_DataServer</param>
 * <param name="pbyData" type="IN">Buffer to receive data</param>
 * <param name="diDataSize" type="IN">Size of receive buffer, in bytes</param>
 * <param name="pReply" type="IN">Pointer to CLIENT_REPLY structure, containing information about received data</param>
 * <param name="ulTimeout" type="IN">Timeout for receiving data</param>
 * <result>Number of bytes successfully read into receive buffer. Return 0 if no data available.</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`RdcyConnectionReceiveData',`(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize, CLIENT_REPLY *pReply, RTS_UI32 ulTimeout)')

/**
 * <description>
 *	Send data to partner device.
 * </description>
 * <param name="hConnection" type="IN">Handle to the connection, previously opened with RdcyConnectionOpen, in
 *	mode RCOM_DataClient or RCOM_DataServer</param>
 * <param name="pbyData" type="IN">Buffer with data to send</param>
 * <param name="diDataSize" type="IN">Size of data to send, in bytes</param>
 * <result>Number of bytes successfully sent. 0 in case of error.</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`RdcyConnectionSendData',`(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize)')

/**
 * <description>
 *	Called when initializing the redundancy component with the redundancy connection settings from the CODESYS control config file.
 *	Connection settings are for e.g. IP / MAC / ... addresses of the redundancy partners, ports, timeouts, ... depending on the used communication.
 * </description>
 * <result>ERR_OK in case of success, ERR_FAILED in case of error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RdcyConnectionReadSettings',`(void)')

/**
 * <description>
 *	Called when service is received to read the redundancy settings from the CODESYS control config file.
 * </description>
 * <param name="pwriter" type="IN">Pointer to the writer to write the settings to.</param>
 * <result>ERR_OK in case of success, ERR_FAILED in case of error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RdcyConnectionSrvReadSettings',`(BINTAGWRITER *pwriter)')

/**
 * <description>
 *	Called when service is received to write the redundancy settings from CODESYS into the CODESYS control config file.
 * </description>
 * <param name="preader" type="IN">Pointer to the reader from which the settings can be read.</param>
 * <result>ERR_OK in case of success, ERR_FAILED in case of error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RdcyConnectionSrvWriteSettings',`(BINTAGREADER *preader)')

/**
 * <description>
 *	This function is used to determine the maximum message size of a data message, including header.
 *	In case of UDP/IP communication, the function will return  0x000001E0
 * </description>
 * <result>Data message size.</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`RdcyConnectionGetSyncMessageSize',`(void)')

/**
 * <description>
 *	This function is used to determine the maximum message size of a data message, including header.
 *	In case of TCP/IP communication, the function will return 0x00005000
 * </description>
 * <result>Data message size.</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`RdcyConnectionGetDataMessageSize',`(void)')

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

