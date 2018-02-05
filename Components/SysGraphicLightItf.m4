/**
 * <interfacename>SysGraphicLight</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`SysGraphicLight')

#ifndef CDECL
	#define CDECL
#endif

#include "SysGraphicBase.h"
#include "CmpStd.h"

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
#define TF_BGELEM						0x80000000
#define TF_WSTRING						0x40000000

/**
 * <category>Font style</category>
 * <description>Styleflags for fonts</description>
 */
#define FF_ITALIC		0x0001
#define FF_BOLD			0x0002
#define FF_UNDERLINE	0x0004
#define FF_STRIKEOUT	0x0008

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
 * <category>Brush style</category>
 * <description>Styleflags that effect the drawing of filled shapes</description>
 */
#define BF_SOLID		0x0000			/* a solid brush */
#define BF_NULL			0x0001			/* a hollow brush */

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysGraphicLightOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysGraphicLightOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *	This function and <see>SysGraphicEndPaint</see> are used to encapsule some paint calls
 *	together. An implementing platform could use this encapsulation for some optimizations. For every
 *	call to SysGraphicBeginPaint there will be an according call to SysGraphicEndPaint.
 *	</description>
 * <param name="hDisplayContext" type="IN">Handle to device context.</param> 
 * <param name="rsCurrentVisuName" type="IN">The name of the current visualization.</param> 
 * <param name="ulFlags" type="IN">Additional flags.</param>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysgraphiclightbeginpaint_struct
{
	RTS_IEC_HANDLE hDisplayContext;		/* VAR_INPUT */
	RTS_IEC_STRING *rsCurrentVisuName;	/* VAR_INPUT */
	RTS_IEC_UDINT ulFlags;				/* VAR_INPUT */
	RTS_IEC_RESULT SysGraphicLightBeginPaint;	/* VAR_OUTPUT */
} sysgraphiclightbeginpaint_struct;

DEF_API(`void',`CDECL',`sysgraphiclightbeginpaint',`(sysgraphiclightbeginpaint_struct *p)',1,0x2CD9603E,0x03050400)
DEF_CREATEITF_API(`RTS_IEC_RESULT',`CDECL',`SysGraphicLightBeginPaint',`(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *rsCurrentVisuName, RTS_IEC_UDINT ulFlags)')

/**
 * <description>
 *	Function to draw a bitmap into a rectangle.
 *	</description>
 * <param name="hDisplayContext" type="IN">Handle to device context.</param> 
 * <param name="rectangle" type="IN">Rectangle description.</param> 
 * <param name="pbyData" TYPE="IN">Bitmap data</param>
 * <param name="ulDataSize" type="IN">Bitmap data size</param>
 * <param name="ulTransparentColor" type="IN">Contains the color that should be used as the transparent color. Will only be evaluated when
 *	the according flag is set. </param>
 * <param name="ulFlags" type="IN">Flags. Defined in IEC-Code for Visualization. At the moment only the flag for
 *	transparency is relevant when loading an image!</param>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysgraphiclightdrawbitmap_struct
{
	RTS_IEC_HANDLE hDisplayContext;		/* VAR_INPUT */
	RTS_Rectangle rectangle;	/* VAR_INPUT */
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */
	RTS_IEC_UDINT ulDataSize;			/* VAR_INPUT */
	RTS_IEC_UDINT ulTransparentColor;	/* VAR_INPUT */
	RTS_IEC_UDINT ulFlags;				/* VAR_INPUT */
	RTS_IEC_RESULT SysGraphicLightDrawBitmap;	/* VAR_OUTPUT */
} sysgraphiclightdrawbitmap_struct;

DEF_API(`void',`CDECL',`sysgraphiclightdrawbitmap',`(sysgraphiclightdrawbitmap_struct *p)',1,0x66222597,0x03050400)
DEF_CREATEITF_API(`RTS_IEC_RESULT',`CDECL',`SysGraphicLightDrawBitmap',`(RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_BYTE *pbyData, RTS_IEC_UDINT ulDataSize, RTS_IEC_UDINT ulTransparentColor, RTS_IEC_UDINT ulFlags)')

/**
 * <description>
 *	Function to draw a polygon based on an array of points.
 *	</description>
 * <param name="hDisplayContext" type="IN">Handle to device context.</param> 
 * <param name="iPoints" type="IN">Number of points in the array.</param> 
 * <param name="pPoints" type="IN">Pointer to the array of points. Length must be less or equal nPoints!</param>
 * <param name="ePolygonType" type="IN">Polygon type. See corresponding category.</param> 
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysgraphiclightdrawpolygon_struct
{
	RTS_IEC_HANDLE hDisplayContext;		/* VAR_INPUT */
	RTS_IEC_INT iPoints;				/* VAR_INPUT */
	RTS_Point *pPoints;					/* VAR_INPUT */
	RTS_IEC_UINT ePolygonType;			/* VAR_INPUT, Enum: POLYGONTYPE */
	RTS_IEC_RESULT SysGraphicLightDrawPolygon;	/* VAR_OUTPUT */
} sysgraphiclightdrawpolygon_struct;

DEF_API(`void',`CDECL',`sysgraphiclightdrawpolygon',`(sysgraphiclightdrawpolygon_struct *p)',1,0x1014158C,0x03050400)
DEF_CREATEITF_API(`RTS_IEC_RESULT',`CDECL',`SysGraphicLightDrawPolygon',`(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_INT iPoints , RTS_Point *pPoints, RTS_IEC_UINT ePolygonType)')

/**
 * <description>
 *	Function to draw a rectangle based on top left and bottom right.
 *	</description>
 * <param name="hDisplayContext" type="IN">Handle to device context.</param> 
 * <param name="rectangle" type="IN">Rectangle description.</param> 
 * <param name="eRectType" type="IN">Rectangle type. See corresponding category.</param> 
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysgraphiclightdrawrect_struct
{
	RTS_IEC_HANDLE hDisplayContext;			/* VAR_INPUT */
	RTS_Rectangle rectangle;				/* VAR_INPUT */
	RTS_IEC_UINT eRectType;					/* VAR_INPUT, Enum: RECTANGLETYPE */
	RTS_IEC_RESULT SysGraphicLightDrawRect;	/* VAR_OUTPUT */
} sysgraphiclightdrawrect_struct;

DEF_API(`void',`CDECL',`sysgraphiclightdrawrect',`(sysgraphiclightdrawrect_struct *p)',1,0x91BA25F9,0x03050400)
DEF_CREATEITF_API(`RTS_IEC_RESULT',`CDECL',`SysGraphicLightDrawRect',`(RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_UINT eRectType)')

/**
 * <description>
 *	Function to draw a text, based on top left and bottom right. Only the first line, if more
 *	than one is given.
 *	</description>
 * <param name="hDisplayContext" type="IN">Handle to device context.</param> 
 * <param name="rectangle" type="IN">Rectangle description.</param> 
 * <param name="pszText" type="IN">Will be either:
 * 	<ul>
 * 		<li>char* if TF_WSTRING is not set in ulDrawFlags</li>
 * 		<li>short* if (TF_WSTRING is set in ulDrawFlags)</li>
 * 	</ul>
 * </param> 
 * <param name="ulDrawFlags" type="IN">Draw flags. Defined in IEC-Code for Visualization.</param> 
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysgraphiclightdrawtext_struct
{
	RTS_IEC_HANDLE hDisplayContext;		/* VAR_INPUT */
	RTS_Rectangle rectangle;	/* VAR_INPUT */
	RTS_IEC_BYTE *pszText;				/* VAR_INPUT */
	RTS_IEC_UDINT ulDrawFlags;			/* VAR_INPUT */
	RTS_IEC_RESULT SysGraphicLightDrawText;	/* VAR_OUTPUT */
} sysgraphiclightdrawtext_struct;

DEF_API(`void',`CDECL',`sysgraphiclightdrawtext',`(sysgraphiclightdrawtext_struct *p)',1,0xE7F29224,0x03050400)
DEF_CREATEITF_API(`RTS_IEC_RESULT',`CDECL',`SysGraphicLightDrawText',`(RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_BYTE *pszText, RTS_IEC_UDINT ulDrawFlags)')

/**
 * <description>
 *	This function and <see>SysGraphicBeginPaint</see> are used to encapsule some paint calls
 *	together. An implementing platform could use this encapsulation for some optimizations. For every
 *	call to SysGraphicBeginPaint there will be an according call to SysGraphicEndPaint.
 *	</description>
 * <param name="hDisplayContext" type="IN">Handle to device context.</param> 
 * <param name="rsCurrentVisuName" type="IN">The name of the current visualization.</param> 
 * <param name="ulFlags" type="IN">Additional flags.</param>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysgraphiclightendpaint_struct
{
	RTS_IEC_HANDLE hDisplayContext;		/* VAR_INPUT */
	RTS_IEC_STRING *rsCurrentVisuName;	/* VAR_INPUT */
	RTS_IEC_UDINT ulFlags;				/* VAR_INPUT */
	RTS_IEC_RESULT SysGraphicLightEndPaint;	/* VAR_OUTPUT */
} sysgraphiclightendpaint_struct;

DEF_API(`void',`CDECL',`sysgraphiclightendpaint',`(sysgraphiclightendpaint_struct *p)',1,0xD48B379D,0x03050400)
DEF_CREATEITF_API(`RTS_IEC_RESULT',`CDECL',`SysGraphicLightEndPaint',`(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *rsCurrentVisuName, RTS_IEC_UDINT ulFlags)')

/**
 * <description>
 *	Provides a handle to the basic display context. If you do not use this handle any more, release it using
 * <see>SysGraphicLightReleaseDisplayDeviceContext</see>
 *	</description>
 * <param name="ulDisplayID" type="IN">Optional parameter for indicating different display contexts by ID. 
 * If only one display is used the parameter is always 0. </param>
 * <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param>	
 * <result><p>RESULT: Handle to the display context or RTS_INVALID_HANDLE if failed.</p></result>
 */
typedef struct tagsysgraphiclightgetdisplaydevicecontext_struct
{
	RTS_IEC_UDINT ulDisplayID;			/* VAR_INPUT */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */
	RTS_IEC_HANDLE SysGraphicLightGetDisplayDeviceContext;	/* VAR_OUTPUT */
} sysgraphiclightgetdisplaydevicecontext_struct;

DEF_API(`void',`CDECL',`sysgraphiclightgetdisplaydevicecontext',`(sysgraphiclightgetdisplaydevicecontext_struct *p)',1,0xFFD6A2B2,0x03050400)
DEF_CREATEITF_API(`RTS_IEC_HANDLE',`CDECL',`SysGraphicLightGetDisplayDeviceContext',`(RTS_IEC_UDINT ulDisplayID, RTS_IEC_RESULT *pResult)')

/**
 * <description>
 *	Releases a handle to the basic display context that was returned by 
 *	<see>SysGraphicLightGetDisplayDeviceContext</see>.
 *	</description>
 * <param name="hDisplayContext" type="IN">The display device context to release.</param> 
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysgraphiclightreleasedisplaydevicecontext_struct
{
	RTS_IEC_HANDLE hDisplayContext;		/* VAR_INPUT */
	RTS_IEC_RESULT SysGraphicLightReleaseDisplayDeviceContext;	/* VAR_OUTPUT */
} sysgraphiclightreleasedisplaydevicecontext_struct;

DEF_API(`void',`CDECL',`sysgraphiclightreleasedisplaydevicecontext',`(sysgraphiclightreleasedisplaydevicecontext_struct *p)',1,0xC2F26175,0x03050400)
DEF_CREATEITF_API(`RTS_IEC_RESULT',`CDECL',`SysGraphicLightReleaseDisplayDeviceContext',`(RTS_IEC_HANDLE hDisplayContext)')

/**
 * <description>
 *	Function to set the fill style of the following objects.
 *	</description>
 * <param name="hDisplayContext" type="IN">Handle to device context.</param> 
 * <param name="ulFillFlags" type="IN">Fill flags.  Defined in IEC-Code for Visualization</param>
 * <param name="ulFillColor" type="IN">Fill color.  Defined in IEC-Code for Visualization</param>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysgraphiclightsetfill_struct
{
	RTS_IEC_HANDLE hDisplayContext;		/* VAR_INPUT */
	RTS_IEC_UDINT ulFillFlags;			/* VAR_INPUT */
	RTS_IEC_UDINT ulFillColor;			/* VAR_INPUT */
	RTS_IEC_RESULT SysGraphicLightSetFill;	/* VAR_OUTPUT */
} sysgraphiclightsetfill_struct;

DEF_API(`void',`CDECL',`sysgraphiclightsetfill',`(sysgraphiclightsetfill_struct *p)',1,0x70355C53,0x03050400)
DEF_CREATEITF_API(`RTS_IEC_RESULT',`CDECL',`SysGraphicLightSetFill',`(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_UDINT ulFillFlags, RTS_IEC_UDINT ulFillColor)')

/**
 * <description>
 *	Function to register a font, which is downloaded by the user.
 *	</description>
 * <param name="pbyData" TYPE="IN">Font data</param>
 * <param name="udiDataSize" type="IN">Font data size</param>
 * <param name="pszFontName" type="IN">Name of the font that should be created.</param> 
 * <param name="iFontSize" type="IN">Size of the font.</param> 
 * <param name="udiFontFlags" type="IN">The font flags.</param>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysgraphiclightregisterfont_struct
{
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiDataSize;			/* VAR_INPUT */	
	RTS_IEC_STRING *pszFontName;		/* VAR_INPUT */	
	RTS_IEC_INT iFontSize;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiFontFlags;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysGraphicLightRegisterFont;	/* VAR_OUTPUT */	
} sysgraphiclightregisterfont_struct;

DEF_API(`void',`CDECL',`sysgraphiclightregisterfont',`(sysgraphiclightregisterfont_struct *p)',1,RTSITF_GET_SIGNATURE(0x2C3535DF, 0),0x03050700)
DEF_CREATEITF_API(`RTS_IEC_RESULT',`CDECL',`SysGraphicLightRegisterFont',`(RTS_IEC_BYTE *pbyData, RTS_IEC_UDINT udiDataSize, RTS_IEC_STRING *pszFontName, RTS_IEC_INT iFontSize, RTS_IEC_UDINT udiFontFlags)')


/**
 * <description>
 *	Function to set the font for the following drawn texts.
 *	</description>
 * <param name="hDisplayContext" type="IN">Handle to device context.</param> 
 * <param name="pszFontName" type="IN">Name of the font that should be created.</param> 
 * <param name="iFontSize" type="IN">Size of the font.</param> 
 * <param name="ulFontFlags" type="IN">The font flags.</param>
 * <param name="ulFontCharSet" type="IN">The font character set.</param>
 * <param name="ulFontColor" type="IN">The font color.</param> 
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysgraphiclightsetfont_struct
{
	RTS_IEC_HANDLE hDisplayContext;		/* VAR_INPUT */
	RTS_IEC_STRING *pszFontName;		/* VAR_INPUT */
	RTS_IEC_INT iFontSize;				/* VAR_INPUT */
	RTS_IEC_UDINT ulFontFlags;			/* VAR_INPUT */
	RTS_IEC_UDINT ulFontCharSet;		/* VAR_INPUT */
	RTS_IEC_UDINT ulFontColor;			/* VAR_INPUT */
	RTS_IEC_RESULT SysGraphicLightSetFont;	/* VAR_OUTPUT */
} sysgraphiclightsetfont_struct;

DEF_API(`void',`CDECL',`sysgraphiclightsetfont',`(sysgraphiclightsetfont_struct *p)',1,0x482F9A11,0x03050400)
DEF_CREATEITF_API(`RTS_IEC_RESULT',`CDECL',`SysGraphicLightSetFont',`(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *pszFontName, RTS_IEC_INT iFontSize, RTS_IEC_UDINT ulFontFlags, RTS_IEC_UDINT ulFontCharSet, RTS_IEC_UDINT ulFontColor)')

/**
 * <description>
 *	Function to set the line style of the following objects.
 *	</description>
 * <param name="hDisplayContext" type="IN">Handle to device context.</param> 
 * <param name="iLineWidth" TYPE="IN">Width OF the line as in Win32</param>
 * <param name="ulLineFlags" type="IN">Line flags.  Defined in IEC-Code for Visualization</param>
 * <param name="ulLineColor" type="IN">Line color.  Defined in IEC-Code for Visualization</param>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysgraphiclightsetline_struct
{
	RTS_IEC_HANDLE hDisplayContext;		/* VAR_INPUT */
	RTS_IEC_INT iLineWidth;				/* VAR_INPUT */
	RTS_IEC_UDINT ulLineFlags;			/* VAR_INPUT */
	RTS_IEC_UDINT ulLineColor;			/* VAR_INPUT */
	RTS_IEC_RESULT SysGraphicLightSetLine;	/* VAR_OUTPUT */
} sysgraphiclightsetline_struct;

DEF_API(`void',`CDECL',`sysgraphiclightsetline',`(sysgraphiclightsetline_struct *p)',1,0xC7E0F739,0x03050400)
DEF_CREATEITF_API(`RTS_IEC_RESULT',`CDECL',`SysGraphicLightSetLine',`(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_INT iLineWidth, RTS_IEC_UDINT ulLineFlags, RTS_IEC_UDINT ulLineColor)')

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

