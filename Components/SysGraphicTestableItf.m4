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

SET_INTERFACE_NAME(`SysGraphicTestable')

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
DEF_ITF_API(`RTS_HANDLE', `CDECL', `SysGraphicTestableCreate', `(RTS_RESULT *pResult)')

/**
 * <description>Releases a handle to a test object that was returned by <see>SysGraphicTestableCreate</see>.</description>
 * <param name="hDisplayContext" type="IN">The native displaycontext to release</param>
 * <result>An error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysGraphicTestableDestroy', `(RTS_HANDLE hTestable)')

/**
 * <description>Returns the size of the display.</description>
 * <param name="pSize" type="OUT">This structure will be filled with the size of the native display.</param>
 * <result>An error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysGraphicTestableGetDisplaySize', `(RTS_HANDLE hTestable, RTS_Size* pSize)')

/**
 * <description>This method can be called for retrieving the color of a displayed pixel.</description>
 * <param name="hDC" type="IN">The testable object</param>
 * <param name="sX" type="IN">The x coordinate to get the color from</param>
 * <param name="sY" type="IN">The y coordinate to get the color from</param>
 * <param name="pulColorValue" type="IN">Pointer that will return the determined color. The color will be in the
 * format used by the iec visualization ([--------|RRRRRRRR|GGGGGGGG|BBBBBBBB]).</param>
 * <result>An error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysGraphicTestableGetDisplayPixel', `(RTS_HANDLE hTestable, short sX, short sY, unsigned long* pulColorValue)')

#ifdef __cplusplus
}
#endif
