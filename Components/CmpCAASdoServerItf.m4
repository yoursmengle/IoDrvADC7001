SET_INTERFACE_NAME(`CmpCAASdoServer')

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
DEF_ITF_API(`CAA_HANDLE',`CAAFKT',`CSS_SDOServerOpen',`(CAA_HANDLE hDriver, CAA_USINT usiNodeId, CSS_CSDOHandler ISDOHandler, CAA_ERROR* peError)')

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
DEF_ITF_API(`CAA_HANDLE',`CAAFKT',`CSS_SDOServerOpenLegacy',`(CAA_HANDLE hDriver, CAA_USINT usiNodeId, CSS_CSDOHandler ISDOHandler, CAA_ERROR* peError)')

/**
 * <description>
 *   Closes a SDO server and releases all resources.
 * </description>
 * <param name="hServer" type="IN">  SDO server handle </param>
 * <result> CSS_NO_ERROR if closing was successful. </result>
*/
DEF_ITF_API(`CAA_ERROR',`CAAFKT',`CSS_SDOServerClose',`(CAA_HANDLE hServer)')

/**
 * <description>
 *   Triggers a cycle for the SDO server. Call this function cyclic!
 * </description>
 * <param name="hServer" type="IN">  SDO server handle </param>
 * <result> CSS_NO_ERROR if no error occurred. </result>
*/
DEF_ITF_API(`CAA_ERROR',`CAAFKT',`CSS_SDOServerDoCycle',`(CAA_HANDLE hServer)')

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

DEF_API(`void',`CDECL',`sdoserveropen',`(sdoserveropen_struct *p)',1,0x0,0x0)

/**
 * <description>sdoserverclose</description>
 */
typedef struct tagsdoserverclose_struct
{
	CAA_HANDLE hServer;			/* VAR_INPUT */
	CAA_ERROR SDOServerClose;	/* VAR_OUTPUT */
} sdoserverclose_struct;

DEF_API(`void',`CDECL',`sdoserverclose',`(sdoserverclose_struct *p)',1,0x0,0x0)

/**
 * <description>sdoserverdocycle</description>
 */
typedef struct tagsdoserverdocycle_struct
{
	CAA_HANDLE hServer;					/* VAR_INPUT */
	CAA_ERROR SDOServerDoCycle;			/* VAR_OUTPUT */
} sdoserverdocycle_struct;

DEF_API(`void',`CDECL',`sdoserverdocycle',`(sdoserverdocycle_struct *p)',1,0x0,0x0)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
