/**
 * <interfacename>CmpTargetVisu</interfacename>
 * <description> 
 *	Interface for the target visu.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpTargetVisu')

#include "SysGraphicBase.h"

/**
 * <category>Settings</category>
 * <description>Setting that decides about the maxmimum numer of entries in the bitmapbuffer.</description>
 */
#define CMPTARGETVISU_KEY_BMPBUFFERSIZE "BitmapbufferSize"
#define CMPTARGETVISU_VALUE_BMPBUFFERSIZE_DEFAULT 50

/**
 * <category>Settings</category>
 * <description>Setting that decides about the rate at which the targetvisu checks for updates of the
 * content of the display. This value in ms is no realtime value, so there can be quite some jitter on this value.</description>
 * <remarks>This setting is obsolete for the targetvisualization when working with recent programming environment and visu-profiles. The evaluation of this setting
 *	might disappear sometimes in the future.
 *	Nevertheless, the setting is still evaluated and respected by the remote targetvisualization.</remarks>
 */
#define CMPTARGETVISU_KEY_UPDATERATEMS "Updaterate_ms"
#define CMPTARGETVISU_VALUE_UPDATERATEMS_DEFAULT 200

/**
 * <category>Settings</category>
 * <description>Setting that decides about the font that is used for displaying tooltips.</description>
 */
#define CMPTARGETVISU_KEY_TOOLTIPFONT "TooltipFont"
#define CMPTARGETVISU_VALUE_TOOLTIPFONT_DEFAULT "Arial"
#define CMPTARGETVISU_MAXLEN_TOOLTIPFONT 30

/**
 * <category>Settings</category>
 * <description>Setting that decides about the fontsize that is used for displaying tooltips.</description>
 */
#define CMPTARGETVISU_KEY_TOOLTIPFONTSIZE "TooltipFontSize"
#define CMPTARGETVISU_VALUE_TOOLTIPFONTSIZE_DEFAULT 11

/**
 * <category>Settings</category>
 * <description>An internal setting affecting the startup of the targetvisualization. This settings should not be
 *	activated without knowledge of the effects! Activating this setting will only work together with a singletasking window component!</description>
 */
#define CMPTARGETVISU_KEY_ASYNCINITIALIZATION					"AsyncInitialization"
#define CMPTARGETVISU_VALUE_ASYNCINITIALIZATION_DEFAULT			0

/**
 * <category>Settings</category>
 * <description>An internal settings affecting the task handling of the targetvisualization. This setting should not be
 *	activated without knowledge of the effects!</description>
 */
#define CMPTARGETVISU_KEY_SIMULATESINGLETASKING					"SimulateSingletasking"
#ifndef CMPTARGETVISU_KEY_SIMULATESINGLETASKING_DEFAULT
	#define CMPTARGETVISU_KEY_SIMULATESINGLETASKING_DEFAULT			0
#endif

/**
 * <category>Settings</category>
 * <description>Special setting, probably only for touch systems to hide the cursor on the targetvisu window. Set to 1 if the cursor should be hidden.
 *	</description>
 */
#define CMPTARGETVISU_KEY_HIDECURSOR					"HideCursorCompletely"
#ifndef CMPTARGETVISU_VALUE_HIDECURSOR
	#define CMPTARGETVISU_VALUE_HIDECURSOR				0
#endif

/**
 * <category>Settings</category>
 * <description>A setting affecting the evaluation of gestures. As the gestures "Pan" and "Flick" both react to a movement of a single touch,
 *	it is necessary to decide which one to raise. For this mechanism, a velocity is calculated. The value of this velocity decides whether a pan or a flick
 *	gesture will be raised. When the velocity (in pixels per second) at the beginning of a gestures exceed the value of this setting, then a flick gesture will
 *	Please remark that this value must be non negative.
 *	be raised. Otherwise a pan gesture will be raised.
 *	</description>
 */
#define CMPTARGETVISU_KEY_GESTURES_FLICKPANTHRESHOLD_VELOCITY				"GesturesFlickPanThresholdVelocity"
#ifndef CMPTARGETVISU_VALUE_GESTURES_FLICKPANTHRESHOLD_VELOCITY_DEFAULT
	#define CMPTARGETVISU_VALUE_GESTURES_FLICKPANTHRESHOLD_VELOCITY_DEFAULT			1000
#endif

/**
 * <category>Settings</category>
 * <description>A setting affecting the evaluation of gestures. As the gestures "Pan" and "Flick" both react to a movement of a single touch,
 *  it is necessary to decide which one to raise. 
 *	For this mechanism, a distance and a velocity is calculated. To be able to calculate a reliable velocity, 
 *	we have to wait a short amount of time before comparing the according touch positions. This minimum waittime in milliseconds is defined by this setting.
 *  Please remark that an according "onetouch" gesture will not be started before this time is elapsed.
 *	Please remark that this value must be non negative.
 *	</description>
 */
#define CMPTARGETVISU_KEY_GESTURES_PANFLICK_THRESHOLD_WAITTIME			"GesturesPanFlickThresholdWaitTime"
#ifndef CMPTARGETVISU_VALUE_GESTURES_PANFLICK_THRESHOLD_WAITTIME_DEFAULT
	#define CMPTARGETVISU_VALUE_GESTURES_PANFLICK_THRESHOLD_WAITTIME_DEFAULT				40
#endif

/**
 * <category>Settings</category>
 * <description>A setting affecting the evaluation of gestures. We do not want to raise a pan gesture for clicks on a visualization. To prevent raising 
 *	such gestures, we do start a pan gesture only when the square of the distance is larger than this value. That means a value of 10 will 
 *	be exceeded by a movement of 4 pixels in one directions or 3 in one direction and 2 in the other one.
 *	Please remark that this value must be non negative.
 *	</description>
 */
#define CMPTARGETVISU_KEY_GESTURES_PANCLICK_THRESHOLD					"GesturesPanClickThresholdDistSquare"
#ifndef CMPTARGETVISU_VALUE_GESTURES_PANCLICK_THRESHOLD_DEFAULT
	#define CMPTARGETVISU_VALUE_GESTURES_PANCLICK_THRESHOLD_DEFAULT					10
#endif

/**
 * <category>Settings</category>
 * <description>Setting affecting the way the support of touch/multitouch features is detected. The following
 *	values are possible at the moment:
 *		o 0: No touch support at all
 *		o 1: Derive touch support from the according operating system window
 *		o 2: Explicitly activate single touch support
 *		o 6: Explicitly activate multi touch support (includes single touch in fact)
 *	</description>
 *	<remarks>This setting is only evaluated when the runtime system is compiled with support for touch-handling. On systems
 *		without this support, a possible touchscreen is handled like a mouse input in former times.
 *	</remarks>
 */
#define CMPTARGETVISU_KEY_TOUCHSUPPORT									"Touchsupport"
#define CMPTARGETVISU_VALUE_TOUCHSUPPORT_DISABLED						0
#define CMPTARGETVISU_VALUE_TOUCHSUPPORT_FROMOS							1
#define CMPTARGETVISU_VALUE_TOUCHSUPPORT_SINGLETOUCH					2
#define CMPTARGETVISU_VALUE_TOUCHSUPPORT_MULTITOUCH						6
#ifndef CMPTARGETVISU_VALUE_TOUCHSUPPORT_DEFAULT
	#define CMPTARGETVISU_VALUE_TOUCHSUPPORT_DEFAULT					CMPTARGETVISU_VALUE_TOUCHSUPPORT_FROMOS
#endif

/**
 * <category>Settings</category>
 * <description>Setting that allows to define additional range(s) of keycodes that will be accepted by the visualization
 *	and transferred to the IEC-Visualization. There these additional keycodes are typically captured by additionally defined
 *	keys (targetsetting "visualization\keyboardusage\additionalkeys"). 
 *	Without such an additional configuration, only the standard keycodes (as described at the targetsetting "visualization\keyboardusage\basekeys") 
 *	are accepted. Ranges are defined in combination with the setting "AdditionalKeyCodeRangeMax"
 *	The list of ranges must be indexed, starting by 0, e.g:
 *	Example for the following (unmapped) range: 55-66,78,90
 *	AdditionalKeyCodeRangeMin.0=55
 *	AdditionalKeyCodeRangeMin.1=78
 *	AdditionalKeyCodeRangeMin.2=90
 *	AdditionalKeyCodeRangeMax.0=66
 *	AdditionalKeyCodeRangeMax.1=78
 *	AdditionalKeyCodeRangeMax.2=90
 *	</description>
 *	<remarks>The numeric values of keycodes in this range will be converted only if there is an according entry "AdditionalKeyCodeOffset". If there
 *	is no such value, then the keycode value will simply be truncated from RTS_I32 to RTS_UI16.
 *	</remarks>
 */
#define CMPTARGETVISU_KEY_ADDITIONALKEYCODERANGEMIN						"AdditionalKeyCodeRangeMin"
#ifndef CMPTARGETVISU_VALUE_ADDITIONALKEYCODERANGEMIN_DEFAULT
	#define CMPTARGETVISU_VALUE_ADDITIONALKEYCODERANGEMIN_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <description>Setting that allows to define additional range(s) of keycodes that will be accepted by the visualization
 *	and transferred to the IEC-Visualization. There these additional keycodes are typically captured by additionally defined
 *	keys (targetsetting "visualization\keyboardusage\additionalkeys"). 
 *	Without such an additional configuration, only the standard keycodes (as described at the targetsetting "visualization\keyboardusage\basekeys") 
 *	are accepted. Ranges are defined in combination with the setting "AdditionalKeyCodeRangeMin"
 *	The list of ranges must be indexed, starting by 0, e.g:
 *	Example for the following (unmapped) range: 55-66,78,90
 *	AdditionalKeyCodeRangeMin.0=55
 *	AdditionalKeyCodeRangeMin.1=78
 *	AdditionalKeyCodeRangeMin.2=90
 *	AdditionalKeyCodeRangeMax.0=66
 *	AdditionalKeyCodeRangeMax.1=78
 *	AdditionalKeyCodeRangeMax.2=90
 *	</description>
 *	<remarks>The numeric values of keycodes in this range will be converted only if there is an according entry "AdditionalKeyCodeOffset". If there
 *	is no such value, then the keycode value will simply be truncated from RTS_I32 to RTS_UI16.
 *	</remarks>
 */
#define CMPTARGETVISU_KEY_ADDITIONALKEYCODERANGEMAX						"AdditionalKeyCodeRangeMax"
#ifndef CMPTARGETVISU_VALUE_ADDITIONALKEYCODERANGEMAX_DEFAULT
	#define CMPTARGETVISU_VALUE_ADDITIONALKEYCODERANGEMAX_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <description>Setting that allows to map keycodes of the related range ("AdditionalKeyCodeRangeMin", "AdditionalKeyCodeRangeMax", relation by index) 
 *	to the accepted range of an RTS_UI16.
 *	The mapped keycode is typically declared by additionally defined keys (targetsetting "visualization\keyboardusage\additionalkeys"). 
 *	This setting is optional. If there is no such setting declaration for a specific keycode range, then these will not become mapped.
 *	As an example for a mapping, have a look at the following declaration:
 *	AdditionalKeyCodeRangeMin.0=2000000
 *	AdditionalKeyCodeRangeMax.0=2000008
 *	AdditionalKeyCodeOffset.0=1999800
 *	In this example OS keycodes in the range [2000000, 2000008] will be mapped to the IEC keycodes [200, 208]
 *	</description>
 */
#define CMPTARGETVISU_KEY_ADDITIONALKEYCODEOFFSET						"AdditionalKeyCodeOffset"
#ifndef CMPTARGETVISU_VALUE_ADDITIONALKEYCODEOFFSET_DEFAULT
	#define CMPTARGETVISU_VALUE_ADDITIONALKEYCODEOFFSET_DEFAULT			0
#endif

/**
 * <category>Settings</category>
 * <description>Setting that decides at whitch position in whitch size and in which window type 
 * the targetvisu window should open. When the values 0,0,0,0,0 where used the targetvisu
 * window opens in fullscreen mode </description>
 *
 */
#define CMPTARGETVISU_KEY_WINDOWPOSITION_X "WindowPositionX"
#define CMPTARGETVISU_KEY_WINDOWPOSITION_Y "WindowPositionY"
#define CMPTARGETVISU_KEY_WINDOWSIZE_WIDTH "WindowSizeWidth"
#define CMPTARGETVISU_KEY_WINDOWSIZE_HEIGHT "WindowSizeHeight"
#define CMPTARGETVISU_KEY_WINDOW_TYPE "WindowType"

#define CMPTARGETVISU_VALUE_WINDOWPOSITION_X_DEFAULT 0
#define CMPTARGETVISU_VALUE_WINDOWPOSITION_Y_DEFAULT 0
#define CMPTARGETVISU_VALUE_WINDOWSIZE_WIDTH_DEFAULT 0
#define CMPTARGETVISU_VALUE_WINDOWSIZE_HEIGHT_DEFAULT 0
#define CMPTARGETVISU_VALUE_WINDOW_TYPE_DEFAULT 0

#ifndef CMPTARGETVISU_MAXSTARTVISUSIZE
	#define CMPTARGETVISU_MAXSTARTVISUSIZE 40
#endif /* CMPTARGETVISU_MAXSTARTVISUSIZE */ 

#ifndef CMPTARGETVISU_MAXCLIENTNAMESIZE
	#define CMPTARGETVISU_MAXCLIENTNAMESIZE 30
#endif	/* CMPTARGETVISU_MAXCLIENTNAMESIZE */

/**
 * <category>Settings</category>
 * <description>
 * Setting for the initial directory when opening or saving a file. The OS specific file path seperator
 * must be used. The configured path has to end with the seperator.
 * The "FileOpenSavePath" is updated automatically with the path selected in the last file open or save.
 * The "FileOpenSavePathFallback" is used whenever the "FileOpenSavePath" is not available, e.g. if it
 * points to a directory on a storage device that has been removed.
 * </description>
*/
#define CMPTARGETVISU_KEY_FILE_OPEN_SAVE_DIR "FileOpenSavePath"
#define CMPTARGETVISU_KEY_FILE_OPEN_SAVE_DIR_FALLBACK "FileOpenSavePathFallback"
#ifndef CMPTARGETVISU_VALUE_FILE_OPEN_SAVE_DIR_DEFAULT
	#define CMPTARGETVISU_VALUE_FILE_OPEN_SAVE_DIR_DEFAULT ""
#endif
#define CMPTARGETVISU_MAXLEN_FILE_OPEN_SAVE_DIR 254


DEF_API(`RTS_RESULT',`CDECL',`ExecutePaintCommands',`(TargetvisuParams* pParams, CommandBuffer* pBuffer)')

/**
 * <description> Creates an instance of a targetvisualisation, ie. creates a window etc. </description>
 * <param name="pszApplication" type="IN">The application the targetvisu should connect to.</param>
 * <param name="pWindowRect" type="IN">An optional rectangle that will be the rectangle of the targetvisu window. 
 * If this parameter is NULL, then the whole Screen will be used.</param>
 * <param name="pHandleRet" type="OUT">A handle to the created instance of the targetvisu.</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`CreateTargetvisuInstance',`(char* pszApplication, RTS_Rectangle* pWindowRect, RTS_HANDLE* pHandleRet)')

/**
 * <description>Special flag that will be set when the targetvisualization is executed (ie. drawn) on a different plc than
 * the paint commands are calculated. Probably only relevant when using CmpVisuHandlerRemote.</description>
 */
#define CMPTARGETVISU_FLAGS_REMOTE							0x0001
/**
 * <description>Special flag that can be set when the targetvisualization is executed (ie. drawn) on a different plc than
 * the paint commands are calculated. If this flag is set, then the visu will be drawn in best fit mode.</description>
 */
#define CMPTARGETVISU_FLAGS_REMOTE_BESTFIT					0x0002			
/**
 * <description>Special flag that can be set when the targetvisualization should measure the time that is necessary for executing
 *	the paint commands. The result of this measurement is sent to the IEC visualization using an input event.</description>
 */
#define CMPTARGETVISU_FLAGS_MEASURE_PAINTCOMMANDEXECUTION	0x0004
/**
 * <description>Special flag that can be set when the targetvisualization should measure the reaction time on mouse down events.
 *	the paint commands. The result of this measurement is sent to the IEC visualization using an input event.</description>
 * <remarks>Mouse events that are raised faster than the reaction can be drawn cannot be measured using this mechanism</remarks>
 */
#define CMPTARGETVISU_FLAGS_MEASURE_MOUSEDOWNREACTION		0x0008
/**
 * <description>Special flag that can be set when the targetvisualization should measure the reaction time on mouse down events.
 *	the paint commands. The result of this measurement is sent to the IEC visualization using an input event.</description>
 * <remarks>Mouse events that are raised faster than the reaction can be drawn cannot be measured using this mechanism</remarks>
 */
#define CMPTARGETVISU_FLAGS_MEASURE_PAINTINGTOSCREEN		0x0010
/**
 * <description>Flag that activates the evaluation of touch events in the targetvisualization (of course only if supported by the
 *	according system implementation.</description>
 */
#define CMPTARGETVISU_FLAGS_ACTIVATE_TOUCHHANDLING			0x0020
/**
 * <description>Flag that activates keyboard usage.</description>
 */
#define CMPTARGETVISU_FLAGS_ACTIVATE_KEYBOARD				0x0040
/**
 * <description>Special flag that can be set when the targetvisualization is executed (ie. drawn) on a different plc than
 * the paint commands are calculated. If this flag is set, then the visu will be drawn with scale type isotropic when best fit mode is set.</description>
 */
#define CMPTARGETVISU_FLAGS_REMOTE_SCALETYPEISOTROPIC		0x0080

/**
 * <description>Special flag that can be set when the targetvisualization is executed (ie. drawn) on a different plc than
 * the paint commands are calculated. If this flag is set, then the visu and the visualization dialogs will be drawn in best fit mode.</description>
 */
#define CMPTARGETVISU_FLAGS_REMOTE_BESTFIT_FOR_DIALOGS		0x0100

/**
 * <description>Notification that can be sent to the targetvisualization to signal that new paint data is available for execution.
 *	Arguments are not used at the moment.</description>
 */
#define	CMPTARGETVISU_NOTIFY_TAG_PAINTDATA_AVAILABLE			1


/**
 * <category>Event parameter</category>
 * <element name="pszImageId" type="IN">The ID of the image that should be (re)loaded.</element>
 * <element name="pszImagePath" type="IN">The filepath of the image that should be (re)loaded.</element>
 */
typedef struct
{
	char* pszImageId;
	char* pszImagePath;
} EVTPARAM_CmpTargetVisu_LoadImage;
#define EVTPARAMID_CmpTargetVisu_LoadImage	0x0001
#define EVTVERSION_CmpTargetVisu_LoadImage	0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when an image should be (re)loaded.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpTargetVisu_LoadImage</param>
 */
 #define EVT_CmpTargetVisu_LoadImage			MAKE_EVENTID(EVTCLASS_INFO, 1)

#define EVTPARAMID_CmpTargetvisu	0x0002
#define EVTVERSION_CmpTargetvisu	0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when the paintbuffer was painted to the system layer.</description>
 */
 #define EVT_CallbackContentPainted			MAKE_EVENTID(EVTCLASS_INFO, 2)


/*********************************************************************************
* Function definitions that could be called via IPC (in stub implementations)
*********************************************************************************/

#define TARGETVISU_IPC_NOTIFY		"targetvisunotify"

/*********************************************************************************
* END: Function definitions that could be called via IPC
*********************************************************************************/

typedef struct
{
	char* pszApplication;				/* The application, the targetvisu should connect to */
	RTS_Rectangle* pOptWindowRect;		/* An optional rectangle that will be the rectangle of the targetvisu window. 
										* If this parameter is NULL, then the whole Screen will be used.*/
	RTS_IEC_UINT uiAntiAliasing;	/* Information about the antialiasing settings chosen by the configuration. 0 -> No Antialiasing; 1 -> High quality antialiasing */
	RTS_IEC_UINT uiWindowType;		/* Information about the frame type of the targetvisu window (fullscreen, with window frame, without window frame,...); Reserved for future use; not yet implemented */
	RTS_IEC_UINT uiUpdateRateMs;	/* The cyclic update rate in milliseconds of the targetvisualization window; Reserved for future use; not yet implemented */
	RTS_IEC_UINT uiFlags;			/* Some flags regarding the targetvisualizations */
	char szOptionalStartVisu[CMPTARGETVISU_MAXSTARTVISUSIZE];		/* can be used for optionally setting a different start visualization than the default one; if an empty string is passed here, the default start visualization will be used */
	char szOptionalClientName[CMPTARGETVISU_MAXCLIENTNAMESIZE];		/* optional name of the client that will be passed to the iec visualization; empty string is the default */
} CmpTargetvisuCreateInformation;

/**
 * <description> Creates an instance of a targetvisualisation, ie. creates a window etc. In fact, this is an extension of <see>CreateTargetvisuInstance</see></description>
 * <param name="pCreateInformation" type="IN">The information used for creating the targetvisualization.</param>
 * <param name="pHandleRet" type="OUT">A handle to the created instance of the targetvisu.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`CreateTargetvisuInstance2',`(CmpTargetvisuCreateInformation* pCreateInformation, RTS_HANDLE* pHandleRet)')

/**
 * <description> Destroys an instance of a targetvisualization. </description>
 * <param name="hTargetVisu" type="IN">The instance that should be destroyed.</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`DestroyTargetvisuInstance',`(RTS_HANDLE hTargetVisu)')

typedef enum 
{
	TCB_BEFORERUNNING,		/* called before the message loop for the targetvisualization is started */
	TCB_REMOVING,			/* called when a targetvisu instance is being removed, in this callback this will be the last chance to access the targetvisuinstance */
	TCB_CREATED,					/* called when a targetvisu instance is created; ulParam1 will point to the CmpTargetvisuCreateInformation that was used for creating this instance */	
	TCB_GETCLIENTIDFAILED,			/* called when the polling for a valid client id failed; ulParam1 will be the error code that caused the problem */
	TCB_WINDOWOPENED,				/* called when the targetvisualization window is created. Take care, this event might be called from different threads! */
	TCB_WINDOWCREATIONFAILED		/* called when the creation of the targetvisualization window failed; ulParam1 will be the error code that caused the problem. Take care, this event might be called from different threads! */
} TargetvisuCallback;

typedef RTS_RESULT (CDECL *PFTARGETVISUCALLBACK)(RTS_HANDLE hTargetVisu, TargetvisuCallback wcb, RTS_UINTPTR ulCallbackParam, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description> Register a callback that will be notified about certain events within this component </description>
 * <param name="pfCallback" type="IN">The function that will be called. </param>
 * <param name="ulParam" type="IN">A Parameter that will be used when calling the registered callback.</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`TargetVisuRegisterEventHandler',`(PFTARGETVISUCALLBACK pfCallback, RTS_UINTPTR ulParam)')

/**
 * <description> Unregister a callback that will be notified about certain events within this component </description>
 * <param name="pfCallback" type="IN">The function for which the callback should be removed. </param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`TargetVisuUnregisterEventHandler',`(PFTARGETVISUCALLBACK pfCallback, RTS_UINTPTR ulParam)')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function will be called cylically by the generic visualization libraries for active targetvisualization clients when it is
 * supported by these libraries.
 * The call is used for implementing a targetvisualization without the need for multitasking systems.
 */
typedef struct tagtargetvisucyclic_struct
{
	RTS_IEC_XWORD dwTargetVisuHandle;	/* VAR_INPUT */	/* The handle of the targetvisualization instance that should be called. */
	RTS_IEC_UDINT TargetVisuCyclic;		/* VAR_OUTPUT */	
} targetvisucyclic_struct;

DEF_API(`void',`CDECL',`targetvisucyclic',`(targetvisucyclic_struct *p)',1,RTSITF_GET_SIGNATURE(0xD44FE2A3, 0xFE915838),0x03050500)

/**
 * This function can be used to find out the handle of the targetvisualization when having the according identification
 */
typedef struct tagtargetvisufindbyid_struct
{
	RTS_IEC_DWORD dwExternId;			/* VAR_INPUT */	/* The identification used by the visualization to manage their different clients. */
	RTS_IEC_RESULT TargetVisuFindById;	/* VAR_OUTPUT */	
	RTS_IEC_HANDLE hTargetVisu;			/* VAR_OUTPUT */	
} targetvisufindbyid_struct;

DEF_API(`void',`CDECL',`targetvisufindbyid',`(targetvisufindbyid_struct *p)',1,0xEC5DE09D,0x03050500)

/**
 * This function can be used to send notifications to a targetvisualization instance.
 * As those notifications are usually sent in an asynchronous way, do not expect immediate
 * effects when this function returned!
 */
typedef struct tagtargetvisunotify_struct
{
	RTS_IEC_HANDLE hTargetVisu;			/* VAR_INPUT */	/* The handle of the targetvisualization */
	RTS_IEC_DWORD dwTag;				/* VAR_INPUT */	/* The tag that signals which kind of information should be sent to the targetvisualization */
	RTS_IEC_BYTE *pParam;				/* VAR_INPUT */	/* This parameter can hold data that is related to the tag. The interpretation of this
 data depends on dwTag. It can as well be interpreted as a numeric (and thus non pointer) value */
	RTS_IEC_RESULT TargetVisuNotify;	/* VAR_OUTPUT */	
} targetvisunotify_struct;

DEF_API(`void',`CDECL',`targetvisunotify',`(targetvisunotify_struct *p)',1,0x78EF227D,0x03050500)

#ifdef __cplusplus
}
#endif

/**
 * <description>Function to raise a custom event, that will be delivered to all target visualizations</description>
 * <param name="uiEventType" type="IN">Identifies the event</param>
 * <param name="dwParam1" type="IN">event parameter 1 (event specific)</param>
 * <param name="dwParam2" type="IN">event parameter 2 (event specific)</param>
 * <param name="pAdditionalData" type="IN">Optional pointer to a piece of memory containing additional event data</param>
 * <param name="additionalDataSize" type="IN">The size of memory pAdditionalData points to. Only relevant if pAdditionalData is not 0</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`TargetVisuRaiseCustomEventAll',`(RTS_UI16 uiEventType, RTS_UI32 dwParam1, RTS_UI32 dwParam2, void* pAdditionalData, RTS_SIZE additionalDataSize)')

/** EXTERN LIB SECTION END **/

