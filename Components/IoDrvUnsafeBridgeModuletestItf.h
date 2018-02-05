 /**
 * <interfacename>IoDrvUnsafeBridgeModuletest</interfacename>
 * <description> 
 * <p>IO-driver interface implementation for unsafe IO drivers.</p>
 * <p>This interface file is only used to create module tests for
 * the IoDrvUnsafeBridge implementation.</p>
 * <p>The IoDrvUnsafeBridge is used for usafe I/O drivers written
 * in C as well as unsafe I/O drivers written in IEC. </p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _IODRVUNSAFEBRIDGEMODULETESTITF_H_
#define _IODRVUNSAFEBRIDGEMODULETESTITF_H_

#include "CmpStd.h"

 

 




#include "CmpIoMgrItf.h"

/**
 * <description>
 * <p>Create a new I/O driver instance.</p>
 * <p>This function is obsolete, because the instance has to be created
 * by the caller before he registers the I/O driver in the I/O Manager.</p>
 * </description>
 * <param name="hIIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IIODRIVER_HANDLE]">Handle to the IO-driver interface. Must be 0 and is filled automatically by calling the CAL_IoDrvCreate() macro!</param>
 * <param name="ClassId" type="IN" range="[RTS_RANGE_OF_RTS_UI32]">ClassID of the driver. See "Class IDs" section in CmpItf.h or in the Dep.h file of the IO-driver.</param>
 * <param name="iId" type="IN" range="[RTS_I16_MIN,RTS_I16_MIN+1,0,RTS_I16_MAX/2,RTS_I16_MAX]">Instance number of the IO-driver</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Should return RTS_INVALID_HANDLE</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTIMPLEMENTED">Not provided by the driver</errorcode>
 */
STATICITF_DEF RTS_HANDLE CDECL IoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIODRVCREATE) (RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVCREATE_NOTIMPLEMENTED)
	#define USE_IoDrvCreate
	#define EXT_IoDrvCreate
	#define GET_IoDrvCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvCreate(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IoDrvCreate  FALSE
	#define EXP_IoDrvCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvCreate
	#define EXT_IoDrvCreate
	#define GET_IoDrvCreate(fl)  ERR_OK
	#define CAL_IoDrvCreate(p0,p1,p2,p3)	p0 = (IBase *)s_pfCMCreateInstance(p1, NULL);\
											((IBase *)p0)->hInstance = ((IIoDrvUnsafeBridgeModuletest*)((IBase *)p0)->QueryInterface((IBase *)p0, ITFID_IIoDrvUnsafeBridgeModuletest, NULL))->IIoDrvCreate(p0,p1,p2,p3)
	#define CHK_IoDrvCreate  TRUE
	#define EXP_IoDrvCreate  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvCreate
	#define EXT_IoDrvCreate
	#define GET_IoDrvCreate(fl)  ERR_OK
	#define CAL_IoDrvCreate(p0,p1,p2,p3)	p0 = (IBase *)s_pfCMCreateInstance(p1, NULL);\
											((IBase *)p0)->hInstance = ((IIoDrvUnsafeBridgeModuletest*)((IBase *)p0)->QueryInterface((IBase *)p0, ITFID_IIoDrvUnsafeBridgeModuletest, NULL))->IIoDrvCreate(p0,p1,p2,p3)
	#define CHK_IoDrvCreate  TRUE
	#define EXP_IoDrvCreate  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvCreate
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvCreate
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvCreate  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvCreate(p0,p1,p2,p3)	p0 = (IBase *)s_pfCMCreateInstance(p1, NULL);\
											((IIoDrvUnsafeBridgeModuletest*)((IBase *)p0)->QueryInterface((IBase *)p0, ITFID_IIoDrvUnsafeBridgeModuletest, (RTS_RESULT *)1))->IIoDrvCreate(p0,p1,p2,p3)
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvCreate  (s_pfCMCreateInstance != NULL)
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvCreate
	#define EXT_IoDrvCreate
	#define GET_IoDrvCreate(fl)  ERR_OK
	#define CAL_IoDrvCreate(p0,p1,p2,p3)	p0 = (IBase *)s_pfCMCreateInstance(p1, NULL);\
											((IIoDrvUnsafeBridgeModuletest*)((IBase *)p0)->QueryInterface((IBase *)p0, ITFID_IIoDrvUnsafeBridgeModuletest, (RTS_RESULT *)1))->IIoDrvCreate(p0,p1,p2,p3)
	#define CHK_IoDrvCreate  (s_pfCMCreateInstance != NULL)
	#define EXP_IoDrvCreate  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvCreate
	#define EXT_IoDrvCreate
	#define GET_IoDrvCreate(fl)  ERR_OK
	#define CAL_IoDrvCreate(p0,p1,p2,p3)	p0 = (IBase *)s_pfCMCreateInstance(p1, NULL);\
											((IBase *)p0)->hInstance = ((IIoDrvUnsafeBridgeModuletest*)((IBase *)p0)->QueryInterface((IBase *)p0, ITFID_IIoDrvUnsafeBridgeModuletest, NULL))->IIoDrvCreate(p0,p1,p2,p3)
	#define CHK_IoDrvCreate  TRUE
	#define EXP_IoDrvCreate  ERR_OK
#endif




/**
 * <description>
 * <p>Delete an I/O driver instance.</p>
 * <p>This function is obsolete, because the instance has to be deleted
 * by the caller after he unregisters the I/O driver from the I/O Manager.</p>
 * </description>
 * <description>Delete an IO-driver instance</description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param>
 * <param name="hIIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IIODRIVER_HANDLE]">Handle of the ITFID_ICmpIoDrv interface</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTIMPLEMENTED">Not provided by the driver</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvDelete(RTS_HANDLE hIoDrv, RTS_HANDLE hIIoDrv);
typedef RTS_RESULT (CDECL * PFIODRVDELETE) (RTS_HANDLE hIoDrv, RTS_HANDLE hIIoDrv);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVDELETE_NOTIMPLEMENTED)
	#define USE_IoDrvDelete
	#define EXT_IoDrvDelete
	#define GET_IoDrvDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDelete(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDelete  FALSE
	#define EXP_IoDrvDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDelete
	#define EXT_IoDrvDelete
	#define GET_IoDrvDelete(fl)  ERR_OK
	#define CAL_IoDrvDelete(p0,p1) 	(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvDelete(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDelete  TRUE
	#define EXP_IoDrvDelete  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvDelete
	#define EXT_IoDrvDelete
	#define GET_IoDrvDelete(fl)  ERR_OK
	#define CAL_IoDrvDelete(p0,p1) 	(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvDelete(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDelete  TRUE
	#define EXP_IoDrvDelete  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvDelete
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvDelete
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvDelete  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvDelete(p0,p1)	 (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvDelete(p1))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvDelete  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDelete
	#define EXT_IoDrvDelete
	#define GET_IoDrvDelete(fl)  ERR_OK
	#define CAL_IoDrvDelete(p0,p1)	 (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvDelete(p1))
	#define CHK_IoDrvDelete  TRUE
	#define EXP_IoDrvDelete  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDelete
	#define EXT_IoDrvDelete
	#define GET_IoDrvDelete(fl)  ERR_OK
	#define CAL_IoDrvDelete(p0,p1)	 (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvDelete(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDelete  TRUE
	#define EXP_IoDrvDelete  ERR_OK
#endif




/**
 * <description>
 * <p>Get a driver specific info structure.</p>
 * <p>This structure contains IDs and names of the driver.</p>
 * <p>In the IoDrvUnsafeBridge implementation, the info structure
 * of the IoDrvUnsafeBridge is returned.</p>
 * </description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param> 
 * <param name="ppInfo" type="OUT" range="[NULL,VALID_IODRVIERINFO]">Pointer to pointer to the driver info. Pointer must be set by the driver to its internal driver info structure!</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The info structure was returned successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or *ppInfo was NULL</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvGetInfo(RTS_HANDLE hIoDrv, IoDrvInfo **ppInfo);
typedef RTS_RESULT (CDECL * PFIODRVGETINFO) (RTS_HANDLE hIoDrv, IoDrvInfo **ppInfo);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVGETINFO_NOTIMPLEMENTED)
	#define USE_IoDrvGetInfo
	#define EXT_IoDrvGetInfo
	#define GET_IoDrvGetInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvGetInfo(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvGetInfo  FALSE
	#define EXP_IoDrvGetInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvGetInfo
	#define EXT_IoDrvGetInfo
	#define GET_IoDrvGetInfo(fl)  ERR_OK
	#define CAL_IoDrvGetInfo(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvGetInfo(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvGetInfo  TRUE
	#define EXP_IoDrvGetInfo  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvGetInfo
	#define EXT_IoDrvGetInfo
	#define GET_IoDrvGetInfo(fl)  ERR_OK
	#define CAL_IoDrvGetInfo(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvGetInfo(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvGetInfo  TRUE
	#define EXP_IoDrvGetInfo  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvGetInfo
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvGetInfo
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvGetInfo  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvGetInfo(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvGetInfo(p1))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvGetInfo  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvGetInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvGetInfo
	#define EXT_IoDrvGetInfo
	#define GET_IoDrvGetInfo(fl)  ERR_OK
	#define CAL_IoDrvGetInfo(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvGetInfo(p1))
	#define CHK_IoDrvGetInfo  TRUE
	#define EXP_IoDrvGetInfo  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvGetInfo
	#define EXT_IoDrvGetInfo
	#define GET_IoDrvGetInfo(fl)  ERR_OK
	#define CAL_IoDrvGetInfo(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvGetInfo(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvGetInfo  TRUE
	#define EXP_IoDrvGetInfo  ERR_OK
#endif




/**
 * <description>
 * <p>Update Connector Flags in the device tree.</p>
 * <p>The driver should write the current diagnostic information (available, no driver,
 * bus error,...) with the function IoDrvSetModuleDiagnosis() to the I/O connector.</p>
 * <p>This function can be used by other components or from the IEC application to
 * update the diagnostic flags of the connector. To update the status from the 
 * driver, it has to call this function manually.</p>
 * <p>The IoDrvUnsafeBridge implementation calls the corresponding unsafe IO driver, which
 * is responsible for the given connector, with the corresponding copied IO configuration
 * via SIL2OEMExecuteNonSafetyJob function and copies the updated flags to the original
 * configuration afterwards.</p>
 * </description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param> 
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR]">Pointer to the connector, that the diagostic information is requested</param> 
 * <parampseudo name="bConnectorCopied" type="IN" range="[TRUE,FALSE]">Given connector was copied before.</parampseudo>
 * <parampseudo name="bIoDrvStubRegistered" type="IN" range="[TRUE,FALSE]">Is IoDrvStub registered for this connector in the corresponding copied connector.</parampseudo>
 * <parampseudo name="IoDrvReturnValue" type="OUT">Return value, which should be returned by called IoDrvStub</parampseudo>
 * <parampseudo name="bRealIODrvFctFailed" type="IN" range="[TRUE,FALSE]">The IoDrvGetModuleDiagnosis function of the real IO driver returned error.</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The flags have been updated</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or pConnector was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvGetModuleDiagnosis(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector);
typedef RTS_RESULT (CDECL * PFIODRVGETMODULEDIAGNOSIS) (RTS_HANDLE hIoDrv, IoConfigConnector *pConnector);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVGETMODULEDIAGNOSIS_NOTIMPLEMENTED)
	#define USE_IoDrvGetModuleDiagnosis
	#define EXT_IoDrvGetModuleDiagnosis
	#define GET_IoDrvGetModuleDiagnosis(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvGetModuleDiagnosis(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvGetModuleDiagnosis  FALSE
	#define EXP_IoDrvGetModuleDiagnosis  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvGetModuleDiagnosis
	#define EXT_IoDrvGetModuleDiagnosis
	#define GET_IoDrvGetModuleDiagnosis(fl)  ERR_OK
	#define CAL_IoDrvGetModuleDiagnosis(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvGetModuleDiagnosis(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvGetModuleDiagnosis  TRUE
	#define EXP_IoDrvGetModuleDiagnosis  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvGetModuleDiagnosis
	#define EXT_IoDrvGetModuleDiagnosis
	#define GET_IoDrvGetModuleDiagnosis(fl)  ERR_OK
	#define CAL_IoDrvGetModuleDiagnosis(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvGetModuleDiagnosis(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvGetModuleDiagnosis  TRUE
	#define EXP_IoDrvGetModuleDiagnosis  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvGetModuleDiagnosis
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvGetModuleDiagnosis
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvGetModuleDiagnosis  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvGetModuleDiagnosis(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvGetModuleDiagnosis(p1))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvGetModuleDiagnosis  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvGetModuleDiagnosis  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvGetModuleDiagnosis
	#define EXT_IoDrvGetModuleDiagnosis
	#define GET_IoDrvGetModuleDiagnosis(fl)  ERR_OK
	#define CAL_IoDrvGetModuleDiagnosis(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvGetModuleDiagnosis(p1))
	#define CHK_IoDrvGetModuleDiagnosis  TRUE
	#define EXP_IoDrvGetModuleDiagnosis  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvGetModuleDiagnosis
	#define EXT_IoDrvGetModuleDiagnosis
	#define GET_IoDrvGetModuleDiagnosis(fl)  ERR_OK
	#define CAL_IoDrvGetModuleDiagnosis(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvGetModuleDiagnosis(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvGetModuleDiagnosis  TRUE
	#define EXP_IoDrvGetModuleDiagnosis  ERR_OK
#endif




/**
 * <description>
 * <p>Identify plugable I/O card or slave.</p>
 * <p>If the configurator supports scanning of modules, this
 * function can be used our of a communication service to
 * identify a module on the bus or locally on the PLC. This 
 * This might be done by a blinking LED or whatever the hardware
 * supports.</p>
 * <p>This function is not implemented in the IoDrvUnsafeBridge implementation and ERR_NOTIMPLEMENTED is returned.</p>
 *</description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param> 
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR]">Pointer to the connector, that should identify itself physically</param> 
 * <parampseudo name="bConnectorCopied" type="IN" range="[TRUE,FALSE]">Given connector was copied before.</parampseudo>
 * <parampseudo name="bIoDrvStubRegistered" type="IN" range="[TRUE,FALSE]">Is IoDrvStub registered for this connector in the corresponding copied connector.</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Not provided by the driver</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvIdentify(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector);
typedef RTS_RESULT (CDECL * PFIODRVIDENTIFY) (RTS_HANDLE hIoDrv, IoConfigConnector *pConnector);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVIDENTIFY_NOTIMPLEMENTED)
	#define USE_IoDrvIdentify
	#define EXT_IoDrvIdentify
	#define GET_IoDrvIdentify(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvIdentify(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvIdentify  FALSE
	#define EXP_IoDrvIdentify  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvIdentify
	#define EXT_IoDrvIdentify
	#define GET_IoDrvIdentify(fl)  ERR_OK
	#define CAL_IoDrvIdentify(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvIdentify(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvIdentify  TRUE
	#define EXP_IoDrvIdentify  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvIdentify
	#define EXT_IoDrvIdentify
	#define GET_IoDrvIdentify(fl)  ERR_OK
	#define CAL_IoDrvIdentify(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvIdentify(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvIdentify  TRUE
	#define EXP_IoDrvIdentify  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvIdentify
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvIdentify
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvIdentify  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvIdentify(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvIdentify(p1))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvIdentify  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvIdentify  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvIdentify
	#define EXT_IoDrvIdentify
	#define GET_IoDrvIdentify(fl)  ERR_OK
	#define CAL_IoDrvIdentify(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvIdentify(p1))
	#define CHK_IoDrvIdentify  TRUE
	#define EXP_IoDrvIdentify  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvIdentify
	#define EXT_IoDrvIdentify
	#define GET_IoDrvIdentify(fl)  ERR_OK
	#define CAL_IoDrvIdentify(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvIdentify(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvIdentify  TRUE
	#define EXP_IoDrvIdentify  ERR_OK
#endif




/**
 * <description>
 * <p>Read inputs for one task</p>
 * <p>This function is called cyclically from every task
 * that is using inputs. A part of the task map list,
 * which contains only the data of one connector are passed
 * to the driver (called connector map list).</p>
 * <p>If a driver has registered one instance to more
 * than one connector, it might get more than one call with
 * a different subset of the task map list.</p>
 * <p>The I/O driver should read the data from the local
 * hardware or a buffer and write them to the corresponding
 * IEC variables.</p>
 * <p>The IoDrvUnsafeBridgeImplementation passes this call to the corresponding 
 * unsafe io driver with the copied connector list. The inputs are copied to the
 * original configuration afterwards.</p>
 * </description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param> 
 * <param name="pConnectorMapList" type="IN" range="[NULL,VALID_CONNECTORMAPLIST]">Pointer to the connector map list</param> 
 * <param name="nCount" type="IN" range="[0..CONNECTORMAPLIST_LEN-1]">Number of entries in the connector map list</param> 
 * <parampseudo name="bConnectorCopied" type="IN" range="[TRUE,FALSE]">Given connector in connector map list was copied before.</parampseudo>
 * <parampseudo name="bIoDrvStubRegistered" type="IN" range="[TRUE,FALSE]">Is IoDrvStub registered for this connector in the corresponding copied connector.</parampseudo>
 * <parampseudo name="nContinuousConnectorsA" type="IN" range="[1,2]">Number of connectors for stub driver A</parampseudo>
 * <parampseudo name="nContinuousConnectorsB" type="IN" range="[0,2]">Number of connectors for stub driver B</parampseudo>
 * <parampseudo name="bDriverBCalled" type="OUT" range="[TRUE,FALSE]">Driver B called.</parampseudo> 
 * <parampseudo name="IoDrvReturnValue" type="OUT" range="[ERR_OK,ERR_FAILED]">Return value, which should be returned by called IoDrvStub</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">ReadInputs was executed successfully.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or pConnectorMapList was NULL.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal error</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvReadInputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount);
typedef RTS_RESULT (CDECL * PFIODRVREADINPUTS) (RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVREADINPUTS_NOTIMPLEMENTED)
	#define USE_IoDrvReadInputs
	#define EXT_IoDrvReadInputs
	#define GET_IoDrvReadInputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvReadInputs(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvReadInputs  FALSE
	#define EXP_IoDrvReadInputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvReadInputs
	#define EXT_IoDrvReadInputs
	#define GET_IoDrvReadInputs(fl)  ERR_OK
	#define CAL_IoDrvReadInputs(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvReadInputs(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvReadInputs  TRUE
	#define EXP_IoDrvReadInputs  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvReadInputs
	#define EXT_IoDrvReadInputs
	#define GET_IoDrvReadInputs(fl)  ERR_OK
	#define CAL_IoDrvReadInputs(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvReadInputs(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvReadInputs  TRUE
	#define EXP_IoDrvReadInputs  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvReadInputs
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvReadInputs
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvReadInputs  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvReadInputs(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvReadInputs(p1,p2))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvReadInputs  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvReadInputs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvReadInputs
	#define EXT_IoDrvReadInputs
	#define GET_IoDrvReadInputs(fl)  ERR_OK
	#define CAL_IoDrvReadInputs(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvReadInputs(p1,p2))
	#define CHK_IoDrvReadInputs  TRUE
	#define EXP_IoDrvReadInputs  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvReadInputs
	#define EXT_IoDrvReadInputs
	#define GET_IoDrvReadInputs(fl)  ERR_OK
	#define CAL_IoDrvReadInputs(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvReadInputs(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvReadInputs  TRUE
	#define EXP_IoDrvReadInputs  ERR_OK
#endif




/**
 * <description>
 * <p>Scan for submodules of a connector.</p>
 * <p>This function is executed when the driver is downloaded. It
 * is called over a communication service.</p>
 * <p>The I/O driver should search for connected subumodules and
 * return them via ppConnectorList.</p>
 * <p>NOTE: This interface is called synchronously and the buffer for
 * the connector list has to be allocated by the driver.</p>
 * <p>The buffer might be freed at the next scan or at the next
 * UpdateConfiguration.</p>
 * <p>The IoDrvUnsafeBridge only forwards the call to the corresponding unsafe IODriver.</p>
 * </description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param> 
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR]">Pointer to the connector, which layout should be scanned</param> 
 * <param name="ppConnectorList" type="OUT" range="[NULL,VALID_SCAN_CONNECTORLIST]">Pointer to the scanned connectors (devices) to return</param> 
 * <param name="pnCount" type="OUT" range="[0,SIZE_OF_VALID_SCAN_CONNECTORLIST]">Pointer to the number of entries in the connector list to return</param> 
 * <parampseudo name="bConnectorCopied" type="IN" range="[TRUE,FALSE]">Given connector was copied before.</parampseudo>
 * <parampseudo name="bIoDrvStubRegistered" type="IN" range="[TRUE,FALSE]">Is IoDrvStub registered for this connector in the corresponding copied connector.</parampseudo>
 * <parampseudo name="bScanSuccessful" type="IN" range="[TRUE,FALSE]">IoDrvStub return value for the scan.</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Scan was executed successfully.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or one of the other parameters was NULL.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal error</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvScanModules(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount);
typedef RTS_RESULT (CDECL * PFIODRVSCANMODULES) (RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVSCANMODULES_NOTIMPLEMENTED)
	#define USE_IoDrvScanModules
	#define EXT_IoDrvScanModules
	#define GET_IoDrvScanModules(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvScanModules(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvScanModules  FALSE
	#define EXP_IoDrvScanModules  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvScanModules
	#define EXT_IoDrvScanModules
	#define GET_IoDrvScanModules(fl)  ERR_OK
	#define CAL_IoDrvScanModules(p0,p1,p2,p3) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvScanModules(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2,p3))
	#define CHK_IoDrvScanModules  TRUE
	#define EXP_IoDrvScanModules  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvScanModules
	#define EXT_IoDrvScanModules
	#define GET_IoDrvScanModules(fl)  ERR_OK
	#define CAL_IoDrvScanModules(p0,p1,p2,p3) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvScanModules(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2,p3))
	#define CHK_IoDrvScanModules  TRUE
	#define EXP_IoDrvScanModules  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvScanModules
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvScanModules
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvScanModules  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvScanModules(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvScanModules(p1,p2,p3))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvScanModules  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvScanModules  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvScanModules
	#define EXT_IoDrvScanModules
	#define GET_IoDrvScanModules(fl)  ERR_OK
	#define CAL_IoDrvScanModules(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvScanModules(p1,p2,p3))
	#define CHK_IoDrvScanModules  TRUE
	#define EXP_IoDrvScanModules  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvScanModules
	#define EXT_IoDrvScanModules
	#define GET_IoDrvScanModules(fl)  ERR_OK
	#define CAL_IoDrvScanModules(p0,p1,p2,p3) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvScanModules(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2,p3))
	#define CHK_IoDrvScanModules  TRUE
	#define EXP_IoDrvScanModules  ERR_OK
#endif




/**
 * <description>
 * <p>Start bus cycle for a specific connector.</p>
 * <p>The bus cycle task is defined globally for the whole PLC
 * or locally for a specific I/O connector in the CoDeSys project.
 * This call can be used by the I/O driver to flush the I/O data
 * if it was cached before.</p>
 * <p>This way we can get a better and consistent timing on the bus.</p>d
 * <p>Note: This function is called for every connector which has a
 * registered I/O driver and "needsbuscycle" set in the device description
 * (this means that it might also be called for children of the connector).</p>
 * <p>Depending on the device description, this function might be executed
 * at the beginning or at the end of the task cycle.</p>
 * <p>The IoDrvUnsafeBridgeImplementation passes this call to the corresponding 
 * unsafe io driver with the copied connector list.</p>
 * </description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR]">Pointer to the connector, on which the buscycle must be triggered</param> 
 * <parampseudo name="bConnectorCopied" type="IN" range="[TRUE,FALSE]">Given connector was copied before.</parampseudo>
 * <parampseudo name="bIoDrvStubRegistered" type="IN" range="[TRUE,FALSE]">Is IoDrvStub registered for this connector in the corresponding copied connector.</parampseudo>
 * <parampseudo name="IoDrvReturnValue" type="OUT">Return value, which should be returned by called IoDrvStub</parampseudo>
 * <parampseudo name="bRealIODrvFctFailed" type="IN" range="[TRUE,FALSE]">The IoDrvStartBusCycle function of the real IO driver returned error.</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Bus cycle was triggered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or pConnector NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvStartBusCycle(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector);
typedef RTS_RESULT (CDECL * PFIODRVSTARTBUSCYCLE) (RTS_HANDLE hIoDrv, IoConfigConnector *pConnector);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVSTARTBUSCYCLE_NOTIMPLEMENTED)
	#define USE_IoDrvStartBusCycle
	#define EXT_IoDrvStartBusCycle
	#define GET_IoDrvStartBusCycle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvStartBusCycle(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvStartBusCycle  FALSE
	#define EXP_IoDrvStartBusCycle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvStartBusCycle
	#define EXT_IoDrvStartBusCycle
	#define GET_IoDrvStartBusCycle(fl)  ERR_OK
	#define CAL_IoDrvStartBusCycle(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvStartBusCycle(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvStartBusCycle  TRUE
	#define EXP_IoDrvStartBusCycle  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvStartBusCycle
	#define EXT_IoDrvStartBusCycle
	#define GET_IoDrvStartBusCycle(fl)  ERR_OK
	#define CAL_IoDrvStartBusCycle(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvStartBusCycle(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvStartBusCycle  TRUE
	#define EXP_IoDrvStartBusCycle  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvStartBusCycle
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvStartBusCycle
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvStartBusCycle  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvStartBusCycle(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvStartBusCycle(p1))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvStartBusCycle  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvStartBusCycle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvStartBusCycle
	#define EXT_IoDrvStartBusCycle
	#define GET_IoDrvStartBusCycle(fl)  ERR_OK
	#define CAL_IoDrvStartBusCycle(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvStartBusCycle(p1))
	#define CHK_IoDrvStartBusCycle  TRUE
	#define EXP_IoDrvStartBusCycle  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvStartBusCycle
	#define EXT_IoDrvStartBusCycle
	#define GET_IoDrvStartBusCycle(fl)  ERR_OK
	#define CAL_IoDrvStartBusCycle(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvStartBusCycle(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvStartBusCycle  TRUE
	#define EXP_IoDrvStartBusCycle  ERR_OK
#endif




/**
 * <description>
 * <p>Propagate I/O configuration to the drivers.</p>
 * <p>This call passes the I/O configuration (based on the
 * configuration tree in the CoDeSys programming system) to
 * all registered I/O drivers. Every driver has the chance
 * to pass this tree and to register itself for a specific
 * connector.</p>
 * <p>The driver can use the I/O Manager Interface to iterate
 * over the I/O Connectors and to read the I/O Parameters.
 * If it decides to handle the I/Os of one of those connectors,
 * it can register it's driver handle (IBase) to the connector
 * in the member hIoDrv.</p>
 * <p>This function is called when the application is initialized
 * as well as when it is de- or reinitialized. In this case it is
 * called with pConnectorList = NULL.</p>
 * <p>The implementation of the IoDrvUnsafeBridge copies the io configuration
 * to unsafe memory, unregisteres supported IO drivers from IoMgr and puts them
 * to local administration and calls the IoDrvUpdateConfiguration functions of
 * the supported IO drivers.</p>
 * </description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param> 
 * <param name="pConnectorList" type="IN" range="[NULL,CONNECTORLIST_HUGE,CONNECTORLIST_HUGE_PARAMETERLIST,CONNECTORLIST_HUGE_PARAMETERVALUES,CONNECTORLIST_VALID_UNSAFE_PARAMETERVALUES,CONNECTORLIST_VALID]">Pointer to the complete connector list</param> 
 * <param name="nCount" type="IN" range="[0,CONNECTORLIST_LEN]">Number of entries in the connector list</param> 
 * <parampseudo name="bFirstIoDrv" type="IN" range="[TRUE,FALSE]">Is IoDrvUnsafeBridge the first registered IO driver</parampseudo> 
 * <parampseudo name="bInitialized" type="IN" range="[TRUE,FALSE]">UpdateConfiguration initialized and connector and parameter lists copied before</parampseudo>
 * <parampseudo name="nIoDrvStub" type="IN" range="[NOIODRVSTUB,CIODRVSTUB,IECIODRVSTUB]">Is IoDrvStub registered for this connector in the corresponding copied connector and is a C or IEC driver.</parampseudo>
 * <parampseudo name="bRealIODrvFctFailed" type="IN" range="[TRUE,FALSE]">The IoDrvUpdateConfiguration function of the real IO driver returned error.</parampseudo>  
 * <parampseudo name="IoDrvReturnValue" type="OUT" range="[ERR_OK,ERR_FAILED]">Return value, which should be returned by called IoDriver</parampseudo>
 * <parampseudo name="bParamValuesCopied" type="OUT" range="[TRUE,FALSE]">Return value, which should be returned by called IoDriver</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">UpdateConfiguration was successfull and found a driver</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or pConnector NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Not enought space to copy configuration</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvUpdateConfiguration(RTS_HANDLE hIoDrv, IoConfigConnector *pConnectorList, int nCount);
typedef RTS_RESULT (CDECL * PFIODRVUPDATECONFIGURATION) (RTS_HANDLE hIoDrv, IoConfigConnector *pConnectorList, int nCount);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVUPDATECONFIGURATION_NOTIMPLEMENTED)
	#define USE_IoDrvUpdateConfiguration
	#define EXT_IoDrvUpdateConfiguration
	#define GET_IoDrvUpdateConfiguration(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvUpdateConfiguration(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvUpdateConfiguration  FALSE
	#define EXP_IoDrvUpdateConfiguration  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvUpdateConfiguration
	#define EXT_IoDrvUpdateConfiguration
	#define GET_IoDrvUpdateConfiguration(fl)  ERR_OK
	#define CAL_IoDrvUpdateConfiguration(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvUpdateConfiguration(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvUpdateConfiguration  TRUE
	#define EXP_IoDrvUpdateConfiguration  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvUpdateConfiguration
	#define EXT_IoDrvUpdateConfiguration
	#define GET_IoDrvUpdateConfiguration(fl)  ERR_OK
	#define CAL_IoDrvUpdateConfiguration(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvUpdateConfiguration(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvUpdateConfiguration  TRUE
	#define EXP_IoDrvUpdateConfiguration  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvUpdateConfiguration
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvUpdateConfiguration
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvUpdateConfiguration  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvUpdateConfiguration(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvUpdateConfiguration(p1,p2))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvUpdateConfiguration  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvUpdateConfiguration  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvUpdateConfiguration
	#define EXT_IoDrvUpdateConfiguration
	#define GET_IoDrvUpdateConfiguration(fl)  ERR_OK
	#define CAL_IoDrvUpdateConfiguration(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvUpdateConfiguration(p1,p2))
	#define CHK_IoDrvUpdateConfiguration  TRUE
	#define EXP_IoDrvUpdateConfiguration  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvUpdateConfiguration
	#define EXT_IoDrvUpdateConfiguration
	#define GET_IoDrvUpdateConfiguration(fl)  ERR_OK
	#define CAL_IoDrvUpdateConfiguration(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvUpdateConfiguration(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvUpdateConfiguration  TRUE
	#define EXP_IoDrvUpdateConfiguration  ERR_OK
#endif




/**
 * <description>
 * <p>Propagate the task map lists to the drivers.</p>
 * <p>This functions gives the drivers a chance to optimize
 * their internal data structures based on the real task map
 * lists. The function is called on every initialization
 * of the application (download, bootproject,...).</p>
 * </description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param> 
 * <param name="pTaskMapList" type="IN" range="[NULL,TASKMAPLIST_HUGE,TASKMAPLIST_HUGE_CONNECTORMAPLIST,TASKMAPLIST_HUGE_CHANNELMAPLIST,TASKMAPLIST_HUGE_IOMEM,TASKMAPLIST_VALID]">Pointer to the task map list of one task</param> 
 * <param name="nCount" type="IN" range="[0,TASKMAPLIST_LEN]">Number of entries in the map list</param> 
 * <parampseudo name="bInitialized" type="IN" range="[TRUE,FALSE]">UpdateConfiguration initialized and connector and parameter lists copied before</parampseudo>
 * <parampseudo name="bIoDrvStubRegistered" type="IN" range="[TRUE,FALSE]">Is IoDrvStub registered for this connector in the corresponding copied connector.</parampseudo>
 * <parampseudo name="bRealIODrvFctFailed" type="IN" range="[TRUE,FALSE]">The IoDrvUpdateMapping function of the real IO driver returned error.</parampseudo>
 * <parampseudo name="IoDrvReturnValue" type="OUT" range="[ERR_OK,ERR_FAILED]">Return value, which should be returned by called IoDriver</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">UpdateMapping successful</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Not enought space to copy configuration</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvUpdateMapping(RTS_HANDLE hIoDrv, IoConfigTaskMap *pTaskMapList, int nCount);
typedef RTS_RESULT (CDECL * PFIODRVUPDATEMAPPING) (RTS_HANDLE hIoDrv, IoConfigTaskMap *pTaskMapList, int nCount);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVUPDATEMAPPING_NOTIMPLEMENTED)
	#define USE_IoDrvUpdateMapping
	#define EXT_IoDrvUpdateMapping
	#define GET_IoDrvUpdateMapping(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvUpdateMapping(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvUpdateMapping  FALSE
	#define EXP_IoDrvUpdateMapping  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvUpdateMapping
	#define EXT_IoDrvUpdateMapping
	#define GET_IoDrvUpdateMapping(fl)  ERR_OK
	#define CAL_IoDrvUpdateMapping(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvUpdateMapping(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvUpdateMapping  TRUE
	#define EXP_IoDrvUpdateMapping  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvUpdateMapping
	#define EXT_IoDrvUpdateMapping
	#define GET_IoDrvUpdateMapping(fl)  ERR_OK
	#define CAL_IoDrvUpdateMapping(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvUpdateMapping(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvUpdateMapping  TRUE
	#define EXP_IoDrvUpdateMapping  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvUpdateMapping
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvUpdateMapping
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvUpdateMapping  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvUpdateMapping(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvUpdateMapping(p1,p2))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvUpdateMapping  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvUpdateMapping  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvUpdateMapping
	#define EXT_IoDrvUpdateMapping
	#define GET_IoDrvUpdateMapping(fl)  ERR_OK
	#define CAL_IoDrvUpdateMapping(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvUpdateMapping(p1,p2))
	#define CHK_IoDrvUpdateMapping  TRUE
	#define EXP_IoDrvUpdateMapping  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvUpdateMapping
	#define EXT_IoDrvUpdateMapping
	#define GET_IoDrvUpdateMapping(fl)  ERR_OK
	#define CAL_IoDrvUpdateMapping(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvUpdateMapping(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvUpdateMapping  TRUE
	#define EXP_IoDrvUpdateMapping  ERR_OK
#endif




/**
 * <description>
 * <p>Trigger the hardware watchdog of a driver.</p>
 * <p>This function is depricated and not used anymore.</p>
 * <p>This function is not implemented in the IoDrvUnsafeBridge implementation and ERR_NOTIMPLEMENTED is returned.</p>
 * </description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR]">Pointer to the connector, on which the watchdog should be retriggered</param> 
 * <parampseudo name="bConnectorCopied" type="IN" range="[TRUE,FALSE]">Given connector was copied before.</parampseudo>
 * <parampseudo name="bIoDrvStubRegistered" type="IN" range="[TRUE,FALSE]">Is IoDrvStub registered for this connector in the corresponding copied connector.</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Not provided by the driver</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvWatchdogTrigger(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector);
typedef RTS_RESULT (CDECL * PFIODRVWATCHDOGTRIGGER) (RTS_HANDLE hIoDrv, IoConfigConnector *pConnector);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVWATCHDOGTRIGGER_NOTIMPLEMENTED)
	#define USE_IoDrvWatchdogTrigger
	#define EXT_IoDrvWatchdogTrigger
	#define GET_IoDrvWatchdogTrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvWatchdogTrigger(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvWatchdogTrigger  FALSE
	#define EXP_IoDrvWatchdogTrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvWatchdogTrigger
	#define EXT_IoDrvWatchdogTrigger
	#define GET_IoDrvWatchdogTrigger(fl)  ERR_OK
	#define CAL_IoDrvWatchdogTrigger(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWatchdogTrigger(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvWatchdogTrigger  TRUE
	#define EXP_IoDrvWatchdogTrigger  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvWatchdogTrigger
	#define EXT_IoDrvWatchdogTrigger
	#define GET_IoDrvWatchdogTrigger(fl)  ERR_OK
	#define CAL_IoDrvWatchdogTrigger(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWatchdogTrigger(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvWatchdogTrigger  TRUE
	#define EXP_IoDrvWatchdogTrigger  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvWatchdogTrigger
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvWatchdogTrigger
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvWatchdogTrigger  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvWatchdogTrigger(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWatchdogTrigger(p1))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvWatchdogTrigger  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvWatchdogTrigger  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvWatchdogTrigger
	#define EXT_IoDrvWatchdogTrigger
	#define GET_IoDrvWatchdogTrigger(fl)  ERR_OK
	#define CAL_IoDrvWatchdogTrigger(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWatchdogTrigger(p1))
	#define CHK_IoDrvWatchdogTrigger  TRUE
	#define EXP_IoDrvWatchdogTrigger  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvWatchdogTrigger
	#define EXT_IoDrvWatchdogTrigger
	#define GET_IoDrvWatchdogTrigger(fl)  ERR_OK
	#define CAL_IoDrvWatchdogTrigger(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWatchdogTrigger(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvWatchdogTrigger  TRUE
	#define EXP_IoDrvWatchdogTrigger  ERR_OK
#endif




/**
 * <description>
 * <p>Write outputs for one task</p>
 * <p>This function is called cyclically from every task
 * that is using outputs. A part of the task map list,
 * which contains only the data of one connector are passed
 * to the driver (called connector map list).</p>
 * <p>If a driver has registered one instance to more
 * than one connector, it might get more than one call with
 * a different subset of the task map list.</p>
 * <p>The I/O driver should write out the data to the local
 * hardware, a buffer or a fieldbus.</p>
 * <p>The IoDrvUnsafeBridgeImplementation copies the output values to unsafe 
 * memory and passes this call to the corresponding unsafe io driver with the
 * copied connector list.</p>
 * </description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param> 
 * <param name="pConnectorMapList" type="IN" range="[NULL,VALID_CONNECTORMAPLIST]">Pointer to the connector map list</param> 
 * <param name="nCount" type="IN" range="[0..CONNECTORMAPLIST_LEN-1]">Number of entries in the connector map list</param>
 * <parampseudo name="bConnectorCopied" type="IN" range="[TRUE,FALSE]">Given connector was copied before.</parampseudo>
 * <parampseudo name="bIoDrvStubRegistered" type="IN" range="[TRUE,FALSE]">Is IoDrvStub registered for this connector in the corresponding copied connector.</parampseudo>
 * <parampseudo name="nContinuousConnectorsA" type="IN" range="[1,2]">Number of connectors for stub driver A</parampseudo>
 * <parampseudo name="nContinuousConnectorsB" type="IN" range="[0,2]">Number of connectors for stub driver B</parampseudo>
 * <parampseudo name="bDriverBCalled" type="OUT" range="[TRUE,FALSE]">Driver B called.</parampseudo> 
 * <parampseudo name="IoDrvReturnValue" type="OUT" range="[ERR_OK,ERR_FAILED]">Return value, which should be returned by called IoDrvStub</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Outputs successfully written</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or pConnectorMapList NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvWriteOutputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount);
typedef RTS_RESULT (CDECL * PFIODRVWRITEOUTPUTS) (RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVWRITEOUTPUTS_NOTIMPLEMENTED)
	#define USE_IoDrvWriteOutputs
	#define EXT_IoDrvWriteOutputs
	#define GET_IoDrvWriteOutputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvWriteOutputs(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvWriteOutputs  FALSE
	#define EXP_IoDrvWriteOutputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvWriteOutputs
	#define EXT_IoDrvWriteOutputs
	#define GET_IoDrvWriteOutputs(fl)  ERR_OK
	#define CAL_IoDrvWriteOutputs(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWriteOutputs(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvWriteOutputs  TRUE
	#define EXP_IoDrvWriteOutputs  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvWriteOutputs
	#define EXT_IoDrvWriteOutputs
	#define GET_IoDrvWriteOutputs(fl)  ERR_OK
	#define CAL_IoDrvWriteOutputs(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWriteOutputs(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvWriteOutputs  TRUE
	#define EXP_IoDrvWriteOutputs  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvWriteOutputs
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvWriteOutputs
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvWriteOutputs  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvWriteOutputs(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWriteOutputs(p1,p2))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvWriteOutputs  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvWriteOutputs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvWriteOutputs
	#define EXT_IoDrvWriteOutputs
	#define GET_IoDrvWriteOutputs(fl)  ERR_OK
	#define CAL_IoDrvWriteOutputs(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWriteOutputs(p1,p2))
	#define CHK_IoDrvWriteOutputs  TRUE
	#define EXP_IoDrvWriteOutputs  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvWriteOutputs
	#define EXT_IoDrvWriteOutputs
	#define GET_IoDrvWriteOutputs(fl)  ERR_OK
	#define CAL_IoDrvWriteOutputs(p0,p1,p2) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWriteOutputs(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2))
	#define CHK_IoDrvWriteOutputs  TRUE
	#define EXP_IoDrvWriteOutputs  ERR_OK
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
 * <param name="hDevice" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR]">Pointer to the connector (might be determined with IoMgrConfigGetConnector).</param>
 * <param name="pParameter" type="IN" range="[NULL,VALID_PARAMETER]">Pointer to the parameter (might be determined with IoMgrConfigGetParameter)</param>
 * <param name="pData" type="IN" range="[NULL,VALID_DATABUFFER]">Buffer where the read data is stored</param>
 * <param name="ulBitSize" type="IN" range="[0..PARAM_SIZE-1]">Size of the part of the parameter data, that should be read</param>
 * <param name="ulBitOffset" type="IN" range="[0..PARAM_SIZE-1]">Offset of the part of the parameter, that should be read</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Not provided by the driver</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvReadParameter(RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
typedef RTS_RESULT (CDECL * PFIODRVREADPARAMETER) (RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVREADPARAMETER_NOTIMPLEMENTED)
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
	#define CAL_IoDrvReadParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvReadParameter(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvReadParameter  TRUE
	#define EXP_IoDrvReadParameter  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvReadParameter
	#define EXT_IoDrvReadParameter
	#define GET_IoDrvReadParameter(fl)  ERR_OK
	#define CAL_IoDrvReadParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvReadParameter(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvReadParameter  TRUE
	#define EXP_IoDrvReadParameter  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvReadParameter
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvReadParameter
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvReadParameter  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvReadParameter(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvReadParameter(p1,p2,p3,p4,p5))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvReadParameter  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvReadParameter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvReadParameter
	#define EXT_IoDrvReadParameter
	#define GET_IoDrvReadParameter(fl)  ERR_OK
	#define CAL_IoDrvReadParameter(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvReadParameter(p1,p2,p3,p4,p5))
	#define CHK_IoDrvReadParameter  TRUE
	#define EXP_IoDrvReadParameter  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvReadParameter
	#define EXT_IoDrvReadParameter
	#define GET_IoDrvReadParameter(fl)  ERR_OK
	#define CAL_IoDrvReadParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvReadParameter(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
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
 * <p>Note: On SIL2 runtimes, this interface is not supported.</p>
 * </description>
 * <param name="hDevice" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER_HANDLE]">Handle to the IO-driver instance</param>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR]">Pointer to the connector (might be determined with IoMgrConfigGetConnector).</param>
 * <param name="pParameter" type="IN" range="[NULL,VALID_PARAMETER]">Pointer to the parameter (might be determined with IoMgrConfigGetParameter)</param>
 * <param name="pData" type="IN" range="[NULL,VALID_DATABUFFER]">Buffer where the read data is stored</param>
 * <param name="ulBitSize" type="IN" range="[0..PARAM_SIZE-1]">Size of the part of the parameter data, that should be written</param>
 * <param name="ulBitOffset" type="IN" range="[0..PARAM_SIZE-1]">Offset of the part of the parameter, that should be written</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Not provided by the driver</errorcode>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvWriteParameter(RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
typedef RTS_RESULT (CDECL * PFIODRVWRITEPARAMETER) (RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
#if defined(IODRVUNSAFEBRIDGEMODULETEST_NOTIMPLEMENTED) || defined(IODRVWRITEPARAMETER_NOTIMPLEMENTED)
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
	#define CAL_IoDrvWriteParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWriteParameter(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameter  TRUE
	#define EXP_IoDrvWriteParameter  ERR_OK
#elif defined(MIXED_LINK) && !defined(IODRVUNSAFEBRIDGEMODULETEST_EXTERNAL)
	#define USE_IoDrvWriteParameter
	#define EXT_IoDrvWriteParameter
	#define GET_IoDrvWriteParameter(fl)  ERR_OK
	#define CAL_IoDrvWriteParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWriteParameter(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameter  TRUE
	#define EXP_IoDrvWriteParameter  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvUnsafeBridgeModuletestIoDrvWriteParameter
	#define EXT_IoDrvUnsafeBridgeModuletestIoDrvWriteParameter
	#define GET_IoDrvUnsafeBridgeModuletestIoDrvWriteParameter  ERR_OK
	#define CAL_IoDrvUnsafeBridgeModuletestIoDrvWriteParameter(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWriteParameter(p1,p2,p3,p4,p5))
	#define CHK_IoDrvUnsafeBridgeModuletestIoDrvWriteParameter  TRUE
	#define EXP_IoDrvUnsafeBridgeModuletestIoDrvWriteParameter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvWriteParameter
	#define EXT_IoDrvWriteParameter
	#define GET_IoDrvWriteParameter(fl)  ERR_OK
	#define CAL_IoDrvWriteParameter(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWriteParameter(p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameter  TRUE
	#define EXP_IoDrvWriteParameter  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvWriteParameter
	#define EXT_IoDrvWriteParameter
	#define GET_IoDrvWriteParameter(fl)  ERR_OK
	#define CAL_IoDrvWriteParameter(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((IIoDrvUnsafeBridgeModuletest*)p0)->IIoDrvWriteParameter(((IIoDrvUnsafeBridgeModuletest*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameter  TRUE
	#define EXP_IoDrvWriteParameter  ERR_OK
#endif






typedef struct
{
	IBase_C *pBase;
	PFIODRVCREATE IIoDrvCreate;
 	PFIODRVDELETE IIoDrvDelete;
 	PFIODRVGETINFO IIoDrvGetInfo;
 	PFIODRVGETMODULEDIAGNOSIS IIoDrvGetModuleDiagnosis;
 	PFIODRVIDENTIFY IIoDrvIdentify;
 	PFIODRVREADINPUTS IIoDrvReadInputs;
 	PFIODRVSCANMODULES IIoDrvScanModules;
 	PFIODRVSTARTBUSCYCLE IIoDrvStartBusCycle;
 	PFIODRVUPDATECONFIGURATION IIoDrvUpdateConfiguration;
 	PFIODRVUPDATEMAPPING IIoDrvUpdateMapping;
 	PFIODRVWATCHDOGTRIGGER IIoDrvWatchdogTrigger;
 	PFIODRVWRITEOUTPUTS IIoDrvWriteOutputs;
 	PFIODRVREADPARAMETER IIoDrvReadParameter;
 	PFIODRVWRITEPARAMETER IIoDrvWriteParameter;
 } IIoDrvUnsafeBridgeModuletest_C;

#ifdef CPLUSPLUS
class IIoDrvUnsafeBridgeModuletest : public IBase
{
	public:
		virtual RTS_HANDLE CDECL IIoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIoDrvDelete(RTS_HANDLE hIIoDrv) =0;
		virtual RTS_RESULT CDECL IIoDrvGetInfo(IoDrvInfo **ppInfo) =0;
		virtual RTS_RESULT CDECL IIoDrvGetModuleDiagnosis(IoConfigConnector *pConnector) =0;
		virtual RTS_RESULT CDECL IIoDrvIdentify(IoConfigConnector *pConnector) =0;
		virtual RTS_RESULT CDECL IIoDrvReadInputs(IoConfigConnectorMap *pConnectorMapList, int nCount) =0;
		virtual RTS_RESULT CDECL IIoDrvScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount) =0;
		virtual RTS_RESULT CDECL IIoDrvStartBusCycle(IoConfigConnector *pConnector) =0;
		virtual RTS_RESULT CDECL IIoDrvUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount) =0;
		virtual RTS_RESULT CDECL IIoDrvUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount) =0;
		virtual RTS_RESULT CDECL IIoDrvWatchdogTrigger(IoConfigConnector *pConnector) =0;
		virtual RTS_RESULT CDECL IIoDrvWriteOutputs(IoConfigConnectorMap *pConnectorMapList, int nCount) =0;
		virtual RTS_RESULT CDECL IIoDrvReadParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset) =0;
		virtual RTS_RESULT CDECL IIoDrvWriteParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset) =0;
};
	#ifndef ITF_IoDrvUnsafeBridgeModuletest
		#define ITF_IoDrvUnsafeBridgeModuletest static IIoDrvUnsafeBridgeModuletest *pIIoDrvUnsafeBridgeModuletest = NULL;
	#endif
	#define EXTITF_IoDrvUnsafeBridgeModuletest
#else	/*CPLUSPLUS*/
	typedef IIoDrvUnsafeBridgeModuletest_C		IIoDrvUnsafeBridgeModuletest;
	#ifndef ITF_IoDrvUnsafeBridgeModuletest
		#define ITF_IoDrvUnsafeBridgeModuletest
	#endif
	#define EXTITF_IoDrvUnsafeBridgeModuletest
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_IODRVUNSAFEBRIDGEMODULETESTITF_H_*/
