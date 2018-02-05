/**
 * <interfacename>SysGraphic</interfacename>
 * <description> 
 *	<p>The SysGraphic interface is projected to get access to the graphic library routines
 *	of a system. This is the system interface typically for the CoDeSys target visualization.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysGraphic')

#ifndef CDECL
	#define CDECL
#endif

#include "SysGraphicBase.h"

/**
 * <category>TF</category>
 * <description>Text Format</description>
 */
#define	TF_LEFT							0x00000000
#define TF_HCENTER						0x00000001
#define TF_RIGHT						0x00000002
#define TF_TOP							0x00000000
#define TF_VCENTER						0x00000004
#define TF_BOTTOM						0x00000008
#define TF_AUTO_SHRINK_TEXT				0x00000010
#define TF_CALCULATE_RESULTING_POSITION	0x00000020
#define TF_DRAW_RELATIVE				0x00000040
#define TF_ROTATE						0x00000080		/* The orientation of the textrectangle should be used for rotating the text */
#define TF_LINEBREAK					0x00000100
#define	TF_ELLIPSIS						0x00000200
#define	TF_SAVE_PREVIOUS_POSITION		0x00000400		/* See comment of VISU_DTF_SAVE_PREVIOUS_POSITION in library VisuElemBase. */
#define	TF_USE_PREVIOUS_POSITION		0x00000800		/* See comment of VISU_DTF_USE_PREVIOUS_POSITION  in library VisuElemBase. */
#define TF_IGNORE_VERTICAL_ALIGNMENT	0x00001000		
#define TF_BGELEM						0x80000000
#define TF_WSTRING						0x40000000
#define TF_MEASURE_ALL					0x00002000		/* Can be used for SysGraphicGetTextExtent: Whole text will be measured and not stopped at first linebreak. */
#define TF_ANTIALIASING_INACTIVE		0x00004000		/* A special flag, used to deactivate the antialiasing feature temporarily */

/**
 * <category>Font style</category>
 * <description>Styleflags for fonts</description>
 */
#define FF_ITALIC		0x0001
#define FF_BOLD			0x0002
#define FF_UNDERLINE	0x0004
#define FF_STRIKEOUT	0x0008
/* Flag deactivates the language specific font for this text */
#define FF_NO_LANGUAGE_DEPENDENCY 0x0100

/**
 * <category>Bitmap style</category>
 * <description>Styleflags that effect the drawing of images</description>
 */
#define BMPF_ISOTROPIC		0x00000001
#define BMPF_ANISOTROPIC	0x00000002
#define BMPF_FIXED			0x00000004
#define BMPF_TRANSPARENT	0x00000008
/* flag-values like in IEC */
#define BMPF_LEFT			0x00000040
#define BMPF_HCENTER		0x00000080
#define	BMPF_RIGHT			0x00000100
#define BMPF_TOP			0x00000200
#define	BMPF_VCENTER		0x00000400
#define BMPF_BOTTOM			0x00000800
#define BMPF_INVALIDATE_CACHE	0x00001000

/**
 * <category>Gradient Type</category>
 */
#define GRADIENT_LINEAR		0
#define GRADIENT_RADIAL 	1
#define GRADIENT_AXIAL		2

/**
 * <category>Pen style</category>
 * <description>Styleflags that effect the drawing of lines</description>
 */
#define PF_SOLID			0 			/* pen is solid */
#define PF_DASH				1			/* pen is dashed */
#define PF_DOT				2			/* pen is dotted */
#define PF_DASHDOT			3			/* pen has alternating dashes and dots. */
#define PF_DASHDOTDOT		4			/* pen has alternating dashes and double dots. */
#define PF_NULL				5			/* pen is invisible */

/**
 * <category>Pen LineCapStyle</category>
 * <description>Styleflags that effect the linecap, means start and end of the line </description>
 */	
#define CAPSTYLE_FLAT		0x0000	/* default-value: flat cap, like no setting */
#define CAPSTYLE_SQUARE		0x0001  /* square cap, is added to the end of the line */
#define CAPSTYLE_ROUND		0x0002  /* round cap */

/**
 * <category>Pen LineJoinStyle</category>
 * <description>Styleflags that effect the linejoin, means the corners of e.g. a polygon </description>
 */	
#define LINEJOIN_MITER		0x0000	/* default-value: sharp line join */
#define LINEJOIN_BEVEL		0x0001  /* flatened line join */
#define LINEJOIN_ROUND		0x0002  /* round line join */
#define LINEJOIN_MITER_NEW	0x0003  /* new default-value */

/**
 * <category>Brush style</category>
 * <description>Styleflags that effect the drawing of filled shapes</description>
 */
#define BF_SOLID		0x0000			/* a solid brush */
#define BF_NULL			0x0001			/* a hollow brush */

/**
 * <category>Feature Flags</category>
 * <description>Feature flags that tell the kernel part of the targetvisualization what features are supported by the
	SysGraphic implementation</description>
 */
#define SYSGRAPHIC_FEATURES_ALL				0xffffffff
/**
 * <category>Feature Flags</category>
 * <description>If this flag is set, then the implementation is able to work with ansi strings. If this flag is
 *	not active, then the methods of SysGraphic should only be called with unicode strings.</description>
 */
#define SYSGRAPHIC_FEATURE_ANSISUPPORT		0x00000001
/**
 * <category>Feature Flags</category>
 * <description>If this flag is not set, then the invalidation rect of the element line is increased by one pixel.</description>
 */
#define SYSGRAPHIC_FEATURE_EXACTLINE		0x00000002
/**
 * <category>Feature Flags</category>
 * <description>If this flag is not set, then the graphics libaray does not support text rotation.</description>
 */
#define SYSGRAPHIC_FEATURE_TEXTROTATION		0x00000004

/**
 * <category>Antialiasing modes</category>
 * <description>This mode for the antialiasing feature means that antialiasing is completely disabled. This is the default for 
 *	newly created device contexts.</description>
 */
#define SYSGRAPHIC_ANTIALIASING_NONE		0x00000000

/**
 * <category>Antialiasing modes</category>
 * <description>This mode for the antialiasing feature means that antialiasing in a lower quality (better performance) is enabled</description>
 */
#define SYSGRAPHIC_ANTIALIASING_LOWQUALITY	0x00000001

/**
 * <category>Antialiasing modes</category>
 * <description>This mode for the antialiasing feature means that antialiasing in a high quality (worse performance) is enabled</description>
 */
#define SYSGRAPHIC_ANTIALIASING_HIGHQUALITY	0x00000002

/**
 * <description>Setting which decides if another font should be used.</description>
 *
 */
#define SYSGRAPHIC_KEY_REPLACEMENT_FONT_NAME "ReplacementFontName"


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	<p>Fonts to be loaded at runtime (not installed in the OS)
 *	Several font paths can be entered, they must be indexed, e.g.:</p>
 *	<p>Font.0=MS Hei</p>
 * (Currently only for Windows CE).
 * </description>
 */	
#define SYSGRAPHIC_KEY_FONT		"Graphics.Font"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	This setting can be used on windows runtimes when the imlementation using SysGraphic (GDI) is used. In this situation,
 *	this option can be set to 1 to save memory, when this is necessary. In such a save memory situation, transparent images
 *	will be drawn in a non optimized way!
 *	By default, the optimized drawing that consumes more memory is activated (ie. default value is 0).
 * (probably only relevant for Windows CE).
 * </description>
 */	
#define SYSGRAPHIC_KEY_TRANSPARENCY_SAVE_MEMORY		"TransparencySaveMemory" 
#ifndef SYSGRAPHIC_VALUE_TRANSPARENCY_SAVE_MEMORY_DEFAULT
	#define SYSGRAPHIC_VALUE_TRANSPARENCY_SAVE_MEMORY_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	By default, under Windows CE the target visu changes the system memory settings so that target visu 
 *  has enough working memory on smaller CE 4/5 devices. This is bad for other applications.
 *	This option can be set to 1 to leave memory settings as they are
 *	default value is 0: memory settings are changed (backward compatible)
 * </description>
 */	
#define SYSGRAPHIC_WINCE_DONT_CHANGE_MEMORY_SETTINGS		"WinCE.DontChangeMemorySettings" 
#ifndef SYSGRAPHIC_VALUE_WINCE_DONT_CHANGE_MEMORY_SETTINGS_DEFAULT
	#define SYSGRAPHIC_VALUE_WINCE_DONT_CHANGE_MEMORY_SETTINGS_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	for converting jpegs into bmps, a big conversion byte array is used
 *  This setting defines the size of this array 
 *	default value is 1024 * 768 * 3
 * </description>
 */	
#define SYSGRAPHIC_WIN32_MAX_JPEG_BYTEARRAY_SIZE					"Win32.MaxJpegByteArraySize" 
#ifndef SYSGRAPHIC_WIN32_MAX_JPEG_BYTEARRAY_SIZE_DEFAULT
	#define SYSGRAPHIC_WIN32_MAX_JPEG_BYTEARRAY_SIZE_DEFAULT		INT32_C(2359296)
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Typically PNG images including palette information are converted during loading into flat RGB pixels. This costs
 *  more memory but typically yields better performance when the image is drawn.
 *	If performance is not an issue but the addtional memory consumption of such PNG images (compared to BMP) is, then
 *	this setting can be set to 1.
 * </description>
 */	
#define SYSGRAPHIC_WIN32_PNG_LOADPALETTE_ASPALETTE					"Win32.LoadPNGImagesPalette" 
#ifndef SYSGRAPHIC_WIN32_PNG_LOADPALETTE_ASPALETTE_DEFAULT
	#define SYSGRAPHIC_WIN32_PNG_LOADPALETTE_ASPALETTE_DEFAULT				0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *  Only relevant for Windows CE: Defines the way how rectangles are drawn.
 *  Starting with 3.5 SP 1 the height and the width of rectangles are decremented by 1, due to a wrong bugfix (paint bug when drawing and invalidating 
 *  rectangles with bar meters, where the origin of the bug was a wrong invalidation and not wrong painting of the rectangles)
 *  Before 3.5 SP 1 the rectangles are drawn correctly.
 *  The default value is 1 to use the correct behaviour before 3.5 SP 1
 * </description>
 */	
#define SYSGRAPHIC_WINCE_OLD_DRAW_RECT_METHOD					"WinCE.UseOldDrawRectMethod" 
#ifndef SYSGRAPHIC_WINCE_OLD_DRAW_RECT_METHOD_DEFAULT
	#define SYSGRAPHIC_WINCE_OLD_DRAW_RECT_METHOD_DEFAULT				1
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *  Same as "WinCE.UseOldDrawRectMethod" but not for rectangles without frame.
 *  This might be necessary on CE5 panels as the rectangle is drawn different.
 *	default value is 0. For Windows CE 6 the default value needs to be 1, because
 *  without this active setting rectangles without frame are not drawn correctly
 * </description>
 */	
#define SYSGRAPHIC_WINCE_OLD_DRAW_RECT_METHODCE5				"WinCE.UseOldDrawRectMethodCE5" 
#ifndef SYSGRAPHIC_WINCE_OLD_DRAW_RECT_METHODCE5_DEFAULT
	#define SYSGRAPHIC_WINCE_OLD_DRAW_RECT_METHODCE5_DEFAULT				0
#endif
#ifndef SYSGRAPHIC_WINCE_OLD_DRAW_RECT_METHODCE5_DEFAULTCE6
	#define SYSGRAPHIC_WINCE_OLD_DRAW_RECT_METHODCE5_DEFAULTCE6				1
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *  Special setting for SysGraphicGDIPlus. If this setting is not 0, then a proxy
 *	process will be used for rendering SVG images instead of directly accessing SVGRenderer.dll.
 *	Usecases for this setting are either 64-Bit runtimes that cannot directly include SVGRenderer.dll
 *	or runtimes that are started/stopped multiple times within the same process (like VisuClientX).
 *	Default value is 0
 * </description>
 */	
#define SYSGRAPHIC_WINGDIPLUS_USESVGPROXY				"WinGDIPlus.UseSVGProxy" 
#ifndef SYSGRAPHIC_WINGDIPLUS_USESVGPROXY_DEFAULT
	#define SYSGRAPHIC_WINGDIPLUS_USESVGPROXY_DEFAULT	0
#endif

typedef struct
{
	int i;	/* TODO */
} SYS_TEXTMETRICS;


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysGraphicOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysGraphicOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Create compatible device context</description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="phDC" type="OUT">Pointer to handle to get the device context</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicCreateCompatibleDeviceContext',`(RTS_HANDLE hWindow, RTS_HANDLE* phDC)')

/**
 * <description>Create compatible device context with custom size</description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="iWidth" type="IN">Width of the device Context</param>
 * <param name="iHeight" type="IN">Height of the device Context</param>
 * <param name="phDC" type="OUT">Pointer to handle to get the device context</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicCreateCompatibleDeviceContextWithCustomSize',`(RTS_HANDLE hWindow, RTS_I16 iWidth, RTS_I16 iHeight, RTS_HANDLE* phDC)')

/**
 * <description>Delete compatible device context</description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="hDC" type="IN">Handle to the device context</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicDeleteDeviceContext',`(RTS_HANDLE hWindow, RTS_HANDLE hDC)')

/**
 * <description>Get a device context. Remember to release such a device context using <see>SysGraphicReleaseDeviceContext</see>
 *	and not with <see>SysGraphicDeleteDeviceContext</see>!</description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="phDC" type="OUT">Pointer to handle to get the device context</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicGetDeviceContext',`(RTS_HANDLE hWindow, RTS_HANDLE* phDC)')

/**
 * <description>Release a device context that has been retrieved using <see>SysGraphicGetDeviceContext</see></description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="hDC" type="IN">Handle to the device context</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicReleaseDeviceContext',`(RTS_HANDLE hWindow, RTS_HANDLE hDC)')

/**
 * <description><p>Get a device context for an existing device context object belonging to a window. 
 *	Remember to release such a device context using <see>SysGraphicReleaseDeviceContextForWindowDeviceContext</see>
 *	and not with <see>SysGraphicDeleteDeviceContext</see> or <see>SysGraphicReleaseDeviceContext</see>!</p>
 *  <p>This method should be used when the SysWindow component wants to use SysGraphic methods directly.
 *	The intent of this method is to allow the syswindow component to convert a system specific device context
 *	to a device context that the SysGraphic component can work with.</p>
 *	<p>This can be necessary in the following situation:
 *	<ul>
 *		<li>SysWindow uses a system specific device context it received from the operating system</li>
 *		<li>SysWindow wants to call methods from SysGraphic on this device context</li>
 *		<li>The actual type SysGraphic uses for a device context is different than the operating system's type</li>
 *	</ul></p>
 *	<p>The previous siutation will work correctly only when both SysGraphic and SysWindow use the same datatype 
 *	for device contexts.</p></description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="hDCWindow" type="IN">Handle to the device context of the actual window</param>
 * <param name="phDC" type="OUT">Pointer to handle to get the device context</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicGetDeviceContextForWindowDeviceContext',`(RTS_HANDLE hWindow, RTS_HANDLE hDCWindow, RTS_HANDLE* phDC)')

/**
 * <description>Release a device context that has been retrieved using <see>SysGraphicGetDeviceContextForWindowDeviceContext</see></description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="hDC" type="IN">Handle to the device context</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicReleaseDeviceContextForWindowDeviceContext',`(RTS_HANDLE hWindow, RTS_HANDLE hDC)')

/**
 * <description>Set the background color of the device context</description>
 * <param name="hWindow" type="IN">Handle to the device context</param>
 * <param name="ulColor" type="IN">Color. Defined in IEC-Code for Visualization</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicSetBackgroundColor',`(RTS_HANDLE hDC, RTS_UI32 ulColor)')

/**
 * <description>Clear the specified rectangle</description>
 * <param name="hWindow" type="IN">Handle to the device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicClearRectangle',`(RTS_HANDLE hDC, RTS_Rectangle rect)')

/**
 * <description>Performs a bit-block transfer of the color data corresponding to a rectangle of pixels 
 *	from the specified source device context into a destination device context</description>
 * <param name="hDCDestination" type="IN">Handle to destination device context</param>
 * <param name="hDCSource" type="IN">Handle to source device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicBitBlt',`(RTS_HANDLE hDCDestination, RTS_HANDLE hDCSource, RTS_Rectangle rect)')

/**
 * <description>Copies a bitmap from a source rectangle into a destination rectangle, stretching or 
 *	compressing the bitmap to fit the dimensions of the destination rectangle, if necessary. The system
 *	stretches or compresses the bitmap according to the stretching mode currently set in the destination
 *	device context.</description>
 * <param name="hDCDestination" type="IN">Handle to destination device context</param>
 * <param name="rectDestination" type="IN">Destination rectangle</param>
 * <param name="hDCSource" type="IN">Handle to source device context</param>
 * <param name="rectSource" type="IN">Source rectangle</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicStretchBlt',`(RTS_HANDLE hDCDestination, RTS_Rectangle rectDestination, RTS_HANDLE hDCSource, RTS_Rectangle rectSource)')

/**
 * <description>Function to draw a rectangle based on top left and bottom right</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <param name="nType" type="IN">Rectangle type. See corresponding category</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicDrawRect',`(RTS_HANDLE hDC, RTS_Rectangle rect, RectangleType nType)')

/**
 * <description>Function to draw a rectangle based on top left and bottom right with real value coordinates</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <param name="nType" type="IN">Rectangle type. See corresponding category</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicDrawRectF',`(RTS_HANDLE hDC, RTS_RectangleF rect, RectangleType nType)')

/**
 * <description>Function to draw a polygon based on an array of points</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="nPoints" type="IN">Number of points in the array</param>
 * <param name="pPoints" type="IN">Pointer to the array of points. Length must be less or equal nPoints!</param>
 * <param name="nType" type="IN">Polygon type. See corresponding category</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicDrawPolygon',`(RTS_HANDLE hDC, RTS_I16 nPoints, RTS_Point* pPoints, PolygonType nType)')

/**
 * <description>Function to draw a polygon based on an array of points</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="nPoints" type="IN">Number of points in the array</param>
 * <param name="pPoints" type="IN">Pointer to the array of points. Length must be less or equal nPoints!</param>
 * <param name="nType" type="IN">Polygon type. See corresponding category</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicDrawPolygonF',`(RTS_HANDLE hDC, RTS_I16 nPoints, RTS_PointF* pPoints, PolygonType nType)')

/**
 * <description>Function to draw a pie based on top left and bottom right</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <param name="iStartAngle" type="IN">The start angle</param>
 * <param name="iSweepAngle" type="IN">The sweep angle</param>
 * <param name="nType" type="IN">Pie type. See corresponding category</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicDrawPie',`(RTS_HANDLE hDC, RTS_Rectangle rect, RTS_IEC_INT iStartAngle, RTS_IEC_INT iSweepAngle, PieType nType)')

/**
 * <description>Applies a clockwise rotation to this system drawing matrix around the point specified in the point parameter</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="iAngle" type="IN">The angle to rotate in radians</param>
 * <param name="point" type="IN">The point represents the center of the rotation</param>
 * <param name="bReset" type="IN">Reset the transformation</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicRotateAt',`(RTS_HANDLE hDC, RTS_REAL32 fAngle, RTS_Point point, RTS_BOOL bReset)')

/**
 * <description>Function to draw a text, based on top left and bottom right. Only the first line, if more
 *	than one is given.</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <param name="pszText" type="IN">Will be either:
 *	<ul>
 *		<li>char* if TF_WSTRING is not set in ulDrawFlags</li>
 *		<li>short* if (TF_WSTRING is set in ulDrawFlags)</li>
 *	</ul>
 * </param>
 * <param name="ulDrawFlags" type="IN">Draw flags. Defined in IEC-Code for Visualization</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicDrawText',`(RTS_HANDLE hDC, RTS_Rectangle rect, void* pszText, RTS_UI32 ulDrawFlags)')

/**
 * <description>Get the system metrics of a device context</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="ptm" type="OUT">Pointer to the system metrics</param>
 * <remarks>This function is not used yet and might not be implemented.</remarks>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicGetTextMetrics',`(RTS_HANDLE hDC, SYS_TEXTMETRICS* ptm)')

/**
 * <description>
 *	Function to calculate the size of a given text with the currently selected font. 
 *  Use case (1): The function will treat the string as a single line string, 
 *  ie. it will cut the string after a possible linefeed and calculate the size of the first line only!
 *  Use case (2): The string will be formated and measured as defined by it's ulDrawFlags.
 *  Here, also text with flag TF_LINEBREAK will be measured, as it will be drawn.
 *  For using this case, the flag TF_MEASURE_ALL has to be used additional.
 *  And the paint rectangle size has to be forwarded by using pSize.
 * </description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="pszText" type="IN">Will be either:
 *	<ul>
 *		<li>char* if TF_WSTRING is not set in ulDrawFlags</li>
 *		<li>short* if (TF_WSTRING is set in ulDrawFlags)</li>
 *	</ul>
 * </param>
 * <param name="ulDrawFlags" type="IN">Draw flags. Defined in IEC-Code for Visualization</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicGetTextExtent',`(RTS_HANDLE hDC, void* pszText, RTS_UI32 ulDrawFlags, RTS_Size* pSize)')

/**
 * <description>
 *  Function to get the height of the currently selected font.
 * </description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="piHeight" type="OUT">Height of the text</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT', `CDECL', `SysGraphicGetFontHeight', `(RTS_HANDLE hDC, RTS_I16* piHeight)')

/**
 * <description>
 *  Function to get the handle of the currently selected font.
 * </description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="phFont" type="OUT"> Pointer to get the font handle</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT', `CDECL', `SysGraphicGetFontHandle', `(RTS_HANDLE hDC, RTS_HANDLE* phFont)')

/**
 * <description>Function to set the fill style of the following objects (i.e. the Brush in Win32)</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="ulFillFlags" type="IN">Fill flags. Defined in IEC-Code for Visualization</param>
 * <param name="ulFillColor" type="IN">Fill color. Defined in IEC-Code for Visualization</param>
 * <param name="phBrush" type="OUT">Pointer to get the brush handle</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicCreateBrush',`(RTS_HANDLE hDC, RTS_UI32 ulFillFlags, RTS_UI32 ulFillColor, RTS_HANDLE* phBrush)')

/**
 * <description>Function to set the font for the following drawn texts</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hBrush" type="IN">Handle to the brush</param>
 * <param name="phOldBrush" type="OUT">Pointer to get the old brush handle. This pointer can be <c>null</c> if the
 *	old brush should not be returned. In this situation, you should take care that you still know a reference to this
 *	old brush to be able to release it after it is used!</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicSetBrush',`(RTS_HANDLE hDC, RTS_HANDLE hBrush, RTS_HANDLE* phOldBrush)')

/**
 * <description>Function to free an earlier created font object</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hBrush" type="IN">Handle to the brush</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicFreeBrush',`(RTS_HANDLE hDC, RTS_HANDLE hBrush)')

/**
* <description>Data for gradient brush</description>
*/
typedef struct _GradientData
{
	RTS_UI32 dwFillFlags;
	RTS_UI32 dwColor1;
	RTS_UI32 dwColor2;
	RTS_UI32 dwAngle;
	RTS_UI32 dwCenterX;
	RTS_UI32 dwCenterY;
	RTS_UI32 dwGradientType;
	RTS_UI32 dwUseTwoColors;
	RTS_UI32 dwBrightness;
	RTS_UI32 dwColorBrightness;
} GradientData;

/**
 * <description>Function to store the gradient fill data of the following objects (i.e. the Brush in Win32). Note: Optional</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="GradientData" type="IN">GradientData</param>
 * <param name="rectangle" type="IN">rectangle</param>
 * <param name="phBrush" type="OUT">Pointer to get the brush handle</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysGraphicCreateGradientBrush',`(RTS_HANDLE hDC, GradientData* gradient, RTS_Rectangle rectangle, RTS_HANDLE* phBrush)')

/**
 * <description> 
 *	Specifies a pattern of horizontal lines for <see>SysGraphicCreatePatternBrush</see>.
 * </description> 
 */
#define PAT_HORIZONTAL		1

/**
 * <description> 
 *	Specifies a pattern of vertical lines for <see>SysGraphicCreatePatternBrush</see>.
 * </description> 
 */
#define PAT_VERTICAL		2

/**
 * <description> 
 *	Specifies a pattern of crossing (at 90-degree angles) horizontal and vertical lines for <see>SysGraphicCreatePatternBrush</see>.
 * </description> 
 */
#define PAT_CROSS			3

/**
 * <description> 
 *	Specifies a light hatch (about 10%) for <see>SysGraphicCreatePatternBrush</see>.
 * </description> 
 */
#define PAT_DENSE_LIGHT		4

/**
 * <description> 
 *	Specifies a normal hatch (about 40-50%) for <see>SysGraphicCreatePatternBrush</see>.
 * </description> 
 */
#define PAT_DENSE_NORMAL	5

/**
 * <description> 
 *	Specifies a dense hatch (about 80%) for <see>SysGraphicCreatePatternBrush</see>.
 * </description> 
 */
#define PAT_DENSE_VERY		6

/**
 * <description>Creates a brush representing a spedific repeating pattern that can be used to fill elements.</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="patternType" type="IN">The type of pattern used by this brush</param>
 * <param name="rectangle" type="IN">The foreground color of the pattern</param>
 * <param name="phBrush" type="OUT">Pointer to get the brush handle</param>
 * <remark>Please remark: The background color of such a brush is expected to be fully transparent. That means only
 *	the foreground color should be used for drawing the pattern.</remark>
 * <result>An error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysGraphicCreatePatternBrush',`(RTS_HANDLE hDC, RTS_UI16 patternType, RTS_UI32 color, RTS_HANDLE* phBrush)')

/**
 * <description>Function to set the line style of the following objects (i.e. the Pen in Win32)</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="nLineWidth" type="IN">Width of the line as in Win32</param>
 * <param name="ulLineFlags" type="IN">Line flags.  Defined in IEC-Code for Visualization</param>
 * <param name="ulLineColor" type="IN">Line color.  Defined in IEC-Code for Visualization</param>
 * <param name="nLineCapFlag" type="IN">Line cap.  Defined in IEC-Code for Visualization</param>
 * <param name="nLineJoinFlag" type="IN">Line join.  Defined in IEC-Code for Visualization</param>
 * <param name="rMiterLimit" type="IN">Miter limit.  Defined in IEC-Code for Visualization</param>
 * <param name="phPen" type="OUT">Pointer to get the pen handle</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicCreatePenDetailed',`(RTS_HANDLE hDC, RTS_I16 nLineWidth, RTS_UI32 ulLineFlags, 
										RTS_UI32 ulLineColor, RTS_I16 nLineCapFlag, RTS_I16 nLineJoinFlag, 
										RTS_REAL32 rMiterLimit, RTS_HANDLE* phPen)')

/**
 * <description>Function to set the line style of the following objects (i.e. the Pen in Win32)</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="nLineWidth" type="IN">Width of the line as in Win32</param>
 * <param name="ulLineFlags" type="IN">Line flags.  Defined in IEC-Code for Visualization</param>
 * <param name="ulLineColor" type="IN">Line color.  Defined in IEC-Code for Visualization</param>
 * <param name="phPen" type="OUT">Pointer to get the pen handle</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicCreatePen',`(RTS_HANDLE hDC, RTS_I16 nLineWidth, RTS_UI32 ulLineFlags, 
										RTS_UI32 ulLineColor, RTS_HANDLE* phPen)')

/**
 * <description>Function to set the font for the following drawn texts</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hPen" type="IN">Handle to the new pen</param>
 * <param name="phOldPen" type="OUT">Pointer to get the previous set pen. This pointer can be <c>null</c> if the
 *	old pen should not be returned. In this situation, you should take care that you still know a reference to this
 *	old pen to be able to release it after it is used!</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicSetPen',`(RTS_HANDLE hDC, RTS_HANDLE hPen, RTS_HANDLE* phOldPen)')

/**
 * <description>Function to free a earlier created font object</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hPen" type="IN">Handle to the new pen</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicFreePen',`(RTS_HANDLE hDC, RTS_HANDLE hPen)')

/**
 * <description>Function to create a font object(i.e. the Font in Win32)</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="pszFontName" type="IN">Name of the font that should be set</param>
 * <param name="nFontSize" type="IN">Size of the font as in Win32</param>
 * <param name="phFont" type="OUT">Pointer to get the font handle</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicCreateFont',`(RTS_HANDLE hDC, char* pszFontName, RTS_I16 nFontSize, RTS_UI32 ulFontFlags, RTS_HANDLE* phFont)')

/**
 * <description>Function to free an earlier created font object</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hFont" type="IN">Handle to the font object</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicFreeFont',`(RTS_HANDLE hDC, RTS_HANDLE hFont)')

/**
 * <description>Function to set the font for the following drawn texts</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hFont" type="IN">Handle to the font object</param>
 * <param name="ulFontColor" type="IN">Font color. Defined in IEC-Code for Visualization</param>
 * <param name="phOldFont" type="OUT">Pointer to get the previous set font. This pointer can be <c>null</c> if the
 *	old font should not be returned. In this situation, you should take care that you still know a reference to this
 *	old font to be able to release it after it is used!</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicSetFont',`(RTS_HANDLE hDC, RTS_HANDLE hFont, RTS_UI32 ulFontColor, RTS_HANDLE* phOldFont)')

/**
 * <description>Function to set the font for the following drawn texts</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hFont" type="IN">Handle to the font object</param>
 * <param name="ulFontColor" type="IN">Font color. Defined in IEC-Code for Visualization</param>
 * <param name="phOldFont" type="OUT">Pointer to get the previous set font. This pointer can be <c>null</c> if the
 *	old font should not be returned. In this situation, you should take care that you still know a reference to this
 *	old font to be able to release it after it is used!</param>
 * <param name="pulOldFontColor" type="OUT">Pointer to get the previously used font color. This pointer can be <c>null</c> if the
 *	old font color should not be returned.</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicSetFont2',`(RTS_HANDLE hDC, RTS_HANDLE hFont, RTS_UI32 ulFontColor, RTS_HANDLE* phOldFont, RTS_UI32* pulOldFontColor)')

/**
 * <description>Function to create a Bitmap object(i.e. the HBITMAP in Win32)</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="pszBmpPath" type="IN">The path of the bitmap to load. Please remark that no mapping of this path is done before this method is called! That 
 *	means that it is up to the system specific implementation to respect possible mappings of paths that might be configured by the SysFile component. 
 *	This mapping can be done by either using <see>SysFileOpen</see> for accessing files or by calling <see>SysFileGetFullPath</see> before passing the path to
 *	an operating system file implementation (like fopen or classes loading images directly like QImage from Qt or Bitmap from GDI+).</param>
 * <param name="ulTransparentColor" type="IN">Contains the color that should be used as the transparent color. Will only be evaluated when
 *	the according flag is set. This color value can be used during loading an image when it is possible to do an optimization
 *	for painting transparent images like setting this color to transparent directly after loading or so. If such an optimization
 *	is not possible or not relevant, then the previous implementation by evaluating it within SysGraphicDrawBitmap can be used.</param>
 * <param name="ulFlags" type="IN">Flags. Defined in IEC-Code for Visualization. At the moment only the flag for
 *	transparency is relevant when loading an image!</param>
 * <param name="phBitmap" type="OUT">Pointer to get the bitmap handle</param>
 * <result>error code</result>
 * <note>Due to optimization reasons, the signature of this function was changed for the version 3.4.4. The transparency information
 *	is passed to this function too, to allow caching of transparency information.
 *	If you do not need to implement such a caching algorithm, then you can simply ignore the two parameters "ulFlags" and "ulTransparentColor".</note>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicCreateBitmap',`(RTS_HANDLE hDC, const char* pszBmpPath, RTS_UI32 ulTransparentColor, RTS_UI32 ulFlags, RTS_HANDLE* phBitmap)')

/**
 * <description>Function to draw a bitmap into a rectangle</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hBmp" type="IN">Handle to the bitmap</param>
 * <param name="rPos" type="IN">Position of the rectangle</param>
 * <param name="ulTransparentColor" type="IN">Contains the color that should be used as the transparent color. Will only be evaluated when
 *	the according flag is set. 
 *	Additionally, this paramter can be ignored, when it is already evaluated by SysGraphicCreateBitmap!</param>
 * <param name="ulFlags" type="IN">Flags. Defined in IEC-Code for Visualization</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicDrawBitmap',`(RTS_HANDLE hDC, RTS_HANDLE hBmp, RTS_Rectangle rPos, RTS_UI32 ulTransparentColor, RTS_UI32 ulFlags)')

/**
 * <description>Function to free a bitmap object</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hBmp" type="IN">Handle to the bitmap</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicFreeBitmap',`(RTS_HANDLE hDC, RTS_HANDLE hBmp)')

/**
 * <description>Function to get the bitmap size</description>
 * <param name="hBmp" type="IN">Handle to the bitmap</param>
 * <param name="pSize" type="IN">Point to store the size of the bitmap</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicGetBitmapSize',`(RTS_HANDLE hBmp, RTS_Point* pSize)')

/** 
 * <description>
 * <p>Obsolete: Use SysGraphicSetClipRectangle instead!</p>
 * <p>OBSOLETE Function to add a clipping rectangle to the current clipping region,
 *	i.e. elements beyond this rectangle won't be drawn</p></description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicAddClipRectangle',`(RTS_HANDLE hDC, RTS_Rectangle rect)')

/**
 * <description>
 * <p>Obsolete: Use SysGraphicSetClipRectangle instead!</p>
 * <p>OBSOLETE function to remove a clipping rectangle from the current clipping region
 *	i.e. elements beyond this rectangle will be drawn again</p></description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicRemoveClipRectangle',`(RTS_HANDLE hDC, RTS_Rectangle rect)')

/**
 * <description>function to set and reset the currently active clipping rectangle 
 *	i.e. elements beyond this rectangle will not be drawn</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="prect" type="IN">An optional Rectangle. If a rectangle is passed here, this rectangle will
 *	become the new clipping rectangle. If <c>NULL</c> is passed, the clipping region will cleared.
 *	The passed rectangle must not be modified by the implementation!</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicSetClipRectangle',`(RTS_HANDLE hDC, RTS_Rectangle* prect)')

/**
 * <description>This function and <see>SysGraphicEndPaint</see> are used to encapsule some paint calls
 *	together. An implementing platform could use this encapsulation for some optimizations. For every
 *	call to SysGraphicBeginPaint there will be an according call to SysGraphicEndPaint.</description>
 * <param name="hDC" type="IN">The device context that will be drawn onto until the next call to 
 *		<see>SysGraphicEndPaint</see> </param>
 * <param name="phPaintContext" type="OUT">An implementation could allocate some data and return it using
 *		this parameter. It will be given in the according call to <see>SysGraphicEndPaint</see> and can 
 *		be deleted there.</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicBeginPaint',`(RTS_HANDLE hDC, RTS_HANDLE* phPaintContext)')

/**
 * <description>This function and <see>SysGraphicBeginPaint</see> are used to encapsule some paint calls
 *	together. An implementing platform could use this encapsulation for some optimizations. For every
 *	call to SysGraphicBeginPaint there will be an according call to SysGraphicEndPaint.</description>
 * <param name="hDC" type="IN">The device context that has been drawn onto until this call</param>
 * <param name="hPaintContext" type="OUT">The data that has been returned by the corresponding call to 
 *		<see>SysGraphicBeginPaint</see>.</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicEndPaint',`(RTS_HANDLE hDC, RTS_HANDLE hPaintContext)')

/**
 * <description>This function allows the sysgraphic implementation to give a hint to the kernel part of the targetvisualization
 *	about some more or less optional feature that can be supported by an implementation. 
 *	As this function was introduced lateron, it should be included as an optional import to prevent inconsistencies. Additionally, calling code
 *	should assume a result of SYSGRAPHIC_FEATURES_ALL in case this function is not implemented for compatibility reasons.</description>
 * <result>The optional features that are implemented by the current sysgraphic implementation as a combination of the 
 *	flag values SYSGRAPHIC_FEATURES_...</result>
 */
DEF_API(`RTS_UI32',`CDECL',`SysGraphicGetFeatureFlags',`(void)')

/**
 * <description>This function can be used to prepare a device context for printing. Normally, this preparation is done 
 *	by the assignment of a transformation so that the screen output is scaled correctly to a printer device context. 
 *	This is perhaps necessary when the extent and/or the resolution of a printer device context is different than 
 *	these properties of the screen device context.</description>
 * <param name="hDC" type="IN">The device context of the printer that has to be prepared by this call.</param>
 * <param name="phOptionalResultData" type="OUT">An optional pointer to a handle that allows this method to allocate data that can be 
 *	released lateron in the call to <see>SysGraphicFinishPrinting</see>. If such data is not necessary on a specific platform implementation,
 *	this pointer can be NULL so that nothing can be returned here.</param>
 * <param name="prWindow" type="IN">A pointer to a rectangle that describes the extent of the targetvisualization window on the screen.</param>
 * <param name="prPrintOutput" type="IN">A pointer to a rectangle that describes the extent of the destination on the printer.</param>
 * <result>An error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicPreparePrinting',`(RTS_HANDLE hDC, RTS_HANDLE* phOptionalResultData, RTS_Rectangle* prWindow, RTS_Rectangle* prPrintOutput)')

/**
 * <description>This function reverts the adaptations done by <see>SysGraphicPreparePrinting</see></description>
 * <param name="hDC" type="IN">The device context of the printer that has to be reverted by this call.</param>
 * <param name="hOptionalResultData" type="IN">When <see>SysGraphicPreparePrinting</see> allocated and returned some additional data,
 *	this handle will be passed here again to be able to release the data correctly.</param>
 * <result>An error code</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`SysGraphicFinishPrinting',`(RTS_HANDLE hDC, RTS_HANDLE hOptionalResultData)')

/**
 * <description>This function assigns the antialiasing mode to a device context. By default, a device context should be in mode 
 *	<see>SYSGRAPHIC_ANTIALIASING_NONE</see>. If a device does not support antialiased drawing, it should return ERR_NOT_SUPPORTED.
 *	To tell the programming system, whether the antialiasing feature is supported, the targetsetting "visualization\targetsupport\targetvisualization_antialiasing"
 *	can be used.</description>
 * <param name="hDC" type="IN">The device context to assign the antialiasing mode to.</param>
 * <param name="uiAntiAliasingSettings" type="IN">The antialiasing mode (SYSGRAPHIC_ANTIALIASING_NONE,...).</param>
 * <result>An error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysGraphicSetAntiAliasingMode',`(RTS_HANDLE hDC, RTS_UI32 uiAntiAliasingSettings)')

/**
 * <description>This function is able to return the probably underlying font type as it is known by the SysWindow component from
 *	a font object that was allocated by the SysGraphic-Component.</description>	
 * <param name="hDC" type="IN">The device context that should be used for the conversion of the font type.</param>
 * <param name="hSysGraphicFont" type="IN">The font that was allocated by the SysGraphic-Component and that should be converted to a font object
 *	that can be handled by the SysWindow-Component.</param>
 * <param name="phSysWindowFont" type="OUT">A pointer that will receive the resulting (SysWindow) font.</param>
 * <result>An error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysGraphicGetSysWindowFont',`(RTS_HANDLE hDC, RTS_HANDLE hSysGraphicFont, RTS_HANDLE* phSysWindowFont)')

/**
 * <description>This function is optional and can be implemented by systems that need a valid backbuffer for painting to the foreground. 
 *  This fact probably depends on the underlying graphics system (for Windows or native systems, this is probably not necessary, for QT based 
 *	systems, an implementation might be necessary. The resulting list of invalidated rectangles should be reset in an implementation of
 *	<see>SysGraphicResetInvalidation</see></description>	
 * <param name="hDC" type="IN">The device context to invalidate in.</param>
 * <param name="rect" type="IN">The rectangle that is invalidated by the visualization. An implementation can use this call for example
 *	to fill a clip region so that only valid content will be drawn into the backbuffer.</param>
 * <result>An error code</result>
*/ 
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysGraphicInvalidateRectangle',`(RTS_HANDLE hDC, RTS_Rectangle rect)')

/**
 * <description>This function is optional in the same way than <see>SysGraphicInvalidateRectangle</see>. Nevertheless, if  <see>SysGraphicInvalidateRectangle</see> is
 *	implemented, then this function should be implemented too. It will be called to reset the list of passed invalidation rectangles. 
 *  This fact probably depends on the underlying graphics system (for Windows or native systems, this is probably not necessary, for QT based 
 *	systems, an implementation might be necessary.</description>	
 * <param name="hDC" type="IN">The device context to invalidate in.</param>
 * <result>An error code</result>
*/ 
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysGraphicResetInvalidation',`(RTS_HANDLE hDC)')

/**
 * <description>This function is optional, just as <see>SysGraphicInvalidateRectangle</see>, but should be implemented, if <see>SysGraphicInvalidateRectangle</see> is
 *  implemented. It will be called when the whole client area should be invalidated.</description>
 * <param name="hDC" type="IN">A handle to the device context.</param>
 * <result>An error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysGraphicInvalidateClientArea',`(RTS_HANDLE hDC)')


/**
 * <description>Creates an affine transformation object. 
 *	Such transformations can be used for client local animations (eg. when
 *	displaying the preview of multitouch gestures) or for drawing transformed elements (eg. rotated images or text).
 *	Usually such transformations are represented by transformation matrices.
 *	If affine transformations are not supported by the implementing platform, *pResult should be set to ERR_NOTIMPLEMENTED. In such
 *	a situation, some features might not work correctly.</description>	
 * <param name="pResult" type="OUT">Optional pointer to error code</param>
 * <result>A handle to the created transformation object</result>
*/ 
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysGraphicCreateTransformation',`(RTS_RESULT* pResult)')

/**
 * <description>Creates an affine transformation object using the given matrix members.
 *	Such transformations can be used for client local animations (eg. when
 *	displaying the preview of multitouch gestures) or for drawing transformed elements (eg. rotated images or text).
 *	Usually such transformations are represented by transformation matrices.
 *	If affine transformations are not supported by the implementing platform, *pResult should be set to ERR_NOTIMPLEMENTED. In such
 *	a situation, some features might not work correctly.</description>	
 * <param name="m11" type="IN">The transformation matrix value in the first row, first column</param>
 * <param name="m12" type="IN">The transformation matrix value in the first row, second column</param>
 * <param name="m21" type="IN">The transformation matrix value in the second row, first column</param>
 * <param name="m22" type="IN">The transformation matrix value in the second row, second column</param>
 * <param name="dx" type="IN">The transformation matrix value in the third row, first column</param>
 * <param name="dy" type="IN">The transformation matrix value in the third row, second column</param>
 * <param name="pResult" type="OUT">Optional pointer to error code</param>
 * <result>A handle to the created transformation object</result>
*/ 
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysGraphicCreateTransformationByValues',`(RTS_REAL32 m11, RTS_REAL32 m12, RTS_REAL32 m21, RTS_REAL32 m22, RTS_REAL32 dx, RTS_REAL32 dy, RTS_RESULT* pResult)')

/**
 * <description>Deletes an affine transformation object.</description>	
 * <param name="hTransform" type="IN">The transformation to delete.</param>
 * <result>An error code</result>
*/ 
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysGraphicFreeTransformation',`(RTS_HANDLE hTransform)')

/**
 * <description>Applies a scaling operation to the transformation object. The origin of the coordinate system (could have been moved by a previous 
 *	call to <see>SysGraphicTransformationTranslate</see> will be used as the origin for the scaling operation.</description>	
 * <param name="hTransform" type="IN">The transformation to scale.</param>
 * <param name="x" type="IN">The factor to scale in horizontal direction.</param>
 * <param name="y" type="IN">The factor to scale in vertical direction.</param>
 * <result>An error code</result>
*/ 
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysGraphicTransformationScale',`(RTS_HANDLE hTransform, RTS_REAL32 x, RTS_REAL32 y)')

/**
 * <description>Applies a rotation operation to the transformation object. The origin of the coordinate system (could have been moved by a previous 
 *	call to <see>SysGraphicTransformationTranslate</see> will be used as the center for the rotation operation.</description>	
 * <param name="hTransform" type="IN">The transformation to rotate.</param>
 * <param name="angle" type="IN">The angle of the rotation in degrees. Positive values specify clockwise rotation.</param>
 * <result>An error code</result>
*/ 
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysGraphicTransformationRotate',`(RTS_HANDLE hTransform, RTS_REAL32 angle)')

/**
 * <description>Applies a translation operation to the transformation object. </description>	
 * <param name="hTransform" type="IN">The transformation to translate.</param>
 * <param name="x" type="IN">The offset to shift in horizontal direction.</param>
 * <param name="y" type="IN">The offset to shift in vertical direction.</param>
 * <result>An error code</result>
*/ 
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysGraphicTransformationTranslate',`(RTS_HANDLE hTransform, RTS_REAL32 x, RTS_REAL32 y)')

/**
 * <description>Activates an affine transformation object on the given device context. This transformation will be applied to modify
 *	all followup drawing operations on this device context until a different (or no) transformation is set.</description>	
 * <param name="hdc" type="IN">The device context to apply the transformation on.</param>
 * <param name="hTransform" type="IN">The transformation to apply. Pass RTS_INVALID_HANDLE to deactivate any transformations.</param>
 * <result>An error code</result>
*/ 
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysGraphicSetActiveTransformation',`(RTS_HANDLE hdc, RTS_HANDLE hTransform)')

/**
 * <description>Returns the currently active affine transformation object on the given device context.</description>	
 * <param name="hdc" type="IN">The device context to retrieve the the transformation from.</param>
 * <param name="hTransform" type="IN">The transformation to apply. Pass RTS_INVALID_HANDLE to deactivate any transformations.</param>
 * <param name="pResult" type="OUT">Optional pointer to error code</param>
 * <result>The handle or the active transformation or RTS_INVALID_HANDLE if there was no active one..</result>
*/ 
DEF_HANDLEITF_API(`RTS_HANDLE',`CDECL',`SysGraphicGetActiveTransformation',`(RTS_HANDLE hdc, RTS_RESULT* pResult)')

/**
 * <description>Creates a new affine transformation object that is a copy of an existing affine transformation object.</description>
 * <param name="hTransform" type="IN">A handle to the object to clone.</param>	
 * <param name="pResult" type="OUT">Optional pointer to error code.</param>
 * <result>A handle to the created transformation object or RTS_INVALID_HANDLE if there was an error.</result>
*/ 
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysGraphicCloneTransformation',`(RTS_HANDLE hTransform, RTS_RESULT* pResult)')

/**
 * <description>Applies a transformation operation to the transformation object. </description>	
 * <param name="hTransform" type="IN">Handle to the transformation object to transform.</param>
 * <param name="m11" type="IN">The transformation matrix value in the first row, first column</param>
 * <param name="m12" type="IN">The transformation matrix value in the first row, second column</param>
 * <param name="m21" type="IN">The transformation matrix value in the second row, first column</param>
 * <param name="m22" type="IN">The transformation matrix value in the second row, second column</param>
 * <param name="dx" type="IN">The transformation matrix value in the third row, first column</param>
 * <param name="dy" type="IN">The transformation matrix value in the third row, second column</param>
 * <result>An error code</result>
*/ 
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysGraphicTransformationTransform',`(RTS_HANDLE hTransform, RTS_REAL32 m11, RTS_REAL32 m12, RTS_REAL32 m21, RTS_REAL32 m22, RTS_REAL32 dx, RTS_REAL32 dy)')


#ifdef __cplusplus
}
#endif
