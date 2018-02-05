 /**
 * <interfacename>CmpVisuClientControllerHost</interfacename>
 * <description> 
 *	Interface for the visu client controller host.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPVISUCLIENTCONTROLLERHOSTITF_H_
#define _CMPVISUCLIENTCONTROLLERHOSTITF_H_

#include "CmpStd.h"

 

 





/**
 * <category>Settings</category>
 * <description> The ipc base name of the visu client controller
 * IMPORTANT: The according visu client controller must have configured the same basename ! </description>
 */
#define CMPVISUCLIENTCONTROLLERSTUB_KEY_IPCBASENAME				"IpcBasename"
#define CMPVISUCLIENTCONTROLLERSTUB_KEY_IPCBASENAME_DEFAULT		"Ipc__VisuClientController__"

/**
 * <description> Function to register the visu client controller host. </description>
 * <param name="pszApplication" type="IN">The target visualization application</param>
 * <param name="pHandleRet" type="OUT">The created handle.</param>
 * <result>error code</result>
 */	
RTS_RESULT CDECL VisuClientControllerHostCreateInstance(char* pszApplication, RTS_HANDLE* pHandleRet);
typedef RTS_RESULT (CDECL * PFVISUCLIENTCONTROLLERHOSTCREATEINSTANCE) (char* pszApplication, RTS_HANDLE* pHandleRet);
#if defined(CMPVISUCLIENTCONTROLLERHOST_NOTIMPLEMENTED) || defined(VISUCLIENTCONTROLLERHOSTCREATEINSTANCE_NOTIMPLEMENTED)
	#define USE_VisuClientControllerHostCreateInstance
	#define EXT_VisuClientControllerHostCreateInstance
	#define GET_VisuClientControllerHostCreateInstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VisuClientControllerHostCreateInstance(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_VisuClientControllerHostCreateInstance  FALSE
	#define EXP_VisuClientControllerHostCreateInstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VisuClientControllerHostCreateInstance
	#define EXT_VisuClientControllerHostCreateInstance
	#define GET_VisuClientControllerHostCreateInstance(fl)  CAL_CMGETAPI( "VisuClientControllerHostCreateInstance" ) 
	#define CAL_VisuClientControllerHostCreateInstance  VisuClientControllerHostCreateInstance
	#define CHK_VisuClientControllerHostCreateInstance  TRUE
	#define EXP_VisuClientControllerHostCreateInstance  CAL_CMEXPAPI( "VisuClientControllerHostCreateInstance" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUCLIENTCONTROLLERHOST_EXTERNAL)
	#define USE_VisuClientControllerHostCreateInstance
	#define EXT_VisuClientControllerHostCreateInstance
	#define GET_VisuClientControllerHostCreateInstance(fl)  CAL_CMGETAPI( "VisuClientControllerHostCreateInstance" ) 
	#define CAL_VisuClientControllerHostCreateInstance  VisuClientControllerHostCreateInstance
	#define CHK_VisuClientControllerHostCreateInstance  TRUE
	#define EXP_VisuClientControllerHostCreateInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VisuClientControllerHostCreateInstance", (RTS_UINTPTR)VisuClientControllerHostCreateInstance, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuClientControllerHostVisuClientControllerHostCreateInstance
	#define EXT_CmpVisuClientControllerHostVisuClientControllerHostCreateInstance
	#define GET_CmpVisuClientControllerHostVisuClientControllerHostCreateInstance  ERR_OK
	#define CAL_CmpVisuClientControllerHostVisuClientControllerHostCreateInstance  VisuClientControllerHostCreateInstance
	#define CHK_CmpVisuClientControllerHostVisuClientControllerHostCreateInstance  TRUE
	#define EXP_CmpVisuClientControllerHostVisuClientControllerHostCreateInstance  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VisuClientControllerHostCreateInstance
	#define EXT_VisuClientControllerHostCreateInstance
	#define GET_VisuClientControllerHostCreateInstance(fl)  CAL_CMGETAPI( "VisuClientControllerHostCreateInstance" ) 
	#define CAL_VisuClientControllerHostCreateInstance  VisuClientControllerHostCreateInstance
	#define CHK_VisuClientControllerHostCreateInstance  TRUE
	#define EXP_VisuClientControllerHostCreateInstance  CAL_CMEXPAPI( "VisuClientControllerHostCreateInstance" ) 
#else /* DYNAMIC_LINK */
	#define USE_VisuClientControllerHostCreateInstance  PFVISUCLIENTCONTROLLERHOSTCREATEINSTANCE pfVisuClientControllerHostCreateInstance;
	#define EXT_VisuClientControllerHostCreateInstance  extern PFVISUCLIENTCONTROLLERHOSTCREATEINSTANCE pfVisuClientControllerHostCreateInstance;
	#define GET_VisuClientControllerHostCreateInstance(fl)  s_pfCMGetAPI2( "VisuClientControllerHostCreateInstance", (RTS_VOID_FCTPTR *)&pfVisuClientControllerHostCreateInstance, (fl), 0, 0)
	#define CAL_VisuClientControllerHostCreateInstance  pfVisuClientControllerHostCreateInstance
	#define CHK_VisuClientControllerHostCreateInstance  (pfVisuClientControllerHostCreateInstance != NULL)
	#define EXP_VisuClientControllerHostCreateInstance   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VisuClientControllerHostCreateInstance", (RTS_UINTPTR)VisuClientControllerHostCreateInstance, 0, 0) 
#endif


/**
 * <description> Function to release a formerly registered visu client controller host. </description>
 * <param name="hInstance" type="IN">The instance that should be released.</param>
 * <result>error code</result>
 */	
RTS_RESULT CDECL VisuClientControllerHostDestroyInstance(RTS_HANDLE hInstance);
typedef RTS_RESULT (CDECL * PFVISUCLIENTCONTROLLERHOSTDESTROYINSTANCE) (RTS_HANDLE hInstance);
#if defined(CMPVISUCLIENTCONTROLLERHOST_NOTIMPLEMENTED) || defined(VISUCLIENTCONTROLLERHOSTDESTROYINSTANCE_NOTIMPLEMENTED)
	#define USE_VisuClientControllerHostDestroyInstance
	#define EXT_VisuClientControllerHostDestroyInstance
	#define GET_VisuClientControllerHostDestroyInstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VisuClientControllerHostDestroyInstance(p0) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_VisuClientControllerHostDestroyInstance  FALSE
	#define EXP_VisuClientControllerHostDestroyInstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VisuClientControllerHostDestroyInstance
	#define EXT_VisuClientControllerHostDestroyInstance
	#define GET_VisuClientControllerHostDestroyInstance(fl)  CAL_CMGETAPI( "VisuClientControllerHostDestroyInstance" ) 
	#define CAL_VisuClientControllerHostDestroyInstance  VisuClientControllerHostDestroyInstance
	#define CHK_VisuClientControllerHostDestroyInstance  TRUE
	#define EXP_VisuClientControllerHostDestroyInstance  CAL_CMEXPAPI( "VisuClientControllerHostDestroyInstance" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUCLIENTCONTROLLERHOST_EXTERNAL)
	#define USE_VisuClientControllerHostDestroyInstance
	#define EXT_VisuClientControllerHostDestroyInstance
	#define GET_VisuClientControllerHostDestroyInstance(fl)  CAL_CMGETAPI( "VisuClientControllerHostDestroyInstance" ) 
	#define CAL_VisuClientControllerHostDestroyInstance  VisuClientControllerHostDestroyInstance
	#define CHK_VisuClientControllerHostDestroyInstance  TRUE
	#define EXP_VisuClientControllerHostDestroyInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VisuClientControllerHostDestroyInstance", (RTS_UINTPTR)VisuClientControllerHostDestroyInstance, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuClientControllerHostVisuClientControllerHostDestroyInstance
	#define EXT_CmpVisuClientControllerHostVisuClientControllerHostDestroyInstance
	#define GET_CmpVisuClientControllerHostVisuClientControllerHostDestroyInstance  ERR_OK
	#define CAL_CmpVisuClientControllerHostVisuClientControllerHostDestroyInstance  VisuClientControllerHostDestroyInstance
	#define CHK_CmpVisuClientControllerHostVisuClientControllerHostDestroyInstance  TRUE
	#define EXP_CmpVisuClientControllerHostVisuClientControllerHostDestroyInstance  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VisuClientControllerHostDestroyInstance
	#define EXT_VisuClientControllerHostDestroyInstance
	#define GET_VisuClientControllerHostDestroyInstance(fl)  CAL_CMGETAPI( "VisuClientControllerHostDestroyInstance" ) 
	#define CAL_VisuClientControllerHostDestroyInstance  VisuClientControllerHostDestroyInstance
	#define CHK_VisuClientControllerHostDestroyInstance  TRUE
	#define EXP_VisuClientControllerHostDestroyInstance  CAL_CMEXPAPI( "VisuClientControllerHostDestroyInstance" ) 
#else /* DYNAMIC_LINK */
	#define USE_VisuClientControllerHostDestroyInstance  PFVISUCLIENTCONTROLLERHOSTDESTROYINSTANCE pfVisuClientControllerHostDestroyInstance;
	#define EXT_VisuClientControllerHostDestroyInstance  extern PFVISUCLIENTCONTROLLERHOSTDESTROYINSTANCE pfVisuClientControllerHostDestroyInstance;
	#define GET_VisuClientControllerHostDestroyInstance(fl)  s_pfCMGetAPI2( "VisuClientControllerHostDestroyInstance", (RTS_VOID_FCTPTR *)&pfVisuClientControllerHostDestroyInstance, (fl), 0, 0)
	#define CAL_VisuClientControllerHostDestroyInstance  pfVisuClientControllerHostDestroyInstance
	#define CHK_VisuClientControllerHostDestroyInstance  (pfVisuClientControllerHostDestroyInstance != NULL)
	#define EXP_VisuClientControllerHostDestroyInstance   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VisuClientControllerHostDestroyInstance", (RTS_UINTPTR)VisuClientControllerHostDestroyInstance, 0, 0) 
#endif





typedef struct
{
	IBase_C *pBase;
} ICmpVisuClientControllerHost_C;

#ifdef CPLUSPLUS
class ICmpVisuClientControllerHost : public IBase
{
	public:
};
	#ifndef ITF_CmpVisuClientControllerHost
		#define ITF_CmpVisuClientControllerHost static ICmpVisuClientControllerHost *pICmpVisuClientControllerHost = NULL;
	#endif
	#define EXTITF_CmpVisuClientControllerHost
#else	/*CPLUSPLUS*/
	typedef ICmpVisuClientControllerHost_C		ICmpVisuClientControllerHost;
	#ifndef ITF_CmpVisuClientControllerHost
		#define ITF_CmpVisuClientControllerHost
	#endif
	#define EXTITF_CmpVisuClientControllerHost
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPVISUCLIENTCONTROLLERHOSTITF_H_*/
