 /**
 * <interfacename>SysGraphicLight</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _SYSGRAPHICLIGHTITF_H_
#define _SYSGRAPHICLIGHTITF_H_

#include "CmpStd.h"

 

 




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

void CDECL CDECL_EXT sysgraphiclightbeginpaint(sysgraphiclightbeginpaint_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTBEGINPAINT_IEC) (sysgraphiclightbeginpaint_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTBEGINPAINT_NOTIMPLEMENTED)
	#define USE_sysgraphiclightbeginpaint
	#define EXT_sysgraphiclightbeginpaint
	#define GET_sysgraphiclightbeginpaint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightbeginpaint(p0) 
	#define CHK_sysgraphiclightbeginpaint  FALSE
	#define EXP_sysgraphiclightbeginpaint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightbeginpaint
	#define EXT_sysgraphiclightbeginpaint
	#define GET_sysgraphiclightbeginpaint(fl)  CAL_CMGETAPI( "sysgraphiclightbeginpaint" ) 
	#define CAL_sysgraphiclightbeginpaint  sysgraphiclightbeginpaint
	#define CHK_sysgraphiclightbeginpaint  TRUE
	#define EXP_sysgraphiclightbeginpaint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightbeginpaint", (RTS_UINTPTR)sysgraphiclightbeginpaint, 1, 0x2CD9603E, 0x03050400) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightbeginpaint
	#define EXT_sysgraphiclightbeginpaint
	#define GET_sysgraphiclightbeginpaint(fl)  CAL_CMGETAPI( "sysgraphiclightbeginpaint" ) 
	#define CAL_sysgraphiclightbeginpaint  sysgraphiclightbeginpaint
	#define CHK_sysgraphiclightbeginpaint  TRUE
	#define EXP_sysgraphiclightbeginpaint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightbeginpaint", (RTS_UINTPTR)sysgraphiclightbeginpaint, 1, 0x2CD9603E, 0x03050400) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightbeginpaint
	#define EXT_SysGraphicLightsysgraphiclightbeginpaint
	#define GET_SysGraphicLightsysgraphiclightbeginpaint  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightbeginpaint  sysgraphiclightbeginpaint
	#define CHK_SysGraphicLightsysgraphiclightbeginpaint  TRUE
	#define EXP_SysGraphicLightsysgraphiclightbeginpaint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightbeginpaint", (RTS_UINTPTR)sysgraphiclightbeginpaint, 1, 0x2CD9603E, 0x03050400) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightbeginpaint
	#define EXT_sysgraphiclightbeginpaint
	#define GET_sysgraphiclightbeginpaint(fl)  CAL_CMGETAPI( "sysgraphiclightbeginpaint" ) 
	#define CAL_sysgraphiclightbeginpaint  sysgraphiclightbeginpaint
	#define CHK_sysgraphiclightbeginpaint  TRUE
	#define EXP_sysgraphiclightbeginpaint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightbeginpaint", (RTS_UINTPTR)sysgraphiclightbeginpaint, 1, 0x2CD9603E, 0x03050400) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightbeginpaint  PFSYSGRAPHICLIGHTBEGINPAINT_IEC pfsysgraphiclightbeginpaint;
	#define EXT_sysgraphiclightbeginpaint  extern PFSYSGRAPHICLIGHTBEGINPAINT_IEC pfsysgraphiclightbeginpaint;
	#define GET_sysgraphiclightbeginpaint(fl)  s_pfCMGetAPI2( "sysgraphiclightbeginpaint", (RTS_VOID_FCTPTR *)&pfsysgraphiclightbeginpaint, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x2CD9603E, 0x03050400)
	#define CAL_sysgraphiclightbeginpaint  pfsysgraphiclightbeginpaint
	#define CHK_sysgraphiclightbeginpaint  (pfsysgraphiclightbeginpaint != NULL)
	#define EXP_sysgraphiclightbeginpaint   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightbeginpaint", (RTS_UINTPTR)sysgraphiclightbeginpaint, 1, 0x2CD9603E, 0x03050400) 
#endif

RTS_IEC_RESULT CDECL SysGraphicLightBeginPaint(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *rsCurrentVisuName, RTS_IEC_UDINT ulFlags);
typedef RTS_IEC_RESULT (CDECL * PFSYSGRAPHICLIGHTBEGINPAINT) (RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *rsCurrentVisuName, RTS_IEC_UDINT ulFlags);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTBEGINPAINT_NOTIMPLEMENTED)
	#define USE_SysGraphicLightBeginPaint
	#define EXT_SysGraphicLightBeginPaint
	#define GET_SysGraphicLightBeginPaint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightBeginPaint(p0,p1,p2)  (RTS_IEC_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightBeginPaint  FALSE
	#define EXP_SysGraphicLightBeginPaint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightBeginPaint
	#define EXT_SysGraphicLightBeginPaint
	#define GET_SysGraphicLightBeginPaint(fl)  CAL_CMGETAPI( "SysGraphicLightBeginPaint" ) 
	#define CAL_SysGraphicLightBeginPaint  SysGraphicLightBeginPaint
	#define CHK_SysGraphicLightBeginPaint  TRUE
	#define EXP_SysGraphicLightBeginPaint  CAL_CMEXPAPI( "SysGraphicLightBeginPaint" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightBeginPaint
	#define EXT_SysGraphicLightBeginPaint
	#define GET_SysGraphicLightBeginPaint(fl)  CAL_CMGETAPI( "SysGraphicLightBeginPaint" ) 
	#define CAL_SysGraphicLightBeginPaint  SysGraphicLightBeginPaint
	#define CHK_SysGraphicLightBeginPaint  TRUE
	#define EXP_SysGraphicLightBeginPaint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightBeginPaint", (RTS_UINTPTR)SysGraphicLightBeginPaint, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightBeginPaint
	#define EXT_SysGraphicLightSysGraphicLightBeginPaint
	#define GET_SysGraphicLightSysGraphicLightBeginPaint  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightBeginPaint  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightBeginPaint
	#define CHK_SysGraphicLightSysGraphicLightBeginPaint	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightBeginPaint  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightBeginPaint
	#define EXT_SysGraphicLightBeginPaint
	#define GET_SysGraphicLightBeginPaint(fl)  CAL_CMGETAPI( "SysGraphicLightBeginPaint" ) 
	#define CAL_SysGraphicLightBeginPaint  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightBeginPaint
	#define CHK_SysGraphicLightBeginPaint	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightBeginPaint  CAL_CMEXPAPI( "SysGraphicLightBeginPaint" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightBeginPaint  PFSYSGRAPHICLIGHTBEGINPAINT pfSysGraphicLightBeginPaint;
	#define EXT_SysGraphicLightBeginPaint  extern PFSYSGRAPHICLIGHTBEGINPAINT pfSysGraphicLightBeginPaint;
	#define GET_SysGraphicLightBeginPaint(fl)  s_pfCMGetAPI2( "SysGraphicLightBeginPaint", (RTS_VOID_FCTPTR *)&pfSysGraphicLightBeginPaint, (fl), 0, 0)
	#define CAL_SysGraphicLightBeginPaint  pfSysGraphicLightBeginPaint
	#define CHK_SysGraphicLightBeginPaint  (pfSysGraphicLightBeginPaint != NULL)
	#define EXP_SysGraphicLightBeginPaint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightBeginPaint", (RTS_UINTPTR)SysGraphicLightBeginPaint, 0, 0) 
#endif




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

void CDECL CDECL_EXT sysgraphiclightdrawbitmap(sysgraphiclightdrawbitmap_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTDRAWBITMAP_IEC) (sysgraphiclightdrawbitmap_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTDRAWBITMAP_NOTIMPLEMENTED)
	#define USE_sysgraphiclightdrawbitmap
	#define EXT_sysgraphiclightdrawbitmap
	#define GET_sysgraphiclightdrawbitmap(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightdrawbitmap(p0) 
	#define CHK_sysgraphiclightdrawbitmap  FALSE
	#define EXP_sysgraphiclightdrawbitmap  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightdrawbitmap
	#define EXT_sysgraphiclightdrawbitmap
	#define GET_sysgraphiclightdrawbitmap(fl)  CAL_CMGETAPI( "sysgraphiclightdrawbitmap" ) 
	#define CAL_sysgraphiclightdrawbitmap  sysgraphiclightdrawbitmap
	#define CHK_sysgraphiclightdrawbitmap  TRUE
	#define EXP_sysgraphiclightdrawbitmap  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawbitmap", (RTS_UINTPTR)sysgraphiclightdrawbitmap, 1, 0x66222597, 0x03050400) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightdrawbitmap
	#define EXT_sysgraphiclightdrawbitmap
	#define GET_sysgraphiclightdrawbitmap(fl)  CAL_CMGETAPI( "sysgraphiclightdrawbitmap" ) 
	#define CAL_sysgraphiclightdrawbitmap  sysgraphiclightdrawbitmap
	#define CHK_sysgraphiclightdrawbitmap  TRUE
	#define EXP_sysgraphiclightdrawbitmap  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawbitmap", (RTS_UINTPTR)sysgraphiclightdrawbitmap, 1, 0x66222597, 0x03050400) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightdrawbitmap
	#define EXT_SysGraphicLightsysgraphiclightdrawbitmap
	#define GET_SysGraphicLightsysgraphiclightdrawbitmap  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightdrawbitmap  sysgraphiclightdrawbitmap
	#define CHK_SysGraphicLightsysgraphiclightdrawbitmap  TRUE
	#define EXP_SysGraphicLightsysgraphiclightdrawbitmap  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawbitmap", (RTS_UINTPTR)sysgraphiclightdrawbitmap, 1, 0x66222597, 0x03050400) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightdrawbitmap
	#define EXT_sysgraphiclightdrawbitmap
	#define GET_sysgraphiclightdrawbitmap(fl)  CAL_CMGETAPI( "sysgraphiclightdrawbitmap" ) 
	#define CAL_sysgraphiclightdrawbitmap  sysgraphiclightdrawbitmap
	#define CHK_sysgraphiclightdrawbitmap  TRUE
	#define EXP_sysgraphiclightdrawbitmap  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawbitmap", (RTS_UINTPTR)sysgraphiclightdrawbitmap, 1, 0x66222597, 0x03050400) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightdrawbitmap  PFSYSGRAPHICLIGHTDRAWBITMAP_IEC pfsysgraphiclightdrawbitmap;
	#define EXT_sysgraphiclightdrawbitmap  extern PFSYSGRAPHICLIGHTDRAWBITMAP_IEC pfsysgraphiclightdrawbitmap;
	#define GET_sysgraphiclightdrawbitmap(fl)  s_pfCMGetAPI2( "sysgraphiclightdrawbitmap", (RTS_VOID_FCTPTR *)&pfsysgraphiclightdrawbitmap, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x66222597, 0x03050400)
	#define CAL_sysgraphiclightdrawbitmap  pfsysgraphiclightdrawbitmap
	#define CHK_sysgraphiclightdrawbitmap  (pfsysgraphiclightdrawbitmap != NULL)
	#define EXP_sysgraphiclightdrawbitmap   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawbitmap", (RTS_UINTPTR)sysgraphiclightdrawbitmap, 1, 0x66222597, 0x03050400) 
#endif

RTS_IEC_RESULT CDECL SysGraphicLightDrawBitmap(RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_BYTE *pbyData, RTS_IEC_UDINT ulDataSize, RTS_IEC_UDINT ulTransparentColor, RTS_IEC_UDINT ulFlags);
typedef RTS_IEC_RESULT (CDECL * PFSYSGRAPHICLIGHTDRAWBITMAP) (RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_BYTE *pbyData, RTS_IEC_UDINT ulDataSize, RTS_IEC_UDINT ulTransparentColor, RTS_IEC_UDINT ulFlags);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTDRAWBITMAP_NOTIMPLEMENTED)
	#define USE_SysGraphicLightDrawBitmap
	#define EXT_SysGraphicLightDrawBitmap
	#define GET_SysGraphicLightDrawBitmap(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightDrawBitmap(p0,p1,p2,p3,p4,p5)  (RTS_IEC_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightDrawBitmap  FALSE
	#define EXP_SysGraphicLightDrawBitmap  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightDrawBitmap
	#define EXT_SysGraphicLightDrawBitmap
	#define GET_SysGraphicLightDrawBitmap(fl)  CAL_CMGETAPI( "SysGraphicLightDrawBitmap" ) 
	#define CAL_SysGraphicLightDrawBitmap  SysGraphicLightDrawBitmap
	#define CHK_SysGraphicLightDrawBitmap  TRUE
	#define EXP_SysGraphicLightDrawBitmap  CAL_CMEXPAPI( "SysGraphicLightDrawBitmap" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightDrawBitmap
	#define EXT_SysGraphicLightDrawBitmap
	#define GET_SysGraphicLightDrawBitmap(fl)  CAL_CMGETAPI( "SysGraphicLightDrawBitmap" ) 
	#define CAL_SysGraphicLightDrawBitmap  SysGraphicLightDrawBitmap
	#define CHK_SysGraphicLightDrawBitmap  TRUE
	#define EXP_SysGraphicLightDrawBitmap  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightDrawBitmap", (RTS_UINTPTR)SysGraphicLightDrawBitmap, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightDrawBitmap
	#define EXT_SysGraphicLightSysGraphicLightDrawBitmap
	#define GET_SysGraphicLightSysGraphicLightDrawBitmap  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightDrawBitmap  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightDrawBitmap
	#define CHK_SysGraphicLightSysGraphicLightDrawBitmap	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightDrawBitmap  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightDrawBitmap
	#define EXT_SysGraphicLightDrawBitmap
	#define GET_SysGraphicLightDrawBitmap(fl)  CAL_CMGETAPI( "SysGraphicLightDrawBitmap" ) 
	#define CAL_SysGraphicLightDrawBitmap  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightDrawBitmap
	#define CHK_SysGraphicLightDrawBitmap	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightDrawBitmap  CAL_CMEXPAPI( "SysGraphicLightDrawBitmap" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightDrawBitmap  PFSYSGRAPHICLIGHTDRAWBITMAP pfSysGraphicLightDrawBitmap;
	#define EXT_SysGraphicLightDrawBitmap  extern PFSYSGRAPHICLIGHTDRAWBITMAP pfSysGraphicLightDrawBitmap;
	#define GET_SysGraphicLightDrawBitmap(fl)  s_pfCMGetAPI2( "SysGraphicLightDrawBitmap", (RTS_VOID_FCTPTR *)&pfSysGraphicLightDrawBitmap, (fl), 0, 0)
	#define CAL_SysGraphicLightDrawBitmap  pfSysGraphicLightDrawBitmap
	#define CHK_SysGraphicLightDrawBitmap  (pfSysGraphicLightDrawBitmap != NULL)
	#define EXP_SysGraphicLightDrawBitmap  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightDrawBitmap", (RTS_UINTPTR)SysGraphicLightDrawBitmap, 0, 0) 
#endif




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

void CDECL CDECL_EXT sysgraphiclightdrawpolygon(sysgraphiclightdrawpolygon_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTDRAWPOLYGON_IEC) (sysgraphiclightdrawpolygon_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTDRAWPOLYGON_NOTIMPLEMENTED)
	#define USE_sysgraphiclightdrawpolygon
	#define EXT_sysgraphiclightdrawpolygon
	#define GET_sysgraphiclightdrawpolygon(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightdrawpolygon(p0) 
	#define CHK_sysgraphiclightdrawpolygon  FALSE
	#define EXP_sysgraphiclightdrawpolygon  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightdrawpolygon
	#define EXT_sysgraphiclightdrawpolygon
	#define GET_sysgraphiclightdrawpolygon(fl)  CAL_CMGETAPI( "sysgraphiclightdrawpolygon" ) 
	#define CAL_sysgraphiclightdrawpolygon  sysgraphiclightdrawpolygon
	#define CHK_sysgraphiclightdrawpolygon  TRUE
	#define EXP_sysgraphiclightdrawpolygon  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawpolygon", (RTS_UINTPTR)sysgraphiclightdrawpolygon, 1, 0x1014158C, 0x03050400) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightdrawpolygon
	#define EXT_sysgraphiclightdrawpolygon
	#define GET_sysgraphiclightdrawpolygon(fl)  CAL_CMGETAPI( "sysgraphiclightdrawpolygon" ) 
	#define CAL_sysgraphiclightdrawpolygon  sysgraphiclightdrawpolygon
	#define CHK_sysgraphiclightdrawpolygon  TRUE
	#define EXP_sysgraphiclightdrawpolygon  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawpolygon", (RTS_UINTPTR)sysgraphiclightdrawpolygon, 1, 0x1014158C, 0x03050400) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightdrawpolygon
	#define EXT_SysGraphicLightsysgraphiclightdrawpolygon
	#define GET_SysGraphicLightsysgraphiclightdrawpolygon  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightdrawpolygon  sysgraphiclightdrawpolygon
	#define CHK_SysGraphicLightsysgraphiclightdrawpolygon  TRUE
	#define EXP_SysGraphicLightsysgraphiclightdrawpolygon  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawpolygon", (RTS_UINTPTR)sysgraphiclightdrawpolygon, 1, 0x1014158C, 0x03050400) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightdrawpolygon
	#define EXT_sysgraphiclightdrawpolygon
	#define GET_sysgraphiclightdrawpolygon(fl)  CAL_CMGETAPI( "sysgraphiclightdrawpolygon" ) 
	#define CAL_sysgraphiclightdrawpolygon  sysgraphiclightdrawpolygon
	#define CHK_sysgraphiclightdrawpolygon  TRUE
	#define EXP_sysgraphiclightdrawpolygon  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawpolygon", (RTS_UINTPTR)sysgraphiclightdrawpolygon, 1, 0x1014158C, 0x03050400) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightdrawpolygon  PFSYSGRAPHICLIGHTDRAWPOLYGON_IEC pfsysgraphiclightdrawpolygon;
	#define EXT_sysgraphiclightdrawpolygon  extern PFSYSGRAPHICLIGHTDRAWPOLYGON_IEC pfsysgraphiclightdrawpolygon;
	#define GET_sysgraphiclightdrawpolygon(fl)  s_pfCMGetAPI2( "sysgraphiclightdrawpolygon", (RTS_VOID_FCTPTR *)&pfsysgraphiclightdrawpolygon, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x1014158C, 0x03050400)
	#define CAL_sysgraphiclightdrawpolygon  pfsysgraphiclightdrawpolygon
	#define CHK_sysgraphiclightdrawpolygon  (pfsysgraphiclightdrawpolygon != NULL)
	#define EXP_sysgraphiclightdrawpolygon   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawpolygon", (RTS_UINTPTR)sysgraphiclightdrawpolygon, 1, 0x1014158C, 0x03050400) 
#endif

RTS_IEC_RESULT CDECL SysGraphicLightDrawPolygon(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_INT iPoints , RTS_Point *pPoints, RTS_IEC_UINT ePolygonType);
typedef RTS_IEC_RESULT (CDECL * PFSYSGRAPHICLIGHTDRAWPOLYGON) (RTS_IEC_HANDLE hDisplayContext, RTS_IEC_INT iPoints , RTS_Point *pPoints, RTS_IEC_UINT ePolygonType);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTDRAWPOLYGON_NOTIMPLEMENTED)
	#define USE_SysGraphicLightDrawPolygon
	#define EXT_SysGraphicLightDrawPolygon
	#define GET_SysGraphicLightDrawPolygon(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightDrawPolygon(p0,p1,p2,p3)  (RTS_IEC_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightDrawPolygon  FALSE
	#define EXP_SysGraphicLightDrawPolygon  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightDrawPolygon
	#define EXT_SysGraphicLightDrawPolygon
	#define GET_SysGraphicLightDrawPolygon(fl)  CAL_CMGETAPI( "SysGraphicLightDrawPolygon" ) 
	#define CAL_SysGraphicLightDrawPolygon  SysGraphicLightDrawPolygon
	#define CHK_SysGraphicLightDrawPolygon  TRUE
	#define EXP_SysGraphicLightDrawPolygon  CAL_CMEXPAPI( "SysGraphicLightDrawPolygon" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightDrawPolygon
	#define EXT_SysGraphicLightDrawPolygon
	#define GET_SysGraphicLightDrawPolygon(fl)  CAL_CMGETAPI( "SysGraphicLightDrawPolygon" ) 
	#define CAL_SysGraphicLightDrawPolygon  SysGraphicLightDrawPolygon
	#define CHK_SysGraphicLightDrawPolygon  TRUE
	#define EXP_SysGraphicLightDrawPolygon  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightDrawPolygon", (RTS_UINTPTR)SysGraphicLightDrawPolygon, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightDrawPolygon
	#define EXT_SysGraphicLightSysGraphicLightDrawPolygon
	#define GET_SysGraphicLightSysGraphicLightDrawPolygon  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightDrawPolygon  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightDrawPolygon
	#define CHK_SysGraphicLightSysGraphicLightDrawPolygon	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightDrawPolygon  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightDrawPolygon
	#define EXT_SysGraphicLightDrawPolygon
	#define GET_SysGraphicLightDrawPolygon(fl)  CAL_CMGETAPI( "SysGraphicLightDrawPolygon" ) 
	#define CAL_SysGraphicLightDrawPolygon  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightDrawPolygon
	#define CHK_SysGraphicLightDrawPolygon	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightDrawPolygon  CAL_CMEXPAPI( "SysGraphicLightDrawPolygon" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightDrawPolygon  PFSYSGRAPHICLIGHTDRAWPOLYGON pfSysGraphicLightDrawPolygon;
	#define EXT_SysGraphicLightDrawPolygon  extern PFSYSGRAPHICLIGHTDRAWPOLYGON pfSysGraphicLightDrawPolygon;
	#define GET_SysGraphicLightDrawPolygon(fl)  s_pfCMGetAPI2( "SysGraphicLightDrawPolygon", (RTS_VOID_FCTPTR *)&pfSysGraphicLightDrawPolygon, (fl), 0, 0)
	#define CAL_SysGraphicLightDrawPolygon  pfSysGraphicLightDrawPolygon
	#define CHK_SysGraphicLightDrawPolygon  (pfSysGraphicLightDrawPolygon != NULL)
	#define EXP_SysGraphicLightDrawPolygon  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightDrawPolygon", (RTS_UINTPTR)SysGraphicLightDrawPolygon, 0, 0) 
#endif




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

void CDECL CDECL_EXT sysgraphiclightdrawrect(sysgraphiclightdrawrect_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTDRAWRECT_IEC) (sysgraphiclightdrawrect_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTDRAWRECT_NOTIMPLEMENTED)
	#define USE_sysgraphiclightdrawrect
	#define EXT_sysgraphiclightdrawrect
	#define GET_sysgraphiclightdrawrect(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightdrawrect(p0) 
	#define CHK_sysgraphiclightdrawrect  FALSE
	#define EXP_sysgraphiclightdrawrect  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightdrawrect
	#define EXT_sysgraphiclightdrawrect
	#define GET_sysgraphiclightdrawrect(fl)  CAL_CMGETAPI( "sysgraphiclightdrawrect" ) 
	#define CAL_sysgraphiclightdrawrect  sysgraphiclightdrawrect
	#define CHK_sysgraphiclightdrawrect  TRUE
	#define EXP_sysgraphiclightdrawrect  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawrect", (RTS_UINTPTR)sysgraphiclightdrawrect, 1, 0x91BA25F9, 0x03050400) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightdrawrect
	#define EXT_sysgraphiclightdrawrect
	#define GET_sysgraphiclightdrawrect(fl)  CAL_CMGETAPI( "sysgraphiclightdrawrect" ) 
	#define CAL_sysgraphiclightdrawrect  sysgraphiclightdrawrect
	#define CHK_sysgraphiclightdrawrect  TRUE
	#define EXP_sysgraphiclightdrawrect  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawrect", (RTS_UINTPTR)sysgraphiclightdrawrect, 1, 0x91BA25F9, 0x03050400) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightdrawrect
	#define EXT_SysGraphicLightsysgraphiclightdrawrect
	#define GET_SysGraphicLightsysgraphiclightdrawrect  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightdrawrect  sysgraphiclightdrawrect
	#define CHK_SysGraphicLightsysgraphiclightdrawrect  TRUE
	#define EXP_SysGraphicLightsysgraphiclightdrawrect  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawrect", (RTS_UINTPTR)sysgraphiclightdrawrect, 1, 0x91BA25F9, 0x03050400) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightdrawrect
	#define EXT_sysgraphiclightdrawrect
	#define GET_sysgraphiclightdrawrect(fl)  CAL_CMGETAPI( "sysgraphiclightdrawrect" ) 
	#define CAL_sysgraphiclightdrawrect  sysgraphiclightdrawrect
	#define CHK_sysgraphiclightdrawrect  TRUE
	#define EXP_sysgraphiclightdrawrect  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawrect", (RTS_UINTPTR)sysgraphiclightdrawrect, 1, 0x91BA25F9, 0x03050400) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightdrawrect  PFSYSGRAPHICLIGHTDRAWRECT_IEC pfsysgraphiclightdrawrect;
	#define EXT_sysgraphiclightdrawrect  extern PFSYSGRAPHICLIGHTDRAWRECT_IEC pfsysgraphiclightdrawrect;
	#define GET_sysgraphiclightdrawrect(fl)  s_pfCMGetAPI2( "sysgraphiclightdrawrect", (RTS_VOID_FCTPTR *)&pfsysgraphiclightdrawrect, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x91BA25F9, 0x03050400)
	#define CAL_sysgraphiclightdrawrect  pfsysgraphiclightdrawrect
	#define CHK_sysgraphiclightdrawrect  (pfsysgraphiclightdrawrect != NULL)
	#define EXP_sysgraphiclightdrawrect   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawrect", (RTS_UINTPTR)sysgraphiclightdrawrect, 1, 0x91BA25F9, 0x03050400) 
#endif

RTS_IEC_RESULT CDECL SysGraphicLightDrawRect(RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_UINT eRectType);
typedef RTS_IEC_RESULT (CDECL * PFSYSGRAPHICLIGHTDRAWRECT) (RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_UINT eRectType);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTDRAWRECT_NOTIMPLEMENTED)
	#define USE_SysGraphicLightDrawRect
	#define EXT_SysGraphicLightDrawRect
	#define GET_SysGraphicLightDrawRect(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightDrawRect(p0,p1,p2)  (RTS_IEC_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightDrawRect  FALSE
	#define EXP_SysGraphicLightDrawRect  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightDrawRect
	#define EXT_SysGraphicLightDrawRect
	#define GET_SysGraphicLightDrawRect(fl)  CAL_CMGETAPI( "SysGraphicLightDrawRect" ) 
	#define CAL_SysGraphicLightDrawRect  SysGraphicLightDrawRect
	#define CHK_SysGraphicLightDrawRect  TRUE
	#define EXP_SysGraphicLightDrawRect  CAL_CMEXPAPI( "SysGraphicLightDrawRect" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightDrawRect
	#define EXT_SysGraphicLightDrawRect
	#define GET_SysGraphicLightDrawRect(fl)  CAL_CMGETAPI( "SysGraphicLightDrawRect" ) 
	#define CAL_SysGraphicLightDrawRect  SysGraphicLightDrawRect
	#define CHK_SysGraphicLightDrawRect  TRUE
	#define EXP_SysGraphicLightDrawRect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightDrawRect", (RTS_UINTPTR)SysGraphicLightDrawRect, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightDrawRect
	#define EXT_SysGraphicLightSysGraphicLightDrawRect
	#define GET_SysGraphicLightSysGraphicLightDrawRect  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightDrawRect  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightDrawRect
	#define CHK_SysGraphicLightSysGraphicLightDrawRect	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightDrawRect  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightDrawRect
	#define EXT_SysGraphicLightDrawRect
	#define GET_SysGraphicLightDrawRect(fl)  CAL_CMGETAPI( "SysGraphicLightDrawRect" ) 
	#define CAL_SysGraphicLightDrawRect  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightDrawRect
	#define CHK_SysGraphicLightDrawRect	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightDrawRect  CAL_CMEXPAPI( "SysGraphicLightDrawRect" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightDrawRect  PFSYSGRAPHICLIGHTDRAWRECT pfSysGraphicLightDrawRect;
	#define EXT_SysGraphicLightDrawRect  extern PFSYSGRAPHICLIGHTDRAWRECT pfSysGraphicLightDrawRect;
	#define GET_SysGraphicLightDrawRect(fl)  s_pfCMGetAPI2( "SysGraphicLightDrawRect", (RTS_VOID_FCTPTR *)&pfSysGraphicLightDrawRect, (fl), 0, 0)
	#define CAL_SysGraphicLightDrawRect  pfSysGraphicLightDrawRect
	#define CHK_SysGraphicLightDrawRect  (pfSysGraphicLightDrawRect != NULL)
	#define EXP_SysGraphicLightDrawRect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightDrawRect", (RTS_UINTPTR)SysGraphicLightDrawRect, 0, 0) 
#endif




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

void CDECL CDECL_EXT sysgraphiclightdrawtext(sysgraphiclightdrawtext_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTDRAWTEXT_IEC) (sysgraphiclightdrawtext_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTDRAWTEXT_NOTIMPLEMENTED)
	#define USE_sysgraphiclightdrawtext
	#define EXT_sysgraphiclightdrawtext
	#define GET_sysgraphiclightdrawtext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightdrawtext(p0) 
	#define CHK_sysgraphiclightdrawtext  FALSE
	#define EXP_sysgraphiclightdrawtext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightdrawtext
	#define EXT_sysgraphiclightdrawtext
	#define GET_sysgraphiclightdrawtext(fl)  CAL_CMGETAPI( "sysgraphiclightdrawtext" ) 
	#define CAL_sysgraphiclightdrawtext  sysgraphiclightdrawtext
	#define CHK_sysgraphiclightdrawtext  TRUE
	#define EXP_sysgraphiclightdrawtext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawtext", (RTS_UINTPTR)sysgraphiclightdrawtext, 1, 0xE7F29224, 0x03050400) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightdrawtext
	#define EXT_sysgraphiclightdrawtext
	#define GET_sysgraphiclightdrawtext(fl)  CAL_CMGETAPI( "sysgraphiclightdrawtext" ) 
	#define CAL_sysgraphiclightdrawtext  sysgraphiclightdrawtext
	#define CHK_sysgraphiclightdrawtext  TRUE
	#define EXP_sysgraphiclightdrawtext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawtext", (RTS_UINTPTR)sysgraphiclightdrawtext, 1, 0xE7F29224, 0x03050400) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightdrawtext
	#define EXT_SysGraphicLightsysgraphiclightdrawtext
	#define GET_SysGraphicLightsysgraphiclightdrawtext  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightdrawtext  sysgraphiclightdrawtext
	#define CHK_SysGraphicLightsysgraphiclightdrawtext  TRUE
	#define EXP_SysGraphicLightsysgraphiclightdrawtext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawtext", (RTS_UINTPTR)sysgraphiclightdrawtext, 1, 0xE7F29224, 0x03050400) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightdrawtext
	#define EXT_sysgraphiclightdrawtext
	#define GET_sysgraphiclightdrawtext(fl)  CAL_CMGETAPI( "sysgraphiclightdrawtext" ) 
	#define CAL_sysgraphiclightdrawtext  sysgraphiclightdrawtext
	#define CHK_sysgraphiclightdrawtext  TRUE
	#define EXP_sysgraphiclightdrawtext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawtext", (RTS_UINTPTR)sysgraphiclightdrawtext, 1, 0xE7F29224, 0x03050400) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightdrawtext  PFSYSGRAPHICLIGHTDRAWTEXT_IEC pfsysgraphiclightdrawtext;
	#define EXT_sysgraphiclightdrawtext  extern PFSYSGRAPHICLIGHTDRAWTEXT_IEC pfsysgraphiclightdrawtext;
	#define GET_sysgraphiclightdrawtext(fl)  s_pfCMGetAPI2( "sysgraphiclightdrawtext", (RTS_VOID_FCTPTR *)&pfsysgraphiclightdrawtext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE7F29224, 0x03050400)
	#define CAL_sysgraphiclightdrawtext  pfsysgraphiclightdrawtext
	#define CHK_sysgraphiclightdrawtext  (pfsysgraphiclightdrawtext != NULL)
	#define EXP_sysgraphiclightdrawtext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightdrawtext", (RTS_UINTPTR)sysgraphiclightdrawtext, 1, 0xE7F29224, 0x03050400) 
#endif

RTS_IEC_RESULT CDECL SysGraphicLightDrawText(RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_BYTE *pszText, RTS_IEC_UDINT ulDrawFlags);
typedef RTS_IEC_RESULT (CDECL * PFSYSGRAPHICLIGHTDRAWTEXT) (RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_BYTE *pszText, RTS_IEC_UDINT ulDrawFlags);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTDRAWTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicLightDrawText
	#define EXT_SysGraphicLightDrawText
	#define GET_SysGraphicLightDrawText(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightDrawText(p0,p1,p2,p3)  (RTS_IEC_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightDrawText  FALSE
	#define EXP_SysGraphicLightDrawText  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightDrawText
	#define EXT_SysGraphicLightDrawText
	#define GET_SysGraphicLightDrawText(fl)  CAL_CMGETAPI( "SysGraphicLightDrawText" ) 
	#define CAL_SysGraphicLightDrawText  SysGraphicLightDrawText
	#define CHK_SysGraphicLightDrawText  TRUE
	#define EXP_SysGraphicLightDrawText  CAL_CMEXPAPI( "SysGraphicLightDrawText" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightDrawText
	#define EXT_SysGraphicLightDrawText
	#define GET_SysGraphicLightDrawText(fl)  CAL_CMGETAPI( "SysGraphicLightDrawText" ) 
	#define CAL_SysGraphicLightDrawText  SysGraphicLightDrawText
	#define CHK_SysGraphicLightDrawText  TRUE
	#define EXP_SysGraphicLightDrawText  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightDrawText", (RTS_UINTPTR)SysGraphicLightDrawText, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightDrawText
	#define EXT_SysGraphicLightSysGraphicLightDrawText
	#define GET_SysGraphicLightSysGraphicLightDrawText  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightDrawText  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightDrawText
	#define CHK_SysGraphicLightSysGraphicLightDrawText	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightDrawText  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightDrawText
	#define EXT_SysGraphicLightDrawText
	#define GET_SysGraphicLightDrawText(fl)  CAL_CMGETAPI( "SysGraphicLightDrawText" ) 
	#define CAL_SysGraphicLightDrawText  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightDrawText
	#define CHK_SysGraphicLightDrawText	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightDrawText  CAL_CMEXPAPI( "SysGraphicLightDrawText" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightDrawText  PFSYSGRAPHICLIGHTDRAWTEXT pfSysGraphicLightDrawText;
	#define EXT_SysGraphicLightDrawText  extern PFSYSGRAPHICLIGHTDRAWTEXT pfSysGraphicLightDrawText;
	#define GET_SysGraphicLightDrawText(fl)  s_pfCMGetAPI2( "SysGraphicLightDrawText", (RTS_VOID_FCTPTR *)&pfSysGraphicLightDrawText, (fl), 0, 0)
	#define CAL_SysGraphicLightDrawText  pfSysGraphicLightDrawText
	#define CHK_SysGraphicLightDrawText  (pfSysGraphicLightDrawText != NULL)
	#define EXP_SysGraphicLightDrawText  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightDrawText", (RTS_UINTPTR)SysGraphicLightDrawText, 0, 0) 
#endif




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

void CDECL CDECL_EXT sysgraphiclightendpaint(sysgraphiclightendpaint_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTENDPAINT_IEC) (sysgraphiclightendpaint_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTENDPAINT_NOTIMPLEMENTED)
	#define USE_sysgraphiclightendpaint
	#define EXT_sysgraphiclightendpaint
	#define GET_sysgraphiclightendpaint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightendpaint(p0) 
	#define CHK_sysgraphiclightendpaint  FALSE
	#define EXP_sysgraphiclightendpaint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightendpaint
	#define EXT_sysgraphiclightendpaint
	#define GET_sysgraphiclightendpaint(fl)  CAL_CMGETAPI( "sysgraphiclightendpaint" ) 
	#define CAL_sysgraphiclightendpaint  sysgraphiclightendpaint
	#define CHK_sysgraphiclightendpaint  TRUE
	#define EXP_sysgraphiclightendpaint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightendpaint", (RTS_UINTPTR)sysgraphiclightendpaint, 1, 0xD48B379D, 0x03050400) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightendpaint
	#define EXT_sysgraphiclightendpaint
	#define GET_sysgraphiclightendpaint(fl)  CAL_CMGETAPI( "sysgraphiclightendpaint" ) 
	#define CAL_sysgraphiclightendpaint  sysgraphiclightendpaint
	#define CHK_sysgraphiclightendpaint  TRUE
	#define EXP_sysgraphiclightendpaint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightendpaint", (RTS_UINTPTR)sysgraphiclightendpaint, 1, 0xD48B379D, 0x03050400) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightendpaint
	#define EXT_SysGraphicLightsysgraphiclightendpaint
	#define GET_SysGraphicLightsysgraphiclightendpaint  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightendpaint  sysgraphiclightendpaint
	#define CHK_SysGraphicLightsysgraphiclightendpaint  TRUE
	#define EXP_SysGraphicLightsysgraphiclightendpaint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightendpaint", (RTS_UINTPTR)sysgraphiclightendpaint, 1, 0xD48B379D, 0x03050400) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightendpaint
	#define EXT_sysgraphiclightendpaint
	#define GET_sysgraphiclightendpaint(fl)  CAL_CMGETAPI( "sysgraphiclightendpaint" ) 
	#define CAL_sysgraphiclightendpaint  sysgraphiclightendpaint
	#define CHK_sysgraphiclightendpaint  TRUE
	#define EXP_sysgraphiclightendpaint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightendpaint", (RTS_UINTPTR)sysgraphiclightendpaint, 1, 0xD48B379D, 0x03050400) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightendpaint  PFSYSGRAPHICLIGHTENDPAINT_IEC pfsysgraphiclightendpaint;
	#define EXT_sysgraphiclightendpaint  extern PFSYSGRAPHICLIGHTENDPAINT_IEC pfsysgraphiclightendpaint;
	#define GET_sysgraphiclightendpaint(fl)  s_pfCMGetAPI2( "sysgraphiclightendpaint", (RTS_VOID_FCTPTR *)&pfsysgraphiclightendpaint, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD48B379D, 0x03050400)
	#define CAL_sysgraphiclightendpaint  pfsysgraphiclightendpaint
	#define CHK_sysgraphiclightendpaint  (pfsysgraphiclightendpaint != NULL)
	#define EXP_sysgraphiclightendpaint   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightendpaint", (RTS_UINTPTR)sysgraphiclightendpaint, 1, 0xD48B379D, 0x03050400) 
#endif

RTS_IEC_RESULT CDECL SysGraphicLightEndPaint(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *rsCurrentVisuName, RTS_IEC_UDINT ulFlags);
typedef RTS_IEC_RESULT (CDECL * PFSYSGRAPHICLIGHTENDPAINT) (RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *rsCurrentVisuName, RTS_IEC_UDINT ulFlags);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTENDPAINT_NOTIMPLEMENTED)
	#define USE_SysGraphicLightEndPaint
	#define EXT_SysGraphicLightEndPaint
	#define GET_SysGraphicLightEndPaint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightEndPaint(p0,p1,p2)  (RTS_IEC_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightEndPaint  FALSE
	#define EXP_SysGraphicLightEndPaint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightEndPaint
	#define EXT_SysGraphicLightEndPaint
	#define GET_SysGraphicLightEndPaint(fl)  CAL_CMGETAPI( "SysGraphicLightEndPaint" ) 
	#define CAL_SysGraphicLightEndPaint  SysGraphicLightEndPaint
	#define CHK_SysGraphicLightEndPaint  TRUE
	#define EXP_SysGraphicLightEndPaint  CAL_CMEXPAPI( "SysGraphicLightEndPaint" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightEndPaint
	#define EXT_SysGraphicLightEndPaint
	#define GET_SysGraphicLightEndPaint(fl)  CAL_CMGETAPI( "SysGraphicLightEndPaint" ) 
	#define CAL_SysGraphicLightEndPaint  SysGraphicLightEndPaint
	#define CHK_SysGraphicLightEndPaint  TRUE
	#define EXP_SysGraphicLightEndPaint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightEndPaint", (RTS_UINTPTR)SysGraphicLightEndPaint, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightEndPaint
	#define EXT_SysGraphicLightSysGraphicLightEndPaint
	#define GET_SysGraphicLightSysGraphicLightEndPaint  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightEndPaint  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightEndPaint
	#define CHK_SysGraphicLightSysGraphicLightEndPaint	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightEndPaint  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightEndPaint
	#define EXT_SysGraphicLightEndPaint
	#define GET_SysGraphicLightEndPaint(fl)  CAL_CMGETAPI( "SysGraphicLightEndPaint" ) 
	#define CAL_SysGraphicLightEndPaint  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightEndPaint
	#define CHK_SysGraphicLightEndPaint	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightEndPaint  CAL_CMEXPAPI( "SysGraphicLightEndPaint" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightEndPaint  PFSYSGRAPHICLIGHTENDPAINT pfSysGraphicLightEndPaint;
	#define EXT_SysGraphicLightEndPaint  extern PFSYSGRAPHICLIGHTENDPAINT pfSysGraphicLightEndPaint;
	#define GET_SysGraphicLightEndPaint(fl)  s_pfCMGetAPI2( "SysGraphicLightEndPaint", (RTS_VOID_FCTPTR *)&pfSysGraphicLightEndPaint, (fl), 0, 0)
	#define CAL_SysGraphicLightEndPaint  pfSysGraphicLightEndPaint
	#define CHK_SysGraphicLightEndPaint  (pfSysGraphicLightEndPaint != NULL)
	#define EXP_SysGraphicLightEndPaint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightEndPaint", (RTS_UINTPTR)SysGraphicLightEndPaint, 0, 0) 
#endif




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

void CDECL CDECL_EXT sysgraphiclightgetdisplaydevicecontext(sysgraphiclightgetdisplaydevicecontext_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTGETDISPLAYDEVICECONTEXT_IEC) (sysgraphiclightgetdisplaydevicecontext_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTGETDISPLAYDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_sysgraphiclightgetdisplaydevicecontext
	#define EXT_sysgraphiclightgetdisplaydevicecontext
	#define GET_sysgraphiclightgetdisplaydevicecontext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightgetdisplaydevicecontext(p0) 
	#define CHK_sysgraphiclightgetdisplaydevicecontext  FALSE
	#define EXP_sysgraphiclightgetdisplaydevicecontext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightgetdisplaydevicecontext
	#define EXT_sysgraphiclightgetdisplaydevicecontext
	#define GET_sysgraphiclightgetdisplaydevicecontext(fl)  CAL_CMGETAPI( "sysgraphiclightgetdisplaydevicecontext" ) 
	#define CAL_sysgraphiclightgetdisplaydevicecontext  sysgraphiclightgetdisplaydevicecontext
	#define CHK_sysgraphiclightgetdisplaydevicecontext  TRUE
	#define EXP_sysgraphiclightgetdisplaydevicecontext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightgetdisplaydevicecontext", (RTS_UINTPTR)sysgraphiclightgetdisplaydevicecontext, 1, 0xFFD6A2B2, 0x03050400) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightgetdisplaydevicecontext
	#define EXT_sysgraphiclightgetdisplaydevicecontext
	#define GET_sysgraphiclightgetdisplaydevicecontext(fl)  CAL_CMGETAPI( "sysgraphiclightgetdisplaydevicecontext" ) 
	#define CAL_sysgraphiclightgetdisplaydevicecontext  sysgraphiclightgetdisplaydevicecontext
	#define CHK_sysgraphiclightgetdisplaydevicecontext  TRUE
	#define EXP_sysgraphiclightgetdisplaydevicecontext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightgetdisplaydevicecontext", (RTS_UINTPTR)sysgraphiclightgetdisplaydevicecontext, 1, 0xFFD6A2B2, 0x03050400) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightgetdisplaydevicecontext
	#define EXT_SysGraphicLightsysgraphiclightgetdisplaydevicecontext
	#define GET_SysGraphicLightsysgraphiclightgetdisplaydevicecontext  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightgetdisplaydevicecontext  sysgraphiclightgetdisplaydevicecontext
	#define CHK_SysGraphicLightsysgraphiclightgetdisplaydevicecontext  TRUE
	#define EXP_SysGraphicLightsysgraphiclightgetdisplaydevicecontext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightgetdisplaydevicecontext", (RTS_UINTPTR)sysgraphiclightgetdisplaydevicecontext, 1, 0xFFD6A2B2, 0x03050400) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightgetdisplaydevicecontext
	#define EXT_sysgraphiclightgetdisplaydevicecontext
	#define GET_sysgraphiclightgetdisplaydevicecontext(fl)  CAL_CMGETAPI( "sysgraphiclightgetdisplaydevicecontext" ) 
	#define CAL_sysgraphiclightgetdisplaydevicecontext  sysgraphiclightgetdisplaydevicecontext
	#define CHK_sysgraphiclightgetdisplaydevicecontext  TRUE
	#define EXP_sysgraphiclightgetdisplaydevicecontext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightgetdisplaydevicecontext", (RTS_UINTPTR)sysgraphiclightgetdisplaydevicecontext, 1, 0xFFD6A2B2, 0x03050400) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightgetdisplaydevicecontext  PFSYSGRAPHICLIGHTGETDISPLAYDEVICECONTEXT_IEC pfsysgraphiclightgetdisplaydevicecontext;
	#define EXT_sysgraphiclightgetdisplaydevicecontext  extern PFSYSGRAPHICLIGHTGETDISPLAYDEVICECONTEXT_IEC pfsysgraphiclightgetdisplaydevicecontext;
	#define GET_sysgraphiclightgetdisplaydevicecontext(fl)  s_pfCMGetAPI2( "sysgraphiclightgetdisplaydevicecontext", (RTS_VOID_FCTPTR *)&pfsysgraphiclightgetdisplaydevicecontext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xFFD6A2B2, 0x03050400)
	#define CAL_sysgraphiclightgetdisplaydevicecontext  pfsysgraphiclightgetdisplaydevicecontext
	#define CHK_sysgraphiclightgetdisplaydevicecontext  (pfsysgraphiclightgetdisplaydevicecontext != NULL)
	#define EXP_sysgraphiclightgetdisplaydevicecontext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightgetdisplaydevicecontext", (RTS_UINTPTR)sysgraphiclightgetdisplaydevicecontext, 1, 0xFFD6A2B2, 0x03050400) 
#endif

RTS_IEC_HANDLE CDECL SysGraphicLightGetDisplayDeviceContext(RTS_IEC_UDINT ulDisplayID, RTS_IEC_RESULT *pResult);
typedef RTS_IEC_HANDLE (CDECL * PFSYSGRAPHICLIGHTGETDISPLAYDEVICECONTEXT) (RTS_IEC_UDINT ulDisplayID, RTS_IEC_RESULT *pResult);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTGETDISPLAYDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicLightGetDisplayDeviceContext
	#define EXT_SysGraphicLightGetDisplayDeviceContext
	#define GET_SysGraphicLightGetDisplayDeviceContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightGetDisplayDeviceContext(p0,p1)  (RTS_IEC_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightGetDisplayDeviceContext  FALSE
	#define EXP_SysGraphicLightGetDisplayDeviceContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightGetDisplayDeviceContext
	#define EXT_SysGraphicLightGetDisplayDeviceContext
	#define GET_SysGraphicLightGetDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicLightGetDisplayDeviceContext" ) 
	#define CAL_SysGraphicLightGetDisplayDeviceContext  SysGraphicLightGetDisplayDeviceContext
	#define CHK_SysGraphicLightGetDisplayDeviceContext  TRUE
	#define EXP_SysGraphicLightGetDisplayDeviceContext  CAL_CMEXPAPI( "SysGraphicLightGetDisplayDeviceContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightGetDisplayDeviceContext
	#define EXT_SysGraphicLightGetDisplayDeviceContext
	#define GET_SysGraphicLightGetDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicLightGetDisplayDeviceContext" ) 
	#define CAL_SysGraphicLightGetDisplayDeviceContext  SysGraphicLightGetDisplayDeviceContext
	#define CHK_SysGraphicLightGetDisplayDeviceContext  TRUE
	#define EXP_SysGraphicLightGetDisplayDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightGetDisplayDeviceContext", (RTS_UINTPTR)SysGraphicLightGetDisplayDeviceContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightGetDisplayDeviceContext
	#define EXT_SysGraphicLightSysGraphicLightGetDisplayDeviceContext
	#define GET_SysGraphicLightSysGraphicLightGetDisplayDeviceContext  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightGetDisplayDeviceContext  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightGetDisplayDeviceContext
	#define CHK_SysGraphicLightSysGraphicLightGetDisplayDeviceContext	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightGetDisplayDeviceContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightGetDisplayDeviceContext
	#define EXT_SysGraphicLightGetDisplayDeviceContext
	#define GET_SysGraphicLightGetDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicLightGetDisplayDeviceContext" ) 
	#define CAL_SysGraphicLightGetDisplayDeviceContext  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightGetDisplayDeviceContext
	#define CHK_SysGraphicLightGetDisplayDeviceContext	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightGetDisplayDeviceContext  CAL_CMEXPAPI( "SysGraphicLightGetDisplayDeviceContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightGetDisplayDeviceContext  PFSYSGRAPHICLIGHTGETDISPLAYDEVICECONTEXT pfSysGraphicLightGetDisplayDeviceContext;
	#define EXT_SysGraphicLightGetDisplayDeviceContext  extern PFSYSGRAPHICLIGHTGETDISPLAYDEVICECONTEXT pfSysGraphicLightGetDisplayDeviceContext;
	#define GET_SysGraphicLightGetDisplayDeviceContext(fl)  s_pfCMGetAPI2( "SysGraphicLightGetDisplayDeviceContext", (RTS_VOID_FCTPTR *)&pfSysGraphicLightGetDisplayDeviceContext, (fl), 0, 0)
	#define CAL_SysGraphicLightGetDisplayDeviceContext  pfSysGraphicLightGetDisplayDeviceContext
	#define CHK_SysGraphicLightGetDisplayDeviceContext  (pfSysGraphicLightGetDisplayDeviceContext != NULL)
	#define EXP_SysGraphicLightGetDisplayDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightGetDisplayDeviceContext", (RTS_UINTPTR)SysGraphicLightGetDisplayDeviceContext, 0, 0) 
#endif




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

void CDECL CDECL_EXT sysgraphiclightreleasedisplaydevicecontext(sysgraphiclightreleasedisplaydevicecontext_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTRELEASEDISPLAYDEVICECONTEXT_IEC) (sysgraphiclightreleasedisplaydevicecontext_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTRELEASEDISPLAYDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_sysgraphiclightreleasedisplaydevicecontext
	#define EXT_sysgraphiclightreleasedisplaydevicecontext
	#define GET_sysgraphiclightreleasedisplaydevicecontext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightreleasedisplaydevicecontext(p0) 
	#define CHK_sysgraphiclightreleasedisplaydevicecontext  FALSE
	#define EXP_sysgraphiclightreleasedisplaydevicecontext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightreleasedisplaydevicecontext
	#define EXT_sysgraphiclightreleasedisplaydevicecontext
	#define GET_sysgraphiclightreleasedisplaydevicecontext(fl)  CAL_CMGETAPI( "sysgraphiclightreleasedisplaydevicecontext" ) 
	#define CAL_sysgraphiclightreleasedisplaydevicecontext  sysgraphiclightreleasedisplaydevicecontext
	#define CHK_sysgraphiclightreleasedisplaydevicecontext  TRUE
	#define EXP_sysgraphiclightreleasedisplaydevicecontext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightreleasedisplaydevicecontext", (RTS_UINTPTR)sysgraphiclightreleasedisplaydevicecontext, 1, 0xC2F26175, 0x03050400) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightreleasedisplaydevicecontext
	#define EXT_sysgraphiclightreleasedisplaydevicecontext
	#define GET_sysgraphiclightreleasedisplaydevicecontext(fl)  CAL_CMGETAPI( "sysgraphiclightreleasedisplaydevicecontext" ) 
	#define CAL_sysgraphiclightreleasedisplaydevicecontext  sysgraphiclightreleasedisplaydevicecontext
	#define CHK_sysgraphiclightreleasedisplaydevicecontext  TRUE
	#define EXP_sysgraphiclightreleasedisplaydevicecontext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightreleasedisplaydevicecontext", (RTS_UINTPTR)sysgraphiclightreleasedisplaydevicecontext, 1, 0xC2F26175, 0x03050400) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightreleasedisplaydevicecontext
	#define EXT_SysGraphicLightsysgraphiclightreleasedisplaydevicecontext
	#define GET_SysGraphicLightsysgraphiclightreleasedisplaydevicecontext  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightreleasedisplaydevicecontext  sysgraphiclightreleasedisplaydevicecontext
	#define CHK_SysGraphicLightsysgraphiclightreleasedisplaydevicecontext  TRUE
	#define EXP_SysGraphicLightsysgraphiclightreleasedisplaydevicecontext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightreleasedisplaydevicecontext", (RTS_UINTPTR)sysgraphiclightreleasedisplaydevicecontext, 1, 0xC2F26175, 0x03050400) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightreleasedisplaydevicecontext
	#define EXT_sysgraphiclightreleasedisplaydevicecontext
	#define GET_sysgraphiclightreleasedisplaydevicecontext(fl)  CAL_CMGETAPI( "sysgraphiclightreleasedisplaydevicecontext" ) 
	#define CAL_sysgraphiclightreleasedisplaydevicecontext  sysgraphiclightreleasedisplaydevicecontext
	#define CHK_sysgraphiclightreleasedisplaydevicecontext  TRUE
	#define EXP_sysgraphiclightreleasedisplaydevicecontext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightreleasedisplaydevicecontext", (RTS_UINTPTR)sysgraphiclightreleasedisplaydevicecontext, 1, 0xC2F26175, 0x03050400) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightreleasedisplaydevicecontext  PFSYSGRAPHICLIGHTRELEASEDISPLAYDEVICECONTEXT_IEC pfsysgraphiclightreleasedisplaydevicecontext;
	#define EXT_sysgraphiclightreleasedisplaydevicecontext  extern PFSYSGRAPHICLIGHTRELEASEDISPLAYDEVICECONTEXT_IEC pfsysgraphiclightreleasedisplaydevicecontext;
	#define GET_sysgraphiclightreleasedisplaydevicecontext(fl)  s_pfCMGetAPI2( "sysgraphiclightreleasedisplaydevicecontext", (RTS_VOID_FCTPTR *)&pfsysgraphiclightreleasedisplaydevicecontext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xC2F26175, 0x03050400)
	#define CAL_sysgraphiclightreleasedisplaydevicecontext  pfsysgraphiclightreleasedisplaydevicecontext
	#define CHK_sysgraphiclightreleasedisplaydevicecontext  (pfsysgraphiclightreleasedisplaydevicecontext != NULL)
	#define EXP_sysgraphiclightreleasedisplaydevicecontext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightreleasedisplaydevicecontext", (RTS_UINTPTR)sysgraphiclightreleasedisplaydevicecontext, 1, 0xC2F26175, 0x03050400) 
#endif

RTS_IEC_RESULT CDECL SysGraphicLightReleaseDisplayDeviceContext(RTS_IEC_HANDLE hDisplayContext);
typedef RTS_IEC_RESULT (CDECL * PFSYSGRAPHICLIGHTRELEASEDISPLAYDEVICECONTEXT) (RTS_IEC_HANDLE hDisplayContext);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTRELEASEDISPLAYDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicLightReleaseDisplayDeviceContext
	#define EXT_SysGraphicLightReleaseDisplayDeviceContext
	#define GET_SysGraphicLightReleaseDisplayDeviceContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightReleaseDisplayDeviceContext(p0)  (RTS_IEC_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightReleaseDisplayDeviceContext  FALSE
	#define EXP_SysGraphicLightReleaseDisplayDeviceContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightReleaseDisplayDeviceContext
	#define EXT_SysGraphicLightReleaseDisplayDeviceContext
	#define GET_SysGraphicLightReleaseDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicLightReleaseDisplayDeviceContext" ) 
	#define CAL_SysGraphicLightReleaseDisplayDeviceContext  SysGraphicLightReleaseDisplayDeviceContext
	#define CHK_SysGraphicLightReleaseDisplayDeviceContext  TRUE
	#define EXP_SysGraphicLightReleaseDisplayDeviceContext  CAL_CMEXPAPI( "SysGraphicLightReleaseDisplayDeviceContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightReleaseDisplayDeviceContext
	#define EXT_SysGraphicLightReleaseDisplayDeviceContext
	#define GET_SysGraphicLightReleaseDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicLightReleaseDisplayDeviceContext" ) 
	#define CAL_SysGraphicLightReleaseDisplayDeviceContext  SysGraphicLightReleaseDisplayDeviceContext
	#define CHK_SysGraphicLightReleaseDisplayDeviceContext  TRUE
	#define EXP_SysGraphicLightReleaseDisplayDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightReleaseDisplayDeviceContext", (RTS_UINTPTR)SysGraphicLightReleaseDisplayDeviceContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightReleaseDisplayDeviceContext
	#define EXT_SysGraphicLightSysGraphicLightReleaseDisplayDeviceContext
	#define GET_SysGraphicLightSysGraphicLightReleaseDisplayDeviceContext  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightReleaseDisplayDeviceContext  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightReleaseDisplayDeviceContext
	#define CHK_SysGraphicLightSysGraphicLightReleaseDisplayDeviceContext	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightReleaseDisplayDeviceContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightReleaseDisplayDeviceContext
	#define EXT_SysGraphicLightReleaseDisplayDeviceContext
	#define GET_SysGraphicLightReleaseDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicLightReleaseDisplayDeviceContext" ) 
	#define CAL_SysGraphicLightReleaseDisplayDeviceContext  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightReleaseDisplayDeviceContext
	#define CHK_SysGraphicLightReleaseDisplayDeviceContext	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightReleaseDisplayDeviceContext  CAL_CMEXPAPI( "SysGraphicLightReleaseDisplayDeviceContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightReleaseDisplayDeviceContext  PFSYSGRAPHICLIGHTRELEASEDISPLAYDEVICECONTEXT pfSysGraphicLightReleaseDisplayDeviceContext;
	#define EXT_SysGraphicLightReleaseDisplayDeviceContext  extern PFSYSGRAPHICLIGHTRELEASEDISPLAYDEVICECONTEXT pfSysGraphicLightReleaseDisplayDeviceContext;
	#define GET_SysGraphicLightReleaseDisplayDeviceContext(fl)  s_pfCMGetAPI2( "SysGraphicLightReleaseDisplayDeviceContext", (RTS_VOID_FCTPTR *)&pfSysGraphicLightReleaseDisplayDeviceContext, (fl), 0, 0)
	#define CAL_SysGraphicLightReleaseDisplayDeviceContext  pfSysGraphicLightReleaseDisplayDeviceContext
	#define CHK_SysGraphicLightReleaseDisplayDeviceContext  (pfSysGraphicLightReleaseDisplayDeviceContext != NULL)
	#define EXP_SysGraphicLightReleaseDisplayDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightReleaseDisplayDeviceContext", (RTS_UINTPTR)SysGraphicLightReleaseDisplayDeviceContext, 0, 0) 
#endif




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

void CDECL CDECL_EXT sysgraphiclightsetfill(sysgraphiclightsetfill_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTSETFILL_IEC) (sysgraphiclightsetfill_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTSETFILL_NOTIMPLEMENTED)
	#define USE_sysgraphiclightsetfill
	#define EXT_sysgraphiclightsetfill
	#define GET_sysgraphiclightsetfill(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightsetfill(p0) 
	#define CHK_sysgraphiclightsetfill  FALSE
	#define EXP_sysgraphiclightsetfill  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightsetfill
	#define EXT_sysgraphiclightsetfill
	#define GET_sysgraphiclightsetfill(fl)  CAL_CMGETAPI( "sysgraphiclightsetfill" ) 
	#define CAL_sysgraphiclightsetfill  sysgraphiclightsetfill
	#define CHK_sysgraphiclightsetfill  TRUE
	#define EXP_sysgraphiclightsetfill  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetfill", (RTS_UINTPTR)sysgraphiclightsetfill, 1, 0x70355C53, 0x03050400) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightsetfill
	#define EXT_sysgraphiclightsetfill
	#define GET_sysgraphiclightsetfill(fl)  CAL_CMGETAPI( "sysgraphiclightsetfill" ) 
	#define CAL_sysgraphiclightsetfill  sysgraphiclightsetfill
	#define CHK_sysgraphiclightsetfill  TRUE
	#define EXP_sysgraphiclightsetfill  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetfill", (RTS_UINTPTR)sysgraphiclightsetfill, 1, 0x70355C53, 0x03050400) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightsetfill
	#define EXT_SysGraphicLightsysgraphiclightsetfill
	#define GET_SysGraphicLightsysgraphiclightsetfill  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightsetfill  sysgraphiclightsetfill
	#define CHK_SysGraphicLightsysgraphiclightsetfill  TRUE
	#define EXP_SysGraphicLightsysgraphiclightsetfill  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetfill", (RTS_UINTPTR)sysgraphiclightsetfill, 1, 0x70355C53, 0x03050400) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightsetfill
	#define EXT_sysgraphiclightsetfill
	#define GET_sysgraphiclightsetfill(fl)  CAL_CMGETAPI( "sysgraphiclightsetfill" ) 
	#define CAL_sysgraphiclightsetfill  sysgraphiclightsetfill
	#define CHK_sysgraphiclightsetfill  TRUE
	#define EXP_sysgraphiclightsetfill  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetfill", (RTS_UINTPTR)sysgraphiclightsetfill, 1, 0x70355C53, 0x03050400) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightsetfill  PFSYSGRAPHICLIGHTSETFILL_IEC pfsysgraphiclightsetfill;
	#define EXT_sysgraphiclightsetfill  extern PFSYSGRAPHICLIGHTSETFILL_IEC pfsysgraphiclightsetfill;
	#define GET_sysgraphiclightsetfill(fl)  s_pfCMGetAPI2( "sysgraphiclightsetfill", (RTS_VOID_FCTPTR *)&pfsysgraphiclightsetfill, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x70355C53, 0x03050400)
	#define CAL_sysgraphiclightsetfill  pfsysgraphiclightsetfill
	#define CHK_sysgraphiclightsetfill  (pfsysgraphiclightsetfill != NULL)
	#define EXP_sysgraphiclightsetfill   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetfill", (RTS_UINTPTR)sysgraphiclightsetfill, 1, 0x70355C53, 0x03050400) 
#endif

RTS_IEC_RESULT CDECL SysGraphicLightSetFill(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_UDINT ulFillFlags, RTS_IEC_UDINT ulFillColor);
typedef RTS_IEC_RESULT (CDECL * PFSYSGRAPHICLIGHTSETFILL) (RTS_IEC_HANDLE hDisplayContext, RTS_IEC_UDINT ulFillFlags, RTS_IEC_UDINT ulFillColor);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTSETFILL_NOTIMPLEMENTED)
	#define USE_SysGraphicLightSetFill
	#define EXT_SysGraphicLightSetFill
	#define GET_SysGraphicLightSetFill(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightSetFill(p0,p1,p2)  (RTS_IEC_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightSetFill  FALSE
	#define EXP_SysGraphicLightSetFill  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightSetFill
	#define EXT_SysGraphicLightSetFill
	#define GET_SysGraphicLightSetFill(fl)  CAL_CMGETAPI( "SysGraphicLightSetFill" ) 
	#define CAL_SysGraphicLightSetFill  SysGraphicLightSetFill
	#define CHK_SysGraphicLightSetFill  TRUE
	#define EXP_SysGraphicLightSetFill  CAL_CMEXPAPI( "SysGraphicLightSetFill" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightSetFill
	#define EXT_SysGraphicLightSetFill
	#define GET_SysGraphicLightSetFill(fl)  CAL_CMGETAPI( "SysGraphicLightSetFill" ) 
	#define CAL_SysGraphicLightSetFill  SysGraphicLightSetFill
	#define CHK_SysGraphicLightSetFill  TRUE
	#define EXP_SysGraphicLightSetFill  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightSetFill", (RTS_UINTPTR)SysGraphicLightSetFill, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightSetFill
	#define EXT_SysGraphicLightSysGraphicLightSetFill
	#define GET_SysGraphicLightSysGraphicLightSetFill  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightSetFill  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightSetFill
	#define CHK_SysGraphicLightSysGraphicLightSetFill	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightSetFill  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightSetFill
	#define EXT_SysGraphicLightSetFill
	#define GET_SysGraphicLightSetFill(fl)  CAL_CMGETAPI( "SysGraphicLightSetFill" ) 
	#define CAL_SysGraphicLightSetFill  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightSetFill
	#define CHK_SysGraphicLightSetFill	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSetFill  CAL_CMEXPAPI( "SysGraphicLightSetFill" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightSetFill  PFSYSGRAPHICLIGHTSETFILL pfSysGraphicLightSetFill;
	#define EXT_SysGraphicLightSetFill  extern PFSYSGRAPHICLIGHTSETFILL pfSysGraphicLightSetFill;
	#define GET_SysGraphicLightSetFill(fl)  s_pfCMGetAPI2( "SysGraphicLightSetFill", (RTS_VOID_FCTPTR *)&pfSysGraphicLightSetFill, (fl), 0, 0)
	#define CAL_SysGraphicLightSetFill  pfSysGraphicLightSetFill
	#define CHK_SysGraphicLightSetFill  (pfSysGraphicLightSetFill != NULL)
	#define EXP_SysGraphicLightSetFill  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightSetFill", (RTS_UINTPTR)SysGraphicLightSetFill, 0, 0) 
#endif




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

void CDECL CDECL_EXT sysgraphiclightregisterfont(sysgraphiclightregisterfont_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTREGISTERFONT_IEC) (sysgraphiclightregisterfont_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTREGISTERFONT_NOTIMPLEMENTED)
	#define USE_sysgraphiclightregisterfont
	#define EXT_sysgraphiclightregisterfont
	#define GET_sysgraphiclightregisterfont(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightregisterfont(p0) 
	#define CHK_sysgraphiclightregisterfont  FALSE
	#define EXP_sysgraphiclightregisterfont  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightregisterfont
	#define EXT_sysgraphiclightregisterfont
	#define GET_sysgraphiclightregisterfont(fl)  CAL_CMGETAPI( "sysgraphiclightregisterfont" ) 
	#define CAL_sysgraphiclightregisterfont  sysgraphiclightregisterfont
	#define CHK_sysgraphiclightregisterfont  TRUE
	#define EXP_sysgraphiclightregisterfont  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightregisterfont", (RTS_UINTPTR)sysgraphiclightregisterfont, 1, RTSITF_GET_SIGNATURE(0x2C3535DF, 0), 0x03050700) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightregisterfont
	#define EXT_sysgraphiclightregisterfont
	#define GET_sysgraphiclightregisterfont(fl)  CAL_CMGETAPI( "sysgraphiclightregisterfont" ) 
	#define CAL_sysgraphiclightregisterfont  sysgraphiclightregisterfont
	#define CHK_sysgraphiclightregisterfont  TRUE
	#define EXP_sysgraphiclightregisterfont  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightregisterfont", (RTS_UINTPTR)sysgraphiclightregisterfont, 1, RTSITF_GET_SIGNATURE(0x2C3535DF, 0), 0x03050700) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightregisterfont
	#define EXT_SysGraphicLightsysgraphiclightregisterfont
	#define GET_SysGraphicLightsysgraphiclightregisterfont  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightregisterfont  sysgraphiclightregisterfont
	#define CHK_SysGraphicLightsysgraphiclightregisterfont  TRUE
	#define EXP_SysGraphicLightsysgraphiclightregisterfont  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightregisterfont", (RTS_UINTPTR)sysgraphiclightregisterfont, 1, RTSITF_GET_SIGNATURE(0x2C3535DF, 0), 0x03050700) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightregisterfont
	#define EXT_sysgraphiclightregisterfont
	#define GET_sysgraphiclightregisterfont(fl)  CAL_CMGETAPI( "sysgraphiclightregisterfont" ) 
	#define CAL_sysgraphiclightregisterfont  sysgraphiclightregisterfont
	#define CHK_sysgraphiclightregisterfont  TRUE
	#define EXP_sysgraphiclightregisterfont  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightregisterfont", (RTS_UINTPTR)sysgraphiclightregisterfont, 1, RTSITF_GET_SIGNATURE(0x2C3535DF, 0), 0x03050700) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightregisterfont  PFSYSGRAPHICLIGHTREGISTERFONT_IEC pfsysgraphiclightregisterfont;
	#define EXT_sysgraphiclightregisterfont  extern PFSYSGRAPHICLIGHTREGISTERFONT_IEC pfsysgraphiclightregisterfont;
	#define GET_sysgraphiclightregisterfont(fl)  s_pfCMGetAPI2( "sysgraphiclightregisterfont", (RTS_VOID_FCTPTR *)&pfsysgraphiclightregisterfont, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x2C3535DF, 0), 0x03050700)
	#define CAL_sysgraphiclightregisterfont  pfsysgraphiclightregisterfont
	#define CHK_sysgraphiclightregisterfont  (pfsysgraphiclightregisterfont != NULL)
	#define EXP_sysgraphiclightregisterfont   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightregisterfont", (RTS_UINTPTR)sysgraphiclightregisterfont, 1, RTSITF_GET_SIGNATURE(0x2C3535DF, 0), 0x03050700) 
#endif

RTS_IEC_RESULT CDECL SysGraphicLightRegisterFont(RTS_IEC_BYTE *pbyData, RTS_IEC_UDINT udiDataSize, RTS_IEC_STRING *pszFontName, RTS_IEC_INT iFontSize, RTS_IEC_UDINT udiFontFlags);
typedef RTS_IEC_RESULT (CDECL * PFSYSGRAPHICLIGHTREGISTERFONT) (RTS_IEC_BYTE *pbyData, RTS_IEC_UDINT udiDataSize, RTS_IEC_STRING *pszFontName, RTS_IEC_INT iFontSize, RTS_IEC_UDINT udiFontFlags);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTREGISTERFONT_NOTIMPLEMENTED)
	#define USE_SysGraphicLightRegisterFont
	#define EXT_SysGraphicLightRegisterFont
	#define GET_SysGraphicLightRegisterFont(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightRegisterFont(p0,p1,p2,p3,p4)  (RTS_IEC_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightRegisterFont  FALSE
	#define EXP_SysGraphicLightRegisterFont  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightRegisterFont
	#define EXT_SysGraphicLightRegisterFont
	#define GET_SysGraphicLightRegisterFont(fl)  CAL_CMGETAPI( "SysGraphicLightRegisterFont" ) 
	#define CAL_SysGraphicLightRegisterFont  SysGraphicLightRegisterFont
	#define CHK_SysGraphicLightRegisterFont  TRUE
	#define EXP_SysGraphicLightRegisterFont  CAL_CMEXPAPI( "SysGraphicLightRegisterFont" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightRegisterFont
	#define EXT_SysGraphicLightRegisterFont
	#define GET_SysGraphicLightRegisterFont(fl)  CAL_CMGETAPI( "SysGraphicLightRegisterFont" ) 
	#define CAL_SysGraphicLightRegisterFont  SysGraphicLightRegisterFont
	#define CHK_SysGraphicLightRegisterFont  TRUE
	#define EXP_SysGraphicLightRegisterFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightRegisterFont", (RTS_UINTPTR)SysGraphicLightRegisterFont, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightRegisterFont
	#define EXT_SysGraphicLightSysGraphicLightRegisterFont
	#define GET_SysGraphicLightSysGraphicLightRegisterFont  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightRegisterFont  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightRegisterFont
	#define CHK_SysGraphicLightSysGraphicLightRegisterFont	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightRegisterFont  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightRegisterFont
	#define EXT_SysGraphicLightRegisterFont
	#define GET_SysGraphicLightRegisterFont(fl)  CAL_CMGETAPI( "SysGraphicLightRegisterFont" ) 
	#define CAL_SysGraphicLightRegisterFont  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightRegisterFont
	#define CHK_SysGraphicLightRegisterFont	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightRegisterFont  CAL_CMEXPAPI( "SysGraphicLightRegisterFont" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightRegisterFont  PFSYSGRAPHICLIGHTREGISTERFONT pfSysGraphicLightRegisterFont;
	#define EXT_SysGraphicLightRegisterFont  extern PFSYSGRAPHICLIGHTREGISTERFONT pfSysGraphicLightRegisterFont;
	#define GET_SysGraphicLightRegisterFont(fl)  s_pfCMGetAPI2( "SysGraphicLightRegisterFont", (RTS_VOID_FCTPTR *)&pfSysGraphicLightRegisterFont, (fl), 0, 0)
	#define CAL_SysGraphicLightRegisterFont  pfSysGraphicLightRegisterFont
	#define CHK_SysGraphicLightRegisterFont  (pfSysGraphicLightRegisterFont != NULL)
	#define EXP_SysGraphicLightRegisterFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightRegisterFont", (RTS_UINTPTR)SysGraphicLightRegisterFont, 0, 0) 
#endif





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

void CDECL CDECL_EXT sysgraphiclightsetfont(sysgraphiclightsetfont_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTSETFONT_IEC) (sysgraphiclightsetfont_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTSETFONT_NOTIMPLEMENTED)
	#define USE_sysgraphiclightsetfont
	#define EXT_sysgraphiclightsetfont
	#define GET_sysgraphiclightsetfont(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightsetfont(p0) 
	#define CHK_sysgraphiclightsetfont  FALSE
	#define EXP_sysgraphiclightsetfont  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightsetfont
	#define EXT_sysgraphiclightsetfont
	#define GET_sysgraphiclightsetfont(fl)  CAL_CMGETAPI( "sysgraphiclightsetfont" ) 
	#define CAL_sysgraphiclightsetfont  sysgraphiclightsetfont
	#define CHK_sysgraphiclightsetfont  TRUE
	#define EXP_sysgraphiclightsetfont  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetfont", (RTS_UINTPTR)sysgraphiclightsetfont, 1, 0x482F9A11, 0x03050400) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightsetfont
	#define EXT_sysgraphiclightsetfont
	#define GET_sysgraphiclightsetfont(fl)  CAL_CMGETAPI( "sysgraphiclightsetfont" ) 
	#define CAL_sysgraphiclightsetfont  sysgraphiclightsetfont
	#define CHK_sysgraphiclightsetfont  TRUE
	#define EXP_sysgraphiclightsetfont  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetfont", (RTS_UINTPTR)sysgraphiclightsetfont, 1, 0x482F9A11, 0x03050400) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightsetfont
	#define EXT_SysGraphicLightsysgraphiclightsetfont
	#define GET_SysGraphicLightsysgraphiclightsetfont  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightsetfont  sysgraphiclightsetfont
	#define CHK_SysGraphicLightsysgraphiclightsetfont  TRUE
	#define EXP_SysGraphicLightsysgraphiclightsetfont  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetfont", (RTS_UINTPTR)sysgraphiclightsetfont, 1, 0x482F9A11, 0x03050400) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightsetfont
	#define EXT_sysgraphiclightsetfont
	#define GET_sysgraphiclightsetfont(fl)  CAL_CMGETAPI( "sysgraphiclightsetfont" ) 
	#define CAL_sysgraphiclightsetfont  sysgraphiclightsetfont
	#define CHK_sysgraphiclightsetfont  TRUE
	#define EXP_sysgraphiclightsetfont  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetfont", (RTS_UINTPTR)sysgraphiclightsetfont, 1, 0x482F9A11, 0x03050400) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightsetfont  PFSYSGRAPHICLIGHTSETFONT_IEC pfsysgraphiclightsetfont;
	#define EXT_sysgraphiclightsetfont  extern PFSYSGRAPHICLIGHTSETFONT_IEC pfsysgraphiclightsetfont;
	#define GET_sysgraphiclightsetfont(fl)  s_pfCMGetAPI2( "sysgraphiclightsetfont", (RTS_VOID_FCTPTR *)&pfsysgraphiclightsetfont, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x482F9A11, 0x03050400)
	#define CAL_sysgraphiclightsetfont  pfsysgraphiclightsetfont
	#define CHK_sysgraphiclightsetfont  (pfsysgraphiclightsetfont != NULL)
	#define EXP_sysgraphiclightsetfont   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetfont", (RTS_UINTPTR)sysgraphiclightsetfont, 1, 0x482F9A11, 0x03050400) 
#endif

RTS_IEC_RESULT CDECL SysGraphicLightSetFont(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *pszFontName, RTS_IEC_INT iFontSize, RTS_IEC_UDINT ulFontFlags, RTS_IEC_UDINT ulFontCharSet, RTS_IEC_UDINT ulFontColor);
typedef RTS_IEC_RESULT (CDECL * PFSYSGRAPHICLIGHTSETFONT) (RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *pszFontName, RTS_IEC_INT iFontSize, RTS_IEC_UDINT ulFontFlags, RTS_IEC_UDINT ulFontCharSet, RTS_IEC_UDINT ulFontColor);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTSETFONT_NOTIMPLEMENTED)
	#define USE_SysGraphicLightSetFont
	#define EXT_SysGraphicLightSetFont
	#define GET_SysGraphicLightSetFont(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightSetFont(p0,p1,p2,p3,p4,p5)  (RTS_IEC_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightSetFont  FALSE
	#define EXP_SysGraphicLightSetFont  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightSetFont
	#define EXT_SysGraphicLightSetFont
	#define GET_SysGraphicLightSetFont(fl)  CAL_CMGETAPI( "SysGraphicLightSetFont" ) 
	#define CAL_SysGraphicLightSetFont  SysGraphicLightSetFont
	#define CHK_SysGraphicLightSetFont  TRUE
	#define EXP_SysGraphicLightSetFont  CAL_CMEXPAPI( "SysGraphicLightSetFont" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightSetFont
	#define EXT_SysGraphicLightSetFont
	#define GET_SysGraphicLightSetFont(fl)  CAL_CMGETAPI( "SysGraphicLightSetFont" ) 
	#define CAL_SysGraphicLightSetFont  SysGraphicLightSetFont
	#define CHK_SysGraphicLightSetFont  TRUE
	#define EXP_SysGraphicLightSetFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightSetFont", (RTS_UINTPTR)SysGraphicLightSetFont, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightSetFont
	#define EXT_SysGraphicLightSysGraphicLightSetFont
	#define GET_SysGraphicLightSysGraphicLightSetFont  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightSetFont  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightSetFont
	#define CHK_SysGraphicLightSysGraphicLightSetFont	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightSetFont  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightSetFont
	#define EXT_SysGraphicLightSetFont
	#define GET_SysGraphicLightSetFont(fl)  CAL_CMGETAPI( "SysGraphicLightSetFont" ) 
	#define CAL_SysGraphicLightSetFont  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightSetFont
	#define CHK_SysGraphicLightSetFont	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSetFont  CAL_CMEXPAPI( "SysGraphicLightSetFont" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightSetFont  PFSYSGRAPHICLIGHTSETFONT pfSysGraphicLightSetFont;
	#define EXT_SysGraphicLightSetFont  extern PFSYSGRAPHICLIGHTSETFONT pfSysGraphicLightSetFont;
	#define GET_SysGraphicLightSetFont(fl)  s_pfCMGetAPI2( "SysGraphicLightSetFont", (RTS_VOID_FCTPTR *)&pfSysGraphicLightSetFont, (fl), 0, 0)
	#define CAL_SysGraphicLightSetFont  pfSysGraphicLightSetFont
	#define CHK_SysGraphicLightSetFont  (pfSysGraphicLightSetFont != NULL)
	#define EXP_SysGraphicLightSetFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightSetFont", (RTS_UINTPTR)SysGraphicLightSetFont, 0, 0) 
#endif




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

void CDECL CDECL_EXT sysgraphiclightsetline(sysgraphiclightsetline_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSGRAPHICLIGHTSETLINE_IEC) (sysgraphiclightsetline_struct *p);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTSETLINE_NOTIMPLEMENTED)
	#define USE_sysgraphiclightsetline
	#define EXT_sysgraphiclightsetline
	#define GET_sysgraphiclightsetline(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysgraphiclightsetline(p0) 
	#define CHK_sysgraphiclightsetline  FALSE
	#define EXP_sysgraphiclightsetline  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysgraphiclightsetline
	#define EXT_sysgraphiclightsetline
	#define GET_sysgraphiclightsetline(fl)  CAL_CMGETAPI( "sysgraphiclightsetline" ) 
	#define CAL_sysgraphiclightsetline  sysgraphiclightsetline
	#define CHK_sysgraphiclightsetline  TRUE
	#define EXP_sysgraphiclightsetline  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetline", (RTS_UINTPTR)sysgraphiclightsetline, 1, 0xC7E0F739, 0x03050400) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_sysgraphiclightsetline
	#define EXT_sysgraphiclightsetline
	#define GET_sysgraphiclightsetline(fl)  CAL_CMGETAPI( "sysgraphiclightsetline" ) 
	#define CAL_sysgraphiclightsetline  sysgraphiclightsetline
	#define CHK_sysgraphiclightsetline  TRUE
	#define EXP_sysgraphiclightsetline  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetline", (RTS_UINTPTR)sysgraphiclightsetline, 1, 0xC7E0F739, 0x03050400) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightsysgraphiclightsetline
	#define EXT_SysGraphicLightsysgraphiclightsetline
	#define GET_SysGraphicLightsysgraphiclightsetline  ERR_OK
	#define CAL_SysGraphicLightsysgraphiclightsetline  sysgraphiclightsetline
	#define CHK_SysGraphicLightsysgraphiclightsetline  TRUE
	#define EXP_SysGraphicLightsysgraphiclightsetline  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetline", (RTS_UINTPTR)sysgraphiclightsetline, 1, 0xC7E0F739, 0x03050400) 
#elif defined(CPLUSPLUS)
	#define USE_sysgraphiclightsetline
	#define EXT_sysgraphiclightsetline
	#define GET_sysgraphiclightsetline(fl)  CAL_CMGETAPI( "sysgraphiclightsetline" ) 
	#define CAL_sysgraphiclightsetline  sysgraphiclightsetline
	#define CHK_sysgraphiclightsetline  TRUE
	#define EXP_sysgraphiclightsetline  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetline", (RTS_UINTPTR)sysgraphiclightsetline, 1, 0xC7E0F739, 0x03050400) 
#else /* DYNAMIC_LINK */
	#define USE_sysgraphiclightsetline  PFSYSGRAPHICLIGHTSETLINE_IEC pfsysgraphiclightsetline;
	#define EXT_sysgraphiclightsetline  extern PFSYSGRAPHICLIGHTSETLINE_IEC pfsysgraphiclightsetline;
	#define GET_sysgraphiclightsetline(fl)  s_pfCMGetAPI2( "sysgraphiclightsetline", (RTS_VOID_FCTPTR *)&pfsysgraphiclightsetline, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xC7E0F739, 0x03050400)
	#define CAL_sysgraphiclightsetline  pfsysgraphiclightsetline
	#define CHK_sysgraphiclightsetline  (pfsysgraphiclightsetline != NULL)
	#define EXP_sysgraphiclightsetline   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysgraphiclightsetline", (RTS_UINTPTR)sysgraphiclightsetline, 1, 0xC7E0F739, 0x03050400) 
#endif

RTS_IEC_RESULT CDECL SysGraphicLightSetLine(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_INT iLineWidth, RTS_IEC_UDINT ulLineFlags, RTS_IEC_UDINT ulLineColor);
typedef RTS_IEC_RESULT (CDECL * PFSYSGRAPHICLIGHTSETLINE) (RTS_IEC_HANDLE hDisplayContext, RTS_IEC_INT iLineWidth, RTS_IEC_UDINT ulLineFlags, RTS_IEC_UDINT ulLineColor);
#if defined(SYSGRAPHICLIGHT_NOTIMPLEMENTED) || defined(SYSGRAPHICLIGHTSETLINE_NOTIMPLEMENTED)
	#define USE_SysGraphicLightSetLine
	#define EXT_SysGraphicLightSetLine
	#define GET_SysGraphicLightSetLine(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicLightSetLine(p0,p1,p2,p3)  (RTS_IEC_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicLightSetLine  FALSE
	#define EXP_SysGraphicLightSetLine  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicLightSetLine
	#define EXT_SysGraphicLightSetLine
	#define GET_SysGraphicLightSetLine(fl)  CAL_CMGETAPI( "SysGraphicLightSetLine" ) 
	#define CAL_SysGraphicLightSetLine  SysGraphicLightSetLine
	#define CHK_SysGraphicLightSetLine  TRUE
	#define EXP_SysGraphicLightSetLine  CAL_CMEXPAPI( "SysGraphicLightSetLine" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICLIGHT_EXTERNAL)
	#define USE_SysGraphicLightSetLine
	#define EXT_SysGraphicLightSetLine
	#define GET_SysGraphicLightSetLine(fl)  CAL_CMGETAPI( "SysGraphicLightSetLine" ) 
	#define CAL_SysGraphicLightSetLine  SysGraphicLightSetLine
	#define CHK_SysGraphicLightSetLine  TRUE
	#define EXP_SysGraphicLightSetLine  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightSetLine", (RTS_UINTPTR)SysGraphicLightSetLine, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicLightSysGraphicLightSetLine
	#define EXT_SysGraphicLightSysGraphicLightSetLine
	#define GET_SysGraphicLightSysGraphicLightSetLine  ERR_OK
	#define CAL_SysGraphicLightSysGraphicLightSetLine  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightSetLine
	#define CHK_SysGraphicLightSysGraphicLightSetLine	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSysGraphicLightSetLine  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicLightSetLine
	#define EXT_SysGraphicLightSetLine
	#define GET_SysGraphicLightSetLine(fl)  CAL_CMGETAPI( "SysGraphicLightSetLine" ) 
	#define CAL_SysGraphicLightSetLine  ((ISysGraphicLight*)s_pfCMCreateInstance(CLASSID_CSysGraphicLight, NULL))->ISysGraphicLightSetLine
	#define CHK_SysGraphicLightSetLine	(s_pfCMCreateInstance != NULL && pISysGraphicLight != NULL)
	#define EXP_SysGraphicLightSetLine  CAL_CMEXPAPI( "SysGraphicLightSetLine" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicLightSetLine  PFSYSGRAPHICLIGHTSETLINE pfSysGraphicLightSetLine;
	#define EXT_SysGraphicLightSetLine  extern PFSYSGRAPHICLIGHTSETLINE pfSysGraphicLightSetLine;
	#define GET_SysGraphicLightSetLine(fl)  s_pfCMGetAPI2( "SysGraphicLightSetLine", (RTS_VOID_FCTPTR *)&pfSysGraphicLightSetLine, (fl), 0, 0)
	#define CAL_SysGraphicLightSetLine  pfSysGraphicLightSetLine
	#define CHK_SysGraphicLightSetLine  (pfSysGraphicLightSetLine != NULL)
	#define EXP_SysGraphicLightSetLine  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicLightSetLine", (RTS_UINTPTR)SysGraphicLightSetLine, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
	PFSYSGRAPHICLIGHTBEGINPAINT ISysGraphicLightBeginPaint;
 	PFSYSGRAPHICLIGHTDRAWBITMAP ISysGraphicLightDrawBitmap;
 	PFSYSGRAPHICLIGHTDRAWPOLYGON ISysGraphicLightDrawPolygon;
 	PFSYSGRAPHICLIGHTDRAWRECT ISysGraphicLightDrawRect;
 	PFSYSGRAPHICLIGHTDRAWTEXT ISysGraphicLightDrawText;
 	PFSYSGRAPHICLIGHTENDPAINT ISysGraphicLightEndPaint;
 	PFSYSGRAPHICLIGHTGETDISPLAYDEVICECONTEXT ISysGraphicLightGetDisplayDeviceContext;
 	PFSYSGRAPHICLIGHTRELEASEDISPLAYDEVICECONTEXT ISysGraphicLightReleaseDisplayDeviceContext;
 	PFSYSGRAPHICLIGHTSETFILL ISysGraphicLightSetFill;
 	PFSYSGRAPHICLIGHTREGISTERFONT ISysGraphicLightRegisterFont;
 	PFSYSGRAPHICLIGHTSETFONT ISysGraphicLightSetFont;
 	PFSYSGRAPHICLIGHTSETLINE ISysGraphicLightSetLine;
 } ISysGraphicLight_C;

#ifdef CPLUSPLUS
class ISysGraphicLight : public IBase
{
	public:
		virtual RTS_IEC_RESULT CDECL ISysGraphicLightBeginPaint(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *rsCurrentVisuName, RTS_IEC_UDINT ulFlags) =0;
		virtual RTS_IEC_RESULT CDECL ISysGraphicLightDrawBitmap(RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_BYTE *pbyData, RTS_IEC_UDINT ulDataSize, RTS_IEC_UDINT ulTransparentColor, RTS_IEC_UDINT ulFlags) =0;
		virtual RTS_IEC_RESULT CDECL ISysGraphicLightDrawPolygon(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_INT iPoints , RTS_Point *pPoints, RTS_IEC_UINT ePolygonType) =0;
		virtual RTS_IEC_RESULT CDECL ISysGraphicLightDrawRect(RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_UINT eRectType) =0;
		virtual RTS_IEC_RESULT CDECL ISysGraphicLightDrawText(RTS_IEC_HANDLE hDisplayContext, RTS_Rectangle rectangle, RTS_IEC_BYTE *pszText, RTS_IEC_UDINT ulDrawFlags) =0;
		virtual RTS_IEC_RESULT CDECL ISysGraphicLightEndPaint(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *rsCurrentVisuName, RTS_IEC_UDINT ulFlags) =0;
		virtual RTS_IEC_HANDLE CDECL ISysGraphicLightGetDisplayDeviceContext(RTS_IEC_UDINT ulDisplayID, RTS_IEC_RESULT *pResult) =0;
		virtual RTS_IEC_RESULT CDECL ISysGraphicLightReleaseDisplayDeviceContext(RTS_IEC_HANDLE hDisplayContext) =0;
		virtual RTS_IEC_RESULT CDECL ISysGraphicLightSetFill(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_UDINT ulFillFlags, RTS_IEC_UDINT ulFillColor) =0;
		virtual RTS_IEC_RESULT CDECL ISysGraphicLightRegisterFont(RTS_IEC_BYTE *pbyData, RTS_IEC_UDINT udiDataSize, RTS_IEC_STRING *pszFontName, RTS_IEC_INT iFontSize, RTS_IEC_UDINT udiFontFlags) =0;
		virtual RTS_IEC_RESULT CDECL ISysGraphicLightSetFont(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_STRING *pszFontName, RTS_IEC_INT iFontSize, RTS_IEC_UDINT ulFontFlags, RTS_IEC_UDINT ulFontCharSet, RTS_IEC_UDINT ulFontColor) =0;
		virtual RTS_IEC_RESULT CDECL ISysGraphicLightSetLine(RTS_IEC_HANDLE hDisplayContext, RTS_IEC_INT iLineWidth, RTS_IEC_UDINT ulLineFlags, RTS_IEC_UDINT ulLineColor) =0;
};
	#ifndef ITF_SysGraphicLight
		#define ITF_SysGraphicLight static ISysGraphicLight *pISysGraphicLight = NULL;
	#endif
	#define EXTITF_SysGraphicLight
#else	/*CPLUSPLUS*/
	typedef ISysGraphicLight_C		ISysGraphicLight;
	#ifndef ITF_SysGraphicLight
		#define ITF_SysGraphicLight
	#endif
	#define EXTITF_SysGraphicLight
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSGRAPHICLIGHTITF_H_*/
