 
	
	
#ifndef _CMPCAASDOSERVERITF_H_
#define _CMPCAASDOSERVERITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "ServerSdo.h"

#ifdef __cplusplus
extern "C" {
#endif


#define	CSS_NO_ERROR				((CAA_ERROR)0)
#define	CSS_FIRST_ERROR				((CAA_ERROR)10600)
#define CSS_ERR_NOT_SUPPORTED		((CAA_ERROR)10601)
#define CSS_ERR_CREATING_HANDLER	((CAA_ERROR)10602)
#define CSS_ERR_NO_MEMORY           ((CAA_ERROR)10603)
#define CSS_ERR_INVALID_HANDLE		((CAA_ERROR)10604)
#define CSS_ERR_WRONG_PARAMETER		((CAA_ERROR)10605)
#define CSS_ERR_INVALID_DRIVER		((CAA_ERROR)10606)
#define CSS_ERR_INVALID_CHANNEL		((CAA_ERROR)10607)
#define CSS_ERR_INTERNAL_ERROR  	((CAA_ERROR)10608)
#define CSS_ERR_TRANSMISSION_ERROR  ((CAA_ERROR)10609)
#define	CSS_LAST_ERROR				((CAA_ERROR)10629)


/**
 * <description>
 *   Opens a CANopen SDO server instance.
 * </description>
 * <param name="hDriver" type="IN">  CAN driver handle the SDO server should operate on. </param>
 * <param name="usiNodeId" type="IN"> CANopen NodeID of SDO server. 'Use values between 1 and 127. </param>
 * <param name="ISDOHandler" type="IN"> SDO Handler interface. Used for getting SDO Read and SDO Write notifications. </param>
 * <param name="ISDOHandler" type="IN"> SDO Handler interface. Used for getting SDO Read and SDO Write notifications. </param>
 * <param name="peError" type="INOUT"> Optional error pointer. </param>
 * <result> SDO server handle </result>
*/
CAA_HANDLE CAAFKT CSS_SDOServerOpen(CAA_HANDLE hDriver, CAA_USINT usiNodeId, CSS_CSDOHandler ISDOHandler, CAA_ERROR* peError);
typedef CAA_HANDLE (CAAFKT * PFCSS_SDOSERVEROPEN) (CAA_HANDLE hDriver, CAA_USINT usiNodeId, CSS_CSDOHandler ISDOHandler, CAA_ERROR* peError);
#if defined(CMPCAASDOSERVER_NOTIMPLEMENTED) || defined(CSS_SDOSERVEROPEN_NOTIMPLEMENTED)
	#define USE_CSS_SDOServerOpen
	#define EXT_CSS_SDOServerOpen
	#define GET_CSS_SDOServerOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CSS_SDOServerOpen(p0,p1,p2,p3)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CSS_SDOServerOpen  FALSE
	#define EXP_CSS_SDOServerOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CSS_SDOServerOpen
	#define EXT_CSS_SDOServerOpen
	#define GET_CSS_SDOServerOpen(fl)  CAL_CMGETAPI( "CSS_SDOServerOpen" ) 
	#define CAL_CSS_SDOServerOpen  CSS_SDOServerOpen
	#define CHK_CSS_SDOServerOpen  TRUE
	#define EXP_CSS_SDOServerOpen  CAL_CMEXPAPI( "CSS_SDOServerOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOSERVER_EXTERNAL)
	#define USE_CSS_SDOServerOpen
	#define EXT_CSS_SDOServerOpen
	#define GET_CSS_SDOServerOpen(fl)  CAL_CMGETAPI( "CSS_SDOServerOpen" ) 
	#define CAL_CSS_SDOServerOpen  CSS_SDOServerOpen
	#define CHK_CSS_SDOServerOpen  TRUE
	#define EXP_CSS_SDOServerOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CSS_SDOServerOpen", (RTS_UINTPTR)CSS_SDOServerOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoServerCSS_SDOServerOpen
	#define EXT_CmpCAASdoServerCSS_SDOServerOpen
	#define GET_CmpCAASdoServerCSS_SDOServerOpen  ERR_OK
	#define CAL_CmpCAASdoServerCSS_SDOServerOpen pICmpCAASdoServer->ICSS_SDOServerOpen
	#define CHK_CmpCAASdoServerCSS_SDOServerOpen (pICmpCAASdoServer != NULL)
	#define EXP_CmpCAASdoServerCSS_SDOServerOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CSS_SDOServerOpen
	#define EXT_CSS_SDOServerOpen
	#define GET_CSS_SDOServerOpen(fl)  CAL_CMGETAPI( "CSS_SDOServerOpen" ) 
	#define CAL_CSS_SDOServerOpen pICmpCAASdoServer->ICSS_SDOServerOpen
	#define CHK_CSS_SDOServerOpen (pICmpCAASdoServer != NULL)
	#define EXP_CSS_SDOServerOpen  CAL_CMEXPAPI( "CSS_SDOServerOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_CSS_SDOServerOpen  PFCSS_SDOSERVEROPEN pfCSS_SDOServerOpen;
	#define EXT_CSS_SDOServerOpen  extern PFCSS_SDOSERVEROPEN pfCSS_SDOServerOpen;
	#define GET_CSS_SDOServerOpen(fl)  s_pfCMGetAPI2( "CSS_SDOServerOpen", (RTS_VOID_FCTPTR *)&pfCSS_SDOServerOpen, (fl), 0, 0)
	#define CAL_CSS_SDOServerOpen  pfCSS_SDOServerOpen
	#define CHK_CSS_SDOServerOpen  (pfCSS_SDOServerOpen != NULL)
	#define EXP_CSS_SDOServerOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CSS_SDOServerOpen", (RTS_UINTPTR)CSS_SDOServerOpen, 0, 0) 
#endif




/**
 * <description>
 *   Opens a legacy CANopen SDO server instance. The legacy implementation uses a wrong CRC implementation for
 *   SDO Block transfer (before 3.5 SP10). Use this function only for compatibility reasons.
 *   Example: The block driver has to use this function to preserve compatibility between different versions of
 *   Gateway and runtime. 
 * </description>
 * <param name="hDriver" type="IN">  CAN driver handle the SDO server should operate on. </param>
 * <param name="usiNodeId" type="IN"> CANopen NodeID of SDO server. 'Use values between 1 and 127. </param>
 * <param name="ISDOHandler" type="IN"> SDO Handler interface. Used for getting SDO Read and SDO Write notifications. </param>
 * <param name="ISDOHandler" type="IN"> SDO Handler interface. Used for getting SDO Read and SDO Write notifications. </param>
 * <param name="peError" type="INOUT"> Optional error pointer. </param>
 * <result> SDO server handle </result>
*/
CAA_HANDLE CAAFKT CSS_SDOServerOpenLegacy(CAA_HANDLE hDriver, CAA_USINT usiNodeId, CSS_CSDOHandler ISDOHandler, CAA_ERROR* peError);
typedef CAA_HANDLE (CAAFKT * PFCSS_SDOSERVEROPENLEGACY) (CAA_HANDLE hDriver, CAA_USINT usiNodeId, CSS_CSDOHandler ISDOHandler, CAA_ERROR* peError);
#if defined(CMPCAASDOSERVER_NOTIMPLEMENTED) || defined(CSS_SDOSERVEROPENLEGACY_NOTIMPLEMENTED)
	#define USE_CSS_SDOServerOpenLegacy
	#define EXT_CSS_SDOServerOpenLegacy
	#define GET_CSS_SDOServerOpenLegacy(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CSS_SDOServerOpenLegacy(p0,p1,p2,p3)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CSS_SDOServerOpenLegacy  FALSE
	#define EXP_CSS_SDOServerOpenLegacy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CSS_SDOServerOpenLegacy
	#define EXT_CSS_SDOServerOpenLegacy
	#define GET_CSS_SDOServerOpenLegacy(fl)  CAL_CMGETAPI( "CSS_SDOServerOpenLegacy" ) 
	#define CAL_CSS_SDOServerOpenLegacy  CSS_SDOServerOpenLegacy
	#define CHK_CSS_SDOServerOpenLegacy  TRUE
	#define EXP_CSS_SDOServerOpenLegacy  CAL_CMEXPAPI( "CSS_SDOServerOpenLegacy" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOSERVER_EXTERNAL)
	#define USE_CSS_SDOServerOpenLegacy
	#define EXT_CSS_SDOServerOpenLegacy
	#define GET_CSS_SDOServerOpenLegacy(fl)  CAL_CMGETAPI( "CSS_SDOServerOpenLegacy" ) 
	#define CAL_CSS_SDOServerOpenLegacy  CSS_SDOServerOpenLegacy
	#define CHK_CSS_SDOServerOpenLegacy  TRUE
	#define EXP_CSS_SDOServerOpenLegacy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CSS_SDOServerOpenLegacy", (RTS_UINTPTR)CSS_SDOServerOpenLegacy, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoServerCSS_SDOServerOpenLegacy
	#define EXT_CmpCAASdoServerCSS_SDOServerOpenLegacy
	#define GET_CmpCAASdoServerCSS_SDOServerOpenLegacy  ERR_OK
	#define CAL_CmpCAASdoServerCSS_SDOServerOpenLegacy pICmpCAASdoServer->ICSS_SDOServerOpenLegacy
	#define CHK_CmpCAASdoServerCSS_SDOServerOpenLegacy (pICmpCAASdoServer != NULL)
	#define EXP_CmpCAASdoServerCSS_SDOServerOpenLegacy  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CSS_SDOServerOpenLegacy
	#define EXT_CSS_SDOServerOpenLegacy
	#define GET_CSS_SDOServerOpenLegacy(fl)  CAL_CMGETAPI( "CSS_SDOServerOpenLegacy" ) 
	#define CAL_CSS_SDOServerOpenLegacy pICmpCAASdoServer->ICSS_SDOServerOpenLegacy
	#define CHK_CSS_SDOServerOpenLegacy (pICmpCAASdoServer != NULL)
	#define EXP_CSS_SDOServerOpenLegacy  CAL_CMEXPAPI( "CSS_SDOServerOpenLegacy" ) 
#else /* DYNAMIC_LINK */
	#define USE_CSS_SDOServerOpenLegacy  PFCSS_SDOSERVEROPENLEGACY pfCSS_SDOServerOpenLegacy;
	#define EXT_CSS_SDOServerOpenLegacy  extern PFCSS_SDOSERVEROPENLEGACY pfCSS_SDOServerOpenLegacy;
	#define GET_CSS_SDOServerOpenLegacy(fl)  s_pfCMGetAPI2( "CSS_SDOServerOpenLegacy", (RTS_VOID_FCTPTR *)&pfCSS_SDOServerOpenLegacy, (fl), 0, 0)
	#define CAL_CSS_SDOServerOpenLegacy  pfCSS_SDOServerOpenLegacy
	#define CHK_CSS_SDOServerOpenLegacy  (pfCSS_SDOServerOpenLegacy != NULL)
	#define EXP_CSS_SDOServerOpenLegacy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CSS_SDOServerOpenLegacy", (RTS_UINTPTR)CSS_SDOServerOpenLegacy, 0, 0) 
#endif




/**
 * <description>
 *   Closes a SDO server and releases all resources.
 * </description>
 * <param name="hServer" type="IN">  SDO server handle </param>
 * <result> CSS_NO_ERROR if closing was successful. </result>
*/
CAA_ERROR CAAFKT CSS_SDOServerClose(CAA_HANDLE hServer);
typedef CAA_ERROR (CAAFKT * PFCSS_SDOSERVERCLOSE) (CAA_HANDLE hServer);
#if defined(CMPCAASDOSERVER_NOTIMPLEMENTED) || defined(CSS_SDOSERVERCLOSE_NOTIMPLEMENTED)
	#define USE_CSS_SDOServerClose
	#define EXT_CSS_SDOServerClose
	#define GET_CSS_SDOServerClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CSS_SDOServerClose(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CSS_SDOServerClose  FALSE
	#define EXP_CSS_SDOServerClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CSS_SDOServerClose
	#define EXT_CSS_SDOServerClose
	#define GET_CSS_SDOServerClose(fl)  CAL_CMGETAPI( "CSS_SDOServerClose" ) 
	#define CAL_CSS_SDOServerClose  CSS_SDOServerClose
	#define CHK_CSS_SDOServerClose  TRUE
	#define EXP_CSS_SDOServerClose  CAL_CMEXPAPI( "CSS_SDOServerClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOSERVER_EXTERNAL)
	#define USE_CSS_SDOServerClose
	#define EXT_CSS_SDOServerClose
	#define GET_CSS_SDOServerClose(fl)  CAL_CMGETAPI( "CSS_SDOServerClose" ) 
	#define CAL_CSS_SDOServerClose  CSS_SDOServerClose
	#define CHK_CSS_SDOServerClose  TRUE
	#define EXP_CSS_SDOServerClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CSS_SDOServerClose", (RTS_UINTPTR)CSS_SDOServerClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoServerCSS_SDOServerClose
	#define EXT_CmpCAASdoServerCSS_SDOServerClose
	#define GET_CmpCAASdoServerCSS_SDOServerClose  ERR_OK
	#define CAL_CmpCAASdoServerCSS_SDOServerClose pICmpCAASdoServer->ICSS_SDOServerClose
	#define CHK_CmpCAASdoServerCSS_SDOServerClose (pICmpCAASdoServer != NULL)
	#define EXP_CmpCAASdoServerCSS_SDOServerClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CSS_SDOServerClose
	#define EXT_CSS_SDOServerClose
	#define GET_CSS_SDOServerClose(fl)  CAL_CMGETAPI( "CSS_SDOServerClose" ) 
	#define CAL_CSS_SDOServerClose pICmpCAASdoServer->ICSS_SDOServerClose
	#define CHK_CSS_SDOServerClose (pICmpCAASdoServer != NULL)
	#define EXP_CSS_SDOServerClose  CAL_CMEXPAPI( "CSS_SDOServerClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_CSS_SDOServerClose  PFCSS_SDOSERVERCLOSE pfCSS_SDOServerClose;
	#define EXT_CSS_SDOServerClose  extern PFCSS_SDOSERVERCLOSE pfCSS_SDOServerClose;
	#define GET_CSS_SDOServerClose(fl)  s_pfCMGetAPI2( "CSS_SDOServerClose", (RTS_VOID_FCTPTR *)&pfCSS_SDOServerClose, (fl), 0, 0)
	#define CAL_CSS_SDOServerClose  pfCSS_SDOServerClose
	#define CHK_CSS_SDOServerClose  (pfCSS_SDOServerClose != NULL)
	#define EXP_CSS_SDOServerClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CSS_SDOServerClose", (RTS_UINTPTR)CSS_SDOServerClose, 0, 0) 
#endif




/**
 * <description>
 *   Triggers a cycle for the SDO server. Call this function cyclic!
 * </description>
 * <param name="hServer" type="IN">  SDO server handle </param>
 * <result> CSS_NO_ERROR if no error occurred. </result>
*/
CAA_ERROR CAAFKT CSS_SDOServerDoCycle(CAA_HANDLE hServer);
typedef CAA_ERROR (CAAFKT * PFCSS_SDOSERVERDOCYCLE) (CAA_HANDLE hServer);
#if defined(CMPCAASDOSERVER_NOTIMPLEMENTED) || defined(CSS_SDOSERVERDOCYCLE_NOTIMPLEMENTED)
	#define USE_CSS_SDOServerDoCycle
	#define EXT_CSS_SDOServerDoCycle
	#define GET_CSS_SDOServerDoCycle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CSS_SDOServerDoCycle(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CSS_SDOServerDoCycle  FALSE
	#define EXP_CSS_SDOServerDoCycle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CSS_SDOServerDoCycle
	#define EXT_CSS_SDOServerDoCycle
	#define GET_CSS_SDOServerDoCycle(fl)  CAL_CMGETAPI( "CSS_SDOServerDoCycle" ) 
	#define CAL_CSS_SDOServerDoCycle  CSS_SDOServerDoCycle
	#define CHK_CSS_SDOServerDoCycle  TRUE
	#define EXP_CSS_SDOServerDoCycle  CAL_CMEXPAPI( "CSS_SDOServerDoCycle" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOSERVER_EXTERNAL)
	#define USE_CSS_SDOServerDoCycle
	#define EXT_CSS_SDOServerDoCycle
	#define GET_CSS_SDOServerDoCycle(fl)  CAL_CMGETAPI( "CSS_SDOServerDoCycle" ) 
	#define CAL_CSS_SDOServerDoCycle  CSS_SDOServerDoCycle
	#define CHK_CSS_SDOServerDoCycle  TRUE
	#define EXP_CSS_SDOServerDoCycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CSS_SDOServerDoCycle", (RTS_UINTPTR)CSS_SDOServerDoCycle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoServerCSS_SDOServerDoCycle
	#define EXT_CmpCAASdoServerCSS_SDOServerDoCycle
	#define GET_CmpCAASdoServerCSS_SDOServerDoCycle  ERR_OK
	#define CAL_CmpCAASdoServerCSS_SDOServerDoCycle pICmpCAASdoServer->ICSS_SDOServerDoCycle
	#define CHK_CmpCAASdoServerCSS_SDOServerDoCycle (pICmpCAASdoServer != NULL)
	#define EXP_CmpCAASdoServerCSS_SDOServerDoCycle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CSS_SDOServerDoCycle
	#define EXT_CSS_SDOServerDoCycle
	#define GET_CSS_SDOServerDoCycle(fl)  CAL_CMGETAPI( "CSS_SDOServerDoCycle" ) 
	#define CAL_CSS_SDOServerDoCycle pICmpCAASdoServer->ICSS_SDOServerDoCycle
	#define CHK_CSS_SDOServerDoCycle (pICmpCAASdoServer != NULL)
	#define EXP_CSS_SDOServerDoCycle  CAL_CMEXPAPI( "CSS_SDOServerDoCycle" ) 
#else /* DYNAMIC_LINK */
	#define USE_CSS_SDOServerDoCycle  PFCSS_SDOSERVERDOCYCLE pfCSS_SDOServerDoCycle;
	#define EXT_CSS_SDOServerDoCycle  extern PFCSS_SDOSERVERDOCYCLE pfCSS_SDOServerDoCycle;
	#define GET_CSS_SDOServerDoCycle(fl)  s_pfCMGetAPI2( "CSS_SDOServerDoCycle", (RTS_VOID_FCTPTR *)&pfCSS_SDOServerDoCycle, (fl), 0, 0)
	#define CAL_CSS_SDOServerDoCycle  pfCSS_SDOServerDoCycle
	#define CHK_CSS_SDOServerDoCycle  (pfCSS_SDOServerDoCycle != NULL)
	#define EXP_CSS_SDOServerDoCycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CSS_SDOServerDoCycle", (RTS_UINTPTR)CSS_SDOServerDoCycle, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
	RTS_IEC_XWORD Itf;
} isdohandler_struct;

/**
 * <description>ISDOHandler::HandleDownloadRequest</description>
 */
typedef struct tagisdohandler_handledownloadrequest_struct
{
	isdohandler_struct *pInstance;		/* VAR_INPUT */
	CAA_WORD wIndex;					/* VAR_INPUT */
	CAA_BYTE bySubIndex;				/* VAR_INPUT */
	CAA_SIZE szSize;					/* VAR_INPUT */
	CAA_BOOL HandleDownloadRequest;		/* VAR_OUTPUT */
	CAA_PVOID pBuffer;					/* VAR_OUTPUT */
	CAA_SIZE szBufferSize;				/* VAR_OUTPUT */
} isdohandler_handledownloadrequest_struct;

/**
 * <description>ISDOHandler::HandleUploadRequest</description>
 */
typedef struct tagisdohandler_handleuploadrequest_struct
{
	isdohandler_struct *pInstance;		/* VAR_INPUT */
	CAA_WORD wIndex;					/* VAR_INPUT */
	CAA_BYTE bySubIndex;				/* VAR_INPUT */
	CAA_BOOL HandleUploadRequest;		/* VAR_OUTPUT */
	CAA_PVOID pData;					/* VAR_OUTPUT */
	CAA_SIZE szSize;					/* VAR_OUTPUT */
} isdohandler_handleuploadrequest_struct;

/**
 * <description>ISDOHandler::EndUpload</description>
 */
typedef struct tagisdohandler_endupload_struct
{
	isdohandler_struct *pInstance;		/* VAR_INPUT */
	CAA_BOOL xSuccess;					/* VAR_INPUT */
	CAA_WORD wIndex;					/* VAR_INPUT */
	CAA_BYTE bySubIndex;				/* VAR_INPUT */
	CAA_SIZE szSize;					/* VAR_INPUT */
} isdohandler_endupload_struct;

/**
 * <description>ISDOHandler::EndDownload</description>
 */
typedef struct tagisdohandler_enddownload_struct
{
	isdohandler_struct *pInstance;		/* VAR_INPUT */
	CAA_BOOL xSuccess;					/* VAR_INPUT */
	CAA_WORD wIndex;					/* VAR_INPUT */
	CAA_BYTE bySubIndex;				/* VAR_INPUT */
	CAA_SIZE szSize;					/* VAR_INPUT */
	CAA_BOOL EndDownload;				/* VAR_OUTPUT */
	CAA_UDINT udiAbortCode;				/* VAR_OUTPUT */
} isdohandler_enddownload_struct;

/**
 * <description>sdoserveropen</description>
 */
typedef struct tagsdoserveropen_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_USINT usiNodeID;				/* VAR_INPUT */
	isdohandler_struct *pIHandler;		/* VAR_INPUT */
	CAA_ERROR *pError;					/* VAR_INPUT */
	CAA_HANDLE SDOServerOpen;			/* VAR_OUTPUT */
} sdoserveropen_struct;

void CDECL CDECL_EXT sdoserveropen(sdoserveropen_struct *p);
typedef void (CDECL CDECL_EXT* PFSDOSERVEROPEN_IEC) (sdoserveropen_struct *p);
#if defined(CMPCAASDOSERVER_NOTIMPLEMENTED) || defined(SDOSERVEROPEN_NOTIMPLEMENTED)
	#define USE_sdoserveropen
	#define EXT_sdoserveropen
	#define GET_sdoserveropen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sdoserveropen(p0) 
	#define CHK_sdoserveropen  FALSE
	#define EXP_sdoserveropen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sdoserveropen
	#define EXT_sdoserveropen
	#define GET_sdoserveropen(fl)  CAL_CMGETAPI( "sdoserveropen" ) 
	#define CAL_sdoserveropen  sdoserveropen
	#define CHK_sdoserveropen  TRUE
	#define EXP_sdoserveropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserveropen", (RTS_UINTPTR)sdoserveropen, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOSERVER_EXTERNAL)
	#define USE_sdoserveropen
	#define EXT_sdoserveropen
	#define GET_sdoserveropen(fl)  CAL_CMGETAPI( "sdoserveropen" ) 
	#define CAL_sdoserveropen  sdoserveropen
	#define CHK_sdoserveropen  TRUE
	#define EXP_sdoserveropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserveropen", (RTS_UINTPTR)sdoserveropen, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoServersdoserveropen
	#define EXT_CmpCAASdoServersdoserveropen
	#define GET_CmpCAASdoServersdoserveropen  ERR_OK
	#define CAL_CmpCAASdoServersdoserveropen  sdoserveropen
	#define CHK_CmpCAASdoServersdoserveropen  TRUE
	#define EXP_CmpCAASdoServersdoserveropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserveropen", (RTS_UINTPTR)sdoserveropen, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_sdoserveropen
	#define EXT_sdoserveropen
	#define GET_sdoserveropen(fl)  CAL_CMGETAPI( "sdoserveropen" ) 
	#define CAL_sdoserveropen  sdoserveropen
	#define CHK_sdoserveropen  TRUE
	#define EXP_sdoserveropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserveropen", (RTS_UINTPTR)sdoserveropen, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_sdoserveropen  PFSDOSERVEROPEN_IEC pfsdoserveropen;
	#define EXT_sdoserveropen  extern PFSDOSERVEROPEN_IEC pfsdoserveropen;
	#define GET_sdoserveropen(fl)  s_pfCMGetAPI2( "sdoserveropen", (RTS_VOID_FCTPTR *)&pfsdoserveropen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_sdoserveropen  pfsdoserveropen
	#define CHK_sdoserveropen  (pfsdoserveropen != NULL)
	#define EXP_sdoserveropen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserveropen", (RTS_UINTPTR)sdoserveropen, 1, 0x0, 0x0) 
#endif


/**
 * <description>sdoserverclose</description>
 */
typedef struct tagsdoserverclose_struct
{
	CAA_HANDLE hServer;			/* VAR_INPUT */
	CAA_ERROR SDOServerClose;	/* VAR_OUTPUT */
} sdoserverclose_struct;

void CDECL CDECL_EXT sdoserverclose(sdoserverclose_struct *p);
typedef void (CDECL CDECL_EXT* PFSDOSERVERCLOSE_IEC) (sdoserverclose_struct *p);
#if defined(CMPCAASDOSERVER_NOTIMPLEMENTED) || defined(SDOSERVERCLOSE_NOTIMPLEMENTED)
	#define USE_sdoserverclose
	#define EXT_sdoserverclose
	#define GET_sdoserverclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sdoserverclose(p0) 
	#define CHK_sdoserverclose  FALSE
	#define EXP_sdoserverclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sdoserverclose
	#define EXT_sdoserverclose
	#define GET_sdoserverclose(fl)  CAL_CMGETAPI( "sdoserverclose" ) 
	#define CAL_sdoserverclose  sdoserverclose
	#define CHK_sdoserverclose  TRUE
	#define EXP_sdoserverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserverclose", (RTS_UINTPTR)sdoserverclose, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOSERVER_EXTERNAL)
	#define USE_sdoserverclose
	#define EXT_sdoserverclose
	#define GET_sdoserverclose(fl)  CAL_CMGETAPI( "sdoserverclose" ) 
	#define CAL_sdoserverclose  sdoserverclose
	#define CHK_sdoserverclose  TRUE
	#define EXP_sdoserverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserverclose", (RTS_UINTPTR)sdoserverclose, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoServersdoserverclose
	#define EXT_CmpCAASdoServersdoserverclose
	#define GET_CmpCAASdoServersdoserverclose  ERR_OK
	#define CAL_CmpCAASdoServersdoserverclose  sdoserverclose
	#define CHK_CmpCAASdoServersdoserverclose  TRUE
	#define EXP_CmpCAASdoServersdoserverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserverclose", (RTS_UINTPTR)sdoserverclose, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_sdoserverclose
	#define EXT_sdoserverclose
	#define GET_sdoserverclose(fl)  CAL_CMGETAPI( "sdoserverclose" ) 
	#define CAL_sdoserverclose  sdoserverclose
	#define CHK_sdoserverclose  TRUE
	#define EXP_sdoserverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserverclose", (RTS_UINTPTR)sdoserverclose, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_sdoserverclose  PFSDOSERVERCLOSE_IEC pfsdoserverclose;
	#define EXT_sdoserverclose  extern PFSDOSERVERCLOSE_IEC pfsdoserverclose;
	#define GET_sdoserverclose(fl)  s_pfCMGetAPI2( "sdoserverclose", (RTS_VOID_FCTPTR *)&pfsdoserverclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_sdoserverclose  pfsdoserverclose
	#define CHK_sdoserverclose  (pfsdoserverclose != NULL)
	#define EXP_sdoserverclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserverclose", (RTS_UINTPTR)sdoserverclose, 1, 0x0, 0x0) 
#endif


/**
 * <description>sdoserverdocycle</description>
 */
typedef struct tagsdoserverdocycle_struct
{
	CAA_HANDLE hServer;					/* VAR_INPUT */
	CAA_ERROR SDOServerDoCycle;			/* VAR_OUTPUT */
} sdoserverdocycle_struct;

void CDECL CDECL_EXT sdoserverdocycle(sdoserverdocycle_struct *p);
typedef void (CDECL CDECL_EXT* PFSDOSERVERDOCYCLE_IEC) (sdoserverdocycle_struct *p);
#if defined(CMPCAASDOSERVER_NOTIMPLEMENTED) || defined(SDOSERVERDOCYCLE_NOTIMPLEMENTED)
	#define USE_sdoserverdocycle
	#define EXT_sdoserverdocycle
	#define GET_sdoserverdocycle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sdoserverdocycle(p0) 
	#define CHK_sdoserverdocycle  FALSE
	#define EXP_sdoserverdocycle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sdoserverdocycle
	#define EXT_sdoserverdocycle
	#define GET_sdoserverdocycle(fl)  CAL_CMGETAPI( "sdoserverdocycle" ) 
	#define CAL_sdoserverdocycle  sdoserverdocycle
	#define CHK_sdoserverdocycle  TRUE
	#define EXP_sdoserverdocycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserverdocycle", (RTS_UINTPTR)sdoserverdocycle, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAASDOSERVER_EXTERNAL)
	#define USE_sdoserverdocycle
	#define EXT_sdoserverdocycle
	#define GET_sdoserverdocycle(fl)  CAL_CMGETAPI( "sdoserverdocycle" ) 
	#define CAL_sdoserverdocycle  sdoserverdocycle
	#define CHK_sdoserverdocycle  TRUE
	#define EXP_sdoserverdocycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserverdocycle", (RTS_UINTPTR)sdoserverdocycle, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASdoServersdoserverdocycle
	#define EXT_CmpCAASdoServersdoserverdocycle
	#define GET_CmpCAASdoServersdoserverdocycle  ERR_OK
	#define CAL_CmpCAASdoServersdoserverdocycle  sdoserverdocycle
	#define CHK_CmpCAASdoServersdoserverdocycle  TRUE
	#define EXP_CmpCAASdoServersdoserverdocycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserverdocycle", (RTS_UINTPTR)sdoserverdocycle, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_sdoserverdocycle
	#define EXT_sdoserverdocycle
	#define GET_sdoserverdocycle(fl)  CAL_CMGETAPI( "sdoserverdocycle" ) 
	#define CAL_sdoserverdocycle  sdoserverdocycle
	#define CHK_sdoserverdocycle  TRUE
	#define EXP_sdoserverdocycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserverdocycle", (RTS_UINTPTR)sdoserverdocycle, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_sdoserverdocycle  PFSDOSERVERDOCYCLE_IEC pfsdoserverdocycle;
	#define EXT_sdoserverdocycle  extern PFSDOSERVERDOCYCLE_IEC pfsdoserverdocycle;
	#define GET_sdoserverdocycle(fl)  s_pfCMGetAPI2( "sdoserverdocycle", (RTS_VOID_FCTPTR *)&pfsdoserverdocycle, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_sdoserverdocycle  pfsdoserverdocycle
	#define CHK_sdoserverdocycle  (pfsdoserverdocycle != NULL)
	#define EXP_sdoserverdocycle   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sdoserverdocycle", (RTS_UINTPTR)sdoserverdocycle, 1, 0x0, 0x0) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



typedef struct
{
	IBase_C *pBase;
	PFCSS_SDOSERVEROPEN ICSS_SDOServerOpen;
 	PFCSS_SDOSERVEROPENLEGACY ICSS_SDOServerOpenLegacy;
 	PFCSS_SDOSERVERCLOSE ICSS_SDOServerClose;
 	PFCSS_SDOSERVERDOCYCLE ICSS_SDOServerDoCycle;
 } ICmpCAASdoServer_C;

#ifdef CPLUSPLUS
class ICmpCAASdoServer : public IBase
{
	public:
		virtual CAA_HANDLE CAAFKT ICSS_SDOServerOpen(CAA_HANDLE hDriver, CAA_USINT usiNodeId, CSS_CSDOHandler ISDOHandler, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CAAFKT ICSS_SDOServerOpenLegacy(CAA_HANDLE hDriver, CAA_USINT usiNodeId, CSS_CSDOHandler ISDOHandler, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CAAFKT ICSS_SDOServerClose(CAA_HANDLE hServer) =0;
		virtual CAA_ERROR CAAFKT ICSS_SDOServerDoCycle(CAA_HANDLE hServer) =0;
};
	#ifndef ITF_CmpCAASdoServer
		#define ITF_CmpCAASdoServer static ICmpCAASdoServer *pICmpCAASdoServer = NULL;
	#endif
	#define EXTITF_CmpCAASdoServer
#else	/*CPLUSPLUS*/
	typedef ICmpCAASdoServer_C		ICmpCAASdoServer;
	#ifndef ITF_CmpCAASdoServer
		#define ITF_CmpCAASdoServer
	#endif
	#define EXTITF_CmpCAASdoServer
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAASDOSERVERITF_H_*/
