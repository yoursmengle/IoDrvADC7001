/**
 * <interfacename>CmpWebServer</interfacename>
 * <description> 
 *	<p>Interface of the web server component.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpWebServer')

REF_ITF(`SysSocketItf.m4')

#include "CmpStd.h"
#include "SysFileItf.h"
#include "CmpSecurityManagerItf.h"

/**
 * <description>WebServer Request Flags.</description>
 */
#define WEBSERVER_GET_REQUEST				0x00000001
#define WEBSERVER_POST_REQUEST				0x00000002
#define WEBSERVER_HEAD_REQUEST				0x00000004
#define WEBSERVER_ASP_REQUEST				0x00000008
#define WEBSERVER_KEEP_ALIVE				0x00000010
#define WEBSERVER_LICENSE_EXPIRED			0x00000020
#define WEBSERVER_IS_MODIFIED_SINCE			0x00000040

/* 
	Only evaluated internally within the webserver. In fact this is an optimization that allows sending 
	small content of POST requests in a BASE64 coded way within the http-header. 
*/
#define WEBSERVER_HEADERONLYCONTENT			0x00000080		
/* 
	Special flag signalling from the WebServer (or a Webserver-WebserverHandlerV3 adaptation) to a Handler-Component that the feature mentioned at
	WEBSERVER_HEADERONLYCONTENT is supported. 
	The intention of this feature is to evaluate the header field "3S-Repl-Content" as a base64 coded content replacement in POST-requests.
	If this header is evaluated correctly, then this flag should be set on all requests forwarded to the handler.
*/
#define WEBSERVER_SUPPORTSHEADERONLYCONTENT	0x00010000


/**
 * <description>WebServer Socket Flags.</description>
 */
#define WEBSERVER_SOCKET_BLOCK				0x00000001
#define WEBSERVER_SOCKET_LISTENING			0x00000002
#define WEBSERVER_SOCKET_READABLE			0x00000004
#define WEBSERVER_SOCKET_WRITEABLE			0x00000008
#define WEBSERVER_SOCKET_EXCEPTION			0x00000010
#define WEBSERVER_SOCKET_CONNRESET			0x00000020
#define WEBSERVER_SOCKET_EAGAIN				0x00000040
#define WEBSERVER_SOCKET_CLOSED				0x00000080
#define WEBSERVER_SOCKET_SENDCONTENT		0x00000100
#define WEBSERVER_SOCKET_READHEADER			0x00000200
#define WEBSERVER_SOCKET_READCONTENT		0x00000400

#define MAX_TYPE_LEN						64
#define MAX_TIME_LEN						64
#ifndef MAX_QUERY_LEN
	#define MAX_QUERY_LEN						255
#endif

typedef struct
{
	RTS_SSIZE		dwSize;					/* File size, we use SSIZE because this is the type we can send directly over sockets */
	RTS_IEC_DWORD	dwTime;					/* Modification time */
} WebServerResponseInfo;

/* 
 *	Per socket connection WebServer request structure
 */
typedef struct WebServerRequest {
	char szPath[MAX_PATH_LEN];
	char szTime[MAX_TIME_LEN];
	char szQuery[MAX_QUERY_LEN];
	void* pMemRequest;
	char* pHeaderBase64Content;		/* valid only if the flag WEBSERVER_HEADERONLYCONTENT is set within dwFlags */
	RTS_SSIZE iRequestMem;
	RTS_SSIZE iRequestRead;
	RTS_SSIZE iRequestLen;
	void* pMemResponse;
	RTS_BOOL bHasResponse;
	RTS_SSIZE iResponseLen;
	RTS_IEC_UDINT udiResponseLastModified;
	RTS_SSIZE iWritten;
	void* pMemRemain;				/* Keeps the remaining content of a file which cannot be sent because of socket E_WOULDBLOCK */
	RTS_SSIZE iRemainLen;
	RTS_UI32 dwFlags;
	RTS_HANDLE				pHandler;
	RTS_HANDLE				pFile;
} WebServerRequest;

typedef struct 
{
	char					pszHostName[64];
	RTS_HANDLE				hSocket;
	CLASSID					socketClassID;
	RTS_UI32				dwStartTime;	/* The start time is used to control timeouts for client requests */
	RTS_UI32				dwFlags;		/* The socket flags and what the socket can do at the moment */
	RTS_UI32				dwHandlerFlags; /* The handler flags keeps the information what the handler wants to do with this socket */
	WebServerRequest*		pRequest;
	RTS_RESULT				LastResult;
	char					szIpAddress[16];		/* holds the ip address of a connected client; might not be assigned for server sockets; at the moment only IPv4 supported */
} WebServerSocket;

/**
 * <description>WebServer memory type - which should be used.</description>
 */
typedef enum WEBSERVER_MEM_TYPEtag
{
	SYSMEM,
	SYSMEMREUSE
} WEBSERVER_MEM_TYPE;

/**
 * <description>WebServer connection type - which sould be used</description>
 * <element name="HTTP_ONLY" type="IN">Only http connections supported [DEFAULT]</element>
 * <element name="HTTPS_ONLY" type="IN">Only https connections supported</element>
 * <element name="HTTP_AND_HTTPS" type="IN">http and https connections supported</element>
 * <element name="REDIRECT_HTTP_TO_HTTPS" type="IN"></element>
 */
typedef enum WEBSERVER_CONNECTION_TYPEtag
{
	HTTP_ONLY,
	HTTPS_ONLY,
	HTTP_AND_HTTPS,
	REDIRECT_HTTP_TO_HTTPS
} WEBSERVER_CONNECTION_TYPE;

/**
 * <category>SecuritySettings</category>
 * <description>All security settings of the webserver. Can be selected in CmpSecurityManager.
 *	NOTE:
 *		Security modes must be ordered in an descending sorting, that the setting with the highest security level is found at the beginning of the list!
 * </description>
 * <element name="HTTPS_ONLY" type="IN">Only https connections supported</element>
 * <element name="REDIRECT_HTTP_TO_HTTPS" type="IN"></element>
 * <element name="HTTP_AND_HTTPS" type="IN">http and https connections supported</element>
 * <element name="HTTP_ONLY" type="IN">Only http connections supported [DEFAULT]</element>
 */
#define RTS_SECURITY_SETTINGS_CMPWEBSERVER		{ \
													{(RTS_I32)HTTPS_ONLY, 0, "HTTPS", "Only https connections supported [HIGHEST SECURITY LEVEL]"},\
													{(RTS_I32)REDIRECT_HTTP_TO_HTTPS, 0, "REDIRECT_HTTP_TO_HTTPS", "Redirection of http to https"},\
													{(RTS_I32)HTTP_AND_HTTPS, CMPSECMAN_FLAGS_DEFAULT, "HTTP, HTTPS", "http and https connections supported"},\
													{(RTS_I32)HTTP_ONLY, 0, "HTTP", "Only http connections supported"}\
												}

#define RTS_CMPWEBSERVER_SECURITY_ID_SERVER				0
#define RTS_CMPWEBSERVER_SECURITY_ID_SELFSIGNEDCERT		RTS_SECURITY_ID_SELFSIGNEDCERT


#ifndef MAX_LEN_APPLNAME
	#define MAX_LEN_APPLNAME			60
#endif


/**
 * <category>Settings</category>
 * <description>The webserver port number</description>
 */
#define CMPWEBSERVER_KEY_PORT								"WebServerPortNr"
#ifndef CMPWEBSERVER_VALUE_PORT_DEFAULT
	#define CMPWEBSERVER_VALUE_PORT_DEFAULT					INT32_C(8080)
#endif

/**
 * <category>Settings</category>
 * <description>The webserver port number for a secure SSL/TLS connection</description>
 */
#define CMPWEBSERVER_KEY_SECUREPORT							"WebServerSecurePortNr"
#ifndef CMPWEBSERVER_VALUE_SECUREPORT_DEFAULT
	#define CMPWEBSERVER_VALUE_SECUREPORT_DEFAULT			INT32_C(443)
#endif

/**
 * <category>Settings</category>
 * <description>Should the webserver open a ssl connection</description>
 */
#define CMPWEBSERVER_CONNECTION_TYPE						"ConnectionType"
#ifndef CMPWEBSERVER_CONNECTION_TYPE_DEFAULT
	#define CMPWEBSERVER_CONNECTION_TYPE_DEFAULT			HTTP_ONLY
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Ip address to which the sockets of the webserver will be bound. If set to a valid ip address, only connection requests received on the
 *  related adapter are accepted by the server. If you want to bind to all addresses, omit all settings named "Local...".
 * </description>
 */
#define CMPWEBSERVER_KEY_LOCALADDRESS						"LocalAddress"
#define CMPWEBSERVER_VALUE_LOCALADDRESS_DEFAULT				""

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>URL of the webserver. This URL will be used for the certificate as common name if HTTPS is activated. If this setting is empty the hostname of the PLC will be used.</description>
 */
#define CMPWEBSERVER_KEY_URL						        "URL"
#ifndef CMPWEBSERVER_VALUE_URL_DEFAULT
    #define CMPWEBSERVER_VALUE_URL_DEFAULT				""
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Name of the network adapter to which the sockets of the webserver will be bound. If set to a valid name, only connection requests received on the
 *  related adapter are accepted by the server. If there is a configuration for "LocalAddress" or "LocalAdapterNameUnicode", this setting will be ignored.
 *	If you want to bind to all addresses, omit all settings named "Local...".
 * </description>
 */
#define CMPWEBSERVER_KEY_LOCALADAPTERNAME					"LocalAdapterName"
#define CMPWEBSERVER_VALUE_LOCALADAPTERNAME_DEFAULT			""

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Name of the network adapter to which the sockets of the webserver will be bound as a UNICODE String. If set to a valid name, only connection requests received on the
 *  related adapter are accepted by the server. If there is a configuration for "LocalAddress", this setting will be ignored.
 *	If you want to bind to all addresses, omit all settings named "Local...".
 * </description>
 */
#define CMPWEBSERVER_KEY_LOCALADAPTERNAMEUNICODE			"LocalAdapterNameUnicode"
#define CMPWEBSERVER_VALUE_LOCALADAPTERNAMEUNICODE_DEFAULT	RTS_WTEXT("")

/**
 * <category>Memory type</category>
 * <description>The webserver memory type which should be used for dynamic memory allocation.</description>
 */
#define CMPWEBSERVER_MEMORY_TYPE							"WebServerMemoryType"
#define CMPWEBSERVER_MEMORY_TYPE_DEFAULT					SYSMEMREUSE

/**
 * <category>Settings</category>
 * <description>The path to the web visualization directory</description>
 */
#define CMPWEBSERVER_KEY_FILE_UPLOAD_DIR					"FileUploadDirectory"

/**
 * <category>Settings</category>
 * <description>The task interval of the webserver task</description>
 */
#define CMPWEBSERVER_KEY_TASKINTERVAL						"TaskInterval"
#define CMPWEBSERVER_VALUE_TASKINTERVAL_DEFAULT				20

/**
 * <category>Settings</category>
 * <description>The timeout for the socket select call.</description>
 */
#define CMPWEBSERVER_KEY_SELECT_TIMEOUT						"SelectTimeout"
#define CMPWEBSERVER_VALUE_SELECT_TIMEOUT_DEFAULT			0

/**
 * <category>Settings</category>
 * <description>The task priority of the webserver task</description>
 */
#define CMPWEBSERVER_KEY_TASKPRIORITY						"TaskPriority"
#define CMPWEBSERVER_VALUE_TASKPRIORITY_DEFAULT				80

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>The startup mechanism used by the webserver. The following values are valid:
	0: The webserver will startup automatically and never shutdown
	1: The webserver will startup automatically with a reference count of 1 that means it can be shutdown by a 
		call to WebServerReleaseRunning
	2: The webserver will startup and shutdown on demand using a referencecounting mechanism</description>
	3: The webserver will startup on demand but never shutdown
 */
#define CMPWEBSERVER_KEY_STARTUPTYPE						"StartupType"
#ifndef CMPWEBSERVER_VALUE_STARTUPTYPE_DEFAULT 
	#define CMPWEBSERVER_VALUE_STARTUPTYPE_DEFAULT			2
#endif


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Setting that allows to define additional mime types for additional file extensions. Default mime type file extension pairs
 * can be overwritten if they are redefined. The pairs must be indexed, multiple pairs can be defined.
 * Example for adding the mime types file extension pairs application/postscript for .ps and application/zip for .zip:
 * AdditionalFileExtension.0=.ps
 * AdditionalMimeType.0=application/postscript
 * AdditionalFileExtension.1=.zip
 * AdditionalMimeType.1=application/zip
 * </description>
 */
#define CMPWEBSERVER_ADDITIONAL_FILE_EXTENSION				"AdditionalFileExtension"
#define	CMPWEBSERVER_ADDITIONAL_MIME_TYPE					"AdditionalMimeType"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> V3 web server dynamic memory management. Attention use this api instead of SysMemAllocData. </description>
 * <param name="ulSize">The webserver request</param>
 * <result>The pointer to the dynamic memory</result>
 */
DEF_API(`void*', `CDECL', `WebServerGetDynamicMem', `(RTS_SIZE ulSize)')

/**
 * <description> V3 web server dynamic memory management. Attention use this api instead of SysMemFreeData. </description>
 * <param name="pMem">The pointer to the dynamic memory</param>
 */
DEF_API(`void', `CDECL', `WebServerFreeDynamicMem', `(void* pMem)')

/**
 * <description> V3 web server startup and shutdown. This function can be called to start the webserver, ie. start listening on the
 *	configured TCP-Port. To allow multiple callers to use this API, the implementation uses a reference counting mechanism.
 *	That means that a caller that requests a start of the webserver using this function should release it using WebServerReleaseRunning
 *	when it is no longer necessary.
 *	A call to this method should not be done before the hook CH_INIT_TASKS</description>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The webserver was started.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">The webserver was already running so only the reference counter was incremented.</errorcode>
 * <result></result>
 */
DEF_API(`RTS_RESULT', `CDECL', `WebServerRequestRunning', `(void)')

/**
 * <description> V3 web server startup and shutdown. This function can be called to shutdown the webserver, ie. stop listening on the
 *	configured TCP-Port. To allow multiple callers to use this API, the implementation uses a reference counting mechanism.
 *	That means that a caller of this method should have called WebServerRequestRunning before.</description>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The webserver was shutdown.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">The reference counter was correctly reduced and the webserver is still running.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The reference counter would become negative and thus the webserver was already shutdown.</errorcode>
 * <result></result>
 */
DEF_API(`RTS_RESULT', `CDECL', `WebServerReleaseRunning', `(void)')

/**
 * <description> Sets the htm file name to use. </description>
  * <param name="pszFileName" type="IN"> contains the htm file name </param>
 */
DEF_API(`void', `CDECL', `WebServerSetDefaultPage', `(char* pszFileName)')

#ifdef __cplusplus
}
#endif

