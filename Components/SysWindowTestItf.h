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


	
	
#ifndef _SYSWINDOWTESTITF_H_
#define _SYSWINDOWTESTITF_H_

#include "CmpStd.h"

 

 




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
RTS_RESULT CDECL SysWindowTestFindWindow(char* pszWindowClass, char* pszWindowTitle, RTS_HANDLE* phFoundWindow);
typedef RTS_RESULT (CDECL * PFSYSWINDOWTESTFINDWINDOW) (char* pszWindowClass, char* pszWindowTitle, RTS_HANDLE* phFoundWindow);
#if defined(SYSWINDOWTEST_NOTIMPLEMENTED) || defined(SYSWINDOWTESTFINDWINDOW_NOTIMPLEMENTED)
	#define USE_SysWindowTestFindWindow
	#define EXT_SysWindowTestFindWindow
	#define GET_SysWindowTestFindWindow(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowTestFindWindow(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowTestFindWindow  FALSE
	#define EXP_SysWindowTestFindWindow  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowTestFindWindow
	#define EXT_SysWindowTestFindWindow
	#define GET_SysWindowTestFindWindow(fl)  CAL_CMGETAPI( "SysWindowTestFindWindow" ) 
	#define CAL_SysWindowTestFindWindow  SysWindowTestFindWindow
	#define CHK_SysWindowTestFindWindow  TRUE
	#define EXP_SysWindowTestFindWindow  CAL_CMEXPAPI( "SysWindowTestFindWindow" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOWTEST_EXTERNAL)
	#define USE_SysWindowTestFindWindow
	#define EXT_SysWindowTestFindWindow
	#define GET_SysWindowTestFindWindow(fl)  CAL_CMGETAPI( "SysWindowTestFindWindow" ) 
	#define CAL_SysWindowTestFindWindow  SysWindowTestFindWindow
	#define CHK_SysWindowTestFindWindow  TRUE
	#define EXP_SysWindowTestFindWindow  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowTestFindWindow", (RTS_UINTPTR)SysWindowTestFindWindow, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowTestSysWindowTestFindWindow
	#define EXT_SysWindowTestSysWindowTestFindWindow
	#define GET_SysWindowTestSysWindowTestFindWindow  ERR_OK
	#define CAL_SysWindowTestSysWindowTestFindWindow pISysWindowTest->ISysWindowTestFindWindow
	#define CHK_SysWindowTestSysWindowTestFindWindow (pISysWindowTest != NULL)
	#define EXP_SysWindowTestSysWindowTestFindWindow  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowTestFindWindow
	#define EXT_SysWindowTestFindWindow
	#define GET_SysWindowTestFindWindow(fl)  CAL_CMGETAPI( "SysWindowTestFindWindow" ) 
	#define CAL_SysWindowTestFindWindow pISysWindowTest->ISysWindowTestFindWindow
	#define CHK_SysWindowTestFindWindow (pISysWindowTest != NULL)
	#define EXP_SysWindowTestFindWindow  CAL_CMEXPAPI( "SysWindowTestFindWindow" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowTestFindWindow  PFSYSWINDOWTESTFINDWINDOW pfSysWindowTestFindWindow;
	#define EXT_SysWindowTestFindWindow  extern PFSYSWINDOWTESTFINDWINDOW pfSysWindowTestFindWindow;
	#define GET_SysWindowTestFindWindow(fl)  s_pfCMGetAPI2( "SysWindowTestFindWindow", (RTS_VOID_FCTPTR *)&pfSysWindowTestFindWindow, (fl), 0, 0)
	#define CAL_SysWindowTestFindWindow  pfSysWindowTestFindWindow
	#define CHK_SysWindowTestFindWindow  (pfSysWindowTestFindWindow != NULL)
	#define EXP_SysWindowTestFindWindow  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowTestFindWindow", (RTS_UINTPTR)SysWindowTestFindWindow, 0, 0) 
#endif




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
RTS_RESULT CDECL SysWindowTestTakeScreenShot(RTS_HANDLE hWindow, char* pszDestinationFileName, SysWindowTestScreenShotInfo* pScreenShotInfo);
typedef RTS_RESULT (CDECL * PFSYSWINDOWTESTTAKESCREENSHOT) (RTS_HANDLE hWindow, char* pszDestinationFileName, SysWindowTestScreenShotInfo* pScreenShotInfo);
#if defined(SYSWINDOWTEST_NOTIMPLEMENTED) || defined(SYSWINDOWTESTTAKESCREENSHOT_NOTIMPLEMENTED)
	#define USE_SysWindowTestTakeScreenShot
	#define EXT_SysWindowTestTakeScreenShot
	#define GET_SysWindowTestTakeScreenShot(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowTestTakeScreenShot(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowTestTakeScreenShot  FALSE
	#define EXP_SysWindowTestTakeScreenShot  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowTestTakeScreenShot
	#define EXT_SysWindowTestTakeScreenShot
	#define GET_SysWindowTestTakeScreenShot(fl)  CAL_CMGETAPI( "SysWindowTestTakeScreenShot" ) 
	#define CAL_SysWindowTestTakeScreenShot  SysWindowTestTakeScreenShot
	#define CHK_SysWindowTestTakeScreenShot  TRUE
	#define EXP_SysWindowTestTakeScreenShot  CAL_CMEXPAPI( "SysWindowTestTakeScreenShot" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOWTEST_EXTERNAL)
	#define USE_SysWindowTestTakeScreenShot
	#define EXT_SysWindowTestTakeScreenShot
	#define GET_SysWindowTestTakeScreenShot(fl)  CAL_CMGETAPI( "SysWindowTestTakeScreenShot" ) 
	#define CAL_SysWindowTestTakeScreenShot  SysWindowTestTakeScreenShot
	#define CHK_SysWindowTestTakeScreenShot  TRUE
	#define EXP_SysWindowTestTakeScreenShot  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowTestTakeScreenShot", (RTS_UINTPTR)SysWindowTestTakeScreenShot, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowTestSysWindowTestTakeScreenShot
	#define EXT_SysWindowTestSysWindowTestTakeScreenShot
	#define GET_SysWindowTestSysWindowTestTakeScreenShot  ERR_OK
	#define CAL_SysWindowTestSysWindowTestTakeScreenShot pISysWindowTest->ISysWindowTestTakeScreenShot
	#define CHK_SysWindowTestSysWindowTestTakeScreenShot (pISysWindowTest != NULL)
	#define EXP_SysWindowTestSysWindowTestTakeScreenShot  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowTestTakeScreenShot
	#define EXT_SysWindowTestTakeScreenShot
	#define GET_SysWindowTestTakeScreenShot(fl)  CAL_CMGETAPI( "SysWindowTestTakeScreenShot" ) 
	#define CAL_SysWindowTestTakeScreenShot pISysWindowTest->ISysWindowTestTakeScreenShot
	#define CHK_SysWindowTestTakeScreenShot (pISysWindowTest != NULL)
	#define EXP_SysWindowTestTakeScreenShot  CAL_CMEXPAPI( "SysWindowTestTakeScreenShot" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowTestTakeScreenShot  PFSYSWINDOWTESTTAKESCREENSHOT pfSysWindowTestTakeScreenShot;
	#define EXT_SysWindowTestTakeScreenShot  extern PFSYSWINDOWTESTTAKESCREENSHOT pfSysWindowTestTakeScreenShot;
	#define GET_SysWindowTestTakeScreenShot(fl)  s_pfCMGetAPI2( "SysWindowTestTakeScreenShot", (RTS_VOID_FCTPTR *)&pfSysWindowTestTakeScreenShot, (fl), 0, 0)
	#define CAL_SysWindowTestTakeScreenShot  pfSysWindowTestTakeScreenShot
	#define CHK_SysWindowTestTakeScreenShot  (pfSysWindowTestTakeScreenShot != NULL)
	#define EXP_SysWindowTestTakeScreenShot  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowTestTakeScreenShot", (RTS_UINTPTR)SysWindowTestTakeScreenShot, 0, 0) 
#endif




/**
 * <description>Function to raise a mouse event on a given window.</description>
 * <param name="hWindow" type="IN">The window where the mouse event should be raised</param>
 * <param name="eventType" type="IN">Information about the mouse event, one of the values of the SYSWINDOWTEST_MOUSE_... constants.</param>
 * <param name="xCoordinateInWindow" type="IN">The x coordinate in window relative positions where the event should be raised.</param>
 * <param name="yCoordinateInWindow" type="IN">The y coordinate in window relative positions where the event should be raised.</param>
 * <result>The result code, ERR_OK if successful, another error code otherwise.</result>
 */
RTS_RESULT CDECL SysWindowTestRaiseMouseEvent(RTS_HANDLE hWindow, RTS_I32 eventType, RTS_I32 xCoordinateInWindow, RTS_I32 yCoordinateInWindow);
typedef RTS_RESULT (CDECL * PFSYSWINDOWTESTRAISEMOUSEEVENT) (RTS_HANDLE hWindow, RTS_I32 eventType, RTS_I32 xCoordinateInWindow, RTS_I32 yCoordinateInWindow);
#if defined(SYSWINDOWTEST_NOTIMPLEMENTED) || defined(SYSWINDOWTESTRAISEMOUSEEVENT_NOTIMPLEMENTED)
	#define USE_SysWindowTestRaiseMouseEvent
	#define EXT_SysWindowTestRaiseMouseEvent
	#define GET_SysWindowTestRaiseMouseEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowTestRaiseMouseEvent(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowTestRaiseMouseEvent  FALSE
	#define EXP_SysWindowTestRaiseMouseEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowTestRaiseMouseEvent
	#define EXT_SysWindowTestRaiseMouseEvent
	#define GET_SysWindowTestRaiseMouseEvent(fl)  CAL_CMGETAPI( "SysWindowTestRaiseMouseEvent" ) 
	#define CAL_SysWindowTestRaiseMouseEvent  SysWindowTestRaiseMouseEvent
	#define CHK_SysWindowTestRaiseMouseEvent  TRUE
	#define EXP_SysWindowTestRaiseMouseEvent  CAL_CMEXPAPI( "SysWindowTestRaiseMouseEvent" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOWTEST_EXTERNAL)
	#define USE_SysWindowTestRaiseMouseEvent
	#define EXT_SysWindowTestRaiseMouseEvent
	#define GET_SysWindowTestRaiseMouseEvent(fl)  CAL_CMGETAPI( "SysWindowTestRaiseMouseEvent" ) 
	#define CAL_SysWindowTestRaiseMouseEvent  SysWindowTestRaiseMouseEvent
	#define CHK_SysWindowTestRaiseMouseEvent  TRUE
	#define EXP_SysWindowTestRaiseMouseEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowTestRaiseMouseEvent", (RTS_UINTPTR)SysWindowTestRaiseMouseEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowTestSysWindowTestRaiseMouseEvent
	#define EXT_SysWindowTestSysWindowTestRaiseMouseEvent
	#define GET_SysWindowTestSysWindowTestRaiseMouseEvent  ERR_OK
	#define CAL_SysWindowTestSysWindowTestRaiseMouseEvent pISysWindowTest->ISysWindowTestRaiseMouseEvent
	#define CHK_SysWindowTestSysWindowTestRaiseMouseEvent (pISysWindowTest != NULL)
	#define EXP_SysWindowTestSysWindowTestRaiseMouseEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowTestRaiseMouseEvent
	#define EXT_SysWindowTestRaiseMouseEvent
	#define GET_SysWindowTestRaiseMouseEvent(fl)  CAL_CMGETAPI( "SysWindowTestRaiseMouseEvent" ) 
	#define CAL_SysWindowTestRaiseMouseEvent pISysWindowTest->ISysWindowTestRaiseMouseEvent
	#define CHK_SysWindowTestRaiseMouseEvent (pISysWindowTest != NULL)
	#define EXP_SysWindowTestRaiseMouseEvent  CAL_CMEXPAPI( "SysWindowTestRaiseMouseEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowTestRaiseMouseEvent  PFSYSWINDOWTESTRAISEMOUSEEVENT pfSysWindowTestRaiseMouseEvent;
	#define EXT_SysWindowTestRaiseMouseEvent  extern PFSYSWINDOWTESTRAISEMOUSEEVENT pfSysWindowTestRaiseMouseEvent;
	#define GET_SysWindowTestRaiseMouseEvent(fl)  s_pfCMGetAPI2( "SysWindowTestRaiseMouseEvent", (RTS_VOID_FCTPTR *)&pfSysWindowTestRaiseMouseEvent, (fl), 0, 0)
	#define CAL_SysWindowTestRaiseMouseEvent  pfSysWindowTestRaiseMouseEvent
	#define CHK_SysWindowTestRaiseMouseEvent  (pfSysWindowTestRaiseMouseEvent != NULL)
	#define EXP_SysWindowTestRaiseMouseEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowTestRaiseMouseEvent", (RTS_UINTPTR)SysWindowTestRaiseMouseEvent, 0, 0) 
#endif




/**
 * <description>Function to raise a key event on a given window.</description>
 * <param name="hWindow" type="IN">The window where the key event should be raised</param>
 * <param name="keyType" type="IN">Information about the what type the keycode is of. Can be one of the values
 *	of the SYSWINDOWTEST_KEYTYPE_... constants.</param>
 * <param name="eventType" type="IN">Information about the key event, one of the values of the SYSWINDOWTEST_KEY_... constants.</param>
 * <param name="keyCode" type="IN">The keycode of the key that should be raised. Value range depends on the <see>keyType</see></param>
 * <result>The result code, ERR_OK if successful, another error code otherwise.</result>
 */
RTS_RESULT CDECL SysWindowTestRaiseKeyEvent(RTS_HANDLE hWindow, RTS_I32 keyType, RTS_I32 eventType, RTS_I32 keyCode);
typedef RTS_RESULT (CDECL * PFSYSWINDOWTESTRAISEKEYEVENT) (RTS_HANDLE hWindow, RTS_I32 keyType, RTS_I32 eventType, RTS_I32 keyCode);
#if defined(SYSWINDOWTEST_NOTIMPLEMENTED) || defined(SYSWINDOWTESTRAISEKEYEVENT_NOTIMPLEMENTED)
	#define USE_SysWindowTestRaiseKeyEvent
	#define EXT_SysWindowTestRaiseKeyEvent
	#define GET_SysWindowTestRaiseKeyEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowTestRaiseKeyEvent(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowTestRaiseKeyEvent  FALSE
	#define EXP_SysWindowTestRaiseKeyEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowTestRaiseKeyEvent
	#define EXT_SysWindowTestRaiseKeyEvent
	#define GET_SysWindowTestRaiseKeyEvent(fl)  CAL_CMGETAPI( "SysWindowTestRaiseKeyEvent" ) 
	#define CAL_SysWindowTestRaiseKeyEvent  SysWindowTestRaiseKeyEvent
	#define CHK_SysWindowTestRaiseKeyEvent  TRUE
	#define EXP_SysWindowTestRaiseKeyEvent  CAL_CMEXPAPI( "SysWindowTestRaiseKeyEvent" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOWTEST_EXTERNAL)
	#define USE_SysWindowTestRaiseKeyEvent
	#define EXT_SysWindowTestRaiseKeyEvent
	#define GET_SysWindowTestRaiseKeyEvent(fl)  CAL_CMGETAPI( "SysWindowTestRaiseKeyEvent" ) 
	#define CAL_SysWindowTestRaiseKeyEvent  SysWindowTestRaiseKeyEvent
	#define CHK_SysWindowTestRaiseKeyEvent  TRUE
	#define EXP_SysWindowTestRaiseKeyEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowTestRaiseKeyEvent", (RTS_UINTPTR)SysWindowTestRaiseKeyEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowTestSysWindowTestRaiseKeyEvent
	#define EXT_SysWindowTestSysWindowTestRaiseKeyEvent
	#define GET_SysWindowTestSysWindowTestRaiseKeyEvent  ERR_OK
	#define CAL_SysWindowTestSysWindowTestRaiseKeyEvent pISysWindowTest->ISysWindowTestRaiseKeyEvent
	#define CHK_SysWindowTestSysWindowTestRaiseKeyEvent (pISysWindowTest != NULL)
	#define EXP_SysWindowTestSysWindowTestRaiseKeyEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowTestRaiseKeyEvent
	#define EXT_SysWindowTestRaiseKeyEvent
	#define GET_SysWindowTestRaiseKeyEvent(fl)  CAL_CMGETAPI( "SysWindowTestRaiseKeyEvent" ) 
	#define CAL_SysWindowTestRaiseKeyEvent pISysWindowTest->ISysWindowTestRaiseKeyEvent
	#define CHK_SysWindowTestRaiseKeyEvent (pISysWindowTest != NULL)
	#define EXP_SysWindowTestRaiseKeyEvent  CAL_CMEXPAPI( "SysWindowTestRaiseKeyEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowTestRaiseKeyEvent  PFSYSWINDOWTESTRAISEKEYEVENT pfSysWindowTestRaiseKeyEvent;
	#define EXT_SysWindowTestRaiseKeyEvent  extern PFSYSWINDOWTESTRAISEKEYEVENT pfSysWindowTestRaiseKeyEvent;
	#define GET_SysWindowTestRaiseKeyEvent(fl)  s_pfCMGetAPI2( "SysWindowTestRaiseKeyEvent", (RTS_VOID_FCTPTR *)&pfSysWindowTestRaiseKeyEvent, (fl), 0, 0)
	#define CAL_SysWindowTestRaiseKeyEvent  pfSysWindowTestRaiseKeyEvent
	#define CHK_SysWindowTestRaiseKeyEvent  (pfSysWindowTestRaiseKeyEvent != NULL)
	#define EXP_SysWindowTestRaiseKeyEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowTestRaiseKeyEvent", (RTS_UINTPTR)SysWindowTestRaiseKeyEvent, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSWINDOWTESTFINDWINDOW ISysWindowTestFindWindow;
 	PFSYSWINDOWTESTTAKESCREENSHOT ISysWindowTestTakeScreenShot;
 	PFSYSWINDOWTESTRAISEMOUSEEVENT ISysWindowTestRaiseMouseEvent;
 	PFSYSWINDOWTESTRAISEKEYEVENT ISysWindowTestRaiseKeyEvent;
 } ISysWindowTest_C;

#ifdef CPLUSPLUS
class ISysWindowTest : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISysWindowTestFindWindow(char* pszWindowClass, char* pszWindowTitle, RTS_HANDLE* phFoundWindow) =0;
		virtual RTS_RESULT CDECL ISysWindowTestTakeScreenShot(RTS_HANDLE hWindow, char* pszDestinationFileName, SysWindowTestScreenShotInfo* pScreenShotInfo) =0;
		virtual RTS_RESULT CDECL ISysWindowTestRaiseMouseEvent(RTS_HANDLE hWindow, RTS_I32 eventType, RTS_I32 xCoordinateInWindow, RTS_I32 yCoordinateInWindow) =0;
		virtual RTS_RESULT CDECL ISysWindowTestRaiseKeyEvent(RTS_HANDLE hWindow, RTS_I32 keyType, RTS_I32 eventType, RTS_I32 keyCode) =0;
};
	#ifndef ITF_SysWindowTest
		#define ITF_SysWindowTest static ISysWindowTest *pISysWindowTest = NULL;
	#endif
	#define EXTITF_SysWindowTest
#else	/*CPLUSPLUS*/
	typedef ISysWindowTest_C		ISysWindowTest;
	#ifndef ITF_SysWindowTest
		#define ITF_SysWindowTest
	#endif
	#define EXTITF_SysWindowTest
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSWINDOWTESTITF_H_*/
