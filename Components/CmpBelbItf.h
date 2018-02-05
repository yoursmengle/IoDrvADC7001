 
	
	
#ifndef _CMPBELBITF_H_
#define _CMPBELBITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/* Hook definitions (0..10000 reserved for core components) */

#define CH_USER_1						10000
/*	First user hook
	ulParam1: Not used
	ulParam2: Not used
*/

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>startwatchdog</description>
 */
typedef struct tagstartwatchdog_struct
{
	RTS_IEC_DWORD StartWatchdog;		/* VAR_OUTPUT */
} startwatchdog_struct;

void CDECL CDECL_EXT startwatchdog(startwatchdog_struct *p);
typedef void (CDECL CDECL_EXT* PFSTARTWATCHDOG_IEC) (startwatchdog_struct *p);
#if defined(CMPBELB_NOTIMPLEMENTED) || defined(STARTWATCHDOG_NOTIMPLEMENTED)
	#define USE_startwatchdog
	#define EXT_startwatchdog
	#define GET_startwatchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_startwatchdog(p0) 
	#define CHK_startwatchdog  FALSE
	#define EXP_startwatchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_startwatchdog
	#define EXT_startwatchdog
	#define GET_startwatchdog(fl)  CAL_CMGETAPI( "startwatchdog" ) 
	#define CAL_startwatchdog  startwatchdog
	#define CHK_startwatchdog  TRUE
	#define EXP_startwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"startwatchdog", (RTS_UINTPTR)startwatchdog, 1, 0x50E033B9, 0x0000) 
#elif defined(MIXED_LINK) && !defined(CMPBELB_EXTERNAL)
	#define USE_startwatchdog
	#define EXT_startwatchdog
	#define GET_startwatchdog(fl)  CAL_CMGETAPI( "startwatchdog" ) 
	#define CAL_startwatchdog  startwatchdog
	#define CHK_startwatchdog  TRUE
	#define EXP_startwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"startwatchdog", (RTS_UINTPTR)startwatchdog, 1, 0x50E033B9, 0x0000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBelbstartwatchdog
	#define EXT_CmpBelbstartwatchdog
	#define GET_CmpBelbstartwatchdog  ERR_OK
	#define CAL_CmpBelbstartwatchdog  startwatchdog
	#define CHK_CmpBelbstartwatchdog  TRUE
	#define EXP_CmpBelbstartwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"startwatchdog", (RTS_UINTPTR)startwatchdog, 1, 0x50E033B9, 0x0000) 
#elif defined(CPLUSPLUS)
	#define USE_startwatchdog
	#define EXT_startwatchdog
	#define GET_startwatchdog(fl)  CAL_CMGETAPI( "startwatchdog" ) 
	#define CAL_startwatchdog  startwatchdog
	#define CHK_startwatchdog  TRUE
	#define EXP_startwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"startwatchdog", (RTS_UINTPTR)startwatchdog, 1, 0x50E033B9, 0x0000) 
#else /* DYNAMIC_LINK */
	#define USE_startwatchdog  PFSTARTWATCHDOG_IEC pfstartwatchdog;
	#define EXT_startwatchdog  extern PFSTARTWATCHDOG_IEC pfstartwatchdog;
	#define GET_startwatchdog(fl)  s_pfCMGetAPI2( "startwatchdog", (RTS_VOID_FCTPTR *)&pfstartwatchdog, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x50E033B9, 0x0000)
	#define CAL_startwatchdog  pfstartwatchdog
	#define CHK_startwatchdog  (pfstartwatchdog != NULL)
	#define EXP_startwatchdog   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"startwatchdog", (RTS_UINTPTR)startwatchdog, 1, 0x50E033B9, 0x0000) 
#endif


/**
 * <description>stopwatchdog</description>
 */
typedef struct tagstopwatchdog_struct
{
	RTS_IEC_DWORD StopWatchdog;			/* VAR_OUTPUT */
} stopwatchdog_struct;

void CDECL CDECL_EXT stopwatchdog(stopwatchdog_struct *p);
typedef void (CDECL CDECL_EXT* PFSTOPWATCHDOG_IEC) (stopwatchdog_struct *p);
#if defined(CMPBELB_NOTIMPLEMENTED) || defined(STOPWATCHDOG_NOTIMPLEMENTED)
	#define USE_stopwatchdog
	#define EXT_stopwatchdog
	#define GET_stopwatchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_stopwatchdog(p0) 
	#define CHK_stopwatchdog  FALSE
	#define EXP_stopwatchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_stopwatchdog
	#define EXT_stopwatchdog
	#define GET_stopwatchdog(fl)  CAL_CMGETAPI( "stopwatchdog" ) 
	#define CAL_stopwatchdog  stopwatchdog
	#define CHK_stopwatchdog  TRUE
	#define EXP_stopwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stopwatchdog", (RTS_UINTPTR)stopwatchdog, 1, 0x2B1E3F4A, 0x0000) 
#elif defined(MIXED_LINK) && !defined(CMPBELB_EXTERNAL)
	#define USE_stopwatchdog
	#define EXT_stopwatchdog
	#define GET_stopwatchdog(fl)  CAL_CMGETAPI( "stopwatchdog" ) 
	#define CAL_stopwatchdog  stopwatchdog
	#define CHK_stopwatchdog  TRUE
	#define EXP_stopwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stopwatchdog", (RTS_UINTPTR)stopwatchdog, 1, 0x2B1E3F4A, 0x0000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBelbstopwatchdog
	#define EXT_CmpBelbstopwatchdog
	#define GET_CmpBelbstopwatchdog  ERR_OK
	#define CAL_CmpBelbstopwatchdog  stopwatchdog
	#define CHK_CmpBelbstopwatchdog  TRUE
	#define EXP_CmpBelbstopwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stopwatchdog", (RTS_UINTPTR)stopwatchdog, 1, 0x2B1E3F4A, 0x0000) 
#elif defined(CPLUSPLUS)
	#define USE_stopwatchdog
	#define EXT_stopwatchdog
	#define GET_stopwatchdog(fl)  CAL_CMGETAPI( "stopwatchdog" ) 
	#define CAL_stopwatchdog  stopwatchdog
	#define CHK_stopwatchdog  TRUE
	#define EXP_stopwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stopwatchdog", (RTS_UINTPTR)stopwatchdog, 1, 0x2B1E3F4A, 0x0000) 
#else /* DYNAMIC_LINK */
	#define USE_stopwatchdog  PFSTOPWATCHDOG_IEC pfstopwatchdog;
	#define EXT_stopwatchdog  extern PFSTOPWATCHDOG_IEC pfstopwatchdog;
	#define GET_stopwatchdog(fl)  s_pfCMGetAPI2( "stopwatchdog", (RTS_VOID_FCTPTR *)&pfstopwatchdog, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x2B1E3F4A, 0x0000)
	#define CAL_stopwatchdog  pfstopwatchdog
	#define CHK_stopwatchdog  (pfstopwatchdog != NULL)
	#define EXP_stopwatchdog   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stopwatchdog", (RTS_UINTPTR)stopwatchdog, 1, 0x2B1E3F4A, 0x0000) 
#endif


/**
 * <description>kickwatchdog</description>
 */
typedef struct tagkickwatchdog_struct
{
	RTS_IEC_DWORD KickWatchdog;			/* VAR_OUTPUT */
} kickwatchdog_struct;

void CDECL CDECL_EXT kickwatchdog(kickwatchdog_struct *p);
typedef void (CDECL CDECL_EXT* PFKICKWATCHDOG_IEC) (kickwatchdog_struct *p);
#if defined(CMPBELB_NOTIMPLEMENTED) || defined(KICKWATCHDOG_NOTIMPLEMENTED)
	#define USE_kickwatchdog
	#define EXT_kickwatchdog
	#define GET_kickwatchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_kickwatchdog(p0) 
	#define CHK_kickwatchdog  FALSE
	#define EXP_kickwatchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_kickwatchdog
	#define EXT_kickwatchdog
	#define GET_kickwatchdog(fl)  CAL_CMGETAPI( "kickwatchdog" ) 
	#define CAL_kickwatchdog  kickwatchdog
	#define CHK_kickwatchdog  TRUE
	#define EXP_kickwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"kickwatchdog", (RTS_UINTPTR)kickwatchdog, 1, 0x12D360F2, 0x0000) 
#elif defined(MIXED_LINK) && !defined(CMPBELB_EXTERNAL)
	#define USE_kickwatchdog
	#define EXT_kickwatchdog
	#define GET_kickwatchdog(fl)  CAL_CMGETAPI( "kickwatchdog" ) 
	#define CAL_kickwatchdog  kickwatchdog
	#define CHK_kickwatchdog  TRUE
	#define EXP_kickwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"kickwatchdog", (RTS_UINTPTR)kickwatchdog, 1, 0x12D360F2, 0x0000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBelbkickwatchdog
	#define EXT_CmpBelbkickwatchdog
	#define GET_CmpBelbkickwatchdog  ERR_OK
	#define CAL_CmpBelbkickwatchdog  kickwatchdog
	#define CHK_CmpBelbkickwatchdog  TRUE
	#define EXP_CmpBelbkickwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"kickwatchdog", (RTS_UINTPTR)kickwatchdog, 1, 0x12D360F2, 0x0000) 
#elif defined(CPLUSPLUS)
	#define USE_kickwatchdog
	#define EXT_kickwatchdog
	#define GET_kickwatchdog(fl)  CAL_CMGETAPI( "kickwatchdog" ) 
	#define CAL_kickwatchdog  kickwatchdog
	#define CHK_kickwatchdog  TRUE
	#define EXP_kickwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"kickwatchdog", (RTS_UINTPTR)kickwatchdog, 1, 0x12D360F2, 0x0000) 
#else /* DYNAMIC_LINK */
	#define USE_kickwatchdog  PFKICKWATCHDOG_IEC pfkickwatchdog;
	#define EXT_kickwatchdog  extern PFKICKWATCHDOG_IEC pfkickwatchdog;
	#define GET_kickwatchdog(fl)  s_pfCMGetAPI2( "kickwatchdog", (RTS_VOID_FCTPTR *)&pfkickwatchdog, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x12D360F2, 0x0000)
	#define CAL_kickwatchdog  pfkickwatchdog
	#define CHK_kickwatchdog  (pfkickwatchdog != NULL)
	#define EXP_kickwatchdog   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"kickwatchdog", (RTS_UINTPTR)kickwatchdog, 1, 0x12D360F2, 0x0000) 
#endif


/*From here functions called by other components should be defined.*/
/**
 * <description> 
 * Comments...
 * </description>
 * <result>ERR_OK</result>
 */
unsigned long CDECL CmpBelbGetInterruptMask(unsigned long ulPar);
typedef unsigned long (CDECL * PFCMPBELBGETINTERRUPTMASK) (unsigned long ulPar);
#if defined(CMPBELB_NOTIMPLEMENTED) || defined(CMPBELBGETINTERRUPTMASK_NOTIMPLEMENTED)
	#define USE_CmpBelbGetInterruptMask
	#define EXT_CmpBelbGetInterruptMask
	#define GET_CmpBelbGetInterruptMask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpBelbGetInterruptMask(p0)  (unsigned long)ERR_NOTIMPLEMENTED
	#define CHK_CmpBelbGetInterruptMask  FALSE
	#define EXP_CmpBelbGetInterruptMask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpBelbGetInterruptMask
	#define EXT_CmpBelbGetInterruptMask
	#define GET_CmpBelbGetInterruptMask(fl)  CAL_CMGETAPI( "CmpBelbGetInterruptMask" ) 
	#define CAL_CmpBelbGetInterruptMask  CmpBelbGetInterruptMask
	#define CHK_CmpBelbGetInterruptMask  TRUE
	#define EXP_CmpBelbGetInterruptMask  CAL_CMEXPAPI( "CmpBelbGetInterruptMask" ) 
#elif defined(MIXED_LINK) && !defined(CMPBELB_EXTERNAL)
	#define USE_CmpBelbGetInterruptMask
	#define EXT_CmpBelbGetInterruptMask
	#define GET_CmpBelbGetInterruptMask(fl)  CAL_CMGETAPI( "CmpBelbGetInterruptMask" ) 
	#define CAL_CmpBelbGetInterruptMask  CmpBelbGetInterruptMask
	#define CHK_CmpBelbGetInterruptMask  TRUE
	#define EXP_CmpBelbGetInterruptMask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpBelbGetInterruptMask", (RTS_UINTPTR)CmpBelbGetInterruptMask, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBelbCmpBelbGetInterruptMask
	#define EXT_CmpBelbCmpBelbGetInterruptMask
	#define GET_CmpBelbCmpBelbGetInterruptMask  ERR_OK
	#define CAL_CmpBelbCmpBelbGetInterruptMask pICmpBelb->ICmpBelbGetInterruptMask
	#define CHK_CmpBelbCmpBelbGetInterruptMask (pICmpBelb != NULL)
	#define EXP_CmpBelbCmpBelbGetInterruptMask  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpBelbGetInterruptMask
	#define EXT_CmpBelbGetInterruptMask
	#define GET_CmpBelbGetInterruptMask(fl)  CAL_CMGETAPI( "CmpBelbGetInterruptMask" ) 
	#define CAL_CmpBelbGetInterruptMask pICmpBelb->ICmpBelbGetInterruptMask
	#define CHK_CmpBelbGetInterruptMask (pICmpBelb != NULL)
	#define EXP_CmpBelbGetInterruptMask  CAL_CMEXPAPI( "CmpBelbGetInterruptMask" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpBelbGetInterruptMask  PFCMPBELBGETINTERRUPTMASK pfCmpBelbGetInterruptMask;
	#define EXT_CmpBelbGetInterruptMask  extern PFCMPBELBGETINTERRUPTMASK pfCmpBelbGetInterruptMask;
	#define GET_CmpBelbGetInterruptMask(fl)  s_pfCMGetAPI2( "CmpBelbGetInterruptMask", (RTS_VOID_FCTPTR *)&pfCmpBelbGetInterruptMask, (fl), 0, 0)
	#define CAL_CmpBelbGetInterruptMask  pfCmpBelbGetInterruptMask
	#define CHK_CmpBelbGetInterruptMask  (pfCmpBelbGetInterruptMask != NULL)
	#define EXP_CmpBelbGetInterruptMask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpBelbGetInterruptMask", (RTS_UINTPTR)CmpBelbGetInterruptMask, 0, 0) 
#endif




/**
 * <description> 
 * Comments...
 * </description>
 * <result>ERR_OK</result>
 */
unsigned long CDECL CmpBelbSetInterruptMask(unsigned long ulPar);
typedef unsigned long (CDECL * PFCMPBELBSETINTERRUPTMASK) (unsigned long ulPar);
#if defined(CMPBELB_NOTIMPLEMENTED) || defined(CMPBELBSETINTERRUPTMASK_NOTIMPLEMENTED)
	#define USE_CmpBelbSetInterruptMask
	#define EXT_CmpBelbSetInterruptMask
	#define GET_CmpBelbSetInterruptMask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpBelbSetInterruptMask(p0)  (unsigned long)ERR_NOTIMPLEMENTED
	#define CHK_CmpBelbSetInterruptMask  FALSE
	#define EXP_CmpBelbSetInterruptMask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpBelbSetInterruptMask
	#define EXT_CmpBelbSetInterruptMask
	#define GET_CmpBelbSetInterruptMask(fl)  CAL_CMGETAPI( "CmpBelbSetInterruptMask" ) 
	#define CAL_CmpBelbSetInterruptMask  CmpBelbSetInterruptMask
	#define CHK_CmpBelbSetInterruptMask  TRUE
	#define EXP_CmpBelbSetInterruptMask  CAL_CMEXPAPI( "CmpBelbSetInterruptMask" ) 
#elif defined(MIXED_LINK) && !defined(CMPBELB_EXTERNAL)
	#define USE_CmpBelbSetInterruptMask
	#define EXT_CmpBelbSetInterruptMask
	#define GET_CmpBelbSetInterruptMask(fl)  CAL_CMGETAPI( "CmpBelbSetInterruptMask" ) 
	#define CAL_CmpBelbSetInterruptMask  CmpBelbSetInterruptMask
	#define CHK_CmpBelbSetInterruptMask  TRUE
	#define EXP_CmpBelbSetInterruptMask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpBelbSetInterruptMask", (RTS_UINTPTR)CmpBelbSetInterruptMask, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBelbCmpBelbSetInterruptMask
	#define EXT_CmpBelbCmpBelbSetInterruptMask
	#define GET_CmpBelbCmpBelbSetInterruptMask  ERR_OK
	#define CAL_CmpBelbCmpBelbSetInterruptMask pICmpBelb->ICmpBelbSetInterruptMask
	#define CHK_CmpBelbCmpBelbSetInterruptMask (pICmpBelb != NULL)
	#define EXP_CmpBelbCmpBelbSetInterruptMask  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpBelbSetInterruptMask
	#define EXT_CmpBelbSetInterruptMask
	#define GET_CmpBelbSetInterruptMask(fl)  CAL_CMGETAPI( "CmpBelbSetInterruptMask" ) 
	#define CAL_CmpBelbSetInterruptMask pICmpBelb->ICmpBelbSetInterruptMask
	#define CHK_CmpBelbSetInterruptMask (pICmpBelb != NULL)
	#define EXP_CmpBelbSetInterruptMask  CAL_CMEXPAPI( "CmpBelbSetInterruptMask" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpBelbSetInterruptMask  PFCMPBELBSETINTERRUPTMASK pfCmpBelbSetInterruptMask;
	#define EXT_CmpBelbSetInterruptMask  extern PFCMPBELBSETINTERRUPTMASK pfCmpBelbSetInterruptMask;
	#define GET_CmpBelbSetInterruptMask(fl)  s_pfCMGetAPI2( "CmpBelbSetInterruptMask", (RTS_VOID_FCTPTR *)&pfCmpBelbSetInterruptMask, (fl), 0, 0)
	#define CAL_CmpBelbSetInterruptMask  pfCmpBelbSetInterruptMask
	#define CHK_CmpBelbSetInterruptMask  (pfCmpBelbSetInterruptMask != NULL)
	#define EXP_CmpBelbSetInterruptMask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpBelbSetInterruptMask", (RTS_UINTPTR)CmpBelbSetInterruptMask, 0, 0) 
#endif





#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
	PFCMPBELBGETINTERRUPTMASK ICmpBelbGetInterruptMask;
 	PFCMPBELBSETINTERRUPTMASK ICmpBelbSetInterruptMask;
 } ICmpBelb_C;

#ifdef CPLUSPLUS
class ICmpBelb : public IBase
{
	public:
		virtual unsigned long CDECL ICmpBelbGetInterruptMask(unsigned long ulPar) =0;
		virtual unsigned long CDECL ICmpBelbSetInterruptMask(unsigned long ulPar) =0;
};
	#ifndef ITF_CmpBelb
		#define ITF_CmpBelb static ICmpBelb *pICmpBelb = NULL;
	#endif
	#define EXTITF_CmpBelb
#else	/*CPLUSPLUS*/
	typedef ICmpBelb_C		ICmpBelb;
	#ifndef ITF_CmpBelb
		#define ITF_CmpBelb
	#endif
	#define EXTITF_CmpBelb
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPBELBITF_H_*/
