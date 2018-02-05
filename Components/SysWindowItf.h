 /**
 * <interfacename>SysWindow</interfacename>
 * <description> 
 *	<p>SysWindow interfaces is porjected to get access to the window manager of a graphical environment
 *	To handle the window of the target visualisation.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSWINDOWITF_H_
#define _SYSWINDOWITF_H_

#include "CmpStd.h"

 

 




#include "SysGraphicBase.h"

#define ERR_TOOMANYWINDOWS			0x0001
#define ERR_TOOMANYCALLBACKS		0x0002
#define ERR_WINDOWNOTCREATED		0x0003
#define ERR_WINDOWNOTREGISTERED		0x0004

#define WINDOW_TYPE_TITLE_FRAME		0x0000
#define WINDOW_TYPE_FRAME			0x0001
#define WINDOW_TYPE_NONE			0x0002
#define WINDOW_TYPE_TITLE_FRAME_CLIENT_SIZE	0x0003
#define WINDOW_TYPE_FRAME_CLIENT_SIZE		0x0004

/**
 * <category>Window Creation Flags</category>
 * <type>Int</type>
 * <description>
 *	For extensibility we define some flags that control some properties of a window. Any of these flags might 
 *	be releated to a special class of window (e.g. the editcontrol).
 * </description>
 */	
#define SYSWINCREATE_FLAGS_NONE			0x00000000

/**
 * <category>Window Creation Flags</category>
 * <type>Int</type>
 * <description>
 *	If this flag is set, then the parentwindow handle is an OS handle and not a window handle returned by the SysWindow-Component.
 * </description>
 */	
#define SYSWINCREATE_FLAGS_PARENTISOSHANDLE			0x00000001

/**
 * <category>Window Creation Flags</category>
 * <type>Int</type>
 * <description>
 *	If this flag is set, then the window or control is created with the text alignment LEFT.
 * </description>
 */	
#define SYSWINCREATE_FLAGS_TEXT_ALIGN_LEFT   0x00000002

/**
 * <category>Window Creation Flags</category>
 * <type>Int</type>
 * <description>
 *	If this flag is set, then the window or control is created with the text alignment CENTER.
 * </description>
 */	
#define SYSWINCREATE_FLAGS_TEXT_ALIGN_HCENTER   0x00000004

/**
 * <category>Window Creation Flags</category>
 * <type>Int</type>
 * <description>
 *	If this flag is set, then the window or control is created with the text alignment RIGHT.
 * </description>
 */	
#define SYSWINCREATE_FLAGS_TEXT_ALIGN_RIGHT   0x00000008

/**
 * <category>Window Creation Flags</category>
 * <type>Int</type>
 * <description>
 *	If this flag is set, then the window will react to touch inputs if possible.
 * </description>
 */	
#define SYSWINCREATE_FLAGS_TOUCHHANDLING_ACTIVE 0x00000010

 /**
 * <category>Window Creation Flags</category>
 * <type>Int</type>
 * <description>
 *	If this flag is set, then the window will created hidden.
 * </description>
 */
#define SYSWINCREATE_FLAGS_CREATE_HIDDEN 0x00000020

/**
 * <category>Window create description</category>
 * <description>
 *	This structure describes a window that has to be created. 
 *	The parameters pszWindowName and pszClassName may be NULL
 *	If pszClassName == "EDIT", a new Editcontrol will be created.
 * </description>
 * <element name="pszWindowName" type="IN">The name/title of the window that shall be created.</element>
 * <element name="pszClassName" type="IN">The type of window that shall be created. At the moment
 *	the following windows are supported: SYSWINDOW_CLASS_TARGETVISU_WINDOW and SYSWINDOW_CLASS_TARGETVISU_EDITCONTROL
 *	</element>
 * <element name="prWindow" type="IN"></element>
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
 * <element name="ulCreationFlags" type="IN">A combination of the SYSWINCREATE_FLAGS... for optionally setting additional flags affecting
 *	the creation of a window.</element>
 */
typedef struct
{
	char* pszWindowName;
	char* pszClassName;
	RTS_Rectangle* prWindow;
	RTS_HANDLE hParentWindow;
	RTS_UI32 ulWindowType;
	RTS_UI32 ulCreationFlags;
} SysWindowCreate_Struct;

/**
 * <category>Event parameter</category>
 * <element name="pfToInvoke" type="IN">The function that should be invoked</element>
 * <element name="ulParam" type="IN">The arbitrary data that should be passed to this function</element>
 * <element name="bHandled" type="OUT">Signal whether the call was executed</element>
 */
typedef struct
{
	PFINVOKEINWINDOWTASK pfToInvoke;
	RTS_UINTPTR ulParam;
	RTS_BOOL bHandled;
} EVTPARAM_SysWindowOnInvokeInWindowTask;
#define EVTPARAMID_SysWindowOnInvokeInWindowTask					0x0001
#define EVTVERSION_SysWindowOnInvokeInWindowTask					0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when the method SysWindowInvokeInWindowTask is called. This event will be raised only when
 * this feature is supported and activated in a system specific implementation!</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysWindowOnInvokeInWindowTask</param>
 */
#define EVT_SysWindow_OnInvokeInWindowTask					MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Event parameter</category>
 * <element name="pCreateInfo" type="IN_OUT">The information structure that is relevant for the creation of the current window</element>
 */
typedef struct
{
	SysWindowCreate_Struct* pCreateInfo;
} EVTPARAM_SysWindowCreate;
#define EVTPARAMID_SysWindowCreateInfo					0x0002
#define EVTVERSION_SysWindowCreateInfo					0x0001

/**
 * <category>Event parameter</category>
 * <element name="pCreateInfo" type="IN_OUT">The information structure that is relevant for the creation of the current window</element>
 * <element name="hWindow" type="IN">The window handle of the newly created window</element>
 * <element name="hOSWindow" type="IN">The operating system window handle of the newly created window</element>
 */
typedef struct
{
	SysWindowCreate_Struct* pCreateInfo;
	RTS_HANDLE hWindow;
	RTS_HANDLE hOSWindow;
} EVTPARAM_SysWindowAfterCreate;
#define EVTPARAMID_SysWindowAfterCreateInfo				0x0003
#define EVTVERSION_SysWindowAfterCreateInfo				0x0001

/**
 * <category>Events</category>
 * <description>Event is sent before a window is created. The information of the creation structure can be altered by the eventhandlers.
 *	This event will only be raised when this is supported by the according operating system implementation.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysWindowCreate</param>
 */
#define EVT_SysWindow_BeforeCreate							MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is sent after a window is created.
 *	This event will only be raised when this is supported by the according operating system implementation.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysWindowAfterCreate</param>
 */
#define EVT_SysWindow_AfterCreate							MAKE_EVENTID(EVTCLASS_INFO, 3)


/**
 * <category>Window Flags</category>
 * <type>Int</type>
 * <description>
 *	For extensibility we define some flags that control some properties of a window. Any of these flags might 
 *	be releated to a special class of window (e.g. the editcontrol).
 * </description>
 */	
#define SYSWIN_FLAGS_NONE			0x00000000
/**
 * <category>Window Flags</category>
 * <type>Int</type>
 * <description>
 *	This flag controls whether an edit control hides the input using a replacement character like '*'. This
 *	can be used to realize a password input field. The default value of this flag is false.
 * </description>
 */	
#define SYSWIN_FLAGS_PASSWORD		0x00000001
/**
 * <category>Window Flags</category>
 * <type>Int</type>
 * <description>
 *	This flag controls whether an edit control has to return the edited value as a wstring
 *  or as string.
 * </description>
 */	
#define SYSWIN_FLAGS_WSTRING		0x00000020


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Windows does support both modes of operation for the SysWindow Component (single- and multitasking). To 
 *	decide which one should be used, this setting can be used. 0 => Mulitasking, 2 using an externally provided window task (communication using
 *	the CmpEventMgr), otherwise => Singletasking
 * (Only for Windows).
 *	Setting the mode to 2 requires that a component handles the event EVT_OnInvokeInWindowTask.
 * </description>
 */	
#define SYSWINDOW_INT_WINDOWS_SINGLETASKING						"Windows.SingleTaskingWindows"
#define SYSWINDOW_INT_WINDOWS_SINGLETASKING_DEFAULT				0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * (Only for Windows)
 *	You can decide with this setting whether the window should be closed when Alt+F4 is pressed by the user or if this keycode should be ignored.
 *	When this setting is activated (it is by default!), then the keyboard handling of the codesys visualization will not react to the key combination of Alt+F4!
 * </description>
 */	
#define SYSWINDOW_INT_WINDOWS_ALLOWCLOSING_WITH_ALT_F4			"Windows.CloseOnAltF4"
#define SYSWINDOW_INT_WINDOWS_ALLOWCLOSING_WITH_ALT_F4_DEFAULT	1

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * (Only for Windows)
 *	You can decide with this setting whether the window should be closed when WM_CLOSE is called.
 *	When this setting is activated (it is by default!), then the window is closed
 * </description>
 */	
#define SYSWINDOW_INT_WINDOWS_ALLOWCLOSING_BY_WM_CLOSE			"Windows.CloseOnWM_CLOSE"
#define SYSWINDOW_INT_WINDOWS_ALLOWCLOSING_BY_WM_CLOSE_DEFAULT	1			

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * (Only for Windows)
 *	This setting defines, whether a window should be cyclically set as the foreground window.
 *  The values have the following meaning:
 *  - a negative value: feature is disabled (the default!)
 *  - 0: The window will be always set as the foreground window (no time limit)
 *  - a positive value: feature will be executed n cycles.
 * </description>
 */	
#define SYSWINDOW_INT_WINDOWS_BRING_WINDOW_TO_FRONT						"Windows.BringWindowToFront"
#define SYSWINDOW_INT_WINDOWS_BRING_WINDOW_TO_FRONT_DEFAULT				-1

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * (Only for Windows)
 *	This setting is used in conjunction with setting "Windows.BringWindowToFront". It defines the cycle time in milliseconds,
 *  when a window will be set as the foreground window.
 * </description>
 */	
#define SYSWINDOW_INT_WINDOWS_BRING_WINDOW_TO_FRONT_CYCLE_TIME			"Windows.BringWindowToFrontCycleTime"
#define SYSWINDOW_INT_WINDOWS_BRING_WINDOW_TO_FRONT_CYCLE_TIME_DEFAULT	1000

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Set Caret Blink Time in Visualization on WinCE in milliseconds. Set -1 to deactivate the Cursor Blink, 0 for default.
 * </description>
 */
#define SYSWINDOW_INT_WINCE_SETCARETBLINKTIME				"WinCE.SetCaretBlinkTime"
#define SYSWINDOW_INT_WINCE_SETCARETBLINKTIME_DEFAULT		0		

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * The Targetvisualization in Linux operating systems supports two different modes of operation. The classical mode (value == 0)
 * opens a window only while the targetvisualization is running. After a deletion of an application or between reset and start of
 * a targetvisu application, there is no open window. 
 * Additionally it is possible to keep the main window open until shutdown of the application (value == 1). This prevents problems
 * on systems based on the Qt5 platform plugin "EGLFS" (for details see http://doc.qt.io/qt-5/embedded-linux.html for example).
 * Nevertheless in this mode there is no possibility for opening several concurrent targetvisu windows as it is possible at least
 * in X-server based installations using the classical mode (value == 0).
 * It is not recommended to use a value != 0 together with X-server based installations as the resulting behaviour will not be the
 * one that users of X-server based systems are expecting.
 * </description>
 */
/* take care: if changing the following setting as there might be a copy of that value in the C++ part of the linux targetvisualization */
#define SYSWINDOW_INT_LINUX_KEEPMAINWINDOWOPEN				"Linux.KeepMainWindowOpen"
/* take care: if changing the following default as there might be a copy of that value in the C++ part of the linux targetvisualization */
#ifndef SYSWINDOW_INT_LINUX_KEEPMAINWINDOWOPEN_DEFAULT	
	#define SYSWINDOW_INT_LINUX_KEEPMAINWINDOWOPEN_DEFAULT		0		
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Only relevant if Linux.KeepMainWindowOpen == 1.
 * To reduce the number of states the targetvisualization window can be in (before showing the window, targetvisu displayed, targetvisu not displayed),
 * this setting can be used to remove the state "before showing the window". If this setting has the value 1, then
 * the window will be displayed immediately at startup without showing a targetvisualization yet. As this mode is recommended only for embedded devices
 * (see SYSWINDOW_INT_LINUX_KEEPMAINWINDOWOPEN too) the initial window is opened in full screen mode.
 * </description>
 */
#define SYSWINDOW_INT_LINUX_KEEPMAINWINDOWOPEN_SHOW_IMMEDIATELY				"Linux.KeepMainWindowOpenShowImmediately"
/* take care: if changing the following setting as there might be a copy of that value in the C++ part of the linux targetvisualization */
#ifndef SYSWINDOW_INT_LINUX_KEEPMAINWINDOWOPEN_SHOW_IMMEDIATELY_DEFAULT		
	#define SYSWINDOW_INT_LINUX_KEEPMAINWINDOWOPEN_SHOW_IMMEDIATELY_DEFAULT		1
#endif

/**
 * <description>Notification code that can be sent to a window using <see>SysWindowNotify</see>. The intention of this notification is
 *	to trigger a refresh and repaint of the window. In case of a targetvisualization window, this notification will usually be sent,
 *	when there is new paintinformation available that should be retrieved by the window.
 *	The notification parameter is not used at the moment.</description>
 */
#define SYSWINDOW_NOTIFICATION_REFRESH_REQUESTED			1

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysWindowOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysWindowOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/* sysspecific method called cyclically */
RTS_RESULT CDECL SysWindowCyclicCall(void);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Function to check whether an implementation of SysWindow can work with windows that are created from
 *	several independant tasks. If several tasks are not supported, then the method <see>SysWindowInvokeInWindowTask</see>
 *	must be implemented. 
 * </description>
 * <result>ERR_OK if several tasks are allowed, otherwise a different error code</result>
 */
RTS_RESULT CDECL SysWindowSupportsSeveralTasks(void);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSUPPORTSSEVERALTASKS) (void);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSUPPORTSSEVERALTASKS_NOTIMPLEMENTED)
	#define USE_SysWindowSupportsSeveralTasks
	#define EXT_SysWindowSupportsSeveralTasks
	#define GET_SysWindowSupportsSeveralTasks(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSupportsSeveralTasks() (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSupportsSeveralTasks  FALSE
	#define EXP_SysWindowSupportsSeveralTasks  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSupportsSeveralTasks
	#define EXT_SysWindowSupportsSeveralTasks
	#define GET_SysWindowSupportsSeveralTasks(fl)  CAL_CMGETAPI( "SysWindowSupportsSeveralTasks" ) 
	#define CAL_SysWindowSupportsSeveralTasks  SysWindowSupportsSeveralTasks
	#define CHK_SysWindowSupportsSeveralTasks  TRUE
	#define EXP_SysWindowSupportsSeveralTasks  CAL_CMEXPAPI( "SysWindowSupportsSeveralTasks" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSupportsSeveralTasks
	#define EXT_SysWindowSupportsSeveralTasks
	#define GET_SysWindowSupportsSeveralTasks(fl)  CAL_CMGETAPI( "SysWindowSupportsSeveralTasks" ) 
	#define CAL_SysWindowSupportsSeveralTasks  SysWindowSupportsSeveralTasks
	#define CHK_SysWindowSupportsSeveralTasks  TRUE
	#define EXP_SysWindowSupportsSeveralTasks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSupportsSeveralTasks", (RTS_UINTPTR)SysWindowSupportsSeveralTasks, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSupportsSeveralTasks
	#define EXT_SysWindowSysWindowSupportsSeveralTasks
	#define GET_SysWindowSysWindowSupportsSeveralTasks  ERR_OK
	#define CAL_SysWindowSysWindowSupportsSeveralTasks  SysWindowSupportsSeveralTasks
	#define CHK_SysWindowSysWindowSupportsSeveralTasks  TRUE
	#define EXP_SysWindowSysWindowSupportsSeveralTasks  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSupportsSeveralTasks
	#define EXT_SysWindowSupportsSeveralTasks
	#define GET_SysWindowSupportsSeveralTasks(fl)  CAL_CMGETAPI( "SysWindowSupportsSeveralTasks" ) 
	#define CAL_SysWindowSupportsSeveralTasks  SysWindowSupportsSeveralTasks
	#define CHK_SysWindowSupportsSeveralTasks  TRUE
	#define EXP_SysWindowSupportsSeveralTasks  CAL_CMEXPAPI( "SysWindowSupportsSeveralTasks" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSupportsSeveralTasks  PFSYSWINDOWSUPPORTSSEVERALTASKS pfSysWindowSupportsSeveralTasks;
	#define EXT_SysWindowSupportsSeveralTasks  extern PFSYSWINDOWSUPPORTSSEVERALTASKS pfSysWindowSupportsSeveralTasks;
	#define GET_SysWindowSupportsSeveralTasks(fl)  s_pfCMGetAPI2( "SysWindowSupportsSeveralTasks", (RTS_VOID_FCTPTR *)&pfSysWindowSupportsSeveralTasks, (fl), 0, 0)
	#define CAL_SysWindowSupportsSeveralTasks  pfSysWindowSupportsSeveralTasks
	#define CHK_SysWindowSupportsSeveralTasks  (pfSysWindowSupportsSeveralTasks != NULL)
	#define EXP_SysWindowSupportsSeveralTasks   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSupportsSeveralTasks", (RTS_UINTPTR)SysWindowSupportsSeveralTasks, 0, 0) 
#endif


/**
 * <description>
 *	Function to transfer a function call from any task to the task where all windows are handled. This might be
 *	needed on some platforms (<see>SysWindowSupportsSeveralTasks</see> says that multitasking is not allowed for windows.
 * </description>
 * <param name="pfToCall" type="IN">The function that shall be called from the window task</param>
 * <param name="ulParam" type="IN">A parameter that will be passed to the call to <see>pfToCall</see>. 
 *	If this parameter is a pointer to some object, then this object must be alive until the method is called.</param>
 * <result>An error code. Will return ERR_NOTIMPLEMENTED if the singletasking mode is not available.</result>
 */
RTS_RESULT CDECL SysWindowInvokeInWindowTask(PFINVOKEINWINDOWTASK pfToCall, RTS_UINTPTR ulParam);
typedef RTS_RESULT (CDECL * PFSYSWINDOWINVOKEINWINDOWTASK) (PFINVOKEINWINDOWTASK pfToCall, RTS_UINTPTR ulParam);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWINVOKEINWINDOWTASK_NOTIMPLEMENTED)
	#define USE_SysWindowInvokeInWindowTask
	#define EXT_SysWindowInvokeInWindowTask
	#define GET_SysWindowInvokeInWindowTask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowInvokeInWindowTask(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowInvokeInWindowTask  FALSE
	#define EXP_SysWindowInvokeInWindowTask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowInvokeInWindowTask
	#define EXT_SysWindowInvokeInWindowTask
	#define GET_SysWindowInvokeInWindowTask(fl)  CAL_CMGETAPI( "SysWindowInvokeInWindowTask" ) 
	#define CAL_SysWindowInvokeInWindowTask  SysWindowInvokeInWindowTask
	#define CHK_SysWindowInvokeInWindowTask  TRUE
	#define EXP_SysWindowInvokeInWindowTask  CAL_CMEXPAPI( "SysWindowInvokeInWindowTask" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowInvokeInWindowTask
	#define EXT_SysWindowInvokeInWindowTask
	#define GET_SysWindowInvokeInWindowTask(fl)  CAL_CMGETAPI( "SysWindowInvokeInWindowTask" ) 
	#define CAL_SysWindowInvokeInWindowTask  SysWindowInvokeInWindowTask
	#define CHK_SysWindowInvokeInWindowTask  TRUE
	#define EXP_SysWindowInvokeInWindowTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowInvokeInWindowTask", (RTS_UINTPTR)SysWindowInvokeInWindowTask, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowInvokeInWindowTask
	#define EXT_SysWindowSysWindowInvokeInWindowTask
	#define GET_SysWindowSysWindowInvokeInWindowTask  ERR_OK
	#define CAL_SysWindowSysWindowInvokeInWindowTask  SysWindowInvokeInWindowTask
	#define CHK_SysWindowSysWindowInvokeInWindowTask  TRUE
	#define EXP_SysWindowSysWindowInvokeInWindowTask  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowInvokeInWindowTask
	#define EXT_SysWindowInvokeInWindowTask
	#define GET_SysWindowInvokeInWindowTask(fl)  CAL_CMGETAPI( "SysWindowInvokeInWindowTask" ) 
	#define CAL_SysWindowInvokeInWindowTask  SysWindowInvokeInWindowTask
	#define CHK_SysWindowInvokeInWindowTask  TRUE
	#define EXP_SysWindowInvokeInWindowTask  CAL_CMEXPAPI( "SysWindowInvokeInWindowTask" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowInvokeInWindowTask  PFSYSWINDOWINVOKEINWINDOWTASK pfSysWindowInvokeInWindowTask;
	#define EXT_SysWindowInvokeInWindowTask  extern PFSYSWINDOWINVOKEINWINDOWTASK pfSysWindowInvokeInWindowTask;
	#define GET_SysWindowInvokeInWindowTask(fl)  s_pfCMGetAPI2( "SysWindowInvokeInWindowTask", (RTS_VOID_FCTPTR *)&pfSysWindowInvokeInWindowTask, (fl), 0, 0)
	#define CAL_SysWindowInvokeInWindowTask  pfSysWindowInvokeInWindowTask
	#define CHK_SysWindowInvokeInWindowTask  (pfSysWindowInvokeInWindowTask != NULL)
	#define EXP_SysWindowInvokeInWindowTask   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowInvokeInWindowTask", (RTS_UINTPTR)SysWindowInvokeInWindowTask, 0, 0) 
#endif


/**
 * <description>A window handling the targetvisualization. This window must have the following behaviour:
 *	First of all during the creation of this window, a pointer to a structure of type <see>TargetvisuParams</see>
 *	will be given in the parameter ulParam of <see>SysWindowCreate</see>. This structure will be valid until
 *	the targetvisualization is closed. The window has to remember this structure because it contains all the information
 *	that is needed for working as a targetvisualization.
 *	One important member in this structure is the member <see>callback</see>. This substructure contains
 *	function pointers that must be called by the targetvisualization window. These callbacks handle for example
 *	the mouse, updating etc.</description>
 */
#define SYSWINDOW_CLASS_TARGETVISU_WINDOW			"TargetVisu_Window"

/**
 * <description>An editcontrol that can be used by the targetvisualizaton. This
 *		control must react to the RETURN-Key and the ESCAPE-Key. As reaction to these keys it must call the 
 *	according callback in the <see>TargetvisuParams</see>.</description>
 */
#define SYSWINDOW_CLASS_TARGETVISU_EDITCONTROL		"TargetVisu_EditControl"

#define WCB_RETURN_ABORT		0x0001		/* if a callback returns this, the window will be killed and the messageloop leaved */

/**
 * <description>
 *	Function to create a new window
 * </description>
 * <param name="pCreate" type="IN">The structure that describes the window that has to be created.</param>
 * <param name="ulParam" type="IN">A parameter that is dependant of the type of the window. Might be a 
 *	Pointer pointing to a structure with further information for the creation of this window. In case
 *	of a pointer, this pointer must be valid until the window is destroyed.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the created window</result>
 */
RTS_HANDLE CDECL SysWindowCreate(SysWindowCreate_Struct* pCreate, RTS_UINTPTR ulParam, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSWINDOWCREATE) (SysWindowCreate_Struct* pCreate, RTS_UINTPTR ulParam, RTS_RESULT *pResult);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWCREATE_NOTIMPLEMENTED)
	#define USE_SysWindowCreate
	#define EXT_SysWindowCreate
	#define GET_SysWindowCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowCreate(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysWindowCreate  FALSE
	#define EXP_SysWindowCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowCreate
	#define EXT_SysWindowCreate
	#define GET_SysWindowCreate(fl)  CAL_CMGETAPI( "SysWindowCreate" ) 
	#define CAL_SysWindowCreate  SysWindowCreate
	#define CHK_SysWindowCreate  TRUE
	#define EXP_SysWindowCreate  CAL_CMEXPAPI( "SysWindowCreate" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowCreate
	#define EXT_SysWindowCreate
	#define GET_SysWindowCreate(fl)  CAL_CMGETAPI( "SysWindowCreate" ) 
	#define CAL_SysWindowCreate  SysWindowCreate
	#define CHK_SysWindowCreate  TRUE
	#define EXP_SysWindowCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowCreate", (RTS_UINTPTR)SysWindowCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowCreate
	#define EXT_SysWindowSysWindowCreate
	#define GET_SysWindowSysWindowCreate  ERR_OK
	#define CAL_SysWindowSysWindowCreate  ((ISysWindow*)s_pfCMCreateInstance(CLASSID_CSysWindow, NULL))->ISysWindowCreate
	#define CHK_SysWindowSysWindowCreate	(s_pfCMCreateInstance != NULL && pISysWindow != NULL)
	#define EXP_SysWindowSysWindowCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowCreate
	#define EXT_SysWindowCreate
	#define GET_SysWindowCreate(fl)  CAL_CMGETAPI( "SysWindowCreate" ) 
	#define CAL_SysWindowCreate  ((ISysWindow*)s_pfCMCreateInstance(CLASSID_CSysWindow, NULL))->ISysWindowCreate
	#define CHK_SysWindowCreate	(s_pfCMCreateInstance != NULL && pISysWindow != NULL)
	#define EXP_SysWindowCreate  CAL_CMEXPAPI( "SysWindowCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowCreate  PFSYSWINDOWCREATE pfSysWindowCreate;
	#define EXT_SysWindowCreate  extern PFSYSWINDOWCREATE pfSysWindowCreate;
	#define GET_SysWindowCreate(fl)  s_pfCMGetAPI2( "SysWindowCreate", (RTS_VOID_FCTPTR *)&pfSysWindowCreate, (fl), 0, 0)
	#define CAL_SysWindowCreate  pfSysWindowCreate
	#define CHK_SysWindowCreate  (pfSysWindowCreate != NULL)
	#define EXP_SysWindowCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowCreate", (RTS_UINTPTR)SysWindowCreate, 0, 0) 
#endif




/**
 * <description>
 *	Function to destroy a new window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 *	<note>A top level window should unregister itself within the platform independent
 *	part using the method InternWindowUnregister</note>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowDestroy(RTS_HANDLE hWindow);
typedef RTS_RESULT (CDECL * PFSYSWINDOWDESTROY) (RTS_HANDLE hWindow);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWDESTROY_NOTIMPLEMENTED)
	#define USE_SysWindowDestroy
	#define EXT_SysWindowDestroy
	#define GET_SysWindowDestroy(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowDestroy(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowDestroy  FALSE
	#define EXP_SysWindowDestroy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowDestroy
	#define EXT_SysWindowDestroy
	#define GET_SysWindowDestroy(fl)  CAL_CMGETAPI( "SysWindowDestroy" ) 
	#define CAL_SysWindowDestroy  SysWindowDestroy
	#define CHK_SysWindowDestroy  TRUE
	#define EXP_SysWindowDestroy  CAL_CMEXPAPI( "SysWindowDestroy" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowDestroy
	#define EXT_SysWindowDestroy
	#define GET_SysWindowDestroy(fl)  CAL_CMGETAPI( "SysWindowDestroy" ) 
	#define CAL_SysWindowDestroy  SysWindowDestroy
	#define CHK_SysWindowDestroy  TRUE
	#define EXP_SysWindowDestroy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowDestroy", (RTS_UINTPTR)SysWindowDestroy, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowDestroy
	#define EXT_SysWindowSysWindowDestroy
	#define GET_SysWindowSysWindowDestroy  ERR_OK
	#define CAL_SysWindowSysWindowDestroy(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysWindow*)p0)->ISysWindowDestroy())
	#define CHK_SysWindowSysWindowDestroy  TRUE
	#define EXP_SysWindowSysWindowDestroy  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowDestroy
	#define EXT_SysWindowDestroy
	#define GET_SysWindowDestroy(fl)  CAL_CMGETAPI( "SysWindowDestroy" ) 
	#define CAL_SysWindowDestroy(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysWindow*)p0)->ISysWindowDestroy())
	#define CHK_SysWindowDestroy  TRUE
	#define EXP_SysWindowDestroy  CAL_CMEXPAPI( "SysWindowDestroy" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowDestroy  PFSYSWINDOWDESTROY pfSysWindowDestroy;
	#define EXT_SysWindowDestroy  extern PFSYSWINDOWDESTROY pfSysWindowDestroy;
	#define GET_SysWindowDestroy(fl)  s_pfCMGetAPI2( "SysWindowDestroy", (RTS_VOID_FCTPTR *)&pfSysWindowDestroy, (fl), 0, 0)
	#define CAL_SysWindowDestroy  pfSysWindowDestroy
	#define CHK_SysWindowDestroy  (pfSysWindowDestroy != NULL)
	#define EXP_SysWindowDestroy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowDestroy", (RTS_UINTPTR)SysWindowDestroy, 0, 0) 
#endif




/**
 * <description>
 *	Function to set some userdefined data for a window, can be used to retrieve information within a window callback. The window should
 *	just store this data in a way so that it can be retrieved lateron using the hWindow and calling <see>SysWindowGetUserData</see>
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="ulData" type="IN">User data</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowSetUserData(RTS_HANDLE hWindow, RTS_UINTPTR ulData);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSETUSERDATA) (RTS_HANDLE hWindow, RTS_UINTPTR ulData);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSETUSERDATA_NOTIMPLEMENTED)
	#define USE_SysWindowSetUserData
	#define EXT_SysWindowSetUserData
	#define GET_SysWindowSetUserData(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSetUserData(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSetUserData  FALSE
	#define EXP_SysWindowSetUserData  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSetUserData
	#define EXT_SysWindowSetUserData
	#define GET_SysWindowSetUserData(fl)  CAL_CMGETAPI( "SysWindowSetUserData" ) 
	#define CAL_SysWindowSetUserData  SysWindowSetUserData
	#define CHK_SysWindowSetUserData  TRUE
	#define EXP_SysWindowSetUserData  CAL_CMEXPAPI( "SysWindowSetUserData" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSetUserData
	#define EXT_SysWindowSetUserData
	#define GET_SysWindowSetUserData(fl)  CAL_CMGETAPI( "SysWindowSetUserData" ) 
	#define CAL_SysWindowSetUserData  SysWindowSetUserData
	#define CHK_SysWindowSetUserData  TRUE
	#define EXP_SysWindowSetUserData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetUserData", (RTS_UINTPTR)SysWindowSetUserData, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSetUserData
	#define EXT_SysWindowSysWindowSetUserData
	#define GET_SysWindowSysWindowSetUserData  ERR_OK
	#define CAL_SysWindowSysWindowSetUserData(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetUserData(p1) : ((ISysWindow*)p0)->ISysWindowSetUserData(p1))
	#define CHK_SysWindowSysWindowSetUserData  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowSetUserData  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSetUserData
	#define EXT_SysWindowSetUserData
	#define GET_SysWindowSetUserData(fl)  CAL_CMGETAPI( "SysWindowSetUserData" ) 
	#define CAL_SysWindowSetUserData(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetUserData(p1) : ((ISysWindow*)p0)->ISysWindowSetUserData(p1))
	#define CHK_SysWindowSetUserData  (pISysWindow != NULL)
	#define EXP_SysWindowSetUserData  CAL_CMEXPAPI( "SysWindowSetUserData" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSetUserData  PFSYSWINDOWSETUSERDATA pfSysWindowSetUserData;
	#define EXT_SysWindowSetUserData  extern PFSYSWINDOWSETUSERDATA pfSysWindowSetUserData;
	#define GET_SysWindowSetUserData(fl)  s_pfCMGetAPI2( "SysWindowSetUserData", (RTS_VOID_FCTPTR *)&pfSysWindowSetUserData, (fl), 0, 0)
	#define CAL_SysWindowSetUserData  pfSysWindowSetUserData
	#define CHK_SysWindowSetUserData  (pfSysWindowSetUserData != NULL)
	#define EXP_SysWindowSetUserData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetUserData", (RTS_UINTPTR)SysWindowSetUserData, 0, 0) 
#endif




/**
 * <description>
 *	Function to change the show flag of a window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="ulData" type="IN">User data. 1 is passed for hiding the window, 0 for showing it.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowShow(RTS_HANDLE hWindow, RTS_UI32 ulData);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSHOW) (RTS_HANDLE hWindow, RTS_UI32 ulData);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSHOW_NOTIMPLEMENTED)
	#define USE_SysWindowShow
	#define EXT_SysWindowShow
	#define GET_SysWindowShow(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowShow(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowShow  FALSE
	#define EXP_SysWindowShow  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowShow
	#define EXT_SysWindowShow
	#define GET_SysWindowShow(fl)  CAL_CMGETAPI( "SysWindowShow" ) 
	#define CAL_SysWindowShow  SysWindowShow
	#define CHK_SysWindowShow  TRUE
	#define EXP_SysWindowShow  CAL_CMEXPAPI( "SysWindowShow" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowShow
	#define EXT_SysWindowShow
	#define GET_SysWindowShow(fl)  CAL_CMGETAPI( "SysWindowShow" ) 
	#define CAL_SysWindowShow  SysWindowShow
	#define CHK_SysWindowShow  TRUE
	#define EXP_SysWindowShow  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowShow", (RTS_UINTPTR)SysWindowShow, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowShow
	#define EXT_SysWindowSysWindowShow
	#define GET_SysWindowSysWindowShow  ERR_OK
	#define CAL_SysWindowSysWindowShow(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowShow(p1) : ((ISysWindow*)p0)->ISysWindowShow(p1))
	#define CHK_SysWindowSysWindowShow  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowShow  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowShow
	#define EXT_SysWindowShow
	#define GET_SysWindowShow(fl)  CAL_CMGETAPI( "SysWindowShow" ) 
	#define CAL_SysWindowShow(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowShow(p1) : ((ISysWindow*)p0)->ISysWindowShow(p1))
	#define CHK_SysWindowShow  (pISysWindow != NULL)
	#define EXP_SysWindowShow  CAL_CMEXPAPI( "SysWindowShow" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowShow  PFSYSWINDOWSHOW pfSysWindowShow;
	#define EXT_SysWindowShow  extern PFSYSWINDOWSHOW pfSysWindowShow;
	#define GET_SysWindowShow(fl)  s_pfCMGetAPI2( "SysWindowShow", (RTS_VOID_FCTPTR *)&pfSysWindowShow, (fl), 0, 0)
	#define CAL_SysWindowShow  pfSysWindowShow
	#define CHK_SysWindowShow  (pfSysWindowShow != NULL)
	#define EXP_SysWindowShow  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowShow", (RTS_UINTPTR)SysWindowShow, 0, 0) 
#endif




/**
 * <description>
 *	Function to get the userdefined data for a window. This data can be attached before using <see>SysWindowSetUserData</see>. At the moment, this
 *	method is not called.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pulData" type="IN">Pointer to user data that will be filled.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowGetUserData(RTS_HANDLE hWindow, RTS_UINTPTR* pulData);
typedef RTS_RESULT (CDECL * PFSYSWINDOWGETUSERDATA) (RTS_HANDLE hWindow, RTS_UINTPTR* pulData);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWGETUSERDATA_NOTIMPLEMENTED)
	#define USE_SysWindowGetUserData
	#define EXT_SysWindowGetUserData
	#define GET_SysWindowGetUserData(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowGetUserData(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowGetUserData  FALSE
	#define EXP_SysWindowGetUserData  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowGetUserData
	#define EXT_SysWindowGetUserData
	#define GET_SysWindowGetUserData(fl)  CAL_CMGETAPI( "SysWindowGetUserData" ) 
	#define CAL_SysWindowGetUserData  SysWindowGetUserData
	#define CHK_SysWindowGetUserData  TRUE
	#define EXP_SysWindowGetUserData  CAL_CMEXPAPI( "SysWindowGetUserData" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowGetUserData
	#define EXT_SysWindowGetUserData
	#define GET_SysWindowGetUserData(fl)  CAL_CMGETAPI( "SysWindowGetUserData" ) 
	#define CAL_SysWindowGetUserData  SysWindowGetUserData
	#define CHK_SysWindowGetUserData  TRUE
	#define EXP_SysWindowGetUserData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowGetUserData", (RTS_UINTPTR)SysWindowGetUserData, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowGetUserData
	#define EXT_SysWindowSysWindowGetUserData
	#define GET_SysWindowSysWindowGetUserData  ERR_OK
	#define CAL_SysWindowSysWindowGetUserData(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowGetUserData(p1) : ((ISysWindow*)p0)->ISysWindowGetUserData(p1))
	#define CHK_SysWindowSysWindowGetUserData  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowGetUserData  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowGetUserData
	#define EXT_SysWindowGetUserData
	#define GET_SysWindowGetUserData(fl)  CAL_CMGETAPI( "SysWindowGetUserData" ) 
	#define CAL_SysWindowGetUserData(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowGetUserData(p1) : ((ISysWindow*)p0)->ISysWindowGetUserData(p1))
	#define CHK_SysWindowGetUserData  (pISysWindow != NULL)
	#define EXP_SysWindowGetUserData  CAL_CMEXPAPI( "SysWindowGetUserData" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowGetUserData  PFSYSWINDOWGETUSERDATA pfSysWindowGetUserData;
	#define EXT_SysWindowGetUserData  extern PFSYSWINDOWGETUSERDATA pfSysWindowGetUserData;
	#define GET_SysWindowGetUserData(fl)  s_pfCMGetAPI2( "SysWindowGetUserData", (RTS_VOID_FCTPTR *)&pfSysWindowGetUserData, (fl), 0, 0)
	#define CAL_SysWindowGetUserData  pfSysWindowGetUserData
	#define CHK_SysWindowGetUserData  (pfSysWindowGetUserData != NULL)
	#define EXP_SysWindowGetUserData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowGetUserData", (RTS_UINTPTR)SysWindowGetUserData, 0, 0) 
#endif




/**
 * <description>
 *	Function to replace the current window callback function of a window, can be used for subclassing controls
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="ulCallback" type="IN">New callback address</param>
 * <param name="pulOldCallback" type="IN">Old callback address</param>
 * <result>error code</result>
 * <remarks>This function is obsolete and is no longer called and used. For that reason, it might be removed in future releases.</remarks>
 */
RTS_RESULT CDECL SysWindowSetCallback(RTS_HANDLE hWindow, unsigned long ulCallback, unsigned long* pulOldCallback);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSETCALLBACK) (RTS_HANDLE hWindow, unsigned long ulCallback, unsigned long* pulOldCallback);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSETCALLBACK_NOTIMPLEMENTED)
	#define USE_SysWindowSetCallback
	#define EXT_SysWindowSetCallback
	#define GET_SysWindowSetCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSetCallback(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSetCallback  FALSE
	#define EXP_SysWindowSetCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSetCallback
	#define EXT_SysWindowSetCallback
	#define GET_SysWindowSetCallback(fl)  CAL_CMGETAPI( "SysWindowSetCallback" ) 
	#define CAL_SysWindowSetCallback  SysWindowSetCallback
	#define CHK_SysWindowSetCallback  TRUE
	#define EXP_SysWindowSetCallback  CAL_CMEXPAPI( "SysWindowSetCallback" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSetCallback
	#define EXT_SysWindowSetCallback
	#define GET_SysWindowSetCallback(fl)  CAL_CMGETAPI( "SysWindowSetCallback" ) 
	#define CAL_SysWindowSetCallback  SysWindowSetCallback
	#define CHK_SysWindowSetCallback  TRUE
	#define EXP_SysWindowSetCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetCallback", (RTS_UINTPTR)SysWindowSetCallback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSetCallback
	#define EXT_SysWindowSysWindowSetCallback
	#define GET_SysWindowSysWindowSetCallback  ERR_OK
	#define CAL_SysWindowSysWindowSetCallback(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetCallback(p1,p2) : ((ISysWindow*)p0)->ISysWindowSetCallback(p1,p2))
	#define CHK_SysWindowSysWindowSetCallback  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowSetCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSetCallback
	#define EXT_SysWindowSetCallback
	#define GET_SysWindowSetCallback(fl)  CAL_CMGETAPI( "SysWindowSetCallback" ) 
	#define CAL_SysWindowSetCallback(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetCallback(p1,p2) : ((ISysWindow*)p0)->ISysWindowSetCallback(p1,p2))
	#define CHK_SysWindowSetCallback  (pISysWindow != NULL)
	#define EXP_SysWindowSetCallback  CAL_CMEXPAPI( "SysWindowSetCallback" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSetCallback  PFSYSWINDOWSETCALLBACK pfSysWindowSetCallback;
	#define EXT_SysWindowSetCallback  extern PFSYSWINDOWSETCALLBACK pfSysWindowSetCallback;
	#define GET_SysWindowSetCallback(fl)  s_pfCMGetAPI2( "SysWindowSetCallback", (RTS_VOID_FCTPTR *)&pfSysWindowSetCallback, (fl), 0, 0)
	#define CAL_SysWindowSetCallback  pfSysWindowSetCallback
	#define CHK_SysWindowSetCallback  (pfSysWindowSetCallback != NULL)
	#define EXP_SysWindowSetCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetCallback", (RTS_UINTPTR)SysWindowSetCallback, 0, 0) 
#endif




/**
 * <description>
 *	Function to run the message loop for handling the created window. Will block and will not return until the window is closed,...
 *	Must only be called when <see>SysWindowSupportsSeveralTasks</see> returns ERR_OK.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>error code, will return ERR_NOTIMPLEMENTED if the window is handled in a single task</result>
 */
RTS_RESULT CDECL SysWindowMessageLoop(RTS_HANDLE hWindow);
typedef RTS_RESULT (CDECL * PFSYSWINDOWMESSAGELOOP) (RTS_HANDLE hWindow);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWMESSAGELOOP_NOTIMPLEMENTED)
	#define USE_SysWindowMessageLoop
	#define EXT_SysWindowMessageLoop
	#define GET_SysWindowMessageLoop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowMessageLoop(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowMessageLoop  FALSE
	#define EXP_SysWindowMessageLoop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowMessageLoop
	#define EXT_SysWindowMessageLoop
	#define GET_SysWindowMessageLoop(fl)  CAL_CMGETAPI( "SysWindowMessageLoop" ) 
	#define CAL_SysWindowMessageLoop  SysWindowMessageLoop
	#define CHK_SysWindowMessageLoop  TRUE
	#define EXP_SysWindowMessageLoop  CAL_CMEXPAPI( "SysWindowMessageLoop" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowMessageLoop
	#define EXT_SysWindowMessageLoop
	#define GET_SysWindowMessageLoop(fl)  CAL_CMGETAPI( "SysWindowMessageLoop" ) 
	#define CAL_SysWindowMessageLoop  SysWindowMessageLoop
	#define CHK_SysWindowMessageLoop  TRUE
	#define EXP_SysWindowMessageLoop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowMessageLoop", (RTS_UINTPTR)SysWindowMessageLoop, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowMessageLoop
	#define EXT_SysWindowSysWindowMessageLoop
	#define GET_SysWindowSysWindowMessageLoop  ERR_OK
	#define CAL_SysWindowSysWindowMessageLoop(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowMessageLoop() : ((ISysWindow*)p0)->ISysWindowMessageLoop())
	#define CHK_SysWindowSysWindowMessageLoop  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowMessageLoop  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowMessageLoop
	#define EXT_SysWindowMessageLoop
	#define GET_SysWindowMessageLoop(fl)  CAL_CMGETAPI( "SysWindowMessageLoop" ) 
	#define CAL_SysWindowMessageLoop(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowMessageLoop() : ((ISysWindow*)p0)->ISysWindowMessageLoop())
	#define CHK_SysWindowMessageLoop  (pISysWindow != NULL)
	#define EXP_SysWindowMessageLoop  CAL_CMEXPAPI( "SysWindowMessageLoop" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowMessageLoop  PFSYSWINDOWMESSAGELOOP pfSysWindowMessageLoop;
	#define EXT_SysWindowMessageLoop  extern PFSYSWINDOWMESSAGELOOP pfSysWindowMessageLoop;
	#define GET_SysWindowMessageLoop(fl)  s_pfCMGetAPI2( "SysWindowMessageLoop", (RTS_VOID_FCTPTR *)&pfSysWindowMessageLoop, (fl), 0, 0)
	#define CAL_SysWindowMessageLoop  pfSysWindowMessageLoop
	#define CHK_SysWindowMessageLoop  (pfSysWindowMessageLoop != NULL)
	#define EXP_SysWindowMessageLoop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowMessageLoop", (RTS_UINTPTR)SysWindowMessageLoop, 0, 0) 
#endif




/**
 * <description>
 *	Callback prototype
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="wcb" type="IN"></param>
 * <param name="ulCallbackParam" type="IN"></param>
 * <param name="ulParam1" type="IN"></param>
 * <param name="ulParam2" type="IN"></param>
 * <result>error code</result>
 */
typedef int (CDECL *PFWINDOWCALLBACK)(RTS_HANDLE hWindow, WindowCallbacks wcb, RTS_UINTPTR ulCallbackParam, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *	Register window handler callback
 * </description>
 *	<note>For Implementers: The platform independent part of the SysWindow component has a default implementation
 *	for this method. You can just add the following code in this implemenation:	
 *		return InternRegisterCallback(hWindow, wcb, callback, ulParam);
 *	</note>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="wcb" type="IN"></param>
 * <param name="callback" type="IN"></param>
 * <param name="ulParam" type="IN"></param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowRegisterCallback(RTS_HANDLE hWindow, WindowCallbacks wcb, PFWINDOWCALLBACK callback, RTS_UINTPTR ulParam);
typedef RTS_RESULT (CDECL * PFSYSWINDOWREGISTERCALLBACK) (RTS_HANDLE hWindow, WindowCallbacks wcb, PFWINDOWCALLBACK callback, RTS_UINTPTR ulParam);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWREGISTERCALLBACK_NOTIMPLEMENTED)
	#define USE_SysWindowRegisterCallback
	#define EXT_SysWindowRegisterCallback
	#define GET_SysWindowRegisterCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowRegisterCallback(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowRegisterCallback  FALSE
	#define EXP_SysWindowRegisterCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowRegisterCallback
	#define EXT_SysWindowRegisterCallback
	#define GET_SysWindowRegisterCallback(fl)  CAL_CMGETAPI( "SysWindowRegisterCallback" ) 
	#define CAL_SysWindowRegisterCallback  SysWindowRegisterCallback
	#define CHK_SysWindowRegisterCallback  TRUE
	#define EXP_SysWindowRegisterCallback  CAL_CMEXPAPI( "SysWindowRegisterCallback" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowRegisterCallback
	#define EXT_SysWindowRegisterCallback
	#define GET_SysWindowRegisterCallback(fl)  CAL_CMGETAPI( "SysWindowRegisterCallback" ) 
	#define CAL_SysWindowRegisterCallback  SysWindowRegisterCallback
	#define CHK_SysWindowRegisterCallback  TRUE
	#define EXP_SysWindowRegisterCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowRegisterCallback", (RTS_UINTPTR)SysWindowRegisterCallback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowRegisterCallback
	#define EXT_SysWindowSysWindowRegisterCallback
	#define GET_SysWindowSysWindowRegisterCallback  ERR_OK
	#define CAL_SysWindowSysWindowRegisterCallback(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowRegisterCallback(p1,p2,p3) : ((ISysWindow*)p0)->ISysWindowRegisterCallback(p1,p2,p3))
	#define CHK_SysWindowSysWindowRegisterCallback  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowRegisterCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowRegisterCallback
	#define EXT_SysWindowRegisterCallback
	#define GET_SysWindowRegisterCallback(fl)  CAL_CMGETAPI( "SysWindowRegisterCallback" ) 
	#define CAL_SysWindowRegisterCallback(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowRegisterCallback(p1,p2,p3) : ((ISysWindow*)p0)->ISysWindowRegisterCallback(p1,p2,p3))
	#define CHK_SysWindowRegisterCallback  (pISysWindow != NULL)
	#define EXP_SysWindowRegisterCallback  CAL_CMEXPAPI( "SysWindowRegisterCallback" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowRegisterCallback  PFSYSWINDOWREGISTERCALLBACK pfSysWindowRegisterCallback;
	#define EXT_SysWindowRegisterCallback  extern PFSYSWINDOWREGISTERCALLBACK pfSysWindowRegisterCallback;
	#define GET_SysWindowRegisterCallback(fl)  s_pfCMGetAPI2( "SysWindowRegisterCallback", (RTS_VOID_FCTPTR *)&pfSysWindowRegisterCallback, (fl), 0, 0)
	#define CAL_SysWindowRegisterCallback  pfSysWindowRegisterCallback
	#define CHK_SysWindowRegisterCallback  (pfSysWindowRegisterCallback != NULL)
	#define EXP_SysWindowRegisterCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowRegisterCallback", (RTS_UINTPTR)SysWindowRegisterCallback, 0, 0) 
#endif




/**
 * <description>Unregister window handler callback</description>
 *	<note>For Implementers: The platform independent part of the SysWindow component has a default implementation
 *	for this method. You can just add the following code in this implemenation:	
 *		return InternUnregisterCallback(hWindow, wcb, callback);</note>
 * 
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="wcb" type="IN"></param>
 * <param name="callback" type="IN"></param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowUnregisterCallback(RTS_HANDLE hWindow, WindowCallbacks wcb, PFWINDOWCALLBACK callback);
typedef RTS_RESULT (CDECL * PFSYSWINDOWUNREGISTERCALLBACK) (RTS_HANDLE hWindow, WindowCallbacks wcb, PFWINDOWCALLBACK callback);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWUNREGISTERCALLBACK_NOTIMPLEMENTED)
	#define USE_SysWindowUnregisterCallback
	#define EXT_SysWindowUnregisterCallback
	#define GET_SysWindowUnregisterCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowUnregisterCallback(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowUnregisterCallback  FALSE
	#define EXP_SysWindowUnregisterCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowUnregisterCallback
	#define EXT_SysWindowUnregisterCallback
	#define GET_SysWindowUnregisterCallback(fl)  CAL_CMGETAPI( "SysWindowUnregisterCallback" ) 
	#define CAL_SysWindowUnregisterCallback  SysWindowUnregisterCallback
	#define CHK_SysWindowUnregisterCallback  TRUE
	#define EXP_SysWindowUnregisterCallback  CAL_CMEXPAPI( "SysWindowUnregisterCallback" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowUnregisterCallback
	#define EXT_SysWindowUnregisterCallback
	#define GET_SysWindowUnregisterCallback(fl)  CAL_CMGETAPI( "SysWindowUnregisterCallback" ) 
	#define CAL_SysWindowUnregisterCallback  SysWindowUnregisterCallback
	#define CHK_SysWindowUnregisterCallback  TRUE
	#define EXP_SysWindowUnregisterCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowUnregisterCallback", (RTS_UINTPTR)SysWindowUnregisterCallback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowUnregisterCallback
	#define EXT_SysWindowSysWindowUnregisterCallback
	#define GET_SysWindowSysWindowUnregisterCallback  ERR_OK
	#define CAL_SysWindowSysWindowUnregisterCallback(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowUnregisterCallback(p1,p2) : ((ISysWindow*)p0)->ISysWindowUnregisterCallback(p1,p2))
	#define CHK_SysWindowSysWindowUnregisterCallback  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowUnregisterCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowUnregisterCallback
	#define EXT_SysWindowUnregisterCallback
	#define GET_SysWindowUnregisterCallback(fl)  CAL_CMGETAPI( "SysWindowUnregisterCallback" ) 
	#define CAL_SysWindowUnregisterCallback(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowUnregisterCallback(p1,p2) : ((ISysWindow*)p0)->ISysWindowUnregisterCallback(p1,p2))
	#define CHK_SysWindowUnregisterCallback  (pISysWindow != NULL)
	#define EXP_SysWindowUnregisterCallback  CAL_CMEXPAPI( "SysWindowUnregisterCallback" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowUnregisterCallback  PFSYSWINDOWUNREGISTERCALLBACK pfSysWindowUnregisterCallback;
	#define EXT_SysWindowUnregisterCallback  extern PFSYSWINDOWUNREGISTERCALLBACK pfSysWindowUnregisterCallback;
	#define GET_SysWindowUnregisterCallback(fl)  s_pfCMGetAPI2( "SysWindowUnregisterCallback", (RTS_VOID_FCTPTR *)&pfSysWindowUnregisterCallback, (fl), 0, 0)
	#define CAL_SysWindowUnregisterCallback  pfSysWindowUnregisterCallback
	#define CHK_SysWindowUnregisterCallback  (pfSysWindowUnregisterCallback != NULL)
	#define EXP_SysWindowUnregisterCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowUnregisterCallback", (RTS_UINTPTR)SysWindowUnregisterCallback, 0, 0) 
#endif




/**
 * <description>
 *	Function to add invalidate a screen rectangle
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="rect" type="IN"></param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowInvalidateRectangle(RTS_HANDLE hWindow, RTS_Rectangle rect);
typedef RTS_RESULT (CDECL * PFSYSWINDOWINVALIDATERECTANGLE) (RTS_HANDLE hWindow, RTS_Rectangle rect);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWINVALIDATERECTANGLE_NOTIMPLEMENTED)
	#define USE_SysWindowInvalidateRectangle
	#define EXT_SysWindowInvalidateRectangle
	#define GET_SysWindowInvalidateRectangle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowInvalidateRectangle(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowInvalidateRectangle  FALSE
	#define EXP_SysWindowInvalidateRectangle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowInvalidateRectangle
	#define EXT_SysWindowInvalidateRectangle
	#define GET_SysWindowInvalidateRectangle(fl)  CAL_CMGETAPI( "SysWindowInvalidateRectangle" ) 
	#define CAL_SysWindowInvalidateRectangle  SysWindowInvalidateRectangle
	#define CHK_SysWindowInvalidateRectangle  TRUE
	#define EXP_SysWindowInvalidateRectangle  CAL_CMEXPAPI( "SysWindowInvalidateRectangle" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowInvalidateRectangle
	#define EXT_SysWindowInvalidateRectangle
	#define GET_SysWindowInvalidateRectangle(fl)  CAL_CMGETAPI( "SysWindowInvalidateRectangle" ) 
	#define CAL_SysWindowInvalidateRectangle  SysWindowInvalidateRectangle
	#define CHK_SysWindowInvalidateRectangle  TRUE
	#define EXP_SysWindowInvalidateRectangle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowInvalidateRectangle", (RTS_UINTPTR)SysWindowInvalidateRectangle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowInvalidateRectangle
	#define EXT_SysWindowSysWindowInvalidateRectangle
	#define GET_SysWindowSysWindowInvalidateRectangle  ERR_OK
	#define CAL_SysWindowSysWindowInvalidateRectangle(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowInvalidateRectangle(p1) : ((ISysWindow*)p0)->ISysWindowInvalidateRectangle(p1))
	#define CHK_SysWindowSysWindowInvalidateRectangle  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowInvalidateRectangle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowInvalidateRectangle
	#define EXT_SysWindowInvalidateRectangle
	#define GET_SysWindowInvalidateRectangle(fl)  CAL_CMGETAPI( "SysWindowInvalidateRectangle" ) 
	#define CAL_SysWindowInvalidateRectangle(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowInvalidateRectangle(p1) : ((ISysWindow*)p0)->ISysWindowInvalidateRectangle(p1))
	#define CHK_SysWindowInvalidateRectangle  (pISysWindow != NULL)
	#define EXP_SysWindowInvalidateRectangle  CAL_CMEXPAPI( "SysWindowInvalidateRectangle" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowInvalidateRectangle  PFSYSWINDOWINVALIDATERECTANGLE pfSysWindowInvalidateRectangle;
	#define EXT_SysWindowInvalidateRectangle  extern PFSYSWINDOWINVALIDATERECTANGLE pfSysWindowInvalidateRectangle;
	#define GET_SysWindowInvalidateRectangle(fl)  s_pfCMGetAPI2( "SysWindowInvalidateRectangle", (RTS_VOID_FCTPTR *)&pfSysWindowInvalidateRectangle, (fl), 0, 0)
	#define CAL_SysWindowInvalidateRectangle  pfSysWindowInvalidateRectangle
	#define CHK_SysWindowInvalidateRectangle  (pfSysWindowInvalidateRectangle != NULL)
	#define EXP_SysWindowInvalidateRectangle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowInvalidateRectangle", (RTS_UINTPTR)SysWindowInvalidateRectangle, 0, 0) 
#endif




/**
 * <description>
 *	Function to repaint a window. In contrast to <see>SysWindowForceUpdate</see>, this method does not have to trigger an immediate repaint.
 *	It can delay the repaint to the system for performance reasons if necessary.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowUpdate(RTS_HANDLE hWindow);
typedef RTS_RESULT (CDECL * PFSYSWINDOWUPDATE) (RTS_HANDLE hWindow);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWUPDATE_NOTIMPLEMENTED)
	#define USE_SysWindowUpdate
	#define EXT_SysWindowUpdate
	#define GET_SysWindowUpdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowUpdate(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowUpdate  FALSE
	#define EXP_SysWindowUpdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowUpdate
	#define EXT_SysWindowUpdate
	#define GET_SysWindowUpdate(fl)  CAL_CMGETAPI( "SysWindowUpdate" ) 
	#define CAL_SysWindowUpdate  SysWindowUpdate
	#define CHK_SysWindowUpdate  TRUE
	#define EXP_SysWindowUpdate  CAL_CMEXPAPI( "SysWindowUpdate" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowUpdate
	#define EXT_SysWindowUpdate
	#define GET_SysWindowUpdate(fl)  CAL_CMGETAPI( "SysWindowUpdate" ) 
	#define CAL_SysWindowUpdate  SysWindowUpdate
	#define CHK_SysWindowUpdate  TRUE
	#define EXP_SysWindowUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowUpdate", (RTS_UINTPTR)SysWindowUpdate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowUpdate
	#define EXT_SysWindowSysWindowUpdate
	#define GET_SysWindowSysWindowUpdate  ERR_OK
	#define CAL_SysWindowSysWindowUpdate(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowUpdate() : ((ISysWindow*)p0)->ISysWindowUpdate())
	#define CHK_SysWindowSysWindowUpdate  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowUpdate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowUpdate
	#define EXT_SysWindowUpdate
	#define GET_SysWindowUpdate(fl)  CAL_CMGETAPI( "SysWindowUpdate" ) 
	#define CAL_SysWindowUpdate(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowUpdate() : ((ISysWindow*)p0)->ISysWindowUpdate())
	#define CHK_SysWindowUpdate  (pISysWindow != NULL)
	#define EXP_SysWindowUpdate  CAL_CMEXPAPI( "SysWindowUpdate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowUpdate  PFSYSWINDOWUPDATE pfSysWindowUpdate;
	#define EXT_SysWindowUpdate  extern PFSYSWINDOWUPDATE pfSysWindowUpdate;
	#define GET_SysWindowUpdate(fl)  s_pfCMGetAPI2( "SysWindowUpdate", (RTS_VOID_FCTPTR *)&pfSysWindowUpdate, (fl), 0, 0)
	#define CAL_SysWindowUpdate  pfSysWindowUpdate
	#define CHK_SysWindowUpdate  (pfSysWindowUpdate != NULL)
	#define EXP_SysWindowUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowUpdate", (RTS_UINTPTR)SysWindowUpdate, 0, 0) 
#endif




/**
 * <description>
 *	Function that causes an immediate repaint of a window. In contrast to <see>SysWindowUpdate</see>, this method must trigger an immediate repaint.
 *	The intention of this method is to redraw immediately which can be used for animations for example.
 *	On systems where <see>SysWindowUpdate</see> already triggered an immediate repaint, this method can simply call <see>SysWindowUpdate</see>.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowForceUpdate(RTS_HANDLE hWindow);
typedef RTS_RESULT (CDECL * PFSYSWINDOWFORCEUPDATE) (RTS_HANDLE hWindow);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWFORCEUPDATE_NOTIMPLEMENTED)
	#define USE_SysWindowForceUpdate
	#define EXT_SysWindowForceUpdate
	#define GET_SysWindowForceUpdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowForceUpdate(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowForceUpdate  FALSE
	#define EXP_SysWindowForceUpdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowForceUpdate
	#define EXT_SysWindowForceUpdate
	#define GET_SysWindowForceUpdate(fl)  CAL_CMGETAPI( "SysWindowForceUpdate" ) 
	#define CAL_SysWindowForceUpdate  SysWindowForceUpdate
	#define CHK_SysWindowForceUpdate  TRUE
	#define EXP_SysWindowForceUpdate  CAL_CMEXPAPI( "SysWindowForceUpdate" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowForceUpdate
	#define EXT_SysWindowForceUpdate
	#define GET_SysWindowForceUpdate(fl)  CAL_CMGETAPI( "SysWindowForceUpdate" ) 
	#define CAL_SysWindowForceUpdate  SysWindowForceUpdate
	#define CHK_SysWindowForceUpdate  TRUE
	#define EXP_SysWindowForceUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowForceUpdate", (RTS_UINTPTR)SysWindowForceUpdate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowForceUpdate
	#define EXT_SysWindowSysWindowForceUpdate
	#define GET_SysWindowSysWindowForceUpdate  ERR_OK
	#define CAL_SysWindowSysWindowForceUpdate(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowForceUpdate() : ((ISysWindow*)p0)->ISysWindowForceUpdate())
	#define CHK_SysWindowSysWindowForceUpdate  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowForceUpdate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowForceUpdate
	#define EXT_SysWindowForceUpdate
	#define GET_SysWindowForceUpdate(fl)  CAL_CMGETAPI( "SysWindowForceUpdate" ) 
	#define CAL_SysWindowForceUpdate(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowForceUpdate() : ((ISysWindow*)p0)->ISysWindowForceUpdate())
	#define CHK_SysWindowForceUpdate  (pISysWindow != NULL)
	#define EXP_SysWindowForceUpdate  CAL_CMEXPAPI( "SysWindowForceUpdate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowForceUpdate  PFSYSWINDOWFORCEUPDATE pfSysWindowForceUpdate;
	#define EXT_SysWindowForceUpdate  extern PFSYSWINDOWFORCEUPDATE pfSysWindowForceUpdate;
	#define GET_SysWindowForceUpdate(fl)  s_pfCMGetAPI2( "SysWindowForceUpdate", (RTS_VOID_FCTPTR *)&pfSysWindowForceUpdate, (fl), 0, 0)
	#define CAL_SysWindowForceUpdate  pfSysWindowForceUpdate
	#define CHK_SysWindowForceUpdate  (pfSysWindowForceUpdate != NULL)
	#define EXP_SysWindowForceUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowForceUpdate", (RTS_UINTPTR)SysWindowForceUpdate, 0, 0) 
#endif




/**
 * <description>
 *	Function to retrieve the rectangle of a window (including a title bar etc)
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pRect" type="IN"></param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowGetPos(RTS_HANDLE hWindow, RTS_Rectangle* pRect);
typedef RTS_RESULT (CDECL * PFSYSWINDOWGETPOS) (RTS_HANDLE hWindow, RTS_Rectangle* pRect);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWGETPOS_NOTIMPLEMENTED)
	#define USE_SysWindowGetPos
	#define EXT_SysWindowGetPos
	#define GET_SysWindowGetPos(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowGetPos(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowGetPos  FALSE
	#define EXP_SysWindowGetPos  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowGetPos
	#define EXT_SysWindowGetPos
	#define GET_SysWindowGetPos(fl)  CAL_CMGETAPI( "SysWindowGetPos" ) 
	#define CAL_SysWindowGetPos  SysWindowGetPos
	#define CHK_SysWindowGetPos  TRUE
	#define EXP_SysWindowGetPos  CAL_CMEXPAPI( "SysWindowGetPos" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowGetPos
	#define EXT_SysWindowGetPos
	#define GET_SysWindowGetPos(fl)  CAL_CMGETAPI( "SysWindowGetPos" ) 
	#define CAL_SysWindowGetPos  SysWindowGetPos
	#define CHK_SysWindowGetPos  TRUE
	#define EXP_SysWindowGetPos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowGetPos", (RTS_UINTPTR)SysWindowGetPos, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowGetPos
	#define EXT_SysWindowSysWindowGetPos
	#define GET_SysWindowSysWindowGetPos  ERR_OK
	#define CAL_SysWindowSysWindowGetPos(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowGetPos(p1) : ((ISysWindow*)p0)->ISysWindowGetPos(p1))
	#define CHK_SysWindowSysWindowGetPos  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowGetPos  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowGetPos
	#define EXT_SysWindowGetPos
	#define GET_SysWindowGetPos(fl)  CAL_CMGETAPI( "SysWindowGetPos" ) 
	#define CAL_SysWindowGetPos(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowGetPos(p1) : ((ISysWindow*)p0)->ISysWindowGetPos(p1))
	#define CHK_SysWindowGetPos  (pISysWindow != NULL)
	#define EXP_SysWindowGetPos  CAL_CMEXPAPI( "SysWindowGetPos" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowGetPos  PFSYSWINDOWGETPOS pfSysWindowGetPos;
	#define EXT_SysWindowGetPos  extern PFSYSWINDOWGETPOS pfSysWindowGetPos;
	#define GET_SysWindowGetPos(fl)  s_pfCMGetAPI2( "SysWindowGetPos", (RTS_VOID_FCTPTR *)&pfSysWindowGetPos, (fl), 0, 0)
	#define CAL_SysWindowGetPos  pfSysWindowGetPos
	#define CHK_SysWindowGetPos  (pfSysWindowGetPos != NULL)
	#define EXP_SysWindowGetPos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowGetPos", (RTS_UINTPTR)SysWindowGetPos, 0, 0) 
#endif




/**
 * <description>
 *	Function to set the position of a window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="rect" type="IN"></param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowSetPos(RTS_HANDLE hWindow, RTS_Rectangle rect);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSETPOS) (RTS_HANDLE hWindow, RTS_Rectangle rect);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSETPOS_NOTIMPLEMENTED)
	#define USE_SysWindowSetPos
	#define EXT_SysWindowSetPos
	#define GET_SysWindowSetPos(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSetPos(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSetPos  FALSE
	#define EXP_SysWindowSetPos  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSetPos
	#define EXT_SysWindowSetPos
	#define GET_SysWindowSetPos(fl)  CAL_CMGETAPI( "SysWindowSetPos" ) 
	#define CAL_SysWindowSetPos  SysWindowSetPos
	#define CHK_SysWindowSetPos  TRUE
	#define EXP_SysWindowSetPos  CAL_CMEXPAPI( "SysWindowSetPos" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSetPos
	#define EXT_SysWindowSetPos
	#define GET_SysWindowSetPos(fl)  CAL_CMGETAPI( "SysWindowSetPos" ) 
	#define CAL_SysWindowSetPos  SysWindowSetPos
	#define CHK_SysWindowSetPos  TRUE
	#define EXP_SysWindowSetPos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetPos", (RTS_UINTPTR)SysWindowSetPos, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSetPos
	#define EXT_SysWindowSysWindowSetPos
	#define GET_SysWindowSysWindowSetPos  ERR_OK
	#define CAL_SysWindowSysWindowSetPos(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetPos(p1) : ((ISysWindow*)p0)->ISysWindowSetPos(p1))
	#define CHK_SysWindowSysWindowSetPos  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowSetPos  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSetPos
	#define EXT_SysWindowSetPos
	#define GET_SysWindowSetPos(fl)  CAL_CMGETAPI( "SysWindowSetPos" ) 
	#define CAL_SysWindowSetPos(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetPos(p1) : ((ISysWindow*)p0)->ISysWindowSetPos(p1))
	#define CHK_SysWindowSetPos  (pISysWindow != NULL)
	#define EXP_SysWindowSetPos  CAL_CMEXPAPI( "SysWindowSetPos" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSetPos  PFSYSWINDOWSETPOS pfSysWindowSetPos;
	#define EXT_SysWindowSetPos  extern PFSYSWINDOWSETPOS pfSysWindowSetPos;
	#define GET_SysWindowSetPos(fl)  s_pfCMGetAPI2( "SysWindowSetPos", (RTS_VOID_FCTPTR *)&pfSysWindowSetPos, (fl), 0, 0)
	#define CAL_SysWindowSetPos  pfSysWindowSetPos
	#define CHK_SysWindowSetPos  (pfSysWindowSetPos != NULL)
	#define EXP_SysWindowSetPos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetPos", (RTS_UINTPTR)SysWindowSetPos, 0, 0) 
#endif




/**
 * <description>
 *	Function to retrieve the client rectangle of a window (without a title bar)
 * </description>
 * <remarks>The rectangle should cover exactly the region that is available for drawing. Typically 0/0 -> clientwidth - 1/clientheight - 1 
 *	is the result.</remarks>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pRect" type="IN"></param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowGetClientRectangle(RTS_HANDLE hWindow, RTS_Rectangle* pRect);
typedef RTS_RESULT (CDECL * PFSYSWINDOWGETCLIENTRECTANGLE) (RTS_HANDLE hWindow, RTS_Rectangle* pRect);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWGETCLIENTRECTANGLE_NOTIMPLEMENTED)
	#define USE_SysWindowGetClientRectangle
	#define EXT_SysWindowGetClientRectangle
	#define GET_SysWindowGetClientRectangle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowGetClientRectangle(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowGetClientRectangle  FALSE
	#define EXP_SysWindowGetClientRectangle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowGetClientRectangle
	#define EXT_SysWindowGetClientRectangle
	#define GET_SysWindowGetClientRectangle(fl)  CAL_CMGETAPI( "SysWindowGetClientRectangle" ) 
	#define CAL_SysWindowGetClientRectangle  SysWindowGetClientRectangle
	#define CHK_SysWindowGetClientRectangle  TRUE
	#define EXP_SysWindowGetClientRectangle  CAL_CMEXPAPI( "SysWindowGetClientRectangle" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowGetClientRectangle
	#define EXT_SysWindowGetClientRectangle
	#define GET_SysWindowGetClientRectangle(fl)  CAL_CMGETAPI( "SysWindowGetClientRectangle" ) 
	#define CAL_SysWindowGetClientRectangle  SysWindowGetClientRectangle
	#define CHK_SysWindowGetClientRectangle  TRUE
	#define EXP_SysWindowGetClientRectangle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowGetClientRectangle", (RTS_UINTPTR)SysWindowGetClientRectangle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowGetClientRectangle
	#define EXT_SysWindowSysWindowGetClientRectangle
	#define GET_SysWindowSysWindowGetClientRectangle  ERR_OK
	#define CAL_SysWindowSysWindowGetClientRectangle(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowGetClientRectangle(p1) : ((ISysWindow*)p0)->ISysWindowGetClientRectangle(p1))
	#define CHK_SysWindowSysWindowGetClientRectangle  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowGetClientRectangle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowGetClientRectangle
	#define EXT_SysWindowGetClientRectangle
	#define GET_SysWindowGetClientRectangle(fl)  CAL_CMGETAPI( "SysWindowGetClientRectangle" ) 
	#define CAL_SysWindowGetClientRectangle(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowGetClientRectangle(p1) : ((ISysWindow*)p0)->ISysWindowGetClientRectangle(p1))
	#define CHK_SysWindowGetClientRectangle  (pISysWindow != NULL)
	#define EXP_SysWindowGetClientRectangle  CAL_CMEXPAPI( "SysWindowGetClientRectangle" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowGetClientRectangle  PFSYSWINDOWGETCLIENTRECTANGLE pfSysWindowGetClientRectangle;
	#define EXT_SysWindowGetClientRectangle  extern PFSYSWINDOWGETCLIENTRECTANGLE pfSysWindowGetClientRectangle;
	#define GET_SysWindowGetClientRectangle(fl)  s_pfCMGetAPI2( "SysWindowGetClientRectangle", (RTS_VOID_FCTPTR *)&pfSysWindowGetClientRectangle, (fl), 0, 0)
	#define CAL_SysWindowGetClientRectangle  pfSysWindowGetClientRectangle
	#define CHK_SysWindowGetClientRectangle  (pfSysWindowGetClientRectangle != NULL)
	#define EXP_SysWindowGetClientRectangle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowGetClientRectangle", (RTS_UINTPTR)SysWindowGetClientRectangle, 0, 0) 
#endif




/**
 * <description>
 *	Function to set the font in a window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="hFont" type="IN"></param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowSetFont(RTS_HANDLE hWindow, RTS_HANDLE hFont);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSETFONT) (RTS_HANDLE hWindow, RTS_HANDLE hFont);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSETFONT_NOTIMPLEMENTED)
	#define USE_SysWindowSetFont
	#define EXT_SysWindowSetFont
	#define GET_SysWindowSetFont(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSetFont(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSetFont  FALSE
	#define EXP_SysWindowSetFont  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSetFont
	#define EXT_SysWindowSetFont
	#define GET_SysWindowSetFont(fl)  CAL_CMGETAPI( "SysWindowSetFont" ) 
	#define CAL_SysWindowSetFont  SysWindowSetFont
	#define CHK_SysWindowSetFont  TRUE
	#define EXP_SysWindowSetFont  CAL_CMEXPAPI( "SysWindowSetFont" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSetFont
	#define EXT_SysWindowSetFont
	#define GET_SysWindowSetFont(fl)  CAL_CMGETAPI( "SysWindowSetFont" ) 
	#define CAL_SysWindowSetFont  SysWindowSetFont
	#define CHK_SysWindowSetFont  TRUE
	#define EXP_SysWindowSetFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetFont", (RTS_UINTPTR)SysWindowSetFont, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSetFont
	#define EXT_SysWindowSysWindowSetFont
	#define GET_SysWindowSysWindowSetFont  ERR_OK
	#define CAL_SysWindowSysWindowSetFont(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetFont(p1) : ((ISysWindow*)p0)->ISysWindowSetFont(p1))
	#define CHK_SysWindowSysWindowSetFont  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowSetFont  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSetFont
	#define EXT_SysWindowSetFont
	#define GET_SysWindowSetFont(fl)  CAL_CMGETAPI( "SysWindowSetFont" ) 
	#define CAL_SysWindowSetFont(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetFont(p1) : ((ISysWindow*)p0)->ISysWindowSetFont(p1))
	#define CHK_SysWindowSetFont  (pISysWindow != NULL)
	#define EXP_SysWindowSetFont  CAL_CMEXPAPI( "SysWindowSetFont" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSetFont  PFSYSWINDOWSETFONT pfSysWindowSetFont;
	#define EXT_SysWindowSetFont  extern PFSYSWINDOWSETFONT pfSysWindowSetFont;
	#define GET_SysWindowSetFont(fl)  s_pfCMGetAPI2( "SysWindowSetFont", (RTS_VOID_FCTPTR *)&pfSysWindowSetFont, (fl), 0, 0)
	#define CAL_SysWindowSetFont  pfSysWindowSetFont
	#define CHK_SysWindowSetFont  (pfSysWindowSetFont != NULL)
	#define EXP_SysWindowSetFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetFont", (RTS_UINTPTR)SysWindowSetFont, 0, 0) 
#endif




/**
 * <description>
 *	Function to get the font in a window. Please remember that this function is not yet completely defined.
 *	For the moment it is ok to have an empty implementation returning ERR_NOTIMPLEMENTED.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="phFont" type="IN"></param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowGetFont(RTS_HANDLE hWindow, RTS_HANDLE* phFont);
typedef RTS_RESULT (CDECL * PFSYSWINDOWGETFONT) (RTS_HANDLE hWindow, RTS_HANDLE* phFont);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWGETFONT_NOTIMPLEMENTED)
	#define USE_SysWindowGetFont
	#define EXT_SysWindowGetFont
	#define GET_SysWindowGetFont(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowGetFont(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowGetFont  FALSE
	#define EXP_SysWindowGetFont  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowGetFont
	#define EXT_SysWindowGetFont
	#define GET_SysWindowGetFont(fl)  CAL_CMGETAPI( "SysWindowGetFont" ) 
	#define CAL_SysWindowGetFont  SysWindowGetFont
	#define CHK_SysWindowGetFont  TRUE
	#define EXP_SysWindowGetFont  CAL_CMEXPAPI( "SysWindowGetFont" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowGetFont
	#define EXT_SysWindowGetFont
	#define GET_SysWindowGetFont(fl)  CAL_CMGETAPI( "SysWindowGetFont" ) 
	#define CAL_SysWindowGetFont  SysWindowGetFont
	#define CHK_SysWindowGetFont  TRUE
	#define EXP_SysWindowGetFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowGetFont", (RTS_UINTPTR)SysWindowGetFont, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowGetFont
	#define EXT_SysWindowSysWindowGetFont
	#define GET_SysWindowSysWindowGetFont  ERR_OK
	#define CAL_SysWindowSysWindowGetFont(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowGetFont(p1) : ((ISysWindow*)p0)->ISysWindowGetFont(p1))
	#define CHK_SysWindowSysWindowGetFont  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowGetFont  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowGetFont
	#define EXT_SysWindowGetFont
	#define GET_SysWindowGetFont(fl)  CAL_CMGETAPI( "SysWindowGetFont" ) 
	#define CAL_SysWindowGetFont(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowGetFont(p1) : ((ISysWindow*)p0)->ISysWindowGetFont(p1))
	#define CHK_SysWindowGetFont  (pISysWindow != NULL)
	#define EXP_SysWindowGetFont  CAL_CMEXPAPI( "SysWindowGetFont" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowGetFont  PFSYSWINDOWGETFONT pfSysWindowGetFont;
	#define EXT_SysWindowGetFont  extern PFSYSWINDOWGETFONT pfSysWindowGetFont;
	#define GET_SysWindowGetFont(fl)  s_pfCMGetAPI2( "SysWindowGetFont", (RTS_VOID_FCTPTR *)&pfSysWindowGetFont, (fl), 0, 0)
	#define CAL_SysWindowGetFont  pfSysWindowGetFont
	#define CHK_SysWindowGetFont  (pfSysWindowGetFont != NULL)
	#define EXP_SysWindowGetFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowGetFont", (RTS_UINTPTR)SysWindowGetFont, 0, 0) 
#endif




/**
 * <description>Get the Text of a window</description>
 * <param name="ulWindow" type="IN">The handle to the window</param>
 * <param name="pszValue" type="INOUT">Pointer to value for result</param>
 * <param name="piLen" type="INOUT">Max length of string value as IN and length of copied values as OUT</param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
RTS_RESULT CDECL SysWindowGetText(RTS_HANDLE hWindow, char* pszValue, RTS_SIZE* piLen);
typedef RTS_RESULT (CDECL * PFSYSWINDOWGETTEXT) (RTS_HANDLE hWindow, char* pszValue, RTS_SIZE* piLen);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWGETTEXT_NOTIMPLEMENTED)
	#define USE_SysWindowGetText
	#define EXT_SysWindowGetText
	#define GET_SysWindowGetText(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowGetText(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowGetText  FALSE
	#define EXP_SysWindowGetText  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowGetText
	#define EXT_SysWindowGetText
	#define GET_SysWindowGetText(fl)  CAL_CMGETAPI( "SysWindowGetText" ) 
	#define CAL_SysWindowGetText  SysWindowGetText
	#define CHK_SysWindowGetText  TRUE
	#define EXP_SysWindowGetText  CAL_CMEXPAPI( "SysWindowGetText" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowGetText
	#define EXT_SysWindowGetText
	#define GET_SysWindowGetText(fl)  CAL_CMGETAPI( "SysWindowGetText" ) 
	#define CAL_SysWindowGetText  SysWindowGetText
	#define CHK_SysWindowGetText  TRUE
	#define EXP_SysWindowGetText  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowGetText", (RTS_UINTPTR)SysWindowGetText, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowGetText
	#define EXT_SysWindowSysWindowGetText
	#define GET_SysWindowSysWindowGetText  ERR_OK
	#define CAL_SysWindowSysWindowGetText(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowGetText(p1,p2) : ((ISysWindow*)p0)->ISysWindowGetText(p1,p2))
	#define CHK_SysWindowSysWindowGetText  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowGetText  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowGetText
	#define EXT_SysWindowGetText
	#define GET_SysWindowGetText(fl)  CAL_CMGETAPI( "SysWindowGetText" ) 
	#define CAL_SysWindowGetText(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowGetText(p1,p2) : ((ISysWindow*)p0)->ISysWindowGetText(p1,p2))
	#define CHK_SysWindowGetText  (pISysWindow != NULL)
	#define EXP_SysWindowGetText  CAL_CMEXPAPI( "SysWindowGetText" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowGetText  PFSYSWINDOWGETTEXT pfSysWindowGetText;
	#define EXT_SysWindowGetText  extern PFSYSWINDOWGETTEXT pfSysWindowGetText;
	#define GET_SysWindowGetText(fl)  s_pfCMGetAPI2( "SysWindowGetText", (RTS_VOID_FCTPTR *)&pfSysWindowGetText, (fl), 0, 0)
	#define CAL_SysWindowGetText  pfSysWindowGetText
	#define CHK_SysWindowGetText  (pfSysWindowGetText != NULL)
	#define EXP_SysWindowGetText  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowGetText", (RTS_UINTPTR)SysWindowGetText, 0, 0) 
#endif




/**
 * <description>
 *	Function to set the text in a window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pszText" type="IN"></param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowSetText(RTS_HANDLE hWindow, char* pszText);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSETTEXT) (RTS_HANDLE hWindow, char* pszText);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSETTEXT_NOTIMPLEMENTED)
	#define USE_SysWindowSetText
	#define EXT_SysWindowSetText
	#define GET_SysWindowSetText(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSetText(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSetText  FALSE
	#define EXP_SysWindowSetText  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSetText
	#define EXT_SysWindowSetText
	#define GET_SysWindowSetText(fl)  CAL_CMGETAPI( "SysWindowSetText" ) 
	#define CAL_SysWindowSetText  SysWindowSetText
	#define CHK_SysWindowSetText  TRUE
	#define EXP_SysWindowSetText  CAL_CMEXPAPI( "SysWindowSetText" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSetText
	#define EXT_SysWindowSetText
	#define GET_SysWindowSetText(fl)  CAL_CMGETAPI( "SysWindowSetText" ) 
	#define CAL_SysWindowSetText  SysWindowSetText
	#define CHK_SysWindowSetText  TRUE
	#define EXP_SysWindowSetText  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetText", (RTS_UINTPTR)SysWindowSetText, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSetText
	#define EXT_SysWindowSysWindowSetText
	#define GET_SysWindowSysWindowSetText  ERR_OK
	#define CAL_SysWindowSysWindowSetText(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetText(p1) : ((ISysWindow*)p0)->ISysWindowSetText(p1))
	#define CHK_SysWindowSysWindowSetText  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowSetText  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSetText
	#define EXT_SysWindowSetText
	#define GET_SysWindowSetText(fl)  CAL_CMGETAPI( "SysWindowSetText" ) 
	#define CAL_SysWindowSetText(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetText(p1) : ((ISysWindow*)p0)->ISysWindowSetText(p1))
	#define CHK_SysWindowSetText  (pISysWindow != NULL)
	#define EXP_SysWindowSetText  CAL_CMEXPAPI( "SysWindowSetText" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSetText  PFSYSWINDOWSETTEXT pfSysWindowSetText;
	#define EXT_SysWindowSetText  extern PFSYSWINDOWSETTEXT pfSysWindowSetText;
	#define GET_SysWindowSetText(fl)  s_pfCMGetAPI2( "SysWindowSetText", (RTS_VOID_FCTPTR *)&pfSysWindowSetText, (fl), 0, 0)
	#define CAL_SysWindowSetText  pfSysWindowSetText
	#define CHK_SysWindowSetText  (pfSysWindowSetText != NULL)
	#define EXP_SysWindowSetText  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetText", (RTS_UINTPTR)SysWindowSetText, 0, 0) 
#endif




/**
 * <description>
 *	Function to set the unicode text in a window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pszText" type="IN"></param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowSetTextW(RTS_HANDLE hWindow, RTS_WCHAR* pwsText);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSETTEXTW) (RTS_HANDLE hWindow, RTS_WCHAR* pwsText);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSETTEXTW_NOTIMPLEMENTED)
	#define USE_SysWindowSetTextW
	#define EXT_SysWindowSetTextW
	#define GET_SysWindowSetTextW(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSetTextW(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSetTextW  FALSE
	#define EXP_SysWindowSetTextW  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSetTextW
	#define EXT_SysWindowSetTextW
	#define GET_SysWindowSetTextW(fl)  CAL_CMGETAPI( "SysWindowSetTextW" ) 
	#define CAL_SysWindowSetTextW  SysWindowSetTextW
	#define CHK_SysWindowSetTextW  TRUE
	#define EXP_SysWindowSetTextW  CAL_CMEXPAPI( "SysWindowSetTextW" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSetTextW
	#define EXT_SysWindowSetTextW
	#define GET_SysWindowSetTextW(fl)  CAL_CMGETAPI( "SysWindowSetTextW" ) 
	#define CAL_SysWindowSetTextW  SysWindowSetTextW
	#define CHK_SysWindowSetTextW  TRUE
	#define EXP_SysWindowSetTextW  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetTextW", (RTS_UINTPTR)SysWindowSetTextW, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSetTextW
	#define EXT_SysWindowSysWindowSetTextW
	#define GET_SysWindowSysWindowSetTextW  ERR_OK
	#define CAL_SysWindowSysWindowSetTextW(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetTextW(p1) : ((ISysWindow*)p0)->ISysWindowSetTextW(p1))
	#define CHK_SysWindowSysWindowSetTextW  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowSetTextW  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSetTextW
	#define EXT_SysWindowSetTextW
	#define GET_SysWindowSetTextW(fl)  CAL_CMGETAPI( "SysWindowSetTextW" ) 
	#define CAL_SysWindowSetTextW(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetTextW(p1) : ((ISysWindow*)p0)->ISysWindowSetTextW(p1))
	#define CHK_SysWindowSetTextW  (pISysWindow != NULL)
	#define EXP_SysWindowSetTextW  CAL_CMEXPAPI( "SysWindowSetTextW" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSetTextW  PFSYSWINDOWSETTEXTW pfSysWindowSetTextW;
	#define EXT_SysWindowSetTextW  extern PFSYSWINDOWSETTEXTW pfSysWindowSetTextW;
	#define GET_SysWindowSetTextW(fl)  s_pfCMGetAPI2( "SysWindowSetTextW", (RTS_VOID_FCTPTR *)&pfSysWindowSetTextW, (fl), 0, 0)
	#define CAL_SysWindowSetTextW  pfSysWindowSetTextW
	#define CHK_SysWindowSetTextW  (pfSysWindowSetTextW != NULL)
	#define EXP_SysWindowSetTextW  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetTextW", (RTS_UINTPTR)SysWindowSetTextW, 0, 0) 
#endif




/**
 * <description>
 *	Function to set the input focus to a specific window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowSetFocus(RTS_HANDLE hWindow);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSETFOCUS) (RTS_HANDLE hWindow);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSETFOCUS_NOTIMPLEMENTED)
	#define USE_SysWindowSetFocus
	#define EXT_SysWindowSetFocus
	#define GET_SysWindowSetFocus(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSetFocus(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSetFocus  FALSE
	#define EXP_SysWindowSetFocus  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSetFocus
	#define EXT_SysWindowSetFocus
	#define GET_SysWindowSetFocus(fl)  CAL_CMGETAPI( "SysWindowSetFocus" ) 
	#define CAL_SysWindowSetFocus  SysWindowSetFocus
	#define CHK_SysWindowSetFocus  TRUE
	#define EXP_SysWindowSetFocus  CAL_CMEXPAPI( "SysWindowSetFocus" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSetFocus
	#define EXT_SysWindowSetFocus
	#define GET_SysWindowSetFocus(fl)  CAL_CMGETAPI( "SysWindowSetFocus" ) 
	#define CAL_SysWindowSetFocus  SysWindowSetFocus
	#define CHK_SysWindowSetFocus  TRUE
	#define EXP_SysWindowSetFocus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetFocus", (RTS_UINTPTR)SysWindowSetFocus, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSetFocus
	#define EXT_SysWindowSysWindowSetFocus
	#define GET_SysWindowSysWindowSetFocus  ERR_OK
	#define CAL_SysWindowSysWindowSetFocus(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetFocus() : ((ISysWindow*)p0)->ISysWindowSetFocus())
	#define CHK_SysWindowSysWindowSetFocus  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowSetFocus  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSetFocus
	#define EXT_SysWindowSetFocus
	#define GET_SysWindowSetFocus(fl)  CAL_CMGETAPI( "SysWindowSetFocus" ) 
	#define CAL_SysWindowSetFocus(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetFocus() : ((ISysWindow*)p0)->ISysWindowSetFocus())
	#define CHK_SysWindowSetFocus  (pISysWindow != NULL)
	#define EXP_SysWindowSetFocus  CAL_CMEXPAPI( "SysWindowSetFocus" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSetFocus  PFSYSWINDOWSETFOCUS pfSysWindowSetFocus;
	#define EXT_SysWindowSetFocus  extern PFSYSWINDOWSETFOCUS pfSysWindowSetFocus;
	#define GET_SysWindowSetFocus(fl)  s_pfCMGetAPI2( "SysWindowSetFocus", (RTS_VOID_FCTPTR *)&pfSysWindowSetFocus, (fl), 0, 0)
	#define CAL_SysWindowSetFocus  pfSysWindowSetFocus
	#define CHK_SysWindowSetFocus  (pfSysWindowSetFocus != NULL)
	#define EXP_SysWindowSetFocus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetFocus", (RTS_UINTPTR)SysWindowSetFocus, 0, 0) 
#endif




/**
 * <description>
 *	Function to set the selection in a window. In case of an edit control, the specified range of text will be highlighted and selected. For
 *	users of this control, that means, they can start entering text and the selected range will be overwritten.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pszClassName" type="IN">The class name of the affected window. At the moment, this feature is only implemented
 *	for the window class "TargetVisu_EditControl".</param>
 * <param name="dwParam1" type="IN">Parameter to specify details for the selection. In case of <see>pszClassName</see>=="TargetVisu_EditControl", 
 *	this will be the start index of the selection. 0 will be given to start the selection at the beginning of the text.</param>
 * <param name="dwParam2" type="IN">Parameter to specify details for the selection. In case of <see>pszClassName</see>=="TargetVisu_EditControl", 
 *	this will be the end index of the selection..</param>
 * <note>If the start is 0 and the end is -1, all the text in the edit control is selected. If the start is -1, the current selection is deselected.</note>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowSetSelection(RTS_HANDLE hWindow, char* pszClassName, RTS_I32 dwParam1, RTS_I32 dwParam2);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSETSELECTION) (RTS_HANDLE hWindow, char* pszClassName, RTS_I32 dwParam1, RTS_I32 dwParam2);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSETSELECTION_NOTIMPLEMENTED)
	#define USE_SysWindowSetSelection
	#define EXT_SysWindowSetSelection
	#define GET_SysWindowSetSelection(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSetSelection(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSetSelection  FALSE
	#define EXP_SysWindowSetSelection  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSetSelection
	#define EXT_SysWindowSetSelection
	#define GET_SysWindowSetSelection(fl)  CAL_CMGETAPI( "SysWindowSetSelection" ) 
	#define CAL_SysWindowSetSelection  SysWindowSetSelection
	#define CHK_SysWindowSetSelection  TRUE
	#define EXP_SysWindowSetSelection  CAL_CMEXPAPI( "SysWindowSetSelection" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSetSelection
	#define EXT_SysWindowSetSelection
	#define GET_SysWindowSetSelection(fl)  CAL_CMGETAPI( "SysWindowSetSelection" ) 
	#define CAL_SysWindowSetSelection  SysWindowSetSelection
	#define CHK_SysWindowSetSelection  TRUE
	#define EXP_SysWindowSetSelection  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetSelection", (RTS_UINTPTR)SysWindowSetSelection, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSetSelection
	#define EXT_SysWindowSysWindowSetSelection
	#define GET_SysWindowSysWindowSetSelection  ERR_OK
	#define CAL_SysWindowSysWindowSetSelection(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetSelection(p1,p2,p3) : ((ISysWindow*)p0)->ISysWindowSetSelection(p1,p2,p3))
	#define CHK_SysWindowSysWindowSetSelection  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowSetSelection  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSetSelection
	#define EXT_SysWindowSetSelection
	#define GET_SysWindowSetSelection(fl)  CAL_CMGETAPI( "SysWindowSetSelection" ) 
	#define CAL_SysWindowSetSelection(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetSelection(p1,p2,p3) : ((ISysWindow*)p0)->ISysWindowSetSelection(p1,p2,p3))
	#define CHK_SysWindowSetSelection  (pISysWindow != NULL)
	#define EXP_SysWindowSetSelection  CAL_CMEXPAPI( "SysWindowSetSelection" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSetSelection  PFSYSWINDOWSETSELECTION pfSysWindowSetSelection;
	#define EXT_SysWindowSetSelection  extern PFSYSWINDOWSETSELECTION pfSysWindowSetSelection;
	#define GET_SysWindowSetSelection(fl)  s_pfCMGetAPI2( "SysWindowSetSelection", (RTS_VOID_FCTPTR *)&pfSysWindowSetSelection, (fl), 0, 0)
	#define CAL_SysWindowSetSelection  pfSysWindowSetSelection
	#define CHK_SysWindowSetSelection  (pfSysWindowSetSelection != NULL)
	#define EXP_SysWindowSetSelection  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetSelection", (RTS_UINTPTR)SysWindowSetSelection, 0, 0) 
#endif




/**
 * <description>Enumeration of different cursor types. Identical to VisuEnumCursor from VisuElemBase.library</description>
 */
typedef enum 
{
	SYSWINCUR_DEFAULT, 
	SYSWINCUR_ARROW, 
	SYSWINCUR_HAND, 
	SYSWINCUR_WAIT, 
	SYSWINCUR_IBEAM, 
	SYSWINCUR_CROSS, 
	SYSWINCUR_HELP, 
	SYSWINCUR_HSPLIT, 
	SYSWINCUR_VSPLIT, 
	SYSWINCUR_SIZENWSE, 
	SYSWINCUR_SIZENESW, 
	SYSWINCUR_SIZEWE, 
	SYSWINCUR_SIZENS, 
	SYSWINCUR_SIZEALL,
	SYSWINCUR_INVISIBLE
} SysWindowCursor;

/**
 * <description>function to set the currently visible cursor</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="usCursor" type="IN">A value of the enumeration <see>SysWindowCursor</see></param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysWindowSetCursor(RTS_HANDLE hWindow, RTS_UI16 usCursor);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSETCURSOR) (RTS_HANDLE hWindow, RTS_UI16 usCursor);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSETCURSOR_NOTIMPLEMENTED)
	#define USE_SysWindowSetCursor
	#define EXT_SysWindowSetCursor
	#define GET_SysWindowSetCursor(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSetCursor(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSetCursor  FALSE
	#define EXP_SysWindowSetCursor  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSetCursor
	#define EXT_SysWindowSetCursor
	#define GET_SysWindowSetCursor(fl)  CAL_CMGETAPI( "SysWindowSetCursor" ) 
	#define CAL_SysWindowSetCursor  SysWindowSetCursor
	#define CHK_SysWindowSetCursor  TRUE
	#define EXP_SysWindowSetCursor  CAL_CMEXPAPI( "SysWindowSetCursor" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSetCursor
	#define EXT_SysWindowSetCursor
	#define GET_SysWindowSetCursor(fl)  CAL_CMGETAPI( "SysWindowSetCursor" ) 
	#define CAL_SysWindowSetCursor  SysWindowSetCursor
	#define CHK_SysWindowSetCursor  TRUE
	#define EXP_SysWindowSetCursor  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetCursor", (RTS_UINTPTR)SysWindowSetCursor, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSetCursor
	#define EXT_SysWindowSysWindowSetCursor
	#define GET_SysWindowSysWindowSetCursor  ERR_OK
	#define CAL_SysWindowSysWindowSetCursor(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetCursor(p1) : ((ISysWindow*)p0)->ISysWindowSetCursor(p1))
	#define CHK_SysWindowSysWindowSetCursor  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowSetCursor  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSetCursor
	#define EXT_SysWindowSetCursor
	#define GET_SysWindowSetCursor(fl)  CAL_CMGETAPI( "SysWindowSetCursor" ) 
	#define CAL_SysWindowSetCursor(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetCursor(p1) : ((ISysWindow*)p0)->ISysWindowSetCursor(p1))
	#define CHK_SysWindowSetCursor  (pISysWindow != NULL)
	#define EXP_SysWindowSetCursor  CAL_CMEXPAPI( "SysWindowSetCursor" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSetCursor  PFSYSWINDOWSETCURSOR pfSysWindowSetCursor;
	#define EXT_SysWindowSetCursor  extern PFSYSWINDOWSETCURSOR pfSysWindowSetCursor;
	#define GET_SysWindowSetCursor(fl)  s_pfCMGetAPI2( "SysWindowSetCursor", (RTS_VOID_FCTPTR *)&pfSysWindowSetCursor, (fl), 0, 0)
	#define CAL_SysWindowSetCursor  pfSysWindowSetCursor
	#define CHK_SysWindowSetCursor  (pfSysWindowSetCursor != NULL)
	#define EXP_SysWindowSetCursor  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetCursor", (RTS_UINTPTR)SysWindowSetCursor, 0, 0) 
#endif




/**
 * <description>Function to set flags on a window. For a detailed description of the possible flags
 *	have a look at the defines beginning with SYSWIN_FLAGS_.</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="uiFlag" type="IN">The flags</param>
 * <param name="bValue" type="IN">The boolean value of the flag</param>
 * <result>Will return ERR_OK if the flag could be set, ERR_NOT_SUPPORTED if the class of the given window
 *	does not support this kind of flag or another error code if other errors happen.</result>
 */
RTS_RESULT CDECL SysWindowSetFlags(RTS_HANDLE hWindow, RTS_UI32 uiFlag, RTS_BOOL bValue);
typedef RTS_RESULT (CDECL * PFSYSWINDOWSETFLAGS) (RTS_HANDLE hWindow, RTS_UI32 uiFlag, RTS_BOOL bValue);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSETFLAGS_NOTIMPLEMENTED)
	#define USE_SysWindowSetFlags
	#define EXT_SysWindowSetFlags
	#define GET_SysWindowSetFlags(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSetFlags(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSetFlags  FALSE
	#define EXP_SysWindowSetFlags  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSetFlags
	#define EXT_SysWindowSetFlags
	#define GET_SysWindowSetFlags(fl)  CAL_CMGETAPI( "SysWindowSetFlags" ) 
	#define CAL_SysWindowSetFlags  SysWindowSetFlags
	#define CHK_SysWindowSetFlags  TRUE
	#define EXP_SysWindowSetFlags  CAL_CMEXPAPI( "SysWindowSetFlags" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSetFlags
	#define EXT_SysWindowSetFlags
	#define GET_SysWindowSetFlags(fl)  CAL_CMGETAPI( "SysWindowSetFlags" ) 
	#define CAL_SysWindowSetFlags  SysWindowSetFlags
	#define CHK_SysWindowSetFlags  TRUE
	#define EXP_SysWindowSetFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetFlags", (RTS_UINTPTR)SysWindowSetFlags, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSetFlags
	#define EXT_SysWindowSysWindowSetFlags
	#define GET_SysWindowSysWindowSetFlags  ERR_OK
	#define CAL_SysWindowSysWindowSetFlags(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetFlags(p1,p2) : ((ISysWindow*)p0)->ISysWindowSetFlags(p1,p2))
	#define CHK_SysWindowSysWindowSetFlags  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowSetFlags  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSetFlags
	#define EXT_SysWindowSetFlags
	#define GET_SysWindowSetFlags(fl)  CAL_CMGETAPI( "SysWindowSetFlags" ) 
	#define CAL_SysWindowSetFlags(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSetFlags(p1,p2) : ((ISysWindow*)p0)->ISysWindowSetFlags(p1,p2))
	#define CHK_SysWindowSetFlags  (pISysWindow != NULL)
	#define EXP_SysWindowSetFlags  CAL_CMEXPAPI( "SysWindowSetFlags" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSetFlags  PFSYSWINDOWSETFLAGS pfSysWindowSetFlags;
	#define EXT_SysWindowSetFlags  extern PFSYSWINDOWSETFLAGS pfSysWindowSetFlags;
	#define GET_SysWindowSetFlags(fl)  s_pfCMGetAPI2( "SysWindowSetFlags", (RTS_VOID_FCTPTR *)&pfSysWindowSetFlags, (fl), 0, 0)
	#define CAL_SysWindowSetFlags  pfSysWindowSetFlags
	#define CHK_SysWindowSetFlags  (pfSysWindowSetFlags != NULL)
	#define EXP_SysWindowSetFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSetFlags", (RTS_UINTPTR)SysWindowSetFlags, 0, 0) 
#endif




/**
 * <description>function print the current screen</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pszTitle" type="IN">The print title</param>
 * <result>error code</result>
 * <remarks>This function is obsolete, might be removed in one of the next releases and is included only for compatibility reasons. 
 *	Please use SysWindowPrintStart etc. instead.</remarks>
 */
RTS_RESULT CDECL SysWindowPrint(RTS_HANDLE hWindow, char* pszTitle);
typedef RTS_RESULT (CDECL * PFSYSWINDOWPRINT) (RTS_HANDLE hWindow, char* pszTitle);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWPRINT_NOTIMPLEMENTED)
	#define USE_SysWindowPrint
	#define EXT_SysWindowPrint
	#define GET_SysWindowPrint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowPrint(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowPrint  FALSE
	#define EXP_SysWindowPrint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowPrint
	#define EXT_SysWindowPrint
	#define GET_SysWindowPrint(fl)  CAL_CMGETAPI( "SysWindowPrint" ) 
	#define CAL_SysWindowPrint  SysWindowPrint
	#define CHK_SysWindowPrint  TRUE
	#define EXP_SysWindowPrint  CAL_CMEXPAPI( "SysWindowPrint" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowPrint
	#define EXT_SysWindowPrint
	#define GET_SysWindowPrint(fl)  CAL_CMGETAPI( "SysWindowPrint" ) 
	#define CAL_SysWindowPrint  SysWindowPrint
	#define CHK_SysWindowPrint  TRUE
	#define EXP_SysWindowPrint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowPrint", (RTS_UINTPTR)SysWindowPrint, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowPrint
	#define EXT_SysWindowSysWindowPrint
	#define GET_SysWindowSysWindowPrint  ERR_OK
	#define CAL_SysWindowSysWindowPrint(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowPrint(p1) : ((ISysWindow*)p0)->ISysWindowPrint(p1))
	#define CHK_SysWindowSysWindowPrint  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowPrint  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowPrint
	#define EXT_SysWindowPrint
	#define GET_SysWindowPrint(fl)  CAL_CMGETAPI( "SysWindowPrint" ) 
	#define CAL_SysWindowPrint(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowPrint(p1) : ((ISysWindow*)p0)->ISysWindowPrint(p1))
	#define CHK_SysWindowPrint  (pISysWindow != NULL)
	#define EXP_SysWindowPrint  CAL_CMEXPAPI( "SysWindowPrint" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowPrint  PFSYSWINDOWPRINT pfSysWindowPrint;
	#define EXT_SysWindowPrint  extern PFSYSWINDOWPRINT pfSysWindowPrint;
	#define GET_SysWindowPrint(fl)  s_pfCMGetAPI2( "SysWindowPrint", (RTS_VOID_FCTPTR *)&pfSysWindowPrint, (fl), 0, 0)
	#define CAL_SysWindowPrint  pfSysWindowPrint
	#define CHK_SysWindowPrint  (pfSysWindowPrint != NULL)
	#define EXP_SysWindowPrint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowPrint", (RTS_UINTPTR)SysWindowPrint, 0, 0) 
#endif




/**
 * <description>function print the current screen</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pszTitle" type="IN">The print title</param>
 * <param name="pszPrinter" type="IN">The printer name</param>
 * <result>The result</result>
 */
RTS_RESULT CDECL SysWindowPrintStart(RTS_HANDLE hWindow, char* pszTitle, char* pszPrinter);
typedef RTS_RESULT (CDECL * PFSYSWINDOWPRINTSTART) (RTS_HANDLE hWindow, char* pszTitle, char* pszPrinter);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWPRINTSTART_NOTIMPLEMENTED)
	#define USE_SysWindowPrintStart
	#define EXT_SysWindowPrintStart
	#define GET_SysWindowPrintStart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowPrintStart(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowPrintStart  FALSE
	#define EXP_SysWindowPrintStart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowPrintStart
	#define EXT_SysWindowPrintStart
	#define GET_SysWindowPrintStart(fl)  CAL_CMGETAPI( "SysWindowPrintStart" ) 
	#define CAL_SysWindowPrintStart  SysWindowPrintStart
	#define CHK_SysWindowPrintStart  TRUE
	#define EXP_SysWindowPrintStart  CAL_CMEXPAPI( "SysWindowPrintStart" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowPrintStart
	#define EXT_SysWindowPrintStart
	#define GET_SysWindowPrintStart(fl)  CAL_CMGETAPI( "SysWindowPrintStart" ) 
	#define CAL_SysWindowPrintStart  SysWindowPrintStart
	#define CHK_SysWindowPrintStart  TRUE
	#define EXP_SysWindowPrintStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowPrintStart", (RTS_UINTPTR)SysWindowPrintStart, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowPrintStart
	#define EXT_SysWindowSysWindowPrintStart
	#define GET_SysWindowSysWindowPrintStart  ERR_OK
	#define CAL_SysWindowSysWindowPrintStart(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowPrintStart(p1,p2) : ((ISysWindow*)p0)->ISysWindowPrintStart(p1,p2))
	#define CHK_SysWindowSysWindowPrintStart  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowPrintStart  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowPrintStart
	#define EXT_SysWindowPrintStart
	#define GET_SysWindowPrintStart(fl)  CAL_CMGETAPI( "SysWindowPrintStart" ) 
	#define CAL_SysWindowPrintStart(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowPrintStart(p1,p2) : ((ISysWindow*)p0)->ISysWindowPrintStart(p1,p2))
	#define CHK_SysWindowPrintStart  (pISysWindow != NULL)
	#define EXP_SysWindowPrintStart  CAL_CMEXPAPI( "SysWindowPrintStart" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowPrintStart  PFSYSWINDOWPRINTSTART pfSysWindowPrintStart;
	#define EXT_SysWindowPrintStart  extern PFSYSWINDOWPRINTSTART pfSysWindowPrintStart;
	#define GET_SysWindowPrintStart(fl)  s_pfCMGetAPI2( "SysWindowPrintStart", (RTS_VOID_FCTPTR *)&pfSysWindowPrintStart, (fl), 0, 0)
	#define CAL_SysWindowPrintStart  pfSysWindowPrintStart
	#define CHK_SysWindowPrintStart  (pfSysWindowPrintStart != NULL)
	#define EXP_SysWindowPrintStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowPrintStart", (RTS_UINTPTR)SysWindowPrintStart, 0, 0) 
#endif




/**
 * <description>Start the print document</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>The result</result>
 */
RTS_RESULT CDECL SysWindowPrintStartDocument(RTS_HANDLE hWindow);
typedef RTS_RESULT (CDECL * PFSYSWINDOWPRINTSTARTDOCUMENT) (RTS_HANDLE hWindow);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWPRINTSTARTDOCUMENT_NOTIMPLEMENTED)
	#define USE_SysWindowPrintStartDocument
	#define EXT_SysWindowPrintStartDocument
	#define GET_SysWindowPrintStartDocument(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowPrintStartDocument(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowPrintStartDocument  FALSE
	#define EXP_SysWindowPrintStartDocument  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowPrintStartDocument
	#define EXT_SysWindowPrintStartDocument
	#define GET_SysWindowPrintStartDocument(fl)  CAL_CMGETAPI( "SysWindowPrintStartDocument" ) 
	#define CAL_SysWindowPrintStartDocument  SysWindowPrintStartDocument
	#define CHK_SysWindowPrintStartDocument  TRUE
	#define EXP_SysWindowPrintStartDocument  CAL_CMEXPAPI( "SysWindowPrintStartDocument" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowPrintStartDocument
	#define EXT_SysWindowPrintStartDocument
	#define GET_SysWindowPrintStartDocument(fl)  CAL_CMGETAPI( "SysWindowPrintStartDocument" ) 
	#define CAL_SysWindowPrintStartDocument  SysWindowPrintStartDocument
	#define CHK_SysWindowPrintStartDocument  TRUE
	#define EXP_SysWindowPrintStartDocument  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowPrintStartDocument", (RTS_UINTPTR)SysWindowPrintStartDocument, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowPrintStartDocument
	#define EXT_SysWindowSysWindowPrintStartDocument
	#define GET_SysWindowSysWindowPrintStartDocument  ERR_OK
	#define CAL_SysWindowSysWindowPrintStartDocument(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowPrintStartDocument() : ((ISysWindow*)p0)->ISysWindowPrintStartDocument())
	#define CHK_SysWindowSysWindowPrintStartDocument  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowPrintStartDocument  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowPrintStartDocument
	#define EXT_SysWindowPrintStartDocument
	#define GET_SysWindowPrintStartDocument(fl)  CAL_CMGETAPI( "SysWindowPrintStartDocument" ) 
	#define CAL_SysWindowPrintStartDocument(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowPrintStartDocument() : ((ISysWindow*)p0)->ISysWindowPrintStartDocument())
	#define CHK_SysWindowPrintStartDocument  (pISysWindow != NULL)
	#define EXP_SysWindowPrintStartDocument  CAL_CMEXPAPI( "SysWindowPrintStartDocument" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowPrintStartDocument  PFSYSWINDOWPRINTSTARTDOCUMENT pfSysWindowPrintStartDocument;
	#define EXT_SysWindowPrintStartDocument  extern PFSYSWINDOWPRINTSTARTDOCUMENT pfSysWindowPrintStartDocument;
	#define GET_SysWindowPrintStartDocument(fl)  s_pfCMGetAPI2( "SysWindowPrintStartDocument", (RTS_VOID_FCTPTR *)&pfSysWindowPrintStartDocument, (fl), 0, 0)
	#define CAL_SysWindowPrintStartDocument  pfSysWindowPrintStartDocument
	#define CHK_SysWindowPrintStartDocument  (pfSysWindowPrintStartDocument != NULL)
	#define EXP_SysWindowPrintStartDocument  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowPrintStartDocument", (RTS_UINTPTR)SysWindowPrintStartDocument, 0, 0) 
#endif




/**
 * <description>End the print document</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>The result</result>
 */
RTS_RESULT CDECL SysWindowPrintEndDocument(RTS_HANDLE hWindow);
typedef RTS_RESULT (CDECL * PFSYSWINDOWPRINTENDDOCUMENT) (RTS_HANDLE hWindow);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWPRINTENDDOCUMENT_NOTIMPLEMENTED)
	#define USE_SysWindowPrintEndDocument
	#define EXT_SysWindowPrintEndDocument
	#define GET_SysWindowPrintEndDocument(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowPrintEndDocument(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowPrintEndDocument  FALSE
	#define EXP_SysWindowPrintEndDocument  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowPrintEndDocument
	#define EXT_SysWindowPrintEndDocument
	#define GET_SysWindowPrintEndDocument(fl)  CAL_CMGETAPI( "SysWindowPrintEndDocument" ) 
	#define CAL_SysWindowPrintEndDocument  SysWindowPrintEndDocument
	#define CHK_SysWindowPrintEndDocument  TRUE
	#define EXP_SysWindowPrintEndDocument  CAL_CMEXPAPI( "SysWindowPrintEndDocument" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowPrintEndDocument
	#define EXT_SysWindowPrintEndDocument
	#define GET_SysWindowPrintEndDocument(fl)  CAL_CMGETAPI( "SysWindowPrintEndDocument" ) 
	#define CAL_SysWindowPrintEndDocument  SysWindowPrintEndDocument
	#define CHK_SysWindowPrintEndDocument  TRUE
	#define EXP_SysWindowPrintEndDocument  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowPrintEndDocument", (RTS_UINTPTR)SysWindowPrintEndDocument, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowPrintEndDocument
	#define EXT_SysWindowSysWindowPrintEndDocument
	#define GET_SysWindowSysWindowPrintEndDocument  ERR_OK
	#define CAL_SysWindowSysWindowPrintEndDocument(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowPrintEndDocument() : ((ISysWindow*)p0)->ISysWindowPrintEndDocument())
	#define CHK_SysWindowSysWindowPrintEndDocument  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowPrintEndDocument  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowPrintEndDocument
	#define EXT_SysWindowPrintEndDocument
	#define GET_SysWindowPrintEndDocument(fl)  CAL_CMGETAPI( "SysWindowPrintEndDocument" ) 
	#define CAL_SysWindowPrintEndDocument(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowPrintEndDocument() : ((ISysWindow*)p0)->ISysWindowPrintEndDocument())
	#define CHK_SysWindowPrintEndDocument  (pISysWindow != NULL)
	#define EXP_SysWindowPrintEndDocument  CAL_CMEXPAPI( "SysWindowPrintEndDocument" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowPrintEndDocument  PFSYSWINDOWPRINTENDDOCUMENT pfSysWindowPrintEndDocument;
	#define EXT_SysWindowPrintEndDocument  extern PFSYSWINDOWPRINTENDDOCUMENT pfSysWindowPrintEndDocument;
	#define GET_SysWindowPrintEndDocument(fl)  s_pfCMGetAPI2( "SysWindowPrintEndDocument", (RTS_VOID_FCTPTR *)&pfSysWindowPrintEndDocument, (fl), 0, 0)
	#define CAL_SysWindowPrintEndDocument  pfSysWindowPrintEndDocument
	#define CHK_SysWindowPrintEndDocument  (pfSysWindowPrintEndDocument != NULL)
	#define EXP_SysWindowPrintEndDocument  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowPrintEndDocument", (RTS_UINTPTR)SysWindowPrintEndDocument, 0, 0) 
#endif




/**
 * <description>Release all print objects if needed</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>The result</result>
 */
RTS_RESULT CDECL SysWindowPrintRelease(RTS_HANDLE hWindow);
typedef RTS_RESULT (CDECL * PFSYSWINDOWPRINTRELEASE) (RTS_HANDLE hWindow);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWPRINTRELEASE_NOTIMPLEMENTED)
	#define USE_SysWindowPrintRelease
	#define EXT_SysWindowPrintRelease
	#define GET_SysWindowPrintRelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowPrintRelease(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowPrintRelease  FALSE
	#define EXP_SysWindowPrintRelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowPrintRelease
	#define EXT_SysWindowPrintRelease
	#define GET_SysWindowPrintRelease(fl)  CAL_CMGETAPI( "SysWindowPrintRelease" ) 
	#define CAL_SysWindowPrintRelease  SysWindowPrintRelease
	#define CHK_SysWindowPrintRelease  TRUE
	#define EXP_SysWindowPrintRelease  CAL_CMEXPAPI( "SysWindowPrintRelease" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowPrintRelease
	#define EXT_SysWindowPrintRelease
	#define GET_SysWindowPrintRelease(fl)  CAL_CMGETAPI( "SysWindowPrintRelease" ) 
	#define CAL_SysWindowPrintRelease  SysWindowPrintRelease
	#define CHK_SysWindowPrintRelease  TRUE
	#define EXP_SysWindowPrintRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowPrintRelease", (RTS_UINTPTR)SysWindowPrintRelease, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowPrintRelease
	#define EXT_SysWindowSysWindowPrintRelease
	#define GET_SysWindowSysWindowPrintRelease  ERR_OK
	#define CAL_SysWindowSysWindowPrintRelease(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowPrintRelease() : ((ISysWindow*)p0)->ISysWindowPrintRelease())
	#define CHK_SysWindowSysWindowPrintRelease  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowPrintRelease  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowPrintRelease
	#define EXT_SysWindowPrintRelease
	#define GET_SysWindowPrintRelease(fl)  CAL_CMGETAPI( "SysWindowPrintRelease" ) 
	#define CAL_SysWindowPrintRelease(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowPrintRelease() : ((ISysWindow*)p0)->ISysWindowPrintRelease())
	#define CHK_SysWindowPrintRelease  (pISysWindow != NULL)
	#define EXP_SysWindowPrintRelease  CAL_CMEXPAPI( "SysWindowPrintRelease" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowPrintRelease  PFSYSWINDOWPRINTRELEASE pfSysWindowPrintRelease;
	#define EXT_SysWindowPrintRelease  extern PFSYSWINDOWPRINTRELEASE pfSysWindowPrintRelease;
	#define GET_SysWindowPrintRelease(fl)  s_pfCMGetAPI2( "SysWindowPrintRelease", (RTS_VOID_FCTPTR *)&pfSysWindowPrintRelease, (fl), 0, 0)
	#define CAL_SysWindowPrintRelease  pfSysWindowPrintRelease
	#define CHK_SysWindowPrintRelease  (pfSysWindowPrintRelease != NULL)
	#define EXP_SysWindowPrintRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowPrintRelease", (RTS_UINTPTR)SysWindowPrintRelease, 0, 0) 
#endif




/**
 * <description>Notifies a window about a certain situation. The intention of this method is to be able to send notifications to a window
 *	from an arbitrary thread (ie. a different one than the one handling the window).</description>
 * <remarks>Implementations of this method should post an according message to the according window and return without waiting for
 *	evaluation of this message.</remarks>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="notificationCode" type="IN">A numeric value that signals the type of notification.</param>
 * <param name="notificationParam" type="IN">A pointer sized value that is used as a parameter. The meaning of this value depends on
 *	<see>notificationCode</see>; it can as well be a numeric and non pointer value.</param>
 * <result>The result</result>
 */
RTS_RESULT CDECL SysWindowNotify(RTS_HANDLE hWindow, RTS_UI32 notificationCode, void* notificationParam);
typedef RTS_RESULT (CDECL * PFSYSWINDOWNOTIFY) (RTS_HANDLE hWindow, RTS_UI32 notificationCode, void* notificationParam);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWNOTIFY_NOTIMPLEMENTED)
	#define USE_SysWindowNotify
	#define EXT_SysWindowNotify
	#define GET_SysWindowNotify(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowNotify(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowNotify  FALSE
	#define EXP_SysWindowNotify  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowNotify
	#define EXT_SysWindowNotify
	#define GET_SysWindowNotify(fl)  CAL_CMGETAPI( "SysWindowNotify" ) 
	#define CAL_SysWindowNotify  SysWindowNotify
	#define CHK_SysWindowNotify  TRUE
	#define EXP_SysWindowNotify  CAL_CMEXPAPI( "SysWindowNotify" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowNotify
	#define EXT_SysWindowNotify
	#define GET_SysWindowNotify(fl)  CAL_CMGETAPI( "SysWindowNotify" ) 
	#define CAL_SysWindowNotify  SysWindowNotify
	#define CHK_SysWindowNotify  TRUE
	#define EXP_SysWindowNotify  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowNotify", (RTS_UINTPTR)SysWindowNotify, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowNotify
	#define EXT_SysWindowSysWindowNotify
	#define GET_SysWindowSysWindowNotify  ERR_OK
	#define CAL_SysWindowSysWindowNotify(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowNotify(p1,p2) : ((ISysWindow*)p0)->ISysWindowNotify(p1,p2))
	#define CHK_SysWindowSysWindowNotify  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowNotify  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowNotify
	#define EXT_SysWindowNotify
	#define GET_SysWindowNotify(fl)  CAL_CMGETAPI( "SysWindowNotify" ) 
	#define CAL_SysWindowNotify(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowNotify(p1,p2) : ((ISysWindow*)p0)->ISysWindowNotify(p1,p2))
	#define CHK_SysWindowNotify  (pISysWindow != NULL)
	#define EXP_SysWindowNotify  CAL_CMEXPAPI( "SysWindowNotify" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowNotify  PFSYSWINDOWNOTIFY pfSysWindowNotify;
	#define EXT_SysWindowNotify  extern PFSYSWINDOWNOTIFY pfSysWindowNotify;
	#define GET_SysWindowNotify(fl)  s_pfCMGetAPI2( "SysWindowNotify", (RTS_VOID_FCTPTR *)&pfSysWindowNotify, (fl), 0, 0)
	#define CAL_SysWindowNotify  pfSysWindowNotify
	#define CHK_SysWindowNotify  (pfSysWindowNotify != NULL)
	#define EXP_SysWindowNotify  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowNotify", (RTS_UINTPTR)SysWindowNotify, 0, 0) 
#endif




/**
 * <category>Window support flags</category>
 * <type>Unsigned int</type>
 * <description> Nothing special supported
 * </description>
 */	
#define SYSWINSUPPORT_FLAG_NONE			0

/**
 * <category>Window support flags</category>
 * <type>Unsigned int</type>
 * <description> Single touch input supported
 * </description>
 */	
#define SYSWINSUPPORT_FLAG_TOUCH		1

/**
 * <category>Window support flags</category>
 * <type>Unsigned int</type>
 * <description> Multi touch input supported
 * </description>
 */	
#define SYSWINSUPPORT_FLAG_MULTITOUCH	2

/**
 * <description>Retrieves information about the support of specific features from the current window.</description>
 * <remarks>Implementations of this method should post an according message to the according window and return without waiting for
 *	evaluation of this message.</remarks>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pResult" type="OUT">An optional pointer to a result value.</param>
 * <result>The result is a flat combination of the values SYSWINSUPPORT_FLAG_*</result>
 */
RTS_UI32 CDECL SysWindowSupportInfo(RTS_HANDLE hWindow, RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFSYSWINDOWSUPPORTINFO) (RTS_HANDLE hWindow, RTS_RESULT* pResult);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWSUPPORTINFO_NOTIMPLEMENTED)
	#define USE_SysWindowSupportInfo
	#define EXT_SysWindowSupportInfo
	#define GET_SysWindowSupportInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowSupportInfo(p0,p1)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowSupportInfo  FALSE
	#define EXP_SysWindowSupportInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowSupportInfo
	#define EXT_SysWindowSupportInfo
	#define GET_SysWindowSupportInfo(fl)  CAL_CMGETAPI( "SysWindowSupportInfo" ) 
	#define CAL_SysWindowSupportInfo  SysWindowSupportInfo
	#define CHK_SysWindowSupportInfo  TRUE
	#define EXP_SysWindowSupportInfo  CAL_CMEXPAPI( "SysWindowSupportInfo" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowSupportInfo
	#define EXT_SysWindowSupportInfo
	#define GET_SysWindowSupportInfo(fl)  CAL_CMGETAPI( "SysWindowSupportInfo" ) 
	#define CAL_SysWindowSupportInfo  SysWindowSupportInfo
	#define CHK_SysWindowSupportInfo  TRUE
	#define EXP_SysWindowSupportInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSupportInfo", (RTS_UINTPTR)SysWindowSupportInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowSupportInfo
	#define EXT_SysWindowSysWindowSupportInfo
	#define GET_SysWindowSysWindowSupportInfo  ERR_OK
	#define CAL_SysWindowSysWindowSupportInfo(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSupportInfo(p1) : ((ISysWindow*)p0)->ISysWindowSupportInfo(p1))
	#define CHK_SysWindowSysWindowSupportInfo  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowSupportInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowSupportInfo
	#define EXT_SysWindowSupportInfo
	#define GET_SysWindowSupportInfo(fl)  CAL_CMGETAPI( "SysWindowSupportInfo" ) 
	#define CAL_SysWindowSupportInfo(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowSupportInfo(p1) : ((ISysWindow*)p0)->ISysWindowSupportInfo(p1))
	#define CHK_SysWindowSupportInfo  (pISysWindow != NULL)
	#define EXP_SysWindowSupportInfo  CAL_CMEXPAPI( "SysWindowSupportInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowSupportInfo  PFSYSWINDOWSUPPORTINFO pfSysWindowSupportInfo;
	#define EXT_SysWindowSupportInfo  extern PFSYSWINDOWSUPPORTINFO pfSysWindowSupportInfo;
	#define GET_SysWindowSupportInfo(fl)  s_pfCMGetAPI2( "SysWindowSupportInfo", (RTS_VOID_FCTPTR *)&pfSysWindowSupportInfo, (fl), 0, 0)
	#define CAL_SysWindowSupportInfo  pfSysWindowSupportInfo
	#define CHK_SysWindowSupportInfo  (pfSysWindowSupportInfo != NULL)
	#define EXP_SysWindowSupportInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowSupportInfo", (RTS_UINTPTR)SysWindowSupportInfo, 0, 0) 
#endif




/** 
 * <description> Signature of the callback passed to <see>SysWindowCreateTimer</see>. </description>
 */
typedef void (*SysWindowTimerCallback)(RTS_HANDLE hWindow, void* pParams);

/**
 * <description>Creates a timer that periodically calls a function.</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="interval" type="IN">The timer interval in milliseconds.</param>
 * <param name="callback" type="IN">The function to call after every interval.</param>
 * <param name="callbackParams" type="IN">The paramaters that should be passed to the callback function.</param>
 * <result>Identifier for the timer that can be used to destroy it.</result>
 */
RTS_HANDLE CDECL SysWindowCreateTimer(RTS_HANDLE hWindow, RTS_UI32 interval, SysWindowTimerCallback callback, void* pCallbackParams, RTS_RESULT* pResult);
typedef RTS_HANDLE (CDECL * PFSYSWINDOWCREATETIMER) (RTS_HANDLE hWindow, RTS_UI32 interval, SysWindowTimerCallback callback, void* pCallbackParams, RTS_RESULT* pResult);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWCREATETIMER_NOTIMPLEMENTED)
	#define USE_SysWindowCreateTimer
	#define EXT_SysWindowCreateTimer
	#define GET_SysWindowCreateTimer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowCreateTimer(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysWindowCreateTimer  FALSE
	#define EXP_SysWindowCreateTimer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowCreateTimer
	#define EXT_SysWindowCreateTimer
	#define GET_SysWindowCreateTimer(fl)  CAL_CMGETAPI( "SysWindowCreateTimer" ) 
	#define CAL_SysWindowCreateTimer  SysWindowCreateTimer
	#define CHK_SysWindowCreateTimer  TRUE
	#define EXP_SysWindowCreateTimer  CAL_CMEXPAPI( "SysWindowCreateTimer" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowCreateTimer
	#define EXT_SysWindowCreateTimer
	#define GET_SysWindowCreateTimer(fl)  CAL_CMGETAPI( "SysWindowCreateTimer" ) 
	#define CAL_SysWindowCreateTimer  SysWindowCreateTimer
	#define CHK_SysWindowCreateTimer  TRUE
	#define EXP_SysWindowCreateTimer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowCreateTimer", (RTS_UINTPTR)SysWindowCreateTimer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowCreateTimer
	#define EXT_SysWindowSysWindowCreateTimer
	#define GET_SysWindowSysWindowCreateTimer  ERR_OK
	#define CAL_SysWindowSysWindowCreateTimer(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowCreateTimer(p1,p2,p3,p4) : ((ISysWindow*)p0)->ISysWindowCreateTimer(p1,p2,p3,p4))
	#define CHK_SysWindowSysWindowCreateTimer  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowCreateTimer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowCreateTimer
	#define EXT_SysWindowCreateTimer
	#define GET_SysWindowCreateTimer(fl)  CAL_CMGETAPI( "SysWindowCreateTimer" ) 
	#define CAL_SysWindowCreateTimer(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowCreateTimer(p1,p2,p3,p4) : ((ISysWindow*)p0)->ISysWindowCreateTimer(p1,p2,p3,p4))
	#define CHK_SysWindowCreateTimer  (pISysWindow != NULL)
	#define EXP_SysWindowCreateTimer  CAL_CMEXPAPI( "SysWindowCreateTimer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowCreateTimer  PFSYSWINDOWCREATETIMER pfSysWindowCreateTimer;
	#define EXT_SysWindowCreateTimer  extern PFSYSWINDOWCREATETIMER pfSysWindowCreateTimer;
	#define GET_SysWindowCreateTimer(fl)  s_pfCMGetAPI2( "SysWindowCreateTimer", (RTS_VOID_FCTPTR *)&pfSysWindowCreateTimer, (fl), 0, 0)
	#define CAL_SysWindowCreateTimer  pfSysWindowCreateTimer
	#define CHK_SysWindowCreateTimer  (pfSysWindowCreateTimer != NULL)
	#define EXP_SysWindowCreateTimer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowCreateTimer", (RTS_UINTPTR)SysWindowCreateTimer, 0, 0) 
#endif




/**
 * <description>Creates a timer that periodically calls a function.</description>
 * <param name="hTimer" type="IN">The timer to destroy.</param>
 * <result>Error code.</result>
 */
RTS_RESULT CDECL SysWindowDestroyTimer(RTS_HANDLE hWindow, RTS_HANDLE hTimer);
typedef RTS_RESULT (CDECL * PFSYSWINDOWDESTROYTIMER) (RTS_HANDLE hWindow, RTS_HANDLE hTimer);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWDESTROYTIMER_NOTIMPLEMENTED)
	#define USE_SysWindowDestroyTimer
	#define EXT_SysWindowDestroyTimer
	#define GET_SysWindowDestroyTimer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowDestroyTimer(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowDestroyTimer  FALSE
	#define EXP_SysWindowDestroyTimer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowDestroyTimer
	#define EXT_SysWindowDestroyTimer
	#define GET_SysWindowDestroyTimer(fl)  CAL_CMGETAPI( "SysWindowDestroyTimer" ) 
	#define CAL_SysWindowDestroyTimer  SysWindowDestroyTimer
	#define CHK_SysWindowDestroyTimer  TRUE
	#define EXP_SysWindowDestroyTimer  CAL_CMEXPAPI( "SysWindowDestroyTimer" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowDestroyTimer
	#define EXT_SysWindowDestroyTimer
	#define GET_SysWindowDestroyTimer(fl)  CAL_CMGETAPI( "SysWindowDestroyTimer" ) 
	#define CAL_SysWindowDestroyTimer  SysWindowDestroyTimer
	#define CHK_SysWindowDestroyTimer  TRUE
	#define EXP_SysWindowDestroyTimer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowDestroyTimer", (RTS_UINTPTR)SysWindowDestroyTimer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowDestroyTimer
	#define EXT_SysWindowSysWindowDestroyTimer
	#define GET_SysWindowSysWindowDestroyTimer  ERR_OK
	#define CAL_SysWindowSysWindowDestroyTimer(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowDestroyTimer(p1) : ((ISysWindow*)p0)->ISysWindowDestroyTimer(p1))
	#define CHK_SysWindowSysWindowDestroyTimer  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowDestroyTimer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowDestroyTimer
	#define EXT_SysWindowDestroyTimer
	#define GET_SysWindowDestroyTimer(fl)  CAL_CMGETAPI( "SysWindowDestroyTimer" ) 
	#define CAL_SysWindowDestroyTimer(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowDestroyTimer(p1) : ((ISysWindow*)p0)->ISysWindowDestroyTimer(p1))
	#define CHK_SysWindowDestroyTimer  (pISysWindow != NULL)
	#define EXP_SysWindowDestroyTimer  CAL_CMEXPAPI( "SysWindowDestroyTimer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowDestroyTimer  PFSYSWINDOWDESTROYTIMER pfSysWindowDestroyTimer;
	#define EXT_SysWindowDestroyTimer  extern PFSYSWINDOWDESTROYTIMER pfSysWindowDestroyTimer;
	#define GET_SysWindowDestroyTimer(fl)  s_pfCMGetAPI2( "SysWindowDestroyTimer", (RTS_VOID_FCTPTR *)&pfSysWindowDestroyTimer, (fl), 0, 0)
	#define CAL_SysWindowDestroyTimer  pfSysWindowDestroyTimer
	#define CHK_SysWindowDestroyTimer  (pfSysWindowDestroyTimer != NULL)
	#define EXP_SysWindowDestroyTimer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowDestroyTimer", (RTS_UINTPTR)SysWindowDestroyTimer, 0, 0) 
#endif




/**
 * <description>
 *	Function to open a message box.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pszText" type="IN">The message to show</param>
 * <param name="pszCaption" type="IN">The caption to show</param>
 * <param name="uiType" type="IN">The type of message box. See MB_TYPE defines</param>
 * <result>see MB_RESULT defines</result>
 */
RTS_RESULT CDECL SysWindowOpenMessageBox(RTS_HANDLE hWindow, char* pszText, char* pszCaption, RTS_UI32 uiType);
typedef RTS_RESULT (CDECL * PFSYSWINDOWOPENMESSAGEBOX) (RTS_HANDLE hWindow, char* pszText, char* pszCaption, RTS_UI32 uiType);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWOPENMESSAGEBOX_NOTIMPLEMENTED)
	#define USE_SysWindowOpenMessageBox
	#define EXT_SysWindowOpenMessageBox
	#define GET_SysWindowOpenMessageBox(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowOpenMessageBox(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowOpenMessageBox  FALSE
	#define EXP_SysWindowOpenMessageBox  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowOpenMessageBox
	#define EXT_SysWindowOpenMessageBox
	#define GET_SysWindowOpenMessageBox(fl)  CAL_CMGETAPI( "SysWindowOpenMessageBox" ) 
	#define CAL_SysWindowOpenMessageBox  SysWindowOpenMessageBox
	#define CHK_SysWindowOpenMessageBox  TRUE
	#define EXP_SysWindowOpenMessageBox  CAL_CMEXPAPI( "SysWindowOpenMessageBox" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowOpenMessageBox
	#define EXT_SysWindowOpenMessageBox
	#define GET_SysWindowOpenMessageBox(fl)  CAL_CMGETAPI( "SysWindowOpenMessageBox" ) 
	#define CAL_SysWindowOpenMessageBox  SysWindowOpenMessageBox
	#define CHK_SysWindowOpenMessageBox  TRUE
	#define EXP_SysWindowOpenMessageBox  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowOpenMessageBox", (RTS_UINTPTR)SysWindowOpenMessageBox, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowOpenMessageBox
	#define EXT_SysWindowSysWindowOpenMessageBox
	#define GET_SysWindowSysWindowOpenMessageBox  ERR_OK
	#define CAL_SysWindowSysWindowOpenMessageBox(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowOpenMessageBox(p1,p2,p3) : ((ISysWindow*)p0)->ISysWindowOpenMessageBox(p1,p2,p3))
	#define CHK_SysWindowSysWindowOpenMessageBox  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowOpenMessageBox  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowOpenMessageBox
	#define EXT_SysWindowOpenMessageBox
	#define GET_SysWindowOpenMessageBox(fl)  CAL_CMGETAPI( "SysWindowOpenMessageBox" ) 
	#define CAL_SysWindowOpenMessageBox(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowOpenMessageBox(p1,p2,p3) : ((ISysWindow*)p0)->ISysWindowOpenMessageBox(p1,p2,p3))
	#define CHK_SysWindowOpenMessageBox  (pISysWindow != NULL)
	#define EXP_SysWindowOpenMessageBox  CAL_CMEXPAPI( "SysWindowOpenMessageBox" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowOpenMessageBox  PFSYSWINDOWOPENMESSAGEBOX pfSysWindowOpenMessageBox;
	#define EXT_SysWindowOpenMessageBox  extern PFSYSWINDOWOPENMESSAGEBOX pfSysWindowOpenMessageBox;
	#define GET_SysWindowOpenMessageBox(fl)  s_pfCMGetAPI2( "SysWindowOpenMessageBox", (RTS_VOID_FCTPTR *)&pfSysWindowOpenMessageBox, (fl), 0, 0)
	#define CAL_SysWindowOpenMessageBox  pfSysWindowOpenMessageBox
	#define CHK_SysWindowOpenMessageBox  (pfSysWindowOpenMessageBox != NULL)
	#define EXP_SysWindowOpenMessageBox  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowOpenMessageBox", (RTS_UINTPTR)SysWindowOpenMessageBox, 0, 0) 
#endif




/**
 * <description>
 *	Function to open a message box.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pwsText" type="IN">The message to show</param>
 * <param name="pwsCaption" type="IN">The caption to show</param>
 * <param name="uiType" type="IN">The type of message box. See MB_TYPE defines</param>
 * <result>see MB_RESULT defines</result>
 */
RTS_RESULT CDECL SysWindowOpenMessageBoxW(RTS_HANDLE hWindow, RTS_WCHAR* pwsText, RTS_WCHAR* pwsCaption, RTS_UI32 uiType);
typedef RTS_RESULT (CDECL * PFSYSWINDOWOPENMESSAGEBOXW) (RTS_HANDLE hWindow, RTS_WCHAR* pwsText, RTS_WCHAR* pwsCaption, RTS_UI32 uiType);
#if defined(SYSWINDOW_NOTIMPLEMENTED) || defined(SYSWINDOWOPENMESSAGEBOXW_NOTIMPLEMENTED)
	#define USE_SysWindowOpenMessageBoxW
	#define EXT_SysWindowOpenMessageBoxW
	#define GET_SysWindowOpenMessageBoxW(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowOpenMessageBoxW(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowOpenMessageBoxW  FALSE
	#define EXP_SysWindowOpenMessageBoxW  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowOpenMessageBoxW
	#define EXT_SysWindowOpenMessageBoxW
	#define GET_SysWindowOpenMessageBoxW(fl)  CAL_CMGETAPI( "SysWindowOpenMessageBoxW" ) 
	#define CAL_SysWindowOpenMessageBoxW  SysWindowOpenMessageBoxW
	#define CHK_SysWindowOpenMessageBoxW  TRUE
	#define EXP_SysWindowOpenMessageBoxW  CAL_CMEXPAPI( "SysWindowOpenMessageBoxW" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOW_EXTERNAL)
	#define USE_SysWindowOpenMessageBoxW
	#define EXT_SysWindowOpenMessageBoxW
	#define GET_SysWindowOpenMessageBoxW(fl)  CAL_CMGETAPI( "SysWindowOpenMessageBoxW" ) 
	#define CAL_SysWindowOpenMessageBoxW  SysWindowOpenMessageBoxW
	#define CHK_SysWindowOpenMessageBoxW  TRUE
	#define EXP_SysWindowOpenMessageBoxW  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowOpenMessageBoxW", (RTS_UINTPTR)SysWindowOpenMessageBoxW, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowSysWindowOpenMessageBoxW
	#define EXT_SysWindowSysWindowOpenMessageBoxW
	#define GET_SysWindowSysWindowOpenMessageBoxW  ERR_OK
	#define CAL_SysWindowSysWindowOpenMessageBoxW(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowOpenMessageBoxW(p1,p2,p3) : ((ISysWindow*)p0)->ISysWindowOpenMessageBoxW(p1,p2,p3))
	#define CHK_SysWindowSysWindowOpenMessageBoxW  (pISysWindow != NULL)
	#define EXP_SysWindowSysWindowOpenMessageBoxW  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowOpenMessageBoxW
	#define EXT_SysWindowOpenMessageBoxW
	#define GET_SysWindowOpenMessageBoxW(fl)  CAL_CMGETAPI( "SysWindowOpenMessageBoxW" ) 
	#define CAL_SysWindowOpenMessageBoxW(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindow->ISysWindowOpenMessageBoxW(p1,p2,p3) : ((ISysWindow*)p0)->ISysWindowOpenMessageBoxW(p1,p2,p3))
	#define CHK_SysWindowOpenMessageBoxW  (pISysWindow != NULL)
	#define EXP_SysWindowOpenMessageBoxW  CAL_CMEXPAPI( "SysWindowOpenMessageBoxW" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowOpenMessageBoxW  PFSYSWINDOWOPENMESSAGEBOXW pfSysWindowOpenMessageBoxW;
	#define EXT_SysWindowOpenMessageBoxW  extern PFSYSWINDOWOPENMESSAGEBOXW pfSysWindowOpenMessageBoxW;
	#define GET_SysWindowOpenMessageBoxW(fl)  s_pfCMGetAPI2( "SysWindowOpenMessageBoxW", (RTS_VOID_FCTPTR *)&pfSysWindowOpenMessageBoxW, (fl), 0, 0)
	#define CAL_SysWindowOpenMessageBoxW  pfSysWindowOpenMessageBoxW
	#define CHK_SysWindowOpenMessageBoxW  (pfSysWindowOpenMessageBoxW != NULL)
	#define EXP_SysWindowOpenMessageBoxW  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowOpenMessageBoxW", (RTS_UINTPTR)SysWindowOpenMessageBoxW, 0, 0) 
#endif




#define MB_TYPE_OK					0x0000
#define MB_TYPE_OKCANCEL			0x0001
#define MB_TYPE_ABORTRETRYIGNORE	0x0002
#define MB_TYPE_YESNOCANCEL			0x0003
#define MB_TYPE_YESNO				0x0004
#define MB_TYPE_RETRYCANCEL			0x0005

#define MB_TYPE_ICONERROR			0x0010
#define MB_TYPE_ICONQUESTION		0x0020
#define MB_TYPE_ICONWARNING			0x0030
#define MB_TYPE_ICONINFORMATION		0x0040

#define MB_TYPE_DEFBUTTON1			0x0000
#define MB_TYPE_DEFBUTTON2			0x0100
#define MB_TYPE_DEFBUTTON3			0x0200
#define MB_TYPE_DEFBUTTON4			0x0300

#define MB_RESULT_OK				0x0001
#define MB_RESULT_CANCEL			0x0002
#define MB_RESULT_ABORT				0x0003
#define MB_RESULT_RETRY				0x0004
#define MB_RESULT_IGNORE			0x0005
#define MB_RESULT_YES				0x0006
#define MB_RESULT_NO				0x0007

#ifdef __cplusplus
}
#endif




typedef struct
{
	IBase_C *pBase;
	PFSYSWINDOWCREATE ISysWindowCreate;
 	PFSYSWINDOWDESTROY ISysWindowDestroy;
 	PFSYSWINDOWSETUSERDATA ISysWindowSetUserData;
 	PFSYSWINDOWSHOW ISysWindowShow;
 	PFSYSWINDOWGETUSERDATA ISysWindowGetUserData;
 	PFSYSWINDOWSETCALLBACK ISysWindowSetCallback;
 	PFSYSWINDOWMESSAGELOOP ISysWindowMessageLoop;
 	PFSYSWINDOWREGISTERCALLBACK ISysWindowRegisterCallback;
 	PFSYSWINDOWUNREGISTERCALLBACK ISysWindowUnregisterCallback;
 	PFSYSWINDOWINVALIDATERECTANGLE ISysWindowInvalidateRectangle;
 	PFSYSWINDOWUPDATE ISysWindowUpdate;
 	PFSYSWINDOWFORCEUPDATE ISysWindowForceUpdate;
 	PFSYSWINDOWGETPOS ISysWindowGetPos;
 	PFSYSWINDOWSETPOS ISysWindowSetPos;
 	PFSYSWINDOWGETCLIENTRECTANGLE ISysWindowGetClientRectangle;
 	PFSYSWINDOWSETFONT ISysWindowSetFont;
 	PFSYSWINDOWGETFONT ISysWindowGetFont;
 	PFSYSWINDOWGETTEXT ISysWindowGetText;
 	PFSYSWINDOWSETTEXT ISysWindowSetText;
 	PFSYSWINDOWSETTEXTW ISysWindowSetTextW;
 	PFSYSWINDOWSETFOCUS ISysWindowSetFocus;
 	PFSYSWINDOWSETSELECTION ISysWindowSetSelection;
 	PFSYSWINDOWSETCURSOR ISysWindowSetCursor;
 	PFSYSWINDOWSETFLAGS ISysWindowSetFlags;
 	PFSYSWINDOWPRINT ISysWindowPrint;
 	PFSYSWINDOWPRINTSTART ISysWindowPrintStart;
 	PFSYSWINDOWPRINTSTARTDOCUMENT ISysWindowPrintStartDocument;
 	PFSYSWINDOWPRINTENDDOCUMENT ISysWindowPrintEndDocument;
 	PFSYSWINDOWPRINTRELEASE ISysWindowPrintRelease;
 	PFSYSWINDOWNOTIFY ISysWindowNotify;
 	PFSYSWINDOWSUPPORTINFO ISysWindowSupportInfo;
 	PFSYSWINDOWCREATETIMER ISysWindowCreateTimer;
 	PFSYSWINDOWDESTROYTIMER ISysWindowDestroyTimer;
 	PFSYSWINDOWOPENMESSAGEBOX ISysWindowOpenMessageBox;
 	PFSYSWINDOWOPENMESSAGEBOXW ISysWindowOpenMessageBoxW;
 } ISysWindow_C;

#ifdef CPLUSPLUS
class ISysWindow : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysWindowCreate(SysWindowCreate_Struct* pCreate, RTS_UINTPTR ulParam, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysWindowDestroy(void) =0;
		virtual RTS_RESULT CDECL ISysWindowSetUserData(RTS_UINTPTR ulData) =0;
		virtual RTS_RESULT CDECL ISysWindowShow(RTS_UI32 ulData) =0;
		virtual RTS_RESULT CDECL ISysWindowGetUserData(RTS_UINTPTR* pulData) =0;
		virtual RTS_RESULT CDECL ISysWindowSetCallback(unsigned long ulCallback, unsigned long* pulOldCallback) =0;
		virtual RTS_RESULT CDECL ISysWindowMessageLoop(void) =0;
		virtual RTS_RESULT CDECL ISysWindowRegisterCallback(WindowCallbacks wcb, PFWINDOWCALLBACK callback, RTS_UINTPTR ulParam) =0;
		virtual RTS_RESULT CDECL ISysWindowUnregisterCallback(WindowCallbacks wcb, PFWINDOWCALLBACK callback) =0;
		virtual RTS_RESULT CDECL ISysWindowInvalidateRectangle(RTS_Rectangle rect) =0;
		virtual RTS_RESULT CDECL ISysWindowUpdate(void) =0;
		virtual RTS_RESULT CDECL ISysWindowForceUpdate(void) =0;
		virtual RTS_RESULT CDECL ISysWindowGetPos(RTS_Rectangle* pRect) =0;
		virtual RTS_RESULT CDECL ISysWindowSetPos(RTS_Rectangle rect) =0;
		virtual RTS_RESULT CDECL ISysWindowGetClientRectangle(RTS_Rectangle* pRect) =0;
		virtual RTS_RESULT CDECL ISysWindowSetFont(RTS_HANDLE hFont) =0;
		virtual RTS_RESULT CDECL ISysWindowGetFont(RTS_HANDLE* phFont) =0;
		virtual RTS_RESULT CDECL ISysWindowGetText(char* pszValue, RTS_SIZE* piLen) =0;
		virtual RTS_RESULT CDECL ISysWindowSetText(char* pszText) =0;
		virtual RTS_RESULT CDECL ISysWindowSetTextW(RTS_WCHAR* pwsText) =0;
		virtual RTS_RESULT CDECL ISysWindowSetFocus(void) =0;
		virtual RTS_RESULT CDECL ISysWindowSetSelection(char* pszClassName, RTS_I32 dwParam1, RTS_I32 dwParam2) =0;
		virtual RTS_RESULT CDECL ISysWindowSetCursor(RTS_UI16 usCursor) =0;
		virtual RTS_RESULT CDECL ISysWindowSetFlags(RTS_UI32 uiFlag, RTS_BOOL bValue) =0;
		virtual RTS_RESULT CDECL ISysWindowPrint(char* pszTitle) =0;
		virtual RTS_RESULT CDECL ISysWindowPrintStart(char* pszTitle, char* pszPrinter) =0;
		virtual RTS_RESULT CDECL ISysWindowPrintStartDocument(void) =0;
		virtual RTS_RESULT CDECL ISysWindowPrintEndDocument(void) =0;
		virtual RTS_RESULT CDECL ISysWindowPrintRelease(void) =0;
		virtual RTS_RESULT CDECL ISysWindowNotify(RTS_UI32 notificationCode, void* notificationParam) =0;
		virtual RTS_UI32 CDECL ISysWindowSupportInfo(RTS_RESULT* pResult) =0;
		virtual RTS_HANDLE CDECL ISysWindowCreateTimer(RTS_UI32 interval, SysWindowTimerCallback callback, void* pCallbackParams, RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL ISysWindowDestroyTimer(RTS_HANDLE hTimer) =0;
		virtual RTS_RESULT CDECL ISysWindowOpenMessageBox(char* pszText, char* pszCaption, RTS_UI32 uiType) =0;
		virtual RTS_RESULT CDECL ISysWindowOpenMessageBoxW(RTS_WCHAR* pwsText, RTS_WCHAR* pwsCaption, RTS_UI32 uiType) =0;
};
	#ifndef ITF_SysWindow
		#define ITF_SysWindow static ISysWindow *pISysWindow = NULL;
	#endif
	#define EXTITF_SysWindow
#else	/*CPLUSPLUS*/
	typedef ISysWindow_C		ISysWindow;
	#ifndef ITF_SysWindow
		#define ITF_SysWindow
	#endif
	#define EXTITF_SysWindow
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSWINDOWITF_H_*/
