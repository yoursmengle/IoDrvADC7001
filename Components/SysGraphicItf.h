 /**
 * <interfacename>SysGraphic</interfacename>
 * <description> 
 *	<p>The SysGraphic interface is projected to get access to the graphic library routines
 *	of a system. This is the system interface typically for the CoDeSys target visualization.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSGRAPHICITF_H_
#define _SYSGRAPHICITF_H_

#include "CmpStd.h"

 

 




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
RTS_RESULT CDECL SysGraphicCreateCompatibleDeviceContext(RTS_HANDLE hWindow, RTS_HANDLE* phDC);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICCREATECOMPATIBLEDEVICECONTEXT) (RTS_HANDLE hWindow, RTS_HANDLE* phDC);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCREATECOMPATIBLEDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicCreateCompatibleDeviceContext
	#define EXT_SysGraphicCreateCompatibleDeviceContext
	#define GET_SysGraphicCreateCompatibleDeviceContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCreateCompatibleDeviceContext(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicCreateCompatibleDeviceContext  FALSE
	#define EXP_SysGraphicCreateCompatibleDeviceContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCreateCompatibleDeviceContext
	#define EXT_SysGraphicCreateCompatibleDeviceContext
	#define GET_SysGraphicCreateCompatibleDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicCreateCompatibleDeviceContext" ) 
	#define CAL_SysGraphicCreateCompatibleDeviceContext  SysGraphicCreateCompatibleDeviceContext
	#define CHK_SysGraphicCreateCompatibleDeviceContext  TRUE
	#define EXP_SysGraphicCreateCompatibleDeviceContext  CAL_CMEXPAPI( "SysGraphicCreateCompatibleDeviceContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCreateCompatibleDeviceContext
	#define EXT_SysGraphicCreateCompatibleDeviceContext
	#define GET_SysGraphicCreateCompatibleDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicCreateCompatibleDeviceContext" ) 
	#define CAL_SysGraphicCreateCompatibleDeviceContext  SysGraphicCreateCompatibleDeviceContext
	#define CHK_SysGraphicCreateCompatibleDeviceContext  TRUE
	#define EXP_SysGraphicCreateCompatibleDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateCompatibleDeviceContext", (RTS_UINTPTR)SysGraphicCreateCompatibleDeviceContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCreateCompatibleDeviceContext
	#define EXT_SysGraphicSysGraphicCreateCompatibleDeviceContext
	#define GET_SysGraphicSysGraphicCreateCompatibleDeviceContext  ERR_OK
	#define CAL_SysGraphicSysGraphicCreateCompatibleDeviceContext  SysGraphicCreateCompatibleDeviceContext
	#define CHK_SysGraphicSysGraphicCreateCompatibleDeviceContext  TRUE
	#define EXP_SysGraphicSysGraphicCreateCompatibleDeviceContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCreateCompatibleDeviceContext
	#define EXT_SysGraphicCreateCompatibleDeviceContext
	#define GET_SysGraphicCreateCompatibleDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicCreateCompatibleDeviceContext" ) 
	#define CAL_SysGraphicCreateCompatibleDeviceContext  SysGraphicCreateCompatibleDeviceContext
	#define CHK_SysGraphicCreateCompatibleDeviceContext  TRUE
	#define EXP_SysGraphicCreateCompatibleDeviceContext  CAL_CMEXPAPI( "SysGraphicCreateCompatibleDeviceContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCreateCompatibleDeviceContext  PFSYSGRAPHICCREATECOMPATIBLEDEVICECONTEXT pfSysGraphicCreateCompatibleDeviceContext;
	#define EXT_SysGraphicCreateCompatibleDeviceContext  extern PFSYSGRAPHICCREATECOMPATIBLEDEVICECONTEXT pfSysGraphicCreateCompatibleDeviceContext;
	#define GET_SysGraphicCreateCompatibleDeviceContext(fl)  s_pfCMGetAPI2( "SysGraphicCreateCompatibleDeviceContext", (RTS_VOID_FCTPTR *)&pfSysGraphicCreateCompatibleDeviceContext, (fl), 0, 0)
	#define CAL_SysGraphicCreateCompatibleDeviceContext  pfSysGraphicCreateCompatibleDeviceContext
	#define CHK_SysGraphicCreateCompatibleDeviceContext  (pfSysGraphicCreateCompatibleDeviceContext != NULL)
	#define EXP_SysGraphicCreateCompatibleDeviceContext   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateCompatibleDeviceContext", (RTS_UINTPTR)SysGraphicCreateCompatibleDeviceContext, 0, 0) 
#endif


/**
 * <description>Create compatible device context with custom size</description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="iWidth" type="IN">Width of the device Context</param>
 * <param name="iHeight" type="IN">Height of the device Context</param>
 * <param name="phDC" type="OUT">Pointer to handle to get the device context</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicCreateCompatibleDeviceContextWithCustomSize(RTS_HANDLE hWindow, RTS_I16 iWidth, RTS_I16 iHeight, RTS_HANDLE* phDC);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICCREATECOMPATIBLEDEVICECONTEXTWITHCUSTOMSIZE) (RTS_HANDLE hWindow, RTS_I16 iWidth, RTS_I16 iHeight, RTS_HANDLE* phDC);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCREATECOMPATIBLEDEVICECONTEXTWITHCUSTOMSIZE_NOTIMPLEMENTED)
	#define USE_SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define EXT_SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define GET_SysGraphicCreateCompatibleDeviceContextWithCustomSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCreateCompatibleDeviceContextWithCustomSize(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicCreateCompatibleDeviceContextWithCustomSize  FALSE
	#define EXP_SysGraphicCreateCompatibleDeviceContextWithCustomSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define EXT_SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define GET_SysGraphicCreateCompatibleDeviceContextWithCustomSize(fl)  CAL_CMGETAPI( "SysGraphicCreateCompatibleDeviceContextWithCustomSize" ) 
	#define CAL_SysGraphicCreateCompatibleDeviceContextWithCustomSize  SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define CHK_SysGraphicCreateCompatibleDeviceContextWithCustomSize  TRUE
	#define EXP_SysGraphicCreateCompatibleDeviceContextWithCustomSize  CAL_CMEXPAPI( "SysGraphicCreateCompatibleDeviceContextWithCustomSize" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define EXT_SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define GET_SysGraphicCreateCompatibleDeviceContextWithCustomSize(fl)  CAL_CMGETAPI( "SysGraphicCreateCompatibleDeviceContextWithCustomSize" ) 
	#define CAL_SysGraphicCreateCompatibleDeviceContextWithCustomSize  SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define CHK_SysGraphicCreateCompatibleDeviceContextWithCustomSize  TRUE
	#define EXP_SysGraphicCreateCompatibleDeviceContextWithCustomSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateCompatibleDeviceContextWithCustomSize", (RTS_UINTPTR)SysGraphicCreateCompatibleDeviceContextWithCustomSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define EXT_SysGraphicSysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define GET_SysGraphicSysGraphicCreateCompatibleDeviceContextWithCustomSize  ERR_OK
	#define CAL_SysGraphicSysGraphicCreateCompatibleDeviceContextWithCustomSize  SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define CHK_SysGraphicSysGraphicCreateCompatibleDeviceContextWithCustomSize  TRUE
	#define EXP_SysGraphicSysGraphicCreateCompatibleDeviceContextWithCustomSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define EXT_SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define GET_SysGraphicCreateCompatibleDeviceContextWithCustomSize(fl)  CAL_CMGETAPI( "SysGraphicCreateCompatibleDeviceContextWithCustomSize" ) 
	#define CAL_SysGraphicCreateCompatibleDeviceContextWithCustomSize  SysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define CHK_SysGraphicCreateCompatibleDeviceContextWithCustomSize  TRUE
	#define EXP_SysGraphicCreateCompatibleDeviceContextWithCustomSize  CAL_CMEXPAPI( "SysGraphicCreateCompatibleDeviceContextWithCustomSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCreateCompatibleDeviceContextWithCustomSize  PFSYSGRAPHICCREATECOMPATIBLEDEVICECONTEXTWITHCUSTOMSIZE pfSysGraphicCreateCompatibleDeviceContextWithCustomSize;
	#define EXT_SysGraphicCreateCompatibleDeviceContextWithCustomSize  extern PFSYSGRAPHICCREATECOMPATIBLEDEVICECONTEXTWITHCUSTOMSIZE pfSysGraphicCreateCompatibleDeviceContextWithCustomSize;
	#define GET_SysGraphicCreateCompatibleDeviceContextWithCustomSize(fl)  s_pfCMGetAPI2( "SysGraphicCreateCompatibleDeviceContextWithCustomSize", (RTS_VOID_FCTPTR *)&pfSysGraphicCreateCompatibleDeviceContextWithCustomSize, (fl), 0, 0)
	#define CAL_SysGraphicCreateCompatibleDeviceContextWithCustomSize  pfSysGraphicCreateCompatibleDeviceContextWithCustomSize
	#define CHK_SysGraphicCreateCompatibleDeviceContextWithCustomSize  (pfSysGraphicCreateCompatibleDeviceContextWithCustomSize != NULL)
	#define EXP_SysGraphicCreateCompatibleDeviceContextWithCustomSize   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateCompatibleDeviceContextWithCustomSize", (RTS_UINTPTR)SysGraphicCreateCompatibleDeviceContextWithCustomSize, 0, 0) 
#endif


/**
 * <description>Delete compatible device context</description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="hDC" type="IN">Handle to the device context</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicDeleteDeviceContext(RTS_HANDLE hWindow, RTS_HANDLE hDC);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICDELETEDEVICECONTEXT) (RTS_HANDLE hWindow, RTS_HANDLE hDC);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICDELETEDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicDeleteDeviceContext
	#define EXT_SysGraphicDeleteDeviceContext
	#define GET_SysGraphicDeleteDeviceContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicDeleteDeviceContext(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicDeleteDeviceContext  FALSE
	#define EXP_SysGraphicDeleteDeviceContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicDeleteDeviceContext
	#define EXT_SysGraphicDeleteDeviceContext
	#define GET_SysGraphicDeleteDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicDeleteDeviceContext" ) 
	#define CAL_SysGraphicDeleteDeviceContext  SysGraphicDeleteDeviceContext
	#define CHK_SysGraphicDeleteDeviceContext  TRUE
	#define EXP_SysGraphicDeleteDeviceContext  CAL_CMEXPAPI( "SysGraphicDeleteDeviceContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicDeleteDeviceContext
	#define EXT_SysGraphicDeleteDeviceContext
	#define GET_SysGraphicDeleteDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicDeleteDeviceContext" ) 
	#define CAL_SysGraphicDeleteDeviceContext  SysGraphicDeleteDeviceContext
	#define CHK_SysGraphicDeleteDeviceContext  TRUE
	#define EXP_SysGraphicDeleteDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDeleteDeviceContext", (RTS_UINTPTR)SysGraphicDeleteDeviceContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicDeleteDeviceContext
	#define EXT_SysGraphicSysGraphicDeleteDeviceContext
	#define GET_SysGraphicSysGraphicDeleteDeviceContext  ERR_OK
	#define CAL_SysGraphicSysGraphicDeleteDeviceContext  SysGraphicDeleteDeviceContext
	#define CHK_SysGraphicSysGraphicDeleteDeviceContext  TRUE
	#define EXP_SysGraphicSysGraphicDeleteDeviceContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicDeleteDeviceContext
	#define EXT_SysGraphicDeleteDeviceContext
	#define GET_SysGraphicDeleteDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicDeleteDeviceContext" ) 
	#define CAL_SysGraphicDeleteDeviceContext  SysGraphicDeleteDeviceContext
	#define CHK_SysGraphicDeleteDeviceContext  TRUE
	#define EXP_SysGraphicDeleteDeviceContext  CAL_CMEXPAPI( "SysGraphicDeleteDeviceContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicDeleteDeviceContext  PFSYSGRAPHICDELETEDEVICECONTEXT pfSysGraphicDeleteDeviceContext;
	#define EXT_SysGraphicDeleteDeviceContext  extern PFSYSGRAPHICDELETEDEVICECONTEXT pfSysGraphicDeleteDeviceContext;
	#define GET_SysGraphicDeleteDeviceContext(fl)  s_pfCMGetAPI2( "SysGraphicDeleteDeviceContext", (RTS_VOID_FCTPTR *)&pfSysGraphicDeleteDeviceContext, (fl), 0, 0)
	#define CAL_SysGraphicDeleteDeviceContext  pfSysGraphicDeleteDeviceContext
	#define CHK_SysGraphicDeleteDeviceContext  (pfSysGraphicDeleteDeviceContext != NULL)
	#define EXP_SysGraphicDeleteDeviceContext   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDeleteDeviceContext", (RTS_UINTPTR)SysGraphicDeleteDeviceContext, 0, 0) 
#endif


/**
 * <description>Get a device context. Remember to release such a device context using <see>SysGraphicReleaseDeviceContext</see>
 *	and not with <see>SysGraphicDeleteDeviceContext</see>!</description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="phDC" type="OUT">Pointer to handle to get the device context</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicGetDeviceContext(RTS_HANDLE hWindow, RTS_HANDLE* phDC);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICGETDEVICECONTEXT) (RTS_HANDLE hWindow, RTS_HANDLE* phDC);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICGETDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicGetDeviceContext
	#define EXT_SysGraphicGetDeviceContext
	#define GET_SysGraphicGetDeviceContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicGetDeviceContext(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicGetDeviceContext  FALSE
	#define EXP_SysGraphicGetDeviceContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicGetDeviceContext
	#define EXT_SysGraphicGetDeviceContext
	#define GET_SysGraphicGetDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicGetDeviceContext" ) 
	#define CAL_SysGraphicGetDeviceContext  SysGraphicGetDeviceContext
	#define CHK_SysGraphicGetDeviceContext  TRUE
	#define EXP_SysGraphicGetDeviceContext  CAL_CMEXPAPI( "SysGraphicGetDeviceContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicGetDeviceContext
	#define EXT_SysGraphicGetDeviceContext
	#define GET_SysGraphicGetDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicGetDeviceContext" ) 
	#define CAL_SysGraphicGetDeviceContext  SysGraphicGetDeviceContext
	#define CHK_SysGraphicGetDeviceContext  TRUE
	#define EXP_SysGraphicGetDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetDeviceContext", (RTS_UINTPTR)SysGraphicGetDeviceContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicGetDeviceContext
	#define EXT_SysGraphicSysGraphicGetDeviceContext
	#define GET_SysGraphicSysGraphicGetDeviceContext  ERR_OK
	#define CAL_SysGraphicSysGraphicGetDeviceContext  SysGraphicGetDeviceContext
	#define CHK_SysGraphicSysGraphicGetDeviceContext  TRUE
	#define EXP_SysGraphicSysGraphicGetDeviceContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicGetDeviceContext
	#define EXT_SysGraphicGetDeviceContext
	#define GET_SysGraphicGetDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicGetDeviceContext" ) 
	#define CAL_SysGraphicGetDeviceContext  SysGraphicGetDeviceContext
	#define CHK_SysGraphicGetDeviceContext  TRUE
	#define EXP_SysGraphicGetDeviceContext  CAL_CMEXPAPI( "SysGraphicGetDeviceContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicGetDeviceContext  PFSYSGRAPHICGETDEVICECONTEXT pfSysGraphicGetDeviceContext;
	#define EXT_SysGraphicGetDeviceContext  extern PFSYSGRAPHICGETDEVICECONTEXT pfSysGraphicGetDeviceContext;
	#define GET_SysGraphicGetDeviceContext(fl)  s_pfCMGetAPI2( "SysGraphicGetDeviceContext", (RTS_VOID_FCTPTR *)&pfSysGraphicGetDeviceContext, (fl), 0, 0)
	#define CAL_SysGraphicGetDeviceContext  pfSysGraphicGetDeviceContext
	#define CHK_SysGraphicGetDeviceContext  (pfSysGraphicGetDeviceContext != NULL)
	#define EXP_SysGraphicGetDeviceContext   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetDeviceContext", (RTS_UINTPTR)SysGraphicGetDeviceContext, 0, 0) 
#endif


/**
 * <description>Release a device context that has been retrieved using <see>SysGraphicGetDeviceContext</see></description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="hDC" type="IN">Handle to the device context</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicReleaseDeviceContext(RTS_HANDLE hWindow, RTS_HANDLE hDC);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICRELEASEDEVICECONTEXT) (RTS_HANDLE hWindow, RTS_HANDLE hDC);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICRELEASEDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicReleaseDeviceContext
	#define EXT_SysGraphicReleaseDeviceContext
	#define GET_SysGraphicReleaseDeviceContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicReleaseDeviceContext(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicReleaseDeviceContext  FALSE
	#define EXP_SysGraphicReleaseDeviceContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicReleaseDeviceContext
	#define EXT_SysGraphicReleaseDeviceContext
	#define GET_SysGraphicReleaseDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicReleaseDeviceContext" ) 
	#define CAL_SysGraphicReleaseDeviceContext  SysGraphicReleaseDeviceContext
	#define CHK_SysGraphicReleaseDeviceContext  TRUE
	#define EXP_SysGraphicReleaseDeviceContext  CAL_CMEXPAPI( "SysGraphicReleaseDeviceContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicReleaseDeviceContext
	#define EXT_SysGraphicReleaseDeviceContext
	#define GET_SysGraphicReleaseDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicReleaseDeviceContext" ) 
	#define CAL_SysGraphicReleaseDeviceContext  SysGraphicReleaseDeviceContext
	#define CHK_SysGraphicReleaseDeviceContext  TRUE
	#define EXP_SysGraphicReleaseDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicReleaseDeviceContext", (RTS_UINTPTR)SysGraphicReleaseDeviceContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicReleaseDeviceContext
	#define EXT_SysGraphicSysGraphicReleaseDeviceContext
	#define GET_SysGraphicSysGraphicReleaseDeviceContext  ERR_OK
	#define CAL_SysGraphicSysGraphicReleaseDeviceContext  SysGraphicReleaseDeviceContext
	#define CHK_SysGraphicSysGraphicReleaseDeviceContext  TRUE
	#define EXP_SysGraphicSysGraphicReleaseDeviceContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicReleaseDeviceContext
	#define EXT_SysGraphicReleaseDeviceContext
	#define GET_SysGraphicReleaseDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicReleaseDeviceContext" ) 
	#define CAL_SysGraphicReleaseDeviceContext  SysGraphicReleaseDeviceContext
	#define CHK_SysGraphicReleaseDeviceContext  TRUE
	#define EXP_SysGraphicReleaseDeviceContext  CAL_CMEXPAPI( "SysGraphicReleaseDeviceContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicReleaseDeviceContext  PFSYSGRAPHICRELEASEDEVICECONTEXT pfSysGraphicReleaseDeviceContext;
	#define EXT_SysGraphicReleaseDeviceContext  extern PFSYSGRAPHICRELEASEDEVICECONTEXT pfSysGraphicReleaseDeviceContext;
	#define GET_SysGraphicReleaseDeviceContext(fl)  s_pfCMGetAPI2( "SysGraphicReleaseDeviceContext", (RTS_VOID_FCTPTR *)&pfSysGraphicReleaseDeviceContext, (fl), 0, 0)
	#define CAL_SysGraphicReleaseDeviceContext  pfSysGraphicReleaseDeviceContext
	#define CHK_SysGraphicReleaseDeviceContext  (pfSysGraphicReleaseDeviceContext != NULL)
	#define EXP_SysGraphicReleaseDeviceContext   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicReleaseDeviceContext", (RTS_UINTPTR)SysGraphicReleaseDeviceContext, 0, 0) 
#endif


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
RTS_RESULT CDECL SysGraphicGetDeviceContextForWindowDeviceContext(RTS_HANDLE hWindow, RTS_HANDLE hDCWindow, RTS_HANDLE* phDC);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICGETDEVICECONTEXTFORWINDOWDEVICECONTEXT) (RTS_HANDLE hWindow, RTS_HANDLE hDCWindow, RTS_HANDLE* phDC);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICGETDEVICECONTEXTFORWINDOWDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicGetDeviceContextForWindowDeviceContext
	#define EXT_SysGraphicGetDeviceContextForWindowDeviceContext
	#define GET_SysGraphicGetDeviceContextForWindowDeviceContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicGetDeviceContextForWindowDeviceContext(p0,p1,p2) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicGetDeviceContextForWindowDeviceContext  FALSE
	#define EXP_SysGraphicGetDeviceContextForWindowDeviceContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicGetDeviceContextForWindowDeviceContext
	#define EXT_SysGraphicGetDeviceContextForWindowDeviceContext
	#define GET_SysGraphicGetDeviceContextForWindowDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicGetDeviceContextForWindowDeviceContext" ) 
	#define CAL_SysGraphicGetDeviceContextForWindowDeviceContext  SysGraphicGetDeviceContextForWindowDeviceContext
	#define CHK_SysGraphicGetDeviceContextForWindowDeviceContext  TRUE
	#define EXP_SysGraphicGetDeviceContextForWindowDeviceContext  CAL_CMEXPAPI( "SysGraphicGetDeviceContextForWindowDeviceContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicGetDeviceContextForWindowDeviceContext
	#define EXT_SysGraphicGetDeviceContextForWindowDeviceContext
	#define GET_SysGraphicGetDeviceContextForWindowDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicGetDeviceContextForWindowDeviceContext" ) 
	#define CAL_SysGraphicGetDeviceContextForWindowDeviceContext  SysGraphicGetDeviceContextForWindowDeviceContext
	#define CHK_SysGraphicGetDeviceContextForWindowDeviceContext  TRUE
	#define EXP_SysGraphicGetDeviceContextForWindowDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetDeviceContextForWindowDeviceContext", (RTS_UINTPTR)SysGraphicGetDeviceContextForWindowDeviceContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicGetDeviceContextForWindowDeviceContext
	#define EXT_SysGraphicSysGraphicGetDeviceContextForWindowDeviceContext
	#define GET_SysGraphicSysGraphicGetDeviceContextForWindowDeviceContext  ERR_OK
	#define CAL_SysGraphicSysGraphicGetDeviceContextForWindowDeviceContext  SysGraphicGetDeviceContextForWindowDeviceContext
	#define CHK_SysGraphicSysGraphicGetDeviceContextForWindowDeviceContext  TRUE
	#define EXP_SysGraphicSysGraphicGetDeviceContextForWindowDeviceContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicGetDeviceContextForWindowDeviceContext
	#define EXT_SysGraphicGetDeviceContextForWindowDeviceContext
	#define GET_SysGraphicGetDeviceContextForWindowDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicGetDeviceContextForWindowDeviceContext" ) 
	#define CAL_SysGraphicGetDeviceContextForWindowDeviceContext  SysGraphicGetDeviceContextForWindowDeviceContext
	#define CHK_SysGraphicGetDeviceContextForWindowDeviceContext  TRUE
	#define EXP_SysGraphicGetDeviceContextForWindowDeviceContext  CAL_CMEXPAPI( "SysGraphicGetDeviceContextForWindowDeviceContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicGetDeviceContextForWindowDeviceContext  PFSYSGRAPHICGETDEVICECONTEXTFORWINDOWDEVICECONTEXT pfSysGraphicGetDeviceContextForWindowDeviceContext;
	#define EXT_SysGraphicGetDeviceContextForWindowDeviceContext  extern PFSYSGRAPHICGETDEVICECONTEXTFORWINDOWDEVICECONTEXT pfSysGraphicGetDeviceContextForWindowDeviceContext;
	#define GET_SysGraphicGetDeviceContextForWindowDeviceContext(fl)  s_pfCMGetAPI2( "SysGraphicGetDeviceContextForWindowDeviceContext", (RTS_VOID_FCTPTR *)&pfSysGraphicGetDeviceContextForWindowDeviceContext, (fl), 0, 0)
	#define CAL_SysGraphicGetDeviceContextForWindowDeviceContext  pfSysGraphicGetDeviceContextForWindowDeviceContext
	#define CHK_SysGraphicGetDeviceContextForWindowDeviceContext  (pfSysGraphicGetDeviceContextForWindowDeviceContext != NULL)
	#define EXP_SysGraphicGetDeviceContextForWindowDeviceContext   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetDeviceContextForWindowDeviceContext", (RTS_UINTPTR)SysGraphicGetDeviceContextForWindowDeviceContext, 0, 0) 
#endif


/**
 * <description>Release a device context that has been retrieved using <see>SysGraphicGetDeviceContextForWindowDeviceContext</see></description>
 * <param name="hWindow" type="IN">Handle to the actual window</param>
 * <param name="hDC" type="IN">Handle to the device context</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicReleaseDeviceContextForWindowDeviceContext(RTS_HANDLE hWindow, RTS_HANDLE hDC);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICRELEASEDEVICECONTEXTFORWINDOWDEVICECONTEXT) (RTS_HANDLE hWindow, RTS_HANDLE hDC);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICRELEASEDEVICECONTEXTFORWINDOWDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define EXT_SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define GET_SysGraphicReleaseDeviceContextForWindowDeviceContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicReleaseDeviceContextForWindowDeviceContext(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicReleaseDeviceContextForWindowDeviceContext  FALSE
	#define EXP_SysGraphicReleaseDeviceContextForWindowDeviceContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define EXT_SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define GET_SysGraphicReleaseDeviceContextForWindowDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicReleaseDeviceContextForWindowDeviceContext" ) 
	#define CAL_SysGraphicReleaseDeviceContextForWindowDeviceContext  SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define CHK_SysGraphicReleaseDeviceContextForWindowDeviceContext  TRUE
	#define EXP_SysGraphicReleaseDeviceContextForWindowDeviceContext  CAL_CMEXPAPI( "SysGraphicReleaseDeviceContextForWindowDeviceContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define EXT_SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define GET_SysGraphicReleaseDeviceContextForWindowDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicReleaseDeviceContextForWindowDeviceContext" ) 
	#define CAL_SysGraphicReleaseDeviceContextForWindowDeviceContext  SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define CHK_SysGraphicReleaseDeviceContextForWindowDeviceContext  TRUE
	#define EXP_SysGraphicReleaseDeviceContextForWindowDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicReleaseDeviceContextForWindowDeviceContext", (RTS_UINTPTR)SysGraphicReleaseDeviceContextForWindowDeviceContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicReleaseDeviceContextForWindowDeviceContext
	#define EXT_SysGraphicSysGraphicReleaseDeviceContextForWindowDeviceContext
	#define GET_SysGraphicSysGraphicReleaseDeviceContextForWindowDeviceContext  ERR_OK
	#define CAL_SysGraphicSysGraphicReleaseDeviceContextForWindowDeviceContext  SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define CHK_SysGraphicSysGraphicReleaseDeviceContextForWindowDeviceContext  TRUE
	#define EXP_SysGraphicSysGraphicReleaseDeviceContextForWindowDeviceContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define EXT_SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define GET_SysGraphicReleaseDeviceContextForWindowDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicReleaseDeviceContextForWindowDeviceContext" ) 
	#define CAL_SysGraphicReleaseDeviceContextForWindowDeviceContext  SysGraphicReleaseDeviceContextForWindowDeviceContext
	#define CHK_SysGraphicReleaseDeviceContextForWindowDeviceContext  TRUE
	#define EXP_SysGraphicReleaseDeviceContextForWindowDeviceContext  CAL_CMEXPAPI( "SysGraphicReleaseDeviceContextForWindowDeviceContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicReleaseDeviceContextForWindowDeviceContext  PFSYSGRAPHICRELEASEDEVICECONTEXTFORWINDOWDEVICECONTEXT pfSysGraphicReleaseDeviceContextForWindowDeviceContext;
	#define EXT_SysGraphicReleaseDeviceContextForWindowDeviceContext  extern PFSYSGRAPHICRELEASEDEVICECONTEXTFORWINDOWDEVICECONTEXT pfSysGraphicReleaseDeviceContextForWindowDeviceContext;
	#define GET_SysGraphicReleaseDeviceContextForWindowDeviceContext(fl)  s_pfCMGetAPI2( "SysGraphicReleaseDeviceContextForWindowDeviceContext", (RTS_VOID_FCTPTR *)&pfSysGraphicReleaseDeviceContextForWindowDeviceContext, (fl), 0, 0)
	#define CAL_SysGraphicReleaseDeviceContextForWindowDeviceContext  pfSysGraphicReleaseDeviceContextForWindowDeviceContext
	#define CHK_SysGraphicReleaseDeviceContextForWindowDeviceContext  (pfSysGraphicReleaseDeviceContextForWindowDeviceContext != NULL)
	#define EXP_SysGraphicReleaseDeviceContextForWindowDeviceContext   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicReleaseDeviceContextForWindowDeviceContext", (RTS_UINTPTR)SysGraphicReleaseDeviceContextForWindowDeviceContext, 0, 0) 
#endif


/**
 * <description>Set the background color of the device context</description>
 * <param name="hWindow" type="IN">Handle to the device context</param>
 * <param name="ulColor" type="IN">Color. Defined in IEC-Code for Visualization</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicSetBackgroundColor(RTS_HANDLE hDC, RTS_UI32 ulColor);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICSETBACKGROUNDCOLOR) (RTS_HANDLE hDC, RTS_UI32 ulColor);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICSETBACKGROUNDCOLOR_NOTIMPLEMENTED)
	#define USE_SysGraphicSetBackgroundColor
	#define EXT_SysGraphicSetBackgroundColor
	#define GET_SysGraphicSetBackgroundColor(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicSetBackgroundColor(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicSetBackgroundColor  FALSE
	#define EXP_SysGraphicSetBackgroundColor  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicSetBackgroundColor
	#define EXT_SysGraphicSetBackgroundColor
	#define GET_SysGraphicSetBackgroundColor(fl)  CAL_CMGETAPI( "SysGraphicSetBackgroundColor" ) 
	#define CAL_SysGraphicSetBackgroundColor  SysGraphicSetBackgroundColor
	#define CHK_SysGraphicSetBackgroundColor  TRUE
	#define EXP_SysGraphicSetBackgroundColor  CAL_CMEXPAPI( "SysGraphicSetBackgroundColor" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicSetBackgroundColor
	#define EXT_SysGraphicSetBackgroundColor
	#define GET_SysGraphicSetBackgroundColor(fl)  CAL_CMGETAPI( "SysGraphicSetBackgroundColor" ) 
	#define CAL_SysGraphicSetBackgroundColor  SysGraphicSetBackgroundColor
	#define CHK_SysGraphicSetBackgroundColor  TRUE
	#define EXP_SysGraphicSetBackgroundColor  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetBackgroundColor", (RTS_UINTPTR)SysGraphicSetBackgroundColor, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicSetBackgroundColor
	#define EXT_SysGraphicSysGraphicSetBackgroundColor
	#define GET_SysGraphicSysGraphicSetBackgroundColor  ERR_OK
	#define CAL_SysGraphicSysGraphicSetBackgroundColor  SysGraphicSetBackgroundColor
	#define CHK_SysGraphicSysGraphicSetBackgroundColor  TRUE
	#define EXP_SysGraphicSysGraphicSetBackgroundColor  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicSetBackgroundColor
	#define EXT_SysGraphicSetBackgroundColor
	#define GET_SysGraphicSetBackgroundColor(fl)  CAL_CMGETAPI( "SysGraphicSetBackgroundColor" ) 
	#define CAL_SysGraphicSetBackgroundColor  SysGraphicSetBackgroundColor
	#define CHK_SysGraphicSetBackgroundColor  TRUE
	#define EXP_SysGraphicSetBackgroundColor  CAL_CMEXPAPI( "SysGraphicSetBackgroundColor" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicSetBackgroundColor  PFSYSGRAPHICSETBACKGROUNDCOLOR pfSysGraphicSetBackgroundColor;
	#define EXT_SysGraphicSetBackgroundColor  extern PFSYSGRAPHICSETBACKGROUNDCOLOR pfSysGraphicSetBackgroundColor;
	#define GET_SysGraphicSetBackgroundColor(fl)  s_pfCMGetAPI2( "SysGraphicSetBackgroundColor", (RTS_VOID_FCTPTR *)&pfSysGraphicSetBackgroundColor, (fl), 0, 0)
	#define CAL_SysGraphicSetBackgroundColor  pfSysGraphicSetBackgroundColor
	#define CHK_SysGraphicSetBackgroundColor  (pfSysGraphicSetBackgroundColor != NULL)
	#define EXP_SysGraphicSetBackgroundColor   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetBackgroundColor", (RTS_UINTPTR)SysGraphicSetBackgroundColor, 0, 0) 
#endif


/**
 * <description>Clear the specified rectangle</description>
 * <param name="hWindow" type="IN">Handle to the device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicClearRectangle(RTS_HANDLE hDC, RTS_Rectangle rect);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICCLEARRECTANGLE) (RTS_HANDLE hDC, RTS_Rectangle rect);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCLEARRECTANGLE_NOTIMPLEMENTED)
	#define USE_SysGraphicClearRectangle
	#define EXT_SysGraphicClearRectangle
	#define GET_SysGraphicClearRectangle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicClearRectangle(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicClearRectangle  FALSE
	#define EXP_SysGraphicClearRectangle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicClearRectangle
	#define EXT_SysGraphicClearRectangle
	#define GET_SysGraphicClearRectangle(fl)  CAL_CMGETAPI( "SysGraphicClearRectangle" ) 
	#define CAL_SysGraphicClearRectangle  SysGraphicClearRectangle
	#define CHK_SysGraphicClearRectangle  TRUE
	#define EXP_SysGraphicClearRectangle  CAL_CMEXPAPI( "SysGraphicClearRectangle" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicClearRectangle
	#define EXT_SysGraphicClearRectangle
	#define GET_SysGraphicClearRectangle(fl)  CAL_CMGETAPI( "SysGraphicClearRectangle" ) 
	#define CAL_SysGraphicClearRectangle  SysGraphicClearRectangle
	#define CHK_SysGraphicClearRectangle  TRUE
	#define EXP_SysGraphicClearRectangle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicClearRectangle", (RTS_UINTPTR)SysGraphicClearRectangle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicClearRectangle
	#define EXT_SysGraphicSysGraphicClearRectangle
	#define GET_SysGraphicSysGraphicClearRectangle  ERR_OK
	#define CAL_SysGraphicSysGraphicClearRectangle  SysGraphicClearRectangle
	#define CHK_SysGraphicSysGraphicClearRectangle  TRUE
	#define EXP_SysGraphicSysGraphicClearRectangle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicClearRectangle
	#define EXT_SysGraphicClearRectangle
	#define GET_SysGraphicClearRectangle(fl)  CAL_CMGETAPI( "SysGraphicClearRectangle" ) 
	#define CAL_SysGraphicClearRectangle  SysGraphicClearRectangle
	#define CHK_SysGraphicClearRectangle  TRUE
	#define EXP_SysGraphicClearRectangle  CAL_CMEXPAPI( "SysGraphicClearRectangle" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicClearRectangle  PFSYSGRAPHICCLEARRECTANGLE pfSysGraphicClearRectangle;
	#define EXT_SysGraphicClearRectangle  extern PFSYSGRAPHICCLEARRECTANGLE pfSysGraphicClearRectangle;
	#define GET_SysGraphicClearRectangle(fl)  s_pfCMGetAPI2( "SysGraphicClearRectangle", (RTS_VOID_FCTPTR *)&pfSysGraphicClearRectangle, (fl), 0, 0)
	#define CAL_SysGraphicClearRectangle  pfSysGraphicClearRectangle
	#define CHK_SysGraphicClearRectangle  (pfSysGraphicClearRectangle != NULL)
	#define EXP_SysGraphicClearRectangle   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicClearRectangle", (RTS_UINTPTR)SysGraphicClearRectangle, 0, 0) 
#endif


/**
 * <description>Performs a bit-block transfer of the color data corresponding to a rectangle of pixels 
 *	from the specified source device context into a destination device context</description>
 * <param name="hDCDestination" type="IN">Handle to destination device context</param>
 * <param name="hDCSource" type="IN">Handle to source device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicBitBlt(RTS_HANDLE hDCDestination, RTS_HANDLE hDCSource, RTS_Rectangle rect);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICBITBLT) (RTS_HANDLE hDCDestination, RTS_HANDLE hDCSource, RTS_Rectangle rect);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICBITBLT_NOTIMPLEMENTED)
	#define USE_SysGraphicBitBlt
	#define EXT_SysGraphicBitBlt
	#define GET_SysGraphicBitBlt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicBitBlt(p0,p1,p2) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicBitBlt  FALSE
	#define EXP_SysGraphicBitBlt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicBitBlt
	#define EXT_SysGraphicBitBlt
	#define GET_SysGraphicBitBlt(fl)  CAL_CMGETAPI( "SysGraphicBitBlt" ) 
	#define CAL_SysGraphicBitBlt  SysGraphicBitBlt
	#define CHK_SysGraphicBitBlt  TRUE
	#define EXP_SysGraphicBitBlt  CAL_CMEXPAPI( "SysGraphicBitBlt" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicBitBlt
	#define EXT_SysGraphicBitBlt
	#define GET_SysGraphicBitBlt(fl)  CAL_CMGETAPI( "SysGraphicBitBlt" ) 
	#define CAL_SysGraphicBitBlt  SysGraphicBitBlt
	#define CHK_SysGraphicBitBlt  TRUE
	#define EXP_SysGraphicBitBlt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicBitBlt", (RTS_UINTPTR)SysGraphicBitBlt, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicBitBlt
	#define EXT_SysGraphicSysGraphicBitBlt
	#define GET_SysGraphicSysGraphicBitBlt  ERR_OK
	#define CAL_SysGraphicSysGraphicBitBlt  SysGraphicBitBlt
	#define CHK_SysGraphicSysGraphicBitBlt  TRUE
	#define EXP_SysGraphicSysGraphicBitBlt  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicBitBlt
	#define EXT_SysGraphicBitBlt
	#define GET_SysGraphicBitBlt(fl)  CAL_CMGETAPI( "SysGraphicBitBlt" ) 
	#define CAL_SysGraphicBitBlt  SysGraphicBitBlt
	#define CHK_SysGraphicBitBlt  TRUE
	#define EXP_SysGraphicBitBlt  CAL_CMEXPAPI( "SysGraphicBitBlt" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicBitBlt  PFSYSGRAPHICBITBLT pfSysGraphicBitBlt;
	#define EXT_SysGraphicBitBlt  extern PFSYSGRAPHICBITBLT pfSysGraphicBitBlt;
	#define GET_SysGraphicBitBlt(fl)  s_pfCMGetAPI2( "SysGraphicBitBlt", (RTS_VOID_FCTPTR *)&pfSysGraphicBitBlt, (fl), 0, 0)
	#define CAL_SysGraphicBitBlt  pfSysGraphicBitBlt
	#define CHK_SysGraphicBitBlt  (pfSysGraphicBitBlt != NULL)
	#define EXP_SysGraphicBitBlt   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicBitBlt", (RTS_UINTPTR)SysGraphicBitBlt, 0, 0) 
#endif


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
RTS_RESULT CDECL SysGraphicStretchBlt(RTS_HANDLE hDCDestination, RTS_Rectangle rectDestination, RTS_HANDLE hDCSource, RTS_Rectangle rectSource);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICSTRETCHBLT) (RTS_HANDLE hDCDestination, RTS_Rectangle rectDestination, RTS_HANDLE hDCSource, RTS_Rectangle rectSource);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICSTRETCHBLT_NOTIMPLEMENTED)
	#define USE_SysGraphicStretchBlt
	#define EXT_SysGraphicStretchBlt
	#define GET_SysGraphicStretchBlt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicStretchBlt(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicStretchBlt  FALSE
	#define EXP_SysGraphicStretchBlt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicStretchBlt
	#define EXT_SysGraphicStretchBlt
	#define GET_SysGraphicStretchBlt(fl)  CAL_CMGETAPI( "SysGraphicStretchBlt" ) 
	#define CAL_SysGraphicStretchBlt  SysGraphicStretchBlt
	#define CHK_SysGraphicStretchBlt  TRUE
	#define EXP_SysGraphicStretchBlt  CAL_CMEXPAPI( "SysGraphicStretchBlt" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicStretchBlt
	#define EXT_SysGraphicStretchBlt
	#define GET_SysGraphicStretchBlt(fl)  CAL_CMGETAPI( "SysGraphicStretchBlt" ) 
	#define CAL_SysGraphicStretchBlt  SysGraphicStretchBlt
	#define CHK_SysGraphicStretchBlt  TRUE
	#define EXP_SysGraphicStretchBlt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicStretchBlt", (RTS_UINTPTR)SysGraphicStretchBlt, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicStretchBlt
	#define EXT_SysGraphicSysGraphicStretchBlt
	#define GET_SysGraphicSysGraphicStretchBlt  ERR_OK
	#define CAL_SysGraphicSysGraphicStretchBlt  SysGraphicStretchBlt
	#define CHK_SysGraphicSysGraphicStretchBlt  TRUE
	#define EXP_SysGraphicSysGraphicStretchBlt  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicStretchBlt
	#define EXT_SysGraphicStretchBlt
	#define GET_SysGraphicStretchBlt(fl)  CAL_CMGETAPI( "SysGraphicStretchBlt" ) 
	#define CAL_SysGraphicStretchBlt  SysGraphicStretchBlt
	#define CHK_SysGraphicStretchBlt  TRUE
	#define EXP_SysGraphicStretchBlt  CAL_CMEXPAPI( "SysGraphicStretchBlt" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicStretchBlt  PFSYSGRAPHICSTRETCHBLT pfSysGraphicStretchBlt;
	#define EXT_SysGraphicStretchBlt  extern PFSYSGRAPHICSTRETCHBLT pfSysGraphicStretchBlt;
	#define GET_SysGraphicStretchBlt(fl)  s_pfCMGetAPI2( "SysGraphicStretchBlt", (RTS_VOID_FCTPTR *)&pfSysGraphicStretchBlt, (fl), 0, 0)
	#define CAL_SysGraphicStretchBlt  pfSysGraphicStretchBlt
	#define CHK_SysGraphicStretchBlt  (pfSysGraphicStretchBlt != NULL)
	#define EXP_SysGraphicStretchBlt   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicStretchBlt", (RTS_UINTPTR)SysGraphicStretchBlt, 0, 0) 
#endif


/**
 * <description>Function to draw a rectangle based on top left and bottom right</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <param name="nType" type="IN">Rectangle type. See corresponding category</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicDrawRect(RTS_HANDLE hDC, RTS_Rectangle rect, RectangleType nType);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICDRAWRECT) (RTS_HANDLE hDC, RTS_Rectangle rect, RectangleType nType);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICDRAWRECT_NOTIMPLEMENTED)
	#define USE_SysGraphicDrawRect
	#define EXT_SysGraphicDrawRect
	#define GET_SysGraphicDrawRect(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicDrawRect(p0,p1,p2) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicDrawRect  FALSE
	#define EXP_SysGraphicDrawRect  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicDrawRect
	#define EXT_SysGraphicDrawRect
	#define GET_SysGraphicDrawRect(fl)  CAL_CMGETAPI( "SysGraphicDrawRect" ) 
	#define CAL_SysGraphicDrawRect  SysGraphicDrawRect
	#define CHK_SysGraphicDrawRect  TRUE
	#define EXP_SysGraphicDrawRect  CAL_CMEXPAPI( "SysGraphicDrawRect" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicDrawRect
	#define EXT_SysGraphicDrawRect
	#define GET_SysGraphicDrawRect(fl)  CAL_CMGETAPI( "SysGraphicDrawRect" ) 
	#define CAL_SysGraphicDrawRect  SysGraphicDrawRect
	#define CHK_SysGraphicDrawRect  TRUE
	#define EXP_SysGraphicDrawRect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawRect", (RTS_UINTPTR)SysGraphicDrawRect, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicDrawRect
	#define EXT_SysGraphicSysGraphicDrawRect
	#define GET_SysGraphicSysGraphicDrawRect  ERR_OK
	#define CAL_SysGraphicSysGraphicDrawRect  SysGraphicDrawRect
	#define CHK_SysGraphicSysGraphicDrawRect  TRUE
	#define EXP_SysGraphicSysGraphicDrawRect  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicDrawRect
	#define EXT_SysGraphicDrawRect
	#define GET_SysGraphicDrawRect(fl)  CAL_CMGETAPI( "SysGraphicDrawRect" ) 
	#define CAL_SysGraphicDrawRect  SysGraphicDrawRect
	#define CHK_SysGraphicDrawRect  TRUE
	#define EXP_SysGraphicDrawRect  CAL_CMEXPAPI( "SysGraphicDrawRect" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicDrawRect  PFSYSGRAPHICDRAWRECT pfSysGraphicDrawRect;
	#define EXT_SysGraphicDrawRect  extern PFSYSGRAPHICDRAWRECT pfSysGraphicDrawRect;
	#define GET_SysGraphicDrawRect(fl)  s_pfCMGetAPI2( "SysGraphicDrawRect", (RTS_VOID_FCTPTR *)&pfSysGraphicDrawRect, (fl), 0, 0)
	#define CAL_SysGraphicDrawRect  pfSysGraphicDrawRect
	#define CHK_SysGraphicDrawRect  (pfSysGraphicDrawRect != NULL)
	#define EXP_SysGraphicDrawRect   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawRect", (RTS_UINTPTR)SysGraphicDrawRect, 0, 0) 
#endif


/**
 * <description>Function to draw a rectangle based on top left and bottom right with real value coordinates</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <param name="nType" type="IN">Rectangle type. See corresponding category</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicDrawRectF(RTS_HANDLE hDC, RTS_RectangleF rect, RectangleType nType);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICDRAWRECTF) (RTS_HANDLE hDC, RTS_RectangleF rect, RectangleType nType);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICDRAWRECTF_NOTIMPLEMENTED)
	#define USE_SysGraphicDrawRectF
	#define EXT_SysGraphicDrawRectF
	#define GET_SysGraphicDrawRectF(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicDrawRectF(p0,p1,p2) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicDrawRectF  FALSE
	#define EXP_SysGraphicDrawRectF  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicDrawRectF
	#define EXT_SysGraphicDrawRectF
	#define GET_SysGraphicDrawRectF(fl)  CAL_CMGETAPI( "SysGraphicDrawRectF" ) 
	#define CAL_SysGraphicDrawRectF  SysGraphicDrawRectF
	#define CHK_SysGraphicDrawRectF  TRUE
	#define EXP_SysGraphicDrawRectF  CAL_CMEXPAPI( "SysGraphicDrawRectF" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicDrawRectF
	#define EXT_SysGraphicDrawRectF
	#define GET_SysGraphicDrawRectF(fl)  CAL_CMGETAPI( "SysGraphicDrawRectF" ) 
	#define CAL_SysGraphicDrawRectF  SysGraphicDrawRectF
	#define CHK_SysGraphicDrawRectF  TRUE
	#define EXP_SysGraphicDrawRectF  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawRectF", (RTS_UINTPTR)SysGraphicDrawRectF, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicDrawRectF
	#define EXT_SysGraphicSysGraphicDrawRectF
	#define GET_SysGraphicSysGraphicDrawRectF  ERR_OK
	#define CAL_SysGraphicSysGraphicDrawRectF  SysGraphicDrawRectF
	#define CHK_SysGraphicSysGraphicDrawRectF  TRUE
	#define EXP_SysGraphicSysGraphicDrawRectF  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicDrawRectF
	#define EXT_SysGraphicDrawRectF
	#define GET_SysGraphicDrawRectF(fl)  CAL_CMGETAPI( "SysGraphicDrawRectF" ) 
	#define CAL_SysGraphicDrawRectF  SysGraphicDrawRectF
	#define CHK_SysGraphicDrawRectF  TRUE
	#define EXP_SysGraphicDrawRectF  CAL_CMEXPAPI( "SysGraphicDrawRectF" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicDrawRectF  PFSYSGRAPHICDRAWRECTF pfSysGraphicDrawRectF;
	#define EXT_SysGraphicDrawRectF  extern PFSYSGRAPHICDRAWRECTF pfSysGraphicDrawRectF;
	#define GET_SysGraphicDrawRectF(fl)  s_pfCMGetAPI2( "SysGraphicDrawRectF", (RTS_VOID_FCTPTR *)&pfSysGraphicDrawRectF, (fl), 0, 0)
	#define CAL_SysGraphicDrawRectF  pfSysGraphicDrawRectF
	#define CHK_SysGraphicDrawRectF  (pfSysGraphicDrawRectF != NULL)
	#define EXP_SysGraphicDrawRectF   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawRectF", (RTS_UINTPTR)SysGraphicDrawRectF, 0, 0) 
#endif


/**
 * <description>Function to draw a polygon based on an array of points</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="nPoints" type="IN">Number of points in the array</param>
 * <param name="pPoints" type="IN">Pointer to the array of points. Length must be less or equal nPoints!</param>
 * <param name="nType" type="IN">Polygon type. See corresponding category</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicDrawPolygon(RTS_HANDLE hDC, RTS_I16 nPoints, RTS_Point* pPoints, PolygonType nType);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICDRAWPOLYGON) (RTS_HANDLE hDC, RTS_I16 nPoints, RTS_Point* pPoints, PolygonType nType);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICDRAWPOLYGON_NOTIMPLEMENTED)
	#define USE_SysGraphicDrawPolygon
	#define EXT_SysGraphicDrawPolygon
	#define GET_SysGraphicDrawPolygon(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicDrawPolygon(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicDrawPolygon  FALSE
	#define EXP_SysGraphicDrawPolygon  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicDrawPolygon
	#define EXT_SysGraphicDrawPolygon
	#define GET_SysGraphicDrawPolygon(fl)  CAL_CMGETAPI( "SysGraphicDrawPolygon" ) 
	#define CAL_SysGraphicDrawPolygon  SysGraphicDrawPolygon
	#define CHK_SysGraphicDrawPolygon  TRUE
	#define EXP_SysGraphicDrawPolygon  CAL_CMEXPAPI( "SysGraphicDrawPolygon" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicDrawPolygon
	#define EXT_SysGraphicDrawPolygon
	#define GET_SysGraphicDrawPolygon(fl)  CAL_CMGETAPI( "SysGraphicDrawPolygon" ) 
	#define CAL_SysGraphicDrawPolygon  SysGraphicDrawPolygon
	#define CHK_SysGraphicDrawPolygon  TRUE
	#define EXP_SysGraphicDrawPolygon  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawPolygon", (RTS_UINTPTR)SysGraphicDrawPolygon, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicDrawPolygon
	#define EXT_SysGraphicSysGraphicDrawPolygon
	#define GET_SysGraphicSysGraphicDrawPolygon  ERR_OK
	#define CAL_SysGraphicSysGraphicDrawPolygon  SysGraphicDrawPolygon
	#define CHK_SysGraphicSysGraphicDrawPolygon  TRUE
	#define EXP_SysGraphicSysGraphicDrawPolygon  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicDrawPolygon
	#define EXT_SysGraphicDrawPolygon
	#define GET_SysGraphicDrawPolygon(fl)  CAL_CMGETAPI( "SysGraphicDrawPolygon" ) 
	#define CAL_SysGraphicDrawPolygon  SysGraphicDrawPolygon
	#define CHK_SysGraphicDrawPolygon  TRUE
	#define EXP_SysGraphicDrawPolygon  CAL_CMEXPAPI( "SysGraphicDrawPolygon" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicDrawPolygon  PFSYSGRAPHICDRAWPOLYGON pfSysGraphicDrawPolygon;
	#define EXT_SysGraphicDrawPolygon  extern PFSYSGRAPHICDRAWPOLYGON pfSysGraphicDrawPolygon;
	#define GET_SysGraphicDrawPolygon(fl)  s_pfCMGetAPI2( "SysGraphicDrawPolygon", (RTS_VOID_FCTPTR *)&pfSysGraphicDrawPolygon, (fl), 0, 0)
	#define CAL_SysGraphicDrawPolygon  pfSysGraphicDrawPolygon
	#define CHK_SysGraphicDrawPolygon  (pfSysGraphicDrawPolygon != NULL)
	#define EXP_SysGraphicDrawPolygon   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawPolygon", (RTS_UINTPTR)SysGraphicDrawPolygon, 0, 0) 
#endif


/**
 * <description>Function to draw a polygon based on an array of points</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="nPoints" type="IN">Number of points in the array</param>
 * <param name="pPoints" type="IN">Pointer to the array of points. Length must be less or equal nPoints!</param>
 * <param name="nType" type="IN">Polygon type. See corresponding category</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicDrawPolygonF(RTS_HANDLE hDC, RTS_I16 nPoints, RTS_PointF* pPoints, PolygonType nType);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICDRAWPOLYGONF) (RTS_HANDLE hDC, RTS_I16 nPoints, RTS_PointF* pPoints, PolygonType nType);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICDRAWPOLYGONF_NOTIMPLEMENTED)
	#define USE_SysGraphicDrawPolygonF
	#define EXT_SysGraphicDrawPolygonF
	#define GET_SysGraphicDrawPolygonF(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicDrawPolygonF(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicDrawPolygonF  FALSE
	#define EXP_SysGraphicDrawPolygonF  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicDrawPolygonF
	#define EXT_SysGraphicDrawPolygonF
	#define GET_SysGraphicDrawPolygonF(fl)  CAL_CMGETAPI( "SysGraphicDrawPolygonF" ) 
	#define CAL_SysGraphicDrawPolygonF  SysGraphicDrawPolygonF
	#define CHK_SysGraphicDrawPolygonF  TRUE
	#define EXP_SysGraphicDrawPolygonF  CAL_CMEXPAPI( "SysGraphicDrawPolygonF" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicDrawPolygonF
	#define EXT_SysGraphicDrawPolygonF
	#define GET_SysGraphicDrawPolygonF(fl)  CAL_CMGETAPI( "SysGraphicDrawPolygonF" ) 
	#define CAL_SysGraphicDrawPolygonF  SysGraphicDrawPolygonF
	#define CHK_SysGraphicDrawPolygonF  TRUE
	#define EXP_SysGraphicDrawPolygonF  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawPolygonF", (RTS_UINTPTR)SysGraphicDrawPolygonF, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicDrawPolygonF
	#define EXT_SysGraphicSysGraphicDrawPolygonF
	#define GET_SysGraphicSysGraphicDrawPolygonF  ERR_OK
	#define CAL_SysGraphicSysGraphicDrawPolygonF  SysGraphicDrawPolygonF
	#define CHK_SysGraphicSysGraphicDrawPolygonF  TRUE
	#define EXP_SysGraphicSysGraphicDrawPolygonF  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicDrawPolygonF
	#define EXT_SysGraphicDrawPolygonF
	#define GET_SysGraphicDrawPolygonF(fl)  CAL_CMGETAPI( "SysGraphicDrawPolygonF" ) 
	#define CAL_SysGraphicDrawPolygonF  SysGraphicDrawPolygonF
	#define CHK_SysGraphicDrawPolygonF  TRUE
	#define EXP_SysGraphicDrawPolygonF  CAL_CMEXPAPI( "SysGraphicDrawPolygonF" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicDrawPolygonF  PFSYSGRAPHICDRAWPOLYGONF pfSysGraphicDrawPolygonF;
	#define EXT_SysGraphicDrawPolygonF  extern PFSYSGRAPHICDRAWPOLYGONF pfSysGraphicDrawPolygonF;
	#define GET_SysGraphicDrawPolygonF(fl)  s_pfCMGetAPI2( "SysGraphicDrawPolygonF", (RTS_VOID_FCTPTR *)&pfSysGraphicDrawPolygonF, (fl), 0, 0)
	#define CAL_SysGraphicDrawPolygonF  pfSysGraphicDrawPolygonF
	#define CHK_SysGraphicDrawPolygonF  (pfSysGraphicDrawPolygonF != NULL)
	#define EXP_SysGraphicDrawPolygonF   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawPolygonF", (RTS_UINTPTR)SysGraphicDrawPolygonF, 0, 0) 
#endif


/**
 * <description>Function to draw a pie based on top left and bottom right</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <param name="iStartAngle" type="IN">The start angle</param>
 * <param name="iSweepAngle" type="IN">The sweep angle</param>
 * <param name="nType" type="IN">Pie type. See corresponding category</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicDrawPie(RTS_HANDLE hDC, RTS_Rectangle rect, RTS_IEC_INT iStartAngle, RTS_IEC_INT iSweepAngle, PieType nType);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICDRAWPIE) (RTS_HANDLE hDC, RTS_Rectangle rect, RTS_IEC_INT iStartAngle, RTS_IEC_INT iSweepAngle, PieType nType);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICDRAWPIE_NOTIMPLEMENTED)
	#define USE_SysGraphicDrawPie
	#define EXT_SysGraphicDrawPie
	#define GET_SysGraphicDrawPie(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicDrawPie(p0,p1,p2,p3,p4) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicDrawPie  FALSE
	#define EXP_SysGraphicDrawPie  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicDrawPie
	#define EXT_SysGraphicDrawPie
	#define GET_SysGraphicDrawPie(fl)  CAL_CMGETAPI( "SysGraphicDrawPie" ) 
	#define CAL_SysGraphicDrawPie  SysGraphicDrawPie
	#define CHK_SysGraphicDrawPie  TRUE
	#define EXP_SysGraphicDrawPie  CAL_CMEXPAPI( "SysGraphicDrawPie" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicDrawPie
	#define EXT_SysGraphicDrawPie
	#define GET_SysGraphicDrawPie(fl)  CAL_CMGETAPI( "SysGraphicDrawPie" ) 
	#define CAL_SysGraphicDrawPie  SysGraphicDrawPie
	#define CHK_SysGraphicDrawPie  TRUE
	#define EXP_SysGraphicDrawPie  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawPie", (RTS_UINTPTR)SysGraphicDrawPie, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicDrawPie
	#define EXT_SysGraphicSysGraphicDrawPie
	#define GET_SysGraphicSysGraphicDrawPie  ERR_OK
	#define CAL_SysGraphicSysGraphicDrawPie  SysGraphicDrawPie
	#define CHK_SysGraphicSysGraphicDrawPie  TRUE
	#define EXP_SysGraphicSysGraphicDrawPie  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicDrawPie
	#define EXT_SysGraphicDrawPie
	#define GET_SysGraphicDrawPie(fl)  CAL_CMGETAPI( "SysGraphicDrawPie" ) 
	#define CAL_SysGraphicDrawPie  SysGraphicDrawPie
	#define CHK_SysGraphicDrawPie  TRUE
	#define EXP_SysGraphicDrawPie  CAL_CMEXPAPI( "SysGraphicDrawPie" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicDrawPie  PFSYSGRAPHICDRAWPIE pfSysGraphicDrawPie;
	#define EXT_SysGraphicDrawPie  extern PFSYSGRAPHICDRAWPIE pfSysGraphicDrawPie;
	#define GET_SysGraphicDrawPie(fl)  s_pfCMGetAPI2( "SysGraphicDrawPie", (RTS_VOID_FCTPTR *)&pfSysGraphicDrawPie, (fl), 0, 0)
	#define CAL_SysGraphicDrawPie  pfSysGraphicDrawPie
	#define CHK_SysGraphicDrawPie  (pfSysGraphicDrawPie != NULL)
	#define EXP_SysGraphicDrawPie   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawPie", (RTS_UINTPTR)SysGraphicDrawPie, 0, 0) 
#endif


/**
 * <description>Applies a clockwise rotation to this system drawing matrix around the point specified in the point parameter</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="iAngle" type="IN">The angle to rotate in radians</param>
 * <param name="point" type="IN">The point represents the center of the rotation</param>
 * <param name="bReset" type="IN">Reset the transformation</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicRotateAt(RTS_HANDLE hDC, RTS_REAL32 fAngle, RTS_Point point, RTS_BOOL bReset);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICROTATEAT) (RTS_HANDLE hDC, RTS_REAL32 fAngle, RTS_Point point, RTS_BOOL bReset);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICROTATEAT_NOTIMPLEMENTED)
	#define USE_SysGraphicRotateAt
	#define EXT_SysGraphicRotateAt
	#define GET_SysGraphicRotateAt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicRotateAt(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicRotateAt  FALSE
	#define EXP_SysGraphicRotateAt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicRotateAt
	#define EXT_SysGraphicRotateAt
	#define GET_SysGraphicRotateAt(fl)  CAL_CMGETAPI( "SysGraphicRotateAt" ) 
	#define CAL_SysGraphicRotateAt  SysGraphicRotateAt
	#define CHK_SysGraphicRotateAt  TRUE
	#define EXP_SysGraphicRotateAt  CAL_CMEXPAPI( "SysGraphicRotateAt" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicRotateAt
	#define EXT_SysGraphicRotateAt
	#define GET_SysGraphicRotateAt(fl)  CAL_CMGETAPI( "SysGraphicRotateAt" ) 
	#define CAL_SysGraphicRotateAt  SysGraphicRotateAt
	#define CHK_SysGraphicRotateAt  TRUE
	#define EXP_SysGraphicRotateAt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicRotateAt", (RTS_UINTPTR)SysGraphicRotateAt, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicRotateAt
	#define EXT_SysGraphicSysGraphicRotateAt
	#define GET_SysGraphicSysGraphicRotateAt  ERR_OK
	#define CAL_SysGraphicSysGraphicRotateAt  SysGraphicRotateAt
	#define CHK_SysGraphicSysGraphicRotateAt  TRUE
	#define EXP_SysGraphicSysGraphicRotateAt  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicRotateAt
	#define EXT_SysGraphicRotateAt
	#define GET_SysGraphicRotateAt(fl)  CAL_CMGETAPI( "SysGraphicRotateAt" ) 
	#define CAL_SysGraphicRotateAt  SysGraphicRotateAt
	#define CHK_SysGraphicRotateAt  TRUE
	#define EXP_SysGraphicRotateAt  CAL_CMEXPAPI( "SysGraphicRotateAt" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicRotateAt  PFSYSGRAPHICROTATEAT pfSysGraphicRotateAt;
	#define EXT_SysGraphicRotateAt  extern PFSYSGRAPHICROTATEAT pfSysGraphicRotateAt;
	#define GET_SysGraphicRotateAt(fl)  s_pfCMGetAPI2( "SysGraphicRotateAt", (RTS_VOID_FCTPTR *)&pfSysGraphicRotateAt, (fl), 0, 0)
	#define CAL_SysGraphicRotateAt  pfSysGraphicRotateAt
	#define CHK_SysGraphicRotateAt  (pfSysGraphicRotateAt != NULL)
	#define EXP_SysGraphicRotateAt   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicRotateAt", (RTS_UINTPTR)SysGraphicRotateAt, 0, 0) 
#endif


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
RTS_RESULT CDECL SysGraphicDrawText(RTS_HANDLE hDC, RTS_Rectangle rect, void* pszText, RTS_UI32 ulDrawFlags);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICDRAWTEXT) (RTS_HANDLE hDC, RTS_Rectangle rect, void* pszText, RTS_UI32 ulDrawFlags);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICDRAWTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicDrawText
	#define EXT_SysGraphicDrawText
	#define GET_SysGraphicDrawText(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicDrawText(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicDrawText  FALSE
	#define EXP_SysGraphicDrawText  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicDrawText
	#define EXT_SysGraphicDrawText
	#define GET_SysGraphicDrawText(fl)  CAL_CMGETAPI( "SysGraphicDrawText" ) 
	#define CAL_SysGraphicDrawText  SysGraphicDrawText
	#define CHK_SysGraphicDrawText  TRUE
	#define EXP_SysGraphicDrawText  CAL_CMEXPAPI( "SysGraphicDrawText" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicDrawText
	#define EXT_SysGraphicDrawText
	#define GET_SysGraphicDrawText(fl)  CAL_CMGETAPI( "SysGraphicDrawText" ) 
	#define CAL_SysGraphicDrawText  SysGraphicDrawText
	#define CHK_SysGraphicDrawText  TRUE
	#define EXP_SysGraphicDrawText  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawText", (RTS_UINTPTR)SysGraphicDrawText, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicDrawText
	#define EXT_SysGraphicSysGraphicDrawText
	#define GET_SysGraphicSysGraphicDrawText  ERR_OK
	#define CAL_SysGraphicSysGraphicDrawText  SysGraphicDrawText
	#define CHK_SysGraphicSysGraphicDrawText  TRUE
	#define EXP_SysGraphicSysGraphicDrawText  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicDrawText
	#define EXT_SysGraphicDrawText
	#define GET_SysGraphicDrawText(fl)  CAL_CMGETAPI( "SysGraphicDrawText" ) 
	#define CAL_SysGraphicDrawText  SysGraphicDrawText
	#define CHK_SysGraphicDrawText  TRUE
	#define EXP_SysGraphicDrawText  CAL_CMEXPAPI( "SysGraphicDrawText" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicDrawText  PFSYSGRAPHICDRAWTEXT pfSysGraphicDrawText;
	#define EXT_SysGraphicDrawText  extern PFSYSGRAPHICDRAWTEXT pfSysGraphicDrawText;
	#define GET_SysGraphicDrawText(fl)  s_pfCMGetAPI2( "SysGraphicDrawText", (RTS_VOID_FCTPTR *)&pfSysGraphicDrawText, (fl), 0, 0)
	#define CAL_SysGraphicDrawText  pfSysGraphicDrawText
	#define CHK_SysGraphicDrawText  (pfSysGraphicDrawText != NULL)
	#define EXP_SysGraphicDrawText   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawText", (RTS_UINTPTR)SysGraphicDrawText, 0, 0) 
#endif


/**
 * <description>Get the system metrics of a device context</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="ptm" type="OUT">Pointer to the system metrics</param>
 * <remarks>This function is not used yet and might not be implemented.</remarks>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicGetTextMetrics(RTS_HANDLE hDC, SYS_TEXTMETRICS* ptm);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICGETTEXTMETRICS) (RTS_HANDLE hDC, SYS_TEXTMETRICS* ptm);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICGETTEXTMETRICS_NOTIMPLEMENTED)
	#define USE_SysGraphicGetTextMetrics
	#define EXT_SysGraphicGetTextMetrics
	#define GET_SysGraphicGetTextMetrics(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicGetTextMetrics(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicGetTextMetrics  FALSE
	#define EXP_SysGraphicGetTextMetrics  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicGetTextMetrics
	#define EXT_SysGraphicGetTextMetrics
	#define GET_SysGraphicGetTextMetrics(fl)  CAL_CMGETAPI( "SysGraphicGetTextMetrics" ) 
	#define CAL_SysGraphicGetTextMetrics  SysGraphicGetTextMetrics
	#define CHK_SysGraphicGetTextMetrics  TRUE
	#define EXP_SysGraphicGetTextMetrics  CAL_CMEXPAPI( "SysGraphicGetTextMetrics" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicGetTextMetrics
	#define EXT_SysGraphicGetTextMetrics
	#define GET_SysGraphicGetTextMetrics(fl)  CAL_CMGETAPI( "SysGraphicGetTextMetrics" ) 
	#define CAL_SysGraphicGetTextMetrics  SysGraphicGetTextMetrics
	#define CHK_SysGraphicGetTextMetrics  TRUE
	#define EXP_SysGraphicGetTextMetrics  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetTextMetrics", (RTS_UINTPTR)SysGraphicGetTextMetrics, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicGetTextMetrics
	#define EXT_SysGraphicSysGraphicGetTextMetrics
	#define GET_SysGraphicSysGraphicGetTextMetrics  ERR_OK
	#define CAL_SysGraphicSysGraphicGetTextMetrics  SysGraphicGetTextMetrics
	#define CHK_SysGraphicSysGraphicGetTextMetrics  TRUE
	#define EXP_SysGraphicSysGraphicGetTextMetrics  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicGetTextMetrics
	#define EXT_SysGraphicGetTextMetrics
	#define GET_SysGraphicGetTextMetrics(fl)  CAL_CMGETAPI( "SysGraphicGetTextMetrics" ) 
	#define CAL_SysGraphicGetTextMetrics  SysGraphicGetTextMetrics
	#define CHK_SysGraphicGetTextMetrics  TRUE
	#define EXP_SysGraphicGetTextMetrics  CAL_CMEXPAPI( "SysGraphicGetTextMetrics" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicGetTextMetrics  PFSYSGRAPHICGETTEXTMETRICS pfSysGraphicGetTextMetrics;
	#define EXT_SysGraphicGetTextMetrics  extern PFSYSGRAPHICGETTEXTMETRICS pfSysGraphicGetTextMetrics;
	#define GET_SysGraphicGetTextMetrics(fl)  s_pfCMGetAPI2( "SysGraphicGetTextMetrics", (RTS_VOID_FCTPTR *)&pfSysGraphicGetTextMetrics, (fl), 0, 0)
	#define CAL_SysGraphicGetTextMetrics  pfSysGraphicGetTextMetrics
	#define CHK_SysGraphicGetTextMetrics  (pfSysGraphicGetTextMetrics != NULL)
	#define EXP_SysGraphicGetTextMetrics   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetTextMetrics", (RTS_UINTPTR)SysGraphicGetTextMetrics, 0, 0) 
#endif


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
RTS_RESULT CDECL SysGraphicGetTextExtent(RTS_HANDLE hDC, void* pszText, RTS_UI32 ulDrawFlags, RTS_Size* pSize);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICGETTEXTEXTENT) (RTS_HANDLE hDC, void* pszText, RTS_UI32 ulDrawFlags, RTS_Size* pSize);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICGETTEXTEXTENT_NOTIMPLEMENTED)
	#define USE_SysGraphicGetTextExtent
	#define EXT_SysGraphicGetTextExtent
	#define GET_SysGraphicGetTextExtent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicGetTextExtent(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicGetTextExtent  FALSE
	#define EXP_SysGraphicGetTextExtent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicGetTextExtent
	#define EXT_SysGraphicGetTextExtent
	#define GET_SysGraphicGetTextExtent(fl)  CAL_CMGETAPI( "SysGraphicGetTextExtent" ) 
	#define CAL_SysGraphicGetTextExtent  SysGraphicGetTextExtent
	#define CHK_SysGraphicGetTextExtent  TRUE
	#define EXP_SysGraphicGetTextExtent  CAL_CMEXPAPI( "SysGraphicGetTextExtent" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicGetTextExtent
	#define EXT_SysGraphicGetTextExtent
	#define GET_SysGraphicGetTextExtent(fl)  CAL_CMGETAPI( "SysGraphicGetTextExtent" ) 
	#define CAL_SysGraphicGetTextExtent  SysGraphicGetTextExtent
	#define CHK_SysGraphicGetTextExtent  TRUE
	#define EXP_SysGraphicGetTextExtent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetTextExtent", (RTS_UINTPTR)SysGraphicGetTextExtent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicGetTextExtent
	#define EXT_SysGraphicSysGraphicGetTextExtent
	#define GET_SysGraphicSysGraphicGetTextExtent  ERR_OK
	#define CAL_SysGraphicSysGraphicGetTextExtent  SysGraphicGetTextExtent
	#define CHK_SysGraphicSysGraphicGetTextExtent  TRUE
	#define EXP_SysGraphicSysGraphicGetTextExtent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicGetTextExtent
	#define EXT_SysGraphicGetTextExtent
	#define GET_SysGraphicGetTextExtent(fl)  CAL_CMGETAPI( "SysGraphicGetTextExtent" ) 
	#define CAL_SysGraphicGetTextExtent  SysGraphicGetTextExtent
	#define CHK_SysGraphicGetTextExtent  TRUE
	#define EXP_SysGraphicGetTextExtent  CAL_CMEXPAPI( "SysGraphicGetTextExtent" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicGetTextExtent  PFSYSGRAPHICGETTEXTEXTENT pfSysGraphicGetTextExtent;
	#define EXT_SysGraphicGetTextExtent  extern PFSYSGRAPHICGETTEXTEXTENT pfSysGraphicGetTextExtent;
	#define GET_SysGraphicGetTextExtent(fl)  s_pfCMGetAPI2( "SysGraphicGetTextExtent", (RTS_VOID_FCTPTR *)&pfSysGraphicGetTextExtent, (fl), 0, 0)
	#define CAL_SysGraphicGetTextExtent  pfSysGraphicGetTextExtent
	#define CHK_SysGraphicGetTextExtent  (pfSysGraphicGetTextExtent != NULL)
	#define EXP_SysGraphicGetTextExtent   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetTextExtent", (RTS_UINTPTR)SysGraphicGetTextExtent, 0, 0) 
#endif


/**
 * <description>
 *  Function to get the height of the currently selected font.
 * </description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="piHeight" type="OUT">Height of the text</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicGetFontHeight(RTS_HANDLE hDC, RTS_I16* piHeight);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICGETFONTHEIGHT) (RTS_HANDLE hDC, RTS_I16* piHeight);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICGETFONTHEIGHT_NOTIMPLEMENTED)
	#define USE_SysGraphicGetFontHeight
	#define EXT_SysGraphicGetFontHeight
	#define GET_SysGraphicGetFontHeight(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicGetFontHeight(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicGetFontHeight  FALSE
	#define EXP_SysGraphicGetFontHeight  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicGetFontHeight
	#define EXT_SysGraphicGetFontHeight
	#define GET_SysGraphicGetFontHeight(fl)  CAL_CMGETAPI( "SysGraphicGetFontHeight" ) 
	#define CAL_SysGraphicGetFontHeight  SysGraphicGetFontHeight
	#define CHK_SysGraphicGetFontHeight  TRUE
	#define EXP_SysGraphicGetFontHeight  CAL_CMEXPAPI( "SysGraphicGetFontHeight" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicGetFontHeight
	#define EXT_SysGraphicGetFontHeight
	#define GET_SysGraphicGetFontHeight(fl)  CAL_CMGETAPI( "SysGraphicGetFontHeight" ) 
	#define CAL_SysGraphicGetFontHeight  SysGraphicGetFontHeight
	#define CHK_SysGraphicGetFontHeight  TRUE
	#define EXP_SysGraphicGetFontHeight  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetFontHeight", (RTS_UINTPTR)SysGraphicGetFontHeight, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicGetFontHeight
	#define EXT_SysGraphicSysGraphicGetFontHeight
	#define GET_SysGraphicSysGraphicGetFontHeight  ERR_OK
	#define CAL_SysGraphicSysGraphicGetFontHeight  SysGraphicGetFontHeight
	#define CHK_SysGraphicSysGraphicGetFontHeight  TRUE
	#define EXP_SysGraphicSysGraphicGetFontHeight  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicGetFontHeight
	#define EXT_SysGraphicGetFontHeight
	#define GET_SysGraphicGetFontHeight(fl)  CAL_CMGETAPI( "SysGraphicGetFontHeight" ) 
	#define CAL_SysGraphicGetFontHeight  SysGraphicGetFontHeight
	#define CHK_SysGraphicGetFontHeight  TRUE
	#define EXP_SysGraphicGetFontHeight  CAL_CMEXPAPI( "SysGraphicGetFontHeight" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicGetFontHeight  PFSYSGRAPHICGETFONTHEIGHT pfSysGraphicGetFontHeight;
	#define EXT_SysGraphicGetFontHeight  extern PFSYSGRAPHICGETFONTHEIGHT pfSysGraphicGetFontHeight;
	#define GET_SysGraphicGetFontHeight(fl)  s_pfCMGetAPI2( "SysGraphicGetFontHeight", (RTS_VOID_FCTPTR *)&pfSysGraphicGetFontHeight, (fl), 0, 0)
	#define CAL_SysGraphicGetFontHeight  pfSysGraphicGetFontHeight
	#define CHK_SysGraphicGetFontHeight  (pfSysGraphicGetFontHeight != NULL)
	#define EXP_SysGraphicGetFontHeight   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetFontHeight", (RTS_UINTPTR)SysGraphicGetFontHeight, 0, 0) 
#endif


/**
 * <description>
 *  Function to get the handle of the currently selected font.
 * </description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="phFont" type="OUT"> Pointer to get the font handle</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicGetFontHandle(RTS_HANDLE hDC, RTS_HANDLE* phFont);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICGETFONTHANDLE) (RTS_HANDLE hDC, RTS_HANDLE* phFont);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICGETFONTHANDLE_NOTIMPLEMENTED)
	#define USE_SysGraphicGetFontHandle
	#define EXT_SysGraphicGetFontHandle
	#define GET_SysGraphicGetFontHandle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicGetFontHandle(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicGetFontHandle  FALSE
	#define EXP_SysGraphicGetFontHandle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicGetFontHandle
	#define EXT_SysGraphicGetFontHandle
	#define GET_SysGraphicGetFontHandle(fl)  CAL_CMGETAPI( "SysGraphicGetFontHandle" ) 
	#define CAL_SysGraphicGetFontHandle  SysGraphicGetFontHandle
	#define CHK_SysGraphicGetFontHandle  TRUE
	#define EXP_SysGraphicGetFontHandle  CAL_CMEXPAPI( "SysGraphicGetFontHandle" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicGetFontHandle
	#define EXT_SysGraphicGetFontHandle
	#define GET_SysGraphicGetFontHandle(fl)  CAL_CMGETAPI( "SysGraphicGetFontHandle" ) 
	#define CAL_SysGraphicGetFontHandle  SysGraphicGetFontHandle
	#define CHK_SysGraphicGetFontHandle  TRUE
	#define EXP_SysGraphicGetFontHandle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetFontHandle", (RTS_UINTPTR)SysGraphicGetFontHandle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicGetFontHandle
	#define EXT_SysGraphicSysGraphicGetFontHandle
	#define GET_SysGraphicSysGraphicGetFontHandle  ERR_OK
	#define CAL_SysGraphicSysGraphicGetFontHandle  SysGraphicGetFontHandle
	#define CHK_SysGraphicSysGraphicGetFontHandle  TRUE
	#define EXP_SysGraphicSysGraphicGetFontHandle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicGetFontHandle
	#define EXT_SysGraphicGetFontHandle
	#define GET_SysGraphicGetFontHandle(fl)  CAL_CMGETAPI( "SysGraphicGetFontHandle" ) 
	#define CAL_SysGraphicGetFontHandle  SysGraphicGetFontHandle
	#define CHK_SysGraphicGetFontHandle  TRUE
	#define EXP_SysGraphicGetFontHandle  CAL_CMEXPAPI( "SysGraphicGetFontHandle" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicGetFontHandle  PFSYSGRAPHICGETFONTHANDLE pfSysGraphicGetFontHandle;
	#define EXT_SysGraphicGetFontHandle  extern PFSYSGRAPHICGETFONTHANDLE pfSysGraphicGetFontHandle;
	#define GET_SysGraphicGetFontHandle(fl)  s_pfCMGetAPI2( "SysGraphicGetFontHandle", (RTS_VOID_FCTPTR *)&pfSysGraphicGetFontHandle, (fl), 0, 0)
	#define CAL_SysGraphicGetFontHandle  pfSysGraphicGetFontHandle
	#define CHK_SysGraphicGetFontHandle  (pfSysGraphicGetFontHandle != NULL)
	#define EXP_SysGraphicGetFontHandle   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetFontHandle", (RTS_UINTPTR)SysGraphicGetFontHandle, 0, 0) 
#endif


/**
 * <description>Function to set the fill style of the following objects (i.e. the Brush in Win32)</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="ulFillFlags" type="IN">Fill flags. Defined in IEC-Code for Visualization</param>
 * <param name="ulFillColor" type="IN">Fill color. Defined in IEC-Code for Visualization</param>
 * <param name="phBrush" type="OUT">Pointer to get the brush handle</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicCreateBrush(RTS_HANDLE hDC, RTS_UI32 ulFillFlags, RTS_UI32 ulFillColor, RTS_HANDLE* phBrush);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICCREATEBRUSH) (RTS_HANDLE hDC, RTS_UI32 ulFillFlags, RTS_UI32 ulFillColor, RTS_HANDLE* phBrush);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCREATEBRUSH_NOTIMPLEMENTED)
	#define USE_SysGraphicCreateBrush
	#define EXT_SysGraphicCreateBrush
	#define GET_SysGraphicCreateBrush(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCreateBrush(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicCreateBrush  FALSE
	#define EXP_SysGraphicCreateBrush  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCreateBrush
	#define EXT_SysGraphicCreateBrush
	#define GET_SysGraphicCreateBrush(fl)  CAL_CMGETAPI( "SysGraphicCreateBrush" ) 
	#define CAL_SysGraphicCreateBrush  SysGraphicCreateBrush
	#define CHK_SysGraphicCreateBrush  TRUE
	#define EXP_SysGraphicCreateBrush  CAL_CMEXPAPI( "SysGraphicCreateBrush" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCreateBrush
	#define EXT_SysGraphicCreateBrush
	#define GET_SysGraphicCreateBrush(fl)  CAL_CMGETAPI( "SysGraphicCreateBrush" ) 
	#define CAL_SysGraphicCreateBrush  SysGraphicCreateBrush
	#define CHK_SysGraphicCreateBrush  TRUE
	#define EXP_SysGraphicCreateBrush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateBrush", (RTS_UINTPTR)SysGraphicCreateBrush, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCreateBrush
	#define EXT_SysGraphicSysGraphicCreateBrush
	#define GET_SysGraphicSysGraphicCreateBrush  ERR_OK
	#define CAL_SysGraphicSysGraphicCreateBrush  SysGraphicCreateBrush
	#define CHK_SysGraphicSysGraphicCreateBrush  TRUE
	#define EXP_SysGraphicSysGraphicCreateBrush  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCreateBrush
	#define EXT_SysGraphicCreateBrush
	#define GET_SysGraphicCreateBrush(fl)  CAL_CMGETAPI( "SysGraphicCreateBrush" ) 
	#define CAL_SysGraphicCreateBrush  SysGraphicCreateBrush
	#define CHK_SysGraphicCreateBrush  TRUE
	#define EXP_SysGraphicCreateBrush  CAL_CMEXPAPI( "SysGraphicCreateBrush" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCreateBrush  PFSYSGRAPHICCREATEBRUSH pfSysGraphicCreateBrush;
	#define EXT_SysGraphicCreateBrush  extern PFSYSGRAPHICCREATEBRUSH pfSysGraphicCreateBrush;
	#define GET_SysGraphicCreateBrush(fl)  s_pfCMGetAPI2( "SysGraphicCreateBrush", (RTS_VOID_FCTPTR *)&pfSysGraphicCreateBrush, (fl), 0, 0)
	#define CAL_SysGraphicCreateBrush  pfSysGraphicCreateBrush
	#define CHK_SysGraphicCreateBrush  (pfSysGraphicCreateBrush != NULL)
	#define EXP_SysGraphicCreateBrush   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateBrush", (RTS_UINTPTR)SysGraphicCreateBrush, 0, 0) 
#endif


/**
 * <description>Function to set the font for the following drawn texts</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hBrush" type="IN">Handle to the brush</param>
 * <param name="phOldBrush" type="OUT">Pointer to get the old brush handle. This pointer can be <c>null</c> if the
 *	old brush should not be returned. In this situation, you should take care that you still know a reference to this
 *	old brush to be able to release it after it is used!</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicSetBrush(RTS_HANDLE hDC, RTS_HANDLE hBrush, RTS_HANDLE* phOldBrush);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICSETBRUSH) (RTS_HANDLE hDC, RTS_HANDLE hBrush, RTS_HANDLE* phOldBrush);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICSETBRUSH_NOTIMPLEMENTED)
	#define USE_SysGraphicSetBrush
	#define EXT_SysGraphicSetBrush
	#define GET_SysGraphicSetBrush(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicSetBrush(p0,p1,p2) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicSetBrush  FALSE
	#define EXP_SysGraphicSetBrush  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicSetBrush
	#define EXT_SysGraphicSetBrush
	#define GET_SysGraphicSetBrush(fl)  CAL_CMGETAPI( "SysGraphicSetBrush" ) 
	#define CAL_SysGraphicSetBrush  SysGraphicSetBrush
	#define CHK_SysGraphicSetBrush  TRUE
	#define EXP_SysGraphicSetBrush  CAL_CMEXPAPI( "SysGraphicSetBrush" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicSetBrush
	#define EXT_SysGraphicSetBrush
	#define GET_SysGraphicSetBrush(fl)  CAL_CMGETAPI( "SysGraphicSetBrush" ) 
	#define CAL_SysGraphicSetBrush  SysGraphicSetBrush
	#define CHK_SysGraphicSetBrush  TRUE
	#define EXP_SysGraphicSetBrush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetBrush", (RTS_UINTPTR)SysGraphicSetBrush, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicSetBrush
	#define EXT_SysGraphicSysGraphicSetBrush
	#define GET_SysGraphicSysGraphicSetBrush  ERR_OK
	#define CAL_SysGraphicSysGraphicSetBrush  SysGraphicSetBrush
	#define CHK_SysGraphicSysGraphicSetBrush  TRUE
	#define EXP_SysGraphicSysGraphicSetBrush  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicSetBrush
	#define EXT_SysGraphicSetBrush
	#define GET_SysGraphicSetBrush(fl)  CAL_CMGETAPI( "SysGraphicSetBrush" ) 
	#define CAL_SysGraphicSetBrush  SysGraphicSetBrush
	#define CHK_SysGraphicSetBrush  TRUE
	#define EXP_SysGraphicSetBrush  CAL_CMEXPAPI( "SysGraphicSetBrush" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicSetBrush  PFSYSGRAPHICSETBRUSH pfSysGraphicSetBrush;
	#define EXT_SysGraphicSetBrush  extern PFSYSGRAPHICSETBRUSH pfSysGraphicSetBrush;
	#define GET_SysGraphicSetBrush(fl)  s_pfCMGetAPI2( "SysGraphicSetBrush", (RTS_VOID_FCTPTR *)&pfSysGraphicSetBrush, (fl), 0, 0)
	#define CAL_SysGraphicSetBrush  pfSysGraphicSetBrush
	#define CHK_SysGraphicSetBrush  (pfSysGraphicSetBrush != NULL)
	#define EXP_SysGraphicSetBrush   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetBrush", (RTS_UINTPTR)SysGraphicSetBrush, 0, 0) 
#endif


/**
 * <description>Function to free an earlier created font object</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hBrush" type="IN">Handle to the brush</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicFreeBrush(RTS_HANDLE hDC, RTS_HANDLE hBrush);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICFREEBRUSH) (RTS_HANDLE hDC, RTS_HANDLE hBrush);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICFREEBRUSH_NOTIMPLEMENTED)
	#define USE_SysGraphicFreeBrush
	#define EXT_SysGraphicFreeBrush
	#define GET_SysGraphicFreeBrush(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicFreeBrush(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicFreeBrush  FALSE
	#define EXP_SysGraphicFreeBrush  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicFreeBrush
	#define EXT_SysGraphicFreeBrush
	#define GET_SysGraphicFreeBrush(fl)  CAL_CMGETAPI( "SysGraphicFreeBrush" ) 
	#define CAL_SysGraphicFreeBrush  SysGraphicFreeBrush
	#define CHK_SysGraphicFreeBrush  TRUE
	#define EXP_SysGraphicFreeBrush  CAL_CMEXPAPI( "SysGraphicFreeBrush" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicFreeBrush
	#define EXT_SysGraphicFreeBrush
	#define GET_SysGraphicFreeBrush(fl)  CAL_CMGETAPI( "SysGraphicFreeBrush" ) 
	#define CAL_SysGraphicFreeBrush  SysGraphicFreeBrush
	#define CHK_SysGraphicFreeBrush  TRUE
	#define EXP_SysGraphicFreeBrush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFreeBrush", (RTS_UINTPTR)SysGraphicFreeBrush, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicFreeBrush
	#define EXT_SysGraphicSysGraphicFreeBrush
	#define GET_SysGraphicSysGraphicFreeBrush  ERR_OK
	#define CAL_SysGraphicSysGraphicFreeBrush  SysGraphicFreeBrush
	#define CHK_SysGraphicSysGraphicFreeBrush  TRUE
	#define EXP_SysGraphicSysGraphicFreeBrush  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicFreeBrush
	#define EXT_SysGraphicFreeBrush
	#define GET_SysGraphicFreeBrush(fl)  CAL_CMGETAPI( "SysGraphicFreeBrush" ) 
	#define CAL_SysGraphicFreeBrush  SysGraphicFreeBrush
	#define CHK_SysGraphicFreeBrush  TRUE
	#define EXP_SysGraphicFreeBrush  CAL_CMEXPAPI( "SysGraphicFreeBrush" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicFreeBrush  PFSYSGRAPHICFREEBRUSH pfSysGraphicFreeBrush;
	#define EXT_SysGraphicFreeBrush  extern PFSYSGRAPHICFREEBRUSH pfSysGraphicFreeBrush;
	#define GET_SysGraphicFreeBrush(fl)  s_pfCMGetAPI2( "SysGraphicFreeBrush", (RTS_VOID_FCTPTR *)&pfSysGraphicFreeBrush, (fl), 0, 0)
	#define CAL_SysGraphicFreeBrush  pfSysGraphicFreeBrush
	#define CHK_SysGraphicFreeBrush  (pfSysGraphicFreeBrush != NULL)
	#define EXP_SysGraphicFreeBrush   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFreeBrush", (RTS_UINTPTR)SysGraphicFreeBrush, 0, 0) 
#endif


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
RTS_RESULT CDECL SysGraphicCreateGradientBrush(RTS_HANDLE hDC, GradientData* gradient, RTS_Rectangle rectangle, RTS_HANDLE* phBrush);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICCREATEGRADIENTBRUSH) (RTS_HANDLE hDC, GradientData* gradient, RTS_Rectangle rectangle, RTS_HANDLE* phBrush);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCREATEGRADIENTBRUSH_NOTIMPLEMENTED)
	#define USE_SysGraphicCreateGradientBrush
	#define EXT_SysGraphicCreateGradientBrush
	#define GET_SysGraphicCreateGradientBrush(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCreateGradientBrush(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicCreateGradientBrush  FALSE
	#define EXP_SysGraphicCreateGradientBrush  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCreateGradientBrush
	#define EXT_SysGraphicCreateGradientBrush
	#define GET_SysGraphicCreateGradientBrush(fl)  CAL_CMGETAPI( "SysGraphicCreateGradientBrush" ) 
	#define CAL_SysGraphicCreateGradientBrush  SysGraphicCreateGradientBrush
	#define CHK_SysGraphicCreateGradientBrush  TRUE
	#define EXP_SysGraphicCreateGradientBrush  CAL_CMEXPAPI( "SysGraphicCreateGradientBrush" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCreateGradientBrush
	#define EXT_SysGraphicCreateGradientBrush
	#define GET_SysGraphicCreateGradientBrush(fl)  CAL_CMGETAPI( "SysGraphicCreateGradientBrush" ) 
	#define CAL_SysGraphicCreateGradientBrush  SysGraphicCreateGradientBrush
	#define CHK_SysGraphicCreateGradientBrush  TRUE
	#define EXP_SysGraphicCreateGradientBrush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateGradientBrush", (RTS_UINTPTR)SysGraphicCreateGradientBrush, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCreateGradientBrush
	#define EXT_SysGraphicSysGraphicCreateGradientBrush
	#define GET_SysGraphicSysGraphicCreateGradientBrush  ERR_OK
	#define CAL_SysGraphicSysGraphicCreateGradientBrush pISysGraphic->ISysGraphicCreateGradientBrush
	#define CHK_SysGraphicSysGraphicCreateGradientBrush (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicCreateGradientBrush  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCreateGradientBrush
	#define EXT_SysGraphicCreateGradientBrush
	#define GET_SysGraphicCreateGradientBrush(fl)  CAL_CMGETAPI( "SysGraphicCreateGradientBrush" ) 
	#define CAL_SysGraphicCreateGradientBrush pISysGraphic->ISysGraphicCreateGradientBrush
	#define CHK_SysGraphicCreateGradientBrush (pISysGraphic != NULL)
	#define EXP_SysGraphicCreateGradientBrush  CAL_CMEXPAPI( "SysGraphicCreateGradientBrush" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCreateGradientBrush  PFSYSGRAPHICCREATEGRADIENTBRUSH pfSysGraphicCreateGradientBrush;
	#define EXT_SysGraphicCreateGradientBrush  extern PFSYSGRAPHICCREATEGRADIENTBRUSH pfSysGraphicCreateGradientBrush;
	#define GET_SysGraphicCreateGradientBrush(fl)  s_pfCMGetAPI2( "SysGraphicCreateGradientBrush", (RTS_VOID_FCTPTR *)&pfSysGraphicCreateGradientBrush, (fl), 0, 0)
	#define CAL_SysGraphicCreateGradientBrush  pfSysGraphicCreateGradientBrush
	#define CHK_SysGraphicCreateGradientBrush  (pfSysGraphicCreateGradientBrush != NULL)
	#define EXP_SysGraphicCreateGradientBrush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateGradientBrush", (RTS_UINTPTR)SysGraphicCreateGradientBrush, 0, 0) 
#endif




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
RTS_RESULT CDECL SysGraphicCreatePatternBrush(RTS_HANDLE hDC, RTS_UI16 patternType, RTS_UI32 color, RTS_HANDLE* phBrush);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICCREATEPATTERNBRUSH) (RTS_HANDLE hDC, RTS_UI16 patternType, RTS_UI32 color, RTS_HANDLE* phBrush);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCREATEPATTERNBRUSH_NOTIMPLEMENTED)
	#define USE_SysGraphicCreatePatternBrush
	#define EXT_SysGraphicCreatePatternBrush
	#define GET_SysGraphicCreatePatternBrush(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCreatePatternBrush(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicCreatePatternBrush  FALSE
	#define EXP_SysGraphicCreatePatternBrush  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCreatePatternBrush
	#define EXT_SysGraphicCreatePatternBrush
	#define GET_SysGraphicCreatePatternBrush(fl)  CAL_CMGETAPI( "SysGraphicCreatePatternBrush" ) 
	#define CAL_SysGraphicCreatePatternBrush  SysGraphicCreatePatternBrush
	#define CHK_SysGraphicCreatePatternBrush  TRUE
	#define EXP_SysGraphicCreatePatternBrush  CAL_CMEXPAPI( "SysGraphicCreatePatternBrush" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCreatePatternBrush
	#define EXT_SysGraphicCreatePatternBrush
	#define GET_SysGraphicCreatePatternBrush(fl)  CAL_CMGETAPI( "SysGraphicCreatePatternBrush" ) 
	#define CAL_SysGraphicCreatePatternBrush  SysGraphicCreatePatternBrush
	#define CHK_SysGraphicCreatePatternBrush  TRUE
	#define EXP_SysGraphicCreatePatternBrush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreatePatternBrush", (RTS_UINTPTR)SysGraphicCreatePatternBrush, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCreatePatternBrush
	#define EXT_SysGraphicSysGraphicCreatePatternBrush
	#define GET_SysGraphicSysGraphicCreatePatternBrush  ERR_OK
	#define CAL_SysGraphicSysGraphicCreatePatternBrush pISysGraphic->ISysGraphicCreatePatternBrush
	#define CHK_SysGraphicSysGraphicCreatePatternBrush (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicCreatePatternBrush  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCreatePatternBrush
	#define EXT_SysGraphicCreatePatternBrush
	#define GET_SysGraphicCreatePatternBrush(fl)  CAL_CMGETAPI( "SysGraphicCreatePatternBrush" ) 
	#define CAL_SysGraphicCreatePatternBrush pISysGraphic->ISysGraphicCreatePatternBrush
	#define CHK_SysGraphicCreatePatternBrush (pISysGraphic != NULL)
	#define EXP_SysGraphicCreatePatternBrush  CAL_CMEXPAPI( "SysGraphicCreatePatternBrush" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCreatePatternBrush  PFSYSGRAPHICCREATEPATTERNBRUSH pfSysGraphicCreatePatternBrush;
	#define EXT_SysGraphicCreatePatternBrush  extern PFSYSGRAPHICCREATEPATTERNBRUSH pfSysGraphicCreatePatternBrush;
	#define GET_SysGraphicCreatePatternBrush(fl)  s_pfCMGetAPI2( "SysGraphicCreatePatternBrush", (RTS_VOID_FCTPTR *)&pfSysGraphicCreatePatternBrush, (fl), 0, 0)
	#define CAL_SysGraphicCreatePatternBrush  pfSysGraphicCreatePatternBrush
	#define CHK_SysGraphicCreatePatternBrush  (pfSysGraphicCreatePatternBrush != NULL)
	#define EXP_SysGraphicCreatePatternBrush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreatePatternBrush", (RTS_UINTPTR)SysGraphicCreatePatternBrush, 0, 0) 
#endif




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
RTS_RESULT CDECL SysGraphicCreatePenDetailed(RTS_HANDLE hDC, RTS_I16 nLineWidth, RTS_UI32 ulLineFlags, 
										RTS_UI32 ulLineColor, RTS_I16 nLineCapFlag, RTS_I16 nLineJoinFlag, 
										RTS_REAL32 rMiterLimit, RTS_HANDLE* phPen);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICCREATEPENDETAILED) (RTS_HANDLE hDC, RTS_I16 nLineWidth, RTS_UI32 ulLineFlags, 
										RTS_UI32 ulLineColor, RTS_I16 nLineCapFlag, RTS_I16 nLineJoinFlag, 
										RTS_REAL32 rMiterLimit, RTS_HANDLE* phPen);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCREATEPENDETAILED_NOTIMPLEMENTED)
	#define USE_SysGraphicCreatePenDetailed
	#define EXT_SysGraphicCreatePenDetailed
	#define GET_SysGraphicCreatePenDetailed(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCreatePenDetailed() (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicCreatePenDetailed  FALSE
	#define EXP_SysGraphicCreatePenDetailed  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCreatePenDetailed
	#define EXT_SysGraphicCreatePenDetailed
	#define GET_SysGraphicCreatePenDetailed(fl)  CAL_CMGETAPI( "SysGraphicCreatePenDetailed" ) 
	#define CAL_SysGraphicCreatePenDetailed  SysGraphicCreatePenDetailed
	#define CHK_SysGraphicCreatePenDetailed  TRUE
	#define EXP_SysGraphicCreatePenDetailed  CAL_CMEXPAPI( "SysGraphicCreatePenDetailed" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCreatePenDetailed
	#define EXT_SysGraphicCreatePenDetailed
	#define GET_SysGraphicCreatePenDetailed(fl)  CAL_CMGETAPI( "SysGraphicCreatePenDetailed" ) 
	#define CAL_SysGraphicCreatePenDetailed  SysGraphicCreatePenDetailed
	#define CHK_SysGraphicCreatePenDetailed  TRUE
	#define EXP_SysGraphicCreatePenDetailed  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreatePenDetailed", (RTS_UINTPTR)SysGraphicCreatePenDetailed, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCreatePenDetailed
	#define EXT_SysGraphicSysGraphicCreatePenDetailed
	#define GET_SysGraphicSysGraphicCreatePenDetailed  ERR_OK
	#define CAL_SysGraphicSysGraphicCreatePenDetailed  SysGraphicCreatePenDetailed
	#define CHK_SysGraphicSysGraphicCreatePenDetailed  TRUE
	#define EXP_SysGraphicSysGraphicCreatePenDetailed  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCreatePenDetailed
	#define EXT_SysGraphicCreatePenDetailed
	#define GET_SysGraphicCreatePenDetailed(fl)  CAL_CMGETAPI( "SysGraphicCreatePenDetailed" ) 
	#define CAL_SysGraphicCreatePenDetailed  SysGraphicCreatePenDetailed
	#define CHK_SysGraphicCreatePenDetailed  TRUE
	#define EXP_SysGraphicCreatePenDetailed  CAL_CMEXPAPI( "SysGraphicCreatePenDetailed" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCreatePenDetailed  PFSYSGRAPHICCREATEPENDETAILED pfSysGraphicCreatePenDetailed;
	#define EXT_SysGraphicCreatePenDetailed  extern PFSYSGRAPHICCREATEPENDETAILED pfSysGraphicCreatePenDetailed;
	#define GET_SysGraphicCreatePenDetailed(fl)  s_pfCMGetAPI2( "SysGraphicCreatePenDetailed", (RTS_VOID_FCTPTR *)&pfSysGraphicCreatePenDetailed, (fl), 0, 0)
	#define CAL_SysGraphicCreatePenDetailed  pfSysGraphicCreatePenDetailed
	#define CHK_SysGraphicCreatePenDetailed  (pfSysGraphicCreatePenDetailed != NULL)
	#define EXP_SysGraphicCreatePenDetailed   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreatePenDetailed", (RTS_UINTPTR)SysGraphicCreatePenDetailed, 0, 0) 
#endif


/**
 * <description>Function to set the line style of the following objects (i.e. the Pen in Win32)</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="nLineWidth" type="IN">Width of the line as in Win32</param>
 * <param name="ulLineFlags" type="IN">Line flags.  Defined in IEC-Code for Visualization</param>
 * <param name="ulLineColor" type="IN">Line color.  Defined in IEC-Code for Visualization</param>
 * <param name="phPen" type="OUT">Pointer to get the pen handle</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicCreatePen(RTS_HANDLE hDC, RTS_I16 nLineWidth, RTS_UI32 ulLineFlags, 
										RTS_UI32 ulLineColor, RTS_HANDLE* phPen);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICCREATEPEN) (RTS_HANDLE hDC, RTS_I16 nLineWidth, RTS_UI32 ulLineFlags, 
										RTS_UI32 ulLineColor, RTS_HANDLE* phPen);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCREATEPEN_NOTIMPLEMENTED)
	#define USE_SysGraphicCreatePen
	#define EXT_SysGraphicCreatePen
	#define GET_SysGraphicCreatePen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCreatePen() (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicCreatePen  FALSE
	#define EXP_SysGraphicCreatePen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCreatePen
	#define EXT_SysGraphicCreatePen
	#define GET_SysGraphicCreatePen(fl)  CAL_CMGETAPI( "SysGraphicCreatePen" ) 
	#define CAL_SysGraphicCreatePen  SysGraphicCreatePen
	#define CHK_SysGraphicCreatePen  TRUE
	#define EXP_SysGraphicCreatePen  CAL_CMEXPAPI( "SysGraphicCreatePen" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCreatePen
	#define EXT_SysGraphicCreatePen
	#define GET_SysGraphicCreatePen(fl)  CAL_CMGETAPI( "SysGraphicCreatePen" ) 
	#define CAL_SysGraphicCreatePen  SysGraphicCreatePen
	#define CHK_SysGraphicCreatePen  TRUE
	#define EXP_SysGraphicCreatePen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreatePen", (RTS_UINTPTR)SysGraphicCreatePen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCreatePen
	#define EXT_SysGraphicSysGraphicCreatePen
	#define GET_SysGraphicSysGraphicCreatePen  ERR_OK
	#define CAL_SysGraphicSysGraphicCreatePen  SysGraphicCreatePen
	#define CHK_SysGraphicSysGraphicCreatePen  TRUE
	#define EXP_SysGraphicSysGraphicCreatePen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCreatePen
	#define EXT_SysGraphicCreatePen
	#define GET_SysGraphicCreatePen(fl)  CAL_CMGETAPI( "SysGraphicCreatePen" ) 
	#define CAL_SysGraphicCreatePen  SysGraphicCreatePen
	#define CHK_SysGraphicCreatePen  TRUE
	#define EXP_SysGraphicCreatePen  CAL_CMEXPAPI( "SysGraphicCreatePen" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCreatePen  PFSYSGRAPHICCREATEPEN pfSysGraphicCreatePen;
	#define EXT_SysGraphicCreatePen  extern PFSYSGRAPHICCREATEPEN pfSysGraphicCreatePen;
	#define GET_SysGraphicCreatePen(fl)  s_pfCMGetAPI2( "SysGraphicCreatePen", (RTS_VOID_FCTPTR *)&pfSysGraphicCreatePen, (fl), 0, 0)
	#define CAL_SysGraphicCreatePen  pfSysGraphicCreatePen
	#define CHK_SysGraphicCreatePen  (pfSysGraphicCreatePen != NULL)
	#define EXP_SysGraphicCreatePen   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreatePen", (RTS_UINTPTR)SysGraphicCreatePen, 0, 0) 
#endif


/**
 * <description>Function to set the font for the following drawn texts</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hPen" type="IN">Handle to the new pen</param>
 * <param name="phOldPen" type="OUT">Pointer to get the previous set pen. This pointer can be <c>null</c> if the
 *	old pen should not be returned. In this situation, you should take care that you still know a reference to this
 *	old pen to be able to release it after it is used!</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicSetPen(RTS_HANDLE hDC, RTS_HANDLE hPen, RTS_HANDLE* phOldPen);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICSETPEN) (RTS_HANDLE hDC, RTS_HANDLE hPen, RTS_HANDLE* phOldPen);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICSETPEN_NOTIMPLEMENTED)
	#define USE_SysGraphicSetPen
	#define EXT_SysGraphicSetPen
	#define GET_SysGraphicSetPen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicSetPen(p0,p1,p2) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicSetPen  FALSE
	#define EXP_SysGraphicSetPen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicSetPen
	#define EXT_SysGraphicSetPen
	#define GET_SysGraphicSetPen(fl)  CAL_CMGETAPI( "SysGraphicSetPen" ) 
	#define CAL_SysGraphicSetPen  SysGraphicSetPen
	#define CHK_SysGraphicSetPen  TRUE
	#define EXP_SysGraphicSetPen  CAL_CMEXPAPI( "SysGraphicSetPen" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicSetPen
	#define EXT_SysGraphicSetPen
	#define GET_SysGraphicSetPen(fl)  CAL_CMGETAPI( "SysGraphicSetPen" ) 
	#define CAL_SysGraphicSetPen  SysGraphicSetPen
	#define CHK_SysGraphicSetPen  TRUE
	#define EXP_SysGraphicSetPen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetPen", (RTS_UINTPTR)SysGraphicSetPen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicSetPen
	#define EXT_SysGraphicSysGraphicSetPen
	#define GET_SysGraphicSysGraphicSetPen  ERR_OK
	#define CAL_SysGraphicSysGraphicSetPen  SysGraphicSetPen
	#define CHK_SysGraphicSysGraphicSetPen  TRUE
	#define EXP_SysGraphicSysGraphicSetPen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicSetPen
	#define EXT_SysGraphicSetPen
	#define GET_SysGraphicSetPen(fl)  CAL_CMGETAPI( "SysGraphicSetPen" ) 
	#define CAL_SysGraphicSetPen  SysGraphicSetPen
	#define CHK_SysGraphicSetPen  TRUE
	#define EXP_SysGraphicSetPen  CAL_CMEXPAPI( "SysGraphicSetPen" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicSetPen  PFSYSGRAPHICSETPEN pfSysGraphicSetPen;
	#define EXT_SysGraphicSetPen  extern PFSYSGRAPHICSETPEN pfSysGraphicSetPen;
	#define GET_SysGraphicSetPen(fl)  s_pfCMGetAPI2( "SysGraphicSetPen", (RTS_VOID_FCTPTR *)&pfSysGraphicSetPen, (fl), 0, 0)
	#define CAL_SysGraphicSetPen  pfSysGraphicSetPen
	#define CHK_SysGraphicSetPen  (pfSysGraphicSetPen != NULL)
	#define EXP_SysGraphicSetPen   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetPen", (RTS_UINTPTR)SysGraphicSetPen, 0, 0) 
#endif


/**
 * <description>Function to free a earlier created font object</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hPen" type="IN">Handle to the new pen</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicFreePen(RTS_HANDLE hDC, RTS_HANDLE hPen);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICFREEPEN) (RTS_HANDLE hDC, RTS_HANDLE hPen);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICFREEPEN_NOTIMPLEMENTED)
	#define USE_SysGraphicFreePen
	#define EXT_SysGraphicFreePen
	#define GET_SysGraphicFreePen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicFreePen(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicFreePen  FALSE
	#define EXP_SysGraphicFreePen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicFreePen
	#define EXT_SysGraphicFreePen
	#define GET_SysGraphicFreePen(fl)  CAL_CMGETAPI( "SysGraphicFreePen" ) 
	#define CAL_SysGraphicFreePen  SysGraphicFreePen
	#define CHK_SysGraphicFreePen  TRUE
	#define EXP_SysGraphicFreePen  CAL_CMEXPAPI( "SysGraphicFreePen" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicFreePen
	#define EXT_SysGraphicFreePen
	#define GET_SysGraphicFreePen(fl)  CAL_CMGETAPI( "SysGraphicFreePen" ) 
	#define CAL_SysGraphicFreePen  SysGraphicFreePen
	#define CHK_SysGraphicFreePen  TRUE
	#define EXP_SysGraphicFreePen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFreePen", (RTS_UINTPTR)SysGraphicFreePen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicFreePen
	#define EXT_SysGraphicSysGraphicFreePen
	#define GET_SysGraphicSysGraphicFreePen  ERR_OK
	#define CAL_SysGraphicSysGraphicFreePen  SysGraphicFreePen
	#define CHK_SysGraphicSysGraphicFreePen  TRUE
	#define EXP_SysGraphicSysGraphicFreePen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicFreePen
	#define EXT_SysGraphicFreePen
	#define GET_SysGraphicFreePen(fl)  CAL_CMGETAPI( "SysGraphicFreePen" ) 
	#define CAL_SysGraphicFreePen  SysGraphicFreePen
	#define CHK_SysGraphicFreePen  TRUE
	#define EXP_SysGraphicFreePen  CAL_CMEXPAPI( "SysGraphicFreePen" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicFreePen  PFSYSGRAPHICFREEPEN pfSysGraphicFreePen;
	#define EXT_SysGraphicFreePen  extern PFSYSGRAPHICFREEPEN pfSysGraphicFreePen;
	#define GET_SysGraphicFreePen(fl)  s_pfCMGetAPI2( "SysGraphicFreePen", (RTS_VOID_FCTPTR *)&pfSysGraphicFreePen, (fl), 0, 0)
	#define CAL_SysGraphicFreePen  pfSysGraphicFreePen
	#define CHK_SysGraphicFreePen  (pfSysGraphicFreePen != NULL)
	#define EXP_SysGraphicFreePen   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFreePen", (RTS_UINTPTR)SysGraphicFreePen, 0, 0) 
#endif


/**
 * <description>Function to create a font object(i.e. the Font in Win32)</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="pszFontName" type="IN">Name of the font that should be set</param>
 * <param name="nFontSize" type="IN">Size of the font as in Win32</param>
 * <param name="phFont" type="OUT">Pointer to get the font handle</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicCreateFont(RTS_HANDLE hDC, char* pszFontName, RTS_I16 nFontSize, RTS_UI32 ulFontFlags, RTS_HANDLE* phFont);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICCREATEFONT) (RTS_HANDLE hDC, char* pszFontName, RTS_I16 nFontSize, RTS_UI32 ulFontFlags, RTS_HANDLE* phFont);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCREATEFONT_NOTIMPLEMENTED)
	#define USE_SysGraphicCreateFont
	#define EXT_SysGraphicCreateFont
	#define GET_SysGraphicCreateFont(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCreateFont(p0,p1,p2,p3,p4) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicCreateFont  FALSE
	#define EXP_SysGraphicCreateFont  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCreateFont
	#define EXT_SysGraphicCreateFont
	#define GET_SysGraphicCreateFont(fl)  CAL_CMGETAPI( "SysGraphicCreateFont" ) 
	#define CAL_SysGraphicCreateFont  SysGraphicCreateFont
	#define CHK_SysGraphicCreateFont  TRUE
	#define EXP_SysGraphicCreateFont  CAL_CMEXPAPI( "SysGraphicCreateFont" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCreateFont
	#define EXT_SysGraphicCreateFont
	#define GET_SysGraphicCreateFont(fl)  CAL_CMGETAPI( "SysGraphicCreateFont" ) 
	#define CAL_SysGraphicCreateFont  SysGraphicCreateFont
	#define CHK_SysGraphicCreateFont  TRUE
	#define EXP_SysGraphicCreateFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateFont", (RTS_UINTPTR)SysGraphicCreateFont, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCreateFont
	#define EXT_SysGraphicSysGraphicCreateFont
	#define GET_SysGraphicSysGraphicCreateFont  ERR_OK
	#define CAL_SysGraphicSysGraphicCreateFont  SysGraphicCreateFont
	#define CHK_SysGraphicSysGraphicCreateFont  TRUE
	#define EXP_SysGraphicSysGraphicCreateFont  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCreateFont
	#define EXT_SysGraphicCreateFont
	#define GET_SysGraphicCreateFont(fl)  CAL_CMGETAPI( "SysGraphicCreateFont" ) 
	#define CAL_SysGraphicCreateFont  SysGraphicCreateFont
	#define CHK_SysGraphicCreateFont  TRUE
	#define EXP_SysGraphicCreateFont  CAL_CMEXPAPI( "SysGraphicCreateFont" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCreateFont  PFSYSGRAPHICCREATEFONT pfSysGraphicCreateFont;
	#define EXT_SysGraphicCreateFont  extern PFSYSGRAPHICCREATEFONT pfSysGraphicCreateFont;
	#define GET_SysGraphicCreateFont(fl)  s_pfCMGetAPI2( "SysGraphicCreateFont", (RTS_VOID_FCTPTR *)&pfSysGraphicCreateFont, (fl), 0, 0)
	#define CAL_SysGraphicCreateFont  pfSysGraphicCreateFont
	#define CHK_SysGraphicCreateFont  (pfSysGraphicCreateFont != NULL)
	#define EXP_SysGraphicCreateFont   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateFont", (RTS_UINTPTR)SysGraphicCreateFont, 0, 0) 
#endif


/**
 * <description>Function to free an earlier created font object</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hFont" type="IN">Handle to the font object</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicFreeFont(RTS_HANDLE hDC, RTS_HANDLE hFont);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICFREEFONT) (RTS_HANDLE hDC, RTS_HANDLE hFont);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICFREEFONT_NOTIMPLEMENTED)
	#define USE_SysGraphicFreeFont
	#define EXT_SysGraphicFreeFont
	#define GET_SysGraphicFreeFont(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicFreeFont(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicFreeFont  FALSE
	#define EXP_SysGraphicFreeFont  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicFreeFont
	#define EXT_SysGraphicFreeFont
	#define GET_SysGraphicFreeFont(fl)  CAL_CMGETAPI( "SysGraphicFreeFont" ) 
	#define CAL_SysGraphicFreeFont  SysGraphicFreeFont
	#define CHK_SysGraphicFreeFont  TRUE
	#define EXP_SysGraphicFreeFont  CAL_CMEXPAPI( "SysGraphicFreeFont" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicFreeFont
	#define EXT_SysGraphicFreeFont
	#define GET_SysGraphicFreeFont(fl)  CAL_CMGETAPI( "SysGraphicFreeFont" ) 
	#define CAL_SysGraphicFreeFont  SysGraphicFreeFont
	#define CHK_SysGraphicFreeFont  TRUE
	#define EXP_SysGraphicFreeFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFreeFont", (RTS_UINTPTR)SysGraphicFreeFont, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicFreeFont
	#define EXT_SysGraphicSysGraphicFreeFont
	#define GET_SysGraphicSysGraphicFreeFont  ERR_OK
	#define CAL_SysGraphicSysGraphicFreeFont  SysGraphicFreeFont
	#define CHK_SysGraphicSysGraphicFreeFont  TRUE
	#define EXP_SysGraphicSysGraphicFreeFont  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicFreeFont
	#define EXT_SysGraphicFreeFont
	#define GET_SysGraphicFreeFont(fl)  CAL_CMGETAPI( "SysGraphicFreeFont" ) 
	#define CAL_SysGraphicFreeFont  SysGraphicFreeFont
	#define CHK_SysGraphicFreeFont  TRUE
	#define EXP_SysGraphicFreeFont  CAL_CMEXPAPI( "SysGraphicFreeFont" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicFreeFont  PFSYSGRAPHICFREEFONT pfSysGraphicFreeFont;
	#define EXT_SysGraphicFreeFont  extern PFSYSGRAPHICFREEFONT pfSysGraphicFreeFont;
	#define GET_SysGraphicFreeFont(fl)  s_pfCMGetAPI2( "SysGraphicFreeFont", (RTS_VOID_FCTPTR *)&pfSysGraphicFreeFont, (fl), 0, 0)
	#define CAL_SysGraphicFreeFont  pfSysGraphicFreeFont
	#define CHK_SysGraphicFreeFont  (pfSysGraphicFreeFont != NULL)
	#define EXP_SysGraphicFreeFont   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFreeFont", (RTS_UINTPTR)SysGraphicFreeFont, 0, 0) 
#endif


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
RTS_RESULT CDECL SysGraphicSetFont(RTS_HANDLE hDC, RTS_HANDLE hFont, RTS_UI32 ulFontColor, RTS_HANDLE* phOldFont);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICSETFONT) (RTS_HANDLE hDC, RTS_HANDLE hFont, RTS_UI32 ulFontColor, RTS_HANDLE* phOldFont);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICSETFONT_NOTIMPLEMENTED)
	#define USE_SysGraphicSetFont
	#define EXT_SysGraphicSetFont
	#define GET_SysGraphicSetFont(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicSetFont(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicSetFont  FALSE
	#define EXP_SysGraphicSetFont  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicSetFont
	#define EXT_SysGraphicSetFont
	#define GET_SysGraphicSetFont(fl)  CAL_CMGETAPI( "SysGraphicSetFont" ) 
	#define CAL_SysGraphicSetFont  SysGraphicSetFont
	#define CHK_SysGraphicSetFont  TRUE
	#define EXP_SysGraphicSetFont  CAL_CMEXPAPI( "SysGraphicSetFont" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicSetFont
	#define EXT_SysGraphicSetFont
	#define GET_SysGraphicSetFont(fl)  CAL_CMGETAPI( "SysGraphicSetFont" ) 
	#define CAL_SysGraphicSetFont  SysGraphicSetFont
	#define CHK_SysGraphicSetFont  TRUE
	#define EXP_SysGraphicSetFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetFont", (RTS_UINTPTR)SysGraphicSetFont, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicSetFont
	#define EXT_SysGraphicSysGraphicSetFont
	#define GET_SysGraphicSysGraphicSetFont  ERR_OK
	#define CAL_SysGraphicSysGraphicSetFont  SysGraphicSetFont
	#define CHK_SysGraphicSysGraphicSetFont  TRUE
	#define EXP_SysGraphicSysGraphicSetFont  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicSetFont
	#define EXT_SysGraphicSetFont
	#define GET_SysGraphicSetFont(fl)  CAL_CMGETAPI( "SysGraphicSetFont" ) 
	#define CAL_SysGraphicSetFont  SysGraphicSetFont
	#define CHK_SysGraphicSetFont  TRUE
	#define EXP_SysGraphicSetFont  CAL_CMEXPAPI( "SysGraphicSetFont" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicSetFont  PFSYSGRAPHICSETFONT pfSysGraphicSetFont;
	#define EXT_SysGraphicSetFont  extern PFSYSGRAPHICSETFONT pfSysGraphicSetFont;
	#define GET_SysGraphicSetFont(fl)  s_pfCMGetAPI2( "SysGraphicSetFont", (RTS_VOID_FCTPTR *)&pfSysGraphicSetFont, (fl), 0, 0)
	#define CAL_SysGraphicSetFont  pfSysGraphicSetFont
	#define CHK_SysGraphicSetFont  (pfSysGraphicSetFont != NULL)
	#define EXP_SysGraphicSetFont   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetFont", (RTS_UINTPTR)SysGraphicSetFont, 0, 0) 
#endif


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
RTS_RESULT CDECL SysGraphicSetFont2(RTS_HANDLE hDC, RTS_HANDLE hFont, RTS_UI32 ulFontColor, RTS_HANDLE* phOldFont, RTS_UI32* pulOldFontColor);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICSETFONT2) (RTS_HANDLE hDC, RTS_HANDLE hFont, RTS_UI32 ulFontColor, RTS_HANDLE* phOldFont, RTS_UI32* pulOldFontColor);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICSETFONT2_NOTIMPLEMENTED)
	#define USE_SysGraphicSetFont2
	#define EXT_SysGraphicSetFont2
	#define GET_SysGraphicSetFont2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicSetFont2(p0,p1,p2,p3,p4) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicSetFont2  FALSE
	#define EXP_SysGraphicSetFont2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicSetFont2
	#define EXT_SysGraphicSetFont2
	#define GET_SysGraphicSetFont2(fl)  CAL_CMGETAPI( "SysGraphicSetFont2" ) 
	#define CAL_SysGraphicSetFont2  SysGraphicSetFont2
	#define CHK_SysGraphicSetFont2  TRUE
	#define EXP_SysGraphicSetFont2  CAL_CMEXPAPI( "SysGraphicSetFont2" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicSetFont2
	#define EXT_SysGraphicSetFont2
	#define GET_SysGraphicSetFont2(fl)  CAL_CMGETAPI( "SysGraphicSetFont2" ) 
	#define CAL_SysGraphicSetFont2  SysGraphicSetFont2
	#define CHK_SysGraphicSetFont2  TRUE
	#define EXP_SysGraphicSetFont2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetFont2", (RTS_UINTPTR)SysGraphicSetFont2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicSetFont2
	#define EXT_SysGraphicSysGraphicSetFont2
	#define GET_SysGraphicSysGraphicSetFont2  ERR_OK
	#define CAL_SysGraphicSysGraphicSetFont2  SysGraphicSetFont2
	#define CHK_SysGraphicSysGraphicSetFont2  TRUE
	#define EXP_SysGraphicSysGraphicSetFont2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicSetFont2
	#define EXT_SysGraphicSetFont2
	#define GET_SysGraphicSetFont2(fl)  CAL_CMGETAPI( "SysGraphicSetFont2" ) 
	#define CAL_SysGraphicSetFont2  SysGraphicSetFont2
	#define CHK_SysGraphicSetFont2  TRUE
	#define EXP_SysGraphicSetFont2  CAL_CMEXPAPI( "SysGraphicSetFont2" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicSetFont2  PFSYSGRAPHICSETFONT2 pfSysGraphicSetFont2;
	#define EXT_SysGraphicSetFont2  extern PFSYSGRAPHICSETFONT2 pfSysGraphicSetFont2;
	#define GET_SysGraphicSetFont2(fl)  s_pfCMGetAPI2( "SysGraphicSetFont2", (RTS_VOID_FCTPTR *)&pfSysGraphicSetFont2, (fl), 0, 0)
	#define CAL_SysGraphicSetFont2  pfSysGraphicSetFont2
	#define CHK_SysGraphicSetFont2  (pfSysGraphicSetFont2 != NULL)
	#define EXP_SysGraphicSetFont2   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetFont2", (RTS_UINTPTR)SysGraphicSetFont2, 0, 0) 
#endif


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
RTS_RESULT CDECL SysGraphicCreateBitmap(RTS_HANDLE hDC, const char* pszBmpPath, RTS_UI32 ulTransparentColor, RTS_UI32 ulFlags, RTS_HANDLE* phBitmap);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICCREATEBITMAP) (RTS_HANDLE hDC, const char* pszBmpPath, RTS_UI32 ulTransparentColor, RTS_UI32 ulFlags, RTS_HANDLE* phBitmap);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCREATEBITMAP_NOTIMPLEMENTED)
	#define USE_SysGraphicCreateBitmap
	#define EXT_SysGraphicCreateBitmap
	#define GET_SysGraphicCreateBitmap(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCreateBitmap(p0,p1,p2,p3,p4) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicCreateBitmap  FALSE
	#define EXP_SysGraphicCreateBitmap  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCreateBitmap
	#define EXT_SysGraphicCreateBitmap
	#define GET_SysGraphicCreateBitmap(fl)  CAL_CMGETAPI( "SysGraphicCreateBitmap" ) 
	#define CAL_SysGraphicCreateBitmap  SysGraphicCreateBitmap
	#define CHK_SysGraphicCreateBitmap  TRUE
	#define EXP_SysGraphicCreateBitmap  CAL_CMEXPAPI( "SysGraphicCreateBitmap" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCreateBitmap
	#define EXT_SysGraphicCreateBitmap
	#define GET_SysGraphicCreateBitmap(fl)  CAL_CMGETAPI( "SysGraphicCreateBitmap" ) 
	#define CAL_SysGraphicCreateBitmap  SysGraphicCreateBitmap
	#define CHK_SysGraphicCreateBitmap  TRUE
	#define EXP_SysGraphicCreateBitmap  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateBitmap", (RTS_UINTPTR)SysGraphicCreateBitmap, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCreateBitmap
	#define EXT_SysGraphicSysGraphicCreateBitmap
	#define GET_SysGraphicSysGraphicCreateBitmap  ERR_OK
	#define CAL_SysGraphicSysGraphicCreateBitmap  SysGraphicCreateBitmap
	#define CHK_SysGraphicSysGraphicCreateBitmap  TRUE
	#define EXP_SysGraphicSysGraphicCreateBitmap  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCreateBitmap
	#define EXT_SysGraphicCreateBitmap
	#define GET_SysGraphicCreateBitmap(fl)  CAL_CMGETAPI( "SysGraphicCreateBitmap" ) 
	#define CAL_SysGraphicCreateBitmap  SysGraphicCreateBitmap
	#define CHK_SysGraphicCreateBitmap  TRUE
	#define EXP_SysGraphicCreateBitmap  CAL_CMEXPAPI( "SysGraphicCreateBitmap" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCreateBitmap  PFSYSGRAPHICCREATEBITMAP pfSysGraphicCreateBitmap;
	#define EXT_SysGraphicCreateBitmap  extern PFSYSGRAPHICCREATEBITMAP pfSysGraphicCreateBitmap;
	#define GET_SysGraphicCreateBitmap(fl)  s_pfCMGetAPI2( "SysGraphicCreateBitmap", (RTS_VOID_FCTPTR *)&pfSysGraphicCreateBitmap, (fl), 0, 0)
	#define CAL_SysGraphicCreateBitmap  pfSysGraphicCreateBitmap
	#define CHK_SysGraphicCreateBitmap  (pfSysGraphicCreateBitmap != NULL)
	#define EXP_SysGraphicCreateBitmap   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateBitmap", (RTS_UINTPTR)SysGraphicCreateBitmap, 0, 0) 
#endif


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
RTS_RESULT CDECL SysGraphicDrawBitmap(RTS_HANDLE hDC, RTS_HANDLE hBmp, RTS_Rectangle rPos, RTS_UI32 ulTransparentColor, RTS_UI32 ulFlags);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICDRAWBITMAP) (RTS_HANDLE hDC, RTS_HANDLE hBmp, RTS_Rectangle rPos, RTS_UI32 ulTransparentColor, RTS_UI32 ulFlags);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICDRAWBITMAP_NOTIMPLEMENTED)
	#define USE_SysGraphicDrawBitmap
	#define EXT_SysGraphicDrawBitmap
	#define GET_SysGraphicDrawBitmap(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicDrawBitmap(p0,p1,p2,p3,p4) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicDrawBitmap  FALSE
	#define EXP_SysGraphicDrawBitmap  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicDrawBitmap
	#define EXT_SysGraphicDrawBitmap
	#define GET_SysGraphicDrawBitmap(fl)  CAL_CMGETAPI( "SysGraphicDrawBitmap" ) 
	#define CAL_SysGraphicDrawBitmap  SysGraphicDrawBitmap
	#define CHK_SysGraphicDrawBitmap  TRUE
	#define EXP_SysGraphicDrawBitmap  CAL_CMEXPAPI( "SysGraphicDrawBitmap" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicDrawBitmap
	#define EXT_SysGraphicDrawBitmap
	#define GET_SysGraphicDrawBitmap(fl)  CAL_CMGETAPI( "SysGraphicDrawBitmap" ) 
	#define CAL_SysGraphicDrawBitmap  SysGraphicDrawBitmap
	#define CHK_SysGraphicDrawBitmap  TRUE
	#define EXP_SysGraphicDrawBitmap  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawBitmap", (RTS_UINTPTR)SysGraphicDrawBitmap, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicDrawBitmap
	#define EXT_SysGraphicSysGraphicDrawBitmap
	#define GET_SysGraphicSysGraphicDrawBitmap  ERR_OK
	#define CAL_SysGraphicSysGraphicDrawBitmap  SysGraphicDrawBitmap
	#define CHK_SysGraphicSysGraphicDrawBitmap  TRUE
	#define EXP_SysGraphicSysGraphicDrawBitmap  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicDrawBitmap
	#define EXT_SysGraphicDrawBitmap
	#define GET_SysGraphicDrawBitmap(fl)  CAL_CMGETAPI( "SysGraphicDrawBitmap" ) 
	#define CAL_SysGraphicDrawBitmap  SysGraphicDrawBitmap
	#define CHK_SysGraphicDrawBitmap  TRUE
	#define EXP_SysGraphicDrawBitmap  CAL_CMEXPAPI( "SysGraphicDrawBitmap" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicDrawBitmap  PFSYSGRAPHICDRAWBITMAP pfSysGraphicDrawBitmap;
	#define EXT_SysGraphicDrawBitmap  extern PFSYSGRAPHICDRAWBITMAP pfSysGraphicDrawBitmap;
	#define GET_SysGraphicDrawBitmap(fl)  s_pfCMGetAPI2( "SysGraphicDrawBitmap", (RTS_VOID_FCTPTR *)&pfSysGraphicDrawBitmap, (fl), 0, 0)
	#define CAL_SysGraphicDrawBitmap  pfSysGraphicDrawBitmap
	#define CHK_SysGraphicDrawBitmap  (pfSysGraphicDrawBitmap != NULL)
	#define EXP_SysGraphicDrawBitmap   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicDrawBitmap", (RTS_UINTPTR)SysGraphicDrawBitmap, 0, 0) 
#endif


/**
 * <description>Function to free a bitmap object</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="hBmp" type="IN">Handle to the bitmap</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicFreeBitmap(RTS_HANDLE hDC, RTS_HANDLE hBmp);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICFREEBITMAP) (RTS_HANDLE hDC, RTS_HANDLE hBmp);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICFREEBITMAP_NOTIMPLEMENTED)
	#define USE_SysGraphicFreeBitmap
	#define EXT_SysGraphicFreeBitmap
	#define GET_SysGraphicFreeBitmap(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicFreeBitmap(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicFreeBitmap  FALSE
	#define EXP_SysGraphicFreeBitmap  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicFreeBitmap
	#define EXT_SysGraphicFreeBitmap
	#define GET_SysGraphicFreeBitmap(fl)  CAL_CMGETAPI( "SysGraphicFreeBitmap" ) 
	#define CAL_SysGraphicFreeBitmap  SysGraphicFreeBitmap
	#define CHK_SysGraphicFreeBitmap  TRUE
	#define EXP_SysGraphicFreeBitmap  CAL_CMEXPAPI( "SysGraphicFreeBitmap" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicFreeBitmap
	#define EXT_SysGraphicFreeBitmap
	#define GET_SysGraphicFreeBitmap(fl)  CAL_CMGETAPI( "SysGraphicFreeBitmap" ) 
	#define CAL_SysGraphicFreeBitmap  SysGraphicFreeBitmap
	#define CHK_SysGraphicFreeBitmap  TRUE
	#define EXP_SysGraphicFreeBitmap  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFreeBitmap", (RTS_UINTPTR)SysGraphicFreeBitmap, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicFreeBitmap
	#define EXT_SysGraphicSysGraphicFreeBitmap
	#define GET_SysGraphicSysGraphicFreeBitmap  ERR_OK
	#define CAL_SysGraphicSysGraphicFreeBitmap  SysGraphicFreeBitmap
	#define CHK_SysGraphicSysGraphicFreeBitmap  TRUE
	#define EXP_SysGraphicSysGraphicFreeBitmap  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicFreeBitmap
	#define EXT_SysGraphicFreeBitmap
	#define GET_SysGraphicFreeBitmap(fl)  CAL_CMGETAPI( "SysGraphicFreeBitmap" ) 
	#define CAL_SysGraphicFreeBitmap  SysGraphicFreeBitmap
	#define CHK_SysGraphicFreeBitmap  TRUE
	#define EXP_SysGraphicFreeBitmap  CAL_CMEXPAPI( "SysGraphicFreeBitmap" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicFreeBitmap  PFSYSGRAPHICFREEBITMAP pfSysGraphicFreeBitmap;
	#define EXT_SysGraphicFreeBitmap  extern PFSYSGRAPHICFREEBITMAP pfSysGraphicFreeBitmap;
	#define GET_SysGraphicFreeBitmap(fl)  s_pfCMGetAPI2( "SysGraphicFreeBitmap", (RTS_VOID_FCTPTR *)&pfSysGraphicFreeBitmap, (fl), 0, 0)
	#define CAL_SysGraphicFreeBitmap  pfSysGraphicFreeBitmap
	#define CHK_SysGraphicFreeBitmap  (pfSysGraphicFreeBitmap != NULL)
	#define EXP_SysGraphicFreeBitmap   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFreeBitmap", (RTS_UINTPTR)SysGraphicFreeBitmap, 0, 0) 
#endif


/**
 * <description>Function to get the bitmap size</description>
 * <param name="hBmp" type="IN">Handle to the bitmap</param>
 * <param name="pSize" type="IN">Point to store the size of the bitmap</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicGetBitmapSize(RTS_HANDLE hBmp, RTS_Point* pSize);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICGETBITMAPSIZE) (RTS_HANDLE hBmp, RTS_Point* pSize);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICGETBITMAPSIZE_NOTIMPLEMENTED)
	#define USE_SysGraphicGetBitmapSize
	#define EXT_SysGraphicGetBitmapSize
	#define GET_SysGraphicGetBitmapSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicGetBitmapSize(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicGetBitmapSize  FALSE
	#define EXP_SysGraphicGetBitmapSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicGetBitmapSize
	#define EXT_SysGraphicGetBitmapSize
	#define GET_SysGraphicGetBitmapSize(fl)  CAL_CMGETAPI( "SysGraphicGetBitmapSize" ) 
	#define CAL_SysGraphicGetBitmapSize  SysGraphicGetBitmapSize
	#define CHK_SysGraphicGetBitmapSize  TRUE
	#define EXP_SysGraphicGetBitmapSize  CAL_CMEXPAPI( "SysGraphicGetBitmapSize" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicGetBitmapSize
	#define EXT_SysGraphicGetBitmapSize
	#define GET_SysGraphicGetBitmapSize(fl)  CAL_CMGETAPI( "SysGraphicGetBitmapSize" ) 
	#define CAL_SysGraphicGetBitmapSize  SysGraphicGetBitmapSize
	#define CHK_SysGraphicGetBitmapSize  TRUE
	#define EXP_SysGraphicGetBitmapSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetBitmapSize", (RTS_UINTPTR)SysGraphicGetBitmapSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicGetBitmapSize
	#define EXT_SysGraphicSysGraphicGetBitmapSize
	#define GET_SysGraphicSysGraphicGetBitmapSize  ERR_OK
	#define CAL_SysGraphicSysGraphicGetBitmapSize  SysGraphicGetBitmapSize
	#define CHK_SysGraphicSysGraphicGetBitmapSize  TRUE
	#define EXP_SysGraphicSysGraphicGetBitmapSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicGetBitmapSize
	#define EXT_SysGraphicGetBitmapSize
	#define GET_SysGraphicGetBitmapSize(fl)  CAL_CMGETAPI( "SysGraphicGetBitmapSize" ) 
	#define CAL_SysGraphicGetBitmapSize  SysGraphicGetBitmapSize
	#define CHK_SysGraphicGetBitmapSize  TRUE
	#define EXP_SysGraphicGetBitmapSize  CAL_CMEXPAPI( "SysGraphicGetBitmapSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicGetBitmapSize  PFSYSGRAPHICGETBITMAPSIZE pfSysGraphicGetBitmapSize;
	#define EXT_SysGraphicGetBitmapSize  extern PFSYSGRAPHICGETBITMAPSIZE pfSysGraphicGetBitmapSize;
	#define GET_SysGraphicGetBitmapSize(fl)  s_pfCMGetAPI2( "SysGraphicGetBitmapSize", (RTS_VOID_FCTPTR *)&pfSysGraphicGetBitmapSize, (fl), 0, 0)
	#define CAL_SysGraphicGetBitmapSize  pfSysGraphicGetBitmapSize
	#define CHK_SysGraphicGetBitmapSize  (pfSysGraphicGetBitmapSize != NULL)
	#define EXP_SysGraphicGetBitmapSize   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetBitmapSize", (RTS_UINTPTR)SysGraphicGetBitmapSize, 0, 0) 
#endif


/** 
 * <description>
 * <p>Obsolete: Use SysGraphicSetClipRectangle instead!</p>
 * <p>OBSOLETE Function to add a clipping rectangle to the current clipping region,
 *	i.e. elements beyond this rectangle won't be drawn</p></description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicAddClipRectangle(RTS_HANDLE hDC, RTS_Rectangle rect);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICADDCLIPRECTANGLE) (RTS_HANDLE hDC, RTS_Rectangle rect);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICADDCLIPRECTANGLE_NOTIMPLEMENTED)
	#define USE_SysGraphicAddClipRectangle
	#define EXT_SysGraphicAddClipRectangle
	#define GET_SysGraphicAddClipRectangle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicAddClipRectangle(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicAddClipRectangle  FALSE
	#define EXP_SysGraphicAddClipRectangle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicAddClipRectangle
	#define EXT_SysGraphicAddClipRectangle
	#define GET_SysGraphicAddClipRectangle(fl)  CAL_CMGETAPI( "SysGraphicAddClipRectangle" ) 
	#define CAL_SysGraphicAddClipRectangle  SysGraphicAddClipRectangle
	#define CHK_SysGraphicAddClipRectangle  TRUE
	#define EXP_SysGraphicAddClipRectangle  CAL_CMEXPAPI( "SysGraphicAddClipRectangle" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicAddClipRectangle
	#define EXT_SysGraphicAddClipRectangle
	#define GET_SysGraphicAddClipRectangle(fl)  CAL_CMGETAPI( "SysGraphicAddClipRectangle" ) 
	#define CAL_SysGraphicAddClipRectangle  SysGraphicAddClipRectangle
	#define CHK_SysGraphicAddClipRectangle  TRUE
	#define EXP_SysGraphicAddClipRectangle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicAddClipRectangle", (RTS_UINTPTR)SysGraphicAddClipRectangle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicAddClipRectangle
	#define EXT_SysGraphicSysGraphicAddClipRectangle
	#define GET_SysGraphicSysGraphicAddClipRectangle  ERR_OK
	#define CAL_SysGraphicSysGraphicAddClipRectangle  SysGraphicAddClipRectangle
	#define CHK_SysGraphicSysGraphicAddClipRectangle  TRUE
	#define EXP_SysGraphicSysGraphicAddClipRectangle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicAddClipRectangle
	#define EXT_SysGraphicAddClipRectangle
	#define GET_SysGraphicAddClipRectangle(fl)  CAL_CMGETAPI( "SysGraphicAddClipRectangle" ) 
	#define CAL_SysGraphicAddClipRectangle  SysGraphicAddClipRectangle
	#define CHK_SysGraphicAddClipRectangle  TRUE
	#define EXP_SysGraphicAddClipRectangle  CAL_CMEXPAPI( "SysGraphicAddClipRectangle" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicAddClipRectangle  PFSYSGRAPHICADDCLIPRECTANGLE pfSysGraphicAddClipRectangle;
	#define EXT_SysGraphicAddClipRectangle  extern PFSYSGRAPHICADDCLIPRECTANGLE pfSysGraphicAddClipRectangle;
	#define GET_SysGraphicAddClipRectangle(fl)  s_pfCMGetAPI2( "SysGraphicAddClipRectangle", (RTS_VOID_FCTPTR *)&pfSysGraphicAddClipRectangle, (fl), 0, 0)
	#define CAL_SysGraphicAddClipRectangle  pfSysGraphicAddClipRectangle
	#define CHK_SysGraphicAddClipRectangle  (pfSysGraphicAddClipRectangle != NULL)
	#define EXP_SysGraphicAddClipRectangle   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicAddClipRectangle", (RTS_UINTPTR)SysGraphicAddClipRectangle, 0, 0) 
#endif


/**
 * <description>
 * <p>Obsolete: Use SysGraphicSetClipRectangle instead!</p>
 * <p>OBSOLETE function to remove a clipping rectangle from the current clipping region
 *	i.e. elements beyond this rectangle will be drawn again</p></description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="rect" type="IN">Rectangle description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicRemoveClipRectangle(RTS_HANDLE hDC, RTS_Rectangle rect);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICREMOVECLIPRECTANGLE) (RTS_HANDLE hDC, RTS_Rectangle rect);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICREMOVECLIPRECTANGLE_NOTIMPLEMENTED)
	#define USE_SysGraphicRemoveClipRectangle
	#define EXT_SysGraphicRemoveClipRectangle
	#define GET_SysGraphicRemoveClipRectangle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicRemoveClipRectangle(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicRemoveClipRectangle  FALSE
	#define EXP_SysGraphicRemoveClipRectangle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicRemoveClipRectangle
	#define EXT_SysGraphicRemoveClipRectangle
	#define GET_SysGraphicRemoveClipRectangle(fl)  CAL_CMGETAPI( "SysGraphicRemoveClipRectangle" ) 
	#define CAL_SysGraphicRemoveClipRectangle  SysGraphicRemoveClipRectangle
	#define CHK_SysGraphicRemoveClipRectangle  TRUE
	#define EXP_SysGraphicRemoveClipRectangle  CAL_CMEXPAPI( "SysGraphicRemoveClipRectangle" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicRemoveClipRectangle
	#define EXT_SysGraphicRemoveClipRectangle
	#define GET_SysGraphicRemoveClipRectangle(fl)  CAL_CMGETAPI( "SysGraphicRemoveClipRectangle" ) 
	#define CAL_SysGraphicRemoveClipRectangle  SysGraphicRemoveClipRectangle
	#define CHK_SysGraphicRemoveClipRectangle  TRUE
	#define EXP_SysGraphicRemoveClipRectangle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicRemoveClipRectangle", (RTS_UINTPTR)SysGraphicRemoveClipRectangle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicRemoveClipRectangle
	#define EXT_SysGraphicSysGraphicRemoveClipRectangle
	#define GET_SysGraphicSysGraphicRemoveClipRectangle  ERR_OK
	#define CAL_SysGraphicSysGraphicRemoveClipRectangle  SysGraphicRemoveClipRectangle
	#define CHK_SysGraphicSysGraphicRemoveClipRectangle  TRUE
	#define EXP_SysGraphicSysGraphicRemoveClipRectangle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicRemoveClipRectangle
	#define EXT_SysGraphicRemoveClipRectangle
	#define GET_SysGraphicRemoveClipRectangle(fl)  CAL_CMGETAPI( "SysGraphicRemoveClipRectangle" ) 
	#define CAL_SysGraphicRemoveClipRectangle  SysGraphicRemoveClipRectangle
	#define CHK_SysGraphicRemoveClipRectangle  TRUE
	#define EXP_SysGraphicRemoveClipRectangle  CAL_CMEXPAPI( "SysGraphicRemoveClipRectangle" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicRemoveClipRectangle  PFSYSGRAPHICREMOVECLIPRECTANGLE pfSysGraphicRemoveClipRectangle;
	#define EXT_SysGraphicRemoveClipRectangle  extern PFSYSGRAPHICREMOVECLIPRECTANGLE pfSysGraphicRemoveClipRectangle;
	#define GET_SysGraphicRemoveClipRectangle(fl)  s_pfCMGetAPI2( "SysGraphicRemoveClipRectangle", (RTS_VOID_FCTPTR *)&pfSysGraphicRemoveClipRectangle, (fl), 0, 0)
	#define CAL_SysGraphicRemoveClipRectangle  pfSysGraphicRemoveClipRectangle
	#define CHK_SysGraphicRemoveClipRectangle  (pfSysGraphicRemoveClipRectangle != NULL)
	#define EXP_SysGraphicRemoveClipRectangle   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicRemoveClipRectangle", (RTS_UINTPTR)SysGraphicRemoveClipRectangle, 0, 0) 
#endif


/**
 * <description>function to set and reset the currently active clipping rectangle 
 *	i.e. elements beyond this rectangle will not be drawn</description>
 * <param name="hDC" type="IN">Handle to device context</param>
 * <param name="prect" type="IN">An optional Rectangle. If a rectangle is passed here, this rectangle will
 *	become the new clipping rectangle. If <c>NULL</c> is passed, the clipping region will cleared.
 *	The passed rectangle must not be modified by the implementation!</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicSetClipRectangle(RTS_HANDLE hDC, RTS_Rectangle* prect);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICSETCLIPRECTANGLE) (RTS_HANDLE hDC, RTS_Rectangle* prect);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICSETCLIPRECTANGLE_NOTIMPLEMENTED)
	#define USE_SysGraphicSetClipRectangle
	#define EXT_SysGraphicSetClipRectangle
	#define GET_SysGraphicSetClipRectangle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicSetClipRectangle(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicSetClipRectangle  FALSE
	#define EXP_SysGraphicSetClipRectangle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicSetClipRectangle
	#define EXT_SysGraphicSetClipRectangle
	#define GET_SysGraphicSetClipRectangle(fl)  CAL_CMGETAPI( "SysGraphicSetClipRectangle" ) 
	#define CAL_SysGraphicSetClipRectangle  SysGraphicSetClipRectangle
	#define CHK_SysGraphicSetClipRectangle  TRUE
	#define EXP_SysGraphicSetClipRectangle  CAL_CMEXPAPI( "SysGraphicSetClipRectangle" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicSetClipRectangle
	#define EXT_SysGraphicSetClipRectangle
	#define GET_SysGraphicSetClipRectangle(fl)  CAL_CMGETAPI( "SysGraphicSetClipRectangle" ) 
	#define CAL_SysGraphicSetClipRectangle  SysGraphicSetClipRectangle
	#define CHK_SysGraphicSetClipRectangle  TRUE
	#define EXP_SysGraphicSetClipRectangle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetClipRectangle", (RTS_UINTPTR)SysGraphicSetClipRectangle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicSetClipRectangle
	#define EXT_SysGraphicSysGraphicSetClipRectangle
	#define GET_SysGraphicSysGraphicSetClipRectangle  ERR_OK
	#define CAL_SysGraphicSysGraphicSetClipRectangle  SysGraphicSetClipRectangle
	#define CHK_SysGraphicSysGraphicSetClipRectangle  TRUE
	#define EXP_SysGraphicSysGraphicSetClipRectangle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicSetClipRectangle
	#define EXT_SysGraphicSetClipRectangle
	#define GET_SysGraphicSetClipRectangle(fl)  CAL_CMGETAPI( "SysGraphicSetClipRectangle" ) 
	#define CAL_SysGraphicSetClipRectangle  SysGraphicSetClipRectangle
	#define CHK_SysGraphicSetClipRectangle  TRUE
	#define EXP_SysGraphicSetClipRectangle  CAL_CMEXPAPI( "SysGraphicSetClipRectangle" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicSetClipRectangle  PFSYSGRAPHICSETCLIPRECTANGLE pfSysGraphicSetClipRectangle;
	#define EXT_SysGraphicSetClipRectangle  extern PFSYSGRAPHICSETCLIPRECTANGLE pfSysGraphicSetClipRectangle;
	#define GET_SysGraphicSetClipRectangle(fl)  s_pfCMGetAPI2( "SysGraphicSetClipRectangle", (RTS_VOID_FCTPTR *)&pfSysGraphicSetClipRectangle, (fl), 0, 0)
	#define CAL_SysGraphicSetClipRectangle  pfSysGraphicSetClipRectangle
	#define CHK_SysGraphicSetClipRectangle  (pfSysGraphicSetClipRectangle != NULL)
	#define EXP_SysGraphicSetClipRectangle   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetClipRectangle", (RTS_UINTPTR)SysGraphicSetClipRectangle, 0, 0) 
#endif


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
RTS_RESULT CDECL SysGraphicBeginPaint(RTS_HANDLE hDC, RTS_HANDLE* phPaintContext);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICBEGINPAINT) (RTS_HANDLE hDC, RTS_HANDLE* phPaintContext);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICBEGINPAINT_NOTIMPLEMENTED)
	#define USE_SysGraphicBeginPaint
	#define EXT_SysGraphicBeginPaint
	#define GET_SysGraphicBeginPaint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicBeginPaint(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicBeginPaint  FALSE
	#define EXP_SysGraphicBeginPaint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicBeginPaint
	#define EXT_SysGraphicBeginPaint
	#define GET_SysGraphicBeginPaint(fl)  CAL_CMGETAPI( "SysGraphicBeginPaint" ) 
	#define CAL_SysGraphicBeginPaint  SysGraphicBeginPaint
	#define CHK_SysGraphicBeginPaint  TRUE
	#define EXP_SysGraphicBeginPaint  CAL_CMEXPAPI( "SysGraphicBeginPaint" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicBeginPaint
	#define EXT_SysGraphicBeginPaint
	#define GET_SysGraphicBeginPaint(fl)  CAL_CMGETAPI( "SysGraphicBeginPaint" ) 
	#define CAL_SysGraphicBeginPaint  SysGraphicBeginPaint
	#define CHK_SysGraphicBeginPaint  TRUE
	#define EXP_SysGraphicBeginPaint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicBeginPaint", (RTS_UINTPTR)SysGraphicBeginPaint, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicBeginPaint
	#define EXT_SysGraphicSysGraphicBeginPaint
	#define GET_SysGraphicSysGraphicBeginPaint  ERR_OK
	#define CAL_SysGraphicSysGraphicBeginPaint  SysGraphicBeginPaint
	#define CHK_SysGraphicSysGraphicBeginPaint  TRUE
	#define EXP_SysGraphicSysGraphicBeginPaint  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicBeginPaint
	#define EXT_SysGraphicBeginPaint
	#define GET_SysGraphicBeginPaint(fl)  CAL_CMGETAPI( "SysGraphicBeginPaint" ) 
	#define CAL_SysGraphicBeginPaint  SysGraphicBeginPaint
	#define CHK_SysGraphicBeginPaint  TRUE
	#define EXP_SysGraphicBeginPaint  CAL_CMEXPAPI( "SysGraphicBeginPaint" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicBeginPaint  PFSYSGRAPHICBEGINPAINT pfSysGraphicBeginPaint;
	#define EXT_SysGraphicBeginPaint  extern PFSYSGRAPHICBEGINPAINT pfSysGraphicBeginPaint;
	#define GET_SysGraphicBeginPaint(fl)  s_pfCMGetAPI2( "SysGraphicBeginPaint", (RTS_VOID_FCTPTR *)&pfSysGraphicBeginPaint, (fl), 0, 0)
	#define CAL_SysGraphicBeginPaint  pfSysGraphicBeginPaint
	#define CHK_SysGraphicBeginPaint  (pfSysGraphicBeginPaint != NULL)
	#define EXP_SysGraphicBeginPaint   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicBeginPaint", (RTS_UINTPTR)SysGraphicBeginPaint, 0, 0) 
#endif


/**
 * <description>This function and <see>SysGraphicBeginPaint</see> are used to encapsule some paint calls
 *	together. An implementing platform could use this encapsulation for some optimizations. For every
 *	call to SysGraphicBeginPaint there will be an according call to SysGraphicEndPaint.</description>
 * <param name="hDC" type="IN">The device context that has been drawn onto until this call</param>
 * <param name="hPaintContext" type="OUT">The data that has been returned by the corresponding call to 
 *		<see>SysGraphicBeginPaint</see>.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysGraphicEndPaint(RTS_HANDLE hDC, RTS_HANDLE hPaintContext);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICENDPAINT) (RTS_HANDLE hDC, RTS_HANDLE hPaintContext);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICENDPAINT_NOTIMPLEMENTED)
	#define USE_SysGraphicEndPaint
	#define EXT_SysGraphicEndPaint
	#define GET_SysGraphicEndPaint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicEndPaint(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicEndPaint  FALSE
	#define EXP_SysGraphicEndPaint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicEndPaint
	#define EXT_SysGraphicEndPaint
	#define GET_SysGraphicEndPaint(fl)  CAL_CMGETAPI( "SysGraphicEndPaint" ) 
	#define CAL_SysGraphicEndPaint  SysGraphicEndPaint
	#define CHK_SysGraphicEndPaint  TRUE
	#define EXP_SysGraphicEndPaint  CAL_CMEXPAPI( "SysGraphicEndPaint" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicEndPaint
	#define EXT_SysGraphicEndPaint
	#define GET_SysGraphicEndPaint(fl)  CAL_CMGETAPI( "SysGraphicEndPaint" ) 
	#define CAL_SysGraphicEndPaint  SysGraphicEndPaint
	#define CHK_SysGraphicEndPaint  TRUE
	#define EXP_SysGraphicEndPaint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicEndPaint", (RTS_UINTPTR)SysGraphicEndPaint, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicEndPaint
	#define EXT_SysGraphicSysGraphicEndPaint
	#define GET_SysGraphicSysGraphicEndPaint  ERR_OK
	#define CAL_SysGraphicSysGraphicEndPaint  SysGraphicEndPaint
	#define CHK_SysGraphicSysGraphicEndPaint  TRUE
	#define EXP_SysGraphicSysGraphicEndPaint  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicEndPaint
	#define EXT_SysGraphicEndPaint
	#define GET_SysGraphicEndPaint(fl)  CAL_CMGETAPI( "SysGraphicEndPaint" ) 
	#define CAL_SysGraphicEndPaint  SysGraphicEndPaint
	#define CHK_SysGraphicEndPaint  TRUE
	#define EXP_SysGraphicEndPaint  CAL_CMEXPAPI( "SysGraphicEndPaint" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicEndPaint  PFSYSGRAPHICENDPAINT pfSysGraphicEndPaint;
	#define EXT_SysGraphicEndPaint  extern PFSYSGRAPHICENDPAINT pfSysGraphicEndPaint;
	#define GET_SysGraphicEndPaint(fl)  s_pfCMGetAPI2( "SysGraphicEndPaint", (RTS_VOID_FCTPTR *)&pfSysGraphicEndPaint, (fl), 0, 0)
	#define CAL_SysGraphicEndPaint  pfSysGraphicEndPaint
	#define CHK_SysGraphicEndPaint  (pfSysGraphicEndPaint != NULL)
	#define EXP_SysGraphicEndPaint   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicEndPaint", (RTS_UINTPTR)SysGraphicEndPaint, 0, 0) 
#endif


/**
 * <description>This function allows the sysgraphic implementation to give a hint to the kernel part of the targetvisualization
 *	about some more or less optional feature that can be supported by an implementation. 
 *	As this function was introduced lateron, it should be included as an optional import to prevent inconsistencies. Additionally, calling code
 *	should assume a result of SYSGRAPHIC_FEATURES_ALL in case this function is not implemented for compatibility reasons.</description>
 * <result>The optional features that are implemented by the current sysgraphic implementation as a combination of the 
 *	flag values SYSGRAPHIC_FEATURES_...</result>
 */
RTS_UI32 CDECL SysGraphicGetFeatureFlags(void);
typedef RTS_UI32 (CDECL * PFSYSGRAPHICGETFEATUREFLAGS) (void);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICGETFEATUREFLAGS_NOTIMPLEMENTED)
	#define USE_SysGraphicGetFeatureFlags
	#define EXT_SysGraphicGetFeatureFlags
	#define GET_SysGraphicGetFeatureFlags(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicGetFeatureFlags() (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicGetFeatureFlags  FALSE
	#define EXP_SysGraphicGetFeatureFlags  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicGetFeatureFlags
	#define EXT_SysGraphicGetFeatureFlags
	#define GET_SysGraphicGetFeatureFlags(fl)  CAL_CMGETAPI( "SysGraphicGetFeatureFlags" ) 
	#define CAL_SysGraphicGetFeatureFlags  SysGraphicGetFeatureFlags
	#define CHK_SysGraphicGetFeatureFlags  TRUE
	#define EXP_SysGraphicGetFeatureFlags  CAL_CMEXPAPI( "SysGraphicGetFeatureFlags" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicGetFeatureFlags
	#define EXT_SysGraphicGetFeatureFlags
	#define GET_SysGraphicGetFeatureFlags(fl)  CAL_CMGETAPI( "SysGraphicGetFeatureFlags" ) 
	#define CAL_SysGraphicGetFeatureFlags  SysGraphicGetFeatureFlags
	#define CHK_SysGraphicGetFeatureFlags  TRUE
	#define EXP_SysGraphicGetFeatureFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetFeatureFlags", (RTS_UINTPTR)SysGraphicGetFeatureFlags, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicGetFeatureFlags
	#define EXT_SysGraphicSysGraphicGetFeatureFlags
	#define GET_SysGraphicSysGraphicGetFeatureFlags  ERR_OK
	#define CAL_SysGraphicSysGraphicGetFeatureFlags  SysGraphicGetFeatureFlags
	#define CHK_SysGraphicSysGraphicGetFeatureFlags  TRUE
	#define EXP_SysGraphicSysGraphicGetFeatureFlags  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicGetFeatureFlags
	#define EXT_SysGraphicGetFeatureFlags
	#define GET_SysGraphicGetFeatureFlags(fl)  CAL_CMGETAPI( "SysGraphicGetFeatureFlags" ) 
	#define CAL_SysGraphicGetFeatureFlags  SysGraphicGetFeatureFlags
	#define CHK_SysGraphicGetFeatureFlags  TRUE
	#define EXP_SysGraphicGetFeatureFlags  CAL_CMEXPAPI( "SysGraphicGetFeatureFlags" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicGetFeatureFlags  PFSYSGRAPHICGETFEATUREFLAGS pfSysGraphicGetFeatureFlags;
	#define EXT_SysGraphicGetFeatureFlags  extern PFSYSGRAPHICGETFEATUREFLAGS pfSysGraphicGetFeatureFlags;
	#define GET_SysGraphicGetFeatureFlags(fl)  s_pfCMGetAPI2( "SysGraphicGetFeatureFlags", (RTS_VOID_FCTPTR *)&pfSysGraphicGetFeatureFlags, (fl), 0, 0)
	#define CAL_SysGraphicGetFeatureFlags  pfSysGraphicGetFeatureFlags
	#define CHK_SysGraphicGetFeatureFlags  (pfSysGraphicGetFeatureFlags != NULL)
	#define EXP_SysGraphicGetFeatureFlags   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetFeatureFlags", (RTS_UINTPTR)SysGraphicGetFeatureFlags, 0, 0) 
#endif


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
RTS_RESULT CDECL SysGraphicPreparePrinting(RTS_HANDLE hDC, RTS_HANDLE* phOptionalResultData, RTS_Rectangle* prWindow, RTS_Rectangle* prPrintOutput);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICPREPAREPRINTING) (RTS_HANDLE hDC, RTS_HANDLE* phOptionalResultData, RTS_Rectangle* prWindow, RTS_Rectangle* prPrintOutput);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICPREPAREPRINTING_NOTIMPLEMENTED)
	#define USE_SysGraphicPreparePrinting
	#define EXT_SysGraphicPreparePrinting
	#define GET_SysGraphicPreparePrinting(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicPreparePrinting(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicPreparePrinting  FALSE
	#define EXP_SysGraphicPreparePrinting  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicPreparePrinting
	#define EXT_SysGraphicPreparePrinting
	#define GET_SysGraphicPreparePrinting(fl)  CAL_CMGETAPI( "SysGraphicPreparePrinting" ) 
	#define CAL_SysGraphicPreparePrinting  SysGraphicPreparePrinting
	#define CHK_SysGraphicPreparePrinting  TRUE
	#define EXP_SysGraphicPreparePrinting  CAL_CMEXPAPI( "SysGraphicPreparePrinting" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicPreparePrinting
	#define EXT_SysGraphicPreparePrinting
	#define GET_SysGraphicPreparePrinting(fl)  CAL_CMGETAPI( "SysGraphicPreparePrinting" ) 
	#define CAL_SysGraphicPreparePrinting  SysGraphicPreparePrinting
	#define CHK_SysGraphicPreparePrinting  TRUE
	#define EXP_SysGraphicPreparePrinting  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicPreparePrinting", (RTS_UINTPTR)SysGraphicPreparePrinting, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicPreparePrinting
	#define EXT_SysGraphicSysGraphicPreparePrinting
	#define GET_SysGraphicSysGraphicPreparePrinting  ERR_OK
	#define CAL_SysGraphicSysGraphicPreparePrinting  SysGraphicPreparePrinting
	#define CHK_SysGraphicSysGraphicPreparePrinting  TRUE
	#define EXP_SysGraphicSysGraphicPreparePrinting  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicPreparePrinting
	#define EXT_SysGraphicPreparePrinting
	#define GET_SysGraphicPreparePrinting(fl)  CAL_CMGETAPI( "SysGraphicPreparePrinting" ) 
	#define CAL_SysGraphicPreparePrinting  SysGraphicPreparePrinting
	#define CHK_SysGraphicPreparePrinting  TRUE
	#define EXP_SysGraphicPreparePrinting  CAL_CMEXPAPI( "SysGraphicPreparePrinting" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicPreparePrinting  PFSYSGRAPHICPREPAREPRINTING pfSysGraphicPreparePrinting;
	#define EXT_SysGraphicPreparePrinting  extern PFSYSGRAPHICPREPAREPRINTING pfSysGraphicPreparePrinting;
	#define GET_SysGraphicPreparePrinting(fl)  s_pfCMGetAPI2( "SysGraphicPreparePrinting", (RTS_VOID_FCTPTR *)&pfSysGraphicPreparePrinting, (fl), 0, 0)
	#define CAL_SysGraphicPreparePrinting  pfSysGraphicPreparePrinting
	#define CHK_SysGraphicPreparePrinting  (pfSysGraphicPreparePrinting != NULL)
	#define EXP_SysGraphicPreparePrinting   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicPreparePrinting", (RTS_UINTPTR)SysGraphicPreparePrinting, 0, 0) 
#endif


/**
 * <description>This function reverts the adaptations done by <see>SysGraphicPreparePrinting</see></description>
 * <param name="hDC" type="IN">The device context of the printer that has to be reverted by this call.</param>
 * <param name="hOptionalResultData" type="IN">When <see>SysGraphicPreparePrinting</see> allocated and returned some additional data,
 *	this handle will be passed here again to be able to release the data correctly.</param>
 * <result>An error code</result>
 */
RTS_RESULT CDECL SysGraphicFinishPrinting(RTS_HANDLE hDC, RTS_HANDLE hOptionalResultData);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICFINISHPRINTING) (RTS_HANDLE hDC, RTS_HANDLE hOptionalResultData);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICFINISHPRINTING_NOTIMPLEMENTED)
	#define USE_SysGraphicFinishPrinting
	#define EXT_SysGraphicFinishPrinting
	#define GET_SysGraphicFinishPrinting(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicFinishPrinting(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicFinishPrinting  FALSE
	#define EXP_SysGraphicFinishPrinting  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicFinishPrinting
	#define EXT_SysGraphicFinishPrinting
	#define GET_SysGraphicFinishPrinting(fl)  CAL_CMGETAPI( "SysGraphicFinishPrinting" ) 
	#define CAL_SysGraphicFinishPrinting  SysGraphicFinishPrinting
	#define CHK_SysGraphicFinishPrinting  TRUE
	#define EXP_SysGraphicFinishPrinting  CAL_CMEXPAPI( "SysGraphicFinishPrinting" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicFinishPrinting
	#define EXT_SysGraphicFinishPrinting
	#define GET_SysGraphicFinishPrinting(fl)  CAL_CMGETAPI( "SysGraphicFinishPrinting" ) 
	#define CAL_SysGraphicFinishPrinting  SysGraphicFinishPrinting
	#define CHK_SysGraphicFinishPrinting  TRUE
	#define EXP_SysGraphicFinishPrinting  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFinishPrinting", (RTS_UINTPTR)SysGraphicFinishPrinting, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicFinishPrinting
	#define EXT_SysGraphicSysGraphicFinishPrinting
	#define GET_SysGraphicSysGraphicFinishPrinting  ERR_OK
	#define CAL_SysGraphicSysGraphicFinishPrinting  SysGraphicFinishPrinting
	#define CHK_SysGraphicSysGraphicFinishPrinting  TRUE
	#define EXP_SysGraphicSysGraphicFinishPrinting  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicFinishPrinting
	#define EXT_SysGraphicFinishPrinting
	#define GET_SysGraphicFinishPrinting(fl)  CAL_CMGETAPI( "SysGraphicFinishPrinting" ) 
	#define CAL_SysGraphicFinishPrinting  SysGraphicFinishPrinting
	#define CHK_SysGraphicFinishPrinting  TRUE
	#define EXP_SysGraphicFinishPrinting  CAL_CMEXPAPI( "SysGraphicFinishPrinting" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicFinishPrinting  PFSYSGRAPHICFINISHPRINTING pfSysGraphicFinishPrinting;
	#define EXT_SysGraphicFinishPrinting  extern PFSYSGRAPHICFINISHPRINTING pfSysGraphicFinishPrinting;
	#define GET_SysGraphicFinishPrinting(fl)  s_pfCMGetAPI2( "SysGraphicFinishPrinting", (RTS_VOID_FCTPTR *)&pfSysGraphicFinishPrinting, (fl), 0, 0)
	#define CAL_SysGraphicFinishPrinting  pfSysGraphicFinishPrinting
	#define CHK_SysGraphicFinishPrinting  (pfSysGraphicFinishPrinting != NULL)
	#define EXP_SysGraphicFinishPrinting   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFinishPrinting", (RTS_UINTPTR)SysGraphicFinishPrinting, 0, 0) 
#endif


/**
 * <description>This function assigns the antialiasing mode to a device context. By default, a device context should be in mode 
 *	<see>SYSGRAPHIC_ANTIALIASING_NONE</see>. If a device does not support antialiased drawing, it should return ERR_NOT_SUPPORTED.
 *	To tell the programming system, whether the antialiasing feature is supported, the targetsetting "visualization\targetsupport\targetvisualization_antialiasing"
 *	can be used.</description>
 * <param name="hDC" type="IN">The device context to assign the antialiasing mode to.</param>
 * <param name="uiAntiAliasingSettings" type="IN">The antialiasing mode (SYSGRAPHIC_ANTIALIASING_NONE,...).</param>
 * <result>An error code</result>
 */
RTS_RESULT CDECL SysGraphicSetAntiAliasingMode(RTS_HANDLE hDC, RTS_UI32 uiAntiAliasingSettings);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICSETANTIALIASINGMODE) (RTS_HANDLE hDC, RTS_UI32 uiAntiAliasingSettings);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICSETANTIALIASINGMODE_NOTIMPLEMENTED)
	#define USE_SysGraphicSetAntiAliasingMode
	#define EXT_SysGraphicSetAntiAliasingMode
	#define GET_SysGraphicSetAntiAliasingMode(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicSetAntiAliasingMode(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicSetAntiAliasingMode  FALSE
	#define EXP_SysGraphicSetAntiAliasingMode  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicSetAntiAliasingMode
	#define EXT_SysGraphicSetAntiAliasingMode
	#define GET_SysGraphicSetAntiAliasingMode(fl)  CAL_CMGETAPI( "SysGraphicSetAntiAliasingMode" ) 
	#define CAL_SysGraphicSetAntiAliasingMode  SysGraphicSetAntiAliasingMode
	#define CHK_SysGraphicSetAntiAliasingMode  TRUE
	#define EXP_SysGraphicSetAntiAliasingMode  CAL_CMEXPAPI( "SysGraphicSetAntiAliasingMode" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicSetAntiAliasingMode
	#define EXT_SysGraphicSetAntiAliasingMode
	#define GET_SysGraphicSetAntiAliasingMode(fl)  CAL_CMGETAPI( "SysGraphicSetAntiAliasingMode" ) 
	#define CAL_SysGraphicSetAntiAliasingMode  SysGraphicSetAntiAliasingMode
	#define CHK_SysGraphicSetAntiAliasingMode  TRUE
	#define EXP_SysGraphicSetAntiAliasingMode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetAntiAliasingMode", (RTS_UINTPTR)SysGraphicSetAntiAliasingMode, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicSetAntiAliasingMode
	#define EXT_SysGraphicSysGraphicSetAntiAliasingMode
	#define GET_SysGraphicSysGraphicSetAntiAliasingMode  ERR_OK
	#define CAL_SysGraphicSysGraphicSetAntiAliasingMode pISysGraphic->ISysGraphicSetAntiAliasingMode
	#define CHK_SysGraphicSysGraphicSetAntiAliasingMode (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicSetAntiAliasingMode  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicSetAntiAliasingMode
	#define EXT_SysGraphicSetAntiAliasingMode
	#define GET_SysGraphicSetAntiAliasingMode(fl)  CAL_CMGETAPI( "SysGraphicSetAntiAliasingMode" ) 
	#define CAL_SysGraphicSetAntiAliasingMode pISysGraphic->ISysGraphicSetAntiAliasingMode
	#define CHK_SysGraphicSetAntiAliasingMode (pISysGraphic != NULL)
	#define EXP_SysGraphicSetAntiAliasingMode  CAL_CMEXPAPI( "SysGraphicSetAntiAliasingMode" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicSetAntiAliasingMode  PFSYSGRAPHICSETANTIALIASINGMODE pfSysGraphicSetAntiAliasingMode;
	#define EXT_SysGraphicSetAntiAliasingMode  extern PFSYSGRAPHICSETANTIALIASINGMODE pfSysGraphicSetAntiAliasingMode;
	#define GET_SysGraphicSetAntiAliasingMode(fl)  s_pfCMGetAPI2( "SysGraphicSetAntiAliasingMode", (RTS_VOID_FCTPTR *)&pfSysGraphicSetAntiAliasingMode, (fl), 0, 0)
	#define CAL_SysGraphicSetAntiAliasingMode  pfSysGraphicSetAntiAliasingMode
	#define CHK_SysGraphicSetAntiAliasingMode  (pfSysGraphicSetAntiAliasingMode != NULL)
	#define EXP_SysGraphicSetAntiAliasingMode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetAntiAliasingMode", (RTS_UINTPTR)SysGraphicSetAntiAliasingMode, 0, 0) 
#endif




/**
 * <description>This function is able to return the probably underlying font type as it is known by the SysWindow component from
 *	a font object that was allocated by the SysGraphic-Component.</description>	
 * <param name="hDC" type="IN">The device context that should be used for the conversion of the font type.</param>
 * <param name="hSysGraphicFont" type="IN">The font that was allocated by the SysGraphic-Component and that should be converted to a font object
 *	that can be handled by the SysWindow-Component.</param>
 * <param name="phSysWindowFont" type="OUT">A pointer that will receive the resulting (SysWindow) font.</param>
 * <result>An error code</result>
 */
RTS_RESULT CDECL SysGraphicGetSysWindowFont(RTS_HANDLE hDC, RTS_HANDLE hSysGraphicFont, RTS_HANDLE* phSysWindowFont);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICGETSYSWINDOWFONT) (RTS_HANDLE hDC, RTS_HANDLE hSysGraphicFont, RTS_HANDLE* phSysWindowFont);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICGETSYSWINDOWFONT_NOTIMPLEMENTED)
	#define USE_SysGraphicGetSysWindowFont
	#define EXT_SysGraphicGetSysWindowFont
	#define GET_SysGraphicGetSysWindowFont(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicGetSysWindowFont(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicGetSysWindowFont  FALSE
	#define EXP_SysGraphicGetSysWindowFont  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicGetSysWindowFont
	#define EXT_SysGraphicGetSysWindowFont
	#define GET_SysGraphicGetSysWindowFont(fl)  CAL_CMGETAPI( "SysGraphicGetSysWindowFont" ) 
	#define CAL_SysGraphicGetSysWindowFont  SysGraphicGetSysWindowFont
	#define CHK_SysGraphicGetSysWindowFont  TRUE
	#define EXP_SysGraphicGetSysWindowFont  CAL_CMEXPAPI( "SysGraphicGetSysWindowFont" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicGetSysWindowFont
	#define EXT_SysGraphicGetSysWindowFont
	#define GET_SysGraphicGetSysWindowFont(fl)  CAL_CMGETAPI( "SysGraphicGetSysWindowFont" ) 
	#define CAL_SysGraphicGetSysWindowFont  SysGraphicGetSysWindowFont
	#define CHK_SysGraphicGetSysWindowFont  TRUE
	#define EXP_SysGraphicGetSysWindowFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetSysWindowFont", (RTS_UINTPTR)SysGraphicGetSysWindowFont, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicGetSysWindowFont
	#define EXT_SysGraphicSysGraphicGetSysWindowFont
	#define GET_SysGraphicSysGraphicGetSysWindowFont  ERR_OK
	#define CAL_SysGraphicSysGraphicGetSysWindowFont pISysGraphic->ISysGraphicGetSysWindowFont
	#define CHK_SysGraphicSysGraphicGetSysWindowFont (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicGetSysWindowFont  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicGetSysWindowFont
	#define EXT_SysGraphicGetSysWindowFont
	#define GET_SysGraphicGetSysWindowFont(fl)  CAL_CMGETAPI( "SysGraphicGetSysWindowFont" ) 
	#define CAL_SysGraphicGetSysWindowFont pISysGraphic->ISysGraphicGetSysWindowFont
	#define CHK_SysGraphicGetSysWindowFont (pISysGraphic != NULL)
	#define EXP_SysGraphicGetSysWindowFont  CAL_CMEXPAPI( "SysGraphicGetSysWindowFont" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicGetSysWindowFont  PFSYSGRAPHICGETSYSWINDOWFONT pfSysGraphicGetSysWindowFont;
	#define EXT_SysGraphicGetSysWindowFont  extern PFSYSGRAPHICGETSYSWINDOWFONT pfSysGraphicGetSysWindowFont;
	#define GET_SysGraphicGetSysWindowFont(fl)  s_pfCMGetAPI2( "SysGraphicGetSysWindowFont", (RTS_VOID_FCTPTR *)&pfSysGraphicGetSysWindowFont, (fl), 0, 0)
	#define CAL_SysGraphicGetSysWindowFont  pfSysGraphicGetSysWindowFont
	#define CHK_SysGraphicGetSysWindowFont  (pfSysGraphicGetSysWindowFont != NULL)
	#define EXP_SysGraphicGetSysWindowFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetSysWindowFont", (RTS_UINTPTR)SysGraphicGetSysWindowFont, 0, 0) 
#endif




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
RTS_RESULT CDECL SysGraphicInvalidateRectangle(RTS_HANDLE hDC, RTS_Rectangle rect);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICINVALIDATERECTANGLE) (RTS_HANDLE hDC, RTS_Rectangle rect);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICINVALIDATERECTANGLE_NOTIMPLEMENTED)
	#define USE_SysGraphicInvalidateRectangle
	#define EXT_SysGraphicInvalidateRectangle
	#define GET_SysGraphicInvalidateRectangle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicInvalidateRectangle(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicInvalidateRectangle  FALSE
	#define EXP_SysGraphicInvalidateRectangle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicInvalidateRectangle
	#define EXT_SysGraphicInvalidateRectangle
	#define GET_SysGraphicInvalidateRectangle(fl)  CAL_CMGETAPI( "SysGraphicInvalidateRectangle" ) 
	#define CAL_SysGraphicInvalidateRectangle  SysGraphicInvalidateRectangle
	#define CHK_SysGraphicInvalidateRectangle  TRUE
	#define EXP_SysGraphicInvalidateRectangle  CAL_CMEXPAPI( "SysGraphicInvalidateRectangle" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicInvalidateRectangle
	#define EXT_SysGraphicInvalidateRectangle
	#define GET_SysGraphicInvalidateRectangle(fl)  CAL_CMGETAPI( "SysGraphicInvalidateRectangle" ) 
	#define CAL_SysGraphicInvalidateRectangle  SysGraphicInvalidateRectangle
	#define CHK_SysGraphicInvalidateRectangle  TRUE
	#define EXP_SysGraphicInvalidateRectangle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicInvalidateRectangle", (RTS_UINTPTR)SysGraphicInvalidateRectangle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicInvalidateRectangle
	#define EXT_SysGraphicSysGraphicInvalidateRectangle
	#define GET_SysGraphicSysGraphicInvalidateRectangle  ERR_OK
	#define CAL_SysGraphicSysGraphicInvalidateRectangle pISysGraphic->ISysGraphicInvalidateRectangle
	#define CHK_SysGraphicSysGraphicInvalidateRectangle (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicInvalidateRectangle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicInvalidateRectangle
	#define EXT_SysGraphicInvalidateRectangle
	#define GET_SysGraphicInvalidateRectangle(fl)  CAL_CMGETAPI( "SysGraphicInvalidateRectangle" ) 
	#define CAL_SysGraphicInvalidateRectangle pISysGraphic->ISysGraphicInvalidateRectangle
	#define CHK_SysGraphicInvalidateRectangle (pISysGraphic != NULL)
	#define EXP_SysGraphicInvalidateRectangle  CAL_CMEXPAPI( "SysGraphicInvalidateRectangle" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicInvalidateRectangle  PFSYSGRAPHICINVALIDATERECTANGLE pfSysGraphicInvalidateRectangle;
	#define EXT_SysGraphicInvalidateRectangle  extern PFSYSGRAPHICINVALIDATERECTANGLE pfSysGraphicInvalidateRectangle;
	#define GET_SysGraphicInvalidateRectangle(fl)  s_pfCMGetAPI2( "SysGraphicInvalidateRectangle", (RTS_VOID_FCTPTR *)&pfSysGraphicInvalidateRectangle, (fl), 0, 0)
	#define CAL_SysGraphicInvalidateRectangle  pfSysGraphicInvalidateRectangle
	#define CHK_SysGraphicInvalidateRectangle  (pfSysGraphicInvalidateRectangle != NULL)
	#define EXP_SysGraphicInvalidateRectangle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicInvalidateRectangle", (RTS_UINTPTR)SysGraphicInvalidateRectangle, 0, 0) 
#endif




/**
 * <description>This function is optional in the same way than <see>SysGraphicInvalidateRectangle</see>. Nevertheless, if  <see>SysGraphicInvalidateRectangle</see> is
 *	implemented, then this function should be implemented too. It will be called to reset the list of passed invalidation rectangles. 
 *  This fact probably depends on the underlying graphics system (for Windows or native systems, this is probably not necessary, for QT based 
 *	systems, an implementation might be necessary.</description>	
 * <param name="hDC" type="IN">The device context to invalidate in.</param>
 * <result>An error code</result>
*/ 
RTS_RESULT CDECL SysGraphicResetInvalidation(RTS_HANDLE hDC);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICRESETINVALIDATION) (RTS_HANDLE hDC);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICRESETINVALIDATION_NOTIMPLEMENTED)
	#define USE_SysGraphicResetInvalidation
	#define EXT_SysGraphicResetInvalidation
	#define GET_SysGraphicResetInvalidation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicResetInvalidation(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicResetInvalidation  FALSE
	#define EXP_SysGraphicResetInvalidation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicResetInvalidation
	#define EXT_SysGraphicResetInvalidation
	#define GET_SysGraphicResetInvalidation(fl)  CAL_CMGETAPI( "SysGraphicResetInvalidation" ) 
	#define CAL_SysGraphicResetInvalidation  SysGraphicResetInvalidation
	#define CHK_SysGraphicResetInvalidation  TRUE
	#define EXP_SysGraphicResetInvalidation  CAL_CMEXPAPI( "SysGraphicResetInvalidation" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicResetInvalidation
	#define EXT_SysGraphicResetInvalidation
	#define GET_SysGraphicResetInvalidation(fl)  CAL_CMGETAPI( "SysGraphicResetInvalidation" ) 
	#define CAL_SysGraphicResetInvalidation  SysGraphicResetInvalidation
	#define CHK_SysGraphicResetInvalidation  TRUE
	#define EXP_SysGraphicResetInvalidation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicResetInvalidation", (RTS_UINTPTR)SysGraphicResetInvalidation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicResetInvalidation
	#define EXT_SysGraphicSysGraphicResetInvalidation
	#define GET_SysGraphicSysGraphicResetInvalidation  ERR_OK
	#define CAL_SysGraphicSysGraphicResetInvalidation pISysGraphic->ISysGraphicResetInvalidation
	#define CHK_SysGraphicSysGraphicResetInvalidation (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicResetInvalidation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicResetInvalidation
	#define EXT_SysGraphicResetInvalidation
	#define GET_SysGraphicResetInvalidation(fl)  CAL_CMGETAPI( "SysGraphicResetInvalidation" ) 
	#define CAL_SysGraphicResetInvalidation pISysGraphic->ISysGraphicResetInvalidation
	#define CHK_SysGraphicResetInvalidation (pISysGraphic != NULL)
	#define EXP_SysGraphicResetInvalidation  CAL_CMEXPAPI( "SysGraphicResetInvalidation" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicResetInvalidation  PFSYSGRAPHICRESETINVALIDATION pfSysGraphicResetInvalidation;
	#define EXT_SysGraphicResetInvalidation  extern PFSYSGRAPHICRESETINVALIDATION pfSysGraphicResetInvalidation;
	#define GET_SysGraphicResetInvalidation(fl)  s_pfCMGetAPI2( "SysGraphicResetInvalidation", (RTS_VOID_FCTPTR *)&pfSysGraphicResetInvalidation, (fl), 0, 0)
	#define CAL_SysGraphicResetInvalidation  pfSysGraphicResetInvalidation
	#define CHK_SysGraphicResetInvalidation  (pfSysGraphicResetInvalidation != NULL)
	#define EXP_SysGraphicResetInvalidation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicResetInvalidation", (RTS_UINTPTR)SysGraphicResetInvalidation, 0, 0) 
#endif




/**
 * <description>This function is optional, just as <see>SysGraphicInvalidateRectangle</see>, but should be implemented, if <see>SysGraphicInvalidateRectangle</see> is
 *  implemented. It will be called when the whole client area should be invalidated.</description>
 * <param name="hDC" type="IN">A handle to the device context.</param>
 * <result>An error code</result>
*/
RTS_RESULT CDECL SysGraphicInvalidateClientArea(RTS_HANDLE hDC);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICINVALIDATECLIENTAREA) (RTS_HANDLE hDC);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICINVALIDATECLIENTAREA_NOTIMPLEMENTED)
	#define USE_SysGraphicInvalidateClientArea
	#define EXT_SysGraphicInvalidateClientArea
	#define GET_SysGraphicInvalidateClientArea(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicInvalidateClientArea(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicInvalidateClientArea  FALSE
	#define EXP_SysGraphicInvalidateClientArea  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicInvalidateClientArea
	#define EXT_SysGraphicInvalidateClientArea
	#define GET_SysGraphicInvalidateClientArea(fl)  CAL_CMGETAPI( "SysGraphicInvalidateClientArea" ) 
	#define CAL_SysGraphicInvalidateClientArea  SysGraphicInvalidateClientArea
	#define CHK_SysGraphicInvalidateClientArea  TRUE
	#define EXP_SysGraphicInvalidateClientArea  CAL_CMEXPAPI( "SysGraphicInvalidateClientArea" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicInvalidateClientArea
	#define EXT_SysGraphicInvalidateClientArea
	#define GET_SysGraphicInvalidateClientArea(fl)  CAL_CMGETAPI( "SysGraphicInvalidateClientArea" ) 
	#define CAL_SysGraphicInvalidateClientArea  SysGraphicInvalidateClientArea
	#define CHK_SysGraphicInvalidateClientArea  TRUE
	#define EXP_SysGraphicInvalidateClientArea  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicInvalidateClientArea", (RTS_UINTPTR)SysGraphicInvalidateClientArea, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicInvalidateClientArea
	#define EXT_SysGraphicSysGraphicInvalidateClientArea
	#define GET_SysGraphicSysGraphicInvalidateClientArea  ERR_OK
	#define CAL_SysGraphicSysGraphicInvalidateClientArea pISysGraphic->ISysGraphicInvalidateClientArea
	#define CHK_SysGraphicSysGraphicInvalidateClientArea (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicInvalidateClientArea  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicInvalidateClientArea
	#define EXT_SysGraphicInvalidateClientArea
	#define GET_SysGraphicInvalidateClientArea(fl)  CAL_CMGETAPI( "SysGraphicInvalidateClientArea" ) 
	#define CAL_SysGraphicInvalidateClientArea pISysGraphic->ISysGraphicInvalidateClientArea
	#define CHK_SysGraphicInvalidateClientArea (pISysGraphic != NULL)
	#define EXP_SysGraphicInvalidateClientArea  CAL_CMEXPAPI( "SysGraphicInvalidateClientArea" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicInvalidateClientArea  PFSYSGRAPHICINVALIDATECLIENTAREA pfSysGraphicInvalidateClientArea;
	#define EXT_SysGraphicInvalidateClientArea  extern PFSYSGRAPHICINVALIDATECLIENTAREA pfSysGraphicInvalidateClientArea;
	#define GET_SysGraphicInvalidateClientArea(fl)  s_pfCMGetAPI2( "SysGraphicInvalidateClientArea", (RTS_VOID_FCTPTR *)&pfSysGraphicInvalidateClientArea, (fl), 0, 0)
	#define CAL_SysGraphicInvalidateClientArea  pfSysGraphicInvalidateClientArea
	#define CHK_SysGraphicInvalidateClientArea  (pfSysGraphicInvalidateClientArea != NULL)
	#define EXP_SysGraphicInvalidateClientArea  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicInvalidateClientArea", (RTS_UINTPTR)SysGraphicInvalidateClientArea, 0, 0) 
#endif





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
RTS_HANDLE CDECL SysGraphicCreateTransformation(RTS_RESULT* pResult);
typedef RTS_HANDLE (CDECL * PFSYSGRAPHICCREATETRANSFORMATION) (RTS_RESULT* pResult);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCREATETRANSFORMATION_NOTIMPLEMENTED)
	#define USE_SysGraphicCreateTransformation
	#define EXT_SysGraphicCreateTransformation
	#define GET_SysGraphicCreateTransformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCreateTransformation(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysGraphicCreateTransformation  FALSE
	#define EXP_SysGraphicCreateTransformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCreateTransformation
	#define EXT_SysGraphicCreateTransformation
	#define GET_SysGraphicCreateTransformation(fl)  CAL_CMGETAPI( "SysGraphicCreateTransformation" ) 
	#define CAL_SysGraphicCreateTransformation  SysGraphicCreateTransformation
	#define CHK_SysGraphicCreateTransformation  TRUE
	#define EXP_SysGraphicCreateTransformation  CAL_CMEXPAPI( "SysGraphicCreateTransformation" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCreateTransformation
	#define EXT_SysGraphicCreateTransformation
	#define GET_SysGraphicCreateTransformation(fl)  CAL_CMGETAPI( "SysGraphicCreateTransformation" ) 
	#define CAL_SysGraphicCreateTransformation  SysGraphicCreateTransformation
	#define CHK_SysGraphicCreateTransformation  TRUE
	#define EXP_SysGraphicCreateTransformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateTransformation", (RTS_UINTPTR)SysGraphicCreateTransformation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCreateTransformation
	#define EXT_SysGraphicSysGraphicCreateTransformation
	#define GET_SysGraphicSysGraphicCreateTransformation  ERR_OK
	#define CAL_SysGraphicSysGraphicCreateTransformation  ((ISysGraphic*)s_pfCMCreateInstance(CLASSID_CSysGraphic, NULL))->ISysGraphicCreateTransformation
	#define CHK_SysGraphicSysGraphicCreateTransformation	(s_pfCMCreateInstance != NULL && pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicCreateTransformation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCreateTransformation
	#define EXT_SysGraphicCreateTransformation
	#define GET_SysGraphicCreateTransformation(fl)  CAL_CMGETAPI( "SysGraphicCreateTransformation" ) 
	#define CAL_SysGraphicCreateTransformation  ((ISysGraphic*)s_pfCMCreateInstance(CLASSID_CSysGraphic, NULL))->ISysGraphicCreateTransformation
	#define CHK_SysGraphicCreateTransformation	(s_pfCMCreateInstance != NULL && pISysGraphic != NULL)
	#define EXP_SysGraphicCreateTransformation  CAL_CMEXPAPI( "SysGraphicCreateTransformation" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCreateTransformation  PFSYSGRAPHICCREATETRANSFORMATION pfSysGraphicCreateTransformation;
	#define EXT_SysGraphicCreateTransformation  extern PFSYSGRAPHICCREATETRANSFORMATION pfSysGraphicCreateTransformation;
	#define GET_SysGraphicCreateTransformation(fl)  s_pfCMGetAPI2( "SysGraphicCreateTransformation", (RTS_VOID_FCTPTR *)&pfSysGraphicCreateTransformation, (fl), 0, 0)
	#define CAL_SysGraphicCreateTransformation  pfSysGraphicCreateTransformation
	#define CHK_SysGraphicCreateTransformation  (pfSysGraphicCreateTransformation != NULL)
	#define EXP_SysGraphicCreateTransformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateTransformation", (RTS_UINTPTR)SysGraphicCreateTransformation, 0, 0) 
#endif




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
RTS_HANDLE CDECL SysGraphicCreateTransformationByValues(RTS_REAL32 m11, RTS_REAL32 m12, RTS_REAL32 m21, RTS_REAL32 m22, RTS_REAL32 dx, RTS_REAL32 dy, RTS_RESULT* pResult);
typedef RTS_HANDLE (CDECL * PFSYSGRAPHICCREATETRANSFORMATIONBYVALUES) (RTS_REAL32 m11, RTS_REAL32 m12, RTS_REAL32 m21, RTS_REAL32 m22, RTS_REAL32 dx, RTS_REAL32 dy, RTS_RESULT* pResult);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCREATETRANSFORMATIONBYVALUES_NOTIMPLEMENTED)
	#define USE_SysGraphicCreateTransformationByValues
	#define EXT_SysGraphicCreateTransformationByValues
	#define GET_SysGraphicCreateTransformationByValues(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCreateTransformationByValues(p0,p1,p2,p3,p4,p5,p6)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysGraphicCreateTransformationByValues  FALSE
	#define EXP_SysGraphicCreateTransformationByValues  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCreateTransformationByValues
	#define EXT_SysGraphicCreateTransformationByValues
	#define GET_SysGraphicCreateTransformationByValues(fl)  CAL_CMGETAPI( "SysGraphicCreateTransformationByValues" ) 
	#define CAL_SysGraphicCreateTransformationByValues  SysGraphicCreateTransformationByValues
	#define CHK_SysGraphicCreateTransformationByValues  TRUE
	#define EXP_SysGraphicCreateTransformationByValues  CAL_CMEXPAPI( "SysGraphicCreateTransformationByValues" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCreateTransformationByValues
	#define EXT_SysGraphicCreateTransformationByValues
	#define GET_SysGraphicCreateTransformationByValues(fl)  CAL_CMGETAPI( "SysGraphicCreateTransformationByValues" ) 
	#define CAL_SysGraphicCreateTransformationByValues  SysGraphicCreateTransformationByValues
	#define CHK_SysGraphicCreateTransformationByValues  TRUE
	#define EXP_SysGraphicCreateTransformationByValues  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateTransformationByValues", (RTS_UINTPTR)SysGraphicCreateTransformationByValues, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCreateTransformationByValues
	#define EXT_SysGraphicSysGraphicCreateTransformationByValues
	#define GET_SysGraphicSysGraphicCreateTransformationByValues  ERR_OK
	#define CAL_SysGraphicSysGraphicCreateTransformationByValues  ((ISysGraphic*)s_pfCMCreateInstance(CLASSID_CSysGraphic, NULL))->ISysGraphicCreateTransformationByValues
	#define CHK_SysGraphicSysGraphicCreateTransformationByValues	(s_pfCMCreateInstance != NULL && pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicCreateTransformationByValues  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCreateTransformationByValues
	#define EXT_SysGraphicCreateTransformationByValues
	#define GET_SysGraphicCreateTransformationByValues(fl)  CAL_CMGETAPI( "SysGraphicCreateTransformationByValues" ) 
	#define CAL_SysGraphicCreateTransformationByValues  ((ISysGraphic*)s_pfCMCreateInstance(CLASSID_CSysGraphic, NULL))->ISysGraphicCreateTransformationByValues
	#define CHK_SysGraphicCreateTransformationByValues	(s_pfCMCreateInstance != NULL && pISysGraphic != NULL)
	#define EXP_SysGraphicCreateTransformationByValues  CAL_CMEXPAPI( "SysGraphicCreateTransformationByValues" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCreateTransformationByValues  PFSYSGRAPHICCREATETRANSFORMATIONBYVALUES pfSysGraphicCreateTransformationByValues;
	#define EXT_SysGraphicCreateTransformationByValues  extern PFSYSGRAPHICCREATETRANSFORMATIONBYVALUES pfSysGraphicCreateTransformationByValues;
	#define GET_SysGraphicCreateTransformationByValues(fl)  s_pfCMGetAPI2( "SysGraphicCreateTransformationByValues", (RTS_VOID_FCTPTR *)&pfSysGraphicCreateTransformationByValues, (fl), 0, 0)
	#define CAL_SysGraphicCreateTransformationByValues  pfSysGraphicCreateTransformationByValues
	#define CHK_SysGraphicCreateTransformationByValues  (pfSysGraphicCreateTransformationByValues != NULL)
	#define EXP_SysGraphicCreateTransformationByValues  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCreateTransformationByValues", (RTS_UINTPTR)SysGraphicCreateTransformationByValues, 0, 0) 
#endif




/**
 * <description>Deletes an affine transformation object.</description>	
 * <param name="hTransform" type="IN">The transformation to delete.</param>
 * <result>An error code</result>
*/ 
RTS_RESULT CDECL SysGraphicFreeTransformation(RTS_HANDLE hTransform);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICFREETRANSFORMATION) (RTS_HANDLE hTransform);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICFREETRANSFORMATION_NOTIMPLEMENTED)
	#define USE_SysGraphicFreeTransformation
	#define EXT_SysGraphicFreeTransformation
	#define GET_SysGraphicFreeTransformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicFreeTransformation(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicFreeTransformation  FALSE
	#define EXP_SysGraphicFreeTransformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicFreeTransformation
	#define EXT_SysGraphicFreeTransformation
	#define GET_SysGraphicFreeTransformation(fl)  CAL_CMGETAPI( "SysGraphicFreeTransformation" ) 
	#define CAL_SysGraphicFreeTransformation  SysGraphicFreeTransformation
	#define CHK_SysGraphicFreeTransformation  TRUE
	#define EXP_SysGraphicFreeTransformation  CAL_CMEXPAPI( "SysGraphicFreeTransformation" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicFreeTransformation
	#define EXT_SysGraphicFreeTransformation
	#define GET_SysGraphicFreeTransformation(fl)  CAL_CMGETAPI( "SysGraphicFreeTransformation" ) 
	#define CAL_SysGraphicFreeTransformation  SysGraphicFreeTransformation
	#define CHK_SysGraphicFreeTransformation  TRUE
	#define EXP_SysGraphicFreeTransformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFreeTransformation", (RTS_UINTPTR)SysGraphicFreeTransformation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicFreeTransformation
	#define EXT_SysGraphicSysGraphicFreeTransformation
	#define GET_SysGraphicSysGraphicFreeTransformation  ERR_OK
	#define CAL_SysGraphicSysGraphicFreeTransformation(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysGraphic*)p0)->ISysGraphicFreeTransformation())
	#define CHK_SysGraphicSysGraphicFreeTransformation  TRUE
	#define EXP_SysGraphicSysGraphicFreeTransformation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicFreeTransformation
	#define EXT_SysGraphicFreeTransformation
	#define GET_SysGraphicFreeTransformation(fl)  CAL_CMGETAPI( "SysGraphicFreeTransformation" ) 
	#define CAL_SysGraphicFreeTransformation(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysGraphic*)p0)->ISysGraphicFreeTransformation())
	#define CHK_SysGraphicFreeTransformation  TRUE
	#define EXP_SysGraphicFreeTransformation  CAL_CMEXPAPI( "SysGraphicFreeTransformation" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicFreeTransformation  PFSYSGRAPHICFREETRANSFORMATION pfSysGraphicFreeTransformation;
	#define EXT_SysGraphicFreeTransformation  extern PFSYSGRAPHICFREETRANSFORMATION pfSysGraphicFreeTransformation;
	#define GET_SysGraphicFreeTransformation(fl)  s_pfCMGetAPI2( "SysGraphicFreeTransformation", (RTS_VOID_FCTPTR *)&pfSysGraphicFreeTransformation, (fl), 0, 0)
	#define CAL_SysGraphicFreeTransformation  pfSysGraphicFreeTransformation
	#define CHK_SysGraphicFreeTransformation  (pfSysGraphicFreeTransformation != NULL)
	#define EXP_SysGraphicFreeTransformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFreeTransformation", (RTS_UINTPTR)SysGraphicFreeTransformation, 0, 0) 
#endif




/**
 * <description>Applies a scaling operation to the transformation object. The origin of the coordinate system (could have been moved by a previous 
 *	call to <see>SysGraphicTransformationTranslate</see> will be used as the origin for the scaling operation.</description>	
 * <param name="hTransform" type="IN">The transformation to scale.</param>
 * <param name="x" type="IN">The factor to scale in horizontal direction.</param>
 * <param name="y" type="IN">The factor to scale in vertical direction.</param>
 * <result>An error code</result>
*/ 
RTS_RESULT CDECL SysGraphicTransformationScale(RTS_HANDLE hTransform, RTS_REAL32 x, RTS_REAL32 y);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICTRANSFORMATIONSCALE) (RTS_HANDLE hTransform, RTS_REAL32 x, RTS_REAL32 y);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICTRANSFORMATIONSCALE_NOTIMPLEMENTED)
	#define USE_SysGraphicTransformationScale
	#define EXT_SysGraphicTransformationScale
	#define GET_SysGraphicTransformationScale(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicTransformationScale(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicTransformationScale  FALSE
	#define EXP_SysGraphicTransformationScale  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicTransformationScale
	#define EXT_SysGraphicTransformationScale
	#define GET_SysGraphicTransformationScale(fl)  CAL_CMGETAPI( "SysGraphicTransformationScale" ) 
	#define CAL_SysGraphicTransformationScale  SysGraphicTransformationScale
	#define CHK_SysGraphicTransformationScale  TRUE
	#define EXP_SysGraphicTransformationScale  CAL_CMEXPAPI( "SysGraphicTransformationScale" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicTransformationScale
	#define EXT_SysGraphicTransformationScale
	#define GET_SysGraphicTransformationScale(fl)  CAL_CMGETAPI( "SysGraphicTransformationScale" ) 
	#define CAL_SysGraphicTransformationScale  SysGraphicTransformationScale
	#define CHK_SysGraphicTransformationScale  TRUE
	#define EXP_SysGraphicTransformationScale  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTransformationScale", (RTS_UINTPTR)SysGraphicTransformationScale, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicTransformationScale
	#define EXT_SysGraphicSysGraphicTransformationScale
	#define GET_SysGraphicSysGraphicTransformationScale  ERR_OK
	#define CAL_SysGraphicSysGraphicTransformationScale(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicTransformationScale(p1,p2) : ((ISysGraphic*)p0)->ISysGraphicTransformationScale(p1,p2))
	#define CHK_SysGraphicSysGraphicTransformationScale  (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicTransformationScale  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicTransformationScale
	#define EXT_SysGraphicTransformationScale
	#define GET_SysGraphicTransformationScale(fl)  CAL_CMGETAPI( "SysGraphicTransformationScale" ) 
	#define CAL_SysGraphicTransformationScale(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicTransformationScale(p1,p2) : ((ISysGraphic*)p0)->ISysGraphicTransformationScale(p1,p2))
	#define CHK_SysGraphicTransformationScale  (pISysGraphic != NULL)
	#define EXP_SysGraphicTransformationScale  CAL_CMEXPAPI( "SysGraphicTransformationScale" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicTransformationScale  PFSYSGRAPHICTRANSFORMATIONSCALE pfSysGraphicTransformationScale;
	#define EXT_SysGraphicTransformationScale  extern PFSYSGRAPHICTRANSFORMATIONSCALE pfSysGraphicTransformationScale;
	#define GET_SysGraphicTransformationScale(fl)  s_pfCMGetAPI2( "SysGraphicTransformationScale", (RTS_VOID_FCTPTR *)&pfSysGraphicTransformationScale, (fl), 0, 0)
	#define CAL_SysGraphicTransformationScale  pfSysGraphicTransformationScale
	#define CHK_SysGraphicTransformationScale  (pfSysGraphicTransformationScale != NULL)
	#define EXP_SysGraphicTransformationScale  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTransformationScale", (RTS_UINTPTR)SysGraphicTransformationScale, 0, 0) 
#endif




/**
 * <description>Applies a rotation operation to the transformation object. The origin of the coordinate system (could have been moved by a previous 
 *	call to <see>SysGraphicTransformationTranslate</see> will be used as the center for the rotation operation.</description>	
 * <param name="hTransform" type="IN">The transformation to rotate.</param>
 * <param name="angle" type="IN">The angle of the rotation in degrees. Positive values specify clockwise rotation.</param>
 * <result>An error code</result>
*/ 
RTS_RESULT CDECL SysGraphicTransformationRotate(RTS_HANDLE hTransform, RTS_REAL32 angle);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICTRANSFORMATIONROTATE) (RTS_HANDLE hTransform, RTS_REAL32 angle);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICTRANSFORMATIONROTATE_NOTIMPLEMENTED)
	#define USE_SysGraphicTransformationRotate
	#define EXT_SysGraphicTransformationRotate
	#define GET_SysGraphicTransformationRotate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicTransformationRotate(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicTransformationRotate  FALSE
	#define EXP_SysGraphicTransformationRotate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicTransformationRotate
	#define EXT_SysGraphicTransformationRotate
	#define GET_SysGraphicTransformationRotate(fl)  CAL_CMGETAPI( "SysGraphicTransformationRotate" ) 
	#define CAL_SysGraphicTransformationRotate  SysGraphicTransformationRotate
	#define CHK_SysGraphicTransformationRotate  TRUE
	#define EXP_SysGraphicTransformationRotate  CAL_CMEXPAPI( "SysGraphicTransformationRotate" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicTransformationRotate
	#define EXT_SysGraphicTransformationRotate
	#define GET_SysGraphicTransformationRotate(fl)  CAL_CMGETAPI( "SysGraphicTransformationRotate" ) 
	#define CAL_SysGraphicTransformationRotate  SysGraphicTransformationRotate
	#define CHK_SysGraphicTransformationRotate  TRUE
	#define EXP_SysGraphicTransformationRotate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTransformationRotate", (RTS_UINTPTR)SysGraphicTransformationRotate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicTransformationRotate
	#define EXT_SysGraphicSysGraphicTransformationRotate
	#define GET_SysGraphicSysGraphicTransformationRotate  ERR_OK
	#define CAL_SysGraphicSysGraphicTransformationRotate(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicTransformationRotate(p1) : ((ISysGraphic*)p0)->ISysGraphicTransformationRotate(p1))
	#define CHK_SysGraphicSysGraphicTransformationRotate  (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicTransformationRotate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicTransformationRotate
	#define EXT_SysGraphicTransformationRotate
	#define GET_SysGraphicTransformationRotate(fl)  CAL_CMGETAPI( "SysGraphicTransformationRotate" ) 
	#define CAL_SysGraphicTransformationRotate(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicTransformationRotate(p1) : ((ISysGraphic*)p0)->ISysGraphicTransformationRotate(p1))
	#define CHK_SysGraphicTransformationRotate  (pISysGraphic != NULL)
	#define EXP_SysGraphicTransformationRotate  CAL_CMEXPAPI( "SysGraphicTransformationRotate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicTransformationRotate  PFSYSGRAPHICTRANSFORMATIONROTATE pfSysGraphicTransformationRotate;
	#define EXT_SysGraphicTransformationRotate  extern PFSYSGRAPHICTRANSFORMATIONROTATE pfSysGraphicTransformationRotate;
	#define GET_SysGraphicTransformationRotate(fl)  s_pfCMGetAPI2( "SysGraphicTransformationRotate", (RTS_VOID_FCTPTR *)&pfSysGraphicTransformationRotate, (fl), 0, 0)
	#define CAL_SysGraphicTransformationRotate  pfSysGraphicTransformationRotate
	#define CHK_SysGraphicTransformationRotate  (pfSysGraphicTransformationRotate != NULL)
	#define EXP_SysGraphicTransformationRotate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTransformationRotate", (RTS_UINTPTR)SysGraphicTransformationRotate, 0, 0) 
#endif




/**
 * <description>Applies a translation operation to the transformation object. </description>	
 * <param name="hTransform" type="IN">The transformation to translate.</param>
 * <param name="x" type="IN">The offset to shift in horizontal direction.</param>
 * <param name="y" type="IN">The offset to shift in vertical direction.</param>
 * <result>An error code</result>
*/ 
RTS_RESULT CDECL SysGraphicTransformationTranslate(RTS_HANDLE hTransform, RTS_REAL32 x, RTS_REAL32 y);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICTRANSFORMATIONTRANSLATE) (RTS_HANDLE hTransform, RTS_REAL32 x, RTS_REAL32 y);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICTRANSFORMATIONTRANSLATE_NOTIMPLEMENTED)
	#define USE_SysGraphicTransformationTranslate
	#define EXT_SysGraphicTransformationTranslate
	#define GET_SysGraphicTransformationTranslate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicTransformationTranslate(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicTransformationTranslate  FALSE
	#define EXP_SysGraphicTransformationTranslate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicTransformationTranslate
	#define EXT_SysGraphicTransformationTranslate
	#define GET_SysGraphicTransformationTranslate(fl)  CAL_CMGETAPI( "SysGraphicTransformationTranslate" ) 
	#define CAL_SysGraphicTransformationTranslate  SysGraphicTransformationTranslate
	#define CHK_SysGraphicTransformationTranslate  TRUE
	#define EXP_SysGraphicTransformationTranslate  CAL_CMEXPAPI( "SysGraphicTransformationTranslate" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicTransformationTranslate
	#define EXT_SysGraphicTransformationTranslate
	#define GET_SysGraphicTransformationTranslate(fl)  CAL_CMGETAPI( "SysGraphicTransformationTranslate" ) 
	#define CAL_SysGraphicTransformationTranslate  SysGraphicTransformationTranslate
	#define CHK_SysGraphicTransformationTranslate  TRUE
	#define EXP_SysGraphicTransformationTranslate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTransformationTranslate", (RTS_UINTPTR)SysGraphicTransformationTranslate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicTransformationTranslate
	#define EXT_SysGraphicSysGraphicTransformationTranslate
	#define GET_SysGraphicSysGraphicTransformationTranslate  ERR_OK
	#define CAL_SysGraphicSysGraphicTransformationTranslate(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicTransformationTranslate(p1,p2) : ((ISysGraphic*)p0)->ISysGraphicTransformationTranslate(p1,p2))
	#define CHK_SysGraphicSysGraphicTransformationTranslate  (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicTransformationTranslate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicTransformationTranslate
	#define EXT_SysGraphicTransformationTranslate
	#define GET_SysGraphicTransformationTranslate(fl)  CAL_CMGETAPI( "SysGraphicTransformationTranslate" ) 
	#define CAL_SysGraphicTransformationTranslate(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicTransformationTranslate(p1,p2) : ((ISysGraphic*)p0)->ISysGraphicTransformationTranslate(p1,p2))
	#define CHK_SysGraphicTransformationTranslate  (pISysGraphic != NULL)
	#define EXP_SysGraphicTransformationTranslate  CAL_CMEXPAPI( "SysGraphicTransformationTranslate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicTransformationTranslate  PFSYSGRAPHICTRANSFORMATIONTRANSLATE pfSysGraphicTransformationTranslate;
	#define EXT_SysGraphicTransformationTranslate  extern PFSYSGRAPHICTRANSFORMATIONTRANSLATE pfSysGraphicTransformationTranslate;
	#define GET_SysGraphicTransformationTranslate(fl)  s_pfCMGetAPI2( "SysGraphicTransformationTranslate", (RTS_VOID_FCTPTR *)&pfSysGraphicTransformationTranslate, (fl), 0, 0)
	#define CAL_SysGraphicTransformationTranslate  pfSysGraphicTransformationTranslate
	#define CHK_SysGraphicTransformationTranslate  (pfSysGraphicTransformationTranslate != NULL)
	#define EXP_SysGraphicTransformationTranslate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTransformationTranslate", (RTS_UINTPTR)SysGraphicTransformationTranslate, 0, 0) 
#endif




/**
 * <description>Activates an affine transformation object on the given device context. This transformation will be applied to modify
 *	all followup drawing operations on this device context until a different (or no) transformation is set.</description>	
 * <param name="hdc" type="IN">The device context to apply the transformation on.</param>
 * <param name="hTransform" type="IN">The transformation to apply. Pass RTS_INVALID_HANDLE to deactivate any transformations.</param>
 * <result>An error code</result>
*/ 
RTS_RESULT CDECL SysGraphicSetActiveTransformation(RTS_HANDLE hdc, RTS_HANDLE hTransform);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICSETACTIVETRANSFORMATION) (RTS_HANDLE hdc, RTS_HANDLE hTransform);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICSETACTIVETRANSFORMATION_NOTIMPLEMENTED)
	#define USE_SysGraphicSetActiveTransformation
	#define EXT_SysGraphicSetActiveTransformation
	#define GET_SysGraphicSetActiveTransformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicSetActiveTransformation(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicSetActiveTransformation  FALSE
	#define EXP_SysGraphicSetActiveTransformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicSetActiveTransformation
	#define EXT_SysGraphicSetActiveTransformation
	#define GET_SysGraphicSetActiveTransformation(fl)  CAL_CMGETAPI( "SysGraphicSetActiveTransformation" ) 
	#define CAL_SysGraphicSetActiveTransformation  SysGraphicSetActiveTransformation
	#define CHK_SysGraphicSetActiveTransformation  TRUE
	#define EXP_SysGraphicSetActiveTransformation  CAL_CMEXPAPI( "SysGraphicSetActiveTransformation" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicSetActiveTransformation
	#define EXT_SysGraphicSetActiveTransformation
	#define GET_SysGraphicSetActiveTransformation(fl)  CAL_CMGETAPI( "SysGraphicSetActiveTransformation" ) 
	#define CAL_SysGraphicSetActiveTransformation  SysGraphicSetActiveTransformation
	#define CHK_SysGraphicSetActiveTransformation  TRUE
	#define EXP_SysGraphicSetActiveTransformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetActiveTransformation", (RTS_UINTPTR)SysGraphicSetActiveTransformation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicSetActiveTransformation
	#define EXT_SysGraphicSysGraphicSetActiveTransformation
	#define GET_SysGraphicSysGraphicSetActiveTransformation  ERR_OK
	#define CAL_SysGraphicSysGraphicSetActiveTransformation(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicSetActiveTransformation(p1) : ((ISysGraphic*)p0)->ISysGraphicSetActiveTransformation(p1))
	#define CHK_SysGraphicSysGraphicSetActiveTransformation  (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicSetActiveTransformation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicSetActiveTransformation
	#define EXT_SysGraphicSetActiveTransformation
	#define GET_SysGraphicSetActiveTransformation(fl)  CAL_CMGETAPI( "SysGraphicSetActiveTransformation" ) 
	#define CAL_SysGraphicSetActiveTransformation(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicSetActiveTransformation(p1) : ((ISysGraphic*)p0)->ISysGraphicSetActiveTransformation(p1))
	#define CHK_SysGraphicSetActiveTransformation  (pISysGraphic != NULL)
	#define EXP_SysGraphicSetActiveTransformation  CAL_CMEXPAPI( "SysGraphicSetActiveTransformation" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicSetActiveTransformation  PFSYSGRAPHICSETACTIVETRANSFORMATION pfSysGraphicSetActiveTransformation;
	#define EXT_SysGraphicSetActiveTransformation  extern PFSYSGRAPHICSETACTIVETRANSFORMATION pfSysGraphicSetActiveTransformation;
	#define GET_SysGraphicSetActiveTransformation(fl)  s_pfCMGetAPI2( "SysGraphicSetActiveTransformation", (RTS_VOID_FCTPTR *)&pfSysGraphicSetActiveTransformation, (fl), 0, 0)
	#define CAL_SysGraphicSetActiveTransformation  pfSysGraphicSetActiveTransformation
	#define CHK_SysGraphicSetActiveTransformation  (pfSysGraphicSetActiveTransformation != NULL)
	#define EXP_SysGraphicSetActiveTransformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicSetActiveTransformation", (RTS_UINTPTR)SysGraphicSetActiveTransformation, 0, 0) 
#endif




/**
 * <description>Returns the currently active affine transformation object on the given device context.</description>	
 * <param name="hdc" type="IN">The device context to retrieve the the transformation from.</param>
 * <param name="hTransform" type="IN">The transformation to apply. Pass RTS_INVALID_HANDLE to deactivate any transformations.</param>
 * <param name="pResult" type="OUT">Optional pointer to error code</param>
 * <result>The handle or the active transformation or RTS_INVALID_HANDLE if there was no active one..</result>
*/ 
RTS_HANDLE CDECL SysGraphicGetActiveTransformation(RTS_HANDLE hdc, RTS_RESULT* pResult);
typedef RTS_HANDLE (CDECL * PFSYSGRAPHICGETACTIVETRANSFORMATION) (RTS_HANDLE hdc, RTS_RESULT* pResult);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICGETACTIVETRANSFORMATION_NOTIMPLEMENTED)
	#define USE_SysGraphicGetActiveTransformation
	#define EXT_SysGraphicGetActiveTransformation
	#define GET_SysGraphicGetActiveTransformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicGetActiveTransformation(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysGraphicGetActiveTransformation  FALSE
	#define EXP_SysGraphicGetActiveTransformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicGetActiveTransformation
	#define EXT_SysGraphicGetActiveTransformation
	#define GET_SysGraphicGetActiveTransformation(fl)  CAL_CMGETAPI( "SysGraphicGetActiveTransformation" ) 
	#define CAL_SysGraphicGetActiveTransformation  SysGraphicGetActiveTransformation
	#define CHK_SysGraphicGetActiveTransformation  TRUE
	#define EXP_SysGraphicGetActiveTransformation  CAL_CMEXPAPI( "SysGraphicGetActiveTransformation" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicGetActiveTransformation
	#define EXT_SysGraphicGetActiveTransformation
	#define GET_SysGraphicGetActiveTransformation(fl)  CAL_CMGETAPI( "SysGraphicGetActiveTransformation" ) 
	#define CAL_SysGraphicGetActiveTransformation  SysGraphicGetActiveTransformation
	#define CHK_SysGraphicGetActiveTransformation  TRUE
	#define EXP_SysGraphicGetActiveTransformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetActiveTransformation", (RTS_UINTPTR)SysGraphicGetActiveTransformation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicGetActiveTransformation
	#define EXT_SysGraphicSysGraphicGetActiveTransformation
	#define GET_SysGraphicSysGraphicGetActiveTransformation  ERR_OK
	#define CAL_SysGraphicSysGraphicGetActiveTransformation(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicGetActiveTransformation(p1) : ((ISysGraphic*)p0)->ISysGraphicGetActiveTransformation(p1))
	#define CHK_SysGraphicSysGraphicGetActiveTransformation  (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicGetActiveTransformation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicGetActiveTransformation
	#define EXT_SysGraphicGetActiveTransformation
	#define GET_SysGraphicGetActiveTransformation(fl)  CAL_CMGETAPI( "SysGraphicGetActiveTransformation" ) 
	#define CAL_SysGraphicGetActiveTransformation(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicGetActiveTransformation(p1) : ((ISysGraphic*)p0)->ISysGraphicGetActiveTransformation(p1))
	#define CHK_SysGraphicGetActiveTransformation  (pISysGraphic != NULL)
	#define EXP_SysGraphicGetActiveTransformation  CAL_CMEXPAPI( "SysGraphicGetActiveTransformation" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicGetActiveTransformation  PFSYSGRAPHICGETACTIVETRANSFORMATION pfSysGraphicGetActiveTransformation;
	#define EXT_SysGraphicGetActiveTransformation  extern PFSYSGRAPHICGETACTIVETRANSFORMATION pfSysGraphicGetActiveTransformation;
	#define GET_SysGraphicGetActiveTransformation(fl)  s_pfCMGetAPI2( "SysGraphicGetActiveTransformation", (RTS_VOID_FCTPTR *)&pfSysGraphicGetActiveTransformation, (fl), 0, 0)
	#define CAL_SysGraphicGetActiveTransformation  pfSysGraphicGetActiveTransformation
	#define CHK_SysGraphicGetActiveTransformation  (pfSysGraphicGetActiveTransformation != NULL)
	#define EXP_SysGraphicGetActiveTransformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicGetActiveTransformation", (RTS_UINTPTR)SysGraphicGetActiveTransformation, 0, 0) 
#endif




/**
 * <description>Creates a new affine transformation object that is a copy of an existing affine transformation object.</description>
 * <param name="hTransform" type="IN">A handle to the object to clone.</param>	
 * <param name="pResult" type="OUT">Optional pointer to error code.</param>
 * <result>A handle to the created transformation object or RTS_INVALID_HANDLE if there was an error.</result>
*/ 
RTS_HANDLE CDECL SysGraphicCloneTransformation(RTS_HANDLE hTransform, RTS_RESULT* pResult);
typedef RTS_HANDLE (CDECL * PFSYSGRAPHICCLONETRANSFORMATION) (RTS_HANDLE hTransform, RTS_RESULT* pResult);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICCLONETRANSFORMATION_NOTIMPLEMENTED)
	#define USE_SysGraphicCloneTransformation
	#define EXT_SysGraphicCloneTransformation
	#define GET_SysGraphicCloneTransformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicCloneTransformation(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysGraphicCloneTransformation  FALSE
	#define EXP_SysGraphicCloneTransformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicCloneTransformation
	#define EXT_SysGraphicCloneTransformation
	#define GET_SysGraphicCloneTransformation(fl)  CAL_CMGETAPI( "SysGraphicCloneTransformation" ) 
	#define CAL_SysGraphicCloneTransformation  SysGraphicCloneTransformation
	#define CHK_SysGraphicCloneTransformation  TRUE
	#define EXP_SysGraphicCloneTransformation  CAL_CMEXPAPI( "SysGraphicCloneTransformation" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicCloneTransformation
	#define EXT_SysGraphicCloneTransformation
	#define GET_SysGraphicCloneTransformation(fl)  CAL_CMGETAPI( "SysGraphicCloneTransformation" ) 
	#define CAL_SysGraphicCloneTransformation  SysGraphicCloneTransformation
	#define CHK_SysGraphicCloneTransformation  TRUE
	#define EXP_SysGraphicCloneTransformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCloneTransformation", (RTS_UINTPTR)SysGraphicCloneTransformation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicCloneTransformation
	#define EXT_SysGraphicSysGraphicCloneTransformation
	#define GET_SysGraphicSysGraphicCloneTransformation  ERR_OK
	#define CAL_SysGraphicSysGraphicCloneTransformation  ((ISysGraphic*)s_pfCMCreateInstance(CLASSID_CSysGraphic, NULL))->ISysGraphicCloneTransformation
	#define CHK_SysGraphicSysGraphicCloneTransformation	(s_pfCMCreateInstance != NULL && pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicCloneTransformation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicCloneTransformation
	#define EXT_SysGraphicCloneTransformation
	#define GET_SysGraphicCloneTransformation(fl)  CAL_CMGETAPI( "SysGraphicCloneTransformation" ) 
	#define CAL_SysGraphicCloneTransformation  ((ISysGraphic*)s_pfCMCreateInstance(CLASSID_CSysGraphic, NULL))->ISysGraphicCloneTransformation
	#define CHK_SysGraphicCloneTransformation	(s_pfCMCreateInstance != NULL && pISysGraphic != NULL)
	#define EXP_SysGraphicCloneTransformation  CAL_CMEXPAPI( "SysGraphicCloneTransformation" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicCloneTransformation  PFSYSGRAPHICCLONETRANSFORMATION pfSysGraphicCloneTransformation;
	#define EXT_SysGraphicCloneTransformation  extern PFSYSGRAPHICCLONETRANSFORMATION pfSysGraphicCloneTransformation;
	#define GET_SysGraphicCloneTransformation(fl)  s_pfCMGetAPI2( "SysGraphicCloneTransformation", (RTS_VOID_FCTPTR *)&pfSysGraphicCloneTransformation, (fl), 0, 0)
	#define CAL_SysGraphicCloneTransformation  pfSysGraphicCloneTransformation
	#define CHK_SysGraphicCloneTransformation  (pfSysGraphicCloneTransformation != NULL)
	#define EXP_SysGraphicCloneTransformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicCloneTransformation", (RTS_UINTPTR)SysGraphicCloneTransformation, 0, 0) 
#endif




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
RTS_RESULT CDECL SysGraphicTransformationTransform(RTS_HANDLE hTransform, RTS_REAL32 m11, RTS_REAL32 m12, RTS_REAL32 m21, RTS_REAL32 m22, RTS_REAL32 dx, RTS_REAL32 dy);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICTRANSFORMATIONTRANSFORM) (RTS_HANDLE hTransform, RTS_REAL32 m11, RTS_REAL32 m12, RTS_REAL32 m21, RTS_REAL32 m22, RTS_REAL32 dx, RTS_REAL32 dy);
#if defined(SYSGRAPHIC_NOTIMPLEMENTED) || defined(SYSGRAPHICTRANSFORMATIONTRANSFORM_NOTIMPLEMENTED)
	#define USE_SysGraphicTransformationTransform
	#define EXT_SysGraphicTransformationTransform
	#define GET_SysGraphicTransformationTransform(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicTransformationTransform(p0,p1,p2,p3,p4,p5,p6)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicTransformationTransform  FALSE
	#define EXP_SysGraphicTransformationTransform  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicTransformationTransform
	#define EXT_SysGraphicTransformationTransform
	#define GET_SysGraphicTransformationTransform(fl)  CAL_CMGETAPI( "SysGraphicTransformationTransform" ) 
	#define CAL_SysGraphicTransformationTransform  SysGraphicTransformationTransform
	#define CHK_SysGraphicTransformationTransform  TRUE
	#define EXP_SysGraphicTransformationTransform  CAL_CMEXPAPI( "SysGraphicTransformationTransform" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHIC_EXTERNAL)
	#define USE_SysGraphicTransformationTransform
	#define EXT_SysGraphicTransformationTransform
	#define GET_SysGraphicTransformationTransform(fl)  CAL_CMGETAPI( "SysGraphicTransformationTransform" ) 
	#define CAL_SysGraphicTransformationTransform  SysGraphicTransformationTransform
	#define CHK_SysGraphicTransformationTransform  TRUE
	#define EXP_SysGraphicTransformationTransform  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTransformationTransform", (RTS_UINTPTR)SysGraphicTransformationTransform, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicSysGraphicTransformationTransform
	#define EXT_SysGraphicSysGraphicTransformationTransform
	#define GET_SysGraphicSysGraphicTransformationTransform  ERR_OK
	#define CAL_SysGraphicSysGraphicTransformationTransform(p0,p1,p2,p3,p4,p5,p6)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicTransformationTransform(p1,p2,p3,p4,p5,p6) : ((ISysGraphic*)p0)->ISysGraphicTransformationTransform(p1,p2,p3,p4,p5,p6))
	#define CHK_SysGraphicSysGraphicTransformationTransform  (pISysGraphic != NULL)
	#define EXP_SysGraphicSysGraphicTransformationTransform  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicTransformationTransform
	#define EXT_SysGraphicTransformationTransform
	#define GET_SysGraphicTransformationTransform(fl)  CAL_CMGETAPI( "SysGraphicTransformationTransform" ) 
	#define CAL_SysGraphicTransformationTransform(p0,p1,p2,p3,p4,p5,p6)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysGraphic->ISysGraphicTransformationTransform(p1,p2,p3,p4,p5,p6) : ((ISysGraphic*)p0)->ISysGraphicTransformationTransform(p1,p2,p3,p4,p5,p6))
	#define CHK_SysGraphicTransformationTransform  (pISysGraphic != NULL)
	#define EXP_SysGraphicTransformationTransform  CAL_CMEXPAPI( "SysGraphicTransformationTransform" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicTransformationTransform  PFSYSGRAPHICTRANSFORMATIONTRANSFORM pfSysGraphicTransformationTransform;
	#define EXT_SysGraphicTransformationTransform  extern PFSYSGRAPHICTRANSFORMATIONTRANSFORM pfSysGraphicTransformationTransform;
	#define GET_SysGraphicTransformationTransform(fl)  s_pfCMGetAPI2( "SysGraphicTransformationTransform", (RTS_VOID_FCTPTR *)&pfSysGraphicTransformationTransform, (fl), 0, 0)
	#define CAL_SysGraphicTransformationTransform  pfSysGraphicTransformationTransform
	#define CHK_SysGraphicTransformationTransform  (pfSysGraphicTransformationTransform != NULL)
	#define EXP_SysGraphicTransformationTransform  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTransformationTransform", (RTS_UINTPTR)SysGraphicTransformationTransform, 0, 0) 
#endif





#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSGRAPHICCREATEGRADIENTBRUSH ISysGraphicCreateGradientBrush;
 	PFSYSGRAPHICCREATEPATTERNBRUSH ISysGraphicCreatePatternBrush;
 	PFSYSGRAPHICSETANTIALIASINGMODE ISysGraphicSetAntiAliasingMode;
 	PFSYSGRAPHICGETSYSWINDOWFONT ISysGraphicGetSysWindowFont;
 	PFSYSGRAPHICINVALIDATERECTANGLE ISysGraphicInvalidateRectangle;
 	PFSYSGRAPHICRESETINVALIDATION ISysGraphicResetInvalidation;
 	PFSYSGRAPHICINVALIDATECLIENTAREA ISysGraphicInvalidateClientArea;
 	PFSYSGRAPHICCREATETRANSFORMATION ISysGraphicCreateTransformation;
 	PFSYSGRAPHICCREATETRANSFORMATIONBYVALUES ISysGraphicCreateTransformationByValues;
 	PFSYSGRAPHICFREETRANSFORMATION ISysGraphicFreeTransformation;
 	PFSYSGRAPHICTRANSFORMATIONSCALE ISysGraphicTransformationScale;
 	PFSYSGRAPHICTRANSFORMATIONROTATE ISysGraphicTransformationRotate;
 	PFSYSGRAPHICTRANSFORMATIONTRANSLATE ISysGraphicTransformationTranslate;
 	PFSYSGRAPHICSETACTIVETRANSFORMATION ISysGraphicSetActiveTransformation;
 	PFSYSGRAPHICGETACTIVETRANSFORMATION ISysGraphicGetActiveTransformation;
 	PFSYSGRAPHICCLONETRANSFORMATION ISysGraphicCloneTransformation;
 	PFSYSGRAPHICTRANSFORMATIONTRANSFORM ISysGraphicTransformationTransform;
 } ISysGraphic_C;

#ifdef CPLUSPLUS
class ISysGraphic : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISysGraphicCreateGradientBrush(RTS_HANDLE hDC, GradientData* gradient, RTS_Rectangle rectangle, RTS_HANDLE* phBrush) =0;
		virtual RTS_RESULT CDECL ISysGraphicCreatePatternBrush(RTS_HANDLE hDC, RTS_UI16 patternType, RTS_UI32 color, RTS_HANDLE* phBrush) =0;
		virtual RTS_RESULT CDECL ISysGraphicSetAntiAliasingMode(RTS_HANDLE hDC, RTS_UI32 uiAntiAliasingSettings) =0;
		virtual RTS_RESULT CDECL ISysGraphicGetSysWindowFont(RTS_HANDLE hDC, RTS_HANDLE hSysGraphicFont, RTS_HANDLE* phSysWindowFont) =0;
		virtual RTS_RESULT CDECL ISysGraphicInvalidateRectangle(RTS_HANDLE hDC, RTS_Rectangle rect) =0;
		virtual RTS_RESULT CDECL ISysGraphicResetInvalidation(RTS_HANDLE hDC) =0;
		virtual RTS_RESULT CDECL ISysGraphicInvalidateClientArea(RTS_HANDLE hDC) =0;
		virtual RTS_HANDLE CDECL ISysGraphicCreateTransformation(RTS_RESULT* pResult) =0;
		virtual RTS_HANDLE CDECL ISysGraphicCreateTransformationByValues(RTS_REAL32 m11, RTS_REAL32 m12, RTS_REAL32 m21, RTS_REAL32 m22, RTS_REAL32 dx, RTS_REAL32 dy, RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL ISysGraphicFreeTransformation(void) =0;
		virtual RTS_RESULT CDECL ISysGraphicTransformationScale(RTS_REAL32 x, RTS_REAL32 y) =0;
		virtual RTS_RESULT CDECL ISysGraphicTransformationRotate(RTS_REAL32 angle) =0;
		virtual RTS_RESULT CDECL ISysGraphicTransformationTranslate(RTS_REAL32 x, RTS_REAL32 y) =0;
		virtual RTS_RESULT CDECL ISysGraphicSetActiveTransformation(RTS_HANDLE hTransform) =0;
		virtual RTS_HANDLE CDECL ISysGraphicGetActiveTransformation(RTS_RESULT* pResult) =0;
		virtual RTS_HANDLE CDECL ISysGraphicCloneTransformation(RTS_HANDLE hTransform, RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL ISysGraphicTransformationTransform(RTS_REAL32 m11, RTS_REAL32 m12, RTS_REAL32 m21, RTS_REAL32 m22, RTS_REAL32 dx, RTS_REAL32 dy) =0;
};
	#ifndef ITF_SysGraphic
		#define ITF_SysGraphic static ISysGraphic *pISysGraphic = NULL;
	#endif
	#define EXTITF_SysGraphic
#else	/*CPLUSPLUS*/
	typedef ISysGraphic_C		ISysGraphic;
	#ifndef ITF_SysGraphic
		#define ITF_SysGraphic
	#endif
	#define EXTITF_SysGraphic
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSGRAPHICITF_H_*/
