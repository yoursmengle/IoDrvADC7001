/**
 * <interfacename>SysNativeControl</interfacename>
 * <description> 
 *	<p>The SysNativeControl interface brings native controls into the visualization. All
	controls are created as child controls of the targetvisualization. </p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysNativeControl')

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
DEF_ITF_API(`RTS_HANDLE', `CDECL', `SysNativeControlCreate', `(SysNativeControlCreate_Struct* pCreate, RTS_RESULT *pResult)')
DEF_ITF_API(`RTS_HANDLE', `CDECL', `SysNativeControlCreate_', `(SysNativeControlCreate_Struct* pCreate, RTS_RESULT *pResult)')

/**
 * <description>
 *	Function to destroy a native control
 * </description>
 * <param name="hControl" type="IN">Handle to the native control</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysNativeControlDestroy',`(RTS_HANDLE hControl)')
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysNativeControlDestroy_',`(RTS_HANDLE hControl)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysNativeControlCallMethod',`(RTS_HANDLE hControl, char* pszMethodName, NativeControlParam* params, RTS_SIZE iParamCount, NativeControlParam* pResult)')
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysNativeControlCallMethod_',`(RTS_HANDLE hControl, char* pszMethodName, NativeControlParam* params, RTS_SIZE iParamCount, NativeControlParam* pResult)')

/**
 * <description>
 *	Function to destroy a native control
 * </description>
 * <param name="hControl" type="IN">Handle to the native control</param>
 * <param name="pRect" type="IN">The new position</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysNativeControlMove',`(RTS_HANDLE hControl, RTS_Rectangle* pRect)')
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysNativeControlMove_',`(RTS_HANDLE hControl, RTS_Rectangle* pRect)')

/**
 * <description>
 *	Function to show or hide a native control
 * </description>
 * <param name="hWindow" type="IN">Handle to the native control</param>
 * <param name="dwFlags" type="IN">The show flags</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysNativeControlShow',`(RTS_HANDLE hControl, RTS_UI32 dwFlags)')
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysNativeControlShow_',`(RTS_HANDLE hControl, RTS_UI32 dwFlags)')

#ifdef __cplusplus
}
#endif
