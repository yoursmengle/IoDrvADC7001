#ifndef _CMPGWCOMMDRVDIRECTCALLSHARED_H_
#define _CMPGWCOMMDRVDIRECTCALLSHARED_H_

typedef enum 
{
	CDCS_Created,			/* The connection has been created and it is waiting for beeing registered */
	CDCS_GatewayRegistered, /* The connection is completed and can now be used */
	CDCS_ClosedByClient,	/* Internal for the gateway */
	CDCS_ClosedByGateway,	/* The connection is closed */
	CDCS_ErrorToClose,		/* The connection was not successfull, the client must call disconnect */
	CDCS_ToRemove			/* Internal for the gateway */
} CommDrvConnectionState;


typedef RTS_RESULT (CDECL *PFCONNECT) (/* out */ RTS_UI32* pulHandle);

typedef RTS_RESULT (CDECL *PFGETCONNINFO) (/* int */ RTS_UI32 ulHandle, /* out */ CommDrvConnectionState* pcs, 
										   /* out */ RTS_RESULT* pConnError);

typedef RTS_RESULT (CDECL *PFCONNECTIONMETHOD) (/* in */ RTS_UI32 ulHandle);

typedef RTS_RESULT (CDECL *PFSEND) (/* in */ RTS_UI32 ulHandle, /* in */ void* pData, 
									/* in */ RTS_UI32 ulSize, /* out */ RTS_UI32* pulCopiedBytes);

typedef struct
{
	unsigned long ulMagic1;
	unsigned long ulMagic2;
	unsigned long ulStructVersion;

	/* this function will be called by the gateway client to init a new connection */
	PFCONNECT pfConnect;

	/* this function will be called by the gateway client to close an existing connection */
	PFCONNECTIONMETHOD pfDisconnect;

	/* this function can be used by the gateway client to poll the state of a created connection */
	PFGETCONNINFO pfGetConnectionInfo;

	/* this function will be called by the gateway client when sth. is to be sent to the gateway */
	PFSEND pfSendToGateway;

	/* this function will be called by the gateway when it wants to send things to the gateway client */
	PFSEND pfSendToGatewayClient;
} CommDrvDirectCall_Shared;

#define COMMDRVDIRECT_MAGIC1	(unsigned long)0xab4621fe
#define COMMDRVDIRECT_MAGIC2	(unsigned long)0xf423121e

#endif /* _CMPGWCOMMDRVDIRECTCALLSHARED_H_ */
