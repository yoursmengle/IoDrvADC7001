SET_INTERFACE_NAME(`CmpCAANetBaseServices')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAAAsyncMan.h"
#include "CAAMemBlockMan.h"
#include "CAANetBaseServices.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>nbs_udp_getdatasize_struct</description>
 */
typedef struct nbs_udp_getdatasize_struct_tag
{
CAA_HANDLE hPeer;					/* VAR_INPUT */
      CAA_ERROR *peError;               /* VAR_INPUT */
      CAA_SIZE UDP_GetDataSize;     /* VAR_OUTPUT */
} nbs_udp_getdatasize_struct; 

DEF_API(`void',`CDECL',`nbs_udp_getdatasize',`(nbs_udp_getdatasize_struct *p)',1,0x0,0x0)

DEF_ITF_API(`CAA_ERROR',`CDECL',`NBS_WorkerInit',`(void)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`NBS_WorkerExit',`(void)')
DEF_ITF_API(`CAA_SIZE',`CDECL',`NBS_UDP_GetDataSize',`(CAA_HANDLE hPeer, CAA_ERROR* peError)')

#ifdef __cplusplus
}
#endif
