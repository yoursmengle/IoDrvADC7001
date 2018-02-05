/**
 * <interfacename>SysSocket</interfacename>
 * <description> 
 *	<p>The SysSocket interface is projected to handle access to ethernet socket layer.
 *	TCP, UDP and RAW sockets can be used.</p>
 * </description>
 *
 * <copyright>(c) 2003-2010 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysSocket2')

REF_ITF(`SysSocketItf.m4')

#define SYSSOCK_TYPE_STD	1
#define SYSSOCK_TYPE_TLS	2

#define USE_SYSSOCKET2_STMT					static PF_DELETEINSTANCE2 s_pfCMDeleteInstance2 = NULL;
#define INIT_SYSSOCKET2_STMT(pInitStruct)	{s_pfCMDeleteInstance2 = ((INIT_STRUCT *)pInitStruct)->pfCMDeleteInstance2;}

typedef struct SysSocket_StdSockets_
{
	RTS_I32 i32AddressFamily;
	RTS_I32 i32Type;
	RTS_I32 i32Protocol;
} SysSocket_StdSockets;

typedef struct SysSocket_TlsSockets_
{
	RTS_HANDLE hTlsContext;
} SysSocket_TlsSockets;

typedef union SysSock_SpecificParameter_
{
	SysSocket_StdSockets stdSockets;
	SysSocket_TlsSockets tlsSockets;
} SysSock_SpecificParameter;

typedef struct SysSock_Parameter_
{
	RTS_UI32 ui32Type;
	SysSock_SpecificParameter specific;
} SysSock_Parameter;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Create a socket of the specified class
 * </description>
 * <param name="hISysSocket" type="IN">Pointer to IBase. Is filled by the generate create interface</param>
 * <param name="ClassId" type="IN">ClassID of the SysSocket2 implementation</param>
 * <param name="pParameter" type="IN">Class specific parameters. See SysSock_Parameter for details</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the SysSocket2Itf interface or RTS_INVALID_HANDLE if failed or ClassID not available</result>
 */
DEF_CREATECLASSITF2_API(`RTS_HANDLE', `CDECL', `SysSock2Create', `(RTS_HANDLE hISysSocket, CLASSID ClassId, SysSock_Parameter *pParameter, RTS_RESULT *pResult)')

/**
 * <description>
 *	Close a socket specified by a SysSocket2Itf handle.
 * </description>
 * <param name="hSocket" type="IN">Handle that was created via SysSockCreate2 API function!</param>
 * <result>Error code</result>
 */
DEF_DELETECLASSITF2_API(`RTS_RESULT', `CDECL', `SysSock2Close', `(RTS_HANDLE hSocket)')

/**
 * <description>
 *	Set options of a specified socket
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="iLevel" type="IN">Level of the socket</param>
 * <param name="iOption" type="IN">Socket option command</param>
 * <param name="pcOptionValue" type="IN">Pointer to the option value</param>
 * <param name="iOptionLen" type="IN">Lenght of option value</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`RTS_RESULT',`CDECL',`SysSock2SetOption',`(RTS_HANDLE hSocket, RTS_I32 iLevel, RTS_I32 iOption, char *pcOptionValue, RTS_I32 iOptionLen)')

/**
 * <description>
 *	Get options of a specified socket
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="iLevel" type="IN">Level of the socket</param>
 * <param name="iOption" type="IN">Socket option command</param>
 * <param name="pcOptionValue" type="OUT">Pointer to get the option value</param>
 * <param name="piOptionLen" type="OUT">Pointer to the option length. Real length is returned</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`RTS_RESULT',`CDECL',`SysSock2GetOption',`(RTS_HANDLE hSocket, RTS_I32 iLevel, RTS_I32 iOption, char *pcOptionValue, RTS_I32 *piOptionLen)')

/**
 * <description>
 *	Bind a socket to a socket address and port number
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="pSockAddr" type="IN">Spcket address</param>
 * <param name="iSockAddrSize" type="IN">Size of the socket address structure</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`RTS_RESULT',`CDECL',`SysSock2Bind',`(RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize)')

/**
 * <description>
 *	Listen on a TCP server socket for new connection
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="iMaxConnections" type="IN">Maximum number of connections allowed</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`RTS_RESULT',`CDECL',`SysSock2Listen',`(RTS_HANDLE hSocket, RTS_I32 iMaxConnections)')

/**
 * <description>
 *	Accept the next incoming TCP connection. Returns the socket for the newly created
 *	connection or RTS_INVALID_HANDLE if failed.
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="pSockAddr" type="OUT">Socket address of the client, who is connected</param>
 * <param name="piSockAddrSize" type="INOUT">Pointer to socket address structure</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the new accepted socket</result>
 */
DEF_PRODUCECLASSITF_API_OWNCPP(`RTS_HANDLE',`CDECL',`SysSock2Accept',`(RTS_HANDLE hISysSocket, CLASSID ClassId, RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize, RTS_RESULT *pResult)')

/**
 * <description>
 *	Connect as a client to a TCP server
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="pSockAddr" type="IN">Socket address of the client, who is connected</param>
 * <param name="iSockAddrSize" type="IN">Size of socket address structure</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`RTS_RESULT',`CDECL',`SysSock2Connect',`(RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize)')

/**
 * <description>
 *	Check a number of sockets for activity	
 * </description>
 * <param name="iWidth" type="IN">Number of sockets in the SOCKET_FD_SET structure, so SOCKET_FD_SETSIZE must be used here.</param>
 * <param name="fdRead" type="IN">Read socket</param>
 * <param name="fdWrite" type="IN">Write socket</param>
 * <param name="fdExcept" type="IN">Exception socket</param>
 * <param name="ptvTimeout" type="IN">Pointer to specify the timeout of the operation.
 *	ptvTimeout=NULL:	Infinite wait
 *	ptvTimeout->tv_sec=-1, ptvTimeout->tv_usec=-1:	Infinite wait
 *	ptvTimeout->tv_sec=0, ptvTimeout->tv_usec=0:	No wait</param>
 * <param name="pnReady" type="OUT">Number of sockets that are ready for IO</param>
 * <result>ERR_OK or ERR_SOCK_TIMEDOUT, if timeout expired</result>
 */
DEF_CLASSITF_API(`RTS_RESULT',`CDECL',`SysSock2Select',`(RTS_HANDLE hSocket, RTS_I32 iWidth, SOCKET_FD_SET *fdRead, SOCKET_FD_SET *fdWrite, SOCKET_FD_SET *fdExcept, SOCKET_TIMEVAL *ptvTimeout, RTS_I32 *pnReady)')

/**
 * <description>
 *	Shutdown a socket
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="iHow" type="IN">Specified, which operations are no longer be allowed. See category shutdown flags</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`RTS_RESULT',`CDECL',`SysSock2Shutdown',`(RTS_HANDLE hSocket, RTS_I32 iHow)')

/**
 * <description>
 *	Io-control of a socket
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="iCommand" type="IN">Io-control command</param>
 * <param name="piParameter" type="INOUT">Parameter value of the command</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`RTS_RESULT',`CDECL',`SysSock2Ioctl',`(RTS_HANDLE hSocket, RTS_I32 iCommand, RTS_I32 *piParameter)')

/**
 * <description>
 *	Check if a socket is inside of a set.
 * </description>
 * <param name="hSocket" type="IN">Socket to check. Can be RTS_INVALID_HANDLE to check for an invalid filled set.</param>
 * <param name="pfs" type="IN">Socket Set</param>
 * <result>TRUE if the specified socket is inside the set, FALSE if not</result>
 */
DEF_CLASSITF_API(`RTS_BOOL',`CDECL',`SysSock2FdIsset',`(RTS_HANDLE hSocket, SOCKET_FD_SET *pfs)')

/**
 * <description>
 *	Add a socket to a socket set.
 * </description>
 * <param name="hSocket" type="IN">Socket to add.</param>
 * <param name="pfs" type="IN">Socket Set</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`RTS_RESULT',`CDECL',`SysSock2FdInit',`(RTS_HANDLE hSocket, SOCKET_FD_SET *pfs)')

/* ------------ TCP specific ------------ */

/**
 * <description>
 *	Receive data from a TCP socket
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="pbyBuffer" type="OUT">Buffer to read data from the socket</param>
 * <param name="iBufferSize" type="IN">Maximum length of the buffer</param>
 * <param name="iFlags" type="IN">The flags parameter can be used to influence the behavior of the 
 *	function beyond the options specified for the associated socket. The semantics of this function 
 *	are determined by the socket options and the flags parameter. The latter is constructed by using the
 *	bitwise OR operator with any of the SOCKET_MSG values. See category TCP flags.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Returns number of bytes received. 0 if failed.</result>
 */
DEF_CLASSITF_API(`RTS_SSIZE',`CDECL',`SysSock2Recv',`(RTS_HANDLE hSocket, char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, RTS_RESULT *pResult)')

/**
 * <description>
 *	Sent data to a TCP socket
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="pbyBuffer" type="IN">Buffer with data to sent</param>
 * <param name="iBufferSize" type="IN">Maximum length of the buffer</param>
 * <param name="iFlags" type="IN">The flags parameter can be used to influence the behavior of the 
 *	function beyond the options specified for the associated socket. The semantics of this function 
 *	are determined by the socket options and the flags parameter. The latter is constructed by using the
 *	bitwise OR operator with any of the SOCKET_MSG values.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Returns number of sent bytes. 0 if failed.</result>
 */
DEF_CLASSITF_API(`RTS_SSIZE',`CDECL',`SysSock2Send',`(RTS_HANDLE hSocket, char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, RTS_RESULT *pResult)')

/* ------------ UDP specific ------------ */

/**
 * <description>
 *	Receive a message from a connectionless socket (UDP)
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="pbyBuffer" type="OUT">Buffer to read data from the socket</param>
 * <param name="iBufferSize" type="IN">Maximum length of the buffer</param>
 * <param name="iFlags" type="IN">The flags parameter can be used to influence the behavior of the 
 *	function beyond the options specified for the associated socket. The semantics of this function 
 *	are determined by the socket options and the flags parameter. The latter is constructed by using the
 *	bitwise OR operator with any of the SOCKET_MSG values.</param>
 * <param name="pSockAddr" type="IN">Socket address and port to receive data from</param>
 * <param name="iSockAddrSize" type="IN">Size of socket address structure</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Returns number of bytes received</result>
 */
DEF_CLASSITF_API(`RTS_SSIZE',`CDECL',`SysSock2RecvFrom',`(RTS_HANDLE hSocket, char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize, RTS_RESULT *pResult)')

/**
 * <description>
 *	Send a message over a connectionless socket (UDP)
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="pbyBuffer" type="IN">Buffer with send data</param>
 * <param name="iBufferSize" type="IN">Length of data to send</param>
 * <param name="iFlags" type="IN">The flags parameter can be used to influence the behavior of the 
 *	function beyond the options specified for the associated socket. The semantics of this function 
 *	are determined by the socket options and the flags parameter. The latter is constructed by using the
 *	bitwise OR operator with any of the SOCKET_MSG values.</param>
 * <param name="pSockAddr" type="IN">Socket address and port to sent data to</param>
 * <param name="iSockAddrSize" type="IN">Size of socket address structure</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Returns number of bytes received</result>
 */
DEF_CLASSITF_API(`RTS_SSIZE',`CDECL',`SysSock2SendTo',`(RTS_HANDLE hSocket, char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize, RTS_RESULT *pResult)')

/**
 * <description>
 *	Returns the socket address of the peer to which a socket is connected.
 *  The SysSockGetPeerName function can be used only on a connected socket. 
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="pSockAddr" type="OUT">Socket address of the peer</param>
 * <param name="piSockAddrSize" type="INOUT">Pointer to size of socket address structure</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`RTS_RESULT',`CDECL',`SysSock2GetPeerName',`(RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize)')

/**
 * <description>
 *	Returns the socket address of the local socket.
 *  Usally this function is called to retrieve the local socket address on multihomed hosts or to get 
 *  the local port number in client implemntations. If the socket is not locally bound to an address,
 *  the function will fail until the socket is connected.
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="pSockAddr" type="OUT">Socket address of the local socket</param>
 * <param name="piSockAddrSize" type="INOUT">Pointer to size of socket address structure</param>
 * <result>error code</result>
 */
DEF_CLASSITF_API(`RTS_RESULT',`CDECL',`SysSock2GetSockName',`(RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize)')

/**
 * <description>
 *	Returns the CLASSID of the socket implementation. Is used to detect, which kind of socket implementation is behind the socket handle.
 * </description>
 * <param name="hSocket" type="IN">Handle to the socket</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>CLASSID of the SysSocket2 implementation</result>
 */
DEF_CLASSITF_API(`CLASSID',`CDECL',`SysSock2GetClassId',`(RTS_HANDLE hSocket, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
