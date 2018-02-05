 /**
 * <interfacename>CmpBlkDrvUsb</interfacename>
 * <description> 
 *	Block driver interface. This interface could be implemented by different components.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPBLKDRVUSBITF_H_
#define _CMPBLKDRVUSBITF_H_

#include "CmpStd.h"

 

 




#ifndef MAX_USBBLK_DRV
	#define MAX_USBBLK_DRV	2
#endif


#ifndef MAX_USB_DEVICES
	#define MAX_USB_DEVICES	2 /*Maximum number of devices per driver.*/
#endif

#ifndef MAX_PORT_NAME
	#define MAX_PORT_NAME 32
#endif

#ifndef CMPBLKDRV_SEND_ADDRESS_REQUESTS_INTERVAL
	#define CMPBLKDRV_SEND_ADDRESS_REQUESTS_INTERVAL	5000 /* ms */
#endif

#ifndef BLKDRVUSB_MAX_READSIZE
	#define BLKDRVUSB_MAX_READSIZE		64 /*Bulk Block size*/
#endif

#ifndef BLKDRVUSB_MAX_BLOCK_SIZE
	#define BLKDRVUSB_MAX_BLOCK_SIZE	512
#endif

#define BLKDRVUSB_MAX_RX_SIZE				(BLKDRVUSB_MAX_BLOCK_SIZE + 2)



#define TYPE_NONE			0x00
#define TYPE_AUTO_ADDR		0x01
#define TYPE_HALFDUPLEX		0x02

/* Definitions for HDX extension */
#define USB_HDX_NEGOTIATION_MIN_WAITTIME	500		/*HDX Init Wait time*/
#define USB_HDX_NEGOTIATION_TIMEOUT			500		/*HDX Address Request/Answer Wait time*/
#define USB_HDX_MASTER_TOKEN_TIMEOUT_1		100		/*HDX Receive Master Tocken Wait time (1. try)*/
#define USB_HDX_MASTER_TOKEN_TIMEOUT_2		1000	/*HDX Receive Master Tocken Wait time (last try) */
#define USB_HDX_SLAVE_TOKEN_TIMEOUT			2000	/*HDX Receive Slave Tocken Wait time (1. try)*/
#define	USB_HDX_MASTER_TOKEN_DELAY_TIME		40
#define USB_HDX_DIRECTION_CHANGE_WAITTIME	3

#define HDX_PROTOCOL_VERSION	0x01

#define HDX_INIT_REQUEST	0x01
#define HDX_INIT_ANSWER		0x81
#define HDX_ADDR_REQUEST	0x02
#define HDX_ADDR_ANSWER		0x82
#define HDX_MASTER_TOKEN	0x03
#define HDX_SLAVE_TOKEN     0x83

#define HDX_ROLE_NONE		0x00
#define HDX_ROLE_MASTER		0x01
#define HDX_ROLE_SLAVE		0x02



typedef struct tagSendBuffer
{
	int nSize; /* 0 --> unused */
	int nPos; 
	char buffer[1040]; /* 2+2*(512+2)+2 */
}SENDBUFFER;

typedef struct tagReceiveBuffer
{
	int nPos; 
	int nRead;
	int bHashReceived;
	int bHeader;
	char buffer[BLKDRVUSB_MAX_RX_SIZE + BLKDRVUSB_MAX_READSIZE];
	int iHeaderType;
}RECBUFFER;

typedef enum 
{
	USBOP_NONE,
	USBOP_OPEN,
	USBOP_CLOSE,
	USBOP_REREGISTER,
	USBOP_ACTIVE,
	USBOP_HDX_INIT,
	USBOP_HDX_WAIT_ADDR_REQ,
	USBOP_HDX_WAIT_ADDR_ANSW,
	USBOP_HDX_WAIT_SEND,  /* not used anymore */
	USBOP_HDX_SEND,
	USBOP_HDX_RECEIVE,
	USBOP_PORT_UNUSED
}USBDEV_OPERATION;

typedef struct tagUsbMpd
{
	/*Filled in by the blkdriver to give the miniportdriver a possibility to talk back.*/
	RTS_HANDLE hInterface; 
	RTS_HANDLE CDECL (*OpenDevice)(unsigned int VendorId, unsigned int DeviceId, int DeviceIdx, int iConf, int iItf, RTS_RESULT *pResult);
	RTS_RESULT CDECL (*CloseDevice)(RTS_HANDLE hCom);
	unsigned int CDECL (*Read)(RTS_HANDLE hCom, unsigned char *pbyBuffer, unsigned int uiSize, unsigned long ulTimeout, RTS_RESULT *pResult);
	unsigned int CDECL (*Write)(RTS_HANDLE hCom, unsigned char *pbyBuffer, unsigned int uiSize, unsigned long ulTimeout, RTS_RESULT *pResult);
	char szName[32];
}MINIPORTDRVUSB;

typedef struct tagUsbMpd2
{
	/*Filled in by the blkdriver to give the miniportdriver a possibility to talk back.*/
	RTS_HANDLE hInterface; 
	RTS_HANDLE CDECL (*OpenDevice)(unsigned int VendorId, unsigned int DeviceId, int DeviceIdx, int iConf, int iItf, RTS_RESULT *pResult);
	RTS_HANDLE CDECL (*OpenDevice2)(unsigned int VendorId, unsigned int DeviceId, int DeviceIdx, int iConf, int iItf, int iEpIn, int iEpOut, RTS_RESULT *pResult);
	RTS_RESULT CDECL (*CloseDevice)(RTS_HANDLE hCom);
	unsigned int CDECL (*Read)(RTS_HANDLE hCom, unsigned char *pbyBuffer, unsigned int uiSize, unsigned long ulTimeout, RTS_RESULT *pResult);
	unsigned int CDECL (*Write)(RTS_HANDLE hCom, unsigned char *pbyBuffer, unsigned int uiSize, unsigned long ulTimeout, RTS_RESULT *pResult);
	char szName[32];
}MINIPORTDRVUSB2;

typedef struct tagUSBDEVICE
{
	RTS_HANDLE hCom;
	int nPort;
	RTS_UI32 iVendorId;
	RTS_UI32 iDeviceId;
	RTS_UI32 iConfig;
	RTS_UI32 iInterface;
	RTS_UI32 iEndpointIn;
	RTS_UI32 iEndpointOut;
	int iDeviceIdx;
	/* Opening and closing the USBDEVICEs must only be done in the main thread (COMM_CYCLE).
	   So if another thread requires this port to be opened or closed, it must set the 
	   required operation and wait for the mainthread to have completed that operation.
	*/
	USBDEV_OPERATION pendingOp; 
	RTS_HANDLE hNetwork;
	SENDBUFFER send;
	RECBUFFER rec;
	RTS_UI32 ulLastAction;
	RTS_UI32 ulSendDelay;
	RTS_BOOL bAddrRequestReceived;
	RTS_BOOL bForceReregister;			/* another protocol type was requested from peer, reregistering at router is needed later on */
	RTS_UI32 ui32ProtocolExtensionType;	/* currently used protocol type: see TYPE_xxx */
	RTS_I32 i32EnableAutoAddressing;
	RTS_I32 i32EnableHalfDuplexMode;	/* enable strict half-duplex communication */
	RTS_UI16 usHdxTokenId;				/* TokenID for the current communication */
	RTS_UI8 ucHdxRole;					/* Device is Master, Slave or undefined */
	RTS_UI8 ucPeerAddr;
	RTS_UI8 ucLocalAddr;				/* configured or negotiated local address */
	MINIPORTDRVUSB2* pDrv;
	char szName[MAX_PORT_NAME];
	char szDriverName[MAX_PORT_NAME];
	RTS_UI8 ucHdxRetries;
	char szInitToken[30];
}USBDEVICE;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> Open a block driver </description>
 * <param name="pInterface" type="IN">Pointer to the mini port driver interface</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL BlkDrvUsbRegisterDriver(MINIPORTDRVUSB* pInterface);
typedef RTS_RESULT (CDECL * PFBLKDRVUSBREGISTERDRIVER) (MINIPORTDRVUSB* pInterface);
#if defined(CMPBLKDRVUSB_NOTIMPLEMENTED) || defined(BLKDRVUSBREGISTERDRIVER_NOTIMPLEMENTED)
	#define USE_BlkDrvUsbRegisterDriver
	#define EXT_BlkDrvUsbRegisterDriver
	#define GET_BlkDrvUsbRegisterDriver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BlkDrvUsbRegisterDriver(p0) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BlkDrvUsbRegisterDriver  FALSE
	#define EXP_BlkDrvUsbRegisterDriver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BlkDrvUsbRegisterDriver
	#define EXT_BlkDrvUsbRegisterDriver
	#define GET_BlkDrvUsbRegisterDriver(fl)  CAL_CMGETAPI( "BlkDrvUsbRegisterDriver" ) 
	#define CAL_BlkDrvUsbRegisterDriver  BlkDrvUsbRegisterDriver
	#define CHK_BlkDrvUsbRegisterDriver  TRUE
	#define EXP_BlkDrvUsbRegisterDriver  CAL_CMEXPAPI( "BlkDrvUsbRegisterDriver" ) 
#elif defined(MIXED_LINK) && !defined(CMPBLKDRVUSB_EXTERNAL)
	#define USE_BlkDrvUsbRegisterDriver
	#define EXT_BlkDrvUsbRegisterDriver
	#define GET_BlkDrvUsbRegisterDriver(fl)  CAL_CMGETAPI( "BlkDrvUsbRegisterDriver" ) 
	#define CAL_BlkDrvUsbRegisterDriver  BlkDrvUsbRegisterDriver
	#define CHK_BlkDrvUsbRegisterDriver  TRUE
	#define EXP_BlkDrvUsbRegisterDriver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BlkDrvUsbRegisterDriver", (RTS_UINTPTR)BlkDrvUsbRegisterDriver, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBlkDrvUsbBlkDrvUsbRegisterDriver
	#define EXT_CmpBlkDrvUsbBlkDrvUsbRegisterDriver
	#define GET_CmpBlkDrvUsbBlkDrvUsbRegisterDriver  ERR_OK
	#define CAL_CmpBlkDrvUsbBlkDrvUsbRegisterDriver  BlkDrvUsbRegisterDriver
	#define CHK_CmpBlkDrvUsbBlkDrvUsbRegisterDriver  TRUE
	#define EXP_CmpBlkDrvUsbBlkDrvUsbRegisterDriver  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BlkDrvUsbRegisterDriver
	#define EXT_BlkDrvUsbRegisterDriver
	#define GET_BlkDrvUsbRegisterDriver(fl)  CAL_CMGETAPI( "BlkDrvUsbRegisterDriver" ) 
	#define CAL_BlkDrvUsbRegisterDriver  BlkDrvUsbRegisterDriver
	#define CHK_BlkDrvUsbRegisterDriver  TRUE
	#define EXP_BlkDrvUsbRegisterDriver  CAL_CMEXPAPI( "BlkDrvUsbRegisterDriver" ) 
#else /* DYNAMIC_LINK */
	#define USE_BlkDrvUsbRegisterDriver  PFBLKDRVUSBREGISTERDRIVER pfBlkDrvUsbRegisterDriver;
	#define EXT_BlkDrvUsbRegisterDriver  extern PFBLKDRVUSBREGISTERDRIVER pfBlkDrvUsbRegisterDriver;
	#define GET_BlkDrvUsbRegisterDriver(fl)  s_pfCMGetAPI2( "BlkDrvUsbRegisterDriver", (RTS_VOID_FCTPTR *)&pfBlkDrvUsbRegisterDriver, (fl), 0, 0)
	#define CAL_BlkDrvUsbRegisterDriver  pfBlkDrvUsbRegisterDriver
	#define CHK_BlkDrvUsbRegisterDriver  (pfBlkDrvUsbRegisterDriver != NULL)
	#define EXP_BlkDrvUsbRegisterDriver   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BlkDrvUsbRegisterDriver", (RTS_UINTPTR)BlkDrvUsbRegisterDriver, 0, 0) 
#endif


/**
 * <description> Open a block driver </description>
 * <param name="pInterface" type="IN">Pointer to the mini port driver interface 2</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL BlkDrvUsbRegisterDriver2(MINIPORTDRVUSB2* pInterface);
typedef RTS_RESULT (CDECL * PFBLKDRVUSBREGISTERDRIVER2) (MINIPORTDRVUSB2* pInterface);
#if defined(CMPBLKDRVUSB_NOTIMPLEMENTED) || defined(BLKDRVUSBREGISTERDRIVER2_NOTIMPLEMENTED)
	#define USE_BlkDrvUsbRegisterDriver2
	#define EXT_BlkDrvUsbRegisterDriver2
	#define GET_BlkDrvUsbRegisterDriver2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BlkDrvUsbRegisterDriver2(p0) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BlkDrvUsbRegisterDriver2  FALSE
	#define EXP_BlkDrvUsbRegisterDriver2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BlkDrvUsbRegisterDriver2
	#define EXT_BlkDrvUsbRegisterDriver2
	#define GET_BlkDrvUsbRegisterDriver2(fl)  CAL_CMGETAPI( "BlkDrvUsbRegisterDriver2" ) 
	#define CAL_BlkDrvUsbRegisterDriver2  BlkDrvUsbRegisterDriver2
	#define CHK_BlkDrvUsbRegisterDriver2  TRUE
	#define EXP_BlkDrvUsbRegisterDriver2  CAL_CMEXPAPI( "BlkDrvUsbRegisterDriver2" ) 
#elif defined(MIXED_LINK) && !defined(CMPBLKDRVUSB_EXTERNAL)
	#define USE_BlkDrvUsbRegisterDriver2
	#define EXT_BlkDrvUsbRegisterDriver2
	#define GET_BlkDrvUsbRegisterDriver2(fl)  CAL_CMGETAPI( "BlkDrvUsbRegisterDriver2" ) 
	#define CAL_BlkDrvUsbRegisterDriver2  BlkDrvUsbRegisterDriver2
	#define CHK_BlkDrvUsbRegisterDriver2  TRUE
	#define EXP_BlkDrvUsbRegisterDriver2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BlkDrvUsbRegisterDriver2", (RTS_UINTPTR)BlkDrvUsbRegisterDriver2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBlkDrvUsbBlkDrvUsbRegisterDriver2
	#define EXT_CmpBlkDrvUsbBlkDrvUsbRegisterDriver2
	#define GET_CmpBlkDrvUsbBlkDrvUsbRegisterDriver2  ERR_OK
	#define CAL_CmpBlkDrvUsbBlkDrvUsbRegisterDriver2  BlkDrvUsbRegisterDriver2
	#define CHK_CmpBlkDrvUsbBlkDrvUsbRegisterDriver2  TRUE
	#define EXP_CmpBlkDrvUsbBlkDrvUsbRegisterDriver2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BlkDrvUsbRegisterDriver2
	#define EXT_BlkDrvUsbRegisterDriver2
	#define GET_BlkDrvUsbRegisterDriver2(fl)  CAL_CMGETAPI( "BlkDrvUsbRegisterDriver2" ) 
	#define CAL_BlkDrvUsbRegisterDriver2  BlkDrvUsbRegisterDriver2
	#define CHK_BlkDrvUsbRegisterDriver2  TRUE
	#define EXP_BlkDrvUsbRegisterDriver2  CAL_CMEXPAPI( "BlkDrvUsbRegisterDriver2" ) 
#else /* DYNAMIC_LINK */
	#define USE_BlkDrvUsbRegisterDriver2  PFBLKDRVUSBREGISTERDRIVER2 pfBlkDrvUsbRegisterDriver2;
	#define EXT_BlkDrvUsbRegisterDriver2  extern PFBLKDRVUSBREGISTERDRIVER2 pfBlkDrvUsbRegisterDriver2;
	#define GET_BlkDrvUsbRegisterDriver2(fl)  s_pfCMGetAPI2( "BlkDrvUsbRegisterDriver2", (RTS_VOID_FCTPTR *)&pfBlkDrvUsbRegisterDriver2, (fl), 0, 0)
	#define CAL_BlkDrvUsbRegisterDriver2  pfBlkDrvUsbRegisterDriver2
	#define CHK_BlkDrvUsbRegisterDriver2  (pfBlkDrvUsbRegisterDriver2 != NULL)
	#define EXP_BlkDrvUsbRegisterDriver2   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BlkDrvUsbRegisterDriver2", (RTS_UINTPTR)BlkDrvUsbRegisterDriver2, 0, 0) 
#endif


#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpBlkDrvUsb_C;

#ifdef CPLUSPLUS
class ICmpBlkDrvUsb : public IBase
{
	public:
};
	#ifndef ITF_CmpBlkDrvUsb
		#define ITF_CmpBlkDrvUsb static ICmpBlkDrvUsb *pICmpBlkDrvUsb = NULL;
	#endif
	#define EXTITF_CmpBlkDrvUsb
#else	/*CPLUSPLUS*/
	typedef ICmpBlkDrvUsb_C		ICmpBlkDrvUsb;
	#ifndef ITF_CmpBlkDrvUsb
		#define ITF_CmpBlkDrvUsb
	#endif
	#define EXTITF_CmpBlkDrvUsb
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPBLKDRVUSBITF_H_*/
