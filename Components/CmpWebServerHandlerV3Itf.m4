/**
 * <interfacename>CmpWebServerHandlerV3</interfacename>
 * <description> 
 *	<p>Interface of the web server V3 handler component.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpWebServerHandlerV3')

#include "CmpWebServerItf.h"

#ifndef MAX_LEN_APPLNAME
	#define MAX_LEN_APPLNAME					60
#endif

#define WEB_CLIENT_OPENCONNECTION		0x0001
#define WEB_CLIENT_RUN_SERVICE			0x0002
#define WEB_CLIENT_RETRIEVEIPINFO		0x0003
#define WEB_CLIENT_DUMMY				0x0064			/* special service only for performance measurements */

/*
	This flag will be set when the client sends the request in a very simple stringencoded format.
	The format is that each byte is encoded in two subsequent characters where the first byte encodes the 
	higher 4 bit of the byte value and a second byte encodes the lower 4 bits of this byte.
	The encoding is done based on the 'A' character, ie. a nibble with the value 0 will be encoded as 'A' whereas
	a nibble with the value 15 will be encoded as 'P'.

	Please remark that even the protocol header is encoded in this format!

	This simple format was chosed because it is simple to read and write and more or less performant to implement in javascript for
	browsers that do not support binary data (ArrayBuffer, typed arrays).
*/
#define WEB_CLIENT_STRINGENCODED		0x8000000

/**
 * <category>Settings</category>
 * <description>The reconnect time in ms</description>
 */
#define CMPWEBSERVERHANDLERV3_KEY_RECONNECT_WAITTIME			"ReconnectTimeMs"
#define CMPWEBSERVERHANDLERV3_VALUE_RECONNECT_WAITTIME_DEFAULT	INT32_C(5000)

/**
 * <category>Settings</category>
 * <description>Task to close channel after timeout.</description>
 */
#define CMPWEBSERVERHANDLERV3_KEY_WEBSERVERCLOSECHANNEL_PRIORITY				"CloseChannel.TaskPriority"
#define CMPWEBSERVERHANDLERV3_KEY_WEBSERVERCLOSECHANNEL_PRIORITY_DEFAULT		150

/**
 * <category>Settings</category>
 * <description>The timeout time in ms to close the unused webserver channel</description>
 */
#define CMPWEBSERVERHANDLERV3_KEY_WEBSERVERCLOSECHANNEL_WAITTIME				"CloseChannelTimeMs"
#define CMPWEBSERVERHANDLERV3_VALUE_WEBSERVERCLOSECHANNEL_WAITTIME_DEFAULT		INT32_C(60000)

/**
 * <category>Settings</category>
 * <description>Allow file transfer services in the webserver handler. 
 * Attention if the webserver could be accessed by hostile traffic:
 * If this setting is activated (!= 0) a runtime user management should be established to protect access to files. 
 * Additionally the usage of the setting "ForceFilePath" of the component "SysFile" is recommended to restrict access 
 * to folders outside the runtime system environment.</description>
*/

#define CMPWEBSERVERHANDLERV3_KEY_WEBSERVER_ALLOW_FILE_TRANSFER_SERVICES				"AllowFileTransferServices"
#define CMPWEBSERVERHANDLERV3_VALUE_WEBSERVER_ALLOW_FILE_TRANSFER_SERVICES_DEFAULT		0

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> V3 web server service handler. </description>
 * <param name="wr">The webserver request</param>
 * <result>The request flags</result>
 */
DEF_API(`int', `CDECL', `WebServerHandlerV3', `(WebServerSocket* pSocket, char* pszUrlPrefix, char* pszDir, 
						char* pszUrl, char* pszPath, int arg)')

#ifdef __cplusplus
}
#endif
