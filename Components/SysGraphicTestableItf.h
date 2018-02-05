 /**
 * <interfacename>SysGraphicTestable</interfacename>
 * <description> 
 *	<p>The interface SysGraphicTestable is intended for implementing automatic testability in a graphical component. Typically this
 *	interface can be implemented by components intended for embedded graphics (framebuffer, light visualization). It is primarily meant as
 *	a simplification of <see>SysGraphicNative</see> to support automated testing.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSGRAPHICTESTABLEITF_H_
#define _SYSGRAPHICTESTABLEITF_H_

#include "CmpStd.h"

 

 




#ifndef CDECL
	#define CDECL
#endif

#include "SysGraphicBase.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Creates a handle to a test object that can be used in further calls. If you do not use this handle any more, release it using
 *	<see>SysGraphicTestableDestroy</see></description>
 * <param name="pResult" type="OUT">Optionally returns an error code</param>
 * <remarks>For Implementers: In fact nothing has to be created; it's merely a way for getting calls to initialize and shutdown.</remarks>
 * <result>The handle to the test object or <see>RTS_INVALID_HANDLE</see> in case of errors.</result>
 */
RTS_HANDLE CDECL SysGraphicTestableCreate(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSGRAPHICTESTABLECREATE) (RTS_RESULT *pResult);
#if defined(SYSGRAPHICTESTABLE_NOTIMPLEMENTED) || defined(SYSGRAPHICTESTABLECREATE_NOTIMPLEMENTED)
	#define USE_SysGraphicTestableCreate
	#define EXT_SysGraphicTestableCreate
	#define GET_SysGraphicTestableCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicTestableCreate(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysGraphicTestableCreate  FALSE
	#define EXP_SysGraphicTestableCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicTestableCreate
	#define EXT_SysGraphicTestableCreate
	#define GET_SysGraphicTestableCreate(fl)  CAL_CMGETAPI( "SysGraphicTestableCreate" ) 
	#define CAL_SysGraphicTestableCreate  SysGraphicTestableCreate
	#define CHK_SysGraphicTestableCreate  TRUE
	#define EXP_SysGraphicTestableCreate  CAL_CMEXPAPI( "SysGraphicTestableCreate" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICTESTABLE_EXTERNAL)
	#define USE_SysGraphicTestableCreate
	#define EXT_SysGraphicTestableCreate
	#define GET_SysGraphicTestableCreate(fl)  CAL_CMGETAPI( "SysGraphicTestableCreate" ) 
	#define CAL_SysGraphicTestableCreate  SysGraphicTestableCreate
	#define CHK_SysGraphicTestableCreate  TRUE
	#define EXP_SysGraphicTestableCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTestableCreate", (RTS_UINTPTR)SysGraphicTestableCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicTestableSysGraphicTestableCreate
	#define EXT_SysGraphicTestableSysGraphicTestableCreate
	#define GET_SysGraphicTestableSysGraphicTestableCreate  ERR_OK
	#define CAL_SysGraphicTestableSysGraphicTestableCreate pISysGraphicTestable->ISysGraphicTestableCreate
	#define CHK_SysGraphicTestableSysGraphicTestableCreate (pISysGraphicTestable != NULL)
	#define EXP_SysGraphicTestableSysGraphicTestableCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicTestableCreate
	#define EXT_SysGraphicTestableCreate
	#define GET_SysGraphicTestableCreate(fl)  CAL_CMGETAPI( "SysGraphicTestableCreate" ) 
	#define CAL_SysGraphicTestableCreate pISysGraphicTestable->ISysGraphicTestableCreate
	#define CHK_SysGraphicTestableCreate (pISysGraphicTestable != NULL)
	#define EXP_SysGraphicTestableCreate  CAL_CMEXPAPI( "SysGraphicTestableCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicTestableCreate  PFSYSGRAPHICTESTABLECREATE pfSysGraphicTestableCreate;
	#define EXT_SysGraphicTestableCreate  extern PFSYSGRAPHICTESTABLECREATE pfSysGraphicTestableCreate;
	#define GET_SysGraphicTestableCreate(fl)  s_pfCMGetAPI2( "SysGraphicTestableCreate", (RTS_VOID_FCTPTR *)&pfSysGraphicTestableCreate, (fl), 0, 0)
	#define CAL_SysGraphicTestableCreate  pfSysGraphicTestableCreate
	#define CHK_SysGraphicTestableCreate  (pfSysGraphicTestableCreate != NULL)
	#define EXP_SysGraphicTestableCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTestableCreate", (RTS_UINTPTR)SysGraphicTestableCreate, 0, 0) 
#endif




/**
 * <description>Releases a handle to a test object that was returned by <see>SysGraphicTestableCreate</see>.</description>
 * <param name="hDisplayContext" type="IN">The native displaycontext to release</param>
 * <result>An error code</result>
 */
RTS_RESULT CDECL SysGraphicTestableDestroy(RTS_HANDLE hTestable);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICTESTABLEDESTROY) (RTS_HANDLE hTestable);
#if defined(SYSGRAPHICTESTABLE_NOTIMPLEMENTED) || defined(SYSGRAPHICTESTABLEDESTROY_NOTIMPLEMENTED)
	#define USE_SysGraphicTestableDestroy
	#define EXT_SysGraphicTestableDestroy
	#define GET_SysGraphicTestableDestroy(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicTestableDestroy(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicTestableDestroy  FALSE
	#define EXP_SysGraphicTestableDestroy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicTestableDestroy
	#define EXT_SysGraphicTestableDestroy
	#define GET_SysGraphicTestableDestroy(fl)  CAL_CMGETAPI( "SysGraphicTestableDestroy" ) 
	#define CAL_SysGraphicTestableDestroy  SysGraphicTestableDestroy
	#define CHK_SysGraphicTestableDestroy  TRUE
	#define EXP_SysGraphicTestableDestroy  CAL_CMEXPAPI( "SysGraphicTestableDestroy" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICTESTABLE_EXTERNAL)
	#define USE_SysGraphicTestableDestroy
	#define EXT_SysGraphicTestableDestroy
	#define GET_SysGraphicTestableDestroy(fl)  CAL_CMGETAPI( "SysGraphicTestableDestroy" ) 
	#define CAL_SysGraphicTestableDestroy  SysGraphicTestableDestroy
	#define CHK_SysGraphicTestableDestroy  TRUE
	#define EXP_SysGraphicTestableDestroy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTestableDestroy", (RTS_UINTPTR)SysGraphicTestableDestroy, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicTestableSysGraphicTestableDestroy
	#define EXT_SysGraphicTestableSysGraphicTestableDestroy
	#define GET_SysGraphicTestableSysGraphicTestableDestroy  ERR_OK
	#define CAL_SysGraphicTestableSysGraphicTestableDestroy pISysGraphicTestable->ISysGraphicTestableDestroy
	#define CHK_SysGraphicTestableSysGraphicTestableDestroy (pISysGraphicTestable != NULL)
	#define EXP_SysGraphicTestableSysGraphicTestableDestroy  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicTestableDestroy
	#define EXT_SysGraphicTestableDestroy
	#define GET_SysGraphicTestableDestroy(fl)  CAL_CMGETAPI( "SysGraphicTestableDestroy" ) 
	#define CAL_SysGraphicTestableDestroy pISysGraphicTestable->ISysGraphicTestableDestroy
	#define CHK_SysGraphicTestableDestroy (pISysGraphicTestable != NULL)
	#define EXP_SysGraphicTestableDestroy  CAL_CMEXPAPI( "SysGraphicTestableDestroy" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicTestableDestroy  PFSYSGRAPHICTESTABLEDESTROY pfSysGraphicTestableDestroy;
	#define EXT_SysGraphicTestableDestroy  extern PFSYSGRAPHICTESTABLEDESTROY pfSysGraphicTestableDestroy;
	#define GET_SysGraphicTestableDestroy(fl)  s_pfCMGetAPI2( "SysGraphicTestableDestroy", (RTS_VOID_FCTPTR *)&pfSysGraphicTestableDestroy, (fl), 0, 0)
	#define CAL_SysGraphicTestableDestroy  pfSysGraphicTestableDestroy
	#define CHK_SysGraphicTestableDestroy  (pfSysGraphicTestableDestroy != NULL)
	#define EXP_SysGraphicTestableDestroy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTestableDestroy", (RTS_UINTPTR)SysGraphicTestableDestroy, 0, 0) 
#endif




/**
 * <description>Returns the size of the display.</description>
 * <param name="pSize" type="OUT">This structure will be filled with the size of the native display.</param>
 * <result>An error code</result>
 */
RTS_RESULT CDECL SysGraphicTestableGetDisplaySize(RTS_HANDLE hTestable, RTS_Size* pSize);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICTESTABLEGETDISPLAYSIZE) (RTS_HANDLE hTestable, RTS_Size* pSize);
#if defined(SYSGRAPHICTESTABLE_NOTIMPLEMENTED) || defined(SYSGRAPHICTESTABLEGETDISPLAYSIZE_NOTIMPLEMENTED)
	#define USE_SysGraphicTestableGetDisplaySize
	#define EXT_SysGraphicTestableGetDisplaySize
	#define GET_SysGraphicTestableGetDisplaySize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicTestableGetDisplaySize(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicTestableGetDisplaySize  FALSE
	#define EXP_SysGraphicTestableGetDisplaySize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicTestableGetDisplaySize
	#define EXT_SysGraphicTestableGetDisplaySize
	#define GET_SysGraphicTestableGetDisplaySize(fl)  CAL_CMGETAPI( "SysGraphicTestableGetDisplaySize" ) 
	#define CAL_SysGraphicTestableGetDisplaySize  SysGraphicTestableGetDisplaySize
	#define CHK_SysGraphicTestableGetDisplaySize  TRUE
	#define EXP_SysGraphicTestableGetDisplaySize  CAL_CMEXPAPI( "SysGraphicTestableGetDisplaySize" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICTESTABLE_EXTERNAL)
	#define USE_SysGraphicTestableGetDisplaySize
	#define EXT_SysGraphicTestableGetDisplaySize
	#define GET_SysGraphicTestableGetDisplaySize(fl)  CAL_CMGETAPI( "SysGraphicTestableGetDisplaySize" ) 
	#define CAL_SysGraphicTestableGetDisplaySize  SysGraphicTestableGetDisplaySize
	#define CHK_SysGraphicTestableGetDisplaySize  TRUE
	#define EXP_SysGraphicTestableGetDisplaySize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTestableGetDisplaySize", (RTS_UINTPTR)SysGraphicTestableGetDisplaySize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicTestableSysGraphicTestableGetDisplaySize
	#define EXT_SysGraphicTestableSysGraphicTestableGetDisplaySize
	#define GET_SysGraphicTestableSysGraphicTestableGetDisplaySize  ERR_OK
	#define CAL_SysGraphicTestableSysGraphicTestableGetDisplaySize pISysGraphicTestable->ISysGraphicTestableGetDisplaySize
	#define CHK_SysGraphicTestableSysGraphicTestableGetDisplaySize (pISysGraphicTestable != NULL)
	#define EXP_SysGraphicTestableSysGraphicTestableGetDisplaySize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicTestableGetDisplaySize
	#define EXT_SysGraphicTestableGetDisplaySize
	#define GET_SysGraphicTestableGetDisplaySize(fl)  CAL_CMGETAPI( "SysGraphicTestableGetDisplaySize" ) 
	#define CAL_SysGraphicTestableGetDisplaySize pISysGraphicTestable->ISysGraphicTestableGetDisplaySize
	#define CHK_SysGraphicTestableGetDisplaySize (pISysGraphicTestable != NULL)
	#define EXP_SysGraphicTestableGetDisplaySize  CAL_CMEXPAPI( "SysGraphicTestableGetDisplaySize" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicTestableGetDisplaySize  PFSYSGRAPHICTESTABLEGETDISPLAYSIZE pfSysGraphicTestableGetDisplaySize;
	#define EXT_SysGraphicTestableGetDisplaySize  extern PFSYSGRAPHICTESTABLEGETDISPLAYSIZE pfSysGraphicTestableGetDisplaySize;
	#define GET_SysGraphicTestableGetDisplaySize(fl)  s_pfCMGetAPI2( "SysGraphicTestableGetDisplaySize", (RTS_VOID_FCTPTR *)&pfSysGraphicTestableGetDisplaySize, (fl), 0, 0)
	#define CAL_SysGraphicTestableGetDisplaySize  pfSysGraphicTestableGetDisplaySize
	#define CHK_SysGraphicTestableGetDisplaySize  (pfSysGraphicTestableGetDisplaySize != NULL)
	#define EXP_SysGraphicTestableGetDisplaySize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTestableGetDisplaySize", (RTS_UINTPTR)SysGraphicTestableGetDisplaySize, 0, 0) 
#endif




/**
 * <description>This method can be called for retrieving the color of a displayed pixel.</description>
 * <param name="hDC" type="IN">The testable object</param>
 * <param name="sX" type="IN">The x coordinate to get the color from</param>
 * <param name="sY" type="IN">The y coordinate to get the color from</param>
 * <param name="pulColorValue" type="IN">Pointer that will return the determined color. The color will be in the
 * format used by the iec visualization ([--------|RRRRRRRR|GGGGGGGG|BBBBBBBB]).</param>
 * <result>An error code</result>
 */
RTS_RESULT CDECL SysGraphicTestableGetDisplayPixel(RTS_HANDLE hTestable, short sX, short sY, unsigned long* pulColorValue);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICTESTABLEGETDISPLAYPIXEL) (RTS_HANDLE hTestable, short sX, short sY, unsigned long* pulColorValue);
#if defined(SYSGRAPHICTESTABLE_NOTIMPLEMENTED) || defined(SYSGRAPHICTESTABLEGETDISPLAYPIXEL_NOTIMPLEMENTED)
	#define USE_SysGraphicTestableGetDisplayPixel
	#define EXT_SysGraphicTestableGetDisplayPixel
	#define GET_SysGraphicTestableGetDisplayPixel(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicTestableGetDisplayPixel(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicTestableGetDisplayPixel  FALSE
	#define EXP_SysGraphicTestableGetDisplayPixel  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicTestableGetDisplayPixel
	#define EXT_SysGraphicTestableGetDisplayPixel
	#define GET_SysGraphicTestableGetDisplayPixel(fl)  CAL_CMGETAPI( "SysGraphicTestableGetDisplayPixel" ) 
	#define CAL_SysGraphicTestableGetDisplayPixel  SysGraphicTestableGetDisplayPixel
	#define CHK_SysGraphicTestableGetDisplayPixel  TRUE
	#define EXP_SysGraphicTestableGetDisplayPixel  CAL_CMEXPAPI( "SysGraphicTestableGetDisplayPixel" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICTESTABLE_EXTERNAL)
	#define USE_SysGraphicTestableGetDisplayPixel
	#define EXT_SysGraphicTestableGetDisplayPixel
	#define GET_SysGraphicTestableGetDisplayPixel(fl)  CAL_CMGETAPI( "SysGraphicTestableGetDisplayPixel" ) 
	#define CAL_SysGraphicTestableGetDisplayPixel  SysGraphicTestableGetDisplayPixel
	#define CHK_SysGraphicTestableGetDisplayPixel  TRUE
	#define EXP_SysGraphicTestableGetDisplayPixel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTestableGetDisplayPixel", (RTS_UINTPTR)SysGraphicTestableGetDisplayPixel, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicTestableSysGraphicTestableGetDisplayPixel
	#define EXT_SysGraphicTestableSysGraphicTestableGetDisplayPixel
	#define GET_SysGraphicTestableSysGraphicTestableGetDisplayPixel  ERR_OK
	#define CAL_SysGraphicTestableSysGraphicTestableGetDisplayPixel pISysGraphicTestable->ISysGraphicTestableGetDisplayPixel
	#define CHK_SysGraphicTestableSysGraphicTestableGetDisplayPixel (pISysGraphicTestable != NULL)
	#define EXP_SysGraphicTestableSysGraphicTestableGetDisplayPixel  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicTestableGetDisplayPixel
	#define EXT_SysGraphicTestableGetDisplayPixel
	#define GET_SysGraphicTestableGetDisplayPixel(fl)  CAL_CMGETAPI( "SysGraphicTestableGetDisplayPixel" ) 
	#define CAL_SysGraphicTestableGetDisplayPixel pISysGraphicTestable->ISysGraphicTestableGetDisplayPixel
	#define CHK_SysGraphicTestableGetDisplayPixel (pISysGraphicTestable != NULL)
	#define EXP_SysGraphicTestableGetDisplayPixel  CAL_CMEXPAPI( "SysGraphicTestableGetDisplayPixel" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicTestableGetDisplayPixel  PFSYSGRAPHICTESTABLEGETDISPLAYPIXEL pfSysGraphicTestableGetDisplayPixel;
	#define EXT_SysGraphicTestableGetDisplayPixel  extern PFSYSGRAPHICTESTABLEGETDISPLAYPIXEL pfSysGraphicTestableGetDisplayPixel;
	#define GET_SysGraphicTestableGetDisplayPixel(fl)  s_pfCMGetAPI2( "SysGraphicTestableGetDisplayPixel", (RTS_VOID_FCTPTR *)&pfSysGraphicTestableGetDisplayPixel, (fl), 0, 0)
	#define CAL_SysGraphicTestableGetDisplayPixel  pfSysGraphicTestableGetDisplayPixel
	#define CHK_SysGraphicTestableGetDisplayPixel  (pfSysGraphicTestableGetDisplayPixel != NULL)
	#define EXP_SysGraphicTestableGetDisplayPixel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicTestableGetDisplayPixel", (RTS_UINTPTR)SysGraphicTestableGetDisplayPixel, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSGRAPHICTESTABLECREATE ISysGraphicTestableCreate;
 	PFSYSGRAPHICTESTABLEDESTROY ISysGraphicTestableDestroy;
 	PFSYSGRAPHICTESTABLEGETDISPLAYSIZE ISysGraphicTestableGetDisplaySize;
 	PFSYSGRAPHICTESTABLEGETDISPLAYPIXEL ISysGraphicTestableGetDisplayPixel;
 } ISysGraphicTestable_C;

#ifdef CPLUSPLUS
class ISysGraphicTestable : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysGraphicTestableCreate(RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysGraphicTestableDestroy(RTS_HANDLE hTestable) =0;
		virtual RTS_RESULT CDECL ISysGraphicTestableGetDisplaySize(RTS_HANDLE hTestable, RTS_Size* pSize) =0;
		virtual RTS_RESULT CDECL ISysGraphicTestableGetDisplayPixel(RTS_HANDLE hTestable, short sX, short sY, unsigned long* pulColorValue) =0;
};
	#ifndef ITF_SysGraphicTestable
		#define ITF_SysGraphicTestable static ISysGraphicTestable *pISysGraphicTestable = NULL;
	#endif
	#define EXTITF_SysGraphicTestable
#else	/*CPLUSPLUS*/
	typedef ISysGraphicTestable_C		ISysGraphicTestable;
	#ifndef ITF_SysGraphicTestable
		#define ITF_SysGraphicTestable
	#endif
	#define EXTITF_SysGraphicTestable
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSGRAPHICTESTABLEITF_H_*/
