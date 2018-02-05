 /**
 * <interfacename>CmpTLS</interfacename>
 * <description> 
 *	<p>Interface for TLS encrypted communication over sockets and encrypted CODESYS communication</p>
 *	Limitations:
 *	- Component should only be used to support TLS within the sebserver. Validation of the peer certificate
 *	is not available. So there is no secure way to establish a secure client connection.
 *	- The functions for secure CODESYS communication are only prototypes. They don't have to be used.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */
 
 SET_INTERFACE_NAME(`CmpTls')
REF_ITF(`CmpSrvItf.m4')
REF_ITF(`CmpCryptoItf.m4')

/* Availabe SSL / TLS versions */
#define TLS_METHOD_SSLv2_CLIENT		0x00		/* Not compiled */
#define TLS_METHOD_SSLv3_CLIENT		0x01
#define TLS_METHOD_SSLv23_CLIENT	0x02
#define TLS_METHOD_TLSv1_CLIENT		0x03
#define TLS_METHOD_TLSv2_CLIENT		0x04
#define TLS_METHOD_SSLv2_SERVER		0x05		/* Not compiled */
#define TLS_METHOD_SSLv3_SERVER		0x06
#define TLS_METHOD_SSLv23_SERVER	0x07
#define TLS_METHOD_TLSv1_SERVER		0x08
#define TLS_METHOD_TLSv2_SERVER		0x09
#define TLS_METHOD_LAST_INDEX		0x0A


/* Verification Methods */
#define TLS_VERIFY_NONE					0x01
#define TLS_VERIFY_PEER					0x02
#define TLS_VERIFY_FAIL_IF_NO_PEER_CERT	0x04
#define TLS_VERIFY_CLIENT_ONCE			0x08

/* Versions */
#define TLS_FIRST_RELEASE_MAJOR		1
#define TLS_FIRST_RELEASE_MINOR		0

#define TLS_HIGHEST_SUPPORTED_MAJOR 1
#define TLS_HIGHEST_SUPPORTED_MINOR 0

/* Maximum sizes of TLS records */
#define TLS_MAX_RECORD_SIZE			0x4000
#define TLS_MAX_HEADER_SIZE			0x0158


/**
 * <category>Memory settings</category>
 * <description>Maximum number of allowed TLS connections</description>
 */
#ifndef TLS_MAX_CONNECTION_COUNT
	#define TLS_MAX_CONNECTION_COUNT					100
#endif

/**
 * <category>Memory settings</category>
 * <description>Maximum number of allowed TLS contextes</description>
 */
#ifndef TLS_MAX_CONTEXT_COUNT
	#define TLS_MAX_CONTEXT_COUNT					10
#endif

/**
 * <type>String</type>
 * <description>Path to the base directory of the PKI infrastructure. The path should contain a trailing slash.
 * This setting is only available until a component for managing certificates is available. Will be removed in future!
 * </description>
 */
#define TLSKEY_STR_CERT_STORE_BASE_DIR				"CertStoreBase"
#ifndef TLSVALUE_STR_CERT_STORE_BASE_DIR_DEFAULT
	#define TLSVALUE_STR_CERT_STORE_BASE_DIR_DEFAULT	"./PKI/"
#endif

/* Folder structure inside the PKI infrastructre. Don't change these defines to avoid future compatability issues.*/
#define TLS_CERT_STORE_CERT_DIR		"cert/"
#define TLS_CERT_STORE_PRIVATE_DIR	"private/"
#define TLS_CERT_STORE_TURESTED_DIR	"trusted/"
#define TLS_CERT_STORE_CRL_DIR		"crl/"


/* These settings are used as namespace settings. 
 * Use Namespace.Setting in the config file to set them.
 * If you create a context using the function TlsCreateContext, use the
 * Namespace used in the config file for your context. 
 */

/**
 * <category>Context settings</category>
 * <type>Int</type>
 * <description>Protocol version of TLS or SSL connection. Can be set per context.
 * Select out of the following values:
 *	- SSL v2: not available
 *	- SSLv3: client = 1, server = 6
 *	- Auto selection from SSLv3 to TLS1.2: client = 2, server = 7
 *	- TLSv1.1: client = 3, server = 8
 *	- TLSv1.2: client = 4, server = 9 (default)
</description>
 */
#define TLSKEY_INT_CTX_METHOD							"Method"
#ifndef TLSVALUE_INT_CTX_METHOD_DEFAULT
	#define TLSVALUE_INT_CTX_METHOD_DEFAULT				TLS_METHOD_TLSv2_SERVER
#endif

/**
 * <category>Context settings</category>
 * <type>String</type>
 * <description>Certificate for a context. Value is the filename of the 
 * certificate inside the PKI/cert folder. Supported filetypes are BASE64 
 * encoding an DER encoding. See the manuel for support in generating a private key
 * and the corresponding certificate. (Default = server.cer)</description>
 */
#define TLSKEY_STR_CTX_CERT_FILE						"Cert"
#ifndef TLSVALUE_STR_CTX_CERT_FILE_DEFAULT
	#define TLSVALUE_STR_CTX_CERT_FILE_DEFAULT			"server.cer"
#endif

/**
 * <category>Context settings</category>
 * <type>String</type>
 * <description>Private key of the certificate configured with the "Cert" setting.
 * Value is the filename of the private key inside the PKI/private folder.
 * Supported are BASE64 and DER encodings. (Default = sercer.key)</description>
 */
#define TLSKEY_STR_CTX_PRIVATE_KEY_FILE					"PrivateKey"
#ifndef TLSVALUE_STR_CTX_PRIVATE_KEY_FILE_DEFAULT
	#define TLSVALUE_STR_CTX_PRIVATE_KEY_FILE_DEFAULT	"server.key"
#endif

/**
 * <category>Context settings</category>
 * <type>Int</type>
 * <description>How the verification process at connection establishment is managed: 
 * Behaves different on client or server side:
 * - TLS_VERIFY_NONE (1): The peer side certificate is not checked against the local CAs. Default for server side.
 * - TLS_VERIFY_PEER (2): The peer side certificate is checked against the local CAs. Default on client side
 * - TLS_VERIFY_FAIL_IF_NO_PEER_CERT (4): Fail the verification of the peer send no cert. Server only. Add value to TLS_VERIFY_PEER
 * - TLS_VERIFY_CLIENT_ONCE (8): Verify the client on each renegotiation. Server only. Add value to TLS_VERIFY_PEER.
 * </description>
 */
#define TLSKEY_INT_CTX_VERIFY_MODE						"VerifyMode"

/**
 * <category>Context settings</category>
 * <type>Str</type>
 * <description>A list of availabe cipher suites for the TLS Context.
 * See notation for cipher selection at: http://www.openssl.org/docs/apps/ciphers.html
 * Default selection uses all cipher suites with DiffieHellman key exchange and strong encryption (HIGH+DH).
 * To support the Microsoft Internet Explorer as client this setting should be set to HIGH.
 * ECDH, ECDSA, ECRSA, IDEA, DES, 3DES, JPAKE, Kerberos 5, MD2, MD5 are not supported
 * </description>
 */
#define TLSKEY_STR_CTX_CIPHER_LIST						"CipherList"
#ifndef TLSVALUE_STR_CTX_CIPHER_LIST_DEFAULT
	#define TLSVALUE_STR_CTX_CIPHER_LIST_DEFAULT		"HIGH+DH"
#endif

/**
 * <category>Context settings</category>
 * <type>Str</type>
 * <description>Path to a file im pem format containing the diffie hellman parameters
 * used for DH key excange. These parameters are neede for secure Diffie Hellman key exchange.
 * These parameters may be generated on a seperate fast workstation. The generation will take a while.
 * Use the OpenSSL toolkit to generate these parameters. See the manual. The Value
 * is the filename of these parameters in the PKI/private folder.
 * </description>
 */
#define TLSKEY_STR_CTX_DH_PARAMS						"DHParams"
#ifndef TLSVALUE_STR_CTX_DH_PARAMS_DEFAULT
	#define TLSVALUE_STR_CTX_DH_PARAMS_DEFAULT			"dhparams.pem"
#endif

 
#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Creates a TLS context, needed for creating TLS connections. One context may be used for many TLS 
 connections. A Context contains all the application specific information of the connection. New connections are 
 initialized using a context.</description>
 * <param name="pszNamespace" type="IN">Namespace of the context. Settings of the context are read from the config file.</param>
 * <param name="pResult" type="OUT">Result of this operation.</param>
 * <result>Handle to the created TLS context.</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`TlsCreateContext',`(char* pszNamespace, RTS_RESULT* pResult)')

/**
 * <description>Creates a TLS context, needed for creating TLS connections. One context may be used for many TLS 
 connections. A Context contains all the application specific information of the connection. New connections are 
 initialized using a context.</description>
 * <param name="hCert" type="IN">Certificate used by the TLS connection. If a client connection should be established the certificate is optional.</param>
 * <param name="ui32TlsMethod" type="IN">Mode of the TLS connections. See: TLS_METHOD_... macros</param>
 * <param name="szCipherList" type="IN">Cipher selection of the TLS connection. See CipherList setting for details. If NULL the default of the setting will be used.</param>
 * <param name="i32VerifyMode" type="IN">Verify mode of the TLS connection. See: TLS_VERIFY... macros. Default server: NONE; Default client: VERIFY_PEER.</param>
 * <param name="pResult" type="IN">Result of the operation.</param>
 * <result>Handle to the created TLS context.</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`TlsCreateContext2',`(RTS_HANDLE hCert, RTS_UI32 ui32TlsMethod, char* szCipherList, RTS_I32 i32VerifyMode,  RTS_RESULT* pResult)')

/**
 * <description>Delete the TLS context created using TLSCreateContext</description>
 * <param name="hTlsCtx" type="IN">Handle to the context, that should be deleted</param>
 * <result>Result of this operation.</result>
 */
 DEF_ITF_API(`RTS_RESULT',`CDECL',`TlsFreeContext',`(RTS_HANDLE hTlsContext)')
 
 /**
 * <description>Create a TLS connection around any existing transport media. There are two buffers needed:
 * a send and a receive buffer. Put the data received from the peer to the Rx buffer. The data written by the TLS implementation 
 * will be put to the Tx buffer. This buffer has to be sent to the peer after calling the connect, accept or write functions. Maybe
 * after calling the read function the buffer has to be sent too. This depends on internal TLS protocol stuff (change of 
 * session keys etc) which may occur at any time. This will be indicated through the corresponding returned flag.
 * The TLS connection will be established explicit by calling TSLConnect, or on the server side by calling the Accept function.
 * If the handshaking hasn't finished the read and write functions will internally finish the handshaking until the connection is
 * established. The implementation will start writing at the beginning at each call. If the function indicated that the
 * the data must be sent the next call will overwrite the data in the Tx buffer. So the caller must handle the data before calling
 * the next TLS function. The buffers given here contain raw TLS protocol data. This data has to be transferred to the peer using
 * a reliable way. The packages have to arrive completely and in the right order. Otherwise TLS won't work. 
 * To read or to write the corresponding plain text data use the TlsRead and TlsWrite functions.
 * Handling is done as follows:
 *    Received data: The bytestrings pointer will point to the beginning of the data.
 *                   The bytestrings max length will hold the buffers size
 *                   The bytestrings length will hold the current available amount of data.
 *                   The function ResetRx will not change any of the byte string. Only the internal read position will be set to the beginning of the buffer
 *
 *    Transmit data: The bytestrings pointer will point to the of the empty writing buffer.
 *                   The bytestrings max length will hold the buffer size
 *                   The bytestrings length will contain the amount of data written by the TLS implementation.
 *                   The function ResetTx will reset the internal write position. The length of the byte string will be set to 0.
 *                   To make the handling of the Tx buffer easier the pDataWritten will be set to 1. This indicates that the TLS implementation has written some data.
 * </description>
 * <param name="hSocket" type="IN">The socket handle, used for the TLC connection. The socket should be TCP type and
 * be connected to it's peer.</param>
 * <param name="hTlsCtx" type="IN">Handle to the TLS configuration context. Create by TlsCreateContext or TlsCreateContext2</param>
 * <param name="pRxBuffer" type="IN">Pointer to the buffer containing the data received from the peer.</param>
 * <param name="pTxBuffer" type="IN">Pointer to the buffer containing the data to be sent to the peer.</param>
 * <param name="pResult" type="OUT">Result of this operation. Possible values:
 *		- ERR_OK: The TLS connection was created successful.
 *		- ERR_NOMEMORY: The TLS connection could not be created. No memory available
 *		- ERR_INVALID_HANDLE: The TLS connection could not be created. The given context handle is invalid.
 *      - ERR_PARAMETER: Some parameters where inconsistent or wrong.</param>
 * <result>The handle to the created TLS connection, or RTS_INVALID_HANDLE, if operation failed.</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`TlsBufferOpen',`(RTS_HANDLE hContext, RtsByteString* pRxBuffer, RtsByteString* pTxBuffer, RTS_RESULT* pResult)')

/**
 * <description>This function is used to indicate that the Rx buffer contains new TLS data. Call this function is new data have arrived. All data of the 
 * buffer has to be consumed by the TLS implementation before overwriting the existing data and calling this function. Call TlsRead until the corresponding 
 * error code is returned. If not all data is consumed the TLS stream will be broken and the data can't be decrypted anymore. The Rx buffer will not be changed.
 * </description>
 * <param name="hTlsConn" type="IN">Handle to the TLS connection. Must have been created with TlsBufferOpen</param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`TlsBufferDataReveived',`(RTS_HANDLE hTlsConn)')

/**
 * <description>This function is used to indicate that the data written by the TLS implementation has been sent to the peer. If this function
 * is called the TLS implementation will start writing it's output at the beginning of the Tx buffer again. Call this function if the data of 
 * the Tx buffer has been sent. The length parameter of the Tx buffer will be set to 0.</description>
 * <param name="hTlsConn" type="IN">Handle to the TLS connection. Must have been created with TlsBufferOpen</param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`TlsBufferDataSent',`(RTS_HANDLE hTlsConn)')

/**
 * <description>This function is called to determine if the tx buffer contains data which should be sent to the peer.</description>
 * <param name="hTlsConn" type="IN">Handle to the TLS connection. Must have been created with TlsBufferOpen</param>
 */
DEF_ITF_API(`RTS_BOOL',`CDECL',`TlsBufferDataToSendAvailable',`(RTS_HANDLE hTlsConn)')

/**
 * <description>This function returns the number of written TLS packets since the last call of TlsBufferDataSent.</description>
 * <param name="hTlsConn" type="IN">Handle to the TLS connection. Must have been created with TlsBufferOpen</param>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`TlsBufferNumOfWrittenBlocks',`(RTS_HANDLE hTlsConn)')


/**
 * <description>Starts handshaking on the server side. The client has to initiate the handshaking.
 * This is the first function call on the server side after establishing the underlaying connection.
 * Data has to be received first. This function will is likely to read and write data.</description>
 * <param name="hTlsConn" type="IN">Handle of the TLS connection, created with one of the TLSxxxOpen functions</param>
 * <result>Result of this operation. May be one of these values:
 *		- ERR_OK: No error. Everything worked as expected.
 *		- ERR_NOTINITIALIZED: The TLS component was not initialized properly.
 *		- ERR_TLS_CONNECTION_CLOSED: The TLS connection is closed. Use TlsShutdown to shutdown locally.
 *      - ERR_TLS_WANT_READ: The operation needs to read data from the IO system. There is no data available.
 *      - ERR_TLS_WANT_WRITE: The operation needs to write data to the IO system. This is not possible.
 *		- ERR_TLS_RETRY_OPERATION: Something went wrong. Try the same function call again
 *		- ERR_TLS_IO_SYSTEM: An error in the underlaying IO system.
 *		- ERR_TLS_INTERNAL: An internal Error of the TLS Component
 *		- ERR_FAILED: Unknown error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`TlsAccept',`(RTS_HANDLE hTlsConn)')

/**
 * <description>Starts handshaking on the client side. This data is likely to read and write data</description>
 * <param name="hTlsConn" type="IN">Handle of the TLS connection, created with one of the TLSxxxOpen functions</param>
 * <result>Result of this operation. May be one of these values:
 *		- ERR_OK: No error. Everything worked as expected.
 *		- ERR_NOTINITIALIZED: The TLS component was not initialized properly.
 *		- ERR_TLS_CONNECTION_CLOSED: The TLS connection is closed. Use TlsShutdown to shutdown locally.
 *      - ERR_TLS_WANT_READ: The operation needs to read data from the IO system. There is no data available.
 *      - ERR_TLS_WANT_WRITE: The operation needs to write data to the IO system. This is not possible.
 *		- ERR_TLS_RETRY_OPERATION: Something went wrong. Try the same function call again
 *		- ERR_TLS_IO_SYSTEM: An error in the underlaying IO system.
 *		- ERR_TLS_INTERNAL: An internal Error of the TLS Component
 *		- ERR_FAILED: Unknown error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`TlsConnect',`(RTS_HANDLE hTlsConn)') 

/**
 * <description>Receive data from the encrypted channel. If the connection is not established yet, this will be done
 * transparent in the background. Normally only data is of the encrypted channel is consumed. In some cases (Handshaking has
 * not finished or renegotiation of the session keys) this function will also write data. If the underlaying IO doesn't write
 * automatically the need to send data will be indicated using the corresponding error code.</description>
 * <param name="hTlsConn" type="IN">Handle of the TLS connection, created with one of the TLSxxxOpen functions</param>
 * <param name="pbyData" type="IN">Pointer to a data buffer, where the received data should be written to.</param>
 * <param name="lDataSize" type="IN">Size of pbyData. Maximum number of bytes, that could be received from the TLS connection.</param>
 * <param name="pResult" type="OUT">Result of this operation. May be one of these values:
 *		- ERR_OK: No error. Everything worked as expected.
 *		- ERR_NOTINITIALIZED: The TLS component was not initialized properly.
 *		- ERR_TLS_CONNECTION_CLOSED: The TLS connection is closed. Use TlsShutdown to shutdown locally.
 *      - ERR_TLS_WANT_READ: The operation needs to read data from the IO system. There is no data available.
 *      - ERR_TLS_WANT_WRITE: The operation needs to write data to the IO system. This is not possible. 
 *		- ERR_TLS_RETRY_OPERATION: Something went wrong. Try the same function call again
 *		- ERR_TLS_IO_SYSTEM: An error in the underlaying IO system.
 *		- ERR_TLS_INTERNAL: An internal Error of the TLS Component
 *		- ERR_FAILED: Unknown error.</param>
 * <result>Number of bytes received. 0 if an error occurred.</result>
 */
DEF_ITF_API(`RTS_SSIZE',`CDECL',`TlsRead',`(RTS_HANDLE hTlsConn, RTS_UI8* pbyBuffer, RTS_SSIZE ulBufferSize, RTS_RESULT* pResult)')
 
/**
 * <description>Send data over the encrypted channel. If the connection is not established yet, this will be done
 * transparent in the background. Normally only data is written to the underlaying IO. In some cases data have to be read
 * (Handshaking has not finished or renegotiation of the session keys). If not data is for reading is available this will
 * be indicated through the corresponding error code.</description>
 * <param name="hTlsConn" type="IN">Handle of the TLS connection, created with one of the TLSxxxOpen functions</param>
 * <param name="pbyData" type="IN">Pointer to data, that should be sent over the TLS connection</param>
 * <param name="lDataSize" type="IN">Size of pbyData. Number of bytes that should be sent over the TLS connection</param>
 * <param name="pResult" type="OUT">Result of this operation. May be one of these values:
 *		- ERR_OK: No error. Everything worked as expected.
 *		- ERR_NOTINITIALIZED: The TLS component was not initialized properly.
 *		- ERR_TLS_CONNECTION_CLOSED: The TLS connection is closed. Use TlsShutdown to shutdown locally.
 *      - ERR_TLS_WANT_READ: The operation needs to read data from the IO system. There is no data available.
 *      - ERR_TLS_WANT_WRITE: The operation needs to write data to the IO system. This is not possible. 
 *		- ERR_TLS_RETRY_OPERATION: Something went wrong. Try the same function call again
 *		- ERR_TLS_IO_SYSTEM: An error in the underlaying IO system.
 *		- ERR_TLS_INTERNAL: An internal Error of the TLS Component
 *		- ERR_FAILED: Unknown error.</param>
 * <result>Number of bytes sent. 0 if an error occured.</result>
 */
DEF_ITF_API(`RTS_SSIZE',`CDECL',`TlsWrite',`(RTS_HANDLE hTlsConn, RTS_UI8* pbyData, RTS_SSIZE ulDataSize, RTS_RESULT* pResult)')

/**
 * <description>Shutdown the TLS connection. There are two ways to shutdown the TLS connection:
 * bidirectional: The first call of TlsShutdown will send the shutdown message. The operation will return ERR_TLS_RETRY_OPERATION.
 *             Then the function has to be called again. If the acknowledge of the peer was received ERR_OK will be returned. If the
 *             acknowledge was not received yet the function will return ERR_TLS_WANT_READ.
 *  unidirectional: The first call of TlsShutdown will send the shutdown message. The operation will return ERR_TLS_RETRY_OPERATION.
               Close the IO channel and clean up. Don't wait for the acknowledge of the peer.
 * </description>
 * <param name="hTlsConn" type="IN">Handle of the TLS connection, created with one of the TLSxxxOpen functions</param>
 * <result>Result of this operation. May be one of these values:
 *		- ERR_OK: No error. Everything worked as expected.
 *		- ERR_NOTINITIALIZED: The TLS component was not initialized properly.
 *		- ERR_TLS_CONNECTION_CLOSED: The TLS connection is closed.
 *      - ERR_TLS_WANT_READ: The operation needs to read data from the IO system. There is no data available.
 *      - ERR_TLS_WANT_WRITE: The operation needs to write data to the IO system. This is not possible. 
 *		- ERR_TLS_RETRY_OPERATION: Something went wrong. Try the same function call again
 *		- ERR_TLS_IO_SYSTEM: An error in the underlaying IO system.
 *		- ERR_TLS_INTERNAL: An internal Error of the TLS Component
 *		- ERR_FAILED: Unknown error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`TlsShutdown',`(RTS_HANDLE hTlsConn)')

/**
 * <description>Close the TLS connection. All data will be cleaned up. The handle used for creating the connection will
 * be closed too. No shutdown is done here. This is allowed by the TLS protocol.</description>
 * <param name="hTlsConn" type="IN">Handle of the TLS connection, created with one of the TLSxxxOpen functions</param>
 * <result>Result of this operation. May be one of these values:
 *		- ERR_OK: No error. Everything worked as expected.
 *		- ERR_FAILED: Unknown error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`TlsClose',`(RTS_HANDLE hTlsConn)')

/*
 * <description>Get the certificate of the peer connected to.</description>
 * <param name="hTlsConn" type="IN">Handle of the TLS connection, created with one of the TLSWrap functions</param>
 * <param name="pResult" type="OUT">Result of this operation.</param>
 * <result>A pointer to the certificate received from the peer. NULL, if no certificate could be received. 
 * Check pResult for more information</result>
 */

 /**
  * <description>Add entropy to the PRNG (Pseudo Random Number Generator)of the underlaying TLS implementation.</description>
  * <param name="pui8Buffer" type="IN">Pointer to the data containing the random value</param>
  * <param name="i32BufferSize" type="IN">Size of the input buffer</param>
  * <param name="dEntropy" type="IN">How many bytes of randomness are in the buffer.</param>
  * <result>TRUE: If the channel has be secured already. FALSE: If the channel has net been secured already, or is not a valid channelID</result>
  */
DEF_ITF_API(`void',`CDECL',`TlsRandAdd',`(const RTS_UI8* pui8Buffer, RTS_I32 i32BufferSize, RTS_REAL64 r64Entroy)')

 /**
  * <description>Check if the PRNG has enought entropy to work properly</description>
  * <param name="ui32ChannelId" type="IN"></param>
  * <result>TRUE: If the channel has be secured already. FALSE: If the channel has net been secured already, or is not a valid channelID</result>
  */
DEF_ITF_API(`RTS_BOOL',`CDECL',`TlsRandCheckStatus',`(void)')

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Enum: CmpTlsMethod</description>
 */
#define CMPTLSMETHOD_SSLV2_CLIENT    RTS_IEC_INT_C(0x0)	
#define CMPTLSMETHOD_SSLV3_CLIENT    RTS_IEC_INT_C(0x1)	/* Not Available */
#define CMPTLSMETHOD_SSLV23_CLIENT    RTS_IEC_INT_C(0x2)	/* SSL v3 Client */
#define CMPTLSMETHOD_TLSV1_CLIENT    RTS_IEC_INT_C(0x3)	/* SSL Client accepting all versions but SSL v2 */
#define CMPTLSMETHOD_TLSV2_CLIENT    RTS_IEC_INT_C(0x4)	/* TLS 1.1 Client */
#define CMPTLSMETHOD_SSLV2_SERVER    RTS_IEC_INT_C(0x5)	/* TLS 1.2 Client (Default for CmpTlsCreateContext) */
#define CMPTLSMETHOD_SSLV3_SERVER    RTS_IEC_INT_C(0x6)	/* Not Available */
#define CMPTLSMETHOD_SSLV23_SERVER    RTS_IEC_INT_C(0x7)	/* SSL v3 Server */
#define CMPTLSMETHOD_TLSV1_SERVER    RTS_IEC_INT_C(0x8)	/* SSL Server accepting all versions but SSL v2 */
#define CMPTLSMETHOD_TLSV2_SERVER    RTS_IEC_INT_C(0x9)	/* TLS 1.1 Server
 TLS 1.2 Server */
/* Typed enum definition */
#define CMPTLSMETHOD    RTS_IEC_INT

/**
 * Starts handshaking on the server side. The client has to initiate the handshaking.
 * This is the first function call on the serverside after establishing the unterlaying connection.
 * Data has to be received first. This function will is likley to read and write data.
 *
 * :return: Result of this operation. May be one of these values:
 *		- ERR_OK: No error. Everything worked as expected.
 *		- ERR_NOTINITIALIZED: The TLS component was not initialized proberly.
 *		- ERR_TLS_CONNECTION_CLOSED: The TLS connection is closed. Use TlsShutdown to shutdown locally.
 *     - ERR_TLS_WANT_READ: The operation needs TO read data FROM the IO system. There is no data available.
 *     - ERR_TLS_WANT_WRITE: The operation needs to write data to the IO system. This is not possible.
 *		- ERR_TLS_RETRY_OPERATION: Something went wrong. Try the same function call again
 *		- ERR_TLS_IO_SYSTEM: An error in the unterlaying IO system.
 *		- ERR_TLS_INTERNAL: An internal Error of the TLS Component
 *		- ERR_FAILED: Unknown error.
 */
typedef struct tagcmptlsaccept_struct
{
	RTS_IEC_HANDLE hTlsConn;			/* VAR_INPUT */	/* Handle of the TLS connection, created with one of the TLSxxxOpen functions */
	RTS_IEC_RESULT CmpTlsAccept;		/* VAR_OUTPUT */	
} cmptlsaccept_struct;

DEF_API(`void',`CDECL',`cmptlsaccept',`(cmptlsaccept_struct *p)',1,0xE5016190,0x03050A00)

/**
 * This function is used to indicate that the Rx buffer contains new TLS data. Call this function is new data have arrived. All data of the 
 * buffer has to be consumed by the TLS implementation before overwritting the existing data and calling this funciton. Call TlsRead until the corresponding 
 * error code is returned. If not all data is consumed the TLS stream will be broken and the data can't be decrypted anymore. The Rx buffer will not be changed.
 */
typedef struct tagcmptlsbufferdatareceived_struct
{
	RTS_IEC_HANDLE hTlsConn;			/* VAR_INPUT */	/* Handle to the TLS connection. Must have been created with CmpTlsBufferOpen */
	RTS_IEC_RESULT CmpTlsBufferDataReceived;	/* VAR_OUTPUT */	
} cmptlsbufferdatareceived_struct;

DEF_API(`void',`CDECL',`cmptlsbufferdatareceived',`(cmptlsbufferdatareceived_struct *p)',1,0x613BC278,0x03050A00)

/**
 * This function is used to indicate that the data written by the TLS implementation has been sent to the peer. If this function
 * is called the TLS implementation will start writing it's output at the beginning of the Tx buffer again. Call this function if the data of 
 * the Tx buffer has been sent. The length parameter of the Tx buffer will be set to 0.
 */
typedef struct tagcmptlsbufferdatasent_struct
{
	RTS_IEC_HANDLE hTlsConn;			/* VAR_INPUT */	/* Handle to the TLS connection. Must have been created with CmpTlsBufferOpen */
	RTS_IEC_RESULT CmpTlsBufferDataSent;	/* VAR_OUTPUT */	
} cmptlsbufferdatasent_struct;

DEF_API(`void',`CDECL',`cmptlsbufferdatasent',`(cmptlsbufferdatasent_struct *p)',1,0xA15919C8,0x03050A00)

/**
 * This function is called to determine if the tx buffer contains data which should be sent to the peer.
 */
typedef struct tagcmptlsbufferdatatosendavailable_struct
{
	RTS_IEC_HANDLE hTlsConn;			/* VAR_INPUT */	/* Handle to the TLS connection. Must have been created with CmpTlsBufferOpen */
	RTS_IEC_BOOL CmpTlsBufferDataToSendAvailable;	/* VAR_OUTPUT */	
} cmptlsbufferdatatosendavailable_struct;

DEF_API(`void',`CDECL',`cmptlsbufferdatatosendavailable',`(cmptlsbufferdatatosendavailable_struct *p)',1,0xFC0521B2,0x03050A00)

/**
 * Create a TLS connection around any existing transport media. There are two buffers needed: a send and a receive buffer. 
 * Put the data received from the peer to the Rx buffer. The data written by the TLS implementation 
 * will be put to the Tx buffer. This buffer has to be sent to the peer after calling the connect, accept or write functions. Maybe
 * after calling the read function the buffer has to be sent too. This depends on internal TLS protocol stuff (change of 
 * session keys etc) which may occur at any time. This will be indicated throuth the corresponding returned flag.
 * The TLS connection will be established explicit by calling TSLConnect, or on the server side by calling the Accept function.
 * If the handshaking hasn't finished the read and write functions will internally finish the handshaking until the connection is
 * established. The implementation will start writing at the beginning at each call. If the function indicated that the
 * the data must be sent the next call will overwrite the data in the Tx buffer. So the caller must handle the data before calling
 * the next TLS function. The buffers given here contain raw TLS protocol data. This data has to be transferred to the peer using
 * a reliable way. The packages have to arrive completely and in the right order. Otherwise TLS won't work. 
 * To read or to write the corresponding plaintext data use the TlsRead and TlsWrite functions.
 * Handling is done as follows:
 *    Received data: 
 *		- The bytestrings pointer will point to the beginning of the data.
 *     - The bytestrings max length will hold the buffers size
 *     - The bytestrings length will hold the current available amount of data.
 *     - The function ResetRx will not change any of the byte string. Only the internal read position will be set to the beginning of the buffer
 *
 *    Transmit data: 
 *		- The bytestrings pointer will point to the of the empty writing buffer.
 *     - The bytestrings max length will hold the buffer size
 *     - The bytestrings length will contain the amount of data written by the TLS implementation.
 *     - The function ResetTx will reset the internal write position. The length of the bytestring will be set to 0.
 *
 * :return: The handle to the created TLS connection, or RTS_INVALID_HANDLE, if operation failed.
 */
typedef struct tagcmptlsbufferopen_struct
{
	RTS_IEC_HANDLE hTlsContext;			/* VAR_INPUT */	/* Handle to the TLS configuration context. Create by CmpTlsCreateContext */
	RtsByteString *pRxBuffer;			/* VAR_INPUT */	/* Pointer to the buffer containing the data received from the peer. */
	RtsByteString *pTxBuffer;			/* VAR_INPUT */	/* Pointer to the buffer containing the data to be sent to the peer. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Result of this operation. Possible values:
   - ERR_OK: The TLS connection was created successful.
   - ERR_NOMEMORY: The TLS connection could not be created. No memory available
   - ERR_INVALID_HANDLE: The TLS connection could not be created. The given context handle is invalid.
   - ERR_PARAMETER: Some parameters where inconsistent or wrong. */
	RTS_IEC_HANDLE CmpTlsBufferOpen;	/* VAR_OUTPUT */	
} cmptlsbufferopen_struct;

DEF_API(`void',`CDECL',`cmptlsbufferopen',`(cmptlsbufferopen_struct *p)',1,0x205777BB,0x03050A00)

/**
 * lose the TLS connection. All data will be cleand up. The handle used for creating the connection will
 * be closed too. No shutdown is done here. This is allowed by the TLS protocol.
 *
 * :return: Result of this operation. May be one of these values:
 * 	- ERR_OK: No error. Everything worked as expected.
 * 	- ERR_FAILED: Unknown error.
 */
typedef struct tagcmptlsclose_struct
{
	RTS_IEC_HANDLE hTlsConn;			/* VAR_INPUT */	/* Handle of the TLS connection, created with one of the TLSxxxOpen functions */
	RTS_IEC_RESULT CmpTlsClose;			/* VAR_OUTPUT */	
} cmptlsclose_struct;

DEF_API(`void',`CDECL',`cmptlsclose',`(cmptlsclose_struct *p)',1,0xBD50D496,0x03050A00)

/**
 * Starts handshaking on the client side. This data is likley to read and write data.
 *
 * :return: Result of this operation. May be one of these values:
 *		- ERR_OK: No error. Everything worked as expected.
 *		- ERR_NOTINITIALIZED: The TLS component was not initialized proberly.
 *		- ERR_TLS_CONNECTION_CLOSED: The TLS connection is closed. Use TlsShutdown to shutdown locally.
 *     - ERR_TLS_WANT_READ: The operation needs TO read data FROM the IO system. There is no data available.
 *     - ERR_TLS_WANT_WRITE: The operation needs to write data to the IO system. This is not possible.
 *		- ERR_TLS_RETRY_OPERATION: Something went wrong. Try the same function call again
 *		- ERR_TLS_IO_SYSTEM: An error in the unterlaying IO system.
 *		- ERR_TLS_INTERNAL: An internal Error of the TLS Component
 *		- ERR_FAILED: Unknown error.
 */
typedef struct tagcmptlsconnect_struct
{
	RTS_IEC_HANDLE hTlsConn;			/* VAR_INPUT */	/* Handle of the TLS connection, created with one of the TLSNewConn functions */
	RTS_IEC_RESULT CmpTlsConnect;		/* VAR_OUTPUT */	
} cmptlsconnect_struct;

DEF_API(`void',`CDECL',`cmptlsconnect',`(cmptlsconnect_struct *p)',1,0xE8789C31,0x03050A00)

/**
 * This function create a TLS context. This context is needed to perform TLS communication
 * using the SysSocket2 library. The context contains all informaiton how to handle this
 * TLS connection.
 *
 *
 * :return: Handle to the new accepted socket or RTS_INVALID_HANDLE if failed.
 */
typedef struct tagcmptlscreatecontext_struct
{
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	/* Handle to a certificate. The private key of this certificate has to be available. 
 Can be RTS_INVALID_HANDLE for client connections. If the server requires a client
 certificate the connection will fail in these case. */
	RTS_IEC_INT tlsMethod;				/* VAR_INPUT, Enum: CMPTLSMETHOD */
	RTS_IEC_STRING *cipherList;			/* VAR_INPUT */	/* Allowed chipers used by this connection. Leave 0 to get default. Default will result in 
 ciphers with HIGH encryption strength and Diffie Hellman key exchange. */
	RTS_IEC_DWORD verifyMode;			/* VAR_INPUT */	/* Set up how to verify the peer. The settings differ between client and server.
 See CmpTlsVerifyMode for details. Default results in: Client -> Verify the peer. Server -> Do not Verify Peer
 The options of CmpTlsConstans can be combined by adding them. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Operations Result */
	RTS_IEC_HANDLE CmpTlsCreateContext;	/* VAR_OUTPUT */	
} cmptlscreatecontext_struct;

DEF_API(`void',`CDECL',`cmptlscreatecontext',`(cmptlscreatecontext_struct *p)',1,0x9BD4354C,0x03050A00)

/**
 * This function cleans up the TLS context created with CmpTlsCreateContext.
 */
typedef struct tagcmptlsfreecontext_struct
{
	RTS_IEC_HANDLE hTlsContext;			/* VAR_INPUT */	/* Handle to the context to clean up */
	RTS_IEC_RESULT CmpTlsFreeContext;	/* VAR_OUTPUT */	
} cmptlsfreecontext_struct;

DEF_API(`void',`CDECL',`cmptlsfreecontext',`(cmptlsfreecontext_struct *p)',1,0x4FCCCE44,0x03050A00)

/**
 * Receive data from the encrypted channel. If the connection is not established yet, this will be done
 * transparent in the background. Normally only data is of the encrypted channel is consumed. In some cases (Handshaking has
 * not finished or renegotiation of the session keys) this function will also write data. If the unterlaying IO doens't write
 * automatically the need to send data will be indicated using the corresponding error code.
 *
 * :return: Number of bytes received. 0 if an error occured.
 */
typedef struct tagcmptlsread_struct
{
	RTS_IEC_HANDLE hTlsConn;			/* VAR_INPUT */	/* Handle of the TLS connection, created with one of the TLSxxxOpen functions */
	RTS_IEC_BYTE *pbyBuffer;			/* VAR_INPUT */	/* Pointer to a databuffer, where the received decrypted data should be written to. */
	RTS_IEC_XINT xiBufferSize;			/* VAR_INPUT */	/* Size of pbyData. Maximum number of bytes, that could be received from the TLS connection. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Result OF THIS operation. May be one OF these values:
 	- ERR_OK: No error. Everything worked as expected.
 	- ERR_NOTINITIALIZED: The TLS component was not initialized proberly.
 	- ERR_TLS_CONNECTION_CLOSED: The TLS connection is closed. Use TlsShutdown to shutdown locally.
     - ERR_TLS_WANT_READ: The operation needs TO read data FROM the IO system. There is no data available.
     - ERR_TLS_WANT_WRITE: The operation needs to write data to the IO system. This is not possible.
 	- ERR_TLS_RETRY_OPERATION: Something went wrong. Try the same function call again
 	- ERR_TLS_IO_SYSTEM: An error in the unterlaying IO system.
 	- ERR_TLS_INTERNAL: An internal Error of the TLS Component
 	- ERR_FAILED: Unknown error. */
	RTS_IEC_XINT CmpTlsRead;			/* VAR_OUTPUT */	
} cmptlsread_struct;

DEF_API(`void',`CDECL',`cmptlsread',`(cmptlsread_struct *p)',1,RTSITF_GET_SIGNATURE(0x7869515D, 0xC50DA073),0x03050A00)

/**
 * There are two ways to shutdown the TLS connection:
 * bidirectional: The first call of TlsShutdown will send the shutdown message. The operation will return ERR_TLS_RETRY_OPERATION.
 *             Then the function has to be called again. If the acknowledge of the peer was received ERR_OK will be returned. If the
 *             acknowledge was not received yet the function will return ERR_TLS_WANT_READ.
 * unidirectional: The first call of TlsShutdown will send the shutdown message. The operation will return ERR_TLS_RETRY_OPERATION.
 *             Close the IO channel and clean up. Don't wait for the acknowledge of the peer.
 *
 * :return: Result of this operation. May be one of these values:
 *		- ERR_OK: No error. Everything worked as expected.
 *		- ERR_NOTINITIALIZED: The TLS component was not initialized proberly.
 *		- ERR_TLS_CONNECTION_CLOSED: The TLS connection is closed.
 *     - ERR_TLS_WANT_READ: The operation needs TO read data FROM the IO system. There is no data available.
 *     - ERR_TLS_WANT_WRITE: The operation needs to write data to the IO system. This is not possible.
 *		- ERR_TLS_RETRY_OPERATION: Something went wrong. Try the same function call again
 *		- ERR_TLS_IO_SYSTEM: An error in the unterlaying IO system.
 *		- ERR_TLS_INTERNAL: An internal Error of the TLS Component
 *		- ERR_FAILED: Unknown error.
 */
typedef struct tagcmptlsshutdown_struct
{
	RTS_IEC_HANDLE hTlsConn;			/* VAR_INPUT */	/* Handle of the TLS connection, created with one of the TLSxxxOpen functions */
	RTS_IEC_RESULT CmpTlsShutdown;		/* VAR_OUTPUT */	
} cmptlsshutdown_struct;

DEF_API(`void',`CDECL',`cmptlsshutdown',`(cmptlsshutdown_struct *p)',1,0x2AA5307D,0x03050A00)

/**
 * Send data over the encrypted channel. If the connection is not established yet, this will be done
 * transparent in the background. Normally only data is written to the unterlaying IO. In some cases data have to be read
 * (Handshaking has not finished or renegotiation of the session keys). If not data is for reading is available this will
 * be indicated through the corresponding error code.
 *
 * :return: Number of bytes sent. 0 if an error occured.
 */
typedef struct tagcmptlswrite_struct
{
	RTS_IEC_HANDLE hTlsConn;			/* VAR_INPUT */	/* Handle of the TLS connection, created with one of the TLSxxxOpen functions */
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	/* Pointer to data, that should be sent over the TLS connection */
	RTS_IEC_XINT xiDataSize;			/* VAR_INPUT */	/* Size of pbyData. Number of bytes that should be sent over the TLS connection */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Result OF THIS operation. May be one OF these values:
 	- ERR_OK: No error. Everything worked as expected.
 	- ERR_NOTINITIALIZED: The TLS component was not initialized proberly.
 	- ERR_TLS_CONNECTION_CLOSED: The TLS connection is closed. Use TlsShutdown to shutdown locally.
     - ERR_TLS_WANT_READ: The operation needs TO read data FROM the IO system. There is no data available.
     - ERR_TLS_WANT_WRITE: The operation needs to write data to the IO system. This is not possible.
 	- ERR_TLS_RETRY_OPERATION: Something went wrong. Try the same function call again
 	- ERR_TLS_IO_SYSTEM: An error in the unterlaying IO system.
 	- ERR_TLS_INTERNAL: An internal Error of the TLS Component
 	- ERR_FAILED: Unknown error. */
	RTS_IEC_XINT CmpTlsWrite;			/* VAR_OUTPUT */	
} cmptlswrite_struct;

DEF_API(`void',`CDECL',`cmptlswrite',`(cmptlswrite_struct *p)',1,RTSITF_GET_SIGNATURE(0xA1D9E8A7, 0xF01B2E0C),0x03050A00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
