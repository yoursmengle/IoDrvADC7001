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


	
	
#ifndef _CMPIODRVCITF_H_
#define _CMPIODRVCITF_H_

#include "CmpStd.h"

 

 




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

void CDECL CDECL_EXT cmpiodrvc__main(cmpiodrvc_main_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__MAIN_IEC) (cmpiodrvc_main_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__MAIN_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__main
	#define EXT_cmpiodrvc__main
	#define GET_cmpiodrvc__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__main(p0) 
	#define CHK_cmpiodrvc__main  FALSE
	#define EXP_cmpiodrvc__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__main
	#define EXT_cmpiodrvc__main
	#define GET_cmpiodrvc__main(fl)  CAL_CMGETAPI( "cmpiodrvc__main" ) 
	#define CAL_cmpiodrvc__main  cmpiodrvc__main
	#define CHK_cmpiodrvc__main  TRUE
	#define EXP_cmpiodrvc__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__main", (RTS_UINTPTR)cmpiodrvc__main, 1, 0/*0xFA08D30C*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__main
	#define EXT_cmpiodrvc__main
	#define GET_cmpiodrvc__main(fl)  CAL_CMGETAPI( "cmpiodrvc__main" ) 
	#define CAL_cmpiodrvc__main  cmpiodrvc__main
	#define CHK_cmpiodrvc__main  TRUE
	#define EXP_cmpiodrvc__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__main", (RTS_UINTPTR)cmpiodrvc__main, 1, 0/*0xFA08D30C*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__main
	#define EXT_CmpIoDrvCcmpiodrvc__main
	#define GET_CmpIoDrvCcmpiodrvc__main  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__main  cmpiodrvc__main
	#define CHK_CmpIoDrvCcmpiodrvc__main  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__main", (RTS_UINTPTR)cmpiodrvc__main, 1, 0/*0xFA08D30C*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__main
	#define EXT_cmpiodrvc__main
	#define GET_cmpiodrvc__main(fl)  CAL_CMGETAPI( "cmpiodrvc__main" ) 
	#define CAL_cmpiodrvc__main  cmpiodrvc__main
	#define CHK_cmpiodrvc__main  TRUE
	#define EXP_cmpiodrvc__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__main", (RTS_UINTPTR)cmpiodrvc__main, 1, 0/*0xFA08D30C*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__main  PFCMPIODRVC__MAIN_IEC pfcmpiodrvc__main;
	#define EXT_cmpiodrvc__main  extern PFCMPIODRVC__MAIN_IEC pfcmpiodrvc__main;
	#define GET_cmpiodrvc__main(fl)  s_pfCMGetAPI2( "cmpiodrvc__main", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0xFA08D30C*/, 0x3050000)
	#define CAL_cmpiodrvc__main  pfcmpiodrvc__main
	#define CHK_cmpiodrvc__main  (pfcmpiodrvc__main != NULL)
	#define EXP_cmpiodrvc__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__main", (RTS_UINTPTR)cmpiodrvc__main, 1, 0/*0xFA08D30C*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvdpv1_c1_m_alarm</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c1_m_alarm_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C1_Alarm *dpv1Alarm;			/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C1_M_Alarm;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c1_m_alarm_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvdpv1_c1_m_alarm(cmpiodrvc_iodrvdpv1_c1_m_alarm_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVDPV1_C1_M_ALARM_IEC) (cmpiodrvc_iodrvdpv1_c1_m_alarm_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVDPV1_C1_M_ALARM_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_alarm(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_alarm(p0) 
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_alarm  FALSE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_alarm  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_alarm(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_alarm" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_alarm  cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_alarm  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_alarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_alarm", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_alarm, 1, 0/*0xE8E6FDC5*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_alarm(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_alarm" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_alarm  cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_alarm  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_alarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_alarm", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_alarm, 1, 0/*0xE8E6FDC5*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarm
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarm
	#define GET_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarm  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarm  cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarm  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_alarm", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_alarm, 1, 0/*0xE8E6FDC5*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_alarm(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_alarm" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_alarm  cmpiodrvc__iodrvdpv1_c1_m_alarm
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_alarm  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_alarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_alarm", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_alarm, 1, 0/*0xE8E6FDC5*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_alarm  PFCMPIODRVC__IODRVDPV1_C1_M_ALARM_IEC pfcmpiodrvc__iodrvdpv1_c1_m_alarm;
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_alarm  extern PFCMPIODRVC__IODRVDPV1_C1_M_ALARM_IEC pfcmpiodrvc__iodrvdpv1_c1_m_alarm;
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_alarm(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvdpv1_c1_m_alarm", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvdpv1_c1_m_alarm, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0xE8E6FDC5*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_alarm  pfcmpiodrvc__iodrvdpv1_c1_m_alarm
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_alarm  (pfcmpiodrvc__iodrvdpv1_c1_m_alarm != NULL)
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_alarm   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_alarm", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_alarm, 1, 0/*0xE8E6FDC5*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvidentify</description>
 */
typedef struct tagcmpiodrvc_iodrvidentify_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvIdentify;		/* VAR_OUTPUT */
} cmpiodrvc_iodrvidentify_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvidentify(cmpiodrvc_iodrvidentify_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVIDENTIFY_IEC) (cmpiodrvc_iodrvidentify_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVIDENTIFY_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvidentify
	#define EXT_cmpiodrvc__iodrvidentify
	#define GET_cmpiodrvc__iodrvidentify(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvidentify(p0) 
	#define CHK_cmpiodrvc__iodrvidentify  FALSE
	#define EXP_cmpiodrvc__iodrvidentify  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvidentify
	#define EXT_cmpiodrvc__iodrvidentify
	#define GET_cmpiodrvc__iodrvidentify(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvidentify" ) 
	#define CAL_cmpiodrvc__iodrvidentify  cmpiodrvc__iodrvidentify
	#define CHK_cmpiodrvc__iodrvidentify  TRUE
	#define EXP_cmpiodrvc__iodrvidentify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvidentify", (RTS_UINTPTR)cmpiodrvc__iodrvidentify, 1, 0/*0x71D91E4E*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvidentify
	#define EXT_cmpiodrvc__iodrvidentify
	#define GET_cmpiodrvc__iodrvidentify(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvidentify" ) 
	#define CAL_cmpiodrvc__iodrvidentify  cmpiodrvc__iodrvidentify
	#define CHK_cmpiodrvc__iodrvidentify  TRUE
	#define EXP_cmpiodrvc__iodrvidentify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvidentify", (RTS_UINTPTR)cmpiodrvc__iodrvidentify, 1, 0/*0x71D91E4E*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvidentify
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvidentify
	#define GET_CmpIoDrvCcmpiodrvc__iodrvidentify  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvidentify  cmpiodrvc__iodrvidentify
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvidentify  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvidentify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvidentify", (RTS_UINTPTR)cmpiodrvc__iodrvidentify, 1, 0/*0x71D91E4E*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvidentify
	#define EXT_cmpiodrvc__iodrvidentify
	#define GET_cmpiodrvc__iodrvidentify(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvidentify" ) 
	#define CAL_cmpiodrvc__iodrvidentify  cmpiodrvc__iodrvidentify
	#define CHK_cmpiodrvc__iodrvidentify  TRUE
	#define EXP_cmpiodrvc__iodrvidentify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvidentify", (RTS_UINTPTR)cmpiodrvc__iodrvidentify, 1, 0/*0x71D91E4E*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvidentify  PFCMPIODRVC__IODRVIDENTIFY_IEC pfcmpiodrvc__iodrvidentify;
	#define EXT_cmpiodrvc__iodrvidentify  extern PFCMPIODRVC__IODRVIDENTIFY_IEC pfcmpiodrvc__iodrvidentify;
	#define GET_cmpiodrvc__iodrvidentify(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvidentify", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvidentify, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x71D91E4E*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvidentify  pfcmpiodrvc__iodrvidentify
	#define CHK_cmpiodrvc__iodrvidentify  (pfcmpiodrvc__iodrvidentify != NULL)
	#define EXP_cmpiodrvc__iodrvidentify   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvidentify", (RTS_UINTPTR)cmpiodrvc__iodrvidentify, 1, 0/*0x71D91E4E*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvdpv1_c1_m_alarmack</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c1_m_alarmack_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C1_AlarmAck *dpv1AlarmAck;		/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C1_M_AlarmAck;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c1_m_alarmack_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvdpv1_c1_m_alarmack(cmpiodrvc_iodrvdpv1_c1_m_alarmack_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVDPV1_C1_M_ALARMACK_IEC) (cmpiodrvc_iodrvdpv1_c1_m_alarmack_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVDPV1_C1_M_ALARMACK_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_alarmack(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_alarmack(p0) 
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_alarmack  FALSE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_alarmack  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_alarmack(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_alarmack" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_alarmack  cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_alarmack  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_alarmack  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_alarmack", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_alarmack, 1, 0/*0x91B9E17F*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_alarmack(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_alarmack" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_alarmack  cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_alarmack  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_alarmack  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_alarmack", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_alarmack, 1, 0/*0x91B9E17F*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define GET_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarmack  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarmack  cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarmack  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_alarmack  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_alarmack", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_alarmack, 1, 0/*0x91B9E17F*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_alarmack(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_alarmack" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_alarmack  cmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_alarmack  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_alarmack  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_alarmack", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_alarmack, 1, 0/*0x91B9E17F*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_alarmack  PFCMPIODRVC__IODRVDPV1_C1_M_ALARMACK_IEC pfcmpiodrvc__iodrvdpv1_c1_m_alarmack;
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_alarmack  extern PFCMPIODRVC__IODRVDPV1_C1_M_ALARMACK_IEC pfcmpiodrvc__iodrvdpv1_c1_m_alarmack;
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_alarmack(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvdpv1_c1_m_alarmack", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvdpv1_c1_m_alarmack, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x91B9E17F*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_alarmack  pfcmpiodrvc__iodrvdpv1_c1_m_alarmack
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_alarmack  (pfcmpiodrvc__iodrvdpv1_c1_m_alarmack != NULL)
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_alarmack   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_alarmack", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_alarmack, 1, 0/*0x91B9E17F*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__release</description>
 */
typedef struct tagcmpiodrvc_release_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	RTS_IEC_DINT Release;				/* VAR_OUTPUT */
} cmpiodrvc_release_struct;

void CDECL CDECL_EXT cmpiodrvc__release(cmpiodrvc_release_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__RELEASE_IEC) (cmpiodrvc_release_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__RELEASE_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__release
	#define EXT_cmpiodrvc__release
	#define GET_cmpiodrvc__release(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__release(p0) 
	#define CHK_cmpiodrvc__release  FALSE
	#define EXP_cmpiodrvc__release  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__release
	#define EXT_cmpiodrvc__release
	#define GET_cmpiodrvc__release(fl)  CAL_CMGETAPI( "cmpiodrvc__release" ) 
	#define CAL_cmpiodrvc__release  cmpiodrvc__release
	#define CHK_cmpiodrvc__release  TRUE
	#define EXP_cmpiodrvc__release  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__release", (RTS_UINTPTR)cmpiodrvc__release, 1, 0/*0xC21041B1*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__release
	#define EXT_cmpiodrvc__release
	#define GET_cmpiodrvc__release(fl)  CAL_CMGETAPI( "cmpiodrvc__release" ) 
	#define CAL_cmpiodrvc__release  cmpiodrvc__release
	#define CHK_cmpiodrvc__release  TRUE
	#define EXP_cmpiodrvc__release  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__release", (RTS_UINTPTR)cmpiodrvc__release, 1, 0/*0xC21041B1*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__release
	#define EXT_CmpIoDrvCcmpiodrvc__release
	#define GET_CmpIoDrvCcmpiodrvc__release  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__release  cmpiodrvc__release
	#define CHK_CmpIoDrvCcmpiodrvc__release  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__release  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__release", (RTS_UINTPTR)cmpiodrvc__release, 1, 0/*0xC21041B1*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__release
	#define EXT_cmpiodrvc__release
	#define GET_cmpiodrvc__release(fl)  CAL_CMGETAPI( "cmpiodrvc__release" ) 
	#define CAL_cmpiodrvc__release  cmpiodrvc__release
	#define CHK_cmpiodrvc__release  TRUE
	#define EXP_cmpiodrvc__release  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__release", (RTS_UINTPTR)cmpiodrvc__release, 1, 0/*0xC21041B1*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__release  PFCMPIODRVC__RELEASE_IEC pfcmpiodrvc__release;
	#define EXT_cmpiodrvc__release  extern PFCMPIODRVC__RELEASE_IEC pfcmpiodrvc__release;
	#define GET_cmpiodrvc__release(fl)  s_pfCMGetAPI2( "cmpiodrvc__release", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__release, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0xC21041B1*/, 0x3050000)
	#define CAL_cmpiodrvc__release  pfcmpiodrvc__release
	#define CHK_cmpiodrvc__release  (pfcmpiodrvc__release != NULL)
	#define EXP_cmpiodrvc__release   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__release", (RTS_UINTPTR)cmpiodrvc__release, 1, 0/*0xC21041B1*/, 0x3050000) 
#endif


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

void CDECL CDECL_EXT cmpiodrvc__iodrvreadparameter(cmpiodrvc_iodrvreadparameter_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVREADPARAMETER_IEC) (cmpiodrvc_iodrvreadparameter_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVREADPARAMETER_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvreadparameter
	#define EXT_cmpiodrvc__iodrvreadparameter
	#define GET_cmpiodrvc__iodrvreadparameter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvreadparameter(p0) 
	#define CHK_cmpiodrvc__iodrvreadparameter  FALSE
	#define EXP_cmpiodrvc__iodrvreadparameter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvreadparameter
	#define EXT_cmpiodrvc__iodrvreadparameter
	#define GET_cmpiodrvc__iodrvreadparameter(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvreadparameter" ) 
	#define CAL_cmpiodrvc__iodrvreadparameter  cmpiodrvc__iodrvreadparameter
	#define CHK_cmpiodrvc__iodrvreadparameter  TRUE
	#define EXP_cmpiodrvc__iodrvreadparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvreadparameter", (RTS_UINTPTR)cmpiodrvc__iodrvreadparameter, 1, 0/*0x263580FA*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvreadparameter
	#define EXT_cmpiodrvc__iodrvreadparameter
	#define GET_cmpiodrvc__iodrvreadparameter(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvreadparameter" ) 
	#define CAL_cmpiodrvc__iodrvreadparameter  cmpiodrvc__iodrvreadparameter
	#define CHK_cmpiodrvc__iodrvreadparameter  TRUE
	#define EXP_cmpiodrvc__iodrvreadparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvreadparameter", (RTS_UINTPTR)cmpiodrvc__iodrvreadparameter, 1, 0/*0x263580FA*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvreadparameter
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvreadparameter
	#define GET_CmpIoDrvCcmpiodrvc__iodrvreadparameter  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvreadparameter  cmpiodrvc__iodrvreadparameter
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvreadparameter  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvreadparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvreadparameter", (RTS_UINTPTR)cmpiodrvc__iodrvreadparameter, 1, 0/*0x263580FA*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvreadparameter
	#define EXT_cmpiodrvc__iodrvreadparameter
	#define GET_cmpiodrvc__iodrvreadparameter(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvreadparameter" ) 
	#define CAL_cmpiodrvc__iodrvreadparameter  cmpiodrvc__iodrvreadparameter
	#define CHK_cmpiodrvc__iodrvreadparameter  TRUE
	#define EXP_cmpiodrvc__iodrvreadparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvreadparameter", (RTS_UINTPTR)cmpiodrvc__iodrvreadparameter, 1, 0/*0x263580FA*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvreadparameter  PFCMPIODRVC__IODRVREADPARAMETER_IEC pfcmpiodrvc__iodrvreadparameter;
	#define EXT_cmpiodrvc__iodrvreadparameter  extern PFCMPIODRVC__IODRVREADPARAMETER_IEC pfcmpiodrvc__iodrvreadparameter;
	#define GET_cmpiodrvc__iodrvreadparameter(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvreadparameter", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvreadparameter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x263580FA*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvreadparameter  pfcmpiodrvc__iodrvreadparameter
	#define CHK_cmpiodrvc__iodrvreadparameter  (pfcmpiodrvc__iodrvreadparameter != NULL)
	#define EXP_cmpiodrvc__iodrvreadparameter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvreadparameter", (RTS_UINTPTR)cmpiodrvc__iodrvreadparameter, 1, 0/*0x263580FA*/, 0x3050000) 
#endif


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

void CDECL CDECL_EXT cmpiodrvc__iodrvwriteoutputs(cmpiodrvc_iodrvwriteoutputs_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVWRITEOUTPUTS_IEC) (cmpiodrvc_iodrvwriteoutputs_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVWRITEOUTPUTS_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvwriteoutputs
	#define EXT_cmpiodrvc__iodrvwriteoutputs
	#define GET_cmpiodrvc__iodrvwriteoutputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvwriteoutputs(p0) 
	#define CHK_cmpiodrvc__iodrvwriteoutputs  FALSE
	#define EXP_cmpiodrvc__iodrvwriteoutputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvwriteoutputs
	#define EXT_cmpiodrvc__iodrvwriteoutputs
	#define GET_cmpiodrvc__iodrvwriteoutputs(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvwriteoutputs" ) 
	#define CAL_cmpiodrvc__iodrvwriteoutputs  cmpiodrvc__iodrvwriteoutputs
	#define CHK_cmpiodrvc__iodrvwriteoutputs  TRUE
	#define EXP_cmpiodrvc__iodrvwriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwriteoutputs", (RTS_UINTPTR)cmpiodrvc__iodrvwriteoutputs, 1, 0/*0x10DE7EF4*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvwriteoutputs
	#define EXT_cmpiodrvc__iodrvwriteoutputs
	#define GET_cmpiodrvc__iodrvwriteoutputs(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvwriteoutputs" ) 
	#define CAL_cmpiodrvc__iodrvwriteoutputs  cmpiodrvc__iodrvwriteoutputs
	#define CHK_cmpiodrvc__iodrvwriteoutputs  TRUE
	#define EXP_cmpiodrvc__iodrvwriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwriteoutputs", (RTS_UINTPTR)cmpiodrvc__iodrvwriteoutputs, 1, 0/*0x10DE7EF4*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvwriteoutputs
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvwriteoutputs
	#define GET_CmpIoDrvCcmpiodrvc__iodrvwriteoutputs  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvwriteoutputs  cmpiodrvc__iodrvwriteoutputs
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvwriteoutputs  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvwriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwriteoutputs", (RTS_UINTPTR)cmpiodrvc__iodrvwriteoutputs, 1, 0/*0x10DE7EF4*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvwriteoutputs
	#define EXT_cmpiodrvc__iodrvwriteoutputs
	#define GET_cmpiodrvc__iodrvwriteoutputs(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvwriteoutputs" ) 
	#define CAL_cmpiodrvc__iodrvwriteoutputs  cmpiodrvc__iodrvwriteoutputs
	#define CHK_cmpiodrvc__iodrvwriteoutputs  TRUE
	#define EXP_cmpiodrvc__iodrvwriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwriteoutputs", (RTS_UINTPTR)cmpiodrvc__iodrvwriteoutputs, 1, 0/*0x10DE7EF4*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvwriteoutputs  PFCMPIODRVC__IODRVWRITEOUTPUTS_IEC pfcmpiodrvc__iodrvwriteoutputs;
	#define EXT_cmpiodrvc__iodrvwriteoutputs  extern PFCMPIODRVC__IODRVWRITEOUTPUTS_IEC pfcmpiodrvc__iodrvwriteoutputs;
	#define GET_cmpiodrvc__iodrvwriteoutputs(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvwriteoutputs", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvwriteoutputs, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x10DE7EF4*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvwriteoutputs  pfcmpiodrvc__iodrvwriteoutputs
	#define CHK_cmpiodrvc__iodrvwriteoutputs  (pfcmpiodrvc__iodrvwriteoutputs != NULL)
	#define EXP_cmpiodrvc__iodrvwriteoutputs   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwriteoutputs", (RTS_UINTPTR)cmpiodrvc__iodrvwriteoutputs, 1, 0/*0x10DE7EF4*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvgetmodulediagnosis</description>
 */
typedef struct tagcmpiodrvc_iodrvgetmodulediagnosis_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvGetModuleDiagnosis;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvgetmodulediagnosis_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvgetmodulediagnosis(cmpiodrvc_iodrvgetmodulediagnosis_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVGETMODULEDIAGNOSIS_IEC) (cmpiodrvc_iodrvgetmodulediagnosis_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVGETMODULEDIAGNOSIS_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvgetmodulediagnosis
	#define EXT_cmpiodrvc__iodrvgetmodulediagnosis
	#define GET_cmpiodrvc__iodrvgetmodulediagnosis(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvgetmodulediagnosis(p0) 
	#define CHK_cmpiodrvc__iodrvgetmodulediagnosis  FALSE
	#define EXP_cmpiodrvc__iodrvgetmodulediagnosis  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvgetmodulediagnosis
	#define EXT_cmpiodrvc__iodrvgetmodulediagnosis
	#define GET_cmpiodrvc__iodrvgetmodulediagnosis(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvgetmodulediagnosis" ) 
	#define CAL_cmpiodrvc__iodrvgetmodulediagnosis  cmpiodrvc__iodrvgetmodulediagnosis
	#define CHK_cmpiodrvc__iodrvgetmodulediagnosis  TRUE
	#define EXP_cmpiodrvc__iodrvgetmodulediagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvgetmodulediagnosis", (RTS_UINTPTR)cmpiodrvc__iodrvgetmodulediagnosis, 1, 0/*0x70DC4D0E*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvgetmodulediagnosis
	#define EXT_cmpiodrvc__iodrvgetmodulediagnosis
	#define GET_cmpiodrvc__iodrvgetmodulediagnosis(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvgetmodulediagnosis" ) 
	#define CAL_cmpiodrvc__iodrvgetmodulediagnosis  cmpiodrvc__iodrvgetmodulediagnosis
	#define CHK_cmpiodrvc__iodrvgetmodulediagnosis  TRUE
	#define EXP_cmpiodrvc__iodrvgetmodulediagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvgetmodulediagnosis", (RTS_UINTPTR)cmpiodrvc__iodrvgetmodulediagnosis, 1, 0/*0x70DC4D0E*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvgetmodulediagnosis
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvgetmodulediagnosis
	#define GET_CmpIoDrvCcmpiodrvc__iodrvgetmodulediagnosis  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvgetmodulediagnosis  cmpiodrvc__iodrvgetmodulediagnosis
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvgetmodulediagnosis  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvgetmodulediagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvgetmodulediagnosis", (RTS_UINTPTR)cmpiodrvc__iodrvgetmodulediagnosis, 1, 0/*0x70DC4D0E*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvgetmodulediagnosis
	#define EXT_cmpiodrvc__iodrvgetmodulediagnosis
	#define GET_cmpiodrvc__iodrvgetmodulediagnosis(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvgetmodulediagnosis" ) 
	#define CAL_cmpiodrvc__iodrvgetmodulediagnosis  cmpiodrvc__iodrvgetmodulediagnosis
	#define CHK_cmpiodrvc__iodrvgetmodulediagnosis  TRUE
	#define EXP_cmpiodrvc__iodrvgetmodulediagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvgetmodulediagnosis", (RTS_UINTPTR)cmpiodrvc__iodrvgetmodulediagnosis, 1, 0/*0x70DC4D0E*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvgetmodulediagnosis  PFCMPIODRVC__IODRVGETMODULEDIAGNOSIS_IEC pfcmpiodrvc__iodrvgetmodulediagnosis;
	#define EXT_cmpiodrvc__iodrvgetmodulediagnosis  extern PFCMPIODRVC__IODRVGETMODULEDIAGNOSIS_IEC pfcmpiodrvc__iodrvgetmodulediagnosis;
	#define GET_cmpiodrvc__iodrvgetmodulediagnosis(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvgetmodulediagnosis", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvgetmodulediagnosis, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x70DC4D0E*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvgetmodulediagnosis  pfcmpiodrvc__iodrvgetmodulediagnosis
	#define CHK_cmpiodrvc__iodrvgetmodulediagnosis  (pfcmpiodrvc__iodrvgetmodulediagnosis != NULL)
	#define EXP_cmpiodrvc__iodrvgetmodulediagnosis   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvgetmodulediagnosis", (RTS_UINTPTR)cmpiodrvc__iodrvgetmodulediagnosis, 1, 0/*0x70DC4D0E*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvdpv1_c1_m_read</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c1_m_read_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C1_Read *dpv1Read;				/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C1_M_Read;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c1_m_read_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvdpv1_c1_m_read(cmpiodrvc_iodrvdpv1_c1_m_read_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVDPV1_C1_M_READ_IEC) (cmpiodrvc_iodrvdpv1_c1_m_read_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVDPV1_C1_M_READ_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_read
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_read
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_read(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_read(p0) 
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_read  FALSE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_read  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_read
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_read
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_read(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_read" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_read  cmpiodrvc__iodrvdpv1_c1_m_read
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_read  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_read", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_read, 1, 0/*0x1CEA8FE0*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_read
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_read
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_read(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_read" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_read  cmpiodrvc__iodrvdpv1_c1_m_read
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_read  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_read", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_read, 1, 0/*0x1CEA8FE0*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_read
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_read
	#define GET_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_read  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_read  cmpiodrvc__iodrvdpv1_c1_m_read
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_read  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_read", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_read, 1, 0/*0x1CEA8FE0*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_read
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_read
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_read(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_read" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_read  cmpiodrvc__iodrvdpv1_c1_m_read
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_read  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_read", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_read, 1, 0/*0x1CEA8FE0*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_read  PFCMPIODRVC__IODRVDPV1_C1_M_READ_IEC pfcmpiodrvc__iodrvdpv1_c1_m_read;
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_read  extern PFCMPIODRVC__IODRVDPV1_C1_M_READ_IEC pfcmpiodrvc__iodrvdpv1_c1_m_read;
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_read(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvdpv1_c1_m_read", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvdpv1_c1_m_read, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x1CEA8FE0*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_read  pfcmpiodrvc__iodrvdpv1_c1_m_read
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_read  (pfcmpiodrvc__iodrvdpv1_c1_m_read != NULL)
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_read   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_read", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_read, 1, 0/*0x1CEA8FE0*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvdpv1_c2_m_abort</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c2_m_abort_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C2_Abort *dpv1c2_Abort;		/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C2_M_Abort;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c2_m_abort_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvdpv1_c2_m_abort(cmpiodrvc_iodrvdpv1_c2_m_abort_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVDPV1_C2_M_ABORT_IEC) (cmpiodrvc_iodrvdpv1_c2_m_abort_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVDPV1_C2_M_ABORT_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_abort
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_abort
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_abort(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_abort(p0) 
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_abort  FALSE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_abort  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_abort
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_abort
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_abort(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_abort" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_abort  cmpiodrvc__iodrvdpv1_c2_m_abort
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_abort  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_abort  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_abort", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_abort, 1, 0/*0x6BE2BA5E*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_abort
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_abort
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_abort(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_abort" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_abort  cmpiodrvc__iodrvdpv1_c2_m_abort
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_abort  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_abort  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_abort", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_abort, 1, 0/*0x6BE2BA5E*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_abort
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_abort
	#define GET_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_abort  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_abort  cmpiodrvc__iodrvdpv1_c2_m_abort
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_abort  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_abort  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_abort", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_abort, 1, 0/*0x6BE2BA5E*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_abort
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_abort
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_abort(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_abort" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_abort  cmpiodrvc__iodrvdpv1_c2_m_abort
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_abort  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_abort  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_abort", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_abort, 1, 0/*0x6BE2BA5E*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_abort  PFCMPIODRVC__IODRVDPV1_C2_M_ABORT_IEC pfcmpiodrvc__iodrvdpv1_c2_m_abort;
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_abort  extern PFCMPIODRVC__IODRVDPV1_C2_M_ABORT_IEC pfcmpiodrvc__iodrvdpv1_c2_m_abort;
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_abort(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvdpv1_c2_m_abort", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvdpv1_c2_m_abort, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x6BE2BA5E*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_abort  pfcmpiodrvc__iodrvdpv1_c2_m_abort
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_abort  (pfcmpiodrvc__iodrvdpv1_c2_m_abort != NULL)
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_abort   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_abort", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_abort, 1, 0/*0x6BE2BA5E*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvdpv1_c1_m_status</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c1_m_status_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C1_Status *dpv1Status;			/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C1_M_Status;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c1_m_status_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvdpv1_c1_m_status(cmpiodrvc_iodrvdpv1_c1_m_status_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVDPV1_C1_M_STATUS_IEC) (cmpiodrvc_iodrvdpv1_c1_m_status_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVDPV1_C1_M_STATUS_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_status
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_status
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_status(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_status(p0) 
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_status  FALSE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_status  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_status
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_status
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_status(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_status" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_status  cmpiodrvc__iodrvdpv1_c1_m_status
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_status  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_status  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_status", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_status, 1, 0/*0x7BA8079D*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_status
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_status
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_status(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_status" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_status  cmpiodrvc__iodrvdpv1_c1_m_status
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_status  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_status  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_status", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_status, 1, 0/*0x7BA8079D*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_status
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_status
	#define GET_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_status  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_status  cmpiodrvc__iodrvdpv1_c1_m_status
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_status  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_status  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_status", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_status, 1, 0/*0x7BA8079D*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_status
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_status
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_status(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_status" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_status  cmpiodrvc__iodrvdpv1_c1_m_status
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_status  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_status  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_status", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_status, 1, 0/*0x7BA8079D*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_status  PFCMPIODRVC__IODRVDPV1_C1_M_STATUS_IEC pfcmpiodrvc__iodrvdpv1_c1_m_status;
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_status  extern PFCMPIODRVC__IODRVDPV1_C1_M_STATUS_IEC pfcmpiodrvc__iodrvdpv1_c1_m_status;
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_status(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvdpv1_c1_m_status", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvdpv1_c1_m_status, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x7BA8079D*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_status  pfcmpiodrvc__iodrvdpv1_c1_m_status
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_status  (pfcmpiodrvc__iodrvdpv1_c1_m_status != NULL)
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_status   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_status", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_status, 1, 0/*0x7BA8079D*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvstartbuscycle</description>
 */
typedef struct tagcmpiodrvc_iodrvstartbuscycle_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvStartBusCycle;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvstartbuscycle_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvstartbuscycle(cmpiodrvc_iodrvstartbuscycle_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVSTARTBUSCYCLE_IEC) (cmpiodrvc_iodrvstartbuscycle_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVSTARTBUSCYCLE_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvstartbuscycle
	#define EXT_cmpiodrvc__iodrvstartbuscycle
	#define GET_cmpiodrvc__iodrvstartbuscycle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvstartbuscycle(p0) 
	#define CHK_cmpiodrvc__iodrvstartbuscycle  FALSE
	#define EXP_cmpiodrvc__iodrvstartbuscycle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvstartbuscycle
	#define EXT_cmpiodrvc__iodrvstartbuscycle
	#define GET_cmpiodrvc__iodrvstartbuscycle(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvstartbuscycle" ) 
	#define CAL_cmpiodrvc__iodrvstartbuscycle  cmpiodrvc__iodrvstartbuscycle
	#define CHK_cmpiodrvc__iodrvstartbuscycle  TRUE
	#define EXP_cmpiodrvc__iodrvstartbuscycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvstartbuscycle", (RTS_UINTPTR)cmpiodrvc__iodrvstartbuscycle, 1, 0/*0xE2AACEF3*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvstartbuscycle
	#define EXT_cmpiodrvc__iodrvstartbuscycle
	#define GET_cmpiodrvc__iodrvstartbuscycle(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvstartbuscycle" ) 
	#define CAL_cmpiodrvc__iodrvstartbuscycle  cmpiodrvc__iodrvstartbuscycle
	#define CHK_cmpiodrvc__iodrvstartbuscycle  TRUE
	#define EXP_cmpiodrvc__iodrvstartbuscycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvstartbuscycle", (RTS_UINTPTR)cmpiodrvc__iodrvstartbuscycle, 1, 0/*0xE2AACEF3*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvstartbuscycle
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvstartbuscycle
	#define GET_CmpIoDrvCcmpiodrvc__iodrvstartbuscycle  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvstartbuscycle  cmpiodrvc__iodrvstartbuscycle
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvstartbuscycle  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvstartbuscycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvstartbuscycle", (RTS_UINTPTR)cmpiodrvc__iodrvstartbuscycle, 1, 0/*0xE2AACEF3*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvstartbuscycle
	#define EXT_cmpiodrvc__iodrvstartbuscycle
	#define GET_cmpiodrvc__iodrvstartbuscycle(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvstartbuscycle" ) 
	#define CAL_cmpiodrvc__iodrvstartbuscycle  cmpiodrvc__iodrvstartbuscycle
	#define CHK_cmpiodrvc__iodrvstartbuscycle  TRUE
	#define EXP_cmpiodrvc__iodrvstartbuscycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvstartbuscycle", (RTS_UINTPTR)cmpiodrvc__iodrvstartbuscycle, 1, 0/*0xE2AACEF3*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvstartbuscycle  PFCMPIODRVC__IODRVSTARTBUSCYCLE_IEC pfcmpiodrvc__iodrvstartbuscycle;
	#define EXT_cmpiodrvc__iodrvstartbuscycle  extern PFCMPIODRVC__IODRVSTARTBUSCYCLE_IEC pfcmpiodrvc__iodrvstartbuscycle;
	#define GET_cmpiodrvc__iodrvstartbuscycle(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvstartbuscycle", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvstartbuscycle, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0xE2AACEF3*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvstartbuscycle  pfcmpiodrvc__iodrvstartbuscycle
	#define CHK_cmpiodrvc__iodrvstartbuscycle  (pfcmpiodrvc__iodrvstartbuscycle != NULL)
	#define EXP_cmpiodrvc__iodrvstartbuscycle   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvstartbuscycle", (RTS_UINTPTR)cmpiodrvc__iodrvstartbuscycle, 1, 0/*0xE2AACEF3*/, 0x3050000) 
#endif


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

void CDECL CDECL_EXT cmpiodrvc__iodrvupdateconfiguration(cmpiodrvc_iodrvupdateconfiguration_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVUPDATECONFIGURATION_IEC) (cmpiodrvc_iodrvupdateconfiguration_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVUPDATECONFIGURATION_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvupdateconfiguration
	#define EXT_cmpiodrvc__iodrvupdateconfiguration
	#define GET_cmpiodrvc__iodrvupdateconfiguration(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvupdateconfiguration(p0) 
	#define CHK_cmpiodrvc__iodrvupdateconfiguration  FALSE
	#define EXP_cmpiodrvc__iodrvupdateconfiguration  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvupdateconfiguration
	#define EXT_cmpiodrvc__iodrvupdateconfiguration
	#define GET_cmpiodrvc__iodrvupdateconfiguration(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvupdateconfiguration" ) 
	#define CAL_cmpiodrvc__iodrvupdateconfiguration  cmpiodrvc__iodrvupdateconfiguration
	#define CHK_cmpiodrvc__iodrvupdateconfiguration  TRUE
	#define EXP_cmpiodrvc__iodrvupdateconfiguration  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvupdateconfiguration", (RTS_UINTPTR)cmpiodrvc__iodrvupdateconfiguration, 1, 0/*0x5600F48B*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvupdateconfiguration
	#define EXT_cmpiodrvc__iodrvupdateconfiguration
	#define GET_cmpiodrvc__iodrvupdateconfiguration(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvupdateconfiguration" ) 
	#define CAL_cmpiodrvc__iodrvupdateconfiguration  cmpiodrvc__iodrvupdateconfiguration
	#define CHK_cmpiodrvc__iodrvupdateconfiguration  TRUE
	#define EXP_cmpiodrvc__iodrvupdateconfiguration  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvupdateconfiguration", (RTS_UINTPTR)cmpiodrvc__iodrvupdateconfiguration, 1, 0/*0x5600F48B*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvupdateconfiguration
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvupdateconfiguration
	#define GET_CmpIoDrvCcmpiodrvc__iodrvupdateconfiguration  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvupdateconfiguration  cmpiodrvc__iodrvupdateconfiguration
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvupdateconfiguration  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvupdateconfiguration  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvupdateconfiguration", (RTS_UINTPTR)cmpiodrvc__iodrvupdateconfiguration, 1, 0/*0x5600F48B*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvupdateconfiguration
	#define EXT_cmpiodrvc__iodrvupdateconfiguration
	#define GET_cmpiodrvc__iodrvupdateconfiguration(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvupdateconfiguration" ) 
	#define CAL_cmpiodrvc__iodrvupdateconfiguration  cmpiodrvc__iodrvupdateconfiguration
	#define CHK_cmpiodrvc__iodrvupdateconfiguration  TRUE
	#define EXP_cmpiodrvc__iodrvupdateconfiguration  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvupdateconfiguration", (RTS_UINTPTR)cmpiodrvc__iodrvupdateconfiguration, 1, 0/*0x5600F48B*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvupdateconfiguration  PFCMPIODRVC__IODRVUPDATECONFIGURATION_IEC pfcmpiodrvc__iodrvupdateconfiguration;
	#define EXT_cmpiodrvc__iodrvupdateconfiguration  extern PFCMPIODRVC__IODRVUPDATECONFIGURATION_IEC pfcmpiodrvc__iodrvupdateconfiguration;
	#define GET_cmpiodrvc__iodrvupdateconfiguration(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvupdateconfiguration", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvupdateconfiguration, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x5600F48B*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvupdateconfiguration  pfcmpiodrvc__iodrvupdateconfiguration
	#define CHK_cmpiodrvc__iodrvupdateconfiguration  (pfcmpiodrvc__iodrvupdateconfiguration != NULL)
	#define EXP_cmpiodrvc__iodrvupdateconfiguration   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvupdateconfiguration", (RTS_UINTPTR)cmpiodrvc__iodrvupdateconfiguration, 1, 0/*0x5600F48B*/, 0x3050000) 
#endif


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

void CDECL CDECL_EXT cmpiodrvc__iodrvwriteparameter(cmpiodrvc_iodrvwriteparameter_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVWRITEPARAMETER_IEC) (cmpiodrvc_iodrvwriteparameter_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVWRITEPARAMETER_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvwriteparameter
	#define EXT_cmpiodrvc__iodrvwriteparameter
	#define GET_cmpiodrvc__iodrvwriteparameter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvwriteparameter(p0) 
	#define CHK_cmpiodrvc__iodrvwriteparameter  FALSE
	#define EXP_cmpiodrvc__iodrvwriteparameter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvwriteparameter
	#define EXT_cmpiodrvc__iodrvwriteparameter
	#define GET_cmpiodrvc__iodrvwriteparameter(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvwriteparameter" ) 
	#define CAL_cmpiodrvc__iodrvwriteparameter  cmpiodrvc__iodrvwriteparameter
	#define CHK_cmpiodrvc__iodrvwriteparameter  TRUE
	#define EXP_cmpiodrvc__iodrvwriteparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwriteparameter", (RTS_UINTPTR)cmpiodrvc__iodrvwriteparameter, 1, 0/*0xA14E52EF*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvwriteparameter
	#define EXT_cmpiodrvc__iodrvwriteparameter
	#define GET_cmpiodrvc__iodrvwriteparameter(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvwriteparameter" ) 
	#define CAL_cmpiodrvc__iodrvwriteparameter  cmpiodrvc__iodrvwriteparameter
	#define CHK_cmpiodrvc__iodrvwriteparameter  TRUE
	#define EXP_cmpiodrvc__iodrvwriteparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwriteparameter", (RTS_UINTPTR)cmpiodrvc__iodrvwriteparameter, 1, 0/*0xA14E52EF*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvwriteparameter
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvwriteparameter
	#define GET_CmpIoDrvCcmpiodrvc__iodrvwriteparameter  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvwriteparameter  cmpiodrvc__iodrvwriteparameter
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvwriteparameter  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvwriteparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwriteparameter", (RTS_UINTPTR)cmpiodrvc__iodrvwriteparameter, 1, 0/*0xA14E52EF*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvwriteparameter
	#define EXT_cmpiodrvc__iodrvwriteparameter
	#define GET_cmpiodrvc__iodrvwriteparameter(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvwriteparameter" ) 
	#define CAL_cmpiodrvc__iodrvwriteparameter  cmpiodrvc__iodrvwriteparameter
	#define CHK_cmpiodrvc__iodrvwriteparameter  TRUE
	#define EXP_cmpiodrvc__iodrvwriteparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwriteparameter", (RTS_UINTPTR)cmpiodrvc__iodrvwriteparameter, 1, 0/*0xA14E52EF*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvwriteparameter  PFCMPIODRVC__IODRVWRITEPARAMETER_IEC pfcmpiodrvc__iodrvwriteparameter;
	#define EXT_cmpiodrvc__iodrvwriteparameter  extern PFCMPIODRVC__IODRVWRITEPARAMETER_IEC pfcmpiodrvc__iodrvwriteparameter;
	#define GET_cmpiodrvc__iodrvwriteparameter(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvwriteparameter", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvwriteparameter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0xA14E52EF*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvwriteparameter  pfcmpiodrvc__iodrvwriteparameter
	#define CHK_cmpiodrvc__iodrvwriteparameter  (pfcmpiodrvc__iodrvwriteparameter != NULL)
	#define EXP_cmpiodrvc__iodrvwriteparameter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwriteparameter", (RTS_UINTPTR)cmpiodrvc__iodrvwriteparameter, 1, 0/*0xA14E52EF*/, 0x3050000) 
#endif


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

void CDECL CDECL_EXT cmpiodrvc__queryinterface(cmpiodrvc_queryinterface_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__QUERYINTERFACE_IEC) (cmpiodrvc_queryinterface_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__QUERYINTERFACE_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__queryinterface
	#define EXT_cmpiodrvc__queryinterface
	#define GET_cmpiodrvc__queryinterface(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__queryinterface(p0) 
	#define CHK_cmpiodrvc__queryinterface  FALSE
	#define EXP_cmpiodrvc__queryinterface  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__queryinterface
	#define EXT_cmpiodrvc__queryinterface
	#define GET_cmpiodrvc__queryinterface(fl)  CAL_CMGETAPI( "cmpiodrvc__queryinterface" ) 
	#define CAL_cmpiodrvc__queryinterface  cmpiodrvc__queryinterface
	#define CHK_cmpiodrvc__queryinterface  TRUE
	#define EXP_cmpiodrvc__queryinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__queryinterface", (RTS_UINTPTR)cmpiodrvc__queryinterface, 1, 0/*0x687F2F81*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__queryinterface
	#define EXT_cmpiodrvc__queryinterface
	#define GET_cmpiodrvc__queryinterface(fl)  CAL_CMGETAPI( "cmpiodrvc__queryinterface" ) 
	#define CAL_cmpiodrvc__queryinterface  cmpiodrvc__queryinterface
	#define CHK_cmpiodrvc__queryinterface  TRUE
	#define EXP_cmpiodrvc__queryinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__queryinterface", (RTS_UINTPTR)cmpiodrvc__queryinterface, 1, 0/*0x687F2F81*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__queryinterface
	#define EXT_CmpIoDrvCcmpiodrvc__queryinterface
	#define GET_CmpIoDrvCcmpiodrvc__queryinterface  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__queryinterface  cmpiodrvc__queryinterface
	#define CHK_CmpIoDrvCcmpiodrvc__queryinterface  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__queryinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__queryinterface", (RTS_UINTPTR)cmpiodrvc__queryinterface, 1, 0/*0x687F2F81*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__queryinterface
	#define EXT_cmpiodrvc__queryinterface
	#define GET_cmpiodrvc__queryinterface(fl)  CAL_CMGETAPI( "cmpiodrvc__queryinterface" ) 
	#define CAL_cmpiodrvc__queryinterface  cmpiodrvc__queryinterface
	#define CHK_cmpiodrvc__queryinterface  TRUE
	#define EXP_cmpiodrvc__queryinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__queryinterface", (RTS_UINTPTR)cmpiodrvc__queryinterface, 1, 0/*0x687F2F81*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__queryinterface  PFCMPIODRVC__QUERYINTERFACE_IEC pfcmpiodrvc__queryinterface;
	#define EXT_cmpiodrvc__queryinterface  extern PFCMPIODRVC__QUERYINTERFACE_IEC pfcmpiodrvc__queryinterface;
	#define GET_cmpiodrvc__queryinterface(fl)  s_pfCMGetAPI2( "cmpiodrvc__queryinterface", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__queryinterface, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x687F2F81*/, 0x3050000)
	#define CAL_cmpiodrvc__queryinterface  pfcmpiodrvc__queryinterface
	#define CHK_cmpiodrvc__queryinterface  (pfcmpiodrvc__queryinterface != NULL)
	#define EXP_cmpiodrvc__queryinterface   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__queryinterface", (RTS_UINTPTR)cmpiodrvc__queryinterface, 1, 0/*0x687F2F81*/, 0x3050000) 
#endif


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

void CDECL CDECL_EXT cmpiodrvc__iodrvscanmodules(cmpiodrvc_iodrvscanmodules_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVSCANMODULES_IEC) (cmpiodrvc_iodrvscanmodules_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVSCANMODULES_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvscanmodules
	#define EXT_cmpiodrvc__iodrvscanmodules
	#define GET_cmpiodrvc__iodrvscanmodules(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvscanmodules(p0) 
	#define CHK_cmpiodrvc__iodrvscanmodules  FALSE
	#define EXP_cmpiodrvc__iodrvscanmodules  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvscanmodules
	#define EXT_cmpiodrvc__iodrvscanmodules
	#define GET_cmpiodrvc__iodrvscanmodules(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvscanmodules" ) 
	#define CAL_cmpiodrvc__iodrvscanmodules  cmpiodrvc__iodrvscanmodules
	#define CHK_cmpiodrvc__iodrvscanmodules  TRUE
	#define EXP_cmpiodrvc__iodrvscanmodules  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvscanmodules", (RTS_UINTPTR)cmpiodrvc__iodrvscanmodules, 1, 0/*0xFE8E174B*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvscanmodules
	#define EXT_cmpiodrvc__iodrvscanmodules
	#define GET_cmpiodrvc__iodrvscanmodules(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvscanmodules" ) 
	#define CAL_cmpiodrvc__iodrvscanmodules  cmpiodrvc__iodrvscanmodules
	#define CHK_cmpiodrvc__iodrvscanmodules  TRUE
	#define EXP_cmpiodrvc__iodrvscanmodules  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvscanmodules", (RTS_UINTPTR)cmpiodrvc__iodrvscanmodules, 1, 0/*0xFE8E174B*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvscanmodules
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvscanmodules
	#define GET_CmpIoDrvCcmpiodrvc__iodrvscanmodules  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvscanmodules  cmpiodrvc__iodrvscanmodules
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvscanmodules  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvscanmodules  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvscanmodules", (RTS_UINTPTR)cmpiodrvc__iodrvscanmodules, 1, 0/*0xFE8E174B*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvscanmodules
	#define EXT_cmpiodrvc__iodrvscanmodules
	#define GET_cmpiodrvc__iodrvscanmodules(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvscanmodules" ) 
	#define CAL_cmpiodrvc__iodrvscanmodules  cmpiodrvc__iodrvscanmodules
	#define CHK_cmpiodrvc__iodrvscanmodules  TRUE
	#define EXP_cmpiodrvc__iodrvscanmodules  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvscanmodules", (RTS_UINTPTR)cmpiodrvc__iodrvscanmodules, 1, 0/*0xFE8E174B*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvscanmodules  PFCMPIODRVC__IODRVSCANMODULES_IEC pfcmpiodrvc__iodrvscanmodules;
	#define EXT_cmpiodrvc__iodrvscanmodules  extern PFCMPIODRVC__IODRVSCANMODULES_IEC pfcmpiodrvc__iodrvscanmodules;
	#define GET_cmpiodrvc__iodrvscanmodules(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvscanmodules", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvscanmodules, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0xFE8E174B*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvscanmodules  pfcmpiodrvc__iodrvscanmodules
	#define CHK_cmpiodrvc__iodrvscanmodules  (pfcmpiodrvc__iodrvscanmodules != NULL)
	#define EXP_cmpiodrvc__iodrvscanmodules   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvscanmodules", (RTS_UINTPTR)cmpiodrvc__iodrvscanmodules, 1, 0/*0xFE8E174B*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvdpv1_c2_m_write</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c2_m_write_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C2_Write *dpv1c2_Write;		/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C2_M_Write;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c2_m_write_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvdpv1_c2_m_write(cmpiodrvc_iodrvdpv1_c2_m_write_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVDPV1_C2_M_WRITE_IEC) (cmpiodrvc_iodrvdpv1_c2_m_write_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVDPV1_C2_M_WRITE_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_write
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_write
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_write(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_write(p0) 
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_write  FALSE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_write  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_write
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_write
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_write(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_write" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_write  cmpiodrvc__iodrvdpv1_c2_m_write
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_write  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_write", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_write, 1, 0/*0x34717EFF*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_write
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_write
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_write(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_write" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_write  cmpiodrvc__iodrvdpv1_c2_m_write
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_write  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_write", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_write, 1, 0/*0x34717EFF*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_write
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_write
	#define GET_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_write  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_write  cmpiodrvc__iodrvdpv1_c2_m_write
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_write  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_write", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_write, 1, 0/*0x34717EFF*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_write
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_write
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_write(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_write" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_write  cmpiodrvc__iodrvdpv1_c2_m_write
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_write  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_write", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_write, 1, 0/*0x34717EFF*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_write  PFCMPIODRVC__IODRVDPV1_C2_M_WRITE_IEC pfcmpiodrvc__iodrvdpv1_c2_m_write;
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_write  extern PFCMPIODRVC__IODRVDPV1_C2_M_WRITE_IEC pfcmpiodrvc__iodrvdpv1_c2_m_write;
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_write(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvdpv1_c2_m_write", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvdpv1_c2_m_write, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x34717EFF*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_write  pfcmpiodrvc__iodrvdpv1_c2_m_write
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_write  (pfcmpiodrvc__iodrvdpv1_c2_m_write != NULL)
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_write   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_write", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_write, 1, 0/*0x34717EFF*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvgetinfo</description>
 */
typedef struct tagcmpiodrvc_iodrvgetinfo_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoDrvInfo **ppInfo;					/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvGetInfo;			/* VAR_OUTPUT */
} cmpiodrvc_iodrvgetinfo_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvgetinfo(cmpiodrvc_iodrvgetinfo_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVGETINFO_IEC) (cmpiodrvc_iodrvgetinfo_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVGETINFO_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvgetinfo
	#define EXT_cmpiodrvc__iodrvgetinfo
	#define GET_cmpiodrvc__iodrvgetinfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvgetinfo(p0) 
	#define CHK_cmpiodrvc__iodrvgetinfo  FALSE
	#define EXP_cmpiodrvc__iodrvgetinfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvgetinfo
	#define EXT_cmpiodrvc__iodrvgetinfo
	#define GET_cmpiodrvc__iodrvgetinfo(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvgetinfo" ) 
	#define CAL_cmpiodrvc__iodrvgetinfo  cmpiodrvc__iodrvgetinfo
	#define CHK_cmpiodrvc__iodrvgetinfo  TRUE
	#define EXP_cmpiodrvc__iodrvgetinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvgetinfo", (RTS_UINTPTR)cmpiodrvc__iodrvgetinfo, 1, 0/*0xDB628C59*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvgetinfo
	#define EXT_cmpiodrvc__iodrvgetinfo
	#define GET_cmpiodrvc__iodrvgetinfo(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvgetinfo" ) 
	#define CAL_cmpiodrvc__iodrvgetinfo  cmpiodrvc__iodrvgetinfo
	#define CHK_cmpiodrvc__iodrvgetinfo  TRUE
	#define EXP_cmpiodrvc__iodrvgetinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvgetinfo", (RTS_UINTPTR)cmpiodrvc__iodrvgetinfo, 1, 0/*0xDB628C59*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvgetinfo
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvgetinfo
	#define GET_CmpIoDrvCcmpiodrvc__iodrvgetinfo  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvgetinfo  cmpiodrvc__iodrvgetinfo
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvgetinfo  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvgetinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvgetinfo", (RTS_UINTPTR)cmpiodrvc__iodrvgetinfo, 1, 0/*0xDB628C59*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvgetinfo
	#define EXT_cmpiodrvc__iodrvgetinfo
	#define GET_cmpiodrvc__iodrvgetinfo(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvgetinfo" ) 
	#define CAL_cmpiodrvc__iodrvgetinfo  cmpiodrvc__iodrvgetinfo
	#define CHK_cmpiodrvc__iodrvgetinfo  TRUE
	#define EXP_cmpiodrvc__iodrvgetinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvgetinfo", (RTS_UINTPTR)cmpiodrvc__iodrvgetinfo, 1, 0/*0xDB628C59*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvgetinfo  PFCMPIODRVC__IODRVGETINFO_IEC pfcmpiodrvc__iodrvgetinfo;
	#define EXT_cmpiodrvc__iodrvgetinfo  extern PFCMPIODRVC__IODRVGETINFO_IEC pfcmpiodrvc__iodrvgetinfo;
	#define GET_cmpiodrvc__iodrvgetinfo(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvgetinfo", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvgetinfo, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0xDB628C59*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvgetinfo  pfcmpiodrvc__iodrvgetinfo
	#define CHK_cmpiodrvc__iodrvgetinfo  (pfcmpiodrvc__iodrvgetinfo != NULL)
	#define EXP_cmpiodrvc__iodrvgetinfo   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvgetinfo", (RTS_UINTPTR)cmpiodrvc__iodrvgetinfo, 1, 0/*0xDB628C59*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvwatchdogtrigger</description>
 */
typedef struct tagcmpiodrvc_iodrvwatchdogtrigger_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	RTS_IEC_UDINT IoDrvWatchdogTrigger;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvwatchdogtrigger_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvwatchdogtrigger(cmpiodrvc_iodrvwatchdogtrigger_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVWATCHDOGTRIGGER_IEC) (cmpiodrvc_iodrvwatchdogtrigger_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVWATCHDOGTRIGGER_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvwatchdogtrigger
	#define EXT_cmpiodrvc__iodrvwatchdogtrigger
	#define GET_cmpiodrvc__iodrvwatchdogtrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvwatchdogtrigger(p0) 
	#define CHK_cmpiodrvc__iodrvwatchdogtrigger  FALSE
	#define EXP_cmpiodrvc__iodrvwatchdogtrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvwatchdogtrigger
	#define EXT_cmpiodrvc__iodrvwatchdogtrigger
	#define GET_cmpiodrvc__iodrvwatchdogtrigger(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvwatchdogtrigger" ) 
	#define CAL_cmpiodrvc__iodrvwatchdogtrigger  cmpiodrvc__iodrvwatchdogtrigger
	#define CHK_cmpiodrvc__iodrvwatchdogtrigger  TRUE
	#define EXP_cmpiodrvc__iodrvwatchdogtrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwatchdogtrigger", (RTS_UINTPTR)cmpiodrvc__iodrvwatchdogtrigger, 1, 0/*0xF1AB6D2E*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvwatchdogtrigger
	#define EXT_cmpiodrvc__iodrvwatchdogtrigger
	#define GET_cmpiodrvc__iodrvwatchdogtrigger(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvwatchdogtrigger" ) 
	#define CAL_cmpiodrvc__iodrvwatchdogtrigger  cmpiodrvc__iodrvwatchdogtrigger
	#define CHK_cmpiodrvc__iodrvwatchdogtrigger  TRUE
	#define EXP_cmpiodrvc__iodrvwatchdogtrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwatchdogtrigger", (RTS_UINTPTR)cmpiodrvc__iodrvwatchdogtrigger, 1, 0/*0xF1AB6D2E*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvwatchdogtrigger
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvwatchdogtrigger
	#define GET_CmpIoDrvCcmpiodrvc__iodrvwatchdogtrigger  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvwatchdogtrigger  cmpiodrvc__iodrvwatchdogtrigger
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvwatchdogtrigger  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvwatchdogtrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwatchdogtrigger", (RTS_UINTPTR)cmpiodrvc__iodrvwatchdogtrigger, 1, 0/*0xF1AB6D2E*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvwatchdogtrigger
	#define EXT_cmpiodrvc__iodrvwatchdogtrigger
	#define GET_cmpiodrvc__iodrvwatchdogtrigger(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvwatchdogtrigger" ) 
	#define CAL_cmpiodrvc__iodrvwatchdogtrigger  cmpiodrvc__iodrvwatchdogtrigger
	#define CHK_cmpiodrvc__iodrvwatchdogtrigger  TRUE
	#define EXP_cmpiodrvc__iodrvwatchdogtrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwatchdogtrigger", (RTS_UINTPTR)cmpiodrvc__iodrvwatchdogtrigger, 1, 0/*0xF1AB6D2E*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvwatchdogtrigger  PFCMPIODRVC__IODRVWATCHDOGTRIGGER_IEC pfcmpiodrvc__iodrvwatchdogtrigger;
	#define EXT_cmpiodrvc__iodrvwatchdogtrigger  extern PFCMPIODRVC__IODRVWATCHDOGTRIGGER_IEC pfcmpiodrvc__iodrvwatchdogtrigger;
	#define GET_cmpiodrvc__iodrvwatchdogtrigger(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvwatchdogtrigger", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvwatchdogtrigger, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0xF1AB6D2E*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvwatchdogtrigger  pfcmpiodrvc__iodrvwatchdogtrigger
	#define CHK_cmpiodrvc__iodrvwatchdogtrigger  (pfcmpiodrvc__iodrvwatchdogtrigger != NULL)
	#define EXP_cmpiodrvc__iodrvwatchdogtrigger   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvwatchdogtrigger", (RTS_UINTPTR)cmpiodrvc__iodrvwatchdogtrigger, 1, 0/*0xF1AB6D2E*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvdpv1_c2_m_initiate</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c2_m_initiate_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C2_Initiate *dpv1c2_Initiate;	/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C2_M_Initiate;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c2_m_initiate_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvdpv1_c2_m_initiate(cmpiodrvc_iodrvdpv1_c2_m_initiate_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVDPV1_C2_M_INITIATE_IEC) (cmpiodrvc_iodrvdpv1_c2_m_initiate_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVDPV1_C2_M_INITIATE_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_initiate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_initiate(p0) 
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_initiate  FALSE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_initiate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_initiate(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_initiate" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_initiate  cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_initiate  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_initiate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_initiate", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_initiate, 1, 0/*0x1F637083*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_initiate(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_initiate" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_initiate  cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_initiate  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_initiate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_initiate", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_initiate, 1, 0/*0x1F637083*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_initiate
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_initiate
	#define GET_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_initiate  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_initiate  cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_initiate  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_initiate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_initiate", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_initiate, 1, 0/*0x1F637083*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_initiate(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_initiate" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_initiate  cmpiodrvc__iodrvdpv1_c2_m_initiate
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_initiate  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_initiate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_initiate", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_initiate, 1, 0/*0x1F637083*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_initiate  PFCMPIODRVC__IODRVDPV1_C2_M_INITIATE_IEC pfcmpiodrvc__iodrvdpv1_c2_m_initiate;
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_initiate  extern PFCMPIODRVC__IODRVDPV1_C2_M_INITIATE_IEC pfcmpiodrvc__iodrvdpv1_c2_m_initiate;
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_initiate(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvdpv1_c2_m_initiate", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvdpv1_c2_m_initiate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x1F637083*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_initiate  pfcmpiodrvc__iodrvdpv1_c2_m_initiate
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_initiate  (pfcmpiodrvc__iodrvdpv1_c2_m_initiate != NULL)
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_initiate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_initiate", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_initiate, 1, 0/*0x1F637083*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvdpv1_c2_m_read</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c2_m_read_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C2_Read *dpv1c2_Read;			/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C2_M_Read;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c2_m_read_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvdpv1_c2_m_read(cmpiodrvc_iodrvdpv1_c2_m_read_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVDPV1_C2_M_READ_IEC) (cmpiodrvc_iodrvdpv1_c2_m_read_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVDPV1_C2_M_READ_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_read
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_read
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_read(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_read(p0) 
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_read  FALSE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_read  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_read
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_read
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_read(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_read" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_read  cmpiodrvc__iodrvdpv1_c2_m_read
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_read  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_read", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_read, 1, 0/*0x42D6E6C8*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_read
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_read
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_read(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_read" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_read  cmpiodrvc__iodrvdpv1_c2_m_read
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_read  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_read", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_read, 1, 0/*0x42D6E6C8*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_read
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_read
	#define GET_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_read  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_read  cmpiodrvc__iodrvdpv1_c2_m_read
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_read  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvdpv1_c2_m_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_read", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_read, 1, 0/*0x42D6E6C8*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_read
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_read
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_read(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c2_m_read" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_read  cmpiodrvc__iodrvdpv1_c2_m_read
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_read  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_read", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_read, 1, 0/*0x42D6E6C8*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvdpv1_c2_m_read  PFCMPIODRVC__IODRVDPV1_C2_M_READ_IEC pfcmpiodrvc__iodrvdpv1_c2_m_read;
	#define EXT_cmpiodrvc__iodrvdpv1_c2_m_read  extern PFCMPIODRVC__IODRVDPV1_C2_M_READ_IEC pfcmpiodrvc__iodrvdpv1_c2_m_read;
	#define GET_cmpiodrvc__iodrvdpv1_c2_m_read(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvdpv1_c2_m_read", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvdpv1_c2_m_read, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x42D6E6C8*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvdpv1_c2_m_read  pfcmpiodrvc__iodrvdpv1_c2_m_read
	#define CHK_cmpiodrvc__iodrvdpv1_c2_m_read  (pfcmpiodrvc__iodrvdpv1_c2_m_read != NULL)
	#define EXP_cmpiodrvc__iodrvdpv1_c2_m_read   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c2_m_read", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c2_m_read, 1, 0/*0x42D6E6C8*/, 0x3050000) 
#endif


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

void CDECL CDECL_EXT cmpiodrvc__iodrvupdatemapping(cmpiodrvc_iodrvupdatemapping_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVUPDATEMAPPING_IEC) (cmpiodrvc_iodrvupdatemapping_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVUPDATEMAPPING_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvupdatemapping
	#define EXT_cmpiodrvc__iodrvupdatemapping
	#define GET_cmpiodrvc__iodrvupdatemapping(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvupdatemapping(p0) 
	#define CHK_cmpiodrvc__iodrvupdatemapping  FALSE
	#define EXP_cmpiodrvc__iodrvupdatemapping  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvupdatemapping
	#define EXT_cmpiodrvc__iodrvupdatemapping
	#define GET_cmpiodrvc__iodrvupdatemapping(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvupdatemapping" ) 
	#define CAL_cmpiodrvc__iodrvupdatemapping  cmpiodrvc__iodrvupdatemapping
	#define CHK_cmpiodrvc__iodrvupdatemapping  TRUE
	#define EXP_cmpiodrvc__iodrvupdatemapping  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvupdatemapping", (RTS_UINTPTR)cmpiodrvc__iodrvupdatemapping, 1, 0/*0x9EE859E0*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvupdatemapping
	#define EXT_cmpiodrvc__iodrvupdatemapping
	#define GET_cmpiodrvc__iodrvupdatemapping(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvupdatemapping" ) 
	#define CAL_cmpiodrvc__iodrvupdatemapping  cmpiodrvc__iodrvupdatemapping
	#define CHK_cmpiodrvc__iodrvupdatemapping  TRUE
	#define EXP_cmpiodrvc__iodrvupdatemapping  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvupdatemapping", (RTS_UINTPTR)cmpiodrvc__iodrvupdatemapping, 1, 0/*0x9EE859E0*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvupdatemapping
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvupdatemapping
	#define GET_CmpIoDrvCcmpiodrvc__iodrvupdatemapping  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvupdatemapping  cmpiodrvc__iodrvupdatemapping
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvupdatemapping  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvupdatemapping  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvupdatemapping", (RTS_UINTPTR)cmpiodrvc__iodrvupdatemapping, 1, 0/*0x9EE859E0*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvupdatemapping
	#define EXT_cmpiodrvc__iodrvupdatemapping
	#define GET_cmpiodrvc__iodrvupdatemapping(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvupdatemapping" ) 
	#define CAL_cmpiodrvc__iodrvupdatemapping  cmpiodrvc__iodrvupdatemapping
	#define CHK_cmpiodrvc__iodrvupdatemapping  TRUE
	#define EXP_cmpiodrvc__iodrvupdatemapping  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvupdatemapping", (RTS_UINTPTR)cmpiodrvc__iodrvupdatemapping, 1, 0/*0x9EE859E0*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvupdatemapping  PFCMPIODRVC__IODRVUPDATEMAPPING_IEC pfcmpiodrvc__iodrvupdatemapping;
	#define EXT_cmpiodrvc__iodrvupdatemapping  extern PFCMPIODRVC__IODRVUPDATEMAPPING_IEC pfcmpiodrvc__iodrvupdatemapping;
	#define GET_cmpiodrvc__iodrvupdatemapping(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvupdatemapping", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvupdatemapping, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x9EE859E0*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvupdatemapping  pfcmpiodrvc__iodrvupdatemapping
	#define CHK_cmpiodrvc__iodrvupdatemapping  (pfcmpiodrvc__iodrvupdatemapping != NULL)
	#define EXP_cmpiodrvc__iodrvupdatemapping   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvupdatemapping", (RTS_UINTPTR)cmpiodrvc__iodrvupdatemapping, 1, 0/*0x9EE859E0*/, 0x3050000) 
#endif


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

void CDECL CDECL_EXT cmpiodrvc__iodrvreadinputs(cmpiodrvc_iodrvreadinputs_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVREADINPUTS_IEC) (cmpiodrvc_iodrvreadinputs_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVREADINPUTS_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvreadinputs
	#define EXT_cmpiodrvc__iodrvreadinputs
	#define GET_cmpiodrvc__iodrvreadinputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvreadinputs(p0) 
	#define CHK_cmpiodrvc__iodrvreadinputs  FALSE
	#define EXP_cmpiodrvc__iodrvreadinputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvreadinputs
	#define EXT_cmpiodrvc__iodrvreadinputs
	#define GET_cmpiodrvc__iodrvreadinputs(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvreadinputs" ) 
	#define CAL_cmpiodrvc__iodrvreadinputs  cmpiodrvc__iodrvreadinputs
	#define CHK_cmpiodrvc__iodrvreadinputs  TRUE
	#define EXP_cmpiodrvc__iodrvreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvreadinputs", (RTS_UINTPTR)cmpiodrvc__iodrvreadinputs, 1, 0/*0x86C4F56B*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvreadinputs
	#define EXT_cmpiodrvc__iodrvreadinputs
	#define GET_cmpiodrvc__iodrvreadinputs(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvreadinputs" ) 
	#define CAL_cmpiodrvc__iodrvreadinputs  cmpiodrvc__iodrvreadinputs
	#define CHK_cmpiodrvc__iodrvreadinputs  TRUE
	#define EXP_cmpiodrvc__iodrvreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvreadinputs", (RTS_UINTPTR)cmpiodrvc__iodrvreadinputs, 1, 0/*0x86C4F56B*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvreadinputs
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvreadinputs
	#define GET_CmpIoDrvCcmpiodrvc__iodrvreadinputs  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvreadinputs  cmpiodrvc__iodrvreadinputs
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvreadinputs  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvreadinputs", (RTS_UINTPTR)cmpiodrvc__iodrvreadinputs, 1, 0/*0x86C4F56B*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvreadinputs
	#define EXT_cmpiodrvc__iodrvreadinputs
	#define GET_cmpiodrvc__iodrvreadinputs(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvreadinputs" ) 
	#define CAL_cmpiodrvc__iodrvreadinputs  cmpiodrvc__iodrvreadinputs
	#define CHK_cmpiodrvc__iodrvreadinputs  TRUE
	#define EXP_cmpiodrvc__iodrvreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvreadinputs", (RTS_UINTPTR)cmpiodrvc__iodrvreadinputs, 1, 0/*0x86C4F56B*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvreadinputs  PFCMPIODRVC__IODRVREADINPUTS_IEC pfcmpiodrvc__iodrvreadinputs;
	#define EXT_cmpiodrvc__iodrvreadinputs  extern PFCMPIODRVC__IODRVREADINPUTS_IEC pfcmpiodrvc__iodrvreadinputs;
	#define GET_cmpiodrvc__iodrvreadinputs(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvreadinputs", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvreadinputs, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x86C4F56B*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvreadinputs  pfcmpiodrvc__iodrvreadinputs
	#define CHK_cmpiodrvc__iodrvreadinputs  (pfcmpiodrvc__iodrvreadinputs != NULL)
	#define EXP_cmpiodrvc__iodrvreadinputs   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvreadinputs", (RTS_UINTPTR)cmpiodrvc__iodrvreadinputs, 1, 0/*0x86C4F56B*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__addref</description>
 */
typedef struct tagcmpiodrvc_addref_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	RTS_IEC_DINT AddRef;				/* VAR_OUTPUT */
} cmpiodrvc_addref_struct;

void CDECL CDECL_EXT cmpiodrvc__addref(cmpiodrvc_addref_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__ADDREF_IEC) (cmpiodrvc_addref_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__ADDREF_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__addref
	#define EXT_cmpiodrvc__addref
	#define GET_cmpiodrvc__addref(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__addref(p0) 
	#define CHK_cmpiodrvc__addref  FALSE
	#define EXP_cmpiodrvc__addref  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__addref
	#define EXT_cmpiodrvc__addref
	#define GET_cmpiodrvc__addref(fl)  CAL_CMGETAPI( "cmpiodrvc__addref" ) 
	#define CAL_cmpiodrvc__addref  cmpiodrvc__addref
	#define CHK_cmpiodrvc__addref  TRUE
	#define EXP_cmpiodrvc__addref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__addref", (RTS_UINTPTR)cmpiodrvc__addref, 1, 0/*0x3D28D31E*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__addref
	#define EXT_cmpiodrvc__addref
	#define GET_cmpiodrvc__addref(fl)  CAL_CMGETAPI( "cmpiodrvc__addref" ) 
	#define CAL_cmpiodrvc__addref  cmpiodrvc__addref
	#define CHK_cmpiodrvc__addref  TRUE
	#define EXP_cmpiodrvc__addref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__addref", (RTS_UINTPTR)cmpiodrvc__addref, 1, 0/*0x3D28D31E*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__addref
	#define EXT_CmpIoDrvCcmpiodrvc__addref
	#define GET_CmpIoDrvCcmpiodrvc__addref  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__addref  cmpiodrvc__addref
	#define CHK_CmpIoDrvCcmpiodrvc__addref  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__addref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__addref", (RTS_UINTPTR)cmpiodrvc__addref, 1, 0/*0x3D28D31E*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__addref
	#define EXT_cmpiodrvc__addref
	#define GET_cmpiodrvc__addref(fl)  CAL_CMGETAPI( "cmpiodrvc__addref" ) 
	#define CAL_cmpiodrvc__addref  cmpiodrvc__addref
	#define CHK_cmpiodrvc__addref  TRUE
	#define EXP_cmpiodrvc__addref  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__addref", (RTS_UINTPTR)cmpiodrvc__addref, 1, 0/*0x3D28D31E*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__addref  PFCMPIODRVC__ADDREF_IEC pfcmpiodrvc__addref;
	#define EXT_cmpiodrvc__addref  extern PFCMPIODRVC__ADDREF_IEC pfcmpiodrvc__addref;
	#define GET_cmpiodrvc__addref(fl)  s_pfCMGetAPI2( "cmpiodrvc__addref", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__addref, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x3D28D31E*/, 0x3050000)
	#define CAL_cmpiodrvc__addref  pfcmpiodrvc__addref
	#define CHK_cmpiodrvc__addref  (pfcmpiodrvc__addref != NULL)
	#define EXP_cmpiodrvc__addref   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__addref", (RTS_UINTPTR)cmpiodrvc__addref, 1, 0/*0x3D28D31E*/, 0x3050000) 
#endif


/**
 * <description>cmpiodrvc__iodrvdpv1_c1_m_write</description>
 */
typedef struct tagcmpiodrvc_iodrvdpv1_c1_m_write_struct
{
	cmpiodrvc_struct *pInstance;		/* VAR_INPUT */
	DPV1_C1_Write *dpv1Write;			/* VAR_IN_OUT */
	RTS_IEC_UDINT IoDrvDPV1_C1_M_Write;	/* VAR_OUTPUT */
} cmpiodrvc_iodrvdpv1_c1_m_write_struct;

void CDECL CDECL_EXT cmpiodrvc__iodrvdpv1_c1_m_write(cmpiodrvc_iodrvdpv1_c1_m_write_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPIODRVC__IODRVDPV1_C1_M_WRITE_IEC) (cmpiodrvc_iodrvdpv1_c1_m_write_struct *p);
#if defined(CMPIODRVC_NOTIMPLEMENTED) || defined(CMPIODRVC__IODRVDPV1_C1_M_WRITE_NOTIMPLEMENTED)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_write
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_write
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_write(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_write(p0) 
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_write  FALSE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_write  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_write
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_write
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_write(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_write" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_write  cmpiodrvc__iodrvdpv1_c1_m_write
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_write  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_write", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_write, 1, 0/*0x3CD3DFFA*/, 0x3050000) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVC_EXTERNAL)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_write
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_write
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_write(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_write" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_write  cmpiodrvc__iodrvdpv1_c1_m_write
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_write  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_write", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_write, 1, 0/*0x3CD3DFFA*/, 0x3050000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_write
	#define EXT_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_write
	#define GET_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_write  ERR_OK
	#define CAL_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_write  cmpiodrvc__iodrvdpv1_c1_m_write
	#define CHK_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_write  TRUE
	#define EXP_CmpIoDrvCcmpiodrvc__iodrvdpv1_c1_m_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_write", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_write, 1, 0/*0x3CD3DFFA*/, 0x3050000) 
#elif defined(CPLUSPLUS)
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_write
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_write
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_write(fl)  CAL_CMGETAPI( "cmpiodrvc__iodrvdpv1_c1_m_write" ) 
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_write  cmpiodrvc__iodrvdpv1_c1_m_write
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_write  TRUE
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_write", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_write, 1, 0/*0x3CD3DFFA*/, 0x3050000) 
#else /* DYNAMIC_LINK */
	#define USE_cmpiodrvc__iodrvdpv1_c1_m_write  PFCMPIODRVC__IODRVDPV1_C1_M_WRITE_IEC pfcmpiodrvc__iodrvdpv1_c1_m_write;
	#define EXT_cmpiodrvc__iodrvdpv1_c1_m_write  extern PFCMPIODRVC__IODRVDPV1_C1_M_WRITE_IEC pfcmpiodrvc__iodrvdpv1_c1_m_write;
	#define GET_cmpiodrvc__iodrvdpv1_c1_m_write(fl)  s_pfCMGetAPI2( "cmpiodrvc__iodrvdpv1_c1_m_write", (RTS_VOID_FCTPTR *)&pfcmpiodrvc__iodrvdpv1_c1_m_write, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0/*0x3CD3DFFA*/, 0x3050000)
	#define CAL_cmpiodrvc__iodrvdpv1_c1_m_write  pfcmpiodrvc__iodrvdpv1_c1_m_write
	#define CHK_cmpiodrvc__iodrvdpv1_c1_m_write  (pfcmpiodrvc__iodrvdpv1_c1_m_write != NULL)
	#define EXP_cmpiodrvc__iodrvdpv1_c1_m_write   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpiodrvc__iodrvdpv1_c1_m_write", (RTS_UINTPTR)cmpiodrvc__iodrvdpv1_c1_m_write, 1, 0/*0x3CD3DFFA*/, 0x3050000) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



/* <SIL2/> */
typedef struct
{
	IBase_C *pBase;
} ICmpIoDrvC_C;

#ifdef CPLUSPLUS
class ICmpIoDrvC : public IBase
{
	public:
};
	#ifndef ITF_CmpIoDrvC
		#define ITF_CmpIoDrvC static ICmpIoDrvC *pICmpIoDrvC = NULL;
	#endif
	#define EXTITF_CmpIoDrvC
#else	/*CPLUSPLUS*/
	typedef ICmpIoDrvC_C		ICmpIoDrvC;
	#ifndef ITF_CmpIoDrvC
		#define ITF_CmpIoDrvC
	#endif
	#define EXTITF_CmpIoDrvC
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIODRVCITF_H_*/
