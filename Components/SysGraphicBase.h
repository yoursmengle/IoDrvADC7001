#ifndef __SYSGRAPHICBASE_H__
#define __SYSGRAPHICBASE_H__

#include "SysGraphicDefines.h"

#if defined __cplusplus && defined QT_TARGET_VISU
	#include <stdint.h>

	typedef int16_t	RTS_I16;
	typedef uint16_t RTS_UI16;
	typedef uintptr_t RTS_UINTPTR;
	typedef uintptr_t RTS_SIZE;
	typedef int32_t RTS_I32;
	typedef uint32_t RTS_UI32;
	typedef uint8_t RTS_IEC_BYTE;
	typedef RTS_I16 RTS_IEC_INT;
	typedef RTS_UI32 RTS_IEC_DWORD;
	typedef void* RTS_IEC_VOIDPTR;
	typedef char RTS_IEC_BOOL;
	typedef void* RTS_HANDLE;
	typedef int RTS_RESULT;
	typedef unsigned short RTS_WCHAR;
	typedef int RTS_BOOL;
	typedef float RTS_REAL32;
	typedef double RTS_REAL64;
#endif

typedef void (*PFINVOKEINWINDOWTASK)(RTS_UINTPTR ulCallbackParam);

typedef struct visucallback {
	int quit;
	PFINVOKEINWINDOWTASK pfToCall;
	RTS_UINTPTR ulParam;
} VISUCALLBACK;

#if defined __cplusplus
extern "C" {
#endif

typedef struct fifo {
	RTS_UI32 readpos;
	RTS_UI32 writepos;
	RTS_UI32 sizemask ;
	VISUCALLBACK *buffer[8];
} VISUFIFO;

#if defined __cplusplus
}
#endif


/**
 * <description> Pretty clear </description>
 * <remark>The layout of this structure must match VisuStructPoint from the library CmpVisuHandler!</remark>
 */
typedef struct
{
	RTS_I16 sX;
	RTS_I16 sY;
} RTS_Point;

/**
* <description> Pretty clear </description>
* <remark>The layout of this structure must match VisuStructPointF from the library CmpVisuHandler!</remark>
*/
typedef struct
{
	RTS_REAL32 fX;
	RTS_REAL32 fY;
} RTS_PointF;

/**
 * <description> Pretty clear </description>
 * <remark>The layout of this structure must match VisuStructSimpleRectangle from the library CmpVisuHandler!</remark>
 */
typedef struct
{
	RTS_Point ptTopLeft;
	RTS_Point ptBottomRight;
} RTS_Rectangle;

/**
* <description> Pretty clear </description>
* <remark>The layout of this structure must match VisuStructSimpleRectangleF from the library CmpVisuHandler!</remark>
*/
typedef struct
{
	RTS_PointF ptTopLeft;
	RTS_PointF ptBottomRight;
} RTS_RectangleF;

typedef struct
{
	RTS_I16 sWidth;
	RTS_I16 sHeight;
} RTS_Size;

/**
 * <category>Rectangle type</category>
 * <description></description>
 */
typedef enum {RT_RECTANGLE, RT_ROUNDRECT, RT_CIRCLE, RT_LINE, RT_LINEFROMTOPLEFT} RectangleType;

/**
 * <category>Polygon type</category>
 * <description></description>
 */
typedef enum {PT_POLYGON, PT_POLYLINE, PT_BEZIERS} PolygonType;

/**
 * <category>Pie type</category>
 * <description></description>
 */
typedef enum {PT_ARC, PT_PIE} PieType;

typedef enum {WCB_CYCLIC, WCB_BEFOREMESSAGE, WCB_AFTERMESSAGE, WCB_MAX} WindowCallbacks;
#if defined __cplusplus
extern "C" {
#endif

typedef RTS_RESULT (*PF_TV_EVENT)(void* pParams);		/* the parameter is a structure of type TargetvisuParams, done this way because of problems with the c++-compiler */

/**
 * <category>Targetvisu callbacks</category>
 * <description>Sends the current client size to the generic targetvisualization. Might be triggered when the 
 *	size has changed.</description>
 * <param name="pParams" type="IN">The targetvisu params.</param>
 * <param name="rNewSize" type="IN">The rectangle containing the new size of the window.</param>
 * <result>error code</result>
 */
typedef RTS_RESULT (*PF_TV_SETCLIENTSIZE)(void* pParams, RTS_Rectangle rNewSize);		

/**
 * <category>Targetvisu callbacks</category>
 * <description>This timer must be called by the targetvisu window to perform the cyclic updating 
 *	(polling if sth. has changed).</description>
 * <param name="pParams" type="IN">The targetvisu params.</param>
 * <param name="pInvalidateRect" type="IN">Optionally an invalid rectangle can be sent to the targetvisu. This rectangled
 *	will then be updated too.</param>
 * <result>error code</result>
 */
typedef RTS_RESULT (*PF_TV_UPDATETIMER)(void* pParams, RTS_Rectangle* pInvalidateRect);		

#define TARGETVISU_EDIT_COMMIT	1
#define TARGETVISU_EDIT_ESCAPE	2
#define TARGETVISU_EDIT_COMMITW	3

/**
 * <category>Targetvisu callbacks</category>
 * <description>This callback must be called by targetvisu window/editcontrol when the input into the editcontro
 *	is finished.
 *	Additionally this callback should be called when there is a click outside the editcontrol. In this situation a <see>TARGETVISU_EDIT_COMMIT</see>
 *	should be sent by the system specific implementation. This behaviour will then realize the possibility for fast user inputs by
 *	entering a value, clicking into the next editable cell and then enter the next value etc.</description>
 * <param name="pParams" type="IN">The targetvisu params.</param>
 * <param name="pszInputResult" type="IN">The result in the editcontrol or NULL in case of Escape. This pointer must be dynamically allocated
 *	because the pointer will be released afterwards.</param>
 * <param name="iAllocLen" type="IN">The allocated length of <see>pszInputResult</see></param>
 * <param name="iCommit" type="IN">1 to commit (return pressed, 2 if escape has been pressed</param>
 * <param name="pInvalidateRect" type="IN">Optionally an invalid rectangle can be sent to the targetvisu. This rectangled
 *	will then be updated too.</param>
 * <result>error code</result>
 */
typedef RTS_RESULT (*PF_TV_EDITCONTROLINPUT)(void* pParams, void* pszInputResult, RTS_SIZE iAllocLen, int iCommit, RTS_Rectangle* pInvalidateRect);		

/**
 * <category>Targetvisu callbacks</category>
 * <description>Such a callback must be called when a mouse event occurs.</description>
 * <param name="pParams" type="IN">The targetvisu params.</param>
 * <param name="ptMouse" type="IN">The coordinate of the mouse pointer.</param>
 * <result>error code</result>
 */
typedef RTS_RESULT (*PF_TV_MOUSEEVENT)(void* pParams, RTS_Point ptMouse);		

#define TV_KEYMOD_SHIFT			1
#define TV_KEYMOD_ALT			2
#define TV_KEYMOD_CTRL			4

/**
 * <category>Targetvisu callbacks</category>
 * <description>This callback must be called when a keyboard event occurs.</description>
 * <param name="lKeyCode" type="IN">The key code of the key event. This can be one of the members in the enum TV_KeyCodes (include SysWindowKeyMapping.h)
 *	or a specifically defined value in the range TV_KC_EXTENSIBLE_START..TV_KC_EXTENSIBLE_END that can be inserted into the configuration of the 
 *	visualization using an entry in the device description. </param>
 * <param name="ulModifierFlags" type="IN">A combination of the modifier keys that are pressed with the key.</param>
 * <result>error code</result>
 */
typedef RTS_RESULT (*PF_TV_KEYEVENT)(void* pParams, RTS_I32 lKeyCode, RTS_UI32 ulModifierFlags);		

/**
 * <category>Targetvisu callbacks</category>
 * <description>This callback can be called when a keyboard character event occurs. As difference to a key event, the usage of this
 *	event is to append characters to a string whereas the keyevents can be used for hotkey handling.</description>
 * <param name="unicodeChar" type="IN">The Unicode character representing the pressed key.</param>
 * <result>error code</result>
 */
typedef RTS_RESULT (*PF_TV_CHAREVENT)(void* pParams, RTS_WCHAR unicodeChar);

#ifndef GESTURES_MAX_PARALLEL_TOUCHES 
	#define GESTURES_MAX_PARALLEL_TOUCHES 5
#endif

typedef struct 
{
	int x;
	int y;
} GesturePoint;

typedef struct
{
	/* The current location of the touch */
	GesturePoint current;
	/* This value will be filled by the gesture manager and has not to be filled by the caller */
	GesturePoint last;				
} GestureTouchPoint;

typedef enum
{
	GESTURE_TYPEFLAGS_MOVE = 1,
	GESTURE_TYPEFLAGS_UP = 2,
	GESTURE_TYPEFLAGS_DOWN = 4,
	GESTURE_TYPEFLAGS_SYSTEMPRIMARY = 8					/* the touch that is regarded the primary one by the system part (usually the first active one) */
} GestureTouchTypeFlags;

typedef struct 
{
	/* The visualization has the following expectations on the id of a single touch: 
			* For a single touch the value should remain constant as long as the touch is active (ie. not released)
			* Each active touch has it's own unique id
			* The range of the ids for an active gesture should be at most 2^16 - 1 (necessary for handling touches in IEC)
		These requirements are fulfilled by the following two schemes for creating ids:
			* Simply increase the id (with wrapping around) with each new touch; theoretical range exceeding should not be
				a problem because an active gesture with 2^16 different touches is not very likely and will probably delay the next 
				repaint of the visualization for a very long time
			* Increase the ids with restart with every new gesture (ie. after all touches were released)
		A scheme using random ids will work only when the underlying range is smaller than 2^16
	*/
	int id;
	GestureTouchTypeFlags type;
	GestureTouchPoint location;
} GesturesTouch;

typedef struct 
{
	int touchesCount;
	GesturesTouch touches[GESTURES_MAX_PARALLEL_TOUCHES];
	/* the timestamp in milliseconds when this touch occurred; will be filled by a kernel 
		component so no need to fill in the sys implementation when raising this event */
	RTS_UI32 timeStamp;			
} GesturesTouchEvent;

/**
 * <category>Targetvisu callbacks</category>
 * <description>This callback can be called when a touch event is detected by the system adaptation.
 * </description>
 * <param name="e" type="IN">A pointer to a structure instance representing the current touch event including the information about 
 *	all the touches that are active.</param>
 * <result>error code</result>
 */
typedef RTS_RESULT (*PF_TV_TOUCHEVENT)(void* pParams, GesturesTouchEvent* e);

/**
 * <category>Targetvisu callbacks</category>
 * <description>This callback can be called to check whether a given keycode should be accepted and map it to the 
 *	according range of IEC-keycodes. This is necessary for those keys that that are not defined by default.
 * </description>
 * <param name="keyCode" type="IN">The keycode to check.</param>
 * <result>The mapped keycode if accepted, 0 if the key is invalid.</result>
 */
typedef RTS_UI16 (*PF_TV_KEYCODEVALDATION)(void* pParams, RTS_I32 keyCode);

#ifdef __cplusplus
}
#endif

typedef struct
{
	/* after this call the targetvisuparams must no longer be accessed from the window! */
	PF_TV_EVENT	pfShutDownVisu;		/* only used in case of singletasking targetvisu */
	
	/* assign the size of the window */
	PF_TV_SETCLIENTSIZE			pfSetClientSize;

	/* must be called in the interval TargetvisuParams.ulUpdateTimeMs to check for changes */
	PF_TV_UPDATETIMER			pfUpdateTimer;

	/* called after an input into an editcontrol is finished */
	PF_TV_EDITCONTROLINPUT		pfEditControlInput;

	/* called when the left mouse button goes down */
	PF_TV_MOUSEEVENT			pfMouseDown;

	/* called when the left mouse button goes up */
	PF_TV_MOUSEEVENT			pfMouseUp;

	/* called when the left mouse button is double clicked, Not yet used! */
	PF_TV_MOUSEEVENT			pfMouseDoubleClick;

	/* called when the mouse is moved */
	PF_TV_MOUSEEVENT			pfMouseMove;

	/* called when the mouse leaves the window */
	PF_TV_MOUSEEVENT			pfMouseLeave;

	/* call when a key goes down */
	PF_TV_KEYEVENT				pfKeyDown;

	/* call when a key goes up */
	PF_TV_KEYEVENT				pfKeyUp;

	/* call when a character is pressed by the keyboard; can be called additionally to pfKeyDown or pfKeyUp!
		This event callback should be called only for printable characters but not for control characters like
		delete etc. 
	*/
	PF_TV_CHAREVENT				pfChar;

	/* call this callback before painting the content of the visualization to the screen */
	PF_TV_EVENT					pfContentPainting;

	/* call this callback whenever the content of the visualization was displayed to the screen */
	PF_TV_EVENT					pfContentPainted;

	/* call this callback when a touch event is detected */
	PF_TV_TOUCHEVENT			pfTouch;

	/* call this callback to validate unknown keycodes */
	PF_TV_KEYCODEVALDATION		pfIsValidAdditionalKeyCode;
} TargetvisuCallbacks;

typedef struct
{
	RTS_IEC_DWORD		ulClientId;
	RTS_HANDLE			hWindow;
	RTS_HANDLE			hEditControl;
	RTS_HANDLE			hBackbuffer;
	RTS_HANDLE			hBackground;
	RTS_HANDLE			hEditFont;
	RTS_HANDLE			hPrint;
	RTS_HANDLE			hPrintSpecificData;
	TargetvisuCallbacks callbacks;
	RTS_UI32			ulUpdateTimeMs;
	void*				pCmpTargetvisuSpecificData;

	/* 
		This pointer can be used by the system specific implementation to store data relevant only
		for the concrete implementation.
		If this information is used by an implementation, it must be allocated using
		SysMemAllocData. The data will be released automatically when the targetvisu window is closed.
	*/
	void*				pSysTargetvisuSpecificData;
} TargetvisuParams;

/**
 * <description> 
 *	This Structure holds the data of a specific Event. This Event can be a Mousemessage,
 *	a pressed key, a written Input or sth. else.
 *		dwTag is defined in IEC-Code
 * </description>
 * <remark>The layout of this structure must match VisuStructEvent from the library CmpVisuHandler!</remark>
 */
typedef struct _tagEventStruct
{
	RTS_IEC_INT		iStructSize;
	RTS_IEC_DWORD	dwTag;
	RTS_IEC_DWORD	dwParam1;
	RTS_IEC_DWORD	dwParam2;
	RTS_IEC_DWORD	dwClientID;					/* The external id the client gets from registerclient, use after isregistered succeeded*/
	RTS_IEC_DWORD	dwAddDataSize;
	RTS_IEC_VOIDPTR	pAdditionalData;
	RTS_IEC_BOOL	bImportant;
	RTS_Rectangle rOptInvalidRect;
} EventStruct;

typedef struct _CommandBuffer
{
	RTS_IEC_BYTE btMagic1;
	RTS_IEC_BYTE btMagic2;
	RTS_IEC_BYTE btAlignment;
	RTS_IEC_BYTE btByteOrder;
	RTS_IEC_DWORD dwBufferProtection;
	RTS_IEC_DWORD dwCommandCount;
	RTS_IEC_DWORD dwUsedBufferSize;
	void* pBuffer;
} CommandBuffer;

#endif /* __SYSGRAPHICBASE_H__ */
