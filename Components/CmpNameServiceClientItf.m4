/**
 * <interfacename>CmpNameServiceClient</interfacename>
 * <description> 
 *	External interface for the naming service client
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpNameServiceClient')

#include "CmpNameService.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Timeout in seconds after the CmpChannelClient (Gateway) signals the end of the network scan to the client. 
 *  All further incomming network scan answers for this scan request will be dropped. 
 *  ATTENTION: This timeout should only be adapted, if there are nodes connected to the PLC network, which 
 *  need more than around 6 seconds to handle the scan request and return the answer. The only known reason 
 *  is, that the scan have to be forwarded into another network (non-3S-protocol).
 *  If this timeout must be adapted, you have to check all used clients (CoDeSys, OPC-Server, PLCHandler,
 *  DataServer, ...) if the network scan and finding the nodes still works in a proper way.       
 * </description>
 */
#define NAMESERVICESRVKEY_INT_SCAN_TIME								"ScanTimeSeconds"
#define NAMESERVICESRVVALUE_INT_SCAN_TIME_DEFAULT					10


 /* -- Functions exported to the Router component */

 /** <description> Protocol handler of CmpNameServiceClient.
 *   Attention: Must only be called by CmpRouter to forward an incoming data package.</description>
 * <param name="hRouter" type="IN">Handle of router instance calling this function.
 *   For L4 client implementations, by default it is called by the router instance 0.
 *   For L4 server implementations, it is called by the router instance which has received the package originally.</param>
 * <param name="hNetworkInterface" type="IN">Handle of the network interface receiving originally the package</param>
 * <param name="byServiceId" type="IN">The protocol id of the package</param>
 * <param name="byMessageId" type="IN">The message id of the package</param>
 * <param name="addrSender"	type="IN"> Sender address.
 *   The pointer within will not be valid after this function returns.</param>
 * <param name="addrReceiver" type="IN">
 *   Receiver address (either the address of this node or a broadcast address).
 *   The pointer within will not be valid after this function returns.</param>
 * <param name="pduData" type="IN">
 *   The received data. The data pointer will not be valid after this function returns.</param>
 * <param name="nRouterError" type="IN">
 *   If this value is not ERR_OK, then this message has been generated by an intermediate node in response to a
 *   message previously sent by this node, that could not be delivered.
 *   nRouterError identifies the kind of error that happened.
 *   pduData then contains a detailed error description depending on the kind of error.
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSClientHandleData',`(RTS_HANDLE hRouter, RTS_HANDLE hNetworkInterface, RTS_UI8 byServiceId, RTS_UI8 byMessageId, PEERADDRESS addrSender, PEERADDRESS addrReceiver, PROTOCOL_DATA_UNIT pduData, RTS_RESULT nRouterError)')


/* -- Functions exported to the client */

/**
 * <description>
 *  A callback passed to the nameservice functions, that is called for each found node, on error or completion.
 *  This version can return all fields of name service answer version V1.1 (NSVERSION_FIRST_IMPLEMENTATION).
 * <param name="nResult" type="IN">The result of the call. Might be ERR_OK or ERR_TIMEOUT.</param>
 * <param name="addrNode" type="IN">The address of the responding node.</param>
 * <param name="pNodeInfo" type="IN">Only valid if nResult==ERR_OK and until callback returns.</param>
 * <param name="wVersion" type="IN">Version of the received name service package.</param>
 * <param name="dwRequestID" type="IN">The same value that was passed in to the request.</param>
 * <param name="bComplete" type="IN">Is true, if this was the last answer to the request.</param>
 * <result></result>
 */
typedef void (CDECL *PFHANDLENSRESPONSE) (RTS_RESULT nResult, NODEADDRESS addrNode, NODEINFOPACKED *pNodeInfo, unsigned short wVersion, RTS_HANDLE dwRequestId, int bComplete);

/**
 * <description>
 *	A callback passed to the nameservice functions, that is called for each found node, on error or completion.
 *  This version can return all fields of name service answer versions <= V1.3 (NSVERSION_WITH_ADDRDIFFERENCE).
 * </description>
 * <param name="nResult" type="IN">The result of the call. Might be ERR_OK or ERR_TIMEOUT.</param>
 * <param name="addrNode" type="IN">The address of the responding node.</param>
 * <param name="pNodeInfo2" type="IN">Only valid if nResult==ERR_OK and until callback returns.</param>
 * <param name="wVersion" type="IN">Version of the received name service package.</param>
 * <param name="dwRequestID" type="IN">The same value that was passed in to the request.</param>
 * <param name="bComplete" type="IN">Is true, if this was the last answer to the request.</param>
 * <result></result>
 */
typedef void (CDECL *PFHANDLENSRESPONSE2) (RTS_RESULT nResult, NODEADDRESS addrNode, NODEINFOPACKED2 *pNodeInfo2, unsigned short wVersion, RTS_HANDLE dwRequestId, int bComplete);

/**
 * <description>
 *  A callback passed to the nameservice functions, that is called on for each found node, on error or completion.
 *  This version can return all fields of all name service answer versions. 
 *  Note: For online received name service answers < V4.0, the length of the returned node name, device name and vendor name
 *  may exceed the limits defined for NODEINFOPACKED3.   
 * </description>
 * <param name="nResult" type="IN">The result of the call. Might be ERR_OK or ERR_TIMEOUT.</param>
 * <param name="addrNode" type="IN">The address of the responding node.</param>
 * <param name="pNodeInfo3" type="IN">Only valid if nResult==ERR_OK and until callback returns.</param>
 * <param name="wVersion" type="IN">Version of the received name service package.</param>
 * <param name="byClientBlkDrvType" type="IN">Type of block driver, which has received the name service answer on client side.</param>
 * <param name="dwRequestID" type="IN">The same value that was passed in to the request.</param>
 * <param name="bComplete" type="IN">Is true, if this was the last answer to the request.</param>
 * <result></result>
 */
typedef void (CDECL *PFHANDLENSRESPONSE3) (RTS_RESULT nResult, NODEADDRESS addrNode, NODEINFOPACKED3 *pNodeInfo3, unsigned short wVersion, RTS_UI8 byClientBlkDrvType, RTS_HANDLE dwRequestId, int bComplete);


/**
 * <description>
 *	Retrieve the node information for the node with name pwszName.
 *	The result is returned asynchronously by calling the pfCallback function, as soon as a node answers.
 *  If the node is not unique in the PLC network all nodes with the specified name will answer.
 *  The end of the scan is indicated by calling pfCallback with ERR_TIMEOUT.
 *	In some cases the pfCallback might be called before this function returns. The caller must be prepared
 *	to deal with that situation.
 * </description>
 * <param name="pwszName" type="IN">The name of the node to find</param>
 * <param name="dwRequestId" type="IN">Identifies the request. Parallel running requests should have a unique id. Returned again by the pfCallback function.</param>
 * <param name="pfCallback" type="IN">The function to be called when retrieving an answer.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSResolveName',`(const RTS_WCHAR * pwszName, RTS_HANDLE dwRequestId, PFHANDLENSRESPONSE pfCallback)')

/**
 * <description>
 *  Retrieve the node information for the node with name pwszName.
 *  The result is returned asynchronously by calling the pfCallback function, as soon as a node answers.
 *  If the node is not unique in the PLC network all nodes with the specified name will answer. Setting the parameter
 *  bFinishWithFirstNode to TRUE is useful, if the client want to connect to the first answering node without
 *  waiting for the timeout. Typically this is used, if unique node names in the network are assured.
 *  The end of the scan is only indicated by calling pfCallback with ERR_TIMEOUT, if bFinishWithFirstNode was set to FALSE
 *  or if no node has anwered the request.
 *  In some cases the pfCallback might be called before this function returns. The caller must be prepared
 *  to deal with that situation.
 * </description>
 * <param name="pwszName" type="IN">The name of the node to find</param>
 * <param name="dwTimeout" type="IN">Overall timeout in ms for this operation. If 0, the default NAMESERVICESRVKEY_INT_SCAN_TIME is used.</param>
 * <param name="bFinishWithFirstNode" type="IN">If TRUE, pfCallback will be called only once for this request. Further answering nodes are ignored.</param>
 * <param name="dwRequestId" type="IN">Identifies the request. Parallel running requests should have a unique id. Returned again by the pfCallback3 function.</param>
 * <param name="pfCallback3" type="IN">The function to be called when retrieving an answer.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSResolveName3',`(const RTS_WCHAR * pwszName, RTS_UI32 dwTimeout, RTS_BOOL bFinishWithFirstNode, RTS_HANDLE dwRequestId, PFHANDLENSRESPONSE3 pfCallback3)')

/**
 * <description>
 *	Retrieve the node information for the node with the given address.
 *	The result is returned asynchronously by calling the pfCallback function,
 *	as soon as the node answers. pfCallback will be called only once for this request.
 *	In some cases the pfCallback might be called before this function returns. The caller
 *	must be prepared to deal with that situation.
 * </description>
 * <param name="addrNode" type="IN">Address of the node to find.</param>
 * <param name="dwRequestId" type="IN">Identifies the request. Parallel running requests should have a unique id. Returned again by the pfCallback function.</param>
 * <param name="pfCallback" type="IN">The function to be called when retrieving an answer.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSResolveAddress',`(NODEADDRESS addrNode, RTS_HANDLE dwRequestId, PFHANDLENSRESPONSE pfCallback)')

/**
 * <description>
 *	Retrieve the node information for the node with the given address.
 *	The result is returned asynchronously by calling the pfCallback2 function,
 *	as soon as the node answers. pfCallback2 will be called only once for this request.
 *	In some cases the pfCallback2 might be called before this function returns. The caller
 *	must be prepared to deal with that situation.
 * </description>
 * <param name="addrNode" type="IN">Address of the node to find.</param>
 * <param name="dwRequestId" type="IN">Identifies the request. Parallel running requests should have a unique id. Returned again by the pfCallback2 function.</param>
 * <param name="pfCallback2" type="IN">The function to be called when retrieving an answer.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSResolveAddress2',`(NODEADDRESS addrNode, RTS_HANDLE dwRequestId, PFHANDLENSRESPONSE2 pfCallback2)')

/**
 * <description>
 *  Retrieve the node information for the node with the given address.
 *  The result is returned asynchronously by calling the pfCallback3 function,
 *  as soon as the node answers. pfCallback3 will be called only once for this request.
 *  In some cases the pfCallback3 might be called before this function returns. The caller
 *  must be prepared to deal with that situation.
 * </description>
 * <param name="addrNode" type="IN">Address of the node to find.</param>
 * <param name="dwTimeout" type="IN">Overall timeout in ms for this operation. If 0, the default NAMESERVICESRVKEY_INT_SCAN_TIME is used.</param>
 * <param name="dwRequestId" type="IN">Identifies the request. Parallel running requests should have a unique id. Returned again by the pfCallback3 function.</param>
 * <param name="pfCallback3" type="IN">The function to be called when retrieving an answer.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSResolveAddress3',`(NODEADDRESS addrNode, RTS_UI32 dwTimeout, RTS_HANDLE dwRequestId, PFHANDLENSRESPONSE3 pfCallback3)')

/**
 * <description>
 *	Retrieve the node information for the node with the given block driver address.
 *  This is specified by the block driver type and the address in the local network (e. g. ipaddress and port).
 *  If RTS_BLK_DRV_TYPE_NONE is passed, the function returns the address of the own runtime system.
 *  In this special use case the node info may not contain a valid node info.
 *	The result is returned asynchronously by calling the pfCallback2 function,
 *	as soon as the node answers. pfCallback2 will be called only once for this request.
 *	In some cases the pfCallback2 might be called before this function returns. The caller
 *	must be prepared to deal with that situation.
 * </description>
 * <param name="byBlkDrvType" type="IN">
 *  The type of the block driver, which should should resolve the address. If set to RTS_BLK_DRV_TYPE_NONE, 
 *  the address of the own runtime system is returned.
 * </param>
 * <param name="byFlags" type="IN">
 *  For future use, must be 0.
 * </param>
 * <param name="byAddrBitLength" type="IN">
 *  Bit length of the network address. Must match with the block driver configuration. 
 *  Should be 0, if RTS_BLK_DRV_TYPE_NONE is used to get the own node info.
 * </param>
 * <param name="pNetworkAddr" type="IN">
 *  Local network address of the node to find.
 *  Should be NULL, if RTS_BLK_DRV_TYPE_NONE is used to get the own node info.
 * </param>
 * <param name="dwRequestId" type="IN">
 *  Identifies the request. Returned again by the pfCallback2 function. Parallel running requests should have a unique id.
 * </param>
 * <param name="pfCallback2" type="IN">
 *  The function to be called when retrieving an answer.
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSResolveBlkDrvAddress2',`(RTS_UI8 byBlkDrvType, RTS_UI8 byFlags, RTS_UI8 byAddrBitLength, NETWORKADDRESS *pNetworkAddr, RTS_HANDLE dwRequestId, PFHANDLENSRESPONSE2 pfCallback2)')

/**
 * <description>
 *  Retrieve the node information for the node with the given block driver address.
 *  This is specified by the block driver type and the address in the local network (e. g. ipaddress and port).
 *  If RTS_BLK_DRV_TYPE_NONE is passed, the function returns the address of the own runtime system.
 *  In this special use case the node info may not contain a valid node info.
 *  The result is returned asynchronously by calling the pfCallback3 function,
 *  as soon as the node answers. pfCallback3 will be called only once for this request.
 *  In some cases the pfCallback3 might be called before this function returns. The caller
 *  must be prepared to deal with that situation.
 * </description>
 * <param name="byBlkDrvType" type="IN">
 *  The type of the block driver, which should should resolve the address. If set to RTS_BLK_DRV_TYPE_NONE,
 *  the address of the own runtime system is returned.
 * </param>
 * <param name="byFlags" type="IN">
 *  For future use, must be 0.
 * </param>
 * <param name="byAddrBitLength" type="IN">
 *  Bit length of the network address. Must match with the block driver configuration.
 *  Should be 0, if RTS_BLK_DRV_TYPE_NONE is used to get the own node info.
 * </param>
 * <param name="pNetworkAddr" type="IN">
 *  Local network address of the node to find.
 *  Should be NULL, if RTS_BLK_DRV_TYPE_NONE is used to get the own node info.
 * </param>
 * <param name="dwTimeout" type="IN">
 *  Overall timeout in ms for this operation. If 0, the default NAMESERVICESRVKEY_INT_SCAN_TIME is used.
 * </param>
 * <param name="dwRequestId" type="IN">
 *  Identifies the request. Returned again by the pfCallback3 function. Parallel running requests should have a unique id.
 * </param>
 * <param name="pfCallback3" type="IN">
 *  The function to be called when retrieving an answer.
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSResolveBlkDrvAddress3',`(RTS_UI8 byBlkDrvType, RTS_UI8 byFlags, RTS_UI8 byAddrBitLength, NETWORKADDRESS *pNetworkAddr, RTS_UI32 dwTimeout, RTS_HANDLE dwRequestId, PFHANDLENSRESPONSE3 pfCallback3)')

/**
 * <description>
 *	Retrieve all nodes in the network.
 *	The result is returned asynchronously by calling the pfCallback function
 *	once for every answering node. That means pfCallback will be called an unknown
 *	number of times. bComplete will not resolve to TRUE until nResult is set to ERR_TIMEOUT.
 *	Thus ERR_TIMEOUT is an expected result for this request.
 *	In some cases the pfCallback might be called before this function
 *	returns. The caller must be prepared to deal with that situation.
 * </description>
 * <param name="dwRequestId" type="IN">Identifies the request. Parallel running requests should have a unique id. Returned again by the pfCallback function.</param>
 * <param name="pfCallback" type="IN">The function to be called when retrieving an answer.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSResolveAll',`(RTS_HANDLE dwRequestId, PFHANDLENSRESPONSE pfCallback)')

/**
 * <description>
 *	Retrieve all nodes in the network.
 *	The result is returned asynchronously by calling the pfCallback2 function
 *	once for every answering node. That means pfCallback2 will be called an unknown
 *	number of times. bComplete will not resolve to TRUE until nResult is set to ERR_TIMEOUT.
 *	Thus ERR_TIMEOUT is an expected result for this request.
 *	In some cases the pfCallback2 might be called before this function returns. The caller must
 *	be prepared to deal with that situation.
 * </description>
 * <param name="dwRequestId" type="IN">Identifies the request. Parallel running requests should have a unique id. Returned again by the pfCallback2 function.</param>
 * <param name="pfCallback2" type="IN">The function to be called when retrieving an answer.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSResolveAll2',`(RTS_HANDLE dwRequestId, PFHANDLENSRESPONSE2 pfCallback2)')

/**
 * <description>
 *  Retrieve all nodes in the network.
 *  The result is returned asynchronously by calling the pfCallback3 function
 *  once for every answering node. That means pfCallback3 will be called an unknown
 *  number of times. bComplete will not resolve to TRUE until nResult is set to ERR_TIMEOUT.
 *  Thus ERR_TIMEOUT is an expected result for this request.
 *  In some cases the pfCallback3 might be called before this function returns. The caller must
 *  be prepared to deal with that situation.
 * </description>
 * <param name="dwTimeout" type="IN">Overall timeout in ms for this operation. If 0, the default NAMESERVICESRVKEY_INT_SCAN_TIME is used.</param>
 * <param name="dwRequestId" type="IN">Identifies the request. Parallel running requests should have a unique id. Returned again by the pfCallback3 function.</param>
 * <param name="pfCallback3" type="IN">The function to be called when retrieving an answer.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSResolveAll3',`(RTS_UI32 dwTimeout, RTS_HANDLE dwRequestId, PFHANDLENSRESPONSE3 pfCallback3)')

/**
* <description>
*  With this function the remaining timeout of all NSResolve... functions can be adjusted. The typical use case is to set the
*  timeout to 0, as soon as the expected node has answered. Beside the new timeout the running NSResolve... function is not 
*  affected in its behavior.
* </description>
* <param name="dwRemainingTimeout" type="IN">Remaining timeout in ms for already running resolve request.</param>
* <param name="dwRequestId" type="IN">Id of the request, whose remaining resolve time should be set.</param>
* <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSAdjustResolveTimeout',`(RTS_UI32 dwRemainingTimeout, RTS_HANDLE dwRequestId)')

#ifdef __cplusplus
}
#endif