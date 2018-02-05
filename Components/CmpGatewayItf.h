 /**
 * <interfacename>CmpGateway</interfacename>
 * <description>
 *	Interface of the gateway
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPGATEWAYITF_H_
#define _CMPGATEWAYITF_H_

#include "CmpStd.h"

 

 




#include "CmpRouterItf.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
* <category>Settings</category>
* <type>Int</type>
* <description>
*	Setting to modify the client inactivity timeout in ms. 
*	If no piece of data (also no keepalive) is received or successfully sent wihtin this time, the Gateway closes the connection to the client.
* </description>
*/
#define GATEWAYKEY_INT_INACTIVITY_TIMEOUT					"InactivityTimeoutMs"
#ifndef GATEWAYKEY_INT_INACTIVITY_TIMEOUT_DEFAULT
	#define GATEWAYKEY_INT_INACTIVITY_TIMEOUT_DEFAULT		60000
#endif


/* -- Functions exported by communication drivers to the Gateway -- */

/* Send data on a connection. If not all of the data could be sent, the number of bytes 
   sent is returned in pdwSent and the function has to be called again later with the remaining
   bytes. 
   NOTE: This function must not block and it must not call any functions of the 
         gateway, since this may lead to deadlocks.
   hConnHandle    IN  identifies the connection.
   data           IN  The data to be sent
   pdwSent        OUT The number of bytes the could actually be sent.

   RETURNS: 
	ERR_NOTCONNECTED if the provided connection handle is not connected.
*/
typedef RTS_RESULT (CDECL *PFCOMMDRVSEND)(RTS_HANDLE hConnHandle, PROTOCOL_DATA_UNIT data, RTS_UI32 *pdwSent);

/* Receive data from an existent connection. 
   NOTE: This function must not block and it must not call any functions of the 
         gateway, since this may lead to deadlocks.
   hConnHandle  IN    identifies the connection
   pData        INOUT 
       .pData  (IN) Provides a buffer for the received data.
	   .nCount (IN) Size of the buffer. (OUT) Number of bytes actually received.
*/
typedef RTS_RESULT (CDECL *PFCOMMDRVRECEIVE)(RTS_HANDLE hConnHandle, PROTOCOL_DATA_UNIT *pData);

/* Close a connection 
   NOTE: This function must not block and it must not call any functions of the 
         gateway, since this may lead to deadlocks.
*/
typedef RTS_RESULT (CDECL *PFCOMMDRVCLOSE)(RTS_HANDLE hConnHandle);

/* -- Functions exported to communication drivers -- */

typedef struct
{
	PFCOMMDRVSEND    pfSend;
	PFCOMMDRVRECEIVE pfReceive;
	PFCOMMDRVCLOSE   pfClose;
} COMMDRVINFO;

/* Called by a gateway communication driver to register 
   with the gateway. 
   pInfo          IN  Contains function pointers to the comm driver api.
   phDriverHandle OUT Set to a unique value for the comm driver. The driver must provide
                      the assigned value in all other calls to the gateway functions 
				      in order to identify itself.
*/
RTS_RESULT CDECL GWRegisterCommDrv(COMMDRVINFO *pInfo, RTS_HANDLE *phDriverHandle);
typedef RTS_RESULT (CDECL * PFGWREGISTERCOMMDRV) (COMMDRVINFO *pInfo, RTS_HANDLE *phDriverHandle);
#if defined(CMPGATEWAY_NOTIMPLEMENTED) || defined(GWREGISTERCOMMDRV_NOTIMPLEMENTED)
	#define USE_GWRegisterCommDrv
	#define EXT_GWRegisterCommDrv
	#define GET_GWRegisterCommDrv(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWRegisterCommDrv(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_GWRegisterCommDrv  FALSE
	#define EXP_GWRegisterCommDrv  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWRegisterCommDrv
	#define EXT_GWRegisterCommDrv
	#define GET_GWRegisterCommDrv(fl)  CAL_CMGETAPI( "GWRegisterCommDrv" ) 
	#define CAL_GWRegisterCommDrv  GWRegisterCommDrv
	#define CHK_GWRegisterCommDrv  TRUE
	#define EXP_GWRegisterCommDrv  CAL_CMEXPAPI( "GWRegisterCommDrv" ) 
#elif defined(MIXED_LINK) && !defined(CMPGATEWAY_EXTERNAL)
	#define USE_GWRegisterCommDrv
	#define EXT_GWRegisterCommDrv
	#define GET_GWRegisterCommDrv(fl)  CAL_CMGETAPI( "GWRegisterCommDrv" ) 
	#define CAL_GWRegisterCommDrv  GWRegisterCommDrv
	#define CHK_GWRegisterCommDrv  TRUE
	#define EXP_GWRegisterCommDrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWRegisterCommDrv", (RTS_UINTPTR)GWRegisterCommDrv, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGatewayGWRegisterCommDrv
	#define EXT_CmpGatewayGWRegisterCommDrv
	#define GET_CmpGatewayGWRegisterCommDrv  ERR_OK
	#define CAL_CmpGatewayGWRegisterCommDrv pICmpGateway->IGWRegisterCommDrv
	#define CHK_CmpGatewayGWRegisterCommDrv (pICmpGateway != NULL)
	#define EXP_CmpGatewayGWRegisterCommDrv  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWRegisterCommDrv
	#define EXT_GWRegisterCommDrv
	#define GET_GWRegisterCommDrv(fl)  CAL_CMGETAPI( "GWRegisterCommDrv" ) 
	#define CAL_GWRegisterCommDrv pICmpGateway->IGWRegisterCommDrv
	#define CHK_GWRegisterCommDrv (pICmpGateway != NULL)
	#define EXP_GWRegisterCommDrv  CAL_CMEXPAPI( "GWRegisterCommDrv" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWRegisterCommDrv  PFGWREGISTERCOMMDRV pfGWRegisterCommDrv;
	#define EXT_GWRegisterCommDrv  extern PFGWREGISTERCOMMDRV pfGWRegisterCommDrv;
	#define GET_GWRegisterCommDrv(fl)  s_pfCMGetAPI2( "GWRegisterCommDrv", (RTS_VOID_FCTPTR *)&pfGWRegisterCommDrv, (fl), 0, 0)
	#define CAL_GWRegisterCommDrv  pfGWRegisterCommDrv
	#define CHK_GWRegisterCommDrv  (pfGWRegisterCommDrv != NULL)
	#define EXP_GWRegisterCommDrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWRegisterCommDrv", (RTS_UINTPTR)GWRegisterCommDrv, 0, 0) 
#endif




enum
{
	COMMDRV_ACTION_SEND = 0,
	COMMDRV_ACTION_RECEIVE = 1
};

/**
 * <description>
 *  May be called by a commdriver if a connection is ready to send/receive.
 *  This function shall not signal a condition more then once without the 
 *  gateway reacting to that signal.
 *  Eg. if the commdriver signals that a connection is ready to send it shall not
 *  signal this situation again before the gateway actually called "send".
 *  The gwclient must not rely on this function to be called but may use 
 *  it to increase the performance of the connection.
 * </description>
 * <param name="hDriverHandle" type="IN">
 *  The driver handle returned by GWRegisterCommDrv.
 * </param>
 * <param name="hConnHandle" type="IN">
 *  The handle to the connection.
 * </param>
 * <param name="nAction" type="IN">
 *  The action that is ready on this connection - eg. COMMDRV_ACTION_SEND, COMMDRV_ACTION_RECEIVE
 * </param>
 */
RTS_RESULT CDECL GWConnectionReady(RTS_HANDLE hDriverHandle, RTS_HANDLE hConnHandle, RTS_I32 nAction);
typedef RTS_RESULT (CDECL * PFGWCONNECTIONREADY) (RTS_HANDLE hDriverHandle, RTS_HANDLE hConnHandle, RTS_I32 nAction);
#if defined(CMPGATEWAY_NOTIMPLEMENTED) || defined(GWCONNECTIONREADY_NOTIMPLEMENTED)
	#define USE_GWConnectionReady
	#define EXT_GWConnectionReady
	#define GET_GWConnectionReady(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWConnectionReady(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_GWConnectionReady  FALSE
	#define EXP_GWConnectionReady  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWConnectionReady
	#define EXT_GWConnectionReady
	#define GET_GWConnectionReady(fl)  CAL_CMGETAPI( "GWConnectionReady" ) 
	#define CAL_GWConnectionReady  GWConnectionReady
	#define CHK_GWConnectionReady  TRUE
	#define EXP_GWConnectionReady  CAL_CMEXPAPI( "GWConnectionReady" ) 
#elif defined(MIXED_LINK) && !defined(CMPGATEWAY_EXTERNAL)
	#define USE_GWConnectionReady
	#define EXT_GWConnectionReady
	#define GET_GWConnectionReady(fl)  CAL_CMGETAPI( "GWConnectionReady" ) 
	#define CAL_GWConnectionReady  GWConnectionReady
	#define CHK_GWConnectionReady  TRUE
	#define EXP_GWConnectionReady  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWConnectionReady", (RTS_UINTPTR)GWConnectionReady, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGatewayGWConnectionReady
	#define EXT_CmpGatewayGWConnectionReady
	#define GET_CmpGatewayGWConnectionReady  ERR_OK
	#define CAL_CmpGatewayGWConnectionReady pICmpGateway->IGWConnectionReady
	#define CHK_CmpGatewayGWConnectionReady (pICmpGateway != NULL)
	#define EXP_CmpGatewayGWConnectionReady  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWConnectionReady
	#define EXT_GWConnectionReady
	#define GET_GWConnectionReady(fl)  CAL_CMGETAPI( "GWConnectionReady" ) 
	#define CAL_GWConnectionReady pICmpGateway->IGWConnectionReady
	#define CHK_GWConnectionReady (pICmpGateway != NULL)
	#define EXP_GWConnectionReady  CAL_CMEXPAPI( "GWConnectionReady" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWConnectionReady  PFGWCONNECTIONREADY pfGWConnectionReady;
	#define EXT_GWConnectionReady  extern PFGWCONNECTIONREADY pfGWConnectionReady;
	#define GET_GWConnectionReady(fl)  s_pfCMGetAPI2( "GWConnectionReady", (RTS_VOID_FCTPTR *)&pfGWConnectionReady, (fl), 0, 0)
	#define CAL_GWConnectionReady  pfGWConnectionReady
	#define CHK_GWConnectionReady  (pfGWConnectionReady != NULL)
	#define EXP_GWConnectionReady  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWConnectionReady", (RTS_UINTPTR)GWConnectionReady, 0, 0) 
#endif




/* Called when a client connects. If anything else then ERR_OK is returned
   the communication driver should close the connection immediatly.
   hDriverHandle   IN  The value assigned during GWRegisterCommDrv.
   hConnHandle     IN  A handle identifing the new connection.
*/
RTS_RESULT CDECL GWClientConnect(RTS_HANDLE hDriverHandle, RTS_HANDLE hConnHandle);
typedef RTS_RESULT (CDECL * PFGWCLIENTCONNECT) (RTS_HANDLE hDriverHandle, RTS_HANDLE hConnHandle);
#if defined(CMPGATEWAY_NOTIMPLEMENTED) || defined(GWCLIENTCONNECT_NOTIMPLEMENTED)
	#define USE_GWClientConnect
	#define EXT_GWClientConnect
	#define GET_GWClientConnect(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWClientConnect(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_GWClientConnect  FALSE
	#define EXP_GWClientConnect  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWClientConnect
	#define EXT_GWClientConnect
	#define GET_GWClientConnect(fl)  CAL_CMGETAPI( "GWClientConnect" ) 
	#define CAL_GWClientConnect  GWClientConnect
	#define CHK_GWClientConnect  TRUE
	#define EXP_GWClientConnect  CAL_CMEXPAPI( "GWClientConnect" ) 
#elif defined(MIXED_LINK) && !defined(CMPGATEWAY_EXTERNAL)
	#define USE_GWClientConnect
	#define EXT_GWClientConnect
	#define GET_GWClientConnect(fl)  CAL_CMGETAPI( "GWClientConnect" ) 
	#define CAL_GWClientConnect  GWClientConnect
	#define CHK_GWClientConnect  TRUE
	#define EXP_GWClientConnect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWClientConnect", (RTS_UINTPTR)GWClientConnect, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGatewayGWClientConnect
	#define EXT_CmpGatewayGWClientConnect
	#define GET_CmpGatewayGWClientConnect  ERR_OK
	#define CAL_CmpGatewayGWClientConnect pICmpGateway->IGWClientConnect
	#define CHK_CmpGatewayGWClientConnect (pICmpGateway != NULL)
	#define EXP_CmpGatewayGWClientConnect  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWClientConnect
	#define EXT_GWClientConnect
	#define GET_GWClientConnect(fl)  CAL_CMGETAPI( "GWClientConnect" ) 
	#define CAL_GWClientConnect pICmpGateway->IGWClientConnect
	#define CHK_GWClientConnect (pICmpGateway != NULL)
	#define EXP_GWClientConnect  CAL_CMEXPAPI( "GWClientConnect" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWClientConnect  PFGWCLIENTCONNECT pfGWClientConnect;
	#define EXT_GWClientConnect  extern PFGWCLIENTCONNECT pfGWClientConnect;
	#define GET_GWClientConnect(fl)  s_pfCMGetAPI2( "GWClientConnect", (RTS_VOID_FCTPTR *)&pfGWClientConnect, (fl), 0, 0)
	#define CAL_GWClientConnect  pfGWClientConnect
	#define CHK_GWClientConnect  (pfGWClientConnect != NULL)
	#define EXP_GWClientConnect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWClientConnect", (RTS_UINTPTR)GWClientConnect, 0, 0) 
#endif




/* Called when a client connection has been disconnected.
   hDriverHandle   IN  The value assigned during GWRegisterCommDrv.
   hConnHandle     IN  A handle identifing the disconnected connection. 
*/
RTS_RESULT CDECL GWClientDisconnect(RTS_HANDLE hDriverHandle, RTS_HANDLE hConnHandle);
typedef RTS_RESULT (CDECL * PFGWCLIENTDISCONNECT) (RTS_HANDLE hDriverHandle, RTS_HANDLE hConnHandle);
#if defined(CMPGATEWAY_NOTIMPLEMENTED) || defined(GWCLIENTDISCONNECT_NOTIMPLEMENTED)
	#define USE_GWClientDisconnect
	#define EXT_GWClientDisconnect
	#define GET_GWClientDisconnect(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWClientDisconnect(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_GWClientDisconnect  FALSE
	#define EXP_GWClientDisconnect  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWClientDisconnect
	#define EXT_GWClientDisconnect
	#define GET_GWClientDisconnect(fl)  CAL_CMGETAPI( "GWClientDisconnect" ) 
	#define CAL_GWClientDisconnect  GWClientDisconnect
	#define CHK_GWClientDisconnect  TRUE
	#define EXP_GWClientDisconnect  CAL_CMEXPAPI( "GWClientDisconnect" ) 
#elif defined(MIXED_LINK) && !defined(CMPGATEWAY_EXTERNAL)
	#define USE_GWClientDisconnect
	#define EXT_GWClientDisconnect
	#define GET_GWClientDisconnect(fl)  CAL_CMGETAPI( "GWClientDisconnect" ) 
	#define CAL_GWClientDisconnect  GWClientDisconnect
	#define CHK_GWClientDisconnect  TRUE
	#define EXP_GWClientDisconnect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWClientDisconnect", (RTS_UINTPTR)GWClientDisconnect, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGatewayGWClientDisconnect
	#define EXT_CmpGatewayGWClientDisconnect
	#define GET_CmpGatewayGWClientDisconnect  ERR_OK
	#define CAL_CmpGatewayGWClientDisconnect pICmpGateway->IGWClientDisconnect
	#define CHK_CmpGatewayGWClientDisconnect (pICmpGateway != NULL)
	#define EXP_CmpGatewayGWClientDisconnect  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWClientDisconnect
	#define EXT_GWClientDisconnect
	#define GET_GWClientDisconnect(fl)  CAL_CMGETAPI( "GWClientDisconnect" ) 
	#define CAL_GWClientDisconnect pICmpGateway->IGWClientDisconnect
	#define CHK_GWClientDisconnect (pICmpGateway != NULL)
	#define EXP_GWClientDisconnect  CAL_CMEXPAPI( "GWClientDisconnect" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWClientDisconnect  PFGWCLIENTDISCONNECT pfGWClientDisconnect;
	#define EXT_GWClientDisconnect  extern PFGWCLIENTDISCONNECT pfGWClientDisconnect;
	#define GET_GWClientDisconnect(fl)  s_pfCMGetAPI2( "GWClientDisconnect", (RTS_VOID_FCTPTR *)&pfGWClientDisconnect, (fl), 0, 0)
	#define CAL_GWClientDisconnect  pfGWClientDisconnect
	#define CHK_GWClientDisconnect  (pfGWClientDisconnect != NULL)
	#define EXP_GWClientDisconnect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWClientDisconnect", (RTS_UINTPTR)GWClientDisconnect, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFGWREGISTERCOMMDRV IGWRegisterCommDrv;
 	PFGWCONNECTIONREADY IGWConnectionReady;
 	PFGWCLIENTCONNECT IGWClientConnect;
 	PFGWCLIENTDISCONNECT IGWClientDisconnect;
 } ICmpGateway_C;

#ifdef CPLUSPLUS
class ICmpGateway : public IBase
{
	public:
		virtual RTS_RESULT CDECL IGWRegisterCommDrv(COMMDRVINFO *pInfo, RTS_HANDLE *phDriverHandle) =0;
		virtual RTS_RESULT CDECL IGWConnectionReady(RTS_HANDLE hDriverHandle, RTS_HANDLE hConnHandle, RTS_I32 nAction) =0;
		virtual RTS_RESULT CDECL IGWClientConnect(RTS_HANDLE hDriverHandle, RTS_HANDLE hConnHandle) =0;
		virtual RTS_RESULT CDECL IGWClientDisconnect(RTS_HANDLE hDriverHandle, RTS_HANDLE hConnHandle) =0;
};
	#ifndef ITF_CmpGateway
		#define ITF_CmpGateway static ICmpGateway *pICmpGateway = NULL;
	#endif
	#define EXTITF_CmpGateway
#else	/*CPLUSPLUS*/
	typedef ICmpGateway_C		ICmpGateway;
	#ifndef ITF_CmpGateway
		#define ITF_CmpGateway
	#endif
	#define EXTITF_CmpGateway
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPGATEWAYITF_H_*/
