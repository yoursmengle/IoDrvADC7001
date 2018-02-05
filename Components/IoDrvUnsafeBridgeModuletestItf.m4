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

SET_INTERFACE_NAME(`IoDrvUnsafeBridgeModuletest')

REF_ITF(`CmpIoMgrItf.m4')

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
DEF_CREATECLASSITF_API(`RTS_HANDLE', `CDECL', `IoDrvCreate', `(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)')

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
DEF_DELETECLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDelete', `(RTS_HANDLE hIoDrv, RTS_HANDLE hIIoDrv)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvGetInfo', `(RTS_HANDLE hIoDrv, IoDrvInfo **ppInfo)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvGetModuleDiagnosis', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvIdentify', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvReadInputs', `(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvScanModules', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvStartBusCycle', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvUpdateConfiguration', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnectorList, int nCount)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvUpdateMapping', `(RTS_HANDLE hIoDrv, IoConfigTaskMap *pTaskMapList, int nCount)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvWatchdogTrigger', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvWriteOutputs', `(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvReadParameter', `(RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)')

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
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvWriteParameter', `(RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)')
