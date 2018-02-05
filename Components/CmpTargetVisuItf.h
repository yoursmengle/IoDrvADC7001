 /**
 * <interfacename>CmpTargetVisu</interfacename>
 * <description> 
 *	Interface for the target visu.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPTARGETVISUITF_H_
#define _CMPTARGETVISUITF_H_

#include "CmpStd.h"

 

 




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


RTS_RESULT CDECL ExecutePaintCommands(TargetvisuParams* pParams, CommandBuffer* pBuffer);
typedef RTS_RESULT (CDECL * PFEXECUTEPAINTCOMMANDS) (TargetvisuParams* pParams, CommandBuffer* pBuffer);
#if defined(CMPTARGETVISU_NOTIMPLEMENTED) || defined(EXECUTEPAINTCOMMANDS_NOTIMPLEMENTED)
	#define USE_ExecutePaintCommands
	#define EXT_ExecutePaintCommands
	#define GET_ExecutePaintCommands(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ExecutePaintCommands(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_ExecutePaintCommands  FALSE
	#define EXP_ExecutePaintCommands  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ExecutePaintCommands
	#define EXT_ExecutePaintCommands
	#define GET_ExecutePaintCommands(fl)  CAL_CMGETAPI( "ExecutePaintCommands" ) 
	#define CAL_ExecutePaintCommands  ExecutePaintCommands
	#define CHK_ExecutePaintCommands  TRUE
	#define EXP_ExecutePaintCommands  CAL_CMEXPAPI( "ExecutePaintCommands" ) 
#elif defined(MIXED_LINK) && !defined(CMPTARGETVISU_EXTERNAL)
	#define USE_ExecutePaintCommands
	#define EXT_ExecutePaintCommands
	#define GET_ExecutePaintCommands(fl)  CAL_CMGETAPI( "ExecutePaintCommands" ) 
	#define CAL_ExecutePaintCommands  ExecutePaintCommands
	#define CHK_ExecutePaintCommands  TRUE
	#define EXP_ExecutePaintCommands  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ExecutePaintCommands", (RTS_UINTPTR)ExecutePaintCommands, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTargetVisuExecutePaintCommands
	#define EXT_CmpTargetVisuExecutePaintCommands
	#define GET_CmpTargetVisuExecutePaintCommands  ERR_OK
	#define CAL_CmpTargetVisuExecutePaintCommands  ExecutePaintCommands
	#define CHK_CmpTargetVisuExecutePaintCommands  TRUE
	#define EXP_CmpTargetVisuExecutePaintCommands  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ExecutePaintCommands
	#define EXT_ExecutePaintCommands
	#define GET_ExecutePaintCommands(fl)  CAL_CMGETAPI( "ExecutePaintCommands" ) 
	#define CAL_ExecutePaintCommands  ExecutePaintCommands
	#define CHK_ExecutePaintCommands  TRUE
	#define EXP_ExecutePaintCommands  CAL_CMEXPAPI( "ExecutePaintCommands" ) 
#else /* DYNAMIC_LINK */
	#define USE_ExecutePaintCommands  PFEXECUTEPAINTCOMMANDS pfExecutePaintCommands;
	#define EXT_ExecutePaintCommands  extern PFEXECUTEPAINTCOMMANDS pfExecutePaintCommands;
	#define GET_ExecutePaintCommands(fl)  s_pfCMGetAPI2( "ExecutePaintCommands", (RTS_VOID_FCTPTR *)&pfExecutePaintCommands, (fl), 0, 0)
	#define CAL_ExecutePaintCommands  pfExecutePaintCommands
	#define CHK_ExecutePaintCommands  (pfExecutePaintCommands != NULL)
	#define EXP_ExecutePaintCommands   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ExecutePaintCommands", (RTS_UINTPTR)ExecutePaintCommands, 0, 0) 
#endif


/**
 * <description> Creates an instance of a targetvisualisation, ie. creates a window etc. </description>
 * <param name="pszApplication" type="IN">The application the targetvisu should connect to.</param>
 * <param name="pWindowRect" type="IN">An optional rectangle that will be the rectangle of the targetvisu window. 
 * If this parameter is NULL, then the whole Screen will be used.</param>
 * <param name="pHandleRet" type="OUT">A handle to the created instance of the targetvisu.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL CreateTargetvisuInstance(char* pszApplication, RTS_Rectangle* pWindowRect, RTS_HANDLE* pHandleRet);
typedef RTS_RESULT (CDECL * PFCREATETARGETVISUINSTANCE) (char* pszApplication, RTS_Rectangle* pWindowRect, RTS_HANDLE* pHandleRet);
#if defined(CMPTARGETVISU_NOTIMPLEMENTED) || defined(CREATETARGETVISUINSTANCE_NOTIMPLEMENTED)
	#define USE_CreateTargetvisuInstance
	#define EXT_CreateTargetvisuInstance
	#define GET_CreateTargetvisuInstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CreateTargetvisuInstance(p0,p1,p2) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CreateTargetvisuInstance  FALSE
	#define EXP_CreateTargetvisuInstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CreateTargetvisuInstance
	#define EXT_CreateTargetvisuInstance
	#define GET_CreateTargetvisuInstance(fl)  CAL_CMGETAPI( "CreateTargetvisuInstance" ) 
	#define CAL_CreateTargetvisuInstance  CreateTargetvisuInstance
	#define CHK_CreateTargetvisuInstance  TRUE
	#define EXP_CreateTargetvisuInstance  CAL_CMEXPAPI( "CreateTargetvisuInstance" ) 
#elif defined(MIXED_LINK) && !defined(CMPTARGETVISU_EXTERNAL)
	#define USE_CreateTargetvisuInstance
	#define EXT_CreateTargetvisuInstance
	#define GET_CreateTargetvisuInstance(fl)  CAL_CMGETAPI( "CreateTargetvisuInstance" ) 
	#define CAL_CreateTargetvisuInstance  CreateTargetvisuInstance
	#define CHK_CreateTargetvisuInstance  TRUE
	#define EXP_CreateTargetvisuInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CreateTargetvisuInstance", (RTS_UINTPTR)CreateTargetvisuInstance, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTargetVisuCreateTargetvisuInstance
	#define EXT_CmpTargetVisuCreateTargetvisuInstance
	#define GET_CmpTargetVisuCreateTargetvisuInstance  ERR_OK
	#define CAL_CmpTargetVisuCreateTargetvisuInstance  CreateTargetvisuInstance
	#define CHK_CmpTargetVisuCreateTargetvisuInstance  TRUE
	#define EXP_CmpTargetVisuCreateTargetvisuInstance  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CreateTargetvisuInstance
	#define EXT_CreateTargetvisuInstance
	#define GET_CreateTargetvisuInstance(fl)  CAL_CMGETAPI( "CreateTargetvisuInstance" ) 
	#define CAL_CreateTargetvisuInstance  CreateTargetvisuInstance
	#define CHK_CreateTargetvisuInstance  TRUE
	#define EXP_CreateTargetvisuInstance  CAL_CMEXPAPI( "CreateTargetvisuInstance" ) 
#else /* DYNAMIC_LINK */
	#define USE_CreateTargetvisuInstance  PFCREATETARGETVISUINSTANCE pfCreateTargetvisuInstance;
	#define EXT_CreateTargetvisuInstance  extern PFCREATETARGETVISUINSTANCE pfCreateTargetvisuInstance;
	#define GET_CreateTargetvisuInstance(fl)  s_pfCMGetAPI2( "CreateTargetvisuInstance", (RTS_VOID_FCTPTR *)&pfCreateTargetvisuInstance, (fl), 0, 0)
	#define CAL_CreateTargetvisuInstance  pfCreateTargetvisuInstance
	#define CHK_CreateTargetvisuInstance  (pfCreateTargetvisuInstance != NULL)
	#define EXP_CreateTargetvisuInstance   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CreateTargetvisuInstance", (RTS_UINTPTR)CreateTargetvisuInstance, 0, 0) 
#endif


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
RTS_RESULT CDECL CreateTargetvisuInstance2(CmpTargetvisuCreateInformation* pCreateInformation, RTS_HANDLE* pHandleRet);
typedef RTS_RESULT (CDECL * PFCREATETARGETVISUINSTANCE2) (CmpTargetvisuCreateInformation* pCreateInformation, RTS_HANDLE* pHandleRet);
#if defined(CMPTARGETVISU_NOTIMPLEMENTED) || defined(CREATETARGETVISUINSTANCE2_NOTIMPLEMENTED)
	#define USE_CreateTargetvisuInstance2
	#define EXT_CreateTargetvisuInstance2
	#define GET_CreateTargetvisuInstance2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CreateTargetvisuInstance2(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CreateTargetvisuInstance2  FALSE
	#define EXP_CreateTargetvisuInstance2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CreateTargetvisuInstance2
	#define EXT_CreateTargetvisuInstance2
	#define GET_CreateTargetvisuInstance2(fl)  CAL_CMGETAPI( "CreateTargetvisuInstance2" ) 
	#define CAL_CreateTargetvisuInstance2  CreateTargetvisuInstance2
	#define CHK_CreateTargetvisuInstance2  TRUE
	#define EXP_CreateTargetvisuInstance2  CAL_CMEXPAPI( "CreateTargetvisuInstance2" ) 
#elif defined(MIXED_LINK) && !defined(CMPTARGETVISU_EXTERNAL)
	#define USE_CreateTargetvisuInstance2
	#define EXT_CreateTargetvisuInstance2
	#define GET_CreateTargetvisuInstance2(fl)  CAL_CMGETAPI( "CreateTargetvisuInstance2" ) 
	#define CAL_CreateTargetvisuInstance2  CreateTargetvisuInstance2
	#define CHK_CreateTargetvisuInstance2  TRUE
	#define EXP_CreateTargetvisuInstance2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CreateTargetvisuInstance2", (RTS_UINTPTR)CreateTargetvisuInstance2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTargetVisuCreateTargetvisuInstance2
	#define EXT_CmpTargetVisuCreateTargetvisuInstance2
	#define GET_CmpTargetVisuCreateTargetvisuInstance2  ERR_OK
	#define CAL_CmpTargetVisuCreateTargetvisuInstance2 pICmpTargetVisu->ICreateTargetvisuInstance2
	#define CHK_CmpTargetVisuCreateTargetvisuInstance2 (pICmpTargetVisu != NULL)
	#define EXP_CmpTargetVisuCreateTargetvisuInstance2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CreateTargetvisuInstance2
	#define EXT_CreateTargetvisuInstance2
	#define GET_CreateTargetvisuInstance2(fl)  CAL_CMGETAPI( "CreateTargetvisuInstance2" ) 
	#define CAL_CreateTargetvisuInstance2 pICmpTargetVisu->ICreateTargetvisuInstance2
	#define CHK_CreateTargetvisuInstance2 (pICmpTargetVisu != NULL)
	#define EXP_CreateTargetvisuInstance2  CAL_CMEXPAPI( "CreateTargetvisuInstance2" ) 
#else /* DYNAMIC_LINK */
	#define USE_CreateTargetvisuInstance2  PFCREATETARGETVISUINSTANCE2 pfCreateTargetvisuInstance2;
	#define EXT_CreateTargetvisuInstance2  extern PFCREATETARGETVISUINSTANCE2 pfCreateTargetvisuInstance2;
	#define GET_CreateTargetvisuInstance2(fl)  s_pfCMGetAPI2( "CreateTargetvisuInstance2", (RTS_VOID_FCTPTR *)&pfCreateTargetvisuInstance2, (fl), 0, 0)
	#define CAL_CreateTargetvisuInstance2  pfCreateTargetvisuInstance2
	#define CHK_CreateTargetvisuInstance2  (pfCreateTargetvisuInstance2 != NULL)
	#define EXP_CreateTargetvisuInstance2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CreateTargetvisuInstance2", (RTS_UINTPTR)CreateTargetvisuInstance2, 0, 0) 
#endif




/**
 * <description> Destroys an instance of a targetvisualization. </description>
 * <param name="hTargetVisu" type="IN">The instance that should be destroyed.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL DestroyTargetvisuInstance(RTS_HANDLE hTargetVisu);
typedef RTS_RESULT (CDECL * PFDESTROYTARGETVISUINSTANCE) (RTS_HANDLE hTargetVisu);
#if defined(CMPTARGETVISU_NOTIMPLEMENTED) || defined(DESTROYTARGETVISUINSTANCE_NOTIMPLEMENTED)
	#define USE_DestroyTargetvisuInstance
	#define EXT_DestroyTargetvisuInstance
	#define GET_DestroyTargetvisuInstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DestroyTargetvisuInstance(p0) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_DestroyTargetvisuInstance  FALSE
	#define EXP_DestroyTargetvisuInstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DestroyTargetvisuInstance
	#define EXT_DestroyTargetvisuInstance
	#define GET_DestroyTargetvisuInstance(fl)  CAL_CMGETAPI( "DestroyTargetvisuInstance" ) 
	#define CAL_DestroyTargetvisuInstance  DestroyTargetvisuInstance
	#define CHK_DestroyTargetvisuInstance  TRUE
	#define EXP_DestroyTargetvisuInstance  CAL_CMEXPAPI( "DestroyTargetvisuInstance" ) 
#elif defined(MIXED_LINK) && !defined(CMPTARGETVISU_EXTERNAL)
	#define USE_DestroyTargetvisuInstance
	#define EXT_DestroyTargetvisuInstance
	#define GET_DestroyTargetvisuInstance(fl)  CAL_CMGETAPI( "DestroyTargetvisuInstance" ) 
	#define CAL_DestroyTargetvisuInstance  DestroyTargetvisuInstance
	#define CHK_DestroyTargetvisuInstance  TRUE
	#define EXP_DestroyTargetvisuInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DestroyTargetvisuInstance", (RTS_UINTPTR)DestroyTargetvisuInstance, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTargetVisuDestroyTargetvisuInstance
	#define EXT_CmpTargetVisuDestroyTargetvisuInstance
	#define GET_CmpTargetVisuDestroyTargetvisuInstance  ERR_OK
	#define CAL_CmpTargetVisuDestroyTargetvisuInstance  DestroyTargetvisuInstance
	#define CHK_CmpTargetVisuDestroyTargetvisuInstance  TRUE
	#define EXP_CmpTargetVisuDestroyTargetvisuInstance  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DestroyTargetvisuInstance
	#define EXT_DestroyTargetvisuInstance
	#define GET_DestroyTargetvisuInstance(fl)  CAL_CMGETAPI( "DestroyTargetvisuInstance" ) 
	#define CAL_DestroyTargetvisuInstance  DestroyTargetvisuInstance
	#define CHK_DestroyTargetvisuInstance  TRUE
	#define EXP_DestroyTargetvisuInstance  CAL_CMEXPAPI( "DestroyTargetvisuInstance" ) 
#else /* DYNAMIC_LINK */
	#define USE_DestroyTargetvisuInstance  PFDESTROYTARGETVISUINSTANCE pfDestroyTargetvisuInstance;
	#define EXT_DestroyTargetvisuInstance  extern PFDESTROYTARGETVISUINSTANCE pfDestroyTargetvisuInstance;
	#define GET_DestroyTargetvisuInstance(fl)  s_pfCMGetAPI2( "DestroyTargetvisuInstance", (RTS_VOID_FCTPTR *)&pfDestroyTargetvisuInstance, (fl), 0, 0)
	#define CAL_DestroyTargetvisuInstance  pfDestroyTargetvisuInstance
	#define CHK_DestroyTargetvisuInstance  (pfDestroyTargetvisuInstance != NULL)
	#define EXP_DestroyTargetvisuInstance   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DestroyTargetvisuInstance", (RTS_UINTPTR)DestroyTargetvisuInstance, 0, 0) 
#endif


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
RTS_RESULT CDECL TargetVisuRegisterEventHandler(PFTARGETVISUCALLBACK pfCallback, RTS_UINTPTR ulParam);
typedef RTS_RESULT (CDECL * PFTARGETVISUREGISTEREVENTHANDLER) (PFTARGETVISUCALLBACK pfCallback, RTS_UINTPTR ulParam);
#if defined(CMPTARGETVISU_NOTIMPLEMENTED) || defined(TARGETVISUREGISTEREVENTHANDLER_NOTIMPLEMENTED)
	#define USE_TargetVisuRegisterEventHandler
	#define EXT_TargetVisuRegisterEventHandler
	#define GET_TargetVisuRegisterEventHandler(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TargetVisuRegisterEventHandler(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TargetVisuRegisterEventHandler  FALSE
	#define EXP_TargetVisuRegisterEventHandler  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TargetVisuRegisterEventHandler
	#define EXT_TargetVisuRegisterEventHandler
	#define GET_TargetVisuRegisterEventHandler(fl)  CAL_CMGETAPI( "TargetVisuRegisterEventHandler" ) 
	#define CAL_TargetVisuRegisterEventHandler  TargetVisuRegisterEventHandler
	#define CHK_TargetVisuRegisterEventHandler  TRUE
	#define EXP_TargetVisuRegisterEventHandler  CAL_CMEXPAPI( "TargetVisuRegisterEventHandler" ) 
#elif defined(MIXED_LINK) && !defined(CMPTARGETVISU_EXTERNAL)
	#define USE_TargetVisuRegisterEventHandler
	#define EXT_TargetVisuRegisterEventHandler
	#define GET_TargetVisuRegisterEventHandler(fl)  CAL_CMGETAPI( "TargetVisuRegisterEventHandler" ) 
	#define CAL_TargetVisuRegisterEventHandler  TargetVisuRegisterEventHandler
	#define CHK_TargetVisuRegisterEventHandler  TRUE
	#define EXP_TargetVisuRegisterEventHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TargetVisuRegisterEventHandler", (RTS_UINTPTR)TargetVisuRegisterEventHandler, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTargetVisuTargetVisuRegisterEventHandler
	#define EXT_CmpTargetVisuTargetVisuRegisterEventHandler
	#define GET_CmpTargetVisuTargetVisuRegisterEventHandler  ERR_OK
	#define CAL_CmpTargetVisuTargetVisuRegisterEventHandler  TargetVisuRegisterEventHandler
	#define CHK_CmpTargetVisuTargetVisuRegisterEventHandler  TRUE
	#define EXP_CmpTargetVisuTargetVisuRegisterEventHandler  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TargetVisuRegisterEventHandler
	#define EXT_TargetVisuRegisterEventHandler
	#define GET_TargetVisuRegisterEventHandler(fl)  CAL_CMGETAPI( "TargetVisuRegisterEventHandler" ) 
	#define CAL_TargetVisuRegisterEventHandler  TargetVisuRegisterEventHandler
	#define CHK_TargetVisuRegisterEventHandler  TRUE
	#define EXP_TargetVisuRegisterEventHandler  CAL_CMEXPAPI( "TargetVisuRegisterEventHandler" ) 
#else /* DYNAMIC_LINK */
	#define USE_TargetVisuRegisterEventHandler  PFTARGETVISUREGISTEREVENTHANDLER pfTargetVisuRegisterEventHandler;
	#define EXT_TargetVisuRegisterEventHandler  extern PFTARGETVISUREGISTEREVENTHANDLER pfTargetVisuRegisterEventHandler;
	#define GET_TargetVisuRegisterEventHandler(fl)  s_pfCMGetAPI2( "TargetVisuRegisterEventHandler", (RTS_VOID_FCTPTR *)&pfTargetVisuRegisterEventHandler, (fl), 0, 0)
	#define CAL_TargetVisuRegisterEventHandler  pfTargetVisuRegisterEventHandler
	#define CHK_TargetVisuRegisterEventHandler  (pfTargetVisuRegisterEventHandler != NULL)
	#define EXP_TargetVisuRegisterEventHandler   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TargetVisuRegisterEventHandler", (RTS_UINTPTR)TargetVisuRegisterEventHandler, 0, 0) 
#endif


/**
 * <description> Unregister a callback that will be notified about certain events within this component </description>
 * <param name="pfCallback" type="IN">The function for which the callback should be removed. </param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TargetVisuUnregisterEventHandler(PFTARGETVISUCALLBACK pfCallback, RTS_UINTPTR ulParam);
typedef RTS_RESULT (CDECL * PFTARGETVISUUNREGISTEREVENTHANDLER) (PFTARGETVISUCALLBACK pfCallback, RTS_UINTPTR ulParam);
#if defined(CMPTARGETVISU_NOTIMPLEMENTED) || defined(TARGETVISUUNREGISTEREVENTHANDLER_NOTIMPLEMENTED)
	#define USE_TargetVisuUnregisterEventHandler
	#define EXT_TargetVisuUnregisterEventHandler
	#define GET_TargetVisuUnregisterEventHandler(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TargetVisuUnregisterEventHandler(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TargetVisuUnregisterEventHandler  FALSE
	#define EXP_TargetVisuUnregisterEventHandler  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TargetVisuUnregisterEventHandler
	#define EXT_TargetVisuUnregisterEventHandler
	#define GET_TargetVisuUnregisterEventHandler(fl)  CAL_CMGETAPI( "TargetVisuUnregisterEventHandler" ) 
	#define CAL_TargetVisuUnregisterEventHandler  TargetVisuUnregisterEventHandler
	#define CHK_TargetVisuUnregisterEventHandler  TRUE
	#define EXP_TargetVisuUnregisterEventHandler  CAL_CMEXPAPI( "TargetVisuUnregisterEventHandler" ) 
#elif defined(MIXED_LINK) && !defined(CMPTARGETVISU_EXTERNAL)
	#define USE_TargetVisuUnregisterEventHandler
	#define EXT_TargetVisuUnregisterEventHandler
	#define GET_TargetVisuUnregisterEventHandler(fl)  CAL_CMGETAPI( "TargetVisuUnregisterEventHandler" ) 
	#define CAL_TargetVisuUnregisterEventHandler  TargetVisuUnregisterEventHandler
	#define CHK_TargetVisuUnregisterEventHandler  TRUE
	#define EXP_TargetVisuUnregisterEventHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TargetVisuUnregisterEventHandler", (RTS_UINTPTR)TargetVisuUnregisterEventHandler, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTargetVisuTargetVisuUnregisterEventHandler
	#define EXT_CmpTargetVisuTargetVisuUnregisterEventHandler
	#define GET_CmpTargetVisuTargetVisuUnregisterEventHandler  ERR_OK
	#define CAL_CmpTargetVisuTargetVisuUnregisterEventHandler  TargetVisuUnregisterEventHandler
	#define CHK_CmpTargetVisuTargetVisuUnregisterEventHandler  TRUE
	#define EXP_CmpTargetVisuTargetVisuUnregisterEventHandler  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TargetVisuUnregisterEventHandler
	#define EXT_TargetVisuUnregisterEventHandler
	#define GET_TargetVisuUnregisterEventHandler(fl)  CAL_CMGETAPI( "TargetVisuUnregisterEventHandler" ) 
	#define CAL_TargetVisuUnregisterEventHandler  TargetVisuUnregisterEventHandler
	#define CHK_TargetVisuUnregisterEventHandler  TRUE
	#define EXP_TargetVisuUnregisterEventHandler  CAL_CMEXPAPI( "TargetVisuUnregisterEventHandler" ) 
#else /* DYNAMIC_LINK */
	#define USE_TargetVisuUnregisterEventHandler  PFTARGETVISUUNREGISTEREVENTHANDLER pfTargetVisuUnregisterEventHandler;
	#define EXT_TargetVisuUnregisterEventHandler  extern PFTARGETVISUUNREGISTEREVENTHANDLER pfTargetVisuUnregisterEventHandler;
	#define GET_TargetVisuUnregisterEventHandler(fl)  s_pfCMGetAPI2( "TargetVisuUnregisterEventHandler", (RTS_VOID_FCTPTR *)&pfTargetVisuUnregisterEventHandler, (fl), 0, 0)
	#define CAL_TargetVisuUnregisterEventHandler  pfTargetVisuUnregisterEventHandler
	#define CHK_TargetVisuUnregisterEventHandler  (pfTargetVisuUnregisterEventHandler != NULL)
	#define EXP_TargetVisuUnregisterEventHandler   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TargetVisuUnregisterEventHandler", (RTS_UINTPTR)TargetVisuUnregisterEventHandler, 0, 0) 
#endif


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT targetvisucyclic(targetvisucyclic_struct *p);
typedef void (CDECL CDECL_EXT* PFTARGETVISUCYCLIC_IEC) (targetvisucyclic_struct *p);
#if defined(CMPTARGETVISU_NOTIMPLEMENTED) || defined(TARGETVISUCYCLIC_NOTIMPLEMENTED)
	#define USE_targetvisucyclic
	#define EXT_targetvisucyclic
	#define GET_targetvisucyclic(fl)  ERR_NOTIMPLEMENTED
	#define CAL_targetvisucyclic(p0) 
	#define CHK_targetvisucyclic  FALSE
	#define EXP_targetvisucyclic  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_targetvisucyclic
	#define EXT_targetvisucyclic
	#define GET_targetvisucyclic(fl)  CAL_CMGETAPI( "targetvisucyclic" ) 
	#define CAL_targetvisucyclic  targetvisucyclic
	#define CHK_targetvisucyclic  TRUE
	#define EXP_targetvisucyclic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisucyclic", (RTS_UINTPTR)targetvisucyclic, 1, RTSITF_GET_SIGNATURE(0xD44FE2A3, 0xFE915838), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPTARGETVISU_EXTERNAL)
	#define USE_targetvisucyclic
	#define EXT_targetvisucyclic
	#define GET_targetvisucyclic(fl)  CAL_CMGETAPI( "targetvisucyclic" ) 
	#define CAL_targetvisucyclic  targetvisucyclic
	#define CHK_targetvisucyclic  TRUE
	#define EXP_targetvisucyclic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisucyclic", (RTS_UINTPTR)targetvisucyclic, 1, RTSITF_GET_SIGNATURE(0xD44FE2A3, 0xFE915838), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTargetVisutargetvisucyclic
	#define EXT_CmpTargetVisutargetvisucyclic
	#define GET_CmpTargetVisutargetvisucyclic  ERR_OK
	#define CAL_CmpTargetVisutargetvisucyclic  targetvisucyclic
	#define CHK_CmpTargetVisutargetvisucyclic  TRUE
	#define EXP_CmpTargetVisutargetvisucyclic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisucyclic", (RTS_UINTPTR)targetvisucyclic, 1, RTSITF_GET_SIGNATURE(0xD44FE2A3, 0xFE915838), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_targetvisucyclic
	#define EXT_targetvisucyclic
	#define GET_targetvisucyclic(fl)  CAL_CMGETAPI( "targetvisucyclic" ) 
	#define CAL_targetvisucyclic  targetvisucyclic
	#define CHK_targetvisucyclic  TRUE
	#define EXP_targetvisucyclic  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisucyclic", (RTS_UINTPTR)targetvisucyclic, 1, RTSITF_GET_SIGNATURE(0xD44FE2A3, 0xFE915838), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_targetvisucyclic  PFTARGETVISUCYCLIC_IEC pftargetvisucyclic;
	#define EXT_targetvisucyclic  extern PFTARGETVISUCYCLIC_IEC pftargetvisucyclic;
	#define GET_targetvisucyclic(fl)  s_pfCMGetAPI2( "targetvisucyclic", (RTS_VOID_FCTPTR *)&pftargetvisucyclic, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xD44FE2A3, 0xFE915838), 0x03050500)
	#define CAL_targetvisucyclic  pftargetvisucyclic
	#define CHK_targetvisucyclic  (pftargetvisucyclic != NULL)
	#define EXP_targetvisucyclic   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisucyclic", (RTS_UINTPTR)targetvisucyclic, 1, RTSITF_GET_SIGNATURE(0xD44FE2A3, 0xFE915838), 0x03050500) 
#endif


/**
 * This function can be used to find out the handle of the targetvisualization when having the according identification
 */
typedef struct tagtargetvisufindbyid_struct
{
	RTS_IEC_DWORD dwExternId;			/* VAR_INPUT */	/* The identification used by the visualization to manage their different clients. */
	RTS_IEC_RESULT TargetVisuFindById;	/* VAR_OUTPUT */	
	RTS_IEC_HANDLE hTargetVisu;			/* VAR_OUTPUT */	
} targetvisufindbyid_struct;

void CDECL CDECL_EXT targetvisufindbyid(targetvisufindbyid_struct *p);
typedef void (CDECL CDECL_EXT* PFTARGETVISUFINDBYID_IEC) (targetvisufindbyid_struct *p);
#if defined(CMPTARGETVISU_NOTIMPLEMENTED) || defined(TARGETVISUFINDBYID_NOTIMPLEMENTED)
	#define USE_targetvisufindbyid
	#define EXT_targetvisufindbyid
	#define GET_targetvisufindbyid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_targetvisufindbyid(p0) 
	#define CHK_targetvisufindbyid  FALSE
	#define EXP_targetvisufindbyid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_targetvisufindbyid
	#define EXT_targetvisufindbyid
	#define GET_targetvisufindbyid(fl)  CAL_CMGETAPI( "targetvisufindbyid" ) 
	#define CAL_targetvisufindbyid  targetvisufindbyid
	#define CHK_targetvisufindbyid  TRUE
	#define EXP_targetvisufindbyid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisufindbyid", (RTS_UINTPTR)targetvisufindbyid, 1, 0xEC5DE09D, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPTARGETVISU_EXTERNAL)
	#define USE_targetvisufindbyid
	#define EXT_targetvisufindbyid
	#define GET_targetvisufindbyid(fl)  CAL_CMGETAPI( "targetvisufindbyid" ) 
	#define CAL_targetvisufindbyid  targetvisufindbyid
	#define CHK_targetvisufindbyid  TRUE
	#define EXP_targetvisufindbyid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisufindbyid", (RTS_UINTPTR)targetvisufindbyid, 1, 0xEC5DE09D, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTargetVisutargetvisufindbyid
	#define EXT_CmpTargetVisutargetvisufindbyid
	#define GET_CmpTargetVisutargetvisufindbyid  ERR_OK
	#define CAL_CmpTargetVisutargetvisufindbyid  targetvisufindbyid
	#define CHK_CmpTargetVisutargetvisufindbyid  TRUE
	#define EXP_CmpTargetVisutargetvisufindbyid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisufindbyid", (RTS_UINTPTR)targetvisufindbyid, 1, 0xEC5DE09D, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_targetvisufindbyid
	#define EXT_targetvisufindbyid
	#define GET_targetvisufindbyid(fl)  CAL_CMGETAPI( "targetvisufindbyid" ) 
	#define CAL_targetvisufindbyid  targetvisufindbyid
	#define CHK_targetvisufindbyid  TRUE
	#define EXP_targetvisufindbyid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisufindbyid", (RTS_UINTPTR)targetvisufindbyid, 1, 0xEC5DE09D, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_targetvisufindbyid  PFTARGETVISUFINDBYID_IEC pftargetvisufindbyid;
	#define EXT_targetvisufindbyid  extern PFTARGETVISUFINDBYID_IEC pftargetvisufindbyid;
	#define GET_targetvisufindbyid(fl)  s_pfCMGetAPI2( "targetvisufindbyid", (RTS_VOID_FCTPTR *)&pftargetvisufindbyid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xEC5DE09D, 0x03050500)
	#define CAL_targetvisufindbyid  pftargetvisufindbyid
	#define CHK_targetvisufindbyid  (pftargetvisufindbyid != NULL)
	#define EXP_targetvisufindbyid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisufindbyid", (RTS_UINTPTR)targetvisufindbyid, 1, 0xEC5DE09D, 0x03050500) 
#endif


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

void CDECL CDECL_EXT targetvisunotify(targetvisunotify_struct *p);
typedef void (CDECL CDECL_EXT* PFTARGETVISUNOTIFY_IEC) (targetvisunotify_struct *p);
#if defined(CMPTARGETVISU_NOTIMPLEMENTED) || defined(TARGETVISUNOTIFY_NOTIMPLEMENTED)
	#define USE_targetvisunotify
	#define EXT_targetvisunotify
	#define GET_targetvisunotify(fl)  ERR_NOTIMPLEMENTED
	#define CAL_targetvisunotify(p0) 
	#define CHK_targetvisunotify  FALSE
	#define EXP_targetvisunotify  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_targetvisunotify
	#define EXT_targetvisunotify
	#define GET_targetvisunotify(fl)  CAL_CMGETAPI( "targetvisunotify" ) 
	#define CAL_targetvisunotify  targetvisunotify
	#define CHK_targetvisunotify  TRUE
	#define EXP_targetvisunotify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisunotify", (RTS_UINTPTR)targetvisunotify, 1, 0x78EF227D, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPTARGETVISU_EXTERNAL)
	#define USE_targetvisunotify
	#define EXT_targetvisunotify
	#define GET_targetvisunotify(fl)  CAL_CMGETAPI( "targetvisunotify" ) 
	#define CAL_targetvisunotify  targetvisunotify
	#define CHK_targetvisunotify  TRUE
	#define EXP_targetvisunotify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisunotify", (RTS_UINTPTR)targetvisunotify, 1, 0x78EF227D, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTargetVisutargetvisunotify
	#define EXT_CmpTargetVisutargetvisunotify
	#define GET_CmpTargetVisutargetvisunotify  ERR_OK
	#define CAL_CmpTargetVisutargetvisunotify  targetvisunotify
	#define CHK_CmpTargetVisutargetvisunotify  TRUE
	#define EXP_CmpTargetVisutargetvisunotify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisunotify", (RTS_UINTPTR)targetvisunotify, 1, 0x78EF227D, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_targetvisunotify
	#define EXT_targetvisunotify
	#define GET_targetvisunotify(fl)  CAL_CMGETAPI( "targetvisunotify" ) 
	#define CAL_targetvisunotify  targetvisunotify
	#define CHK_targetvisunotify  TRUE
	#define EXP_targetvisunotify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisunotify", (RTS_UINTPTR)targetvisunotify, 1, 0x78EF227D, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_targetvisunotify  PFTARGETVISUNOTIFY_IEC pftargetvisunotify;
	#define EXT_targetvisunotify  extern PFTARGETVISUNOTIFY_IEC pftargetvisunotify;
	#define GET_targetvisunotify(fl)  s_pfCMGetAPI2( "targetvisunotify", (RTS_VOID_FCTPTR *)&pftargetvisunotify, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x78EF227D, 0x03050500)
	#define CAL_targetvisunotify  pftargetvisunotify
	#define CHK_targetvisunotify  (pftargetvisunotify != NULL)
	#define EXP_targetvisunotify   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"targetvisunotify", (RTS_UINTPTR)targetvisunotify, 1, 0x78EF227D, 0x03050500) 
#endif


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
RTS_RESULT CDECL TargetVisuRaiseCustomEventAll(RTS_UI16 uiEventType, RTS_UI32 dwParam1, RTS_UI32 dwParam2, void* pAdditionalData, RTS_SIZE additionalDataSize);
typedef RTS_RESULT (CDECL * PFTARGETVISURAISECUSTOMEVENTALL) (RTS_UI16 uiEventType, RTS_UI32 dwParam1, RTS_UI32 dwParam2, void* pAdditionalData, RTS_SIZE additionalDataSize);
#if defined(CMPTARGETVISU_NOTIMPLEMENTED) || defined(TARGETVISURAISECUSTOMEVENTALL_NOTIMPLEMENTED)
	#define USE_TargetVisuRaiseCustomEventAll
	#define EXT_TargetVisuRaiseCustomEventAll
	#define GET_TargetVisuRaiseCustomEventAll(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TargetVisuRaiseCustomEventAll(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TargetVisuRaiseCustomEventAll  FALSE
	#define EXP_TargetVisuRaiseCustomEventAll  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TargetVisuRaiseCustomEventAll
	#define EXT_TargetVisuRaiseCustomEventAll
	#define GET_TargetVisuRaiseCustomEventAll(fl)  CAL_CMGETAPI( "TargetVisuRaiseCustomEventAll" ) 
	#define CAL_TargetVisuRaiseCustomEventAll  TargetVisuRaiseCustomEventAll
	#define CHK_TargetVisuRaiseCustomEventAll  TRUE
	#define EXP_TargetVisuRaiseCustomEventAll  CAL_CMEXPAPI( "TargetVisuRaiseCustomEventAll" ) 
#elif defined(MIXED_LINK) && !defined(CMPTARGETVISU_EXTERNAL)
	#define USE_TargetVisuRaiseCustomEventAll
	#define EXT_TargetVisuRaiseCustomEventAll
	#define GET_TargetVisuRaiseCustomEventAll(fl)  CAL_CMGETAPI( "TargetVisuRaiseCustomEventAll" ) 
	#define CAL_TargetVisuRaiseCustomEventAll  TargetVisuRaiseCustomEventAll
	#define CHK_TargetVisuRaiseCustomEventAll  TRUE
	#define EXP_TargetVisuRaiseCustomEventAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TargetVisuRaiseCustomEventAll", (RTS_UINTPTR)TargetVisuRaiseCustomEventAll, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTargetVisuTargetVisuRaiseCustomEventAll
	#define EXT_CmpTargetVisuTargetVisuRaiseCustomEventAll
	#define GET_CmpTargetVisuTargetVisuRaiseCustomEventAll  ERR_OK
	#define CAL_CmpTargetVisuTargetVisuRaiseCustomEventAll pICmpTargetVisu->ITargetVisuRaiseCustomEventAll
	#define CHK_CmpTargetVisuTargetVisuRaiseCustomEventAll (pICmpTargetVisu != NULL)
	#define EXP_CmpTargetVisuTargetVisuRaiseCustomEventAll  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TargetVisuRaiseCustomEventAll
	#define EXT_TargetVisuRaiseCustomEventAll
	#define GET_TargetVisuRaiseCustomEventAll(fl)  CAL_CMGETAPI( "TargetVisuRaiseCustomEventAll" ) 
	#define CAL_TargetVisuRaiseCustomEventAll pICmpTargetVisu->ITargetVisuRaiseCustomEventAll
	#define CHK_TargetVisuRaiseCustomEventAll (pICmpTargetVisu != NULL)
	#define EXP_TargetVisuRaiseCustomEventAll  CAL_CMEXPAPI( "TargetVisuRaiseCustomEventAll" ) 
#else /* DYNAMIC_LINK */
	#define USE_TargetVisuRaiseCustomEventAll  PFTARGETVISURAISECUSTOMEVENTALL pfTargetVisuRaiseCustomEventAll;
	#define EXT_TargetVisuRaiseCustomEventAll  extern PFTARGETVISURAISECUSTOMEVENTALL pfTargetVisuRaiseCustomEventAll;
	#define GET_TargetVisuRaiseCustomEventAll(fl)  s_pfCMGetAPI2( "TargetVisuRaiseCustomEventAll", (RTS_VOID_FCTPTR *)&pfTargetVisuRaiseCustomEventAll, (fl), 0, 0)
	#define CAL_TargetVisuRaiseCustomEventAll  pfTargetVisuRaiseCustomEventAll
	#define CHK_TargetVisuRaiseCustomEventAll  (pfTargetVisuRaiseCustomEventAll != NULL)
	#define EXP_TargetVisuRaiseCustomEventAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TargetVisuRaiseCustomEventAll", (RTS_UINTPTR)TargetVisuRaiseCustomEventAll, 0, 0) 
#endif




/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
	PFCREATETARGETVISUINSTANCE2 ICreateTargetvisuInstance2;
 	PFTARGETVISURAISECUSTOMEVENTALL ITargetVisuRaiseCustomEventAll;
 } ICmpTargetVisu_C;

#ifdef CPLUSPLUS
class ICmpTargetVisu : public IBase
{
	public:
		virtual RTS_RESULT CDECL ICreateTargetvisuInstance2(CmpTargetvisuCreateInformation* pCreateInformation, RTS_HANDLE* pHandleRet) =0;
		virtual RTS_RESULT CDECL ITargetVisuRaiseCustomEventAll(RTS_UI16 uiEventType, RTS_UI32 dwParam1, RTS_UI32 dwParam2, void* pAdditionalData, RTS_SIZE additionalDataSize) =0;
};
	#ifndef ITF_CmpTargetVisu
		#define ITF_CmpTargetVisu static ICmpTargetVisu *pICmpTargetVisu = NULL;
	#endif
	#define EXTITF_CmpTargetVisu
#else	/*CPLUSPLUS*/
	typedef ICmpTargetVisu_C		ICmpTargetVisu;
	#ifndef ITF_CmpTargetVisu
		#define ITF_CmpTargetVisu
	#endif
	#define EXTITF_CmpTargetVisu
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPTARGETVISUITF_H_*/
