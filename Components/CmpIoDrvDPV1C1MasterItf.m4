/**
 * <interfacename>CmpIoDrvDPV1C1Master</interfacename>
 * <description> 
 *	Interface of a profibus IO-driver for the DPV1 Class 1 Master interface.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpIoDrvDPV1C1Master')

#include "CmpItf.h"
REF_ITF(`CmpIoDrvItf.m4')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C1_M_Read', `(RTS_HANDLE hIoDrv, DPV1_C1_Read *pRead)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C1_M_Write', `(RTS_HANDLE hIoDrv, DPV1_C1_Write *pWrite)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C1_M_Alarm', `(RTS_HANDLE hIoDrv, DPV1_C1_Alarm *pAlarm)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C1_M_AlarmAck', `(RTS_HANDLE hIoDrv, DPV1_C1_AlarmAck *pAlarmAck)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C1_M_Status', `(RTS_HANDLE hIoDrv, DPV1_C1_Status *pStatus)')

