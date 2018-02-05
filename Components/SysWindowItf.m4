/**
 * <interfacename>SysWindow</interfacename>
 * <description> 
 *	<p>SysWindow interfaces is porjected to get access to the window manager of a graphical environment
 *	To handle the window of the target visualisation.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysWindow')

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
DEF_API(`RTS_RESULT',`CDECL',`SysWindowSupportsSeveralTasks',`(void)')

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
DEF_API(`RTS_RESULT',`CDECL',`SysWindowInvokeInWindowTask',`(PFINVOKEINWINDOWTASK pfToCall, RTS_UINTPTR ulParam)')

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysWindowCreate',`(SysWindowCreate_Struct* pCreate, RTS_UINTPTR ulParam, RTS_RESULT *pResult)')

/**
 * <description>
 *	Function to destroy a new window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 *	<note>A top level window should unregister itself within the platform independent
 *	part using the method InternWindowUnregister</note>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysWindowDestroy',`(RTS_HANDLE hWindow)')

/**
 * <description>
 *	Function to set some userdefined data for a window, can be used to retrieve information within a window callback. The window should
 *	just store this data in a way so that it can be retrieved lateron using the hWindow and calling <see>SysWindowGetUserData</see>
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="ulData" type="IN">User data</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowSetUserData',`(RTS_HANDLE hWindow, RTS_UINTPTR ulData)')

/**
 * <description>
 *	Function to change the show flag of a window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="ulData" type="IN">User data. 1 is passed for hiding the window, 0 for showing it.</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowShow',`(RTS_HANDLE hWindow, RTS_UI32 ulData)')

/**
 * <description>
 *	Function to get the userdefined data for a window. This data can be attached before using <see>SysWindowSetUserData</see>. At the moment, this
 *	method is not called.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pulData" type="IN">Pointer to user data that will be filled.</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowGetUserData',`(RTS_HANDLE hWindow, RTS_UINTPTR* pulData)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowSetCallback',`(RTS_HANDLE hWindow, unsigned long ulCallback, unsigned long* pulOldCallback)')

/**
 * <description>
 *	Function to run the message loop for handling the created window. Will block and will not return until the window is closed,...
 *	Must only be called when <see>SysWindowSupportsSeveralTasks</see> returns ERR_OK.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>error code, will return ERR_NOTIMPLEMENTED if the window is handled in a single task</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowMessageLoop',`(RTS_HANDLE hWindow)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowRegisterCallback',`(RTS_HANDLE hWindow, WindowCallbacks wcb, PFWINDOWCALLBACK callback, RTS_UINTPTR ulParam)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowUnregisterCallback',`(RTS_HANDLE hWindow, WindowCallbacks wcb, PFWINDOWCALLBACK callback)')

/**
 * <description>
 *	Function to add invalidate a screen rectangle
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="rect" type="IN"></param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowInvalidateRectangle',`(RTS_HANDLE hWindow, RTS_Rectangle rect)')

/**
 * <description>
 *	Function to repaint a window. In contrast to <see>SysWindowForceUpdate</see>, this method does not have to trigger an immediate repaint.
 *	It can delay the repaint to the system for performance reasons if necessary.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowUpdate',`(RTS_HANDLE hWindow)')

/**
 * <description>
 *	Function that causes an immediate repaint of a window. In contrast to <see>SysWindowUpdate</see>, this method must trigger an immediate repaint.
 *	The intention of this method is to redraw immediately which can be used for animations for example.
 *	On systems where <see>SysWindowUpdate</see> already triggered an immediate repaint, this method can simply call <see>SysWindowUpdate</see>.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowForceUpdate',`(RTS_HANDLE hWindow)')

/**
 * <description>
 *	Function to retrieve the rectangle of a window (including a title bar etc)
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pRect" type="IN"></param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowGetPos',`(RTS_HANDLE hWindow, RTS_Rectangle* pRect)')

/**
 * <description>
 *	Function to set the position of a window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="rect" type="IN"></param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowSetPos',`(RTS_HANDLE hWindow, RTS_Rectangle rect)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowGetClientRectangle',`(RTS_HANDLE hWindow, RTS_Rectangle* pRect)')

/**
 * <description>
 *	Function to set the font in a window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="hFont" type="IN"></param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowSetFont',`(RTS_HANDLE hWindow, RTS_HANDLE hFont)')

/**
 * <description>
 *	Function to get the font in a window. Please remember that this function is not yet completely defined.
 *	For the moment it is ok to have an empty implementation returning ERR_NOTIMPLEMENTED.
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="phFont" type="IN"></param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowGetFont',`(RTS_HANDLE hWindow, RTS_HANDLE* phFont)')

/**
 * <description>Get the Text of a window</description>
 * <param name="ulWindow" type="IN">The handle to the window</param>
 * <param name="pszValue" type="INOUT">Pointer to value for result</param>
 * <param name="piLen" type="INOUT">Max length of string value as IN and length of copied values as OUT</param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowGetText',`(RTS_HANDLE hWindow, char* pszValue, RTS_SIZE* piLen)')

/**
 * <description>
 *	Function to set the text in a window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pszText" type="IN"></param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowSetText',`(RTS_HANDLE hWindow, char* pszText)')

/**
 * <description>
 *	Function to set the unicode text in a window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pszText" type="IN"></param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowSetTextW',`(RTS_HANDLE hWindow, RTS_WCHAR* pwsText)')

/**
 * <description>
 *	Function to set the input focus to a specific window
 * </description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowSetFocus',`(RTS_HANDLE hWindow)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowSetSelection',`(RTS_HANDLE hWindow, char* pszClassName, RTS_I32 dwParam1, RTS_I32 dwParam2)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowSetCursor',`(RTS_HANDLE hWindow, RTS_UI16 usCursor)')

/**
 * <description>Function to set flags on a window. For a detailed description of the possible flags
 *	have a look at the defines beginning with SYSWIN_FLAGS_.</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="uiFlag" type="IN">The flags</param>
 * <param name="bValue" type="IN">The boolean value of the flag</param>
 * <result>Will return ERR_OK if the flag could be set, ERR_NOT_SUPPORTED if the class of the given window
 *	does not support this kind of flag or another error code if other errors happen.</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowSetFlags',`(RTS_HANDLE hWindow, RTS_UI32 uiFlag, RTS_BOOL bValue)')

/**
 * <description>function print the current screen</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pszTitle" type="IN">The print title</param>
 * <result>error code</result>
 * <remarks>This function is obsolete, might be removed in one of the next releases and is included only for compatibility reasons. 
 *	Please use SysWindowPrintStart etc. instead.</remarks>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowPrint',`(RTS_HANDLE hWindow, char* pszTitle)')

/**
 * <description>function print the current screen</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <param name="pszTitle" type="IN">The print title</param>
 * <param name="pszPrinter" type="IN">The printer name</param>
 * <result>The result</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowPrintStart',`(RTS_HANDLE hWindow, char* pszTitle, char* pszPrinter)')

/**
 * <description>Start the print document</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>The result</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowPrintStartDocument',`(RTS_HANDLE hWindow)')

/**
 * <description>End the print document</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>The result</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowPrintEndDocument',`(RTS_HANDLE hWindow)')

/**
 * <description>Release all print objects if needed</description>
 * <param name="hWindow" type="IN">Handle to the window</param>
 * <result>The result</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowPrintRelease',`(RTS_HANDLE hWindow)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowNotify',`(RTS_HANDLE hWindow, RTS_UI32 notificationCode, void* notificationParam)')

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
DEF_HANDLEITF_API(`RTS_UI32',`CDECL',`SysWindowSupportInfo',`(RTS_HANDLE hWindow, RTS_RESULT* pResult)')

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
DEF_HANDLEITF_API(`RTS_HANDLE',`CDECL',`SysWindowCreateTimer',`(RTS_HANDLE hWindow, RTS_UI32 interval, SysWindowTimerCallback callback, void* pCallbackParams, RTS_RESULT* pResult)')

/**
 * <description>Creates a timer that periodically calls a function.</description>
 * <param name="hTimer" type="IN">The timer to destroy.</param>
 * <result>Error code.</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowDestroyTimer',`(RTS_HANDLE hWindow, RTS_HANDLE hTimer)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowOpenMessageBox',`(RTS_HANDLE hWindow, char* pszText, char* pszCaption, RTS_UI32 uiType)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysWindowOpenMessageBoxW',`(RTS_HANDLE hWindow, RTS_WCHAR* pwsText, RTS_WCHAR* pwsCaption, RTS_UI32 uiType)')

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

