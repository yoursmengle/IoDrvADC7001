/**
 * <interfacename>CmpIoDrvDPV1C1Slave</interfacename>
 * <description> 
 *	Interface of a profibus IO-driver for the DPV1 Class 1 Slave interface.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpIoDrvDPV1C1Slave')

#include "CmpItf.h"
REF_ITF(`CmpIoDrvItf.m4')
REF_ITF(`CmpIoDrvDPV1C1MasterItf.m4')
REF_ITF(`CmpEventCallbackItf.m4')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C1_S_RegisterRecvCallback', `(RTS_HANDLE hIoDrv, ICmpEventCallback *pICallback)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C1_S_UnregisterRecvCallback', `(RTS_HANDLE hIoDrv, ICmpEventCallback *pICallback)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C1_S_RegisterRecvCallbackFunction', `(RTS_HANDLE hIoDrv, PFEVENTCALLBACKFUNCTION pfCallbackFunction, int bIec)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction', `(RTS_HANDLE hIoDrv, PFEVENTCALLBACKFUNCTION pfCallbackFunction)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C1_S_Write', `(RTS_HANDLE hIoDrv, DPV1_C1_Write *pWrite)')

