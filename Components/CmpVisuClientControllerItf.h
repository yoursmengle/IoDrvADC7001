 /**
 * <interfacename>CmpVisuClientController</interfacename>
 * <description> 
 *	Interface for the visu client controller.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPVISUCLIENTCONTROLLERITF_H_
#define _CMPVISUCLIENTCONTROLLERITF_H_

#include "CmpStd.h"

 

 




/**
 * <category>Settings</category>
 * <description>The basename for the ipcchannel.
 *	IMPORTANT: The according visuclientcontroller must have configured the same basename ! </description>
 */
#define CMPVISUCLIENTCONTROLLER_KEY_TARGETVISUPROCESS_IPCBASENAME				"IpcBasename"
#define CMPVISUCLIENTCONTROLLER_KEY_TARGETVISUPROCESS_IPCBASENAME_DEFAULT		"Ipc__VisuClientController__"

/**
 * <category>Settings</category>
 * <description>Setting that decides about the timeout that is used for single ipccalls </description>
 */
#define CMPVISUCLIENTCONTROLLER_KEY_IPCTIMEOUT				"IpcTimeoutMs"
#define CMPVISUCLIENTCONTROLLER_KEY_IPCTIMEOUT_DEFAULT		INT32_C(5000)

/**
 * <category>Settings</category>
 * <description>The basename of the sharedmemory. Will be followed by the externid of the specific client.
 * IMPORTANT: The according visualization must have configured the same basename ! </description>
 */
#define CMPVISUCLIENTCONTROLLER_KEY_TARGETVISUPROCESS_SHMBASENAME				"SharedMemoryBasename"
#define CMPVISUCLIENTCONTROLLER_KEY_TARGETVISUPROCESS_SHMBASENAME_DEFAULT		"SHM_EXTERN_VISUCLIENTCONTROLLER_"


/**
 * <description> Function to register the visu client controller host. </description>
 * <param name="pszAppName" type="IN">The target visualization application</param>
 * <param name="dwFlags" type="IN">The flags if the visu client should be created or destoyed.</param>
 * <result>error code</result>
 */	
RTS_RESULT CDECL VisuClientControllerSendRequest(char* pszAppName, RTS_IEC_DWORD dwFlags);
typedef RTS_RESULT (CDECL * PFVISUCLIENTCONTROLLERSENDREQUEST) (char* pszAppName, RTS_IEC_DWORD dwFlags);
#if defined(CMPVISUCLIENTCONTROLLER_NOTIMPLEMENTED) || defined(VISUCLIENTCONTROLLERSENDREQUEST_NOTIMPLEMENTED)
	#define USE_VisuClientControllerSendRequest
	#define EXT_VisuClientControllerSendRequest
	#define GET_VisuClientControllerSendRequest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VisuClientControllerSendRequest(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_VisuClientControllerSendRequest  FALSE
	#define EXP_VisuClientControllerSendRequest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VisuClientControllerSendRequest
	#define EXT_VisuClientControllerSendRequest
	#define GET_VisuClientControllerSendRequest(fl)  CAL_CMGETAPI( "VisuClientControllerSendRequest" ) 
	#define CAL_VisuClientControllerSendRequest  VisuClientControllerSendRequest
	#define CHK_VisuClientControllerSendRequest  TRUE
	#define EXP_VisuClientControllerSendRequest  CAL_CMEXPAPI( "VisuClientControllerSendRequest" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUCLIENTCONTROLLER_EXTERNAL)
	#define USE_VisuClientControllerSendRequest
	#define EXT_VisuClientControllerSendRequest
	#define GET_VisuClientControllerSendRequest(fl)  CAL_CMGETAPI( "VisuClientControllerSendRequest" ) 
	#define CAL_VisuClientControllerSendRequest  VisuClientControllerSendRequest
	#define CHK_VisuClientControllerSendRequest  TRUE
	#define EXP_VisuClientControllerSendRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VisuClientControllerSendRequest", (RTS_UINTPTR)VisuClientControllerSendRequest, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuClientControllerVisuClientControllerSendRequest
	#define EXT_CmpVisuClientControllerVisuClientControllerSendRequest
	#define GET_CmpVisuClientControllerVisuClientControllerSendRequest  ERR_OK
	#define CAL_CmpVisuClientControllerVisuClientControllerSendRequest  VisuClientControllerSendRequest
	#define CHK_CmpVisuClientControllerVisuClientControllerSendRequest  TRUE
	#define EXP_CmpVisuClientControllerVisuClientControllerSendRequest  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VisuClientControllerSendRequest
	#define EXT_VisuClientControllerSendRequest
	#define GET_VisuClientControllerSendRequest(fl)  CAL_CMGETAPI( "VisuClientControllerSendRequest" ) 
	#define CAL_VisuClientControllerSendRequest  VisuClientControllerSendRequest
	#define CHK_VisuClientControllerSendRequest  TRUE
	#define EXP_VisuClientControllerSendRequest  CAL_CMEXPAPI( "VisuClientControllerSendRequest" ) 
#else /* DYNAMIC_LINK */
	#define USE_VisuClientControllerSendRequest  PFVISUCLIENTCONTROLLERSENDREQUEST pfVisuClientControllerSendRequest;
	#define EXT_VisuClientControllerSendRequest  extern PFVISUCLIENTCONTROLLERSENDREQUEST pfVisuClientControllerSendRequest;
	#define GET_VisuClientControllerSendRequest(fl)  s_pfCMGetAPI2( "VisuClientControllerSendRequest", (RTS_VOID_FCTPTR *)&pfVisuClientControllerSendRequest, (fl), 0, 0)
	#define CAL_VisuClientControllerSendRequest  pfVisuClientControllerSendRequest
	#define CHK_VisuClientControllerSendRequest  (pfVisuClientControllerSendRequest != NULL)
	#define EXP_VisuClientControllerSendRequest   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VisuClientControllerSendRequest", (RTS_UINTPTR)VisuClientControllerSendRequest, 0, 0) 
#endif





typedef struct
{
	IBase_C *pBase;
} ICmpVisuClientController_C;

#ifdef CPLUSPLUS
class ICmpVisuClientController : public IBase
{
	public:
};
	#ifndef ITF_CmpVisuClientController
		#define ITF_CmpVisuClientController static ICmpVisuClientController *pICmpVisuClientController = NULL;
	#endif
	#define EXTITF_CmpVisuClientController
#else	/*CPLUSPLUS*/
	typedef ICmpVisuClientController_C		ICmpVisuClientController;
	#ifndef ITF_CmpVisuClientController
		#define ITF_CmpVisuClientController
	#endif
	#define EXTITF_CmpVisuClientController
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPVISUCLIENTCONTROLLERITF_H_*/
