 /**
 * <interfacename>SysGraphicNative</interfacename>
 * <description> 
 *	<p>The SysGraphicNative interface is projected to provide access to the graphic library routines
 *	implemented based on a native implementation. Such a native implementation could be a direct framebuffer access of the usage 
 *	of a proprietary graphics chip/card. This is the system interface typically for the CoDeSys target visualization.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSGRAPHICNATIVEITF_H_
#define _SYSGRAPHICNATIVEITF_H_

#include "CmpStd.h"

 

 




#ifndef CDECL
	#define CDECL
#endif

#include "SysGraphicBase.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Provides a handle to the native display context. If you do not use this handle any more, release it using
 *	<see>SysGraphicNativeReleaseDisplayDeviceContext</see></description>
 * <param name="pResult" type="OUT">Optionally returns an error code</param>
 * <result>The handle to the native display context or <see>RTS_INVALID_HANDLE</see> in case of errors.</result>
 */
RTS_HANDLE CDECL SysGraphicNativeGetDisplayDeviceContext(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSGRAPHICNATIVEGETDISPLAYDEVICECONTEXT) (RTS_RESULT *pResult);
#if defined(SYSGRAPHICNATIVE_NOTIMPLEMENTED) || defined(SYSGRAPHICNATIVEGETDISPLAYDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicNativeGetDisplayDeviceContext
	#define EXT_SysGraphicNativeGetDisplayDeviceContext
	#define GET_SysGraphicNativeGetDisplayDeviceContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicNativeGetDisplayDeviceContext(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysGraphicNativeGetDisplayDeviceContext  FALSE
	#define EXP_SysGraphicNativeGetDisplayDeviceContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicNativeGetDisplayDeviceContext
	#define EXT_SysGraphicNativeGetDisplayDeviceContext
	#define GET_SysGraphicNativeGetDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicNativeGetDisplayDeviceContext" ) 
	#define CAL_SysGraphicNativeGetDisplayDeviceContext  SysGraphicNativeGetDisplayDeviceContext
	#define CHK_SysGraphicNativeGetDisplayDeviceContext  TRUE
	#define EXP_SysGraphicNativeGetDisplayDeviceContext  CAL_CMEXPAPI( "SysGraphicNativeGetDisplayDeviceContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICNATIVE_EXTERNAL)
	#define USE_SysGraphicNativeGetDisplayDeviceContext
	#define EXT_SysGraphicNativeGetDisplayDeviceContext
	#define GET_SysGraphicNativeGetDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicNativeGetDisplayDeviceContext" ) 
	#define CAL_SysGraphicNativeGetDisplayDeviceContext  SysGraphicNativeGetDisplayDeviceContext
	#define CHK_SysGraphicNativeGetDisplayDeviceContext  TRUE
	#define EXP_SysGraphicNativeGetDisplayDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeGetDisplayDeviceContext", (RTS_UINTPTR)SysGraphicNativeGetDisplayDeviceContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicNativeSysGraphicNativeGetDisplayDeviceContext
	#define EXT_SysGraphicNativeSysGraphicNativeGetDisplayDeviceContext
	#define GET_SysGraphicNativeSysGraphicNativeGetDisplayDeviceContext  ERR_OK
	#define CAL_SysGraphicNativeSysGraphicNativeGetDisplayDeviceContext pISysGraphicNative->ISysGraphicNativeGetDisplayDeviceContext
	#define CHK_SysGraphicNativeSysGraphicNativeGetDisplayDeviceContext (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeSysGraphicNativeGetDisplayDeviceContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicNativeGetDisplayDeviceContext
	#define EXT_SysGraphicNativeGetDisplayDeviceContext
	#define GET_SysGraphicNativeGetDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicNativeGetDisplayDeviceContext" ) 
	#define CAL_SysGraphicNativeGetDisplayDeviceContext pISysGraphicNative->ISysGraphicNativeGetDisplayDeviceContext
	#define CHK_SysGraphicNativeGetDisplayDeviceContext (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeGetDisplayDeviceContext  CAL_CMEXPAPI( "SysGraphicNativeGetDisplayDeviceContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicNativeGetDisplayDeviceContext  PFSYSGRAPHICNATIVEGETDISPLAYDEVICECONTEXT pfSysGraphicNativeGetDisplayDeviceContext;
	#define EXT_SysGraphicNativeGetDisplayDeviceContext  extern PFSYSGRAPHICNATIVEGETDISPLAYDEVICECONTEXT pfSysGraphicNativeGetDisplayDeviceContext;
	#define GET_SysGraphicNativeGetDisplayDeviceContext(fl)  s_pfCMGetAPI2( "SysGraphicNativeGetDisplayDeviceContext", (RTS_VOID_FCTPTR *)&pfSysGraphicNativeGetDisplayDeviceContext, (fl), 0, 0)
	#define CAL_SysGraphicNativeGetDisplayDeviceContext  pfSysGraphicNativeGetDisplayDeviceContext
	#define CHK_SysGraphicNativeGetDisplayDeviceContext  (pfSysGraphicNativeGetDisplayDeviceContext != NULL)
	#define EXP_SysGraphicNativeGetDisplayDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeGetDisplayDeviceContext", (RTS_UINTPTR)SysGraphicNativeGetDisplayDeviceContext, 0, 0) 
#endif




/**
 * <description>Releases a handle to the native display context that was returned by 
 *	<see>SysGraphicNativeGetDisplayDeviceContext</see>.</description>
 * <param name="hDisplayContext" type="IN">The native displaycontext to release</param>
 * <result>An error code</result>
 */
RTS_RESULT CDECL SysGraphicNativeReleaseDisplayDeviceContext(RTS_HANDLE hDisplayContext);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICNATIVERELEASEDISPLAYDEVICECONTEXT) (RTS_HANDLE hDisplayContext);
#if defined(SYSGRAPHICNATIVE_NOTIMPLEMENTED) || defined(SYSGRAPHICNATIVERELEASEDISPLAYDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_SysGraphicNativeReleaseDisplayDeviceContext
	#define EXT_SysGraphicNativeReleaseDisplayDeviceContext
	#define GET_SysGraphicNativeReleaseDisplayDeviceContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicNativeReleaseDisplayDeviceContext(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicNativeReleaseDisplayDeviceContext  FALSE
	#define EXP_SysGraphicNativeReleaseDisplayDeviceContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicNativeReleaseDisplayDeviceContext
	#define EXT_SysGraphicNativeReleaseDisplayDeviceContext
	#define GET_SysGraphicNativeReleaseDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicNativeReleaseDisplayDeviceContext" ) 
	#define CAL_SysGraphicNativeReleaseDisplayDeviceContext  SysGraphicNativeReleaseDisplayDeviceContext
	#define CHK_SysGraphicNativeReleaseDisplayDeviceContext  TRUE
	#define EXP_SysGraphicNativeReleaseDisplayDeviceContext  CAL_CMEXPAPI( "SysGraphicNativeReleaseDisplayDeviceContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICNATIVE_EXTERNAL)
	#define USE_SysGraphicNativeReleaseDisplayDeviceContext
	#define EXT_SysGraphicNativeReleaseDisplayDeviceContext
	#define GET_SysGraphicNativeReleaseDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicNativeReleaseDisplayDeviceContext" ) 
	#define CAL_SysGraphicNativeReleaseDisplayDeviceContext  SysGraphicNativeReleaseDisplayDeviceContext
	#define CHK_SysGraphicNativeReleaseDisplayDeviceContext  TRUE
	#define EXP_SysGraphicNativeReleaseDisplayDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeReleaseDisplayDeviceContext", (RTS_UINTPTR)SysGraphicNativeReleaseDisplayDeviceContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicNativeSysGraphicNativeReleaseDisplayDeviceContext
	#define EXT_SysGraphicNativeSysGraphicNativeReleaseDisplayDeviceContext
	#define GET_SysGraphicNativeSysGraphicNativeReleaseDisplayDeviceContext  ERR_OK
	#define CAL_SysGraphicNativeSysGraphicNativeReleaseDisplayDeviceContext pISysGraphicNative->ISysGraphicNativeReleaseDisplayDeviceContext
	#define CHK_SysGraphicNativeSysGraphicNativeReleaseDisplayDeviceContext (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeSysGraphicNativeReleaseDisplayDeviceContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicNativeReleaseDisplayDeviceContext
	#define EXT_SysGraphicNativeReleaseDisplayDeviceContext
	#define GET_SysGraphicNativeReleaseDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysGraphicNativeReleaseDisplayDeviceContext" ) 
	#define CAL_SysGraphicNativeReleaseDisplayDeviceContext pISysGraphicNative->ISysGraphicNativeReleaseDisplayDeviceContext
	#define CHK_SysGraphicNativeReleaseDisplayDeviceContext (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeReleaseDisplayDeviceContext  CAL_CMEXPAPI( "SysGraphicNativeReleaseDisplayDeviceContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicNativeReleaseDisplayDeviceContext  PFSYSGRAPHICNATIVERELEASEDISPLAYDEVICECONTEXT pfSysGraphicNativeReleaseDisplayDeviceContext;
	#define EXT_SysGraphicNativeReleaseDisplayDeviceContext  extern PFSYSGRAPHICNATIVERELEASEDISPLAYDEVICECONTEXT pfSysGraphicNativeReleaseDisplayDeviceContext;
	#define GET_SysGraphicNativeReleaseDisplayDeviceContext(fl)  s_pfCMGetAPI2( "SysGraphicNativeReleaseDisplayDeviceContext", (RTS_VOID_FCTPTR *)&pfSysGraphicNativeReleaseDisplayDeviceContext, (fl), 0, 0)
	#define CAL_SysGraphicNativeReleaseDisplayDeviceContext  pfSysGraphicNativeReleaseDisplayDeviceContext
	#define CHK_SysGraphicNativeReleaseDisplayDeviceContext  (pfSysGraphicNativeReleaseDisplayDeviceContext != NULL)
	#define EXP_SysGraphicNativeReleaseDisplayDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeReleaseDisplayDeviceContext", (RTS_UINTPTR)SysGraphicNativeReleaseDisplayDeviceContext, 0, 0) 
#endif




/**
 * <description>Returns the size of the native display.</description>
 * <param name="pSize" type="OUT">This structure will be filled with the size of the native display.</param>
 * <result>An error code</result>
 */
RTS_RESULT CDECL SysGraphicNativeGetDisplaySize(RTS_Size* pSize);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICNATIVEGETDISPLAYSIZE) (RTS_Size* pSize);
#if defined(SYSGRAPHICNATIVE_NOTIMPLEMENTED) || defined(SYSGRAPHICNATIVEGETDISPLAYSIZE_NOTIMPLEMENTED)
	#define USE_SysGraphicNativeGetDisplaySize
	#define EXT_SysGraphicNativeGetDisplaySize
	#define GET_SysGraphicNativeGetDisplaySize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicNativeGetDisplaySize(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicNativeGetDisplaySize  FALSE
	#define EXP_SysGraphicNativeGetDisplaySize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicNativeGetDisplaySize
	#define EXT_SysGraphicNativeGetDisplaySize
	#define GET_SysGraphicNativeGetDisplaySize(fl)  CAL_CMGETAPI( "SysGraphicNativeGetDisplaySize" ) 
	#define CAL_SysGraphicNativeGetDisplaySize  SysGraphicNativeGetDisplaySize
	#define CHK_SysGraphicNativeGetDisplaySize  TRUE
	#define EXP_SysGraphicNativeGetDisplaySize  CAL_CMEXPAPI( "SysGraphicNativeGetDisplaySize" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICNATIVE_EXTERNAL)
	#define USE_SysGraphicNativeGetDisplaySize
	#define EXT_SysGraphicNativeGetDisplaySize
	#define GET_SysGraphicNativeGetDisplaySize(fl)  CAL_CMGETAPI( "SysGraphicNativeGetDisplaySize" ) 
	#define CAL_SysGraphicNativeGetDisplaySize  SysGraphicNativeGetDisplaySize
	#define CHK_SysGraphicNativeGetDisplaySize  TRUE
	#define EXP_SysGraphicNativeGetDisplaySize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeGetDisplaySize", (RTS_UINTPTR)SysGraphicNativeGetDisplaySize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicNativeSysGraphicNativeGetDisplaySize
	#define EXT_SysGraphicNativeSysGraphicNativeGetDisplaySize
	#define GET_SysGraphicNativeSysGraphicNativeGetDisplaySize  ERR_OK
	#define CAL_SysGraphicNativeSysGraphicNativeGetDisplaySize pISysGraphicNative->ISysGraphicNativeGetDisplaySize
	#define CHK_SysGraphicNativeSysGraphicNativeGetDisplaySize (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeSysGraphicNativeGetDisplaySize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicNativeGetDisplaySize
	#define EXT_SysGraphicNativeGetDisplaySize
	#define GET_SysGraphicNativeGetDisplaySize(fl)  CAL_CMGETAPI( "SysGraphicNativeGetDisplaySize" ) 
	#define CAL_SysGraphicNativeGetDisplaySize pISysGraphicNative->ISysGraphicNativeGetDisplaySize
	#define CHK_SysGraphicNativeGetDisplaySize (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeGetDisplaySize  CAL_CMEXPAPI( "SysGraphicNativeGetDisplaySize" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicNativeGetDisplaySize  PFSYSGRAPHICNATIVEGETDISPLAYSIZE pfSysGraphicNativeGetDisplaySize;
	#define EXT_SysGraphicNativeGetDisplaySize  extern PFSYSGRAPHICNATIVEGETDISPLAYSIZE pfSysGraphicNativeGetDisplaySize;
	#define GET_SysGraphicNativeGetDisplaySize(fl)  s_pfCMGetAPI2( "SysGraphicNativeGetDisplaySize", (RTS_VOID_FCTPTR *)&pfSysGraphicNativeGetDisplaySize, (fl), 0, 0)
	#define CAL_SysGraphicNativeGetDisplaySize  pfSysGraphicNativeGetDisplaySize
	#define CHK_SysGraphicNativeGetDisplaySize  (pfSysGraphicNativeGetDisplaySize != NULL)
	#define EXP_SysGraphicNativeGetDisplaySize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeGetDisplaySize", (RTS_UINTPTR)SysGraphicNativeGetDisplaySize, 0, 0) 
#endif




/**
 * <description>This method will be called cyclically from the context of the IEC-Visualization-Task. The
 *	call is intended to check for user inputs (keyboard event, mouse event,...) and raise the according events in the
 *	SysWindowNative component using <see>SysWindowNativeRaiseInput</see>. If the method <see>SysWindowNativeRaiseInput</see> is
 *	called directly when the input is received (signal, interrupt,...), then this call can be ignored.</description>
 * <result>An error code</result>
 */
RTS_RESULT CDECL SysGraphicNativeProcessInputs(void);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICNATIVEPROCESSINPUTS) (void);
#if defined(SYSGRAPHICNATIVE_NOTIMPLEMENTED) || defined(SYSGRAPHICNATIVEPROCESSINPUTS_NOTIMPLEMENTED)
	#define USE_SysGraphicNativeProcessInputs
	#define EXT_SysGraphicNativeProcessInputs
	#define GET_SysGraphicNativeProcessInputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicNativeProcessInputs()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicNativeProcessInputs  FALSE
	#define EXP_SysGraphicNativeProcessInputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicNativeProcessInputs
	#define EXT_SysGraphicNativeProcessInputs
	#define GET_SysGraphicNativeProcessInputs(fl)  CAL_CMGETAPI( "SysGraphicNativeProcessInputs" ) 
	#define CAL_SysGraphicNativeProcessInputs  SysGraphicNativeProcessInputs
	#define CHK_SysGraphicNativeProcessInputs  TRUE
	#define EXP_SysGraphicNativeProcessInputs  CAL_CMEXPAPI( "SysGraphicNativeProcessInputs" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICNATIVE_EXTERNAL)
	#define USE_SysGraphicNativeProcessInputs
	#define EXT_SysGraphicNativeProcessInputs
	#define GET_SysGraphicNativeProcessInputs(fl)  CAL_CMGETAPI( "SysGraphicNativeProcessInputs" ) 
	#define CAL_SysGraphicNativeProcessInputs  SysGraphicNativeProcessInputs
	#define CHK_SysGraphicNativeProcessInputs  TRUE
	#define EXP_SysGraphicNativeProcessInputs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeProcessInputs", (RTS_UINTPTR)SysGraphicNativeProcessInputs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicNativeSysGraphicNativeProcessInputs
	#define EXT_SysGraphicNativeSysGraphicNativeProcessInputs
	#define GET_SysGraphicNativeSysGraphicNativeProcessInputs  ERR_OK
	#define CAL_SysGraphicNativeSysGraphicNativeProcessInputs pISysGraphicNative->ISysGraphicNativeProcessInputs
	#define CHK_SysGraphicNativeSysGraphicNativeProcessInputs (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeSysGraphicNativeProcessInputs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicNativeProcessInputs
	#define EXT_SysGraphicNativeProcessInputs
	#define GET_SysGraphicNativeProcessInputs(fl)  CAL_CMGETAPI( "SysGraphicNativeProcessInputs" ) 
	#define CAL_SysGraphicNativeProcessInputs pISysGraphicNative->ISysGraphicNativeProcessInputs
	#define CHK_SysGraphicNativeProcessInputs (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeProcessInputs  CAL_CMEXPAPI( "SysGraphicNativeProcessInputs" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicNativeProcessInputs  PFSYSGRAPHICNATIVEPROCESSINPUTS pfSysGraphicNativeProcessInputs;
	#define EXT_SysGraphicNativeProcessInputs  extern PFSYSGRAPHICNATIVEPROCESSINPUTS pfSysGraphicNativeProcessInputs;
	#define GET_SysGraphicNativeProcessInputs(fl)  s_pfCMGetAPI2( "SysGraphicNativeProcessInputs", (RTS_VOID_FCTPTR *)&pfSysGraphicNativeProcessInputs, (fl), 0, 0)
	#define CAL_SysGraphicNativeProcessInputs  pfSysGraphicNativeProcessInputs
	#define CHK_SysGraphicNativeProcessInputs  (pfSysGraphicNativeProcessInputs != NULL)
	#define EXP_SysGraphicNativeProcessInputs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeProcessInputs", (RTS_UINTPTR)SysGraphicNativeProcessInputs, 0, 0) 
#endif




/**
 * <description>This method will be called cyclically from the context of the IEC-Visualization-Task.
 * The call is intended to pass the buffer to the video driver. Means display the content.</description>
 * <result>An error code</result>
 */
RTS_RESULT CDECL SysGraphicNativeBufferWasUpdated(void);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICNATIVEBUFFERWASUPDATED) (void);
#if defined(SYSGRAPHICNATIVE_NOTIMPLEMENTED) || defined(SYSGRAPHICNATIVEBUFFERWASUPDATED_NOTIMPLEMENTED)
	#define USE_SysGraphicNativeBufferWasUpdated
	#define EXT_SysGraphicNativeBufferWasUpdated
	#define GET_SysGraphicNativeBufferWasUpdated(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicNativeBufferWasUpdated()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicNativeBufferWasUpdated  FALSE
	#define EXP_SysGraphicNativeBufferWasUpdated  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicNativeBufferWasUpdated
	#define EXT_SysGraphicNativeBufferWasUpdated
	#define GET_SysGraphicNativeBufferWasUpdated(fl)  CAL_CMGETAPI( "SysGraphicNativeBufferWasUpdated" ) 
	#define CAL_SysGraphicNativeBufferWasUpdated  SysGraphicNativeBufferWasUpdated
	#define CHK_SysGraphicNativeBufferWasUpdated  TRUE
	#define EXP_SysGraphicNativeBufferWasUpdated  CAL_CMEXPAPI( "SysGraphicNativeBufferWasUpdated" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICNATIVE_EXTERNAL)
	#define USE_SysGraphicNativeBufferWasUpdated
	#define EXT_SysGraphicNativeBufferWasUpdated
	#define GET_SysGraphicNativeBufferWasUpdated(fl)  CAL_CMGETAPI( "SysGraphicNativeBufferWasUpdated" ) 
	#define CAL_SysGraphicNativeBufferWasUpdated  SysGraphicNativeBufferWasUpdated
	#define CHK_SysGraphicNativeBufferWasUpdated  TRUE
	#define EXP_SysGraphicNativeBufferWasUpdated  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeBufferWasUpdated", (RTS_UINTPTR)SysGraphicNativeBufferWasUpdated, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicNativeSysGraphicNativeBufferWasUpdated
	#define EXT_SysGraphicNativeSysGraphicNativeBufferWasUpdated
	#define GET_SysGraphicNativeSysGraphicNativeBufferWasUpdated  ERR_OK
	#define CAL_SysGraphicNativeSysGraphicNativeBufferWasUpdated pISysGraphicNative->ISysGraphicNativeBufferWasUpdated
	#define CHK_SysGraphicNativeSysGraphicNativeBufferWasUpdated (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeSysGraphicNativeBufferWasUpdated  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicNativeBufferWasUpdated
	#define EXT_SysGraphicNativeBufferWasUpdated
	#define GET_SysGraphicNativeBufferWasUpdated(fl)  CAL_CMGETAPI( "SysGraphicNativeBufferWasUpdated" ) 
	#define CAL_SysGraphicNativeBufferWasUpdated pISysGraphicNative->ISysGraphicNativeBufferWasUpdated
	#define CHK_SysGraphicNativeBufferWasUpdated (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeBufferWasUpdated  CAL_CMEXPAPI( "SysGraphicNativeBufferWasUpdated" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicNativeBufferWasUpdated  PFSYSGRAPHICNATIVEBUFFERWASUPDATED pfSysGraphicNativeBufferWasUpdated;
	#define EXT_SysGraphicNativeBufferWasUpdated  extern PFSYSGRAPHICNATIVEBUFFERWASUPDATED pfSysGraphicNativeBufferWasUpdated;
	#define GET_SysGraphicNativeBufferWasUpdated(fl)  s_pfCMGetAPI2( "SysGraphicNativeBufferWasUpdated", (RTS_VOID_FCTPTR *)&pfSysGraphicNativeBufferWasUpdated, (fl), 0, 0)
	#define CAL_SysGraphicNativeBufferWasUpdated  pfSysGraphicNativeBufferWasUpdated
	#define CHK_SysGraphicNativeBufferWasUpdated  (pfSysGraphicNativeBufferWasUpdated != NULL)
	#define EXP_SysGraphicNativeBufferWasUpdated  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeBufferWasUpdated", (RTS_UINTPTR)SysGraphicNativeBufferWasUpdated, 0, 0) 
#endif




/**
 * <description>This method can be called for retrieving the color of a pixel in the given device context.
 *	An implementation of this method is optional, as it is used only for automatic testing of the visualization.</description>
 * <param name="hDC" type="IN">The displaycontext to get a color from</param>
 * <param name="sX" type="IN">The x coordinate to get the color from</param>
 * <param name="sY" type="IN">The y coordinate to get the color from</param>
 * <param name="pulColorValue" type="IN">Pointer that will return the determined color. The color will be in the
 * format used by the iec visualization ([--------|RRRRRRRR|GGGGGGGG|BBBBBBBB]).</param>
 * <result>An error code</result>
 */
RTS_RESULT CDECL SysGraphicNativeGetPixel(RTS_HANDLE hDC, short sX, short sY, unsigned long* pulColorValue);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICNATIVEGETPIXEL) (RTS_HANDLE hDC, short sX, short sY, unsigned long* pulColorValue);
#if defined(SYSGRAPHICNATIVE_NOTIMPLEMENTED) || defined(SYSGRAPHICNATIVEGETPIXEL_NOTIMPLEMENTED)
	#define USE_SysGraphicNativeGetPixel
	#define EXT_SysGraphicNativeGetPixel
	#define GET_SysGraphicNativeGetPixel(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicNativeGetPixel(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicNativeGetPixel  FALSE
	#define EXP_SysGraphicNativeGetPixel  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicNativeGetPixel
	#define EXT_SysGraphicNativeGetPixel
	#define GET_SysGraphicNativeGetPixel(fl)  CAL_CMGETAPI( "SysGraphicNativeGetPixel" ) 
	#define CAL_SysGraphicNativeGetPixel  SysGraphicNativeGetPixel
	#define CHK_SysGraphicNativeGetPixel  TRUE
	#define EXP_SysGraphicNativeGetPixel  CAL_CMEXPAPI( "SysGraphicNativeGetPixel" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICNATIVE_EXTERNAL)
	#define USE_SysGraphicNativeGetPixel
	#define EXT_SysGraphicNativeGetPixel
	#define GET_SysGraphicNativeGetPixel(fl)  CAL_CMGETAPI( "SysGraphicNativeGetPixel" ) 
	#define CAL_SysGraphicNativeGetPixel  SysGraphicNativeGetPixel
	#define CHK_SysGraphicNativeGetPixel  TRUE
	#define EXP_SysGraphicNativeGetPixel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeGetPixel", (RTS_UINTPTR)SysGraphicNativeGetPixel, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicNativeSysGraphicNativeGetPixel
	#define EXT_SysGraphicNativeSysGraphicNativeGetPixel
	#define GET_SysGraphicNativeSysGraphicNativeGetPixel  ERR_OK
	#define CAL_SysGraphicNativeSysGraphicNativeGetPixel pISysGraphicNative->ISysGraphicNativeGetPixel
	#define CHK_SysGraphicNativeSysGraphicNativeGetPixel (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeSysGraphicNativeGetPixel  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicNativeGetPixel
	#define EXT_SysGraphicNativeGetPixel
	#define GET_SysGraphicNativeGetPixel(fl)  CAL_CMGETAPI( "SysGraphicNativeGetPixel" ) 
	#define CAL_SysGraphicNativeGetPixel pISysGraphicNative->ISysGraphicNativeGetPixel
	#define CHK_SysGraphicNativeGetPixel (pISysGraphicNative != NULL)
	#define EXP_SysGraphicNativeGetPixel  CAL_CMEXPAPI( "SysGraphicNativeGetPixel" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicNativeGetPixel  PFSYSGRAPHICNATIVEGETPIXEL pfSysGraphicNativeGetPixel;
	#define EXT_SysGraphicNativeGetPixel  extern PFSYSGRAPHICNATIVEGETPIXEL pfSysGraphicNativeGetPixel;
	#define GET_SysGraphicNativeGetPixel(fl)  s_pfCMGetAPI2( "SysGraphicNativeGetPixel", (RTS_VOID_FCTPTR *)&pfSysGraphicNativeGetPixel, (fl), 0, 0)
	#define CAL_SysGraphicNativeGetPixel  pfSysGraphicNativeGetPixel
	#define CHK_SysGraphicNativeGetPixel  (pfSysGraphicNativeGetPixel != NULL)
	#define EXP_SysGraphicNativeGetPixel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicNativeGetPixel", (RTS_UINTPTR)SysGraphicNativeGetPixel, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSGRAPHICNATIVEGETDISPLAYDEVICECONTEXT ISysGraphicNativeGetDisplayDeviceContext;
 	PFSYSGRAPHICNATIVERELEASEDISPLAYDEVICECONTEXT ISysGraphicNativeReleaseDisplayDeviceContext;
 	PFSYSGRAPHICNATIVEGETDISPLAYSIZE ISysGraphicNativeGetDisplaySize;
 	PFSYSGRAPHICNATIVEPROCESSINPUTS ISysGraphicNativeProcessInputs;
 	PFSYSGRAPHICNATIVEBUFFERWASUPDATED ISysGraphicNativeBufferWasUpdated;
 	PFSYSGRAPHICNATIVEGETPIXEL ISysGraphicNativeGetPixel;
 } ISysGraphicNative_C;

#ifdef CPLUSPLUS
class ISysGraphicNative : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysGraphicNativeGetDisplayDeviceContext(RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysGraphicNativeReleaseDisplayDeviceContext(RTS_HANDLE hDisplayContext) =0;
		virtual RTS_RESULT CDECL ISysGraphicNativeGetDisplaySize(RTS_Size* pSize) =0;
		virtual RTS_RESULT CDECL ISysGraphicNativeProcessInputs(void) =0;
		virtual RTS_RESULT CDECL ISysGraphicNativeBufferWasUpdated(void) =0;
		virtual RTS_RESULT CDECL ISysGraphicNativeGetPixel(RTS_HANDLE hDC, short sX, short sY, unsigned long* pulColorValue) =0;
};
	#ifndef ITF_SysGraphicNative
		#define ITF_SysGraphicNative static ISysGraphicNative *pISysGraphicNative = NULL;
	#endif
	#define EXTITF_SysGraphicNative
#else	/*CPLUSPLUS*/
	typedef ISysGraphicNative_C		ISysGraphicNative;
	#ifndef ITF_SysGraphicNative
		#define ITF_SysGraphicNative
	#endif
	#define EXTITF_SysGraphicNative
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSGRAPHICNATIVEITF_H_*/
