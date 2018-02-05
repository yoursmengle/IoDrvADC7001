SET_INTERFACE_NAME(`CmpEL6751CanDrv')

#include "CmpItf.h"

/**
 * <description>EL6751_CANRxMessage</description>
 */
typedef struct tagEL6751_CANRxMessage
{
	RTS_IEC_WORD wCobID;
	RTS_IEC_BYTE aby[8];
} EL6751_CANRxMessage;

/**
 * <description>EL6751_CANTxMessage</description>
 */
typedef struct tagEL6751_CANTxMessage
{
	RTS_IEC_UINT uiTransactionNumber;
	RTS_IEC_WORD wCobID;
	RTS_IEC_BYTE aby[8];
} EL6751_CANTxMessage;

/**
 * <description>EL6751_Config</description>
 */
typedef struct tagEL6751_Config
{
	RTS_IEC_UINT *m_puiQTxCounter;
	RTS_IEC_UINT *m_puiQRxCounter;
	RTS_IEC_UINT *m_puiQNoTxMessages;
	EL6751_CANTxMessage *m_pcmQTx;
	RTS_IEC_UINT *m_puiITxCounter;
	RTS_IEC_UINT *m_puiIRxCounter;
	RTS_IEC_UINT *m_puiINoRxMessages;
	RTS_IEC_UINT *m_puiITransactionNumber;
	EL6751_CANRxMessage *m_pcmIRx;
	RTS_IEC_UINT m_uiMaxTelegrams;
	RTS_IEC_UINT m_uiBaudrate;
	RTS_IEC_USINT m_usiNet;
	RTS_IEC_DWORD m_dwLibVersion;
	RTS_IEC_DWORD m_dwCmpVersion;
	RTS_IEC_BOOL m_bETCDeviceOperational;
} EL6751_Config;

/**
 * <description>el6751_killcmd</description>
 */
typedef struct tagel6751_killcmd_struct
{
	EL6751_Config *pcfg;				/* VAR_INPUT */
	RTS_IEC_UINT EL6751_KillCMD;		/* VAR_OUTPUT */
} el6751_killcmd_struct;

/**
 * <description>el6751_registercmd</description>
 */
typedef struct tagel6751_registercmd_struct
{
	EL6751_Config *pcfg;				/* VAR_INPUT */
	RTS_IEC_UINT EL6751_RegisterCMD;	/* VAR_OUTPUT */
} el6751_registercmd_struct;

/**
 * <description>el6751_afterreadinputs</description>
 */
typedef struct tagel6751_afterreadinputs_struct
{
	EL6751_Config *pcfg;				/* VAR_INPUT */
	RTS_IEC_UINT EL6751_AfterReadInputs;	/* VAR_OUTPUT */
} el6751_afterreadinputs_struct;

/**
 * <description>el6751_beforewriteoutputs</description>
 */
typedef struct tagel6751_beforewriteoutputs_struct
{
	EL6751_Config *pcfg;				/* VAR_INPUT */
	RTS_IEC_UINT EL6751_BeforeWriteOutputs;	/* VAR_OUTPUT */
} el6751_beforewriteoutputs_struct;

#ifdef __cplusplus
extern "C" {
#endif

DEF_API(`void',`CDECL',`el6751_killcmd',`(el6751_killcmd_struct *p)',1,0x53D657BE,0x3030014)
DEF_API(`void',`CDECL',`el6751_registercmd',`(el6751_registercmd_struct *p)',1,0xD69C906,0x3030014)
DEF_API(`void',`CDECL',`el6751_afterreadinputs',`(el6751_afterreadinputs_struct *p)',1,0x157B908B,0x3030014)
DEF_API(`void',`CDECL',`el6751_beforewriteoutputs',`(el6751_beforewriteoutputs_struct *p)',1,0x5E9C43EC,0x3030014)

#ifdef __cplusplus
}
#endif
