/**
 * <interfacename>CmpOPCUAServer</interfacename>
 * <description></description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */
 
/*
 * Description of the OPC UA Provider interface. This interface is used to add
 * different data sources to an existing OPC UA server. The OPC UA server calls
 * the provider interface to fullfill the different requests of OPC UA.
 *
 * Version 1.0 of the interface supports the following features of OPC UA.
 * -> Data Access
 *
 */

SET_INTERFACE_NAME(`CmpOPCUAProvider')

/* OPC UA Stack header files */
#include "opcua.h"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Use the nodename of the PLC instead of the device name as display name of the PLC node within the OPC UA namespace.
 * Note: This setting will be used by the CmpOPCUAPROVIDERIecVarAccess.</description>
 */
#define CMPOPCUAPROVIDERIECVARACCESS_KEY_USE_NODENAME               "UseNodeName"
#define CMPOPCUAPROVIDERIECVARACCESS_VALUE_USE_NODENAME_DEFAULT		0

/**
 * <category>viewservices</category>
 * <description>View Services of the provider</description>
 * <element name="ui32SessionID" type="IN">Session ID of the current request</element>
 * <element name="pNodeToBrowse" type="IN">Information for node to browse</element>
 * <element name="pViewDescription" type="IN">Information of the view to browse this node</element>
 * <element name="pReference" type="INOUT">References allocaed by the server. Provider fill this up.</element>
 * <element name="ui32NumNodes" type="INOUT">Number of nodes, first cycle get number of nodes to fill to allocate memory.</element>
 * <element name="ui32CurrentNode" type="INOUT">Current node to fill with data.</element>
 * <element name="ui32MaxNumOfResults" type="IN">Maximum count of result nodes.</element>
 * <element name="hProviderContinueInfo" type="INOUT">Information created by the provider to perform the browsenext operation.</element>
 * <element name="bClearProviderContinureInfo" type="IN">The provider should clear the continuation info.</element>
 * <element name="bFinished" type="OUT">Set by the provider. Set to true if all nodes are added. Indicates that the server can call the next Provider.</element>
 */
typedef struct _OpcUaProvider_BrowseContext
{
	OpcUa_UInt32 ui32SessionID;
	const OpcUa_BrowseDescription *pNodeToBrowse;
	const OpcUa_ViewDescription *pViewDescription;
	OpcUa_ReferenceDescription *pReference;
	OpcUa_UInt32 ui32NumNodes;
	OpcUa_UInt32 ui32CurrentNode;
	OpcUa_UInt32 ui32MaxNumOfResults;
	OpcUa_Handle hProviderContinueInfo;
	OpcUa_Boolean bClearProviderContinureInfo;
	OpcUa_Boolean bFinished;
} OpcUaProvider_BrowseContext;

/**
 * <category>viewservices</category>
 * <description></description>
 * <element name="ui32SessionID" type="IN">Session ID of the current request</element>
 * <element name="pNodeToRegister" type="IN">Node that should be registerd.</element>
 * <element name="pRegisterdNode" type="OUT">Handle for client to access the registerd node. NodeID have to be an integer type.</element>
 */
typedef struct _OpcUaProvider_RegisterNodeContext
{
	OpcUa_UInt32 ui32SessionID;
	const OpcUa_NodeId *pNodeToRegister;
	OpcUa_NodeId *pRegisterdNode;
} OpcUaProvider_RegisterNodeContext;

/**
 * <category>viewservices</category>
 * <description></description>
 * <element name="ui32SessionID" type="IN">Session ID of the current request</element>
 * <element name="pRegisterdNode" type="IN">Handle of the registerd node. All ressources needed to create the handle have to be freed up.</element>
 */
typedef struct _OpcUaProvider_UnregisterNodeContext
{
	OpcUa_UInt32 ui32SessionID;
	const OpcUa_NodeId *pRegisterdNode;
} OpcUaProvider_UnregisterNodeContext;

/**
 * <category>monitoreditemservices</category>
 * <description><p>Monitored Item services of the provider</p>
 * <p>Most parts of the monitored items are managed by the server. The provider is
 * only responsible for sampling the data values. The server manages the other 
 * parts including sampling timers, filtering the results, buffering the values
 * and adding notifications to subscriptions.</p>
 * <p>To keep the performance high no heap operations should be called within the 
 * sampling cycles. All needed memory will be allocated while performing the 
 * CreateMonitoredItem service.</p>
 * <element name="ui32SessionID" type="IN">Session ID of the current request</element>
 * <element name="pItemToCreate" type="IN">Information for node to monitor</element>
 * <element name="pValue" type="OUT">Sampledata value. Created by the provider. Server clones this value.</element>
 * <element name="pProviderInformation" type="OUT">Information of the provider needed to identify the monitored item quickly (Index, Handle).</element>
 */
typedef struct _OpcUaProvider_CreateMonitoredItemContext
{
	OpcUa_UInt32 ui32SessionID;
	const OpcUa_ReadValueId* pItemToCreate;
	OpcUa_DataValue* pValue;
	OpcUa_Void* pProviderInformation;
} OpcUaProvider_CreateMonitoredItemContext;

/**
 * <category>monitoreditemservices</category>
 * <element name="ui32SessionID" type="IN">Session ID of the current request</element>
 * <element name="pProviderInformation" type="IN">Information of item. Free ressources.</element>
 */
typedef struct _OpcUaProvider_DeleteMonitoredItemContext
{
	OpcUa_UInt32 ui32SessionID;
	OpcUa_Void* pProviderInformation;
} OpcUaProvider_DeleteMonitoredItemContext;

/**
 * <category>monitoreditemservices</category>
 * <element name="ui32SessionID" type="IN">Session ID of the current request</element>
 * <element name="pProviderInformation" type="IN">Information of provider created with CreateMonitoredItem.</element>
 * <element name="pDataValue" type="IN">Pointer to datavalue where to store the sample.</element>
 */
typedef struct _OpcUaProvider_SampleMonitoredItemContext
{
	OpcUa_UInt32 ui32SessionID;
	const OpcUa_Void* pProviderInformation;
	OpcUa_DataValue* pDataValue;
} OpcUaProvider_SampleMonitoredItemContext;

/**
 * <category>attributeservices</category>
 * <element name="ui32SessionID" type="IN">Session ID of the current request</element>
 * <element name="pNodeToRead" type="IN">Informaiton of the node to be read. Contains AttributeId and NodeID</element>
 * <element name="eTimestampsToReturn" type="IN">Timestamps to add to the data value.</element>
 * <element name="pDataValue" type="OUT">Pointer to datavalue where to store the values.</element>
 */
typedef struct _OpcUaProvider_ReadContext
{
	OpcUa_UInt32 ui32SessionID;
	const OpcUa_ReadValueId *pNodeToRead;
	OpcUa_TimestampsToReturn eTimestampsToReturn;
	OpcUa_DataValue *pDataValue;
} OpcUaProvider_ReadContext;

/**
 * <category>attributeservices</category>
 * <element name="ui32SessionID" type="IN">Session ID of the current request</element>
 * <element name="pNodeToRead" type="IN">Informaiton of the node to be written. Contains AttributeId, NodeID and value.</element>
 */
typedef struct _OpcUaProvider_WriteContext
{
	OpcUa_UInt32 ui32SessionID;
	const OpcUa_WriteValue *pNodeToWrite;
} OpcUaProvider_WriteContext;

/**
 * <description>Create a new OPC UA provider instance. Is typically internally used by the provider itself</description>
 * <param name="hIOpcUaProvider" type="IN">Handle to the provider interface. Must be 0 and is filled automatically by calling the CAL_OpcUaProviderCreate() macro!</param>
 * <param name="ClassId" type="IN">ClassID of the driver. See "Class IDs" section in CmpItf.h or in the Dep.h file of the provider.</param>
 * <param name="iId" type="IN">Instance number of the provider</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Should return RTS_INVALID_HANDLE</result>
 */
DEF_CREATECLASSITF_API(`RTS_HANDLE', `CDECL', `OpcUaProviderCreate', `(RTS_HANDLE hIOpcUaProvider, CLASSID ClassId, int iId, RTS_RESULT *pResult)')

/**
 * <description>Delete an OPC UA provider instance. Is typically internally used by the provider itself</description>
 * <param name="hOpcUaProvider" type="IN">Handle to the provider instance</param>
 * <result>Should return ERR_NOTIMPLEMENTED</result>
 */
DEF_DELETECLASSITF_API(`RTS_RESULT', `CDECL', `OpcUaProviderDelete', `(RTS_HANDLE hOpcUaProvider)')

/**
 * <description>This function is called by the OPC UA server to initialize the provider. After the call to this function the provider
 * should be ready to be used.</description>
 * <result>Function returns OpcUa_Good if everything went fine. Return OpcUa_Bad if an error occures.</result>
 */
DEF_CLASSITF_API(`OpcUa_StatusCode', `CDECL', `OpcUaProviderInitialize', `(RTS_HANDLE hProvider)')

/**
 * <description>This function is called by the OPC UA server to cleanup the provider. Ressources schould be clean up.</description>
 * <result>Function returns OpcUa_Good if everything went fine. Return OpcUa_Bad if an error occures.</result>
 */
DEF_CLASSITF_API(`OpcUa_StatusCode', `CDECL', `OpcUaProviderCleanup', `(RTS_HANDLE hProvider)')

/**
 * <category>viewservices</category>
 * <description>
 * <p>Function to provide the OPC UA browse function.</p>
 * <p>For a detailed description of the browse service see OPC UA Part 4 chapter 5.8.2</p>
 * <p>This function is called for both OPC UA Browse and OPC UA BrowseNext service. 
 * The needed information to continue browsing is included to a_pContext. The 
 * function have to set the member bFinished of a_pContext to OpcUa_True if no 
 * more nodes have to be added to the result. Set this value to OpcUa_False if 
 * not all nodes are added to the Result. If the client uses the OPC UA 
 * BrowseNext service the provider will be called again, to add the missing 
 * nodes.</p>
 * <p>For the values pReference and ui32NumNodes of a_pContext there is a special 
 * handling. The provider will be called two times. At the first call pReference 
 * will be OpcUa_Null. This call is used to count the number of resulting nodes.
 * The neede memory is allocated by the server and within the second run of 
 * Browse the references can be filled up by the provider. The current index is 
 * part of the context.</p>
 * </description>
 * <param type="INOUT" name="pContext">Browse context. Contains NodeID, Index, Maximum result size...</param>
 * <result>Function returns OpcUa_Good if everything went fine. For OpcUa_Bad... error codes refer to table 21 of OPC UA Part 4</result>
 *
 */
DEF_CLASSITF_API(`OpcUa_StatusCode', `CDECL', `OpcUaProviderBrowse', `(RTS_HANDLE hProvider, OpcUaProvider_BrowseContext *pContext)')

/**
 * <category>monitoreditemservices</category>
 * <description><p>Function to create a monitored item.</p>
 * <p>For a detaild description of the CreateMonitoredItem service see OPC UA Part 4 chapter 5.12.2</p>
 * <p>This function is called while the server runs the CreateMonitoredItems service.
 * The server performs as much as he can. Only the sampling of the values is done
 * by the provider. If this function is called, the provider should check if
 * the requested node is in his datasources. If the value is found the following
 * steps are done:</p>
 *	<p>1. A sample item containg a complete sample of the value is generated. 
 *		The server will use this sample as template. The value is cloned as often
 *		as needed to perform the request of the client</p>
 *	<p>2. The provider should fill up his own information of this data value.
 *		This information is passed to the provider to perform the sampling. It 
 *		should be possible that the provider has direct access to the value 
 *		using the stored informations.</p>
 * <p>The function has to return OpcUa_BadNodeIdUnknown to indicate the the node
 * is not known in the datasources. The next provider will be called then.</p>
 * <param type="INOUT", name="pContext">Create MonitoredItemContext. Contains information about the value to be monitored</param>
 * <result><p>Function returns OpcUa_Good if everything went fine. For OpcUa_Bad... error codes refer to table 38 of OPC UA spec Part 4</p>
 *					<p>The error code OpcUa_BadNodeIdUnknown is used to indicate that the next provider have called.</p>
 * </result>
 */
DEF_CLASSITF_API(`OpcUa_StatusCode', `CDECL', `OpcUaProviderCreateMonitoredItem', `(RTS_HANDLE hProvider, OpcUaProvider_CreateMonitoredItemContext *pContext)')

/**
 * <category>monitoreditemservices</category>
 * <description><p>Function to sample a monitored item.</p>
 * <p>This function is used to sample the item. It should perform as fast as possible.
 * No heap operations have to be used within this function. If reading the data
 * value blocks operation the function should return an error.</p></description>
 * <param type="INOUT", name="pContext">Information of the item to sample. Created by the provider.</param>
 * <result>Function returns OpcUa_Good if everything went fine. For OpcUa_Bad... error codes refer to table 38 of OPC UA spec Part 4</result>
 */
DEF_CLASSITF_API(`OpcUa_StatusCode', `CDECL', `OpcUaProviderDeleteMonitoredItem', `(RTS_HANDLE hProvider, OpcUaProvider_DeleteMonitoredItemContext *pContext)')

/**
 * <category>monitoreditemservices</category>
 * <description><p>This function is used to delete a monitored item</p>
 * <p>This function is used to clean up the monitored items. The provider should
 * clean up the provider specific informations created within the 
 * CreateMonitoredItem function and other stuff dedicated to this item.</p>
 * <p>The DataValues are freed by the server.</p></description>
 * <param type="IN" name="pContext">Information of item to sample.</param>
 * <result>Function returns OpcUa_Good if everything went fine. Return OpcUa_Bad if an error occures.</result>
 */
DEF_CLASSITF_API(`OpcUa_StatusCode', `CDECL', `OpcUaProviderSampleMonitoredItem', `(RTS_HANDLE hProvider, OpcUaProvider_SampleMonitoredItemContext *pContext)')

/**
 * <category>attributeservices</category>
 * <description><p>This function is used to read attributes of the specified node.</p>
 * <p>If the provider is the owner of the specified node it should fill up the value in the ReadContext. If the node is not known to the 
 * provider the provider MUST return OpcUa_BadNodeIdUnknown.</p></description>
 * <param type="IN" name="pContext">Information of item to read.</param>
 * <result>Function returns OpcUa_Good if everything went fine. Return OpcUa_Bad if an error occures.</result>
 */
DEF_CLASSITF_API(`OpcUa_StatusCode', `CDECL', `OpcUaProviderRead', `(RTS_HANDLE hProvider, OpcUaProvider_ReadContext *pContext)')

/**
 * <category>attributeservices</category>
 * <description><p>This function is used to write to a specific node item</p>
 * If the provider is the owner of the speficif node it should write the value to the node if possible. If the node is not known to the 
 * provider the proivder MUST return OpcUa_BadNodeIdUnknown.</description>
 * <param type="IN" name="pContext">Information of node to write.</param>
 * <result>Function returns OpcUa_Good if everything went fine. Return OpcUa_Bad if an error occures.</result>
 */
DEF_CLASSITF_API(`OpcUa_StatusCode', `CDECL', `OpcUaProviderWrite', `(RTS_HANDLE hProvider, OpcUaProvider_WriteContext *pContext)')

#ifdef CPLUSPLUS
extern "C" {
#endif

typedef struct _OpcUaProvider_Info
{
	OpcUa_UInt32 structSize;
	OpcUa_UInt32 providerInterfaceSize;
	OpcUa_UInt32 providerVersion;
	OpcUa_String providerName;
	RTS_HANDLE hProvider;
    CMPID cmpId;                /* Added with V3.5.12.0 */

} OpcUaProvider_Info;

#ifdef CPLUSPLUS
}
#endif
