 /**
 * <interfacename>CmpOPCUAProviderAlarmConfiguration</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPOPCUAPROVIDERALARMCONFIGURATIONITF_H_
#define _CMPOPCUAPROVIDERALARMCONFIGURATIONITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function is used to send and event to the OPC UA Server.
 */
typedef struct tagcmpopcuaprovideralarmconfigurationfireevent_struct
{
	RTS_IEC_HANDLE hApplication;		/* VAR_INPUT */	/* Handle to the registered application returned by CmpOPCUAProviderAlarmConfigurationRegister */
	RTS_IEC_UDINT ui32EventId;			/* VAR_INPUT */	/* EventID of the alarm manager. */
	RTS_IEC_LINT eventTimestamp;		/* VAR_INPUT */	/* The timestamp of the event. The alarm Manager used 100ns interval since 1.1.1601. Same format as OPC UA. */
	RTS_IEC_UDINT ui32Priority;			/* VAR_INPUT */	/* Priority of the event. Has to be converted to OPC UA notation 1 (lowest) - 1000 (highest) priority */
	RTS_IEC_WSTRING *message;			/* VAR_INPUT */	/* WSTRING message of the event. Will be converted to UTF-8 by the OPC UA server. */
	RTS_IEC_RESULT CmpOPCUAProviderAlarmConfigurationFireEvent;	/* VAR_OUTPUT */	
} cmpopcuaprovideralarmconfigurationfireevent_struct;

void CDECL CDECL_EXT cmpopcuaprovideralarmconfigurationfireevent(cmpopcuaprovideralarmconfigurationfireevent_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPOPCUAPROVIDERALARMCONFIGURATIONFIREEVENT_IEC) (cmpopcuaprovideralarmconfigurationfireevent_struct *p);
#if defined(CMPOPCUAPROVIDERALARMCONFIGURATION_NOTIMPLEMENTED) || defined(CMPOPCUAPROVIDERALARMCONFIGURATIONFIREEVENT_NOTIMPLEMENTED)
	#define USE_cmpopcuaprovideralarmconfigurationfireevent
	#define EXT_cmpopcuaprovideralarmconfigurationfireevent
	#define GET_cmpopcuaprovideralarmconfigurationfireevent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpopcuaprovideralarmconfigurationfireevent(p0) 
	#define CHK_cmpopcuaprovideralarmconfigurationfireevent  FALSE
	#define EXP_cmpopcuaprovideralarmconfigurationfireevent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpopcuaprovideralarmconfigurationfireevent
	#define EXT_cmpopcuaprovideralarmconfigurationfireevent
	#define GET_cmpopcuaprovideralarmconfigurationfireevent(fl)  CAL_CMGETAPI( "cmpopcuaprovideralarmconfigurationfireevent" ) 
	#define CAL_cmpopcuaprovideralarmconfigurationfireevent  cmpopcuaprovideralarmconfigurationfireevent
	#define CHK_cmpopcuaprovideralarmconfigurationfireevent  TRUE
	#define EXP_cmpopcuaprovideralarmconfigurationfireevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationfireevent", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationfireevent, 1, 0xEC235428, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUAPROVIDERALARMCONFIGURATION_EXTERNAL)
	#define USE_cmpopcuaprovideralarmconfigurationfireevent
	#define EXT_cmpopcuaprovideralarmconfigurationfireevent
	#define GET_cmpopcuaprovideralarmconfigurationfireevent(fl)  CAL_CMGETAPI( "cmpopcuaprovideralarmconfigurationfireevent" ) 
	#define CAL_cmpopcuaprovideralarmconfigurationfireevent  cmpopcuaprovideralarmconfigurationfireevent
	#define CHK_cmpopcuaprovideralarmconfigurationfireevent  TRUE
	#define EXP_cmpopcuaprovideralarmconfigurationfireevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationfireevent", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationfireevent, 1, 0xEC235428, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationfireevent
	#define EXT_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationfireevent
	#define GET_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationfireevent  ERR_OK
	#define CAL_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationfireevent  cmpopcuaprovideralarmconfigurationfireevent
	#define CHK_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationfireevent  TRUE
	#define EXP_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationfireevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationfireevent", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationfireevent, 1, 0xEC235428, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_cmpopcuaprovideralarmconfigurationfireevent
	#define EXT_cmpopcuaprovideralarmconfigurationfireevent
	#define GET_cmpopcuaprovideralarmconfigurationfireevent(fl)  CAL_CMGETAPI( "cmpopcuaprovideralarmconfigurationfireevent" ) 
	#define CAL_cmpopcuaprovideralarmconfigurationfireevent  cmpopcuaprovideralarmconfigurationfireevent
	#define CHK_cmpopcuaprovideralarmconfigurationfireevent  TRUE
	#define EXP_cmpopcuaprovideralarmconfigurationfireevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationfireevent", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationfireevent, 1, 0xEC235428, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_cmpopcuaprovideralarmconfigurationfireevent  PFCMPOPCUAPROVIDERALARMCONFIGURATIONFIREEVENT_IEC pfcmpopcuaprovideralarmconfigurationfireevent;
	#define EXT_cmpopcuaprovideralarmconfigurationfireevent  extern PFCMPOPCUAPROVIDERALARMCONFIGURATIONFIREEVENT_IEC pfcmpopcuaprovideralarmconfigurationfireevent;
	#define GET_cmpopcuaprovideralarmconfigurationfireevent(fl)  s_pfCMGetAPI2( "cmpopcuaprovideralarmconfigurationfireevent", (RTS_VOID_FCTPTR *)&pfcmpopcuaprovideralarmconfigurationfireevent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xEC235428, 0x03050C00)
	#define CAL_cmpopcuaprovideralarmconfigurationfireevent  pfcmpopcuaprovideralarmconfigurationfireevent
	#define CHK_cmpopcuaprovideralarmconfigurationfireevent  (pfcmpopcuaprovideralarmconfigurationfireevent != NULL)
	#define EXP_cmpopcuaprovideralarmconfigurationfireevent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationfireevent", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationfireevent, 1, 0xEC235428, 0x03050C00) 
#endif


/**
 * This function is used to register the applicaiton at the OPC UA server as event source.
 */
typedef struct tagcmpopcuaprovideralarmconfigurationregister_struct
{
	APPLICATION *pApplication;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE CmpOPCUAProviderAlarmConfigurationRegister;	/* VAR_OUTPUT */	
} cmpopcuaprovideralarmconfigurationregister_struct;

void CDECL CDECL_EXT cmpopcuaprovideralarmconfigurationregister(cmpopcuaprovideralarmconfigurationregister_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPOPCUAPROVIDERALARMCONFIGURATIONREGISTER_IEC) (cmpopcuaprovideralarmconfigurationregister_struct *p);
#if defined(CMPOPCUAPROVIDERALARMCONFIGURATION_NOTIMPLEMENTED) || defined(CMPOPCUAPROVIDERALARMCONFIGURATIONREGISTER_NOTIMPLEMENTED)
	#define USE_cmpopcuaprovideralarmconfigurationregister
	#define EXT_cmpopcuaprovideralarmconfigurationregister
	#define GET_cmpopcuaprovideralarmconfigurationregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpopcuaprovideralarmconfigurationregister(p0) 
	#define CHK_cmpopcuaprovideralarmconfigurationregister  FALSE
	#define EXP_cmpopcuaprovideralarmconfigurationregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpopcuaprovideralarmconfigurationregister
	#define EXT_cmpopcuaprovideralarmconfigurationregister
	#define GET_cmpopcuaprovideralarmconfigurationregister(fl)  CAL_CMGETAPI( "cmpopcuaprovideralarmconfigurationregister" ) 
	#define CAL_cmpopcuaprovideralarmconfigurationregister  cmpopcuaprovideralarmconfigurationregister
	#define CHK_cmpopcuaprovideralarmconfigurationregister  TRUE
	#define EXP_cmpopcuaprovideralarmconfigurationregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationregister", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationregister, 1, 0xF4F696A7, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUAPROVIDERALARMCONFIGURATION_EXTERNAL)
	#define USE_cmpopcuaprovideralarmconfigurationregister
	#define EXT_cmpopcuaprovideralarmconfigurationregister
	#define GET_cmpopcuaprovideralarmconfigurationregister(fl)  CAL_CMGETAPI( "cmpopcuaprovideralarmconfigurationregister" ) 
	#define CAL_cmpopcuaprovideralarmconfigurationregister  cmpopcuaprovideralarmconfigurationregister
	#define CHK_cmpopcuaprovideralarmconfigurationregister  TRUE
	#define EXP_cmpopcuaprovideralarmconfigurationregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationregister", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationregister, 1, 0xF4F696A7, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationregister
	#define EXT_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationregister
	#define GET_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationregister  ERR_OK
	#define CAL_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationregister  cmpopcuaprovideralarmconfigurationregister
	#define CHK_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationregister  TRUE
	#define EXP_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationregister", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationregister, 1, 0xF4F696A7, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_cmpopcuaprovideralarmconfigurationregister
	#define EXT_cmpopcuaprovideralarmconfigurationregister
	#define GET_cmpopcuaprovideralarmconfigurationregister(fl)  CAL_CMGETAPI( "cmpopcuaprovideralarmconfigurationregister" ) 
	#define CAL_cmpopcuaprovideralarmconfigurationregister  cmpopcuaprovideralarmconfigurationregister
	#define CHK_cmpopcuaprovideralarmconfigurationregister  TRUE
	#define EXP_cmpopcuaprovideralarmconfigurationregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationregister", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationregister, 1, 0xF4F696A7, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_cmpopcuaprovideralarmconfigurationregister  PFCMPOPCUAPROVIDERALARMCONFIGURATIONREGISTER_IEC pfcmpopcuaprovideralarmconfigurationregister;
	#define EXT_cmpopcuaprovideralarmconfigurationregister  extern PFCMPOPCUAPROVIDERALARMCONFIGURATIONREGISTER_IEC pfcmpopcuaprovideralarmconfigurationregister;
	#define GET_cmpopcuaprovideralarmconfigurationregister(fl)  s_pfCMGetAPI2( "cmpopcuaprovideralarmconfigurationregister", (RTS_VOID_FCTPTR *)&pfcmpopcuaprovideralarmconfigurationregister, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xF4F696A7, 0x03050C00)
	#define CAL_cmpopcuaprovideralarmconfigurationregister  pfcmpopcuaprovideralarmconfigurationregister
	#define CHK_cmpopcuaprovideralarmconfigurationregister  (pfcmpopcuaprovideralarmconfigurationregister != NULL)
	#define EXP_cmpopcuaprovideralarmconfigurationregister   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationregister", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationregister, 1, 0xF4F696A7, 0x03050C00) 
#endif


/**
 * This function is used to unregsiter the applicaiton as an event source.
 */
typedef struct tagcmpopcuaprovideralarmconfigurationunregister_struct
{
	RTS_IEC_HANDLE hAlarmHandler;		/* VAR_INPUT */	
	RTS_IEC_RESULT CmpOPCUAProviderAlarmConfigurationUnregister;	/* VAR_OUTPUT */	
} cmpopcuaprovideralarmconfigurationunregister_struct;

void CDECL CDECL_EXT cmpopcuaprovideralarmconfigurationunregister(cmpopcuaprovideralarmconfigurationunregister_struct *p);
typedef void (CDECL CDECL_EXT* PFCMPOPCUAPROVIDERALARMCONFIGURATIONUNREGISTER_IEC) (cmpopcuaprovideralarmconfigurationunregister_struct *p);
#if defined(CMPOPCUAPROVIDERALARMCONFIGURATION_NOTIMPLEMENTED) || defined(CMPOPCUAPROVIDERALARMCONFIGURATIONUNREGISTER_NOTIMPLEMENTED)
	#define USE_cmpopcuaprovideralarmconfigurationunregister
	#define EXT_cmpopcuaprovideralarmconfigurationunregister
	#define GET_cmpopcuaprovideralarmconfigurationunregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cmpopcuaprovideralarmconfigurationunregister(p0) 
	#define CHK_cmpopcuaprovideralarmconfigurationunregister  FALSE
	#define EXP_cmpopcuaprovideralarmconfigurationunregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cmpopcuaprovideralarmconfigurationunregister
	#define EXT_cmpopcuaprovideralarmconfigurationunregister
	#define GET_cmpopcuaprovideralarmconfigurationunregister(fl)  CAL_CMGETAPI( "cmpopcuaprovideralarmconfigurationunregister" ) 
	#define CAL_cmpopcuaprovideralarmconfigurationunregister  cmpopcuaprovideralarmconfigurationunregister
	#define CHK_cmpopcuaprovideralarmconfigurationunregister  TRUE
	#define EXP_cmpopcuaprovideralarmconfigurationunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationunregister", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationunregister, 1, 0x06481C5A, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUAPROVIDERALARMCONFIGURATION_EXTERNAL)
	#define USE_cmpopcuaprovideralarmconfigurationunregister
	#define EXT_cmpopcuaprovideralarmconfigurationunregister
	#define GET_cmpopcuaprovideralarmconfigurationunregister(fl)  CAL_CMGETAPI( "cmpopcuaprovideralarmconfigurationunregister" ) 
	#define CAL_cmpopcuaprovideralarmconfigurationunregister  cmpopcuaprovideralarmconfigurationunregister
	#define CHK_cmpopcuaprovideralarmconfigurationunregister  TRUE
	#define EXP_cmpopcuaprovideralarmconfigurationunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationunregister", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationunregister, 1, 0x06481C5A, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationunregister
	#define EXT_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationunregister
	#define GET_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationunregister  ERR_OK
	#define CAL_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationunregister  cmpopcuaprovideralarmconfigurationunregister
	#define CHK_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationunregister  TRUE
	#define EXP_CmpOPCUAProviderAlarmConfigurationcmpopcuaprovideralarmconfigurationunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationunregister", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationunregister, 1, 0x06481C5A, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_cmpopcuaprovideralarmconfigurationunregister
	#define EXT_cmpopcuaprovideralarmconfigurationunregister
	#define GET_cmpopcuaprovideralarmconfigurationunregister(fl)  CAL_CMGETAPI( "cmpopcuaprovideralarmconfigurationunregister" ) 
	#define CAL_cmpopcuaprovideralarmconfigurationunregister  cmpopcuaprovideralarmconfigurationunregister
	#define CHK_cmpopcuaprovideralarmconfigurationunregister  TRUE
	#define EXP_cmpopcuaprovideralarmconfigurationunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationunregister", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationunregister, 1, 0x06481C5A, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_cmpopcuaprovideralarmconfigurationunregister  PFCMPOPCUAPROVIDERALARMCONFIGURATIONUNREGISTER_IEC pfcmpopcuaprovideralarmconfigurationunregister;
	#define EXT_cmpopcuaprovideralarmconfigurationunregister  extern PFCMPOPCUAPROVIDERALARMCONFIGURATIONUNREGISTER_IEC pfcmpopcuaprovideralarmconfigurationunregister;
	#define GET_cmpopcuaprovideralarmconfigurationunregister(fl)  s_pfCMGetAPI2( "cmpopcuaprovideralarmconfigurationunregister", (RTS_VOID_FCTPTR *)&pfcmpopcuaprovideralarmconfigurationunregister, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x06481C5A, 0x03050C00)
	#define CAL_cmpopcuaprovideralarmconfigurationunregister  pfcmpopcuaprovideralarmconfigurationunregister
	#define CHK_cmpopcuaprovideralarmconfigurationunregister  (pfcmpopcuaprovideralarmconfigurationunregister != NULL)
	#define EXP_cmpopcuaprovideralarmconfigurationunregister   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cmpopcuaprovideralarmconfigurationunregister", (RTS_UINTPTR)cmpopcuaprovideralarmconfigurationunregister, 1, 0x06481C5A, 0x03050C00) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpOPCUAProviderAlarmConfiguration_C;

#ifdef CPLUSPLUS
class ICmpOPCUAProviderAlarmConfiguration : public IBase
{
	public:
};
	#ifndef ITF_CmpOPCUAProviderAlarmConfiguration
		#define ITF_CmpOPCUAProviderAlarmConfiguration static ICmpOPCUAProviderAlarmConfiguration *pICmpOPCUAProviderAlarmConfiguration = NULL;
	#endif
	#define EXTITF_CmpOPCUAProviderAlarmConfiguration
#else	/*CPLUSPLUS*/
	typedef ICmpOPCUAProviderAlarmConfiguration_C		ICmpOPCUAProviderAlarmConfiguration;
	#ifndef ITF_CmpOPCUAProviderAlarmConfiguration
		#define ITF_CmpOPCUAProviderAlarmConfiguration
	#endif
	#define EXTITF_CmpOPCUAProviderAlarmConfiguration
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPOPCUAPROVIDERALARMCONFIGURATIONITF_H_*/
