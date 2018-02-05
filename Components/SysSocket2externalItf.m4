/**
 * <interfacename>SysSocket2</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`SysSocket2external')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Enum: SysSocket2_Type</description>
 */
#define SYSSOCKET2_TYPE_STD    RTS_IEC_INT_C(0x1)	
#define SYSSOCKET2_TYPE_TLS    RTS_IEC_INT_C(0x2)	
/* Typed enum definition */
#define SYSSOCKET2_TYPE    RTS_IEC_INT

/**
 * <description>SysSocket2_StdSockets</description>
 */
typedef struct tagSysSocket2_StdSockets
{
	RTS_IEC_INT i32AddressFamily;		
	RTS_IEC_DINT i32Type;		
	RTS_IEC_DINT i32Protocol;		
} SysSocket2_StdSockets;

/**
 * <description>SysSocket2_TlsSockets</description>
 */
typedef struct tagSysSocket2_TlsSockets
{
	RTS_IEC_HANDLE hTlsContext;		
} SysSocket2_TlsSockets;

/**
 * <description>SysSocket2_SpecificParameter</description>
 */
typedef union
{
	SysSocket2_StdSockets stdSockets;		
	SysSocket2_TlsSockets tlsSockets;		
} SysSocket2_SpecificParameter;

/**
 * This structure represents the parameters to create a specific socket type
 * Set the parameterType to your desired socket type. By now Std or TLS sockets
 * are available.
 * The specifica member contains the parameters needed to create this socket type
 */
typedef struct tagSysSocket2_Parameter
{
	RTS_IEC_INT parameterType;		
	SysSocket2_SpecificParameter specific;		
} SysSocket2_Parameter;

/**
 * | Accept the next incoming TCP connection.
 * | This functions calls the function accept of the operating system, which can accept a request to connect
 *   to a socket. A new descriptor (handle) for the socket is returned. The original socket is reset to the
 *   "listening" state (see SysSockListen).
 *
 * :return: Handle to the new accepted socket or RTS_INVALID_HANDLE if failed.
 */
typedef struct tagsyssock2accept_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	SOCKADDRESS *pSockAddr;				/* VAR_INPUT */	/* Socket address of the client, who is connected */
	RTS_IEC_DINT *pdiSockAddrSize;		/* VAR_INPUT */	/* Pointer to size of socket address structure */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_HANDLE SysSock2Accept;		/* VAR_OUTPUT */	
} syssock2accept_struct;

DEF_API(`void',`CDECL',`syssock2accept',`(syssock2accept_struct *p)',1,0x17C31CE6,0x03050A00)

/**
 * | Bind a socket to a socket address and port number.
 * | This functions calls the function bind of the operating system, which will assign a local address
 *   to a socket that has already been allocated to an address by |SysSock2Create|, but not yet fixed uniquely.
 *   This is usually done previous to a call to functions like |SysSock2Listen| or |SysSock2Accept|.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsyssock2bind_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	SOCKADDRESS *pSockAddr;				/* VAR_INPUT */	/* Spcket address */
	RTS_IEC_DINT diSockAddrSize;		/* VAR_INPUT */	/* Size of the socket address structure */
	RTS_IEC_RESULT SysSock2Bind;		/* VAR_OUTPUT */	
} syssock2bind_struct;

DEF_API(`void',`CDECL',`syssock2bind',`(syssock2bind_struct *p)',1,0x1AA54880,0x03050A00)

/**
 *  | Close a socket.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsyssock2close_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	RTS_IEC_RESULT SysSock2Close;		/* VAR_OUTPUT */	
} syssock2close_struct;

DEF_API(`void',`CDECL',`syssock2close',`(syssock2close_struct *p)',1,0xEE4C98E7,0x03050A00)

/**
 * | Connect as a client to a TCP server.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsyssock2connect_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	SOCKADDRESS *pSockAddr;				/* VAR_INPUT */	/* Socket address of the server to connect to */
	RTS_IEC_DINT diSockAddrSize;		/* VAR_INPUT */	/* Size of socket address structure */
	RTS_IEC_RESULT SysSock2Connect;		/* VAR_OUTPUT */	
} syssock2connect_struct;

DEF_API(`void',`CDECL',`syssock2connect',`(syssock2connect_struct *p)',1,0x482EC7EC,0x03050A00)

/**
 * Create a new socket and return the socket handle.
 * By now STD or TLS sockets are available. Using a STD socket results in the default
 * socket behavior.
 * Using the TLS socket results in a IPv4 TCP socket where the TLC protocol is used. Additional
 * the handshaking until the connection is ready takes some time loger. By default these sockets
 * are created as **nonblocking**. If a blocking behavior is needed this **has to be set explicitly**.
 * :return: A handle to the created socket or INVALID_HANDLE if something went wrong.  
 * The return is a descriptor (handle) of the new socket, which is required as input parameter by other 
 * library functions like |SysSock2Bind|, |SysSock2Connect| etc.
 */
typedef struct tagsyssock2create_struct
{
	SysSocket2_Parameter *pParameter;	/* VAR_INPUT */	/* Class specific parameters. See SysSock_Parameter for details */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_HANDLE SysSock2Create;		/* VAR_OUTPUT */	
} syssock2create_struct;

DEF_API(`void',`CDECL',`syssock2create',`(syssock2create_struct *p)',1,0xF631E049,0x03050A00)

/**
 * | Add a socket to a socket set.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsyssock2fdinit_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Socket to add */
	SOCKET_FD_SET *pfs;					/* VAR_INPUT */	/* Socket Set */
	RTS_IEC_RESULT SysSock2FdInit;		/* VAR_OUTPUT */	
} syssock2fdinit_struct;

DEF_API(`void',`CDECL',`syssock2fdinit',`(syssock2fdinit_struct *p)',1,0xAD038A02,0x03050A00)

/**
 * | Check if a socket is inside of a set.
 * :return: TRUE if it is inside the set, FALSE if not.
 */
typedef struct tagsyssock2fdisset_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Socket to check */
	SOCKET_FD_SET *pfs;					/* VAR_INPUT */	/* Socket Set */
	RTS_IEC_BOOL SysSock2FdIsset;		/* VAR_OUTPUT */	
} syssock2fdisset_struct;

DEF_API(`void',`CDECL',`syssock2fdisset',`(syssock2fdisset_struct *p)',1,0x838C8AA3,0x03050A00)

/**
 * | Set options of a specified socket.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsyssock2getoption_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	RTS_IEC_DINT diLevel;				/* VAR_INPUT */	/* Level of the socket */
	RTS_IEC_DINT diOption;				/* VAR_INPUT */	/* Socket option command */
	RTS_IEC_BYTE *pdiOptionValue;		/* VAR_INPUT */	/* Pointer to the option value */
	RTS_IEC_DINT *pdiOptionLen;			/* VAR_INPUT */	/* Lenght of option value */
	RTS_IEC_RESULT SysSock2GetOption;	/* VAR_OUTPUT */	
} syssock2getoption_struct;

DEF_API(`void',`CDECL',`syssock2getoption',`(syssock2getoption_struct *p)',1,0xE48066F9,0x03050A00)

/**
 * | Returns the socket address of the peer to which a socket is connected.
 * | The SysSockGetPeerName function can be used only on a connected socket. 
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsyssock2getpeername_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	SOCKADDRESS *pSockAddr;				/* VAR_INPUT */	/* Socket address of the peer */
	RTS_IEC_DINT *pdiSockAddrSize;		/* VAR_INPUT */	/* Pointer to size of socket address structure */
	RTS_IEC_RESULT SysSock2GetPeerName;	/* VAR_OUTPUT */	
} syssock2getpeername_struct;

DEF_API(`void',`CDECL',`syssock2getpeername',`(syssock2getpeername_struct *p)',1,0x4D1F4B79,0x03050A00)

/**
 * | Returns the socket address of the local socket.
 * | Usally this function is called to retrieve the local socket address on multihomed hosts or to get 
 *   the local port number in client implemntations. If the socket is neither connected nor locally bound to an address,
 *   the result of the function and the value stored in the object pointed to by pSockAddress is unspecified. 
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsyssock2getsockname_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	SOCKADDRESS *pSockAddr;				/* VAR_INPUT */	/* Socket address of the local socket */
	RTS_IEC_DINT *pdiSockAddrSize;		/* VAR_INPUT */	/* Pointer to size of socket address structure */
	RTS_IEC_RESULT SysSock2GetSockName;	/* VAR_OUTPUT */	
} syssock2getsockname_struct;

DEF_API(`void',`CDECL',`syssock2getsockname',`(syssock2getsockname_struct *p)',1,0xCD3D4AC3,0x03050A00)

/**
 * | Io-control of a socket.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsyssock2ioctl_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	RTS_IEC_DINT diCommand;				/* VAR_INPUT */	/* Io-control command */
	RTS_IEC_DINT *pdiParameter;			/* VAR_INPUT */	/* Parameter value of the command */
	RTS_IEC_RESULT SysSock2Ioctl;		/* VAR_OUTPUT */	
} syssock2ioctl_struct;

DEF_API(`void',`CDECL',`syssock2ioctl',`(syssock2ioctl_struct *p)',1,0xCF1E8764,0x03050A00)

/**
 * | Listen on a TCP server socket for new connection.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsyssock2listen_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	RTS_IEC_DINT diMaxConnections;		/* VAR_INPUT */	/* Maximum number of connections allowed */
	RTS_IEC_RESULT SysSock2Listen;		/* VAR_OUTPUT */	
} syssock2listen_struct;

DEF_API(`void',`CDECL',`syssock2listen',`(syssock2listen_struct *p)',1,0xC76C27A4,0x03050A00)

/**
 * | Receive data from a TCP socket.
 * :return: Number of bytes received. 0 if failed.
 */
typedef struct tagsyssock2recv_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	RTS_IEC_BYTE *pbyBuffer;			/* VAR_INPUT */	/* Buffer to read data from the socket */
	RTS_IEC_XINT diBufferSize;			/* VAR_INPUT */	/* Maximum length of the buffer */
	RTS_IEC_DINT diFlags;				/* VAR_INPUT */	/* | The flags parameter can be used to influence the behavior of the 
	  function beyond the options specified for the associated socket. The semantics of this function 
	  are determined by the socket options and the flags parameter. The latter is constructed by using the
	  bitwise OR operator with any of the SOCKET_MSG values. See category TCP flags. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_XINT SysSock2Recv;			/* VAR_OUTPUT */	
} syssock2recv_struct;

DEF_API(`void',`CDECL',`syssock2recv',`(syssock2recv_struct *p)',1,RTSITF_GET_SIGNATURE(0xB660C00E, 0xC68B1F2F),0x03050A00)

/**
 * | Receive a message from a connectionless socket (UDP).
 * :return: Number of bytes received
 */
typedef struct tagsyssock2recvfrom_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	RTS_IEC_BYTE *pbyBuffer;			/* VAR_INPUT */	/* Buffer to read data from the socket */
	RTS_IEC_XINT diBufferSize;			/* VAR_INPUT */	/* Maximum length of the buffer */
	RTS_IEC_DINT diFlags;				/* VAR_INPUT */	/* | The flags parameter can be used to influence the behavior of the 
	  function beyond the options specified for the associated socket. The semantics of this function 
	  are determined by the socket options and the flags parameter. The latter is constructed by using the
	  bitwise OR operator with any of the SOCKET_MSG values. */
	SOCKADDRESS *pSockAddr;				/* VAR_INPUT */	/* Socket address and port to receive data from */
	RTS_IEC_DINT diSockAddrSize;		/* VAR_INPUT */	/* Size of socket address structure */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_XINT SysSock2RecvFrom;		/* VAR_OUTPUT */	
} syssock2recvfrom_struct;

DEF_API(`void',`CDECL',`syssock2recvfrom',`(syssock2recvfrom_struct *p)',1,RTSITF_GET_SIGNATURE(0x1109A6B6, 0xE3F1F6D3),0x03050A00)

/**
 * | Check a number of sockets for activity. All sockets added to the FD_SETs have to be of the same type (Standard or TLS)
 * :return: Runtime system error code (see CmpErrors.library):
 *		| ERR_OK
 *		| ERR_SOCK_TIMEDOUT, if timeout expired
 */
typedef struct tagsyssock2select_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to one of the socket handles added to the FD Sets. */
	RTS_IEC_DINT diWidth;				/* VAR_INPUT */	/* Number of sockets in the |SOCKET_FD_SET| structure, so |SOCKET_FD_SETSIZE| must be used here. */
	SOCKET_FD_SET *pfdRead;				/* VAR_INPUT */	/* Optional pointer to the structure |SOCKET_FD_SET| defining the socket set
 to be checked for reading. It is also possible to set this parameter to 0. */
	SOCKET_FD_SET *pfdWrite;			/* VAR_INPUT */	/* Optional pointer to the structure |SOCKET_FD_SET| defining the socket set
 to be checked for writing. It is also possible to set this parameter to 0. */
	SOCKET_FD_SET *pfdExcept;			/* VAR_INPUT */	/* Optional pointer to structure |SOCKET_FD_SET| that defines the socket set
 the error state has to be checked. It is also possible to set this parameter to 0. */
	SOCKET_TIMEVAL *ptvTimeout;			/* VAR_INPUT */	/* Pointer to maximum timespan which the function SysSockSelect waits for a response:
 	| ptvTimeout=NULL:	Infinite wait
 	| ptvTimeout->tv_sec=-1, ptvTimeout->tv_usec=-1:	Infinite wait
 	| ptvTimeout->tv_sec=0, ptvTimeout->tv_usec=0:	No wait */
	RTS_IEC_DINT *pdiReady;				/* VAR_INPUT */	/* Number of sockets that are ready for IO */
	RTS_IEC_RESULT SysSock2Select;		/* VAR_OUTPUT */	
} syssock2select_struct;

DEF_API(`void',`CDECL',`syssock2select',`(syssock2select_struct *p)',1,0x027528F5,0x03050A00)

/**
 * | Sent data to a TCP socket.
 * :return: Number of sent bytes. 0 if failed.
 */
typedef struct tagsyssock2send_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	RTS_IEC_BYTE *pbyBuffer;			/* VAR_INPUT */	/* Buffer with data to sent */
	RTS_IEC_XINT diBufferSize;			/* VAR_INPUT */	/* Maximum length of the buffer */
	RTS_IEC_DINT diFlags;				/* VAR_INPUT */	/* | The flags parameter can be used to influence the behavior of the 
	  function beyond the options specified for the associated socket. The semantics of this function 
	  are determined by the socket options and the flags parameter. The latter is constructed by using the
	  bitwise OR operator with any of the SOCKET_MSG values. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_XINT SysSock2Send;			/* VAR_OUTPUT */	
} syssock2send_struct;

DEF_API(`void',`CDECL',`syssock2send',`(syssock2send_struct *p)',1,RTSITF_GET_SIGNATURE(0x92166851, 0xE2FDB770),0x03050A00)

/**
 * | Send a message over a connectionless socket (UDP).
 * :return: Number of bytes received.
 */
typedef struct tagsyssock2sendto_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	RTS_IEC_BYTE *pbyBuffer;			/* VAR_INPUT */	/* Buffer with send data */
	RTS_IEC_XINT diBufferSize;			/* VAR_INPUT */	/* Length of data to send. If diBufferSize = 0 ERR_PARAMETER is returned */
	RTS_IEC_DINT diFlags;				/* VAR_INPUT */	/* | The flags parameter can be used to influence the behavior of the 
	  function beyond the options specified for the associated socket. The semantics of this function 
	  are determined by the socket options and the flags parameter. The latter is constructed by using the
	  bitwise OR operator with any of the SOCKET_MSG values. */
	SOCKADDRESS *pSockAddr;				/* VAR_INPUT */	/* Socket address and port to sent data to */
	RTS_IEC_DINT diSockAddrSize;		/* VAR_INPUT */	/* Size of socket address structure */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_XINT SysSock2SendTo;		/* VAR_OUTPUT */	
} syssock2sendto_struct;

DEF_API(`void',`CDECL',`syssock2sendto',`(syssock2sendto_struct *p)',1,RTSITF_GET_SIGNATURE(0xBC837B5E, 0x5311AA5A),0x03050A00)

/**
 * | Set options of a specified socket.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsyssock2setoption_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	RTS_IEC_DINT diLevel;				/* VAR_INPUT */	/* Level of the socket */
	RTS_IEC_DINT diOption;				/* VAR_INPUT */	/* Socket option command */
	RTS_IEC_BYTE *pdiOptionValue;		/* VAR_INPUT */	/* Pointer to the option value */
	RTS_IEC_DINT diOptionLen;			/* VAR_INPUT */	/* Lenght of option value */
	RTS_IEC_RESULT SysSock2SetOption;	/* VAR_OUTPUT */	
} syssock2setoption_struct;

DEF_API(`void',`CDECL',`syssock2setoption',`(syssock2setoption_struct *p)',1,0x442C7F14,0x03050A00)

/**
 * | Shutdown a socket.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsyssock2shutdown_struct
{
	RTS_IEC_HANDLE hSocket;				/* VAR_INPUT */	/* Handle to the socket */
	RTS_IEC_DINT diHow;					/* VAR_INPUT */	/* Specifies, which operations are no longer be allowed. See shutdown flags. */
	RTS_IEC_RESULT SysSock2Shutdown;	/* VAR_OUTPUT */	
} syssock2shutdown_struct;

DEF_API(`void',`CDECL',`syssock2shutdown',`(syssock2shutdown_struct *p)',1,0x775B849E,0x03050A00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

