 /**
 * <interfacename>SysNativeControl</interfacename>
 * <description> 
 *	<p>The SysNativeControl interface brings native controls into the visualization. All
	controls are created as child controls of the targetvisualization. </p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSNATIVECONTROLITF_H_
#define _SYSNATIVECONTROLITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "SysGraphicBase.h"

#define NATIVE_CONTROL_SNCF_SHOW							0x00000001
#define NATIVE_CONTROL_SNCF_HIDE							0x00000002
#define NATIVE_CONTROL_SNCF_HIDE_AND_DESTROY				0x00000004

#define NATIVE_CONTROL_CNCMF_WITHOUT_RESULT					0x00000001
#define NATIVE_CONTROL_CNCMF_WITH_RESULT					0x00000002
#define NATIVE_CONTROL_CNCMF_DYNAMIC_MEMORY_ALLOCATED		0x00000004

/**
 * <category>Static defines</category>
 * <description>Number of static native control instances</description>
 */
#ifndef NUM_OF_STATIC_NATIVE_CONTROLS
	#define NUM_OF_STATIC_NATIVE_CONTROLS	4
#endif

typedef struct tagNativeControlParam
{
	RTS_UI32 dwType;
	RTS_SIZE dwSize;
	RTS_UI32 dwFlags;
	RTS_HANDLE hData;
} NativeControlParam;

/**
 * <category>Native control create description</category>
 * <description>
 *	This structure describes a native control that has to be created. 
 * </description>
 * <element name="pszControlName" type="IN">The name/title of the window that shall be created.</element>
 * <element name="hParentWindow" type="IN">If this member equals RTS_INVALID_HANDLE, than the window will be a
 *	top level window. In this case it must do cyclic checks whether it is still alive. For this cyclic checking
 *	it has to do the following steps every second or so:
 *	<ul>
 *	<li>InternCallCallback(hWindow, WCB_CYCLIC, 0, 0);		// allow other components to react to the window</li> 
 *	<li>if (!InternWindowStillAlive(hWindow)) DoSomethingToCloseTheWindow(hWindow);	// check if the window has to be closed and close it if needed</li>
 *	</ul>
 *	To make this mechanism work correctly it is necessary that each top level window
 *	registers itself within the platform independent part using the method InterWindowRegister.
 *	</element>
 * <element name="prWindow" type="IN">The position where the native control should be opened.</element>
 * <element name="ulCreationFlags" type="IN">Additional flags affecting
 *	the creation of the native control.</element>
 */
typedef struct
{
	char* pszControlName;
	RTS_HANDLE hParentWindow;
	RTS_Rectangle* prWindow;
	RTS_UI16 ulType;
	RTS_UI32 ulCreationFlags;
} SysNativeControlCreate_Struct;

/**
 * <category>Event parameter</category>
 * <element name="pCreateInfo" type="IN_OUT">The information structure that is relevant for the creation of the current control</element>
 * <element name="bHandled" type="OUT">Signal whether the call was executed</element>
 * <element name="hControl" type="OUT">The handle to the created control</element>
 */
typedef struct
{
	SysNativeControlCreate_Struct* pCreateInfo;
	RTS_BOOL bHandled;
	RTS_HANDLE hControl;
} EVTPARAM_SysNativeControlCreate;
#define EVTPARAMID_SysNativeControlCreate					0x0001
#define EVTVERSION_SysNativeControlCreate					0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when the method SysNativeControlCreate is called. </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_SysNativeControlCreate</param>
 */
#define EVT_SysNativeControlCreate					MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>This additional event is sent when the method SysNativeControlCreate is called.
 * It returns instead of an operation system handle to a native control a pointer to a
 * SysNativeControlCustom structure.
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_SysNativeControlCreate</param>
 */
#define EVT_SysNativeControlCreate2					MAKE_EVENTID(EVTCLASS_INFO, 6)

#define EVTPARAMID_SysNativeControlCreate2					0x0006
#define EVTVERSION_SysNativeControlCreate2					0x0001

/* Data types forward declarations */
typedef struct tagSysNativeControlCustom SysNativeControlCustom;

/**
 * <category>parameter</category>
 * <description>A pointer to this structure is returned by the event EVT_SysNativeControlCreate2.
 * </description>
 * <element name="hControl">The handle to the control, that has been created</element>
 * <element name="uiControlType">An int representing the type of the control</element>
 * <element name="pfMove">A pointer to the callback function, that has to be called if the native control has to be moved</element>
 * <element name="pfCall">A pointer to the callback function, that has to be called if a method of the native control has to be called</element>
 * <element name="pfShow">A pointer to the callback function, that has to be called if the native control has to be set visible</element>
 * <element name="pfDestroy">A pointer to the callback function, that has to be called if the native control has to be destroyed</element>
 */
struct tagSysNativeControlCustom
{
	RTS_HANDLE hControl;
	RTS_UI16   uiControlType;
	RTS_RESULT (*pfMove)(SysNativeControlCustom*, ...);
	RTS_RESULT (*pfCall)(SysNativeControlCustom*, ...);
	RTS_RESULT (*pfShow)(SysNativeControlCustom*, ...);
	RTS_RESULT (*pfDestroy)(SysNativeControlCustom*, ...);
};

/**
 * <category>Event parameter</category>
 * <element name="hControl" type="IN_OUT">The handle to the control which should be destroyed</element>
 * <element name="bHandled" type="OUT">Signal whether the call was executed</element>
 * <element name="hResult" type="OUT">The result value</element>
 */
typedef struct
{
	RTS_HANDLE hControl;
	RTS_BOOL bHandled;
	RTS_RESULT hResult;
} EVTPARAM_SysNativeControlDestroy;
#define EVTPARAMID_SysNativeControlDestroy					0x0002
#define EVTVERSION_SysNativeControlDestroy					0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when the method SysNativeControlDestroy is called. </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_SysNativeControlDestroy</param>
 */
#define EVT_SysNativeControlDestroy					MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Event parameter</category>
 * <element name="hControl" type="IN_OUT">The handle to the control which should be called</element>
 * <element name="pszMethodName" type="IN_OUT">The name of the method which should be called</element>
 * <element name="params" type="IN_OUT">The parameters for the method call</element>
 * <element name="iParamCount" type="IN_OUT">The parameter count</element>
 * <element name="bHandled" type="OUT">Signal whether the call was executed</element>
 * <element name="hResult" type="OUT">The result value</element>
 */
typedef struct
{
	RTS_HANDLE hControl;
	char* pszMethodName;
	NativeControlParam* params;
	RTS_SIZE iParamCount;
	NativeControlParam* pResult;
	RTS_BOOL bHandled;
	RTS_RESULT hResult;
} EVTPARAM_SysNativeControlCallMethod;
#define EVTPARAMID_SysNativeControlCallMethod					0x0003
#define EVTVERSION_SysNativeControlCallMethod					0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when the method SysNativeControlCallMethod is called. </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_SysNativeControlCallMethod</param>
 */
#define EVT_SysNativeControlCallMethod					MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Event parameter</category>
 * <element name="hControl" type="IN_OUT">The handle to the control which should be moved</element>
 * <element name="prRect" type="IN_OUT">The new position rectangle</element>
 * <element name="bHandled" type="OUT">Signal whether the call was executed</element>
 * <element name="hResult" type="OUT">The result value</element>
 */
typedef struct
{
	RTS_HANDLE hControl;
	RTS_Rectangle* prRect;
	RTS_BOOL bHandled;
	RTS_RESULT hResult;
} EVTPARAM_SysNativeControlMove;
#define EVTPARAMID_SysNativeControlMove					0x0004
#define EVTVERSION_SysNativeControlMove					0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when the method SysNativeControlMove is called. </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_SysNativeControlMove</param>
 */
#define EVT_SysNativeControlMove					MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Event parameter</category>
 * <element name="hControl" type="IN_OUT">The handle to the control which should be shown</element>
 * <element name="ulFlags" type="IN_OUT">The flags NATIVE_CONTROL_SHOW or NATIVE_CONTROL_HIDE</element>
 * <element name="bHandled" type="OUT">Signal whether the call was executed</element>
 * <element name="hResult" type="OUT">The result value</element>
 */
typedef struct
{
	RTS_HANDLE hControl;
	RTS_UI32 ulFlags;
	RTS_BOOL bHandled;
	RTS_RESULT hResult;
} EVTPARAM_SysNativeControlShow;
#define EVTPARAMID_SysNativeControlShow					0x0005
#define EVTVERSION_SysNativeControlShow					0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when the method SysNativeControlShow is called. </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_SysNativeControlShow</param>
 */
#define EVT_SysNativeControlShow					MAKE_EVENTID(EVTCLASS_INFO, 5)

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysNativeControlOSInit(INIT_STRUCT *pInit);
int CDECL SysNativeControlOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *	Function to create a native control
 * </description>
 * <param name="pCreate" type="IN">The structure that describes the native control that has to be created.</param>
 * <param name="ulParam" type="IN">A parameter that is dependant of the type of the native control. Might be a 
 *	pointer pointing to a structure with further information for the creation of this native control. In case
 *	of a pointer, this pointer must be valid until the control is destroyed.</param>
 * <param name="pResult" type="OUT">Optionally returns an error code</param>
 * <result>The handle to the native display context or <see>RTS_INVALID_HANDLE</see> in case of errors.</result>
 */
RTS_HANDLE CDECL SysNativeControlCreate(SysNativeControlCreate_Struct* pCreate, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSNATIVECONTROLCREATE) (SysNativeControlCreate_Struct* pCreate, RTS_RESULT *pResult);
#if defined(SYSNATIVECONTROL_NOTIMPLEMENTED) || defined(SYSNATIVECONTROLCREATE_NOTIMPLEMENTED)
	#define USE_SysNativeControlCreate
	#define EXT_SysNativeControlCreate
	#define GET_SysNativeControlCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysNativeControlCreate(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysNativeControlCreate  FALSE
	#define EXP_SysNativeControlCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysNativeControlCreate
	#define EXT_SysNativeControlCreate
	#define GET_SysNativeControlCreate(fl)  CAL_CMGETAPI( "SysNativeControlCreate" ) 
	#define CAL_SysNativeControlCreate  SysNativeControlCreate
	#define CHK_SysNativeControlCreate  TRUE
	#define EXP_SysNativeControlCreate  CAL_CMEXPAPI( "SysNativeControlCreate" ) 
#elif defined(MIXED_LINK) && !defined(SYSNATIVECONTROL_EXTERNAL)
	#define USE_SysNativeControlCreate
	#define EXT_SysNativeControlCreate
	#define GET_SysNativeControlCreate(fl)  CAL_CMGETAPI( "SysNativeControlCreate" ) 
	#define CAL_SysNativeControlCreate  SysNativeControlCreate
	#define CHK_SysNativeControlCreate  TRUE
	#define EXP_SysNativeControlCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlCreate", (RTS_UINTPTR)SysNativeControlCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysNativeControlSysNativeControlCreate
	#define EXT_SysNativeControlSysNativeControlCreate
	#define GET_SysNativeControlSysNativeControlCreate  ERR_OK
	#define CAL_SysNativeControlSysNativeControlCreate pISysNativeControl->ISysNativeControlCreate
	#define CHK_SysNativeControlSysNativeControlCreate (pISysNativeControl != NULL)
	#define EXP_SysNativeControlSysNativeControlCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysNativeControlCreate
	#define EXT_SysNativeControlCreate
	#define GET_SysNativeControlCreate(fl)  CAL_CMGETAPI( "SysNativeControlCreate" ) 
	#define CAL_SysNativeControlCreate pISysNativeControl->ISysNativeControlCreate
	#define CHK_SysNativeControlCreate (pISysNativeControl != NULL)
	#define EXP_SysNativeControlCreate  CAL_CMEXPAPI( "SysNativeControlCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysNativeControlCreate  PFSYSNATIVECONTROLCREATE pfSysNativeControlCreate;
	#define EXT_SysNativeControlCreate  extern PFSYSNATIVECONTROLCREATE pfSysNativeControlCreate;
	#define GET_SysNativeControlCreate(fl)  s_pfCMGetAPI2( "SysNativeControlCreate", (RTS_VOID_FCTPTR *)&pfSysNativeControlCreate, (fl), 0, 0)
	#define CAL_SysNativeControlCreate  pfSysNativeControlCreate
	#define CHK_SysNativeControlCreate  (pfSysNativeControlCreate != NULL)
	#define EXP_SysNativeControlCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlCreate", (RTS_UINTPTR)SysNativeControlCreate, 0, 0) 
#endif



RTS_HANDLE CDECL SysNativeControlCreate_(SysNativeControlCreate_Struct* pCreate, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSNATIVECONTROLCREATE_) (SysNativeControlCreate_Struct* pCreate, RTS_RESULT *pResult);
#if defined(SYSNATIVECONTROL_NOTIMPLEMENTED) || defined(SYSNATIVECONTROLCREATE__NOTIMPLEMENTED)
	#define USE_SysNativeControlCreate_
	#define EXT_SysNativeControlCreate_
	#define GET_SysNativeControlCreate_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysNativeControlCreate_(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysNativeControlCreate_  FALSE
	#define EXP_SysNativeControlCreate_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysNativeControlCreate_
	#define EXT_SysNativeControlCreate_
	#define GET_SysNativeControlCreate_(fl)  CAL_CMGETAPI( "SysNativeControlCreate_" ) 
	#define CAL_SysNativeControlCreate_  SysNativeControlCreate_
	#define CHK_SysNativeControlCreate_  TRUE
	#define EXP_SysNativeControlCreate_  CAL_CMEXPAPI( "SysNativeControlCreate_" ) 
#elif defined(MIXED_LINK) && !defined(SYSNATIVECONTROL_EXTERNAL)
	#define USE_SysNativeControlCreate_
	#define EXT_SysNativeControlCreate_
	#define GET_SysNativeControlCreate_(fl)  CAL_CMGETAPI( "SysNativeControlCreate_" ) 
	#define CAL_SysNativeControlCreate_  SysNativeControlCreate_
	#define CHK_SysNativeControlCreate_  TRUE
	#define EXP_SysNativeControlCreate_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlCreate_", (RTS_UINTPTR)SysNativeControlCreate_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysNativeControlSysNativeControlCreate_
	#define EXT_SysNativeControlSysNativeControlCreate_
	#define GET_SysNativeControlSysNativeControlCreate_  ERR_OK
	#define CAL_SysNativeControlSysNativeControlCreate_ pISysNativeControl->ISysNativeControlCreate_
	#define CHK_SysNativeControlSysNativeControlCreate_ (pISysNativeControl != NULL)
	#define EXP_SysNativeControlSysNativeControlCreate_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysNativeControlCreate_
	#define EXT_SysNativeControlCreate_
	#define GET_SysNativeControlCreate_(fl)  CAL_CMGETAPI( "SysNativeControlCreate_" ) 
	#define CAL_SysNativeControlCreate_ pISysNativeControl->ISysNativeControlCreate_
	#define CHK_SysNativeControlCreate_ (pISysNativeControl != NULL)
	#define EXP_SysNativeControlCreate_  CAL_CMEXPAPI( "SysNativeControlCreate_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysNativeControlCreate_  PFSYSNATIVECONTROLCREATE_ pfSysNativeControlCreate_;
	#define EXT_SysNativeControlCreate_  extern PFSYSNATIVECONTROLCREATE_ pfSysNativeControlCreate_;
	#define GET_SysNativeControlCreate_(fl)  s_pfCMGetAPI2( "SysNativeControlCreate_", (RTS_VOID_FCTPTR *)&pfSysNativeControlCreate_, (fl), 0, 0)
	#define CAL_SysNativeControlCreate_  pfSysNativeControlCreate_
	#define CHK_SysNativeControlCreate_  (pfSysNativeControlCreate_ != NULL)
	#define EXP_SysNativeControlCreate_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlCreate_", (RTS_UINTPTR)SysNativeControlCreate_, 0, 0) 
#endif




/**
 * <description>
 *	Function to destroy a native control
 * </description>
 * <param name="hControl" type="IN">Handle to the native control</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysNativeControlDestroy(RTS_HANDLE hControl);
typedef RTS_RESULT (CDECL * PFSYSNATIVECONTROLDESTROY) (RTS_HANDLE hControl);
#if defined(SYSNATIVECONTROL_NOTIMPLEMENTED) || defined(SYSNATIVECONTROLDESTROY_NOTIMPLEMENTED)
	#define USE_SysNativeControlDestroy
	#define EXT_SysNativeControlDestroy
	#define GET_SysNativeControlDestroy(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysNativeControlDestroy(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysNativeControlDestroy  FALSE
	#define EXP_SysNativeControlDestroy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysNativeControlDestroy
	#define EXT_SysNativeControlDestroy
	#define GET_SysNativeControlDestroy(fl)  CAL_CMGETAPI( "SysNativeControlDestroy" ) 
	#define CAL_SysNativeControlDestroy  SysNativeControlDestroy
	#define CHK_SysNativeControlDestroy  TRUE
	#define EXP_SysNativeControlDestroy  CAL_CMEXPAPI( "SysNativeControlDestroy" ) 
#elif defined(MIXED_LINK) && !defined(SYSNATIVECONTROL_EXTERNAL)
	#define USE_SysNativeControlDestroy
	#define EXT_SysNativeControlDestroy
	#define GET_SysNativeControlDestroy(fl)  CAL_CMGETAPI( "SysNativeControlDestroy" ) 
	#define CAL_SysNativeControlDestroy  SysNativeControlDestroy
	#define CHK_SysNativeControlDestroy  TRUE
	#define EXP_SysNativeControlDestroy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlDestroy", (RTS_UINTPTR)SysNativeControlDestroy, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysNativeControlSysNativeControlDestroy
	#define EXT_SysNativeControlSysNativeControlDestroy
	#define GET_SysNativeControlSysNativeControlDestroy  ERR_OK
	#define CAL_SysNativeControlSysNativeControlDestroy(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlDestroy() : ((ISysNativeControl*)p0)->ISysNativeControlDestroy())
	#define CHK_SysNativeControlSysNativeControlDestroy  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlSysNativeControlDestroy  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysNativeControlDestroy
	#define EXT_SysNativeControlDestroy
	#define GET_SysNativeControlDestroy(fl)  CAL_CMGETAPI( "SysNativeControlDestroy" ) 
	#define CAL_SysNativeControlDestroy(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlDestroy() : ((ISysNativeControl*)p0)->ISysNativeControlDestroy())
	#define CHK_SysNativeControlDestroy  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlDestroy  CAL_CMEXPAPI( "SysNativeControlDestroy" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysNativeControlDestroy  PFSYSNATIVECONTROLDESTROY pfSysNativeControlDestroy;
	#define EXT_SysNativeControlDestroy  extern PFSYSNATIVECONTROLDESTROY pfSysNativeControlDestroy;
	#define GET_SysNativeControlDestroy(fl)  s_pfCMGetAPI2( "SysNativeControlDestroy", (RTS_VOID_FCTPTR *)&pfSysNativeControlDestroy, (fl), 0, 0)
	#define CAL_SysNativeControlDestroy  pfSysNativeControlDestroy
	#define CHK_SysNativeControlDestroy  (pfSysNativeControlDestroy != NULL)
	#define EXP_SysNativeControlDestroy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlDestroy", (RTS_UINTPTR)SysNativeControlDestroy, 0, 0) 
#endif



RTS_RESULT CDECL SysNativeControlDestroy_(RTS_HANDLE hControl);
typedef RTS_RESULT (CDECL * PFSYSNATIVECONTROLDESTROY_) (RTS_HANDLE hControl);
#if defined(SYSNATIVECONTROL_NOTIMPLEMENTED) || defined(SYSNATIVECONTROLDESTROY__NOTIMPLEMENTED)
	#define USE_SysNativeControlDestroy_
	#define EXT_SysNativeControlDestroy_
	#define GET_SysNativeControlDestroy_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysNativeControlDestroy_(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysNativeControlDestroy_  FALSE
	#define EXP_SysNativeControlDestroy_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysNativeControlDestroy_
	#define EXT_SysNativeControlDestroy_
	#define GET_SysNativeControlDestroy_(fl)  CAL_CMGETAPI( "SysNativeControlDestroy_" ) 
	#define CAL_SysNativeControlDestroy_  SysNativeControlDestroy_
	#define CHK_SysNativeControlDestroy_  TRUE
	#define EXP_SysNativeControlDestroy_  CAL_CMEXPAPI( "SysNativeControlDestroy_" ) 
#elif defined(MIXED_LINK) && !defined(SYSNATIVECONTROL_EXTERNAL)
	#define USE_SysNativeControlDestroy_
	#define EXT_SysNativeControlDestroy_
	#define GET_SysNativeControlDestroy_(fl)  CAL_CMGETAPI( "SysNativeControlDestroy_" ) 
	#define CAL_SysNativeControlDestroy_  SysNativeControlDestroy_
	#define CHK_SysNativeControlDestroy_  TRUE
	#define EXP_SysNativeControlDestroy_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlDestroy_", (RTS_UINTPTR)SysNativeControlDestroy_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysNativeControlSysNativeControlDestroy_
	#define EXT_SysNativeControlSysNativeControlDestroy_
	#define GET_SysNativeControlSysNativeControlDestroy_  ERR_OK
	#define CAL_SysNativeControlSysNativeControlDestroy_(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlDestroy_() : ((ISysNativeControl*)p0)->ISysNativeControlDestroy_())
	#define CHK_SysNativeControlSysNativeControlDestroy_  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlSysNativeControlDestroy_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysNativeControlDestroy_
	#define EXT_SysNativeControlDestroy_
	#define GET_SysNativeControlDestroy_(fl)  CAL_CMGETAPI( "SysNativeControlDestroy_" ) 
	#define CAL_SysNativeControlDestroy_(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlDestroy_() : ((ISysNativeControl*)p0)->ISysNativeControlDestroy_())
	#define CHK_SysNativeControlDestroy_  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlDestroy_  CAL_CMEXPAPI( "SysNativeControlDestroy_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysNativeControlDestroy_  PFSYSNATIVECONTROLDESTROY_ pfSysNativeControlDestroy_;
	#define EXT_SysNativeControlDestroy_  extern PFSYSNATIVECONTROLDESTROY_ pfSysNativeControlDestroy_;
	#define GET_SysNativeControlDestroy_(fl)  s_pfCMGetAPI2( "SysNativeControlDestroy_", (RTS_VOID_FCTPTR *)&pfSysNativeControlDestroy_, (fl), 0, 0)
	#define CAL_SysNativeControlDestroy_  pfSysNativeControlDestroy_
	#define CHK_SysNativeControlDestroy_  (pfSysNativeControlDestroy_ != NULL)
	#define EXP_SysNativeControlDestroy_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlDestroy_", (RTS_UINTPTR)SysNativeControlDestroy_, 0, 0) 
#endif




/**
 * <description>
 *	Function to destroy a native control
 * </description>
 * <param name="hControl" type="IN">Handle to the native control</param>
 * <param name="pszMethodName" type="IN">The name of the method call</param>
 * <param name="params" type="IN">The parameters for the method call</param>
 * <param name="iParamCount" type="IN">The parameter count</param>
 * <param name="pResult" type="IN">The result parameter</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysNativeControlCallMethod(RTS_HANDLE hControl, char* pszMethodName, NativeControlParam* params, RTS_SIZE iParamCount, NativeControlParam* pResult);
typedef RTS_RESULT (CDECL * PFSYSNATIVECONTROLCALLMETHOD) (RTS_HANDLE hControl, char* pszMethodName, NativeControlParam* params, RTS_SIZE iParamCount, NativeControlParam* pResult);
#if defined(SYSNATIVECONTROL_NOTIMPLEMENTED) || defined(SYSNATIVECONTROLCALLMETHOD_NOTIMPLEMENTED)
	#define USE_SysNativeControlCallMethod
	#define EXT_SysNativeControlCallMethod
	#define GET_SysNativeControlCallMethod(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysNativeControlCallMethod(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysNativeControlCallMethod  FALSE
	#define EXP_SysNativeControlCallMethod  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysNativeControlCallMethod
	#define EXT_SysNativeControlCallMethod
	#define GET_SysNativeControlCallMethod(fl)  CAL_CMGETAPI( "SysNativeControlCallMethod" ) 
	#define CAL_SysNativeControlCallMethod  SysNativeControlCallMethod
	#define CHK_SysNativeControlCallMethod  TRUE
	#define EXP_SysNativeControlCallMethod  CAL_CMEXPAPI( "SysNativeControlCallMethod" ) 
#elif defined(MIXED_LINK) && !defined(SYSNATIVECONTROL_EXTERNAL)
	#define USE_SysNativeControlCallMethod
	#define EXT_SysNativeControlCallMethod
	#define GET_SysNativeControlCallMethod(fl)  CAL_CMGETAPI( "SysNativeControlCallMethod" ) 
	#define CAL_SysNativeControlCallMethod  SysNativeControlCallMethod
	#define CHK_SysNativeControlCallMethod  TRUE
	#define EXP_SysNativeControlCallMethod  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlCallMethod", (RTS_UINTPTR)SysNativeControlCallMethod, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysNativeControlSysNativeControlCallMethod
	#define EXT_SysNativeControlSysNativeControlCallMethod
	#define GET_SysNativeControlSysNativeControlCallMethod  ERR_OK
	#define CAL_SysNativeControlSysNativeControlCallMethod(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlCallMethod(p1,p2,p3,p4) : ((ISysNativeControl*)p0)->ISysNativeControlCallMethod(p1,p2,p3,p4))
	#define CHK_SysNativeControlSysNativeControlCallMethod  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlSysNativeControlCallMethod  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysNativeControlCallMethod
	#define EXT_SysNativeControlCallMethod
	#define GET_SysNativeControlCallMethod(fl)  CAL_CMGETAPI( "SysNativeControlCallMethod" ) 
	#define CAL_SysNativeControlCallMethod(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlCallMethod(p1,p2,p3,p4) : ((ISysNativeControl*)p0)->ISysNativeControlCallMethod(p1,p2,p3,p4))
	#define CHK_SysNativeControlCallMethod  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlCallMethod  CAL_CMEXPAPI( "SysNativeControlCallMethod" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysNativeControlCallMethod  PFSYSNATIVECONTROLCALLMETHOD pfSysNativeControlCallMethod;
	#define EXT_SysNativeControlCallMethod  extern PFSYSNATIVECONTROLCALLMETHOD pfSysNativeControlCallMethod;
	#define GET_SysNativeControlCallMethod(fl)  s_pfCMGetAPI2( "SysNativeControlCallMethod", (RTS_VOID_FCTPTR *)&pfSysNativeControlCallMethod, (fl), 0, 0)
	#define CAL_SysNativeControlCallMethod  pfSysNativeControlCallMethod
	#define CHK_SysNativeControlCallMethod  (pfSysNativeControlCallMethod != NULL)
	#define EXP_SysNativeControlCallMethod  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlCallMethod", (RTS_UINTPTR)SysNativeControlCallMethod, 0, 0) 
#endif



RTS_RESULT CDECL SysNativeControlCallMethod_(RTS_HANDLE hControl, char* pszMethodName, NativeControlParam* params, RTS_SIZE iParamCount, NativeControlParam* pResult);
typedef RTS_RESULT (CDECL * PFSYSNATIVECONTROLCALLMETHOD_) (RTS_HANDLE hControl, char* pszMethodName, NativeControlParam* params, RTS_SIZE iParamCount, NativeControlParam* pResult);
#if defined(SYSNATIVECONTROL_NOTIMPLEMENTED) || defined(SYSNATIVECONTROLCALLMETHOD__NOTIMPLEMENTED)
	#define USE_SysNativeControlCallMethod_
	#define EXT_SysNativeControlCallMethod_
	#define GET_SysNativeControlCallMethod_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysNativeControlCallMethod_(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysNativeControlCallMethod_  FALSE
	#define EXP_SysNativeControlCallMethod_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysNativeControlCallMethod_
	#define EXT_SysNativeControlCallMethod_
	#define GET_SysNativeControlCallMethod_(fl)  CAL_CMGETAPI( "SysNativeControlCallMethod_" ) 
	#define CAL_SysNativeControlCallMethod_  SysNativeControlCallMethod_
	#define CHK_SysNativeControlCallMethod_  TRUE
	#define EXP_SysNativeControlCallMethod_  CAL_CMEXPAPI( "SysNativeControlCallMethod_" ) 
#elif defined(MIXED_LINK) && !defined(SYSNATIVECONTROL_EXTERNAL)
	#define USE_SysNativeControlCallMethod_
	#define EXT_SysNativeControlCallMethod_
	#define GET_SysNativeControlCallMethod_(fl)  CAL_CMGETAPI( "SysNativeControlCallMethod_" ) 
	#define CAL_SysNativeControlCallMethod_  SysNativeControlCallMethod_
	#define CHK_SysNativeControlCallMethod_  TRUE
	#define EXP_SysNativeControlCallMethod_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlCallMethod_", (RTS_UINTPTR)SysNativeControlCallMethod_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysNativeControlSysNativeControlCallMethod_
	#define EXT_SysNativeControlSysNativeControlCallMethod_
	#define GET_SysNativeControlSysNativeControlCallMethod_  ERR_OK
	#define CAL_SysNativeControlSysNativeControlCallMethod_(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlCallMethod_(p1,p2,p3,p4) : ((ISysNativeControl*)p0)->ISysNativeControlCallMethod_(p1,p2,p3,p4))
	#define CHK_SysNativeControlSysNativeControlCallMethod_  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlSysNativeControlCallMethod_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysNativeControlCallMethod_
	#define EXT_SysNativeControlCallMethod_
	#define GET_SysNativeControlCallMethod_(fl)  CAL_CMGETAPI( "SysNativeControlCallMethod_" ) 
	#define CAL_SysNativeControlCallMethod_(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlCallMethod_(p1,p2,p3,p4) : ((ISysNativeControl*)p0)->ISysNativeControlCallMethod_(p1,p2,p3,p4))
	#define CHK_SysNativeControlCallMethod_  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlCallMethod_  CAL_CMEXPAPI( "SysNativeControlCallMethod_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysNativeControlCallMethod_  PFSYSNATIVECONTROLCALLMETHOD_ pfSysNativeControlCallMethod_;
	#define EXT_SysNativeControlCallMethod_  extern PFSYSNATIVECONTROLCALLMETHOD_ pfSysNativeControlCallMethod_;
	#define GET_SysNativeControlCallMethod_(fl)  s_pfCMGetAPI2( "SysNativeControlCallMethod_", (RTS_VOID_FCTPTR *)&pfSysNativeControlCallMethod_, (fl), 0, 0)
	#define CAL_SysNativeControlCallMethod_  pfSysNativeControlCallMethod_
	#define CHK_SysNativeControlCallMethod_  (pfSysNativeControlCallMethod_ != NULL)
	#define EXP_SysNativeControlCallMethod_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlCallMethod_", (RTS_UINTPTR)SysNativeControlCallMethod_, 0, 0) 
#endif




/**
 * <description>
 *	Function to destroy a native control
 * </description>
 * <param name="hControl" type="IN">Handle to the native control</param>
 * <param name="pRect" type="IN">The new position</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysNativeControlMove(RTS_HANDLE hControl, RTS_Rectangle* pRect);
typedef RTS_RESULT (CDECL * PFSYSNATIVECONTROLMOVE) (RTS_HANDLE hControl, RTS_Rectangle* pRect);
#if defined(SYSNATIVECONTROL_NOTIMPLEMENTED) || defined(SYSNATIVECONTROLMOVE_NOTIMPLEMENTED)
	#define USE_SysNativeControlMove
	#define EXT_SysNativeControlMove
	#define GET_SysNativeControlMove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysNativeControlMove(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysNativeControlMove  FALSE
	#define EXP_SysNativeControlMove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysNativeControlMove
	#define EXT_SysNativeControlMove
	#define GET_SysNativeControlMove(fl)  CAL_CMGETAPI( "SysNativeControlMove" ) 
	#define CAL_SysNativeControlMove  SysNativeControlMove
	#define CHK_SysNativeControlMove  TRUE
	#define EXP_SysNativeControlMove  CAL_CMEXPAPI( "SysNativeControlMove" ) 
#elif defined(MIXED_LINK) && !defined(SYSNATIVECONTROL_EXTERNAL)
	#define USE_SysNativeControlMove
	#define EXT_SysNativeControlMove
	#define GET_SysNativeControlMove(fl)  CAL_CMGETAPI( "SysNativeControlMove" ) 
	#define CAL_SysNativeControlMove  SysNativeControlMove
	#define CHK_SysNativeControlMove  TRUE
	#define EXP_SysNativeControlMove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlMove", (RTS_UINTPTR)SysNativeControlMove, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysNativeControlSysNativeControlMove
	#define EXT_SysNativeControlSysNativeControlMove
	#define GET_SysNativeControlSysNativeControlMove  ERR_OK
	#define CAL_SysNativeControlSysNativeControlMove(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlMove(p1) : ((ISysNativeControl*)p0)->ISysNativeControlMove(p1))
	#define CHK_SysNativeControlSysNativeControlMove  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlSysNativeControlMove  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysNativeControlMove
	#define EXT_SysNativeControlMove
	#define GET_SysNativeControlMove(fl)  CAL_CMGETAPI( "SysNativeControlMove" ) 
	#define CAL_SysNativeControlMove(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlMove(p1) : ((ISysNativeControl*)p0)->ISysNativeControlMove(p1))
	#define CHK_SysNativeControlMove  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlMove  CAL_CMEXPAPI( "SysNativeControlMove" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysNativeControlMove  PFSYSNATIVECONTROLMOVE pfSysNativeControlMove;
	#define EXT_SysNativeControlMove  extern PFSYSNATIVECONTROLMOVE pfSysNativeControlMove;
	#define GET_SysNativeControlMove(fl)  s_pfCMGetAPI2( "SysNativeControlMove", (RTS_VOID_FCTPTR *)&pfSysNativeControlMove, (fl), 0, 0)
	#define CAL_SysNativeControlMove  pfSysNativeControlMove
	#define CHK_SysNativeControlMove  (pfSysNativeControlMove != NULL)
	#define EXP_SysNativeControlMove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlMove", (RTS_UINTPTR)SysNativeControlMove, 0, 0) 
#endif



RTS_RESULT CDECL SysNativeControlMove_(RTS_HANDLE hControl, RTS_Rectangle* pRect);
typedef RTS_RESULT (CDECL * PFSYSNATIVECONTROLMOVE_) (RTS_HANDLE hControl, RTS_Rectangle* pRect);
#if defined(SYSNATIVECONTROL_NOTIMPLEMENTED) || defined(SYSNATIVECONTROLMOVE__NOTIMPLEMENTED)
	#define USE_SysNativeControlMove_
	#define EXT_SysNativeControlMove_
	#define GET_SysNativeControlMove_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysNativeControlMove_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysNativeControlMove_  FALSE
	#define EXP_SysNativeControlMove_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysNativeControlMove_
	#define EXT_SysNativeControlMove_
	#define GET_SysNativeControlMove_(fl)  CAL_CMGETAPI( "SysNativeControlMove_" ) 
	#define CAL_SysNativeControlMove_  SysNativeControlMove_
	#define CHK_SysNativeControlMove_  TRUE
	#define EXP_SysNativeControlMove_  CAL_CMEXPAPI( "SysNativeControlMove_" ) 
#elif defined(MIXED_LINK) && !defined(SYSNATIVECONTROL_EXTERNAL)
	#define USE_SysNativeControlMove_
	#define EXT_SysNativeControlMove_
	#define GET_SysNativeControlMove_(fl)  CAL_CMGETAPI( "SysNativeControlMove_" ) 
	#define CAL_SysNativeControlMove_  SysNativeControlMove_
	#define CHK_SysNativeControlMove_  TRUE
	#define EXP_SysNativeControlMove_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlMove_", (RTS_UINTPTR)SysNativeControlMove_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysNativeControlSysNativeControlMove_
	#define EXT_SysNativeControlSysNativeControlMove_
	#define GET_SysNativeControlSysNativeControlMove_  ERR_OK
	#define CAL_SysNativeControlSysNativeControlMove_(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlMove_(p1) : ((ISysNativeControl*)p0)->ISysNativeControlMove_(p1))
	#define CHK_SysNativeControlSysNativeControlMove_  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlSysNativeControlMove_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysNativeControlMove_
	#define EXT_SysNativeControlMove_
	#define GET_SysNativeControlMove_(fl)  CAL_CMGETAPI( "SysNativeControlMove_" ) 
	#define CAL_SysNativeControlMove_(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlMove_(p1) : ((ISysNativeControl*)p0)->ISysNativeControlMove_(p1))
	#define CHK_SysNativeControlMove_  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlMove_  CAL_CMEXPAPI( "SysNativeControlMove_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysNativeControlMove_  PFSYSNATIVECONTROLMOVE_ pfSysNativeControlMove_;
	#define EXT_SysNativeControlMove_  extern PFSYSNATIVECONTROLMOVE_ pfSysNativeControlMove_;
	#define GET_SysNativeControlMove_(fl)  s_pfCMGetAPI2( "SysNativeControlMove_", (RTS_VOID_FCTPTR *)&pfSysNativeControlMove_, (fl), 0, 0)
	#define CAL_SysNativeControlMove_  pfSysNativeControlMove_
	#define CHK_SysNativeControlMove_  (pfSysNativeControlMove_ != NULL)
	#define EXP_SysNativeControlMove_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlMove_", (RTS_UINTPTR)SysNativeControlMove_, 0, 0) 
#endif




/**
 * <description>
 *	Function to show or hide a native control
 * </description>
 * <param name="hWindow" type="IN">Handle to the native control</param>
 * <param name="dwFlags" type="IN">The show flags</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysNativeControlShow(RTS_HANDLE hControl, RTS_UI32 dwFlags);
typedef RTS_RESULT (CDECL * PFSYSNATIVECONTROLSHOW) (RTS_HANDLE hControl, RTS_UI32 dwFlags);
#if defined(SYSNATIVECONTROL_NOTIMPLEMENTED) || defined(SYSNATIVECONTROLSHOW_NOTIMPLEMENTED)
	#define USE_SysNativeControlShow
	#define EXT_SysNativeControlShow
	#define GET_SysNativeControlShow(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysNativeControlShow(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysNativeControlShow  FALSE
	#define EXP_SysNativeControlShow  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysNativeControlShow
	#define EXT_SysNativeControlShow
	#define GET_SysNativeControlShow(fl)  CAL_CMGETAPI( "SysNativeControlShow" ) 
	#define CAL_SysNativeControlShow  SysNativeControlShow
	#define CHK_SysNativeControlShow  TRUE
	#define EXP_SysNativeControlShow  CAL_CMEXPAPI( "SysNativeControlShow" ) 
#elif defined(MIXED_LINK) && !defined(SYSNATIVECONTROL_EXTERNAL)
	#define USE_SysNativeControlShow
	#define EXT_SysNativeControlShow
	#define GET_SysNativeControlShow(fl)  CAL_CMGETAPI( "SysNativeControlShow" ) 
	#define CAL_SysNativeControlShow  SysNativeControlShow
	#define CHK_SysNativeControlShow  TRUE
	#define EXP_SysNativeControlShow  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlShow", (RTS_UINTPTR)SysNativeControlShow, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysNativeControlSysNativeControlShow
	#define EXT_SysNativeControlSysNativeControlShow
	#define GET_SysNativeControlSysNativeControlShow  ERR_OK
	#define CAL_SysNativeControlSysNativeControlShow(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlShow(p1) : ((ISysNativeControl*)p0)->ISysNativeControlShow(p1))
	#define CHK_SysNativeControlSysNativeControlShow  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlSysNativeControlShow  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysNativeControlShow
	#define EXT_SysNativeControlShow
	#define GET_SysNativeControlShow(fl)  CAL_CMGETAPI( "SysNativeControlShow" ) 
	#define CAL_SysNativeControlShow(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlShow(p1) : ((ISysNativeControl*)p0)->ISysNativeControlShow(p1))
	#define CHK_SysNativeControlShow  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlShow  CAL_CMEXPAPI( "SysNativeControlShow" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysNativeControlShow  PFSYSNATIVECONTROLSHOW pfSysNativeControlShow;
	#define EXT_SysNativeControlShow  extern PFSYSNATIVECONTROLSHOW pfSysNativeControlShow;
	#define GET_SysNativeControlShow(fl)  s_pfCMGetAPI2( "SysNativeControlShow", (RTS_VOID_FCTPTR *)&pfSysNativeControlShow, (fl), 0, 0)
	#define CAL_SysNativeControlShow  pfSysNativeControlShow
	#define CHK_SysNativeControlShow  (pfSysNativeControlShow != NULL)
	#define EXP_SysNativeControlShow  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlShow", (RTS_UINTPTR)SysNativeControlShow, 0, 0) 
#endif



RTS_RESULT CDECL SysNativeControlShow_(RTS_HANDLE hControl, RTS_UI32 dwFlags);
typedef RTS_RESULT (CDECL * PFSYSNATIVECONTROLSHOW_) (RTS_HANDLE hControl, RTS_UI32 dwFlags);
#if defined(SYSNATIVECONTROL_NOTIMPLEMENTED) || defined(SYSNATIVECONTROLSHOW__NOTIMPLEMENTED)
	#define USE_SysNativeControlShow_
	#define EXT_SysNativeControlShow_
	#define GET_SysNativeControlShow_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysNativeControlShow_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysNativeControlShow_  FALSE
	#define EXP_SysNativeControlShow_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysNativeControlShow_
	#define EXT_SysNativeControlShow_
	#define GET_SysNativeControlShow_(fl)  CAL_CMGETAPI( "SysNativeControlShow_" ) 
	#define CAL_SysNativeControlShow_  SysNativeControlShow_
	#define CHK_SysNativeControlShow_  TRUE
	#define EXP_SysNativeControlShow_  CAL_CMEXPAPI( "SysNativeControlShow_" ) 
#elif defined(MIXED_LINK) && !defined(SYSNATIVECONTROL_EXTERNAL)
	#define USE_SysNativeControlShow_
	#define EXT_SysNativeControlShow_
	#define GET_SysNativeControlShow_(fl)  CAL_CMGETAPI( "SysNativeControlShow_" ) 
	#define CAL_SysNativeControlShow_  SysNativeControlShow_
	#define CHK_SysNativeControlShow_  TRUE
	#define EXP_SysNativeControlShow_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlShow_", (RTS_UINTPTR)SysNativeControlShow_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysNativeControlSysNativeControlShow_
	#define EXT_SysNativeControlSysNativeControlShow_
	#define GET_SysNativeControlSysNativeControlShow_  ERR_OK
	#define CAL_SysNativeControlSysNativeControlShow_(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlShow_(p1) : ((ISysNativeControl*)p0)->ISysNativeControlShow_(p1))
	#define CHK_SysNativeControlSysNativeControlShow_  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlSysNativeControlShow_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysNativeControlShow_
	#define EXT_SysNativeControlShow_
	#define GET_SysNativeControlShow_(fl)  CAL_CMGETAPI( "SysNativeControlShow_" ) 
	#define CAL_SysNativeControlShow_(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysNativeControl->ISysNativeControlShow_(p1) : ((ISysNativeControl*)p0)->ISysNativeControlShow_(p1))
	#define CHK_SysNativeControlShow_  (pISysNativeControl != NULL)
	#define EXP_SysNativeControlShow_  CAL_CMEXPAPI( "SysNativeControlShow_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysNativeControlShow_  PFSYSNATIVECONTROLSHOW_ pfSysNativeControlShow_;
	#define EXT_SysNativeControlShow_  extern PFSYSNATIVECONTROLSHOW_ pfSysNativeControlShow_;
	#define GET_SysNativeControlShow_(fl)  s_pfCMGetAPI2( "SysNativeControlShow_", (RTS_VOID_FCTPTR *)&pfSysNativeControlShow_, (fl), 0, 0)
	#define CAL_SysNativeControlShow_  pfSysNativeControlShow_
	#define CHK_SysNativeControlShow_  (pfSysNativeControlShow_ != NULL)
	#define EXP_SysNativeControlShow_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysNativeControlShow_", (RTS_UINTPTR)SysNativeControlShow_, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSNATIVECONTROLCREATE ISysNativeControlCreate;
 	PFSYSNATIVECONTROLCREATE_ ISysNativeControlCreate_;
 	PFSYSNATIVECONTROLDESTROY ISysNativeControlDestroy;
 	PFSYSNATIVECONTROLDESTROY_ ISysNativeControlDestroy_;
 	PFSYSNATIVECONTROLCALLMETHOD ISysNativeControlCallMethod;
 	PFSYSNATIVECONTROLCALLMETHOD_ ISysNativeControlCallMethod_;
 	PFSYSNATIVECONTROLMOVE ISysNativeControlMove;
 	PFSYSNATIVECONTROLMOVE_ ISysNativeControlMove_;
 	PFSYSNATIVECONTROLSHOW ISysNativeControlShow;
 	PFSYSNATIVECONTROLSHOW_ ISysNativeControlShow_;
 } ISysNativeControl_C;

#ifdef CPLUSPLUS
class ISysNativeControl : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysNativeControlCreate(SysNativeControlCreate_Struct* pCreate, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ISysNativeControlCreate_(SysNativeControlCreate_Struct* pCreate, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysNativeControlDestroy(void) =0;
		virtual RTS_RESULT CDECL ISysNativeControlDestroy_(void) =0;
		virtual RTS_RESULT CDECL ISysNativeControlCallMethod(char* pszMethodName, NativeControlParam* params, RTS_SIZE iParamCount, NativeControlParam* pResult) =0;
		virtual RTS_RESULT CDECL ISysNativeControlCallMethod_(char* pszMethodName, NativeControlParam* params, RTS_SIZE iParamCount, NativeControlParam* pResult) =0;
		virtual RTS_RESULT CDECL ISysNativeControlMove(RTS_Rectangle* pRect) =0;
		virtual RTS_RESULT CDECL ISysNativeControlMove_(RTS_Rectangle* pRect) =0;
		virtual RTS_RESULT CDECL ISysNativeControlShow(RTS_UI32 dwFlags) =0;
		virtual RTS_RESULT CDECL ISysNativeControlShow_(RTS_UI32 dwFlags) =0;
};
	#ifndef ITF_SysNativeControl
		#define ITF_SysNativeControl static ISysNativeControl *pISysNativeControl = NULL;
	#endif
	#define EXTITF_SysNativeControl
#else	/*CPLUSPLUS*/
	typedef ISysNativeControl_C		ISysNativeControl;
	#ifndef ITF_SysNativeControl
		#define ITF_SysNativeControl
	#endif
	#define EXTITF_SysNativeControl
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSNATIVECONTROLITF_H_*/
