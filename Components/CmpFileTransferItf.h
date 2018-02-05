 /**
 * <interfacename>CmpFileTransfer</interfacename>
 * <description> 
 *	This interface is specified for the file transfer component, to enable the transmission of files
 *	from and to the runtime system, to browse the directories online on the target and to handle 
 *	directories (create, delete, rename).
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPFILETRANSFERITF_H_
#define _CMPFILETRANSFERITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/**
 * <category>Alloc types</category>
 * <description>Alloc types for the file name</description>
 */
#define FILENAME_STATIC		0
#define FILENAME_DYNAMIC	1

/**
 * <category>Transfer types</category>
 * <description>Type of file transfer</description>
 */
#define FT_UPLOAD			0
#define FT_DOWNLOAD			1

/**
 * <category>Transfer types</category>
 * <description>Type of file transfer notification</description>
 */
#define FT_SYNC_FILE_BEGIN_APP			0x01
#define FT_SYNC_FILE_END_APP			0x02
#define FT_SYNC_FILE_BEING_DEVICE		0x03
#define FT_SYNC_FILE_END_DEVICE			0x04
#define FT_FILE_BEGIN_LOGIN_APP			0x05
#define FT_FILE_END_LOGIN_APP			0x06
#define FT_FILE_BEGIN_OEM				0x07
#define FT_FILE_END_OEM					0x08

/**
 * <category>Static defines</category>
 * <description>Number of static transfers possible</description>
 */
#ifndef FT_NUM_OF_STATIC_TANSFERS
	#define FT_NUM_OF_STATIC_TANSFERS	4
#endif

/**
 * <category>Static defines</category>
 * <description>Extension for files during download sequence. This extension is removed at the end of the successful transfer or renamed into
 *	FT_BACKUP_FILE_EXTENSION, if origin file is occupied with a parallel running file transfer.
 *	NOTE:
 *	If this extension is defined empty "", no rename of the transferred file is done. FT_BACKUP_FILE_EXTENSION must be defined empty too!
 * </description>
 */
#ifndef FT_TEMP_FILE_EXTENSION
	#define FT_TEMP_FILE_EXTENSION		".tmp"
#endif

/**
 * <category>Static defines</category>
 * <description>Extension for files after successful file download. The extension is removed, if the still running file transfer on the source file ends.
 *	NOTE:
 *	If this extension is defined empty "", no rename of the transferred file is done. FT_TEMP_FILE_EXTENSION must be defined empty too!
 * </description>
 */
#ifndef FT_BACKUP_FILE_EXTENSION
	#define FT_BACKUP_FILE_EXTENSION	".bak"
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Handle all file transfer services asynchronously.
 * </description>
 */
#define FTKEY_INT_ASYNC_SERVICES					"AsyncServices"
#ifndef FTVALUE_INT_ASYNC_SERVICES_DEFAULT
	#define FTVALUE_INT_ASYNC_SERVICES_DEFAULT		0
#endif


typedef struct
{
	RTS_UI32 ulCRC32;
	RTS_UI32 ulSize;
} FileInfo;

typedef struct
{
	int iAllocType;
	RTS_SIZE iMaxLen;
	char *pszName;
	char sz[64];
} FileName;

typedef struct
{
	RTS_HANDLE hFile;
	RTS_SIZE ulTransferred;
	RTS_UI32 ulSessionId;
	RTS_UI32 ulOnlineCRC32;
	FileInfo fi;
	FileName fn;
	int iTransferType;
} FileTransfer;

/**
 * <category>Operations</category>
 * <description>Operations of the file transfer component. Can be disabled with the event CMPID_CmpMgr::EVT_CmpMgr_DisableOperation!</description>
 */
#define OP_FILE_TRANSFER_DOWNLOAD				1
#define OP_FILE_TRANSFER_UPLOAD					2
#define OP_FILE_TRANSFER_DELETE_FILE			3
#define OP_FILE_TRANSFER_RENAME_FILE			4
#define OP_FILE_TRANSFER_CREATE_DIRECTORY		5
#define OP_FILE_TRANSFER_DELETE_DIRECTORY		6
#define OP_FILE_TRANSFER_RENAME_DIRECTORY		7

/**
 * <category>Event parameter</category>
 * <element name="pszFileName" type="IN">File name that is transferred</element>
 * <element name="pInfo" type="IN">Pointer to actual file info</element>
 * <element name="usType" type="IN">File transfer type. See category "Transfer types" for details.</element>
 * <element name="bBegin" type="IN">bBegin=1: Begin of the file transfer, bBegin=0: End of the file transfer</element>
 * <element name="pszPlaceHolderFileName" type="IN">File name including any place holder path. Optional, may be NULL.</element>
 */
typedef struct
{
	char *pszFileName;
	FileInfo *pInfo;
	unsigned short usType;
	char bBegin;
	char *pszPlaceHolderFileName;
} EVTPARAM_CmpFileTransfer;
#define EVTPARAMID_CmpFileTransfer		0x0001
#define EVTVERSION_CmpFileTransfer		0x0002


/**
 * <category>Events</category>
 * <description>Event is sent at each begin and end of a filetransfer</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpFileTransfer</param>
 */
#define EVT_FileTransfer				MAKE_EVENTID(EVTCLASS_INFO, 1)



/**
 * <category>Event parameter</category>
 * <element name="pszApplicationName" type="IN">Application name for which the files are being transferred.</element>
 * <element name="usType" type="IN">Synchronized file transfer type. See category "Transfer types" for details.</element>
 */
typedef struct
{
	char *pszApplicationName;
	RTS_UI16 usType;
} EVTPARAM_CmpSyncFileTransfer;
#define EVTPARAMID_CmpSyncFileTransfer		0x0002
#define EVTVERSION_CmpSyncFileTransfer		0x0001

/**
 * <category>Events</category>
 * <description>
 * This event is sent before and after synchronized files are downloaded. 
 * Typically this occurs after an application download or online change.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpSyncFileTransfer</param>
 */
#define EVT_SyncFileTransfer				MAKE_EVENTID(EVTCLASS_INFO, 2)



/**
 * <category>Online services</category>
 * <description>
 *	Online services for the file transfer
 * </description>
 */
#define SRVFT_GET_FILEINFO			0x01	
#define SRVFT_START_DOWNLOAD		0x02
#define SRVFT_RESTART_DOWNLOAD		0x03
#define SRVFT_DOWNLOAD				0x04
#define SRVFT_START_UPLOAD			0x05
#define SRVFT_RESTART_UPLOAD		0x06
#define SRVFT_UPLOAD				0x07
#define SRVFT_END					0x08
#define SRVFT_CANCEL				0x09
#define SRVFT_SAFE_SIGNATURE		0x0A
#define SRVFT_GET_SAFED_SIGNATURE	0x0B
#define SRVFT_GET_DIRECTORYINFO		0x0C
#define SRVFT_GET_DIRECTORYINFO_CANCEL	0x0D
#define SRVFT_DELETE_FILE			0x0E
#define SRVFT_RENAME_FILE			0x0F
#define SRVFT_CREATE_DIRECTORY		0x10
#define SRVFT_DELETE_DIRECTORY		0x11
#define SRVFT_RENAME_DIRECTORY		0x12
#define SRVFT_GET_FREE_DISK_SPACE	0x13	/* Not implemented, only sent by CDS >= V3.5.1.0 and < V3.5.1.30 */
#define SRVFT_SYNC_FILE_TRANSFER	0x14

#define FTT_DOWNLOAD				1
#define FTT_UPLOAD					2

/**
 * <category>Online reply tags</category>
 * <description>
 * </description>
 */
#define TAG_REPLY_FILEINFO			0x81
#define TAG_FILENAME				0x01
#define TAG_FILEINFO				0x02
#define TAG_SESSIONID				0x03

#define TAG_STARTINFO				0x04
#define TAG_REPLY_STARTINFO			0x84
#define TAG_DATA					0x05
#define TAG_REPLY_DATAACK			0x05
#define TAG_DATASIZE				0x06
#define TAG_REPLY_DATASIZE			0x06
#define TAG_END						0x07
#define TAG_REPLY_ENDACK			0x07
#define TAG_REPLY_ERROR				0x08
#define TAG_REPLY_GET_SAFED_SIGNATURE	0x09
#define TAG_REPLY_GET_FILENAME		0x0A

#define TAG_DIRECTORY_NAME			0x0B
#define TAG_DIRECTORY_HANDLE		0x0C
#define TAG_REPLY_DIRECTORY_INFO	0x8D
#define TAG_ENTRY_NAME				0x0E
#define TAG_DIRECTORY_INFO			0x0F
#define TAG_FILETRANSFER_TYPE		0x10
#define TAG_DIRECTORY_EXTRAINFO		0x11
#define TAG_REPLY_DIRECTORY_HANDLE	0x1F
#define TAG_DIR_ENTRY               0x90

/**
 * <category>Directory extra info flags</category>
 * <description>
 * Bits for the bitvector submitted via TAG_DIRECTORY_EXTRAINFO.
 * All other bits are reserved and may be used for future extensions.
 * </description>
 * <element name="TDEI_PLACEHOLDER" type="IN">Entry is a placeholder</element>
 * <element name="TDEI_REDUNDANT" type="IN">Entry is redundant, i.e. links to a subdirectory in the default path</element>
 */
#define TDEI_PLACEHOLDER			0x00000001
#define TDEI_REDUNDANT				0x00000002

/**
 * <category>Static defines</category>
 * <description>Predefined objects in the runtime</description>
 */
#define USERDB_OBJECT_ROOTDIRECTORY	"/"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Creates a file transfer download object to transfer a file from client to target</description>
 * <param name="pszFileName" type="IN">File name (can have a file path)</param>
 * <param name="pInfo" type="IN">File info of the file to be transmitted from the client</param>
 * <param name="ulSessionId" type="IN">SessionId (can be the channelid) of the transfer</param>
 * <param name="bRestart" type="IN">1: the file transfer will be continued, 0: start of the file transfer from the beginning</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the file transfer object</result>
 */
RTS_HANDLE CDECL FileTransferStartDownload(char *pszFileName, FileInfo *pInfo, RTS_UI32 ulSessionId, int bRestart, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFFILETRANSFERSTARTDOWNLOAD) (char *pszFileName, FileInfo *pInfo, RTS_UI32 ulSessionId, int bRestart, RTS_RESULT *pResult);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERSTARTDOWNLOAD_NOTIMPLEMENTED)
	#define USE_FileTransferStartDownload
	#define EXT_FileTransferStartDownload
	#define GET_FileTransferStartDownload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferStartDownload(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_FileTransferStartDownload  FALSE
	#define EXP_FileTransferStartDownload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferStartDownload
	#define EXT_FileTransferStartDownload
	#define GET_FileTransferStartDownload(fl)  CAL_CMGETAPI( "FileTransferStartDownload" ) 
	#define CAL_FileTransferStartDownload  FileTransferStartDownload
	#define CHK_FileTransferStartDownload  TRUE
	#define EXP_FileTransferStartDownload  CAL_CMEXPAPI( "FileTransferStartDownload" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferStartDownload
	#define EXT_FileTransferStartDownload
	#define GET_FileTransferStartDownload(fl)  CAL_CMGETAPI( "FileTransferStartDownload" ) 
	#define CAL_FileTransferStartDownload  FileTransferStartDownload
	#define CHK_FileTransferStartDownload  TRUE
	#define EXP_FileTransferStartDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferStartDownload", (RTS_UINTPTR)FileTransferStartDownload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferStartDownload
	#define EXT_CmpFileTransferFileTransferStartDownload
	#define GET_CmpFileTransferFileTransferStartDownload  ERR_OK
	#define CAL_CmpFileTransferFileTransferStartDownload CCmpFileTransfer::IFileTransferStartDownload
	#define CHK_CmpFileTransferFileTransferStartDownload  TRUE
	#define EXP_CmpFileTransferFileTransferStartDownload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferStartDownload
	#define EXT_FileTransferStartDownload
	#define GET_FileTransferStartDownload(fl)  CAL_CMGETAPI( "FileTransferStartDownload" ) 
	#define CAL_FileTransferStartDownload CCmpFileTransfer::IFileTransferStartDownload
	#define CHK_FileTransferStartDownload  TRUE
	#define EXP_FileTransferStartDownload  CAL_CMEXPAPI( "FileTransferStartDownload" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferStartDownload  PFFILETRANSFERSTARTDOWNLOAD pfFileTransferStartDownload;
	#define EXT_FileTransferStartDownload  extern PFFILETRANSFERSTARTDOWNLOAD pfFileTransferStartDownload;
	#define GET_FileTransferStartDownload(fl)  s_pfCMGetAPI2( "FileTransferStartDownload", (RTS_VOID_FCTPTR *)&pfFileTransferStartDownload, (fl), 0, 0)
	#define CAL_FileTransferStartDownload  pfFileTransferStartDownload
	#define CHK_FileTransferStartDownload  (pfFileTransferStartDownload != NULL)
	#define EXP_FileTransferStartDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferStartDownload", (RTS_UINTPTR)FileTransferStartDownload, 0, 0) 
#endif




/**
 * <description>Transfer file data to the target</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <param name="pbyData" type="IN">Data to transfer into the file</param>
 * <param name="ulLen" type="IN">Number of bytes to transfer</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FileTransferDownload(RTS_HANDLE hFiletransfer, unsigned char *pbyData, RTS_SIZE ulLen);
typedef RTS_RESULT (CDECL * PFFILETRANSFERDOWNLOAD) (RTS_HANDLE hFiletransfer, unsigned char *pbyData, RTS_SIZE ulLen);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERDOWNLOAD_NOTIMPLEMENTED)
	#define USE_FileTransferDownload
	#define EXT_FileTransferDownload
	#define GET_FileTransferDownload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferDownload(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FileTransferDownload  FALSE
	#define EXP_FileTransferDownload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferDownload
	#define EXT_FileTransferDownload
	#define GET_FileTransferDownload(fl)  CAL_CMGETAPI( "FileTransferDownload" ) 
	#define CAL_FileTransferDownload  FileTransferDownload
	#define CHK_FileTransferDownload  TRUE
	#define EXP_FileTransferDownload  CAL_CMEXPAPI( "FileTransferDownload" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferDownload
	#define EXT_FileTransferDownload
	#define GET_FileTransferDownload(fl)  CAL_CMGETAPI( "FileTransferDownload" ) 
	#define CAL_FileTransferDownload  FileTransferDownload
	#define CHK_FileTransferDownload  TRUE
	#define EXP_FileTransferDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferDownload", (RTS_UINTPTR)FileTransferDownload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferDownload
	#define EXT_CmpFileTransferFileTransferDownload
	#define GET_CmpFileTransferFileTransferDownload  ERR_OK
	#define CAL_CmpFileTransferFileTransferDownload CCmpFileTransfer::IFileTransferDownload
	#define CHK_CmpFileTransferFileTransferDownload  TRUE
	#define EXP_CmpFileTransferFileTransferDownload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferDownload
	#define EXT_FileTransferDownload
	#define GET_FileTransferDownload(fl)  CAL_CMGETAPI( "FileTransferDownload" ) 
	#define CAL_FileTransferDownload CCmpFileTransfer::IFileTransferDownload
	#define CHK_FileTransferDownload  TRUE
	#define EXP_FileTransferDownload  CAL_CMEXPAPI( "FileTransferDownload" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferDownload  PFFILETRANSFERDOWNLOAD pfFileTransferDownload;
	#define EXT_FileTransferDownload  extern PFFILETRANSFERDOWNLOAD pfFileTransferDownload;
	#define GET_FileTransferDownload(fl)  s_pfCMGetAPI2( "FileTransferDownload", (RTS_VOID_FCTPTR *)&pfFileTransferDownload, (fl), 0, 0)
	#define CAL_FileTransferDownload  pfFileTransferDownload
	#define CHK_FileTransferDownload  (pfFileTransferDownload != NULL)
	#define EXP_FileTransferDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferDownload", (RTS_UINTPTR)FileTransferDownload, 0, 0) 
#endif




/**
 * <description>Finish file transfer download</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FileTransferEndDownload(RTS_HANDLE hFiletransfer);
typedef RTS_RESULT (CDECL * PFFILETRANSFERENDDOWNLOAD) (RTS_HANDLE hFiletransfer);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERENDDOWNLOAD_NOTIMPLEMENTED)
	#define USE_FileTransferEndDownload
	#define EXT_FileTransferEndDownload
	#define GET_FileTransferEndDownload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferEndDownload(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FileTransferEndDownload  FALSE
	#define EXP_FileTransferEndDownload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferEndDownload
	#define EXT_FileTransferEndDownload
	#define GET_FileTransferEndDownload(fl)  CAL_CMGETAPI( "FileTransferEndDownload" ) 
	#define CAL_FileTransferEndDownload  FileTransferEndDownload
	#define CHK_FileTransferEndDownload  TRUE
	#define EXP_FileTransferEndDownload  CAL_CMEXPAPI( "FileTransferEndDownload" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferEndDownload
	#define EXT_FileTransferEndDownload
	#define GET_FileTransferEndDownload(fl)  CAL_CMGETAPI( "FileTransferEndDownload" ) 
	#define CAL_FileTransferEndDownload  FileTransferEndDownload
	#define CHK_FileTransferEndDownload  TRUE
	#define EXP_FileTransferEndDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferEndDownload", (RTS_UINTPTR)FileTransferEndDownload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferEndDownload
	#define EXT_CmpFileTransferFileTransferEndDownload
	#define GET_CmpFileTransferFileTransferEndDownload  ERR_OK
	#define CAL_CmpFileTransferFileTransferEndDownload CCmpFileTransfer::IFileTransferEndDownload
	#define CHK_CmpFileTransferFileTransferEndDownload  TRUE
	#define EXP_CmpFileTransferFileTransferEndDownload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferEndDownload
	#define EXT_FileTransferEndDownload
	#define GET_FileTransferEndDownload(fl)  CAL_CMGETAPI( "FileTransferEndDownload" ) 
	#define CAL_FileTransferEndDownload CCmpFileTransfer::IFileTransferEndDownload
	#define CHK_FileTransferEndDownload  TRUE
	#define EXP_FileTransferEndDownload  CAL_CMEXPAPI( "FileTransferEndDownload" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferEndDownload  PFFILETRANSFERENDDOWNLOAD pfFileTransferEndDownload;
	#define EXT_FileTransferEndDownload  extern PFFILETRANSFERENDDOWNLOAD pfFileTransferEndDownload;
	#define GET_FileTransferEndDownload(fl)  s_pfCMGetAPI2( "FileTransferEndDownload", (RTS_VOID_FCTPTR *)&pfFileTransferEndDownload, (fl), 0, 0)
	#define CAL_FileTransferEndDownload  pfFileTransferEndDownload
	#define CHK_FileTransferEndDownload  (pfFileTransferEndDownload != NULL)
	#define EXP_FileTransferEndDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferEndDownload", (RTS_UINTPTR)FileTransferEndDownload, 0, 0) 
#endif




/**
 * <description>Creates a file transfer upload object to transfer a file from target to client</description>
 * <param name="pszFileName" type="IN">File name (can have a file path)</param>
 * <param name="pInfo" type="IN">File info of the file to be transmitted to the client</param>
 * <param name="ulSessionId" type="IN">SessionId (can be the channelid) of the transfer</param>
 * <param name="bRestart" type="IN">1: the file transfer will be continued, 0: start of the file transfer from the beginning</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the file transfer object</result>
 */
RTS_HANDLE CDECL FileTransferStartUpload(char *pszFileName, FileInfo *pInfo, RTS_UI32 ulSessionId, int bRestart, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFFILETRANSFERSTARTUPLOAD) (char *pszFileName, FileInfo *pInfo, RTS_UI32 ulSessionId, int bRestart, RTS_RESULT *pResult);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERSTARTUPLOAD_NOTIMPLEMENTED)
	#define USE_FileTransferStartUpload
	#define EXT_FileTransferStartUpload
	#define GET_FileTransferStartUpload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferStartUpload(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_FileTransferStartUpload  FALSE
	#define EXP_FileTransferStartUpload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferStartUpload
	#define EXT_FileTransferStartUpload
	#define GET_FileTransferStartUpload(fl)  CAL_CMGETAPI( "FileTransferStartUpload" ) 
	#define CAL_FileTransferStartUpload  FileTransferStartUpload
	#define CHK_FileTransferStartUpload  TRUE
	#define EXP_FileTransferStartUpload  CAL_CMEXPAPI( "FileTransferStartUpload" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferStartUpload
	#define EXT_FileTransferStartUpload
	#define GET_FileTransferStartUpload(fl)  CAL_CMGETAPI( "FileTransferStartUpload" ) 
	#define CAL_FileTransferStartUpload  FileTransferStartUpload
	#define CHK_FileTransferStartUpload  TRUE
	#define EXP_FileTransferStartUpload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferStartUpload", (RTS_UINTPTR)FileTransferStartUpload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferStartUpload
	#define EXT_CmpFileTransferFileTransferStartUpload
	#define GET_CmpFileTransferFileTransferStartUpload  ERR_OK
	#define CAL_CmpFileTransferFileTransferStartUpload CCmpFileTransfer::IFileTransferStartUpload
	#define CHK_CmpFileTransferFileTransferStartUpload  TRUE
	#define EXP_CmpFileTransferFileTransferStartUpload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferStartUpload
	#define EXT_FileTransferStartUpload
	#define GET_FileTransferStartUpload(fl)  CAL_CMGETAPI( "FileTransferStartUpload" ) 
	#define CAL_FileTransferStartUpload CCmpFileTransfer::IFileTransferStartUpload
	#define CHK_FileTransferStartUpload  TRUE
	#define EXP_FileTransferStartUpload  CAL_CMEXPAPI( "FileTransferStartUpload" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferStartUpload  PFFILETRANSFERSTARTUPLOAD pfFileTransferStartUpload;
	#define EXT_FileTransferStartUpload  extern PFFILETRANSFERSTARTUPLOAD pfFileTransferStartUpload;
	#define GET_FileTransferStartUpload(fl)  s_pfCMGetAPI2( "FileTransferStartUpload", (RTS_VOID_FCTPTR *)&pfFileTransferStartUpload, (fl), 0, 0)
	#define CAL_FileTransferStartUpload  pfFileTransferStartUpload
	#define CHK_FileTransferStartUpload  (pfFileTransferStartUpload != NULL)
	#define EXP_FileTransferStartUpload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferStartUpload", (RTS_UINTPTR)FileTransferStartUpload, 0, 0) 
#endif




/**
 * <description>Transfer file data to the client</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <param name="pbyData" type="IN">Data to transfer from the file</param>
 * <param name="pulMaxLen" type="INOUT">Number of bytes to transfer, returns the real number of transferred bytes</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FileTransferUpload(RTS_HANDLE hFiletransfer, unsigned char *pbyData, RTS_SIZE *pulMaxLen);
typedef RTS_RESULT (CDECL * PFFILETRANSFERUPLOAD) (RTS_HANDLE hFiletransfer, unsigned char *pbyData, RTS_SIZE *pulMaxLen);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERUPLOAD_NOTIMPLEMENTED)
	#define USE_FileTransferUpload
	#define EXT_FileTransferUpload
	#define GET_FileTransferUpload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferUpload(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FileTransferUpload  FALSE
	#define EXP_FileTransferUpload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferUpload
	#define EXT_FileTransferUpload
	#define GET_FileTransferUpload(fl)  CAL_CMGETAPI( "FileTransferUpload" ) 
	#define CAL_FileTransferUpload  FileTransferUpload
	#define CHK_FileTransferUpload  TRUE
	#define EXP_FileTransferUpload  CAL_CMEXPAPI( "FileTransferUpload" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferUpload
	#define EXT_FileTransferUpload
	#define GET_FileTransferUpload(fl)  CAL_CMGETAPI( "FileTransferUpload" ) 
	#define CAL_FileTransferUpload  FileTransferUpload
	#define CHK_FileTransferUpload  TRUE
	#define EXP_FileTransferUpload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferUpload", (RTS_UINTPTR)FileTransferUpload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferUpload
	#define EXT_CmpFileTransferFileTransferUpload
	#define GET_CmpFileTransferFileTransferUpload  ERR_OK
	#define CAL_CmpFileTransferFileTransferUpload CCmpFileTransfer::IFileTransferUpload
	#define CHK_CmpFileTransferFileTransferUpload  TRUE
	#define EXP_CmpFileTransferFileTransferUpload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferUpload
	#define EXT_FileTransferUpload
	#define GET_FileTransferUpload(fl)  CAL_CMGETAPI( "FileTransferUpload" ) 
	#define CAL_FileTransferUpload CCmpFileTransfer::IFileTransferUpload
	#define CHK_FileTransferUpload  TRUE
	#define EXP_FileTransferUpload  CAL_CMEXPAPI( "FileTransferUpload" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferUpload  PFFILETRANSFERUPLOAD pfFileTransferUpload;
	#define EXT_FileTransferUpload  extern PFFILETRANSFERUPLOAD pfFileTransferUpload;
	#define GET_FileTransferUpload(fl)  s_pfCMGetAPI2( "FileTransferUpload", (RTS_VOID_FCTPTR *)&pfFileTransferUpload, (fl), 0, 0)
	#define CAL_FileTransferUpload  pfFileTransferUpload
	#define CHK_FileTransferUpload  (pfFileTransferUpload != NULL)
	#define EXP_FileTransferUpload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferUpload", (RTS_UINTPTR)FileTransferUpload, 0, 0) 
#endif




/**
 * <description>Finish file transfer upload</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <param name="pFileInfo" type="OUT">Returns the file info of the uploaded file. Can be used to check the consistence on the upload side.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FileTransferEndUpload(RTS_HANDLE hFiletransfer, FileInfo *pFileInfo);
typedef RTS_RESULT (CDECL * PFFILETRANSFERENDUPLOAD) (RTS_HANDLE hFiletransfer, FileInfo *pFileInfo);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERENDUPLOAD_NOTIMPLEMENTED)
	#define USE_FileTransferEndUpload
	#define EXT_FileTransferEndUpload
	#define GET_FileTransferEndUpload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferEndUpload(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FileTransferEndUpload  FALSE
	#define EXP_FileTransferEndUpload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferEndUpload
	#define EXT_FileTransferEndUpload
	#define GET_FileTransferEndUpload(fl)  CAL_CMGETAPI( "FileTransferEndUpload" ) 
	#define CAL_FileTransferEndUpload  FileTransferEndUpload
	#define CHK_FileTransferEndUpload  TRUE
	#define EXP_FileTransferEndUpload  CAL_CMEXPAPI( "FileTransferEndUpload" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferEndUpload
	#define EXT_FileTransferEndUpload
	#define GET_FileTransferEndUpload(fl)  CAL_CMGETAPI( "FileTransferEndUpload" ) 
	#define CAL_FileTransferEndUpload  FileTransferEndUpload
	#define CHK_FileTransferEndUpload  TRUE
	#define EXP_FileTransferEndUpload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferEndUpload", (RTS_UINTPTR)FileTransferEndUpload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferEndUpload
	#define EXT_CmpFileTransferFileTransferEndUpload
	#define GET_CmpFileTransferFileTransferEndUpload  ERR_OK
	#define CAL_CmpFileTransferFileTransferEndUpload CCmpFileTransfer::IFileTransferEndUpload
	#define CHK_CmpFileTransferFileTransferEndUpload  TRUE
	#define EXP_CmpFileTransferFileTransferEndUpload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferEndUpload
	#define EXT_FileTransferEndUpload
	#define GET_FileTransferEndUpload(fl)  CAL_CMGETAPI( "FileTransferEndUpload" ) 
	#define CAL_FileTransferEndUpload CCmpFileTransfer::IFileTransferEndUpload
	#define CHK_FileTransferEndUpload  TRUE
	#define EXP_FileTransferEndUpload  CAL_CMEXPAPI( "FileTransferEndUpload" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferEndUpload  PFFILETRANSFERENDUPLOAD pfFileTransferEndUpload;
	#define EXT_FileTransferEndUpload  extern PFFILETRANSFERENDUPLOAD pfFileTransferEndUpload;
	#define GET_FileTransferEndUpload(fl)  s_pfCMGetAPI2( "FileTransferEndUpload", (RTS_VOID_FCTPTR *)&pfFileTransferEndUpload, (fl), 0, 0)
	#define CAL_FileTransferEndUpload  pfFileTransferEndUpload
	#define CHK_FileTransferEndUpload  (pfFileTransferEndUpload != NULL)
	#define EXP_FileTransferEndUpload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferEndUpload", (RTS_UINTPTR)FileTransferEndUpload, 0, 0) 
#endif




/**
 * <description>Close a file transfer</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FileTransferClose(RTS_HANDLE hFiletransfer);
typedef RTS_RESULT (CDECL * PFFILETRANSFERCLOSE) (RTS_HANDLE hFiletransfer);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERCLOSE_NOTIMPLEMENTED)
	#define USE_FileTransferClose
	#define EXT_FileTransferClose
	#define GET_FileTransferClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FileTransferClose  FALSE
	#define EXP_FileTransferClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferClose
	#define EXT_FileTransferClose
	#define GET_FileTransferClose(fl)  CAL_CMGETAPI( "FileTransferClose" ) 
	#define CAL_FileTransferClose  FileTransferClose
	#define CHK_FileTransferClose  TRUE
	#define EXP_FileTransferClose  CAL_CMEXPAPI( "FileTransferClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferClose
	#define EXT_FileTransferClose
	#define GET_FileTransferClose(fl)  CAL_CMGETAPI( "FileTransferClose" ) 
	#define CAL_FileTransferClose  FileTransferClose
	#define CHK_FileTransferClose  TRUE
	#define EXP_FileTransferClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferClose", (RTS_UINTPTR)FileTransferClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferClose
	#define EXT_CmpFileTransferFileTransferClose
	#define GET_CmpFileTransferFileTransferClose  ERR_OK
	#define CAL_CmpFileTransferFileTransferClose CCmpFileTransfer::IFileTransferClose
	#define CHK_CmpFileTransferFileTransferClose  TRUE
	#define EXP_CmpFileTransferFileTransferClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferClose
	#define EXT_FileTransferClose
	#define GET_FileTransferClose(fl)  CAL_CMGETAPI( "FileTransferClose" ) 
	#define CAL_FileTransferClose CCmpFileTransfer::IFileTransferClose
	#define CHK_FileTransferClose  TRUE
	#define EXP_FileTransferClose  CAL_CMEXPAPI( "FileTransferClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferClose  PFFILETRANSFERCLOSE pfFileTransferClose;
	#define EXT_FileTransferClose  extern PFFILETRANSFERCLOSE pfFileTransferClose;
	#define GET_FileTransferClose(fl)  s_pfCMGetAPI2( "FileTransferClose", (RTS_VOID_FCTPTR *)&pfFileTransferClose, (fl), 0, 0)
	#define CAL_FileTransferClose  pfFileTransferClose
	#define CHK_FileTransferClose  (pfFileTransferClose != NULL)
	#define EXP_FileTransferClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferClose", (RTS_UINTPTR)FileTransferClose, 0, 0) 
#endif




/**
 * <description>Cancel and abort a file transfer</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FileTransferCancel(RTS_HANDLE hFiletransfer);
typedef RTS_RESULT (CDECL * PFFILETRANSFERCANCEL) (RTS_HANDLE hFiletransfer);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERCANCEL_NOTIMPLEMENTED)
	#define USE_FileTransferCancel
	#define EXT_FileTransferCancel
	#define GET_FileTransferCancel(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferCancel(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FileTransferCancel  FALSE
	#define EXP_FileTransferCancel  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferCancel
	#define EXT_FileTransferCancel
	#define GET_FileTransferCancel(fl)  CAL_CMGETAPI( "FileTransferCancel" ) 
	#define CAL_FileTransferCancel  FileTransferCancel
	#define CHK_FileTransferCancel  TRUE
	#define EXP_FileTransferCancel  CAL_CMEXPAPI( "FileTransferCancel" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferCancel
	#define EXT_FileTransferCancel
	#define GET_FileTransferCancel(fl)  CAL_CMGETAPI( "FileTransferCancel" ) 
	#define CAL_FileTransferCancel  FileTransferCancel
	#define CHK_FileTransferCancel  TRUE
	#define EXP_FileTransferCancel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferCancel", (RTS_UINTPTR)FileTransferCancel, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferCancel
	#define EXT_CmpFileTransferFileTransferCancel
	#define GET_CmpFileTransferFileTransferCancel  ERR_OK
	#define CAL_CmpFileTransferFileTransferCancel CCmpFileTransfer::IFileTransferCancel
	#define CHK_CmpFileTransferFileTransferCancel  TRUE
	#define EXP_CmpFileTransferFileTransferCancel  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferCancel
	#define EXT_FileTransferCancel
	#define GET_FileTransferCancel(fl)  CAL_CMGETAPI( "FileTransferCancel" ) 
	#define CAL_FileTransferCancel CCmpFileTransfer::IFileTransferCancel
	#define CHK_FileTransferCancel  TRUE
	#define EXP_FileTransferCancel  CAL_CMEXPAPI( "FileTransferCancel" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferCancel  PFFILETRANSFERCANCEL pfFileTransferCancel;
	#define EXT_FileTransferCancel  extern PFFILETRANSFERCANCEL pfFileTransferCancel;
	#define GET_FileTransferCancel(fl)  s_pfCMGetAPI2( "FileTransferCancel", (RTS_VOID_FCTPTR *)&pfFileTransferCancel, (fl), 0, 0)
	#define CAL_FileTransferCancel  pfFileTransferCancel
	#define CHK_FileTransferCancel  (pfFileTransferCancel != NULL)
	#define EXP_FileTransferCancel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferCancel", (RTS_UINTPTR)FileTransferCancel, 0, 0) 
#endif




/**
 * <description>Cancel and abort all file transfers on the specified sessionid (channelid)</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FileTransferCancelAll(RTS_UI32 ulSessionId);
typedef RTS_RESULT (CDECL * PFFILETRANSFERCANCELALL) (RTS_UI32 ulSessionId);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERCANCELALL_NOTIMPLEMENTED)
	#define USE_FileTransferCancelAll
	#define EXT_FileTransferCancelAll
	#define GET_FileTransferCancelAll(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferCancelAll(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FileTransferCancelAll  FALSE
	#define EXP_FileTransferCancelAll  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferCancelAll
	#define EXT_FileTransferCancelAll
	#define GET_FileTransferCancelAll(fl)  CAL_CMGETAPI( "FileTransferCancelAll" ) 
	#define CAL_FileTransferCancelAll  FileTransferCancelAll
	#define CHK_FileTransferCancelAll  TRUE
	#define EXP_FileTransferCancelAll  CAL_CMEXPAPI( "FileTransferCancelAll" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferCancelAll
	#define EXT_FileTransferCancelAll
	#define GET_FileTransferCancelAll(fl)  CAL_CMGETAPI( "FileTransferCancelAll" ) 
	#define CAL_FileTransferCancelAll  FileTransferCancelAll
	#define CHK_FileTransferCancelAll  TRUE
	#define EXP_FileTransferCancelAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferCancelAll", (RTS_UINTPTR)FileTransferCancelAll, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferCancelAll
	#define EXT_CmpFileTransferFileTransferCancelAll
	#define GET_CmpFileTransferFileTransferCancelAll  ERR_OK
	#define CAL_CmpFileTransferFileTransferCancelAll CCmpFileTransfer::IFileTransferCancelAll
	#define CHK_CmpFileTransferFileTransferCancelAll  TRUE
	#define EXP_CmpFileTransferFileTransferCancelAll  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferCancelAll
	#define EXT_FileTransferCancelAll
	#define GET_FileTransferCancelAll(fl)  CAL_CMGETAPI( "FileTransferCancelAll" ) 
	#define CAL_FileTransferCancelAll CCmpFileTransfer::IFileTransferCancelAll
	#define CHK_FileTransferCancelAll  TRUE
	#define EXP_FileTransferCancelAll  CAL_CMEXPAPI( "FileTransferCancelAll" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferCancelAll  PFFILETRANSFERCANCELALL pfFileTransferCancelAll;
	#define EXT_FileTransferCancelAll  extern PFFILETRANSFERCANCELALL pfFileTransferCancelAll;
	#define GET_FileTransferCancelAll(fl)  s_pfCMGetAPI2( "FileTransferCancelAll", (RTS_VOID_FCTPTR *)&pfFileTransferCancelAll, (fl), 0, 0)
	#define CAL_FileTransferCancelAll  pfFileTransferCancelAll
	#define CHK_FileTransferCancelAll  (pfFileTransferCancelAll != NULL)
	#define EXP_FileTransferCancelAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferCancelAll", (RTS_UINTPTR)FileTransferCancelAll, 0, 0) 
#endif




/**
 * <description>Get file infos from target and client</description>
 * <param name="pszFileName" type="IN">File name (can have a file path)</param>
 * <param name="pInfo" type="OUT">File info of the file in the target</param>
 * <param name="pInfoClient" type="IN">File info of the file at the client</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FileTransferGetInfo(char *pszFileName, FileInfo *pInfo, FileInfo *pInfoClient);
typedef RTS_RESULT (CDECL * PFFILETRANSFERGETINFO) (char *pszFileName, FileInfo *pInfo, FileInfo *pInfoClient);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERGETINFO_NOTIMPLEMENTED)
	#define USE_FileTransferGetInfo
	#define EXT_FileTransferGetInfo
	#define GET_FileTransferGetInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferGetInfo(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FileTransferGetInfo  FALSE
	#define EXP_FileTransferGetInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferGetInfo
	#define EXT_FileTransferGetInfo
	#define GET_FileTransferGetInfo(fl)  CAL_CMGETAPI( "FileTransferGetInfo" ) 
	#define CAL_FileTransferGetInfo  FileTransferGetInfo
	#define CHK_FileTransferGetInfo  TRUE
	#define EXP_FileTransferGetInfo  CAL_CMEXPAPI( "FileTransferGetInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferGetInfo
	#define EXT_FileTransferGetInfo
	#define GET_FileTransferGetInfo(fl)  CAL_CMGETAPI( "FileTransferGetInfo" ) 
	#define CAL_FileTransferGetInfo  FileTransferGetInfo
	#define CHK_FileTransferGetInfo  TRUE
	#define EXP_FileTransferGetInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferGetInfo", (RTS_UINTPTR)FileTransferGetInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferGetInfo
	#define EXT_CmpFileTransferFileTransferGetInfo
	#define GET_CmpFileTransferFileTransferGetInfo  ERR_OK
	#define CAL_CmpFileTransferFileTransferGetInfo CCmpFileTransfer::IFileTransferGetInfo
	#define CHK_CmpFileTransferFileTransferGetInfo  TRUE
	#define EXP_CmpFileTransferFileTransferGetInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferGetInfo
	#define EXT_FileTransferGetInfo
	#define GET_FileTransferGetInfo(fl)  CAL_CMGETAPI( "FileTransferGetInfo" ) 
	#define CAL_FileTransferGetInfo CCmpFileTransfer::IFileTransferGetInfo
	#define CHK_FileTransferGetInfo  TRUE
	#define EXP_FileTransferGetInfo  CAL_CMEXPAPI( "FileTransferGetInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferGetInfo  PFFILETRANSFERGETINFO pfFileTransferGetInfo;
	#define EXT_FileTransferGetInfo  extern PFFILETRANSFERGETINFO pfFileTransferGetInfo;
	#define GET_FileTransferGetInfo(fl)  s_pfCMGetAPI2( "FileTransferGetInfo", (RTS_VOID_FCTPTR *)&pfFileTransferGetInfo, (fl), 0, 0)
	#define CAL_FileTransferGetInfo  pfFileTransferGetInfo
	#define CHK_FileTransferGetInfo  (pfFileTransferGetInfo != NULL)
	#define EXP_FileTransferGetInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferGetInfo", (RTS_UINTPTR)FileTransferGetInfo, 0, 0) 
#endif




/**
 * <description>Get number of bytes to transmit</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes to transmit</result>
 */
RTS_SIZE CDECL FileTransferToTransmit(RTS_HANDLE hFiletransfer, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFFILETRANSFERTOTRANSMIT) (RTS_HANDLE hFiletransfer, RTS_RESULT *pResult);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERTOTRANSMIT_NOTIMPLEMENTED)
	#define USE_FileTransferToTransmit
	#define EXT_FileTransferToTransmit
	#define GET_FileTransferToTransmit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferToTransmit(p0,p1)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_FileTransferToTransmit  FALSE
	#define EXP_FileTransferToTransmit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferToTransmit
	#define EXT_FileTransferToTransmit
	#define GET_FileTransferToTransmit(fl)  CAL_CMGETAPI( "FileTransferToTransmit" ) 
	#define CAL_FileTransferToTransmit  FileTransferToTransmit
	#define CHK_FileTransferToTransmit  TRUE
	#define EXP_FileTransferToTransmit  CAL_CMEXPAPI( "FileTransferToTransmit" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferToTransmit
	#define EXT_FileTransferToTransmit
	#define GET_FileTransferToTransmit(fl)  CAL_CMGETAPI( "FileTransferToTransmit" ) 
	#define CAL_FileTransferToTransmit  FileTransferToTransmit
	#define CHK_FileTransferToTransmit  TRUE
	#define EXP_FileTransferToTransmit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferToTransmit", (RTS_UINTPTR)FileTransferToTransmit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferToTransmit
	#define EXT_CmpFileTransferFileTransferToTransmit
	#define GET_CmpFileTransferFileTransferToTransmit  ERR_OK
	#define CAL_CmpFileTransferFileTransferToTransmit CCmpFileTransfer::IFileTransferToTransmit
	#define CHK_CmpFileTransferFileTransferToTransmit  TRUE
	#define EXP_CmpFileTransferFileTransferToTransmit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferToTransmit
	#define EXT_FileTransferToTransmit
	#define GET_FileTransferToTransmit(fl)  CAL_CMGETAPI( "FileTransferToTransmit" ) 
	#define CAL_FileTransferToTransmit CCmpFileTransfer::IFileTransferToTransmit
	#define CHK_FileTransferToTransmit  TRUE
	#define EXP_FileTransferToTransmit  CAL_CMEXPAPI( "FileTransferToTransmit" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferToTransmit  PFFILETRANSFERTOTRANSMIT pfFileTransferToTransmit;
	#define EXT_FileTransferToTransmit  extern PFFILETRANSFERTOTRANSMIT pfFileTransferToTransmit;
	#define GET_FileTransferToTransmit(fl)  s_pfCMGetAPI2( "FileTransferToTransmit", (RTS_VOID_FCTPTR *)&pfFileTransferToTransmit, (fl), 0, 0)
	#define CAL_FileTransferToTransmit  pfFileTransferToTransmit
	#define CHK_FileTransferToTransmit  (pfFileTransferToTransmit != NULL)
	#define EXP_FileTransferToTransmit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferToTransmit", (RTS_UINTPTR)FileTransferToTransmit, 0, 0) 
#endif




/**
 * <description>Safe signature of a specified file to check consistency</description>
 * <param name="pszFileName" type="IN">File name (can have a file path)</param>
 * <param name="ulCRC32" type="IN">CRC32 of the file</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FileTransferSafeSignature(char *pszFileName, RTS_UI32 ulCRC32);
typedef RTS_RESULT (CDECL * PFFILETRANSFERSAFESIGNATURE) (char *pszFileName, RTS_UI32 ulCRC32);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERSAFESIGNATURE_NOTIMPLEMENTED)
	#define USE_FileTransferSafeSignature
	#define EXT_FileTransferSafeSignature
	#define GET_FileTransferSafeSignature(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferSafeSignature(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FileTransferSafeSignature  FALSE
	#define EXP_FileTransferSafeSignature  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferSafeSignature
	#define EXT_FileTransferSafeSignature
	#define GET_FileTransferSafeSignature(fl)  CAL_CMGETAPI( "FileTransferSafeSignature" ) 
	#define CAL_FileTransferSafeSignature  FileTransferSafeSignature
	#define CHK_FileTransferSafeSignature  TRUE
	#define EXP_FileTransferSafeSignature  CAL_CMEXPAPI( "FileTransferSafeSignature" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferSafeSignature
	#define EXT_FileTransferSafeSignature
	#define GET_FileTransferSafeSignature(fl)  CAL_CMGETAPI( "FileTransferSafeSignature" ) 
	#define CAL_FileTransferSafeSignature  FileTransferSafeSignature
	#define CHK_FileTransferSafeSignature  TRUE
	#define EXP_FileTransferSafeSignature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferSafeSignature", (RTS_UINTPTR)FileTransferSafeSignature, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferSafeSignature
	#define EXT_CmpFileTransferFileTransferSafeSignature
	#define GET_CmpFileTransferFileTransferSafeSignature  ERR_OK
	#define CAL_CmpFileTransferFileTransferSafeSignature CCmpFileTransfer::IFileTransferSafeSignature
	#define CHK_CmpFileTransferFileTransferSafeSignature  TRUE
	#define EXP_CmpFileTransferFileTransferSafeSignature  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferSafeSignature
	#define EXT_FileTransferSafeSignature
	#define GET_FileTransferSafeSignature(fl)  CAL_CMGETAPI( "FileTransferSafeSignature" ) 
	#define CAL_FileTransferSafeSignature CCmpFileTransfer::IFileTransferSafeSignature
	#define CHK_FileTransferSafeSignature  TRUE
	#define EXP_FileTransferSafeSignature  CAL_CMEXPAPI( "FileTransferSafeSignature" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferSafeSignature  PFFILETRANSFERSAFESIGNATURE pfFileTransferSafeSignature;
	#define EXT_FileTransferSafeSignature  extern PFFILETRANSFERSAFESIGNATURE pfFileTransferSafeSignature;
	#define GET_FileTransferSafeSignature(fl)  s_pfCMGetAPI2( "FileTransferSafeSignature", (RTS_VOID_FCTPTR *)&pfFileTransferSafeSignature, (fl), 0, 0)
	#define CAL_FileTransferSafeSignature  pfFileTransferSafeSignature
	#define CHK_FileTransferSafeSignature  (pfFileTransferSafeSignature != NULL)
	#define EXP_FileTransferSafeSignature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferSafeSignature", (RTS_UINTPTR)FileTransferSafeSignature, 0, 0) 
#endif




/**
 * <description>Get safed signature of a specified file to check consistency</description>
 * <param name="pszFileName" type="IN">File name (can have a file path)</param>
 * <param name="pulCRC32" type="OUT">Pointer to get CRC32 of the file</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FileTransferGetSafedSignature(char *pszFileName, RTS_UI32 *pulCRC32);
typedef RTS_RESULT (CDECL * PFFILETRANSFERGETSAFEDSIGNATURE) (char *pszFileName, RTS_UI32 *pulCRC32);
#if defined(CMPFILETRANSFER_NOTIMPLEMENTED) || defined(FILETRANSFERGETSAFEDSIGNATURE_NOTIMPLEMENTED)
	#define USE_FileTransferGetSafedSignature
	#define EXT_FileTransferGetSafedSignature
	#define GET_FileTransferGetSafedSignature(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FileTransferGetSafedSignature(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FileTransferGetSafedSignature  FALSE
	#define EXP_FileTransferGetSafedSignature  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FileTransferGetSafedSignature
	#define EXT_FileTransferGetSafedSignature
	#define GET_FileTransferGetSafedSignature(fl)  CAL_CMGETAPI( "FileTransferGetSafedSignature" ) 
	#define CAL_FileTransferGetSafedSignature  FileTransferGetSafedSignature
	#define CHK_FileTransferGetSafedSignature  TRUE
	#define EXP_FileTransferGetSafedSignature  CAL_CMEXPAPI( "FileTransferGetSafedSignature" ) 
#elif defined(MIXED_LINK) && !defined(CMPFILETRANSFER_EXTERNAL)
	#define USE_FileTransferGetSafedSignature
	#define EXT_FileTransferGetSafedSignature
	#define GET_FileTransferGetSafedSignature(fl)  CAL_CMGETAPI( "FileTransferGetSafedSignature" ) 
	#define CAL_FileTransferGetSafedSignature  FileTransferGetSafedSignature
	#define CHK_FileTransferGetSafedSignature  TRUE
	#define EXP_FileTransferGetSafedSignature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferGetSafedSignature", (RTS_UINTPTR)FileTransferGetSafedSignature, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpFileTransferFileTransferGetSafedSignature
	#define EXT_CmpFileTransferFileTransferGetSafedSignature
	#define GET_CmpFileTransferFileTransferGetSafedSignature  ERR_OK
	#define CAL_CmpFileTransferFileTransferGetSafedSignature CCmpFileTransfer::IFileTransferGetSafedSignature
	#define CHK_CmpFileTransferFileTransferGetSafedSignature  TRUE
	#define EXP_CmpFileTransferFileTransferGetSafedSignature  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FileTransferGetSafedSignature
	#define EXT_FileTransferGetSafedSignature
	#define GET_FileTransferGetSafedSignature(fl)  CAL_CMGETAPI( "FileTransferGetSafedSignature" ) 
	#define CAL_FileTransferGetSafedSignature CCmpFileTransfer::IFileTransferGetSafedSignature
	#define CHK_FileTransferGetSafedSignature  TRUE
	#define EXP_FileTransferGetSafedSignature  CAL_CMEXPAPI( "FileTransferGetSafedSignature" ) 
#else /* DYNAMIC_LINK */
	#define USE_FileTransferGetSafedSignature  PFFILETRANSFERGETSAFEDSIGNATURE pfFileTransferGetSafedSignature;
	#define EXT_FileTransferGetSafedSignature  extern PFFILETRANSFERGETSAFEDSIGNATURE pfFileTransferGetSafedSignature;
	#define GET_FileTransferGetSafedSignature(fl)  s_pfCMGetAPI2( "FileTransferGetSafedSignature", (RTS_VOID_FCTPTR *)&pfFileTransferGetSafedSignature, (fl), 0, 0)
	#define CAL_FileTransferGetSafedSignature  pfFileTransferGetSafedSignature
	#define CHK_FileTransferGetSafedSignature  (pfFileTransferGetSafedSignature != NULL)
	#define EXP_FileTransferGetSafedSignature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FileTransferGetSafedSignature", (RTS_UINTPTR)FileTransferGetSafedSignature, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFFILETRANSFERSTARTDOWNLOAD IFileTransferStartDownload;
 	PFFILETRANSFERDOWNLOAD IFileTransferDownload;
 	PFFILETRANSFERENDDOWNLOAD IFileTransferEndDownload;
 	PFFILETRANSFERSTARTUPLOAD IFileTransferStartUpload;
 	PFFILETRANSFERUPLOAD IFileTransferUpload;
 	PFFILETRANSFERENDUPLOAD IFileTransferEndUpload;
 	PFFILETRANSFERCLOSE IFileTransferClose;
 	PFFILETRANSFERCANCEL IFileTransferCancel;
 	PFFILETRANSFERCANCELALL IFileTransferCancelAll;
 	PFFILETRANSFERGETINFO IFileTransferGetInfo;
 	PFFILETRANSFERTOTRANSMIT IFileTransferToTransmit;
 	PFFILETRANSFERSAFESIGNATURE IFileTransferSafeSignature;
 	PFFILETRANSFERGETSAFEDSIGNATURE IFileTransferGetSafedSignature;
 } ICmpFileTransfer_C;

#ifdef CPLUSPLUS
class ICmpFileTransfer : public IBase
{
	public:
		static RTS_HANDLE CDECL IFileTransferStartDownload(char *pszFileName, FileInfo *pInfo, RTS_UI32 ulSessionId, int bRestart, RTS_RESULT *pResult);
		static RTS_RESULT CDECL IFileTransferDownload(RTS_HANDLE hFiletransfer, unsigned char *pbyData, RTS_SIZE ulLen);
		static RTS_RESULT CDECL IFileTransferEndDownload(RTS_HANDLE hFiletransfer);
		static RTS_HANDLE CDECL IFileTransferStartUpload(char *pszFileName, FileInfo *pInfo, RTS_UI32 ulSessionId, int bRestart, RTS_RESULT *pResult);
		static RTS_RESULT CDECL IFileTransferUpload(RTS_HANDLE hFiletransfer, unsigned char *pbyData, RTS_SIZE *pulMaxLen);
		static RTS_RESULT CDECL IFileTransferEndUpload(RTS_HANDLE hFiletransfer, FileInfo *pFileInfo);
		static RTS_RESULT CDECL IFileTransferClose(RTS_HANDLE hFiletransfer);
		static RTS_RESULT CDECL IFileTransferCancel(RTS_HANDLE hFiletransfer);
		static RTS_RESULT CDECL IFileTransferCancelAll(RTS_UI32 ulSessionId);
		static RTS_RESULT CDECL IFileTransferGetInfo(char *pszFileName, FileInfo *pInfo, FileInfo *pInfoClient);
		static RTS_SIZE CDECL IFileTransferToTransmit(RTS_HANDLE hFiletransfer, RTS_RESULT *pResult);
		static RTS_RESULT CDECL IFileTransferSafeSignature(char *pszFileName, RTS_UI32 ulCRC32);
		static RTS_RESULT CDECL IFileTransferGetSafedSignature(char *pszFileName, RTS_UI32 *pulCRC32);
};
	#ifndef ITF_CmpFileTransfer
		#define ITF_CmpFileTransfer static ICmpFileTransfer *pICmpFileTransfer = NULL;
	#endif
	#define EXTITF_CmpFileTransfer
#else	/*CPLUSPLUS*/
	typedef ICmpFileTransfer_C		ICmpFileTransfer;
	#ifndef ITF_CmpFileTransfer
		#define ITF_CmpFileTransfer
	#endif
	#define EXTITF_CmpFileTransfer
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPFILETRANSFERITF_H_*/
