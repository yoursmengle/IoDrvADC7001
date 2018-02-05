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

SET_INTERFACE_NAME(`SysGraphicNative')

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
DEF_ITF_API(`RTS_HANDLE', `CDECL', `SysGraphicNativeGetDisplayDeviceContext', `(RTS_RESULT *pResult)')

/**
 * <description>Releases a handle to the native display context that was returned by 
 *	<see>SysGraphicNativeGetDisplayDeviceContext</see>.</description>
 * <param name="hDisplayContext" type="IN">The native displaycontext to release</param>
 * <result>An error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysGraphicNativeReleaseDisplayDeviceContext', `(RTS_HANDLE hDisplayContext)')

/**
 * <description>Returns the size of the native display.</description>
 * <param name="pSize" type="OUT">This structure will be filled with the size of the native display.</param>
 * <result>An error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysGraphicNativeGetDisplaySize', `(RTS_Size* pSize)')

/**
 * <description>This method will be called cyclically from the context of the IEC-Visualization-Task. The
 *	call is intended to check for user inputs (keyboard event, mouse event,...) and raise the according events in the
 *	SysWindowNative component using <see>SysWindowNativeRaiseInput</see>. If the method <see>SysWindowNativeRaiseInput</see> is
 *	called directly when the input is received (signal, interrupt,...), then this call can be ignored.</description>
 * <result>An error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysGraphicNativeProcessInputs', `(void)')

/**
 * <description>This method will be called cyclically from the context of the IEC-Visualization-Task.
 * The call is intended to pass the buffer to the video driver. Means display the content.</description>
 * <result>An error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysGraphicNativeBufferWasUpdated', `(void)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysGraphicNativeGetPixel', `(RTS_HANDLE hDC, short sX, short sY, unsigned long* pulColorValue)')

#ifdef __cplusplus
}
#endif
