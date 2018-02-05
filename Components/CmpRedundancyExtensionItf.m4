/**
 * <interfacename>Redundancy Extension</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpRedundancyExtension')

#include "CmpItf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>setredundancylinestatus</description>
 */
typedef struct tagsetredundancylinestatus_struct
{
	RTS_IEC_BOOL bIsConnected;			/* VAR_INPUT */
	RTS_IEC_BOOL SetRedundancyLineStatus;	/* VAR_OUTPUT */
} setredundancylinestatus_struct;

DEF_API(`void',`CDECL',`setredundancylinestatus',`(setredundancylinestatus_struct *p)',1,0)
DEF_ITF_API(`RTS_BOOL',`CDECL',`RedundancySetLineStatus',`(RTS_BOOL)')

DEF_ITF_API(`RTS_BOOL',`CDECL',`RedundancyGetLineStatus',`(void)')

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

