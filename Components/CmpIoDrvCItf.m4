/**
 * <interfacename>CmpIoDrvC</interfacename>
 * <description>
 *	This is the interface to get access from an IEC program to every IO-driver written in C.
 *	All interfaces of an IO-driver in C must be specified in this wrapper!
 *	In the IEC program, the CmpIoDrvC.library is needed to enable this access.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpIoDrvC')

#include "CmpIoDrvItf.h"
#include "CmpIoDrvParameterItf.h"
#include "CmpIoDrvDPV1C1MasterItf.h"
#include "CmpIoDrvDPV1C2MasterItf.h"

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>cmpiodrvc__main</description>
 */
typedef struct tagcmpiodrvc_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of CmpIoDrvC */
	RTS_IEC_BYTE *__pIBase;	/* Pointer to interface IBase */
	RTS_IEC_BYTE *pICmpIoDrv;	/* Pointer to interface ICmpIoDrv */
	RTS_IEC_BYTE *pICmpIoDrvParameter;	/* Pointer to interface ICmpIoDrvParameter */
	RTS_IEC_BYTE *pICmpIoDrvDPV1C1Master;	/* Pointer to interface ICmpIoDrvDPV1C1Master */
	RTS_IEC_BYTE *pICmpIoDrvDPV1C2Master;	/* Pointer to interface ICmpIoDrvDPV1C2Master */

	RTS_IEC_DWORD dwVersion;			/* VAR_INPUT */
	IBase *pIBase;						/* VAR_INPUT */
} cmpiodrvc_struct;

typedef struct
{
	cmpiodrvc_struct *pInstance;	/* VAR_INPUT */
} cmpiodrvc_main_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__main',`(cmpiodrvc_main_struct *p)',1,0/*0xFA08D30C*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvdpv1_c1_m_alarm</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c1_m_alarm_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C1_Alarm *dpv1Alarm;			/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C1_M_Alarm;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c1_m_alarm_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvdpv1_c1_m_alarm',`(cmpiodrvc_iodrvdpv1_c1_m_alarm_struct *p)',1,0/*0xE8E6FDC5*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvidentify</description>
 */
typedef struct tagcmpiodrvc_iodrvidentify_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvIdentify;		/* VAR_OUTPUT */
} cmpiodrvc_iodrvidentify_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvidentify',`(cmpiodrvc_iodrvidentify_struct *p)',1,0/*0x71D91E4E*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvdpv1_c1_m_alarmack</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c1_m_alarmack_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C1_AlarmAck *dpv1AlarmAck;		/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C1_M_AlarmAck;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c1_m_alarmack_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvdpv1_c1_m_alarmack',`(cmpiodrvc_iodrvdpv1_c1_m_alarmack_struct *p)',1,0/*0x91B9E17F*/,0x3050000)

/**
 * <description>cmpiodrvc__release</description>
 */
typedef struct tagcmpiodrvc_release_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	RTS_IEC_DINT Release;				/* VAR_OUTPUT */
} cmpiodrvc_release_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__release',`(cmpiodrvc_release_struct *p)',1,0/*0xC21041B1*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvreadparameter</description>
 */
typedef struct tagcmpiodrvc_iodrvreadparameter_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	IoConfigParameter *pParameter;		/* VAR_INPUT */
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */
	RTS_IEC_DWORD dwBitSize;			/* VAR_INPUT */
	RTS_IEC_DWORD dwBitOffset;			/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvReadParameter;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvreadparameter_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvreadparameter',`(cmpiodrvc_iodrvreadparameter_struct *p)',1,0/*0x263580FA*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvwriteoutputs</description>
 */
typedef struct tagcmpiodrvc_iodrvwriteoutputs_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnectorMap *pConnectorMapList;	/* VAR_INPUT */
	RTS_IEC_DINT nCount;				/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvWriteOutputs;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvwriteoutputs_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvwriteoutputs',`(cmpiodrvc_iodrvwriteoutputs_struct *p)',1,0/*0x10DE7EF4*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvgetmodulediagnosis</description>
 */
typedef struct tagcmpiodrvc_iodrvgetmodulediagnosis_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvGetModuleDiagnosis;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvgetmodulediagnosis_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvgetmodulediagnosis',`(cmpiodrvc_iodrvgetmodulediagnosis_struct *p)',1,0/*0x70DC4D0E*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvdpv1_c1_m_read</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c1_m_read_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C1_Read *dpv1Read;				/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C1_M_Read;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c1_m_read_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvdpv1_c1_m_read',`(cmpiodrvc_iodrvdpv1_c1_m_read_struct *p)',1,0/*0x1CEA8FE0*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvdpv1_c2_m_abort</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c2_m_abort_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C2_Abort *dpv1c2_Abort;		/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C2_M_Abort;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c2_m_abort_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvdpv1_c2_m_abort',`(cmpiodrvc_iodrvdpv1_c2_m_abort_struct *p)',1,0/*0x6BE2BA5E*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvdpv1_c1_m_status</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c1_m_status_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C1_Status *dpv1Status;			/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C1_M_Status;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c1_m_status_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvdpv1_c1_m_status',`(cmpiodrvc_iodrvdpv1_c1_m_status_struct *p)',1,0/*0x7BA8079D*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvstartbuscycle</description>
 */
typedef struct tagcmpiodrvc_iodrvstartbuscycle_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvStartBusCycle;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvstartbuscycle_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvstartbuscycle',`(cmpiodrvc_iodrvstartbuscycle_struct *p)',1,0/*0xE2AACEF3*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvupdateconfiguration</description>
 */
typedef struct tagcmpiodrvc_iodrvupdateconfiguration_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnectorList;	/* VAR_INPUT */
	RTS_IEC_DINT nCount;				/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvUpdateConfiguration;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvupdateconfiguration_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvupdateconfiguration',`(cmpiodrvc_iodrvupdateconfiguration_struct *p)',1,0/*0x5600F48B*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvwriteparameter</description>
 */
typedef struct tagcmpiodrvc_iodrvwriteparameter_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	IoConfigParameter *pParameter;		/* VAR_INPUT */
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */
	RTS_IEC_DWORD dwBitSize;			/* VAR_INPUT */
	RTS_IEC_DWORD dwBitOffset;			/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvWriteParameter;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvwriteparameter_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvwriteparameter',`(cmpiodrvc_iodrvwriteparameter_struct *p)',1,0/*0xA14E52EF*/,0x3050000)

/**
 * <description>cmpiodrvc__queryinterface</description>
 */
typedef struct tagcmpiodrvc_queryinterface_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	RTS_IEC_DWORD iid;					/* VAR_INPUT */
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */
	RTS_IEC_BYTE **QueryInterface;		/* VAR_OUTPUT */
} cmpiodrvc_queryinterface_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__queryinterface',`(cmpiodrvc_queryinterface_struct *p)',1,0/*0x687F2F81*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvscanmodules</description>
 */
typedef struct tagcmpiodrvc_iodrvscanmodules_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	IoConfigConnector **ppConnectorList;	/* VAR_INPUT */
	RTS_IEC_DINT *pnCount;				/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvScanModules;		/* VAR_OUTPUT */
} cmpiodrvc_iodrvscanmodules_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvscanmodules',`(cmpiodrvc_iodrvscanmodules_struct *p)',1,0/*0xFE8E174B*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvdpv1_c2_m_write</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c2_m_write_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C2_Write *dpv1c2_Write;		/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C2_M_Write;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c2_m_write_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvdpv1_c2_m_write',`(cmpiodrvc_iodrvdpv1_c2_m_write_struct *p)',1,0/*0x34717EFF*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvgetinfo</description>
 */
typedef struct tagcmpiodrvc_iodrvgetinfo_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoDrvInfo **ppInfo;					/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvGetInfo;			/* VAR_OUTPUT */
} cmpiodrvc_iodrvgetinfo_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvgetinfo',`(cmpiodrvc_iodrvgetinfo_struct *p)',1,0/*0xDB628C59*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvwatchdogtrigger</description>
 */
typedef struct tagcmpiodrvc_iodrvwatchdogtrigger_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvWatchdogTrigger;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvwatchdogtrigger_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvwatchdogtrigger',`(cmpiodrvc_iodrvwatchdogtrigger_struct *p)',1,0/*0xF1AB6D2E*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvdpv1_c2_m_initiate</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c2_m_initiate_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C2_Initiate *dpv1c2_Initiate;	/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C2_M_Initiate;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c2_m_initiate_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvdpv1_c2_m_initiate',`(cmpiodrvc_iodrvdpv1_c2_m_initiate_struct *p)',1,0/*0x1F637083*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvdpv1_c2_m_read</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c2_m_read_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C2_Read *dpv1c2_Read;			/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C2_M_Read;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c2_m_read_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvdpv1_c2_m_read',`(cmpiodrvc_iodrvdpv1_c2_m_read_struct *p)',1,0/*0x42D6E6C8*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvupdatemapping</description>
 */
typedef struct tagcmpiodrvc_iodrvupdatemapping_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigTaskMap *pTaskMapList;		/* VAR_INPUT */
	RTS_IEC_DINT nCount;				/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvUpdateMapping;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvupdatemapping_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvupdatemapping',`(cmpiodrvc_iodrvupdatemapping_struct *p)',1,0/*0x9EE859E0*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvreadinputs</description>
 */
typedef struct tagcmpiodrvc_iodrvreadinputs_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnectorMap *pConnectorMapList;	/* VAR_INPUT */
	RTS_IEC_DINT nCount;				/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvReadInputs;		/* VAR_OUTPUT */
} cmpiodrvc_iodrvreadinputs_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvreadinputs',`(cmpiodrvc_iodrvreadinputs_struct *p)',1,0/*0x86C4F56B*/,0x3050000)

/**
 * <description>cmpiodrvc__addref</description>
 */
typedef struct tagcmpiodrvc_addref_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	RTS_IEC_DINT AddRef;				/* VAR_OUTPUT */
} cmpiodrvc_addref_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__addref',`(cmpiodrvc_addref_struct *p)',1,0/*0x3D28D31E*/,0x3050000)

/**
 * <description>cmpiodrvc__iodrvdpv1_c1_m_write</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c1_m_write_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C1_Write *dpv1Write;			/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C1_M_Write;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c1_m_write_struct;

DEF_API(`void',`CDECL',`cmpiodrvc__iodrvdpv1_c1_m_write',`(cmpiodrvc_iodrvdpv1_c1_m_write_struct *p)',1,0/*0x3CD3DFFA*/,0x3050000)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

