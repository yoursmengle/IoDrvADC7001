 /**
 * <interfacename>CmpMgrBasicChecks</interfacename>
 * <description>
 *	<p>Interface to check the runtime environment. Here things like datatype size and
 *	byte order are checked, before the runtime system was started.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPMGRBASICCHECKSITF_H_
#define _CMPMGRBASICCHECKSITF_H_

#include "CmpStd.h"

 

 




#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> 
 *	Checks to environment and the compiled runtime system for consistency.
 *	- Checks the real size of all data types
 *	- Checks, if swapping must be done and if swapping is done correctly
 * </description>
 * <result>TRUE if successful, FALSE if error occurred</result>
 */
int CDECL CMBasicChecks(void);
typedef int (CDECL * PFCMBASICCHECKS) (void);
#if defined(CMPMGRBASICCHECKS_NOTIMPLEMENTED) || defined(CMBASICCHECKS_NOTIMPLEMENTED)
	#define USE_CMBasicChecks
	#define EXT_CMBasicChecks
	#define GET_CMBasicChecks(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CMBasicChecks()  (int)ERR_NOTIMPLEMENTED
	#define CHK_CMBasicChecks  FALSE
	#define EXP_CMBasicChecks  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CMBasicChecks
	#define EXT_CMBasicChecks
	#define GET_CMBasicChecks(fl)  CAL_CMGETAPI( "CMBasicChecks" ) 
	#define CAL_CMBasicChecks  CMBasicChecks
	#define CHK_CMBasicChecks  TRUE
	#define EXP_CMBasicChecks  CAL_CMEXPAPI( "CMBasicChecks" ) 
#elif defined(MIXED_LINK) && !defined(CMPMGRBASICCHECKS_EXTERNAL)
	#define USE_CMBasicChecks
	#define EXT_CMBasicChecks
	#define GET_CMBasicChecks(fl)  CAL_CMGETAPI( "CMBasicChecks" ) 
	#define CAL_CMBasicChecks  CMBasicChecks
	#define CHK_CMBasicChecks  TRUE
	#define EXP_CMBasicChecks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CMBasicChecks", (RTS_UINTPTR)CMBasicChecks, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMgrBasicChecksCMBasicChecks
	#define EXT_CmpMgrBasicChecksCMBasicChecks
	#define GET_CmpMgrBasicChecksCMBasicChecks  ERR_OK
	#define CAL_CmpMgrBasicChecksCMBasicChecks CCmpMgrBasicChecks::ICMBasicChecks
	#define CHK_CmpMgrBasicChecksCMBasicChecks  TRUE
	#define EXP_CmpMgrBasicChecksCMBasicChecks  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CMBasicChecks
	#define EXT_CMBasicChecks
	#define GET_CMBasicChecks(fl)  CAL_CMGETAPI( "CMBasicChecks" ) 
	#define CAL_CMBasicChecks CCmpMgrBasicChecks::ICMBasicChecks
	#define CHK_CMBasicChecks  TRUE
	#define EXP_CMBasicChecks  CAL_CMEXPAPI( "CMBasicChecks" ) 
#else /* DYNAMIC_LINK */
	#define USE_CMBasicChecks  PFCMBASICCHECKS pfCMBasicChecks;
	#define EXT_CMBasicChecks  extern PFCMBASICCHECKS pfCMBasicChecks;
	#define GET_CMBasicChecks(fl)  s_pfCMGetAPI2( "CMBasicChecks", (RTS_VOID_FCTPTR *)&pfCMBasicChecks, (fl), 0, 0)
	#define CAL_CMBasicChecks  pfCMBasicChecks
	#define CHK_CMBasicChecks  (pfCMBasicChecks != NULL)
	#define EXP_CMBasicChecks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CMBasicChecks", (RTS_UINTPTR)CMBasicChecks, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFCMBASICCHECKS ICMBasicChecks;
 } ICmpMgrBasicChecks_C;

#ifdef CPLUSPLUS
class ICmpMgrBasicChecks : public IBase
{
	public:
		static int CDECL ICMBasicChecks(void);
};
	#ifndef ITF_CmpMgrBasicChecks
		#define ITF_CmpMgrBasicChecks static ICmpMgrBasicChecks *pICmpMgrBasicChecks = NULL;
	#endif
	#define EXTITF_CmpMgrBasicChecks
#else	/*CPLUSPLUS*/
	typedef ICmpMgrBasicChecks_C		ICmpMgrBasicChecks;
	#ifndef ITF_CmpMgrBasicChecks
		#define ITF_CmpMgrBasicChecks
	#endif
	#define EXTITF_CmpMgrBasicChecks
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPMGRBASICCHECKSITF_H_*/
