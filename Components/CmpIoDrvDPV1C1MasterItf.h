 /**
 * <interfacename>CmpIoDrvDPV1C1Master</interfacename>
 * <description> 
 *	Interface of a profibus IO-driver for the DPV1 Class 1 Master interface.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPIODRVDPV1C1MASTERITF_H_
#define _CMPIODRVDPV1C1MASTERITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CmpIoDrvItf.h"

#define DPV1_STATE_NOT_ENABLED		0
#define DPV1_STATE_INVALID_PARAM	1
#define DPV1_STATE_PENDING			2
#define DPV1_STATE_DONE				3
#define DPV1_STATE_ERROR			4

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	/* IN */
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE bySlotNr;
	RTS_IEC_BYTE byIndex;

	/* INOUT */	
	RTS_IEC_WORD wLen;
	RTS_IEC_BYTE byDummy[2];
	void *pBuffer;

	/* OUT */
	RTS_IEC_BYTE abyError[4];
	RTS_IEC_WORD wOpState;

	/* LOCAL */
	RTS_IEC_WORD wJobId;
	RTS_IEC_BOOL bOldEnable;
} DPV1_C1_Read;

typedef struct
{
	/* IN */
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE bySlotNr;
	RTS_IEC_BYTE byIndex;

	/* INOUT */	
	RTS_IEC_WORD wLen;
	RTS_IEC_BYTE byDummy[2];
	void *pBuffer;

	/* OUT */
	RTS_IEC_BYTE abyError[4];
	RTS_IEC_WORD wOpState;

	/* LOCAL */
	RTS_IEC_WORD wJobId;
	RTS_IEC_BOOL bOldEnable;
} DPV1_C1_Write;

typedef struct
{
	/* IN */
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE byAlarmSpecifier;
	RTS_IEC_BYTE byAddAck;
	void *pUserData;

	/* INOUT */
	RTS_IEC_WORD wSlotNr;
	RTS_IEC_WORD wSeqNr;
	RTS_IEC_WORD wAlarmType;

	/* OUT */
	RTS_IEC_WORD wOpState;
	RTS_IEC_BYTE abyError[4];
	RTS_IEC_WORD wStatus;

	/* LOCAL */
	RTS_IEC_WORD wJobId;
	RTS_IEC_BOOL bOldEnable;
} DPV1_C1_Alarm;

typedef struct
{
	/* IN */
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE byAlarmSpecifier;
	RTS_IEC_BYTE byAddAck;
	RTS_IEC_WORD wLen;
	RTS_IEC_BYTE byDummy[2];
	void *pUserData;

	/* INOUT */
	RTS_IEC_WORD wSlotNr;
	RTS_IEC_WORD wSeqNr;
	RTS_IEC_WORD wAlarmType;

	/* OUT */
	RTS_IEC_WORD wOpState;
	RTS_IEC_BYTE abyError[4];

	/* LOCAL */
	RTS_IEC_WORD wJobId;
	RTS_IEC_BOOL bOldEnable;
} DPV1_C1_AlarmAck;

typedef struct
{
	/* IN */
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;

	/* INOUT */
	RTS_IEC_BYTE bySlotNr;
	RTS_IEC_BYTE bySeqNr;

	/* OUT */
	RTS_IEC_WORD wOpState;
	RTS_IEC_WORD wLen;
	RTS_IEC_BYTE abyError[4];
	void *pStatus;

	/* LOCAL */
	RTS_IEC_WORD wJobId;
	RTS_IEC_BOOL bOldEnable;
} DPV1_C1_Status;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C1_Read *pRead;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c1_m_read_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C1_Write *pWrite;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c1_m_write_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C1_Alarm *pAlarm;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c1_m_alarm_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C1_AlarmAck *pAlarmAck;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c1_m_alarmack_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C1_Status *pStatus;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c1_m_status_struct;

#ifdef __cplusplus
}
#endif

/**
 * <description></description>
 * <result>ERR_OK</result>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C1_M_Read(RTS_HANDLE hIoDrv, DPV1_C1_Read *pRead);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C1_M_READ) (RTS_HANDLE hIoDrv, DPV1_C1_Read *pRead);
#if defined(CMPIODRVDPV1C1MASTER_NOTIMPLEMENTED) || defined(IODRVDPV1_C1_M_READ_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C1_M_Read
	#define EXT_IoDrvDPV1_C1_M_Read
	#define GET_IoDrvDPV1_C1_M_Read(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C1_M_Read(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C1_M_Read  FALSE
	#define EXP_IoDrvDPV1_C1_M_Read  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C1_M_Read
	#define EXT_IoDrvDPV1_C1_M_Read
	#define GET_IoDrvDPV1_C1_M_Read(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Read(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Read(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Read  TRUE
	#define EXP_IoDrvDPV1_C1_M_Read  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C1MASTER_EXTERNAL)
	#define USE_IoDrvDPV1_C1_M_Read
	#define EXT_IoDrvDPV1_C1_M_Read
	#define GET_IoDrvDPV1_C1_M_Read(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Read(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Read(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Read  TRUE
	#define EXP_IoDrvDPV1_C1_M_Read  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Read
	#define EXT_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Read
	#define GET_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Read  ERR_OK
	#define CAL_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Read(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Read(p1))
	#define CHK_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Read  TRUE
	#define EXP_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Read  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C1_M_Read
	#define EXT_IoDrvDPV1_C1_M_Read
	#define GET_IoDrvDPV1_C1_M_Read(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Read(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Read(p1))
	#define CHK_IoDrvDPV1_C1_M_Read  TRUE
	#define EXP_IoDrvDPV1_C1_M_Read  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C1_M_Read
	#define EXT_IoDrvDPV1_C1_M_Read
	#define GET_IoDrvDPV1_C1_M_Read(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Read(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Read(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Read  TRUE
	#define EXP_IoDrvDPV1_C1_M_Read  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C1_M_Write(RTS_HANDLE hIoDrv, DPV1_C1_Write *pWrite);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C1_M_WRITE) (RTS_HANDLE hIoDrv, DPV1_C1_Write *pWrite);
#if defined(CMPIODRVDPV1C1MASTER_NOTIMPLEMENTED) || defined(IODRVDPV1_C1_M_WRITE_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C1_M_Write
	#define EXT_IoDrvDPV1_C1_M_Write
	#define GET_IoDrvDPV1_C1_M_Write(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C1_M_Write(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C1_M_Write  FALSE
	#define EXP_IoDrvDPV1_C1_M_Write  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C1_M_Write
	#define EXT_IoDrvDPV1_C1_M_Write
	#define GET_IoDrvDPV1_C1_M_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Write(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Write(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Write  TRUE
	#define EXP_IoDrvDPV1_C1_M_Write  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C1MASTER_EXTERNAL)
	#define USE_IoDrvDPV1_C1_M_Write
	#define EXT_IoDrvDPV1_C1_M_Write
	#define GET_IoDrvDPV1_C1_M_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Write(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Write(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Write  TRUE
	#define EXP_IoDrvDPV1_C1_M_Write  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Write
	#define EXT_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Write
	#define GET_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Write  ERR_OK
	#define CAL_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Write(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Write(p1))
	#define CHK_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Write  TRUE
	#define EXP_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Write  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C1_M_Write
	#define EXT_IoDrvDPV1_C1_M_Write
	#define GET_IoDrvDPV1_C1_M_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Write(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Write(p1))
	#define CHK_IoDrvDPV1_C1_M_Write  TRUE
	#define EXP_IoDrvDPV1_C1_M_Write  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C1_M_Write
	#define EXT_IoDrvDPV1_C1_M_Write
	#define GET_IoDrvDPV1_C1_M_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Write(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Write(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Write  TRUE
	#define EXP_IoDrvDPV1_C1_M_Write  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C1_M_Alarm(RTS_HANDLE hIoDrv, DPV1_C1_Alarm *pAlarm);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C1_M_ALARM) (RTS_HANDLE hIoDrv, DPV1_C1_Alarm *pAlarm);
#if defined(CMPIODRVDPV1C1MASTER_NOTIMPLEMENTED) || defined(IODRVDPV1_C1_M_ALARM_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C1_M_Alarm
	#define EXT_IoDrvDPV1_C1_M_Alarm
	#define GET_IoDrvDPV1_C1_M_Alarm(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C1_M_Alarm(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C1_M_Alarm  FALSE
	#define EXP_IoDrvDPV1_C1_M_Alarm  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C1_M_Alarm
	#define EXT_IoDrvDPV1_C1_M_Alarm
	#define GET_IoDrvDPV1_C1_M_Alarm(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Alarm(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Alarm(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Alarm  TRUE
	#define EXP_IoDrvDPV1_C1_M_Alarm  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C1MASTER_EXTERNAL)
	#define USE_IoDrvDPV1_C1_M_Alarm
	#define EXT_IoDrvDPV1_C1_M_Alarm
	#define GET_IoDrvDPV1_C1_M_Alarm(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Alarm(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Alarm(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Alarm  TRUE
	#define EXP_IoDrvDPV1_C1_M_Alarm  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Alarm
	#define EXT_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Alarm
	#define GET_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Alarm  ERR_OK
	#define CAL_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Alarm(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Alarm(p1))
	#define CHK_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Alarm  TRUE
	#define EXP_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Alarm  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C1_M_Alarm
	#define EXT_IoDrvDPV1_C1_M_Alarm
	#define GET_IoDrvDPV1_C1_M_Alarm(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Alarm(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Alarm(p1))
	#define CHK_IoDrvDPV1_C1_M_Alarm  TRUE
	#define EXP_IoDrvDPV1_C1_M_Alarm  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C1_M_Alarm
	#define EXT_IoDrvDPV1_C1_M_Alarm
	#define GET_IoDrvDPV1_C1_M_Alarm(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Alarm(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Alarm(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Alarm  TRUE
	#define EXP_IoDrvDPV1_C1_M_Alarm  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C1_M_AlarmAck(RTS_HANDLE hIoDrv, DPV1_C1_AlarmAck *pAlarmAck);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C1_M_ALARMACK) (RTS_HANDLE hIoDrv, DPV1_C1_AlarmAck *pAlarmAck);
#if defined(CMPIODRVDPV1C1MASTER_NOTIMPLEMENTED) || defined(IODRVDPV1_C1_M_ALARMACK_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C1_M_AlarmAck
	#define EXT_IoDrvDPV1_C1_M_AlarmAck
	#define GET_IoDrvDPV1_C1_M_AlarmAck(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C1_M_AlarmAck(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C1_M_AlarmAck  FALSE
	#define EXP_IoDrvDPV1_C1_M_AlarmAck  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C1_M_AlarmAck
	#define EXT_IoDrvDPV1_C1_M_AlarmAck
	#define GET_IoDrvDPV1_C1_M_AlarmAck(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_AlarmAck(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_AlarmAck(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_AlarmAck  TRUE
	#define EXP_IoDrvDPV1_C1_M_AlarmAck  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C1MASTER_EXTERNAL)
	#define USE_IoDrvDPV1_C1_M_AlarmAck
	#define EXT_IoDrvDPV1_C1_M_AlarmAck
	#define GET_IoDrvDPV1_C1_M_AlarmAck(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_AlarmAck(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_AlarmAck(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_AlarmAck  TRUE
	#define EXP_IoDrvDPV1_C1_M_AlarmAck  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_AlarmAck
	#define EXT_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_AlarmAck
	#define GET_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_AlarmAck  ERR_OK
	#define CAL_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_AlarmAck(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_AlarmAck(p1))
	#define CHK_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_AlarmAck  TRUE
	#define EXP_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_AlarmAck  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C1_M_AlarmAck
	#define EXT_IoDrvDPV1_C1_M_AlarmAck
	#define GET_IoDrvDPV1_C1_M_AlarmAck(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_AlarmAck(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_AlarmAck(p1))
	#define CHK_IoDrvDPV1_C1_M_AlarmAck  TRUE
	#define EXP_IoDrvDPV1_C1_M_AlarmAck  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C1_M_AlarmAck
	#define EXT_IoDrvDPV1_C1_M_AlarmAck
	#define GET_IoDrvDPV1_C1_M_AlarmAck(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_AlarmAck(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_AlarmAck(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_AlarmAck  TRUE
	#define EXP_IoDrvDPV1_C1_M_AlarmAck  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C1_M_Status(RTS_HANDLE hIoDrv, DPV1_C1_Status *pStatus);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C1_M_STATUS) (RTS_HANDLE hIoDrv, DPV1_C1_Status *pStatus);
#if defined(CMPIODRVDPV1C1MASTER_NOTIMPLEMENTED) || defined(IODRVDPV1_C1_M_STATUS_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C1_M_Status
	#define EXT_IoDrvDPV1_C1_M_Status
	#define GET_IoDrvDPV1_C1_M_Status(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C1_M_Status(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C1_M_Status  FALSE
	#define EXP_IoDrvDPV1_C1_M_Status  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C1_M_Status
	#define EXT_IoDrvDPV1_C1_M_Status
	#define GET_IoDrvDPV1_C1_M_Status(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Status(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Status(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Status  TRUE
	#define EXP_IoDrvDPV1_C1_M_Status  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C1MASTER_EXTERNAL)
	#define USE_IoDrvDPV1_C1_M_Status
	#define EXT_IoDrvDPV1_C1_M_Status
	#define GET_IoDrvDPV1_C1_M_Status(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Status(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Status(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Status  TRUE
	#define EXP_IoDrvDPV1_C1_M_Status  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Status
	#define EXT_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Status
	#define GET_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Status  ERR_OK
	#define CAL_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Status(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Status(p1))
	#define CHK_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Status  TRUE
	#define EXP_CmpIoDrvDPV1C1MasterIoDrvDPV1_C1_M_Status  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C1_M_Status
	#define EXT_IoDrvDPV1_C1_M_Status
	#define GET_IoDrvDPV1_C1_M_Status(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Status(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Status(p1))
	#define CHK_IoDrvDPV1_C1_M_Status  TRUE
	#define EXP_IoDrvDPV1_C1_M_Status  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C1_M_Status
	#define EXT_IoDrvDPV1_C1_M_Status
	#define GET_IoDrvDPV1_C1_M_Status(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C1_M_Status(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C1Master*)p0)->IIoDrvDPV1_C1_M_Status(((ICmpIoDrvDPV1C1Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C1_M_Status  TRUE
	#define EXP_IoDrvDPV1_C1_M_Status  ERR_OK
#endif







typedef struct
{
	IBase_C *pBase;
	PFIODRVDPV1_C1_M_READ IIoDrvDPV1_C1_M_Read;
 	PFIODRVDPV1_C1_M_WRITE IIoDrvDPV1_C1_M_Write;
 	PFIODRVDPV1_C1_M_ALARM IIoDrvDPV1_C1_M_Alarm;
 	PFIODRVDPV1_C1_M_ALARMACK IIoDrvDPV1_C1_M_AlarmAck;
 	PFIODRVDPV1_C1_M_STATUS IIoDrvDPV1_C1_M_Status;
 } ICmpIoDrvDPV1C1Master_C;

#ifdef CPLUSPLUS
class ICmpIoDrvDPV1C1Master : public IBase
{
	public:
		virtual RTS_RESULT CDECL IIoDrvDPV1_C1_M_Read(DPV1_C1_Read *pRead) =0;
		virtual RTS_RESULT CDECL IIoDrvDPV1_C1_M_Write(DPV1_C1_Write *pWrite) =0;
		virtual RTS_RESULT CDECL IIoDrvDPV1_C1_M_Alarm(DPV1_C1_Alarm *pAlarm) =0;
		virtual RTS_RESULT CDECL IIoDrvDPV1_C1_M_AlarmAck(DPV1_C1_AlarmAck *pAlarmAck) =0;
		virtual RTS_RESULT CDECL IIoDrvDPV1_C1_M_Status(DPV1_C1_Status *pStatus) =0;
};
	#ifndef ITF_CmpIoDrvDPV1C1Master
		#define ITF_CmpIoDrvDPV1C1Master static ICmpIoDrvDPV1C1Master *pICmpIoDrvDPV1C1Master = NULL;
	#endif
	#define EXTITF_CmpIoDrvDPV1C1Master
#else	/*CPLUSPLUS*/
	typedef ICmpIoDrvDPV1C1Master_C		ICmpIoDrvDPV1C1Master;
	#ifndef ITF_CmpIoDrvDPV1C1Master
		#define ITF_CmpIoDrvDPV1C1Master
	#endif
	#define EXTITF_CmpIoDrvDPV1C1Master
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIODRVDPV1C1MASTERITF_H_*/
