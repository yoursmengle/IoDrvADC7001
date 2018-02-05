/**
 * <interfacename>SysWindowNative</interfacename>
 * <description> 
 *	<p>SysWindowNative interface is projected for implementing a simple window management system that is not based on
 *	operating system functionality. This interface is an extension of the interface SysWindow.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysWindowNative')

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysWindowNativeOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysWindowNativeOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

typedef enum
{
	SYSWIN_INPUT_DUMMY,		/* just a dummy event, will not be handled; can be used for a cycle in the message loop*/
	SYSWIN_INPUT_TIMER,
	SYSWIN_INPUT_MOUSE,
	SYSWIN_INPUT_KEY,
	SYSWIN_INPUT_KEYCHAR,	/* this event will be raised when a character key is pressed, It might be raised additionally to KEY(Down, Up) */
	SYSWIN_INPUT_INVALIDATION,
	SYSWIN_INPUT_NOTIFICATION
} SysWindowNativeInputType;

typedef enum
{
	SYSWIN_MOUSE_DOWN,
	SYSWIN_MOUSE_UP,
	SYSWIN_MOUSE_MOVE
} SysWindowNativeMouseEventType;

typedef enum
{
	SYSWIN_KEY_DOWN,
	SYSWIN_KEY_UP
} SysWindowNativeKeyEventType;

typedef struct _tagSysWindowNativeTimer
{
	int iTimerNumber;
} SysWindowNativeInputTimer;

typedef struct _tagSysWindowNativeInputMouse
{
	SysWindowNativeMouseEventType	eventType;
	/* For raising events, the coordinates are in absolute (-> screen relative coordinates) */
	int								x;
	/* For raising events, the coordinates are in absolute (-> screen relative coordinates) */
	int								y;
} SysWindowNativeInputMouse;

typedef struct _tagSysWindowNativeInputKey
{
	SysWindowNativeKeyEventType		eventType;
	/* The keycodes have values that are defined in the header SysWindowKeyMapping.h */
	int								iKeyCode;
	/* The values of the modifiers are defined in the header SysWindowKeyMapping.h */
	unsigned int					uiModifiers;
} SysWindowNativeInputKey;

typedef struct _tagSysWindowNativeInputKeyChar
{
	/* The character that was pressed. Will only be raised when there are according characters to the pressed keys. */
	RTS_WCHAR						wcKey;
	/* not yet used and not yet defined */
	unsigned int					uiFlags;
} SysWindowNativeInputKeyChar;

typedef struct _tagSysWindowNativeInputNotification
{
	/* specifies the invalidation area in screen coordinates; evaluation of these coordinates is not yet implemented! */
	RTS_UI32 notificationCode;
	void* notificationParam;
} SysWindowNativeInputNotification;

typedef struct _tagSysWindowNativeInputInvalidation
{
	/* specifies the invalidation area in screen coordinates; evaluation of these coordinates is not yet implemented! */
	short x, y, width, height;
} SysWindowNativeInputInvalidation;

typedef struct _tagSysWindowNativeInput
{
	SysWindowNativeInputType	inputType;
	union
	{
		SysWindowNativeInputTimer	timerInput;
		SysWindowNativeInputMouse	mouseInput;
		SysWindowNativeInputKey		keyInput;
		SysWindowNativeInputKeyChar	keyCharInput;
		SysWindowNativeInputInvalidation	invalidation;
		SysWindowNativeInputNotification notification;
	} info;
} SysWindowNativeInput;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Returns a handle to the display context of the given window. The returned handle is still owned by
 *	the window so there is no need to release this handle after usage.</description>
 * <param name="hWindow" type="IN">The window to get the display context of.</param>
 * <param name="pResult" type="OUT">Optionally returns an error code</param>
 * <result>The handle to the native display context or <see>RTS_INVALID_HANDLE</see> in case of errors.</result>
 */
DEF_HANDLEITF_API2(`RTS_HANDLE', `CDECL', `SysWindowNativeGetDisplayDeviceContext', `(RTS_HANDLE hWindow, RTS_RESULT *pResult)')

/**
 * <description>This method can be called to raise an input event that can be evaluated by the visualization for example. 
 *	The method may be called from arbitrary tasks.</description>
 * <param name="pInput" type="IN">A pointer to the structure describing the input event.</param>
 * <result>A result code.</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysWindowNativeRaiseInput', `(SysWindowNativeInput* pInput)')

/**
 * <description>This method will be called cyclically from the context of the IEC-Visualization-Task in environments using the embedded
 *	targetvisualization. The call is intended to do the processing of the pending input events as well as painting the content of the visualization.
 *	</description>
 * <param name="hWindow" type="IN">The handle of the window that should be processed.</param>
 * <result>A result code.</result>
 */
DEF_HANDLEITF_API2(`RTS_RESULT', `CDECL', `SysWindowNativeProcessCyclic', `(RTS_HANDLE hWindow)')

#ifdef __cplusplus
}
#endif