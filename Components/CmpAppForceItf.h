 /**
 * <interfacename>CmpAppForce</interfacename>
 * <description> 
 *	This is the interface of the IEC application manager to handle forcing variables.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPAPPFORCEITF_H_
#define _CMPAPPFORCEITF_H_

#include "CmpStd.h"

 

 




#include "CmpAppItf.h"
#include "CmpSrvItf.h"

#ifdef CMPAPP_NOTIMPLEMENTED
	#ifndef CMPAPPFORCE_NOTIMPLEMENTED
		#define CMPAPPFORCE_NOTIMPLEMENTED
	#endif
#endif

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="APPFORCE_DISABLE_PERSISTENT_FORCE">Switch to disable persistent force</element>
 */


/**
 * <category>Static defines</category>
 * <description>Length of force list that is allocated static in the application object</description>
 */
#ifndef APPL_STATIC_FORCE_ENTRIES
	#define APPL_STATIC_FORCE_ENTRIES		10
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Settings to enable persistent force</description>
 */
#define APPKEY_INT_PERSISTENT_FORCE					"PersistentForce"
#ifndef APPVALUE_INT_PERSISTENT_FORCE_DEFAULT
	#define APPVALUE_INT_PERSISTENT_FORCE_DEFAULT	0
#endif
#ifdef APPFORCE_DISABLE_PERSISTENT_FORCE
	#undef APPVALUE_INT_PERSISTENT_FORCE_DEFAULT
	#define APPVALUE_INT_PERSISTENT_FORCE_DEFAULT	0
#endif

#define RTS_FORCEFLAGS_SAFEDOLDVALUE			1
#define RTS_FORCEFLAGS_RESTORE					2

typedef struct tagForceVarDesc
{
	RTS_I32 nRefCount;
	RTS_UI32 ulFlags;
	VarDataRef DataRef;
	VarValue Value;
	VarValue OldValue;
} ForceVarDesc;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Init force list on the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppForceInit(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFAPPFORCEINIT) (APPLICATION *pApp);
#if defined(CMPAPPFORCE_NOTIMPLEMENTED) || defined(APPFORCEINIT_NOTIMPLEMENTED)
	#define USE_AppForceInit
	#define EXT_AppForceInit
	#define GET_AppForceInit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppForceInit(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppForceInit  FALSE
	#define EXP_AppForceInit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppForceInit
	#define EXT_AppForceInit
	#define GET_AppForceInit(fl)  CAL_CMGETAPI( "AppForceInit" ) 
	#define CAL_AppForceInit  AppForceInit
	#define CHK_AppForceInit  TRUE
	#define EXP_AppForceInit  CAL_CMEXPAPI( "AppForceInit" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPFORCE_EXTERNAL)
	#define USE_AppForceInit
	#define EXT_AppForceInit
	#define GET_AppForceInit(fl)  CAL_CMGETAPI( "AppForceInit" ) 
	#define CAL_AppForceInit  AppForceInit
	#define CHK_AppForceInit  TRUE
	#define EXP_AppForceInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppForceInit", (RTS_UINTPTR)AppForceInit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppForceAppForceInit
	#define EXT_CmpAppForceAppForceInit
	#define GET_CmpAppForceAppForceInit  ERR_OK
	#define CAL_CmpAppForceAppForceInit pICmpAppForce->IAppForceInit
	#define CHK_CmpAppForceAppForceInit (pICmpAppForce != NULL)
	#define EXP_CmpAppForceAppForceInit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppForceInit
	#define EXT_AppForceInit
	#define GET_AppForceInit(fl)  CAL_CMGETAPI( "AppForceInit" ) 
	#define CAL_AppForceInit pICmpAppForce->IAppForceInit
	#define CHK_AppForceInit (pICmpAppForce != NULL)
	#define EXP_AppForceInit  CAL_CMEXPAPI( "AppForceInit" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppForceInit  PFAPPFORCEINIT pfAppForceInit;
	#define EXT_AppForceInit  extern PFAPPFORCEINIT pfAppForceInit;
	#define GET_AppForceInit(fl)  s_pfCMGetAPI2( "AppForceInit", (RTS_VOID_FCTPTR *)&pfAppForceInit, (fl), 0, 0)
	#define CAL_AppForceInit  pfAppForceInit
	#define CHK_AppForceInit  (pfAppForceInit != NULL)
	#define EXP_AppForceInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppForceInit", (RTS_UINTPTR)AppForceInit, 0, 0) 
#endif




/**
 * <description>Exit force list on the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <element name="bShutdown" type="IN">1=Runtime exits the application and so the force during shutdown, 0=else</element>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppForceExit(APPLICATION *pApp, int bShutdown);
typedef RTS_RESULT (CDECL * PFAPPFORCEEXIT) (APPLICATION *pApp, int bShutdown);
#if defined(CMPAPPFORCE_NOTIMPLEMENTED) || defined(APPFORCEEXIT_NOTIMPLEMENTED)
	#define USE_AppForceExit
	#define EXT_AppForceExit
	#define GET_AppForceExit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppForceExit(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppForceExit  FALSE
	#define EXP_AppForceExit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppForceExit
	#define EXT_AppForceExit
	#define GET_AppForceExit(fl)  CAL_CMGETAPI( "AppForceExit" ) 
	#define CAL_AppForceExit  AppForceExit
	#define CHK_AppForceExit  TRUE
	#define EXP_AppForceExit  CAL_CMEXPAPI( "AppForceExit" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPFORCE_EXTERNAL)
	#define USE_AppForceExit
	#define EXT_AppForceExit
	#define GET_AppForceExit(fl)  CAL_CMGETAPI( "AppForceExit" ) 
	#define CAL_AppForceExit  AppForceExit
	#define CHK_AppForceExit  TRUE
	#define EXP_AppForceExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppForceExit", (RTS_UINTPTR)AppForceExit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppForceAppForceExit
	#define EXT_CmpAppForceAppForceExit
	#define GET_CmpAppForceAppForceExit  ERR_OK
	#define CAL_CmpAppForceAppForceExit pICmpAppForce->IAppForceExit
	#define CHK_CmpAppForceAppForceExit (pICmpAppForce != NULL)
	#define EXP_CmpAppForceAppForceExit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppForceExit
	#define EXT_AppForceExit
	#define GET_AppForceExit(fl)  CAL_CMGETAPI( "AppForceExit" ) 
	#define CAL_AppForceExit pICmpAppForce->IAppForceExit
	#define CHK_AppForceExit (pICmpAppForce != NULL)
	#define EXP_AppForceExit  CAL_CMEXPAPI( "AppForceExit" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppForceExit  PFAPPFORCEEXIT pfAppForceExit;
	#define EXT_AppForceExit  extern PFAPPFORCEEXIT pfAppForceExit;
	#define GET_AppForceExit(fl)  s_pfCMGetAPI2( "AppForceExit", (RTS_VOID_FCTPTR *)&pfAppForceExit, (fl), 0, 0)
	#define CAL_AppForceExit  pfAppForceExit
	#define CHK_AppForceExit  (pfAppForceExit != NULL)
	#define EXP_AppForceExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppForceExit", (RTS_UINTPTR)AppForceExit, 0, 0) 
#endif




/**
 * <description>Add a new force value, that is forced in every task of the application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pDataRef" type="IN">Pointer to decription of the force variable</param>
 * <param name="pValue" type="IN">Pointer to value of the force variable that will be hold</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppAddForceValue(APPLICATION* pApp, VarDataRef *pDataRef, VarValue *pValue);
typedef RTS_RESULT (CDECL * PFAPPADDFORCEVALUE) (APPLICATION* pApp, VarDataRef *pDataRef, VarValue *pValue);
#if defined(CMPAPPFORCE_NOTIMPLEMENTED) || defined(APPADDFORCEVALUE_NOTIMPLEMENTED)
	#define USE_AppAddForceValue
	#define EXT_AppAddForceValue
	#define GET_AppAddForceValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppAddForceValue(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppAddForceValue  FALSE
	#define EXP_AppAddForceValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppAddForceValue
	#define EXT_AppAddForceValue
	#define GET_AppAddForceValue(fl)  CAL_CMGETAPI( "AppAddForceValue" ) 
	#define CAL_AppAddForceValue  AppAddForceValue
	#define CHK_AppAddForceValue  TRUE
	#define EXP_AppAddForceValue  CAL_CMEXPAPI( "AppAddForceValue" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPFORCE_EXTERNAL)
	#define USE_AppAddForceValue
	#define EXT_AppAddForceValue
	#define GET_AppAddForceValue(fl)  CAL_CMGETAPI( "AppAddForceValue" ) 
	#define CAL_AppAddForceValue  AppAddForceValue
	#define CHK_AppAddForceValue  TRUE
	#define EXP_AppAddForceValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppAddForceValue", (RTS_UINTPTR)AppAddForceValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppForceAppAddForceValue
	#define EXT_CmpAppForceAppAddForceValue
	#define GET_CmpAppForceAppAddForceValue  ERR_OK
	#define CAL_CmpAppForceAppAddForceValue pICmpAppForce->IAppAddForceValue
	#define CHK_CmpAppForceAppAddForceValue (pICmpAppForce != NULL)
	#define EXP_CmpAppForceAppAddForceValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppAddForceValue
	#define EXT_AppAddForceValue
	#define GET_AppAddForceValue(fl)  CAL_CMGETAPI( "AppAddForceValue" ) 
	#define CAL_AppAddForceValue pICmpAppForce->IAppAddForceValue
	#define CHK_AppAddForceValue (pICmpAppForce != NULL)
	#define EXP_AppAddForceValue  CAL_CMEXPAPI( "AppAddForceValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppAddForceValue  PFAPPADDFORCEVALUE pfAppAddForceValue;
	#define EXT_AppAddForceValue  extern PFAPPADDFORCEVALUE pfAppAddForceValue;
	#define GET_AppAddForceValue(fl)  s_pfCMGetAPI2( "AppAddForceValue", (RTS_VOID_FCTPTR *)&pfAppAddForceValue, (fl), 0, 0)
	#define CAL_AppAddForceValue  pfAppAddForceValue
	#define CHK_AppAddForceValue  (pfAppAddForceValue != NULL)
	#define EXP_AppAddForceValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppAddForceValue", (RTS_UINTPTR)AppAddForceValue, 0, 0) 
#endif




/**
 * <description>Remove a single force value</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pDataRef" type="IN">Pointer to decription of the force variable</param>
 * <param name="bRestoreValue" type="IN">1=Restore old value before force. 0=Actual force value will not be modified</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppReleaseForceValue(APPLICATION* pApp, VarDataRef *pDataRef, int bRestoreValue);
typedef RTS_RESULT (CDECL * PFAPPRELEASEFORCEVALUE) (APPLICATION* pApp, VarDataRef *pDataRef, int bRestoreValue);
#if defined(CMPAPPFORCE_NOTIMPLEMENTED) || defined(APPRELEASEFORCEVALUE_NOTIMPLEMENTED)
	#define USE_AppReleaseForceValue
	#define EXT_AppReleaseForceValue
	#define GET_AppReleaseForceValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppReleaseForceValue(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppReleaseForceValue  FALSE
	#define EXP_AppReleaseForceValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppReleaseForceValue
	#define EXT_AppReleaseForceValue
	#define GET_AppReleaseForceValue(fl)  CAL_CMGETAPI( "AppReleaseForceValue" ) 
	#define CAL_AppReleaseForceValue  AppReleaseForceValue
	#define CHK_AppReleaseForceValue  TRUE
	#define EXP_AppReleaseForceValue  CAL_CMEXPAPI( "AppReleaseForceValue" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPFORCE_EXTERNAL)
	#define USE_AppReleaseForceValue
	#define EXT_AppReleaseForceValue
	#define GET_AppReleaseForceValue(fl)  CAL_CMGETAPI( "AppReleaseForceValue" ) 
	#define CAL_AppReleaseForceValue  AppReleaseForceValue
	#define CHK_AppReleaseForceValue  TRUE
	#define EXP_AppReleaseForceValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppReleaseForceValue", (RTS_UINTPTR)AppReleaseForceValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppForceAppReleaseForceValue
	#define EXT_CmpAppForceAppReleaseForceValue
	#define GET_CmpAppForceAppReleaseForceValue  ERR_OK
	#define CAL_CmpAppForceAppReleaseForceValue pICmpAppForce->IAppReleaseForceValue
	#define CHK_CmpAppForceAppReleaseForceValue (pICmpAppForce != NULL)
	#define EXP_CmpAppForceAppReleaseForceValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppReleaseForceValue
	#define EXT_AppReleaseForceValue
	#define GET_AppReleaseForceValue(fl)  CAL_CMGETAPI( "AppReleaseForceValue" ) 
	#define CAL_AppReleaseForceValue pICmpAppForce->IAppReleaseForceValue
	#define CHK_AppReleaseForceValue (pICmpAppForce != NULL)
	#define EXP_AppReleaseForceValue  CAL_CMEXPAPI( "AppReleaseForceValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppReleaseForceValue  PFAPPRELEASEFORCEVALUE pfAppReleaseForceValue;
	#define EXT_AppReleaseForceValue  extern PFAPPRELEASEFORCEVALUE pfAppReleaseForceValue;
	#define GET_AppReleaseForceValue(fl)  s_pfCMGetAPI2( "AppReleaseForceValue", (RTS_VOID_FCTPTR *)&pfAppReleaseForceValue, (fl), 0, 0)
	#define CAL_AppReleaseForceValue  pfAppReleaseForceValue
	#define CHK_AppReleaseForceValue  (pfAppReleaseForceValue != NULL)
	#define EXP_AppReleaseForceValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppReleaseForceValue", (RTS_UINTPTR)AppReleaseForceValue, 0, 0) 
#endif




/**
 * <description>Get first force entry</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to force value</result>
 */
ForceVarDesc * CDECL AppGetFirstForce(APPLICATION *pApp, RTS_RESULT *pResult);
typedef ForceVarDesc * (CDECL * PFAPPGETFIRSTFORCE) (APPLICATION *pApp, RTS_RESULT *pResult);
#if defined(CMPAPPFORCE_NOTIMPLEMENTED) || defined(APPGETFIRSTFORCE_NOTIMPLEMENTED)
	#define USE_AppGetFirstForce
	#define EXT_AppGetFirstForce
	#define GET_AppGetFirstForce(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetFirstForce(p0,p1)  (ForceVarDesc *)ERR_NOTIMPLEMENTED
	#define CHK_AppGetFirstForce  FALSE
	#define EXP_AppGetFirstForce  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetFirstForce
	#define EXT_AppGetFirstForce
	#define GET_AppGetFirstForce(fl)  CAL_CMGETAPI( "AppGetFirstForce" ) 
	#define CAL_AppGetFirstForce  AppGetFirstForce
	#define CHK_AppGetFirstForce  TRUE
	#define EXP_AppGetFirstForce  CAL_CMEXPAPI( "AppGetFirstForce" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPFORCE_EXTERNAL)
	#define USE_AppGetFirstForce
	#define EXT_AppGetFirstForce
	#define GET_AppGetFirstForce(fl)  CAL_CMGETAPI( "AppGetFirstForce" ) 
	#define CAL_AppGetFirstForce  AppGetFirstForce
	#define CHK_AppGetFirstForce  TRUE
	#define EXP_AppGetFirstForce  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetFirstForce", (RTS_UINTPTR)AppGetFirstForce, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppForceAppGetFirstForce
	#define EXT_CmpAppForceAppGetFirstForce
	#define GET_CmpAppForceAppGetFirstForce  ERR_OK
	#define CAL_CmpAppForceAppGetFirstForce pICmpAppForce->IAppGetFirstForce
	#define CHK_CmpAppForceAppGetFirstForce (pICmpAppForce != NULL)
	#define EXP_CmpAppForceAppGetFirstForce  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetFirstForce
	#define EXT_AppGetFirstForce
	#define GET_AppGetFirstForce(fl)  CAL_CMGETAPI( "AppGetFirstForce" ) 
	#define CAL_AppGetFirstForce pICmpAppForce->IAppGetFirstForce
	#define CHK_AppGetFirstForce (pICmpAppForce != NULL)
	#define EXP_AppGetFirstForce  CAL_CMEXPAPI( "AppGetFirstForce" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetFirstForce  PFAPPGETFIRSTFORCE pfAppGetFirstForce;
	#define EXT_AppGetFirstForce  extern PFAPPGETFIRSTFORCE pfAppGetFirstForce;
	#define GET_AppGetFirstForce(fl)  s_pfCMGetAPI2( "AppGetFirstForce", (RTS_VOID_FCTPTR *)&pfAppGetFirstForce, (fl), 0, 0)
	#define CAL_AppGetFirstForce  pfAppGetFirstForce
	#define CHK_AppGetFirstForce  (pfAppGetFirstForce != NULL)
	#define EXP_AppGetFirstForce  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetFirstForce", (RTS_UINTPTR)AppGetFirstForce, 0, 0) 
#endif




/**
 * <description>Get next force entry</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pPrevForce" type="IN">Pointer to previous force entry</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to force value</result>
 */
ForceVarDesc * CDECL AppGetNextForce(APPLICATION *pApp, ForceVarDesc *pPrevForce, RTS_RESULT *pResult);
typedef ForceVarDesc * (CDECL * PFAPPGETNEXTFORCE) (APPLICATION *pApp, ForceVarDesc *pPrevForce, RTS_RESULT *pResult);
#if defined(CMPAPPFORCE_NOTIMPLEMENTED) || defined(APPGETNEXTFORCE_NOTIMPLEMENTED)
	#define USE_AppGetNextForce
	#define EXT_AppGetNextForce
	#define GET_AppGetNextForce(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetNextForce(p0,p1,p2)  (ForceVarDesc *)ERR_NOTIMPLEMENTED
	#define CHK_AppGetNextForce  FALSE
	#define EXP_AppGetNextForce  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetNextForce
	#define EXT_AppGetNextForce
	#define GET_AppGetNextForce(fl)  CAL_CMGETAPI( "AppGetNextForce" ) 
	#define CAL_AppGetNextForce  AppGetNextForce
	#define CHK_AppGetNextForce  TRUE
	#define EXP_AppGetNextForce  CAL_CMEXPAPI( "AppGetNextForce" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPFORCE_EXTERNAL)
	#define USE_AppGetNextForce
	#define EXT_AppGetNextForce
	#define GET_AppGetNextForce(fl)  CAL_CMGETAPI( "AppGetNextForce" ) 
	#define CAL_AppGetNextForce  AppGetNextForce
	#define CHK_AppGetNextForce  TRUE
	#define EXP_AppGetNextForce  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNextForce", (RTS_UINTPTR)AppGetNextForce, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppForceAppGetNextForce
	#define EXT_CmpAppForceAppGetNextForce
	#define GET_CmpAppForceAppGetNextForce  ERR_OK
	#define CAL_CmpAppForceAppGetNextForce pICmpAppForce->IAppGetNextForce
	#define CHK_CmpAppForceAppGetNextForce (pICmpAppForce != NULL)
	#define EXP_CmpAppForceAppGetNextForce  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetNextForce
	#define EXT_AppGetNextForce
	#define GET_AppGetNextForce(fl)  CAL_CMGETAPI( "AppGetNextForce" ) 
	#define CAL_AppGetNextForce pICmpAppForce->IAppGetNextForce
	#define CHK_AppGetNextForce (pICmpAppForce != NULL)
	#define EXP_AppGetNextForce  CAL_CMEXPAPI( "AppGetNextForce" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetNextForce  PFAPPGETNEXTFORCE pfAppGetNextForce;
	#define EXT_AppGetNextForce  extern PFAPPGETNEXTFORCE pfAppGetNextForce;
	#define GET_AppGetNextForce(fl)  s_pfCMGetAPI2( "AppGetNextForce", (RTS_VOID_FCTPTR *)&pfAppGetNextForce, (fl), 0, 0)
	#define CAL_AppGetNextForce  pfAppGetNextForce
	#define CHK_AppGetNextForce  (pfAppGetNextForce != NULL)
	#define EXP_AppGetNextForce  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNextForce", (RTS_UINTPTR)AppGetNextForce, 0, 0) 
#endif




/**
 * <description>Release all force values of the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <element name="bShutdown" type="IN">1=Runtime exits the application and so the force during shutdown, 0=else</element>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppReleaseAllForceValues(APPLICATION* pApp, int bShutdown);
typedef RTS_RESULT (CDECL * PFAPPRELEASEALLFORCEVALUES) (APPLICATION* pApp, int bShutdown);
#if defined(CMPAPPFORCE_NOTIMPLEMENTED) || defined(APPRELEASEALLFORCEVALUES_NOTIMPLEMENTED)
	#define USE_AppReleaseAllForceValues
	#define EXT_AppReleaseAllForceValues
	#define GET_AppReleaseAllForceValues(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppReleaseAllForceValues(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppReleaseAllForceValues  FALSE
	#define EXP_AppReleaseAllForceValues  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppReleaseAllForceValues
	#define EXT_AppReleaseAllForceValues
	#define GET_AppReleaseAllForceValues(fl)  CAL_CMGETAPI( "AppReleaseAllForceValues" ) 
	#define CAL_AppReleaseAllForceValues  AppReleaseAllForceValues
	#define CHK_AppReleaseAllForceValues  TRUE
	#define EXP_AppReleaseAllForceValues  CAL_CMEXPAPI( "AppReleaseAllForceValues" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPFORCE_EXTERNAL)
	#define USE_AppReleaseAllForceValues
	#define EXT_AppReleaseAllForceValues
	#define GET_AppReleaseAllForceValues(fl)  CAL_CMGETAPI( "AppReleaseAllForceValues" ) 
	#define CAL_AppReleaseAllForceValues  AppReleaseAllForceValues
	#define CHK_AppReleaseAllForceValues  TRUE
	#define EXP_AppReleaseAllForceValues  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppReleaseAllForceValues", (RTS_UINTPTR)AppReleaseAllForceValues, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppForceAppReleaseAllForceValues
	#define EXT_CmpAppForceAppReleaseAllForceValues
	#define GET_CmpAppForceAppReleaseAllForceValues  ERR_OK
	#define CAL_CmpAppForceAppReleaseAllForceValues pICmpAppForce->IAppReleaseAllForceValues
	#define CHK_CmpAppForceAppReleaseAllForceValues (pICmpAppForce != NULL)
	#define EXP_CmpAppForceAppReleaseAllForceValues  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppReleaseAllForceValues
	#define EXT_AppReleaseAllForceValues
	#define GET_AppReleaseAllForceValues(fl)  CAL_CMGETAPI( "AppReleaseAllForceValues" ) 
	#define CAL_AppReleaseAllForceValues pICmpAppForce->IAppReleaseAllForceValues
	#define CHK_AppReleaseAllForceValues (pICmpAppForce != NULL)
	#define EXP_AppReleaseAllForceValues  CAL_CMEXPAPI( "AppReleaseAllForceValues" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppReleaseAllForceValues  PFAPPRELEASEALLFORCEVALUES pfAppReleaseAllForceValues;
	#define EXT_AppReleaseAllForceValues  extern PFAPPRELEASEALLFORCEVALUES pfAppReleaseAllForceValues;
	#define GET_AppReleaseAllForceValues(fl)  s_pfCMGetAPI2( "AppReleaseAllForceValues", (RTS_VOID_FCTPTR *)&pfAppReleaseAllForceValues, (fl), 0, 0)
	#define CAL_AppReleaseAllForceValues  pfAppReleaseAllForceValues
	#define CHK_AppReleaseAllForceValues  (pfAppReleaseAllForceValues != NULL)
	#define EXP_AppReleaseAllForceValues  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppReleaseAllForceValues", (RTS_UINTPTR)AppReleaseAllForceValues, 0, 0) 
#endif




/**
 * <description>Load persistent force list, if available</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppLoadPersistentForce(APPLICATION* pApp);
typedef RTS_RESULT (CDECL * PFAPPLOADPERSISTENTFORCE) (APPLICATION* pApp);
#if defined(CMPAPPFORCE_NOTIMPLEMENTED) || defined(APPLOADPERSISTENTFORCE_NOTIMPLEMENTED)
	#define USE_AppLoadPersistentForce
	#define EXT_AppLoadPersistentForce
	#define GET_AppLoadPersistentForce(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppLoadPersistentForce(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppLoadPersistentForce  FALSE
	#define EXP_AppLoadPersistentForce  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppLoadPersistentForce
	#define EXT_AppLoadPersistentForce
	#define GET_AppLoadPersistentForce(fl)  CAL_CMGETAPI( "AppLoadPersistentForce" ) 
	#define CAL_AppLoadPersistentForce  AppLoadPersistentForce
	#define CHK_AppLoadPersistentForce  TRUE
	#define EXP_AppLoadPersistentForce  CAL_CMEXPAPI( "AppLoadPersistentForce" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPFORCE_EXTERNAL)
	#define USE_AppLoadPersistentForce
	#define EXT_AppLoadPersistentForce
	#define GET_AppLoadPersistentForce(fl)  CAL_CMGETAPI( "AppLoadPersistentForce" ) 
	#define CAL_AppLoadPersistentForce  AppLoadPersistentForce
	#define CHK_AppLoadPersistentForce  TRUE
	#define EXP_AppLoadPersistentForce  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppLoadPersistentForce", (RTS_UINTPTR)AppLoadPersistentForce, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppForceAppLoadPersistentForce
	#define EXT_CmpAppForceAppLoadPersistentForce
	#define GET_CmpAppForceAppLoadPersistentForce  ERR_OK
	#define CAL_CmpAppForceAppLoadPersistentForce pICmpAppForce->IAppLoadPersistentForce
	#define CHK_CmpAppForceAppLoadPersistentForce (pICmpAppForce != NULL)
	#define EXP_CmpAppForceAppLoadPersistentForce  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppLoadPersistentForce
	#define EXT_AppLoadPersistentForce
	#define GET_AppLoadPersistentForce(fl)  CAL_CMGETAPI( "AppLoadPersistentForce" ) 
	#define CAL_AppLoadPersistentForce pICmpAppForce->IAppLoadPersistentForce
	#define CHK_AppLoadPersistentForce (pICmpAppForce != NULL)
	#define EXP_AppLoadPersistentForce  CAL_CMEXPAPI( "AppLoadPersistentForce" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppLoadPersistentForce  PFAPPLOADPERSISTENTFORCE pfAppLoadPersistentForce;
	#define EXT_AppLoadPersistentForce  extern PFAPPLOADPERSISTENTFORCE pfAppLoadPersistentForce;
	#define GET_AppLoadPersistentForce(fl)  s_pfCMGetAPI2( "AppLoadPersistentForce", (RTS_VOID_FCTPTR *)&pfAppLoadPersistentForce, (fl), 0, 0)
	#define CAL_AppLoadPersistentForce  pfAppLoadPersistentForce
	#define CHK_AppLoadPersistentForce  (pfAppLoadPersistentForce != NULL)
	#define EXP_AppLoadPersistentForce  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppLoadPersistentForce", (RTS_UINTPTR)AppLoadPersistentForce, 0, 0) 
#endif




/**
 * <description>Create persistent force list. This is used to force values right after a reboot
 *	of the controller</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppCreatePersistentForce(APPLICATION* pApp);
typedef RTS_RESULT (CDECL * PFAPPCREATEPERSISTENTFORCE) (APPLICATION* pApp);
#if defined(CMPAPPFORCE_NOTIMPLEMENTED) || defined(APPCREATEPERSISTENTFORCE_NOTIMPLEMENTED)
	#define USE_AppCreatePersistentForce
	#define EXT_AppCreatePersistentForce
	#define GET_AppCreatePersistentForce(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppCreatePersistentForce(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppCreatePersistentForce  FALSE
	#define EXP_AppCreatePersistentForce  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppCreatePersistentForce
	#define EXT_AppCreatePersistentForce
	#define GET_AppCreatePersistentForce(fl)  CAL_CMGETAPI( "AppCreatePersistentForce" ) 
	#define CAL_AppCreatePersistentForce  AppCreatePersistentForce
	#define CHK_AppCreatePersistentForce  TRUE
	#define EXP_AppCreatePersistentForce  CAL_CMEXPAPI( "AppCreatePersistentForce" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPFORCE_EXTERNAL)
	#define USE_AppCreatePersistentForce
	#define EXT_AppCreatePersistentForce
	#define GET_AppCreatePersistentForce(fl)  CAL_CMGETAPI( "AppCreatePersistentForce" ) 
	#define CAL_AppCreatePersistentForce  AppCreatePersistentForce
	#define CHK_AppCreatePersistentForce  TRUE
	#define EXP_AppCreatePersistentForce  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCreatePersistentForce", (RTS_UINTPTR)AppCreatePersistentForce, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppForceAppCreatePersistentForce
	#define EXT_CmpAppForceAppCreatePersistentForce
	#define GET_CmpAppForceAppCreatePersistentForce  ERR_OK
	#define CAL_CmpAppForceAppCreatePersistentForce pICmpAppForce->IAppCreatePersistentForce
	#define CHK_CmpAppForceAppCreatePersistentForce (pICmpAppForce != NULL)
	#define EXP_CmpAppForceAppCreatePersistentForce  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppCreatePersistentForce
	#define EXT_AppCreatePersistentForce
	#define GET_AppCreatePersistentForce(fl)  CAL_CMGETAPI( "AppCreatePersistentForce" ) 
	#define CAL_AppCreatePersistentForce pICmpAppForce->IAppCreatePersistentForce
	#define CHK_AppCreatePersistentForce (pICmpAppForce != NULL)
	#define EXP_AppCreatePersistentForce  CAL_CMEXPAPI( "AppCreatePersistentForce" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppCreatePersistentForce  PFAPPCREATEPERSISTENTFORCE pfAppCreatePersistentForce;
	#define EXT_AppCreatePersistentForce  extern PFAPPCREATEPERSISTENTFORCE pfAppCreatePersistentForce;
	#define GET_AppCreatePersistentForce(fl)  s_pfCMGetAPI2( "AppCreatePersistentForce", (RTS_VOID_FCTPTR *)&pfAppCreatePersistentForce, (fl), 0, 0)
	#define CAL_AppCreatePersistentForce  pfAppCreatePersistentForce
	#define CHK_AppCreatePersistentForce  (pfAppCreatePersistentForce != NULL)
	#define EXP_AppCreatePersistentForce  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCreatePersistentForce", (RTS_UINTPTR)AppCreatePersistentForce, 0, 0) 
#endif




/**
 * <description>Delete persistent force list of the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppDeletePersistentForce(APPLICATION* pApp);
typedef RTS_RESULT (CDECL * PFAPPDELETEPERSISTENTFORCE) (APPLICATION* pApp);
#if defined(CMPAPPFORCE_NOTIMPLEMENTED) || defined(APPDELETEPERSISTENTFORCE_NOTIMPLEMENTED)
	#define USE_AppDeletePersistentForce
	#define EXT_AppDeletePersistentForce
	#define GET_AppDeletePersistentForce(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppDeletePersistentForce(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppDeletePersistentForce  FALSE
	#define EXP_AppDeletePersistentForce  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppDeletePersistentForce
	#define EXT_AppDeletePersistentForce
	#define GET_AppDeletePersistentForce(fl)  CAL_CMGETAPI( "AppDeletePersistentForce" ) 
	#define CAL_AppDeletePersistentForce  AppDeletePersistentForce
	#define CHK_AppDeletePersistentForce  TRUE
	#define EXP_AppDeletePersistentForce  CAL_CMEXPAPI( "AppDeletePersistentForce" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPFORCE_EXTERNAL)
	#define USE_AppDeletePersistentForce
	#define EXT_AppDeletePersistentForce
	#define GET_AppDeletePersistentForce(fl)  CAL_CMGETAPI( "AppDeletePersistentForce" ) 
	#define CAL_AppDeletePersistentForce  AppDeletePersistentForce
	#define CHK_AppDeletePersistentForce  TRUE
	#define EXP_AppDeletePersistentForce  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDeletePersistentForce", (RTS_UINTPTR)AppDeletePersistentForce, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppForceAppDeletePersistentForce
	#define EXT_CmpAppForceAppDeletePersistentForce
	#define GET_CmpAppForceAppDeletePersistentForce  ERR_OK
	#define CAL_CmpAppForceAppDeletePersistentForce pICmpAppForce->IAppDeletePersistentForce
	#define CHK_CmpAppForceAppDeletePersistentForce (pICmpAppForce != NULL)
	#define EXP_CmpAppForceAppDeletePersistentForce  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppDeletePersistentForce
	#define EXT_AppDeletePersistentForce
	#define GET_AppDeletePersistentForce(fl)  CAL_CMGETAPI( "AppDeletePersistentForce" ) 
	#define CAL_AppDeletePersistentForce pICmpAppForce->IAppDeletePersistentForce
	#define CHK_AppDeletePersistentForce (pICmpAppForce != NULL)
	#define EXP_AppDeletePersistentForce  CAL_CMEXPAPI( "AppDeletePersistentForce" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppDeletePersistentForce  PFAPPDELETEPERSISTENTFORCE pfAppDeletePersistentForce;
	#define EXT_AppDeletePersistentForce  extern PFAPPDELETEPERSISTENTFORCE pfAppDeletePersistentForce;
	#define GET_AppDeletePersistentForce(fl)  s_pfCMGetAPI2( "AppDeletePersistentForce", (RTS_VOID_FCTPTR *)&pfAppDeletePersistentForce, (fl), 0, 0)
	#define CAL_AppDeletePersistentForce  pfAppDeletePersistentForce
	#define CHK_AppDeletePersistentForce  (pfAppDeletePersistentForce != NULL)
	#define EXP_AppDeletePersistentForce  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDeletePersistentForce", (RTS_UINTPTR)AppDeletePersistentForce, 0, 0) 
#endif




/**
 * <description>Handler for all force services</description>
 * <param name="ulChannelId" type="IN">ChannelID of the communication channel</param>
 * <param name="pHeaderTag" type="IN">Pointer to the service header</param>
 * <param name="pduData" type="IN">Data unit of the received service</param>
 * <param name="pduSendBuffer" type="IN">Data unit for the service reply</param>
 * <result>Error code:
 *		ERR_OK: Service could be executed successfully.
 *		ERR_NOT_SUPPORTED: Service is not supported
 *		ERR_FAILED: Error during executing service
 * </result>
 */
RTS_RESULT CDECL AppForceServiceHandler2(RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT *pduSendBuffer);
typedef RTS_RESULT (CDECL * PFAPPFORCESERVICEHANDLER2) (RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT *pduSendBuffer);
#if defined(CMPAPPFORCE_NOTIMPLEMENTED) || defined(APPFORCESERVICEHANDLER2_NOTIMPLEMENTED)
	#define USE_AppForceServiceHandler2
	#define EXT_AppForceServiceHandler2
	#define GET_AppForceServiceHandler2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppForceServiceHandler2(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppForceServiceHandler2  FALSE
	#define EXP_AppForceServiceHandler2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppForceServiceHandler2
	#define EXT_AppForceServiceHandler2
	#define GET_AppForceServiceHandler2(fl)  CAL_CMGETAPI( "AppForceServiceHandler2" ) 
	#define CAL_AppForceServiceHandler2  AppForceServiceHandler2
	#define CHK_AppForceServiceHandler2  TRUE
	#define EXP_AppForceServiceHandler2  CAL_CMEXPAPI( "AppForceServiceHandler2" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPFORCE_EXTERNAL)
	#define USE_AppForceServiceHandler2
	#define EXT_AppForceServiceHandler2
	#define GET_AppForceServiceHandler2(fl)  CAL_CMGETAPI( "AppForceServiceHandler2" ) 
	#define CAL_AppForceServiceHandler2  AppForceServiceHandler2
	#define CHK_AppForceServiceHandler2  TRUE
	#define EXP_AppForceServiceHandler2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppForceServiceHandler2", (RTS_UINTPTR)AppForceServiceHandler2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppForceAppForceServiceHandler2
	#define EXT_CmpAppForceAppForceServiceHandler2
	#define GET_CmpAppForceAppForceServiceHandler2  ERR_OK
	#define CAL_CmpAppForceAppForceServiceHandler2 pICmpAppForce->IAppForceServiceHandler2
	#define CHK_CmpAppForceAppForceServiceHandler2 (pICmpAppForce != NULL)
	#define EXP_CmpAppForceAppForceServiceHandler2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppForceServiceHandler2
	#define EXT_AppForceServiceHandler2
	#define GET_AppForceServiceHandler2(fl)  CAL_CMGETAPI( "AppForceServiceHandler2" ) 
	#define CAL_AppForceServiceHandler2 pICmpAppForce->IAppForceServiceHandler2
	#define CHK_AppForceServiceHandler2 (pICmpAppForce != NULL)
	#define EXP_AppForceServiceHandler2  CAL_CMEXPAPI( "AppForceServiceHandler2" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppForceServiceHandler2  PFAPPFORCESERVICEHANDLER2 pfAppForceServiceHandler2;
	#define EXT_AppForceServiceHandler2  extern PFAPPFORCESERVICEHANDLER2 pfAppForceServiceHandler2;
	#define GET_AppForceServiceHandler2(fl)  s_pfCMGetAPI2( "AppForceServiceHandler2", (RTS_VOID_FCTPTR *)&pfAppForceServiceHandler2, (fl), 0, 0)
	#define CAL_AppForceServiceHandler2  pfAppForceServiceHandler2
	#define CHK_AppForceServiceHandler2  (pfAppForceServiceHandler2 != NULL)
	#define EXP_AppForceServiceHandler2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppForceServiceHandler2", (RTS_UINTPTR)AppForceServiceHandler2, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif




typedef struct
{
	IBase_C *pBase;
	PFAPPFORCEINIT IAppForceInit;
 	PFAPPFORCEEXIT IAppForceExit;
 	PFAPPADDFORCEVALUE IAppAddForceValue;
 	PFAPPRELEASEFORCEVALUE IAppReleaseForceValue;
 	PFAPPGETFIRSTFORCE IAppGetFirstForce;
 	PFAPPGETNEXTFORCE IAppGetNextForce;
 	PFAPPRELEASEALLFORCEVALUES IAppReleaseAllForceValues;
 	PFAPPLOADPERSISTENTFORCE IAppLoadPersistentForce;
 	PFAPPCREATEPERSISTENTFORCE IAppCreatePersistentForce;
 	PFAPPDELETEPERSISTENTFORCE IAppDeletePersistentForce;
 	PFAPPFORCESERVICEHANDLER2 IAppForceServiceHandler2;
 } ICmpAppForce_C;

#ifdef CPLUSPLUS
class ICmpAppForce : public IBase
{
	public:
		virtual RTS_RESULT CDECL IAppForceInit(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IAppForceExit(APPLICATION *pApp, int bShutdown) =0;
		virtual RTS_RESULT CDECL IAppAddForceValue(APPLICATION* pApp, VarDataRef *pDataRef, VarValue *pValue) =0;
		virtual RTS_RESULT CDECL IAppReleaseForceValue(APPLICATION* pApp, VarDataRef *pDataRef, int bRestoreValue) =0;
		virtual ForceVarDesc * CDECL IAppGetFirstForce(APPLICATION *pApp, RTS_RESULT *pResult) =0;
		virtual ForceVarDesc * CDECL IAppGetNextForce(APPLICATION *pApp, ForceVarDesc *pPrevForce, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IAppReleaseAllForceValues(APPLICATION* pApp, int bShutdown) =0;
		virtual RTS_RESULT CDECL IAppLoadPersistentForce(APPLICATION* pApp) =0;
		virtual RTS_RESULT CDECL IAppCreatePersistentForce(APPLICATION* pApp) =0;
		virtual RTS_RESULT CDECL IAppDeletePersistentForce(APPLICATION* pApp) =0;
		virtual RTS_RESULT CDECL IAppForceServiceHandler2(RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT *pduSendBuffer) =0;
};
	#ifndef ITF_CmpAppForce
		#define ITF_CmpAppForce static ICmpAppForce *pICmpAppForce = NULL;
	#endif
	#define EXTITF_CmpAppForce
#else	/*CPLUSPLUS*/
	typedef ICmpAppForce_C		ICmpAppForce;
	#ifndef ITF_CmpAppForce
		#define ITF_CmpAppForce
	#endif
	#define EXTITF_CmpAppForce
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPAPPFORCEITF_H_*/
