 /**
 * <interfacename>Redundancy Extension</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPREDUNDANCYEXTENSIONITF_H_
#define _CMPREDUNDANCYEXTENSIONITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>setredundancylinestatus</description>
 */
typedef struct tagsetredundancylinestatus_struct
{
	RTS_IEC_BOOL bIsConnected;			/* VAR_INPUT */
	RTS_IEC_BOOL SetRedundancyLineStatus;	/* VAR_OUTPUT */
} setredundancylinestatus_struct;

void CDECL CDECL_EXT setredundancylinestatus(setredundancylinestatus_struct *p);
typedef void (CDECL CDECL_EXT* PFSETREDUNDANCYLINESTATUS_IEC) (setredundancylinestatus_struct *p);
#if defined(CMPREDUNDANCYEXTENSION_NOTIMPLEMENTED) || defined(SETREDUNDANCYLINESTATUS_NOTIMPLEMENTED)
	#define USE_setredundancylinestatus
	#define EXT_setredundancylinestatus
	#define GET_setredundancylinestatus(fl)  ERR_NOTIMPLEMENTED
	#define CAL_setredundancylinestatus(p0) 
	#define CHK_setredundancylinestatus  FALSE
	#define EXP_setredundancylinestatus  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_setredundancylinestatus
	#define EXT_setredundancylinestatus
	#define GET_setredundancylinestatus(fl)  CAL_CMGETAPI( "setredundancylinestatus" ) 
	#define CAL_setredundancylinestatus  setredundancylinestatus
	#define CHK_setredundancylinestatus  TRUE
	#define EXP_setredundancylinestatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"setredundancylinestatus", (RTS_UINTPTR)setredundancylinestatus, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYEXTENSION_EXTERNAL)
	#define USE_setredundancylinestatus
	#define EXT_setredundancylinestatus
	#define GET_setredundancylinestatus(fl)  CAL_CMGETAPI( "setredundancylinestatus" ) 
	#define CAL_setredundancylinestatus  setredundancylinestatus
	#define CHK_setredundancylinestatus  TRUE
	#define EXP_setredundancylinestatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"setredundancylinestatus", (RTS_UINTPTR)setredundancylinestatus, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyExtensionsetredundancylinestatus
	#define EXT_CmpRedundancyExtensionsetredundancylinestatus
	#define GET_CmpRedundancyExtensionsetredundancylinestatus  ERR_OK
	#define CAL_CmpRedundancyExtensionsetredundancylinestatus  setredundancylinestatus
	#define CHK_CmpRedundancyExtensionsetredundancylinestatus  TRUE
	#define EXP_CmpRedundancyExtensionsetredundancylinestatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"setredundancylinestatus", (RTS_UINTPTR)setredundancylinestatus, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_setredundancylinestatus
	#define EXT_setredundancylinestatus
	#define GET_setredundancylinestatus(fl)  CAL_CMGETAPI( "setredundancylinestatus" ) 
	#define CAL_setredundancylinestatus  setredundancylinestatus
	#define CHK_setredundancylinestatus  TRUE
	#define EXP_setredundancylinestatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"setredundancylinestatus", (RTS_UINTPTR)setredundancylinestatus, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_setredundancylinestatus  PFSETREDUNDANCYLINESTATUS_IEC pfsetredundancylinestatus;
	#define EXT_setredundancylinestatus  extern PFSETREDUNDANCYLINESTATUS_IEC pfsetredundancylinestatus;
	#define GET_setredundancylinestatus(fl)  s_pfCMGetAPI2( "setredundancylinestatus", (RTS_VOID_FCTPTR *)&pfsetredundancylinestatus, (fl), 0, 0)
	#define CAL_setredundancylinestatus  pfsetredundancylinestatus
	#define CHK_setredundancylinestatus  (pfsetredundancylinestatus != NULL)
	#define EXP_setredundancylinestatus   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"setredundancylinestatus", (RTS_UINTPTR)setredundancylinestatus, 1, 0) 
#endif

RTS_BOOL CDECL RedundancySetLineStatus(RTS_BOOL);
typedef RTS_BOOL (CDECL * PFREDUNDANCYSETLINESTATUS) (RTS_BOOL);
#if defined(CMPREDUNDANCYEXTENSION_NOTIMPLEMENTED) || defined(REDUNDANCYSETLINESTATUS_NOTIMPLEMENTED)
	#define USE_RedundancySetLineStatus
	#define EXT_RedundancySetLineStatus
	#define GET_RedundancySetLineStatus(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancySetLineStatus(p0)  (RTS_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancySetLineStatus  FALSE
	#define EXP_RedundancySetLineStatus  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancySetLineStatus
	#define EXT_RedundancySetLineStatus
	#define GET_RedundancySetLineStatus(fl)  CAL_CMGETAPI( "RedundancySetLineStatus" ) 
	#define CAL_RedundancySetLineStatus  RedundancySetLineStatus
	#define CHK_RedundancySetLineStatus  TRUE
	#define EXP_RedundancySetLineStatus  CAL_CMEXPAPI( "RedundancySetLineStatus" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYEXTENSION_EXTERNAL)
	#define USE_RedundancySetLineStatus
	#define EXT_RedundancySetLineStatus
	#define GET_RedundancySetLineStatus(fl)  CAL_CMGETAPI( "RedundancySetLineStatus" ) 
	#define CAL_RedundancySetLineStatus  RedundancySetLineStatus
	#define CHK_RedundancySetLineStatus  TRUE
	#define EXP_RedundancySetLineStatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySetLineStatus", (RTS_UINTPTR)RedundancySetLineStatus, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyExtensionRedundancySetLineStatus
	#define EXT_CmpRedundancyExtensionRedundancySetLineStatus
	#define GET_CmpRedundancyExtensionRedundancySetLineStatus  ERR_OK
	#define CAL_CmpRedundancyExtensionRedundancySetLineStatus pICmpRedundancyExtension->IRedundancySetLineStatus
	#define CHK_CmpRedundancyExtensionRedundancySetLineStatus (pICmpRedundancyExtension != NULL)
	#define EXP_CmpRedundancyExtensionRedundancySetLineStatus  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancySetLineStatus
	#define EXT_RedundancySetLineStatus
	#define GET_RedundancySetLineStatus(fl)  CAL_CMGETAPI( "RedundancySetLineStatus" ) 
	#define CAL_RedundancySetLineStatus pICmpRedundancyExtension->IRedundancySetLineStatus
	#define CHK_RedundancySetLineStatus (pICmpRedundancyExtension != NULL)
	#define EXP_RedundancySetLineStatus  CAL_CMEXPAPI( "RedundancySetLineStatus" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancySetLineStatus  PFREDUNDANCYSETLINESTATUS pfRedundancySetLineStatus;
	#define EXT_RedundancySetLineStatus  extern PFREDUNDANCYSETLINESTATUS pfRedundancySetLineStatus;
	#define GET_RedundancySetLineStatus(fl)  s_pfCMGetAPI2( "RedundancySetLineStatus", (RTS_VOID_FCTPTR *)&pfRedundancySetLineStatus, (fl), 0, 0)
	#define CAL_RedundancySetLineStatus  pfRedundancySetLineStatus
	#define CHK_RedundancySetLineStatus  (pfRedundancySetLineStatus != NULL)
	#define EXP_RedundancySetLineStatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySetLineStatus", (RTS_UINTPTR)RedundancySetLineStatus, 0, 0) 
#endif




RTS_BOOL CDECL RedundancyGetLineStatus(void);
typedef RTS_BOOL (CDECL * PFREDUNDANCYGETLINESTATUS) (void);
#if defined(CMPREDUNDANCYEXTENSION_NOTIMPLEMENTED) || defined(REDUNDANCYGETLINESTATUS_NOTIMPLEMENTED)
	#define USE_RedundancyGetLineStatus
	#define EXT_RedundancyGetLineStatus
	#define GET_RedundancyGetLineStatus(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancyGetLineStatus()  (RTS_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancyGetLineStatus  FALSE
	#define EXP_RedundancyGetLineStatus  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancyGetLineStatus
	#define EXT_RedundancyGetLineStatus
	#define GET_RedundancyGetLineStatus(fl)  CAL_CMGETAPI( "RedundancyGetLineStatus" ) 
	#define CAL_RedundancyGetLineStatus  RedundancyGetLineStatus
	#define CHK_RedundancyGetLineStatus  TRUE
	#define EXP_RedundancyGetLineStatus  CAL_CMEXPAPI( "RedundancyGetLineStatus" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCYEXTENSION_EXTERNAL)
	#define USE_RedundancyGetLineStatus
	#define EXT_RedundancyGetLineStatus
	#define GET_RedundancyGetLineStatus(fl)  CAL_CMGETAPI( "RedundancyGetLineStatus" ) 
	#define CAL_RedundancyGetLineStatus  RedundancyGetLineStatus
	#define CHK_RedundancyGetLineStatus  TRUE
	#define EXP_RedundancyGetLineStatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyGetLineStatus", (RTS_UINTPTR)RedundancyGetLineStatus, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyExtensionRedundancyGetLineStatus
	#define EXT_CmpRedundancyExtensionRedundancyGetLineStatus
	#define GET_CmpRedundancyExtensionRedundancyGetLineStatus  ERR_OK
	#define CAL_CmpRedundancyExtensionRedundancyGetLineStatus pICmpRedundancyExtension->IRedundancyGetLineStatus
	#define CHK_CmpRedundancyExtensionRedundancyGetLineStatus (pICmpRedundancyExtension != NULL)
	#define EXP_CmpRedundancyExtensionRedundancyGetLineStatus  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancyGetLineStatus
	#define EXT_RedundancyGetLineStatus
	#define GET_RedundancyGetLineStatus(fl)  CAL_CMGETAPI( "RedundancyGetLineStatus" ) 
	#define CAL_RedundancyGetLineStatus pICmpRedundancyExtension->IRedundancyGetLineStatus
	#define CHK_RedundancyGetLineStatus (pICmpRedundancyExtension != NULL)
	#define EXP_RedundancyGetLineStatus  CAL_CMEXPAPI( "RedundancyGetLineStatus" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancyGetLineStatus  PFREDUNDANCYGETLINESTATUS pfRedundancyGetLineStatus;
	#define EXT_RedundancyGetLineStatus  extern PFREDUNDANCYGETLINESTATUS pfRedundancyGetLineStatus;
	#define GET_RedundancyGetLineStatus(fl)  s_pfCMGetAPI2( "RedundancyGetLineStatus", (RTS_VOID_FCTPTR *)&pfRedundancyGetLineStatus, (fl), 0, 0)
	#define CAL_RedundancyGetLineStatus  pfRedundancyGetLineStatus
	#define CHK_RedundancyGetLineStatus  (pfRedundancyGetLineStatus != NULL)
	#define EXP_RedundancyGetLineStatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyGetLineStatus", (RTS_UINTPTR)RedundancyGetLineStatus, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
	PFREDUNDANCYSETLINESTATUS IRedundancySetLineStatus;
 	PFREDUNDANCYGETLINESTATUS IRedundancyGetLineStatus;
 } ICmpRedundancyExtension_C;

#ifdef CPLUSPLUS
class ICmpRedundancyExtension : public IBase
{
	public:
		virtual RTS_BOOL CDECL IRedundancySetLineStatus(RTS_BOOL) =0;
		virtual RTS_BOOL CDECL IRedundancyGetLineStatus(void) =0;
};
	#ifndef ITF_CmpRedundancyExtension
		#define ITF_CmpRedundancyExtension static ICmpRedundancyExtension *pICmpRedundancyExtension = NULL;
	#endif
	#define EXTITF_CmpRedundancyExtension
#else	/*CPLUSPLUS*/
	typedef ICmpRedundancyExtension_C		ICmpRedundancyExtension;
	#ifndef ITF_CmpRedundancyExtension
		#define ITF_CmpRedundancyExtension
	#endif
	#define EXTITF_CmpRedundancyExtension
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPREDUNDANCYEXTENSIONITF_H_*/
