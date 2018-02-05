 /**
 * <interfacename>CmpIoDrvParameter</interfacename>
 * <description> 
 *	Interface to access parameters of an IO-driver.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPIODRVPARAMETERITF_H_
#define _CMPIODRVPARAMETERITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

#include "CmpIoMgrItf.h"
#include "CmpIoDrvItf.h"

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
STATICITF_DEF RTS_RESULT CDECL IoDrvReadParameter(RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
typedef RTS_RESULT (CDECL * PFIODRVREADPARAMETER) (RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
#if defined(CMPIODRVPARAMETER_NOTIMPLEMENTED) || defined(IODRVREADPARAMETER_NOTIMPLEMENTED)
	#define USE_IoDrvReadParameter
	#define EXT_IoDrvReadParameter
	#define GET_IoDrvReadParameter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvReadParameter(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvReadParameter  FALSE
	#define EXP_IoDrvReadParameter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvReadParameter
	#define EXT_IoDrvReadParameter
	#define GET_IoDrvReadParameter(fl)  ERR_OK
	#define CAL_IoDrvReadParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter*)p0)->IIoDrvReadParameter(((ICmpIoDrvParameter*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvReadParameter  TRUE
	#define EXP_IoDrvReadParameter  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVPARAMETER_EXTERNAL)
	#define USE_IoDrvReadParameter
	#define EXT_IoDrvReadParameter
	#define GET_IoDrvReadParameter(fl)  ERR_OK
	#define CAL_IoDrvReadParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter*)p0)->IIoDrvReadParameter(((ICmpIoDrvParameter*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvReadParameter  TRUE
	#define EXP_IoDrvReadParameter  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvParameterIoDrvReadParameter
	#define EXT_CmpIoDrvParameterIoDrvReadParameter
	#define GET_CmpIoDrvParameterIoDrvReadParameter  ERR_OK
	#define CAL_CmpIoDrvParameterIoDrvReadParameter(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter*)p0)->IIoDrvReadParameter(p1,p2,p3,p4,p5))
	#define CHK_CmpIoDrvParameterIoDrvReadParameter  TRUE
	#define EXP_CmpIoDrvParameterIoDrvReadParameter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvReadParameter
	#define EXT_IoDrvReadParameter
	#define GET_IoDrvReadParameter(fl)  ERR_OK
	#define CAL_IoDrvReadParameter(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter*)p0)->IIoDrvReadParameter(p1,p2,p3,p4,p5))
	#define CHK_IoDrvReadParameter  TRUE
	#define EXP_IoDrvReadParameter  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvReadParameter
	#define EXT_IoDrvReadParameter
	#define GET_IoDrvReadParameter(fl)  ERR_OK
	#define CAL_IoDrvReadParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter*)p0)->IIoDrvReadParameter(((ICmpIoDrvParameter*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvReadParameter  TRUE
	#define EXP_IoDrvReadParameter  ERR_OK
#endif




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
STATICITF_DEF RTS_RESULT CDECL IoDrvWriteParameter(RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
typedef RTS_RESULT (CDECL * PFIODRVWRITEPARAMETER) (RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
#if defined(CMPIODRVPARAMETER_NOTIMPLEMENTED) || defined(IODRVWRITEPARAMETER_NOTIMPLEMENTED)
	#define USE_IoDrvWriteParameter
	#define EXT_IoDrvWriteParameter
	#define GET_IoDrvWriteParameter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvWriteParameter(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvWriteParameter  FALSE
	#define EXP_IoDrvWriteParameter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvWriteParameter
	#define EXT_IoDrvWriteParameter
	#define GET_IoDrvWriteParameter(fl)  ERR_OK
	#define CAL_IoDrvWriteParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter*)p0)->IIoDrvWriteParameter(((ICmpIoDrvParameter*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameter  TRUE
	#define EXP_IoDrvWriteParameter  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVPARAMETER_EXTERNAL)
	#define USE_IoDrvWriteParameter
	#define EXT_IoDrvWriteParameter
	#define GET_IoDrvWriteParameter(fl)  ERR_OK
	#define CAL_IoDrvWriteParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter*)p0)->IIoDrvWriteParameter(((ICmpIoDrvParameter*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameter  TRUE
	#define EXP_IoDrvWriteParameter  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvParameterIoDrvWriteParameter
	#define EXT_CmpIoDrvParameterIoDrvWriteParameter
	#define GET_CmpIoDrvParameterIoDrvWriteParameter  ERR_OK
	#define CAL_CmpIoDrvParameterIoDrvWriteParameter(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter*)p0)->IIoDrvWriteParameter(p1,p2,p3,p4,p5))
	#define CHK_CmpIoDrvParameterIoDrvWriteParameter  TRUE
	#define EXP_CmpIoDrvParameterIoDrvWriteParameter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvWriteParameter
	#define EXT_IoDrvWriteParameter
	#define GET_IoDrvWriteParameter(fl)  ERR_OK
	#define CAL_IoDrvWriteParameter(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter*)p0)->IIoDrvWriteParameter(p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameter  TRUE
	#define EXP_IoDrvWriteParameter  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvWriteParameter
	#define EXT_IoDrvWriteParameter
	#define GET_IoDrvWriteParameter(fl)  ERR_OK
	#define CAL_IoDrvWriteParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter*)p0)->IIoDrvWriteParameter(((ICmpIoDrvParameter*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameter  TRUE
	#define EXP_IoDrvWriteParameter  ERR_OK
#endif







typedef struct
{
	IBase_C *pBase;
	PFIODRVREADPARAMETER IIoDrvReadParameter;
 	PFIODRVWRITEPARAMETER IIoDrvWriteParameter;
 } ICmpIoDrvParameter_C;

#ifdef CPLUSPLUS
class ICmpIoDrvParameter : public IBase
{
	public:
		virtual RTS_RESULT CDECL IIoDrvReadParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset) =0;
		virtual RTS_RESULT CDECL IIoDrvWriteParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset) =0;
};
	#ifndef ITF_CmpIoDrvParameter
		#define ITF_CmpIoDrvParameter static ICmpIoDrvParameter *pICmpIoDrvParameter = NULL;
	#endif
	#define EXTITF_CmpIoDrvParameter
#else	/*CPLUSPLUS*/
	typedef ICmpIoDrvParameter_C		ICmpIoDrvParameter;
	#ifndef ITF_CmpIoDrvParameter
		#define ITF_CmpIoDrvParameter
	#endif
	#define EXTITF_CmpIoDrvParameter
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIODRVPARAMETERITF_H_*/
