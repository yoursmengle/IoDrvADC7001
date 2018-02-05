 /**
 * <interfacename>SysCpuBreakpoints</interfacename>
 * <description> 
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSCPUBREAKPOINTSITF_H_
#define _SYSCPUBREAKPOINTSITF_H_

#include "CmpStd.h"

 

 




/* Since CpuBreakpoints are only available on Windows this interface has to be deactivated by default. */
#if !defined(SYSCPUBREAKPOINTS_IMPLEMENTED) && !defined(SYSCPUBREAKPOINTS_EXTERNAL)
	#define SYSCPUBREAKPOINTS_NOTIMPLEMENTED
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysCpuBreakpointsOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysCpuBreakpointsOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 * <p>Function to set a hardware breakpoint (data breakpoint).</p>
 * </description>
 * <param name="hApp" type="IN" range="[RTS_INVALID_HANDLE]">Handle to the application (see CmpAppItf.h)</param>
 * <param name="ulBPType" type="IN" range="[RTS_RANGE_OF_RTS_UI32]">The type of the breakpoint to set (BP_DATA)</param>
 * <param name="pAddress" type="IN">The address in the global data are to be observed</param>
 * <param name="ulSize" type="IN">The size of data to be observed</param>
 * <result>Returns ERR_OK or ERR_FAILED</result>
 */
RTS_RESULT CDECL SysCpuBreakpointSet(RTS_HANDLE hApp, RTS_UI32 ulBPType, void *pAddress, RTS_UI32 ulSize);
typedef RTS_RESULT (CDECL * PFSYSCPUBREAKPOINTSET) (RTS_HANDLE hApp, RTS_UI32 ulBPType, void *pAddress, RTS_UI32 ulSize);
#if defined(SYSCPUBREAKPOINTS_NOTIMPLEMENTED) || defined(SYSCPUBREAKPOINTSET_NOTIMPLEMENTED)
	#define USE_SysCpuBreakpointSet
	#define EXT_SysCpuBreakpointSet
	#define GET_SysCpuBreakpointSet(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysCpuBreakpointSet(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysCpuBreakpointSet  FALSE
	#define EXP_SysCpuBreakpointSet  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysCpuBreakpointSet
	#define EXT_SysCpuBreakpointSet
	#define GET_SysCpuBreakpointSet(fl)  CAL_CMGETAPI( "SysCpuBreakpointSet" ) 
	#define CAL_SysCpuBreakpointSet  SysCpuBreakpointSet
	#define CHK_SysCpuBreakpointSet  TRUE
	#define EXP_SysCpuBreakpointSet  CAL_CMEXPAPI( "SysCpuBreakpointSet" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUBREAKPOINTS_EXTERNAL)
	#define USE_SysCpuBreakpointSet
	#define EXT_SysCpuBreakpointSet
	#define GET_SysCpuBreakpointSet(fl)  CAL_CMGETAPI( "SysCpuBreakpointSet" ) 
	#define CAL_SysCpuBreakpointSet  SysCpuBreakpointSet
	#define CHK_SysCpuBreakpointSet  TRUE
	#define EXP_SysCpuBreakpointSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysCpuBreakpointSet", (RTS_UINTPTR)SysCpuBreakpointSet, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuBreakpointsSysCpuBreakpointSet
	#define EXT_SysCpuBreakpointsSysCpuBreakpointSet
	#define GET_SysCpuBreakpointsSysCpuBreakpointSet  ERR_OK
	#define CAL_SysCpuBreakpointsSysCpuBreakpointSet pISysCpuBreakpoints->ISysCpuBreakpointSet
	#define CHK_SysCpuBreakpointsSysCpuBreakpointSet (pISysCpuBreakpoints != NULL)
	#define EXP_SysCpuBreakpointsSysCpuBreakpointSet  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysCpuBreakpointSet
	#define EXT_SysCpuBreakpointSet
	#define GET_SysCpuBreakpointSet(fl)  CAL_CMGETAPI( "SysCpuBreakpointSet" ) 
	#define CAL_SysCpuBreakpointSet pISysCpuBreakpoints->ISysCpuBreakpointSet
	#define CHK_SysCpuBreakpointSet (pISysCpuBreakpoints != NULL)
	#define EXP_SysCpuBreakpointSet  CAL_CMEXPAPI( "SysCpuBreakpointSet" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysCpuBreakpointSet  PFSYSCPUBREAKPOINTSET pfSysCpuBreakpointSet;
	#define EXT_SysCpuBreakpointSet  extern PFSYSCPUBREAKPOINTSET pfSysCpuBreakpointSet;
	#define GET_SysCpuBreakpointSet(fl)  s_pfCMGetAPI2( "SysCpuBreakpointSet", (RTS_VOID_FCTPTR *)&pfSysCpuBreakpointSet, (fl), 0, 0)
	#define CAL_SysCpuBreakpointSet  pfSysCpuBreakpointSet
	#define CHK_SysCpuBreakpointSet  (pfSysCpuBreakpointSet != NULL)
	#define EXP_SysCpuBreakpointSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysCpuBreakpointSet", (RTS_UINTPTR)SysCpuBreakpointSet, 0, 0) 
#endif




 /**
 * <description>
 * <p>Function to delete a hardware breakpoint (data breakpoint).</p>
 * </description>
 * <param name="hApp" type="IN" range="[RTS_INVALID_HANDLE]">Handle to the application (see CmpAppItf.h)</param>
 * <param name="ulBPType" type="IN" range="[RTS_RANGE_OF_RTS_I32]">The type of the breakpoint to set (BP_DATA)</param>
 * <param name="pAddress" type="IN">The address in the global data area of the breakpoint to be deleted</param>
 * <param name="ulSize" type="IN">The size of data of the breakpoint to be deleted</param>
 * <result>Returns ERR_OK or ERR_FAILED</result>
 */
RTS_RESULT CDECL SysCpuBreakpointDelete(RTS_HANDLE hApp, RTS_UI32 ulBPType, void *pAddress, RTS_UI32 ulSize);
typedef RTS_RESULT (CDECL * PFSYSCPUBREAKPOINTDELETE) (RTS_HANDLE hApp, RTS_UI32 ulBPType, void *pAddress, RTS_UI32 ulSize);
#if defined(SYSCPUBREAKPOINTS_NOTIMPLEMENTED) || defined(SYSCPUBREAKPOINTDELETE_NOTIMPLEMENTED)
	#define USE_SysCpuBreakpointDelete
	#define EXT_SysCpuBreakpointDelete
	#define GET_SysCpuBreakpointDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysCpuBreakpointDelete(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysCpuBreakpointDelete  FALSE
	#define EXP_SysCpuBreakpointDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysCpuBreakpointDelete
	#define EXT_SysCpuBreakpointDelete
	#define GET_SysCpuBreakpointDelete(fl)  CAL_CMGETAPI( "SysCpuBreakpointDelete" ) 
	#define CAL_SysCpuBreakpointDelete  SysCpuBreakpointDelete
	#define CHK_SysCpuBreakpointDelete  TRUE
	#define EXP_SysCpuBreakpointDelete  CAL_CMEXPAPI( "SysCpuBreakpointDelete" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUBREAKPOINTS_EXTERNAL)
	#define USE_SysCpuBreakpointDelete
	#define EXT_SysCpuBreakpointDelete
	#define GET_SysCpuBreakpointDelete(fl)  CAL_CMGETAPI( "SysCpuBreakpointDelete" ) 
	#define CAL_SysCpuBreakpointDelete  SysCpuBreakpointDelete
	#define CHK_SysCpuBreakpointDelete  TRUE
	#define EXP_SysCpuBreakpointDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysCpuBreakpointDelete", (RTS_UINTPTR)SysCpuBreakpointDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuBreakpointsSysCpuBreakpointDelete
	#define EXT_SysCpuBreakpointsSysCpuBreakpointDelete
	#define GET_SysCpuBreakpointsSysCpuBreakpointDelete  ERR_OK
	#define CAL_SysCpuBreakpointsSysCpuBreakpointDelete pISysCpuBreakpoints->ISysCpuBreakpointDelete
	#define CHK_SysCpuBreakpointsSysCpuBreakpointDelete (pISysCpuBreakpoints != NULL)
	#define EXP_SysCpuBreakpointsSysCpuBreakpointDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysCpuBreakpointDelete
	#define EXT_SysCpuBreakpointDelete
	#define GET_SysCpuBreakpointDelete(fl)  CAL_CMGETAPI( "SysCpuBreakpointDelete" ) 
	#define CAL_SysCpuBreakpointDelete pISysCpuBreakpoints->ISysCpuBreakpointDelete
	#define CHK_SysCpuBreakpointDelete (pISysCpuBreakpoints != NULL)
	#define EXP_SysCpuBreakpointDelete  CAL_CMEXPAPI( "SysCpuBreakpointDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysCpuBreakpointDelete  PFSYSCPUBREAKPOINTDELETE pfSysCpuBreakpointDelete;
	#define EXT_SysCpuBreakpointDelete  extern PFSYSCPUBREAKPOINTDELETE pfSysCpuBreakpointDelete;
	#define GET_SysCpuBreakpointDelete(fl)  s_pfCMGetAPI2( "SysCpuBreakpointDelete", (RTS_VOID_FCTPTR *)&pfSysCpuBreakpointDelete, (fl), 0, 0)
	#define CAL_SysCpuBreakpointDelete  pfSysCpuBreakpointDelete
	#define CHK_SysCpuBreakpointDelete  (pfSysCpuBreakpointDelete != NULL)
	#define EXP_SysCpuBreakpointDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysCpuBreakpointDelete", (RTS_UINTPTR)SysCpuBreakpointDelete, 0, 0) 
#endif




 /**
 * <description>
 * <p>Function to retrieve a breakpoint address by the context as produced in the breakpoint exception. This function is system specific and may only be called by other system components.</p>
 * </description>
 * <param name="pContext" type="IN" range="NULL">pointer to the context. This parameter is system specific and is interpreted as a system specific type. (e.g: in Windows CONTEXT). It contains all information necessary to retrieve the active hardware breakpoint.</param>
 * <param name="ppAddress" type="OUT">The address in the global data area of the currently active breakpoint as retrieved according to the pContext.</param>
 * <param name="pulSize" type="OUT">The size of data of the currently active breakpoint as retrieved according to the pContext</param>
 * <result>Returns ERR_OK or ERR_FAILED</result>
 */
RTS_RESULT CDECL SysCpuBreakpointGetAddressByContext(void* pContext, RTS_UINTPTR *pAddress, RTS_UI32 *pulSize);
typedef RTS_RESULT (CDECL * PFSYSCPUBREAKPOINTGETADDRESSBYCONTEXT) (void* pContext, RTS_UINTPTR *pAddress, RTS_UI32 *pulSize);
#if defined(SYSCPUBREAKPOINTS_NOTIMPLEMENTED) || defined(SYSCPUBREAKPOINTGETADDRESSBYCONTEXT_NOTIMPLEMENTED)
	#define USE_SysCpuBreakpointGetAddressByContext
	#define EXT_SysCpuBreakpointGetAddressByContext
	#define GET_SysCpuBreakpointGetAddressByContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysCpuBreakpointGetAddressByContext(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysCpuBreakpointGetAddressByContext  FALSE
	#define EXP_SysCpuBreakpointGetAddressByContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysCpuBreakpointGetAddressByContext
	#define EXT_SysCpuBreakpointGetAddressByContext
	#define GET_SysCpuBreakpointGetAddressByContext(fl)  CAL_CMGETAPI( "SysCpuBreakpointGetAddressByContext" ) 
	#define CAL_SysCpuBreakpointGetAddressByContext  SysCpuBreakpointGetAddressByContext
	#define CHK_SysCpuBreakpointGetAddressByContext  TRUE
	#define EXP_SysCpuBreakpointGetAddressByContext  CAL_CMEXPAPI( "SysCpuBreakpointGetAddressByContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUBREAKPOINTS_EXTERNAL)
	#define USE_SysCpuBreakpointGetAddressByContext
	#define EXT_SysCpuBreakpointGetAddressByContext
	#define GET_SysCpuBreakpointGetAddressByContext(fl)  CAL_CMGETAPI( "SysCpuBreakpointGetAddressByContext" ) 
	#define CAL_SysCpuBreakpointGetAddressByContext  SysCpuBreakpointGetAddressByContext
	#define CHK_SysCpuBreakpointGetAddressByContext  TRUE
	#define EXP_SysCpuBreakpointGetAddressByContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysCpuBreakpointGetAddressByContext", (RTS_UINTPTR)SysCpuBreakpointGetAddressByContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuBreakpointsSysCpuBreakpointGetAddressByContext
	#define EXT_SysCpuBreakpointsSysCpuBreakpointGetAddressByContext
	#define GET_SysCpuBreakpointsSysCpuBreakpointGetAddressByContext  ERR_OK
	#define CAL_SysCpuBreakpointsSysCpuBreakpointGetAddressByContext pISysCpuBreakpoints->ISysCpuBreakpointGetAddressByContext
	#define CHK_SysCpuBreakpointsSysCpuBreakpointGetAddressByContext (pISysCpuBreakpoints != NULL)
	#define EXP_SysCpuBreakpointsSysCpuBreakpointGetAddressByContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysCpuBreakpointGetAddressByContext
	#define EXT_SysCpuBreakpointGetAddressByContext
	#define GET_SysCpuBreakpointGetAddressByContext(fl)  CAL_CMGETAPI( "SysCpuBreakpointGetAddressByContext" ) 
	#define CAL_SysCpuBreakpointGetAddressByContext pISysCpuBreakpoints->ISysCpuBreakpointGetAddressByContext
	#define CHK_SysCpuBreakpointGetAddressByContext (pISysCpuBreakpoints != NULL)
	#define EXP_SysCpuBreakpointGetAddressByContext  CAL_CMEXPAPI( "SysCpuBreakpointGetAddressByContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysCpuBreakpointGetAddressByContext  PFSYSCPUBREAKPOINTGETADDRESSBYCONTEXT pfSysCpuBreakpointGetAddressByContext;
	#define EXT_SysCpuBreakpointGetAddressByContext  extern PFSYSCPUBREAKPOINTGETADDRESSBYCONTEXT pfSysCpuBreakpointGetAddressByContext;
	#define GET_SysCpuBreakpointGetAddressByContext(fl)  s_pfCMGetAPI2( "SysCpuBreakpointGetAddressByContext", (RTS_VOID_FCTPTR *)&pfSysCpuBreakpointGetAddressByContext, (fl), 0, 0)
	#define CAL_SysCpuBreakpointGetAddressByContext  pfSysCpuBreakpointGetAddressByContext
	#define CHK_SysCpuBreakpointGetAddressByContext  (pfSysCpuBreakpointGetAddressByContext != NULL)
	#define EXP_SysCpuBreakpointGetAddressByContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysCpuBreakpointGetAddressByContext", (RTS_UINTPTR)SysCpuBreakpointGetAddressByContext, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif




typedef struct
{
	IBase_C *pBase;
	PFSYSCPUBREAKPOINTSET ISysCpuBreakpointSet;
 	PFSYSCPUBREAKPOINTDELETE ISysCpuBreakpointDelete;
 	PFSYSCPUBREAKPOINTGETADDRESSBYCONTEXT ISysCpuBreakpointGetAddressByContext;
 } ISysCpuBreakpoints_C;

#ifdef CPLUSPLUS
class ISysCpuBreakpoints : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISysCpuBreakpointSet(RTS_HANDLE hApp, RTS_UI32 ulBPType, void *pAddress, RTS_UI32 ulSize) =0;
		virtual RTS_RESULT CDECL ISysCpuBreakpointDelete(RTS_HANDLE hApp, RTS_UI32 ulBPType, void *pAddress, RTS_UI32 ulSize) =0;
		virtual RTS_RESULT CDECL ISysCpuBreakpointGetAddressByContext(void* pContext, RTS_UINTPTR *pAddress, RTS_UI32 *pulSize) =0;
};
	#ifndef ITF_SysCpuBreakpoints
		#define ITF_SysCpuBreakpoints static ISysCpuBreakpoints *pISysCpuBreakpoints = NULL;
	#endif
	#define EXTITF_SysCpuBreakpoints
#else	/*CPLUSPLUS*/
	typedef ISysCpuBreakpoints_C		ISysCpuBreakpoints;
	#ifndef ITF_SysCpuBreakpoints
		#define ITF_SysCpuBreakpoints
	#endif
	#define EXTITF_SysCpuBreakpoints
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSCPUBREAKPOINTSITF_H_*/
