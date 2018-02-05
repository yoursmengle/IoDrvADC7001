SET_INTERFACE_NAME(`SysGraphicFBCstAdaption')

#include "CmpItf.h"

/* Hook definitions (0..10000 reserved for core components) */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	int iWindow_size_x;
	int iWindow_size_y;
	int iBits_per_pixel;
	int iBytes_per_pixel;
}SysGraphicGlobalParameters;

/**
 * <description> 
 * 
 * </description>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysGraphicFBCstAdaptionGetGlobalParameters',`(SysGraphicGlobalParameters* pParameters)')

/**
 * <description> 
 * 
 * </description>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysGraphicFBCstAdaptionBufferWasUpdated',`(char* pcFBAddress)')

/**
 * <description> 
 * 
 * </description>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`char*',`CDECL',`SysGraphicFBCstAdaptionGetFBAddress',`(char* pcFBAddress)')

/**
 * <description> 
 * 
 * </description>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysGraphicFBCstAdaptionGetTouchPosition',`(int* iX, int* iY, int* bPressed)')

#ifdef __cplusplus
}
#endif
