/**
 * <interfacename>CmpIoDrvParameter2</interfacename>
 * <description> 
 *	Interface to access parameters of an IO-driver by their parameter id
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpIoDrvParameter2')

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
	RTS_IEC_DWORD ulParamId;
	RTS_IEC_BYTE *pData;
	RTS_IEC_DWORD ulBitSize;
	RTS_IEC_DWORD ulBitOffset;
	RTS_IEC_UDINT Result;
} iodrvreadparameterbyid_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnector *pConnector;
	RTS_IEC_DWORD ulParamId;
	RTS_IEC_BYTE *pData;
	RTS_IEC_DWORD ulBitSize;
	RTS_IEC_DWORD ulBitOffset;
	RTS_IEC_UDINT Result;
} iodrvwriteparameterbyid_struct;

#ifdef __cplusplus
}
#endif

/**
 * <description>  </description>
 * <result>ERR_OK</result>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvReadParameterById', `(RTS_HANDLE hDevice, IoConfigConnector *pConnector, RTS_UI32 dwParamId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvWriteParameterById', `(RTS_HANDLE hDevice, IoConfigConnector *pConnector, RTS_UI32 dwParamId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)')


