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

SET_INTERFACE_NAME(`CmpIoDrvIec')

REF_ITF(`CmpIoDrvItf.m4')
REF_ITF(`CmpIoDrvParameterItf.m4')
REF_ITF(`CmpIoDrvParameter2Itf.m4')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`IoDrvRegisterInstance',`(iodrviecregisterinstance_struct *p)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`IoDrvRegisterInstance2',`(iodrviecregisterinstance2_struct *p)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`IoDrvUnregisterInstance',`(iodrviecunregisterinstance_struct *p)')

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
DEF_ITF_API(`IBase*',`CDECL',`IoDrvGetIecInterface',`(RTS_HANDLE hIoDrv, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
