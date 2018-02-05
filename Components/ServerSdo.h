/*****************************************************************************
*
*	Copyright:	© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		ServerSdo.h
*	Version:		2.4
*	Purpose:		Implementation of Server side CANopen service data object protocol.
*
******************************************************************************/

#ifdef CAALib

#include "CAADefines.h"
#include "CmpCAASdoServerItf.h"

#ifdef CAA_CL2

#ifndef _SERVER_SDO_H_
#define _SERVER_SDO_H_

#include "CAATypes.h"

#define SDO_PRIO 1

#define SDO_TIMEOUT (1000000UL) /* 1 Sec Timeout in uSec */
#define CSS_SET_ERROR(pError,ErrorCode) if(pError) *pError = ErrorCode;

typedef struct sdo_buffer_info_tag
{
	CAA_PVOID pBuffer;
	CAA_SIZE szBufferSize;
} SDO_BUFFER_INFO;

typedef CAA_BOOL (CDECL *PFIECDOWNLOADHANDLERFUNCTION)(CAA_WORD wIndex, CAA_BYTE bySubIndex, CAA_SIZE szSize);
typedef CAA_BOOL (CDECL *PFDOWNLOADHANDLERFUNCTION)(CAA_WORD wIndex, CAA_BYTE bySubIndex, CAA_SIZE szSize, SDO_BUFFER_INFO* pBufferInfo);

typedef CAA_BOOL (CDECL *PFIECUPLOADHANDLERFUNCTION)(CAA_WORD wIndex, CAA_BYTE bySubIndex);
typedef CAA_BOOL (CDECL *PFUPLOADHANDLERFUNCTION)(CAA_WORD wIndex, CAA_BYTE bySubIndex, SDO_BUFFER_INFO* pBufferInfo);

typedef void (CDECL *PFIECENDUPLOADFUNCTION)(CAA_BOOL xSuccess, CAA_WORD wIndex, CAA_BYTE bySubIndex, CAA_SIZE szSize);
typedef void (CDECL *PFENDUPLOADFUNCTION)(CAA_BOOL xSuccess, CAA_WORD wIndex, CAA_BYTE bySubIndex, CAA_SIZE szSize);

typedef void (CDECL *PFIECENDDOWNLOADFUNCTION)(CAA_BOOL xSuccess, CAA_WORD wIndex, CAA_BYTE bySubIndex, CAA_SIZE szSize);
typedef CAA_BOOL (CDECL *PFENDDOWNLOADFUNCTION)(CAA_BOOL xSuccess, CAA_WORD wIndex, CAA_BYTE bySubIndex, CAA_SIZE szSize, CAA_UDINT * pudiAbortCode);

typedef struct sdo_sdohandler_tag
{
	CAA_HANDLE hInstance;
	CAA_PVOID IHandleDownloadRequest;
	CAA_PVOID IHandleUploadRequest;
	CAA_PVOID IEndUpload;
	CAA_PVOID IEndDownload;
	CAA_ENUM eSDOEvent;
} CSS_SDOHandler;

typedef struct sdo_csdohandler_tag
{
	PFDOWNLOADHANDLERFUNCTION IHandleDownloadRequest;
	PFUPLOADHANDLERFUNCTION IHandleUploadRequest;
	PFENDUPLOADFUNCTION IEndUpload;
	PFENDDOWNLOADFUNCTION IEndDownload;
	CAA_ENUM eSDOEvent;
} CSS_CSDOHandler;

typedef struct sdo_object_tag
{
	CAA_WORD		wIndex;
	CAA_BYTE		bySubIndex;
	CAA_SIZE		szSize;

	CAA_PVOID		pucData;
	CAA_SIZE		szBufferSize;
	CAA_SIZE		szBytesFinished;
	CAA_SIZE		szBlockBytesFinished;
} SDO_OBJECT;

CAA_HANDLE SDOServerOpen(CAA_HANDLE hDriver, CAA_USINT usiNodeId, CSS_SDOHandler SDOHandler, CAA_ERROR* peError, CAA_BOOL xIEC);
CAA_ERROR SDOServerClose(CAA_HANDLE hServer);
CAA_ERROR SDOServerDoCycle(CAA_HANDLE hServer);

#endif /* _SERVER_SDO_H_ */
#endif /* CAA_CL2 */
#endif /* CAALib */
