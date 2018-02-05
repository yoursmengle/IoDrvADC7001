 /**
 * <interfacename>CmpIoDrvIec</interfacename>
 * <description>
 * <p>Wrapper to access the interface functions of an IEC driver from C.</p>
 * <p>The registration of a new IEC driver instance is going like this:</p>
 * <pre>
 * .   +--------------+   +--------+   +-----------+
 * .   |IEC Driver Lib|   |CmpIoMgr|   |CmpIoDrvIec|
 * .   +--------------+   +--------+   +-----------+
 * .          |               |              |
 * .         +-+ Register     |              |
 * .         | |   Instance   |              |
 * .         | |-------------+-+ Register    |
 * .         | |             | |   Instance  |
 * .         | |             | |------------+-+
 * .         | |             | |            | |
 * .         | |             | |            | |
 * .         | |             |+++-----------| |
 * .         | |             || |           | |
 * .         | |             || |           | |
 * .         | |             || |           | |
 * .         | |             || |           | |
 * .         | |             |+++...........| |
 * .         | |             | |            | |
 * .         | |             | |            | |
 * .         | |             | |............+-+
 * .         | |.............+-+
 * .         +-+
 * </pre>
 * <p>The handle of the I/O driver wrapper looks like this:</p>
 * <pre>
 * .                +------------------------+
 * .                |CCmpIoDrvIec            |
 * .                +------------------------+
 * .                |hInstance               | ----.
 * .                +------------------------+     |
 * .              . |IoDrvGetInfo            |     |
 * .             /  |IoDrvGetModuleDiagnosis |     |
 * .            /   |IoDrvIdentify           |     |
 * .            |   |IoDrvReadInputs         |     |
 * . C-Wrapper -'   |IoDrvScanModules        |     |
 * .            |   |IoDrvStartBusCycle      |     |
 * .            |   |IoDrvUpdateConfiguration|     |     +-------------+
 * .            \   |IoDrvUpdateMapping      |     '---- |I/O Drv FB   |
 * .             \  |IoDrvWatchdogTrigger    |           +-------------+
 * .              ' |IoDrvWriteOutputs       |           |ITF_ICmpIoDrv|
 * .                +------------------------+           +-------------+
 * .                |IoDrvGetInfo            | .         |pvftable[4]  |
 * .                |IoDrvGetModuleDiagnosis |  \        |pvftable[5]  |
 * .                |IoDrvIdentify           |   \       |pvftable[6]  |
 * .                |IoDrvReadInputs         |   |       |pvftable[7]  |
 * .                |IoDrvScanModules        |   '------ |pvftable[8]  |
 * .                |IoDrvStartBusCycle      |   |       |pvftable[9]  |
 * .                |IoDrvUpdateConfiguration|   |       |pvftable[10] |
 * .                |IoDrvUpdateMapping      |   /       |pvftable[11] |
 * .                |IoDrvWatchdogTrigger    |  /        |pvftable[12] |
 * .                |IoDrvWriteOutputs       | '         |pvftable[13] |
 * .                +------------------------+           +-------------+
 * </pre>
 * <p>The main difference between the registration with IoDrvRegisterInstance()
 * vs. IoDrvRegisterInstance2() is, that the first one was initializing all IEC
 * function pointers by itself and the second is using BaseUpdateConfiguration()
 * for this purpose. IoDrvRegisterInstance is now depricated.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPIODRVIECITF_H_
#define _CMPIODRVIECITF_H_

#include "CmpStd.h"

 

 




#include "CmpIoDrvItf.h"
#include "CmpIoDrvParameterItf.h"
#include "CmpIoDrvParameter2Itf.h"

#ifndef MAX_STATIC_IEC_DRIVER
	#define MAX_STATIC_IEC_DRIVER	2
#endif

/* <SIL2/> */
typedef struct
{
	RTS_IEC_DWORD dwClassId;
	RTS_IEC_DWORD dwItfId;
	ieciodrvinstance_struct *pInterface;
	RTS_IEC_UDINT *pResult;
	RTS_IEC_HANDLE hInterface;
} iodrviecregisterinstance_struct;

/* <SIL2/> */
typedef struct
{
	RTS_IEC_DWORD dwClassId;
	ieciodrvinstance_struct *pInterface;
	RTS_IEC_UDINT *pResult;
	RTS_IEC_HANDLE hInterface;
} iodrviecregisterinstance2_struct;

/* <SIL2/> */
typedef struct
{
	RTS_IEC_HANDLE hInterface;
	RTS_IEC_UDINT Result;
} iodrviecunregisterinstance_struct;

#ifdef __cplusplus
extern "C" {
#endif

void* CDECL BaseQueryInterface(IBase *pIBase, ITFID iid, RTS_RESULT *pResult);

/**
 * <description>
 * <p>Obsolete! This interface is not used anymore.</p>
 * <p>Note: On SIL2 Runtimes, this call leads to an exception.</p>
 * </description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMEPLEMENTED">The function is obsolete and not available anymore</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The function was called in a SIL2 runtime and the exception handling returned</errorcode>
 */
RTS_RESULT CDECL IoDrvRegisterInstance(iodrviecregisterinstance_struct *p);
typedef RTS_RESULT (CDECL * PFIODRVREGISTERINSTANCE) (iodrviecregisterinstance_struct *p);
#if defined(CMPIODRVIEC_NOTIMPLEMENTED) || defined(IODRVREGISTERINSTANCE_NOTIMPLEMENTED)
	#define USE_IoDrvRegisterInstance
	#define EXT_IoDrvRegisterInstance
	#define GET_IoDrvRegisterInstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvRegisterInstance(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvRegisterInstance  FALSE
	#define EXP_IoDrvRegisterInstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvRegisterInstance
	#define EXT_IoDrvRegisterInstance
	#define GET_IoDrvRegisterInstance(fl)  CAL_CMGETAPI( "IoDrvRegisterInstance" ) 
	#define CAL_IoDrvRegisterInstance  IoDrvRegisterInstance
	#define CHK_IoDrvRegisterInstance  TRUE
	#define EXP_IoDrvRegisterInstance  CAL_CMEXPAPI( "IoDrvRegisterInstance" ) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVIEC_EXTERNAL)
	#define USE_IoDrvRegisterInstance
	#define EXT_IoDrvRegisterInstance
	#define GET_IoDrvRegisterInstance(fl)  CAL_CMGETAPI( "IoDrvRegisterInstance" ) 
	#define CAL_IoDrvRegisterInstance  IoDrvRegisterInstance
	#define CHK_IoDrvRegisterInstance  TRUE
	#define EXP_IoDrvRegisterInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoDrvRegisterInstance", (RTS_UINTPTR)IoDrvRegisterInstance, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvIecIoDrvRegisterInstance
	#define EXT_CmpIoDrvIecIoDrvRegisterInstance
	#define GET_CmpIoDrvIecIoDrvRegisterInstance  ERR_OK
	#define CAL_CmpIoDrvIecIoDrvRegisterInstance pICmpIoDrvIec->IIoDrvRegisterInstance
	#define CHK_CmpIoDrvIecIoDrvRegisterInstance (pICmpIoDrvIec != NULL)
	#define EXP_CmpIoDrvIecIoDrvRegisterInstance  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvRegisterInstance
	#define EXT_IoDrvRegisterInstance
	#define GET_IoDrvRegisterInstance(fl)  CAL_CMGETAPI( "IoDrvRegisterInstance" ) 
	#define CAL_IoDrvRegisterInstance pICmpIoDrvIec->IIoDrvRegisterInstance
	#define CHK_IoDrvRegisterInstance (pICmpIoDrvIec != NULL)
	#define EXP_IoDrvRegisterInstance  CAL_CMEXPAPI( "IoDrvRegisterInstance" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoDrvRegisterInstance  PFIODRVREGISTERINSTANCE pfIoDrvRegisterInstance;
	#define EXT_IoDrvRegisterInstance  extern PFIODRVREGISTERINSTANCE pfIoDrvRegisterInstance;
	#define GET_IoDrvRegisterInstance(fl)  s_pfCMGetAPI2( "IoDrvRegisterInstance", (RTS_VOID_FCTPTR *)&pfIoDrvRegisterInstance, (fl), 0, 0)
	#define CAL_IoDrvRegisterInstance  pfIoDrvRegisterInstance
	#define CHK_IoDrvRegisterInstance  (pfIoDrvRegisterInstance != NULL)
	#define EXP_IoDrvRegisterInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoDrvRegisterInstance", (RTS_UINTPTR)IoDrvRegisterInstance, 0, 0) 
#endif




/**
 * <description>
 * <p>Register an IEC I/O driver.</p>
 * <p>A call to this function creates a new instance of the CmpIoDrvIec
 * component, which acts as a wrapper for the registered IEC I/O driver.
 * It will, by itself, call IoMgrRegisterInstance2() to register the
 * newly created C-Wrapper Interface at the I/O Manager.
 * </p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REGISTERINSTANCE_PARAMETER]">IEC Parameter structure</param>
 * <parampseudo name="p.pInterface" type="IN" range="[NULL,VALID_INTERFACE]">IEC Interface Pointer</parampseudo>
 * <parampseudo name="p.pInterface" type="IN" range="[NULL,VALID_INTERFACE]">IEC Interface Pointer</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Registration was successfull</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Not enough memory to create a new instance</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">No valid Interface</errorcode>
 * 
 */
RTS_RESULT CDECL IoDrvRegisterInstance2(iodrviecregisterinstance2_struct *p);
typedef RTS_RESULT (CDECL * PFIODRVREGISTERINSTANCE2) (iodrviecregisterinstance2_struct *p);
#if defined(CMPIODRVIEC_NOTIMPLEMENTED) || defined(IODRVREGISTERINSTANCE2_NOTIMPLEMENTED)
	#define USE_IoDrvRegisterInstance2
	#define EXT_IoDrvRegisterInstance2
	#define GET_IoDrvRegisterInstance2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvRegisterInstance2(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvRegisterInstance2  FALSE
	#define EXP_IoDrvRegisterInstance2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvRegisterInstance2
	#define EXT_IoDrvRegisterInstance2
	#define GET_IoDrvRegisterInstance2(fl)  CAL_CMGETAPI( "IoDrvRegisterInstance2" ) 
	#define CAL_IoDrvRegisterInstance2  IoDrvRegisterInstance2
	#define CHK_IoDrvRegisterInstance2  TRUE
	#define EXP_IoDrvRegisterInstance2  CAL_CMEXPAPI( "IoDrvRegisterInstance2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVIEC_EXTERNAL)
	#define USE_IoDrvRegisterInstance2
	#define EXT_IoDrvRegisterInstance2
	#define GET_IoDrvRegisterInstance2(fl)  CAL_CMGETAPI( "IoDrvRegisterInstance2" ) 
	#define CAL_IoDrvRegisterInstance2  IoDrvRegisterInstance2
	#define CHK_IoDrvRegisterInstance2  TRUE
	#define EXP_IoDrvRegisterInstance2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoDrvRegisterInstance2", (RTS_UINTPTR)IoDrvRegisterInstance2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvIecIoDrvRegisterInstance2
	#define EXT_CmpIoDrvIecIoDrvRegisterInstance2
	#define GET_CmpIoDrvIecIoDrvRegisterInstance2  ERR_OK
	#define CAL_CmpIoDrvIecIoDrvRegisterInstance2 pICmpIoDrvIec->IIoDrvRegisterInstance2
	#define CHK_CmpIoDrvIecIoDrvRegisterInstance2 (pICmpIoDrvIec != NULL)
	#define EXP_CmpIoDrvIecIoDrvRegisterInstance2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvRegisterInstance2
	#define EXT_IoDrvRegisterInstance2
	#define GET_IoDrvRegisterInstance2(fl)  CAL_CMGETAPI( "IoDrvRegisterInstance2" ) 
	#define CAL_IoDrvRegisterInstance2 pICmpIoDrvIec->IIoDrvRegisterInstance2
	#define CHK_IoDrvRegisterInstance2 (pICmpIoDrvIec != NULL)
	#define EXP_IoDrvRegisterInstance2  CAL_CMEXPAPI( "IoDrvRegisterInstance2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoDrvRegisterInstance2  PFIODRVREGISTERINSTANCE2 pfIoDrvRegisterInstance2;
	#define EXT_IoDrvRegisterInstance2  extern PFIODRVREGISTERINSTANCE2 pfIoDrvRegisterInstance2;
	#define GET_IoDrvRegisterInstance2(fl)  s_pfCMGetAPI2( "IoDrvRegisterInstance2", (RTS_VOID_FCTPTR *)&pfIoDrvRegisterInstance2, (fl), 0, 0)
	#define CAL_IoDrvRegisterInstance2  pfIoDrvRegisterInstance2
	#define CHK_IoDrvRegisterInstance2  (pfIoDrvRegisterInstance2 != NULL)
	#define EXP_IoDrvRegisterInstance2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoDrvRegisterInstance2", (RTS_UINTPTR)IoDrvRegisterInstance2, 0, 0) 
#endif




/**
 * <description>
 * <p>Unregister an IEC I/O driver.</p>
 * <p>Delete a driver instance and unregister it from the I/O Manager.</p>
 * <p>Note: On SIL2 runtimes, this function is only allowed in debug mode.
 * When it is called outside of the debug mode, it will throw an exception.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_UNREGISTERINSTANCE_PARAMETER]">IEC Parameter structure</param>
 * <parampseudo name="p.hInterface" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_INTERFACE_HANDLE]">IEC Interface Pointer</parampseudo>
 * <parampseudo name="OperationMode" type="IN" range="[RTS_SIL2_OPMODE_SAFE,RTS_SIL2_OPMODE_DEBUG]">Operation mode</parampseudo>
 * <parampseudo name="bExceptionGenerated" type="OUT" range="[TRUE,FALSE]">Indicates, if an exception was thrown or not</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Deregistration was successfull</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pIBase was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="*">Internal error when trying to free the driver handle</errorcode>
 */
RTS_RESULT CDECL IoDrvUnregisterInstance(iodrviecunregisterinstance_struct *p);
typedef RTS_RESULT (CDECL * PFIODRVUNREGISTERINSTANCE) (iodrviecunregisterinstance_struct *p);
#if defined(CMPIODRVIEC_NOTIMPLEMENTED) || defined(IODRVUNREGISTERINSTANCE_NOTIMPLEMENTED)
	#define USE_IoDrvUnregisterInstance
	#define EXT_IoDrvUnregisterInstance
	#define GET_IoDrvUnregisterInstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvUnregisterInstance(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvUnregisterInstance  FALSE
	#define EXP_IoDrvUnregisterInstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvUnregisterInstance
	#define EXT_IoDrvUnregisterInstance
	#define GET_IoDrvUnregisterInstance(fl)  CAL_CMGETAPI( "IoDrvUnregisterInstance" ) 
	#define CAL_IoDrvUnregisterInstance  IoDrvUnregisterInstance
	#define CHK_IoDrvUnregisterInstance  TRUE
	#define EXP_IoDrvUnregisterInstance  CAL_CMEXPAPI( "IoDrvUnregisterInstance" ) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVIEC_EXTERNAL)
	#define USE_IoDrvUnregisterInstance
	#define EXT_IoDrvUnregisterInstance
	#define GET_IoDrvUnregisterInstance(fl)  CAL_CMGETAPI( "IoDrvUnregisterInstance" ) 
	#define CAL_IoDrvUnregisterInstance  IoDrvUnregisterInstance
	#define CHK_IoDrvUnregisterInstance  TRUE
	#define EXP_IoDrvUnregisterInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoDrvUnregisterInstance", (RTS_UINTPTR)IoDrvUnregisterInstance, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvIecIoDrvUnregisterInstance
	#define EXT_CmpIoDrvIecIoDrvUnregisterInstance
	#define GET_CmpIoDrvIecIoDrvUnregisterInstance  ERR_OK
	#define CAL_CmpIoDrvIecIoDrvUnregisterInstance pICmpIoDrvIec->IIoDrvUnregisterInstance
	#define CHK_CmpIoDrvIecIoDrvUnregisterInstance (pICmpIoDrvIec != NULL)
	#define EXP_CmpIoDrvIecIoDrvUnregisterInstance  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvUnregisterInstance
	#define EXT_IoDrvUnregisterInstance
	#define GET_IoDrvUnregisterInstance(fl)  CAL_CMGETAPI( "IoDrvUnregisterInstance" ) 
	#define CAL_IoDrvUnregisterInstance pICmpIoDrvIec->IIoDrvUnregisterInstance
	#define CHK_IoDrvUnregisterInstance (pICmpIoDrvIec != NULL)
	#define EXP_IoDrvUnregisterInstance  CAL_CMEXPAPI( "IoDrvUnregisterInstance" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoDrvUnregisterInstance  PFIODRVUNREGISTERINSTANCE pfIoDrvUnregisterInstance;
	#define EXT_IoDrvUnregisterInstance  extern PFIODRVUNREGISTERINSTANCE pfIoDrvUnregisterInstance;
	#define GET_IoDrvUnregisterInstance(fl)  s_pfCMGetAPI2( "IoDrvUnregisterInstance", (RTS_VOID_FCTPTR *)&pfIoDrvUnregisterInstance, (fl), 0, 0)
	#define CAL_IoDrvUnregisterInstance  pfIoDrvUnregisterInstance
	#define CHK_IoDrvUnregisterInstance  (pfIoDrvUnregisterInstance != NULL)
	#define EXP_IoDrvUnregisterInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoDrvUnregisterInstance", (RTS_UINTPTR)IoDrvUnregisterInstance, 0, 0) 
#endif




/**
 * <description>
 * <p>Get an IEC I/O driver interface pointer, based on a handle
 * to it's corresponding C-Wrapper.</p>
 * </description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_IODRIVER]">Handle of a C-Wrapper</param>
 * <param name="Result" type="OUT">Result of the function</param>
 * <result>Pointer to the IEC base interface</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Interface returned successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was NULL or invalid</errorcode>
 */
IBase* CDECL IoDrvGetIecInterface(RTS_HANDLE hIoDrv, RTS_RESULT *pResult);
typedef IBase* (CDECL * PFIODRVGETIECINTERFACE) (RTS_HANDLE hIoDrv, RTS_RESULT *pResult);
#if defined(CMPIODRVIEC_NOTIMPLEMENTED) || defined(IODRVGETIECINTERFACE_NOTIMPLEMENTED)
	#define USE_IoDrvGetIecInterface
	#define EXT_IoDrvGetIecInterface
	#define GET_IoDrvGetIecInterface(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvGetIecInterface(p0,p1)  (IBase*)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvGetIecInterface  FALSE
	#define EXP_IoDrvGetIecInterface  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvGetIecInterface
	#define EXT_IoDrvGetIecInterface
	#define GET_IoDrvGetIecInterface(fl)  CAL_CMGETAPI( "IoDrvGetIecInterface" ) 
	#define CAL_IoDrvGetIecInterface  IoDrvGetIecInterface
	#define CHK_IoDrvGetIecInterface  TRUE
	#define EXP_IoDrvGetIecInterface  CAL_CMEXPAPI( "IoDrvGetIecInterface" ) 
#elif defined(MIXED_LINK) && !defined(CMPIODRVIEC_EXTERNAL)
	#define USE_IoDrvGetIecInterface
	#define EXT_IoDrvGetIecInterface
	#define GET_IoDrvGetIecInterface(fl)  CAL_CMGETAPI( "IoDrvGetIecInterface" ) 
	#define CAL_IoDrvGetIecInterface  IoDrvGetIecInterface
	#define CHK_IoDrvGetIecInterface  TRUE
	#define EXP_IoDrvGetIecInterface  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoDrvGetIecInterface", (RTS_UINTPTR)IoDrvGetIecInterface, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvIecIoDrvGetIecInterface
	#define EXT_CmpIoDrvIecIoDrvGetIecInterface
	#define GET_CmpIoDrvIecIoDrvGetIecInterface  ERR_OK
	#define CAL_CmpIoDrvIecIoDrvGetIecInterface pICmpIoDrvIec->IIoDrvGetIecInterface
	#define CHK_CmpIoDrvIecIoDrvGetIecInterface (pICmpIoDrvIec != NULL)
	#define EXP_CmpIoDrvIecIoDrvGetIecInterface  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvGetIecInterface
	#define EXT_IoDrvGetIecInterface
	#define GET_IoDrvGetIecInterface(fl)  CAL_CMGETAPI( "IoDrvGetIecInterface" ) 
	#define CAL_IoDrvGetIecInterface pICmpIoDrvIec->IIoDrvGetIecInterface
	#define CHK_IoDrvGetIecInterface (pICmpIoDrvIec != NULL)
	#define EXP_IoDrvGetIecInterface  CAL_CMEXPAPI( "IoDrvGetIecInterface" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoDrvGetIecInterface  PFIODRVGETIECINTERFACE pfIoDrvGetIecInterface;
	#define EXT_IoDrvGetIecInterface  extern PFIODRVGETIECINTERFACE pfIoDrvGetIecInterface;
	#define GET_IoDrvGetIecInterface(fl)  s_pfCMGetAPI2( "IoDrvGetIecInterface", (RTS_VOID_FCTPTR *)&pfIoDrvGetIecInterface, (fl), 0, 0)
	#define CAL_IoDrvGetIecInterface  pfIoDrvGetIecInterface
	#define CHK_IoDrvGetIecInterface  (pfIoDrvGetIecInterface != NULL)
	#define EXP_IoDrvGetIecInterface  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoDrvGetIecInterface", (RTS_UINTPTR)IoDrvGetIecInterface, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif


/* <SIL2/> */
typedef struct
{
	IBase_C *pBase;
	PFIODRVREGISTERINSTANCE IIoDrvRegisterInstance;
 	PFIODRVREGISTERINSTANCE2 IIoDrvRegisterInstance2;
 	PFIODRVUNREGISTERINSTANCE IIoDrvUnregisterInstance;
 	PFIODRVGETIECINTERFACE IIoDrvGetIecInterface;
 } ICmpIoDrvIec_C;

#ifdef CPLUSPLUS
class ICmpIoDrvIec : public IBase
{
	public:
		virtual RTS_RESULT CDECL IIoDrvRegisterInstance(iodrviecregisterinstance_struct *p) =0;
		virtual RTS_RESULT CDECL IIoDrvRegisterInstance2(iodrviecregisterinstance2_struct *p) =0;
		virtual RTS_RESULT CDECL IIoDrvUnregisterInstance(iodrviecunregisterinstance_struct *p) =0;
		virtual IBase* CDECL IIoDrvGetIecInterface(RTS_HANDLE hIoDrv, RTS_RESULT *pResult) =0;
};
	#ifndef ITF_CmpIoDrvIec
		#define ITF_CmpIoDrvIec static ICmpIoDrvIec *pICmpIoDrvIec = NULL;
	#endif
	#define EXTITF_CmpIoDrvIec
#else	/*CPLUSPLUS*/
	typedef ICmpIoDrvIec_C		ICmpIoDrvIec;
	#ifndef ITF_CmpIoDrvIec
		#define ITF_CmpIoDrvIec
	#endif
	#define EXTITF_CmpIoDrvIec
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIODRVIECITF_H_*/
