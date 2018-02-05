 /**
 * <interfacename>CmpIoDrvDPV1C1Slave</interfacename>
 * <description> 
 *	Interface of a profibus IO-driver for the DPV1 Class 1 Slave interface.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPIODRVDPV1C1SLAVEITF_H_
#define _CMPIODRVDPV1C1SLAVEITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CmpIoDrvItf.h"
#include "CmpIoDrvDPV1C1MasterItf.h"
#include "CmpEventCallbackItf.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	RTS_IEC_UINT wModuleType;
	RTS_IEC_UDINT dwInstance;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE bySlotNr;
	RTS_IEC_BYTE byIndex;
	RTS_IEC_BYTE byLen;
	void *pBuffer;
} DPV1_C1_S_Recv;

/**
 * <category>Event parameter</category>
 * <element name="recv" type="IN">Receive structure of a DPV1 message</element>
 */
typedef struct
{
	DPV1_C1_S_Recv recv;
} EVTPARAM_IoDrvDPV1_Recv;
#define EVTPARAMID_IoDrvDPV1_Recv	0x0001
#define EVTVERSION_IoDrvDPV1_Recv	0x0001

/**
 * <category>Events</category>
 * <description></description>
 * <param name="pEventParam" type="IN">EVTPARAM_IoDrvDPV1_Recv</param>
 */
#define EVT_IoDrvDPV1_Recv			MAKE_EVENTID(EVTCLASS_INFO, 1)

#ifdef __cplusplus
}
#endif

/**
 * <description>  </description>
 * <result>ERR_OK</result>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C1_S_RegisterRecvCallback(RTS_HANDLE hIoDrv, ICmpEventCallback *pICallback);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C1_S_REGISTERRECVCALLBACK) (RTS_HANDLE hIoDrv, ICmpEventCallback *pICallback);
#if defined(CMPIODRVDPV1C1SLAVE_NOTIMPLEMENTED) || defined(IODRVDPV1_C1_S_REGISTERRECVCALLBACK_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C1_S_RegisterRecvCallback
	#define EXT_IoDrvDPV1_C1_S_RegisterRecvCallback
	#define GET_IoDrvDPV1_C1_S_RegisterRecvCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C1_S_RegisterRecvCallback(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C1_S_RegisterRecvCallback  FALSE
	#define EXP_IoDrvDPV1_C1_S_RegisterRecvCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C1_S_RegisterRecvCallback
	#define EXT_IoDrvDPV1_C1_S_RegisterRecvCallback
	#define GET_IoDrvDPV1_C1_S_RegisterRecvCallback(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_RegisterRecvCallback(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_RegisterRecvCallback(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_RegisterRecvCallback  TRUE
	#define EXP_IoDrvDPV1_C1_S_RegisterRecvCallback  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C1SLAVE_EXTERNAL)
	#define USE_IoDrvDPV1_C1_S_RegisterRecvCallback
	#define EXT_IoDrvDPV1_C1_S_RegisterRecvCallback
	#define GET_IoDrvDPV1_C1_S_RegisterRecvCallback(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_RegisterRecvCallback(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_RegisterRecvCallback(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_RegisterRecvCallback  TRUE
	#define EXP_IoDrvDPV1_C1_S_RegisterRecvCallback  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallback
	#define EXT_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallback
	#define GET_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallback  ERR_OK
	#define CAL_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallback(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_RegisterRecvCallback(p1))
	#define CHK_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallback  TRUE
	#define EXP_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C1_S_RegisterRecvCallback
	#define EXT_IoDrvDPV1_C1_S_RegisterRecvCallback
	#define GET_IoDrvDPV1_C1_S_RegisterRecvCallback(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_RegisterRecvCallback(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_RegisterRecvCallback(p1))
	#define CHK_IoDrvDPV1_C1_S_RegisterRecvCallback  TRUE
	#define EXP_IoDrvDPV1_C1_S_RegisterRecvCallback  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C1_S_RegisterRecvCallback
	#define EXT_IoDrvDPV1_C1_S_RegisterRecvCallback
	#define GET_IoDrvDPV1_C1_S_RegisterRecvCallback(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_RegisterRecvCallback(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_RegisterRecvCallback(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_RegisterRecvCallback  TRUE
	#define EXP_IoDrvDPV1_C1_S_RegisterRecvCallback  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C1_S_UnregisterRecvCallback(RTS_HANDLE hIoDrv, ICmpEventCallback *pICallback);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C1_S_UNREGISTERRECVCALLBACK) (RTS_HANDLE hIoDrv, ICmpEventCallback *pICallback);
#if defined(CMPIODRVDPV1C1SLAVE_NOTIMPLEMENTED) || defined(IODRVDPV1_C1_S_UNREGISTERRECVCALLBACK_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C1_S_UnregisterRecvCallback
	#define EXT_IoDrvDPV1_C1_S_UnregisterRecvCallback
	#define GET_IoDrvDPV1_C1_S_UnregisterRecvCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C1_S_UnregisterRecvCallback(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C1_S_UnregisterRecvCallback  FALSE
	#define EXP_IoDrvDPV1_C1_S_UnregisterRecvCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C1_S_UnregisterRecvCallback
	#define EXT_IoDrvDPV1_C1_S_UnregisterRecvCallback
	#define GET_IoDrvDPV1_C1_S_UnregisterRecvCallback(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_UnregisterRecvCallback(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_UnregisterRecvCallback(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_UnregisterRecvCallback  TRUE
	#define EXP_IoDrvDPV1_C1_S_UnregisterRecvCallback  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C1SLAVE_EXTERNAL)
	#define USE_IoDrvDPV1_C1_S_UnregisterRecvCallback
	#define EXT_IoDrvDPV1_C1_S_UnregisterRecvCallback
	#define GET_IoDrvDPV1_C1_S_UnregisterRecvCallback(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_UnregisterRecvCallback(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_UnregisterRecvCallback(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_UnregisterRecvCallback  TRUE
	#define EXP_IoDrvDPV1_C1_S_UnregisterRecvCallback  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallback
	#define EXT_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallback
	#define GET_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallback  ERR_OK
	#define CAL_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallback(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_UnregisterRecvCallback(p1))
	#define CHK_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallback  TRUE
	#define EXP_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C1_S_UnregisterRecvCallback
	#define EXT_IoDrvDPV1_C1_S_UnregisterRecvCallback
	#define GET_IoDrvDPV1_C1_S_UnregisterRecvCallback(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_UnregisterRecvCallback(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_UnregisterRecvCallback(p1))
	#define CHK_IoDrvDPV1_C1_S_UnregisterRecvCallback  TRUE
	#define EXP_IoDrvDPV1_C1_S_UnregisterRecvCallback  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C1_S_UnregisterRecvCallback
	#define EXT_IoDrvDPV1_C1_S_UnregisterRecvCallback
	#define GET_IoDrvDPV1_C1_S_UnregisterRecvCallback(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_UnregisterRecvCallback(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_UnregisterRecvCallback(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_UnregisterRecvCallback  TRUE
	#define EXP_IoDrvDPV1_C1_S_UnregisterRecvCallback  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(RTS_HANDLE hIoDrv, PFEVENTCALLBACKFUNCTION pfCallbackFunction, int bIec);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C1_S_REGISTERRECVCALLBACKFUNCTION) (RTS_HANDLE hIoDrv, PFEVENTCALLBACKFUNCTION pfCallbackFunction, int bIec);
#if defined(CMPIODRVDPV1C1SLAVE_NOTIMPLEMENTED) || defined(IODRVDPV1_C1_S_REGISTERRECVCALLBACKFUNCTION_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define EXT_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define GET_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction  FALSE
	#define EXP_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define EXT_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define GET_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_RegisterRecvCallbackFunction(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction  TRUE
	#define EXP_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C1SLAVE_EXTERNAL)
	#define USE_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define EXT_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define GET_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_RegisterRecvCallbackFunction(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction  TRUE
	#define EXP_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define EXT_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define GET_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallbackFunction  ERR_OK
	#define CAL_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallbackFunction(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_RegisterRecvCallbackFunction(p1,p2))
	#define CHK_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallbackFunction  TRUE
	#define EXP_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_RegisterRecvCallbackFunction  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define EXT_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define GET_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_RegisterRecvCallbackFunction(p1,p2))
	#define CHK_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction  TRUE
	#define EXP_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define EXT_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction
	#define GET_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_RegisterRecvCallbackFunction(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction  TRUE
	#define EXP_IoDrvDPV1_C1_S_RegisterRecvCallbackFunction  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(RTS_HANDLE hIoDrv, PFEVENTCALLBACKFUNCTION pfCallbackFunction);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C1_S_UNREGISTERRECVCALLBACKFUNCTION) (RTS_HANDLE hIoDrv, PFEVENTCALLBACKFUNCTION pfCallbackFunction);
#if defined(CMPIODRVDPV1C1SLAVE_NOTIMPLEMENTED) || defined(IODRVDPV1_C1_S_UNREGISTERRECVCALLBACKFUNCTION_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define EXT_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define GET_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  FALSE
	#define EXP_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define EXT_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define GET_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  TRUE
	#define EXP_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C1SLAVE_EXTERNAL)
	#define USE_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define EXT_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define GET_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  TRUE
	#define EXP_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define EXT_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define GET_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  ERR_OK
	#define CAL_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(p1))
	#define CHK_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  TRUE
	#define EXP_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define EXT_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define GET_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(p1))
	#define CHK_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  TRUE
	#define EXP_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define EXT_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction
	#define GET_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  TRUE
	#define EXP_IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C1_S_Write(RTS_HANDLE hIoDrv, DPV1_C1_Write *pWrite);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C1_S_WRITE) (RTS_HANDLE hIoDrv, DPV1_C1_Write *pWrite);
#if defined(CMPIODRVDPV1C1SLAVE_NOTIMPLEMENTED) || defined(IODRVDPV1_C1_S_WRITE_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C1_S_Write
	#define EXT_IoDrvDPV1_C1_S_Write
	#define GET_IoDrvDPV1_C1_S_Write(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C1_S_Write(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C1_S_Write  FALSE
	#define EXP_IoDrvDPV1_C1_S_Write  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C1_S_Write
	#define EXT_IoDrvDPV1_C1_S_Write
	#define GET_IoDrvDPV1_C1_S_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_Write(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_Write(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_Write  TRUE
	#define EXP_IoDrvDPV1_C1_S_Write  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C1SLAVE_EXTERNAL)
	#define USE_IoDrvDPV1_C1_S_Write
	#define EXT_IoDrvDPV1_C1_S_Write
	#define GET_IoDrvDPV1_C1_S_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_Write(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_Write(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_Write  TRUE
	#define EXP_IoDrvDPV1_C1_S_Write  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_Write
	#define EXT_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_Write
	#define GET_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_Write  ERR_OK
	#define CAL_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_Write(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_Write(p1))
	#define CHK_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_Write  TRUE
	#define EXP_CmpIoDrvDPV1C1SlaveIoDrvDPV1_C1_S_Write  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C1_S_Write
	#define EXT_IoDrvDPV1_C1_S_Write
	#define GET_IoDrvDPV1_C1_S_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_Write(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_Write(p1))
	#define CHK_IoDrvDPV1_C1_S_Write  TRUE
	#define EXP_IoDrvDPV1_C1_S_Write  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C1_S_Write
	#define EXT_IoDrvDPV1_C1_S_Write
	#define GET_IoDrvDPV1_C1_S_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_S_Write(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Slave*)p0)->IIoDrvDPV1_C1_S_Write(((ICmpIoDrvDPV1C1Slave*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_S_Write  TRUE
	#define EXP_IoDrvDPV1_C1_S_Write  ERR_OK
#endif







typedef struct
{
	IBase_C *pBase;
	PFIODRVDPV1_C1_S_REGISTERRECVCALLBACK IIoDrvDPV1_C1_S_RegisterRecvCallback;
 	PFIODRVDPV1_C1_S_UNREGISTERRECVCALLBACK IIoDrvDPV1_C1_S_UnregisterRecvCallback;
 	PFIODRVDPV1_C1_S_REGISTERRECVCALLBACKFUNCTION IIoDrvDPV1_C1_S_RegisterRecvCallbackFunction;
 	PFIODRVDPV1_C1_S_UNREGISTERRECVCALLBACKFUNCTION IIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction;
 	PFIODRVDPV1_C1_S_WRITE IIoDrvDPV1_C1_S_Write;
 } ICmpIoDrvDPV1C1Slave_C;

#ifdef CPLUSPLUS
class ICmpIoDrvDPV1C1Slave : public IBase
{
	public:
		virtual RTS_RESULT CDECL IIoDrvDPV1_C1_S_RegisterRecvCallback(ICmpEventCallback *pICallback) =0;
		virtual RTS_RESULT CDECL IIoDrvDPV1_C1_S_UnregisterRecvCallback(ICmpEventCallback *pICallback) =0;
		virtual RTS_RESULT CDECL IIoDrvDPV1_C1_S_RegisterRecvCallbackFunction(PFEVENTCALLBACKFUNCTION pfCallbackFunction, int bIec) =0;
		virtual RTS_RESULT CDECL IIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(PFEVENTCALLBACKFUNCTION pfCallbackFunction) =0;
		virtual RTS_RESULT CDECL IIoDrvDPV1_C1_S_Write(DPV1_C1_Write *pWrite) =0;
};
	#ifndef ITF_CmpIoDrvDPV1C1Slave
		#define ITF_CmpIoDrvDPV1C1Slave static ICmpIoDrvDPV1C1Slave *pICmpIoDrvDPV1C1Slave = NULL;
	#endif
	#define EXTITF_CmpIoDrvDPV1C1Slave
#else	/*CPLUSPLUS*/
	typedef ICmpIoDrvDPV1C1Slave_C		ICmpIoDrvDPV1C1Slave;
	#ifndef ITF_CmpIoDrvDPV1C1Slave
		#define ITF_CmpIoDrvDPV1C1Slave
	#endif
	#define EXTITF_CmpIoDrvDPV1C1Slave
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIODRVDPV1C1SLAVEITF_H_*/
