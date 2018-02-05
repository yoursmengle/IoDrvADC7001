 
	
	
#ifndef _CMPEL6751CANDRVITF_H_
#define _CMPEL6751CANDRVITF_H_

#include "CmpStd.h"

 

 




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

void CDECL CDECL_EXT el6751_killcmd(el6751_killcmd_struct *p);
typedef void (CDECL CDECL_EXT* PFEL6751_KILLCMD_IEC) (el6751_killcmd_struct *p);
#if defined(CMPEL6751CANDRV_NOTIMPLEMENTED) || defined(EL6751_KILLCMD_NOTIMPLEMENTED)
	#define USE_el6751_killcmd
	#define EXT_el6751_killcmd
	#define GET_el6751_killcmd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_el6751_killcmd(p0) 
	#define CHK_el6751_killcmd  FALSE
	#define EXP_el6751_killcmd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_el6751_killcmd
	#define EXT_el6751_killcmd
	#define GET_el6751_killcmd(fl)  CAL_CMGETAPI( "el6751_killcmd" ) 
	#define CAL_el6751_killcmd  el6751_killcmd
	#define CHK_el6751_killcmd  TRUE
	#define EXP_el6751_killcmd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_killcmd", (RTS_UINTPTR)el6751_killcmd, 1, 0x53D657BE, 0x3030014) 
#elif defined(MIXED_LINK) && !defined(CMPEL6751CANDRV_EXTERNAL)
	#define USE_el6751_killcmd
	#define EXT_el6751_killcmd
	#define GET_el6751_killcmd(fl)  CAL_CMGETAPI( "el6751_killcmd" ) 
	#define CAL_el6751_killcmd  el6751_killcmd
	#define CHK_el6751_killcmd  TRUE
	#define EXP_el6751_killcmd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_killcmd", (RTS_UINTPTR)el6751_killcmd, 1, 0x53D657BE, 0x3030014) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEL6751CanDrvel6751_killcmd
	#define EXT_CmpEL6751CanDrvel6751_killcmd
	#define GET_CmpEL6751CanDrvel6751_killcmd  ERR_OK
	#define CAL_CmpEL6751CanDrvel6751_killcmd  el6751_killcmd
	#define CHK_CmpEL6751CanDrvel6751_killcmd  TRUE
	#define EXP_CmpEL6751CanDrvel6751_killcmd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_killcmd", (RTS_UINTPTR)el6751_killcmd, 1, 0x53D657BE, 0x3030014) 
#elif defined(CPLUSPLUS)
	#define USE_el6751_killcmd
	#define EXT_el6751_killcmd
	#define GET_el6751_killcmd(fl)  CAL_CMGETAPI( "el6751_killcmd" ) 
	#define CAL_el6751_killcmd  el6751_killcmd
	#define CHK_el6751_killcmd  TRUE
	#define EXP_el6751_killcmd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_killcmd", (RTS_UINTPTR)el6751_killcmd, 1, 0x53D657BE, 0x3030014) 
#else /* DYNAMIC_LINK */
	#define USE_el6751_killcmd  PFEL6751_KILLCMD_IEC pfel6751_killcmd;
	#define EXT_el6751_killcmd  extern PFEL6751_KILLCMD_IEC pfel6751_killcmd;
	#define GET_el6751_killcmd(fl)  s_pfCMGetAPI2( "el6751_killcmd", (RTS_VOID_FCTPTR *)&pfel6751_killcmd, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x53D657BE, 0x3030014)
	#define CAL_el6751_killcmd  pfel6751_killcmd
	#define CHK_el6751_killcmd  (pfel6751_killcmd != NULL)
	#define EXP_el6751_killcmd   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_killcmd", (RTS_UINTPTR)el6751_killcmd, 1, 0x53D657BE, 0x3030014) 
#endif

void CDECL CDECL_EXT el6751_registercmd(el6751_registercmd_struct *p);
typedef void (CDECL CDECL_EXT* PFEL6751_REGISTERCMD_IEC) (el6751_registercmd_struct *p);
#if defined(CMPEL6751CANDRV_NOTIMPLEMENTED) || defined(EL6751_REGISTERCMD_NOTIMPLEMENTED)
	#define USE_el6751_registercmd
	#define EXT_el6751_registercmd
	#define GET_el6751_registercmd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_el6751_registercmd(p0) 
	#define CHK_el6751_registercmd  FALSE
	#define EXP_el6751_registercmd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_el6751_registercmd
	#define EXT_el6751_registercmd
	#define GET_el6751_registercmd(fl)  CAL_CMGETAPI( "el6751_registercmd" ) 
	#define CAL_el6751_registercmd  el6751_registercmd
	#define CHK_el6751_registercmd  TRUE
	#define EXP_el6751_registercmd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_registercmd", (RTS_UINTPTR)el6751_registercmd, 1, 0xD69C906, 0x3030014) 
#elif defined(MIXED_LINK) && !defined(CMPEL6751CANDRV_EXTERNAL)
	#define USE_el6751_registercmd
	#define EXT_el6751_registercmd
	#define GET_el6751_registercmd(fl)  CAL_CMGETAPI( "el6751_registercmd" ) 
	#define CAL_el6751_registercmd  el6751_registercmd
	#define CHK_el6751_registercmd  TRUE
	#define EXP_el6751_registercmd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_registercmd", (RTS_UINTPTR)el6751_registercmd, 1, 0xD69C906, 0x3030014) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEL6751CanDrvel6751_registercmd
	#define EXT_CmpEL6751CanDrvel6751_registercmd
	#define GET_CmpEL6751CanDrvel6751_registercmd  ERR_OK
	#define CAL_CmpEL6751CanDrvel6751_registercmd  el6751_registercmd
	#define CHK_CmpEL6751CanDrvel6751_registercmd  TRUE
	#define EXP_CmpEL6751CanDrvel6751_registercmd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_registercmd", (RTS_UINTPTR)el6751_registercmd, 1, 0xD69C906, 0x3030014) 
#elif defined(CPLUSPLUS)
	#define USE_el6751_registercmd
	#define EXT_el6751_registercmd
	#define GET_el6751_registercmd(fl)  CAL_CMGETAPI( "el6751_registercmd" ) 
	#define CAL_el6751_registercmd  el6751_registercmd
	#define CHK_el6751_registercmd  TRUE
	#define EXP_el6751_registercmd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_registercmd", (RTS_UINTPTR)el6751_registercmd, 1, 0xD69C906, 0x3030014) 
#else /* DYNAMIC_LINK */
	#define USE_el6751_registercmd  PFEL6751_REGISTERCMD_IEC pfel6751_registercmd;
	#define EXT_el6751_registercmd  extern PFEL6751_REGISTERCMD_IEC pfel6751_registercmd;
	#define GET_el6751_registercmd(fl)  s_pfCMGetAPI2( "el6751_registercmd", (RTS_VOID_FCTPTR *)&pfel6751_registercmd, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD69C906, 0x3030014)
	#define CAL_el6751_registercmd  pfel6751_registercmd
	#define CHK_el6751_registercmd  (pfel6751_registercmd != NULL)
	#define EXP_el6751_registercmd   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_registercmd", (RTS_UINTPTR)el6751_registercmd, 1, 0xD69C906, 0x3030014) 
#endif

void CDECL CDECL_EXT el6751_afterreadinputs(el6751_afterreadinputs_struct *p);
typedef void (CDECL CDECL_EXT* PFEL6751_AFTERREADINPUTS_IEC) (el6751_afterreadinputs_struct *p);
#if defined(CMPEL6751CANDRV_NOTIMPLEMENTED) || defined(EL6751_AFTERREADINPUTS_NOTIMPLEMENTED)
	#define USE_el6751_afterreadinputs
	#define EXT_el6751_afterreadinputs
	#define GET_el6751_afterreadinputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_el6751_afterreadinputs(p0) 
	#define CHK_el6751_afterreadinputs  FALSE
	#define EXP_el6751_afterreadinputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_el6751_afterreadinputs
	#define EXT_el6751_afterreadinputs
	#define GET_el6751_afterreadinputs(fl)  CAL_CMGETAPI( "el6751_afterreadinputs" ) 
	#define CAL_el6751_afterreadinputs  el6751_afterreadinputs
	#define CHK_el6751_afterreadinputs  TRUE
	#define EXP_el6751_afterreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_afterreadinputs", (RTS_UINTPTR)el6751_afterreadinputs, 1, 0x157B908B, 0x3030014) 
#elif defined(MIXED_LINK) && !defined(CMPEL6751CANDRV_EXTERNAL)
	#define USE_el6751_afterreadinputs
	#define EXT_el6751_afterreadinputs
	#define GET_el6751_afterreadinputs(fl)  CAL_CMGETAPI( "el6751_afterreadinputs" ) 
	#define CAL_el6751_afterreadinputs  el6751_afterreadinputs
	#define CHK_el6751_afterreadinputs  TRUE
	#define EXP_el6751_afterreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_afterreadinputs", (RTS_UINTPTR)el6751_afterreadinputs, 1, 0x157B908B, 0x3030014) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEL6751CanDrvel6751_afterreadinputs
	#define EXT_CmpEL6751CanDrvel6751_afterreadinputs
	#define GET_CmpEL6751CanDrvel6751_afterreadinputs  ERR_OK
	#define CAL_CmpEL6751CanDrvel6751_afterreadinputs  el6751_afterreadinputs
	#define CHK_CmpEL6751CanDrvel6751_afterreadinputs  TRUE
	#define EXP_CmpEL6751CanDrvel6751_afterreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_afterreadinputs", (RTS_UINTPTR)el6751_afterreadinputs, 1, 0x157B908B, 0x3030014) 
#elif defined(CPLUSPLUS)
	#define USE_el6751_afterreadinputs
	#define EXT_el6751_afterreadinputs
	#define GET_el6751_afterreadinputs(fl)  CAL_CMGETAPI( "el6751_afterreadinputs" ) 
	#define CAL_el6751_afterreadinputs  el6751_afterreadinputs
	#define CHK_el6751_afterreadinputs  TRUE
	#define EXP_el6751_afterreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_afterreadinputs", (RTS_UINTPTR)el6751_afterreadinputs, 1, 0x157B908B, 0x3030014) 
#else /* DYNAMIC_LINK */
	#define USE_el6751_afterreadinputs  PFEL6751_AFTERREADINPUTS_IEC pfel6751_afterreadinputs;
	#define EXT_el6751_afterreadinputs  extern PFEL6751_AFTERREADINPUTS_IEC pfel6751_afterreadinputs;
	#define GET_el6751_afterreadinputs(fl)  s_pfCMGetAPI2( "el6751_afterreadinputs", (RTS_VOID_FCTPTR *)&pfel6751_afterreadinputs, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x157B908B, 0x3030014)
	#define CAL_el6751_afterreadinputs  pfel6751_afterreadinputs
	#define CHK_el6751_afterreadinputs  (pfel6751_afterreadinputs != NULL)
	#define EXP_el6751_afterreadinputs   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_afterreadinputs", (RTS_UINTPTR)el6751_afterreadinputs, 1, 0x157B908B, 0x3030014) 
#endif

void CDECL CDECL_EXT el6751_beforewriteoutputs(el6751_beforewriteoutputs_struct *p);
typedef void (CDECL CDECL_EXT* PFEL6751_BEFOREWRITEOUTPUTS_IEC) (el6751_beforewriteoutputs_struct *p);
#if defined(CMPEL6751CANDRV_NOTIMPLEMENTED) || defined(EL6751_BEFOREWRITEOUTPUTS_NOTIMPLEMENTED)
	#define USE_el6751_beforewriteoutputs
	#define EXT_el6751_beforewriteoutputs
	#define GET_el6751_beforewriteoutputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_el6751_beforewriteoutputs(p0) 
	#define CHK_el6751_beforewriteoutputs  FALSE
	#define EXP_el6751_beforewriteoutputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_el6751_beforewriteoutputs
	#define EXT_el6751_beforewriteoutputs
	#define GET_el6751_beforewriteoutputs(fl)  CAL_CMGETAPI( "el6751_beforewriteoutputs" ) 
	#define CAL_el6751_beforewriteoutputs  el6751_beforewriteoutputs
	#define CHK_el6751_beforewriteoutputs  TRUE
	#define EXP_el6751_beforewriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_beforewriteoutputs", (RTS_UINTPTR)el6751_beforewriteoutputs, 1, 0x5E9C43EC, 0x3030014) 
#elif defined(MIXED_LINK) && !defined(CMPEL6751CANDRV_EXTERNAL)
	#define USE_el6751_beforewriteoutputs
	#define EXT_el6751_beforewriteoutputs
	#define GET_el6751_beforewriteoutputs(fl)  CAL_CMGETAPI( "el6751_beforewriteoutputs" ) 
	#define CAL_el6751_beforewriteoutputs  el6751_beforewriteoutputs
	#define CHK_el6751_beforewriteoutputs  TRUE
	#define EXP_el6751_beforewriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_beforewriteoutputs", (RTS_UINTPTR)el6751_beforewriteoutputs, 1, 0x5E9C43EC, 0x3030014) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEL6751CanDrvel6751_beforewriteoutputs
	#define EXT_CmpEL6751CanDrvel6751_beforewriteoutputs
	#define GET_CmpEL6751CanDrvel6751_beforewriteoutputs  ERR_OK
	#define CAL_CmpEL6751CanDrvel6751_beforewriteoutputs  el6751_beforewriteoutputs
	#define CHK_CmpEL6751CanDrvel6751_beforewriteoutputs  TRUE
	#define EXP_CmpEL6751CanDrvel6751_beforewriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_beforewriteoutputs", (RTS_UINTPTR)el6751_beforewriteoutputs, 1, 0x5E9C43EC, 0x3030014) 
#elif defined(CPLUSPLUS)
	#define USE_el6751_beforewriteoutputs
	#define EXT_el6751_beforewriteoutputs
	#define GET_el6751_beforewriteoutputs(fl)  CAL_CMGETAPI( "el6751_beforewriteoutputs" ) 
	#define CAL_el6751_beforewriteoutputs  el6751_beforewriteoutputs
	#define CHK_el6751_beforewriteoutputs  TRUE
	#define EXP_el6751_beforewriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_beforewriteoutputs", (RTS_UINTPTR)el6751_beforewriteoutputs, 1, 0x5E9C43EC, 0x3030014) 
#else /* DYNAMIC_LINK */
	#define USE_el6751_beforewriteoutputs  PFEL6751_BEFOREWRITEOUTPUTS_IEC pfel6751_beforewriteoutputs;
	#define EXT_el6751_beforewriteoutputs  extern PFEL6751_BEFOREWRITEOUTPUTS_IEC pfel6751_beforewriteoutputs;
	#define GET_el6751_beforewriteoutputs(fl)  s_pfCMGetAPI2( "el6751_beforewriteoutputs", (RTS_VOID_FCTPTR *)&pfel6751_beforewriteoutputs, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x5E9C43EC, 0x3030014)
	#define CAL_el6751_beforewriteoutputs  pfel6751_beforewriteoutputs
	#define CHK_el6751_beforewriteoutputs  (pfel6751_beforewriteoutputs != NULL)
	#define EXP_el6751_beforewriteoutputs   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"el6751_beforewriteoutputs", (RTS_UINTPTR)el6751_beforewriteoutputs, 1, 0x5E9C43EC, 0x3030014) 
#endif


#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpEL6751CanDrv_C;

#ifdef CPLUSPLUS
class ICmpEL6751CanDrv : public IBase
{
	public:
};
	#ifndef ITF_CmpEL6751CanDrv
		#define ITF_CmpEL6751CanDrv static ICmpEL6751CanDrv *pICmpEL6751CanDrv = NULL;
	#endif
	#define EXTITF_CmpEL6751CanDrv
#else	/*CPLUSPLUS*/
	typedef ICmpEL6751CanDrv_C		ICmpEL6751CanDrv;
	#ifndef ITF_CmpEL6751CanDrv
		#define ITF_CmpEL6751CanDrv
	#endif
	#define EXTITF_CmpEL6751CanDrv
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPEL6751CANDRVITF_H_*/
