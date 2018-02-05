 /**
 * <interfacename>CmpWebServerHandlerV3</interfacename>
 * <description> 
 *	<p>Interface of the web server V3 handler component.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPWEBSERVERHANDLERV3ITF_H_
#define _CMPWEBSERVERHANDLERV3ITF_H_

#include "CmpStd.h"

 

 




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
int CDECL WebServerHandlerV3(WebServerSocket* pSocket, char* pszUrlPrefix, char* pszDir, 
						char* pszUrl, char* pszPath, int arg);
typedef int (CDECL * PFWEBSERVERHANDLERV3) (WebServerSocket* pSocket, char* pszUrlPrefix, char* pszDir, 
						char* pszUrl, char* pszPath, int arg);
#if defined(CMPWEBSERVERHANDLERV3_NOTIMPLEMENTED) || defined(WEBSERVERHANDLERV3_NOTIMPLEMENTED)
	#define USE_WebServerHandlerV3
	#define EXT_WebServerHandlerV3
	#define GET_WebServerHandlerV3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_WebServerHandlerV3() (int)ERR_NOTIMPLEMENTED
	#define CHK_WebServerHandlerV3  FALSE
	#define EXP_WebServerHandlerV3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_WebServerHandlerV3
	#define EXT_WebServerHandlerV3
	#define GET_WebServerHandlerV3(fl)  CAL_CMGETAPI( "WebServerHandlerV3" ) 
	#define CAL_WebServerHandlerV3  WebServerHandlerV3
	#define CHK_WebServerHandlerV3  TRUE
	#define EXP_WebServerHandlerV3  CAL_CMEXPAPI( "WebServerHandlerV3" ) 
#elif defined(MIXED_LINK) && !defined(CMPWEBSERVERHANDLERV3_EXTERNAL)
	#define USE_WebServerHandlerV3
	#define EXT_WebServerHandlerV3
	#define GET_WebServerHandlerV3(fl)  CAL_CMGETAPI( "WebServerHandlerV3" ) 
	#define CAL_WebServerHandlerV3  WebServerHandlerV3
	#define CHK_WebServerHandlerV3  TRUE
	#define EXP_WebServerHandlerV3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"WebServerHandlerV3", (RTS_UINTPTR)WebServerHandlerV3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpWebServerHandlerV3WebServerHandlerV3
	#define EXT_CmpWebServerHandlerV3WebServerHandlerV3
	#define GET_CmpWebServerHandlerV3WebServerHandlerV3  ERR_OK
	#define CAL_CmpWebServerHandlerV3WebServerHandlerV3  WebServerHandlerV3
	#define CHK_CmpWebServerHandlerV3WebServerHandlerV3  TRUE
	#define EXP_CmpWebServerHandlerV3WebServerHandlerV3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_WebServerHandlerV3
	#define EXT_WebServerHandlerV3
	#define GET_WebServerHandlerV3(fl)  CAL_CMGETAPI( "WebServerHandlerV3" ) 
	#define CAL_WebServerHandlerV3  WebServerHandlerV3
	#define CHK_WebServerHandlerV3  TRUE
	#define EXP_WebServerHandlerV3  CAL_CMEXPAPI( "WebServerHandlerV3" ) 
#else /* DYNAMIC_LINK */
	#define USE_WebServerHandlerV3  PFWEBSERVERHANDLERV3 pfWebServerHandlerV3;
	#define EXT_WebServerHandlerV3  extern PFWEBSERVERHANDLERV3 pfWebServerHandlerV3;
	#define GET_WebServerHandlerV3(fl)  s_pfCMGetAPI2( "WebServerHandlerV3", (RTS_VOID_FCTPTR *)&pfWebServerHandlerV3, (fl), 0, 0)
	#define CAL_WebServerHandlerV3  pfWebServerHandlerV3
	#define CHK_WebServerHandlerV3  (pfWebServerHandlerV3 != NULL)
	#define EXP_WebServerHandlerV3   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"WebServerHandlerV3", (RTS_UINTPTR)WebServerHandlerV3, 0, 0) 
#endif


#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpWebServerHandlerV3_C;

#ifdef CPLUSPLUS
class ICmpWebServerHandlerV3 : public IBase
{
	public:
};
	#ifndef ITF_CmpWebServerHandlerV3
		#define ITF_CmpWebServerHandlerV3 static ICmpWebServerHandlerV3 *pICmpWebServerHandlerV3 = NULL;
	#endif
	#define EXTITF_CmpWebServerHandlerV3
#else	/*CPLUSPLUS*/
	typedef ICmpWebServerHandlerV3_C		ICmpWebServerHandlerV3;
	#ifndef ITF_CmpWebServerHandlerV3
		#define ITF_CmpWebServerHandlerV3
	#endif
	#define EXTITF_CmpWebServerHandlerV3
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPWEBSERVERHANDLERV3ITF_H_*/
