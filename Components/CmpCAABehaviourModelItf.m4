/**
 * <interfacename>CAA_BehaviourModel_Extern</interfacename>
 * <description>
 * </description>
 *
 * <copyright>
 * (c) 2003-2017 3S-Smart Software Solutions
 * </copyright>
 */

SET_INTERFACE_NAME(`CmpCAABehaviourModel')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAABehaviourModel.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Interface functions of CAA BehaviourModel*/
DEF_ITF_API(`void',`CDECL',`CBM_ETrig',`(CBM_ETRIG_CLASS* pInstance)')
DEF_ITF_API(`void',`CDECL',`CBM_ETrig_prvStart',`(void)')
DEF_ITF_API(`void',`CDECL',`CBM_ETrig_prvCyclicAction',`(void)')
DEF_ITF_API(`void',`CDECL',`CBM_ETrig_prvAbort',`(void)')
DEF_ITF_API(`void',`CDECL',`CBM_ETrig_prvResetOutputs',`(CBM_ETRIG_CLASS* pInstance)')

#ifdef __cplusplus
}
#endif

