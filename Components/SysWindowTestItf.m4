/**
 * <interfacename>SysWindowTest</interfacename>
 * <description> 
 *	<p>SysWindowTest interfaces is intended to allow access to operating system methods that are necessary for
 *	automatic testing of window components. If you do not intend to do such tests on a platform, an implementation of this
 *	interface is not necessary!</p>
 *	Normally, components implementing this interface are bound very tightly to the implementation of the SysWindow-Interface.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysWindowTest')

/**
 * <category>Image formats</category>
 * <type>Int</type>
 * <description>
 *	The screenshots that can be taken by this components can be stored in one of several image formats.
 * </description>
 */	
#define SYSWINDOWTEST_IMAGEFORMAT_BMP		0
#define SYSWINDOWTEST_IMAGEFORMAT_PNG		1
#define SYSWINDOWTEST_IMAGEFORMAT_GIF		2
#define SYSWINDOWTEST_IMAGEFORMAT_TIFF		3
#define SYSWINDOWTEST_IMAGEFORMAT_NATIVE	4

/**
 * <category>Color formats</category>
 * <type>Int</type>
 * <description>
 *	Further specification of the color format in case of the imageformat <see>SYSWINDOWTEST_IMAGEFORMAT_NATIVE</see>
 * </description>
 */	
#define SYSWINDOWTEST_COLORFORMAT_NONE		0

/**
 * <category>Mouse event types</category>
 * <type>Int</type>
 * <description>
 *	Information about the mouse event that should be raised
 * </description>
 */	
#define SYSWINDOWTEST_MOUSE_LEFT_DOWN		1
#define SYSWINDOWTEST_MOUSE_LEFT_UP			2
#define SYSWINDOWTEST_MOUSE_MOVE			3

/**
 * <category>Key types</category>
 * <type>Int</type>
 * <description>
 *	Information about what type the key code is. 
 * </description>
 */	
#define SYSWINDOWTEST_KEYTYPE_SPECIALKEY	1		/* a special key, keycodes in SysWindow/SysWindowKeyMapping.h, values TV_KC_... */
#define SYSWINDOWTEST_KEYTYPE_MODIFIERKEY	2		/* a modifier key like CTRL, SHIFT, ALT; keycodes in SysGraphicBase.h, values of TV_KEYMOD_... */
#define SYSWINDOWTEST_KEYTYPE_ASCIIKEY		3		/* a ASCII character that should be raised; keycodes are ascii values */

/**
 * <category>Key event types</category>
 * <type>Int</type>
 * <description>
 *	Information about the key event that should be raised
 * </description>
 */	
#define SYSWINDOWTEST_KEY_DOWN				1
#define SYSWINDOWTEST_KEY_UP				2

/* This structure contains information about the file format of screenshots taken by this component. */
typedef struct
{
	/* the image format of the screenshot file */
	RTS_UI16 uiImageFormat;
	/* further information about the screenshot file if this is necessary; probably only for a native format */
	RTS_UI16 uiColorFormat;
} SysWindowTestScreenShotInfo;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Function to search the operating system's window manager for a window by some criteria.</description>
 * <param name="pszWindowClass" type="IN">The name of the window class to search for</param>
 * <param name="pszWindowTitle" type="IN">The name of the window title to search for. If the title of the window should be ignored,
 *	a value of <c>NULL</c> can be passed.</param>
 * <param name="phFoundWindow" type="OUT">The window handle (if one was found)</param>
 * <result>The result code, ERR_OK if the search was successful and a window was found, another error code otherwise.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysWindowTestFindWindow',`(char* pszWindowClass, char* pszWindowTitle, RTS_HANDLE* phFoundWindow)')

/**
 * <description>Function to take a screenshot into a file from the passed window.</description>
 * <param name="hWindow" type="IN">The window to take a screen shot from.</param>
 * <param name="pszDestinationFileName" type="IN">The file name of the screen shot that should be written.</param>
 * <param name="pScreenShotInfo" type="OUT">This pointer will be used to return information about the format of the screenshot. 
 *	A pointer to a valid object must be passed; This object will then be filled with the necessary information.</param>
 * <remarks>This method is optional (either by returnvalue ERR_NOTIMPLEMENTED or at compiletime) when the related SysGraphic* implementation
 *	implements the interface <see>SysGraphicTestable</see></remarks>
 * <result>The result code, ERR_OK if the screenshot was successful, another error code otherwise.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysWindowTestTakeScreenShot',`(RTS_HANDLE hWindow, char* pszDestinationFileName, SysWindowTestScreenShotInfo* pScreenShotInfo)')

/**
 * <description>Function to raise a mouse event on a given window.</description>
 * <param name="hWindow" type="IN">The window where the mouse event should be raised</param>
 * <param name="eventType" type="IN">Information about the mouse event, one of the values of the SYSWINDOWTEST_MOUSE_... constants.</param>
 * <param name="xCoordinateInWindow" type="IN">The x coordinate in window relative positions where the event should be raised.</param>
 * <param name="yCoordinateInWindow" type="IN">The y coordinate in window relative positions where the event should be raised.</param>
 * <result>The result code, ERR_OK if successful, another error code otherwise.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysWindowTestRaiseMouseEvent',`(RTS_HANDLE hWindow, RTS_I32 eventType, RTS_I32 xCoordinateInWindow, RTS_I32 yCoordinateInWindow)')

/**
 * <description>Function to raise a key event on a given window.</description>
 * <param name="hWindow" type="IN">The window where the key event should be raised</param>
 * <param name="keyType" type="IN">Information about the what type the keycode is of. Can be one of the values
 *	of the SYSWINDOWTEST_KEYTYPE_... constants.</param>
 * <param name="eventType" type="IN">Information about the key event, one of the values of the SYSWINDOWTEST_KEY_... constants.</param>
 * <param name="keyCode" type="IN">The keycode of the key that should be raised. Value range depends on the <see>keyType</see></param>
 * <result>The result code, ERR_OK if successful, another error code otherwise.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysWindowTestRaiseKeyEvent',`(RTS_HANDLE hWindow, RTS_I32 keyType, RTS_I32 eventType, RTS_I32 keyCode)')

#ifdef __cplusplus
}
#endif
