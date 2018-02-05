/**
 * <interfacename>CmpIoDrvProfinet</interfacename>
 * <description> 
 *	Interface to get access to a ProfiNet IO-driver.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpIoDrvProfinet')

#include "CmpItf.h"

REF_ITF(`CmpIoMgrItf.m4')
REF_ITF(`CmpIoDrvItf.m4')

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnector *pConnector;
	RTS_IEC_UDINT Result;
} iodrvprofinet_nominate_struct;

#ifdef __cplusplus
}
#endif

/**
 * <description>  </description>
 * <result>ERR_OK</result>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvProfinet_Nominate', `(RTS_HANDLE hDevice, IoConfigConnector *pConnector)')

