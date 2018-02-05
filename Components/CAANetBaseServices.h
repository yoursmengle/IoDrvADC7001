/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAANetBaseServices.h
*	Version:		2.4
*	Purpose:		Interface to the CAA net based services handler.
*
******************************************************************************/

#ifndef __CAANETBASESERVICES_H__
#define __CAANETBASESERVICES_H__

#ifdef CAALib

#include "CAADefines.h"

#ifdef CAA_NBS

#ifndef __CAA_NBS_H__
#define __CAA_NBS_H__

/*ENUMS*/

/**
 * <description>ERROR</description>
 */
#define	NBS_NO_ERROR						((CAA_ERROR)0)
#define	NBS_FIRST_ERROR						((CAA_ERROR)6000)
#define	NBS_TIME_OUT						((CAA_ERROR)6001)
#define	NBS_INVALID_ADDR					((CAA_ERROR)6002)
#define	NBS_INVALID_HANDLE					((CAA_ERROR)6003)
#define	NBS_INVALID_DATAPOINTER				((CAA_ERROR)6004)
#define	NBS_INVALID_DATASIZE				((CAA_ERROR)6005)
#define	NBS_UDP_RECEIVE_ERROR				((CAA_ERROR)6006)
#define	NBS_UDP_SEND_ERROR					((CAA_ERROR)6007)
#define	NBS_UDP_SEND_NOT_COMPLETE			((CAA_ERROR)6008)
#define NBS_UDP_OPEN_ERROR					((CAA_ERROR)6009)
#define NBS_UDP_CLOSE_ERROR					((CAA_ERROR)6010)
#define	NBS_TCP_SEND_ERROR					((CAA_ERROR)6011)
#define	NBS_TCP_RECEIVE_ERROR				((CAA_ERROR)6012)
#define NBS_TCP_OPEN_ERROR					((CAA_ERROR)6013)
#define NBS_TCP_CONNECT_ERROR				((CAA_ERROR)6014)
#define NBS_TCP_CLOSE_ERROR					((CAA_ERROR)6015)
#define NBS_TCP_SERVER_ERROR				((CAA_ERROR)6016)
#define	NBS_WRONG_PARAMETER					((CAA_ERROR)6017)
#define NBS_ERROR_UNKNOWN					((CAA_ERROR)6018)
#define NBS_TCP_NO_CONNECTION				((CAA_ERROR)6019)
#define	NBS_FIRST_MF						((CAA_ERROR)6050)
#define	NBS_LAST_ERROR						((CAA_ERROR)6099)

/**
 * <description>CONNECTION_STATE</description>
 */
typedef enum
{
	CLOSED = 0,
	ESTABLISHED = 1,
	LISTEN = 2,
	CLOSE_WAIT = 3
} NBS_CONNECTION_STATE;

/**
 * <description>IP_ADDR</description>
 */
typedef struct tagIP_ADDR
{
	RTS_IEC_STRING sAddr[81];
} NBS_IP_ADDR;

/**
 * <description>NBS_TcpServerOpenParams</description>
 */
typedef struct
{
	NBS_IP_ADDR ipAddr;				/* VAR_INPUT */
	CAA_UINT uiPort;				/* VAR_INPUT */
	CAA_HANDLE hServer;				/* VAR_OUTPUT */
} NBS_TcpServerOpenParams;

/**
 * <description>NBS_TcpConnectionOpenParams</description>
 */
typedef struct
{
	CAA_HANDLE hServer;				/* VAR_INTPUT */
	CAA_HANDLE hConnection;			/* VAR_OUTPUT */
} NBS_TcpConnectionOpenParams;

/**
 * <description>NBS_TcpClientOpenParams</description>
 */
typedef struct
{
	CAA_UDINT udiTimeout;			/* VAR_INPUT */
	NBS_IP_ADDR ipAddr;				/* VAR_INPUT */
	CAA_UINT uiPort;				/* VAR_INPUT */
	CAA_HANDLE hConnection;			/* VAR_OUTPUT */
	CAA_BYTE byState;				/* VAR_OUTPUT */
} NBS_TcpClientOpenParams;

/**
 * <description>NBS_TcpCloseParams</description>
 */
typedef struct
{
	CAA_HANDLE hHandle;				/* VAR_INPUT */
} NBS_TcpCloseParams;

/**
 * <description>NBS_TcpReadParams</description>
 */
typedef struct
{
	CAA_HANDLE hConnection;			/* VAR_INPUT */
	CAA_SIZE szSize;				/* VAR_INPUT */
	CAA_BOOL xReady;				/* VAR_OUTPUT */
	CAA_HANDLE hBuffer;				/* VAR_OUTPUT */
} NBS_TcpReadParams;

/**
 * <description>NBS_TcpWriteParams</description>
 */
typedef struct
{
	CAA_HANDLE hConnection;			/* VAR_INPUT */
	CAA_HANDLE hBuffer;				/* VAR_INPUT */
} NBS_TcpWriteParams;

/**
 * <description>NBS_UdpPeerOpenParams</description>
 */
typedef struct
{
	NBS_IP_ADDR ipAddr;				/* VAR_INPUT */
	CAA_UINT uiPort;				/* VAR_INPUT */
	NBS_IP_ADDR ipMultiCast;		/* VAR_INPUT */
	CAA_HANDLE hPeer;				/* VAR_OUTPUT */
} NBS_UdpPeerOpenParams;

/**
 * <description>NBS_UdpPeerCloseParams</description>
 */
typedef struct
{
	CAA_HANDLE hPeer;				/* VAR_INPUT */
} NBS_UdpPeerCloseParams;

/**
 * <description>NBS_UdpReceiveParams</description>
 */
typedef struct
{
	CAA_HANDLE hPeer;				/* VAR_INPUT */
	CAA_SIZE szSize;				/* VAR_INPUT */
	CAA_BOOL xReady;				/* VAR_OUTPUT */
	NBS_IP_ADDR ipAddrFrom;			/* VAR_OUTPUT */
	CAA_UINT uiPortFrom;			/* VAR_OUTPUT */
	CAA_HANDLE hBuffer;				/* VAR_OUTPUT */
} NBS_UdpReceiveParams;

/**
 * <description>NBS_UdpSendParams</description>
 */
typedef struct
{
	CAA_HANDLE hPeer;				/* VAR_INPUT */
	NBS_IP_ADDR ipAddr;				/* VAR_INPUT */
	CAA_UINT uiPort;				/* VAR_INPUT */
	CAA_HANDLE hBuffer;				/* VAR_INPUT */
} NBS_UdpSendParams;

#endif /*__CAA_FILE_H__*/
#endif /* CAA_FILE */
#endif /* CAALib */

#endif /*__CAANETBASESERVICES_H__*/
