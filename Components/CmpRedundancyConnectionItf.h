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


	
	
#ifndef _CMPREDUNDANCYCONNECTIONITF_H_
#define _CMPREDUNDANCYCONNECTIONITF_H_

#include "CmpStd.h"

 

 




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
RTS_HANDLE CDECL RdcyConnectionOpen(REDUNDANCY_COMM_MODE mode, RTS_UI32 uiMessageSize);
typedef RTS_HANDLE (CDECL * PFRDCYCONNECTIONOPEN) (REDUNDANCY_COMM_MODE mode, RTS_UI32 uiMessageSize);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONOPEN_NOTIMPLEMENTED)
	#define USE_RdcyConnectionOpen
	#define EXT_RdcyConnectionOpen
	#define GET_RdcyConnectionOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionOpen(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_RdcyConnectionOpen  FALSE
	#define EXP_RdcyConnectionOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionOpen
	#define EXT_RdcyConnectionOpen
	#define GET_RdcyConnectionOpen(fl)  CAL_CMGETAPI( "RdcyConnectionOpen" ) 
	#define CAL_RdcyConnectionOpen  RdcyConnectionOpen
	#define CHK_RdcyConnectionOpen  TRUE
	#define EXP_RdcyConnectionOpen  CAL_CMEXPAPI( "RdcyConnectionOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionOpen
	#define EXT_RdcyConnectionOpen
	#define GET_RdcyConnectionOpen(fl)  CAL_CMGETAPI( "RdcyConnectionOpen" ) 
	#define CAL_RdcyConnectionOpen  RdcyConnectionOpen
	#define CHK_RdcyConnectionOpen  TRUE
	#define EXP_RdcyConnectionOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionOpen", (RTS_UINTPTR)RdcyConnectionOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionOpen
	#define EXT_CmpRedundancyConnectionRdcyConnectionOpen
	#define GET_CmpRedundancyConnectionRdcyConnectionOpen  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionOpen pICmpRedundancyConnection->IRdcyConnectionOpen
	#define CHK_CmpRedundancyConnectionRdcyConnectionOpen (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionOpen
	#define EXT_RdcyConnectionOpen
	#define GET_RdcyConnectionOpen(fl)  CAL_CMGETAPI( "RdcyConnectionOpen" ) 
	#define CAL_RdcyConnectionOpen pICmpRedundancyConnection->IRdcyConnectionOpen
	#define CHK_RdcyConnectionOpen (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionOpen  CAL_CMEXPAPI( "RdcyConnectionOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionOpen  PFRDCYCONNECTIONOPEN pfRdcyConnectionOpen;
	#define EXT_RdcyConnectionOpen  extern PFRDCYCONNECTIONOPEN pfRdcyConnectionOpen;
	#define GET_RdcyConnectionOpen(fl)  s_pfCMGetAPI2( "RdcyConnectionOpen", (RTS_VOID_FCTPTR *)&pfRdcyConnectionOpen, (fl), 0, 0)
	#define CAL_RdcyConnectionOpen  pfRdcyConnectionOpen
	#define CHK_RdcyConnectionOpen  (pfRdcyConnectionOpen != NULL)
	#define EXP_RdcyConnectionOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionOpen", (RTS_UINTPTR)RdcyConnectionOpen, 0, 0) 
#endif




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
RTS_RESULT CDECL RdcyConnectionClose(RTS_HANDLE hConnection, REDUNDANCY_COMM_MODE mode);
typedef RTS_RESULT (CDECL * PFRDCYCONNECTIONCLOSE) (RTS_HANDLE hConnection, REDUNDANCY_COMM_MODE mode);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONCLOSE_NOTIMPLEMENTED)
	#define USE_RdcyConnectionClose
	#define EXT_RdcyConnectionClose
	#define GET_RdcyConnectionClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionClose(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionClose  FALSE
	#define EXP_RdcyConnectionClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionClose
	#define EXT_RdcyConnectionClose
	#define GET_RdcyConnectionClose(fl)  CAL_CMGETAPI( "RdcyConnectionClose" ) 
	#define CAL_RdcyConnectionClose  RdcyConnectionClose
	#define CHK_RdcyConnectionClose  TRUE
	#define EXP_RdcyConnectionClose  CAL_CMEXPAPI( "RdcyConnectionClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionClose
	#define EXT_RdcyConnectionClose
	#define GET_RdcyConnectionClose(fl)  CAL_CMGETAPI( "RdcyConnectionClose" ) 
	#define CAL_RdcyConnectionClose  RdcyConnectionClose
	#define CHK_RdcyConnectionClose  TRUE
	#define EXP_RdcyConnectionClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionClose", (RTS_UINTPTR)RdcyConnectionClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionClose
	#define EXT_CmpRedundancyConnectionRdcyConnectionClose
	#define GET_CmpRedundancyConnectionRdcyConnectionClose  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionClose pICmpRedundancyConnection->IRdcyConnectionClose
	#define CHK_CmpRedundancyConnectionRdcyConnectionClose (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionClose
	#define EXT_RdcyConnectionClose
	#define GET_RdcyConnectionClose(fl)  CAL_CMGETAPI( "RdcyConnectionClose" ) 
	#define CAL_RdcyConnectionClose pICmpRedundancyConnection->IRdcyConnectionClose
	#define CHK_RdcyConnectionClose (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionClose  CAL_CMEXPAPI( "RdcyConnectionClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionClose  PFRDCYCONNECTIONCLOSE pfRdcyConnectionClose;
	#define EXT_RdcyConnectionClose  extern PFRDCYCONNECTIONCLOSE pfRdcyConnectionClose;
	#define GET_RdcyConnectionClose(fl)  s_pfCMGetAPI2( "RdcyConnectionClose", (RTS_VOID_FCTPTR *)&pfRdcyConnectionClose, (fl), 0, 0)
	#define CAL_RdcyConnectionClose  pfRdcyConnectionClose
	#define CHK_RdcyConnectionClose  (pfRdcyConnectionClose != NULL)
	#define EXP_RdcyConnectionClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionClose", (RTS_UINTPTR)RdcyConnectionClose, 0, 0) 
#endif




/**
 * <description>
 *	Return unique address of local device. Used to determine active/standby state in case both devices boot up at the same time. The device with higher address 
 *	will be active. (if devices do not boot up at the same time, first device booting up will be first standalone, and then active when second device boots.
 * </description>
 * <result>Unique address of device as DWORD.</result>
 */
RTS_UI32 CDECL RdcyConnectionGetOwnAddress(void);
typedef RTS_UI32 (CDECL * PFRDCYCONNECTIONGETOWNADDRESS) (void);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONGETOWNADDRESS_NOTIMPLEMENTED)
	#define USE_RdcyConnectionGetOwnAddress
	#define EXT_RdcyConnectionGetOwnAddress
	#define GET_RdcyConnectionGetOwnAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionGetOwnAddress()  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionGetOwnAddress  FALSE
	#define EXP_RdcyConnectionGetOwnAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionGetOwnAddress
	#define EXT_RdcyConnectionGetOwnAddress
	#define GET_RdcyConnectionGetOwnAddress(fl)  CAL_CMGETAPI( "RdcyConnectionGetOwnAddress" ) 
	#define CAL_RdcyConnectionGetOwnAddress  RdcyConnectionGetOwnAddress
	#define CHK_RdcyConnectionGetOwnAddress  TRUE
	#define EXP_RdcyConnectionGetOwnAddress  CAL_CMEXPAPI( "RdcyConnectionGetOwnAddress" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionGetOwnAddress
	#define EXT_RdcyConnectionGetOwnAddress
	#define GET_RdcyConnectionGetOwnAddress(fl)  CAL_CMGETAPI( "RdcyConnectionGetOwnAddress" ) 
	#define CAL_RdcyConnectionGetOwnAddress  RdcyConnectionGetOwnAddress
	#define CHK_RdcyConnectionGetOwnAddress  TRUE
	#define EXP_RdcyConnectionGetOwnAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionGetOwnAddress", (RTS_UINTPTR)RdcyConnectionGetOwnAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionGetOwnAddress
	#define EXT_CmpRedundancyConnectionRdcyConnectionGetOwnAddress
	#define GET_CmpRedundancyConnectionRdcyConnectionGetOwnAddress  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionGetOwnAddress pICmpRedundancyConnection->IRdcyConnectionGetOwnAddress
	#define CHK_CmpRedundancyConnectionRdcyConnectionGetOwnAddress (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionGetOwnAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionGetOwnAddress
	#define EXT_RdcyConnectionGetOwnAddress
	#define GET_RdcyConnectionGetOwnAddress(fl)  CAL_CMGETAPI( "RdcyConnectionGetOwnAddress" ) 
	#define CAL_RdcyConnectionGetOwnAddress pICmpRedundancyConnection->IRdcyConnectionGetOwnAddress
	#define CHK_RdcyConnectionGetOwnAddress (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionGetOwnAddress  CAL_CMEXPAPI( "RdcyConnectionGetOwnAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionGetOwnAddress  PFRDCYCONNECTIONGETOWNADDRESS pfRdcyConnectionGetOwnAddress;
	#define EXT_RdcyConnectionGetOwnAddress  extern PFRDCYCONNECTIONGETOWNADDRESS pfRdcyConnectionGetOwnAddress;
	#define GET_RdcyConnectionGetOwnAddress(fl)  s_pfCMGetAPI2( "RdcyConnectionGetOwnAddress", (RTS_VOID_FCTPTR *)&pfRdcyConnectionGetOwnAddress, (fl), 0, 0)
	#define CAL_RdcyConnectionGetOwnAddress  pfRdcyConnectionGetOwnAddress
	#define CHK_RdcyConnectionGetOwnAddress  (pfRdcyConnectionGetOwnAddress != NULL)
	#define EXP_RdcyConnectionGetOwnAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionGetOwnAddress", (RTS_UINTPTR)RdcyConnectionGetOwnAddress, 0, 0) 
#endif




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
RTS_BOOL CDECL RdcyConnectionReceiveSync(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize, CLIENT_REPLY *pReply);
typedef RTS_BOOL (CDECL * PFRDCYCONNECTIONRECEIVESYNC) (RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize, CLIENT_REPLY *pReply);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONRECEIVESYNC_NOTIMPLEMENTED)
	#define USE_RdcyConnectionReceiveSync
	#define EXT_RdcyConnectionReceiveSync
	#define GET_RdcyConnectionReceiveSync(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionReceiveSync(p0,p1,p2,p3)  (RTS_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionReceiveSync  FALSE
	#define EXP_RdcyConnectionReceiveSync  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionReceiveSync
	#define EXT_RdcyConnectionReceiveSync
	#define GET_RdcyConnectionReceiveSync(fl)  CAL_CMGETAPI( "RdcyConnectionReceiveSync" ) 
	#define CAL_RdcyConnectionReceiveSync  RdcyConnectionReceiveSync
	#define CHK_RdcyConnectionReceiveSync  TRUE
	#define EXP_RdcyConnectionReceiveSync  CAL_CMEXPAPI( "RdcyConnectionReceiveSync" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionReceiveSync
	#define EXT_RdcyConnectionReceiveSync
	#define GET_RdcyConnectionReceiveSync(fl)  CAL_CMGETAPI( "RdcyConnectionReceiveSync" ) 
	#define CAL_RdcyConnectionReceiveSync  RdcyConnectionReceiveSync
	#define CHK_RdcyConnectionReceiveSync  TRUE
	#define EXP_RdcyConnectionReceiveSync  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionReceiveSync", (RTS_UINTPTR)RdcyConnectionReceiveSync, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionReceiveSync
	#define EXT_CmpRedundancyConnectionRdcyConnectionReceiveSync
	#define GET_CmpRedundancyConnectionRdcyConnectionReceiveSync  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionReceiveSync pICmpRedundancyConnection->IRdcyConnectionReceiveSync
	#define CHK_CmpRedundancyConnectionRdcyConnectionReceiveSync (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionReceiveSync  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionReceiveSync
	#define EXT_RdcyConnectionReceiveSync
	#define GET_RdcyConnectionReceiveSync(fl)  CAL_CMGETAPI( "RdcyConnectionReceiveSync" ) 
	#define CAL_RdcyConnectionReceiveSync pICmpRedundancyConnection->IRdcyConnectionReceiveSync
	#define CHK_RdcyConnectionReceiveSync (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionReceiveSync  CAL_CMEXPAPI( "RdcyConnectionReceiveSync" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionReceiveSync  PFRDCYCONNECTIONRECEIVESYNC pfRdcyConnectionReceiveSync;
	#define EXT_RdcyConnectionReceiveSync  extern PFRDCYCONNECTIONRECEIVESYNC pfRdcyConnectionReceiveSync;
	#define GET_RdcyConnectionReceiveSync(fl)  s_pfCMGetAPI2( "RdcyConnectionReceiveSync", (RTS_VOID_FCTPTR *)&pfRdcyConnectionReceiveSync, (fl), 0, 0)
	#define CAL_RdcyConnectionReceiveSync  pfRdcyConnectionReceiveSync
	#define CHK_RdcyConnectionReceiveSync  (pfRdcyConnectionReceiveSync != NULL)
	#define EXP_RdcyConnectionReceiveSync  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionReceiveSync", (RTS_UINTPTR)RdcyConnectionReceiveSync, 0, 0) 
#endif




/**
 * <description>
 *	Determine the number of bytes that can be read. Return 0 if no data is available.
 * </description>
 * <param name="hConnection" type="IN">Handle to the connection, previously opened with RdcyConnectionOpen</param>
 * <param name="ulTimeout" type="IN">Timeout in milliseconds</param>
 * <result>Number of bytes that can be read with a following call of RdcyConnectionReceiveSync.</result>
 */
RTS_UI32 CDECL RdcyConnectionGetReceiveSize(RTS_HANDLE hConnection, RTS_UI32 ulTimeout);
typedef RTS_UI32 (CDECL * PFRDCYCONNECTIONGETRECEIVESIZE) (RTS_HANDLE hConnection, RTS_UI32 ulTimeout);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONGETRECEIVESIZE_NOTIMPLEMENTED)
	#define USE_RdcyConnectionGetReceiveSize
	#define EXT_RdcyConnectionGetReceiveSize
	#define GET_RdcyConnectionGetReceiveSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionGetReceiveSize(p0,p1)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionGetReceiveSize  FALSE
	#define EXP_RdcyConnectionGetReceiveSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionGetReceiveSize
	#define EXT_RdcyConnectionGetReceiveSize
	#define GET_RdcyConnectionGetReceiveSize(fl)  CAL_CMGETAPI( "RdcyConnectionGetReceiveSize" ) 
	#define CAL_RdcyConnectionGetReceiveSize  RdcyConnectionGetReceiveSize
	#define CHK_RdcyConnectionGetReceiveSize  TRUE
	#define EXP_RdcyConnectionGetReceiveSize  CAL_CMEXPAPI( "RdcyConnectionGetReceiveSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionGetReceiveSize
	#define EXT_RdcyConnectionGetReceiveSize
	#define GET_RdcyConnectionGetReceiveSize(fl)  CAL_CMGETAPI( "RdcyConnectionGetReceiveSize" ) 
	#define CAL_RdcyConnectionGetReceiveSize  RdcyConnectionGetReceiveSize
	#define CHK_RdcyConnectionGetReceiveSize  TRUE
	#define EXP_RdcyConnectionGetReceiveSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionGetReceiveSize", (RTS_UINTPTR)RdcyConnectionGetReceiveSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionGetReceiveSize
	#define EXT_CmpRedundancyConnectionRdcyConnectionGetReceiveSize
	#define GET_CmpRedundancyConnectionRdcyConnectionGetReceiveSize  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionGetReceiveSize pICmpRedundancyConnection->IRdcyConnectionGetReceiveSize
	#define CHK_CmpRedundancyConnectionRdcyConnectionGetReceiveSize (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionGetReceiveSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionGetReceiveSize
	#define EXT_RdcyConnectionGetReceiveSize
	#define GET_RdcyConnectionGetReceiveSize(fl)  CAL_CMGETAPI( "RdcyConnectionGetReceiveSize" ) 
	#define CAL_RdcyConnectionGetReceiveSize pICmpRedundancyConnection->IRdcyConnectionGetReceiveSize
	#define CHK_RdcyConnectionGetReceiveSize (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionGetReceiveSize  CAL_CMEXPAPI( "RdcyConnectionGetReceiveSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionGetReceiveSize  PFRDCYCONNECTIONGETRECEIVESIZE pfRdcyConnectionGetReceiveSize;
	#define EXT_RdcyConnectionGetReceiveSize  extern PFRDCYCONNECTIONGETRECEIVESIZE pfRdcyConnectionGetReceiveSize;
	#define GET_RdcyConnectionGetReceiveSize(fl)  s_pfCMGetAPI2( "RdcyConnectionGetReceiveSize", (RTS_VOID_FCTPTR *)&pfRdcyConnectionGetReceiveSize, (fl), 0, 0)
	#define CAL_RdcyConnectionGetReceiveSize  pfRdcyConnectionGetReceiveSize
	#define CHK_RdcyConnectionGetReceiveSize  (pfRdcyConnectionGetReceiveSize != NULL)
	#define EXP_RdcyConnectionGetReceiveSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionGetReceiveSize", (RTS_UINTPTR)RdcyConnectionGetReceiveSize, 0, 0) 
#endif




/**
 * <description>
 *	Send synchronisation data to partner device. 
 * </description>
 * <param name="hConnection" type="IN">Handle to the connection, previously opened with RdcyConnectionOpen</param>
 * <param name="pbyData" type="IN">Buffer with data to send</param>
 * <param name="diDataSize" type="IN">Size of data to send, in bytes</param>
 * <result>Number of bytes successfully sent. 0 in case of error.</result>
 */
RTS_UI32 CDECL RdcyConnectionSendSync(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize);
typedef RTS_UI32 (CDECL * PFRDCYCONNECTIONSENDSYNC) (RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONSENDSYNC_NOTIMPLEMENTED)
	#define USE_RdcyConnectionSendSync
	#define EXT_RdcyConnectionSendSync
	#define GET_RdcyConnectionSendSync(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionSendSync(p0,p1,p2)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionSendSync  FALSE
	#define EXP_RdcyConnectionSendSync  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionSendSync
	#define EXT_RdcyConnectionSendSync
	#define GET_RdcyConnectionSendSync(fl)  CAL_CMGETAPI( "RdcyConnectionSendSync" ) 
	#define CAL_RdcyConnectionSendSync  RdcyConnectionSendSync
	#define CHK_RdcyConnectionSendSync  TRUE
	#define EXP_RdcyConnectionSendSync  CAL_CMEXPAPI( "RdcyConnectionSendSync" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionSendSync
	#define EXT_RdcyConnectionSendSync
	#define GET_RdcyConnectionSendSync(fl)  CAL_CMGETAPI( "RdcyConnectionSendSync" ) 
	#define CAL_RdcyConnectionSendSync  RdcyConnectionSendSync
	#define CHK_RdcyConnectionSendSync  TRUE
	#define EXP_RdcyConnectionSendSync  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionSendSync", (RTS_UINTPTR)RdcyConnectionSendSync, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionSendSync
	#define EXT_CmpRedundancyConnectionRdcyConnectionSendSync
	#define GET_CmpRedundancyConnectionRdcyConnectionSendSync  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionSendSync pICmpRedundancyConnection->IRdcyConnectionSendSync
	#define CHK_CmpRedundancyConnectionRdcyConnectionSendSync (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionSendSync  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionSendSync
	#define EXT_RdcyConnectionSendSync
	#define GET_RdcyConnectionSendSync(fl)  CAL_CMGETAPI( "RdcyConnectionSendSync" ) 
	#define CAL_RdcyConnectionSendSync pICmpRedundancyConnection->IRdcyConnectionSendSync
	#define CHK_RdcyConnectionSendSync (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionSendSync  CAL_CMEXPAPI( "RdcyConnectionSendSync" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionSendSync  PFRDCYCONNECTIONSENDSYNC pfRdcyConnectionSendSync;
	#define EXT_RdcyConnectionSendSync  extern PFRDCYCONNECTIONSENDSYNC pfRdcyConnectionSendSync;
	#define GET_RdcyConnectionSendSync(fl)  s_pfCMGetAPI2( "RdcyConnectionSendSync", (RTS_VOID_FCTPTR *)&pfRdcyConnectionSendSync, (fl), 0, 0)
	#define CAL_RdcyConnectionSendSync  pfRdcyConnectionSendSync
	#define CHK_RdcyConnectionSendSync  (pfRdcyConnectionSendSync != NULL)
	#define EXP_RdcyConnectionSendSync  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionSendSync", (RTS_UINTPTR)RdcyConnectionSendSync, 0, 0) 
#endif




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
RTS_UI32 CDECL RdcyConnectionReceiveData(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize, CLIENT_REPLY *pReply, RTS_UI32 ulTimeout);
typedef RTS_UI32 (CDECL * PFRDCYCONNECTIONRECEIVEDATA) (RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize, CLIENT_REPLY *pReply, RTS_UI32 ulTimeout);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONRECEIVEDATA_NOTIMPLEMENTED)
	#define USE_RdcyConnectionReceiveData
	#define EXT_RdcyConnectionReceiveData
	#define GET_RdcyConnectionReceiveData(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionReceiveData(p0,p1,p2,p3,p4)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionReceiveData  FALSE
	#define EXP_RdcyConnectionReceiveData  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionReceiveData
	#define EXT_RdcyConnectionReceiveData
	#define GET_RdcyConnectionReceiveData(fl)  CAL_CMGETAPI( "RdcyConnectionReceiveData" ) 
	#define CAL_RdcyConnectionReceiveData  RdcyConnectionReceiveData
	#define CHK_RdcyConnectionReceiveData  TRUE
	#define EXP_RdcyConnectionReceiveData  CAL_CMEXPAPI( "RdcyConnectionReceiveData" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionReceiveData
	#define EXT_RdcyConnectionReceiveData
	#define GET_RdcyConnectionReceiveData(fl)  CAL_CMGETAPI( "RdcyConnectionReceiveData" ) 
	#define CAL_RdcyConnectionReceiveData  RdcyConnectionReceiveData
	#define CHK_RdcyConnectionReceiveData  TRUE
	#define EXP_RdcyConnectionReceiveData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionReceiveData", (RTS_UINTPTR)RdcyConnectionReceiveData, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionReceiveData
	#define EXT_CmpRedundancyConnectionRdcyConnectionReceiveData
	#define GET_CmpRedundancyConnectionRdcyConnectionReceiveData  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionReceiveData pICmpRedundancyConnection->IRdcyConnectionReceiveData
	#define CHK_CmpRedundancyConnectionRdcyConnectionReceiveData (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionReceiveData  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionReceiveData
	#define EXT_RdcyConnectionReceiveData
	#define GET_RdcyConnectionReceiveData(fl)  CAL_CMGETAPI( "RdcyConnectionReceiveData" ) 
	#define CAL_RdcyConnectionReceiveData pICmpRedundancyConnection->IRdcyConnectionReceiveData
	#define CHK_RdcyConnectionReceiveData (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionReceiveData  CAL_CMEXPAPI( "RdcyConnectionReceiveData" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionReceiveData  PFRDCYCONNECTIONRECEIVEDATA pfRdcyConnectionReceiveData;
	#define EXT_RdcyConnectionReceiveData  extern PFRDCYCONNECTIONRECEIVEDATA pfRdcyConnectionReceiveData;
	#define GET_RdcyConnectionReceiveData(fl)  s_pfCMGetAPI2( "RdcyConnectionReceiveData", (RTS_VOID_FCTPTR *)&pfRdcyConnectionReceiveData, (fl), 0, 0)
	#define CAL_RdcyConnectionReceiveData  pfRdcyConnectionReceiveData
	#define CHK_RdcyConnectionReceiveData  (pfRdcyConnectionReceiveData != NULL)
	#define EXP_RdcyConnectionReceiveData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionReceiveData", (RTS_UINTPTR)RdcyConnectionReceiveData, 0, 0) 
#endif




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
RTS_UI32 CDECL RdcyConnectionSendData(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize);
typedef RTS_UI32 (CDECL * PFRDCYCONNECTIONSENDDATA) (RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONSENDDATA_NOTIMPLEMENTED)
	#define USE_RdcyConnectionSendData
	#define EXT_RdcyConnectionSendData
	#define GET_RdcyConnectionSendData(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionSendData(p0,p1,p2)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionSendData  FALSE
	#define EXP_RdcyConnectionSendData  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionSendData
	#define EXT_RdcyConnectionSendData
	#define GET_RdcyConnectionSendData(fl)  CAL_CMGETAPI( "RdcyConnectionSendData" ) 
	#define CAL_RdcyConnectionSendData  RdcyConnectionSendData
	#define CHK_RdcyConnectionSendData  TRUE
	#define EXP_RdcyConnectionSendData  CAL_CMEXPAPI( "RdcyConnectionSendData" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionSendData
	#define EXT_RdcyConnectionSendData
	#define GET_RdcyConnectionSendData(fl)  CAL_CMGETAPI( "RdcyConnectionSendData" ) 
	#define CAL_RdcyConnectionSendData  RdcyConnectionSendData
	#define CHK_RdcyConnectionSendData  TRUE
	#define EXP_RdcyConnectionSendData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionSendData", (RTS_UINTPTR)RdcyConnectionSendData, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionSendData
	#define EXT_CmpRedundancyConnectionRdcyConnectionSendData
	#define GET_CmpRedundancyConnectionRdcyConnectionSendData  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionSendData pICmpRedundancyConnection->IRdcyConnectionSendData
	#define CHK_CmpRedundancyConnectionRdcyConnectionSendData (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionSendData  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionSendData
	#define EXT_RdcyConnectionSendData
	#define GET_RdcyConnectionSendData(fl)  CAL_CMGETAPI( "RdcyConnectionSendData" ) 
	#define CAL_RdcyConnectionSendData pICmpRedundancyConnection->IRdcyConnectionSendData
	#define CHK_RdcyConnectionSendData (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionSendData  CAL_CMEXPAPI( "RdcyConnectionSendData" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionSendData  PFRDCYCONNECTIONSENDDATA pfRdcyConnectionSendData;
	#define EXT_RdcyConnectionSendData  extern PFRDCYCONNECTIONSENDDATA pfRdcyConnectionSendData;
	#define GET_RdcyConnectionSendData(fl)  s_pfCMGetAPI2( "RdcyConnectionSendData", (RTS_VOID_FCTPTR *)&pfRdcyConnectionSendData, (fl), 0, 0)
	#define CAL_RdcyConnectionSendData  pfRdcyConnectionSendData
	#define CHK_RdcyConnectionSendData  (pfRdcyConnectionSendData != NULL)
	#define EXP_RdcyConnectionSendData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionSendData", (RTS_UINTPTR)RdcyConnectionSendData, 0, 0) 
#endif




/**
 * <description>
 *	Called when initializing the redundancy component with the redundancy connection settings from the CODESYS control config file.
 *	Connection settings are for e.g. IP / MAC / ... addresses of the redundancy partners, ports, timeouts, ... depending on the used communication.
 * </description>
 * <result>ERR_OK in case of success, ERR_FAILED in case of error.</result>
 */
RTS_RESULT CDECL RdcyConnectionReadSettings(void);
typedef RTS_RESULT (CDECL * PFRDCYCONNECTIONREADSETTINGS) (void);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONREADSETTINGS_NOTIMPLEMENTED)
	#define USE_RdcyConnectionReadSettings
	#define EXT_RdcyConnectionReadSettings
	#define GET_RdcyConnectionReadSettings(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionReadSettings()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionReadSettings  FALSE
	#define EXP_RdcyConnectionReadSettings  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionReadSettings
	#define EXT_RdcyConnectionReadSettings
	#define GET_RdcyConnectionReadSettings(fl)  CAL_CMGETAPI( "RdcyConnectionReadSettings" ) 
	#define CAL_RdcyConnectionReadSettings  RdcyConnectionReadSettings
	#define CHK_RdcyConnectionReadSettings  TRUE
	#define EXP_RdcyConnectionReadSettings  CAL_CMEXPAPI( "RdcyConnectionReadSettings" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionReadSettings
	#define EXT_RdcyConnectionReadSettings
	#define GET_RdcyConnectionReadSettings(fl)  CAL_CMGETAPI( "RdcyConnectionReadSettings" ) 
	#define CAL_RdcyConnectionReadSettings  RdcyConnectionReadSettings
	#define CHK_RdcyConnectionReadSettings  TRUE
	#define EXP_RdcyConnectionReadSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionReadSettings", (RTS_UINTPTR)RdcyConnectionReadSettings, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionReadSettings
	#define EXT_CmpRedundancyConnectionRdcyConnectionReadSettings
	#define GET_CmpRedundancyConnectionRdcyConnectionReadSettings  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionReadSettings pICmpRedundancyConnection->IRdcyConnectionReadSettings
	#define CHK_CmpRedundancyConnectionRdcyConnectionReadSettings (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionReadSettings  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionReadSettings
	#define EXT_RdcyConnectionReadSettings
	#define GET_RdcyConnectionReadSettings(fl)  CAL_CMGETAPI( "RdcyConnectionReadSettings" ) 
	#define CAL_RdcyConnectionReadSettings pICmpRedundancyConnection->IRdcyConnectionReadSettings
	#define CHK_RdcyConnectionReadSettings (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionReadSettings  CAL_CMEXPAPI( "RdcyConnectionReadSettings" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionReadSettings  PFRDCYCONNECTIONREADSETTINGS pfRdcyConnectionReadSettings;
	#define EXT_RdcyConnectionReadSettings  extern PFRDCYCONNECTIONREADSETTINGS pfRdcyConnectionReadSettings;
	#define GET_RdcyConnectionReadSettings(fl)  s_pfCMGetAPI2( "RdcyConnectionReadSettings", (RTS_VOID_FCTPTR *)&pfRdcyConnectionReadSettings, (fl), 0, 0)
	#define CAL_RdcyConnectionReadSettings  pfRdcyConnectionReadSettings
	#define CHK_RdcyConnectionReadSettings  (pfRdcyConnectionReadSettings != NULL)
	#define EXP_RdcyConnectionReadSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionReadSettings", (RTS_UINTPTR)RdcyConnectionReadSettings, 0, 0) 
#endif




/**
 * <description>
 *	Called when service is received to read the redundancy settings from the CODESYS control config file.
 * </description>
 * <param name="pwriter" type="IN">Pointer to the writer to write the settings to.</param>
 * <result>ERR_OK in case of success, ERR_FAILED in case of error.</result>
 */
RTS_RESULT CDECL RdcyConnectionSrvReadSettings(BINTAGWRITER *pwriter);
typedef RTS_RESULT (CDECL * PFRDCYCONNECTIONSRVREADSETTINGS) (BINTAGWRITER *pwriter);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONSRVREADSETTINGS_NOTIMPLEMENTED)
	#define USE_RdcyConnectionSrvReadSettings
	#define EXT_RdcyConnectionSrvReadSettings
	#define GET_RdcyConnectionSrvReadSettings(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionSrvReadSettings(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionSrvReadSettings  FALSE
	#define EXP_RdcyConnectionSrvReadSettings  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionSrvReadSettings
	#define EXT_RdcyConnectionSrvReadSettings
	#define GET_RdcyConnectionSrvReadSettings(fl)  CAL_CMGETAPI( "RdcyConnectionSrvReadSettings" ) 
	#define CAL_RdcyConnectionSrvReadSettings  RdcyConnectionSrvReadSettings
	#define CHK_RdcyConnectionSrvReadSettings  TRUE
	#define EXP_RdcyConnectionSrvReadSettings  CAL_CMEXPAPI( "RdcyConnectionSrvReadSettings" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionSrvReadSettings
	#define EXT_RdcyConnectionSrvReadSettings
	#define GET_RdcyConnectionSrvReadSettings(fl)  CAL_CMGETAPI( "RdcyConnectionSrvReadSettings" ) 
	#define CAL_RdcyConnectionSrvReadSettings  RdcyConnectionSrvReadSettings
	#define CHK_RdcyConnectionSrvReadSettings  TRUE
	#define EXP_RdcyConnectionSrvReadSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionSrvReadSettings", (RTS_UINTPTR)RdcyConnectionSrvReadSettings, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionSrvReadSettings
	#define EXT_CmpRedundancyConnectionRdcyConnectionSrvReadSettings
	#define GET_CmpRedundancyConnectionRdcyConnectionSrvReadSettings  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionSrvReadSettings pICmpRedundancyConnection->IRdcyConnectionSrvReadSettings
	#define CHK_CmpRedundancyConnectionRdcyConnectionSrvReadSettings (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionSrvReadSettings  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionSrvReadSettings
	#define EXT_RdcyConnectionSrvReadSettings
	#define GET_RdcyConnectionSrvReadSettings(fl)  CAL_CMGETAPI( "RdcyConnectionSrvReadSettings" ) 
	#define CAL_RdcyConnectionSrvReadSettings pICmpRedundancyConnection->IRdcyConnectionSrvReadSettings
	#define CHK_RdcyConnectionSrvReadSettings (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionSrvReadSettings  CAL_CMEXPAPI( "RdcyConnectionSrvReadSettings" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionSrvReadSettings  PFRDCYCONNECTIONSRVREADSETTINGS pfRdcyConnectionSrvReadSettings;
	#define EXT_RdcyConnectionSrvReadSettings  extern PFRDCYCONNECTIONSRVREADSETTINGS pfRdcyConnectionSrvReadSettings;
	#define GET_RdcyConnectionSrvReadSettings(fl)  s_pfCMGetAPI2( "RdcyConnectionSrvReadSettings", (RTS_VOID_FCTPTR *)&pfRdcyConnectionSrvReadSettings, (fl), 0, 0)
	#define CAL_RdcyConnectionSrvReadSettings  pfRdcyConnectionSrvReadSettings
	#define CHK_RdcyConnectionSrvReadSettings  (pfRdcyConnectionSrvReadSettings != NULL)
	#define EXP_RdcyConnectionSrvReadSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionSrvReadSettings", (RTS_UINTPTR)RdcyConnectionSrvReadSettings, 0, 0) 
#endif




/**
 * <description>
 *	Called when service is received to write the redundancy settings from CODESYS into the CODESYS control config file.
 * </description>
 * <param name="preader" type="IN">Pointer to the reader from which the settings can be read.</param>
 * <result>ERR_OK in case of success, ERR_FAILED in case of error.</result>
 */
RTS_RESULT CDECL RdcyConnectionSrvWriteSettings(BINTAGREADER *preader);
typedef RTS_RESULT (CDECL * PFRDCYCONNECTIONSRVWRITESETTINGS) (BINTAGREADER *preader);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONSRVWRITESETTINGS_NOTIMPLEMENTED)
	#define USE_RdcyConnectionSrvWriteSettings
	#define EXT_RdcyConnectionSrvWriteSettings
	#define GET_RdcyConnectionSrvWriteSettings(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionSrvWriteSettings(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionSrvWriteSettings  FALSE
	#define EXP_RdcyConnectionSrvWriteSettings  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionSrvWriteSettings
	#define EXT_RdcyConnectionSrvWriteSettings
	#define GET_RdcyConnectionSrvWriteSettings(fl)  CAL_CMGETAPI( "RdcyConnectionSrvWriteSettings" ) 
	#define CAL_RdcyConnectionSrvWriteSettings  RdcyConnectionSrvWriteSettings
	#define CHK_RdcyConnectionSrvWriteSettings  TRUE
	#define EXP_RdcyConnectionSrvWriteSettings  CAL_CMEXPAPI( "RdcyConnectionSrvWriteSettings" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionSrvWriteSettings
	#define EXT_RdcyConnectionSrvWriteSettings
	#define GET_RdcyConnectionSrvWriteSettings(fl)  CAL_CMGETAPI( "RdcyConnectionSrvWriteSettings" ) 
	#define CAL_RdcyConnectionSrvWriteSettings  RdcyConnectionSrvWriteSettings
	#define CHK_RdcyConnectionSrvWriteSettings  TRUE
	#define EXP_RdcyConnectionSrvWriteSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionSrvWriteSettings", (RTS_UINTPTR)RdcyConnectionSrvWriteSettings, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionSrvWriteSettings
	#define EXT_CmpRedundancyConnectionRdcyConnectionSrvWriteSettings
	#define GET_CmpRedundancyConnectionRdcyConnectionSrvWriteSettings  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionSrvWriteSettings pICmpRedundancyConnection->IRdcyConnectionSrvWriteSettings
	#define CHK_CmpRedundancyConnectionRdcyConnectionSrvWriteSettings (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionSrvWriteSettings  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionSrvWriteSettings
	#define EXT_RdcyConnectionSrvWriteSettings
	#define GET_RdcyConnectionSrvWriteSettings(fl)  CAL_CMGETAPI( "RdcyConnectionSrvWriteSettings" ) 
	#define CAL_RdcyConnectionSrvWriteSettings pICmpRedundancyConnection->IRdcyConnectionSrvWriteSettings
	#define CHK_RdcyConnectionSrvWriteSettings (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionSrvWriteSettings  CAL_CMEXPAPI( "RdcyConnectionSrvWriteSettings" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionSrvWriteSettings  PFRDCYCONNECTIONSRVWRITESETTINGS pfRdcyConnectionSrvWriteSettings;
	#define EXT_RdcyConnectionSrvWriteSettings  extern PFRDCYCONNECTIONSRVWRITESETTINGS pfRdcyConnectionSrvWriteSettings;
	#define GET_RdcyConnectionSrvWriteSettings(fl)  s_pfCMGetAPI2( "RdcyConnectionSrvWriteSettings", (RTS_VOID_FCTPTR *)&pfRdcyConnectionSrvWriteSettings, (fl), 0, 0)
	#define CAL_RdcyConnectionSrvWriteSettings  pfRdcyConnectionSrvWriteSettings
	#define CHK_RdcyConnectionSrvWriteSettings  (pfRdcyConnectionSrvWriteSettings != NULL)
	#define EXP_RdcyConnectionSrvWriteSettings  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionSrvWriteSettings", (RTS_UINTPTR)RdcyConnectionSrvWriteSettings, 0, 0) 
#endif




/**
 * <description>
 *	This function is used to determine the maximum message size of a data message, including header.
 *	In case of UDP/IP communication, the function will return  0x000001E0
 * </description>
 * <result>Data message size.</result>
 */
RTS_UI32 CDECL RdcyConnectionGetSyncMessageSize(void);
typedef RTS_UI32 (CDECL * PFRDCYCONNECTIONGETSYNCMESSAGESIZE) (void);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONGETSYNCMESSAGESIZE_NOTIMPLEMENTED)
	#define USE_RdcyConnectionGetSyncMessageSize
	#define EXT_RdcyConnectionGetSyncMessageSize
	#define GET_RdcyConnectionGetSyncMessageSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionGetSyncMessageSize()  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionGetSyncMessageSize  FALSE
	#define EXP_RdcyConnectionGetSyncMessageSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionGetSyncMessageSize
	#define EXT_RdcyConnectionGetSyncMessageSize
	#define GET_RdcyConnectionGetSyncMessageSize(fl)  CAL_CMGETAPI( "RdcyConnectionGetSyncMessageSize" ) 
	#define CAL_RdcyConnectionGetSyncMessageSize  RdcyConnectionGetSyncMessageSize
	#define CHK_RdcyConnectionGetSyncMessageSize  TRUE
	#define EXP_RdcyConnectionGetSyncMessageSize  CAL_CMEXPAPI( "RdcyConnectionGetSyncMessageSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionGetSyncMessageSize
	#define EXT_RdcyConnectionGetSyncMessageSize
	#define GET_RdcyConnectionGetSyncMessageSize(fl)  CAL_CMGETAPI( "RdcyConnectionGetSyncMessageSize" ) 
	#define CAL_RdcyConnectionGetSyncMessageSize  RdcyConnectionGetSyncMessageSize
	#define CHK_RdcyConnectionGetSyncMessageSize  TRUE
	#define EXP_RdcyConnectionGetSyncMessageSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionGetSyncMessageSize", (RTS_UINTPTR)RdcyConnectionGetSyncMessageSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionGetSyncMessageSize
	#define EXT_CmpRedundancyConnectionRdcyConnectionGetSyncMessageSize
	#define GET_CmpRedundancyConnectionRdcyConnectionGetSyncMessageSize  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionGetSyncMessageSize pICmpRedundancyConnection->IRdcyConnectionGetSyncMessageSize
	#define CHK_CmpRedundancyConnectionRdcyConnectionGetSyncMessageSize (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionGetSyncMessageSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionGetSyncMessageSize
	#define EXT_RdcyConnectionGetSyncMessageSize
	#define GET_RdcyConnectionGetSyncMessageSize(fl)  CAL_CMGETAPI( "RdcyConnectionGetSyncMessageSize" ) 
	#define CAL_RdcyConnectionGetSyncMessageSize pICmpRedundancyConnection->IRdcyConnectionGetSyncMessageSize
	#define CHK_RdcyConnectionGetSyncMessageSize (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionGetSyncMessageSize  CAL_CMEXPAPI( "RdcyConnectionGetSyncMessageSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionGetSyncMessageSize  PFRDCYCONNECTIONGETSYNCMESSAGESIZE pfRdcyConnectionGetSyncMessageSize;
	#define EXT_RdcyConnectionGetSyncMessageSize  extern PFRDCYCONNECTIONGETSYNCMESSAGESIZE pfRdcyConnectionGetSyncMessageSize;
	#define GET_RdcyConnectionGetSyncMessageSize(fl)  s_pfCMGetAPI2( "RdcyConnectionGetSyncMessageSize", (RTS_VOID_FCTPTR *)&pfRdcyConnectionGetSyncMessageSize, (fl), 0, 0)
	#define CAL_RdcyConnectionGetSyncMessageSize  pfRdcyConnectionGetSyncMessageSize
	#define CHK_RdcyConnectionGetSyncMessageSize  (pfRdcyConnectionGetSyncMessageSize != NULL)
	#define EXP_RdcyConnectionGetSyncMessageSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionGetSyncMessageSize", (RTS_UINTPTR)RdcyConnectionGetSyncMessageSize, 0, 0) 
#endif




/**
 * <description>
 *	This function is used to determine the maximum message size of a data message, including header.
 *	In case of TCP/IP communication, the function will return 0x00005000
 * </description>
 * <result>Data message size.</result>
 */
RTS_UI32 CDECL RdcyConnectionGetDataMessageSize(void);
typedef RTS_UI32 (CDECL * PFRDCYCONNECTIONGETDATAMESSAGESIZE) (void);
#if defined(CMPREDUNDANCYCONNECTION_NOTIMPLEMENTED) || defined(RDCYCONNECTIONGETDATAMESSAGESIZE_NOTIMPLEMENTED)
	#define USE_RdcyConnectionGetDataMessageSize
	#define EXT_RdcyConnectionGetDataMessageSize
	#define GET_RdcyConnectionGetDataMessageSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RdcyConnectionGetDataMessageSize()  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_RdcyConnectionGetDataMessageSize  FALSE
	#define EXP_RdcyConnectionGetDataMessageSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RdcyConnectionGetDataMessageSize
	#define EXT_RdcyConnectionGetDataMessageSize
	#define GET_RdcyConnectionGetDataMessageSize(fl)  CAL_CMGETAPI( "RdcyConnectionGetDataMessageSize" ) 
	#define CAL_RdcyConnectionGetDataMessageSize  RdcyConnectionGetDataMessageSize
	#define CHK_RdcyConnectionGetDataMessageSize  TRUE
	#define EXP_RdcyConnectionGetDataMessageSize  CAL_CMEXPAPI( "RdcyConnectionGetDataMessageSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYCONNECTION_EXTERNAL)
	#define USE_RdcyConnectionGetDataMessageSize
	#define EXT_RdcyConnectionGetDataMessageSize
	#define GET_RdcyConnectionGetDataMessageSize(fl)  CAL_CMGETAPI( "RdcyConnectionGetDataMessageSize" ) 
	#define CAL_RdcyConnectionGetDataMessageSize  RdcyConnectionGetDataMessageSize
	#define CHK_RdcyConnectionGetDataMessageSize  TRUE
	#define EXP_RdcyConnectionGetDataMessageSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionGetDataMessageSize", (RTS_UINTPTR)RdcyConnectionGetDataMessageSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyConnectionRdcyConnectionGetDataMessageSize
	#define EXT_CmpRedundancyConnectionRdcyConnectionGetDataMessageSize
	#define GET_CmpRedundancyConnectionRdcyConnectionGetDataMessageSize  ERR_OK
	#define CAL_CmpRedundancyConnectionRdcyConnectionGetDataMessageSize pICmpRedundancyConnection->IRdcyConnectionGetDataMessageSize
	#define CHK_CmpRedundancyConnectionRdcyConnectionGetDataMessageSize (pICmpRedundancyConnection != NULL)
	#define EXP_CmpRedundancyConnectionRdcyConnectionGetDataMessageSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RdcyConnectionGetDataMessageSize
	#define EXT_RdcyConnectionGetDataMessageSize
	#define GET_RdcyConnectionGetDataMessageSize(fl)  CAL_CMGETAPI( "RdcyConnectionGetDataMessageSize" ) 
	#define CAL_RdcyConnectionGetDataMessageSize pICmpRedundancyConnection->IRdcyConnectionGetDataMessageSize
	#define CHK_RdcyConnectionGetDataMessageSize (pICmpRedundancyConnection != NULL)
	#define EXP_RdcyConnectionGetDataMessageSize  CAL_CMEXPAPI( "RdcyConnectionGetDataMessageSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_RdcyConnectionGetDataMessageSize  PFRDCYCONNECTIONGETDATAMESSAGESIZE pfRdcyConnectionGetDataMessageSize;
	#define EXT_RdcyConnectionGetDataMessageSize  extern PFRDCYCONNECTIONGETDATAMESSAGESIZE pfRdcyConnectionGetDataMessageSize;
	#define GET_RdcyConnectionGetDataMessageSize(fl)  s_pfCMGetAPI2( "RdcyConnectionGetDataMessageSize", (RTS_VOID_FCTPTR *)&pfRdcyConnectionGetDataMessageSize, (fl), 0, 0)
	#define CAL_RdcyConnectionGetDataMessageSize  pfRdcyConnectionGetDataMessageSize
	#define CHK_RdcyConnectionGetDataMessageSize  (pfRdcyConnectionGetDataMessageSize != NULL)
	#define EXP_RdcyConnectionGetDataMessageSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RdcyConnectionGetDataMessageSize", (RTS_UINTPTR)RdcyConnectionGetDataMessageSize, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
	PFRDCYCONNECTIONOPEN IRdcyConnectionOpen;
 	PFRDCYCONNECTIONCLOSE IRdcyConnectionClose;
 	PFRDCYCONNECTIONGETOWNADDRESS IRdcyConnectionGetOwnAddress;
 	PFRDCYCONNECTIONRECEIVESYNC IRdcyConnectionReceiveSync;
 	PFRDCYCONNECTIONGETRECEIVESIZE IRdcyConnectionGetReceiveSize;
 	PFRDCYCONNECTIONSENDSYNC IRdcyConnectionSendSync;
 	PFRDCYCONNECTIONRECEIVEDATA IRdcyConnectionReceiveData;
 	PFRDCYCONNECTIONSENDDATA IRdcyConnectionSendData;
 	PFRDCYCONNECTIONREADSETTINGS IRdcyConnectionReadSettings;
 	PFRDCYCONNECTIONSRVREADSETTINGS IRdcyConnectionSrvReadSettings;
 	PFRDCYCONNECTIONSRVWRITESETTINGS IRdcyConnectionSrvWriteSettings;
 	PFRDCYCONNECTIONGETSYNCMESSAGESIZE IRdcyConnectionGetSyncMessageSize;
 	PFRDCYCONNECTIONGETDATAMESSAGESIZE IRdcyConnectionGetDataMessageSize;
 } ICmpRedundancyConnection_C;

#ifdef CPLUSPLUS
class ICmpRedundancyConnection : public IBase
{
	public:
		virtual RTS_HANDLE CDECL IRdcyConnectionOpen(REDUNDANCY_COMM_MODE mode, RTS_UI32 uiMessageSize) =0;
		virtual RTS_RESULT CDECL IRdcyConnectionClose(RTS_HANDLE hConnection, REDUNDANCY_COMM_MODE mode) =0;
		virtual RTS_UI32 CDECL IRdcyConnectionGetOwnAddress(void) =0;
		virtual RTS_BOOL CDECL IRdcyConnectionReceiveSync(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize, CLIENT_REPLY *pReply) =0;
		virtual RTS_UI32 CDECL IRdcyConnectionGetReceiveSize(RTS_HANDLE hConnection, RTS_UI32 ulTimeout) =0;
		virtual RTS_UI32 CDECL IRdcyConnectionSendSync(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize) =0;
		virtual RTS_UI32 CDECL IRdcyConnectionReceiveData(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize, CLIENT_REPLY *pReply, RTS_UI32 ulTimeout) =0;
		virtual RTS_UI32 CDECL IRdcyConnectionSendData(RTS_HANDLE hConnection, char *pbyData, RTS_UI32 diDataSize) =0;
		virtual RTS_RESULT CDECL IRdcyConnectionReadSettings(void) =0;
		virtual RTS_RESULT CDECL IRdcyConnectionSrvReadSettings(BINTAGWRITER *pwriter) =0;
		virtual RTS_RESULT CDECL IRdcyConnectionSrvWriteSettings(BINTAGREADER *preader) =0;
		virtual RTS_UI32 CDECL IRdcyConnectionGetSyncMessageSize(void) =0;
		virtual RTS_UI32 CDECL IRdcyConnectionGetDataMessageSize(void) =0;
};
	#ifndef ITF_CmpRedundancyConnection
		#define ITF_CmpRedundancyConnection static ICmpRedundancyConnection *pICmpRedundancyConnection = NULL;
	#endif
	#define EXTITF_CmpRedundancyConnection
#else	/*CPLUSPLUS*/
	typedef ICmpRedundancyConnection_C		ICmpRedundancyConnection;
	#ifndef ITF_CmpRedundancyConnection
		#define ITF_CmpRedundancyConnection
	#endif
	#define EXTITF_CmpRedundancyConnection
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPREDUNDANCYCONNECTIONITF_H_*/
