/**
 * <interfacename>CmpIoDrvParameter</interfacename>
 * <description> 
 *	Interface to access parameters of an IO-driver.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpIoDrvParameter')

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
	IoConfigParameter *pParameter;
	RTS_IEC_BYTE *pData;
	RTS_IEC_DWORD ulBitSize;
	RTS_IEC_DWORD ulBitOffset;
	RTS_IEC_UDINT Result;
} iodrvreadparameter_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnector *pConnector;
	IoConfigParameter *pParameter;
	RTS_IEC_BYTE *pData;
	RTS_IEC_DWORD ulBitSize;
	RTS_IEC_DWORD ulBitOffset;
	RTS_IEC_UDINT Result;
} iodrvwriteparameter_struct;

#ifdef __cplusplus
}
#endif

/**
 * <description>
 * <p>Read a driver specific parameters.</p>
 * <p>These parameters can be read by the application, as
 * well as, by an online service, which is triggered from
 * the device configurator plugin in the CoDeSys programming
 * system.</p>
 * <p>Note: If the I/O driver returns an error, the I/O
 * Manager may try to read the parameter himself</p>
 * <p>Note2: On SIL2 runtimes, this interface is not supported.</p>
 * </description>
 * <param name="hDevice" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER]">Handle to the IO-driver instance</param>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR]">Pointer to the connector (might be determined with IoMgrConfigGetConnector).</param>
 * <param name="pParameter" type="IN" range="[NULL,VALID_PARAMETER]">Pointer to the parameter (might be determined with IoMgrConfigGetParameter)</param>
 * <param name="pData" type="IN" range="[NULL,VALID_DATABUFFER]">Buffer where the read data is stored</param>
 * <param name="ulBitSize" type="IN" range="[0..PARAM_SIZE-1]">Size of the part of the parameter data, that should be read</param>
 * <param name="ulBitOffset" type="IN" range="[0..PARAM_SIZE-1]">Offset of the part of the parameter, that should be read</param>
 * <parampseudo name="OperationMode" type="IN" range="[RTS_SIL2_OPMODE_SAFE,RTS_SIL2_OPMODE_DEBUG]">Operation mode</parampseudo>
 * <parampseudo name="bExceptionGenerated" type="OUT" range="[TRUE,FALSE]">Indicates, if an exception was thrown or not</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Parameter was retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hDevice was invalid, or pConnector, pConfigParameter or pData was NULL.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Parameter is not handled by the driver</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">This feature is not supported by the driver, or the I/O Manager</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvReadParameter', `(RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)')

/**
 * <description>
 * <p>Write a driver specific parameters.</p>
 * <p>These parameters can be written by the application, as
 * well as, by an online service, which is triggered from
 * the device configurator plugin in the CoDeSys programming
 * system.</p>
 * <p>Note: On SIL2 runtimes, this interface is not supported. And if called in safe-mode,
 * on SIL2 Runtimes, an exception is generated.</p>
 * </description>
 * <param name="hDevice" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER]">Handle to the IO-driver instance</param>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR]">Pointer to the connector (might be determined with IoMgrConfigGetConnector).</param>
 * <param name="pParameter" type="IN" range="[NULL,VALID_PARAMETER]">Pointer to the parameter (might be determined with IoMgrConfigGetParameter)</param>
 * <param name="pData" type="IN" range="[NULL,VALID_DATABUFFER]">Buffer where the read data is stored</param>
 * <param name="ulBitSize" type="IN" range="[0..PARAM_SIZE-1]">Size of the part of the parameter data, that should be written</param>
 * <param name="ulBitOffset" type="IN" range="[0..PARAM_SIZE-1]">Offset of the part of the parameter, that should be written</param>
 * <parampseudo name="OperationMode" type="IN" range="[RTS_SIL2_OPMODE_SAFE,RTS_SIL2_OPMODE_DEBUG]">Operation mode</parampseudo>
 * <parampseudo name="bExceptionGenerated" type="OUT" range="[TRUE,FALSE]">Indicates, if an exception was thrown or not</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Parameter was retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hDevice was invalid, or pConnector, pConfigParameter or pData was NULL.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Parameter is not handled by the driver</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">This feature is not supported by the driver, or the I/O Manager</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvWriteParameter', `(RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)')

